"""Collect skipped-z constraints and recover s1 with the requested BP solver."""

from __future__ import annotations

import sys
from dataclasses import dataclass, replace
from pathlib import Path
from time import perf_counter

import numpy as np

from mldsa_model import (
    Challenge,
    MLDSAParams,
    row_terms,
    sample_challenge,
    sample_y,
    sparse_product,
)


_MODULE_DIR = Path(__file__).resolve().parent
_SOLVER_FILENAME = "ILWE_all_solvers_hillclimb_ref_param.py"
_LOCAL_SOLVER_FILE = _MODULE_DIR / _SOLVER_FILENAME
_SIBLING_SOLVER_FILE = _MODULE_DIR.parent / "CLWE_Solve" / _SOLVER_FILENAME

# A packaged Attack_s1 directory keeps the BP wrapper beside this module.
# Preserve compatibility with the original repository layout, where the same
# wrapper lives in a sibling CLWE_Solve directory.
CLWE_SOLVER_FILE = (
    _LOCAL_SOLVER_FILE
    if _LOCAL_SOLVER_FILE.is_file()
    else _SIBLING_SOLVER_FILE
)
CLWE_SOLVER_DIR = CLWE_SOLVER_FILE.parent
if str(CLWE_SOLVER_DIR) not in sys.path:
    sys.path.insert(0, str(CLWE_SOLVER_DIR))

try:
    from ILWE_all_solvers_hillclimb_ref_param import (  # type: ignore
        HINT_SOLVER_IMPORT_ERROR,
        normalize_dist,
        solve_bp,
    )
except Exception as exc:  # reported clearly when solve_secret_bp is called
    HINT_SOLVER_IMPORT_ERROR = exc
    normalize_dist = None
    solve_bp = None


@dataclass(frozen=True)
class InequalitySample:
    signature_index: int
    challenge: Challenge
    poly_index: int
    coeff_index: int
    z_value: int
    lower: int
    upper: int
    side: str
    constraint_kind: str
    y_value: int | None
    shifted_z: int | None
    shifted_y: int | None
    equality_rhs: int | None
    conversion_rhs: int | None = None
    slack_sign: int | None = None
    slack_lower: int | None = None
    slack_upper: int | None = None
    nominal_rhs: int | None = None
    error_lower: int | None = None
    error_upper: int | None = None


@dataclass(frozen=True)
class CollectionResult:
    samples: list[InequalitySample]
    signatures_generated: int
    useful_signatures: int
    rows_by_poly: list[int]
    positive_rows: int
    negative_rows: int
    rejected_attempts: int = 0


@dataclass(frozen=True)
class SolveResult:
    recovered: np.ndarray
    elapsed_seconds: float
    rows_by_poly: list[int]
    mismatches_by_poly: list[int]
    total_mismatches: int
    interval_violations: int
    exact_recovery: bool


def resolve_threshold(params: MLDSAParams, specification: str) -> int:
    text = str(specification).strip().lower()
    aliases = {
        "gamma1-beta": params.gamma1 - params.beta,
        "gamma1": params.gamma1,
    }
    if text in aliases:
        return aliases[text]
    try:
        threshold = int(text)
    except ValueError as exc:
        raise ValueError(
            "threshold must be gamma1-beta, gamma1, or a positive integer"
        ) from exc
    if threshold <= 0:
        raise ValueError("threshold must be positive")
    return threshold


