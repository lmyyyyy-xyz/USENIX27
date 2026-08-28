pub const NVAR: usize = 256;
// ML-DSA-65 uses eta = 4, so the complement-ordered secret message must
// represent every value in [-4, 4].
pub const SZ_MSG: usize = 9;
