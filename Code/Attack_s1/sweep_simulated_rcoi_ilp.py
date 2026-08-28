#!/usr/bin/env python3
"""Collect simulated RCoI attempts once and sweep ILP recovery sample counts."""

from __future__ import annotations

import argparse
import csv
import json
from collections import Counter
from dataclasses import asdict
from datetime import datetime
from pathlib import Path
from time import perf_counter

import numpy as np

from binary_search_constraints import constraint_prefix
from bp_attack import CollectionResult, collect_constraints
from ilp_attack import ILP_FORMULATIONS, ILPSolveResult, solve_secret_ilp
from mldsa_model import get_params, row_terms, sample_secret


REFERENCE_SOLVER = Path(__file__).resolve().parents[1] / "rej_2026_D2_SCA" / "code" / "14_ilp_solve.py"
REFERENCE_SOLVER_LABEL = "rej_2026_D2_SCA/code/14_ilp_solve.py"


def parse_counts(specification: str) -> list[int]:
    counts: list[int] = []
    for raw in specification.split(","):
        token = raw.strip()
        if not token:
            continue
        try:
            count = int(token)
        except ValueError as exc:
            raise ValueError(
                f"invalid count {raw!r}; --counts-per-poly requires integers"
            ) from exc
        if count <= 0:
            raise ValueError("--counts-per-poly values must be positive")
        counts.append(count)
    if not counts:
        raise ValueError("--counts-per-poly did not contain a positive integer")
    return sorted(set(counts))


def parse_args(argv: list[str] | None = None) -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Simulate signing attempts, retain attempts whose first z-norm abort "
            "is one of the four RCoI values, and solve fixed sample prefixes "
            "with a selectable SciPy/HiGHS ILP formulation."
        )
    )
    parser.add_argument("--level", default="2", choices=["2", "3", "5", "toy"])
    parser.add_argument(
        "--signature-attempts",
        type=int,
        default=4_000_000,
        help="maximum simulated internal signing attempts",
    )
    parser.add_argument(
        "--counts-per-poly",
        default="1000,2000,3000,4000,5000",
        help="comma-separated balanced RCoI constraint prefixes to solve",
    )
    parser.add_argument("--seed", type=int, default=1)
    parser.add_argument(
        "--time-limit-per-poly",
        type=float,
        default=120.0,
        help="HiGHS time limit for each polynomial; 0 disables the limit",
    )
    parser.add_argument(
        "--ilp-formulation",
        choices=ILP_FORMULATIONS,
        default="interval",
        help=(
            "'interval' uses ranged constraints; 'noisy-equality' writes each "
            "four-value equation with bounded noise as two <= inequalities"
        ),
    )
    parser.add_argument(
        "--allow-multiple-per-attempt",
        action="store_true",
        help=(
            "skipped-check baseline: retain all four-class target coefficients; "
            "default keeps only a first-abort RCoI, matching poly_chknorm"
        ),
    )
    parser.add_argument(
        "--progress-every",
        type=int,
        default=100_000,
        help="print collection progress every N attempts; 0 disables it",
    )
    parser.add_argument("--output-dir", type=Path, default=Path("outputs"))
    parser.add_argument("--no-save", action="store_true")
    args = parser.parse_args(argv)
    if args.signature_attempts <= 0:
        parser.error("--signature-attempts must be positive")
    if args.time_limit_per_poly < 0:
        parser.error("--time-limit-per-poly must be nonnegative")
    if args.progress_every < 0:
        parser.error("--progress-every must be nonnegative")
    try:
        args.resolved_counts = parse_counts(args.counts_per_poly)
    except ValueError as exc:
        parser.error(str(exc))
    return args


def rcoi_class(params, z_value: int) -> int:
    classes = {
        params.gamma1: 0,
        params.gamma1 - 1: 1,
        -params.gamma1: 2,
        -params.gamma1 - 1: 3,
    }
    try:
        return classes[int(z_value)]
    except KeyError as exc:
        raise ValueError(f"z={z_value} is not one of the four RCoI values") from exc


def dense_challenge(params, sample) -> np.ndarray:
    challenge = np.zeros(params.n, dtype=np.int8)
    challenge[sample.challenge.positions] = sample.challenge.signs
    return challenge


