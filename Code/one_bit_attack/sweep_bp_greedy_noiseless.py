#!/usr/bin/env python3
"""Find 1000-granularity noiseless ML-DSA s1 recovery thresholds.

Four solver/constraint branches consume prefixes of the same random-number
leakage relation stream:

* ``bp-equality`` uses the external CLWE BP solver on probability-equality
  hints calibrated from an independent leakage stream.
* ``greedy-equality`` uses the external CLWE distribution-hint greedy solver
  on exactly the same probability-equality hints.
* ``bp-inequality`` uses the external CLWE BP solver with a uniform RHS over
  every integer satisfying the transformed interval constraint.
* ``greedy-inequality`` minimizes interval violation by this repository's
  hill-climbing greedy implementation.

The reported threshold is the first tested prefix for which every requested
key is recovered exactly.  Sample counts and the scan step are constrained to
multiples of 1000.
"""

from __future__ import annotations

import argparse
import csv
import json
import sys
from concurrent.futures import ThreadPoolExecutor
from datetime import datetime
from pathlib import Path
from time import perf_counter

import numpy as np

from hillclimb_mldsa_noise import (
    MLDSA_PARAMS,
    compute_beta_eff,
    generate_informative_relations,
    regression_warm_start,
)
from hillclimb_mldsa import hillclimb as inequality_hillclimb


CLWE_SOLVER_FILE = (
    Path(__file__).resolve().parent
    / "ILWE_all_solvers_hillclimb_ref_param.py"
)
if not CLWE_SOLVER_FILE.is_file():
    raise RuntimeError(f"required CLWE solver file not found: {CLWE_SOLVER_FILE}")
if str(CLWE_SOLVER_FILE.parent) not in sys.path:
    sys.path.insert(0, str(CLWE_SOLVER_FILE.parent))

from ILWE_all_solvers_hillclimb_ref_param import (  # noqa: E402
    HINT_SOLVER_IMPORT_ERROR,
    PyBP,
    PyGreedy,
    normalize_dist as clwe_normalize_dist,
    solve_bp as clwe_solve_bp,
    solve_greedy_dh as clwe_solve_greedy_dh,
)


SAMPLE_GRANULARITY = 1000
BRANCH_BP_EQUALITY = "bp-equality"
BRANCH_EQUALITY_GREEDY = "greedy-equality"
BRANCH_BP_INEQUALITY = "bp-inequality"
BRANCH_INEQUALITY_GREEDY = "greedy-inequality"
ALL_BRANCHES = (
    BRANCH_BP_EQUALITY,
    BRANCH_EQUALITY_GREEDY,
    BRANCH_BP_INEQUALITY,
    BRANCH_INEQUALITY_GREEDY,
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Find minimum tested sample counts for BP and greedy recovery of "
            "ML-DSA s1 under probability-equality and interval-inequality "
            "models (resolution: 1000 samples)."
        )
    )
    parser.add_argument("--params", type=int, choices=[44, 65, 87], default=44)
    parser.add_argument("--leakage", type=int, default=6)
    parser.add_argument("--num-keys", type=int, default=1)
    parser.add_argument("--seed", type=int, default=42)
    parser.add_argument("--min-samples", type=int, default=1000)
    parser.add_argument("--max-samples", type=int, default=30000)
    parser.add_argument(
        "--step",
        type=int,
        default=SAMPLE_GRANULARITY,
        help="Scan step; must be a positive multiple of 1000 (default: 1000)",
    )
    parser.add_argument(
        "--branches",
        nargs="+",
        choices=ALL_BRANCHES,
        default=list(ALL_BRANCHES),
    )
    parser.add_argument(
        "--collection-workers",
        type=int,
        default=1,
        help="Threads used to collect independent 1000-relation chunks",
    )

    bp = parser.add_argument_group("External CLWE BP solvers")
    bp.add_argument("--bp-iterations", type=int, default=20)
    bp.add_argument("--bp-threads", type=int, default=16)
    bp.add_argument(
        "--bp-uniform-prior",
        action="store_true",
        help="Use a uniform external-BP prior instead of its eta-bounded prior",
    )

    eq_greedy = parser.add_argument_group("External CLWE probability-equality greedy")
    eq_greedy.add_argument("--equality-greedy-iterations", type=int, default=100)
    eq_greedy.add_argument("--equality-greedy-threads", type=int, default=16)
    eq_greedy.add_argument(
        "--equality-greedy-kappa-mode",
        choices=["decay", "cycle", "small", "one"],
        default="decay",
    )
    eq_greedy.add_argument("--equality-greedy-fixed-kappa", type=int, default=None)

    hillclimb = parser.add_argument_group("Interval-inequality hill-climbing greedy")
    hillclimb.add_argument("--hillclimb-max-iter", type=int, default=100000)
    hillclimb.add_argument("--hillclimb-block-size", type=int, default=2)
    hillclimb.add_argument("--hillclimb-workers", type=int, default=1)
    hillclimb.add_argument(
        "--hillclimb-fitness",
        choices=["count", "excess", "combined"],
        default="excess",
    )
    hillclimb.add_argument("--hillclimb-adaptive-w-max", type=int, default=4)
    hillclimb.add_argument("--hillclimb-perturb-strength", type=int, default=30)
    hillclimb.add_argument("--hillclimb-perturb-patience", type=int, default=50)
    hillclimb.add_argument("--hillclimb-perturb-max", type=int, default=150)

    likelihood = parser.add_argument_group("Probability-equality calibration")
    likelihood.add_argument(
        "--likelihood-calibration-samples",
        type=int,
        default=20000,
        help="Independent leakage relations used to estimate P(C*s1-z_tilde)",
    )
    likelihood.add_argument(
        "--likelihood-smoothing",
        type=float,
        default=1.0,
        help="Additive histogram smoothing pseudocount (default: 1.0)",
    )

    parser.add_argument("--output-dir", default="noiseless_threshold_results")
    parser.add_argument("--non-verbose", action="store_true")

    args = parser.parse_args()
    _validate_args(parser, args)
    return args


