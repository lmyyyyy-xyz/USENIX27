# Recovering Dilithium/ML-DSA `t0` from standard signatures

This repository contains the research artifact for recovering the hidden low-bit
vector `t0` of a Dilithium/ML-DSA public key from many valid signatures. The
default environment described below is 64-bit Linux.

## Supported parameter sets

| Mode | Historical name | Standard name | Number of `t0` polynomials |
| ---: | --- | --- | ---: |
| 2 | Dilithium2 | ML-DSA-44 | 4 |
| 3 | Dilithium3 | ML-DSA-65 | 6 |
| 5 | Dilithium5 | ML-DSA-87 | 8 |

Every `t0` polynomial has 256 unknown coefficients. Select the mode through
`Additional_files/Dilithium_parameters.py` for the Notebook workflow, or with
`--level 2`, `--level 3`, or `--level 5` for the greedy command-line driver.

## Prerequisites

- 64-bit Linux
- Python >= 3.10
- Pipenv
- GCC or another C compiler available as `cc`
- GNU Make and Bash
- OpenSSL development headers, only when regenerating KAT files
- lp_solve 5.5, only for the LP solver

On Debian or Ubuntu:

```bash
sudo apt update
sudo apt install python3 python3-pip pipenv build-essential openssl libssl-dev
```

Install the Python dependencies from the repository root:

```bash
pipenv install
```

The core Python dependencies are NumPy, PyCryptodome and Jupyter Notebook.

## Repository layout

| Path | Purpose |
| --- | --- |
| `Additional_files/Notebooks/Attack_t0.ipynb` | Original end-to-end LP workflow |
| `Additional_files/C_functions/sign_rdm_msg_and_save.c` | Generates valid signatures and stores attack data `(c,r0,h)` |
| `Additional_files/C_functions/build_solve_t0_lp.c` | Builds and solves one LP for each `t0` polynomial |
| `Additional_files/C_functions/build_solve_t0_greedy.c` | Sparse greedy solver for the same inequalities |
| `Additional_files/C_functions/noisy_equality.c` | Converts each noisy equality into two canonical inequalities shared by LP and hill climbing |
| `Additional_files/C_functions/test_noisy_equality.c` | Checks the equality formulas for modes 2, 3 and 5 |
| `Additional_files/run_greedy_matched_lp.py` | Automated shrinking-radius greedy driver |
| `Additional_files/mldsa_t0_params.py` | ML-DSA parameter mapping and true-`t0` decoding for evaluation |
| `dilithium/ref/` | Bundled Dilithium reference implementation and KAT files |
| `lp_solve_5.5/` | Bundled lp_solve source tree |

## Build lp_solve on Linux

This step is required only for `build_solve_t0_lp*`. The greedy solver does not
link against lp_solve.

From the repository root:

```bash
cd lp_solve_5.5/lpsolve55
sh ccc
cd ../..
```

On 64-bit Linux, the expected library directory is:

```text
lp_solve_5.5/lpsolve55/bin/ux64
```

Expose the shared library before running an LP executable:

```bash
export LD_LIBRARY_PATH="$PWD/lp_solve_5.5/lpsolve55/bin/ux64:${LD_LIBRARY_PATH:-}"
```

`Additional_files/C_functions/Makefile` uses this `ux64` directory by default.
If lp_solve is installed elsewhere, override the directory while compiling:

```bash
make LPSOLVE_LIBDIR=/absolute/path/to/lpsolve/lib build_solve_t0_lp2
```

## KAT input files

The attack reads the target public and private keys from one of:

```text
dilithium/ref/PQCsignKAT_Dilithium2.rsp
dilithium/ref/PQCsignKAT_Dilithium3.rsp
dilithium/ref/PQCsignKAT_Dilithium5.rsp
```

These files are already included. Regenerating them is optional. For example:

```bash
cd dilithium/ref
make nistkat/PQCgenKAT_sign2
./nistkat/PQCgenKAT_sign2
cd ../..
```

KAT generation requires OpenSSL and `libssl-dev`.

## Build the attack programs

Run the following commands from `Additional_files/C_functions`.

For Dilithium2 / ML-DSA-44:

```bash
cd Additional_files/C_functions
make sign_rdm_msg_and_save2
make build_solve_t0_lp2
make build_solve_t0_greedy2_matched
make build_solve_t0_eq_lp2
make build_solve_t0_eq_greedy2
make check-noisy-equality
cd ../..
```

Replace the final `2` with `3` or `5` for ML-DSA-65 or ML-DSA-87.

## End-to-end attack sequence

The implementation performs the following steps:

