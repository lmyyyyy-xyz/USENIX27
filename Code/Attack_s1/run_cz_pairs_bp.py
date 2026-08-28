#!/usr/bin/env python3
"""Recover ML-DSA s1 from externally recovered rejected (c, z) pairs."""

from __future__ import annotations

import argparse
import csv
import json
from collections import Counter
from dataclasses import dataclass
from datetime import datetime
from pathlib import Path

import numpy as np

from bp_attack import CLWE_SOLVER_FILE, InequalitySample, solve_secret_bp
from mldsa_model import Challenge, MLDSAParams, get_params


DEFAULT_DATASET = (
    Path(__file__).resolve().parents[1]
    / "cz_pairs_D2"
    / "cz_pairs_verified.npz"
)


@dataclass(frozen=True)
class LoadedCZPairs:
    samples: list[InequalitySample]
    source_rows: int
    selected_rows: int
    rows_by_poly: list[int]
    positive_rows: int
    negative_rows: int
    unique_trace_ids: int
    z_value_counts: dict[int, int]
    pair_ok_count: int | None


def _one_dimensional(array: np.ndarray, name: str, rows: int) -> np.ndarray:
    array = np.asarray(array)
    if array.shape != (rows,):
        raise ValueError(f"{name} shape is {array.shape}, expected {(rows,)}")
    return array


