#!/usr/bin/env python3
"""Binary-search the per-polynomial BP sample count for recovered (c,z) data."""

from __future__ import annotations

import argparse
import csv
import json
from datetime import datetime
from pathlib import Path
from time import perf_counter

import numpy as np

from binary_search_constraints import (
    binary_search_first_success,
    constraint_prefix,
)
from bp_attack import solve_secret_bp
from mldsa_model import get_params
from run_cz_pairs_bp import DEFAULT_DATASET, load_cz_pairs


def order_samples_for_prefix(samples: list, order: str) -> list:
    """Return a deterministic prefix order without changing sample contents."""

    if order == "file":
        return list(samples)
    if order == "trace-id":
        return [
            sample
            for _index, sample in sorted(
                enumerate(samples),
                key=lambda item: (int(item[1].signature_index), item[0]),
            )
        ]
    raise ValueError("prefix order must be 'trace-id' or 'file'")


def parse_args(argv: list[str] | None = None) -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Load one recovered (c,z) dataset and binary-search the smallest "
            "equal per-polynomial prefix that exactly recovers s1 with BP."
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
    parser.add_argument("--min-constraints-per-poly", type=int, default=1200)
    parser.add_argument("--max-constraints-per-poly", type=int, default=2000)
    parser.add_argument("--bp-iterations", type=int, default=20)
    parser.add_argument("--bp-damping", type=float, default=0.0)
    parser.add_argument("--threads", type=int, default=16)
    parser.add_argument("--uniform-prior", action="store_true")
    parser.add_argument(
        "--prefix-order",
        choices=["trace-id", "file"],
        default="trace-id",
        help="order used before taking the first N constraints per polynomial",
    )
    parser.add_argument(
        "--verification-radius",
        type=int,
        default=3,
        help="evaluate every count within this distance of the binary boundary",
    )
    parser.add_argument("--output-dir", type=Path, default=Path("outputs"))
    parser.add_argument("--no-save", action="store_true")
    args = parser.parse_args(argv)
    if args.min_constraints_per_poly <= 0:
        parser.error("--min-constraints-per-poly must be positive")
    if args.max_constraints_per_poly < args.min_constraints_per_poly:
        parser.error(
            "--max-constraints-per-poly must be >= --min-constraints-per-poly"
        )
    if args.bp_iterations <= 0 or args.threads <= 0:
        parser.error("--bp-iterations and --threads must be positive")
    if not 0.0 <= args.bp_damping < 1.0:
        parser.error("--bp-damping must satisfy 0 <= value < 1")
    if args.verification_radius < 0:
        parser.error("--verification-radius must be nonnegative")
    return args