def inequalities_from_z(
    params: MLDSAParams,
    challenge: Challenge,
    z: np.ndarray,
    threshold: int,
    signature_index: int,
    remaining_by_poly: list[int | None],
    one_per_signature: bool = False,
) -> list[InequalitySample]:
    """Select boundary coefficients and derive exact integer constraints.

    Since z_i = (c*s1)_i + y_i and y_i is in
    [-gamma1+1, gamma1], every selected row implies

        z_i-gamma1 <= (c*s1)_i <= z_i+gamma1-1.

    The interval is clipped to the natural bound eta*tau.  For a positive
    boundary observation this leaves an informative lower inequality; for a
    negative observation it leaves an informative upper inequality.
    """

    if threshold <= 0:
        raise ValueError("threshold must be positive")
    z = np.asarray(z)
    if z.shape != (params.ell, params.n):
        raise ValueError(f"z shape is {z.shape}, expected {(params.ell, params.n)}")

    selected: list[InequalitySample] = []
    natural_bound = params.inner_product_bound
    for poly_index, coeff_index in np.argwhere(np.abs(z) >= threshold):
        poly = int(poly_index)
        if remaining_by_poly[poly] is not None and remaining_by_poly[poly] <= 0:
            continue

        z_value = int(z[poly, int(coeff_index)])
        lower = max(z_value - params.y_high, -natural_bound)
        upper = min(z_value - params.y_low, natural_bound)
        if lower > upper:
            raise RuntimeError(
                f"generated observation has empty feasible interval [{lower}, {upper}]"
            )

        # Rows equal to the full natural interval do not constrain s1.
        if lower == -natural_bound and upper == natural_bound:
            continue

        selected.append(
            InequalitySample(
                signature_index=int(signature_index),
                challenge=challenge,
                poly_index=poly,
                coeff_index=int(coeff_index),
                z_value=z_value,
                lower=int(lower),
                upper=int(upper),
                side="positive" if z_value >= 0 else "negative",
                constraint_kind="inequality",
                y_value=None,
                shifted_z=None,
                shifted_y=None,
                equality_rhs=None,
            )
        )
        if remaining_by_poly[poly] is not None:
            remaining_by_poly[poly] -= 1
        if one_per_signature:
            break
    return selected


def rcoi_inequalities_from_z(
    params: MLDSAParams,
    challenge: Challenge,
    z: np.ndarray,
    signature_index: int,
    remaining_by_poly: list[int | None],
    one_per_signature: bool = True,
) -> list[InequalitySample]:
    """Select the four RCoI response values used by the rejected-pair attack.

    The supplied side-channel artifact labels exactly four response classes:

    ``+gamma1``, ``+gamma1-1``, ``-gamma1`` and ``-gamma1-1``.

    For unknown ``y`` in ``[-gamma1+1, gamma1]`` these values imply the four
    intervals from Theorem 1.  Values farther beyond the raw boundary are not
    RCoIs and are deliberately excluded, even though they would also give a
    valid generic inequality.
    """

    z = np.asarray(z)
    expected_shape = (params.ell, params.n)
    if z.shape != expected_shape:
        raise ValueError(f"z shape is {z.shape}, expected {expected_shape}")

    natural_bound = params.inner_product_bound
    target_bounds = {
        params.gamma1: (0, natural_bound),
        params.gamma1 - 1: (-1, natural_bound),
        -params.gamma1: (-natural_bound, -1),
        -params.gamma1 - 1: (-natural_bound, -2),
    }
    selected: list[InequalitySample] = []
    target_values = np.asarray(list(target_bounds), dtype=z.dtype)
    if one_per_signature:
        # poly_chknorm scans in flattened polynomial/coefficient order and
        # returns at the first coefficient outside gamma1-beta.  A signing
        # attempt is an RCoI attempt only when that first aborting value is one
        # of the four target values.
        aborting = np.argwhere(np.abs(z) >= params.gamma1 - params.beta)
        candidates = aborting[:1]
    else:
        # Useful for a skipped-check synthetic baseline: retain every target
        # coefficient, including values after the first would-be abort.
        candidates = np.argwhere(np.isin(z, target_values))

    for poly_index, coeff_index in candidates:
        poly = int(poly_index)
        coeff = int(coeff_index)
        z_value = int(z[poly, coeff])
        if z_value not in target_bounds:
            continue
        if remaining_by_poly[poly] is not None and remaining_by_poly[poly] <= 0:
            continue
        lower, upper = target_bounds[z_value]
        selected.append(
            InequalitySample(
                signature_index=int(signature_index),
                challenge=challenge,
                poly_index=poly,
                coeff_index=coeff,
                z_value=z_value,
                lower=int(lower),
                upper=int(upper),
                side="positive" if z_value >= 0 else "negative",
                constraint_kind="rcoi-inequality",
                y_value=None,
                shifted_z=None,
                shifted_y=None,
                equality_rhs=None,
            )
        )
        if remaining_by_poly[poly] is not None:
            remaining_by_poly[poly] -= 1
        if one_per_signature:
            break
    return selected