def _validate_args(parser: argparse.ArgumentParser, args: argparse.Namespace) -> None:
    for name in ("min_samples", "max_samples", "step"):
        value = int(getattr(args, name))
        if value < SAMPLE_GRANULARITY or value % SAMPLE_GRANULARITY != 0:
            parser.error(f"--{name.replace('_', '-')} must be a positive multiple of 1000")
    if args.max_samples < args.min_samples:
        parser.error("--max-samples must be >= --min-samples")
    if args.num_keys <= 0:
        parser.error("--num-keys must be positive")
    if args.collection_workers <= 0 or args.hillclimb_workers <= 0:
        parser.error("worker counts must be positive")
    if args.bp_iterations <= 0 or args.bp_threads <= 0:
        parser.error("BP iterations and threads must be positive")
    if args.equality_greedy_iterations <= 0 or args.equality_greedy_threads <= 0:
        parser.error("equality-greedy iterations and threads must be positive")
    if (args.equality_greedy_fixed_kappa is not None
            and args.equality_greedy_fixed_kappa <= 0):
        parser.error("--equality-greedy-fixed-kappa must be positive")
    if args.hillclimb_max_iter <= 0 or args.hillclimb_block_size <= 0:
        parser.error("hill-climbing iteration count and block size must be positive")
    if (args.likelihood_calibration_samples < SAMPLE_GRANULARITY
            or args.likelihood_calibration_samples % SAMPLE_GRANULARITY != 0):
        parser.error(
            "--likelihood-calibration-samples must be a positive multiple of 1000"
        )
    if args.likelihood_smoothing <= 0.0:
        parser.error("--likelihood-smoothing must be positive")
    if ({BRANCH_BP_EQUALITY, BRANCH_BP_INEQUALITY} & set(args.branches)
            and PyBP is None):
        parser.error(f"external PyBP backend unavailable: {HINT_SOLVER_IMPORT_ERROR!r}")
    if BRANCH_EQUALITY_GREEDY in args.branches and PyGreedy is None:
        parser.error(f"external PyGreedy backend unavailable: {HINT_SOLVER_IMPORT_ERROR!r}")


def sample_counts(min_samples: int, max_samples: int, step: int) -> list[int]:
    """Return ascending tested prefixes, retaining the requested maximum."""
    counts = list(range(min_samples, max_samples + 1, step))
    if counts[-1] != max_samples:
        counts.append(max_samples)
    return counts


