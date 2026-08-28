"""Integer-programming recovery of ML-DSA ``s1`` from four-value samples.

This module adapts the downstream solver in ``14_ilp_solve.py`` from the
``rej_2026_D2_SCA_package`` artifact.  Each rejected ``(c, z)`` pair gives one
bounded linear row on a single polynomial of ``s1``.  The four (or more, for
other parameter sets) polynomials are solved independently with SciPy/HiGHS.

Despite sometimes being called the "NLP" route in experiment notes, the
reference implementation is an ILP: all 256 secret coefficients are integral
and bounded to ``[-eta, eta]``.  The original interval formulation is retained,
and an equivalent bounded-noise equality formulation can convert every source
row into two upper-bound inequalities before calling SciPy/HiGHS.
"""

from __future__ import annotations

from dataclasses import dataclass
from time import perf_counter

import numpy as np
from scipy.optimize import Bounds, LinearConstraint, milp

from bp_attack import InequalitySample
from mldsa_model import MLDSAParams, row_terms
from rcoi_noisy_equality import convert_rcoi_rows_to_inequalities


ILP_FORMULATIONS = ("interval", "noisy-equality")


@dataclass(frozen=True)
class PolyILPResult:
    formulation: str
    source_rows: int
    solver_rows: int
    recovered: np.ndarray | None
    elapsed_seconds: float
    status: int
    success: bool
    feasible_integer_solution: bool
    message: str
    objective_value: float | None
    mip_gap: float | None
    mip_node_count: int | None
    interval_violations: int | None


@dataclass(frozen=True)
class ILPSolveResult:
    formulation: str
    recovered: np.ndarray
    elapsed_seconds: float
    rows_by_poly: list[int]
    poly_results: list[PolyILPResult]
    has_solution_by_poly: list[bool]
    mismatches_by_poly: list[int | None]
    total_mismatches: int | None
    interval_violations: int | None
    exact_recovery: bool


def dense_row_for_sample(
    params: MLDSAParams,
    sample: InequalitySample,
) -> np.ndarray:
    """Return the negacyclic convolution row used by the reference ILP."""

    row = np.zeros(params.n, dtype=np.float64)
    columns, values = row_terms(params, sample.challenge, sample.coeff_index)
    for column, value in zip(columns, values):
        row[int(column)] += int(value)
    return row


def normalize_ilp_formulation(formulation: str) -> str:
    normalized = str(formulation).strip().lower().replace("_", "-")
    aliases = {
        "interval": "interval",
        "original": "interval",
        "noisy-equality": "noisy-equality",
        "equality": "noisy-equality",
        "noisy-eq": "noisy-equality",
    }
    try:
        return aliases[normalized]
    except KeyError as exc:
        raise ValueError(
            f"unsupported ILP formulation {formulation!r}; "
            f"choose one of {ILP_FORMULATIONS}"
        ) from exc


def build_poly_problem(
    params: MLDSAParams,
    samples: list[InequalitySample],
    poly_index: int,
) -> tuple[np.ndarray, np.ndarray, np.ndarray]:
    """Build ``A``, lower bounds and upper bounds for one ``s1`` polynomial."""

    selected = [sample for sample in samples if sample.poly_index == poly_index]
    if not selected:
        raise ValueError(f"no constraints for s1 polynomial {poly_index}")
    matrix = np.vstack([dense_row_for_sample(params, sample) for sample in selected])
    lower = np.asarray([sample.lower for sample in selected], dtype=np.float64)
    upper = np.asarray([sample.upper for sample in selected], dtype=np.float64)
    if np.any(lower > upper):
        first = int(np.flatnonzero(lower > upper)[0])
        raise ValueError(
            f"empty interval in polynomial {poly_index}, row {first}: "
            f"[{lower[first]},{upper[first]}]"
        )
    return matrix, lower, upper


def _optional_float(result, name: str) -> float | None:
    value = getattr(result, name, None)
    return None if value is None else float(value)


def _optional_int(result, name: str) -> int | None:
    value = getattr(result, name, None)
    return None if value is None else int(value)


