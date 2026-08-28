#!/usr/bin/env python3
"""08: Export recovered rejected (c, z) pairs for downstream s1 recovery.

Each RCoI rejected round gives one boundary constraint for s1:
  z^(poly_l)_{coeff_i} = boundary value in {+g1, +g1-1, -g1, -g1-1},
  with the full recovered challenge c (256 coeffs in {-1,0,1}).
Position k = poly_l*256 + coeff_i is the abort index (= chknorm pulse count,
verified == label k for all RCoI). Downstream method (colleague, replaces ILP)
consumes these (c, z@position) pairs; ~7000 pairs cover l*256=1024 s1 coeffs.

Provenance (honest): models were trained ONLY on RCoI-train (split_seed20260819).
Default pool = held-out RCoI = (cal U attack) & cls<4  -> models never saw these.
  c: 07_ntt_c_upper.keras (crop 56:132, c[128:256]) + 07_ntt_c_lower.keras (0:200, c[0:128])
  z: 02_mlp_full300.keras on reduce32 window at k (X_at_k_reject_int8.npy)
Ground truth (c_rej_i32.bin, labels zval) is exported alongside ONLY for the
colleague to measure their method's noise tolerance; it is not used in recovery.

Outputs (results/cz_pairs/):
  cz_pairs_heldout.npz   arrays incl. c_pred/c_true (N,256) int8
  cz_pairs_heldout.csv   per-pair summary (no 256-wide c)
  README_cz_pairs.txt    format description
GPU 3.
"""
from __future__ import annotations
import json, os
os.environ.setdefault("CUDA_VISIBLE_DEVICES", "3")
os.environ.setdefault("TF_CPP_MIN_LOG_LEVEL", "2")
import numpy as np
import pandas as pd
from sklearn.preprocessing import StandardScaler

from path_config import (
    EXTRACTED_TRACE_ROOT,
    LABEL_ROOT,
    PACKAGE_ROOT,
    RESULTS_ROOT,
    SUPPORT_CODE_ROOT,
)

CODE = SUPPORT_CODE_ROOT
HERE = PACKAGE_ROOT; OUT = RESULTS_ROOT
DST = os.path.join(OUT, "cz_pairs"); os.makedirs(DST, exist_ok=True)
EX = EXTRACTED_TRACE_ROOT
LAB = LABEL_ROOT
N0, N, SEED = 128, 256, 20260819
ZVAL = {0: 131072, 1: 131071, 2: -131072, 3: -131073}   # +g1,+g1-1,-g1,-g1-1  (g1=2^17)
CROP_UP, CROP_LO = (56, 132), (0, 200)


def downsample_other(idx, y, seed=SEED):
    """Reproduce 02's train-set for the z StandardScaler (deterministic)."""
    rng = np.random.RandomState(seed)
    rcoi = idx[y[idx] < 4]; other = idx[y[idx] == 4]
    n_t = min(int((y[idx] == c).sum()) for c in range(4))
    if other.size > n_t:
        other = rng.choice(other, n_t, replace=False)
    out = np.concatenate([rcoi, other]); rng.shuffle(out)
    return out