def samples_as_npz_arrays(params, samples: list, secret: np.ndarray) -> dict[str, np.ndarray]:
    rows = len(samples)
    c_pred = np.empty((rows, params.n), dtype=np.int8)
    trace_id = np.empty(rows, dtype=np.int64)
    poly_l = np.empty(rows, dtype=np.int16)
    coeff_i = np.empty(rows, dtype=np.int16)
    z_pred_val = np.empty(rows, dtype=np.int32)
    lower = np.empty(rows, dtype=np.int16)
    upper = np.empty(rows, dtype=np.int16)
    classes = np.empty(rows, dtype=np.int8)
    pair_ok = np.empty(rows, dtype=np.bool_)
    for row, sample in enumerate(samples):
        c_pred[row] = dense_challenge(params, sample)
        trace_id[row] = int(sample.signature_index)
        poly_l[row] = int(sample.poly_index)
        coeff_i[row] = int(sample.coeff_index)
        z_pred_val[row] = int(sample.z_value)
        lower[row] = int(sample.lower)
        upper[row] = int(sample.upper)
        classes[row] = rcoi_class(params, sample.z_value)
        columns, values = row_terms(params, sample.challenge, sample.coeff_index)
        product = sum(
            int(value) * int(secret[sample.poly_index, int(column)])
            for column, value in zip(columns, values)
        )
        pair_ok[row] = int(sample.lower) <= product <= int(sample.upper)
    return {
        "trace_id": trace_id,
        "poly_l": poly_l,
        "coeff_i": coeff_i,
        "k": poly_l.astype(np.int64) * params.n + coeff_i.astype(np.int64),
        "c_pred": c_pred,
        "z_pred_val": z_pred_val,
        "rcoi_class": classes,
        "lower": lower,
        "upper": upper,
        "pair_ok": pair_ok,
    }


def evaluation_record(count: int, samples: list, result: ILPSolveResult) -> dict:
    trace_ids = {int(sample.signature_index) for sample in samples}
    poly_solve = []
    for poly_index, poly_result in enumerate(result.poly_results):
        record = asdict(poly_result)
        record.pop("recovered")
        record["poly_index"] = poly_index
        record["rows"] = result.rows_by_poly[poly_index]
        record["mismatches"] = result.mismatches_by_poly[poly_index]
        poly_solve.append(record)
    return {
        "constraints_per_poly": count,
        "total_constraints": len(samples),
        "rows_by_poly": result.rows_by_poly,
        "unique_signature_attempts": len(trace_ids),
        "max_signature_attempt": max(trace_ids),
        "exact_recovery": result.exact_recovery,
        "has_solution_by_poly": result.has_solution_by_poly,
        "total_mismatches": result.total_mismatches,
        "mismatches_by_poly": result.mismatches_by_poly,
        "interval_violations": result.interval_violations,
        "elapsed_seconds": result.elapsed_seconds,
        "poly_solve": poly_solve,
    }


