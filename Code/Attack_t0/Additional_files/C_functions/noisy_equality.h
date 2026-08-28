#ifndef NOISY_EQUALITY_H
#define NOISY_EQUALITY_H

#include <stdint.h>

#include "params.h"

/* A noisy equation is interpreted as
 *
 *   <row, t0> = rhs + error,  error_low <= error <= error_high.
 *
 * The two returned inequalities always use the canonical form
 *
 *   sign * <row, t0> <= bound.
 */
typedef struct {
  int32_t rhs;
  int32_t error_low;
  int32_t error_high;
} noisy_equality_t;

typedef struct {
  int sign;
  int32_t bound;
} noisy_inequality_t;

int noisy_equality_from_signature(int32_t hint, int32_t r0,
                                  noisy_equality_t *equation);

void noisy_equality_to_inequalities(const noisy_equality_t *equation,
                                    noisy_inequality_t inequalities[2]);

double noisy_equality_row_dot(const int8_t row[N], const double x[N]);

double noisy_equality_interval_distance(const noisy_equality_t *equation,
                                        double row_dot);

#endif