def load_cz_pairs(
    dataset_path: Path,
    params: MLDSAParams,
    max_constraints_per_poly: int | None = None,
) -> LoadedCZPairs:
    """Load verified pairs and construct unknown-y interval constraints.

    Recovery uses only ``trace_id``, ``poly_l``, ``coeff_i``, ``k``,
    ``c_pred``, and ``z_pred_val``.  Any truth/audit arrays in the archive are
    deliberately excluded from constraint construction and row selection.
    """

    if max_constraints_per_poly is not None and max_constraints_per_poly <= 0:
        raise ValueError("max_constraints_per_poly must be positive or None")
    dataset_path = Path(dataset_path)
    if not dataset_path.is_file():
        raise FileNotFoundError(f"cz-pairs dataset not found: {dataset_path}")

    required = {
        "trace_id",
        "poly_l",
        "coeff_i",
        "k",
        "c_pred",
        "z_pred_val",
    }
    with np.load(dataset_path, allow_pickle=False) as archive:
        missing = sorted(required.difference(archive.files))
        if missing:
            raise ValueError(f"dataset is missing required arrays: {missing}")

        trace_id = np.asarray(archive["trace_id"], dtype=np.int64)
        rows = int(trace_id.size)
        trace_id = _one_dimensional(trace_id, "trace_id", rows)
        poly_l = _one_dimensional(archive["poly_l"], "poly_l", rows).astype(
            np.int64, copy=False
        )
        coeff_i = _one_dimensional(
            archive["coeff_i"], "coeff_i", rows
        ).astype(np.int64, copy=False)
        flat_k = _one_dimensional(archive["k"], "k", rows).astype(
            np.int64, copy=False
        )
        z_pred_val = _one_dimensional(
            archive["z_pred_val"], "z_pred_val", rows
        ).astype(np.int64, copy=False)
        c_pred = np.asarray(archive["c_pred"], dtype=np.int8)
        pair_ok_count = (
            int(np.count_nonzero(archive["pair_ok"]))
            if "pair_ok" in archive.files
            else None
        )

    if rows == 0:
        raise ValueError("cz-pairs dataset contains no rows")
    if c_pred.shape != (rows, params.n):
        raise ValueError(
            f"c_pred shape is {c_pred.shape}, expected {(rows, params.n)}"
        )
    if np.any((poly_l < 0) | (poly_l >= params.ell)):
        raise ValueError(f"poly_l must lie in [0,{params.ell - 1}]")
    if np.any((coeff_i < 0) | (coeff_i >= params.n)):
        raise ValueError(f"coeff_i must lie in [0,{params.n - 1}]")
    expected_k = poly_l * params.n + coeff_i
    if not np.array_equal(flat_k, expected_k):
        first = int(np.flatnonzero(flat_k != expected_k)[0])
        raise ValueError(
            f"invalid k at row {first}: got {flat_k[first]}, "
            f"expected {expected_k[first]}"
        )
    if not np.all(np.isin(c_pred, np.asarray([-1, 0, 1], dtype=np.int8))):
        raise ValueError("c_pred contains a coefficient outside {-1,0,1}")
    challenge_weights = np.count_nonzero(c_pred, axis=1)
    if np.any(challenge_weights != params.tau):
        first = int(np.flatnonzero(challenge_weights != params.tau)[0])
        raise ValueError(
            f"challenge weight at row {first} is {challenge_weights[first]}, "
            f"expected tau={params.tau}"
        )

    natural_bound = params.inner_product_bound
    rows_by_poly = [0] * params.ell
    samples: list[InequalitySample] = []
    positive_rows = 0
    negative_rows = 0
    z_counts: Counter[int] = Counter()

    for row in range(rows):
        poly_index = int(poly_l[row])
        if (
            max_constraints_per_poly is not None
            and rows_by_poly[poly_index] >= max_constraints_per_poly
        ):
            continue

        challenge_poly = c_pred[row]
        positions = np.flatnonzero(challenge_poly).astype(np.int16)
        challenge = Challenge(
            positions=positions,
            signs=challenge_poly[positions].astype(np.int8, copy=True),
        )
        z_value = int(z_pred_val[row])
        lower = max(z_value - params.y_high, -natural_bound)
        upper = min(z_value - params.y_low, natural_bound)
        if lower > upper:
            raise ValueError(
                f"row {row} gives an empty interval [{lower},{upper}]"
            )
        if lower == -natural_bound and upper == natural_bound:
            raise ValueError(f"row {row} is not an informative boundary constraint")

        side = "positive" if z_value >= 0 else "negative"
        samples.append(
            InequalitySample(
                signature_index=int(trace_id[row]),
                challenge=challenge,
                poly_index=poly_index,
                coeff_index=int(coeff_i[row]),
                z_value=z_value,
                lower=int(lower),
                upper=int(upper),
                side=side,
                constraint_kind="inequality",
                y_value=None,
                shifted_z=None,
                shifted_y=None,
                equality_rhs=None,
            )
        )
        rows_by_poly[poly_index] += 1
        z_counts[z_value] += 1
        if side == "positive":
            positive_rows += 1
        else:
            negative_rows += 1

    if max_constraints_per_poly is not None and any(
        count < max_constraints_per_poly for count in rows_by_poly
    ):
        raise ValueError(
            "dataset cannot meet --max-constraints-per-poly for every polynomial: "
            f"rows_by_poly={rows_by_poly}, target={max_constraints_per_poly}"
        )

    return LoadedCZPairs(
        samples=samples,
        source_rows=rows,
        selected_rows=len(samples),
        rows_by_poly=rows_by_poly,
        positive_rows=positive_rows,
        negative_rows=negative_rows,
        unique_trace_ids=int(np.unique(trace_id).size),
        z_value_counts=dict(sorted(z_counts.items())),
        pair_ok_count=pair_ok_count,
    )


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Load recovered rejected (c,z) pairs, construct unknown-y s1 "
            "inequalities, and solve them with the attack_s1 BP backend."
        )
    )
    parser.add_argument("--dataset", type=Path, default=DEFAULT_DATASET)
    parser.add_argument(
        "--secret",
        type=Path,
        default=None,
        help="truth s1 for evaluation (default: s1_true.npy beside the dataset)",
    )
    parser.add_argument("--level", default="2", choices=["2", "3", "5", "toy"])
    parser.add_argument(
        "--max-constraints-per-poly",
        type=int,
        default=0,
        help="use the first N rows per polynomial; 0 uses every row",
    )
    parser.add_argument("--bp-iterations", type=int, default=20)
    parser.add_argument(
        "--bp-damping",
        type=float,
        default=0.0,
        help="old-message weight in [0,1); 0 disables damping",
    )
    parser.add_argument("--threads", type=int, default=16)
    parser.add_argument("--uniform-prior", action="store_true")
    parser.add_argument("--output-dir", type=Path, default=Path("outputs"))
    parser.add_argument("--no-save", action="store_true")
    args = parser.parse_args()
    if args.max_constraints_per_poly < 0:
        parser.error("--max-constraints-per-poly must be nonnegative")
    if args.bp_iterations <= 0 or args.threads <= 0:
        parser.error("--bp-iterations and --threads must be positive")
    if not 0.0 <= args.bp_damping < 1.0:
        parser.error("--bp-damping must satisfy 0 <= value < 1")
    return args