def save_results(
    args: argparse.Namespace,
    params,
    loaded,
    available_rows_by_poly: list[int],
    effective_upper: int,
    evaluations: list[dict],
    status: str,
    monotone_minimum: int | None,
    smallest_evaluated_success: int | None,
    recovered: np.ndarray | None,
    secret: np.ndarray,
    wall_seconds: float,
) -> dict[str, str]:
    output_dir = args.output_dir
    if not output_dir.is_absolute():
        output_dir = Path(__file__).resolve().parent / output_dir
    output_dir.mkdir(parents=True, exist_ok=True)
    stamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    prefix = output_dir / (
        f"{params.name}_s1_cz_pairs_bp_binary_"
        f"{args.min_constraints_per_poly}-{args.max_constraints_per_poly}_{stamp}"
    )
    summary_path = Path(f"{prefix}_summary.json")
    evaluations_path = Path(f"{prefix}_evaluations.csv")
    arrays_path = Path(f"{prefix}_result.npz")

    ordered = sorted(evaluations, key=lambda record: record["constraints_per_poly"])
    fields = [
        "constraints_per_poly",
        "total_constraints",
        "unique_trace_ids",
        "max_trace_id",
        "exact_recovery",
        "total_mismatches",
        "mismatches_by_poly",
        "interval_violations",
        "elapsed_seconds",
    ]
    with evaluations_path.open("w", newline="", encoding="utf-8") as file:
        writer = csv.DictWriter(file, fieldnames=fields)
        writer.writeheader()
        for record in ordered:
            row = dict(record)
            row["mismatches_by_poly"] = ";".join(
                str(value) for value in row["mismatches_by_poly"]
            )
            writer.writerow(row)

    monotonicity_violations: list[dict[str, int]] = []
    seen_success: int | None = None
    for record in ordered:
        count = int(record["constraints_per_poly"])
        if record["exact_recovery"]:
            if seen_success is None:
                seen_success = count
        elif seen_success is not None:
            monotonicity_violations.append(
                {"earlier_success": seen_success, "later_failure": count}
            )

    argument_payload = {
        key: str(value) if isinstance(value, Path) else value
        for key, value in vars(args).items()
    }
    summary = {
        "status": status,
        "minimum_constraints_per_poly_under_monotone_assumption": monotone_minimum,
        "smallest_evaluated_success": smallest_evaluated_success,
        "requested_range": [
            args.min_constraints_per_poly,
            args.max_constraints_per_poly,
        ],
        "effective_range": [args.min_constraints_per_poly, effective_upper],
        "upper_bound_clamped_to_available_data": (
            effective_upper < args.max_constraints_per_poly
        ),
        "warning": (
            "Loopy BP success is not theoretically monotone. The reported binary "
            "boundary is conditional on monotonicity and is not an exhaustive "
            "global-minimum proof."
        ),
        "parameters": params.__dict__,
        "arguments": argument_payload,
        "dataset": {
            "path": str(args.dataset.resolve()),
            "source_rows": loaded.source_rows,
            "available_rows_by_poly": available_rows_by_poly,
            "unique_trace_ids": loaded.unique_trace_ids,
            "truth_fields_used_for_recovery": False,
        },
        "evaluations": ordered,
        "monotonicity_violations_among_evaluated_counts": monotonicity_violations,
        "cumulative_bp_seconds": float(
            sum(record["elapsed_seconds"] for record in evaluations)
        ),
        "wall_seconds": wall_seconds,
        "files": {
            "secret": str(args.secret.resolve()),
            "evaluations": str(evaluations_path.resolve()),
            "arrays": str(arrays_path.resolve()),
        },
    }
    summary_path.write_text(json.dumps(summary, indent=2), encoding="utf-8")
    if recovered is None:
        np.savez_compressed(arrays_path, secret=secret)
    else:
        np.savez_compressed(arrays_path, secret=secret, recovered=recovered)
    return {
        "summary": str(summary_path.resolve()),
        "evaluations": str(evaluations_path.resolve()),
        "arrays": str(arrays_path.resolve()),
    }