def save_results(
    args: argparse.Namespace,
    params,
    collection: CollectionResult,
    secret: np.ndarray,
    evaluations: list[dict],
    recovered_arrays: list[np.ndarray],
    wall_seconds: float,
) -> dict[str, str]:
    output_dir = args.output_dir
    if not output_dir.is_absolute():
        output_dir = Path(__file__).resolve().parent / output_dir
    output_dir.mkdir(parents=True, exist_ok=True)
    stamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    formulation_tag = args.ilp_formulation.replace("-", "_")
    prefix = output_dir / (
        f"{params.name}_s1_simulated_rcoi_ilp_{formulation_tag}_{stamp}"
    )
    summary_path = Path(f"{prefix}_summary.json")
    evaluations_path = Path(f"{prefix}_evaluations.csv")
    arrays_path = Path(f"{prefix}_result.npz")
    samples_path = Path(f"{prefix}_samples.npz")
    secret_path = Path(f"{prefix}_s1_true.npy")

    sample_arrays = samples_as_npz_arrays(params, collection.samples, secret)
    np.savez_compressed(samples_path, **sample_arrays)
    np.save(secret_path, secret)
    np.savez_compressed(
        arrays_path,
        secret=secret,
        counts_per_poly=np.asarray(args.resolved_counts, dtype=np.int32),
        recovered=np.stack(recovered_arrays),
        exact_recovery=np.asarray(
            [evaluation["exact_recovery"] for evaluation in evaluations],
            dtype=np.bool_,
        ),
    )

    fields = [
        "constraints_per_poly",
        "total_constraints",
        "unique_signature_attempts",
        "max_signature_attempt",
        "exact_recovery",
        "has_solution_by_poly",
        "total_mismatches",
        "mismatches_by_poly",
        "interval_violations",
        "elapsed_seconds",
        "solver_status_by_poly",
        "solver_time_by_poly",
    ]
    with evaluations_path.open("w", newline="", encoding="utf-8") as file:
        writer = csv.DictWriter(file, fieldnames=fields)
        writer.writeheader()
        for evaluation in evaluations:
            writer.writerow(
                {
                    "constraints_per_poly": evaluation["constraints_per_poly"],
                    "total_constraints": evaluation["total_constraints"],
                    "unique_signature_attempts": evaluation[
                        "unique_signature_attempts"
                    ],
                    "max_signature_attempt": evaluation["max_signature_attempt"],
                    "exact_recovery": evaluation["exact_recovery"],
                    "has_solution_by_poly": ";".join(
                        map(str, evaluation["has_solution_by_poly"])
                    ),
                    "total_mismatches": evaluation["total_mismatches"],
                    "mismatches_by_poly": ";".join(
                        "" if value is None else str(value)
                        for value in evaluation["mismatches_by_poly"]
                    ),
                    "interval_violations": evaluation["interval_violations"],
                    "elapsed_seconds": evaluation["elapsed_seconds"],
                    "solver_status_by_poly": ";".join(
                        str(poly["status"]) for poly in evaluation["poly_solve"]
                    ),
                    "solver_time_by_poly": ";".join(
                        f"{poly['elapsed_seconds']:.6f}"
                        for poly in evaluation["poly_solve"]
                    ),
                }
            )

    z_counts = Counter(int(sample.z_value) for sample in collection.samples)
    argument_payload = {
        key: str(value) if isinstance(value, Path) else value
        for key, value in vars(args).items()
        if key != "resolved_counts"
    }
    summary = {
        "solver": {
            "name": "SciPy HiGHS MILP",
            "formulation": args.ilp_formulation,
            "constraint_encoding": (
                "two upper-bound inequalities per bounded noisy equality"
                if args.ilp_formulation == "noisy-equality"
                else "one ranged LinearConstraint per sample"
            ),
            "objective": "minimize sum(s1 coefficients), matching reference script 14",
            "reference_file": REFERENCE_SOLVER_LABEL,
            "reference_file_exists": REFERENCE_SOLVER.is_file(),
        },
        "parameters": params.__dict__,
        "arguments": argument_payload,
        "resolved_counts_per_poly": args.resolved_counts,
        "simulation": {
            "seed": args.seed,
            "model": "z=y+c*s1; first poly_chknorm abort retained only for four RCoI values",
            "rcoi_values": [
                params.gamma1,
                params.gamma1 - 1,
                -params.gamma1,
                -params.gamma1 - 1,
            ],
            "one_per_attempt": not args.allow_multiple_per_attempt,
            "signature_attempts": collection.signatures_generated,
            "rejected_attempts": collection.rejected_attempts,
            "accepted_attempts": (
                collection.signatures_generated - collection.rejected_attempts
            ),
            "rcoi_attempts": collection.useful_signatures,
            "rcoi_rows": len(collection.samples),
            "rows_by_poly": collection.rows_by_poly,
            "z_value_counts": {str(key): value for key, value in sorted(z_counts.items())},
            "rcoi_rate_per_attempt": (
                collection.useful_signatures / collection.signatures_generated
            ),
            "rejection_rate_per_attempt": (
                collection.rejected_attempts / collection.signatures_generated
            ),
            "truth_fields_used_for_constraint_construction": False,
        },
        "evaluations": evaluations,
        "successful_counts_per_poly": [
            evaluation["constraints_per_poly"]
            for evaluation in evaluations
            if evaluation["exact_recovery"]
        ],
        "wall_seconds": wall_seconds,
        "files": {
            "samples": str(samples_path.resolve()),
            "secret": str(secret_path.resolve()),
            "evaluations": str(evaluations_path.resolve()),
            "arrays": str(arrays_path.resolve()),
        },
    }
    summary_path.write_text(
        json.dumps(summary, indent=2, ensure_ascii=False), encoding="utf-8"
    )
    return {
        "summary": str(summary_path.resolve()),
        "samples": str(samples_path.resolve()),
        "secret": str(secret_path.resolve()),
        "evaluations": str(evaluations_path.resolve()),
        "arrays": str(arrays_path.resolve()),
    }