def _collect_relation_stream(
    rng: np.random.Generator,
    x_true: np.ndarray,
    max_samples: int,
    params: dict,
    leakage_index: int,
    workers: int,
) -> tuple[np.ndarray, np.ndarray, int]:
    """Collect a stable ordered stream in independent 1000-row chunks.

    Small chunks avoid the multi-gigabyte temporary random matrix that a
    single large Phase-1 call would allocate.  Chunk order is deterministic
    for a fixed seed and is independent of thread scheduling.
    """
    chunk_sizes = [SAMPLE_GRANULARITY] * (max_samples // SAMPLE_GRANULARITY)
    remainder = int(max_samples) % SAMPLE_GRANULARITY
    if remainder:
        chunk_sizes.append(remainder)
    child_rngs = rng.spawn(len(chunk_sizes))

    def collect_one(item: tuple[np.random.Generator, int]):
        child_rng, chunk_size = item
        return generate_informative_relations(
            child_rng,
            x_true,
            chunk_size,
            params,
            leakage_index,
            0.0,
        )

    work = list(zip(child_rngs, chunk_sizes))
    if workers == 1:
        chunks = [collect_one(item) for item in work]
    else:
        with ThreadPoolExecutor(max_workers=workers) as executor:
            chunks = list(executor.map(collect_one, work))

    z_tilde = np.concatenate([chunk[0] for chunk in chunks])
    C = np.vstack([chunk[1] for chunk in chunks])
    total_signatures = sum(int(chunk[2]) for chunk in chunks)
    return z_tilde, C, total_signatures


def _calibrate_error_distribution(
    params: dict,
    leakage_index: int,
    seed: int,
    samples: int,
    workers: int,
    smoothing: float,
) -> tuple[np.ndarray, int, dict]:
    """Estimate P(C*s1-z_tilde) on the valid centered-error support."""
    rng = np.random.default_rng(seed)
    x_profile = rng.integers(
        -params["eta"], params["eta"] + 1,
        size=params["n"], dtype=np.int8,
    )
    started = perf_counter()
    z_profile, C_profile, total_signatures = _collect_relation_stream(
        rng, x_profile, samples, params, leakage_index, workers
    )
    residual = _centered_residuals(
        C_profile, x_profile, z_profile, params, leakage_index
    )
    beta_eff = int(compute_beta_eff(params, leakage_index))
    outside = np.abs(residual) > beta_eff
    if np.any(outside):
        bad = residual[outside]
        raise RuntimeError(
            "profiling stream violated the deterministic leakage bound: "
            f"min={int(np.min(bad))}, max={int(np.max(bad))}, "
            f"beta_eff={beta_eff}"
        )

    offset = beta_eff
    counts = np.bincount(
        residual + offset, minlength=2 * beta_eff + 1
    ).astype(np.float64)

    smoothed = counts + float(smoothing)
    probabilities = smoothed / np.sum(smoothed)
    metadata = {
        "seed": seed,
        "relations": int(samples),
        "accepted_signatures_consumed": int(total_signatures),
        "smoothing": float(smoothing),
        "support": f"centered residuals [{-beta_eff}, {beta_eff}]",
        "offset": int(offset),
        "observed_residual_min": int(np.min(residual)),
        "observed_residual_max": int(np.max(residual)),
        "nonzero_bins": int(np.count_nonzero(counts)),
        "time_s": perf_counter() - started,
        "counts": counts.astype(np.int64).tolist(),
        "probabilities": probabilities.tolist(),
    }
    return probabilities, offset, metadata


def _centered_residuals(
    C: np.ndarray,
    x: np.ndarray,
    z_tilde: np.ndarray,
    params: dict,
    leakage_index: int,
) -> np.ndarray:
    """Return signed residuals using the transformed relation's semantics."""
    beta = params["eta"] * params["tau"]
    beta_eff = compute_beta_eff(params, leakage_index)
    residual = (
        C.astype(np.int32, copy=False) @ np.asarray(x, dtype=np.int32)
        - np.rint(z_tilde).astype(np.int64)
    )
    if beta_eff < beta:
        modulus = 2 ** (leakage_index + 1)
        residual %= modulus
        residual = np.where(residual > modulus // 2, residual - modulus, residual)
    return residual.astype(np.int64, copy=False)


def _constraint_violations(
    C: np.ndarray,
    x: np.ndarray,
    z_tilde: np.ndarray,
    params: dict,
    leakage_index: int,
    *,
    modular_lower_open: bool = False,
) -> int:
    beta_eff = compute_beta_eff(params, leakage_index)
    residual = _centered_residuals(C, x, z_tilde, params, leakage_index)
    beta = params["eta"] * params["tau"]
    if beta_eff < beta and modular_lower_open:
        # In the low-leakage modular regime the j-independence transform has
        # 2^j possible residuals, not 2^j+1.  Its integer support is
        # (-beta_eff, beta_eff], e.g. [-31, 32] for j=6.  The negative
        # endpoint -beta_eff is therefore a violation.
        feasible = (residual > -beta_eff) & (residual <= beta_eff)
    else:
        feasible = np.abs(residual) <= beta_eff
    return int(np.count_nonzero(~feasible))


def _build_distribution_hints(
    C: np.ndarray,
    z_tilde: np.ndarray,
    params: dict,
    leakage_index: int,
    *,
    constraint_model: str,
    residual_probabilities: np.ndarray | None = None,
    residual_offset: int = 0,
):
    """Build probability-equality or hard-interval RHS distributions.

    For ``equality``, the factor weight at an exact RHS r is the independently
    calibrated probability of the centered residual r-z_tilde.  For
    ``inequality``, every RHS satisfying the bounded (possibly modular)
    interval receives equal weight.  Uniform interval weights are exactly a
    hard interval indicator for sum-product BP after message normalization.
    """
    if constraint_model not in {"equality", "inequality"}:
        raise ValueError(f"unknown constraint model: {constraint_model}")
    if constraint_model == "equality" and residual_probabilities is None:
        raise ValueError("probability-equality hints require calibration")

    eta = int(params["eta"])
    beta = int(params["eta"] * params["tau"])
    beta_eff = int(compute_beta_eff(params, leakage_index))
    modulus = 2 ** (leakage_index + 1) if beta_eff < beta else None
    z_int = np.rint(z_tilde).astype(np.int64)
    hints = []
    rhs_cache: dict[tuple[int, int], list[tuple[int, float]]] = {}

    for row, target in zip(C, z_int):
        coeffs = np.asarray(row, dtype=np.int64).tolist()
        inner_bound = eta * int(np.sum(np.abs(row), dtype=np.int64))
        cache_key = (int(target), inner_bound)
        rhs_dist = rhs_cache.get(cache_key)
        if rhs_dist is None:
            rhs_values = np.arange(
                -inner_bound, inner_bound + 1, dtype=np.int64
            )
            residual = rhs_values - int(target)
            if modulus is not None:
                residual %= modulus
                residual = np.where(
                    residual > modulus // 2, residual - modulus, residual
                )
            if constraint_model == "inequality" and modulus is not None:
                # Remove the impossible negative endpoint.  For j=6 this is
                # e=-32, leaving the exact 64-value support [-31, 32].
                feasible = (residual > -beta_eff) & (residual <= beta_eff)
            else:
                feasible = np.abs(residual) <= beta_eff
            rhs_values = rhs_values[feasible]
            feasible_residual = residual[feasible]
            if rhs_values.size == 0:
                raise ValueError(
                    f"relation has no feasible RHS: target={target}, "
                    f"bound={inner_bound}, beta_eff={beta_eff}"
                )

            if constraint_model == "inequality":
                weights = np.ones(rhs_values.size, dtype=np.float64)
            else:
                table = np.asarray(residual_probabilities, dtype=np.float64)
                indices = feasible_residual + int(residual_offset)
                if np.any(indices < 0) or np.any(indices >= len(table)):
                    raise ValueError(
                        "calibrated residual table does not cover all feasible "
                        f"residuals for target={target}"
                    )
                weights = table[indices]

            rhs_dist = clwe_normalize_dist(
                zip(rhs_values.tolist(), weights.tolist())
            )
            rhs_cache[cache_key] = rhs_dist
        hints.append((coeffs, rhs_dist))
    return hints


def _build_equality_hints(
    C: np.ndarray,
    z_tilde: np.ndarray,
    params: dict,
    leakage_index: int,
    residual_probabilities: np.ndarray,
    residual_offset: int,
):
    return _build_distribution_hints(
        C,
        z_tilde,
        params,
        leakage_index,
        constraint_model="equality",
        residual_probabilities=residual_probabilities,
        residual_offset=residual_offset,
    )


def _build_inequality_hints(
    C: np.ndarray,
    z_tilde: np.ndarray,
    params: dict,
    leakage_index: int,
):
    return _build_distribution_hints(
        C,
        z_tilde,
        params,
        leakage_index,
        constraint_model="inequality",
    )


def _solve_bp_equality(
    C: np.ndarray,
    z_tilde: np.ndarray,
    params: dict,
    args: argparse.Namespace,
    residual_probabilities: np.ndarray,
    residual_offset: int,
) -> tuple[np.ndarray, int, int]:
    hints = _build_equality_hints(
        C,
        z_tilde,
        params,
        args.leakage,
        residual_probabilities,
        residual_offset,
    )
    recovered = clwe_solve_bp(
        hints,
        params["eta"],
        max_iter=args.bp_iterations,
        threads=args.bp_threads,
        use_sparse_prior=not args.bp_uniform_prior,
    )
    recovered = np.asarray(recovered, dtype=np.int8)
    violations = _constraint_violations(C, recovered, z_tilde, params, args.leakage)
    return recovered, violations, args.bp_iterations


def _solve_bp_inequality(
    C: np.ndarray,
    z_tilde: np.ndarray,
    params: dict,
    args: argparse.Namespace,
) -> tuple[np.ndarray, int, int]:
    hints = _build_inequality_hints(C, z_tilde, params, args.leakage)
    recovered = clwe_solve_bp(
        hints,
        params["eta"],
        max_iter=args.bp_iterations,
        threads=args.bp_threads,
        use_sparse_prior=not args.bp_uniform_prior,
    )
    recovered = np.asarray(recovered, dtype=np.int8)
    violations = _constraint_violations(
        C,
        recovered,
        z_tilde,
        params,
        args.leakage,
        modular_lower_open=True,
    )
    return recovered, violations, args.bp_iterations


def _solve_greedy_equality(
    C: np.ndarray,
    z_tilde: np.ndarray,
    params: dict,
    args: argparse.Namespace,
    residual_probabilities: np.ndarray,
    residual_offset: int,
) -> tuple[np.ndarray, int, int]:
    hints = _build_equality_hints(
        C,
        z_tilde,
        params,
        args.leakage,
        residual_probabilities,
        residual_offset,
    )
    recovered = clwe_solve_greedy_dh(
        hints,
        params["eta"],
        max_iter=args.equality_greedy_iterations,
        threads=args.equality_greedy_threads,
        kappa_mode=args.equality_greedy_kappa_mode,
        fixed_kappa=args.equality_greedy_fixed_kappa,
    )
    recovered = np.asarray(recovered, dtype=np.int8)
    violations = _constraint_violations(C, recovered, z_tilde, params, args.leakage)
    return recovered, violations, args.equality_greedy_iterations


def _solve_greedy_inequality(
    C: np.ndarray,
    z_tilde: np.ndarray,
    x_init: np.ndarray,
    x_true: np.ndarray,
    params: dict,
    args: argparse.Namespace,
    solver_seed: int,
) -> tuple[np.ndarray, int, int]:
    beta = params["eta"] * params["tau"]
    beta_eff = compute_beta_eff(params, args.leakage)
    modulus = 2 ** (args.leakage + 1) if beta_eff < beta else None
    recovered, violations, iterations, _, _ = inequality_hillclimb(
        C.astype(np.int32, copy=False),
        z_tilde,
        x_init,
        params,
        np.random.default_rng(solver_seed),
        w=args.hillclimb_block_size,
        T=args.hillclimb_max_iter,
        leakage_index=args.leakage,
        true_key=x_true,
        verbose=not args.non_verbose,
        print_keys=False,
        num_workers=args.hillclimb_workers,
        fitness_mode=args.hillclimb_fitness,
        fitness_lambda=float(beta_eff),
        modulus=modulus,
        modular_residual_lower_open=modulus is not None,
        likelihood_nll=None,
        likelihood_offset=0,
        score_weights=None,
        use_adaptive_w=True,
        adaptive_w_max=args.hillclimb_adaptive_w_max,
        adaptive_w_patience=50,
        use_lateral_moves=True,
        use_diversify=True,
        diversify_strength=1.0,
        sweep_interval=0,
        use_perturb_restart=True,
        perturb_strength=args.hillclimb_perturb_strength,
        perturb_patience=args.hillclimb_perturb_patience,
        perturb_max=args.hillclimb_perturb_max,
        perturb_score_guided=False,
        use_w1_sweep=True,
        w1_batch_size=16,
    )
    return recovered, int(violations), int(iterations)


def _write_results(
    args: argparse.Namespace,
    params: dict,
    beta_eff: int,
    collections: list[dict],
    thresholds: dict[str, int | None],
    rows: list[dict],
    secrets: np.ndarray,
    threshold_recovered: dict[str, np.ndarray],
    residual_calibration: dict | None,
) -> tuple[Path, Path, Path, dict[str, str]]:
    output_dir = Path(args.output_dir)
    if not output_dir.is_absolute():
        output_dir = Path(__file__).resolve().parent / output_dir
    output_dir.mkdir(parents=True, exist_ok=True)

    stamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    prefix = output_dir / f"{params['name']}_j{args.leakage}_noiseless_{stamp}"
    csv_path = prefix.with_suffix(".csv")
    json_path = prefix.with_suffix(".json")
    secret_path = Path(f"{prefix}_secrets.npy")

    with csv_path.open("w", newline="", encoding="utf-8") as file:
        writer = csv.DictWriter(file, fieldnames=list(rows[0].keys()))
        writer.writeheader()
        writer.writerows(rows)

    np.save(secret_path, secrets)
    recovered_paths: dict[str, str] = {}
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
            "inequality_residual_support": (
                f"({-beta_eff}, {beta_eff}] in the modular low-leakage regime"
            ),
        },
        "arguments": vars(args),
        "sample_granularity": SAMPLE_GRANULARITY,
        "threshold_definition": (
            "first ascending tested prefix at which every requested key is "
            "recovered exactly"
        ),
        "constraint_branches": {
            BRANCH_BP_EQUALITY: (
                "independently calibrated probability-equality hints solved "
                "by CLWE solve_bp from "
                f"{CLWE_SOLVER_FILE}"
            ),
            BRANCH_EQUALITY_GREEDY: (
                "the same probability-equality hints solved by CLWE "
                f"solve_greedy_dh from {CLWE_SOLVER_FILE}"
            ),
            BRANCH_BP_INEQUALITY: (
                "uniform RHS over every integer satisfying centered_mod(" 
                "C_i*x-z_i) in (-beta_eff,beta_eff], solved by CLWE solve_bp"
            ),
            BRANCH_INEQUALITY_GREEDY: (
                "centered_mod(C_i*x - z_i, 2^(j+1)) in "
                "(-beta_eff, beta_eff], solved by hill-climbing greedy"
            ),
        },
        "minimum_tested_samples": thresholds,
        "residual_calibration": residual_calibration,
        "collections": collections,
        "secret_path": str(secret_path.resolve()),
        "recovered_paths": recovered_paths,
        "results": rows,
    }
    with json_path.open("w", encoding="utf-8") as file:
        json.dump(payload, file, ensure_ascii=False, indent=2)

    return csv_path, json_path, secret_path, recovered_paths


