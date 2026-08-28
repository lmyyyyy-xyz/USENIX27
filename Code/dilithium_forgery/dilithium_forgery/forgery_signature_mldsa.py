import argparse
import subprocess
from pathlib import Path

import numpy as np


BASE_DIR = Path(__file__).resolve().parent
MEDIAN_DIR = BASE_DIR / "median_value_mldsa"
OUTPUT_DIR = BASE_DIR / "forgery_signature_output_mldsa"
MLDSA_C_DIR = BASE_DIR / "c_file_mldsa"
MEDIAN_DIR.mkdir(parents=True, exist_ok=True)
OUTPUT_DIR.mkdir(parents=True, exist_ok=True)

L = 4
K = 4
N = 256
GAMMA1 = 1 << 17
BETA = 78
OMEGA = 80


def get_s1(filename):
    rows = []
    with open(filename, "r", encoding="utf-8") as f:
        for line in f:
            values = [int(x) for x in line.split()]
            if values:
                rows.append(values)

    if len(rows) != L or any(len(row) != N for row in rows):
        raise ValueError(
            f"s1 must have shape {L}x{N}, "
            f"got {[len(row) for row in rows]}"
        )

    if any(x not in (-2, -1, 0, 1, 2) for row in rows for x in row):
        raise ValueError(
            "ML-DSA-44 s1 coefficients must be in {-2,-1,0,1,2}"
        )
    return rows


def read_data(metadata_file, s1_file, pk_file):
    """Read messages from the original metadata and external s1/pk."""
    s1 = get_s1(s1_file)
    pk = "".join(Path(pk_file).read_text(encoding="ascii").split()).upper()

    if len(pk) != 2 * 1312:
        raise ValueError("pk file must contain exactly 2624 hex characters")
    if any(ch not in "0123456789ABCDEF" for ch in pk):
        raise ValueError("pk file contains non-hexadecimal characters")

    profiling_data = np.load(metadata_file, allow_pickle=True)
    messages = [str(message).strip() for message in profiling_data["msg"]]
    if not messages:
        raise ValueError("messages file contains no messages")

    for message in messages:
        if len(message) % 2:
            raise ValueError("each message must have an even number of hex digits")
        if any(ch not in "0123456789abcdefABCDEF" for ch in message):
            raise ValueError("message contains non-hexadecimal characters")

    return messages, s1, pk


def _read_matrix(path, rows, cols):
    values = []
    for line in Path(path).read_text(encoding="utf-8").splitlines():
        row = [int(x) for x in line.split()]
        if row:
            values.append(row)

    if len(values) != rows or any(len(row) != cols for row in values):
        raise ValueError(f"{path} does not contain a {rows}x{cols} matrix")
    return values


def _max_abs(matrix):
    return max(abs(value) for row in matrix for value in row)


def _write_s1(s1):
    """Write mathematical ML-DSA coefficients without legacy recoding."""
    text = "\n".join(" ".join(str(x) for x in row) for row in s1) + "\n"
    (MEDIAN_DIR / "write_s1.txt").write_text(text, encoding="ascii")


def _ensure_binary():
    binary = MLDSA_C_DIR / "PQCgenKAT_sign"
    if not binary.exists():
        subprocess.run(["make"], cwd=MLDSA_C_DIR, check=True)


def forgery_sign(message, s1, pk):
    """Run the ML-DSA-44 candidate loop with the supplied s1 and pk."""
    _ensure_binary()

    (MEDIAN_DIR / "m.txt").write_text(
        f"m = {message}", encoding="ascii"
    )
    (MEDIAN_DIR / "pk.txt").write_text(pk + "\n", encoding="ascii")

    # Each message gets an independent copy.  The ML-DSA adapter expects
    # mathematical coefficients in {-2,-1,0,1,2}; no Dilithium digit
    # conversion (-1 -> 3, -2 -> 4) is performed here.
    s1_work = [row[:] for row in s1]
    _write_s1(s1_work)

    response_file = MLDSA_C_DIR / "PQCsignKAT_2560.rsp"

    for iteration in range(100):
        result = subprocess.run(
            ["./PQCgenKAT_sign", str(iteration)],
            cwd=MLDSA_C_DIR,
            capture_output=True,
            text=True,
            check=False,
        )

        if result.stdout:
            print(result.stdout, end="")
        if result.stderr:
            print(result.stderr, end="")

        if result.returncode != 0:
            print(
                f"iteration {iteration + 1}: candidate rejected by C "
                f"(returncode={result.returncode})"
            )
            continue

        z = _read_matrix(MEDIAN_DIR / "z.txt", L, N)
        t = _read_matrix(MEDIAN_DIR / "t.txt", K, N)
        w = _read_matrix(MEDIAN_DIR / "w1.txt", K, N)
        hint_weight = sum(
            a != b
            for t_row, w_row in zip(t, w)
            for a, b in zip(t_row, w_row)
        )
        max_abs_z = _max_abs(z)
        accepted = (
            max_abs_z < GAMMA1 - BETA
            and hint_weight <= OMEGA
        )
        print(
            f"iteration {iteration + 1}: "
            f"hint_weight={hint_weight}, "
            f"max_abs_z={max_abs_z}, accepted={accepted}"
        )

        if accepted and response_file.exists():
            for line in response_file.read_text(encoding="ascii").splitlines():
                if line.startswith("sm = "):
                    return line.split("=", 1)[1].strip()

    return ""


def main():
    parser = argparse.ArgumentParser(
        description="Run the ML-DSA-44 research forgery experiment"
    )
    parser.add_argument(
        "--metadata-file",
        default=str(BASE_DIR / "input_s1_pk_m" / "meta_data_part0.npz"),
    )
    parser.add_argument(
        "--s1-file",
        default=str(BASE_DIR / "input_s1_pk_m" / "s1_true.txt"),
    )
    parser.add_argument(
        "--pk-file",
        default=str(BASE_DIR / "input_s1_pk_m" / "pk_16.txt"),
    )
    args = parser.parse_args()

    messages, s1, pk = read_data(
        args.metadata_file,
        args.s1_file,
        args.pk_file,
    )
    outputs = [forgery_sign(message, s1, pk) for message in messages]

    if any(not sm for sm in outputs):
        failed = [str(i + 1) for i, sm in enumerate(outputs) if not sm]
        raise RuntimeError(
            "no ML-DSA-44 candidate passed verification for message(s): "
            + ", ".join(failed)
        )

    output_file = OUTPUT_DIR / "new_sm_mldsa.txt"
    output_file.write_text(
        "".join(f"sm = {sm}\n" for sm in outputs),
        encoding="ascii",
    )
    print(f"wrote {len(outputs)} result(s) to {output_file}")


if __name__ == "__main__":
    main()