def main(argv: list[str] | None = None) -> int:
    args = parse_args(argv)
    started = perf_counter()
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
    if secret.shape != (params.ell, params.n):
        raise ValueError(
            f"secret shape is {secret.shape}, expected {(params.ell, params.n)}"
        )

    loaded = load_cz_pairs(args.dataset, params)
    prefix_samples = order_samples_for_prefix(loaded.samples, args.prefix_order)
    available_rows_by_poly = loaded.rows_by_poly
    effective_upper = min(
        args.max_constraints_per_poly,
        min(available_rows_by_poly),
    )
    if effective_upper < args.min_constraints_per_poly:
        raise RuntimeError(
            "dataset cannot fill the requested lower bound: "
            f"available={available_rows_by_poly}, "
            f"lower={args.min_constraints_per_poly}"
        )

    print(
        f"parameters: {params.name}, n={params.n}, ell={params.ell}, "
        f"eta={params.eta}, tau={params.tau}"
    )
    print(
        f"dataset: {args.dataset}, rows={loaded.source_rows}, "
        f"available_rows_by_poly={available_rows_by_poly}"
    )
    print(
        f"search: requested=[{args.min_constraints_per_poly},"
        f"{args.max_constraints_per_poly}], "
        f"effective=[{args.min_constraints_per_poly},{effective_upper}], "
        f"bp_iter={args.bp_iterations}, damping={args.bp_damping}, "
        f"threads={args.threads}, prefix_order={args.prefix_order}"
    )
    if effective_upper < args.max_constraints_per_poly:
        print(
            "notice: upper bound clamped because equal per-polynomial prefixes "
            f"cannot exceed {effective_upper}."
        )
    print(
        "warning: loopy BP success is not guaranteed monotone; binary search "
        "reports a conditional boundary and verifies its local neighborhood."
    )

    result_cache: dict[int, object] = {}
    evaluations: list[dict] = []

    def evaluate(rows_per_poly: int):
        cached = result_cache.get(rows_per_poly)
        if cached is not None:
            return cached
        samples = constraint_prefix(
            prefix_samples,
            params.ell,
            rows_per_poly,
        )
        result = solve_secret_bp(
            params=params,
            samples=samples,
            secret=secret,
            max_iter=args.bp_iterations,
            threads=args.threads,
            use_sparse_prior=not args.uniform_prior,
            damping=args.bp_damping,
        )
        result_cache[rows_per_poly] = result
        record = {
            "constraints_per_poly": rows_per_poly,
            "total_constraints": len(samples),
            "unique_trace_ids": len(
                {int(sample.signature_index) for sample in samples}
            ),
            "max_trace_id": max(int(sample.signature_index) for sample in samples),
            "exact_recovery": result.exact_recovery,
            "total_mismatches": result.total_mismatches,
            "mismatches_by_poly": result.mismatches_by_poly,
            "interval_violations": result.interval_violations,
            "elapsed_seconds": result.elapsed_seconds,
        }
        evaluations.append(record)
        print(
            f"probe: N={rows_per_poly}, exact={result.exact_recovery}, "
            f"mismatches={result.total_mismatches}, "
            f"by_poly={result.mismatches_by_poly}, "
            f"violations={result.interval_violations}, "
            f"time={result.elapsed_seconds:.3f}s",
            flush=True,
        )
        return result

    lower = args.min_constraints_per_poly
    lower_result = evaluate(lower)
    monotone_minimum: int | None = None
    final_result = None

    if lower_result.exact_recovery:
        status = "lower_bound_succeeds"
        monotone_minimum = lower
        final_result = lower_result
    else:
        upper_result = evaluate(effective_upper)
        if not upper_result.exact_recovery:
            status = "effective_upper_bound_fails"
        else:
            monotone_minimum = binary_search_first_success(
                lower,
                effective_upper,
                lambda count: evaluate(count).exact_recovery,
            )
            final_result = evaluate(monotone_minimum)
            evaluate(monotone_minimum - 1)
            status = "minimum_found_under_monotone_assumption"

    if monotone_minimum is not None and args.verification_radius:
        start = max(lower, monotone_minimum - args.verification_radius)
        stop = min(effective_upper, monotone_minimum + args.verification_radius)
        for count in range(start, stop + 1):
            evaluate(count)

    successful_counts = [
        int(record["constraints_per_poly"])
        for record in evaluations
        if record["exact_recovery"]
    ]
    smallest_evaluated_success = min(successful_counts) if successful_counts else None
    wall_seconds = perf_counter() - started
    print(
        f"result: status={status}, monotone_minimum={monotone_minimum}, "
        f"smallest_evaluated_success={smallest_evaluated_success}, "
        f"probes={len(evaluations)}, "
        f"cumulative_bp={sum(r['elapsed_seconds'] for r in evaluations):.3f}s, "
        f"wall={wall_seconds:.3f}s"
    )

    if not args.no_save:
        paths = save_results(
            args=args,
            params=params,
            loaded=loaded,
            available_rows_by_poly=available_rows_by_poly,
            effective_upper=effective_upper,
            evaluations=evaluations,
            status=status,
            monotone_minimum=monotone_minimum,
            smallest_evaluated_success=smallest_evaluated_success,
            recovered=None if final_result is None else final_result.recovered,
            secret=secret,
            wall_seconds=wall_seconds,
        )
        print(f"saved summary: {paths['summary']}")
        print(f"saved evaluations: {paths['evaluations']}")
        print(f"saved arrays: {paths['arrays']}")
    return 0 if monotone_minimum is not None else 2


if __name__ == "__main__":
    raise SystemExit(main())
