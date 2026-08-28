#!/usr/bin/env python3
"""D2 reduce32 5-class profiled attack (abort coefficient at window k).

Protocol from Zhou et al., TCHES 2025(4) 817–847 (not the eprint):
  Table 5 MLP: Dense 128 ReLU L2=0.01, Dropout 0.2, softmax, Adam
  §5.4.3 reduce32, 60 epochs, batch 512
  §5.4.1 loss_ratio = (N_all - N_pre) / N_all on the 4 RCoI values
  StandardScaler on features; POI from HW-PCC (train only)

X = sweep-0 reduce32 window k (legal sweep is alignment only, never 'other').
y = cls in {+γ1, +γ1-1, −γ1, −γ1-1, other rejected}.
Do not use labels_45k.csv 'split' (that is 70/15/15 by idx inside (cls, poly_l)).
4-class (RCoI-only) is an appendix diagnostic, not the main result.
"""
from __future__ import annotations

import json
import os
import sys
import time

os.environ.setdefault("CUDA_VISIBLE_DEVICES", "2")
os.environ.setdefault("TF_CPP_MIN_LOG_LEVEL", "2")
os.environ.setdefault("TF_ENABLE_ONEDNN_OPTS", "0")

import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis
from sklearn.metrics import classification_report, confusion_matrix
from sklearn.preprocessing import StandardScaler

from path_config import (
    LABEL_ROOT,
    PACKAGE_ROOT,
    RESULTS_ROOT,
    SUPPORT_CODE_ROOT,
    TRACE_ROOT,
)

CODE_DIR = SUPPORT_CODE_ROOT
HERE = PACKAGE_ROOT
sys.path.insert(0, CODE_DIR)
from sca_utils import corr_fast  # noqa: E402

TRACE_PATH = os.path.join(
    TRACE_ROOT,
    "reject1_legal_reduce_z_mldsa_o3_time_opt_44_100MHz_4.5e4_v2.npy",
)
LABEL_DIR = LABEL_ROOT
OUT_DIR = RESULTS_ROOT

N_WIN = 1024
N_SWEEP = 2
N_EXPECT = 45000
N_CLASS = 5
SEED = 20260819
EPOCHS = 60
BATCH = 512
CROP_HALF = 20  # samples around train-only PCC peak

CLASS_NAMES = ["+g1", "+g1-1", "-g1", "-g1-1", "other"]
CLASS_TEX = [r"$+\gamma_1$", r"$+\gamma_1-1$", r"$-\gamma_1$", r"$-\gamma_1-1$", "other"]


def _tf():
    import tensorflow as tf

    tf.keras.utils.set_random_seed(SEED)
    gpus = tf.config.list_physical_devices("GPU")
    for g in gpus:
        try:
            tf.config.experimental.set_memory_growth(g, True)
        except Exception:
            pass
    return tf


def extract_at_k(tr, k, sweep: int) -> np.ndarray:
    n, _, n_s = tr.shape
    off = sweep * N_WIN
    X = np.empty((n, n_s), dtype=np.int8)
    k = np.asarray(k, dtype=np.int32)
    t0 = time.time()
    for i in range(n):
        X[i] = tr[i, off + int(k[i])]
        if (i + 1) % 10000 == 0:
            print(f"  extract sweep={sweep} {i+1}/{n}  {time.time()-t0:.1f}s", flush=True)
    print(f"  extract sweep={sweep} done {time.time()-t0:.1f}s", flush=True)
    return X


def load_or_extract(path, tr, k, sweep: int) -> np.ndarray:
    if os.path.isfile(path):
        X = np.load(path)
        if X.shape == (N_EXPECT, tr.shape[2]) and X.dtype == np.int8:
            print("cache hit", path, X.shape, flush=True)
            return X
        print("cache mismatch, rebuilding", path, X.shape, X.dtype, flush=True)
    X = extract_at_k(tr, k, sweep)
    np.save(path, X)
    return X


