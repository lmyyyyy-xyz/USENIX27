# Attack_s1: Dilithium/ML-DSA `s1` Recovery Experiments

This directory implements two key-recovery experiments based on rejected
Dilithium/ML-DSA signing responses of the form `z = y + c*s1`:

1. **Boundary-recovery scenario**: retain coefficients close to or beyond a
   response boundary, derive interval constraints on `(c*s1)_i` from the
   theoretical range of `y`, and recover `s1` with belief propagation (BP).
2. **Four-value recovery scenario**: retain only the four response values
   `+gamma1`, `+gamma1-1`, `-gamma1`, and `-gamma1-1`, construct the RCoI
   inequalities, and recover `s1` with SciPy/HiGHS ILP or BP.

The code supports toy, Dilithium2, Dilithium3, and Dilithium5 parameters.
Always run the toy smoke tests before starting a full Dilithium2 experiment.

## 1. Files and directory layout

The core files are:

| File | Purpose |
|---|---|
| `mldsa_model.py` | Parameter sets, `s1`, sparse challenge `c`, mask `y`, and negacyclic multiplication |
| `bp_attack.py` | Sample collection, four-value and boundary constraints, BP conversion, and BP recovery |
| `ilp_attack.py` | Per-polynomial integer linear programs solved by SciPy/HiGHS; supports interval and noisy-equality encodings |
| `rcoi_noisy_equality.py` | Converts each four-value bounded noisy equality into two canonical `<=` inequalities |
| `test_rcoi_noisy_equality.py` | Focused tests for all four equations and their inequality conversion |
| `ILWE_all_solvers_hillclimb_ref_param.py` | Python BP wrapper; the local copy is preferred |
| `run_attack.py` | Main simulated boundary-recovery entry point |
| `binary_search_constraints.py` | Minimum-constraint search on simulated boundary samples |
| `binary_search_inequality.py` | Preset Dilithium2 boundary-inequality search |
| `sweep_simulated_rcoi_ilp.py` | Simulated first-abort four-value collection and ILP sweep |
| `run_cz_pairs_bp.py` | BP recovery from an external `(c,z)` data set |
| `sweep_cz_pairs_ilp.py` | ILP sweep over an external `(c,z)` data set |
| `binary_search_cz_pairs_bp.py` | Minimum-constraint BP search on an external data set |
| `requirements.txt` | Python dependencies: NumPy and SciPy |

A complete layout should look like this:

```text
Code/
|-- Attack_s1/
|   |-- *.py
|   |-- requirements.txt
|   |-- README.md
|   `-- outputs/                    # Created automatically
|-- hint_solver/                    # Rust/PyO3 BP backend source
|   |-- Cargo.toml
|   `-- src/
`-- cz_pairs_D2/                    # Required only for external-data runs
    |-- cz_pairs_verified.npz
    `-- s1_true.npy
```

The external data files do not have to be copied into the default sibling
directory. They can be supplied with explicit `--dataset` and `--secret`
arguments.

## 2. Environment setup

### 2.1 Python environment

Python 3.10 or newer is required. The following example uses Windows
PowerShell:

```powershell
cd "<path-to-Code>\Attack_s1"

py -3.10 -m venv .venv
.\.venv\Scripts\Activate.ps1

python -m pip install --upgrade pip
python -m pip install -r requirements.txt
```

If `py -3.10` is not available, use an installed Python 3.10+ interpreter:

```powershell
python -m venv .venv
.\.venv\Scripts\Activate.ps1
```

On Linux:

```bash
cd "<path-to-Code>/Attack_s1"
python3 -m venv .venv
source .venv/bin/activate
python -m pip install --upgrade pip
python -m pip install -r requirements.txt
```

### 2.2 Build and install `hint_solver`

BP depends on the Rust/PyO3 extension module `hint_solver`. Install a Rust
toolchain and `maturin`, then build it inside the active Python environment.

Windows PowerShell:

```powershell
python -m pip install maturin

Push-Location ..\hint_solver
maturin develop --release
Pop-Location
```

