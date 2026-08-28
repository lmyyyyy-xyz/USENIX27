#!/usr/bin/env python3
"""Slice reject1_legal_ntt_c ETS into NTT(c) / add(z) / chknorm(z).

The reduce32 extractor assumed a rectangular 256*L*2 grid and filled
missing edges with base_period. That is wrong here: chknorm is early-abort
(k+1 pulses on the reject trial) and the three ops are concatenated in
the signing loop with large inter-op gaps.

Per UART (last-reject + legal), trigger edges form 6 blocks:

    0  NTT(c)  reject     1024  period ~225
    1  add(z)  reject     1024  period ~100
    2  chknorm reject     k+1   period ~106   (last pulse = abort coeff)
    3  NTT(c)  legal      1024  period ~225
    4  add(z)  legal      1024  period ~100
    5  chknorm legal     <=1024 period ~106   (truncated if k is large)

Do not fill; do not use max_triggers=2048. Split on gaps > 20k samples
(NTT layer gaps are ~345; add→chknorm / untriggered reduce is ~110k).

Usage:
  python -u 00_extract_ntt_add_chknorm.py
  python -u 00_extract_ntt_add_chknorm.py --limit 400
"""
from __future__ import annotations

import argparse
import os
import sys
import time

import numpy as np
import pandas as pd

from path_config import (
    ETS_ROOT,
    EXTRACTED_TRACE_ROOT,
    LABEL_ROOT,
    PACKAGE_ROOT,
    SUPPORT_CODE_ROOT,
)

CODE_DIR = SUPPORT_CODE_ROOT
HERE = PACKAGE_ROOT
sys.path.insert(0, CODE_DIR)

ETS_DIR = ETS_ROOT
PW_ETS = os.path.join(ETS_DIR, "mldsa_o3_time_opt_44_100MHz_reject1_legal_ntt_c_pw_4.5e4.ets")
TG_ETS = os.path.join(ETS_DIR, "mldsa_o3_time_opt_44_100MHz_reject1_legal_ntt_c_tg_4.5e4.ets")
LABEL_CSV = os.path.join(LABEL_ROOT, "labels_45k.csv")
OUT_DIR = EXTRACTED_TRACE_ROOT

N_WIN = 1024
HIGH = 75
EDGE_GAP = 10
BLOCK_GAP = 20000
PRE = 8
NTT_SEG = 200  # NTT period ~225
ADD_SEG = 90  # add period ~100
CHK_SEG = 95  # chknorm period ~106


def pulse_starts(trace, high=HIGH, gap=EDGE_GAP):
    hi = np.where(np.asarray(trace) >= high)[0]
    if hi.size == 0:
        return np.empty(0, dtype=np.int64)
    starts = [int(hi[0])]
    for j in range(1, hi.size):
        if int(hi[j]) - int(hi[j - 1]) > gap:
            starts.append(int(hi[j]))
    return np.asarray(starts, dtype=np.int64)


def split6(starts):
    if starts.size < 6:
        return None
    d = np.diff(starts)
    cut_after = np.flatnonzero(d > BLOCK_GAP)
    bounds = np.concatenate([[0], cut_after + 1, [starts.size]])
    return [starts[bounds[i] : bounds[i + 1]] for i in range(len(bounds) - 1)]


def slice_windows(pw, starts, seg, pre=PRE):
    n_s = pw.shape[0]
    out = np.zeros((len(starts), seg), dtype=np.int8)
    for j, st in enumerate(starts):
        a = int(st) - pre
        b = a + seg
        if a >= 0 and b <= n_s:
            out[j] = pw[a:b]
            continue
        for k in range(seg):
            idx = a + k
            if 0 <= idx < n_s:
                v = int(pw[idx])
                if v > 127:
                    v = 127
                elif v < -128:
                    v = -128
                out[j, k] = v
    return out


