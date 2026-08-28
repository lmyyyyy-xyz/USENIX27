#!/usr/bin/env python3
"""Recovery vs profiling-set size for the four targeted operations (D2).

NTT(c): LDA on layer-0 windows, two lines (upper c[128:256] 3-class, lower c[0:128] -1 vs {0,1}).
z ops (reduce32 / poly_add / poly_chknorm): TCHES Table-5 MLP (Dense-128 ReLU, dropout, softmax),
5-class, metric = RCoI boundary-class recall.  MLP (not LDA) so the curves climb toward 100%.

Writes the curve DATA to results/16_four_op_curves.csv (author re-plots via 16_plot_curves.ipynb).
"""
import os, time, numpy as np, pandas as pd, warnings; warnings.filterwarnings("ignore")
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis as LDA
from sklearn.neural_network import MLPClassifier
from sklearn.preprocessing import StandardScaler
import matplotlib; matplotlib.use("Agg"); import matplotlib.pyplot as plt

from path_config import EXTRACTED_TRACE_ROOT, LABEL_ROOT, RESULTS_ROOT

R = RESULTS_ROOT
EX = EXTRACTED_TRACE_ROOT
LAB = LABEL_ROOT
os.makedirs(R, exist_ok=True)
N0, N = 128, 256
SIZES = [50, 100, 200, 500, 1000, 2000, 5000, 10000, 20000, 30000]
NREP = 2

lab = pd.read_csv(LAB + "/labels_45k.csv"); cls = lab["cls"].values; kcol = lab["k"].values.astype(int)
spl = np.load(R + "/split_seed20260819.npz"); split = spl["split"]
tr_all = np.flatnonzero(split == "train"); te_all = np.flatnonzero(split == "attack")
rcoi = cls < 4
c = np.fromfile(LAB + "/c_rej_i32.bin", np.int32).reshape(-1, N)


def extract_at_k(path, cache):
    if os.path.isfile(cache):
        return np.load(cache, mmap_mode="r")
    A = np.load(path, mmap_mode="r"); n, W, t = A.shape; X = np.empty((n, t), np.int8)
    for i in range(n):
        X[i] = A[i, min(int(kcol[i]), W - 1)]
    np.save(cache, X); return X


def ntt_curve(side):
    ntt = np.load(EX + "/ntt_c_reject_n45000.npy", mmap_mode="r")
    lo, hi = (56, 132) if side == "upper" else (0, 200)
    trR = tr_all[rcoi[tr_all] & (tr_all < 30000)]; teR = te_all[rcoi[te_all] & (te_all < 30000)]
    Xte = np.asarray(ntt[teR][:, :N0, lo:hi]).astype(np.float32).reshape(-1, hi - lo)
    yte = (c[teR][:, N0:] if side == "upper" else c[teR][:, :N0]).reshape(-1)
    out = []
    for n in SIZES:
        rep = []
        for s in range(NREP):
            sub = np.random.RandomState(s).choice(trR, min(n, len(trR)), replace=False)
            Xtr = np.asarray(ntt[sub][:, :N0, lo:hi]).astype(np.float32).reshape(-1, hi - lo)
            ytr = (c[sub][:, N0:] if side == "upper" else c[sub][:, :N0]).reshape(-1)
            sc = StandardScaler().fit(Xtr); m = LDA().fit(sc.transform(Xtr), ytr)
            pr = m.predict(sc.transform(Xte))
            rep.append((pr == yte).mean() if side == "upper" else ((pr == -1) == (yte == -1)).mean())
        out.append(float(np.mean(rep))); print(f"  ntt {side} n={n}: {out[-1]:.4f}", flush=True)
    return out


def z_curve(Xall, name):
    Xte = np.asarray(Xall[te_all]).astype(np.float32); rmask = rcoi[te_all]; ytrue = cls[te_all[rmask]]
    out = []
    for n in SIZES:
        rep = []
        for s in range(NREP):
            sub = np.random.RandomState(s).choice(tr_all, min(n, len(tr_all)), replace=False)
            Xs = np.asarray(Xall[sub]).astype(np.float32)
            sc = StandardScaler().fit(Xs)
            clf = MLPClassifier(hidden_layer_sizes=(128,), alpha=1e-2, max_iter=200,
                                early_stopping=True, n_iter_no_change=8, random_state=s)
            clf.fit(sc.transform(Xs), cls[sub])
            pr = clf.predict(sc.transform(Xte))[rmask]
            rep.append((pr == ytrue).mean())
        out.append(float(np.mean(rep))); print(f"  {name} n={n}: {out[-1]:.4f}", flush=True)
    return out


def main():
    t0 = time.time()
    up = ntt_curve("upper"); lo = ntt_curve("lower")
    Xr = np.load(R + "/X_at_k_reject_int8.npy", mmap_mode="r")
    Xa = extract_at_k(EX + "/add_z_reject_n45000.npy", R + "/X_at_k_add_int8.npy")
    Xc = np.load(EX + "/chknorm_z_reject_at_k_n45000.npy", mmap_mode="r")
    red = z_curve(Xr, "reduce32"); add = z_curve(Xa, "add"); chk = z_curve(Xc, "chknorm")

    df = pd.DataFrame({"n_traces": SIZES, "ntt_c_upper_3class": up, "ntt_c_lower_m1_vs_rest": lo,
                       "reduce32_z_RCoI_recall": red, "poly_add_z_RCoI_recall": add,
                       "poly_chknorm_z_RCoI_recall": chk})
    df.to_csv(R + "/16_four_op_curves.csv", index=False)
    print("\nwrote 16_four_op_curves.csv\n", df.to_string(index=False), flush=True)

    fig, ax = plt.subplots(1, 2, figsize=(11, 3.8))
    ax[0].plot(SIZES, np.array(up) * 100, "-o", label="NTT(c) upper c[128:256]  {-1,0,1}")
    ax[0].plot(SIZES, np.array(lo) * 100, "-s", label="NTT(c) lower c[0:128]  -1 vs {0,1}")
    ax[0].set_xscale("log"); ax[0].set_ylim(98.5, 100.15); ax[0].set_title("(a) NTT(c) first-layer recovery")
    ax[1].plot(SIZES, np.array(red) * 100, "-o", label="reduce32(z)")
    ax[1].plot(SIZES, np.array(add) * 100, "-^", label="poly_add(z)")
    ax[1].plot(SIZES, np.array(chk) * 100, "-s", label="poly_chknorm(z)")
    ax[1].set_xscale("log"); ax[1].set_ylim(50, 101); ax[1].set_title("(b) z boundary-value recovery (MLP)")
    for a, yl in ((ax[0], "recovery accuracy %"), (ax[1], "RCoI 5-class recall %")):
        a.set_xlabel("profiling traces"); a.set_ylabel(yl); a.grid(alpha=0.3); a.legend(fontsize=8, loc="lower right")
    fig.suptitle("Recovery vs profiling-set size — four targeted operations (D2)")
    fig.tight_layout(rect=[0, 0, 1, 0.94]); fig.savefig(R + "/16_four_op_curves.png", dpi=150)
    print(f"done {time.time()-t0:.0f}s", flush=True)


if __name__ == "__main__":
    main()