def boundary_equalities_from_z(
    params: MLDSAParams,
    challenge: Challenge,
    z: np.ndarray,
    y: np.ndarray,
    signature_index: int,
    remaining_by_poly: list[int | None],
    one_per_signature: bool = False,
) -> list[InequalitySample]:
    """Build exact BP equalities from coefficients outside the gamma1 boundary.

    The two requested forms are

        z_i >=  gamma1: (c*s1)_i = (z_i-gamma1) - (y_i-gamma1)
        z_i <= -gamma1: (c*s1)_i = (z_i+gamma1) - (y_i+gamma1).

    Both simplify to the exact identity ``(c*s1)_i = z_i-y_i``.  The shifted
    terms are retained in each sample so the branch-specific construction can
    be inspected and tested directly.
    """

    z = np.asarray(z)
    y = np.asarray(y)
    expected_shape = (params.ell, params.n)
    if z.shape != expected_shape or y.shape != expected_shape:
        raise ValueError(
            f"z/y shapes are {z.shape}/{y.shape}, expected {expected_shape}"
        )

    selected: list[InequalitySample] = []
    boundary_mask = (z >= params.gamma1) | (z <= -params.gamma1)
    for poly_index, coeff_index in np.argwhere(boundary_mask):
        poly = int(poly_index)
        coeff = int(coeff_index)
        if remaining_by_poly[poly] is not None and remaining_by_poly[poly] <= 0:
            continue

        z_value = int(z[poly, coeff])
        y_value = int(y[poly, coeff])
        if z_value >= params.gamma1:
            side = "positive"
            shifted_z = z_value - params.gamma1
            shifted_y = y_value - params.gamma1
        else:
            side = "negative"
            shifted_z = z_value + params.gamma1
            shifted_y = y_value + params.gamma1
        rhs = shifted_z - shifted_y

        selected.append(
            InequalitySample(
                signature_index=int(signature_index),
                challenge=challenge,
                poly_index=poly,
                coeff_index=coeff,
                z_value=z_value,
                lower=int(rhs),
                upper=int(rhs),
                side=side,
                constraint_kind="boundary-equality",
                y_value=y_value,
                shifted_z=int(shifted_z),
                shifted_y=int(shifted_y),
                equality_rhs=int(rhs),
            )
        )
        if remaining_by_poly[poly] is not None:
            remaining_by_poly[poly] -= 1
        if one_per_signature:
            break
    return selected


def marginalized_boundary_equalities_from_z(
    params: MLDSAParams,
    challenge: Challenge,
    z: np.ndarray,
    signature_index: int,
    remaining_by_poly: list[int | None],
    one_per_signature: bool = False,
) -> list[InequalitySample]:
    """Marginalize unknown y from the boundary equality ``c*s1 + y = z``.

    This function deliberately receives no y array. It uses only z and
    ``-gamma1+1 <= y_i <= gamma1``. The resulting feasible RHS interval is

        max(z_i-gamma1, -eta*tau)
            <= (c*s1)_i <=
        min(z_i+gamma1-1, eta*tau).

    Only raw boundary crossings ``|z_i| >= gamma1`` are retained.
    """

    samples = inequalities_from_z(
        params=params,
        challenge=challenge,
        z=z,
        threshold=params.gamma1,
        signature_index=signature_index,
        remaining_by_poly=remaining_by_poly,
        one_per_signature=one_per_signature,
    )
    return [
        replace(sample, constraint_kind="boundary-equality-marginalized")
        for sample in samples
    ]


