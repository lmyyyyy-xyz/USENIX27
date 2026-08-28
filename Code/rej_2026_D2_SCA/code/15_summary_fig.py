#!/usr/bin/env python3
"""TCHES-style summary of the rej_2026 D2 blind (c,z)->s1 pipeline."""
import os
import matplotlib; matplotlib.use("Agg")
import matplotlib.pyplot as plt
import numpy as np

from path_config import RESULTS_ROOT

os.makedirs(RESULTS_ROOT, exist_ok=True)
OUT = os.path.join(RESULTS_ROOT, "15_pipeline_summary.png")

fig, ax = plt.subplots(1, 3, figsize=(13.5, 3.7))

# Panel A: per-layer NTT HW leakage (feasibility, script 09) -> Algorithm 5 viability
L = np.arange(8)
out = [1.00, 0.99, 0.99, 0.98, 0.98, 0.98, 0.98, 0.98]
up = [0.96, 0.95, 0.97, 0.96, 0.95, 0.95, 0.95, 0.95]
tw = [0.98, 0.94, 0.90, 0.81, 0.58, 0.66, 0.72, 0.70]
ax[0].plot(L, out, "-o", label="butterfly output HW", lw=2)
ax[0].plot(L, up, "-s", label="upper-load HW", lw=1.5)
ax[0].plot(L, tw, "-^", label="twiddle-product HW", lw=1.5)
ax[0].set_ylim(0.5, 1.02); ax[0].set_xlabel("NTT layer"); ax[0].set_ylabel("|PCC|  (trace vs HW)")
ax[0].set_title("(a) NTT HW leakage per layer"); ax[0].legend(fontsize=8, loc="lower left"); ax[0].grid(alpha=0.3)

# Panel B: blind verification -> kept pairs & purity vs discard threshold (run 0)
thr = [0, 1, 2, 3, 5, 10]
kept = [938, 2618, 4167, 5135, 5854, 6021]
ax[1].bar(range(len(thr)), kept, color="#4C78A8", alpha=0.85)
ax[1].set_xticks(range(len(thr))); ax[1].set_xticklabels(thr)
ax[1].set_xlabel("discard threshold (max output-HW mismatch)"); ax[1].set_ylabel("pairs kept (per run)")
ax[1].set_title("(b) Blind verification: kept pairs")
axb = ax[1].twinx(); axb.plot(range(len(thr)), [100] * len(thr), "r--o", lw=2)
axb.set_ylim(90, 101); axb.set_ylabel("purity %  (vs key)", color="r"); axb.tick_params(axis="y", colors="r")
for i, k in enumerate(kept): ax[1].text(i, k + 60, str(k), ha="center", fontsize=7)

# Panel C: pipeline accuracy summary
labels = ["upper c\n{-1,0,1}", "lower c\nper-coeff", "z\n5-class", "verified\npair purity"]
vals = [100.0, 97.1, 99.96, 100.0]
cols = ["#54A24B", "#F58518", "#54A24B", "#E45756"]
b = ax[2].bar(labels, vals, color=cols, alpha=0.9)
ax[2].set_ylim(90, 101); ax[2].set_ylabel("accuracy / purity %")
ax[2].set_title("(c) Blind recovery accuracy")
for bar, v in zip(b, vals): ax[2].text(bar.get_x() + bar.get_width() / 2, v + 0.15, f"{v:g}", ha="center", fontsize=8)
ax[2].axhline(100, color="grey", ls=":", lw=0.8)

fig.suptitle("Rejected (c,z)->s1 blind SCA pipeline (D2): NTT-HW leakage -> Algorithm-5 c-recovery -> "
             "self-consistency verify (100% pure) -> ILP", fontsize=10)
fig.tight_layout(rect=[0, 0, 1, 0.95])
fig.savefig(OUT, dpi=145)
print("wrote", OUT)
