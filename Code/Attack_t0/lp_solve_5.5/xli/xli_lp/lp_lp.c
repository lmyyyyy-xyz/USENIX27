
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
#include <string.h>
#include "lp_lib.h"

/* Include libraries for this language system */
#include <math.h>

#ifdef FORTIFY
# include "lp_fortify.h"
#endif

#define LPSOLVEAPIFROMLPRECDEF

#include "lp_explicit.h"

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
  return( "XLI_lp v1.0" );
}

MYBOOL XLI_CALLMODEL xli_readmodel(lprec *lp, char *model, char *data, char *options, int verbose)
{
  MYBOOL status;
  FILE *fpin;

  lp0 = lp;

  init_lpsolve(lp);

  /* lp = read_LPex(lp, model, verbose, ""); */
  if((fpin = fopen(model, "r")) != NULL) {
    status = LP_readhandle(&lp, fpin, verbose, "");
    fclose(fpin);
  }
  else
    status = FALSE;

  return(status);
}

MYBOOL XLI_CALLMODEL xli_writemodel(lprec *lp, char *filename, char *options, MYBOOL results)
{
  MYBOOL status;
  MYBOOL scaling_used;
  int argc, i;
  char **argv, bas = FALSE;

  setarg(options, &argc, &argv);

  lp0 = lp;

  init_lpsolve(lp);

  scaling_used = lp->scaling_used;

  for(i = 0; i < argc; i++)
    if ((strcmp(argv[i], "-h") == 0) || (strcmp(argv[i], "-help") == 0) || (strcmp(argv[i], "--help") == 0)) {
      lp->report(lp, NEUTRAL, "xli_LP.xli_writemodel options:\n");
      lp->report(lp, NEUTRAL, "  -scaled: Write scaled model\n");
      return(FALSE);
    }
    else if (strcmp(argv[i], "-scaled") == 0)
      lp->scaling_used = FALSE;
    else {
      lp->report(lp, IMPORTANT, "xli_LP.xli_writemodel: option %s unsupported.\n", argv[i]);
	  return(FALSE);
    }

  status = write_lp(lp, filename);
  lp->scaling_used = scaling_used;

  return(status);
}