def slack_equalities_from_z(
    params: MLDSAParams,
    challenge: Challenge,
    z: np.ndarray,
    threshold: int,
    signature_index: int,
    remaining_by_poly: list[int | None],
    one_per_signature: bool = False,
) -> list[InequalitySample]:
    """Convert each original interval to an equality with bounded slack.

    For a positive row ``lower <= x <= upper`` this records

        x - r = lower,  0 <= r <= upper-lower.

    For a negative row it records

        x + r = upper,  0 <= r <= upper-lower.

    The current BP backend has a shared small variable domain, so the possibly
    large slack r is marginalized before solving. The resulting RHS support is
    exactly the original integer interval; no true y value is used.
    """

    samples = inequalities_from_z(
        params=params,
        challenge=challenge,
        z=z,
        threshold=threshold,
        signature_index=signature_index,
        remaining_by_poly=remaining_by_poly,
        one_per_signature=one_per_signature,
    )
    converted: list[InequalitySample] = []
    for sample in samples:
        width = int(sample.upper - sample.lower)
        if sample.side == "positive":
            rhs = int(sample.lower)
            slack_sign = -1
        else:
            rhs = int(sample.upper)
            slack_sign = 1
        converted.append(
            replace(
                sample,
                constraint_kind="slack-equality",
                conversion_rhs=rhs,
                slack_sign=slack_sign,
                slack_lower=0,
                slack_upper=width,
            )
        )
    return converted


def unknown_y_error_intervals_from_z(
    params: MLDSAParams,
    challenge: Challenge,
    z: np.ndarray,
    signature_index: int,
    remaining_by_poly: list[int | None],
    one_per_signature: bool = False,
) -> list[InequalitySample]:
    """Convert the boundary nominal equality into a derived error interval.

    For z_i >= gamma1, ``t=z_i-gamma1`` and
    ``(c*s1)_i=t+e`` with ``0 <= e <= B-t``.

    For z_i <= -gamma1, ``t=z_i+gamma1-1`` and
    ``(c*s1)_i=t+e`` with ``-B-t <= e <= 0``.

    Here B=eta*tau. These are exact, per-row, asymmetric bounds derived without
    reading y; they are not an artificial user-selected error parameter.
    """

    samples = marginalized_boundary_equalities_from_z(
        params=params,
        challenge=challenge,
        z=z,
        signature_index=signature_index,
        remaining_by_poly=remaining_by_poly,
        one_per_signature=one_per_signature,
    )
    converted: list[InequalitySample] = []
    for sample in samples:
        if sample.side == "positive":
            nominal = int(sample.lower)
            error_lower = 0
            error_upper = int(sample.upper - nominal)
        else:
            nominal = int(sample.upper)
            error_lower = int(sample.lower - nominal)
            error_upper = 0
        converted.append(
            replace(
                sample,
                constraint_kind="unknown-y-error-interval",
                nominal_rhs=nominal,
                error_lower=error_lower,
                error_upper=error_upper,
            )
        )
    return converted


def collect_inequalities(
    params: MLDSAParams,
    secret: np.ndarray,
    rng: np.random.Generator,
    signatures: int,
    threshold: int,
    max_constraints_per_poly: int | None = None,
    one_per_signature: bool = False,
) -> CollectionResult:
    return collect_constraints(
        params=params,
        secret=secret,
        rng=rng,
        signatures=signatures,
        constraint_mode="inequality",
        threshold=threshold,
        max_constraints_per_poly=max_constraints_per_poly,
        one_per_signature=one_per_signature,
    )


def collect_rcoi_inequalities(
    params: MLDSAParams,
    secret: np.ndarray,
    rng: np.random.Generator,
    signatures: int,
    max_constraints_per_poly: int | None = None,
    one_per_signature: bool = True,
) -> CollectionResult:
    return collect_constraints(
        params=params,
        secret=secret,
        rng=rng,
        signatures=signatures,
        constraint_mode="rcoi-inequality",
        threshold=None,
        max_constraints_per_poly=max_constraints_per_poly,
        one_per_signature=one_per_signature,
    )


