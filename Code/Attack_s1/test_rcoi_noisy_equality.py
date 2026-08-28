from __future__ import annotations

import unittest
from dataclasses import dataclass

import numpy as np

from bp_attack import InequalitySample
from ilp_attack import solve_poly_ilp
from mldsa_model import Challenge, get_params
from rcoi_noisy_equality import (
    convert_rcoi_rows_to_inequalities,
    four_value_bounds,
    noisy_equality_to_inequalities,
    rcoi_sample_to_noisy_equality,
)


@dataclass(frozen=True)
class Sample:
    z_value: int
    lower: int
    upper: int
    side: str


class NoisyEqualityTests(unittest.TestCase):
    def setUp(self) -> None:
        self.params = get_params("toy")

    def sample(self, z_value: int) -> Sample:
        lower, upper = four_value_bounds(self.params)[z_value]
        return Sample(
            z_value=z_value,
            lower=lower,
            upper=upper,
            side="positive" if z_value >= 0 else "negative",
        )

    def test_all_four_values_have_expected_noise(self) -> None:
        bound = self.params.inner_product_bound
        expected = {
            self.params.gamma1: (0, 0, bound),
            self.params.gamma1 - 1: (-1, 0, bound + 1),
            -self.params.gamma1: (-1, -bound + 1, 0),
            -self.params.gamma1 - 1: (-2, -bound + 2, 0),
        }
        for z_value, triple in expected.items():
            equation = rcoi_sample_to_noisy_equality(
                self.params, self.sample(z_value)
            )
            self.assertEqual(
                (equation.rhs, equation.error_lower, equation.error_upper),
                triple,
            )

    def test_conversion_is_exact_interval(self) -> None:
        row = np.asarray([1.0, -1.0, 0.0])
        for z_value, (lower, upper) in four_value_bounds(self.params).items():
            equation = rcoi_sample_to_noisy_equality(
                self.params, self.sample(z_value)
            )
            matrix, bounds = noisy_equality_to_inequalities(row, equation)
            self.assertTrue(np.array_equal(matrix[0], row))
            self.assertTrue(np.array_equal(matrix[1], -row))
            self.assertEqual(float(bounds[0]), float(upper))
            self.assertEqual(float(bounds[1]), float(-lower))

    def test_batch_conversion_doubles_rows(self) -> None:
        samples = [
            self.sample(self.params.gamma1),
            self.sample(-self.params.gamma1 - 1),
        ]
        rows = np.zeros((2, self.params.n), dtype=np.float64)
        rows[0, 0] = 1
        rows[1, 1] = -1
        converted = convert_rcoi_rows_to_inequalities(
            self.params, rows, samples
        )
        self.assertEqual(converted.matrix.shape, (4, self.params.n))
        self.assertEqual(converted.upper_bounds.shape, (4,))
        self.assertEqual(len(converted.equations), 2)

    def test_rejects_non_four_value_sample(self) -> None:
        sample = Sample(0, -1, 1, "positive")
        with self.assertRaises(ValueError):
            rcoi_sample_to_noisy_equality(self.params, sample)

    def test_ilp_backend_solves_both_equivalent_encodings(self) -> None:
        lower, upper = four_value_bounds(self.params)[self.params.gamma1]
        sample = InequalitySample(
            signature_index=0,
            challenge=Challenge(
                positions=np.asarray([0], dtype=np.int16),
                signs=np.asarray([1], dtype=np.int8),
            ),
            poly_index=0,
            coeff_index=0,
            z_value=self.params.gamma1,
            lower=lower,
            upper=upper,
            side="positive",
            constraint_kind="rcoi-inequality",
            y_value=None,
            shifted_z=None,
            shifted_y=None,
            equality_rhs=None,
        )
        interval = solve_poly_ilp(
            self.params, [sample], 0, time_limit=10, formulation="interval"
        )
        noisy = solve_poly_ilp(
            self.params,
            [sample],
            0,
            time_limit=10,
            formulation="noisy-equality",
        )
        self.assertTrue(interval.feasible_integer_solution)
        self.assertTrue(noisy.feasible_integer_solution)
        self.assertEqual(interval.interval_violations, 0)
        self.assertEqual(noisy.interval_violations, 0)
        self.assertEqual((interval.source_rows, interval.solver_rows), (1, 1))
        self.assertEqual((noisy.source_rows, noisy.solver_rows), (1, 2))


if __name__ == "__main__":
    unittest.main()
