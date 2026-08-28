#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#ifdef _WIN32
#include <direct.h>
#endif

#include "lp_lib.h"

#include "additional_fct.h"
#include "fips202.h"
#ifdef T0_NOISY_EQUALITY
#include "noisy_equality.h"
#endif
#include "packing.h"
#include "poly.h"
#include "polyvec.h"
#include "randombytes.h"
#include "sign.h"
#include "symmetric.h"

#ifdef _WIN32
#define MKDIR(path, mode) _mkdir(path)
#else
#define MKDIR(path, mode) mkdir(path, mode)
#endif

#ifdef T0_NOISY_EQUALITY
static int add_lp_inequality(lprec *lp, const int8_t line[N], int sign,
                             double bound, int colno[N], REAL row[N]) {
  uint32_t i;
  int count = 0;

  for (i = 0; i < N; i++) {
    if (line[i] != 0) {
      colno[count] = (int)i + 1;
      row[count] = (REAL)(sign * line[i]);
      count++;
    }
  }
  return add_constraintex(lp, count, row, colno, LE, bound);
}
#endif

int main(int argc, char const *argv[]) {
  uint32_t NB_INEQ;
  int sk_index;
  float C_low, C_up;

  if (argc == 4) {
    // Case 1: Two arguments   (int NB_inequalities, float C)
    sk_index = atoi(argv[1]);
    NB_INEQ = atoi(argv[2]);
    C_up = strtof(argv[3], NULL);
    C_low = -C_up;
  } else if (argc == 5) {
    // Case 2: Three arguments (int NB_inequalities, float C_low, float C_up)
    sk_index = atoi(argv[1]);
    NB_INEQ = atoi(argv[2]);
    C_low = -strtof(argv[3], NULL);
    C_up = strtof(argv[4], NULL);
  } else {
    // Invalid number of arguments
    printf("Usage:\n");
#ifdef T0_NOISY_EQUALITY
    printf("  %s <key_idx> <nb_equations> <C>\n", argv[0]);
    printf("  %s <key_idx> <nb_equations> <C_low_abs> <C_up>\n", argv[0]);
#else
    printf("  %s <key_idx> <nb_inequalities> <C>\n", argv[0]);
    printf("  %s <key_idx> <nb_inequalities> <C_low_abs> <C_up>\n", argv[0]);
#endif
    return DATA_ERROR;
  }

  char t0_guess_filename[256];
  FILE *t0_guess_file;
  double t0_guess[K][N];
  double t0_guess_updated[K][N];

  char sign_compressed_file_name[128];
  FILE *sign_compressed_file;
  uint8_t sm_compressed[MLEN + COMP_CRYPTO_BYTES];

  uint32_t i, j;

  float C = C_up;
  int8_t ineq_line[N];
  uint32_t cpt_ineq[K], cpt_ineq1[K], cpt_ineq0[K];
  uint32_t poly_index, coeff_index, ineq_index, cpt_signs;
  uint32_t sig_limit = 0;
  const char *env_sig_limit = getenv("T0_SIG_LIMIT");
  const char *env_sig_file = getenv("T0_SIG_FILE");
  const char *env_guess_file = getenv("T0_GUESS_FILE");

  double bound;
  double guess;

  polyveck r0, h;
  poly c;
  uint8_t c_seed[CTILDEBYTES];

  clock_t start, end;
  double cpu_time_used;

  char name_var[14];
  char name_lp_file[58];
  lprec *LPs[K];
  int *colno = NULL, ret = 0;
  REAL *row = NULL;

  int ch;
  unsigned char ich;
  int started = 0;
  int eof_reached = 0;

  char directory[32];
  struct stat st = {0};

  sprintf(directory, "../Guess/");
  if (stat(directory, &st) == -1) {
    MKDIR(directory, 0700);
  }

  sprintf(directory, "../Guess/%.16s/", CRYPTO_ALGNAME);
  if (stat(directory, &st) == -1) {
    MKDIR(directory, 0700);
  }

  sprintf(directory, "../Guess/%.16s/key%d/", CRYPTO_ALGNAME, sk_index);
  if (stat(directory, &st) == -1) {
    MKDIR(directory, 0700);
  }

  sprintf(directory, "../Lps/");
  if (stat(directory, &st) == -1) {
    MKDIR(directory, 0700);
  }

  sprintf(directory, "../Lps/%.16s/", CRYPTO_ALGNAME);
  if (stat(directory, &st) == -1) {
    MKDIR(directory, 0700);
  }

  sprintf(directory, "../Lps/%.16s/key%d/", CRYPTO_ALGNAME, sk_index);
  if (stat(directory, &st) == -1) {
    MKDIR(directory, 0700);
  }

  if (env_sig_limit != NULL && env_sig_limit[0] != '\0') {
    sig_limit = (uint32_t)strtoul(env_sig_limit, NULL, 10);
  }
  if (env_sig_file != NULL && env_sig_file[0] != '\0') {
    snprintf(sign_compressed_file_name, sizeof(sign_compressed_file_name), "%s",
             env_sig_file);
  } else {
    sprintf(sign_compressed_file_name,
            "../Signs/%.16s/key%d/PQCsignKAT_%.16s_compressed.rsp",
            CRYPTO_ALGNAME, sk_index, CRYPTO_ALGNAME);
  }
  if ((sign_compressed_file = fopen(sign_compressed_file_name, "r")) == NULL) {
    printf("Couldn't open <%s> for read\n", sign_compressed_file_name);
    return DATA_ERROR;
  }

  if (env_guess_file != NULL && env_guess_file[0] != '\0') {
    snprintf(t0_guess_filename, sizeof(t0_guess_filename), "%s",
             env_guess_file);
  } else {
    sprintf(t0_guess_filename,
            "../Guess/%.16s/key%d/t0_guess_file.bin",
            CRYPTO_ALGNAME, sk_index);
  }
  t0_guess_file = fopen(t0_guess_filename, "rb");
  if (t0_guess_file == NULL) {
    perror("Error opening file");
    return FILE_OPEN_ERROR;
  }

  if (fread(t0_guess, sizeof(double), K * N, t0_guess_file) != K * N) {
    printf("Invalid t0 guess file <%s>\n", t0_guess_filename);
    fclose(t0_guess_file);
    fclose(sign_compressed_file);
    return DATA_ERROR;
  }
  fclose(t0_guess_file);

  for (poly_index = 0; poly_index < K; poly_index++) {
    cpt_ineq[poly_index] = 0;
    cpt_ineq0[poly_index] = 0;
    cpt_ineq1[poly_index] = 0;
  }

  /* We create models with 0 rows, N columns because we build the model row by
   * row */
  for (poly_index = 0; poly_index < K; poly_index++) {
    LPs[poly_index] = make_lp(0, N);
    if (LPs[poly_index] == NULL) {
      ret = 1;
    }
  }

  if (ret == 0) {
    for (poly_index = 0; poly_index < K; poly_index++) {
      for (coeff_index = 0; coeff_index < N; coeff_index++) {
        sprintf(name_var, "s%d", coeff_index);
        if (!set_col_name(LPs[poly_index], coeff_index + 1, name_var)) {
          ret = 1;
        }
      }
    }

    colno = (int *)malloc(N * sizeof(*colno));
    row = (REAL *)malloc(N * sizeof(*row));
    if ((colno == NULL) || (row == NULL)) {
      ret = 1;
    }
  }

  printf("C: %.2f\n", C_up);
  if (ret == 0) {
    for (poly_index = 0; poly_index < K; poly_index++) {
      for (coeff_index = 0; coeff_index < N; coeff_index++) {
        if (!set_lowbo(LPs[poly_index], coeff_index + 1,
                       get_max(t0_guess[poly_index][coeff_index] + C_low))) {
          ret = 1;
        }
        if (!set_upbo(LPs[poly_index], coeff_index + 1,
                      get_min(t0_guess[poly_index][coeff_index] + C_up))) {
          ret = 1;
        }
      }
    }
  }

  cpt_signs = 0;
  start = clock();
  while (find_min(cpt_ineq) < NB_INEQ && !eof_reached && ret == 0 &&
         (sig_limit == 0 || cpt_signs < sig_limit)) {
    started = 0;
    memset(sm_compressed, 0x00, MLEN + COMP_CRYPTO_BYTES);
    while ((ch = fgetc(sign_compressed_file)) != EOF) {
      if (!isxdigit(ch)) {
        if (!started) {
          if (ch == '\n')
            break;
          else
            continue;
        } else
          break;
      }
      started = 1;
      if ((ch >= '0') && (ch <= '9'))
        ich = ch - '0';
      else if ((ch >= 'A') && (ch <= 'F'))
        ich = ch - 'A' + 10;
      else if ((ch >= 'a') && (ch <= 'f'))
        ich = ch - 'a' + 10;
      else // shouldn't ever get here
        ich = 0;

      for (i = 0; i < MLEN + COMP_CRYPTO_BYTES - 1; i++)
        sm_compressed[i] =
            (sm_compressed[i] << 4) | (sm_compressed[i + 1] >> 4);
      sm_compressed[MLEN + COMP_CRYPTO_BYTES - 1] =
          (sm_compressed[MLEN + COMP_CRYPTO_BYTES - 1] << 4) | ich;
    }

    if (!started) {
      eof_reached = 1;
      break;
    }

    unpack_sig_compressed(c_seed, &r0, &h, sm_compressed);
    poly_challenge(&c, c_seed);

    for (poly_index = 0; poly_index < K; poly_index++) {
      for (coeff_index = 0; coeff_index < N; coeff_index++) {
#ifdef T0_NOISY_EQUALITY
        noisy_equality_t equation;
        noisy_inequality_t converted[2];
        int32_t hint_value;
        int32_t r0_value;

        if (cpt_ineq[poly_index] >= NB_INEQ) {
          break;
        }

        hint_value = h.vec[poly_index].coeffs[coeff_index];
        r0_value = r0.vec[poly_index].coeffs[coeff_index];
        if (!noisy_equality_from_signature(hint_value, r0_value, &equation)) {
          continue;
        }

        creat_ineq(&c, coeff_index, ineq_line);
        guess = noisy_equality_row_dot(ineq_line, t0_guess[poly_index]);
        C = (C_up > -C_low) ? C_up : -C_low;
        if (noisy_equality_interval_distance(&equation, guess) > C * TAU) {
          continue;
        }

        noisy_equality_to_inequalities(&equation, converted);
        for (i = 0; i < 2; i++) {
          if (!add_lp_inequality(LPs[poly_index], ineq_line,
                                 converted[i].sign,
                                 (double)converted[i].bound, colno, row)) {
            ret = LP_ERROR;
            break;
          }
        }
        if (ret != 0) {
          break;
        }

        cpt_ineq[poly_index]++;
        if (hint_value == 0) {
          cpt_ineq0[poly_index]++;
        } else {
          cpt_ineq1[poly_index]++;
        }
#else
        if (h.vec[poly_index].coeffs[coeff_index] == 1) {
          if (r0.vec[poly_index].coeffs[coeff_index] > 0) {
            creat_ineq(&c, coeff_index, ineq_line);
            guess = scalar_product(ineq_line, t0_guess[poly_index]);
            bound = -GAMMA2 - BETA - 1 + r0.vec[poly_index].coeffs[coeff_index];
            if (bound + guess < C * TAU) {
              if (ret == 0) {
                j = 0;
                for (ineq_index = 0; ineq_index < N; ineq_index++) {
                  if (ineq_line[ineq_index] != 0) {
                    colno[j] = ineq_index + 1;
                    row[j++] = ineq_line[ineq_index];
                  }
                }

                /* add the row to lpsolve */
                if (!add_constraintex(LPs[poly_index], j, row, colno, LE,
                                      bound)) {
                  ret = 1;
                }
              }
              cpt_ineq1[poly_index]++;
              cpt_ineq[poly_index]++;
            }
          }

          if (r0.vec[poly_index].coeffs[coeff_index] < 0) {
            creat_ineq(&c, coeff_index, ineq_line);
            guess = scalar_product(ineq_line, t0_guess[poly_index]);
            bound = -GAMMA2 - BETA - 1 - r0.vec[poly_index].coeffs[coeff_index];
            // if(bound < C*TAU){
            if (bound - guess < C * TAU) {
              if (ret == 0) {
                j = 0;
                for (ineq_index = 0; ineq_index < N; ineq_index++) {
                  if (ineq_line[ineq_index] != 0) {
                    colno[j] = ineq_index + 1;
                    row[j++] = -ineq_line[ineq_index];
                  }
                }

                /* add the row to lpsolve */
                if (!add_constraintex(LPs[poly_index], j, row, colno, LE,
                                      bound)) {
                  ret = 1;
                }
              }
              cpt_ineq1[poly_index]++;
              cpt_ineq[poly_index]++;
            }
          }
        } else {
          bound = GAMMA2 - BETA - 1 - r0.vec[poly_index].coeffs[coeff_index];
          creat_ineq(&c, coeff_index, ineq_line);
          guess = scalar_product(ineq_line, t0_guess[poly_index]);

          if (bound - guess < C * TAU) {
            if (ret == 0) {
              j = 0;
              for (ineq_index = 0; ineq_index < N; ineq_index++) {
                if (ineq_line[ineq_index] != 0) {
                  colno[j] = ineq_index + 1;
                  row[j++] = -ineq_line[ineq_index];
                }
              }

              if (!add_constraintex(LPs[poly_index], j, row, colno, LE,
                                    bound)) {
                ret = 1;
              }
            }
            cpt_ineq0[poly_index]++;
            cpt_ineq[poly_index]++;
          }

          bound = GAMMA2 - BETA - 1 + r0.vec[poly_index].coeffs[coeff_index];
          if (bound + guess < C * TAU) {
            if (ret == 0) {
              j = 0;
              for (ineq_index = 0; ineq_index < N; ineq_index++) {
                if (ineq_line[ineq_index] != 0) {
                  colno[j] = ineq_index + 1;
                  row[j++] = ineq_line[ineq_index];
                }
              }

              if (!add_constraintex(LPs[poly_index], j, row, colno, LE,
                                    bound)) {
                ret = 1;
              }
            }
            cpt_ineq[poly_index]++;
            cpt_ineq0[poly_index]++;
          }
        }
#endif
      }
      if (ret != 0) {
        break;
      }
    }
    cpt_signs++;
    // if(cpt_signs%500 == 0){
    //   printf("%d/%d\r", find_min(cpt_ineq), cpt_signs);
    //   fflush(stdout);
    // }
  }

  end = clock();

  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
#ifdef T0_NOISY_EQUALITY
  printf("Building %d noisy-equality LPs: %f sec/%d signs/", K,
         cpu_time_used, cpt_signs);
#else
  printf("Building %d LPs: %f sec/%d signs/", K, cpu_time_used, cpt_signs);
#endif
  for (poly_index = 0; poly_index < K; poly_index++) {
    printf("%d, ", cpt_ineq0[poly_index]);
  }
#ifdef T0_NOISY_EQUALITY
  printf(" h=0 eq/ ");
#else
  printf(" 0 ineq/ ");
#endif
  for (poly_index = 0; poly_index < K; poly_index++) {
    printf("%d, ", cpt_ineq1[poly_index]);
  }
#ifdef T0_NOISY_EQUALITY
  printf(" h=1 eq\n");
  if (eof_reached && find_min(cpt_ineq) < NB_INEQ) {
    printf("Warning: signature file exhausted at %u/%u equations per "
           "polynomial (minimum).\n",
           find_min(cpt_ineq), NB_INEQ);
  }
#else
  printf(" 1 ineq\n");
#endif
  if (ret == 0) {
    for (poly_index = 0; poly_index < K; poly_index++) {
      set_add_rowmode(LPs[poly_index], FALSE);
#ifdef T0_NOISY_EQUALITY
      sprintf(name_lp_file, "../Lps/%.16s/key%d/poly%d_eq.lp",
              CRYPTO_ALGNAME, sk_index, poly_index);
#else
      sprintf(name_lp_file, "../Lps/%.16s/key%d/poly%d.lp",
              CRYPTO_ALGNAME, sk_index, poly_index);
#endif
      write_lp(LPs[poly_index], name_lp_file);
    }

    for (poly_index = 0; poly_index < K; poly_index++) {
      set_verbose(LPs[poly_index], IMPORTANT);
      start = clock();
      /* Now let lpsolve calculate a solution */
      ret = solve(LPs[poly_index]);
      end = clock();
      cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
      printf("Solving LP#%d (code %d): %f sec\n", poly_index, ret,
             cpu_time_used);

      if (ret == OPTIMAL) {
        ret = 0;
      } else {
        ret = 5;
        break;
      }
    }
  }

  if (ret == 0) {
    for (poly_index = 0; poly_index < K; poly_index++) {
      get_variables(LPs[poly_index], t0_guess_updated[poly_index]);
    }
  }

  if (ret == 0) {
    t0_guess_file = fopen(t0_guess_filename, "wb");
    if (t0_guess_file == NULL) {
      perror("Error opening file");
      return FILE_OPEN_ERROR;
    }

    if (fwrite(t0_guess_updated, sizeof(double), K * N, t0_guess_file) !=
        K * N) {
      printf("Couldn't write complete t0 guess to <%s>\n", t0_guess_filename);
      fclose(t0_guess_file);
      ret = FILE_OPEN_ERROR;
    } else {
      fclose(t0_guess_file);
    }
  }

  if (row != NULL) { /* free allocated memory */
    free(row);
  }
  if (colno != NULL) {
    free(colno);
  }

  for (poly_index = 0; poly_index < K; poly_index++) {
    if (LPs[poly_index] != NULL) {
      delete_lp(LPs[poly_index]); /* clean up such that all used memory by
                                     lpsolve is freed */
    }
  }

  fclose(sign_compressed_file);
  return ret;
}
