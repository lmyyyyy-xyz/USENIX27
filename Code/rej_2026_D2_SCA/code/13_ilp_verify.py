#!/usr/bin/env python3
"""13: ILP setup verification + solve.  (TCHES 2025 Thm 1)

Unpack true s1 from the D2 secret key; for each rejected round check the boundary
constraint x_i = (c * s1)_i (negacyclic) lies in the interval its z-class implies:
  cls0 z=+g1   : 0  <= x <= b       cls2 z=-g1   : -b <= x <= -1
  cls1 z=+g1-1 : -1 <= x <= b       cls3 z=-g1-1 : -b <= x <= -2   (b=BETA=78)
Then build the ILP (C s1 <= b) from RECOVERED pairs and solve per polynomial,
comparing to the true s1.
"""
import re, sys, numpy as np

from path_config import KNOWN_KEYS_C_PATH, LABEL_ROOT

LAB = LABEL_ROOT
KK = KNOWN_KEYS_C_PATH
N, L, ETA, BETA = 256, 4, 2, 78
SEED_OFF = 32 + 32 + 64          # rho(32)+key(32)+tr(64); s1 packed next
POLYETA_PACKEDBYTES = 96


def load_s1():
    txt = open(KK).read()
    sks = [m for m in re.findall(r'sksstr\[\]\s*=\s*"([0-9A-Fa-f]+)"', txt)]
    # D2 key is the one starting with the D2 rho 16F553B0
    hexs = next(h for h in sks if h.upper().startswith("16F553B0"))
    sk = bytes.fromhex(hexs)
    s1 = np.zeros((L, N), np.int64)
    for p in range(L):
        a = sk[SEED_OFF + p * POLYETA_PACKEDBYTES: SEED_OFF + (p + 1) * POLYETA_PACKEDBYTES]
        r = np.zeros(N, np.int64)
        for i in range(N // 8):
            b0, b1, b2 = a[3 * i], a[3 * i + 1], a[3 * i + 2]
            r[8 * i + 0] = b0 & 7
            r[8 * i + 1] = (b0 >> 3) & 7
            r[8 * i + 2] = ((b0 >> 6) | (b1 << 2)) & 7
            r[8 * i + 3] = (b1 >> 1) & 7
            r[8 * i + 4] = (b1 >> 4) & 7
            r[8 * i + 5] = ((b1 >> 7) | (b2 << 1)) & 7
            r[8 * i + 6] = (b2 >> 2) & 7
            r[8 * i + 7] = (b2 >> 5) & 7
        s1[p] = ETA - r
    return s1


def negacyclic(c, s):
    full = np.convolve(c, s)                       # length 2N-1
    x = full[:N].copy(); x[:N - 1] -= full[N:]     # reduce mod X^N+1
    return x


BOUND = {0: (0, BETA), 1: (-1, BETA), 2: (-BETA, -1), 3: (-BETA, -2)}


def main():
    s1 = load_s1()
    print("s1 shape", s1.shape, "range", int(s1.min()), int(s1.max()), "|| per-poly nnz",
          [int((s1[p] != 0).sum()) for p in range(L)], flush=True)
    import pandas as pd
    lab = pd.read_csv(LAB + "/labels_45k.csv")
    cls = lab["cls"].values; poly_l = lab["poly_l"].values; coeff_i = lab["coeff_i"].values
    c = np.fromfile(LAB + "/c_rej_i32.bin", np.int32).reshape(-1, N)
    rc = np.flatnonzero(cls < 4)
    ok = 0; bad = 0
    xs = np.zeros(len(rc))
    for n, r in enumerate(rc):
        x = negacyclic(c[r], s1[poly_l[r]])[coeff_i[r]]
        xs[n] = x
        lo, hi = BOUND[int(cls[r])]
        if lo <= x <= hi: ok += 1
        else: bad += 1
    print(f"boundary-constraint check on {len(rc)} RCoI rounds (TRUE s1): satisfied {ok}, violated {bad}", flush=True)
    print("x_i stats: min/med/max", int(xs.min()), int(np.median(xs)), int(xs.max()), "|x|<=BETA:", int((np.abs(xs) <= BETA).sum()), flush=True)


if __name__ == "__main__":
    main()
