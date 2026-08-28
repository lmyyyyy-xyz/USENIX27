#!/usr/bin/env python3
"""Signed PCC + TCHES-style SNR on the same (6, 3) axes.

SNR = Var(group means) / Mean(within-group var)  [TCHES 2025(4) §5.2].
Their quoted 0.34 is a generic load < q, not these intermediates.
We use the same formula on the attack grouping (HW of z_k, or c in {-1,0,1}).
"""
from __future__ import annotations

import os
import sys

import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

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
from sca_utils import corr_fast

OUT_FIG = RESULTS_ROOT
OUT_TR = EXTRACTED_TRACE_ROOT
LABEL_DIR = LABEL_ROOT
C_BIN = os.path.join(LABEL_DIR, "c_rej_i32.bin")
N0, N = 128, 256
BUTTERFLY_J = 0
TCHES_SNR = 0.34


def hw32(x):
    u = np.asarray(x, dtype=np.int32).view(np.uint32)
    return (
        np.unpackbits(u.reshape(-1, 1).view(np.uint8), axis=1)
        .sum(axis=1)
        .astype(np.float64)
    )


def snr_tches(X, y):
    """TCHES §5.2: var(class means) / mean(class variances). X=(n,t), y=(n,)."""
    X = np.asarray(X, dtype=np.float64)
    y = np.asarray(y)
    means, vars_ = [], []
    for g in np.unique(y):
        xg = X[y == g]
        if xg.shape[0] < 2:
            continue
        means.append(xg.mean(axis=0))
        vars_.append(xg.var(axis=0, ddof=1))
    if len(means) < 2:
        return np.zeros(X.shape[1], dtype=np.float64)
    means = np.stack(means)
    vars_ = np.stack(vars_)
    num = means.var(axis=0, ddof=1)
    den = np.nanmean(vars_, axis=0)
    return np.divide(num, den, out=np.zeros_like(num), where=den > 0)


def pcc_snr_plot(pccs, pcc_labs, snrs, snr_labs, n_s, title, fname):
    fig, ax = plt.subplots(figsize=(6, 3))
    for y, lab in zip(pccs, pcc_labs):
        ax.plot(np.asarray(y), lw=1.2, label=lab)
    ax.set_xlim(0, n_s)
    ax.set_ylim(-1, 1)
    ax.set_yticks(np.arange(-1, 1.1, 0.5))
    ax.set_xlabel("sample")
    ax.set_ylabel("PCC")
    ax.grid(True, linestyle=":", alpha=0.7)

    ax2 = ax.twinx()
    for y, lab in zip(snrs, snr_labs):
        ax2.plot(np.asarray(y), lw=1.0, ls="--", label=lab)
    ax2.set_ylabel("SNR")
    ax2.set_ylim(bottom=0)
    ax2.axhline(TCHES_SNR, color="0.5", ls=":", lw=0.8, label=f"TCHES {TCHES_SNR}")

    h1, l1 = ax.get_legend_handles_labels()
    h2, l2 = ax2.get_legend_handles_labels()
    ax.legend(h1 + h2, l1 + l2, fontsize=7, loc="upper right")
    ax.set_title(title)
    fig.tight_layout()
    path = os.path.join(OUT_FIG, fname)
    fig.savefig(path, dpi=140, bbox_inches="tight")
    plt.close(fig)
    print("wrote", path, flush=True)


