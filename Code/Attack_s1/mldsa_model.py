"""Minimal ML-DSA/Dilithium model used by the skipped-z s1 experiment."""

from __future__ import annotations

from dataclasses import dataclass

import numpy as np


@dataclass(frozen=True)
class MLDSAParams:
    name: str
    level: str
    n: int
    k: int
    ell: int
    eta: int
    tau: int
    beta: int
    gamma1: int
    gamma2: int

    @property
    def dimension(self) -> int:
        return self.ell * self.n

    @property
    def y_low(self) -> int:
        return -self.gamma1 + 1

    @property
    def y_high(self) -> int:
        return self.gamma1

    @property
    def inner_product_bound(self) -> int:
        return self.eta * self.tau


PARAMS: dict[str, MLDSAParams] = {
    "2": MLDSAParams("Dilithium2", "2", 256, 4, 4, 2, 39, 78, 1 << 17, 95_232),
    "3": MLDSAParams("Dilithium3", "3", 256, 6, 5, 4, 49, 196, 1 << 19, 261_888),
    "5": MLDSAParams("Dilithium5", "5", 256, 8, 7, 2, 60, 120, 1 << 19, 261_888),
    "toy": MLDSAParams("Toy", "toy", 64, 2, 2, 2, 12, 24, 256, 128),
}


@dataclass(frozen=True)
class Challenge:
    """Sparse challenge c with coefficients in {-1, 0, 1}."""

    positions: np.ndarray
    signs: np.ndarray


def get_params(level: str) -> MLDSAParams:
    try:
        return PARAMS[str(level)]
    except KeyError as exc:
        raise ValueError(f"unknown level {level!r}; choose 2, 3, 5, or toy") from exc


def sample_secret(params: MLDSAParams, rng: np.random.Generator) -> np.ndarray:
    """Sample the simulated small secret uniformly coefficient by coefficient."""

    return rng.integers(
        -params.eta,
        params.eta + 1,
        size=(params.ell, params.n),
        dtype=np.int16,
    )


def sample_challenge(params: MLDSAParams, rng: np.random.Generator) -> Challenge:
    positions = rng.choice(params.n, size=params.tau, replace=False).astype(np.int16)
    signs = rng.choice(np.asarray([-1, 1], dtype=np.int8), size=params.tau)
    return Challenge(positions=positions, signs=signs)


def sample_y(params: MLDSAParams, rng: np.random.Generator) -> np.ndarray:
    """Sample y uniformly from Dilithium's inclusive coefficient interval."""

    return rng.integers(
        params.y_low,
        params.y_high + 1,
        size=(params.ell, params.n),
        dtype=np.int32,
    )


def row_terms(
    params: MLDSAParams,
    challenge: Challenge,
    coeff_index: int,
) -> tuple[list[int], list[int]]:
    """Return one sparse row of c*s in Z[X]/(X^n + 1)."""

    columns: list[int] = []
    values: list[int] = []
    for position, sign in zip(challenge.positions, challenge.signs):
        position_int = int(position)
        secret_coeff = (int(coeff_index) - position_int) % params.n
        wrap_sign = 1 if int(coeff_index) >= position_int else -1
        columns.append(secret_coeff)
        values.append(int(sign) * wrap_sign)
    return columns, values


def sparse_product(
    params: MLDSAParams,
    secret: np.ndarray,
    challenge: Challenge,
) -> np.ndarray:
    """Compute c*s for every polynomial of s using negacyclic convolution."""

    secret = np.asarray(secret, dtype=np.int16)
    if secret.shape != (params.ell, params.n):
        raise ValueError(
            f"secret shape is {secret.shape}, expected {(params.ell, params.n)}"
        )

    product = np.zeros((params.ell, params.n), dtype=np.int16)
    for position, sign in zip(challenge.positions, challenge.signs):
        position_int = int(position)
        sign_int = int(sign)
        if position_int == 0:
            product += sign_int * secret
        else:
            product[:, position_int:] += sign_int * secret[:, : params.n - position_int]
            product[:, :position_int] -= sign_int * secret[:, params.n - position_int :]
    return product

