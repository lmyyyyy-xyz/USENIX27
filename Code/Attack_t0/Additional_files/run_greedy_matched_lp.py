#!/usr/bin/env python3
"""Run the C-halving t0 attack with greedy search under the LP sample policy.

The comparison intentionally keeps the LP experiment's data and constraint
policy fixed.  Each round reads the same signature pool from the start and
stops only after every t0 polynomial has at least ``--nb-ineq`` selected
inequalities.  Modes 2/3/5 correspond to ML-DSA-44/65/87 and use K=4/6/8
polynomials, respectively.
"""

from __future__ import annotations

import argparse
import csv
import os
import re
import shutil
import subprocess
import time
from datetime import datetime
from pathlib import Path

import numpy as np

from mldsa_t0_params import T0Parameters, load_true_t0, resolve_t0_parameters


def parse_args(argv: list[str] | None = None) -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="C-halving greedy t0 recovery matched to the original LP samples",
        epilog=(
            "Levels 2/3/5 are aliases for ML-DSA-44/65/87. "
            "Build the matching executable with: make "
            "build_solve_t0_greedy<mode>_matched"
        ),
    )
    parser.add_argument(
        "--level",
        default="2",
        help="2/3/5 or ML-DSA-44/65/87 (default: 2)",
    )
    parser.add_argument("--key", type=int, default=0)
    parser.add_argument(
        "--nb-ineq",
        type=int,
        default=50000,
        help="Minimum selected inequalities per t0 polynomial in every round",
    )
    parser.add_argument("--max-passes", type=int, default=80)
    parser.add_argument(
        "--signature-file",
        type=Path,
        default=None,
        help=(
            "Compressed signature pool. Default: the selected level's "
            "*_compressed_300000.rsp, falling back to *_compressed.rsp"
        ),
    )
    parser.add_argument(
        "--kat-file",
        type=Path,
        default=None,
        help="KAT response file used only to evaluate recovery against true t0",
    )
    parser.add_argument(
        "--executable",
        type=Path,
        default=None,
        help="Override the level-specific greedy executable",
    )
    parser.add_argument(
        "--tag",
        default=None,
        help="Unique output suffix (default: matched_lp_<timestamp>)",
    )
    return parser.parse_args(argv)


def compute_error(guess: np.ndarray, true_t0: np.ndarray) -> tuple[int, int]:
    rounded = np.rint(guess).astype(np.int32)
    diff = true_t0 - rounded
    return int(np.max(np.abs(diff))), int(np.count_nonzero(diff))


def parse_builder_output(text: str, poly_count: int) -> dict[str, object] | None:
    match = re.search(
        r"Building\s+\d+\s+LPs:\s*([0-9.]+)\s*sec/(\d+)\s*signs/"
        r"(.*?)\s*0 ineq/\s*(.*?)\s*1 ineq",
        text,
        re.S,
    )
    if not match:
        return None
    ineq0 = [int(value) for value in re.findall(r"\d+", match.group(3))]
    ineq1 = [int(value) for value in re.findall(r"\d+", match.group(4))]
    if len(ineq0) < poly_count or len(ineq1) < poly_count:
        return None
    return {
        "build_sec": float(match.group(1)),
        "signs": int(match.group(2)),
        "ineq0": ineq0[:poly_count],
        "ineq1": ineq1[:poly_count],
    }


def _executable_candidates(path: Path) -> list[Path]:
    if path.suffix.lower() == ".exe":
        return [path, path.with_suffix("")]
    return [path.with_suffix(".exe"), path]


def resolve_executable(
    c_dir: Path, params: T0Parameters, override: Path | None
) -> Path:
    requested = override or (
        c_dir / f"build_solve_t0_greedy{params.mode}_matched"
    )
    for candidate in _executable_candidates(requested):
        if candidate.is_file():
            return candidate
    return _executable_candidates(requested)[0]


def resolve_signature_file(
    base: Path,
    params: T0Parameters,
    key_index: int,
    override: Path | None,
) -> Path:
    if override is not None:
        return override
    directory = (
        base
        / "Additional_files"
        / "Signs"
        / params.dilithium_name
        / f"key{key_index}"
    )
    stem = f"PQCsignKAT_{params.dilithium_name}_compressed"
    preferred = directory / f"{stem}_300000.rsp"
    fallback = directory / f"{stem}.rsp"
    return preferred if preferred.is_file() or not fallback.is_file() else fallback


