#!/usr/bin/env python3
"""Binary-search the per-polynomial BP constraint count needed for s1 recovery.

The expensive skipped-z simulation is performed once at the upper constraint
limit.  Every BP probe then uses the first ``m`` rows of that same collected
data for each polynomial, so probe results are comparable and reproducible.
"""

from __future__ import annotations

import argparse
import json
from datetime import datetime
from pathlib import Path
from typing import Callable, TypeVar

import numpy as np

from bp_attack import (
    CollectionResult,
    InequalitySample,
    collect_constraints,
    resolve_threshold,
    solve_secret_bp,
)
from mldsa_model import get_params, sample_secret


_T = TypeVar("_T")


def parse_args(argv: list[str] | None = None) -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Collect one skipped-z data set, then binary-search the smallest "
            "per-polynomial constraint prefix that exactly recovers s1 with BP."
        )
    )
    parser.add_argument("--level", default="2", choices=["2", "3", "5", "toy"])
    parser.add_argument(
        "--constraint-mode",
        default="boundary-equality-marginalized",
        choices=[
            "inequality",
            "slack-equality",
            "boundary-equality",
            "boundary-equality-marginalized",
            "unknown-y-error-interval",
        ],
    )
    parser.add_argument(
        "--threshold",
        default="gamma1-beta",
        help=(
            "Threshold for inequality/slack-equality; boundary modes always "
            "use gamma1."
        ),
    )
    parser.add_argument("--signatures", type=int, default=1_000_000)
    parser.add_argument("--min-constraints-per-poly", type=int, default=1_000)
    parser.add_argument("--max-constraints-per-poly", type=int, default=2_000)
    parser.add_argument(
        "--scan-step",
        type=int,
        default=0,
        help=(
            "Evaluate every constraint count from min to max at this step. "
            "Zero keeps the default binary-search behavior."
        ),
    )
    parser.add_argument(
        "--freeze-recovered-polys",
        action="store_true",
        help=(
            "In scan mode, use the known simulation secret as an oracle and stop "
            "re-solving a polynomial after its 256 coefficients are all correct."
        ),
    )
    parser.add_argument("--seed", type=int, default=1)
    parser.add_argument("--bp-iterations", type=int, default=20)
    parser.add_argument("--bp-damping", type=float, default=0.0)
    parser.add_argument("--threads", type=int, default=16)
    parser.add_argument("--uniform-prior", action="store_true")
    parser.add_argument("--one-per-signature", action="store_true")
    parser.add_argument("--output-dir", default="outputs")
    parser.add_argument("--no-save", action="store_true")
    args = parser.parse_args(argv)

    if args.signatures <= 0:
        parser.error("--signatures must be positive")
    if args.min_constraints_per_poly <= 0:
        parser.error("--min-constraints-per-poly must be positive")
    if args.max_constraints_per_poly < args.min_constraints_per_poly:
        parser.error(
            "--max-constraints-per-poly must be >= --min-constraints-per-poly"
        )
    if args.scan_step < 0:
        parser.error("--scan-step must be nonnegative")
    if args.freeze_recovered_polys and args.scan_step == 0:
        parser.error("--freeze-recovered-polys requires a positive --scan-step")
    if args.bp_iterations <= 0 or args.threads <= 0:
        parser.error("--bp-iterations and --threads must be positive")
    if not 0.0 <= args.bp_damping < 1.0:
        parser.error("--bp-damping must satisfy 0 <= value < 1")
    return args


def constraint_prefix(
    samples: list[InequalitySample],
    ell: int,
    rows_per_poly: int,
) -> list[InequalitySample]:
    """Return the first ``rows_per_poly`` samples of every polynomial."""

    if ell <= 0:
        raise ValueError("ell must be positive")
    if rows_per_poly <= 0:
        raise ValueError("rows_per_poly must be positive")

    selected: list[InequalitySample] = []
    counts = [0] * ell
    for sample in samples:
        poly = int(sample.poly_index)
        if not 0 <= poly < ell:
            raise ValueError(f"sample polynomial index {poly} is outside [0,{ell})")
        if counts[poly] < rows_per_poly:
            selected.append(sample)
            counts[poly] += 1
    if any(count != rows_per_poly for count in counts):
        raise ValueError(
            f"requested {rows_per_poly} rows per polynomial, but selected {counts}"
        )
    return selected


def binary_search_first_success(
    lower_failure: int,
    upper_success: int,
    succeeds: Callable[[int], bool],
) -> int:
    """Find the first success assuming all counts after it also succeed.

    The caller must already have established that ``lower_failure`` fails and
    ``upper_success`` succeeds.  Loopy BP is not theoretically monotone, so the
    returned value is a boundary under that explicit assumption.
    """

    if lower_failure >= upper_success:
        raise ValueError("lower_failure must be smaller than upper_success")
    low = int(lower_failure)
    high = int(upper_success)
    while high - low > 1:
        middle = (low + high) // 2
        if succeeds(middle):
            high = middle
        else:
            low = middle
    return high


