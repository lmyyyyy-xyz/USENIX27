#define LPSOLVEAPIFROMLPREC

#include "lp_explicit.h"

#undef read_mps
#undef read_MPS
#undef write_mps

#define mat_validate(matA) TRUE

#include "../../lp_MPS.c"
