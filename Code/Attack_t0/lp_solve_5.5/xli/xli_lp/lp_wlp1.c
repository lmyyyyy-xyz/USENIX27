#define LPSOLVEAPIFROMLPREC

#include "lp_explicit.h"

#undef write_lp

#define mat_validate(matA) TRUE

#include "lp_wlp.c"