def main(argv: list[str] | None = None) -> int:
    args = parse_args(argv)
    started = perf_counter()
    params = get_params(args.level)
    rng = np.random.default_rng(args.seed)
    secret = sample_secret(params, rng)
    largest_count = max(args.resolved_counts)
    print(
        f"parameters: {params.name}, n={params.n}, ell={params.ell}, "
        f"eta={params.eta}, tau={params.tau}, gamma1={params.gamma1}, "
        f"beta={params.beta}",
        flush=True,
    )
    print(
        "simulation: first-abort RCoI collection, "
        f"seed={args.seed}, max_attempts={args.signature_attempts}, "
        f"target_rows_per_poly={largest_count}, "
        f"one_per_attempt={not args.allow_multiple_per_attempt}",
        flush=True,
    )
    print(f"ILP formulation: {args.ilp_formulation}", flush=True)
    collection = collect_constraints(
        params=params,
        secret=secret,
        rng=rng,
        signatures=args.signature_attempts,
        constraint_mode="rcoi-inequality",
        threshold=None,
        max_constraints_per_poly=largest_count,
        one_per_signature=not args.allow_multiple_per_attempt,
        progress_interval=args.progress_every,
    )
    print(
        f"collection: attempts={collection.signatures_generated}, "
        f"rejected={collection.rejected_attempts}, "
        f"rcoi_attempts={collection.useful_signatures}, "
        f"rows={len(collection.samples)}, rows_by_poly={collection.rows_by_poly}",
        flush=True,
    )
    if any(count < largest_count for count in collection.rows_by_poly):
        raise RuntimeError(
            "not enough simulated attempts to fill the largest balanced RCoI "
            f"prefix: wanted {largest_count}, got {collection.rows_by_poly}; "
            "increase --signature-attempts"
        )

    time_limit = args.time_limit_per_poly or None
    evaluations: list[dict] = []
    recovered_arrays: list[np.ndarray] = []
    for count in args.resolved_counts:
        samples = constraint_prefix(collection.samples, params.ell, count)
        result = solve_secret_ilp(
            params=params,
            samples=samples,
            secret=secret,
            time_limit_per_poly=time_limit,
            formulation=args.ilp_formulation,
        )
        evaluation = evaluation_record(count, samples, result)
        evaluations.append(evaluation)
        recovered_arrays.append(result.recovered)
        print(
            f"probe: constraints_per_poly={count}, total={len(samples)}, "
            f"max_attempt={evaluation['max_signature_attempt']}, "
            f"exact={result.exact_recovery}, mismatches={result.total_mismatches}, "
            f"by_poly={result.mismatches_by_poly}, "
            f"has_solution={result.has_solution_by_poly}, "
            f"time={result.elapsed_seconds:.3f}s",
            flush=True,
        )

    wall_seconds = perf_counter() - started
    successes = [
        evaluation["constraints_per_poly"]
        for evaluation in evaluations
        if evaluation["exact_recovery"]
    ]
    print(
        f"result: successful_counts_per_poly={successes}, wall={wall_seconds:.3f}s",
        flush=True,
    )
    if not args.no_save:
        paths = save_results(
            args=args,
            params=params,
            collection=collection,
            secret=secret,
            evaluations=evaluations,
            recovered_arrays=recovered_arrays,
            wall_seconds=wall_seconds,
        )
        print(f"saved summary: {paths['summary']}")
        print(f"saved simulated samples: {paths['samples']}")
        print(f"saved truth s1: {paths['secret']}")
        print(f"saved evaluations: {paths['evaluations']}")
        print(f"saved arrays: {paths['arrays']}")
    return 0 if successes else 2


if __name__ == "__main__":
    raise SystemExit(main())
