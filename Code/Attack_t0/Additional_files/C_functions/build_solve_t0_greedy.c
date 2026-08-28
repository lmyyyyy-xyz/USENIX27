#include <ctype.h>
#include <math.h>
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

#include "additional_fct.h"
#ifdef T0_NOISY_EQUALITY
#include "noisy_equality.h"
#endif
#include "packing.h"
#include "poly.h"
#include "polyvec.h"

#ifdef _WIN32
#define MKDIR(path, mode) _mkdir(path)
#else
#define MKDIR(path, mode) mkdir(path, mode)
#endif

#define DEFAULT_MAX_PASSES 80
#define MAX_INEQ_NNZ 64
#define INITIAL_INEQ_CAPACITY 1024
#define MAIN_MAX_STEP_POWER 6
#define MAIN_STAGNATION_PASSES 3
#define MAIN_RESTARTS 6
#define MAIN_RESTART_PASS_DIV 3
#define MAIN_RESTART_JITTER 2
#define REFINEMENT_MAX_PASSES 96
#define REFINEMENT_MAX_STEP_POWER 1
#define REFINEMENT_STAGNATION_PASSES 6
#define ESCAPE_TOPK 24
#ifdef T0_NOISY_EQUALITY
#define DEFAULT_WINDOW_ALPHA 1.0
#else
#define DEFAULT_WINDOW_ALPHA 2.0
#endif
#define LOW_C_RELAX_THRESHOLD 8.0
#define DEFAULT_LOW_C_RELAX_FACTOR 4.0

typedef struct {
  uint16_t nnz;
  uint16_t idx[MAX_INEQ_NNZ];
  int8_t coeff[MAX_INEQ_NNZ];
  double bound;
  double slack;
} sparse_ineq_t;

typedef struct {
  sparse_ineq_t *rows;
  uint32_t size;
  uint32_t capacity;
} sparse_ineq_list_t;

typedef struct {
  uint32_t ineq_index;
  int8_t coeff;
} adj_entry_t;

static int ensure_capacity(sparse_ineq_list_t *list, uint32_t required) {
  sparse_ineq_t *tmp;
  uint32_t new_capacity;

  if (required <= list->capacity) {
    return 1;
  }

  new_capacity =
      (list->capacity == 0) ? INITIAL_INEQ_CAPACITY : (2U * list->capacity);
  while (new_capacity < required) {
    new_capacity *= 2U;
  }

  tmp = (sparse_ineq_t *)realloc(list->rows, new_capacity * sizeof(*tmp));
  if (tmp == NULL) {
    return 0;
  }

  list->rows = tmp;
  list->capacity = new_capacity;
  return 1;
}

static int add_sparse_constraint(sparse_ineq_list_t *list, const int8_t line[N],
                                 int sign, double bound) {
  sparse_ineq_t row;
  uint32_t i;

  row.nnz = 0;
  row.bound = bound;
  row.slack = 0.0;

  for (i = 0; i < N; i++) {
    int8_t v = (sign > 0) ? line[i] : -line[i];
    if (v == 0) {
      continue;
    }

    if (row.nnz >= MAX_INEQ_NNZ) {
      return 0;
    }

    row.idx[row.nnz] = (uint16_t)i;
    row.coeff[row.nnz] = v;
    row.nnz++;
  }

  if (!ensure_capacity(list, list->size + 1)) {
    return 0;
  }
  list->rows[list->size++] = row;
  return 1;
}

static int write_sparse_lp_file(const char *filename, const sparse_ineq_list_t *list,
                                const double t0_guess_poly[N],
                                double window_low, double window_up) {
  FILE *fp = fopen(filename, "w");
  uint32_t i, j;

  if (fp == NULL) {
    return 0;
  }

  fprintf(fp, "/* Objective function */\n");
  fprintf(fp, "min: ;\n\n");
  fprintf(fp, "/* Constraints */\n");
  for (i = 0; i < list->size; i++) {
    const sparse_ineq_t *row = &list->rows[i];
    for (j = 0; j < row->nnz; j++) {
      int coeff = row->coeff[j];
      if (coeff >= 0) {
        fprintf(fp, "+");
      }
      if (coeff == -1) {
        fprintf(fp, "-s%u", row->idx[j]);
      } else if (coeff == 1) {
        fprintf(fp, "s%u", row->idx[j]);
      } else {
        fprintf(fp, "%d s%u", coeff, row->idx[j]);
      }
      if (j + 1 < row->nnz) {
        fprintf(fp, " ");
      }
    }
    fprintf(fp, " <= %.17g;\n", row->bound);
  }

  fprintf(fp, "\n/* Variable bounds */\n");
  for (j = 0; j < N; j++) {
    double lb = get_max(t0_guess_poly[j] + window_low);
    double ub = get_min(t0_guess_poly[j] + window_up);
    fprintf(fp, "%.17g <= s%u <= %.17g;\n", lb, j, ub);
  }

  fclose(fp);
  return 1;
}

