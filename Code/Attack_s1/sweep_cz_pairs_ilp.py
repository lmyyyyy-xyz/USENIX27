#!/usr/bin/env python3
"""Sweep the ILP sample cost on one collected rejected ``(c,z)`` data set.

The data loading and prefix policy are shared with the existing BP experiment.
The solve step is adapted from ``14_ilp_solve.py`` in the supplied
``rej_2026_D2_SCA_package``.  Thus BP and ILP can be compared on exactly the
same recovered pairs rather than on independently sampled constraints.
"""

from __future__ import annotations

import argparse
import csv
import json
from dataclasses import asdict
from datetime import datetime
from pathlib import Path
from time import perf_counter

import numpy as np

from binary_search_constraints import constraint_prefix
from binary_search_cz_pairs_bp import order_samples_for_prefix
from ilp_attack import ILP_FORMULATIONS, ILPSolveResult, solve_secret_ilp
from mldsa_model import get_params
from run_cz_pairs_bp import DEFAULT_DATASET, load_cz_pairs


REFERENCE_SOLVER = Path(__file__).resolve().parents[1] / "rej_2026_D2_SCA" / "code" / "14_ilp_solve.py"
REFERENCE_SOLVER_LABEL = "rej_2026_D2_SCA/code/14_ilp_solve.py"


