#!/usr/bin/env python3
"""07: First-layer NTT(c) attack, RCoI-only  (supersedes 06).

WHY 06 FAILED (upper acc3 0.91 / lower 0.81):
  The 45k split mixes 15000 OTHER rows (labels cls=4, rows 30000:45000). Those
  rows carry NO first-layer NTT(c) leak: max 3-class Fisher over all 200 samples
  is ~0.001 (vs ~10-15 for RCoI); every c-class has identical mean ~19, std ~11.
  Their extracted ntt_c window is decorrelated from c_rej (misaligned block).
  That unusable 1/3 of train+attack pinned recall(+-1) at ~0.694, acc3 at 0.91.

FIX (this script):
  (1) restrict NTT(c) to RCoI rows (cls<4) -- the rounds we need c for;
  (2) crop must span BOTH POIs: the a[j+128] store ~sample 68 (separates -1) AND
      the resolve region ~116-123 (separates +1 from 0; at 68 alone +1~=0).

Layer-0 CT butterfly j (j=0..127): len=128, zeta=zetas[1]=25847.
  t = mont(zeta*c[j+128]) in {-3572223,0,+3572223};  a[j]=c[j]+t; a[j+128]=c[j]-t.
  window j -> lower c[j] (weak, dominated by t) and upper c[j+128] (strong).
  Each c-coeff probed once in layer 1 (i<128 lower, i>=128 upper).

Targets (TCHES 5.3.1): upper {-1,0,1} 100%; lower -1 vs {0,1} 100%; lower 0 vs 1 hard.
Split: split_seed20260819 (trace-level) INTERSECT RCoI. Train fits; cal+attack held out.
Model: TCHES Table 5 MLP (Dense128 ReLU L2=.01, Dropout .2, softmax, Adam, 60ep, batch512,
StandardScaler train-only) + LDA cross-check. GPU 3.
"""
from __future__ import annotations
import json, os, sys
os.environ.setdefault("CUDA_VISIBLE_DEVICES", "3")
os.environ.setdefault("TF_CPP_MIN_LOG_LEVEL", "2")
os.environ.setdefault("TF_ENABLE_ONEDNN_OPTS", "0")
import matplotlib; matplotlib.use("Agg")
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis as LDA
from sklearn.metrics import classification_report, confusion_matrix
from sklearn.preprocessing import StandardScaler

from path_config import (
    EXTRACTED_TRACE_ROOT,
    LABEL_ROOT,
    PACKAGE_ROOT,
    RESULTS_ROOT,
    SUPPORT_CODE_ROOT,
)

CODE_DIR = SUPPORT_CODE_ROOT
HERE = PACKAGE_ROOT; OUT = RESULTS_ROOT
EX = EXTRACTED_TRACE_ROOT
LAB_DIR = LABEL_ROOT
C_BIN = os.path.join(LAB_DIR, "c_rej_i32.bin")
N0, N = 128, 256
SEED, EPOCHS, BATCH = 20260819, 60, 512
CROP_UP = (56, 132)   # store(~68) + resolve(~116-123)
CROP_LO = (0, 200)    # full; lower -1 leaks at store ~164-178, 0-vs-1 unrecoverable in L1
CN = ["-1", "0", "+1"]


def _tf():
    import tensorflow as tf
    tf.keras.utils.set_random_seed(SEED)
    for g in tf.config.list_physical_devices("GPU"):
        try:
            tf.config.experimental.set_memory_growth(g, True)
        except Exception:
            pass
    return tf


def build_mlp(tf, n_feat):
    reg = tf.keras.regularizers.l2(0.01)
    m = tf.keras.Sequential([
        tf.keras.layers.Input(shape=(n_feat,)),
        tf.keras.layers.Dense(128, activation="relu", kernel_regularizer=reg),
        tf.keras.layers.Dropout(0.2),
        tf.keras.layers.Dense(3, activation="softmax")])
    m.compile(optimizer="adam", loss="sparse_categorical_crossentropy", metrics=["accuracy"])
    return m