static int dump_sparse_lps(int sk_index, sparse_ineq_list_t ineqs[K],
                           double t0_guess[K][N], double window_low,
                           double window_up) {
  char directory[64];
  char filename[96];
  struct stat st = {0};
  uint32_t poly_index;

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

  for (poly_index = 0; poly_index < K; poly_index++) {
#ifdef T0_NOISY_EQUALITY
    sprintf(filename, "../Lps/%.16s/key%d/poly%d_eq.lp", CRYPTO_ALGNAME,
            sk_index, poly_index);
#else
    sprintf(filename, "../Lps/%.16s/key%d/poly%d.lp", CRYPTO_ALGNAME, sk_index,
            poly_index);
#endif
    if (!write_sparse_lp_file(filename, &ineqs[poly_index],
                              t0_guess[poly_index], window_low, window_up)) {
      return 0;
    }
  }
  return 1;
}

static int read_hex_blob_line(FILE *infile, uint8_t *out, size_t length) {
  int ch;
  int started = 0;
  size_t i;
  unsigned char ich;

  memset(out, 0x00, length);

  while ((ch = fgetc(infile)) != EOF) {
    if (!isxdigit(ch)) {
      if (!started) {
        continue;
      }
      break;
    }

    started = 1;
    if ((ch >= '0') && (ch <= '9'))
      ich = (unsigned char)(ch - '0');
    else if ((ch >= 'A') && (ch <= 'F'))
      ich = (unsigned char)(ch - 'A' + 10);
    else if ((ch >= 'a') && (ch <= 'f'))
      ich = (unsigned char)(ch - 'a' + 10);
    else
      ich = 0;

    for (i = 0; i < length - 1; i++) {
      out[i] = (uint8_t)((out[i] << 4) | (out[i + 1] >> 4));
    }
    out[length - 1] = (uint8_t)((out[length - 1] << 4) | ich);
  }

  return started;
}

static double violation_from_slack(double slack) {
  return (slack < 0.0) ? -slack : 0.0;
}

static int is_truthy_str(const char *s) {
  if (s == NULL) {
    return 0;
  }
  if (!strcmp(s, "1") || !strcmp(s, "true") || !strcmp(s, "TRUE") ||
      !strcmp(s, "on") || !strcmp(s, "ON")) {
    return 1;
  }
  return 0;
}

static uint32_t count_violated(const sparse_ineq_list_t *ineqs) {
  uint32_t i;
  uint32_t count = 0;

  for (i = 0; i < ineqs->size; i++) {
    if (ineqs->rows[i].slack < 0.0) {
      count++;
    }
  }
  return count;
}

static int check_and_repair_state(sparse_ineq_list_t *ineqs, const int32_t x[N],
                                  double *objective_io, uint32_t *violated_io,
                                  uint32_t poly_index, uint32_t pass_index,
                                  const char *stage_tag) {
  const double eps = 1e-6;
  uint32_t i, j;
  uint32_t violated = 0;
  uint32_t worst_row = 0;
  double objective_recomputed = 0.0;
  double max_slack_diff = 0.0;
  double old_objective = *objective_io;
  int mismatch = 0;

  for (i = 0; i < ineqs->size; i++) {
    double dot = 0.0;
    double expected_slack;
    double diff;
    for (j = 0; j < ineqs->rows[i].nnz; j++) {
      uint16_t idx = ineqs->rows[i].idx[j];
      dot += ((double)ineqs->rows[i].coeff[j]) * ((double)x[idx]);
    }
    expected_slack = ineqs->rows[i].bound - dot;
    diff = fabs(expected_slack - ineqs->rows[i].slack);
    if (diff > max_slack_diff) {
      max_slack_diff = diff;
      worst_row = i;
    }
    ineqs->rows[i].slack = expected_slack;
    objective_recomputed += violation_from_slack(expected_slack);
    if (expected_slack < 0.0) {
      violated++;
    }
  }

  if (fabs(objective_recomputed - old_objective) > eps || max_slack_diff > eps) {
    mismatch = 1;
    printf(
        "[CONSISTENCY][WARN] poly#%u pass#%u stage=%s obj_diff=%.6f "
        "max_slack_diff=%.6f(row=%u)\n",
        poly_index, pass_index, stage_tag, fabs(objective_recomputed - old_objective),
        max_slack_diff, worst_row);
  }

  *objective_io = objective_recomputed;
  *violated_io = violated;
  return mismatch;
}

static uint32_t compute_pass_budget(float c_up, uint32_t base_max_passes) {
  const double max_c = (double)(1U << (D - 1));
  double c = (c_up < 1.0f) ? 1.0 : (double)c_up;
  double level = log(max_c / c) / log(2.0);

  if (level < 0.0) {
    level = 0.0;
  }
  return base_max_passes + (uint32_t)(24.0 * level);
}

static double read_positive_env_double(const char *name, double fallback) {
  const char *value = getenv(name);
  char *end = NULL;
  double parsed;

  if (value == NULL || value[0] == '\0') {
    return fallback;
  }

  parsed = strtod(value, &end);
  if (end == value || *end != '\0' || !isfinite(parsed) || parsed <= 0.0) {
    printf("Ignoring invalid %s=%s; using %.2f\n", name, value, fallback);
    return fallback;
  }
  return parsed;
}

