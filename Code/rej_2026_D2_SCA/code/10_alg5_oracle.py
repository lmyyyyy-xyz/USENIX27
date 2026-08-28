#!/usr/bin/env python3
"""Algorithm 5 (§5.3.2) intrinsic success rate with ORACLE Hamming weights.

Reproduces the paper's Fig 5 (SR vs tolerance epsilon) and gives the intrinsic
c-recovery discard rate -- independent of SCA model noise.

Method: after the first layer we know all uppers c[128:256] and all lower -1s.
For each unknown lower coeff m (true value in {0,1}), give it the full true
context (all other coeffs = truth, as the sequential Alg-5 schedule guarantees)
and ask: are hypotheses c[m]=0 and c[m]=1 distinguishable under tolerance eps?
distinguishable[m] = ( max over all measured intermediate HWs |HW(hyp0)-HW(hyp1)| > eps ).
Measured intermediates per butterfly = twiddle product t=c', and both outputs
a[j]+t, a[j]-t (the inner coeffs c). A challenge is recovered (SR success) iff
every unknown lower coeff is distinguishable; otherwise Alg 5 returns Unsuccess
(discard). c0 fixed by tau. This upper-bounds SR and matches the paper's analysis.
"""
import re, numpy as np

from path_config import LABEL_ROOT, NTT_C_PATH

NTT_C = NTT_C_PATH
LAB = LABEL_ROOT
Q, QINV, N = 8380417, 58728449, 256
_POP16 = np.array([bin(i).count("1") for i in range(1 << 16)], dtype=np.int16)


def load_zetas():
    m = re.search(r"zetas\[MLDSA_N\]\s*=\s*\{(.+?)\};", open(NTT_C).read(), re.S)
    z = np.array([int(x) for x in re.findall(r"-?\d+", m.group(1))], np.int64)
    assert z.size == 256 and z[1] == 25847
    return z


def mont(a):
    a = a.astype(np.int64)
    lo = (a.astype(np.uint64) * np.uint64(QINV)).astype(np.uint32).astype(np.int32).astype(np.int64)
    return (a - lo * Q) >> 32


def hw(x):  # popcount of int32 two's complement, vectorized
    u = (x.astype(np.int64) & 0xFFFFFFFF)
    return (_POP16[(u & 0xFFFF).astype(np.int64)] + _POP16[((u >> 16) & 0xFFFF).astype(np.int64)]).astype(np.int16)


def maxdiff_flip(cbatch, m, zetas):
    """Run NTT for c[m]=0 and c[m]=1 in lockstep; return per-row max |HW diff|
    over all butterflies' {t, out_lo, out_up}."""
    n = cbatch.shape[0]
    a0 = cbatch.copy().astype(np.int64); a0[:, m] = 0
    a1 = cbatch.copy().astype(np.int64); a1[:, m] = 1
    md = np.zeros(n, np.int16)
    k = 0; length = 128
    while length > 0:
        for start in range(0, N, 2 * length):
            k += 1; zeta = int(zetas[k])
            for j in range(start, start + length):
                u0 = a0[:, j + length]; u1 = a1[:, j + length]
                t0 = mont(zeta * u0); t1 = mont(zeta * u1)
                lo0 = a0[:, j] + t0; lo1 = a1[:, j] + t1
                up0 = a0[:, j] - t0; up1 = a1[:, j] - t1
                d = np.abs(hw(t0) - hw(t1))
                d = np.maximum(d, np.abs(hw(lo0) - hw(lo1)))
                d = np.maximum(d, np.abs(hw(up0) - hw(up1)))
                md = np.maximum(md, d)
                a0[:, j + length] = up0; a0[:, j] = lo0
                a1[:, j + length] = up1; a1[:, j] = lo1
        length >>= 1
    return md


def main():
    import time
    zetas = load_zetas()
    c = np.fromfile(LAB + "/c_rej_i32.bin", np.int32).reshape(-1, N)[:30000]
    n = 3000
    cb = c[:n]
    t0 = time.time()
    MD = np.zeros((n, 128), np.int16)          # per-row, per-lower-position max HW-diff between 0/1 hyp
    unknown = (cb[:, :128] != -1)               # lower positions with value in {0,1}
    for m in range(128):
        MD[:, m] = maxdiff_flip(cb, m, zetas)
        if (m + 1) % 32 == 0:
            print(f"  m={m+1}/128  {time.time()-t0:.1f}s", flush=True)
    # tau known -> c0 fixed; treat position 0 as resolvable by tau (paper), exclude from ambiguity
    unknown[:, 0] = False
    print("\neps |  per-coeff distinguishable  |  per-challenge SR (all unknowns ok)  | mean #ambiguous/challenge")
    for eps in range(0, 7):
        dist = MD > eps                          # distinguishable if some HW diff exceeds tolerance
        # a coeff is a problem only if it is unknown AND not distinguishable
        amb = unknown & ~dist
        per_coeff = 1.0 - amb.sum() / unknown.sum()
        sr = (amb.sum(1) == 0).mean()
        print(f"  {eps} |        {per_coeff:.5f}          |            {sr:.5f}                | {amb.sum(1).mean():.3f}")
    np.save("/tmp/alg5_MD.npy", MD)
    print("\nmean unknown lowers/challenge", unknown.sum(1).mean(), "(nonzero lower {0,1} count)")


if __name__ == "__main__":
    main()
