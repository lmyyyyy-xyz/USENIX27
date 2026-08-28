#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "api.h"
#include "params.h"
#include "sign.h"

#define MAX_MESSAGE_BYTES 4096

static int hex_value(int c)
{
  if(c >= '0' && c <= '9') return c - '0';
  if(c >= 'a' && c <= 'f') return c - 'a' + 10;
  if(c >= 'A' && c <= 'F') return c - 'A' + 10;
  return -1;
}

static int read_hex_bytes(const char *path, uint8_t *out, size_t outlen)
{
  FILE *fp = fopen(path, "r");
  size_t n = 0;
  int c, high = -1;

  if(fp == NULL)
    return 0;
  while((c = fgetc(fp)) != EOF) {
    int v;
    if(isspace((unsigned char)c))
      continue;
    v = hex_value(c);
    if(v < 0) {
      fclose(fp);
      return 0;
    }
    if(high < 0)
      high = v;
    else {
      if(n >= outlen) {
        fclose(fp);
        return 0;
      }
      out[n++] = (uint8_t)((high << 4) | v);
      high = -1;
    }
  }
  fclose(fp);
  return n == outlen && high < 0;
}

static int read_message(const char *path, uint8_t *msg, size_t *mlen)
{
  FILE *fp = fopen(path, "r");
  char hex[2 * MAX_MESSAGE_BYTES + 1];
  size_t n = 0, i;
  int c;

  if(fp == NULL)
    return 0;
  while((c = fgetc(fp)) != EOF && c != '=')
    ;
  if(c != '=') {
    fclose(fp);
    return 0;
  }
  while((c = fgetc(fp)) != EOF && isspace((unsigned char)c))
    ;
  if(c != EOF)
    hex[n++] = (char)c;
  while(n < sizeof(hex) - 1 && (c = fgetc(fp)) != EOF && !isspace((unsigned char)c))
    hex[n++] = (char)c;
  hex[n] = '\0';
  fclose(fp);

  if(n == 0 || (n & 1) != 0 || n / 2 > MAX_MESSAGE_BYTES)
    return 0;
  for(i = 0; i < n / 2; ++i) {
    int hi = hex_value((unsigned char)hex[2 * i]);
    int lo = hex_value((unsigned char)hex[2 * i + 1]);
    if(hi < 0 || lo < 0)
      return 0;
    msg[i] = (uint8_t)((hi << 4) | lo);
  }
  *mlen = n / 2;
  return 1;
}

static int read_s1(const char *path, polyvecl *s1)
{
  FILE *fp = fopen(path, "r");
  unsigned int i, j;

  if(fp == NULL)
    return 0;
  for(i = 0; i < L; ++i) {
    for(j = 0; j < N; ++j) {
      int value;
      if(fscanf(fp, "%d", &value) != 1 || value < -ETA || value > ETA) {
        fclose(fp);
        return 0;
      }
      s1->vec[i].coeffs[j] = value;
    }
  }
  fclose(fp);
  return 1;
}

static void write_hex(FILE *fp, const uint8_t *data, size_t len)
{
  static const char digits[] = "0123456789abcdef";
  size_t i;
  for(i = 0; i < len; ++i)
    fprintf(fp, "%c%c", digits[data[i] >> 4], digits[data[i] & 0xf]);
}

int main(int argc, char **argv)
{
  uint8_t msg[MAX_MESSAGE_BYTES];
  uint8_t pk[CRYPTO_PUBLICKEYBYTES];
  uint8_t sm[CRYPTO_BYTES + MAX_MESSAGE_BYTES];
  uint8_t recovered[MAX_MESSAGE_BYTES];
  polyvecl s1;
  size_t mlen, smlen, recovered_len;
  unsigned int iteration;
  int ret;
  FILE *fp;

  if(argc != 2) {
    fprintf(stderr, "usage: %s ITERATION\n", argv[0]);
    return 2;
  }
  iteration = (unsigned int)strtoul(argv[1], NULL, 10);

  if(!read_message("../median_value_mldsa/m.txt", msg, &mlen)) {
    fprintf(stderr, "cannot read message from ../median_value_mldsa/m.txt\n");
    return 2;
  }
  if(!read_hex_bytes("../median_value_mldsa/pk.txt", pk, sizeof(pk))) {
    fprintf(stderr, "invalid ML-DSA-44 public key\n");
    return 2;
  }
  if(!read_s1("../median_value_mldsa/write_s1.txt", &s1)) {
    fprintf(stderr, "invalid external s1; expected %u x %u coefficients\n", L, N);
    return 2;
  }

  ret = crypto_sign_forge(sm, &smlen, msg, mlen, pk, &s1, iteration);
  if(ret != 0) {
    printf("candidate construction returned <%d>\n", ret);
    return 3;
  }

  fp = fopen("PQCsignKAT_2560.rsp", "w");
  if(fp == NULL) {
    fprintf(stderr, "cannot write PQCsignKAT_2560.rsp\n");
    return 2;
  }
  fprintf(fp, "# %s\n\n", CRYPTO_ALGNAME);
  fprintf(fp, "mlen = %zu\n", mlen);
  fprintf(fp, "msg = ");
  write_hex(fp, msg, mlen);
  fprintf(fp, "\nsmlen = %zu\nsm = ", smlen);
  write_hex(fp, sm, smlen);
  fprintf(fp, "\n");
  fclose(fp);

  ret = crypto_sign_open(recovered, &recovered_len, sm, smlen, NULL, 0, pk);
  if(ret != 0) {
    printf("crypto_sign_open returned <%d>\n", ret);
    return 4;
  }
  if(recovered_len != mlen) {
    printf("verification failed: message length mismatch\n");
    return 4;
  }
  if(memcmp(msg, recovered, mlen) != 0) {
    printf("verification failed: message mismatch\n");
    return 4;
  }

  printf("ML-DSA-44 verification success\n");
  return 0;
}