static double compute_filter_c(float c_up, double low_c_relax_factor) {
  double c = (c_up < 1.0f) ? 1.0 : (double)c_up;
  if (c <= LOW_C_RELAX_THRESHOLD) {
    c *= low_c_relax_factor;
  }
  return c;
}

static int build_adjacency(const sparse_ineq_list_t *ineqs, adj_entry_t **entries,
                           uint32_t **offsets) {
  uint32_t deg[N];
  uint32_t cursor[N];
  uint32_t total_nnz = 0;
  uint32_t i, j;

  memset(deg, 0, sizeof(deg));

  for (i = 0; i < ineqs->size; i++) {
    for (j = 0; j < ineqs->rows[i].nnz; j++) {
      uint16_t idx = ineqs->rows[i].idx[j];
      deg[idx]++;
      total_nnz++;
    }
  }

  *offsets = (uint32_t *)malloc((N + 1) * sizeof(**offsets));
  if (*offsets == NULL) {
    return 0;
  }

  if (total_nnz == 0) {
    *entries = NULL;
    for (j = 0; j <= N; j++) {
      (*offsets)[j] = 0;
    }
    return 1;
  }

  *entries = (adj_entry_t *)malloc(total_nnz * sizeof(**entries));
  if (*entries == NULL) {
    free(*offsets);
    *offsets = NULL;
    return 0;
  }

  (*offsets)[0] = 0;
  for (j = 0; j < N; j++) {
    (*offsets)[j + 1] = (*offsets)[j] + deg[j];
    cursor[j] = (*offsets)[j];
  }

  for (i = 0; i < ineqs->size; i++) {
    for (j = 0; j < ineqs->rows[i].nnz; j++) {
      uint16_t idx = ineqs->rows[i].idx[j];
      uint32_t pos = cursor[idx]++;
      (*entries)[pos].ineq_index = i;
      (*entries)[pos].coeff = ineqs->rows[i].coeff[j];
    }
  }

  return 1;
}

static int8_t row_coeff_at(const sparse_ineq_t *row, uint16_t var_idx) {
  uint16_t t;
  for (t = 0; t < row->nnz; t++) {
    if (row->idx[t] == var_idx) {
      return row->coeff[t];
    }
  }
  return 0;
}

static uint32_t select_topk_impact(const double impact[N], uint16_t *top_idx,
                                   uint32_t topk) {
  uint8_t chosen[N];
  uint32_t out_count = 0;
  uint32_t i, j;

  if (topk > N) {
    topk = N;
  }

  memset(chosen, 0, sizeof(chosen));
  for (i = 0; i < topk; i++) {
    double best = 0.0;
    int best_j = -1;
    for (j = 0; j < N; j++) {
      if (chosen[j]) {
        continue;
      }
      if (impact[j] > best) {
        best = impact[j];
        best_j = (int)j;
      }
    }
    if (best_j < 0) {
      break;
    }
    chosen[best_j] = 1;
    top_idx[out_count++] = (uint16_t)best_j;
  }
  return out_count;
}

static uint32_t next_token(uint32_t *token, uint32_t *seen, uint32_t seen_len) {
  (*token)++;
  if (*token == 0) {
    memset(seen, 0, seen_len * sizeof(*seen));
    *token = 1;
  }
  return *token;
}

