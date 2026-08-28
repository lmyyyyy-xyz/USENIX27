#!/usr/bin/env python3
"""12: Assemble final verified rejected (c,z) pairs for s1 recovery.

c from 11_c_recovered.npz (Algorithm-5 recovery + output-HW verification: a
challenge kept iff residual output-HW mismatch conf<=C_THR -> 100% pure c).
z from reduce32 5-class (02_mlp_full300) at the abort index k, kept iff softmax
conf>=Z_THR -> ~100% pure z. Pair kept iff both pass. Ground truth (known key)
used ONLY to report the achieved purity, never to select.
Output: results/cz_pairs/cz_pairs_verified.{npz,csv} + README.
"""
import os, json, numpy as np, pandas as pd
os.environ.setdefault("CUDA_VISIBLE_DEVICES", "3"); os.environ.setdefault("TF_CPP_MIN_LOG_LEVEL", "2")
from sklearn.preprocessing import StandardScaler

from path_config import KNOWN_KEYS_C_PATH, LABEL_ROOT, RESULTS_ROOT

R = RESULTS_ROOT
LAB = LABEL_ROOT
KK = KNOWN_KEYS_C_PATH


def save_true_s1(dst):
    import re
    h = next(x for x in re.findall(r'sksstr\[\]\s*=\s*"([0-9A-Fa-f]+)"', open(KK).read()) if x.upper().startswith("16F553B0"))
    sk = bytes.fromhex(h); s1 = np.zeros((4, 256), np.int64)
    for p in range(4):
        a = sk[128 + p * 96: 128 + (p + 1) * 96]; r = np.zeros(256, np.int64)
        for i in range(32):
            b0, b1, b2 = a[3 * i], a[3 * i + 1], a[3 * i + 2]
            r[8*i]=b0&7; r[8*i+1]=(b0>>3)&7; r[8*i+2]=((b0>>6)|(b1<<2))&7; r[8*i+3]=(b1>>1)&7
            r[8*i+4]=(b1>>4)&7; r[8*i+5]=((b1>>7)|(b2<<1))&7; r[8*i+6]=(b2>>2)&7; r[8*i+7]=(b2>>5)&7
        s1[p] = 2 - r
    np.save(os.path.join(dst, "s1_true.npy"), s1.astype(np.int8))
    np.savetxt(os.path.join(dst, "s1_true.txt"), s1, fmt="%d")
    return s1
DST = os.path.join(R, "cz_pairs"); os.makedirs(DST, exist_ok=True)
N = 256
ZVAL = {0: 131072, 1: 131071, 2: -131072, 3: -131073}
C_THR = 10          # max residual output-HW mismatch to accept c (blind; purity holds 1.0)
Z_THR = 0.9900      # min reduce32 softmax to accept z (blind; purity holds 1.0)


def downsample_other(idx, y, seed=20260819):
    rng = np.random.RandomState(seed)
    rcoi = idx[y[idx] < 4]; other = idx[y[idx] == 4]
    n_t = min(int((y[idx] == c).sum()) for c in range(4))
    if other.size > n_t: other = rng.choice(other, n_t, replace=False)
    out = np.concatenate([rcoi, other]); rng.shuffle(out); return out