def _save_summary(
    args: argparse.Namespace,
    params,
    threshold: int,
    collection: CollectionResult,
    evaluations: list[dict],
    status: str,
    minimum: int | None,
    secret: np.ndarray,
    recovered: np.ndarray | None,
) -> dict[str, str]:
    output_dir = Path(args.output_dir)
    if not output_dir.is_absolute():
        output_dir = Path(__file__).resolve().parent / output_dir
    output_dir.mkdir(parents=True, exist_ok=True)

    stamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    mode_tag = args.constraint_mode.replace("-", "_")
    search_tag = "scan" if args.scan_step else "binary"
    prefix = output_dir / (
        f"{params.name}_s1_{mode_tag}_bp_{search_tag}_"
        f"{args.min_constraints_per_poly}-{args.max_constraints_per_poly}_{stamp}"
    )
    summary_path = Path(f"{prefix}_summary.json")
    arrays_path = Path(f"{prefix}_result.npz")

    summary = {
        "status": status,
        "minimum_constraints_per_poly": minimum,
        "guarantee": (
            "first successful evaluated grid point; counts between grid points "
            "were not evaluated"
            if minimum is not None and args.scan_step
            else (
                "minimum inside the requested interval under the monotone BP-success "
                "assumption"
                if minimum is not None
                else None
            )
        ),
        "warning": (
            "Loopy BP recovery is not theoretically monotone; only the configured "
            "grid points were evaluated."
            if args.scan_step
            else (
                "Loopy BP recovery is not theoretically monotone; binary search can "
                "miss isolated successes or failures between evaluated counts."
            )
        ),
        "parameters": {
            "name": params.name,
            "n": params.n,
            "ell": params.ell,
            "eta": params.eta,
            "tau": params.tau,
            "gamma1": params.gamma1,
            "beta": params.beta,
        },
        "experiment": {
            "level": args.level,
            "constraint_mode": args.constraint_mode,
            "resolved_threshold": threshold,
            "signatures": args.signatures,
            "min_constraints_per_poly": args.min_constraints_per_poly,
            "max_constraints_per_poly": args.max_constraints_per_poly,
            "scan_step": args.scan_step,
            "freeze_recovered_polys": args.freeze_recovered_polys,
            "seed": args.seed,
            "bp_iterations": args.bp_iterations,
            "bp_damping": args.bp_damping,
            "threads": args.threads,
            "uniform_prior": args.uniform_prior,
            "one_per_signature": args.one_per_signature,
        },
        "collection": {
            "signatures_generated": collection.signatures_generated,
            "useful_signatures": collection.useful_signatures,
            "total_rows": len(collection.samples),
            "rows_by_poly": collection.rows_by_poly,
            "positive_rows": collection.positive_rows,
            "negative_rows": collection.negative_rows,
        },
        "evaluations": evaluations,
    }
    summary_path.write_text(json.dumps(summary, indent=2), encoding="utf-8")
    if recovered is None:
        np.savez_compressed(arrays_path, secret=secret)
    else:
        np.savez_compressed(arrays_path, secret=secret, recovered=recovered)
    return {
        "summary": str(summary_path.resolve()),
        "arrays": str(arrays_path.resolve()),
    }