static int try_pair_escape(sparse_ineq_list_t *ineqs, int32_t x[N],
                           const int32_t lb[N], const int32_t ub[N],
                           const adj_entry_t *entries, const uint32_t *offsets,
                           uint32_t *seen, uint32_t *seen_token,
                           double *objective, uint32_t *moves_total,
                           uint32_t *escape_moves_out) {
  double impact[N];
  uint16_t top_idx[ESCAPE_TOPK];
  uint32_t top_count;
  uint32_t i, j;

  int best_a = -1, best_b = -1;
  int best_da = 0, best_db = 0;
  double best_delta_obj = 0.0;

  memset(impact, 0, sizeof(impact));
  for (i = 0; i < ineqs->size; i++) {
    double viol = violation_from_slack(ineqs->rows[i].slack);
    if (viol <= 0.0) {
      continue;
    }
    for (j = 0; j < ineqs->rows[i].nnz; j++) {
      uint16_t idx = ineqs->rows[i].idx[j];
      impact[idx] += viol * (double)abs((int)ineqs->rows[i].coeff[j]);
    }
  }

  top_count = select_topk_impact(impact, top_idx, ESCAPE_TOPK);
  if (top_count < 2) {
    return 0;
  }

  for (i = 0; i < top_count; i++) {
    uint16_t a = top_idx[i];
    uint32_t i2;
    for (i2 = i + 1; i2 < top_count; i2++) {
      uint16_t b = top_idx[i2];
      int da, db;

      for (da = -1; da <= 1; da += 2) {
        if (x[a] + da < lb[a] || x[a] + da > ub[a]) {
          continue;
        }
        for (db = -1; db <= 1; db += 2) {
          double delta_obj = 0.0;
          uint32_t token;
          uint32_t pos;

          if (x[b] + db < lb[b] || x[b] + db > ub[b]) {
            continue;
          }

          token = next_token(seen_token, seen, ineqs->size);
          for (pos = offsets[a]; pos < offsets[a + 1]; pos++) {
            uint32_t ineq_index = entries[pos].ineq_index;
            const sparse_ineq_t *row;
            double old_slack, new_slack;
            int8_t ca, cb;

            if (seen[ineq_index] == token) {
              continue;
            }
            seen[ineq_index] = token;
            row = &ineqs->rows[ineq_index];
            old_slack = row->slack;
            ca = row_coeff_at(row, a);
            cb = row_coeff_at(row, b);
            new_slack = old_slack - (double)ca * da - (double)cb * db;
            delta_obj +=
                violation_from_slack(new_slack) - violation_from_slack(old_slack);
          }
          for (pos = offsets[b]; pos < offsets[b + 1]; pos++) {
            uint32_t ineq_index = entries[pos].ineq_index;
            const sparse_ineq_t *row;
            double old_slack, new_slack;
            int8_t ca, cb;

            if (seen[ineq_index] == token) {
              continue;
            }
            seen[ineq_index] = token;
            row = &ineqs->rows[ineq_index];
            old_slack = row->slack;
            ca = row_coeff_at(row, a);
            cb = row_coeff_at(row, b);
            new_slack = old_slack - (double)ca * da - (double)cb * db;
            delta_obj +=
                violation_from_slack(new_slack) - violation_from_slack(old_slack);
          }

          if (delta_obj < best_delta_obj - 1e-12) {
            best_delta_obj = delta_obj;
            best_a = (int)a;
            best_b = (int)b;
            best_da = da;
            best_db = db;
          }
        }
      }
    }
  }

  if (best_a < 0) {
    return 0;
  }

  x[best_a] += best_da;
  x[best_b] += best_db;
  *objective += best_delta_obj;
  *moves_total += 2;
  (*escape_moves_out)++;

  {
    uint16_t a = (uint16_t)best_a;
    uint16_t b = (uint16_t)best_b;
    uint32_t token = next_token(seen_token, seen, ineqs->size);
    uint32_t pos;

    for (pos = offsets[a]; pos < offsets[a + 1]; pos++) {
      uint32_t ineq_index = entries[pos].ineq_index;
      sparse_ineq_t *row;
      int8_t ca, cb;
      if (seen[ineq_index] == token) {
        continue;
      }
      seen[ineq_index] = token;
      row = &ineqs->rows[ineq_index];
      ca = row_coeff_at(row, a);
      cb = row_coeff_at(row, b);
      row->slack -= (double)ca * best_da + (double)cb * best_db;
    }
    for (pos = offsets[b]; pos < offsets[b + 1]; pos++) {
      uint32_t ineq_index = entries[pos].ineq_index;
      sparse_ineq_t *row;
      int8_t ca, cb;
      if (seen[ineq_index] == token) {
        continue;
      }
      seen[ineq_index] = token;
      row = &ineqs->rows[ineq_index];
      ca = row_coeff_at(row, a);
      cb = row_coeff_at(row, b);
      row->slack -= (double)ca * best_da + (double)cb * best_db;
    }
  }

  return 1;
}

