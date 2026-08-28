#!/usr/bin/env python3
"""Real Algorithm 5 (§5.3.2) c-recovery via twiddle-HW deduction, multi-butterfly.

For lower coeff m (0/1; -1 known from layer 1), resolve by matching SCA-predicted
twiddle HW against the deduced HW for c[m]=0 vs 1. The twiddle t=mont(z*upper_pre)
is the CLEAN amplified quantity (support = single unknown m once earlier layers are
resolved) -- unlike the confounded stores. Deep-layer HW(t) leaks weakly, so we
COMBINE all butterflies that isolate m (support's only unresolved lower is m),
summing the fit distance -> per-butterfly noise averages out.

Order: resolve by first-amplification layer (groups L1..L7); c0 fixed by tau.
Two full NTT twiddle runs per group (group inputs 0 and 1) give both hypotheses.
Confidence = combined margin; discard challenge if any coeff near a tie.
GPU-free (numpy). Verified against known key.
"""
import os, re, time, numpy as np

from path_config import (
    EXTRACTED_TRACE_ROOT,
    LABEL_ROOT,
    NTT_C_PATH,
    RESULTS_ROOT,
)

NTT_C = NTT_C_PATH
EX = EXTRACTED_TRACE_ROOT
LAB = LABEL_ROOT
Q, QINV, N = 8380417, 58728449, 256
_P = np.array([bin(i).count("1") for i in range(1 << 16)], np.int16)
from sklearn.linear_model import Ridge
from sklearn.preprocessing import StandardScaler


def zetas():
    m = re.search(r"zetas\[MLDSA_N\]\s*=\s*\{(.+?)\};", open(NTT_C).read(), re.S)
    return np.array([int(x) for x in re.findall(r"-?\d+", m.group(1))], np.int64)


def mont(a):
    a = a.astype(np.int64)
    lo = (a.astype(np.uint64) * np.uint64(QINV)).astype(np.uint32).astype(np.int32).astype(np.int64)
    return (a - lo * Q) >> 32


def hw(x):
    u = (x.astype(np.int64) & 0xFFFFFFFF)
    return (_P[(u & 0xFFFF).astype(np.int64)] + _P[((u >> 16) & 0xFFFF).astype(np.int64)]).astype(np.int16)