def main(argv: list[str] | None = None) -> int:
    args = parse_args(argv)
    params = get_params(args.level)
    boundary_modes = {
        "boundary-equality",
        "boundary-equality-marginalized",
        "unknown-y-error-interval",
    }
    threshold = (
        params.gamma1
        if args.constraint_mode in boundary_modes
        else resolve_threshold(params, args.threshold)
    )

    rng = np.random.default_rng(args.seed)
    secret = sample_secret(params, rng)
    print(
        f"parameters: {params.name}, n={params.n}, ell={params.ell}, "
        f"eta={params.eta}, tau={params.tau}, gamma1={params.gamma1}, "
        f"beta={params.beta}"
    )
    print(
        f"search: range=[{args.min_constraints_per_poly},"
        f"{args.max_constraints_per_poly}], mode={args.constraint_mode}, "
        f"signatures={args.signatures}, seed={args.seed}"
    )
    print(
        "warning: binary search assumes BP success is monotone in the constraint "
        "prefix; loopy BP does not guarantee this."
    )

    collection = collect_constraints(
        params=params,
        secret=secret,
        rng=rng,
        signatures=args.signatures,
        constraint_mode=args.constraint_mode,
        threshold=threshold,
        max_constraints_per_poly=args.max_constraints_per_poly,
        one_per_signature=args.one_per_signature,
    )
    print(
        f"collection: signatures={collection.signatures_generated}, "
        f"useful={collection.useful_signatures}, rows={len(collection.samples)}, "
        f"rows_by_poly={collection.rows_by_poly}"
    )
    if any(
        count < args.max_constraints_per_poly for count in collection.rows_by_poly
    ):
        raise RuntimeError(
            "not enough signatures to fill the upper search bound: "
            f"wanted {args.max_constraints_per_poly} rows per polynomial, got "
            f"{collection.rows_by_poly}; increase --signatures"
        )

    result_cache: dict[int, _T] = {}
    evaluations: list[dict] = []
    fixed_polynomials: dict[int, np.ndarray] = {}
    first_success_by_poly: dict[int, int] = {}

    def evaluate(rows_per_poly: int):
        cached = result_cache.get(rows_per_poly)
        if cached is not None:
            return cached
        samples = constraint_prefix(
            collection.samples,
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
            fixed_polynomials=(
                fixed_polynomials if args.freeze_recovered_polys else None
            ),
        )
        newly_frozen: list[int] = []
        if args.freeze_recovered_polys:
            for poly_index in range(params.ell):
                if poly_index in fixed_polynomials:
                    continue
                if np.array_equal(result.recovered[poly_index], secret[poly_index]):
                    fixed_polynomials[poly_index] = result.recovered[poly_index].copy()
                    first_success_by_poly[poly_index] = rows_per_poly
                    newly_frozen.append(poly_index)
        result_cache[rows_per_poly] = result
        record = {
            "constraints_per_poly": rows_per_poly,
            "total_constraints": len(samples),
            "exact_recovery": result.exact_recovery,
            "total_mismatches": result.total_mismatches,
            "mismatches_by_poly": result.mismatches_by_poly,
            "interval_violations": result.interval_violations,
            "elapsed_seconds": result.elapsed_seconds,
            "newly_frozen_polynomials": newly_frozen,
            "frozen_polynomials": sorted(fixed_polynomials),
            "first_success_by_poly": {
                str(poly): count for poly, count in sorted(first_success_by_poly.items())
            },
        }
        evaluations.append(record)
        print(
            f"probe: constraints_per_poly={rows_per_poly}, "
            f"exact={result.exact_recovery}, "
            f"mismatches={result.total_mismatches}/{params.dimension}, "
            f"mismatches_by_poly={result.mismatches_by_poly}, "
            f"violations={result.interval_violations}, "
            f"newly_frozen={newly_frozen}, "
            f"frozen={sorted(fixed_polynomials)}, "
            f"time={result.elapsed_seconds:.3f}s",
            flush=True,
        )
        return result

    lower = args.min_constraints_per_poly
    upper = args.max_constraints_per_poly
    status: str
    minimum: int | None
    final_result = None

    if args.scan_step:
        scan_counts = list(range(lower, upper + 1, args.scan_step))
        if scan_counts[-1] != upper:
            scan_counts.append(upper)
        successful_counts: list[int] = []
        for count in scan_counts:
            result = evaluate(count)
            if result.exact_recovery:
                successful_counts.append(count)
                if final_result is None:
                    final_result = result
        minimum = min(successful_counts, default=None)
        status = "scan_complete_with_success" if minimum is not None else "scan_complete_no_success"
        print(
            f"scan complete: evaluated={len(scan_counts)}, "
            f"successful_counts={successful_counts}",
            flush=True,
        )
    else:
        lower_result = evaluate(lower)
        if lower_result.exact_recovery:
            status = "lower_bound_succeeds"
            minimum = lower
            final_result = lower_result
            print(
                f"minimum inside requested range: {minimum} "
                "(the true minimum may be below the lower bound)"
            )
        else:
            upper_result = evaluate(upper)
            if not upper_result.exact_recovery:
                status = "upper_bound_fails"
                minimum = None
                print(
                    "no monotone failure/success bracket: the upper bound did not "
                    "recover exactly; increase the upper bound or fix BP stability."
                )
            else:
                minimum = binary_search_first_success(
                    lower,
                    upper,
                    lambda count: evaluate(count).exact_recovery,
                )
                final_result = evaluate(minimum)
                previous_result = evaluate(minimum - 1)
                status = "minimum_found"
                print(
                    f"minimum under monotone-success assumption: {minimum}; "
                    f"count={minimum - 1} exact={previous_result.exact_recovery}"
                )

    if not args.no_save:
        paths = _save_summary(
            args=args,
            params=params,
            threshold=threshold,
            collection=collection,
            evaluations=evaluations,
            status=status,
            minimum=minimum,
            secret=secret,
            recovered=None if final_result is None else final_result.recovered,
        )
        print(f"saved summary: {paths['summary']}")
        print(f"saved arrays: {paths['arrays']}")
    return 0 if minimum is not None else 2


if __name__ == "__main__":
    raise SystemExit(main())