def collect_boundary_equalities(
    params: MLDSAParams,
    secret: np.ndarray,
    rng: np.random.Generator,
    signatures: int,
    max_constraints_per_poly: int | None = None,
    one_per_signature: bool = False,
) -> CollectionResult:
    return collect_constraints(
        params=params,
        secret=secret,
        rng=rng,
        signatures=signatures,
        constraint_mode="boundary-equality",
        threshold=params.gamma1,
        max_constraints_per_poly=max_constraints_per_poly,
        one_per_signature=one_per_signature,
    )


def collect_marginalized_boundary_equalities(
    params: MLDSAParams,
    secret: np.ndarray,
    rng: np.random.Generator,
    signatures: int,
    max_constraints_per_poly: int | None = None,
    one_per_signature: bool = False,
) -> CollectionResult:
    return collect_constraints(
        params=params,
        secret=secret,
        rng=rng,
        signatures=signatures,
        constraint_mode="boundary-equality-marginalized",
        threshold=params.gamma1,
        max_constraints_per_poly=max_constraints_per_poly,
        one_per_signature=one_per_signature,
    )


def collect_slack_equalities(
    params: MLDSAParams,
    secret: np.ndarray,
    rng: np.random.Generator,
    signatures: int,
    threshold: int,
    max_constraints_per_poly: int | None = None,
    one_per_signature: bool = False,
) -> CollectionResult:
    return collect_constraints(
        params=params,
        secret=secret,
        rng=rng,
        signatures=signatures,
        constraint_mode="slack-equality",
        threshold=threshold,
        max_constraints_per_poly=max_constraints_per_poly,
        one_per_signature=one_per_signature,
    )


def collect_unknown_y_error_intervals(
    params: MLDSAParams,
    secret: np.ndarray,
    rng: np.random.Generator,
    signatures: int,
    max_constraints_per_poly: int | None = None,
    one_per_signature: bool = False,
) -> CollectionResult:
    return collect_constraints(
        params=params,
        secret=secret,
        rng=rng,
        signatures=signatures,
        constraint_mode="unknown-y-error-interval",
        threshold=params.gamma1,
        max_constraints_per_poly=max_constraints_per_poly,
        one_per_signature=one_per_signature,
    )