def balance3(X, y, seed=SEED):
    rng = np.random.RandomState(seed)
    keep = max(int((y == -1).sum()), int((y == 1).sum()))
    parts = []
    for val, cap in ((-1, None), (1, None), (0, keep)):
        idx = np.flatnonzero(y == val)
        if cap is not None and idx.size > cap:
            idx = rng.choice(idx, cap, replace=False)
        parts.append(idx)
    sel = np.concatenate(parts); rng.shuffle(sel)
    return X[sel], y[sel]


def metrics(name, yt, pred, n_tr):
    acc3 = float((pred == yt).mean())
    cm = confusion_matrix(yt, pred, labels=[-1, 0, 1])
    rec = {int(cc): (float((pred[yt == cc] == cc).mean()) if (yt == cc).any() else None) for cc in (-1, 0, 1)}
    acc2 = float(((pred == -1) == (yt == -1)).mean())
    rec2 = float((pred[yt == -1] == -1).mean()) if (yt == -1).any() else None
    pm = pred.reshape(n_tr, N0); tm = yt.reshape(n_tr, N0)
    all128 = float((pm == tm).all(1).mean()); pertr = float((pm == tm).mean(1).mean())
    print("  [%s] acc3=%.4f rec(-1/0/+1)=%.3f/%.3f/%.3f acc2(-1vs{0,1})=%.4f rec2(-1)=%.3f all128=%.4f"
          % (name, acc3, rec[-1], rec[0], rec[1], acc2, rec2, all128), flush=True)
    return dict(acc3=acc3, recall=rec, acc2_m1=acc2, recall2_m1=rec2,
                per_trace_all128=all128, per_trace_mean=pertr, confusion=cm.tolist())


def plot_cm(cm, title, path):
    cm = np.array(cm, float); row = cm / np.clip(cm.sum(1, keepdims=True), 1, None)
    fig, ax = plt.subplots(1, 2, figsize=(8.5, 3.6))
    for a, M, t in ((ax[0], cm, "counts"), (ax[1], row, "row-normalized")):
        a.imshow(M, cmap="Blues", vmin=0, vmax=(1 if t != "counts" else None))
        a.set_title(t); a.set_xticks(range(3)); a.set_yticks(range(3))
        a.set_xticklabels(CN); a.set_yticklabels(CN); a.set_xlabel("pred"); a.set_ylabel("true")
        for i in range(3):
            for j in range(3):
                a.text(j, i, (("%d" % int(M[i, j])) if t == "counts" else ("%.2f" % M[i, j])),
                       ha="center", va="center", fontsize=8)
    fig.suptitle(title); fig.tight_layout(); fig.savefig(path, dpi=140); plt.close(fig)


def jsonable(o):
    if isinstance(o, dict):
        return {str(k): jsonable(v) for k, v in o.items()}
    if isinstance(o, (list, tuple)):
        return [jsonable(v) for v in o]
    if isinstance(o, np.integer):
        return int(o)
    if isinstance(o, np.floating):
        return float(o)
    if isinstance(o, np.ndarray):
        return o.tolist()
    return o


