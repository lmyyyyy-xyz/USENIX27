#!/usr/bin/env python3
"""Binary-search BP sample thresholds for noiseless randomness leakage.

The probability-equality and corrected interval-inequality BP branches use the
same generated secrets, ordered relation streams, tested prefixes, and BP
configuration.  Search is performed on a configurable sample grid (one sample
by default) under the usual monotonic-success assumption.
"""

from __future__ import annotations

import argparse
import csv
import json
from datetime import datetime
from pathlib import Path
from time import perf_counter

import numpy as np

from hillclimb_mldsa_noise import MLDSA_PARAMS, compute_beta_eff
from sweep_bp_greedy_noiseless import (
    BRANCH_BP_EQUALITY,
    BRANCH_BP_INEQUALITY,
    HINT_SOLVER_IMPORT_ERROR,
    PyBP,
    _calibrate_error_distribution,
    _collect_relation_stream,
    _solve_bp_equality,
    _solve_bp_inequality,
)


DEFAULT_GRANULARITY = 1
ALL_BRANCHES = (BRANCH_BP_EQUALITY, BRANCH_BP_INEQUALITY)
RESULT_FIELDS = [
    "trial_index",
    "samples",
    "branch",
    "key_idx",
    "success",
    "mismatches",
    "violations",
    "bp_iterations",
    "time_s",
]


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Use binary search to find BP recovery thresholds for probability "
            "equalities and interval inequalities under noiseless randomness leakage."
        )
    )
    parser.add_argument("--params", type=int, choices=[44, 65, 87], default=44)
    parser.add_argument("--leakage", type=int, default=6)
    parser.add_argument("--num-keys", type=int, default=5)
    parser.add_argument("--seed", type=int, default=42)
    parser.add_argument("--min-samples", type=int, default=500)
    parser.add_argument("--max-samples", type=int, default=8_000)
    parser.add_argument("--granularity", type=int, default=DEFAULT_GRANULARITY)
    parser.add_argument(
        "--branches", nargs="+", choices=ALL_BRANCHES, default=list(ALL_BRANCHES)
    )
    parser.add_argument("--collection-workers", type=int, default=1)
    parser.add_argument("--bp-iterations", type=int, default=20)
    parser.add_argument("--bp-threads", type=int, default=16)
    parser.add_argument("--bp-uniform-prior", action="store_true")
    parser.add_argument("--likelihood-calibration-samples", type=int, default=50_000)
    parser.add_argument("--likelihood-smoothing", type=float, default=1.0)
    parser.add_argument("--output-dir", default="noiseless_threshold_results")
    args = parser.parse_args()
    _validate_args(parser, args)
    return args


def _validate_args(parser: argparse.ArgumentParser, args: argparse.Namespace) -> None:
    if args.granularity <= 0:
        parser.error("--granularity must be positive")
    for name in ("min_samples", "max_samples"):
        value = int(getattr(args, name))
        if value <= 0 or value % args.granularity != 0:
            parser.error(
                f"--{name.replace('_', '-')} must be a positive multiple of "
                "--granularity"
            )
    if args.max_samples < args.min_samples:
        parser.error("--max-samples must be >= --min-samples")
    if args.num_keys <= 0:
        parser.error("--num-keys must be positive")
    if args.collection_workers <= 0:
        parser.error("--collection-workers must be positive")
    if args.bp_iterations <= 0 or args.bp_threads <= 0:
        parser.error("BP iterations and threads must be positive")
    if args.likelihood_calibration_samples <= 0:
        parser.error("--likelihood-calibration-samples must be positive")
    if args.likelihood_smoothing <= 0:
        parser.error("--likelihood-smoothing must be positive")
    if PyBP is None:
        parser.error(f"external PyBP backend unavailable: {HINT_SOLVER_IMPORT_ERROR!r}")


def sample_grid(minimum: int, maximum: int, granularity: int) -> list[int]:
    return list(range(int(minimum), int(maximum) + 1, int(granularity)))