def parse_greedy_stats(output: str, poly_count: int) -> tuple[list[int], list[float]]:
    violated = [0] * poly_count
    objective = [0.0] * poly_count
    for poly_s, violated_s, objective_s in re.findall(
        r"Refine\s+GR#(\d+).*?violated\s+(\d+),\s+obj\s+([0-9.eE+-]+)",
        output,
    ):
        poly = int(poly_s)
        if 0 <= poly < poly_count:
            violated[poly] = int(violated_s)
            objective[poly] = float(objective_s)
    return violated, objective


def main() -> None:
    args = parse_args()
    params = resolve_t0_parameters(args.level)
    if args.key < 0:
        raise ValueError("--key must be nonnegative")
    if args.nb_ineq <= 0:
        raise ValueError("--nb-ineq must be positive")
    if args.max_passes <= 0:
        raise ValueError("--max-passes must be positive")

    base = Path(__file__).resolve().parents[1]
    c_dir = base / "Additional_files" / "C_functions"
    exe = resolve_executable(c_dir, params, args.executable)
    guess_dir = (
        base
        / "Additional_files"
        / "Guess"
        / params.dilithium_name
        / f"key{args.key}"
    )
    guess_file = guess_dir / "t0_guess_file.bin"
    signature_file = resolve_signature_file(
        base, params, args.key, args.signature_file
    )

    if not exe.is_file():
        raise FileNotFoundError(
            f"Greedy executable not found: {exe}. Build it in {c_dir} with "
            f"make build_solve_t0_greedy{params.mode}_matched"
        )
    if not signature_file.is_file():
        raise FileNotFoundError(
            f"Signature file not found: {signature_file}. Generate a pool with "
            f"sign_rdm_msg_and_save{params.mode} or pass --signature-file."
        )

    true_t0, d_value = load_true_t0(base, args.key, params, args.kat_file)
    poly_count, poly_degree = true_t0.shape
    if (poly_count, poly_degree) != (params.k, params.n):
        raise RuntimeError(
            f"Unexpected true t0 shape {true_t0.shape}; "
            f"expected {(params.k, params.n)} for {params.mldsa_name}"
        )
    expected_guess_bytes = poly_count * poly_degree * np.dtype(np.float64).itemsize

    tag = args.tag or datetime.now().strftime("matched_lp_%Y%m%d_%H%M%S")
    prefix = guess_dir / f"greedy_c_halving_n{args.nb_ineq}_{tag}"
    csv_file = prefix.with_suffix(".csv")
    log_file = prefix.with_suffix(".log")
    final_guess_file = prefix.with_suffix(".bin")
    before_guess_file = guess_dir / f"t0_guess_file.before_{tag}.bin"

    for path in (csv_file, log_file, final_guess_file, before_guess_file):
        if path.exists():
            raise FileExistsError(f"Refusing to overwrite existing output: {path}")

    guess_dir.mkdir(parents=True, exist_ok=True)
    had_guess = guess_file.exists()
    if had_guess:
        if guess_file.stat().st_size != expected_guess_bytes:
            raise RuntimeError(
                f"Unexpected guess size {guess_file.stat().st_size}; "
                f"expected {expected_guess_bytes} bytes"
            )
        shutil.copy2(guess_file, before_guess_file)

    fields = [
        "parameter_set",
        "C",
        "signature_pool",
        "target_ineq_per_poly",
        "signatures_read",
        "ineq_total_per_poly",
        "build_sec",
        "solve_wall_sec",
        "violated_per_poly",
        "objective_per_poly",
        "max_abs_error",
        "mismatched_coefficients",
    ]
    rows: list[dict[str, object]] = []
    c_values = [1 << (d_value - 1 - i) for i in range(d_value)]

    env = os.environ.copy()
    env["T0_SIG_FILE"] = str(signature_file.resolve())
    env.pop("T0_SIG_LIMIT", None)
    env["GREEDY_CONSISTENCY_CHECK"] = "1"
    # Strict LP comparison: do not use the enhanced greedy-only 2C window or
    # the low-C filter relaxation.  These values make both identical to LP.
    env["T0_WINDOW_ALPHA"] = "1"
    env["T0_LOW_C_RELAX_FACTOR"] = "1"

    run_succeeded = False
    try:
        np.zeros_like(true_t0, dtype=np.float64).tofile(guess_file)

        with log_file.open("w", encoding="utf-8") as log:
            log.write(f"started={datetime.now().isoformat()}\n")
            log.write(f"parameter_set={params.mldsa_name}\n")
            log.write(f"reference_name={params.dilithium_name}\n")
            log.write(f"mode={params.mode}\n")
            log.write(f"K={params.k}\n")
            log.write(f"executable={exe.resolve()}\n")
            log.write(f"signature_file={signature_file.resolve()}\n")
            log.write(f"signature_file_bytes={signature_file.stat().st_size}\n")
            log.write(f"nb_ineq_per_poly={args.nb_ineq}\n")
            log.write("T0_SIG_LIMIT=unset\n")
            log.write("T0_WINDOW_ALPHA=1\n")
            log.write("T0_LOW_C_RELAX_FACTOR=1\n\n")

            for round_index, c_value in enumerate(c_values, start=1):
                c_low_abs = c_value - 1 if round_index == 1 else c_value
                cmd = [
                    str(exe),
                    str(args.key),
                    str(args.nb_ineq),
                    str(c_low_abs),
                    str(c_value),
                    str(args.max_passes),
                    "1",
                ]

                print(
                    f"[{round_index}/{len(c_values)}] C={c_value}: "
                    f"greedy, target={args.nb_ineq} inequalities/poly",
                    flush=True,
                )
                started = time.perf_counter()
                completed = subprocess.run(
                    cmd,
                    cwd=c_dir,
                    env=env,
                    capture_output=True,
                    text=True,
                    errors="replace",
                    check=False,
                )
                wall_sec = time.perf_counter() - started
                output = (completed.stdout or "") + (completed.stderr or "")

                log.write(f"===== C={c_value} =====\n")
                log.write("command=" + subprocess.list2cmdline(cmd) + "\n")
                log.write(output)
                if output and not output.endswith("\n"):
                    log.write("\n")
                log.flush()

                if completed.returncode != 0:
                    raise RuntimeError(
                        f"Greedy solver failed at C={c_value} with "
                        f"return code {completed.returncode}; see {log_file}"
                    )

                build = parse_builder_output(output, poly_count)
                if build is None:
                    raise RuntimeError(
                        f"Could not parse constraint counts at C={c_value}; "
                        f"see {log_file}"
                    )
                totals = [
                    build["ineq0"][i] + build["ineq1"][i]
                    for i in range(poly_count)
                ]
                if min(totals) < args.nb_ineq:
                    raise RuntimeError(
                        f"Signature pool exhausted at C={c_value}: only "
                        f"{totals} inequalities; target is {args.nb_ineq}"
                    )

                guess = np.fromfile(guess_file, dtype=np.float64)
                if guess.size != poly_count * poly_degree:
                    raise RuntimeError(
                        f"Invalid greedy output size at C={c_value}: {guess.size} doubles"
                    )
                guess = guess.reshape(true_t0.shape)
                max_error, mismatches = compute_error(guess, true_t0)
                violated, objective = parse_greedy_stats(output, poly_count)

                row = {
                    "parameter_set": params.mldsa_name,
                    "C": c_value,
                    "signature_pool": signature_file.name,
                    "target_ineq_per_poly": args.nb_ineq,
                    "signatures_read": build["signs"],
                    "ineq_total_per_poly": ";".join(map(str, totals)),
                    "build_sec": build["build_sec"],
                    "solve_wall_sec": f"{wall_sec:.3f}",
                    "violated_per_poly": ";".join(map(str, violated)),
                    "objective_per_poly": ";".join(map(str, objective)),
                    "max_abs_error": max_error,
                    "mismatched_coefficients": mismatches,
                }
                rows.append(row)
                with csv_file.open("w", newline="", encoding="utf-8") as csv_out:
                    writer = csv.DictWriter(csv_out, fieldnames=fields)
                    writer.writeheader()
                    writer.writerows(rows)

                print(
                    f"    signs={build['signs']}, inequalities={totals}, "
                    f"max_error={max_error}, mismatches={mismatches}, "
                    f"wall={wall_sec:.1f}s",
                    flush=True,
                )

        shutil.copy2(guess_file, final_guess_file)
        run_succeeded = True
    finally:
        if had_guess and before_guess_file.exists():
            shutil.copy2(before_guess_file, guess_file)
        elif guess_file.exists():
            guess_file.unlink()

    if not run_succeeded:
        raise RuntimeError(f"Experiment did not complete; partial results: {csv_file}")

    final = rows[-1]
    print(f"CSV: {csv_file}")
    print(f"Log: {log_file}")
    print(f"Final guess: {final_guess_file}")
    print(
        f"Final recovery ({params.mldsa_name}, K={params.k}): "
        f"max_abs_error={final['max_abs_error']}, "
        f"mismatched_coefficients={final['mismatched_coefficients']}"
    )


if __name__ == "__main__":
    main()
