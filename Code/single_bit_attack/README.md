# One-Bit ML-DSA Secret-Recovery Experiments

This directory contains the noiseless one-bit leakage experiments associated
with *Descent into Broken Trust: Uncovering ML-DSA Subkeys with Scarce Leakage
and Local Optimization*.

The code is a simulation. It generates an ML-DSA `s1` polynomial, simulates
accepted signing relations and one leaked bit of the masking randomness, builds
probability-equality or interval-inequality constraints, and recovers the 256
secret coefficients with belief propagation (BP) or local optimization. It
does not read real ML-DSA keys or captured side-channel traces.

The equality and inequality experiments are run separately. Using different
output directories for them preserves an independent result set for each
constraint model.

## 1. Repository layout

The expected layout is:

```text
Code/
|-- single_bit_attack/
|   |-- README.md
|   |-- sweep_bp_greedy_noiseless.py
|   |-- binary_search_bp_equality_inequality_noiseless.py
|   |-- hillclimb_mldsa.py
|   |-- hillclimb_mldsa_noise.py
|   |-- ILWE_all_solvers_hillclimb_ref_param.py
|   `-- results/                         # Created by the commands below
`-- hint_solver/
    |-- Cargo.toml
    |-- Cargo.lock
    `-- src/
```

Important files:

| File | Purpose |
|---|---|
| `sweep_bp_greedy_noiseless.py` | Generates secrets and noiseless leakage relations, constructs one selected constraint model, runs BP or greedy recovery, and saves CSV/JSON/NumPy results |
| `binary_search_bp_equality_inequality_noiseless.py` | Optional BP threshold search under a monotonic-success assumption |
| `hillclimb_mldsa.py` | Standalone noiseless interval-inequality hill-climbing experiment |
| `hillclimb_mldsa_noise.py` | Relation generator, ML-DSA parameters, and regression warm start used by the main sweep; its noisy CLI is outside the scope of this README |
| `ILWE_all_solvers_hillclimb_ref_param.py` | Local Python wrapper around the compiled `hint_solver` extension |
| `../hint_solver` | Rust/PyO3 implementation of `PyBP` and `PyGreedy` |

No external data set is required for the commands in this README.

## 2. Constraint models

For every accepted simulated signature, the scripts derive a transformed
relation involving one 256-coefficient `s1` polynomial.

### 2.1 Probability-equality model

The `bp-equality` branch estimates the centered residual distribution from an
independent profiling key and independent relation stream. Every attack
relation becomes a distribution-valued equality hint, which is solved by
`hint_solver.PyBP`.

Profiling relations are controlled by
`--likelihood-calibration-samples` and are not counted as attack relations.

### 2.2 Interval-inequality model

The `bp-inequality` branch assigns a uniform RHS distribution to every integer
residual satisfying

```text
-beta_eff < centered_mod(C_i * s1 - z_i) <= beta_eff.
```

For ML-DSA-44 with leakage index `j=6`, `beta_eff=32`, so the exact integral
support is `[-31, 32]`. The impossible endpoint `-32` is excluded.

The experiment is noiseless: the leaked bit is never flipped.

## 3. Supported environment

Recommended and tested-compatible version ranges:

| Component | Version |
|---|---|
| Python | 3.10 through 3.13 |
| NumPy | `>=1.25,<3` |
| SciPy | `>=1.11,<2` |
| Rust | stable toolchain |
| maturin | `>=1.5,<2` |
| PyO3 | resolved from `hint_solver/Cargo.lock` (0.23.x) |

The BP backend is a native extension. It must be built inside the same virtual
environment whose Python interpreter runs the experiments.

## 4. Windows PowerShell setup

### 4.1 Install system prerequisites

Install:

1. 64-bit Python 3.10, 3.11, 3.12, or 3.13.
2. Rust through `rustup` with the stable MSVC toolchain.
3. Microsoft Visual Studio Build Tools with the **Desktop development with
   C++** workload.

Open a new PowerShell window after installation and verify:

```powershell
python --version
rustc --version
cargo --version
```

The Python version must be in the supported range above.

### 4.2 Create the Python environment

```powershell
cd "<path-to-Code>\one_bit_attack"

python -m venv .venv
.\.venv\Scripts\Activate.ps1