def write_outputs(
    args: argparse.Namespace,
    params: dict,
    beta_eff: int,
    calibration: dict,
    collections: list[dict],
    thresholds: dict[str, int | None],
    traces: dict[str, list[dict]],
    rows: list[dict],
    secrets: np.ndarray,
    threshold_recovered: dict[str, np.ndarray],
) -> dict:
    output_dir = Path(args.output_dir)
    if not output_dir.is_absolute():
        output_dir = Path(__file__).resolve().parent / output_dir
    output_dir.mkdir(parents=True, exist_ok=True)
    stamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    prefix = output_dir / f"{params['name']}_j{args.leakage}_bp_binary_{stamp}"
    csv_path = prefix.with_suffix(".csv")
    json_path = prefix.with_suffix(".json")
    secret_path = Path(f"{prefix}_secrets.npy")

    with csv_path.open("w", newline="", encoding="utf-8") as file:
        writer = csv.DictWriter(file, fieldnames=RESULT_FIELDS)
        writer.writeheader()
        writer.writerows(rows)
    np.save(secret_path, secrets)

    recovered_paths = {}
    for branch, recovered in threshold_recovered.items():
        count = thresholds[branch]
        path = Path(f"{prefix}_{branch}_{count}_recovered.npy")
        np.save(path, recovered)
        recovered_paths[branch] = str(path.resolve())

    payload = {
        "parameters": {
            "variant": params["name"],
            "n": params["n"],
            "eta": params["eta"],
            "tau": params["tau"],
            "leakage_index": args.leakage,
            "beta_eff": beta_eff,
            "noise_level": 0.0,
            "inequality_residual_support": f"({-beta_eff}, {beta_eff}]",
        },
        "arguments": vars(args),
        "search": {
            "method": "binary search over the finite sample grid",
            "granularity": args.granularity,
            "monotonicity_assumption": (
                "for each branch, exact BP recovery is assumed not to revert as "
                "more rows from the same ordered prefix stream are added"
            ),
            "boundary_checks": (
                "the maximum is tested first; the minimum and the final failing "
                "predecessor are tested by the binary-search procedure"
            ),
            "traces": traces,
        },
        "constraint_branches": {
            BRANCH_BP_EQUALITY: (
                "independently calibrated probability-equality RHS distributions"
            ),
            BRANCH_BP_INEQUALITY: (
                "uniform RHS over centered modular residual support "
                "(-beta_eff,beta_eff], excluding the negative endpoint"
            ),
        },
        "success_definition": "all 256 coefficients of every requested s1 key are correct",
        "threshold_definition": (
            "smallest successful grid point returned by binary search under the "
            "monotonicity assumption"
        ),
        "minimum_tested_samples": thresholds,
        "residual_calibration": calibration,
        "collections": collections,
        "secret_path": str(secret_path.resolve()),
        "recovered_paths": recovered_paths,
        "csv_path": str(csv_path.resolve()),
        "results": rows,
    }
    with json_path.open("w", encoding="utf-8") as file:
        json.dump(payload, file, ensure_ascii=False, indent=2)
    return {
        "csv": str(csv_path.resolve()),
        "json": str(json_path.resolve()),
        "secrets": str(secret_path.resolve()),
        "recovered": recovered_paths,
    }


