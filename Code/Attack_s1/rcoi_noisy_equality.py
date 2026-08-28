"""Noisy-equality formulation for the four-value RCoI ``s1`` attack.

For a selected negacyclic row ``a``, the module records

    a @ s1 = rhs + error,  error_lower <= error <= error_upper

and converts it to two canonical upper-bound inequalities.  The conversion is
kept separate from the ILP backend so every solver receives the same signs and
right-hand sides.
"""

from __future__ import annotations

from dataclasses import dataclass
from typing import Protocol, Sequence

import numpy as np

from mldsa_model import MLDSAParams


class FourValueSample(Protocol):
    """Fields required from ``bp_attack.InequalitySample``."""

    z_value: int
    lower: int
    upper: int
    side: str


@dataclass(frozen=True)
class NoisyEquality:
    rhs: int
    error_lower: int
    error_upper: int

    @property
    def lower(self) -> int:
        return self.rhs + self.error_lower

    @property
    def upper(self) -> int:
        return self.rhs + self.error_upper


@dataclass(frozen=True)
class ConvertedInequalities:
    matrix: np.ndarray
    upper_bounds: np.ndarray
    equations: tuple[NoisyEquality, ...]


def four_value_bounds(params: MLDSAParams) -> dict[int, tuple[int, int]]:
    """Return the four documented RCoI intervals for ``(c*s1)_i``."""

    bound = params.inner_product_bound
    return {
        params.gamma1: (0, bound),
        params.gamma1 - 1: (-1, bound),
        -params.gamma1: (-bound, -1),
        -params.gamma1 - 1: (-bound, -2),
    }


def rcoi_sample_to_noisy_equality(
    params: MLDSAParams,
    sample: FourValueSample,
) -> NoisyEquality:
    """Convert one four-value interval to an equivalent noisy equality.

    Positive observations use the lower endpoint as the nominal right-hand
    side and nonnegative noise.  Negative observations use the upper endpoint
    and nonpositive noise.  No truth value such as ``y`` or ``s1`` is read.
    """

    expected = four_value_bounds(params)
    z_value = int(sample.z_value)
    try:
        lower, upper = expected[z_value]
    except KeyError as exc:
        raise ValueError(
            f"z={z_value} is not one of the four RCoI values"
        ) from exc

    supplied = (int(sample.lower), int(sample.upper))
    if supplied != (lower, upper):
        raise ValueError(
            f"z={z_value} has interval {supplied}, expected {(lower, upper)}"
        )

    expected_side = "positive" if z_value >= 0 else "negative"
    if sample.side != expected_side:
        raise ValueError(
            f"z={z_value} has side {sample.side!r}, expected {expected_side!r}"
        )

    if expected_side == "positive":
        return NoisyEquality(
            rhs=lower,
            error_lower=0,
            error_upper=upper - lower,
        )
    return NoisyEquality(
        rhs=upper,
        error_lower=lower - upper,
        error_upper=0,
    )


def noisy_equality_to_inequalities(
    row: np.ndarray,
    equation: NoisyEquality,
) -> tuple[np.ndarray, np.ndarray]:
    """Return ``A_ub`` and ``b_ub`` for one bounded-noise equality."""

    row = np.asarray(row, dtype=np.float64)
    if row.ndim != 1:
        raise ValueError(f"row must be one-dimensional, got shape {row.shape}")
    if equation.error_lower > equation.error_upper:
        raise ValueError(
            "empty noise interval: "
            f"[{equation.error_lower},{equation.error_upper}]"
        )

    matrix = np.stack((row, -row))
    upper_bounds = np.asarray(
        [equation.upper, -equation.lower],
        dtype=np.float64,
    )
    return matrix, upper_bounds


def convert_rcoi_rows_to_inequalities(
    params: MLDSAParams,
    rows: np.ndarray,
    samples: Sequence[FourValueSample],
) -> ConvertedInequalities:
    """Convert all four-value rows to a single ``A_ub @ x <= b_ub`` model."""

    rows = np.asarray(rows, dtype=np.float64)
    if rows.ndim != 2:
        raise ValueError(f"rows must be two-dimensional, got shape {rows.shape}")
    if rows.shape[0] != len(samples):
        raise ValueError(
            f"row/sample mismatch: {rows.shape[0]} rows for {len(samples)} samples"
        )
    if not samples:
        raise ValueError("at least one four-value sample is required")

    matrices: list[np.ndarray] = []
    bounds: list[np.ndarray] = []
    equations: list[NoisyEquality] = []
    for row, sample in zip(rows, samples):
        equation = rcoi_sample_to_noisy_equality(params, sample)
        matrix, upper = noisy_equality_to_inequalities(row, equation)
        matrices.append(matrix)
        bounds.append(upper)
        equations.append(equation)

    return ConvertedInequalities(
        matrix=np.vstack(matrices),
        upper_bounds=np.concatenate(bounds),
        equations=tuple(equations),
    )