def main():
    os.makedirs(OUT_FIG, exist_ok=True)

    # --- reduce32 45k at labelled k ---
    pcc_red = np.load(os.path.join(OUT_FIG, "pcc_at_labelled_k.npy"))
    Xk = np.load(os.path.join(OUT_FIG, "X_at_k_reject_int8.npy"), mmap_mode="r")
    lab = pd.read_csv(os.path.join(LABEL_DIR, "labels_45k.csv"))
    hw_all = np.fromfile(os.path.join(LABEL_DIR, "z_target_hw.bin"), dtype=np.uint8)
    cls_all = lab["cls"].to_numpy()
    snr_red_hw = snr_tches(Xk, hw_all)
    snr_red_cls = snr_tches(Xk, cls_all)
    print(
        "reduce32 PCC",
        float(np.min(pcc_red)),
        float(np.max(pcc_red)),
        "SNR_HW peak",
        float(snr_red_hw.max()),
        "@",
        int(snr_red_hw.argmax()),
        "SNR_5class peak",
        float(snr_red_cls.max()),
        flush=True,
    )
    pcc_snr_plot(
        [pcc_red],
        [r"HW($z_k$)"],
        [snr_red_cls, snr_red_hw],
        ["SNR 5-class", "SNR HW($z_k$)"],
        len(pcc_red),
        "reduce32  window $k$",
        "pcc_signed_reduce32_at_k.png",
    )

    # --- add + chknorm n400 ---
    tag = "n400"
    meta = np.load(os.path.join(OUT_TR, f"block_meta_{tag}.npz"))
    k = meta["k"]
    n = len(k)
    add_r = np.load(os.path.join(OUT_TR, f"add_z_reject_{tag}.npy"), mmap_mode="r")
    chk_k = np.load(os.path.join(OUT_TR, f"chknorm_z_reject_at_k_{tag}.npy"), mmap_mode="r")
    hw_z = np.fromfile(os.path.join(LABEL_DIR, "z_target_hw.bin"), dtype=np.uint8)[:n]
    Pz = hw_z.astype(np.float64).reshape(-1, 1)
    Xadd = np.empty((n, add_r.shape[2]), dtype=np.float64)
    for i in range(n):
        Xadd[i] = add_r[i, int(k[i])]
    Xchk = np.asarray(chk_k[:n], dtype=np.float64)
    pcc_add = corr_fast(Xadd, Pz)[0]
    pcc_chk = corr_fast(Xchk, Pz)[0]
    snr_add = snr_tches(Xadd, hw_z)
    snr_chk = snr_tches(Xchk, hw_z)
    print(
        "add PCC",
        float(np.min(pcc_add)),
        float(np.max(pcc_add)),
        "SNR peak",
        float(snr_add.max()),
        "@",
        int(snr_add.argmax()),
        flush=True,
    )
    print(
        "chknorm PCC",
        float(np.min(pcc_chk)),
        float(np.max(pcc_chk)),
        "SNR peak",
        float(snr_chk.max()),
        "@",
        int(snr_chk.argmax()),
        flush=True,
    )
    pcc_snr_plot(
        [pcc_add],
        [r"HW($z_k$)"],
        [snr_add],
        ["SNR HW($z_k$)"],
        len(pcc_add),
        "poly_add  window $k$",
        "pcc_signed_add_at_k.png",
    )
    pcc_snr_plot(
        [pcc_chk],
        [r"HW($z_k$)"],
        [snr_chk],
        ["SNR HW($z_k$)"],
        len(pcc_chk),
        "poly_chknorm  abort pulse",
        "pcc_signed_chknorm_at_k.png",
    )

    # --- NTT(c) first layer: c[j] and c[j+128] in the same window ---
    ntt_r = np.load(os.path.join(OUT_TR, f"ntt_c_reject_{tag}.npy"), mmap_mode="r")
    n_c = ntt_r.shape[0]
    c = np.fromfile(C_BIN, dtype=np.int32).reshape(-1, N)[:n_c]
    j = BUTTERFLY_J
    O = np.asarray(ntt_r[:, j, :], dtype=np.float64)
    lo, up = c[:, j], c[:, j + N0]
    pcc_lo = corr_fast(O, hw32(lo).reshape(-1, 1))[0]
    pcc_up = corr_fast(O, hw32(up).reshape(-1, 1))[0]
    snr_lo = snr_tches(O, lo)
    snr_up = snr_tches(O, up)
    print(
        "ntt c[%d] PCC" % j,
        float(np.min(pcc_lo)),
        float(np.max(pcc_lo)),
        "SNR peak",
        float(snr_lo.max()),
        "c[%d]" % (j + N0),
        float(np.min(pcc_up)),
        float(np.max(pcc_up)),
        "SNR peak",
        float(snr_up.max()),
        flush=True,
    )
    pcc_snr_plot(
        [pcc_lo, pcc_up],
        [rf"HW($c[{j}]$)", rf"HW($c[{j + N0}]$)"],
        [snr_lo, snr_up],
        [rf"SNR $c[{j}]$", rf"SNR $c[{j + N0}]$"],
        len(pcc_lo),
        rf"NTT($c$) first layer  butterfly {j}",
        "pcc_signed_ntt_c_pair.png",
    )


if __name__ == "__main__":
    main()
