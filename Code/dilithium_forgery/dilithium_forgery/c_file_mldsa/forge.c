#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "params.h"
#include "sign.h"
#include "packing.h"
#include "polyvec.h"
#include "poly.h"
#include "rounding.h"
#include "symmetric.h"
#include "fips202.h"

static void write_polyvecl(const char *path, const polyvecl *v)
{
  FILE *fp = fopen(path, "w");
  unsigned int i, j;

  if(fp == NULL)
    return;
  for(i = 0; i < L; ++i) {
    for(j = 0; j < N; ++j)
      fprintf(fp, "%d%c", v->vec[i].coeffs[j], j + 1 == N ? '\n' : ' ');
  }
  fclose(fp);
}

static void write_polyveck(const char *path, const polyveck *v)
{
  FILE *fp = fopen(path, "w");
  unsigned int i, j;

  if(fp == NULL)
    return;
  for(i = 0; i < K; ++i) {
    for(j = 0; j < N; ++j)
      fprintf(fp, "%d%c", v->vec[i].coeffs[j], j + 1 == N ? '\n' : ' ');
  }
  fclose(fp);
}

static void write_poly(const char *path, const poly *v)
{
  FILE *fp = fopen(path, "w");
  unsigned int j;

  if(fp == NULL)
    return;
  for(j = 0; j < N; ++j)
    fprintf(fp, "%d%c", v->coeffs[j], j + 1 == N ? '\n' : ' ');
  fclose(fp);
}

/*
 * Construct one research candidate using only the supplied s1 and pk.
 * The verifier remains the official ML-DSA verifier in sign.c.
 */
int crypto_sign_forge(uint8_t *sm, size_t *smlen,
                      const uint8_t *m, size_t mlen,
                      const uint8_t *pk,
                      const polyvecl *s1_in,
                      unsigned int iteration)
{
  uint8_t rho[SEEDBYTES];
  uint8_t mu[CRHBYTES];
  uint8_t rhoprime[CRHBYTES];
  uint8_t ctilde[CTILDEBYTES];
  uint8_t packed_w1[K * POLYW1_PACKEDBYTES];
  uint8_t sig[CRYPTO_BYTES];
  uint8_t counter[4];
  polyvecl mat[K], s1hat, y, yhat, z, zhat;
  polyveck t1, w, w0, w1, raw, raw0, raw1, h, ct1;
  poly cp;
  keccak_state state;
  unsigned int i, j, hint_weight = 0;

  unpack_pk(rho, &t1, pk);

  /* ML-DSA's empty-context prefix is 0 || 0. */
  {
    const uint8_t pre[2] = {0, 0};

    shake256(mu, TRBYTES, pk, CRYPTO_PUBLICKEYBYTES);
    shake256_init(&state);
    shake256_absorb(&state, mu, TRBYTES);
    shake256_absorb(&state, pre, sizeof(pre));
    shake256_absorb(&state, m, mlen);
    shake256_finalize(&state);
    shake256_squeeze(mu, CRHBYTES, &state);
  }

  /* Make the candidate sequence reproducible across Python invocations. */
  counter[0] = (uint8_t)iteration;
  counter[1] = (uint8_t)(iteration >> 8);
  counter[2] = (uint8_t)(iteration >> 16);
  counter[3] = (uint8_t)(iteration >> 24);
  shake256_init(&state);
  shake256_absorb(&state, pk, CRYPTO_PUBLICKEYBYTES);
  shake256_absorb(&state, m, mlen);
  shake256_absorb(&state, counter, sizeof(counter));
  shake256_finalize(&state);
  shake256_squeeze(rhoprime, CRHBYTES, &state);

  polyvec_matrix_expand(mat, rho);

  /* w1 = HighBits(Ay). */
  polyvecl_uniform_gamma1(&y, rhoprime, 0);
  yhat = y;
  polyvecl_ntt(&yhat);
  polyvec_matrix_pointwise_montgomery(&w, mat, &yhat);
  polyveck_reduce(&w);
  polyveck_invntt_tomont(&w);
  polyveck_caddq(&w);
  polyveck_decompose(&w1, &w0, &w);
  polyveck_pack_w1(packed_w1, &w1);
  write_polyveck("../median_value_mldsa/w1.txt", &w1);

  /* c = H(mu || w1). */
  shake256_init(&state);
  shake256_absorb(&state, mu, CRHBYTES);
  shake256_absorb(&state, packed_w1, sizeof(packed_w1));
  shake256_finalize(&state);
  shake256_squeeze(ctilde, CTILDEBYTES, &state);
  poly_challenge(&cp, ctilde);
  write_poly("../median_value_mldsa/c.txt", &cp);

  /* z = y + c*s1. */
  s1hat = *s1_in;
  polyvecl_ntt(&s1hat);
  poly_ntt(&cp);
  polyvecl_pointwise_poly_montgomery(&z, &cp, &s1hat);
  polyvecl_invntt_tomont(&z);
  polyvecl_add(&z, &z, &y);
  polyvecl_reduce(&z);
  write_polyvecl("../median_value_mldsa/z.txt", &z);

  if(polyvecl_chknorm(&z, GAMMA1 - BETA))
    return -2;

  /* raw = Az - c*(2^D*t1), the verifier's pre-hint value. */
  zhat = z;
  polyvecl_ntt(&zhat);
  polyvec_matrix_pointwise_montgomery(&raw, mat, &zhat);
  polyveck_reduce(&raw);
  polyveck_invntt_tomont(&raw);

  ct1 = t1;
  polyveck_shiftl(&ct1);
  polyveck_ntt(&ct1);
  polyveck_pointwise_poly_montgomery(&ct1, &cp, &ct1);
  polyveck_sub(&raw, &raw, &ct1);
  polyveck_reduce(&raw);
  polyveck_invntt_tomont(&raw);
  polyveck_caddq(&raw);

  /* t.txt stores raw HighBits; Python uses it for the hint diagnostic. */
  polyveck_decompose(&raw1, &raw0, &raw);
  write_polyveck("../median_value_mldsa/t.txt", &raw1);

  /* h is accepted only when UseHint(raw,h) equals the target w1. */
  for(i = 0; i < K; ++i) {
    for(j = 0; j < N; ++j) {
      int32_t a = raw.vec[i].coeffs[j];
      int32_t target = w1.vec[i].coeffs[j];

      if(use_hint(a, 0) == target)
        h.vec[i].coeffs[j] = 0;
      else if(use_hint(a, 1) == target) {
        h.vec[i].coeffs[j] = 1;
        ++hint_weight;
      } else {
        h.vec[i].coeffs[j] = 0;
        write_polyveck("../median_value_mldsa/h.txt", &h);
        return -3;
      }
    }
  }

  write_polyveck("../median_value_mldsa/h.txt", &h);
  if(hint_weight > OMEGA)
    return -4;

  pack_sig(sig, ctilde, &z, &h);
  memcpy(sm, sig, CRYPTO_BYTES);
  memcpy(sm + CRYPTO_BYTES, m, mlen);
  *smlen = CRYPTO_BYTES + mlen;
  return 0;
}