Linux:

```bash
python -m pip install maturin
pushd ../hint_solver
maturin develop --release
popd
```

Windows builds also require the MSVC C++ Build Tools. The compiled extension
must match the Python interpreter used to run the experiments.

Verify the dependencies and BP wrapper path:

```powershell
python -c "import numpy, scipy, hint_solver; print('dependencies: OK')"
python -c "import bp_attack; print(bp_attack.CLWE_SOLVER_FILE); print('BP:', bp_attack.solve_bp is not None)"
```

The second command should point to:

```text
<path-to-Code>\Attack_s1\ILWE_all_solvers_hillclimb_ref_param.py
```

and print `BP: True`.

## 3. Constraint model

Every response coefficient satisfies:

```text
z_i = y_i + (c*s1)_i,
-gamma1 + 1 <= y_i <= gamma1.
```

Using only observable `c` and `z`, the attacker obtains:

```text
z_i - gamma1 <= (c*s1)_i <= z_i + gamma1 - 1.
```

The implementation clips this interval to the natural product bound:

```text
-eta*tau <= (c*s1)_i <= eta*tau.
```

The four-value constraints are:

| `z_i` | Allowed range of `(c*s1)_i` |
|---|---|
| `+gamma1` | `[0, eta*tau]` |
| `+gamma1-1` | `[-1, eta*tau]` |
| `-gamma1` | `[-eta*tau, -1]` |
| `-gamma1-1` | `[-eta*tau, -2]` |

The four-value ILP has two equivalent encodings. The default
`--ilp-formulation interval` passes the ranges in the table directly to
SciPy. The new `--ilp-formulation noisy-equality` first writes each row
`a = row(c, i)` as `a*s1 = rhs + e`, with `B = eta*tau`:

| `z_i` | Bounded noisy equality |
|---|---|
| `+gamma1` | `a*s1 = 0 + e`, `0 <= e <= B` |
| `+gamma1-1` | `a*s1 = -1 + e`, `0 <= e <= B+1` |
| `-gamma1` | `a*s1 = -1 + e`, `-B+1 <= e <= 0` |
| `-gamma1-1` | `a*s1 = -2 + e`, `-B+2 <= e <= 0` |

For `e_lower <= e <= e_upper`, the module sends these two rows to HiGHS:

```text
 a*s1 <= rhs + e_upper
-a*s1 <= -(rhs + e_lower)
```

This doubles the number of solver rows while preserving exactly the same
feasible integer set as the interval formulation. It does not use the true
`y` or `s1`. The conversion intentionally accepts only the four exact RCoI
values; it is not used by the boundary-recovery/BP scenario.

Each standard `s1` polynomial has 256 unknown coefficients. The toy parameter
set has 64 coefficients. Polynomials are modeled and solved independently.

## 4. Initial checks

Confirm that every command-line entry point loads successfully:

```powershell
python run_attack.py --help
python sweep_simulated_rcoi_ilp.py --help
python run_cz_pairs_bp.py --help
python sweep_cz_pairs_ilp.py --help
python binary_search_constraints.py --help
python binary_search_cz_pairs_bp.py --help
```

Run the noisy-equality conversion tests:

```powershell
python -m unittest -v test_rcoi_noisy_equality.py
```

If the optional broader test files are also present, run them separately.

Do not begin a long parameter-set experiment until all imports and tests pass.

## 5. Boundary-recovery scenario

### 5.1 Toy smoke experiment with unknown `y`

Start with the realistic bounded-`y` inequality mode. This configuration is
suitable for an end-to-end smoke test:

```powershell
python run_attack.py `
  --level toy `
  --constraint-mode inequality `
  --threshold gamma1-beta `
  --signatures 50000 `
  --max-constraints-per-poly 2000 `
  --bp-iterations 100 `
  --threads 1