def stratified_split(y, poly_l, seed=SEED, fracs=(0.70, 0.15, 0.15)):
    """70/15/15 inside each (cls, poly_l) bucket, shuffled (not idx-order)."""
    rng = np.random.RandomState(seed)
    split = np.empty(len(y), dtype=object)
    split[:] = ""
    for c in range(N_CLASS):
        for p in np.unique(poly_l[y == c]):
            ids = np.flatnonzero((y == c) & (poly_l == p))
            rng.shuffle(ids)
            n = len(ids)
            n_tr = int(round(n * fracs[0]))
            n_ca = int(round(n * fracs[1]))
            split[ids[:n_tr]] = "train"
            split[ids[n_tr : n_tr + n_ca]] = "cal"
            split[ids[n_tr + n_ca :]] = "attack"
    if np.any(split == ""):
        raise RuntimeError("unassigned split rows")
    return split


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


def crop_around(X, poi: int, half: int):
    lo = max(0, poi - half)
    hi = min(X.shape[1], poi + half + 1)
    return X[:, lo:hi], lo, hi


def snr_per_sample(X, y):
    """Between-class SNR: var(class means) / mean(class vars)."""
    n_s = X.shape[1]
    means = []
    vars_ = []
    for c in range(N_CLASS):
        xc = X[y == c].astype(np.float64)
        if xc.shape[0] < 2:
            continue
        means.append(xc.mean(axis=0))
        vars_.append(xc.var(axis=0, ddof=1))
    means = np.stack(means)
    vars_ = np.stack(vars_)
    num = means.var(axis=0, ddof=1)
    den = vars_.mean(axis=0)
    return np.divide(num, den, out=np.zeros(n_s), where=den > 0)


def build_mlp(tf, n_feat, n_classes=N_CLASS):
    # TCHES Table 5
    reg = tf.keras.regularizers.l2(0.01)
    model = tf.keras.Sequential(
        [
            tf.keras.layers.Input(shape=(n_feat,)),
            tf.keras.layers.Dense(128, activation="relu", kernel_regularizer=reg),
            tf.keras.layers.Dropout(0.2),
            tf.keras.layers.Dense(n_classes, activation="softmax"),
        ]
    )
    model.compile(
        optimizer="adam",
        loss="sparse_categorical_crossentropy",
        metrics=["accuracy"],
    )
    return model


def fit_mlp(tf, Xtr, ytr, n_classes=N_CLASS, epochs=EPOCHS):
    model = build_mlp(tf, Xtr.shape[1], n_classes=n_classes)
    hist = model.fit(
        Xtr,
        ytr,
        epochs=epochs,
        batch_size=BATCH,
        verbose=2,
        shuffle=True,
    )
    return model, hist.history


def predict_proba_mlp(model, X):
    return model.predict(X, batch_size=2048, verbose=0)


def threshold_curve(y, proba, n_class=N_CLASS):
    """Paper §5.4.1: N_all = true RCoI count; N_pre = accepted predicted-RCoI.

    A prediction is accepted as RCoI iff argmax in {0,1,2,3} and max softmax >= t.
    Precision is P(y == pred | accepted as RCoI). At 100% precision, N_pre equals
    correctly recovered RCoI and loss_ratio = (N_all - N_pre) / N_all.
    """
    pred = proba.argmax(axis=1)
    conf = proba.max(axis=1)
    rcoi = y < 4
    n_all = int(rcoi.sum())
    ts = np.unique(
        np.concatenate(
            [
                np.linspace(0.20, 0.95, 16),
                np.linspace(0.96, 0.999, 40),
                np.array([0.9995, 0.9999, 1.0]),
            ]
        )
    )
    rows = []
    for t in ts:
        keep = (pred < 4) & (conf >= t)
        n_pre = int(keep.sum())
        n_correct = int((keep & (y == pred)).sum())
        prec = n_correct / n_pre if n_pre else float("nan")
        acc5 = float((y[conf >= t] == pred[conf >= t]).mean()) if (conf >= t).any() else float("nan")
        loss = (n_all - n_correct) / n_all if n_all else float("nan")
        rows.append(
            dict(
                t=float(t),
                n_pre=n_pre,
                n_correct=n_correct,
                n_all=n_all,
                precision=float(prec) if n_pre else None,
                acc_among_conf=float(acc5) if (conf >= t).any() else None,
                loss_ratio=float(loss),
                n_kept_any=int((conf >= t).sum()),
            )
        )
    return pd.DataFrame(rows)


def first_perfect_threshold(curve: pd.DataFrame):
    ok = curve[curve["precision"].fillna(0) >= 1.0 - 1e-12]
    if len(ok) == 0:
        return None
    return float(ok.iloc[0]["t"])


