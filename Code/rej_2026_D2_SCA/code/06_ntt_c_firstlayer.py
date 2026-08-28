#!/usr/bin/env python3
"""First-layer NTT(c) profiled attack (TCHES §5.3.1).

Each butterfly window j leaks c[j] (lower) and c[j+128] (upper).
3-class {-1,0,1} on both; also report lower 2-class -1 vs {0,1}.
Trace split = same split_seed20260819 as z so pairs stay aligned.
Windows pooled across 128 butterflies; zeros subsampled in train.
GPU 3.
"""
from __future__ import annotations

import json
import os
import sys

os.environ.setdefault("CUDA_VISIBLE_DEVICES", "3")
os.environ.setdefault("TF_CPP_MIN_LOG_LEVEL", "2")
os.environ.setdefault("TF_ENABLE_ONEDNN_OPTS", "0")

import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt
import numpy as np
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
HERE = PACKAGE_ROOT
OUT_DIR = RESULTS_ROOT
EX_DIR = EXTRACTED_TRACE_ROOT
C_BIN = os.path.join(LABEL_ROOT, "c_rej_i32.bin")
N0, N = 128, 256
SEED = 20260819
EPOCHS = 60
BATCH = 512
C_NAMES = ["-1", "0", "+1"]


def _tf():
    import tensorflow as tf

    tf.keras.utils.set_random_seed(SEED)
    for g in tf.config.list_physical_devices("GPU"):
        try:
            tf.config.experimental.set_memory_growth(g, True)
        except Exception:
            pass
    return tf


def build_mlp(tf, n_feat, n_classes=3):
    reg = tf.keras.regularizers.l2(0.01)
    model = tf.keras.Sequential(
        [
            tf.keras.layers.Input(shape=(n_feat,)),
            tf.keras.layers.Dense(128, activation="relu", kernel_regularizer=reg),
            tf.keras.layers.Dropout(0.2),
            tf.keras.layers.Dense(n_classes, activation="softmax"),
        ]
    )
    model.compile(optimizer="adam", loss="sparse_categorical_crossentropy", metrics=["accuracy"])
    return model


def balance3(X, y, seed=SEED):
    """y in {-1,0,1}; downsample 0 to max(n_{-1}, n_{+1})."""
    rng = np.random.RandomState(seed)
    n_m = int((y == -1).sum())
    n_p = int((y == 1).sum())
    n0_keep = max(n_m, n_p)
    parts = []
    for val, cap in ((-1, None), (1, None), (0, n0_keep)):
        idx = np.flatnonzero(y == val)
        if cap is not None and idx.size > cap:
            idx = rng.choice(idx, cap, replace=False)
        parts.append(idx)
    sel = np.concatenate(parts)
    rng.shuffle(sel)
    return X[sel], y[sel]


def map01(y):
    return (y + 1).astype(np.int32)


def unmap01(yp):
    return yp.astype(np.int32) - 1


def plot_cm(cm, title, path, names=C_NAMES):
    fig, ax = plt.subplots(1, 2, figsize=(8.5, 3.6))
    row = cm.astype(np.float64)
    row = np.divide(row, row.sum(1, keepdims=True), out=np.zeros_like(row), where=row.sum(1, keepdims=True) > 0)
    ax[0].imshow(cm, cmap="Blues")
    ax[1].imshow(row, cmap="Blues", vmin=0, vmax=1)
    ax[0].set_title("counts")
    ax[1].set_title("row-normalized")
    for a, M in zip(ax, (cm, row)):
        a.set_xticks(range(len(names)))
        a.set_yticks(range(len(names)))
        a.set_xticklabels(names)
        a.set_yticklabels(names)
        a.set_xlabel("predicted")
        a.set_ylabel("true")
        for i in range(cm.shape[0]):
            for j in range(cm.shape[1]):
                txt = str(int(M[i, j])) if a is ax[0] else f"{M[i, j]:.2f}"
                a.text(j, i, txt, ha="center", va="center", fontsize=8)
    fig.suptitle(title)
    fig.tight_layout()
    fig.savefig(path, dpi=140)
    plt.close(fig)