```

A successful run reports:

```text
BP: exact_recovery=True, mismatches=0/128, interval_violations=0
```

Only `exact_recovery=True` means that the complete key was recovered.
Producing a BP estimate is not, by itself, a successful recovery.

### 5.2 Known-`y` debug baseline

The following mode uses the simulator's true `y_i` and converts every selected
observation into an exact equality. It verifies multiplication, indexing, and
the BP pipeline. It is an oracle/debug baseline, not a realistic attacker
model, because a real attacker does not know `y_i`.

```powershell
python run_attack.py `
  --level toy `
  --constraint-mode boundary-equality `
  --signatures 50000 `
  --max-constraints-per-poly 200 `
  --bp-iterations 100 `
  --threads 1
```

### 5.3 Other boundary representations

`run_attack.py` supports the following modes:

- `inequality`: direct bounded-`y` interval constraints; use this as the main
  boundary-recovery experiment.
- `boundary-equality-marginalized`: retain only `|z_i| >= gamma1` and
  marginalize unknown `y`.
- `slack-equality`: record an equivalent bounded-slack equality and marginalize
  the slack before BP.
- `unknown-y-error-interval`: use the asymmetric error interval derived from
  `eta*tau`.
- `boundary-equality`: known-`y` oracle/debug baseline.

Example using only raw `gamma1` boundary crossings with unknown `y`:

```powershell
python run_attack.py `
  --level toy `
  --constraint-mode boundary-equality-marginalized `
  --signatures 50000 `
  --max-constraints-per-poly 2000 `
  --bp-iterations 100
```

### 5.4 Full Dilithium2 boundary experiment

Run a fixed number of constraints per polynomial:

```powershell
python run_attack.py `
  --level 2 `
  --constraint-mode inequality `
  --threshold gamma1-beta `
  --signatures 1000000 `
  --max-constraints-per-poly 2000 `
  --bp-iterations 100 `
  --bp-damping 0.7 `
  --threads 16
```

Search for the smallest successful constraint prefix:

```powershell
python binary_search_constraints.py `
  --level 2 `
  --constraint-mode inequality `
  --threshold gamma1-beta `
  --signatures 1000000 `
  --min-constraints-per-poly 500 `
  --max-constraints-per-poly 2000 `
  --bp-iterations 20 `
  --bp-damping 0 `
  --threads 16
```

The preset entry point for the same Dilithium2 experiment is:

```powershell
python binary_search_inequality.py
```

Loopy BP is not guaranteed to succeed monotonically as the number of
constraints increases. To perform a grid scan instead of relying only on the
binary-search assumption, add an option such as:

```powershell
--scan-step 100
```

## 6. Four-value recovery with simulated samples

### 6.1 Standard first-abort experiment

The standard collector simulates internal Dilithium signing attempts and
follows the `poly_chknorm` scan order. It identifies the first coefficient
that would cause rejection and retains the attempt only if that coefficient
is one of the four target values.

```powershell
python sweep_simulated_rcoi_ilp.py `
  --level 2 `
  --signature-attempts 4000000 `
  --counts-per-poly 1000,2000,3000,4000,5000 `
  --ilp-formulation noisy-equality `
  --time-limit-per-poly 120 `
  --progress-every 100000
```

The largest requested sample set is collected once. Every ILP evaluation uses
a nested prefix of that fixed data, so different constraint counts do not
resample the secret or observations.

`--allow-multiple-per-attempt` retains every four-value coefficient in an
attempt, including coefficients that occur after the first position where the
normal implementation would already have aborted. This option is a synthetic
skipped-check baseline and must not be reported as the realistic first-abort
experiment.

### 6.2 Compare BP and ILP on the same simulated data

The simulation writes a matched pair of files under `outputs`:

```text
*_samples.npz
*_s1_true.npy
```

Select the most recent sample file in PowerShell:

```powershell
$sample = Get-ChildItem .\outputs\*_samples.npz |
  Sort-Object LastWriteTime -Descending |
  Select-Object -First 1