def parse_args(argv: list[str] | None = None) -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Use a selectable SciPy/HiGHS integer-programming formulation to "
            "solve collected four-value (c,z) samples at several prefix sizes."
        )
    )
    parser.add_argument("--dataset", type=Path, default=DEFAULT_DATASET)
    parser.add_argument(
        "--secret",
        type=Path,
        default=None,
        help="truth s1 for evaluation only (default: s1_true.npy beside dataset)",
    )
    parser.add_argument("--level", default="2", choices=["2", "3", "5", "toy"])
    parser.add_argument(
        "--counts",
        default="500,1000,1500,max,all",
        help=(
            "comma-separated equal rows per polynomial; 'max' uses the largest "
            "balanced prefix and 'all' uses every collected row"
        ),
    )
    parser.add_argument(
        "--prefix-order",
        choices=["trace-id", "file"],
        default="trace-id",
        help="deterministic order before taking equal per-polynomial prefixes",
    )
    parser.add_argument(
        "--time-limit-per-poly",
        type=float,
        default=120.0,
        help="HiGHS limit for each polynomial in seconds; 0 disables the limit",
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
    parser.add_argument("--output-dir", type=Path, default=Path("outputs"))
    parser.add_argument("--no-save", action="store_true")
    args = parser.parse_args(argv)
    if args.time_limit_per_poly < 0:
        parser.error("--time-limit-per-poly must be nonnegative")
    if not args.counts.strip():
        parser.error("--counts must not be empty")
    return args


def resolve_count_specs(specification: str, available: list[int]) -> list[tuple[str, int | None]]:
    """Resolve numeric, ``max`` and ``all`` sample selections."""

    balanced_max = min(available)
    resolved: list[tuple[str, int | None]] = []
    seen: set[tuple[str, int | None]] = set()
    for raw in specification.split(","):
        token = raw.strip().lower()
        if not token:
            continue
        if token == "all":
            item = ("all", None)
        elif token == "max":
            item = (f"max={balanced_max}", balanced_max)
        else:
            try:
                count = int(token)
            except ValueError as exc:
                raise ValueError(
                    f"invalid --counts item {raw!r}; use positive integers, max, or all"
                ) from exc
            if count <= 0:
                raise ValueError("numeric --counts items must be positive")
            if count > balanced_max:
                raise ValueError(
                    f"requested {count} rows per polynomial, but the balanced "
                    f"maximum is {balanced_max} from available rows {available}"
                )
            item = (str(count), count)
        if item not in seen:
            resolved.append(item)
            seen.add(item)
    if not resolved:
        raise ValueError("--counts did not contain a usable selection")
    return resolved


def _poly_payload(result: ILPSolveResult) -> list[dict]:
    payload: list[dict] = []
    for poly_index, poly in enumerate(result.poly_results):
        record = asdict(poly)
        record.pop("recovered")
        record["poly_index"] = poly_index
        record["rows"] = result.rows_by_poly[poly_index]
        record["mismatches"] = result.mismatches_by_poly[poly_index]
        payload.append(record)
    return payload


def _evaluation_record(
    label: str,
    equal_count: int | None,
    samples: list,
    result: ILPSolveResult,
) -> dict:
    trace_ids = {int(sample.signature_index) for sample in samples}
    return {
        "selection": label,
        "constraints_per_poly": equal_count,
        "total_constraints": len(samples),
        "rows_by_poly": result.rows_by_poly,
        "unique_trace_ids": len(trace_ids),
        "max_trace_id": max(trace_ids),
        "exact_recovery": result.exact_recovery,
        "has_solution_by_poly": result.has_solution_by_poly,
        "total_mismatches": result.total_mismatches,
        "mismatches_by_poly": result.mismatches_by_poly,
        "interval_violations": result.interval_violations,
        "elapsed_seconds": result.elapsed_seconds,
        "poly_solve": _poly_payload(result),
    }


def save_results(
    args: argparse.Namespace,
    params,
    loaded,
    selections: list[tuple[str, int | None]],
    evaluations: list[dict],
    recovered_arrays: list[np.ndarray],
    secret: np.ndarray,
    wall_seconds: float,
) -> dict[str, str]:
    output_dir = args.output_dir
    if not output_dir.is_absolute():
        output_dir = Path(__file__).resolve().parent / output_dir
    output_dir.mkdir(parents=True, exist_ok=True)
    stamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    formulation_tag = args.ilp_formulation.replace("-", "_")
    prefix = output_dir / (
        f"{params.name}_s1_cz_pairs_ilp_sweep_{formulation_tag}_{stamp}"
    )
    summary_path = Path(f"{prefix}_summary.json")
    evaluations_path = Path(f"{prefix}_evaluations.csv")
    arrays_path = Path(f"{prefix}_result.npz")

    fields = [
        "selection",
        "constraints_per_poly",
        "total_constraints",
        "rows_by_poly",
        "unique_trace_ids",
        "max_trace_id",
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
                    "selection": evaluation["selection"],
                    "constraints_per_poly": evaluation["constraints_per_poly"],
                    "total_constraints": evaluation["total_constraints"],
                    "rows_by_poly": ";".join(map(str, evaluation["rows_by_poly"])),
                    "unique_trace_ids": evaluation["unique_trace_ids"],
                    "max_trace_id": evaluation["max_trace_id"],
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

    argument_payload = {
        key: str(value) if isinstance(value, Path) else value
        for key, value in vars(args).items()
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
        "dataset": {
            "path": str(args.dataset.resolve()),
            "source_rows": loaded.source_rows,
            "available_rows_by_poly": loaded.rows_by_poly,
            "unique_trace_ids": loaded.unique_trace_ids,
            "pair_ok_count_for_audit": loaded.pair_ok_count,
            "truth_fields_used_for_recovery": False,
        },
        "selection_policy": {
            "prefix_order": args.prefix_order,
            "resolved": [
                {"label": label, "constraints_per_poly": count}
                for label, count in selections
            ],
            "all_means_unbalanced_complete_dataset": True,
        },
        "evaluations": evaluations,
        "successful_selections": [
            evaluation["selection"]
            for evaluation in evaluations
            if evaluation["exact_recovery"]
        ],
        "wall_seconds": wall_seconds,
        "files": {
            "secret": str(args.secret.resolve()),
            "evaluations": str(evaluations_path.resolve()),
            "arrays": str(arrays_path.resolve()),
        },
    }
    summary_path.write_text(
        json.dumps(summary, indent=2, ensure_ascii=False), encoding="utf-8"
    )
    np.savez_compressed(
        arrays_path,
        secret=secret,
        selections=np.asarray([label for label, _count in selections]),
        counts_per_poly=np.asarray(
            [-1 if count is None else count for _label, count in selections],
            dtype=np.int32,
        ),
        recovered=np.stack(recovered_arrays),
        exact_recovery=np.asarray(
            [evaluation["exact_recovery"] for evaluation in evaluations],
            dtype=np.bool_,
        ),
    )
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
    ordered_samples = order_samples_for_prefix(loaded.samples, args.prefix_order)
    selections = resolve_count_specs(args.counts, loaded.rows_by_poly)
    time_limit = args.time_limit_per_poly or None
    print(
        f"parameters: {params.name}, n={params.n}, ell={params.ell}, "
        f"eta={params.eta}, tau={params.tau}",
        flush=True,
    )
    print(
        f"dataset: {args.dataset}, rows={loaded.source_rows}, "
        f"rows_by_poly={loaded.rows_by_poly}, prefix_order={args.prefix_order}",
        flush=True,
    )
    print(
        "solver: SciPy/HiGHS MILP from reference script 14; "
        f"formulation={args.ilp_formulation}; "
        f"time_limit_per_poly={time_limit}; selections={selections}",
        flush=True,
    )

    evaluations: list[dict] = []
    recovered_arrays: list[np.ndarray] = []
    for label, equal_count in selections:
        samples = (
            list(ordered_samples)
            if equal_count is None
            else constraint_prefix(ordered_samples, params.ell, equal_count)
        )
        result = solve_secret_ilp(
            params=params,
            samples=samples,
            secret=secret,
            time_limit_per_poly=time_limit,
            formulation=args.ilp_formulation,
        )
        evaluation = _evaluation_record(label, equal_count, samples, result)
        evaluations.append(evaluation)
        recovered_arrays.append(result.recovered)
        print(
            f"probe: selection={label}, rows={len(samples)}, "
            f"rows_by_poly={result.rows_by_poly}, exact={result.exact_recovery}, "
            f"mismatches={result.total_mismatches}, "
            f"by_poly={result.mismatches_by_poly}, "
            f"has_solution={result.has_solution_by_poly}, "
            f"time={result.elapsed_seconds:.3f}s",
            flush=True,
        )

    wall_seconds = perf_counter() - started
    successes = [
        evaluation["selection"]
        for evaluation in evaluations
        if evaluation["exact_recovery"]
    ]
    print(
        f"result: successful_selections={successes}, wall={wall_seconds:.3f}s",
        flush=True,
    )
    if not args.no_save:
        paths = save_results(
            args=args,
            params=params,
            loaded=loaded,
            selections=selections,
            evaluations=evaluations,
            recovered_arrays=recovered_arrays,
            secret=secret,
            wall_seconds=wall_seconds,
        )
        print(f"saved summary: {paths['summary']}")
        print(f"saved evaluations: {paths['evaluations']}")
        print(f"saved arrays: {paths['arrays']}")
    return 0 if successes else 2


if __name__ == "__main__":
    raise SystemExit(main())
