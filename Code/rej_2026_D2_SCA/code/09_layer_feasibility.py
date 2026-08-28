#!/usr/bin/env python3
"""Feasibility gate for Algorithm 5: does HW of NTT intermediates leak in
later-layer butterfly windows (cube windows [j*128:(j+1)*128])?

Simulate the exact firmware NTT (dilithium_rej_filter/ntt.c) on c_rej, record
per-butterfly HW of: upper input (pre), twiddle product t, lower output, upper
output. Then PCC each cube window against those HWs, per layer.
"""
import re, sys, numpy as np

from path_config import (
    EXTRACTED_TRACE_ROOT,
    LABEL_ROOT,
    NTT_C_PATH,
    SUPPORT_CODE_ROOT,
)

sys.path.insert(0, SUPPORT_CODE_ROOT)
from sca_utils import corr_fast

NTT_C = NTT_C_PATH
EX = EXTRACTED_TRACE_ROOT
LAB = LABEL_ROOT
Q, QINV = 8380417, 58728449
N = 256


def load_zetas():
    txt = open(NTT_C).read()
    m = re.search(r"zetas\[MLDSA_N\]\s*=\s*\{(.+?)\};", txt, re.S)
    nums = [int(x) for x in re.findall(r"-?\d+", m.group(1))]
    assert len(nums) == 256, len(nums)
    return np.array(nums, dtype=np.int64)


def mont(a):  # montgomery_reduce, vectorized, matches C (uint64_t)a*QINV -> int32 low bits
    a = a.astype(np.int64)
    lo = (a.astype(np.uint64) * np.uint64(QINV)).astype(np.uint32).astype(np.int32).astype(np.int64)
    return ((a - lo * Q) >> 32).astype(np.int64)


def hw32(x):
    u = x.astype(np.int32).astype(np.uint32)
    return np.unpackbits(u.view(np.uint8).reshape(-1, 4), axis=1, bitorder="little").sum(1).astype(np.float64)


def ntt_trace(a, zetas):
    """a: (n,256) int64. Returns per-butterfly HW arrays (n,1024) for
    upper_pre, tprod, lower_out, upper_out; and butterfly meta (layer, jlo, jup, zidx)."""
    n = a.shape[0]
    a = a.copy().astype(np.int64)
    HWup = np.empty((n, 1024)); HWt = np.empty((n, 1024))
    HWlo = np.empty((n, 1024)); HWuo = np.empty((n, 1024))
    meta = []
    k = 0; bf = 0
    length = 128
    while length > 0:
        for start in range(0, N, 2 * length):
            k += 1; zeta = int(zetas[k])
            for j in range(start, start + length):
                up = a[:, j + length].copy()
                t = mont(zeta * up)
                HWup[:, bf] = hw32(up); HWt[:, bf] = hw32(t)
                HWlo[:, bf] = hw32(a[:, j] - t); HWuo[:, bf] = hw32(a[:, j] + t)
                a[:, j + length] = a[:, j] - t
                a[:, j] = a[:, j] + t
                meta.append((int(np.log2(128 // length)), j, j + length, k))
                bf += 1
        length >>= 1
    return HWup, HWt, HWlo, HWuo, meta


def main():
    zetas = load_zetas()
    assert int(zetas[1]) == 25847
    c = np.fromfile(LAB + "/c_rej_i32.bin", np.int32).reshape(-1, N)[:30000]
    n = 4000
    sub = np.arange(n)  # first 4000 rows are RCoI
    cube = np.load(EX + "/ntt_c_reject_n45000.npy", mmap_mode="r")
    HWup, HWt, HWlo, HWuo, meta = ntt_trace(c[sub].astype(np.int64), zetas)
    print("simulated NTT; butterflies", len(meta), flush=True)
    # sanity: layer0 upper leak should match earlier (window j vs HW(upper)=HW(c[j+128]))
    print("\nlayer | best|PCC| for HW(upper_pre)/HW(t)/HW(lower_out)/HW(upper_out)  (peak over 128 bf x 200 samp)")
    for layer in range(8):
        bfs = [b for b, m in enumerate(meta) if m[0] == layer]
        # PCC per butterfly window vs its own HW; take max |PCC| over samples, mean over butterflies, and global peak
        def layer_pcc(HW):
            peaks = []
            for b in bfs:
                O = np.asarray(cube[sub, b, :]).astype(np.float64)
                P = HW[:, b:b + 1]
                if P.std() < 1e-9:
                    continue
                peaks.append(np.nanmax(np.abs(corr_fast(O, P)[0])))
            return (np.nanmax(peaks) if peaks else 0.0, np.nanmean(peaks) if peaks else 0.0)
        pu = layer_pcc(HWup); pt = layer_pcc(HWt); pl = layer_pcc(HWlo); po = layer_pcc(HWuo)
        print(f"  L{layer}: up(max/mean {pu[0]:.2f}/{pu[1]:.2f})  t({pt[0]:.2f}/{pt[1]:.2f})  "
              f"lo_out({pl[0]:.2f}/{pl[1]:.2f})  up_out({po[0]:.2f}/{po[1]:.2f})", flush=True)


if __name__ == "__main__":
    main()