static uint32_t greedy_solve_poly(sparse_ineq_list_t *ineqs, int32_t x[N],
                                  const int32_t lb[N], const int32_t ub[N],
                                  uint32_t max_passes, int max_step_power,
                                  uint32_t stagnation_passes_limit,
                                  double *objective_out, uint32_t *violated_out,
                                  uint32_t *passes_used_out,
                                  uint32_t *escape_moves_out,
                                  uint32_t poly_index,
                                  int consistency_check_mode) {
  adj_entry_t *entries = NULL;
  uint32_t *offsets = NULL;
  uint32_t *seen = NULL;
  uint32_t seen_token = 1;
  uint32_t i, j, pass;
  uint32_t moves_total = 0;
  uint32_t escape_moves = 0;
  uint32_t stagnant_passes = 0;
  uint32_t passes_used = 0;
  double objective = 0.0;
  uint32_t rand_state = 0xA511E9B3u ^ (uint32_t)ineqs->size;

  if (!build_adjacency(ineqs, &entries, &offsets)) {
    *objective_out = 0.0;
    *violated_out = ineqs->size;
    *passes_used_out = 0;
    *escape_moves_out = 0;
    return 0;
  }
  if (ineqs->size > 0) {
    seen = (uint32_t *)calloc(ineqs->size, sizeof(*seen));
  }

  for (i = 0; i < ineqs->size; i++) {
    double dot = 0.0;
    for (j = 0; j < ineqs->rows[i].nnz; j++) {
      uint16_t idx = ineqs->rows[i].idx[j];
      dot += ((double)ineqs->rows[i].coeff[j]) * ((double)x[idx]);
    }
    ineqs->rows[i].slack = ineqs->rows[i].bound - dot;
    objective += violation_from_slack(ineqs->rows[i].slack);
  }

  if (consistency_check_mode) {
    check_and_repair_state(ineqs, x, &objective, violated_out, poly_index, 0,
                           "init");
  }

  for (pass = 0; pass < max_passes; pass++) {
    uint32_t moves_this_pass = 0;
    double objective_before = objective;
    double improvement;
    uint32_t start_j;
    uint32_t k;

    rand_state = rand_state * 1664525u + 1013904223u;
    start_j = rand_state % N;

    for (k = 0; k < N; k++) {
      j = (start_j + k) % N;
      int best_delta = 0;
      double best_delta_obj = 0.0;
      int32_t max_up = ub[j] - x[j];
      int32_t max_dn = x[j] - lb[j];
      int32_t max_step = (max_up > max_dn) ? max_up : max_dn;
      int32_t step = 1;

      while (step <= max_step && step <= (1 << max_step_power)) {
        int candidates[2] = {-step, +step};
        uint32_t c_idx;

        for (c_idx = 0; c_idx < 2; c_idx++) {
          int delta = candidates[c_idx];
          double delta_obj = 0.0;
          uint32_t pos;

          if (x[j] + delta < lb[j] || x[j] + delta > ub[j]) {
            continue;
          }

          for (pos = offsets[j]; pos < offsets[j + 1]; pos++) {
            uint32_t ineq_index = entries[pos].ineq_index;
            double old_slack = ineqs->rows[ineq_index].slack;
            double new_slack = old_slack - ((double)entries[pos].coeff * delta);
            delta_obj += violation_from_slack(new_slack) -
                         violation_from_slack(old_slack);
          }

          if (delta_obj < best_delta_obj - 1e-12) {
            best_delta_obj = delta_obj;
            best_delta = delta;
          }
        }
        step <<= 1;
      }

      if (best_delta != 0) {
        uint32_t pos;
        x[j] += best_delta;
        objective += best_delta_obj;
        moves_total++;
        moves_this_pass++;

        for (pos = offsets[j]; pos < offsets[j + 1]; pos++) {
          uint32_t ineq_index = entries[pos].ineq_index;
          ineqs->rows[ineq_index].slack -=
              ((double)entries[pos].coeff * best_delta);
        }
      }
    }

    passes_used = pass + 1;
    improvement = objective_before - objective;
    if (moves_this_pass == 0 && objective > 0.0 && seen != NULL) {
      if (try_pair_escape(ineqs, x, lb, ub, entries, offsets, seen, &seen_token,
                          &objective, &moves_total, &escape_moves)) {
        moves_this_pass = 1;
        improvement = objective_before - objective;
      }
    }

    if (consistency_check_mode) {
      uint32_t violated_now = 0;
      check_and_repair_state(ineqs, x, &objective, &violated_now, poly_index,
                             pass + 1, "pass");
      improvement = objective_before - objective;
    }

    if (moves_this_pass == 0 || objective <= 0.0) {
      break;
    }

    if (improvement <= (1e-6 * (1.0 + fabs(objective_before)))) {
      stagnant_passes++;
      if (stagnant_passes >= stagnation_passes_limit) {
        break;
      }
    } else {
      stagnant_passes = 0;
    }
  }

  *objective_out = objective;
  *violated_out = count_violated(ineqs);
  *passes_used_out = passes_used;
  *escape_moves_out = escape_moves;

  if (entries != NULL) {
    free(entries);
  }
  if (offsets != NULL) {
    free(offsets);
  }
  if (seen != NULL) {
    free(seen);
  }
  return moves_total;
}