def run_sweep(args: argparse.Namespace) -> dict[str, int | None]:
    params = MLDSA_PARAMS[args.params]
    n = params["n"]
    eta = params["eta"]
    beta_eff = compute_beta_eff(params, args.leakage)
    counts = sample_counts(args.min_samples, args.max_samples, args.step)

    residual_probabilities = None
    residual_offset = 0
    residual_calibration = None
    if ({BRANCH_BP_EQUALITY, BRANCH_EQUALITY_GREEDY} & set(args.branches)):
        calibration_seed = args.seed + 9_000_001
        residual_probabilities, residual_offset, residual_calibration = (
            _calibrate_error_distribution(
                params,
                args.leakage,
                calibration_seed,
                args.likelihood_calibration_samples,
                args.collection_workers,
                args.likelihood_smoothing,
            )
        )
        print(
            "  calibrated probability-equality model: "
            f"relations={args.likelihood_calibration_samples}, "
            f"support={residual_calibration['support']}, "
            f"nonzero_bins={residual_calibration['nonzero_bins']}, "
            f"time={residual_calibration['time_s']:.2f}s"
        )

    master_rng = np.random.default_rng(args.seed)
    key_rngs = master_rng.spawn(args.num_keys)
    datasets: list[dict] = []
    collections: list[dict] = []

    print(
        f"=== Noiseless threshold sweep: {params['name']}, j={args.leakage}, "
        f"beta_eff={beta_eff}, keys={args.num_keys} ==="
    )
    print(
        f"  sample counts: {counts[0]}..{counts[-1]}, step={args.step}; "
        f"branches={args.branches}"
    )
    for key_idx, key_rng in enumerate(key_rngs):
        x_true = key_rng.integers(-eta, eta + 1, size=n, dtype=np.int8)
        started = perf_counter()
        z_tilde, C, total_signatures = _collect_relation_stream(
            key_rng,
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
                "accepted_signatures_consumed": total_signatures,
                "time_s": elapsed,
            }
        )
        print(
            f"  collected key {key_idx + 1}/{args.num_keys}: "
            f"relations={len(z_tilde)}, signatures={total_signatures}, "
            f"time={elapsed:.2f}s"
        )

    active = set(args.branches)
    thresholds: dict[str, int | None] = {branch: None for branch in args.branches}
    threshold_recovered: dict[str, np.ndarray] = {}
    rows: list[dict] = []
    print(
        "samples,branch,key_idx,success,mismatches,violations,"
        "init_correct,iterations,time_s"
    )

    for count in counts:
        warm_starts = []
        for dataset in datasets:
            C_prefix = dataset["C"][:count]
            z_prefix = dataset["z_tilde"][:count]
            _, x_init = regression_warm_start(
                C_prefix, z_prefix, n, eta, 0.0
            )
            warm_starts.append(x_init)

        for branch in args.branches:
            if branch not in active:
                continue

            branch_success = True
            recovered_for_count = []
            for key_idx, dataset in enumerate(datasets):
                C_prefix = dataset["C"][:count]
                z_prefix = dataset["z_tilde"][:count]
                x_true = dataset["x_true"]
                x_init = warm_starts[key_idx]
                init_correct = int(np.count_nonzero(x_init == x_true))
                solver_seed = args.seed + 1_000_003 * (key_idx + 1) + count

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
                elif branch == BRANCH_EQUALITY_GREEDY:
                    recovered, violations, iterations = _solve_greedy_equality(
                        C_prefix,
                        z_prefix,
                        params,
                        args,
                        residual_probabilities,
                        residual_offset,
                    )
                elif branch == BRANCH_BP_INEQUALITY:
                    recovered, violations, iterations = _solve_bp_inequality(
                        C_prefix,
                        z_prefix,
                        params,
                        args,
                    )
                else:
                    recovered, violations, iterations = _solve_greedy_inequality(
                        C_prefix,
                        z_prefix,
                        x_init,
                        x_true,
                        params,
                        args,
                        solver_seed,
                    )
                elapsed = perf_counter() - started
                mismatches = int(np.count_nonzero(recovered != x_true))
                success = mismatches == 0
                branch_success = branch_success and success
                recovered_for_count.append(recovered)
                row = {
                    "samples": count,
                    "branch": branch,
                    "key_idx": key_idx,
                    "success": success,
                    "mismatches": mismatches,
                    "violations": int(violations),
                    "init_correct": init_correct,
                    "init_accuracy": init_correct / n,
                    "iterations": int(iterations),
                    "time_s": elapsed,
                }
                rows.append(row)
                print(
                    f"{count},{branch},{key_idx},{success},{mismatches},"
                    f"{violations},{init_correct},{iterations},{elapsed:.3f}",
                    flush=True,
                )

            if branch_success:
                thresholds[branch] = count
                threshold_recovered[branch] = np.stack(recovered_for_count)
                active.remove(branch)
                print(f"  threshold found: {branch} -> {count}", flush=True)

        if not active:
            break

    secrets = np.stack([dataset["x_true"] for dataset in datasets])
    csv_path, json_path, secret_path, recovered_paths = _write_results(
        args,
        params,
        beta_eff,
        collections,
        thresholds,
        rows,
        secrets,
        threshold_recovered,
        residual_calibration,
    )
    print(f"minimum_tested_samples={thresholds}")
    print(f"saved_csv={csv_path.resolve()}")
    print(f"saved_json={json_path.resolve()}")
    print(f"saved_secrets={secret_path.resolve()}")
    print(f"saved_recovered={recovered_paths}")
    return thresholds


def main() -> None:
    args = parse_args()
    thresholds = run_sweep(args)
    raise SystemExit(0 if all(value is not None for value in thresholds.values()) else 2)


if __name__ == "__main__":
    main()
