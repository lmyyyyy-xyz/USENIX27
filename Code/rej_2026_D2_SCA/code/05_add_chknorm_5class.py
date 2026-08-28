#!/usr/bin/env python3
"""5-class MLP on add(z) at k and chknorm last pulse.

Same split as reduce32 (split_seed20260819.npz). TCHES Table 5.
Runs on CPU so NTT(c) can take GPU 3 in parallel.
"""
from __future__ import annotations

import json
import os
import sys

os.environ["CUDA_VISIBLE_DEVICES"] = ""
os.environ.setdefault("TF_CPP_MIN_LOG_LEVEL", "2")
os.environ.setdefault("TF_ENABLE_ONEDNN_OPTS", "0")

import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
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
sys.path.insert(0, CODE_DIR)
from sca_utils import corr_fast  # noqa: E402

LABEL_DIR = LABEL_ROOT
EX_DIR = EXTRACTED_TRACE_ROOT
OUT_DIR = RESULTS_ROOT
N_EXPECT = 45000
N_CLASS = 5
SEED = 20260819
EPOCHS = 60
BATCH = 512
CLASS_NAMES = ["+g1", "+g1-1", "-g1", "-g1-1", "other"]
CLASS_TEX = [r"$+\gamma_1$", r"$+\gamma_1-1$", r"$-\gamma_1$", r"$-\gamma_1-1$", "other"]


def _tf():
    import tensorflow as tf

    tf.keras.utils.set_random_seed(SEED)
    return tf


def downsample_other(idx, y, seed=SEED):
    rng = np.random.RandomState(seed)
    rcoi = idx[y[idx] < 4]
    other = idx[y[idx] == 4]
    n_target = min(int((y[idx] == c).sum()) for c in range(4))
    if other.size > n_target:
        other = rng.choice(other, n_target, replace=False)
    out = np.concatenate([rcoi, other])
    rng.shuffle(out)
    return out


def build_mlp(tf, n_feat, n_classes=N_CLASS):
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


def threshold_curve(y, proba):
    pred = proba.argmax(axis=1)
    conf = proba.max(axis=1)
    n_all = int((y < 4).sum())
    ts = np.unique(np.concatenate([np.linspace(0.20, 0.95, 16), np.linspace(0.96, 0.999, 40), [0.9995, 0.9999, 1.0]]))
    rows = []
    for t in ts:
        keep = (pred < 4) & (conf >= t)
        n_pre = int(keep.sum())
        n_correct = int((keep & (y == pred)).sum())
        prec = n_correct / n_pre if n_pre else None
        loss = (n_all - n_correct) / n_all if n_all else None
        rows.append(dict(t=float(t), n_pre=n_pre, n_correct=n_correct, n_all=n_all, precision=prec, loss_ratio=loss))
    return pd.DataFrame(rows)


def first_perfect(curve):
    ok = curve[curve["precision"].fillna(0) >= 1.0 - 1e-12]
    return None if len(ok) == 0 else float(ok.iloc[0]["t"])


def plot_confusion(cm, title, path):
    fig, ax = plt.subplots(1, 2, figsize=(10.5, 4.2))
    row = cm.astype(np.float64)
    row = np.divide(row, row.sum(1, keepdims=True), out=np.zeros_like(row), where=row.sum(1, keepdims=True) > 0)
    ax[0].imshow(cm, cmap="Blues")
    ax[1].imshow(row, cmap="Blues", vmin=0, vmax=1)
    ax[0].set_title("counts")
    ax[1].set_title("row-normalized")
    for a, M in zip(ax, (cm, row)):
        a.set_xticks(range(5))
        a.set_yticks(range(5))
        a.set_xticklabels(CLASS_TEX, rotation=30, ha="right")
        a.set_yticklabels(CLASS_TEX)
        a.set_xlabel("predicted")
        a.set_ylabel("true")
        for i in range(5):
            for j in range(5):
                txt = str(int(M[i, j])) if a is ax[0] else f"{M[i, j]:.2f}"
                a.text(j, i, txt, ha="center", va="center", fontsize=8)
    fig.suptitle(title)
    fig.tight_layout()
    fig.savefig(path, dpi=140)
    plt.close(fig)


