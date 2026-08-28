"""Parameter and secret-key helpers for the Dilithium/ML-DSA t0 attacks.

The bundled C reference implementation still uses the historical executable
and directory names Dilithium2/3/5.  They correspond to ML-DSA-44/65/87,
respectively.  Keeping that mapping in one module prevents Python drivers from
silently assuming K=4 when a mode-3 or mode-5 executable is selected.
"""

from __future__ import annotations

import re
from dataclasses import dataclass
from pathlib import Path

import numpy as np


N = 256
D = 13
POLYT0_PACKEDBYTES = 416
SEEDBYTES = 32
TRBYTES = 64


@dataclass(frozen=True)
class T0Parameters:
    """Parameters needed by the t0 recovery pipeline."""

    mode: int
    security_level: int
    dilithium_name: str
    mldsa_name: str
    k: int
    l: int
    eta: int
    polyeta_packedbytes: int
    secret_key_bytes: int
    n: int = N
    d: int = D

    @property
    def t0_offset(self) -> int:
        return (
            2 * SEEDBYTES
            + TRBYTES
            + (self.l + self.k) * self.polyeta_packedbytes
        )

    @property
    def t0_bytes(self) -> int:
        return self.k * POLYT0_PACKEDBYTES


_PARAMETERS = {
    2: T0Parameters(2, 44, "Dilithium2", "ML-DSA-44", 4, 4, 2, 96, 2560),
    3: T0Parameters(3, 65, "Dilithium3", "ML-DSA-65", 6, 5, 4, 128, 4032),
    5: T0Parameters(5, 87, "Dilithium5", "ML-DSA-87", 8, 7, 2, 96, 4896),
}

_ALIASES = {
    "2": 2,
    "44": 2,
    "dilithium2": 2,
    "mldsa44": 2,
    "3": 3,
    "65": 3,
    "dilithium3": 3,
    "mldsa65": 3,
    "5": 5,
    "87": 5,
    "dilithium5": 5,
    "mldsa87": 5,
}


def resolve_t0_parameters(level: str | int) -> T0Parameters:
    """Resolve 2/3/5, 44/65/87, and common scheme-name spellings."""

    normalized = re.sub(r"[^a-z0-9]", "", str(level).lower())
    try:
        mode = _ALIASES[normalized]
    except KeyError as exc:
        raise ValueError(
            f"Unsupported level {level!r}; use 2/3/5 or ML-DSA-44/65/87"
        ) from exc
    return _PARAMETERS[mode]


def unpack_t0(secret_key: bytes, params: T0Parameters) -> np.ndarray:
    """Decode the K x 256 t0 vector from a packed reference secret key."""

    if len(secret_key) != params.secret_key_bytes:
        raise ValueError(
            f"Invalid {params.mldsa_name} secret key length: "
            f"got {len(secret_key)}, expected {params.secret_key_bytes} bytes"
        )

    start = params.t0_offset
    end = start + params.t0_bytes
    if end != len(secret_key):
        raise ValueError(
            f"Internal {params.mldsa_name} layout mismatch: "
            f"t0 ends at {end}, secret key has {len(secret_key)} bytes"
        )

    packed = secret_key[start:end]
    result = np.empty((params.k, params.n), dtype=np.int32)
    for poly_index in range(params.k):
        poly = packed[
            poly_index * POLYT0_PACKEDBYTES : (poly_index + 1)
            * POLYT0_PACKEDBYTES
        ]
        bit_buffer = 0
        bit_count = 0
        byte_index = 0
        for coeff_index in range(params.n):
            while bit_count < params.d:
                bit_buffer |= poly[byte_index] << bit_count
                byte_index += 1
                bit_count += 8
            encoded = bit_buffer & ((1 << params.d) - 1)
            bit_buffer >>= params.d
            bit_count -= params.d
            result[poly_index, coeff_index] = (1 << (params.d - 1)) - encoded

        if byte_index != POLYT0_PACKEDBYTES or bit_count != 0:
            raise ValueError("Internal t0 unpacking length mismatch")
    return result


def load_true_t0(
    base: Path,
    key_index: int,
    params: T0Parameters,
    kat_file: Path | None = None,
) -> tuple[np.ndarray, int]:
    """Load and decode one KAT secret key for the requested parameter set."""

    if key_index < 0:
        raise ValueError("--key must be nonnegative")
    path = kat_file or (
        base
        / "dilithium"
        / "ref"
        / f"PQCsignKAT_{params.dilithium_name}.rsp"
    )
    if not path.is_file():
        raise FileNotFoundError(
            f"KAT file not found: {path}. Generate it with "
            f"dilithium/ref/nistkat/PQCgenKAT_sign{params.mode}."
        )

    text = path.read_text(encoding="utf-8", errors="ignore")
    secret_keys = re.findall(r"(?m)^sk\s*=\s*([0-9A-Fa-f]+)\s*$", text)
    if key_index >= len(secret_keys):
        raise IndexError(
            f"KAT file {path} contains {len(secret_keys)} secret keys; "
            f"key index {key_index} is unavailable"
        )

    try:
        secret_key = bytes.fromhex(secret_keys[key_index])
    except ValueError as exc:
        raise ValueError(f"Malformed secret-key hex in {path}, key {key_index}") from exc
    return unpack_t0(secret_key, params), params.d

