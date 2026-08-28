#include <math.h>
#include <stdint.h>
#include <stdio.h>

#include "noisy_equality.h"
#include "params.h"

#define EQUATION_ERROR_ABS (GAMMA2 - BETA - 1)

static int check_equation(int32_t hint, int32_t r0, int32_t rhs,
                          int32_t error_low, int32_t error_high) {
  noisy_equality_t equation;
  noisy_inequality_t inequalities[2];

  if (!noisy_equality_from_signature(hint, r0, &equation)) {
    return 0;
  }
  if (equation.rhs != rhs || equation.error_low != error_low ||
      equation.error_high != error_high) {
    return 0;
  }

  noisy_equality_to_inequalities(&equation, inequalities);
  if (inequalities[0].sign != 1 ||
      inequalities[0].bound != rhs + error_high) {
    return 0;
  }
  if (inequalities[1].sign != -1 ||
      inequalities[1].bound != -(rhs + error_low)) {
    return 0;
  }
  return 1;
}

int main(void) {
  noisy_equality_t equation;
  int8_t row[N] = {0};
  double x[N] = {0.0};
  double dot;

  if (!check_equation(0, 123, 123, -EQUATION_ERROR_ABS,
                      EQUATION_ERROR_ABS)) {
    return 1;
  }
  if (!check_equation(1, 123, 123 - 2 * GAMMA2, 0,
                      EQUATION_ERROR_ABS)) {
    return 2;
  }
  if (!check_equation(1, -123, -123 + 2 * GAMMA2,
                      -EQUATION_ERROR_ABS, 0)) {
    return 3;
  }
  if (noisy_equality_from_signature(1, 0, &equation)) {
    return 4;
  }
  if (noisy_equality_from_signature(2, 1, &equation)) {
    return 5;
  }

  row[0] = 1;
  row[1] = -1;
  x[0] = 100.0;
  x[1] = 25.0;
  dot = noisy_equality_row_dot(row, x);
  if (fabs(dot - 75.0) > 1e-12) {
    return 6;
  }

  equation.rhs = 70;
  equation.error_low = -5;
  equation.error_high = 10;
  if (noisy_equality_interval_distance(&equation, 75.0) != 0.0 ||
      noisy_equality_interval_distance(&equation, 60.0) != 5.0 ||
      noisy_equality_interval_distance(&equation, 90.0) != 10.0) {
    return 7;
  }

  printf("noisy_equality: all tests passed\n");
  return 0;
}