def solve_poly_ilp(
    params: MLDSAParams,
    samples: list[InequalitySample],
    poly_index: int,
    time_limit: float | None = 120.0,
    formulation: str = "interval",
) -> PolyILPResult:
    """Solve one integer program using interval or noisy-equality constraints.

    The all-ones objective intentionally matches the reference implementation.
    It gives HiGHS an LP bound for branch-and-bound; it is not information about
    the secret.  A result returned at a time limit is accepted only when the
    rounded integer vector satisfies every supplied source interval.  The
    noisy-equality mode is restricted to exact four-value RCoI samples.
    """

    if time_limit is not None and time_limit <= 0:
        raise ValueError("time_limit must be positive or None")
    formulation = normalize_ilp_formulation(formulation)
    selected = [sample for sample in samples if sample.poly_index == poly_index]
    matrix, lower, upper = build_poly_problem(params, samples, poly_index)
    if formulation == "noisy-equality":
        converted = convert_rcoi_rows_to_inequalities(
            params=params,
            rows=matrix,
            samples=selected,
        )
        model_constraint = LinearConstraint(
            converted.matrix,
            -np.inf,
            converted.upper_bounds,
        )
        solver_rows = int(converted.matrix.shape[0])
    else:
        model_constraint = LinearConstraint(matrix, lower, upper)
        solver_rows = int(matrix.shape[0])
    options: dict[str, float] = {}
    if time_limit is not None:
        options["time_limit"] = float(time_limit)

    started = perf_counter()
    result = milp(
        c=np.ones(params.n, dtype=np.float64),
        integrality=np.ones(params.n, dtype=np.uint8),
        bounds=Bounds(-params.eta, params.eta),
        constraints=[model_constraint],
        options=options,
    )
    elapsed = perf_counter() - started

    recovered: np.ndarray | None = None
    violations: int | None = None
    feasible = False
    if result.x is not None:
        candidate = np.rint(np.asarray(result.x, dtype=np.float64)).astype(np.int16)
        if candidate.shape == (params.n,) and np.all(
            (candidate >= -params.eta) & (candidate <= params.eta)
        ):
            products = matrix @ candidate.astype(np.float64)
            violations = int(np.count_nonzero((products < lower) | (products > upper)))
            feasible = violations == 0
            if feasible:
                recovered = candidate

    return PolyILPResult(
        formulation=formulation,
        source_rows=int(matrix.shape[0]),
        solver_rows=solver_rows,
        recovered=recovered,
        elapsed_seconds=elapsed,
        status=int(result.status),
        success=bool(result.success),
        feasible_integer_solution=feasible,
        message=str(result.message),
        objective_value=_optional_float(result, "fun"),
        mip_gap=_optional_float(result, "mip_gap"),
        mip_node_count=_optional_int(result, "mip_node_count"),
        interval_violations=violations,
    )


def solve_secret_ilp(
    params: MLDSAParams,
    samples: list[InequalitySample],
    secret: np.ndarray,
    time_limit_per_poly: float | None = 120.0,
    formulation: str = "interval",
) -> ILPSolveResult:
    """Solve every polynomial independently and evaluate against ``secret``."""

    formulation = normalize_ilp_formulation(formulation)
    secret = np.asarray(secret, dtype=np.int16)
    expected_shape = (params.ell, params.n)
    if secret.shape != expected_shape:
        raise ValueError(f"secret shape is {secret.shape}, expected {expected_shape}")

    rows_by_poly = [
        sum(sample.poly_index == poly for sample in samples)
        for poly in range(params.ell)
    ]
    if any(count == 0 for count in rows_by_poly):
        raise ValueError(f"every polynomial needs constraints, got {rows_by_poly}")

    started = perf_counter()
    poly_results = [
        solve_poly_ilp(
            params=params,
            samples=samples,
            poly_index=poly,
            time_limit=time_limit_per_poly,
            formulation=formulation,
        )
        for poly in range(params.ell)
    ]
    elapsed = perf_counter() - started

    sentinel = np.iinfo(np.int16).min
    recovered = np.full(expected_shape, sentinel, dtype=np.int16)
    has_solution: list[bool] = []
    mismatches_by_poly: list[int | None] = []
    violation_values: list[int] = []
    for poly, poly_result in enumerate(poly_results):
        available = poly_result.recovered is not None
        has_solution.append(available)
        if not available:
            mismatches_by_poly.append(None)
            continue
        recovered[poly] = poly_result.recovered
        mismatches_by_poly.append(int(np.count_nonzero(recovered[poly] != secret[poly])))
        violation_values.append(int(poly_result.interval_violations or 0))

    all_available = all(has_solution)
    total_mismatches = (
        int(sum(value for value in mismatches_by_poly if value is not None))
        if all_available
        else None
    )
    interval_violations = int(sum(violation_values)) if all_available else None
    exact = bool(all_available and total_mismatches == 0)
    return ILPSolveResult(
        formulation=formulation,
        recovered=recovered,
        elapsed_seconds=elapsed,
        rows_by_poly=rows_by_poly,
        poly_results=poly_results,
        has_solution_by_poly=has_solution,
        mismatches_by_poly=mismatches_by_poly,
        total_mismatches=total_mismatches,
        interval_violations=interval_violations,
        exact_recovery=exact,
    )