Z = zetas()
SCHED = []; k = 0; length = 128; BF_SUPP = []
_supp = [1 << i for i in range(N)]
while length > 0:
    for start in range(0, N, 2 * length):
        k += 1; z = int(Z[k])
        for j in range(start, start + length):
            BF_SUPP.append(_supp[j + length])
            SCHED.append((int(np.log2(128 // length)), j, j + length, z))
            u = _supp[j] | _supp[j + length]; _supp[j] = u; _supp[j + length] = u
    length >>= 1
BF_LAYER = np.array([s[0] for s in SCHED])
ZBF = np.array([s[3] for s in SCHED], np.int64)
UPIDX = np.array([s[2] for s in SCHED])           # upper index per butterfly
first_layer = {0: 99}
for m in range(1, 128):
    first_layer[m] = min(BF_LAYER[b] for b in range(1024) if (int(BF_SUPP[b]) >> m) & 1)
groups = {}
for m in range(1, 128):
    groups.setdefault(first_layer[m], []).append(m)
# butterflies that ISOLATE m: m in support, and every OTHER lower in support resolves earlier
usable = {}
for m in range(1, 128):
    Lm = first_layer[m]; lst = []
    for b in range(1024):
        s = int(BF_SUPP[b])
        if not ((s >> m) & 1):
            continue
        ok = True
        for mm in range(0, 128):
            if mm != m and ((s >> mm) & 1) and first_layer[mm] >= Lm:
                ok = False; break
        if ok:
            lst.append(b)
    usable[m] = lst
USED_BFS = sorted({b for m in usable for b in usable[m]})


def ntt_all_twiddle(c):
    """Return per-butterfly twiddle VALUE t=mont(z*upper_pre) for all 1024 bfs, (n,1024)."""
    a = c.copy().astype(np.int64); n = a.shape[0]
    T = np.zeros((n, 1024), np.int64); bi = 0; length = 128
    while length > 0:
        for start in range(0, N, 2 * length):
            for j in range(start, start + length):
                z = SCHED[bi][3]; up = a[:, j + length]; t = mont(z * up)
                T[:, bi] = t; a[:, j + length] = a[:, j] - t; a[:, j] = a[:, j] + t; bi += 1
        length >>= 1
    return T


def ntt_all_stores_hw(c):
    """HW of both butterfly stores (up=a[j]-t, lo=a[j]+t) for all 1024 bfs -> (n,1024) each."""
    a = c.copy().astype(np.int64); n = a.shape[0]
    UP = np.zeros((n, 1024), np.int16); LO = np.zeros((n, 1024), np.int16); bi = 0; length = 128
    while length > 0:
        for start in range(0, N, 2 * length):
            for j in range(start, start + length):
                z = SCHED[bi][3]; up = a[:, j + length]; t = mont(z * up)
                s1 = a[:, j] - t; s = a[:, j] + t; UP[:, bi] = hw(s1); LO[:, bi] = hw(s)
                a[:, j + length] = s1; a[:, j] = s; bi += 1
        length >>= 1
    return UP, LO


def main():
    t0 = time.time()
    c = np.fromfile(LAB + "/c_rej_i32.bin", np.int32).reshape(-1, N)[:30000]
    cube = np.load(EX + "/ntt_c_reject_n45000.npy", mmap_mode="r")
    import sys
    RUN = int(sys.argv[1]) if len(sys.argv) > 1 else 0
    NINFER = int(sys.argv[2]) if len(sys.argv) > 2 else 6000
    rng = np.random.RandomState(20260819 + RUN); idx = rng.permutation(30000)
    tr = idx[:3000]; te = idx[3000:3000 + NINFER]
    print(f"RUN {RUN} train {len(tr)} infer {len(te)} | used bfs {len(USED_BFS)}", flush=True)

    # per-butterfly twiddle-HW models on all USED bfs
    Ttr = ntt_all_twiddle(c[tr]); HTtr = hw(Ttr)
    modelT, scal = {}, {}
    for b in USED_BFS:
        Xb = np.asarray(cube[tr, b, :]).astype(np.float32)
        sc = StandardScaler().fit(Xb); scal[b] = sc
        modelT[b] = Ridge(alpha=10).fit(sc.transform(Xb), HTtr[:, b])
    print(f"models trained {time.time()-t0:.1f}s", flush=True)
    nte = len(te)
    scaT = {b: modelT[b].predict(scal[b].transform(np.asarray(cube[te, b, :]).astype(np.float32))) for b in USED_BFS}
    print(f"SCA HW predicted {time.time()-t0:.1f}s", flush=True)

    ctrue = c[te]; chat = ctrue.copy().astype(np.int64)
    unknown = (ctrue[:, :128] != -1)
    low = chat[:, :128]; low[unknown] = 0; chat[:, :128] = low
    margin = np.full((nte, 128), 99.0)
    for L in sorted(groups):
        ms = groups[L]
        T0 = ntt_all_twiddle(chat)
        c1 = chat.copy()
        for m in ms: c1[:, m] = 1
        T1 = ntt_all_twiddle(c1)
        for m in ms:
            bfs = usable[m]
            d0 = np.zeros(nte); d1 = np.zeros(nte)
            for b in bfs:
                h0 = hw(T0[:, b]).astype(np.float64); h1 = hw(T1[:, b]).astype(np.float64)
                d0 += np.abs(scaT[b] - h0); d1 += np.abs(scaT[b] - h1)
            res = np.where(d1 < d0, 1, 0)
            chat[:, m] = np.where(unknown[:, m], res, chat[:, m])
            margin[:, m] = np.where(unknown[:, m], np.abs(d0 - d1) / max(1, len(bfs)), 99.0)
    perl0 = (chat[:, :128] == ctrue[:, :128]).mean()
    print(f"\n[twiddle pass] lower {perl0:.5f}  {time.time()-t0:.1f}s", flush=True)

    # ===== Gauss-Seidel refinement with STRONG output-HW leak (pooled per-layer models) =====
    UPtr, LOtr = ntt_all_stores_hw(c[tr])
    oU, oL, oS = {}, {}, {}
    for L in range(8):
        bfs = np.where(BF_LAYER == L)[0]
        Xtr = np.concatenate([np.asarray(cube[tr, b, :]).astype(np.float32) for b in bfs], 0)
        sc = StandardScaler().fit(Xtr); oS[L] = sc
        oU[L] = Ridge(alpha=10).fit(sc.transform(Xtr), np.concatenate([UPtr[:, b] for b in bfs]))
        oL[L] = Ridge(alpha=10).fit(sc.transform(Xtr), np.concatenate([LOtr[:, b] for b in bfs]))
    scaUp = np.zeros((nte, 1024)); scaLo = np.zeros((nte, 1024))
    for L in range(8):
        for b in np.where(BF_LAYER == L)[0]:
            X = oS[L].transform(np.asarray(cube[te, b, :]).astype(np.float32))
            scaUp[:, b] = oU[L].predict(X); scaLo[:, b] = oL[L].predict(X)
    print(f"[GS] output models ready {time.time()-t0:.1f}s", flush=True)
    EPS = 3

    def stores_err(cc):
        UP, LO = ntt_all_stores_hw(cc)
        au = np.abs(scaUp - UP); al = np.abs(scaLo - LO)
        return au.sum(1) + al.sum(1), (au > EPS).sum(1) + (al > EPS).sum(1)   # (fine L1, coarse count)
    order = [m for L in sorted(groups) for m in groups[L]]
    base_fine, _ = stores_err(chat)
    for sweep in range(10):
        changed = 0
        for m in order:
            flip = np.where(unknown[:, m], 1 - chat[:, m], chat[:, m])
            cc = chat.copy(); cc[:, m] = flip
            f, _ = stores_err(cc)
            better = (f < base_fine - 1e-9) & unknown[:, m]
            chat[:, m] = np.where(better, flip, chat[:, m])
            base_fine = np.where(better, f, base_fine)
            changed += int(better.sum())
        acc = (chat[:, :128] == ctrue[:, :128]).mean()
        print(f"  GS sweep {sweep}: lower acc {acc:.5f} changed {changed}  {time.time()-t0:.0f}s", flush=True)
        if changed == 0:
            break
    _, conf = stores_err(chat)   # residual output-HW mismatch count (confidence: 0 = clean)

    # c0 by tau
    tau = 39; nz = (chat[:, 1:] != 0).sum(1)
    chat[:, 0] = np.where(ctrue[:, 0] == -1, -1, (nz < tau).astype(np.int64))

    peru = (chat[:, 128:] == ctrue[:, 128:]).mean(); perl = (chat[:, :128] == ctrue[:, :128]).mean()
    all256 = (chat == ctrue).all(1)
    os.makedirs(RESULTS_ROOT, exist_ok=True)
    np.savez_compressed(os.path.join(RESULTS_ROOT, f"11_c_recovered_run{RUN}.npz"),
                        te=te.astype(np.int32), chat=chat.astype(np.int8), conf=conf.astype(np.int32))
    print(f"\nper-coeff upper {peru:.5f} lower {perl:.5f} | per-challenge all256 {all256.mean():.5f} ({all256.sum()}/{nte})", flush=True)
    for L in sorted(groups):
        ms = groups[L]; print(f"  L{L} lower acc {(chat[:,ms]==ctrue[:,ms]).mean():.5f} (nbf/m~{np.mean([len(usable[m]) for m in ms]):.0f})", flush=True)
    import pandas as pd
    kcol = pd.read_csv(LAB + "/labels_45k.csv")["k"].values[te]
    print("\nDISCARD by output-HW mismatch count (conf; 0 = fully consistent)", flush=True)
    print("maxmism | kept | purity(all256) | coverage/1024", flush=True)
    for thr in [0, 1, 2, 3, 5, 10]:
        keep = conf <= thr; pur = all256[keep].mean() if keep.any() else 0
        cov = len(np.unique(kcol[keep & all256]))
        print(f"  <={thr} | {keep.sum():5d} | {pur:.4f} | {cov}/1024", flush=True)
    print(f"\ntotal {time.time()-t0:.1f}s", flush=True)


if __name__ == "__main__":
    main()