def main() -> None:
    args = parse_args()
    params = MLDSA_PARAMS[args.params]
    beta_eff = int(compute_beta_eff(params, args.leakage))
    grid = sample_grid(args.min_samples, args.max_samples, args.granularity)

    residual_probabilities = None
    residual_offset = 0
    calibration = None
    if BRANCH_BP_EQUALITY in args.branches:
        residual_probabilities, residual_offset, calibration = (
            _calibrate_error_distribution(
                params,
                args.leakage,
                args.seed + 9_000_001,
                args.likelihood_calibration_samples,
                args.collection_workers,
                args.likelihood_smoothing,
            )
        )
        print(
            "calibrated probability equality: "
            f"relations={args.likelihood_calibration_samples}, "
            f"observed=[{calibration['observed_residual_min']},"
            f"{calibration['observed_residual_max']}], "
            f"time={calibration['time_s']:.2f}s",
            flush=True,
        )

    master_rng = np.random.default_rng(args.seed)
    datasets = []
    collections = []
    for key_idx, rng in enumerate(master_rng.spawn(args.num_keys)):
        x_true = rng.integers(
            -params["eta"], params["eta"] + 1,
            size=params["n"], dtype=np.int8,
        )
        started = perf_counter()
        z_tilde, C, signatures = _collect_relation_stream(
            rng,
            x_true,
            args.max_samples,
            params,
            args.leakage,
            args.collection_workers,
        )
        elapsed = perf_counter() - started
        datasets.append({"x_true": x_true, "z_tilde": z_tilde, "C": C})
        collections.append(
            {
                "key_idx": key_idx,
                "relations": int(len(z_tilde)),
                "accepted_signatures_consumed": int(signatures),
                "time_s": elapsed,
            }
        )
        print(
            f"collected key {key_idx + 1}/{args.num_keys}: "
            f"relations={len(z_tilde)}, time={elapsed:.2f}s",
            flush=True,
        )

    rows = []
    traces = {branch: [] for branch in args.branches}
    cache: dict[tuple[str, int], dict] = {}
    trial_index = 0

    def evaluate(branch: str, count: int) -> dict:
        nonlocal trial_index
        key = (branch, int(count))
        if key in cache:
            return cache[key]
        trial_index += 1
        all_success = True
        recovered_keys = []
        total_time = 0.0
        key_summaries = []
        for key_idx, dataset in enumerate(datasets):
            C_prefix = dataset["C"][:count]
            z_prefix = dataset["z_tilde"][:count]
            started = perf_counter()
            if branch == BRANCH_BP_EQUALITY:
                recovered, violations, iterations = _solve_bp_equality(
                    C_prefix,
                    z_prefix,
                    params,
                    args,
                    residual_probabilities,
                    residual_offset,
                )
            elif branch == BRANCH_BP_INEQUALITY:
                recovered, violations, iterations = _solve_bp_inequality(
                    C_prefix, z_prefix, params, args
                )
            else:
                raise ValueError(f"unknown branch: {branch}")
            elapsed = perf_counter() - started
            mismatches = int(np.count_nonzero(recovered != dataset["x_true"]))
            success = mismatches == 0
            all_success = all_success and success
            recovered_keys.append(recovered)
            total_time += elapsed
            key_summaries.append(
                {"key_idx": key_idx, "success": success, "mismatches": mismatches}
            )
            row = {
                "trial_index": trial_index,
                "samples": int(count),
                "branch": branch,
                "key_idx": key_idx,
                "success": success,
                "mismatches": mismatches,
                "violations": int(violations),
                "bp_iterations": int(iterations),
                "time_s": elapsed,
            }
            rows.append(row)
            print(
                f"trial={trial_index},samples={count},branch={branch},"
                f"key={key_idx},success={success},mismatches={mismatches},"
                f"violations={violations},time={elapsed:.3f}s",
                flush=True,
            )

        result = {
            "success": bool(all_success),
            "recovered": np.stack(recovered_keys),
            "time_s": total_time,
            "keys": key_summaries,
        }
        cache[key] = result
        traces[branch].append(
            {
                "trial_index": trial_index,
                "samples": int(count),
                "all_keys_success": bool(all_success),
                "time_s": total_time,
                "keys": key_summaries,
            }
        )
        return result

    thresholds = {branch: None for branch in args.branches}
    threshold_recovered = {}
    for branch in args.branches:
        high_index = len(grid) - 1
        high_result = evaluate(branch, grid[high_index])
        if not high_result["success"]:
            print(
                f"no threshold for {branch}: upper bound {grid[high_index]} failed",
                flush=True,
            )
            continue

        low_result = evaluate(branch, grid[0])
        if low_result["success"]:
            threshold_index = 0
        else:
            low_index = 0
            while high_index - low_index > 1:
                midpoint = (low_index + high_index) // 2
                result = evaluate(branch, grid[midpoint])
                if result["success"]:
                    high_index = midpoint
                else:
                    low_index = midpoint
            threshold_index = high_index

        threshold = grid[threshold_index]
        thresholds[branch] = threshold
        threshold_recovered[branch] = evaluate(branch, threshold)["recovered"]
        print(f"binary threshold found: {branch} -> {threshold}", flush=True)

    paths = write_outputs(
        args=args,
        params=params,
        beta_eff=beta_eff,
        calibration=calibration,
        collections=collections,
        thresholds=thresholds,
        traces=traces,
        rows=rows,
        secrets=np.stack([dataset["x_true"] for dataset in datasets]),
        threshold_recovered=threshold_recovered,
    )
    print(f"minimum_tested_samples={thresholds}")
    print(f"saved_csv={paths['csv']}")
    print(f"saved_json={paths['json']}")
    print(f"saved_secrets={paths['secrets']}")
    print(f"saved_recovered={paths['recovered']}")
    raise SystemExit(0 if all(value is not None for value in thresholds.values()) else 2)


if __name__ == "__main__":
    main()
