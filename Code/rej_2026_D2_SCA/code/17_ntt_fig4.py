#!/usr/bin/env python3
"""Exact TCHES Figure-4 clone for NTT(c) first-layer recovery (D2).

2x2: (a) upper accuracy vs profiling traces, (b) upper confusion {-1,0,1},
     (c) lower accuracy vs profiling traces, (d) lower confusion {-1} vs {0,1}.
Curves come from 16_four_op_curves.csv; confusion counts are (re)computed with the
Table-5 MLP on the full RCoI profiling set and saved to CSV so the author re-plots.
"""
import os
import numpy as np, pandas as pd, warnings; warnings.filterwarnings("ignore")
from sklearn.neural_network import MLPClassifier
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import confusion_matrix
import matplotlib; matplotlib.use("Agg"); import matplotlib.pyplot as plt

from path_config import EXTRACTED_TRACE_ROOT, LABEL_ROOT, RESULTS_ROOT

R = RESULTS_ROOT
EX = EXTRACTED_TRACE_ROOT
LAB = LABEL_ROOT
os.makedirs(R, exist_ok=True)
N0, N = 128, 256
lab = pd.read_csv(LAB + "/labels_45k.csv"); cls = lab["cls"].values
spl = np.load(R + "/split_seed20260819.npz"); split = spl["split"]
tr = np.flatnonzero((split == "train") & (cls < 4) & (np.arange(45000) < 30000))
tr = np.random.RandomState(0).choice(tr, 5000, replace=False)   # 5000 traces already give 100% (see curve)
te = np.flatnonzero((split == "attack") & (cls < 4) & (np.arange(45000) < 30000))
c = np.fromfile(LAB + "/c_rej_i32.bin", np.int32).reshape(-1, N)
ntt = np.load(EX + "/ntt_c_reject_n45000.npy", mmap_mode="r")


def fit_predict(side):
    lo, hi = (56, 132) if side == "upper" else (0, 200)
    Xtr = np.asarray(ntt[tr][:, :N0, lo:hi]).astype(np.float32).reshape(-1, hi - lo)
    Xte = np.asarray(ntt[te][:, :N0, lo:hi]).astype(np.float32).reshape(-1, hi - lo)
    ytr = (c[tr][:, N0:] if side == "upper" else c[tr][:, :N0]).reshape(-1)
    yte = (c[te][:, N0:] if side == "upper" else c[te][:, :N0]).reshape(-1)
    if side == "lower":
        ytr = (ytr == -1).astype(int); yte = (yte == -1).astype(int)   # -1 vs {0,1}
    sc = StandardScaler().fit(Xtr)
    m = MLPClassifier(hidden_layer_sizes=(128,), alpha=1e-2, max_iter=200,
                      early_stopping=True, n_iter_no_change=8, random_state=0).fit(sc.transform(Xtr), ytr)
    return yte, m.predict(sc.transform(Xte))


yu, pu = fit_predict("upper"); yl, pl = fit_predict("lower")
cmU = confusion_matrix(yu, pu, labels=[-1, 0, 1])
cmL = confusion_matrix(yl, pl, labels=[1, 0])          # 1 = (c==-1), 0 = {0,1}
# save confusion CSVs
pd.DataFrame(cmU, index=["true_-1", "true_0", "true_1"], columns=["pred_-1", "pred_0", "pred_1"]).to_csv(R + "/17_ntt_upper_confusion.csv")
pd.DataFrame(cmL, index=["true_-1", "true_{0,1}"], columns=["pred_-1", "pred_{0,1}"]).to_csv(R + "/17_ntt_lower_confusion.csv")
print("upper acc", (yu == pu).mean(), "\n", cmU, "\nlower acc", (yl == pl).mean(), "\n", cmL, flush=True)

df = pd.read_csv(R + "/16_four_op_curves.csv")
fig, ax = plt.subplots(2, 2, figsize=(9.5, 7))


def curve(a, col, title):
    d = df.dropna(subset=[col]); a.plot(d["n_traces"], d[col] * 100, "-o", color="C0")
    a.axhline(100, color="grey", ls=":", lw=0.8); a.set_xscale("log")
    a.set(xlabel="number of profiling traces", ylabel="accuracy %", ylim=(98.5, 100.15), title=title); a.grid(alpha=0.3)


def cmat(a, cm, labs, title):
    im = a.imshow(cm, cmap="Greys"); fig.colorbar(im, ax=a, fraction=0.046)
    a.set_xticks(range(len(labs))); a.set_yticks(range(len(labs))); a.set_xticklabels(labs); a.set_yticklabels(labs)
    a.set(xlabel="predicted label", ylabel="true label", title=title)
    thr = cm.max() / 2
    for i in range(cm.shape[0]):
        for j in range(cm.shape[1]):
            a.text(j, i, f"{cm[i, j]}", ha="center", va="center", color="white" if cm[i, j] > thr else "black", fontsize=9)


curve(ax[0, 0], "ntt_c_upper_3class", "(a) upper input coefficient")
cmat(ax[0, 1], cmU, ["-1", "0", "1"], "(b) upper confusion  {-1,0,1}")
curve(ax[1, 0], "ntt_c_lower_m1_vs_rest", "(c) lower input coefficient")
cmat(ax[1, 1], cmL, ["-1", "{0,1}"], "(d) lower confusion  {-1} vs {0,1}")
fig.suptitle("Figure 4 (reproduction) — attack results of the first-layer NTT (D2)")
fig.tight_layout(rect=[0, 0, 1, 0.96]); fig.savefig(R + "/17_ntt_fig4.png", dpi=150)
print("wrote 17_ntt_fig4.png + confusion CSVs", flush=True)