def plot_threshold(cal_c, atk_c, t_star, path, name):
    fig, ax = plt.subplots(figsize=(7.2, 4.0))
    ax.plot(cal_c["t"], cal_c["precision"], label="cal RCoI precision")
    ax.plot(atk_c["t"], atk_c["precision"], label="attack RCoI precision")
    ax.plot(cal_c["t"], 1.0 - cal_c["loss_ratio"], label="cal 1-loss")
    ax.plot(atk_c["t"], 1.0 - atk_c["loss_ratio"], label="attack 1-loss")
    if t_star is not None:
        ax.axvline(t_star, color="k", ls="--", lw=1, label=f"cal t*={t_star:.4f}")
    ax.set_ylim(-0.02, 1.05)
    ax.set_xlabel("softmax confidence threshold")
    ax.legend(fontsize=8)
    ax.set_title(f"{name} 5-class — threshold / loss (TCHES §5.4.1)")
    fig.tight_layout()
    fig.savefig(path, dpi=140)
    plt.close(fig)


def metrics_block(y, proba, tag):
    pred = proba.argmax(axis=1)
    acc = float((pred == y).mean())
    cm = confusion_matrix(y, pred, labels=list(range(5)))
    rcoi_pred = pred < 4
    rcoi_true = y < 4
    rcoi_prec = float((pred[rcoi_pred] == y[rcoi_pred]).mean()) if rcoi_pred.any() else None
    rcoi_rec = float((pred[rcoi_true] == y[rcoi_true]).mean()) if rcoi_true.any() else None
    print(f"\n==== {tag} ====", flush=True)
    print("acc", acc, "RCoI-pred precision", rcoi_prec, "RCoI exact recall", rcoi_rec)
    print(classification_report(y, pred, target_names=CLASS_NAMES, digits=4))
    print("confusion\n", cm)
    return dict(acc=acc, rcoi_precision_unfiltered=rcoi_prec, rcoi_exact_recall_unfiltered=rcoi_rec, confusion=cm.tolist())


def run_one(tf, name, X, y, idx_tr, idx_ca, idx_te):
    scaler = StandardScaler()
    Xtr = scaler.fit_transform(X[idx_tr].astype(np.float64))
    Xca = scaler.transform(X[idx_ca].astype(np.float64))
    Xte = scaler.transform(X[idx_te].astype(np.float64))
    model = build_mlp(tf, Xtr.shape[1])
    hist = model.fit(Xtr, y[idx_tr], epochs=EPOCHS, batch_size=BATCH, verbose=2, shuffle=True)
    model.save(os.path.join(OUT_DIR, f"05_{name}.keras"))
    proba_ca = model.predict(Xca, batch_size=2048, verbose=0)
    proba_te = model.predict(Xte, batch_size=2048, verbose=0)
    np.save(os.path.join(OUT_DIR, f"05_{name}_proba_attack.npy"), proba_te.astype(np.float32))
    blk = metrics_block(y[idx_te], proba_te, f"{name} ATTACK")
    plot_confusion(np.array(blk["confusion"]), f"{name} attack 5-class", os.path.join(OUT_DIR, f"05_{name}_confusion.png"))
    cal_c = threshold_curve(y[idx_ca], proba_ca)
    atk_c = threshold_curve(y[idx_te], proba_te)
    cal_c.to_csv(os.path.join(OUT_DIR, f"05_{name}_threshold_cal.csv"), index=False)
    atk_c.to_csv(os.path.join(OUT_DIR, f"05_{name}_threshold_attack.csv"), index=False)
    t_star = first_perfect(cal_c)
    plot_threshold(cal_c, atk_c, t_star, os.path.join(OUT_DIR, f"05_{name}_threshold.png"), name)
    atk_at = None
    if t_star is not None:
        row = atk_c.iloc[(atk_c["t"] - t_star).abs().argmin()]
        atk_at = {k: (None if pd.isna(v) else v) for k, v in row.to_dict().items()}
        print(f"{name} cal t*={t_star:.6f} attack@t* prec={atk_at['precision']} loss={atk_at['loss_ratio']}", flush=True)
    else:
        print(f"{name} cal never 100% RCoI precision; attack first perfect t={first_perfect(atk_c)}", flush=True)
    fig, ax = plt.subplots(figsize=(5.5, 3.2))
    ax.plot(hist.history["accuracy"], label="train acc")
    ax.plot(hist.history["loss"], label="train loss")
    ax.legend()
    ax.set_title(name)
    fig.tight_layout()
    fig.savefig(os.path.join(OUT_DIR, f"05_{name}_history.png"), dpi=140)
    plt.close(fig)
    return dict(attack=blk, t_star_cal=t_star, attack_at_t_star=atk_at, n_feat=int(Xtr.shape[1]))