def plot_confusion(cm, title, path, names=CLASS_TEX):
    fig, ax = plt.subplots(1, 2, figsize=(10.5, 4.2))
    im0 = ax[0].imshow(cm, cmap="Blues")
    ax[0].set_title("counts")
    fig.colorbar(im0, ax=ax[0], fraction=0.046)
    row = cm.astype(np.float64)
    row = np.divide(row, row.sum(axis=1, keepdims=True), out=np.zeros_like(row), where=row.sum(axis=1, keepdims=True) > 0)
    im1 = ax[1].imshow(row, cmap="Blues", vmin=0, vmax=1)
    ax[1].set_title("row-normalized")
    fig.colorbar(im1, ax=ax[1], fraction=0.046)
    for a in ax:
        a.set_xticks(range(len(names)))
        a.set_yticks(range(len(names)))
        a.set_xticklabels(names, rotation=30, ha="right")
        a.set_yticklabels(names)
        a.set_xlabel("predicted")
        a.set_ylabel("true")
    for i in range(cm.shape[0]):
        for j in range(cm.shape[1]):
            ax[0].text(j, i, str(int(cm[i, j])), ha="center", va="center", fontsize=8)
            ax[1].text(j, i, f"{row[i, j]:.2f}", ha="center", va="center", fontsize=8)
    fig.suptitle(title)
    fig.tight_layout()
    fig.savefig(path, dpi=140)
    plt.close(fig)


def plot_threshold(cal_curve, atk_curve, t_star, path):
    fig, ax = plt.subplots(figsize=(7.2, 4.0))
    ax.plot(cal_curve["t"], cal_curve["precision"], label="cal RCoI precision")
    ax.plot(atk_curve["t"], atk_curve["precision"], label="attack RCoI precision")
    ax.plot(cal_curve["t"], 1.0 - cal_curve["loss_ratio"], label="cal 1-loss (recall of correct RCoI)")
    ax.plot(atk_curve["t"], 1.0 - atk_curve["loss_ratio"], label="attack 1-loss")
    if t_star is not None:
        ax.axvline(t_star, color="k", ls="--", lw=1, label=f"cal t*={t_star:.4f}")
    ax.set_xlabel("softmax confidence threshold")
    ax.set_ylabel("precision / keep-rate of true RCoI")
    ax.set_ylim(-0.02, 1.05)
    ax.legend(fontsize=8)
    ax.set_title("reduce32 5-class — threshold vs precision / loss (TCHES §5.4.1)")
    fig.tight_layout()
    fig.savefig(path, dpi=140)
    plt.close(fig)


def plot_profile_size(sizes, accs, path):
    fig, ax = plt.subplots(figsize=(6.4, 3.6))
    ax.plot(sizes, accs, marker="o")
    ax.set_xlabel("profiling traces (balanced 1:1:1:1:1 train)")
    ax.set_ylabel("attack 5-class accuracy (unfiltered)")
    ax.set_title("reduce32 MLP — profiling set size vs accuracy (TCHES Fig. 11a analogue)")
    ax.set_ylim(0, 1.02)
    fig.tight_layout()
    fig.savefig(path, dpi=140)
    plt.close(fig)


def metrics_block(y, proba, tag):
    pred = proba.argmax(axis=1)
    acc = float((pred == y).mean())
    cm = confusion_matrix(y, pred, labels=list(range(proba.shape[1])))
    rcoi_true = y < 4
    rcoi_pred = pred < 4
    rcoi_prec = float((pred[rcoi_pred] == y[rcoi_pred]).mean()) if rcoi_pred.any() else None
    rcoi_rec = float((pred[rcoi_true] == y[rcoi_true]).mean()) if rcoi_true.any() else None
    print(f"\n==== {tag} ====", flush=True)
    print("acc", acc, "RCoI-pred precision", rcoi_prec, "RCoI-true exact-class recall", rcoi_rec)
    print(classification_report(y, pred, target_names=CLASS_NAMES[: proba.shape[1]], digits=4))
    print("confusion\n", cm)
    return dict(
        acc=acc,
        rcoi_precision_unfiltered=rcoi_prec,
        rcoi_exact_recall_unfiltered=rcoi_rec,
        confusion=cm.tolist(),
        n=int(len(y)),
        n_rcoi=int(rcoi_true.sum()),
    )


