#define LPSOLVEAPIFROMLPREC

#include "lp_explicit.h"

#undef write_lnd

#define mat_validate(matA) TRUE

#include "lp_wlnd.c"