$secret = $sample.FullName -replace '_samples\.npz$', '_s1_true.npy'
```

Run BP on that exact sample set:

```powershell
python run_cz_pairs_bp.py `
  --dataset $sample.FullName `
  --secret $secret `
  --level 2 `
  --max-constraints-per-poly 2000 `
  --bp-iterations 100 `
  --threads 16
```

Run an ILP sweep on the same data:

```powershell
python sweep_cz_pairs_ilp.py `
  --dataset $sample.FullName `
  --secret $secret `
  --level 2 `
  --counts 1000,2000,max,all `
  --ilp-formulation noisy-equality `
  --time-limit-per-poly 120
```

## 7. Four-value recovery with an external `(c,z)` data set

### 7.1 Required input arrays

`cz_pairs_verified.npz` must contain at least:

| Array | Shape and meaning |
|---|---|
| `trace_id` | `(rows,)`; sample or trace identifier |
| `poly_l` | `(rows,)`; target `s1` polynomial index |
| `coeff_i` | `(rows,)`; selected response coefficient index |
| `k` | `(rows,)`; must equal `poly_l*n + coeff_i` |
| `c_pred` | `(rows,n)`; coefficients in `{-1,0,1}` with Hamming weight `tau` |
| `z_pred_val` | `(rows,)`; recovered four-value response |

`s1_true.npy` must have shape `(ell,n)`. It is loaded only for scoring the
recovered key. It is not used to construct constraints or select rows.

### 7.2 Check the external data set

```powershell
python -c "import numpy as np; p=r'..\rej_2026_D2_SCA\04_output_cz_pairs_s1\cz_pairs_verified.npz'; d=np.load(p); print(d.files); print({k:d[k].shape for k in d.files})"
```

### 7.3 ILP constraint sweep

```powershell
python sweep_cz_pairs_ilp.py `
  --dataset ..\rej_2026_D2_SCA\04_output_cz_pairs_s1\cz_pairs_verified.npz `
  --secret ..\rej_2026_D2_SCA\04_output_cz_pairs_s1\s1_true.npy `
  --level 2 `
  --counts 500,1000,1500,max,all `
  --prefix-order trace-id `
  --ilp-formulation noisy-equality `
  --time-limit-per-poly 120
```

Selection rules:

- A numeric value `N` uses the first `N` constraints for every polynomial
  after applying the requested order.
- `max` uses the largest balanced prefix allowed by the least represented
  polynomial.
- `all` uses every row and permits unequal row counts across polynomials.

Use `--ilp-formulation interval` to reproduce the original ranged-constraint
model. Use `--ilp-formulation noisy-equality` to run the new bounded-noise
equation conversion on the same four-value samples. The JSON summary records
the selected formulation, and each per-polynomial record reports both
`source_rows` and `solver_rows` (the latter is twice the former in
noisy-equality mode).

### 7.4 BP with a fixed constraint count

```powershell
python run_cz_pairs_bp.py `
  --dataset ..\rej_2026_D2_SCA\04_output_cz_pairs_s1\cz_pairs_verified.npz `
  --secret ..\rej_2026_D2_SCA\04_output_cz_pairs_s1\s1_true.npy `
  --level 2 `
  --max-constraints-per-poly 1500 `
  --bp-iterations 100 `
  --bp-damping 0.7 `
  --threads 16
```

Set `--max-constraints-per-poly 0` to use every available constraint.

### 7.5 Search for the minimum BP constraint count

```powershell
python binary_search_cz_pairs_bp.py `
  --dataset ..\rej_2026_D2_SCA\04_output_cz_pairs_s1\cz_pairs_verified.npz `
  --secret ..\rej_2026_D2_SCA\04_output_cz_pairs_s1\s1_true.npy `
  --level 2 `
  --min-constraints-per-poly 500 `
  --max-constraints-per-poly 1900 `
  --prefix-order trace-id `
  --verification-radius 10 `
  --bp-iterations 100 `
  --threads 16
```

For a fair BP/ILP comparison, use the same data file, `--prefix-order`, and
number of constraints per polynomial.

## 8. Outputs and success criteria