1. Read the selected public and private key from a Dilithium KAT response file.
2. Sign many random 32-byte messages with the standard Dilithium signer.
3. Compute `LowBits(Az - c*t1*2^D)` for every accepted signature.
4. Store the attack data `(c,r0,h)` in a compact signature pool.
5. Derive sparse linear inequalities for the unknown product `c*t0` from the
   signature acceptance bounds and hint state.
6. Split `t0` into independent 256-variable polynomial problems.
7. Solve each problem with lp_solve or the sparse greedy solver.
8. Start from an all-zero guess and repeat with shrinking radii
   `C = 4096, 2048, ..., 1`.
9. Save the approximate or fully recovered `t0` and report its error when the
   KAT secret key is available for evaluation.

## Generate the compressed signature pool

The following example selects KAT key index 0 and generates 300,000 signatures
for Dilithium2:

```bash
cd Additional_files/C_functions
./sign_rdm_msg_and_save2 0 300000
cd ../..
```

The generated file is:

```text
Additional_files/Signs/Dilithium2/key0/PQCsignKAT_Dilithium2_compressed.rsp
```

Use a smaller value such as 1,000 for an initial smoke test. A small signature
pool may not contain enough useful inequalities for complete recovery.

## LP workflow

### Recommended: run the Notebook

Start Jupyter from the Notebook directory so that all relative paths match the
paths used by the C programs:

```bash
pipenv shell
cd Additional_files/Notebooks
jupyter notebook Attack_t0.ipynb
```

Run the cells in order. The Notebook:

- loads the selected KAT key;
- optionally generates the compressed signature pool;
- compiles `sign_rdm_msg_and_save<mode>` and `build_solve_t0_lp<mode>`;
- initializes an all-zero `t0_guess_file.bin`;
- runs every shrinking-radius LP round;
- compares the recovered vector with the true KAT `t0` when `known_sk=True`;
- writes a Markdown summary.

The default Notebook configuration requests 300,000 signatures and 50,000
selected inequalities per polynomial, so a full run can require substantial
time and disk space.

### Manual LP commands

After compiling the programs and generating signatures, initialize the
Dilithium2 guess from the repository root:

```bash
mkdir -p Additional_files/Guess/Dilithium2/key0
python - <<'PY'
import numpy as np

np.zeros((4, 256), dtype=np.float64).tofile(
    "Additional_files/Guess/Dilithium2/key0/t0_guess_file.bin"
)
PY
```

Then run the shrinking-radius sequence from `Additional_files/C_functions`:

```bash
cd Additional_files/C_functions
./build_solve_t0_lp2 0 50000 4095 4096
for C in 2048 1024 512 256 128 64 32 16 8 4 2 1; do
    ./build_solve_t0_lp2 0 50000 "$C"
done
cd ../..
```

For modes 3 and 5, use the matching executable and initialize a `(6,256)` or
`(8,256)` zero array respectively.

## Noisy-equality workflow

The equality module uses the same compressed `(c,r0,h)` pool as the original
inequality attack. For coefficient `j`, let `a` be the negacyclic convolution
row produced from challenge `c`, so that `a*t0` is coefficient `j` of `c*t0`.
Let

```text
E = GAMMA2 - BETA - 1.
```

The module constructs `a*t0 = b + e` as follows:

| Signature state | `b` | Noise interval for `e` |
| --- | ---: | ---: |
| `h[j] = 0` | `r0[j]` | `[-E, E]` |
| `h[j] = 1` and `r0[j] > 0` | `r0[j] - 2*GAMMA2` | `[0, E]` |
| `h[j] = 1` and `r0[j] < 0` | `r0[j] + 2*GAMMA2` | `[-E, 0]` |

An invalid `h[j] = 1, r0[j] = 0` pair is skipped. Every valid noisy equality
is converted once, in the shared C module, to the two inequalities

```text
 a*t0 <= b + e_max
-a*t0 <= -(b + e_min).
```

Consequently, LP and hill climbing receive exactly the same feasible interval.
The command-line value `nb_equations` counts original equality rows per `t0`
polynomial; each row creates two solver inequalities.

### Build the equality solvers

From `Additional_files/C_functions`, build the matching mode. For example,
for Dilithium2 / ML-DSA-44:

```bash
make build_solve_t0_eq_lp2
make build_solve_t0_eq_greedy2
make check-noisy-equality
```

Replace `2` with `3` or `5` for the other parameter sets. The equality LP
target needs lp_solve; the equality greedy target and formula tests do not.

### Run the equality LP

Initialize `t0_guess_file.bin` exactly as in the manual LP workflow, then run:

```bash
cd Additional_files/C_functions
./build_solve_t0_eq_lp2 0 50000 4096
for C in 2048 1024 512 256 128 64 32 16 8 4 2 1; do
    ./build_solve_t0_eq_lp2 0 50000 "$C"
done
cd ../..
```

Each LP uses coefficient bounds centered on the current guess and overwrites
the guess only when all `K` models solve successfully. Equality LP dumps use
`poly0_eq.lp`, ..., so they do not overwrite the original `poly0.lp` files.

### Run equality hill climbing

Start again from an independent zero guess when comparing it with LP. Then run:

```bash
cd Additional_files/C_functions
./build_solve_t0_eq_greedy2 0 50000 4096
for C in 2048 1024 512 256 128 64 32 16 8 4 2 1; do
    ./build_solve_t0_eq_greedy2 0 50000 "$C"
done
cd ../..
```

The hill-climbing objective is the total L1 violation of the converted
inequalities. A zero objective means all selected noisy-equality intervals are
satisfied. Optional arguments are:

```text
build_solve_t0_eq_greedy<mode> KEY NB_EQ C_LOW_ABS C_UP MAX_PASSES
build_solve_t0_eq_greedy<mode> KEY NB_EQ C_LOW_ABS C_UP MAX_PASSES CHECK
```

Set `GREEDY_CONSISTENCY_CHECK=1` (or pass `CHECK=1`) for expensive internal
objective checks. `T0_WINDOW_ALPHA` changes the search box multiplier; its
equality-mode default is `1`. Both equality backends also accept
`T0_SIG_FILE=/path/to/pool.rsp`, `T0_SIG_LIMIT=N`, and
`T0_GUESS_FILE=/path/to/guess.bin` for controlled tests or independent LP and
hill-climbing guess files.

Do not reduce `C` until the current estimate is good enough for the true value
to remain inside the next search box. Otherwise the hard LP intervals can
become infeasible; hill climbing will instead report a nonzero violation.

## Greedy workflow

The command-line driver applies the same shrinking-radius schedule and the same
signature/constraint policy as the LP comparison. It initializes and restores
the working guess automatically.

From the repository root:

```bash
pipenv run python Additional_files/run_greedy_matched_lp.py \
    --level 2 \
    --key 0 \
    --nb-ineq 50000 \
    --max-passes 80
```

The driver looks first for a file ending in `_compressed_300000.rsp`, then falls
back to the ordinary `_compressed.rsp` file generated above. Use
`--signature-file` or `--executable` to override those paths.

## Inputs and outputs

| Path | Contents |
| --- | --- |
| `dilithium/ref/PQCsignKAT_Dilithium*.rsp` | KAT public and private keys |
| `Additional_files/Signs/Dilithium*/key*/` | Compact `(c,r0,h)` signature pools |
| `Additional_files/Guess/Dilithium*/key*/t0_guess_file.bin` | Current `t0` guess as `K x 256` little-endian `float64` values |
| `Additional_files/Lps/Dilithium*/key*/poly*.lp` | LP model for each `t0` polynomial |
| `Additional_files/Lps/Dilithium*/key*/poly*_eq.lp` | Converted noisy-equality LP/hill-climb model |
| `Additional_files/Sum_ups/Dilithium*/key*/results.md` | Notebook timing and recovery summary |
| `Additional_files/Guess/Dilithium*/key*/greedy_*.csv` | Per-radius greedy statistics and recovery errors |
| `Additional_files/Guess/Dilithium*/key*/greedy_*.log` | Full greedy solver output |
| `Additional_files/Guess/Dilithium*/key*/greedy_*.bin` | Preserved final greedy guess |

The `Signs`, `Guess`, `Lps` and `Sum_ups` directories are created at runtime.
Directory names are case-sensitive on Linux.

## Common problems

- **`liblpsolve55.so` not found:** build lp_solve and export
  `LD_LIBRARY_PATH` as shown above.
- **Compressed signature file not found:** run `sign_rdm_msg_and_save<mode>`
  before the LP or greedy solver.
- **Not enough inequalities:** generate a larger signature pool or reduce the
  requested `--nb-ineq` value for a smoke test.
- **Equality LP is infeasible:** restore the previous guess and use a larger
  radius `C`; the current coefficient box no longer contains a common feasible
  point for the selected equality intervals.
- **KAT file not found:** generate the matching KAT or place it under
  `dilithium/ref/`.
- **Relative paths fail:** run the Notebook from
  `Additional_files/Notebooks`, and run C executables from
  `Additional_files/C_functions`.

## Third-party code

The repository bundles the Dilithium reference implementation and lp_solve
5.5. Consult their respective source directories for upstream licensing and
copyright information.