def collect_constraints(
    params: MLDSAParams,
    secret: np.ndarray,
    rng: np.random.Generator,
    signatures: int,
    constraint_mode: str,
    threshold: int | None = None,
    max_constraints_per_poly: int | None = None,
    one_per_signature: bool = False,
    progress_interval: int = 0,
) -> CollectionResult:
    """Collect either bounded-y inequalities or exact boundary equalities."""

    if signatures <= 0:
        raise ValueError("signatures must be positive")
    if max_constraints_per_poly is not None and max_constraints_per_poly <= 0:
        raise ValueError("max_constraints_per_poly must be positive or None")
    if progress_interval < 0:
        raise ValueError("progress_interval must be nonnegative")
    supported_modes = {
        "inequality",
        "rcoi-inequality",
        "slack-equality",
        "boundary-equality",
        "boundary-equality-marginalized",
        "unknown-y-error-interval",
    }
    if constraint_mode not in supported_modes:
        raise ValueError(
            "unsupported constraint_mode; choose inequality, rcoi-inequality, "
            "slack-equality, boundary-equality, "
            "boundary-equality-marginalized, or unknown-y-error-interval"
        )
    threshold_modes = {"inequality", "slack-equality"}
    if constraint_mode in threshold_modes and (threshold is None or threshold <= 0):
        raise ValueError("a positive threshold is required for this constraint mode")

    samples: list[InequalitySample] = []
    rows_by_poly = [0] * params.ell
    remaining: list[int | None] = [max_constraints_per_poly] * params.ell
    useful_signatures = 0
    positive_rows = 0
    negative_rows = 0
    signatures_generated = 0
    rejected_attempts = 0

    for signature_index in range(1, signatures + 1):
        signatures_generated = signature_index
        challenge = sample_challenge(params, rng)
        product = sparse_product(params, secret, challenge).astype(np.int32)
        y = sample_y(params, rng)
        z = y + product  # intentionally skip z norm rejection
        if np.any(np.abs(z) >= params.gamma1 - params.beta):
            rejected_attempts += 1
        if constraint_mode == "inequality":
            new_samples = inequalities_from_z(
                params,
                challenge,
                z,
                int(threshold),
                signature_index,
                remaining,
                one_per_signature,
            )
        elif constraint_mode == "rcoi-inequality":
            new_samples = rcoi_inequalities_from_z(
                params,
                challenge,
                z,
                signature_index,
                remaining,
                one_per_signature,
            )
        elif constraint_mode == "slack-equality":
            new_samples = slack_equalities_from_z(
                params,
                challenge,
                z,
                int(threshold),
                signature_index,
                remaining,
                one_per_signature,
            )
        elif constraint_mode == "boundary-equality":
            new_samples = boundary_equalities_from_z(
                params,
                challenge,
                z,
                y,
                signature_index,
                remaining,
                one_per_signature,
            )
        elif constraint_mode == "boundary-equality-marginalized":
            new_samples = marginalized_boundary_equalities_from_z(
                params,
                challenge,
                z,
                signature_index,
                remaining,
                one_per_signature,
            )
        else:
            new_samples = unknown_y_error_intervals_from_z(
                params,
                challenge,
                z,
                signature_index,
                remaining,
                one_per_signature,
            )
        if new_samples:
            useful_signatures += 1
            samples.extend(new_samples)
            for sample in new_samples:
                rows_by_poly[sample.poly_index] += 1
                if sample.side == "positive":
                    positive_rows += 1
                else:
                    negative_rows += 1

        if progress_interval and signature_index % progress_interval == 0:
            print(
                f"collection progress: attempts={signature_index}, "
                f"rejected={rejected_attempts}, useful={useful_signatures}, "
                f"rows_by_poly={rows_by_poly}",
                flush=True,
            )

        if max_constraints_per_poly is not None and all(value == 0 for value in remaining):
            break

    return CollectionResult(
        samples=samples,
        signatures_generated=signatures_generated,
        useful_signatures=useful_signatures,
        rows_by_poly=rows_by_poly,
        positive_rows=positive_rows,
        negative_rows=negative_rows,
        rejected_attempts=rejected_attempts,
    )


def _hint_for_sample(params: MLDSAParams, sample: InequalitySample):
    if normalize_dist is None:
        raise RuntimeError(f"CLWE BP utilities unavailable: {HINT_SOLVER_IMPORT_ERROR!r}")

    coeffs = [0] * params.n
    columns, values = row_terms(params, sample.challenge, sample.coeff_index)
    for column, value in zip(columns, values):
        coeffs[int(column)] += int(value)

    row_bound = params.eta * sum(abs(value) for value in coeffs)
    if sample.constraint_kind == "boundary-equality":
        if sample.equality_rhs is None:
            raise RuntimeError("boundary equality is missing its RHS")
        lower = upper = int(sample.equality_rhs)
    elif sample.constraint_kind in {
        "inequality",
        "rcoi-inequality",
        "slack-equality",
        "boundary-equality-marginalized",
        "unknown-y-error-interval",
    }:
        lower = max(int(sample.lower), -row_bound)
        upper = min(int(sample.upper), row_bound)
    else:
        raise RuntimeError(f"unknown constraint kind: {sample.constraint_kind}")
    if lower > upper:
        raise RuntimeError(f"empty BP RHS interval [{lower}, {upper}]")
    if lower < -row_bound or upper > row_bound:
        raise RuntimeError(
            f"constraint RHS [{lower}, {upper}] exceeds row bound +/-{row_bound}"
        )

    # Equality mode has a singleton support; inequality mode has uniform support.
    rhs = normalize_dist((value, 1.0) for value in range(lower, upper + 1))
    return coeffs, rhs


def build_hints_for_poly(
    params: MLDSAParams,
    samples: list[InequalitySample],
    poly_index: int,
):
    poly_samples = [sample for sample in samples if sample.poly_index == poly_index]
    return [_hint_for_sample(params, sample) for sample in poly_samples]