python -m pip install --upgrade pip
python -m pip install "numpy>=1.25,<3" "scipy>=1.11,<2" "maturin>=1.5,<2"
```

If PowerShell blocks activation, enable scripts for the current process only:

```powershell
Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass
.\.venv\Scripts\Activate.ps1
```

### 4.3 Build and install `hint_solver`

From the active `one_bit_attack` virtual environment:

```powershell
Push-Location ..\hint_solver
python -m maturin develop --release --locked
Pop-Location
```

`maturin develop` installs the compiled extension into the active virtual
environment. Repeat this step after changing the Rust source or when creating
a new virtual environment.

### 4.4 Verify the backend

```powershell
python -c "import hint_solver; b=hint_solver.PyBP([[1]], [[(0,1.0)]]); print(hint_solver.__file__); print(hint_solver.PyBP.__text_signature__); print(len(b.get_prior()), b.get_nvar(), hasattr(b, 'propagate_damped'))"
```

The final two lines must be equivalent to:

```text
(coeffs, rhs, sz_chk=None, prior=None)
9 256 True
```

Verify the local Python wrapper:

```powershell
python -c "import sweep_bp_greedy_noiseless as s; print(s.CLWE_SOLVER_FILE); print('PyBP:', s.PyBP is not None); print('PyGreedy:', s.PyGreedy is not None)"
```

The printed solver path must end in this file (with the platform's path
separator):

```text
one_bit_attack/ILWE_all_solvers_hillclimb_ref_param.py
```

Both backend checks must print `True`.

## 5. Linux setup

Install a C compiler and Python development headers using the package manager
for the distribution, then install the stable Rust toolchain. On Debian or
Ubuntu, the system prerequisites normally include:

```bash
sudo apt update
sudo apt install build-essential python3-dev python3-venv curl
```

Install Rust with `rustup` if it is not already available, then verify
`rustc --version` and `cargo --version`.

Create the environment and build the extension:

```bash
cd "<path-to-Code>/one_bit_attack"

python3 -m venv .venv
source .venv/bin/activate

python -m pip install --upgrade pip
python -m pip install "numpy>=1.25,<3" "scipy>=1.11,<2" "maturin>=1.5,<2"

pushd ../hint_solver
python -m maturin develop --release --locked
popd
```

Use the same backend verification commands from the Windows section.

## 6. Preflight checks

Run these commands from `one_bit_attack` with the virtual environment active:

```powershell
python -c "import sys, numpy, scipy, hint_solver; print(sys.version); print('NumPy', numpy.__version__); print('SciPy', scipy.__version__); print('hint_solver', hint_solver.__file__)"
python sweep_bp_greedy_noiseless.py --help
python binary_search_bp_equality_inequality_noiseless.py --help
python hillclimb_mldsa.py --help
```

Do not continue if `PyBP` is unavailable or the wrapper points outside the
current `one_bit_attack` directory.

## 7. Validated single-key BP reproduction

These commands reproduce the configuration used to validate the bundled BP
backend. They generate the same secret and relation stream because both use
`--seed 42`. The two models are intentionally run as separate experiments and
write to separate directories.

### 7.1 Probability-equality BP

Windows PowerShell:

```powershell
python sweep_bp_greedy_noiseless.py `
    --params 44 --leakage 6 --branches bp-equality `
    --min-samples 6000 --max-samples 6000 --step 1000 `
    --num-keys 1 --seed 42 --collection-workers 4 `
    --bp-iterations 20 --bp-threads 8 `
    --likelihood-calibration-samples 50000 `
    --output-dir results\validated_bp_equality --non-verbose
```

Linux:

```bash
python sweep_bp_greedy_noiseless.py \
    --params 44 --leakage 6 --branches bp-equality \
    --min-samples 6000 --max-samples 6000 --step 1000 \
    --num-keys 1 --seed 42 --collection-workers 4 \
    --bp-iterations 20 --bp-threads 8 \
    --likelihood-calibration-samples 50000 \
    --output-dir results/validated_bp_equality --non-verbose
```

### 7.2 Interval-inequality BP

Windows PowerShell:

```powershell
python sweep_bp_greedy_noiseless.py `
    --params 44 --leakage 6 --branches bp-inequality `
    --min-samples 6000 --max-samples 6000 --step 1000 `
    --num-keys 1 --seed 42 --collection-workers 4 `
    --bp-iterations 20 --bp-threads 8 `
    --output-dir results\validated_bp_inequality --non-verbose
```

Linux:

```bash
python sweep_bp_greedy_noiseless.py \
    --params 44 --leakage 6 --branches bp-inequality \
    --min-samples 6000 --max-samples 6000 --step 1000 \
    --num-keys 1 --seed 42 --collection-workers 4 \
    --bp-iterations 20 --bp-threads 8 \
    --output-dir results/validated_bp_inequality --non-verbose
```

The validated result for both commands is:

```text
success=True
mismatches=0
violations=0
minimum_tested_samples=6000
```

The exact runtime depends on the processor and thread count.

## 8. Full independent BP threshold experiments

