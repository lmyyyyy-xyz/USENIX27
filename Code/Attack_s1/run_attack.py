#!/usr/bin/env python3
"""End-to-end skipped-z constraint attack on simulated Dilithium s1."""

from __future__ import annotations

import argparse
import csv
import json
from datetime import datetime
from pathlib import Path

import numpy as np

from bp_attack import (
    CLWE_SOLVER_FILE,
    collect_constraints,
    resolve_threshold,
    solve_secret_bp,
)
from mldsa_model import get_params, sample_secret


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Generate simulated skipped-z Dilithium observations, construct s1 "
            "constraints, and recover s1 with CLWE_Solve belief propagation."
        )
    )
    parser.add_argument("--level", default="toy", choices=["2", "3", "5", "toy"])
    parser.add_argument("--signatures", type=int, default=50_000)
    parser.add_argument(
        "--constraint-mode",
        default="inequality",
        choices=[
            "inequality",
            "slack-equality",
            "boundary-equality",
            "boundary-equality-marginalized",
            "unknown-y-error-interval",
        ],
        help=(
            "inequality uses bounded-y intervals; slack-equality records their "
            "bounded-slack equality conversion; boundary-equality is a known-y "
            "oracle; the marginalized and error-interval modes use unknown y"
        ),
    )
    parser.add_argument(
        "--threshold",
        default="gamma1-beta",
        help=(
            "inequality/slack-equality z threshold: gamma1-beta, gamma1, or a "
            "positive integer; the other boundary modes always use gamma1"
        ),
    )
    parser.add_argument(
        "--max-constraints-per-poly",
        type=int,
        default=2_000,
        help="stop once every s1 polynomial has this many rows; 0 disables the cap",
    )
    parser.add_argument("--seed", type=int, default=1)
    parser.add_argument("--bp-iterations", type=int, default=100)
    parser.add_argument(
        "--bp-damping",
        type=float,
        default=0.7,
        help="old-message weight in [0,1); 0 disables BP message damping",
    )
    parser.add_argument("--threads", type=int, default=16)
    parser.add_argument(
        "--uniform-prior",
        action="store_true",
        help="do not restrict the BP prior to coefficients in [-eta, eta]",
    )
    parser.add_argument("--one-per-signature", action="store_true")
    parser.add_argument("--output-dir", default="outputs")
    parser.add_argument("--no-save", action="store_true")
    args = parser.parse_args()

    if args.signatures <= 0:
        parser.error("--signatures must be positive")
    if args.max_constraints_per_poly < 0:
        parser.error("--max-constraints-per-poly must be nonnegative")
    if args.bp_iterations <= 0 or args.threads <= 0:
        parser.error("--bp-iterations and --threads must be positive")
    if not 0.0 <= args.bp_damping < 1.0:
        parser.error("--bp-damping must satisfy 0 <= value < 1")
    return args


def save_results(
    output_dir: Path,
    params,
    args: argparse.Namespace,
    threshold: int,
    collection,
    secret: np.ndarray,
    result,
) -> dict[str, str]:
    output_dir.mkdir(parents=True, exist_ok=True)
    stamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    mode_tag = args.constraint_mode.replace("-", "_")
    prefix = output_dir / f"{params.name}_s1_{mode_tag}_bp_{len(collection.samples)}rows_{stamp}"
    secret_path = Path(f"{prefix}_secret.npy")
    recovered_path = Path(f"{prefix}_recovered.npy")
    coefficients_path = Path(f"{prefix}_coefficients.csv")
    summary_path = Path(f"{prefix}_summary.json")

    np.save(secret_path, secret)
    np.save(recovered_path, result.recovered)
    with coefficients_path.open("w", newline="", encoding="utf-8") as file:
        writer = csv.writer(file)
        writer.writerow(["poly_index", "coeff_index", "true_s1", "recovered_s1", "match"])
        for poly_index in range(params.ell):
            for coeff_index in range(params.n):
                true_value = int(secret[poly_index, coeff_index])
                recovered_value = int(result.recovered[poly_index, coeff_index])
                writer.writerow(
                    [poly_index, coeff_index, true_value, recovered_value, true_value == recovered_value]
                )

    payload = {
        "parameters": params.__dict__,
        "arguments": vars(args),
        "resolved_threshold": threshold,
        "y_interval": [params.y_low, params.y_high],
        "uses_true_y": args.constraint_mode == "boundary-equality",
        "conversion": {
            "slack-equality": "x + slack_sign*r = conversion_rhs",
            "unknown-y-error-interval": "x = nominal_rhs + e",
        }.get(args.constraint_mode),
        "bp_solver_file": str(CLWE_SOLVER_FILE.resolve()),
        "collection": {
            "signatures_generated": collection.signatures_generated,
            "useful_signatures": collection.useful_signatures,
            "total_rows": len(collection.samples),
            "rows_by_poly": collection.rows_by_poly,
            "positive_rows": collection.positive_rows,
            "negative_rows": collection.negative_rows,
        },
        "solve": {
            "elapsed_seconds": result.elapsed_seconds,
            "rows_by_poly": result.rows_by_poly,
            "mismatches_by_poly": result.mismatches_by_poly,
            "total_mismatches": result.total_mismatches,
            "interval_violations": result.interval_violations,
            "exact_recovery": result.exact_recovery,
        },
        "files": {
            "secret": str(secret_path.resolve()),
            "recovered": str(recovered_path.resolve()),
            "coefficients": str(coefficients_path.resolve()),
        },
    }
    with summary_path.open("w", encoding="utf-8") as file:
        json.dump(payload, file, indent=2, ensure_ascii=False)
    return {
        "summary": str(summary_path.resolve()),
        "secret": str(secret_path.resolve()),
        "recovered": str(recovered_path.resolve()),
        "coefficients": str(coefficients_path.resolve()),
    }


def main() -> int:
    args = parse_args()
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
    max_rows = args.max_constraints_per_poly or None
    rng = np.random.default_rng(args.seed)
    secret = sample_secret(params, rng)

    print(
        f"parameters: {params.name}, n={params.n}, ell={params.ell}, eta={params.eta}, "
        f"tau={params.tau}, gamma1={params.gamma1}, beta={params.beta}"
    )
    print(
        f"simulation: seed={args.seed}, y=[{params.y_low},{params.y_high}], "
        f"constraint-mode={args.constraint_mode}, z-threshold={threshold}, "
        f"norm-check=SKIPPED"
    )
    collection = collect_constraints(
        params=params,
        secret=secret,
        rng=rng,
        signatures=args.signatures,
        constraint_mode=args.constraint_mode,
        threshold=threshold,
        max_constraints_per_poly=max_rows,
        one_per_signature=args.one_per_signature,
    )
    print(
        f"collection: signatures={collection.signatures_generated}, "
        f"useful={collection.useful_signatures}, rows={len(collection.samples)}, "
        f"rows_by_poly={collection.rows_by_poly}, positive={collection.positive_rows}, "
        f"negative={collection.negative_rows}"
    )

    result = solve_secret_bp(
        params=params,
        samples=collection.samples,
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
        output_dir = Path(args.output_dir)
        if not output_dir.is_absolute():
            output_dir = Path(__file__).resolve().parent / output_dir
        paths = save_results(output_dir, params, args, threshold, collection, secret, result)
        print(f"saved summary: {paths['summary']}")
        print(f"saved coefficient comparison: {paths['coefficients']}")
    return 0 if result.exact_recovery else 2


if __name__ == "__main__":
    raise SystemExit(main())