def apply_features(X, kind, poi, half, top_idx=None):
    if kind == "full":
        return X
    if kind == "crop":
        xc, _, _ = crop_around(X, poi, half)
        return xc
    if kind == "top":
        return X[:, top_idx]
    raise ValueError(kind)


def main():
    os.makedirs(OUT_DIR, exist_ok=True)
    print("OUT_DIR", OUT_DIR, flush=True)
    print("paper TCHES 2025(4) 817-847  Table 5 / §5.4.3 reduce32", flush=True)

    tr = np.load(TRACE_PATH, mmap_mode="r")
    print("traces", tr.shape, tr.dtype, flush=True)
    assert tr.shape == (N_EXPECT, N_SWEEP * N_WIN, 300), tr.shape

    lab = pd.read_csv(os.path.join(LABEL_DIR, "labels_45k.csv"))
    assert len(lab) == N_EXPECT
    y = lab["cls"].to_numpy(dtype=np.int32)
    k = lab["k"].to_numpy(dtype=np.int32)
    poly_l = lab["poly_l"].to_numpy(dtype=np.int32)
    hw_tgt = np.fromfile(os.path.join(LABEL_DIR, "z_target_hw.bin"), dtype=np.uint8)
    print("cls", {int(c): int((y == c).sum()) for c in range(N_CLASS)}, flush=True)
    print(
        "file-order check first30000",
        {int(c): int((y[:30000] == c).sum()) for c in range(N_CLASS)},
        "last15000",
        {int(c): int((y[30000:] == c).sum()) for c in range(N_CLASS)},
        flush=True,
    )

    X_rej = load_or_extract(os.path.join(OUT_DIR, "X_at_k_reject_int8.npy"), tr, k, sweep=0)
    X_leg = load_or_extract(os.path.join(OUT_DIR, "X_at_k_legal_int8.npy"), tr, k, sweep=1)

    split = stratified_split(y, poly_l, seed=SEED)
    np.savez(
        os.path.join(OUT_DIR, "split_seed20260819.npz"),
        split=split.astype("U8"),
        y=y,
        k=k,
        poly_l=poly_l,
    )
    print("new split (not csv idx-split)", pd.Series(split).value_counts().to_dict(), flush=True)
    print(pd.crosstab(split, y), flush=True)

    idx_tr_all = np.flatnonzero(split == "train")
    idx_ca = np.flatnonzero(split == "cal")
    idx_te = np.flatnonzero(split == "attack")
    idx_tr = downsample_other(idx_tr_all, y, seed=SEED)
    print(
        "train balanced",
        {int(c): int((y[idx_tr] == c).sum()) for c in range(N_CLASS)},
        "from",
        {int(c): int((y[idx_tr_all] == c).sum()) for c in range(N_CLASS)},
        flush=True,
    )

    # POI from train-only HW-PCC of zval (TCHES §5.2)
    rho = corr_fast(
        X_rej[idx_tr].astype(np.float64),
        hw_tgt[idx_tr].astype(np.float64).reshape(-1, 1),
    )[0]
    poi = int(np.nanargmax(np.abs(rho)))
    print("train-only PCC peak", float(np.nanmax(np.abs(rho))), "at sample", poi, flush=True)
    np.save(os.path.join(OUT_DIR, "pcc_at_k_trainonly.npy"), rho)

    snr = snr_per_sample(X_rej[idx_tr].astype(np.float64), y[idx_tr])
    top30 = np.argsort(-snr)[:30]
    print("SNR peak", float(snr.max()), "at", int(snr.argmax()), "top30", top30.tolist(), flush=True)
    np.save(os.path.join(OUT_DIR, "snr_at_k_train.npy"), snr)

    fig, ax = plt.subplots(figsize=(7.5, 3.4))
    ax.plot(np.abs(rho), label="|PCC| HW(zval) train")
    ax.plot(snr / (snr.max() + 1e-12) * np.abs(rho).max(), label="SNR (rescaled)", alpha=0.8)
    ax.axvline(poi, color="C3", ls="--", label=f"POI {poi}")
    ax.set_xlabel("sample in reduce32 window k")
    ax.legend(fontsize=8)
    ax.set_title("train-only POI (reject sweep, labelled k)")
    fig.tight_layout()
    fig.savefig(os.path.join(OUT_DIR, "02_poi_trainonly.png"), dpi=140)
    plt.close(fig)

    tf = _tf()
    print("TF", tf.__version__, "GPU", tf.config.list_physical_devices("GPU"), flush=True)

    variants = [
        ("mlp_full300", "mlp", "full", None),
        ("mlp_crop_pm20", "mlp", "crop", None),
        ("lda_full_shrink", "lda", "full", None),
        ("lda_top30snr", "lda", "top", top30),
    ]

    summary = {
        "paper": "TCHES 2025(4) 817-847 Zhou et al.",
        "section": "Table 5, §5.4.3 reduce32, loss-ratio §5.4.1",
        "poi_train": poi,
        "n_expect": N_EXPECT,
        "seed": SEED,
        "split_note": "70/15/15 shuffled inside (cls, poly_l); csv split unused",
        "train_balanced": {int(c): int((y[idx_tr] == c).sum()) for c in range(N_CLASS)},
        "cal": {int(c): int((y[idx_ca] == c).sum()) for c in range(N_CLASS)},
        "attack": {int(c): int((y[idx_te] == c).sum()) for c in range(N_CLASS)},
        "variants": {},
    }

    for name, model_kind, feat, extra in variants:
        print(f"\n######## {name} ########", flush=True)
        Xf = apply_features(X_rej, feat, poi, CROP_HALF, extra)
        print("feat", feat, "shape", Xf.shape, flush=True)
        scaler = StandardScaler()
        Xtr = scaler.fit_transform(Xf[idx_tr].astype(np.float64))
        Xca = scaler.transform(Xf[idx_ca].astype(np.float64))
        Xte = scaler.transform(Xf[idx_te].astype(np.float64))
        Xleg = scaler.transform(
            apply_features(X_leg, feat, poi, CROP_HALF, extra)[idx_te].astype(np.float64)
        )

        if model_kind == "mlp":
            model, hist = fit_mlp(tf, Xtr, y[idx_tr])
            model.save(os.path.join(OUT_DIR, f"02_{name}.keras"))
            fig, ax = plt.subplots(figsize=(5.5, 3.2))
            ax.plot(hist["accuracy"], label="train acc")
            ax.plot(hist["loss"], label="train loss")
            ax.legend()
            ax.set_xlabel("epoch")
            ax.set_title(name)
            fig.tight_layout()
            fig.savefig(os.path.join(OUT_DIR, f"02_{name}_history.png"), dpi=140)
            plt.close(fig)
            proba_ca = predict_proba_mlp(model, Xca)
            proba_te = predict_proba_mlp(model, Xte)
            proba_leg = predict_proba_mlp(model, Xleg)
        else:
            lda = LinearDiscriminantAnalysis(solver="lsqr", shrinkage="auto")
            lda.fit(Xtr, y[idx_tr])
            proba_ca = lda.predict_proba(Xca)
            proba_te = lda.predict_proba(Xte)
            proba_leg = lda.predict_proba(Xleg)

        np.save(os.path.join(OUT_DIR, f"02_{name}_proba_attack.npy"), proba_te.astype(np.float32))
        blk = metrics_block(y[idx_te], proba_te, f"{name} ATTACK")
        blk_leg = metrics_block(y[idx_te], proba_leg, f"{name} LEGAL-WINDOW CONTROL (same k, sweep 1)")
        cm = np.array(blk["confusion"], dtype=np.int64)
        plot_confusion(cm, f"{name} attack 5-class", os.path.join(OUT_DIR, f"02_{name}_confusion.png"))

        cal_curve = threshold_curve(y[idx_ca], proba_ca)
        atk_curve = threshold_curve(y[idx_te], proba_te)
        cal_curve.to_csv(os.path.join(OUT_DIR, f"02_{name}_threshold_cal.csv"), index=False)
        atk_curve.to_csv(os.path.join(OUT_DIR, f"02_{name}_threshold_attack.csv"), index=False)
        t_star = first_perfect_threshold(cal_curve)
        plot_threshold(cal_curve, atk_curve, t_star, os.path.join(OUT_DIR, f"02_{name}_threshold.png"))

        atk_at_t = None
        if t_star is not None:
            row = atk_curve.iloc[(atk_curve["t"] - t_star).abs().argmin()]
            atk_at_t = {k: (None if pd.isna(v) else (v.item() if hasattr(v, "item") else v)) for k, v in row.to_dict().items()}
            print(
                f"{name} cal t*={t_star:.6f}  attack@t* precision={atk_at_t['precision']} "
                f"loss={atk_at_t['loss_ratio']} n_pre={atk_at_t['n_pre']}",
                flush=True,
            )
        else:
            print(f"{name} cal never reached 100% RCoI precision", flush=True)
            # still report attack t where precision first hits 1 if any
            t_atk = first_perfect_threshold(atk_curve)
            print(f"{name} attack first perfect t={t_atk}", flush=True)

        summary["variants"][name] = dict(
            feat=feat,
            n_feat=int(Xtr.shape[1]),
            attack=blk,
            legal_control=blk_leg,
            t_star_cal=t_star,
            attack_at_t_star=atk_at_t,
        )

    # Profiling-size curve on main MLP (full 300), TCHES Fig. 11a analogue
    print("\n######## profiling-size curve (mlp_full300) ########", flush=True)
    Xf = X_rej
    scaler = StandardScaler()
    Xtr_all = scaler.fit_transform(Xf[idx_tr].astype(np.float64))
    Xte = scaler.transform(Xf[idx_te].astype(np.float64))
    rng = np.random.RandomState(SEED + 1)
    # per-class counts in balanced train
    n_per = min(int((y[idx_tr] == c).sum()) for c in range(N_CLASS))
    byc = {c: idx_tr[y[idx_tr] == c] for c in range(N_CLASS)}
    sizes, accs = [], []
    for n_c in [200, 500, 1000, 2000, 3500, n_per]:
        n_c = min(n_c, n_per)
        pick = np.concatenate([rng.choice(byc[c], n_c, replace=False) for c in range(N_CLASS)])
        # map pick (global idx) -> rows in idx_tr
        pos = {int(g): i for i, g in enumerate(idx_tr)}
        rows = np.array([pos[int(g)] for g in pick])
        model, _ = fit_mlp(tf, Xtr_all[rows], y[pick], epochs=EPOCHS)
        proba = predict_proba_mlp(model, Xte)
        acc = float((proba.argmax(1) == y[idx_te]).mean())
        sizes.append(int(n_c * N_CLASS))
        accs.append(acc)
        print("  n_profile", n_c * N_CLASS, "acc", acc, flush=True)
        if n_c == n_per:
            break
    plot_profile_size(sizes, accs, os.path.join(OUT_DIR, "02_mlp_full300_profile_size.png"))
    summary["profile_size"] = {"n": sizes, "attack_acc": accs}

    # Appendix: 4-class on RCoI only (NOT the main result)
    print("\n######## APPENDIX 4-class RCoI-only (not main) ########", flush=True)
    m_tr = idx_tr[y[idx_tr] < 4]
    m_ca = idx_ca[y[idx_ca] < 4]
    m_te = idx_te[y[idx_te] < 4]
    scaler = StandardScaler()
    Xtr = scaler.fit_transform(X_rej[m_tr].astype(np.float64))
    Xte = scaler.transform(X_rej[m_te].astype(np.float64))
    model, _ = fit_mlp(tf, Xtr, y[m_tr], n_classes=4)
    proba = predict_proba_mlp(model, Xte)
    blk4 = metrics_block(y[m_te], proba, "APPENDIX 4-class ATTACK (RCoI only)")
    plot_confusion(
        np.array(blk4["confusion"]),
        "APPENDIX 4-class RCoI-only (not main)",
        os.path.join(OUT_DIR, "02_appendix_4class_confusion.png"),
        names=CLASS_TEX[:4],
    )
    summary["appendix_4class"] = blk4

    def _jsonable(o):
        if isinstance(o, dict):
            return {str(k): _jsonable(v) for k, v in o.items()}
        if isinstance(o, (list, tuple)):
            return [_jsonable(v) for v in o]
        if isinstance(o, np.integer):
            return int(o)
        if isinstance(o, np.floating):
            return float(o)
        if isinstance(o, np.ndarray):
            return o.tolist()
        if o is None or isinstance(o, (str, int, float, bool)):
            return o
        return str(o)

    out_json = os.path.join(OUT_DIR, "02_5class_summary.json")
    with open(out_json, "w") as f:
        json.dump(_jsonable(summary), f, indent=2)
    print("wrote", out_json, flush=True)
    print("DONE", flush=True)
    return summary


if __name__ == "__main__":
    main()
