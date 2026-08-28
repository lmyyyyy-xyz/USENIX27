
/*  Modularized external language interface module - w/interface for lp_solve v5.0+
   ----------------------------------------------------------------------------------
    Author:        Peter Notebaert
    Contact:       lpsolve@peno.be
    License terms: LGPL.

    Template used:
    Requires:

    Release notes:
    v1.0.0  31 July 2004        First implementation.

   ---------------------------------------------------------------------------------- */

/* Generic include libraries */
#include <sys/types.h>
/*#include <malloc.h>*/
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "lp_lib.h"

/* Include libraries for this language system */
#include <math.h>

#ifdef FORTIFY
# include "lp_fortify.h"
#endif

#define LPSOLVEAPIFROMLPRECDEF

#include "lp_explicit.h"

#include "lp_rlpt.h"
#include "lp_wlpt.h"

#include "args.h"

/* Include routines common to language interface implementations */
#include "lp_XLI1.c"

#if defined _MSC_VER
# define vsnprintf _vsnprintf
#endif

#undef report

static lprec *lp0;

/* Various reporting functions for lp_solve                                  */
/* ------------------------------------------------------------------------- */

/* First define general utilties for reporting and output */
#if 0
void __WINAPI report(lprec *lp, int level, char *format, ...)
{
  static char buff[DEF_STRBUFSIZE+1];
  static va_list ap;

  va_start(ap, format);
  vsnprintf(buff, DEF_STRBUFSIZE, format, ap);
  va_end(ap);
  lp0->report(lp0, level, "%s", buff);
}
#endif

int SOS_count(lprec *lp)
{
  if(lp->SOS == NULL)
    return( 0 );
  else
    return( lp->SOS->sos_count );
}

MYBOOL is_splitvar(lprec *lp, int column)
/* Two cases handled by var_is_free:

   1) LB:-Inf / UB:<Inf variables
      No helper column created, sign of var_is_free set negative with index to itself.
   2) LB:-Inf / UB: Inf (free) variables
      Sign of var_is_free set positive with index to new helper column,
      helper column created with negative var_is_free with index to the original column.

   This function helps identify the helper column in 2).
*/
{
   return((MYBOOL) ((lp->var_is_free != NULL) &&
                    (lp->var_is_free[column] < 0) && (-lp->var_is_free[column] != column)));
}

REAL unscaled_mat(lprec *lp, REAL value, int row, int col)
{
  if(lp->scaling_used)
    value /= lp->scalars[row] * lp->scalars[lp->rows + col];
  return( value );
}

MYBOOL is_chsign(lprec *lp, int rownr)
{
  return( (MYBOOL) ((lp->row_type[rownr] & ROWTYPE_CONSTRAINT) == ROWTYPE_CHSIGN) );
}


char * XLI_CALLMODEL xli_name(void)
{
  return( "XLI_XPRESS v1.0" );
}

MYBOOL XLI_CALLMODEL xli_readmodel(lprec *lp, char *model, char *data, char *options, int verbose)
{
  MYBOOL status;
  int argc, i;
  char **argv;
  char objconst = TRUE;

  setarg(options, &argc, &argv);

  lp0 = lp;

  init_lpsolve(lp);

  for(i = 0; i < argc; i++)
    if (strcmp(argv[i], "-objconst") == 0)
      objconst = TRUE;
    else if (strcmp(argv[i], "-noobjconst") == 0)
      objconst = FALSE;
    else
      lp->report(lp, IMPORTANT, "xli_XPRESS.xli_readmodel: option %s unknown. Ignoring.\n", argv[i]);

  lp = read_LPTex(lp, model, verbose, "", objconst);
  status = (lp != NULL);

  freearg(argc, argv);

  return(status);
}

MYBOOL XLI_CALLMODEL xli_writemodel(lprec *lp, char *filename, char *options, MYBOOL results)
{
  MYBOOL status;
  int argc, i;
  char **argv;
  char objconst = FALSE;

  setarg(options, &argc, &argv);

  lp0 = lp;

  init_lpsolve(lp);

  for(i = 0; i < argc; i++)
    if (strcmp(argv[i], "-objconst") == 0)
      objconst = TRUE;
    else if (strcmp(argv[i], "-noobjconst") == 0)
      objconst = FALSE;
    else
      lp->report(lp, IMPORTANT, "xli_XPRESS.xli_writemodel: option %s unknown. Ignoring.\n", argv[i]);

  status = write_lpt(lp, filename, objconst);

  freearg(argc, argv);

  return(status);
}

