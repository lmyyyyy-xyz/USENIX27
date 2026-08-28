#!/usr/bin/env python3
"""14: Solve the TCHES ILP for s1 from (c,z) pairs and compare to the true key.

Per s1 polynomial p, each pair (challenge c, RCoI position i, z-class) gives
  lb <= <rot(c,i), s1_p> <= ub .
Decomposes into L independent 256-var integer programs (s1 in [-eta,eta]).
Solve with scipy HiGHS milp (feasibility), compare to true s1.
Usage: 14_ilp_solve.py {true N | recovered}
"""
import re, sys, time, numpy as np, pandas as pd
from scipy.optimize import milp, LinearConstraint, Bounds

from path_config import KNOWN_KEYS_C_PATH, LABEL_ROOT, RESULTS_ROOT

LAB = LABEL_ROOT
KK = KNOWN_KEYS_C_PATH
R = RESULTS_ROOT
N, L, ETA, BETA = 256, 4, 2, 78
BOUND = {0: (0, BETA), 1: (-1, BETA), 2: (-BETA, -1), 3: (-BETA, -2)}


def load_s1():
    txt = open(KK).read()
    hexs = next(h for h in re.findall(r'sksstr\[\]\s*=\s*"([0-9A-Fa-f]+)"', txt) if h.upper().startswith("16F553B0"))
    sk = bytes.fromhex(hexs); off = 128; s1 = np.zeros((L, N), np.int64)
    for p in range(L):
        a = sk[off + p * 96: off + (p + 1) * 96]
        r = np.zeros(N, np.int64)
        for i in range(32):
            b0, b1, b2 = a[3 * i], a[3 * i + 1], a[3 * i + 2]
            r[8*i+0]=b0&7; r[8*i+1]=(b0>>3)&7; r[8*i+2]=((b0>>6)|(b1<<2))&7; r[8*i+3]=(b1>>1)&7
            r[8*i+4]=(b1>>4)&7; r[8*i+5]=((b1>>7)|(b2<<1))&7; r[8*i+6]=(b2>>2)&7; r[8*i+7]=(b2>>5)&7
        s1[p] = ETA - r
    return s1


def rot_row(c, i):
    j = np.arange(N); idx = i - j
    row = np.empty(N, np.int64); pos = idx >= 0
    row[pos] = c[idx[pos]]; row[~pos] = -c[idx[~pos] + N]
    return row


def solve_poly(rows, los, his, s1p, tl=120):
    """Integer feasibility with a real objective so HiGHS branch-and-bound has an LP
    bound to prune with (pure c=0 feasibility stalls). With enough tight constraints the
    integer feasible region is the single point s1."""
    t0 = time.time()
    A = np.array(rows, float)
    con = LinearConstraint(A, np.array(los, float), np.array(his, float))
    res = milp(c=np.ones(N), constraints=[con], integrality=np.ones(N),
               bounds=Bounds(-ETA, ETA), options={"time_limit": tl})
    dt = time.time() - t0
    if res.x is None:
        return None, (0, 0), dt
    x = np.round(res.x).astype(np.int64)
    return x, (N, int((x == s1p).sum())), dt


def main():
    s1 = load_s1()
    lab = pd.read_csv(LAB + "/labels_45k.csv")
    cls = lab["cls"].values; poly_l = lab["poly_l"].values; coeff_i = lab["coeff_i"].values
    src = sys.argv[1] if len(sys.argv) > 1 else "true"
    if src == "recovered":
        d = np.load(R + "/cz_pairs/cz_pairs_verified.npz")
        tid = d["trace_id"]; C = d["c_pred"].astype(np.int64); zc = d["z_pred_cls"]; pl = d["poly_l"]; ci = d["coeff_i"]
        print(f"recovered pairs {len(tid)}", flush=True)
    else:
        M = int(sys.argv[2]) if len(sys.argv) > 2 else 7000
        rc = np.flatnonzero(cls < 4); rng = np.random.RandomState(1); rc = rng.choice(rc, min(M, len(rc)), replace=False)
        C = np.fromfile(LAB + "/c_rej_i32.bin", np.int32).reshape(-1, N)[rc].astype(np.int64)
        zc = cls[rc]; pl = poly_l[rc]; ci = coeff_i[rc]
        print(f"TRUE pairs {len(rc)}", flush=True)
    tot = 0
    for p in range(L):
        sel = np.flatnonzero(pl == p)
        rows = []; los = []; his = []; covered = set()
        for k in sel:
            row = rot_row(C[k], int(ci[k])); lo, hi = BOUND[int(zc[k])]
            rows.append(row); los.append(lo); his.append(hi); covered.add(int(ci[k]))
        rec, (pinned, correct), dt = solve_poly(rows, los, his, s1[p])
        cov = len(covered)
        print(f"  poly {p}: LP-pinned {pinned}/256, correct {correct}/256 | n_constr {len(rows)} pos covered {cov}/256  {dt:.1f}s", flush=True)
        tot += correct
    print(f"TOTAL s1 coeffs uniquely recovered {tot}/{L*N}", flush=True)


if __name__ == "__main__":
    main()