The following commands scan ascending 1000-relation prefixes for ten
independent keys. A branch threshold is the first tested prefix at which all
ten generated keys are recovered exactly.

These runs use substantially more memory and time than the single-key
validation.

### 8.1 Full probability-equality experiment

```powershell
python sweep_bp_greedy_noiseless.py `
    --params 44 --leakage 6 --branches bp-equality `
    --min-samples 1000 --max-samples 30000 --step 1000 `
    --num-keys 10 --seed 42 --collection-workers 4 `
    --bp-iterations 20 --bp-threads 16 `
    --likelihood-calibration-samples 50000 `
    --output-dir results\bp_equality_full --non-verbose
```

### 8.2 Full interval-inequality experiment

```powershell
python sweep_bp_greedy_noiseless.py `
    --params 44 --leakage 6 --branches bp-inequality `
    --min-samples 1000 --max-samples 30000 --step 1000 `
    --num-keys 10 --seed 42 --collection-workers 4 `
    --bp-iterations 20 --bp-threads 16 `
    --output-dir results\bp_inequality_full --non-verbose
```

On Linux, replace PowerShell backticks with `\` and use `/` in the output
paths.

Change `--params` to `65` or `87` and select the required `--leakage` index to
run another ML-DSA parameter set. The compiled message size is 9, so the same
backend supports both `eta=2` and `eta=4` secrets.

## 9. Optional greedy and hill-climbing runs

These are independent solver runs, not required for the two BP results above.

### 9.1 Probability-equality greedy solver

```powershell
python sweep_bp_greedy_noiseless.py `
    --params 44 --leakage 6 --branches greedy-equality `
    --min-samples 1000 --max-samples 30000 --step 1000 `
    --num-keys 1 --seed 42 --collection-workers 4 `
    --equality-greedy-iterations 100 --equality-greedy-threads 16 `
    --likelihood-calibration-samples 50000 `
    --output-dir results\greedy_equality --non-verbose
```

### 9.2 Interval-inequality hill-climbing branch

```powershell
python sweep_bp_greedy_noiseless.py `
    --params 44 --leakage 6 --branches greedy-inequality `
    --min-samples 1000 --max-samples 30000 --step 1000 `
    --num-keys 1 --seed 42 --collection-workers 4 `
    --hillclimb-max-iter 100000 --hillclimb-workers 4 `
    --hillclimb-fitness excess `
    --output-dir results\hillclimb_inequality --non-verbose
```

The standalone noiseless hill-climbing experiment can also be run directly:

```powershell
New-Item -ItemType Directory -Force results | Out-Null
python hillclimb_mldsa.py `
    --params 44 --leakage 6 --inf-rels 6000 `
    --num-keys 10 --seed 42 --block-size 2 `
    --max-iter 100000 --workers 4 --fitness excess `
    --default-optimizations --output results\hillclimb_inequality.csv `
    --non-verbose
```

## 10. Optional binary-search BP threshold

The binary-search program assumes that exact BP recovery remains successful
when more rows from the same ordered stream are added. Because this monotonicity
is an experimental assumption, retain the complete trace and confirm the
reported threshold when exact minimality matters.

Run the two models separately:

```powershell
python binary_search_bp_equality_inequality_noiseless.py `
    --params 44 --leakage 6 --branches bp-equality `
    --num-keys 5 --seed 42 `
    --min-samples 500 --max-samples 8000 --granularity 1 `
    --likelihood-calibration-samples 50000 `
    --bp-iterations 20 --bp-threads 16 --collection-workers 4 `
    --output-dir results\binary_bp_equality

python binary_search_bp_equality_inequality_noiseless.py `
    --params 44 --leakage 6 --branches bp-inequality `
    --num-keys 5 --seed 42 `
    --min-samples 500 --max-samples 8000 --granularity 1 `
    --bp-iterations 20 --bp-threads 16 --collection-workers 4 `
    --output-dir results\binary_bp_inequality