def main():
    os.makedirs(OUT, exist_ok=True)
    lab = pd.read_csv(os.path.join(LAB_DIR, "labels_45k.csv"))
    cls = lab["cls"].values
    spl = np.load(os.path.join(OUT, "split_seed20260819.npz")); split = spl["split"]
    rcoi = cls < 4
    tr = np.flatnonzero((split == "train") & rcoi)
    ca = np.flatnonzero((split == "cal") & rcoi)
    te = np.flatnonzero((split == "attack") & rcoi)
    assert tr.max() < 30000 and te.max() < 30000  # RCoI rows live in 0:30000
    print("RCoI traces  train %d  cal %d  attack %d" % (len(tr), len(ca), len(te)), flush=True)

    ntt = np.load(os.path.join(EX, "ntt_c_reject_n45000.npy"), mmap_mode="r")
    L0 = np.asarray(ntt[:30000, :N0, :])          # (30000,128,200) int8, RCoI block
    c = np.fromfile(C_BIN, dtype=np.int32).reshape(-1, N)[:30000]
    print("L0", L0.shape, L0.dtype, "c uniq", np.unique(c), flush=True)

    tf = _tf(); print("TF", tf.__version__, "GPU", tf.config.list_physical_devices("GPU"), flush=True)
    summary = {"crop_upper": CROP_UP, "crop_lower": CROP_LO,
               "n_train": len(tr), "n_cal": len(ca), "n_attack": len(te)}

    for side, crop in (("upper", CROP_UP), ("lower", CROP_LO)):
        lo, hi = crop; w = hi - lo
        print("\n######## %s  crop%s (w=%d) ########" % (side, crop, w), flush=True)

        def pack(idx):
            X = L0[idx][:, :, lo:hi].reshape(-1, w).astype(np.float32)
            y = (c[idx][:, N0:] if side == "upper" else c[idx][:, :N0]).reshape(-1)
            return X, y
        Xtr, ytr = pack(tr); Xca, yca = pack(ca); Xte, yte = pack(te)
        print("raw train counts", {int(v): int((ytr == v).sum()) for v in (-1, 0, 1)}, flush=True)

        sc = StandardScaler().fit(Xtr)
        Xtr_s, Xca_s, Xte_s = sc.transform(Xtr), sc.transform(Xca), sc.transform(Xte)

        # --- LDA cross-check (fast, unbalanced) ---
        lda = LDA().fit(Xtr_s, ytr)
        summary.setdefault(side, {})["lda_attack"] = metrics("%s LDA attack" % side, yte, lda.predict(Xte_s), len(te))

        # --- TCHES MLP (balanced train) ---
        Xb, yb = balance3(Xtr_s, ytr)
        print("balanced train", {int(v): int((yb == v).sum()) for v in (-1, 0, 1)}, "n", len(yb), flush=True)
        model = build_mlp(tf, w)
        hist = model.fit(Xb, (yb + 1).astype(np.int32), epochs=EPOCHS, batch_size=BATCH, verbose=2, shuffle=True)
        model.save(os.path.join(OUT, "07_ntt_c_%s.keras" % side))
        proba = model.predict(Xte_s, batch_size=8192, verbose=0)
        np.save(os.path.join(OUT, "07_ntt_c_%s_proba_attack.npy" % side), proba.astype(np.float32))
        pred = proba.argmax(1).astype(np.int32) - 1
        summary[side]["mlp_attack"] = metrics("%s MLP attack" % side, yte, pred, len(te))
        pred_ca = model.predict(Xca_s, batch_size=8192, verbose=0).argmax(1).astype(np.int32) - 1
        summary[side]["mlp_cal"] = metrics("%s MLP cal   " % side, yca, pred_ca, len(ca))
        print("full 3-class report (MLP attack):")
        print(classification_report(yte, pred, labels=[-1, 0, 1], target_names=CN, digits=4))
        plot_cm(summary[side]["mlp_attack"]["confusion"], "07 NTT(c) %s (RCoI, MLP attack)" % side,
                os.path.join(OUT, "07_ntt_c_%s_confusion.png" % side))
        fig, ax = plt.subplots(figsize=(5.5, 3.2)); ax.plot(hist.history["accuracy"])
        ax.set_title("07 ntt_c %s train acc" % side); fig.tight_layout()
        fig.savefig(os.path.join(OUT, "07_ntt_c_%s_history.png" % side), dpi=140); plt.close(fig)

    with open(os.path.join(OUT, "07_ntt_c_summary.json"), "w") as f:
        json.dump(jsonable(summary), f, indent=2)
    print("\nDONE 07", flush=True)


if __name__ == "__main__":
    main()