def main():
    import tensorflow as tf
    for g in tf.config.list_physical_devices("GPU"):
        try: tf.config.experimental.set_memory_growth(g, True)
        except Exception: pass

    lab = pd.read_csv(os.path.join(LAB, "labels_45k.csv"))
    cls = lab["cls"].values
    k_all = lab["k"].values.astype(np.int32)
    poly_l = lab["poly_l"].values.astype(np.int32)
    coeff_i = lab["coeff_i"].values.astype(np.int32)
    zval_true_all = lab["zval"].values.astype(np.int64)
    spl = np.load(os.path.join(OUT, "split_seed20260819.npz")); split = spl["split"]
    rcoi = cls < 4
    tr = np.flatnonzero((split == "train") & rcoi)          # c-model train (RCoI only)
    tr_all = np.flatnonzero(split == "train")               # z-model train (all classes)
    pool = np.flatnonzero(((split == "cal") | (split == "attack")) & rcoi)  # held-out RCoI
    print("held-out RCoI pool", len(pool), "| c-train", len(tr), "| z-train(all)", len(tr_all), flush=True)

    # ---- c recovery ----
    ntt = np.load(os.path.join(EX, "ntt_c_reject_n45000.npy"), mmap_mode="r")
    L0 = np.asarray(ntt[:30000, :N0, :])
    c_true = np.fromfile(os.path.join(LAB, "c_rej_i32.bin"), np.int32).reshape(-1, N)[:30000].astype(np.int8)

    def c_side(keras, crop):
        lo, hi = crop
        sc = StandardScaler().fit(L0[tr][:, :, lo:hi].reshape(-1, hi - lo).astype(np.float32))
        m = tf.keras.models.load_model(os.path.join(OUT, keras), compile=False)
        Xp = L0[pool][:, :, lo:hi].reshape(-1, hi - lo).astype(np.float32)
        pr = m.predict(sc.transform(Xp), batch_size=8192, verbose=0).argmax(1).astype(np.int8) - 1
        return pr.reshape(len(pool), N0)

    c_lo = c_side("07_ntt_c_lower.keras", CROP_LO)   # c[0:128]
    c_up = c_side("07_ntt_c_upper.keras", CROP_UP)   # c[128:256]
    c_pred = np.concatenate([c_lo, c_up], axis=1).astype(np.int8)   # (Npool,256)

    # ---- z recovery ----
    Xk = np.load(os.path.join(OUT, "X_at_k_reject_int8.npy"))       # (45000,300) reduce32 @k
    idx_ztr = downsample_other(tr_all, cls, SEED)
    scz = StandardScaler().fit(Xk[idx_ztr].astype(np.float64))
    mz = tf.keras.models.load_model(os.path.join(OUT, "02_mlp_full300.keras"), compile=False)
    pz = mz.predict(scz.transform(Xk[pool].astype(np.float64)), batch_size=8192, verbose=0)
    z_cls = pz.argmax(1).astype(np.int32); z_conf = pz.max(1).astype(np.float32)
    z_val = np.array([ZVAL.get(int(cc), 0) for cc in z_cls], np.int64)

    # ---- truth + flags ----
    ct = c_true[pool]
    c_ok_lo = (c_lo == ct[:, :N0]).all(1); c_ok_up = (c_up == ct[:, N0:]).all(1)
    c_ok256 = (c_pred == ct).all(1)
    c_nerr_lo = (c_lo != ct[:, :N0]).sum(1); c_nerr_up = (c_up != ct[:, N0:]).sum(1)
    z_cls_true = cls[pool]; z_val_true = zval_true_all[pool]
    z_ok = z_cls == z_cls_true
    pair_ok = c_ok256 & z_ok

    # ---- save ----
    np.savez_compressed(os.path.join(DST, "cz_pairs_heldout.npz"),
        trace_id=pool.astype(np.int32), poly_l=poly_l[pool], coeff_i=coeff_i[pool], k=k_all[pool],
        c_pred=c_pred, z_pred_cls=z_cls, z_pred_val=z_val, z_conf=z_conf,
        c_true=ct, z_true_cls=z_cls_true, z_true_val=z_val_true,
        c_ok256=c_ok256, z_ok=z_ok, pair_ok=pair_ok,
        c_nerr_lower=c_nerr_lo, c_nerr_upper=c_nerr_up)
    df = pd.DataFrame(dict(
        trace_id=pool, poly_l=poly_l[pool], coeff_i=coeff_i[pool], k=k_all[pool],
        z_pred_cls=z_cls, z_pred_val=z_val, z_conf=np.round(z_conf, 4),
        z_true_cls=z_cls_true, z_true_val=z_val_true, z_ok=z_ok,
        c_nerr_lower=c_nerr_lo, c_nerr_upper=c_nerr_up, c_ok256=c_ok256, pair_ok=pair_ok))
    df.to_csv(os.path.join(DST, "cz_pairs_heldout.csv"), index=False)

    # ---- metrics ----
    kp = k_all[pool]
    cov = len(np.unique(kp)); cov_ok = len(np.unique(kp[pair_ok]))
    rep = dict(
        pool="heldout_RCoI(cal|attack)", n_pairs=int(len(pool)),
        c_per_coeff_upper=float((c_up == ct[:, N0:]).mean()),
        c_per_coeff_lower=float((c_lo == ct[:, :N0]).mean()),
        c_all256_correct_frac=float(c_ok256.mean()), c_all256_correct_n=int(c_ok256.sum()),
        z_acc5=float(z_ok.mean()), z_pred_other_on_rcoi=int((z_cls == 4).sum()),
        pair_ok_n=int(pair_ok.sum()), pair_ok_frac=float(pair_ok.mean()),
        coverage_all=f"{cov}/1024", coverage_pair_ok=f"{cov_ok}/1024",
        mean_c_lower_errors_per_pair=float(c_nerr_lo.mean()))
    with open(os.path.join(DST, "cz_pairs_summary.json"), "w") as f:
        json.dump(rep, f, indent=2)
    for kk, vv in rep.items():
        print(f"  {kk}: {vv}", flush=True)

    with open(os.path.join(DST, "README_cz_pairs.txt"), "w") as f:
        f.write(
"Recovered rejected (c, z) pairs -- D2 (ML-DSA-44), known key.\n"
"Source: side-channel recovery on held-out RCoI rounds (models trained only on\n"
"RCoI-train of split_seed20260819; these rounds were never in training).\n\n"
"cz_pairs_heldout.npz keys:\n"
"  trace_id (N)       row id into the 45k capture\n"
"  c_pred   (N,256)   RECOVERED challenge, int8 in {-1,0,1}  <-- use this as c\n"
"  z_pred_val (N)     RECOVERED boundary value at the RCoI coeff, int64\n"
"                     in {+131072,+131071,-131072,-131073} = {+g1,+g1-1,-g1,-g1-1}\n"
"  poly_l,coeff_i (N) RCoI position: z of polynomial poly_l, coefficient coeff_i\n"
"  k (N)              = poly_l*256+coeff_i (abort index; SCA = chknorm pulse count)\n"
"  z_pred_cls (N)     0=+g1 1=+g1-1 2=-g1 3=-g1-1 (4=other, should not occur)\n"
"  z_conf (N)         z softmax confidence (optional filter)\n"
"  --- verification only (do NOT feed to recovery; needs the secret key) ---\n"
"  c_true (N,256), z_true_cls (N), z_true_val (N)\n"
"  c_ok256 (N)        c_pred exactly equals c_true (all 256)\n"
"  z_ok (N)           z_pred_cls == z_true_cls\n"
"  pair_ok (N)        c_ok256 & z_ok  (fully-correct pair)\n"
"  c_nerr_lower/upper (N)  # wrong c coeffs in lower[0:128]/upper[128:256]\n\n"
"NOTE: upper half c[128:256] is 100% correct; lower half c[0:128] ~98.7%/coeff,\n"
"errors are 0<->+1 only (NTT first-layer limit). If your method needs fully-\n"
"correct c per pair, use rows with c_ok256/pair_ok, or request NTT layer-combine.\n")
    print("\nDONE 08 -> " + DST, flush=True)


if __name__ == "__main__":
    main()
