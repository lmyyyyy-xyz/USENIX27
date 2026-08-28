#!/usr/bin/env python3
"""Headless twin of 01_reduce32_pcc.ipynb — PCC of reduce32 traces vs rejected z HW."""
import os
import sys
import numpy as np
import pandas as pd
import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt

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
from sca_utils import corr_fast

TRACE_PATH = os.path.join(
    TRACE_ROOT,
    "reject1_legal_reduce_z_mldsa_o3_time_opt_44_100MHz_4.5e4_v2.npy",
)
LABEL_DIR = LABEL_ROOT
OUT_DIR = RESULTS_ROOT
os.makedirs(OUT_DIR, exist_ok=True)

N_WIN = 1024
N_SWEEP = 2
N_EXPECT = 45000


def pcc_maxabs_per_window(traces_mm, hw_mat, sweep, n_win=N_WIN):
    n_s = traces_mm.shape[2]
    pcc = np.empty((n_win, n_s), dtype=np.float64)
    peak = np.empty(n_win, dtype=np.float64)
    off = sweep * n_win
    for j in range(n_win):
        O = np.asarray(traces_mm[:, off + j, :], dtype=np.float64)
        P = hw_mat[:, j : j + 1].astype(np.float64)
        rho = corr_fast(O, P)[0]
        pcc[j] = rho
        peak[j] = np.nanmax(np.abs(rho))
        if (j + 1) % 256 == 0:
            print(
                f"  sweep {sweep} poly {j // 256} done  max so far {peak[: j + 1].max():.4f}",
                flush=True,
            )
    return pcc, peak


def main():
    tr = np.load(TRACE_PATH, mmap_mode="r")
    print("traces", tr.shape, tr.dtype, flush=True)
    assert tr.shape[0] == N_EXPECT, tr.shape
    assert tr.shape[1] == N_SWEEP * N_WIN, tr.shape

    lab = pd.read_csv(os.path.join(LABEL_DIR, "labels_45k.csv"))
    assert len(lab) == N_EXPECT
    hw = np.fromfile(os.path.join(LABEL_DIR, "z_rej_hw.bin"), dtype=np.uint8).reshape(
        N_EXPECT, N_WIN
    )
    hw_tgt = np.fromfile(os.path.join(LABEL_DIR, "z_target_hw.bin"), dtype=np.uint8)
    k_all = lab["k"].to_numpy()
    cls = lab["cls"].to_numpy()
    print("cls", lab["cls"].value_counts().sort_index().to_dict(), flush=True)

    print("reject sweep ...", flush=True)
    pcc_rej, peak_rej = pcc_maxabs_per_window(tr, hw, sweep=0)
    print("legal sweep (rejected HW, control) ...", flush=True)
    pcc_leg, peak_leg = pcc_maxabs_per_window(tr, hw, sweep=1)

    np.save(os.path.join(OUT_DIR, "pcc_reject_1024x300.npy"), pcc_rej)
    np.save(os.path.join(OUT_DIR, "pcc_legal_1024x300.npy"), pcc_leg)
    np.save(os.path.join(OUT_DIR, "peak_reject.npy"), peak_rej)
    np.save(os.path.join(OUT_DIR, "peak_legal.npy"), peak_leg)
    print("reject peak: max", float(peak_rej.max()), "at j", int(peak_rej.argmax()))
    print("legal  peak: max", float(peak_leg.max()), "at j", int(peak_leg.argmax()))

    j_star = int(peak_rej.argmax())
    fig, ax = plt.subplots(2, 1, figsize=(11, 6), sharex=True)
    ax[0].plot(peak_rej, lw=0.8, label="reject sweep |PCC|_max")
    ax[0].plot(peak_leg, lw=0.8, alpha=0.7, label="legal sweep |PCC|_max (rej HW)")
    for p in range(5):
        ax[0].axvline(p * 256, color="k", ls=":", lw=0.6)
    ax[0].axvline(j_star, color="C3", ls="--", lw=1, label=f"global peak j={j_star}")
    ax[0].set_ylabel("|PCC| max over 300 samples")
    ax[0].legend(loc="upper right", fontsize=8)
    ax[0].set_title("reduce32 HW(z) PCC — 1024 coeff windows")
    ax[1].plot(pcc_rej[j_star], label=f"reject window {j_star}")
    ax[1].plot(pcc_leg[j_star], alpha=0.7, label=f"legal window {j_star}")
    ax[1].set_xlabel("sample inside 300-pt window")
    ax[1].set_ylabel("PCC")
    ax[1].legend(fontsize=8)
    fig.tight_layout()
    fig.savefig(os.path.join(OUT_DIR, "pcc_scan_reject_vs_legal.png"), dpi=140)
    plt.close(fig)

    O_k = np.empty((N_EXPECT, tr.shape[2]), dtype=np.float64)
    for i in range(N_EXPECT):
        O_k[i] = tr[i, int(k_all[i]), :]
    pcc_at_k = corr_fast(O_k, hw_tgt.astype(np.float64).reshape(-1, 1))[0]
    print(
        "PCC HW(zval) at window k: max",
        float(np.nanmax(np.abs(pcc_at_k))),
        "at sample",
        int(np.nanargmax(np.abs(pcc_at_k))),
    )
    np.save(os.path.join(OUT_DIR, "pcc_at_labelled_k.npy"), pcc_at_k)

    fig, ax = plt.subplots(1, 2, figsize=(11, 3.6))
    ax[0].plot(pcc_at_k)
    ax[0].set_title("corr_fast(traces[i, k_i, :], HW(zval_i))")
    ax[0].set_xlabel("sample")
    ax[0].set_ylabel("PCC")
    ax[1].hist(k_all[cls < 4], bins=64, alpha=0.7, label="RCoI")
    ax[1].hist(k_all[cls == 4], bins=64, alpha=0.5, label="other")
    ax[1].set_title("abort index k")
    ax[1].legend()
    fig.tight_layout()
    fig.savefig(os.path.join(OUT_DIR, "pcc_at_labelled_k.png"), dpi=140)
    plt.close(fig)

    # RCoI classes have CONSTANT HW, so per-class corr_fast(HW) is undefined.
    # Plot mean trace at labelled k instead (template shape).
    names = {0: "+g1 HW1", 1: "+g1-1 HW17", 2: "-g1 HW15", 3: "-g1-1 HW31", 4: "other"}
    fig, ax = plt.subplots(figsize=(8, 3.5))
    for c, name in names.items():
        m = cls == c
        if m.sum() < 50:
            continue
        idx = np.flatnonzero(m)
        O = np.empty((idx.size, tr.shape[2]), dtype=np.float64)
        for t, i in enumerate(idx):
            O[t] = tr[i, int(k_all[i]), :]
        ax.plot(O.mean(axis=0), label=f"{name} n={m.sum()}")
    ax.legend(fontsize=8)
    ax.set_title("mean trace at labelled k (template shape), by class")
    ax.set_xlabel("sample")
    fig.tight_layout()
    fig.savefig(os.path.join(OUT_DIR, "mean_at_k_by_class.png"), dpi=140)
    plt.close(fig)
    print("wrote", OUT_DIR)


if __name__ == "__main__":
    main()