int main(int argc, char const *argv[]) {
  uint32_t NB_INEQ;
  int sk_index;
  int consistency_check_mode = 0;
  float C_low, C_up;
  double filter_c;
  double window_low, window_up;
  double window_alpha;
  double low_c_relax_factor;
  uint32_t max_passes = DEFAULT_MAX_PASSES;
  const char *env_check = getenv("GREEDY_CONSISTENCY_CHECK");

  char t0_guess_filename[256];
  FILE *t0_guess_file = NULL;
  double t0_guess[K][N];
  double t0_guess_updated[K][N];

  char sign_compressed_file_name[128];
  FILE *sign_compressed_file = NULL;
  uint8_t sm_compressed[MLEN + COMP_CRYPTO_BYTES];

  uint32_t i, j;
  int8_t ineq_line[N];
  uint32_t cpt_ineq[K], cpt_ineq1[K], cpt_ineq0[K];
  uint32_t poly_index, coeff_index, cpt_signs;
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

  int ret = 0;
  char directory[32];
  struct stat st = {0};
  sparse_ineq_list_t ineqs[K];

  if (is_truthy_str(env_check)) {
    consistency_check_mode = 1;
  }
  if (env_sig_limit != NULL && env_sig_limit[0] != '\0') {
    sig_limit = (uint32_t)strtoul(env_sig_limit, NULL, 10);
  }

  if (argc == 4) {
    sk_index = atoi(argv[1]);
    NB_INEQ = (uint32_t)atoi(argv[2]);
    C_up = strtof(argv[3], NULL);
    C_low = -C_up;
  } else if (argc == 5) {
    sk_index = atoi(argv[1]);
    NB_INEQ = (uint32_t)atoi(argv[2]);
    C_low = -strtof(argv[3], NULL);
    C_up = strtof(argv[4], NULL);
  } else if (argc == 6) {
    sk_index = atoi(argv[1]);
    NB_INEQ = (uint32_t)atoi(argv[2]);
    C_low = -strtof(argv[3], NULL);
    C_up = strtof(argv[4], NULL);
    max_passes = (uint32_t)atoi(argv[5]);
    if (max_passes == 0) {
      max_passes = DEFAULT_MAX_PASSES;
    }
  } else if (argc == 7) {
    sk_index = atoi(argv[1]);
    NB_INEQ = (uint32_t)atoi(argv[2]);
    C_low = -strtof(argv[3], NULL);
    C_up = strtof(argv[4], NULL);
    max_passes = (uint32_t)atoi(argv[5]);
    consistency_check_mode = atoi(argv[6]) ? 1 : 0;
    if (max_passes == 0) {
      max_passes = DEFAULT_MAX_PASSES;
    }
  } else {
    printf("Usage:\n");
#ifdef T0_NOISY_EQUALITY
    printf("  %s <key_idx> <nb_equations> <C>\n", argv[0]);
    printf("  %s <key_idx> <nb_equations> <C_low_abs> <C_up>\n", argv[0]);
    printf("  %s <key_idx> <nb_equations> <C_low_abs> <C_up> <max_passes>\n",
           argv[0]);
    printf(
        "  %s <key_idx> <nb_equations> <C_low_abs> <C_up> <max_passes> "
        "<consistency_check:0|1>\n",
        argv[0]);
#else
    printf("  %s <key_idx> <nb_ineq> <C>\n", argv[0]);
    printf("  %s <key_idx> <nb_ineq> <C_low_abs> <C_up>\n", argv[0]);
    printf("  %s <key_idx> <nb_ineq> <C_low_abs> <C_up> <max_passes>\n",
           argv[0]);
    printf(
        "  %s <key_idx> <nb_ineq> <C_low_abs> <C_up> <max_passes> "
        "<consistency_check:0|1>\n",
        argv[0]);
#endif
    return DATA_ERROR;
  }

  window_alpha = read_positive_env_double("T0_WINDOW_ALPHA",
                                          DEFAULT_WINDOW_ALPHA);
  low_c_relax_factor = read_positive_env_double(
      "T0_LOW_C_RELAX_FACTOR", DEFAULT_LOW_C_RELAX_FACTOR);
  filter_c = compute_filter_c(C_up, low_c_relax_factor);
  window_low = window_alpha * (double)C_low;
  window_up = window_alpha * (double)C_up;

  for (poly_index = 0; poly_index < K; poly_index++) {
    ineqs[poly_index].rows = NULL;
    ineqs[poly_index].size = 0;
    ineqs[poly_index].capacity = 0;
    cpt_ineq[poly_index] = 0;
    cpt_ineq0[poly_index] = 0;
    cpt_ineq1[poly_index] = 0;
  }

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
    ret = DATA_ERROR;
    goto cleanup;
  }

  if (env_guess_file != NULL && env_guess_file[0] != '\0') {
    snprintf(t0_guess_filename, sizeof(t0_guess_filename), "%s",
             env_guess_file);
  } else {
    sprintf(t0_guess_filename, "../Guess/%.16s/key%d/t0_guess_file.bin",
            CRYPTO_ALGNAME, sk_index);
  }
  t0_guess_file = fopen(t0_guess_filename, "rb");
  if (t0_guess_file == NULL) {
    perror("Error opening file");
    ret = FILE_OPEN_ERROR;
    goto cleanup;
  }
  if (fread(t0_guess, sizeof(double), K * N, t0_guess_file) != K * N) {
    printf("Invalid t0 guess file <%s>\n", t0_guess_filename);
    fclose(t0_guess_file);
    ret = DATA_ERROR;
    goto cleanup;
  }
  fclose(t0_guess_file);

  printf("C: %.2f (filter=%.2f, window=[%.2f, %.2f])\n", C_up, filter_c,
         window_low, window_up);
#ifdef T0_NOISY_EQUALITY
  printf("Noisy-equality hill-climb config: window_alpha=%.2f, "
         "low_C_relax=%.2f\n",
         window_alpha, low_c_relax_factor);
#else
  printf("Greedy comparison config: window_alpha=%.2f, low_C_relax=%.2f\n",
         window_alpha, low_c_relax_factor);
#endif
  printf("Consistency check mode: %s\n",
         consistency_check_mode ? "ON" : "OFF");
  start = clock();
  cpt_signs = 0;