def eval_side(name, y_true, proba):
    pred = unmap01(proba.argmax(1))
    acc = float((pred == y_true).mean())
    cm = confusion_matrix(y_true, pred, labels=[-1, 0, 1])
    print(f"\n==== {name} ====", flush=True)
    print("3-class acc", acc)
    print(classification_report(y_true, pred, labels=[-1, 0, 1], target_names=C_NAMES, digits=4))
    print("confusion [-1,0,1]\n", cm)
    # 2-class: -1 vs {0,1} (paper lower-coeff task)
    t_bin = (y_true == -1).astype(np.int32)
    p_bin = (pred == -1).astype(np.int32)
    acc2 = float((t_bin == p_bin).mean())
    rec_m1 = float((pred[y_true == -1] == -1).mean()) if (y_true == -1).any() else None
    print("2-class -1 vs {0,1} acc", acc2, "recall -1", rec_m1)
    return dict(acc3=acc, acc2_m1=acc2, recall_m1=rec_m1, confusion=cm.tolist())


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
    if o is None or isinstance(o, (str, int, float, bool)):
        return o
    return str(o)


def main():
    os.makedirs(OUT_DIR, exist_ok=True)
    spl = np.load(os.path.join(OUT_DIR, "split_seed20260819.npz"))
    split = spl["split"]
    idx_tr = np.flatnonzero(split == "train")
    idx_ca = np.flatnonzero(split == "cal")
    idx_te = np.flatnonzero(split == "attack")
    print("n train/cal/attack traces", len(idx_tr), len(idx_ca), len(idx_te), flush=True)

    ntt = np.load(os.path.join(EX_DIR, "ntt_c_reject_n45000.npy"), mmap_mode="r")
    layer0 = np.asarray(ntt[:, :N0, :])  # (45000, 128, 200)
    c = np.fromfile(C_BIN, dtype=np.int32).reshape(-1, N)
    print("layer0", layer0.shape, "c", c.shape, "unique", np.unique(c), flush=True)
    assert c.shape[0] == layer0.shape[0]

    def pack(idx, side):
        X = layer0[idx].reshape(-1, layer0.shape[2])
        if side == "upper":
            y = c[idx][:, N0:].reshape(-1)
        else:
            y = c[idx][:, :N0].reshape(-1)
        return X, y

    tf = _tf()
    print("TF", tf.__version__, "GPU", tf.config.list_physical_devices("GPU"), flush=True)
    summary = {}

    for side in ("upper", "lower"):
        print(f"\n######## {side} ########", flush=True)
        Xtr, ytr = pack(idx_tr, side)
        Xca, yca = pack(idx_ca, side)
        Xte, yte = pack(idx_te, side)
        print("raw train counts", {int(v): int((ytr == v).sum()) for v in (-1, 0, 1)}, flush=True)
        Xtr, ytr = balance3(Xtr, ytr)
        print("balanced train", {int(v): int((ytr == v).sum()) for v in (-1, 0, 1)}, "n", len(ytr), flush=True)
        scaler = StandardScaler()
        Xtr_s = scaler.fit_transform(Xtr.astype(np.float64))
        Xte_s = scaler.transform(Xte.astype(np.float64))
        model = build_mlp(tf, Xtr_s.shape[1], 3)
        hist = model.fit(Xtr_s, map01(ytr), epochs=EPOCHS, batch_size=BATCH, verbose=2, shuffle=True)
        model.save(os.path.join(OUT_DIR, f"06_ntt_c_{side}.keras"))
        proba = model.predict(Xte_s, batch_size=4096, verbose=0)
        np.save(os.path.join(OUT_DIR, f"06_ntt_c_{side}_proba_attack.npy"), proba.astype(np.float32))
        blk = eval_side(f"NTT(c) {side} ATTACK pooled butterflies", yte, proba)
        plot_cm(np.array(blk["confusion"]), f"NTT(c) first-layer {side}", os.path.join(OUT_DIR, f"06_ntt_c_{side}_confusion.png"))

        # per-trace: reshape attack to (n_tr, 128)
        n_te = len(idx_te)
        pred = unmap01(proba.argmax(1)).reshape(n_te, N0)
        true = yte.reshape(n_te, N0)
        per_ok = (pred == true).mean(axis=1)
        all_ok = float((pred == true).all(axis=1).mean())
        print(f"{side} per-trace mean coeff acc", float(per_ok.mean()), "all-128-correct", all_ok, flush=True)
        blk["per_trace_mean_acc"] = float(per_ok.mean())
        blk["per_trace_all128"] = all_ok
        summary[side] = blk
        fig, ax = plt.subplots(figsize=(5.5, 3.2))
        ax.plot(hist.history["accuracy"])
        ax.set_title(f"ntt_c {side} train acc")
        fig.tight_layout()
        fig.savefig(os.path.join(OUT_DIR, f"06_ntt_c_{side}_history.png"), dpi=140)
        plt.close(fig)

    with open(os.path.join(OUT_DIR, "06_ntt_c_summary.json"), "w") as f:
        json.dump(jsonable(summary), f, indent=2)
    print("DONE 06", flush=True)


if __name__ == "__main__":
    main()