```

## 11. Output files and success criteria

`sweep_bp_greedy_noiseless.py` writes timestamped files below the selected
`--output-dir`:

```text
ML-DSA-44_j6_noiseless_<timestamp>.csv
ML-DSA-44_j6_noiseless_<timestamp>.json
ML-DSA-44_j6_noiseless_<timestamp>_secrets.npy
ML-DSA-44_j6_noiseless_<timestamp>_<branch>_<count>_recovered.npy
```

CSV columns:

| Column | Meaning |
|---|---|
| `samples` | Number of attack relations in the tested prefix |
| `branch` | Selected solver and constraint model |
| `key_idx` | Zero-based generated-key index |
| `success` | `True` only when every recovered coefficient equals the generated secret |
| `mismatches` | Number of incorrect coefficients out of 256 |
| `violations` | Number of selected constraints violated by the recovered candidate |
| `init_correct` | Correct coefficients in the regression warm start |
| `init_accuracy` | `init_correct / 256` |
| `iterations` | Configured or completed solver iterations |
| `time_s` | Solver time for that row |

The JSON file records the complete command arguments, ML-DSA parameters,
constraint descriptions, calibration metadata, relation-collection statistics,
thresholds, and paths to saved arrays.

`*_secrets.npy` has shape `(num_keys, 256)`. A recovered array is written when
the selected branch reaches exact recovery and has the same shape.

The required success condition is:

```text
success == True
mismatches == 0
violations == 0
```

Constraint satisfaction by itself is not sufficient: an alternative feasible
candidate is not counted as key recovery.

If no tested prefix recovers every requested key, the program still writes CSV,
JSON, and the true-secret array, but no recovered array is written for that
branch. `minimum_tested_samples` is `null`, `saved_recovered` is empty, and the
process exits with a nonzero status. This means “threshold not found in the
requested range,” not necessarily an import or runtime failure.

## 12. Important parameters

| Option | Meaning |
|---|---|
| `--params {44,65,87}` | ML-DSA parameter set |
| `--leakage J` | Leaked masking-randomness bit index |
| `--num-keys K` | Number of independent generated secrets |
| `--seed S` | Reproducible secret, profiling, and relation streams |
| `--min-samples`, `--max-samples`, `--step` | Ascending prefix grid; the main sweep requires multiples of 1000 |
| `--branches` | Run only the explicitly selected model/solver |
| `--bp-iterations` | Number of BP propagation rounds |
| `--bp-threads` | Native BP worker threads |
| `--collection-workers` | Relation-generation threads |
| `--likelihood-calibration-samples` | Independent profiling relations used only by equality branches |
| `--output-dir` | Result directory; use a different directory for every independent experiment |

For reproducibility, record all arguments and software versions. Increasing
thread counts can increase memory use.

## 13. Troubleshooting

### `No module named hint_solver`

Activate the intended virtual environment and rebuild the extension:

```powershell
.\.venv\Scripts\Activate.ps1
Push-Location ..\hint_solver
python -m maturin develop --release --locked
Pop-Location
python -c "import hint_solver; print(hint_solver.__file__)"
```

### The wrong `hint_solver` is imported

Print its location:

```powershell
python -c "import hint_solver; print(hint_solver.__file__)"
```

It must belong to the active virtual environment. If it points to a global
Python installation, activate the correct environment and run `maturin develop`
again.

### `PyBP` constructor or prior-size errors

Verify the bundled source contains:

```text
hint_solver/src/constants.rs: NVAR = 256, SZ_MSG = 9
PyBP signature: (coeffs, rhs, sz_chk=None, prior=None)
```

Then rebuild the extension. A previously installed stale binary can be removed
with:

```powershell
python -m pip uninstall -y hint-solver
```

### Windows linker errors

Install Visual Studio Build Tools and select **Desktop development with C++**.
Restart PowerShell so that Rust can locate the MSVC linker, then rebuild.

### BP is unavailable even though the wrapper exists

Run:

```powershell
python -c "import sweep_bp_greedy_noiseless as s; print(s.HINT_SOLVER_IMPORT_ERROR); print(s.CLWE_SOLVER_FILE)"
```

The wrapper must be the local
`one_bit_attack/ILWE_all_solvers_hillclimb_ref_param.py`, and the import error
must be `None`.

### The process exits nonzero after writing results

Inspect the CSV and JSON. If there is no traceback and
`minimum_tested_samples` is `null`, increase `--max-samples`, BP iterations, or
the search budget. The run completed, but exact recovery was not reached.

### Excessive memory use

Start with one key, reduce `--max-samples`, and lower worker/thread counts. The
full relation matrix and BP messages are held in memory during recovery.

## 14. Reproducibility record

Preserve the following with every reported result:

1. Python, NumPy, SciPy, Rust, Cargo, maturin, and `hint_solver` versions.
2. The exact command and random seed.
3. ML-DSA parameter set and leakage index.
4. Relation-count range and step.
5. BP iterations and thread counts.
6. Equality calibration sample count where applicable.
7. The complete CSV, JSON, secret array, and recovered array.
8. The source revision or archived source tree used to build `hint_solver`.

Useful version commands:

```powershell
python --version
python -c "import numpy, scipy, hint_solver; print('NumPy', numpy.__version__); print('SciPy', scipy.__version__); print('hint_solver', hint_solver.__file__)"
python -m maturin --version
rustc --version
cargo --version
```