#ifdef T0_NOISY_EQUALITY
  while (find_min(cpt_ineq) < NB_INEQ &&
         (sig_limit == 0 || cpt_signs < sig_limit)) {
#else
  while ((sig_limit > 0 && cpt_signs < sig_limit) ||
         (sig_limit == 0 && find_min(cpt_ineq) < NB_INEQ)) {
#endif
    if (!read_hex_blob_line(sign_compressed_file, sm_compressed,
                            MLEN + COMP_CRYPTO_BYTES)) {
      if (find_min(cpt_ineq) == 0) {
        printf("No usable inequalities from <%s>.\n", sign_compressed_file_name);
        ret = DATA_ERROR;
      } else {
        printf("Reached EOF in <%s>, using available inequalities (%u/%u min).\n",
               sign_compressed_file_name, find_min(cpt_ineq), NB_INEQ);
      }
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
        if (noisy_equality_interval_distance(&equation, guess) >
            filter_c * TAU) {
          continue;
        }

        noisy_equality_to_inequalities(&equation, converted);
        for (i = 0; i < 2; i++) {
          if (!add_sparse_constraint(&ineqs[poly_index], ineq_line,
                                     converted[i].sign,
                                     (double)converted[i].bound)) {
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
            if (bound + guess < filter_c * TAU) {
              if (!add_sparse_constraint(&ineqs[poly_index], ineq_line, +1,
                                         bound)) {
                ret = LP_ERROR;
                break;
              }
              cpt_ineq1[poly_index]++;
              cpt_ineq[poly_index]++;
            }
          }

          if (r0.vec[poly_index].coeffs[coeff_index] < 0) {
            creat_ineq(&c, coeff_index, ineq_line);
            guess = scalar_product(ineq_line, t0_guess[poly_index]);
            bound = -GAMMA2 - BETA - 1 - r0.vec[poly_index].coeffs[coeff_index];
            if (bound - guess < filter_c * TAU) {
              if (!add_sparse_constraint(&ineqs[poly_index], ineq_line, -1,
                                         bound)) {
                ret = LP_ERROR;
                break;
              }
              cpt_ineq1[poly_index]++;
              cpt_ineq[poly_index]++;
            }
          }
        } else {
          creat_ineq(&c, coeff_index, ineq_line);
          guess = scalar_product(ineq_line, t0_guess[poly_index]);

          bound = GAMMA2 - BETA - 1 - r0.vec[poly_index].coeffs[coeff_index];
          if (bound - guess < filter_c * TAU) {
            if (!add_sparse_constraint(&ineqs[poly_index], ineq_line, -1,
                                       bound)) {
              ret = LP_ERROR;
              break;
            }
            cpt_ineq0[poly_index]++;
            cpt_ineq[poly_index]++;
          }

          bound = GAMMA2 - BETA - 1 + r0.vec[poly_index].coeffs[coeff_index];
          if (bound + guess < filter_c * TAU) {
            if (!add_sparse_constraint(&ineqs[poly_index], ineq_line, +1,
                                       bound)) {
              ret = LP_ERROR;
              break;
            }
            cpt_ineq0[poly_index]++;
            cpt_ineq[poly_index]++;
          }
        }
#endif
      }
      if (ret != 0) {
        break;
      }
    }

    if (ret != 0) {
      break;
    }
    cpt_signs++;
  }

  end = clock();
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
#ifdef T0_NOISY_EQUALITY
  printf("Building %d noisy-equality models: %f sec/%d signs/", K,
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
#else
  printf(" 1 ineq\n");
#endif

  if (ret == 0 && is_truthy_str(getenv("DUMP_T0_LP_ONLY"))) {
    if (!dump_sparse_lps(sk_index, ineqs, t0_guess, window_low, window_up)) {
      ret = FILE_OPEN_ERROR;
    }
    goto cleanup;
  }

  if (ret == 0) {
    for (poly_index = 0; poly_index < K; poly_index++) {
      int32_t x[N];
      int32_t x_seed[N];
      int32_t x_best[N];
      int32_t x_try[N];
      int32_t lb[N];
      int32_t ub[N];
      int32_t lb_ref[N];
      int32_t ub_ref[N];
      uint32_t moves = 0;
      uint32_t moves_ref = 0;
      uint32_t escape_moves = 0;
      uint32_t escape_moves_ref = 0;
      uint32_t violated = 0;
      uint32_t violated_ref = 0;
      uint32_t passes_used = 0;
      uint32_t passes_used_ref = 0;
      uint32_t pass_budget = compute_pass_budget(C_up, max_passes);
      uint32_t restart_budget =
          (pass_budget / MAIN_RESTART_PASS_DIV) + MAIN_STAGNATION_PASSES + 8;
      uint32_t restart_idx;
      uint32_t restart_best_idx = 0;
      uint32_t restart_moves_total = 0;
      uint32_t restart_escape_total = 0;
      uint32_t restart_passes_total = 0;
      uint32_t total_restarts_used = 1;
      uint32_t rand_state =
          0x9E3779B9u ^ ((uint32_t)poly_index << 16) ^ ((uint32_t)C_up << 1);
      double objective = 0.0;
      double objective_ref = 0.0;
      double best_objective = 0.0;
      uint32_t best_violated = 0;

      for (coeff_index = 0; coeff_index < N; coeff_index++) {
        double g = t0_guess[poly_index][coeff_index];
        int32_t x0 = (int32_t)llround(g);
        int32_t lo = (int32_t)llround(get_max(g + window_low));
        int32_t hi = (int32_t)llround(get_min(g + window_up));

        if (lo > hi) {
          int32_t mid = (lo + hi) / 2;
          lo = mid;
          hi = mid;
        }

        if (x0 < lo) {
          x0 = lo;
        }
        if (x0 > hi) {
          x0 = hi;
        }

        x[coeff_index] = x0;
        x_seed[coeff_index] = x0;
        lb[coeff_index] = lo;
        ub[coeff_index] = hi;
      }

      if (restart_budget > pass_budget) {
        restart_budget = pass_budget;
      }

      start = clock();
      moves = greedy_solve_poly(&ineqs[poly_index], x, lb, ub, pass_budget,
                                MAIN_MAX_STEP_POWER, MAIN_STAGNATION_PASSES,
                                &objective, &violated, &passes_used,
                                &escape_moves, poly_index,
                                consistency_check_mode);
      end = clock();
      cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

      best_objective = objective;
      best_violated = violated;
      for (coeff_index = 0; coeff_index < N; coeff_index++) {
        x_best[coeff_index] = x[coeff_index];
      }
      restart_moves_total = moves;
      restart_escape_total = escape_moves;
      restart_passes_total = passes_used;

      for (restart_idx = 1; restart_idx < MAIN_RESTARTS; restart_idx++) {
        uint32_t moves_try = 0;
        uint32_t escape_try = 0;
        uint32_t violated_try = 0;
        uint32_t passes_try = 0;
        double objective_try = 0.0;

        for (coeff_index = 0; coeff_index < N; coeff_index++) {
          int32_t jitter;
          rand_state = rand_state * 1664525u + 1013904223u;
          jitter = (int32_t)(rand_state % (2 * MAIN_RESTART_JITTER + 1)) -
                   MAIN_RESTART_JITTER;
          x_try[coeff_index] = x_seed[coeff_index] + jitter;
          if (x_try[coeff_index] < lb[coeff_index]) {
            x_try[coeff_index] = lb[coeff_index];
          }
          if (x_try[coeff_index] > ub[coeff_index]) {
            x_try[coeff_index] = ub[coeff_index];
          }
        }

        moves_try = greedy_solve_poly(
            &ineqs[poly_index], x_try, lb, ub, restart_budget,
            MAIN_MAX_STEP_POWER, MAIN_STAGNATION_PASSES, &objective_try,
            &violated_try, &passes_try, &escape_try, poly_index,
            consistency_check_mode);

        restart_moves_total += moves_try;
        restart_escape_total += escape_try;
        restart_passes_total += passes_try;
        total_restarts_used++;

        if ((objective_try < best_objective - 1e-9) ||
            (fabs(objective_try - best_objective) <= 1e-9 &&
             violated_try < best_violated)) {
          best_objective = objective_try;
          best_violated = violated_try;
          restart_best_idx = restart_idx;
          for (coeff_index = 0; coeff_index < N; coeff_index++) {
            x_best[coeff_index] = x_try[coeff_index];
          }
        }
      }

      objective = best_objective;
      violated = best_violated;
      for (coeff_index = 0; coeff_index < N; coeff_index++) {
        x[coeff_index] = x_best[coeff_index];
      }

      for (coeff_index = 0; coeff_index < N; coeff_index++) {
        int32_t lo = x[coeff_index] - 2;
        int32_t hi = x[coeff_index] + 2;
        if (lo < lb[coeff_index]) {
          lo = lb[coeff_index];
        }
        if (hi > ub[coeff_index]) {
          hi = ub[coeff_index];
        }
        lb_ref[coeff_index] = lo;
        ub_ref[coeff_index] = hi;
      }

      moves_ref = greedy_solve_poly(
          &ineqs[poly_index], x, lb_ref, ub_ref, REFINEMENT_MAX_PASSES,
          REFINEMENT_MAX_STEP_POWER, REFINEMENT_STAGNATION_PASSES,
          &objective_ref, &violated_ref, &passes_used_ref, &escape_moves_ref,
          poly_index, consistency_check_mode);

      for (coeff_index = 0; coeff_index < N; coeff_index++) {
        t0_guess_updated[poly_index][coeff_index] = (double)x[coeff_index];
      }

      printf(
          "Solving GR#%d (restarts %u, best#%u, passes %u/%u, moves %u, escape "
          "%u, violated %u, obj %.1f): %f sec\n",
          poly_index, total_restarts_used, restart_best_idx,
          restart_passes_total, pass_budget, restart_moves_total,
          restart_escape_total, violated, objective, cpu_time_used);
      printf(
          "Refine GR#%d (passes %u/%u, moves %u, escape %u, violated %u, obj "
          "%.1f)\n",
          poly_index, passes_used_ref, REFINEMENT_MAX_PASSES, moves_ref,
          escape_moves_ref, violated_ref, objective_ref);
    }

    t0_guess_file = fopen(t0_guess_filename, "wb");
    if (t0_guess_file == NULL) {
      perror("Error opening file");
      ret = FILE_OPEN_ERROR;
      goto cleanup;
    }
    fwrite(t0_guess_updated, sizeof(double), K * N, t0_guess_file);
    fclose(t0_guess_file);
  }

cleanup:
  for (poly_index = 0; poly_index < K; poly_index++) {
    if (ineqs[poly_index].rows != NULL) {
      free(ineqs[poly_index].rows);
      ineqs[poly_index].rows = NULL;
    }
  }

  if (sign_compressed_file != NULL) {
    fclose(sign_compressed_file);
  }
  return ret;
}