def extract_one(tg, pw, k):
    starts = pulse_starts(tg)
    blocks = split6(starts)
    rec = dict(
        n_pulse=int(starts.size),
        n_block=0 if blocks is None else len(blocks),
        ntt_r=None,
        add_r=None,
        chk_r=None,
        ntt_l=None,
        add_l=None,
        chk_l=None,
        chk_r_len=0,
        chk_l_len=0,
        ok_ntt_add=False,
        chk_r_matches_k=False,
    )
    if blocks is None or len(blocks) != 6:
        return rec
    ntt_r, add_r, chk_r, ntt_l, add_l, chk_l = blocks
    rec["chk_r_len"] = int(chk_r.size)
    rec["chk_l_len"] = int(chk_l.size)
    rec["ok_ntt_add"] = (
        ntt_r.size == N_WIN
        and add_r.size == N_WIN
        and ntt_l.size == N_WIN
        and add_l.size == N_WIN
    )
    rec["chk_r_matches_k"] = chk_r.size == int(k) + 1
    rec["ntt_r"] = ntt_r
    rec["add_r"] = add_r
    rec["chk_r"] = chk_r
    rec["ntt_l"] = ntt_l
    rec["add_l"] = add_l
    rec["chk_l"] = chk_l
    rec["n_block"] = 6
    return rec


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--limit", type=int, default=0, help="only first N traces (0=all)")
    ap.add_argument("--out", default=OUT_DIR)
    args = ap.parse_args()
    os.makedirs(args.out, exist_ok=True)

    import estraces

    print("PW", PW_ETS, flush=True)
    print("TG", TG_ETS, flush=True)
    pw_ths = estraces.read_ths_from_ets_file(PW_ETS)
    tg_ths = estraces.read_ths_from_ets_file(TG_ETS)
    pw_mm = pw_ths.samples
    tg_mm = tg_ths.samples
    print("power", pw_mm.shape, pw_mm.dtype, "trig", tg_mm.shape, tg_mm.dtype, flush=True)
    n = int(pw_mm.shape[0])
    if args.limit and args.limit < n:
        n = int(args.limit)
        print("LIMIT", n, flush=True)

    lab = pd.read_csv(LABEL_CSV)
    k_all = lab["k"].to_numpy(dtype=np.int32)
    cls_all = lab["cls"].to_numpy(dtype=np.int32)
    assert len(lab) >= n

    ntt_r = np.zeros((n, N_WIN, NTT_SEG), dtype=np.int8)
    ntt_l = np.zeros((n, N_WIN, NTT_SEG), dtype=np.int8)
    add_r = np.zeros((n, N_WIN, ADD_SEG), dtype=np.int8)
    add_l = np.zeros((n, N_WIN, ADD_SEG), dtype=np.int8)
    chk_k = np.zeros((n, CHK_SEG), dtype=np.int8)
    chk_l = np.zeros((n, N_WIN, CHK_SEG), dtype=np.int8)
    meta_chk_r_len = np.zeros(n, dtype=np.int32)
    meta_chk_l_len = np.zeros(n, dtype=np.int32)
    meta_ok = np.zeros(n, dtype=np.uint8)
    meta_match = np.zeros(n, dtype=np.uint8)

    t0 = time.time()
    n_ok = 0
    for i in range(n):
        rec = extract_one(tg_mm[i], pw_mm[i], int(k_all[i]))
        meta_chk_r_len[i] = rec["chk_r_len"]
        meta_chk_l_len[i] = rec["chk_l_len"]
        if rec["ok_ntt_add"]:
            ntt_r[i] = slice_windows(pw_mm[i], rec["ntt_r"], NTT_SEG)
            ntt_l[i] = slice_windows(pw_mm[i], rec["ntt_l"], NTT_SEG)
            add_r[i] = slice_windows(pw_mm[i], rec["add_r"], ADD_SEG)
            add_l[i] = slice_windows(pw_mm[i], rec["add_l"], ADD_SEG)
            # abort window = last pulse of reject chknorm (early-return coeff)
            if rec["chk_r"] is not None and rec["chk_r"].size:
                chk_k[i] = slice_windows(pw_mm[i], rec["chk_r"][-1:], CHK_SEG)[0]
            nl = min(N_WIN, rec["chk_l_len"])
            if nl:
                chk_l[i, :nl] = slice_windows(pw_mm[i], rec["chk_l"][:nl], CHK_SEG)
            meta_ok[i] = 1
            n_ok += 1
        meta_match[i] = 1 if rec["chk_r_matches_k"] else 0
        if (i + 1) % 100 == 0 or i == 0:
            dt = time.time() - t0
            print(
                f"  {i+1}/{n}  ok={n_ok} match_k={int(meta_match[: i + 1].sum())}  "
                f"{dt:.1f}s  {(i+1)/max(dt,1e-6):.2f} tr/s",
                flush=True,
            )

    tag = f"n{n}"
    np.save(os.path.join(args.out, f"ntt_c_reject_{tag}.npy"), ntt_r)
    np.save(os.path.join(args.out, f"ntt_c_legal_{tag}.npy"), ntt_l)
    np.save(os.path.join(args.out, f"add_z_reject_{tag}.npy"), add_r)
    np.save(os.path.join(args.out, f"add_z_legal_{tag}.npy"), add_l)
    np.save(os.path.join(args.out, f"chknorm_z_reject_at_k_{tag}.npy"), chk_k)
    np.save(os.path.join(args.out, f"chknorm_z_legal_{tag}.npy"), chk_l)
    np.savez(
        os.path.join(args.out, f"block_meta_{tag}.npz"),
        k=k_all[:n],
        cls=cls_all[:n],
        chk_r_len=meta_chk_r_len,
        chk_l_len=meta_chk_l_len,
        ok_ntt_add=meta_ok,
        chk_r_matches_k=meta_match,
        high=HIGH,
        edge_gap=EDGE_GAP,
        block_gap=BLOCK_GAP,
        ntt_seg=NTT_SEG,
        add_seg=ADD_SEG,
        chk_seg=CHK_SEG,
        pre=PRE,
    )
    print("ok_ntt_add", int(meta_ok.sum()), "/", n, flush=True)
    print("chk_r_len == k+1", int(meta_match.sum()), "/", n, flush=True)
    print("chk_r_len vs k+1 (RCoI)", end=" ", flush=True)
    rcoi = cls_all[:n] < 4
    print(
        int((meta_chk_r_len[rcoi] == k_all[:n][rcoi] + 1).sum()),
        "/",
        int(rcoi.sum()),
        flush=True,
    )
    print("wrote", args.out, flush=True)


if __name__ == "__main__":
    main()
