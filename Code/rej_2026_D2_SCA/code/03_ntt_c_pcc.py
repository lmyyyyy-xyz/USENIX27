#!/usr/bin/env python3
"""First-layer NTT(c) PCC: each butterfly window j leaks c[j] and c[j+128].

Rejected c is time-domain poly_challenge (not UART/legal c).
Windows 0:128 of ntt_c_reject are layer-0 CT butterflies
(len=128, pair (a[j], a[j+128]), zeta=zetas[1]=25847).
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

OUT_TR = EXTRACTED_TRACE_ROOT
OUT_FIG = RESULTS_ROOT
LABEL_DIR = LABEL_ROOT
C_BIN = os.path.join(LABEL_DIR, "c_rej_i32.bin")  # (N,256) int32 LE
N0 = 128  # first-layer butterflies
N = 256


def hw32(x):
    u = np.asarray(x, dtype=np.int32).view(np.uint32)
    return np.unpackbits(u.reshape(-1, 1).view(np.uint8), axis=1).sum(axis=1).astype(np.float64)


def pcc_windows(traces, pred):
    """traces (n, nwin, t), pred (n, nwin) -> (nwin, t) PCC of each window vs its column."""
    nwin = traces.shape[1]
    t = traces.shape[2]
    out = np.empty((nwin, t), dtype=np.float64)
    for j in range(nwin):
        O = traces[:, j, :].astype(np.float64)
        P = pred[:, j : j + 1]
        out[j] = corr_fast(O, P)[0]
    return out


def main():
    os.makedirs(OUT_FIG, exist_ok=True)
    tag = "n400"
    ntt_r = np.load(os.path.join(OUT_TR, f"ntt_c_reject_{tag}.npy"), mmap_mode="r")
    ntt_l = np.load(os.path.join(OUT_TR, f"ntt_c_legal_{tag}.npy"), mmap_mode="r")
    n = ntt_r.shape[0]
    print("ntt reject", ntt_r.shape, "legal", ntt_l.shape, flush=True)

    c = np.fromfile(C_BIN, dtype=np.int32).reshape(-1, N)[:n]
    print("c", c.shape, "unique", np.unique(c), "nnz/trace mean", float((c != 0).sum(1).mean()), flush=True)
    assert set(np.unique(c).tolist()) <= {-1, 0, 1}

    hw = np.vstack([hw32(c[:, j]) for j in range(N)]).T  # (n,256)
    print("HW unique", np.unique(hw), flush=True)  # 0,1,32

    layer0 = np.asarray(ntt_r[:, :N0, :])
    layer0_leg = np.asarray(ntt_l[:, :N0, :])

    pcc_lo = pcc_windows(layer0, hw[:, :N0])          # c[j]
    pcc_up = pcc_windows(layer0, hw[:, N0 : 2 * N0])  # c[j+128]
    pcc_lo_leg = pcc_windows(layer0_leg, hw[:, :N0])
    pcc_up_leg = pcc_windows(layer0_leg, hw[:, N0 : 2 * N0])

    rng = np.random.RandomState(0)
    perm = rng.permutation(n)
    pcc_lo_shuf = pcc_windows(layer0, hw[perm, :N0])

    def peak(a):
        aa = np.abs(a)
        j, s = np.unravel_index(int(np.nanargmax(aa)), aa.shape)
        return float(aa[j, s]), int(j), int(s)

    print("reject HW(c[j])     peak", peak(pcc_lo), "mean_win_max", float(np.nanmean(np.nanmax(np.abs(pcc_lo), 1))))
    print("reject HW(c[j+128]) peak", peak(pcc_up), "mean_win_max", float(np.nanmean(np.nanmax(np.abs(pcc_up), 1))))
    print("legal  HW(c[j])     peak", peak(pcc_lo_leg), "(control, rejected c)")
    print("legal  HW(c[j+128]) peak", peak(pcc_up_leg))
    print("shuffle HW(c[j])    peak", peak(pcc_lo_shuf))

    np.save(os.path.join(OUT_FIG, "pcc_ntt_c_layer0_lower.npy"), pcc_lo)
    np.save(os.path.join(OUT_FIG, "pcc_ntt_c_layer0_upper.npy"), pcc_up)

    fig, ax = plt.subplots(2, 1, figsize=(10, 6), sharex=True)
    ax[0].plot(np.nanmax(np.abs(pcc_lo), 1), label="reject |PCC|_max HW(c[j])")
    ax[0].plot(np.nanmax(np.abs(pcc_up), 1), label="reject |PCC|_max HW(c[j+128])")
    ax[0].plot(np.nanmax(np.abs(pcc_lo_leg), 1), alpha=0.7, label="legal |PCC|_max HW(c[j])")
    ax[0].plot(np.nanmax(np.abs(pcc_lo_shuf), 1), alpha=0.5, label="shuffle")
    ax[0].set_ylabel("|PCC| max over samples")
    ax[0].legend(fontsize=8)
    ax[0].set_title("NTT(c) first layer — butterfly j leaks c[j] and c[j+128]  (n=%d)" % n)
    jstar = int(np.nanargmax(np.nanmax(np.abs(pcc_up), 1)))
    ax[1].plot(pcc_lo[jstar], label=f"HW(c[{jstar}]) window {jstar}")
    ax[1].plot(pcc_up[jstar], label=f"HW(c[{jstar}+128]) window {jstar}")
    ax[1].plot(pcc_lo_leg[jstar], alpha=0.6, label="legal same window")
    ax[1].set_xlabel("sample in butterfly window")
    ax[1].set_ylabel("PCC")
    ax[1].legend(fontsize=8)
    fig.tight_layout()
    fig.savefig(os.path.join(OUT_FIG, "pcc_ntt_c_layer0.png"), dpi=140)
    plt.close(fig)
    print("wrote", os.path.join(OUT_FIG, "pcc_ntt_c_layer0.png"), flush=True)

    # also scan all 1024 windows vs HW(c[0]) as a sanity that leakage is localized
    # too expensive? 1024 * corr of n x t is ok for n=400
    # skip full scan; print first 8 layer peaks vs lower HW of that layer's pairs if needed


if __name__ == "__main__":
    main()