def count_interval_violations(
    params: MLDSAParams,
    samples: list[InequalitySample],
    recovered: np.ndarray,
) -> int:
    violations = 0
    for sample in samples:
        columns, values = row_terms(params, sample.challenge, sample.coeff_index)
        dot = sum(
            int(value) * int(recovered[sample.poly_index, int(column)])
            for column, value in zip(columns, values)
        )
        if dot < sample.lower or dot > sample.upper:
            violations += 1
    return violations


def solve_secret_bp(
    params: MLDSAParams,
    samples: list[InequalitySample],
    secret: np.ndarray,
    max_iter: int = 100,
    threads: int | None = 16,
    use_sparse_prior: bool = True,
    damping: float = 0.0,
    fixed_polynomials: dict[int, np.ndarray] | None = None,
) -> SolveResult:
    """Solve each s1 polynomial independently, optionally reusing fixed results."""

    if solve_bp is None:
        raise RuntimeError(
            f"cannot import BP from {CLWE_SOLVER_FILE}: {HINT_SOLVER_IMPORT_ERROR!r}"
        )
    if not CLWE_SOLVER_FILE.exists():
        raise FileNotFoundError(f"required BP solver not found: {CLWE_SOLVER_FILE}")
    if max_iter <= 0:
        raise ValueError("max_iter must be positive")
    if not 0.0 <= float(damping) < 1.0:
        raise ValueError("damping must satisfy 0 <= damping < 1")

    fixed_polynomials = {} if fixed_polynomials is None else fixed_polynomials
    invalid_fixed = set(fixed_polynomials) - set(range(params.ell))
    if invalid_fixed:
        raise ValueError(f"fixed polynomial indices outside range: {sorted(invalid_fixed)}")

    recovered_polys: list[np.ndarray] = []
    rows_by_poly: list[int] = []
    started = perf_counter()
    for poly_index in range(params.ell):
        hints = build_hints_for_poly(params, samples, poly_index)
        rows_by_poly.append(len(hints))
        if poly_index in fixed_polynomials:
            recovered_poly = np.asarray(
                fixed_polynomials[poly_index], dtype=np.int16
            ).reshape(-1)
            if recovered_poly.shape != (params.n,):
                raise ValueError(
                    f"fixed polynomial {poly_index} has shape "
                    f"{recovered_poly.shape}, expected {(params.n,)}"
                )
            recovered_polys.append(recovered_poly.copy())
            continue
        if not hints:
            raise RuntimeError(f"no informative constraints for s1 polynomial {poly_index}")
        recovered_poly = solve_bp(
            hints,
            params.eta,
            max_iter=max_iter,
            threads=threads,
            use_sparse_prior=use_sparse_prior,
            damping=damping,
        )
        recovered_poly = np.asarray(recovered_poly, dtype=np.int16).reshape(-1)
        if recovered_poly.shape != (params.n,):
            raise RuntimeError(
                f"BP returned shape {recovered_poly.shape} for poly {poly_index}, "
                f"expected {(params.n,)}"
            )
        recovered_polys.append(recovered_poly)

    recovered = np.asarray(recovered_polys, dtype=np.int16)
    elapsed = perf_counter() - started
    secret = np.asarray(secret, dtype=np.int16)
    if secret.shape != recovered.shape:
        raise ValueError(f"secret shape {secret.shape} does not match {recovered.shape}")
    mismatch_mask = recovered != secret
    mismatches_by_poly = [int(value) for value in mismatch_mask.sum(axis=1)]
    total_mismatches = int(mismatch_mask.sum())
    interval_violations = count_interval_violations(params, samples, recovered)
    return SolveResult(
        recovered=recovered,
        elapsed_seconds=elapsed,
        rows_by_poly=rows_by_poly,
        mismatches_by_poly=mismatches_by_poly,
        total_mismatches=total_mismatches,
        interval_violations=interval_violations,
        exact_recovery=total_mismatches == 0,
    )