The default output directory is:

```text
<path-to-Code>\Attack_s1\outputs
```

A relative `--output-dir` is resolved relative to the `Attack_s1` directory.
Use `--no-save` for a run that should not create result files.

The main output suffixes are:

| Suffix | Contents |
|---|---|
| `*_summary.json` | Parameters, selected ILP formulation, sample statistics, solver row counts, timing, mismatch counts, and final status |
| `*_coefficients.csv` | True value, recovered value, and match flag for every `s1` coefficient |
| `*_evaluations.csv` | Per-probe results for constraint sweeps |
| `*_secret.npy` or `*_s1_true.npy` | Simulated ground truth used only for evaluation |
| `*_recovered.npy` | BP recovery result |
| `*_result.npz` | Arrays collected by a sweep or binary search |
| `*_samples.npz` | Simulated four-value observations reusable by BP and ILP |

A complete recovery requires:

```text
exact_recovery=True
mismatches=0
all has_solution entries are True       # ILP
interval_violations=0                    # BP/ILP estimate satisfies all constraints
```

A feasible solution with `exact_recovery=False` means that the selected
constraints did not uniquely force the true `s1`. It must not be reported as
a successful key recovery.

Some entry points return a nonzero process exit code when execution completed
normally but no evaluated prefix recovered the exact key. Automation should
inspect `summary.json` and `exact_recovery` instead of treating the presence of
an output file as success.

## 9. Recommended complete experiment order

1. Create and activate a Python 3.10+ virtual environment.
2. Install NumPy and SciPy, then build and verify `hint_solver`.
3. run every entry point with `--help` to rule out import and path errors.
4. Run the toy `boundary-equality` oracle baseline.
5. Run the toy `inequality` experiment and require
   `exact_recovery=True` with unknown `y`.
6. Run the Dilithium2 boundary scenario and search for the minimum successful
   constraint prefix with `binary_search_constraints.py`.
7. Run `sweep_simulated_rcoi_ilp.py` once with `interval` and once with
   `noisy-equality`, using the same seed and prefix counts.
8. Give the same `*_samples.npz` file to BP and both ILP formulations and
   compare their recovery results.
9. Run both ILP formulations, fixed-count BP, and BP prefix search on the external
   `cz_pairs_verified.npz` data set.
10. Preserve the random seed, exact data paths, parameters, software versions,
    commands, and `outputs` directory for paper reproducibility.

## 10. Troubleshooting

### `required BP solver not found`

Place `ILWE_all_solvers_hillclimb_ref_param.py` beside `bp_attack.py`. The
current implementation also supports the original layout with the wrapper in
a sibling `CLWE_Solve` directory.

### `No module named hint_solver`

Activate the correct virtual environment, enter `../hint_solver`, and run:

```powershell
maturin develop --release
```

Then verify it with `python -c "import hint_solver"`.

### `cz-pairs dataset not found`

Copy the data into the default `../cz_pairs_D2` directory, or always pass
explicit `--dataset` and `--secret` paths.

### `dataset cannot meet ... for every polynomial`

At least one polynomial has fewer samples than requested. Reduce
`--max-constraints-per-poly`, or use `max` or `all` in an ILP sweep.

### The simulated four-value collector cannot fill the requested prefix

Increase `--signature-attempts`. Toy parameters can produce severe
polynomial imbalance in realistic first-abort mode. Use `--level 2` for the
standard four-value experiment, and do not replace the first-abort experiment
with `--allow-multiple-per-attempt`.

### ILP times out or reports `has_solution=False`

Increase `--time-limit-per-poly`, reduce the constraint count for a smoke
test, and verify that every input interval is valid. `has_solution=False` is
different from finding a feasible solution that does not match the true key.

### BP does not recover the complete key

Increase the number of constraints per polynomial or `--bp-iterations`, try
different `--bp-damping` values and random seeds, and check whether positive
and negative boundary samples are badly imbalanced. The final result must
always be judged by `exact_recovery` and `mismatches`.
