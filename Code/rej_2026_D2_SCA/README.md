# Side-channel recovery of rejected `(c, z)` pairs on Dilithium-2

This package documents the **side-channel front end** of the rejected-signature attack of Zhou et al.
(*Rejected Signatures' Challenges Pose New Challenges*, TCHES 2025(4), 817–847), reproduced on
ML-DSA-44 (Dilithium-2). Starting from power traces of the last rejected signing trial, we recover the
rejected challenge `c` and the boundary response coefficient `z`, and export a set of `(c, z)` pairs
from which the secret vector `s1` can be solved. The layout mirrors §5 of the paper.

Throughout, recovery and its verification are **blind**: the secret key is never used to obtain or to
filter a pair; it is used only to *score* the reported accuracy.

## 1. Experimental setup

The device under test runs the unprotected pq-crystals ML-DSA-44 reference implementation, compiled with
`-O3` and time optimization, on an **STM32F405** mounted on a CW308 UFO board and clocked at its full
**168 MHz**. Power leakage is band-limited by a BLP-5+ low-pass filter, amplified by a
**PA303** pre-amplifier, filtered again, and digitised on a **LeCroy WaveRunner 9104** at **100 MSa/s**.
Signing is deterministic (`rnd = 0`) under a fixed known key (ρ = `16F553B0…`). Messages are filtered so
that the target `z` values occur, and **4.5×10⁴** traces are captured, each covering the **last rejected
trial immediately preceding the accepting trial**. Of these, 30 000 are *rejected-coefficient-of-interest*
(RCoI) rounds whose aborting `z` coefficient takes one of the four boundary values, and 15 000 are the
remaining "other" rejections.

## 2. Leakage characterisation (§5.2)

Figure `01_data_quality/pcc_signed_*.png` reports the signed Pearson correlation between each targeted
operation's leakage and the Hamming-weight of the manipulated value. The first-layer `ntt(c)`
butterfly correlates at 0.97 (upper coefficient) and 0.77 (lower); the response leaks correlate at 0.99
(`poly_add`), 0.88 (`reduce32`) and −0.93 (`poly_chknorm`). The signal-to-noise ratio, defined as
Var(class means)/E(class variance), is **1.3** for a generic reduced coefficient grouped by Hamming
weight and **12.2** for the five-class boundary problem at the abort index — well above the **0.34**
reported in the paper. This higher SNR is the reason every classifier below saturates with far fewer
profiling traces than the original work.

## 3. Recovering the challenge `c` (§5.3)

`c` is transformed by the eight-layer Cooley–Tukey NTT, and each butterfly leaks its operands.

**First layer.** The upper input coefficients `c[128:256]` are classified over {−1, 0, 1} and the lower
coefficients `c[0:128]` are separated as −1 versus {0, 1}. Figure `02_recover_c/16_four_op_curves.png(a)`
shows both recovered to **100%** — the upper by ~100 profiling traces and the lower by ~1000. The exact
reproduction of the paper's **Figure 4** (2×2: upper/lower accuracy curves with their confusion matrices)
is `02_recover_c/17_ntt_fig4.png`, whose confusion counts are provided as CSV; both matrices are perfect
diagonals.
Distinguishing **0 from 1** in the lower half is not possible at this layer, because their Hamming weights
differ by a single bit. A necessary observation for this dataset is that the first-layer leak is strong
only on RCoI rounds: `07_rcoi_vs_other_leak.png` shows a three-class Fisher ratio of ≈ 17.6 on RCoI rounds
against ≈ 10⁻⁴ on "other" rounds, so `c` recovery is confined to the RCoI rounds the attack requires.

**Deeper layers (Algorithm 5, §5.3.2).** The remaining lower 0/1 coefficients are resolved by propagating
through layers 2–8, where the Hamming weight of the butterfly output leaks at correlation 0.98–1.00 in
every layer (script `09`). An oracle consistency check confirms that a tolerance of ε = 3 makes every
coefficient distinguishable (script `10`, reproducing Fig. 5). Our implementation (twiddle-Hamming-weight
deduction refined by output-Hamming-weight relaxation, script `11`) recovers the upper half exactly and
the lower half to ≈ 97% per coefficient, so a challenge is fully correct in ≈ 24% of rounds.

**Blind verification.** A recovered challenge is accepted only if re-simulating the NTT reproduces the
measured intermediate Hamming weights; challenges that are inconsistent are discarded. This
self-consistency test — which never consults the key — yields **100.0% purity at every discard threshold**,
i.e. every retained challenge is exactly correct. This is the paper's discard-rather-than-tolerate
philosophy (Alg. 6) applied to `c`.

## 4. Recovering the response coefficient `z` (§5.4)

At the abort index `k`, the boundary value is classified into {+γ1, +γ1−1, −γ1, −γ1−1, other} from three
independent leaks with the Table-5 MLP (Dense-128 + ReLU, dropout 0.2, softmax; StandardScaler on the
profiling set). Figure `16_four_op_curves.png(b)` gives the recall against profiling-set size:
`reduce32` reaches **99.96%** (attack loss ratio 0.41, better than the paper's combined 0.457), `poly_add`
**99.7%**, and `poly_chknorm` ≈ 96% (this window is imperfectly sliced and serves only as an auxiliary
vote). Confusion matrices and confidence-threshold curves are in `03_recover_z/`; thresholding the softmax
confidence removes the residual RCoI→other confusion and drives the retained set to 100% precision, again
via discarding.

## 5. Output: `(c, z)` pairs and key recovery (§5.5)

`04_output_cz_pairs_s1/cz_pairs_D2.zip` contains **7 989 blind, fully-correct `(c, z)` pairs** covering all
1024 coefficient positions of `s1`. Each pair provides the recovered challenge `c` (256 values in {−1,0,1})
and the boundary value `z` at position `(poly_l, coeff_i)`; the true key `s1_true` is included so that any
pair can be checked against `⟨rot(c, i), s1⟩ ∈ [lb, ub]`, the interval implied by its class
(cls0 [0,β], cls1 [−1,β], cls2 [−β,−1], cls3 [−β,−2], β = 78).

The distribution ZIP is rebuilt with deterministic, identity-free metadata:
all entries use the fixed timestamp `1980-01-01 00:00:00`, the generic DOS
creation platform, no archive or entry comments, no Unix UID/GID, and no extra
fields. The six entry names and their uncompressed payload bytes are unchanged.

We verified the integer-programming formulation of Theorem 1 (scripts `13`/`14`): the boundary constraint
holds for the true `s1` on all 30 000 RCoI rounds without exception, and solving the resulting program
recovers all 1024 coefficients of `s1` in about two seconds per polynomial from 30 000 pairs. The program
is, however, pair-hungry — it requires on the order of 17 500 RCoI pairs (consistent with Table 3), and
fewer than ~8 000 do not pin `s1` uniquely. The blind front end here yields ~8 000 exact pairs, which is
sufficient for the more pair-efficient downstream method (target 7 000) but short of the integer program
itself; closing that gap requires the exact cross-layer Algorithm 5 (≈100% per-round `c` recovery).

## Re-plotting and files

All recovery-curve data is provided as CSV (`02_recover_c/16_four_op_curves.csv`) and re-plotted by
`16_plot_curves.ipynb`, which exposes a log/linear x-axis toggle so the figure can be rendered in the
paper's style (linear axis) or with the rise emphasised (log axis). The classifiers behind the curves are
the Table-5 MLP; LDA was used only for quick scans and plateaus ~0.04% below the MLP on the lower −1 task.

- `01_data_quality/` — signed-PCC panels (SNR in §2)
- `02_recover_c/` — recovery curves + CSV, confusion matrices, RCoI/other leak contrast, Algorithm-5 summary
- `03_recover_z/` — reduce32 / add / chknorm confusion matrices, confidence-threshold and profiling-size curves
- `04_output_cz_pairs_s1/` — the `(c, z)` pairs, `s1_true`, and the colleague zip
- `code/` — scripts 00–16 (extraction → PCC → per-operation recovery → Algorithm 5 → export → ILP → figures)

## Portable path configuration

The scripts do not contain user names, home directories, or fixed laboratory
storage paths. `code/path_config.py` uses package-relative defaults and accepts
the following environment-variable overrides:

| Variable | Resource |
|---|---|
| `REJ_SCA_PACKAGE_ROOT` | Package/work root; defaults to the directory containing `code/` |
| `REJ_SCA_SUPPORT_ROOT` | Directory containing shared helpers such as the required `sca_utils.py`; defaults to `code/` |
| `REJ_SCA_ETS_ROOT` | Raw LeCroy ETS input directory; defaults to `data/ets/` |
| `REJ_SCA_TRACE_ROOT` | Raw NumPy trace directory; defaults to `data/traces/` |
| `REJ_SCA_EXTRACTED_ROOT` | Extracted NTT/add/chknorm arrays; defaults to `data/traces/rej_2026_ntt_add_chk/` |
| `REJ_SCA_LABEL_ROOT` | `labels_45k.csv`, `c_rej_i32.bin`, and related labels; defaults to `data/labels/` |
| `REJ_SCA_RESULTS_ROOT` | Models, intermediate arrays, and figures; defaults to `results/` |
| `REJ_SCA_MLDSA_SOURCE_ROOT` | Directory containing `ntt.c` and `known_keys.c`; defaults to `external/dilithium_rej_filter/` |

Example for PowerShell:

```powershell
$env:REJ_SCA_ETS_ROOT = "<path-to-raw-ets>"
$env:REJ_SCA_TRACE_ROOT = "<path-to-trace-arrays>"
$env:REJ_SCA_EXTRACTED_ROOT = "<path-to-extracted-arrays>"
$env:REJ_SCA_LABEL_ROOT = "<path-to-label-files>"
$env:REJ_SCA_RESULTS_ROOT = "<path-to-results>"
$env:REJ_SCA_MLDSA_SOURCE_ROOT = "<path-to-dilithium_rej_filter>"

python code\00_extract_ntt_add_chknorm.py --help
```
