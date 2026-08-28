## Files

| Name                      | Description                                           |
| :---                      | :---                                                  |
| `additional_fct.c`        | C auxiliary functions used in the attack              |
| `build_solve_t0_lp.c`     | Main function used for the attack                     |
| `build_solve_t0_greedy.c` | Greedy-based inequality solver for `t0` reconstruction |
| `noisy_equality.[ch]`     | Shared noisy-equality to two-inequality conversion     |
| `test_noisy_equality.c`   | Formula and interval-conversion unit test              |

`build_solve_t0_lp.c` and `build_solve_t0_greedy.c` retain the original
acceptance-inequality behavior by default. The Makefile compiles them with
`T0_NOISY_EQUALITY` for the separate `build_solve_t0_eq_lp{2,3,5}` and
`build_solve_t0_eq_greedy{2,3,5}` executables.

Run `make check-noisy-equality` to test all three parameter sets.



