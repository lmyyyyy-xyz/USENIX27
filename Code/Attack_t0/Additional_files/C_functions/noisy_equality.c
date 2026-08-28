#include "noisy_equality.h"

#include <stddef.h>

#include "params.h"

#define EQUATION_ERROR_ABS (GAMMA2 - BETA - 1)

int noisy_equality_from_signature(int32_t hint, int32_t r0,
                                  noisy_equality_t *equation) {
  if (equation == NULL) {
    return 0;
  }

  if (hint == 0) {
    equation->rhs = r0;
    equation->error_low = -EQUATION_ERROR_ABS;
    equation->error_high = EQUATION_ERROR_ABS;
    return 1;
  }

  if (hint != 1) {
    return 0;
  }

  if (r0 > 0) {
    equation->rhs = r0 - 2 * GAMMA2;
    equation->error_low = 0;
    equation->error_high = EQUATION_ERROR_ABS;
    return 1;
  }

  if (r0 < 0) {
    equation->rhs = r0 + 2 * GAMMA2;
    equation->error_low = -EQUATION_ERROR_ABS;
    equation->error_high = 0;
    return 1;
  }

  /* A set hint with r0 == 0 has no documented equality branch. */
  return 0;
}

void noisy_equality_to_inequalities(const noisy_equality_t *equation,
                                    noisy_inequality_t inequalities[2]) {
  const int32_t lower = equation->rhs + equation->error_low;
  const int32_t upper = equation->rhs + equation->error_high;

  inequalities[0].sign = +1;
  inequalities[0].bound = upper;
  inequalities[1].sign = -1;
  inequalities[1].bound = -lower;
}

double noisy_equality_row_dot(const int8_t row[N], const double x[N]) {
  double result = 0.0;
  uint32_t i;

  for (i = 0; i < N; i++) {
    result += (double)row[i] * x[i];
  }
  return result;
}

double noisy_equality_interval_distance(const noisy_equality_t *equation,
                                        double row_dot) {
  const double lower = (double)equation->rhs + equation->error_low;
  const double upper = (double)equation->rhs + equation->error_high;

  if (row_dot < lower) {
    return lower - row_dot;
  }
  if (row_dot > upper) {
    return row_dot - upper;
  }
  return 0.0;
}