def save_results(
    output_dir: Path,
    params: MLDSAParams,
    args: argparse.Namespace,
    loaded: LoadedCZPairs,
    secret: np.ndarray,
    result,
) -> dict[str, str]:
    output_dir.mkdir(parents=True, exist_ok=True)
    stamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    prefix = output_dir / (
        f"{params.name}_s1_cz_pairs_bp_{loaded.selected_rows}rows_{stamp}"
    )
    recovered_path = Path(f"{prefix}_recovered.npy")
    coefficients_path = Path(f"{prefix}_coefficients.csv")
    summary_path = Path(f"{prefix}_summary.json")

    np.save(recovered_path, result.recovered)
    with coefficients_path.open("w", newline="", encoding="utf-8") as file:
        writer = csv.writer(file)
        writer.writerow(
            ["poly_index", "coeff_index", "true_s1", "recovered_s1", "match"]
        )
        for poly_index in range(params.ell):
            for coeff_index in range(params.n):
                true_value = int(secret[poly_index, coeff_index])
                recovered_value = int(result.recovered[poly_index, coeff_index])
                writer.writerow(
                    [
                        poly_index,
                        coeff_index,
                        true_value,
                        recovered_value,
                        true_value == recovered_value,
                    ]
                )

    argument_payload = {
        key: str(value) if isinstance(value, Path) else value
        for key, value in vars(args).items()
    }
    payload = {
        "parameters": params.__dict__,
        "arguments": argument_payload,
        "dataset": {
            "path": str(Path(args.dataset).resolve()),
            "source_rows": loaded.source_rows,
            "selected_rows": loaded.selected_rows,
            "rows_by_poly": loaded.rows_by_poly,
            "positive_rows": loaded.positive_rows,
            "negative_rows": loaded.negative_rows,
            "unique_trace_ids": loaded.unique_trace_ids,
            "z_value_counts": {
                str(key): value for key, value in loaded.z_value_counts.items()
            },
            "pair_ok_count_for_audit": loaded.pair_ok_count,
            "fields_used_for_recovery": [
                "trace_id",
                "poly_l",
                "coeff_i",
                "k",
                "c_pred",
                "z_pred_val",
            ],
            "truth_fields_used_for_recovery": False,
        },
        "constraints": {
            "kind": "unknown-y inequality",
            "formula": "z-gamma1 <= (c*s1)_i <= z+gamma1-1, clipped to +/-eta*tau",
            "y_interval": [params.y_low, params.y_high],
        },
        "bp_solver_file": str(CLWE_SOLVER_FILE.resolve()),
        "solve": {
            "elapsed_seconds": result.elapsed_seconds,
            "rows_by_poly": result.rows_by_poly,
            "mismatches_by_poly": result.mismatches_by_poly,
            "total_mismatches": result.total_mismatches,
            "interval_violations": result.interval_violations,
            "exact_recovery": result.exact_recovery,
        },
        "files": {
            "secret": str(Path(args.secret).resolve()),
            "recovered": str(recovered_path.resolve()),
            "coefficients": str(coefficients_path.resolve()),
        },
    }
    with summary_path.open("w", encoding="utf-8") as file:
        json.dump(payload, file, indent=2, ensure_ascii=False)
    return {
        "summary": str(summary_path.resolve()),
        "recovered": str(recovered_path.resolve()),
        "coefficients": str(coefficients_path.resolve()),
    }


def main() -> int:
    args = parse_args()
    params = get_params(args.level)
    args.dataset = args.dataset.resolve()
    args.secret = (
        args.secret.resolve()
        if args.secret is not None
        else args.dataset.with_name("s1_true.npy")
    )
    if not args.secret.is_file():
        raise FileNotFoundError(f"truth s1 not found: {args.secret}")

    secret = np.asarray(np.load(args.secret, allow_pickle=False), dtype=np.int16)
    expected_secret_shape = (params.ell, params.n)
    if secret.shape != expected_secret_shape:
        raise ValueError(
            f"secret shape is {secret.shape}, expected {expected_secret_shape}"
        )
    if np.any((secret < -params.eta) | (secret > params.eta)):
        raise ValueError(f"secret contains a value outside [-{params.eta},{params.eta}]")

    cap = args.max_constraints_per_poly or None
    loaded = load_cz_pairs(args.dataset, params, cap)
    print(
        f"parameters: {params.name}, n={params.n}, ell={params.ell}, "
        f"eta={params.eta}, tau={params.tau}, gamma1={params.gamma1}, beta={params.beta}"
    )
    print(
        f"dataset: path={args.dataset}, source_rows={loaded.source_rows}, "
        f"selected_rows={loaded.selected_rows}, unique_traces={loaded.unique_trace_ids}, "
        f"pair_ok_for_audit={loaded.pair_ok_count}"
    )
    print(
        f"constraints: kind=unknown-y-inequality, rows_by_poly={loaded.rows_by_poly}, "
        f"positive={loaded.positive_rows}, negative={loaded.negative_rows}, "
        f"z_values={loaded.z_value_counts}"
    )

    result = solve_secret_bp(
        params=params,
        samples=loaded.samples,
        secret=secret,
        max_iter=args.bp_iterations,
        threads=args.threads,
        use_sparse_prior=not args.uniform_prior,
        damping=args.bp_damping,
    )
    print(
        f"BP: exact_recovery={result.exact_recovery}, "
        f"mismatches={result.total_mismatches}/{params.dimension}, "
        f"mismatches_by_poly={result.mismatches_by_poly}, "
        f"interval_violations={result.interval_violations}, "
        f"time={result.elapsed_seconds:.3f}s"
    )

    if not args.no_save:
        output_dir = args.output_dir
        if not output_dir.is_absolute():
            output_dir = Path(__file__).resolve().parent / output_dir
        paths = save_results(output_dir, params, args, loaded, secret, result)
        print(f"saved summary: {paths['summary']}")
        print(f"saved recovered s1: {paths['recovered']}")
        print(f"saved coefficient comparison: {paths['coefficients']}")
    return 0 if result.exact_recovery else 2


if __name__ == "__main__":
    raise SystemExit(main())