def jsonable(o):
    if isinstance(o, dict):
        return {str(k): jsonable(v) for k, v in o.items()}
    if isinstance(o, (list, tuple)):
        return [jsonable(v) for v in o]
    if isinstance(o, (np.integer,)):
        return int(o)
    if isinstance(o, (np.floating,)):
        return float(o)
    if isinstance(o, np.ndarray):
        return o.tolist()
    if o is None or isinstance(o, (str, int, float, bool)):
        return o
    return str(o)


def main():
    os.makedirs(OUT_DIR, exist_ok=True)
    lab = pd.read_csv(os.path.join(LABEL_DIR, "labels_45k.csv"))
    y = lab["cls"].to_numpy(dtype=np.int32)
    k = lab["k"].to_numpy(dtype=np.int32)
    assert len(y) == N_EXPECT
    spl = np.load(os.path.join(OUT_DIR, "split_seed20260819.npz"))
    split = spl["split"]
    print("split", pd.Series(split).value_counts().to_dict(), flush=True)
    idx_tr = downsample_other(np.flatnonzero(split == "train"), y, seed=SEED)
    idx_ca = np.flatnonzero(split == "cal")
    idx_te = np.flatnonzero(split == "attack")
    print("train balanced", {c: int((y[idx_tr] == c).sum()) for c in range(5)}, flush=True)

    add = np.load(os.path.join(EX_DIR, "add_z_reject_n45000.npy"), mmap_mode="r")
    chk = np.load(os.path.join(EX_DIR, "chknorm_z_reject_at_k_n45000.npy"), mmap_mode="r")
    Xadd = np.empty((N_EXPECT, add.shape[2]), dtype=np.int8)
    for i in range(N_EXPECT):
        Xadd[i] = add[i, int(k[i])]
    Xchk = np.asarray(chk)

    hw = np.fromfile(os.path.join(LABEL_DIR, "z_target_hw.bin"), dtype=np.uint8)
    other = y == 4
    rho_chk_o = corr_fast(Xchk[other].astype(np.float64), hw[other].astype(np.float64).reshape(-1, 1))[0]
    rho_add_o = corr_fast(Xadd[other].astype(np.float64), hw[other].astype(np.float64).reshape(-1, 1))[0]
    print(
        "OTHER-only PCC chknorm last",
        float(np.nanmax(np.abs(rho_chk_o))),
        "add@k",
        float(np.nanmax(np.abs(rho_add_o))),
        flush=True,
    )

    tf = _tf()
    print("TF", tf.__version__, "CPU-only", flush=True)
    summary = {"split": "split_seed20260819.npz", "ops": {}}
    summary["ops"]["add"] = run_one(tf, "add", Xadd, y, idx_tr, idx_ca, idx_te)
    summary["ops"]["chknorm"] = run_one(tf, "chknorm", Xchk, y, idx_tr, idx_ca, idx_te)
    with open(os.path.join(OUT_DIR, "05_add_chknorm_summary.json"), "w") as f:
        json.dump(jsonable(summary), f, indent=2)
    print("DONE 05", flush=True)


if __name__ == "__main__":
    main()