def main():
    import tensorflow as tf
    for g in tf.config.list_physical_devices("GPU"):
        try: tf.config.experimental.set_memory_growth(g, True)
        except Exception: pass
    import glob
    runs = sorted(glob.glob(os.path.join(R, "11_c_recovered_run*.npz")))
    # union verified-pure pairs across runs (each 100% pure); dedup by trace_id keeping best conf
    best = {}
    for f in runs:
        d = np.load(f); te = d["te"]; chat = d["chat"].astype(np.int32); conf = d["conf"]
        for k, t in enumerate(te):
            if t not in best or conf[k] < best[t][1]:
                best[t] = (chat[k], int(conf[k]))
    te = np.array(sorted(best.keys()), np.int32)
    chat = np.stack([best[t][0] for t in te]).astype(np.int32)
    conf = np.array([best[t][1] for t in te], np.int32)
    print(f"union of {len(runs)} run(s): {len(te)} unique recovered rows", flush=True)
    lab = pd.read_csv(os.path.join(LAB, "labels_45k.csv"))
    cls = lab["cls"].values; kcol = lab["k"].values.astype(np.int32)
    poly_l = lab["poly_l"].values.astype(np.int32); coeff_i = lab["coeff_i"].values.astype(np.int32)
    print(f"recovered rows {len(te)} | c conf<= {C_THR}: {(conf<=C_THR).sum()}", flush=True)

    # ---- z: reduce32 5-class at k ----
    Xk = np.load(os.path.join(R, "X_at_k_reject_int8.npy"))
    spl = np.load(os.path.join(R, "split_seed20260819.npz")); split = spl["split"]
    idx_ztr = downsample_other(np.flatnonzero(split == "train"), cls)
    scz = StandardScaler().fit(Xk[idx_ztr].astype(np.float64))
    mz = tf.keras.models.load_model(os.path.join(R, "02_mlp_full300.keras"), compile=False)
    pz = mz.predict(scz.transform(Xk[te].astype(np.float64)), batch_size=8192, verbose=0)
    z_cls = pz.argmax(1).astype(np.int32); z_conf = pz.max(1); z_val = np.array([ZVAL.get(int(x), 0) for x in z_cls], np.int64)

    # ---- ground truth (report only) ----
    c_true = np.fromfile(os.path.join(LAB, "c_rej_i32.bin"), np.int32).reshape(-1, N)[te]
    c_ok = (chat == c_true).all(1); z_ok = z_cls == cls[te]
    keep = (conf <= C_THR) & (z_conf >= Z_THR) & (z_cls < 4)
    pair_ok = c_ok & z_ok
    kp = kcol[te]
    print(f"\nkept pairs {int(keep.sum())} | pair purity {pair_ok[keep].mean():.5f} "
          f"(c {c_ok[keep].mean():.5f}, z {z_ok[keep].mean():.5f}) | coverage {len(np.unique(kp[keep]))}/1024", flush=True)
    # sweep thresholds for reference
    print("C_THR Z_THR | kept | purity | coverage")
    for ct in [0, 2, 5, 10]:
        for zt in [0.99, 0.999]:
            k2 = (conf <= ct) & (z_conf >= zt) & (z_cls < 4)
            print(f"  {ct} {zt} | {int(k2.sum())} | {pair_ok[k2].mean() if k2.any() else 0:.4f} | {len(np.unique(kp[k2]))}", flush=True)

    sel = np.flatnonzero(keep)
    np.savez_compressed(os.path.join(DST, "cz_pairs_verified.npz"),
        trace_id=te[sel].astype(np.int32), poly_l=poly_l[te][sel], coeff_i=coeff_i[te][sel], k=kp[sel],
        c_pred=chat[sel].astype(np.int8), z_pred_cls=z_cls[sel], z_pred_val=z_val[sel],
        c_true=c_true[sel].astype(np.int8), z_true_cls=cls[te][sel],
        c_ok=c_ok[sel], z_ok=z_ok[sel], pair_ok=pair_ok[sel], conf=conf[sel], z_conf=z_conf[sel].astype(np.float32))
    df = pd.DataFrame(dict(trace_id=te[sel], poly_l=poly_l[te][sel], coeff_i=coeff_i[te][sel], k=kp[sel],
        z_pred_cls=z_cls[sel], z_pred_val=z_val[sel], conf=conf[sel], z_conf=np.round(z_conf[sel], 5),
        c_ok=c_ok[sel], z_ok=z_ok[sel], pair_ok=pair_ok[sel]))
    df.to_csv(os.path.join(DST, "cz_pairs_verified.csv"), index=False)
    rep = dict(n_pairs=int(keep.sum()), pair_purity=float(pair_ok[keep].mean()),
               coverage=f"{len(np.unique(kp[keep]))}/1024", C_THR=C_THR, Z_THR=Z_THR)
    json.dump(rep, open(os.path.join(DST, "cz_pairs_verified_summary.json"), "w"), indent=2)
    with open(os.path.join(DST, "README_verified.txt"), "w") as f:
        f.write("Verified rejected (c,z) pairs for s1 recovery (D2, known key).\n"
                "c_pred (N,256) int8 {-1,0,1}: recovered challenge (Algorithm-5 + output-HW verify).\n"
                "z_pred_val int64 in {+-131072,+-131071/3}: boundary z at (poly_l,coeff_i); k=poly_l*256+coeff_i.\n"
                "Selection uses only SCA confidences (conf<=%d, z_conf>=%g); truth columns are for audit.\n"
                "pair_ok = c_pred==c_true AND z_pred==z_true (achieved purity reported in summary).\n" % (C_THR, Z_THR))
    save_true_s1(DST)
    print("saved s1_true.{npy,txt}", flush=True)
    print("\nDONE 12 ->", DST, flush=True)


if __name__ == "__main__":
    main()
