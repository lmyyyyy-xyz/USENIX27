
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
#include "lp_lib.h"
#include "../../lp_MPS.h"

/* Include libraries for this language system */
#include <math.h>

#ifdef FORTIFY
# include "lp_fortify.h"
#endif

#define LPSOLVEAPIFROMLPRECDEF

#include "lp_explicit.h"

#include "args.h"

/* Include routines common to language interface implementations */
#include "lp_XLI1.c"

#if defined _MSC_VER
# define vsnprintf _vsnprintf
#endif

#undef report

static lprec *lp0;

extern int _MPSFREEPrecision;

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

REAL unscaled_value(lprec *lp, REAL value, int index)
{
  if(fabs(value) < lp->infinite) {
    if(lp->scaling_used)
      if(index > lp->rows)
        value *= lp->scalars[index];
      else
        value /= lp->scalars[index];
  }
  else
    value = my_sign(value)*lp->infinite;
  return(value);
}

STATIC MYBOOL modifyUndoLadder(DeltaVrec *DV, int itemno, REAL target[], REAL newvalue)
{
    return(FALSE);
}

MYBOOL is_chsign(lprec *lp, int rownr)
{
  return( (MYBOOL) ((lp->row_type[rownr] & ROWTYPE_CONSTRAINT) == ROWTYPE_CHSIGN) );
}

char * XLI_CALLMODEL xli_name(void)
{
  return( "XLI_MPS v1.1" );
}

MYBOOL XLI_CALLMODEL xli_readmodel(lprec *lp, char *model, char *data, char *options, int verbose)
{
  MYBOOL status;
  FILE *fpin;
  int typeMPS = MPSFIXED;
  int argc, i;
  char **argv;  

  setarg(options, &argc, &argv);

  lp0 = lp;

  init_lpsolve(lp);

  for(i = 0; i < argc; i++)
    if ((strcmp(argv[i], "-h") == 0) || (strcmp(argv[i], "-help") == 0) || (strcmp(argv[i], "--help") == 0)) {
      lp->report(lp, NEUTRAL, "xli_MPS.xli_readmodel options:\n");
      lp->report(lp, NEUTRAL, "  -free: Read free MPS format\n");
      lp->report(lp, NEUTRAL, "  -negobjconst: Negate objective function\n");
      lp->report(lp, NEUTRAL, "  -bas: Write basis file\n");
      return(FALSE);
    }
    else if (strcmp(argv[i], "-free") == 0)
      typeMPS = (typeMPS & ~MPSFIXED) | MPSFREE;
    else if (strcmp(argv[i], "-ibm") == 0)
      typeMPS |= MPSIBM;
    else if (strcmp(argv[i], "-negobjconst") == 0)
      typeMPS |= MPSNEGOBJCONST;
	else {
      lp->report(lp, IMPORTANT, "xli_MPS.xli_readmodel: option %s unsupported.\n", argv[i]);
	  return(FALSE);
	}

#if 1
  status = MPS_readfile(&lp, model, typeMPS, verbose);
#else
  if((fpin = fopen(model, "r")) != NULL) {
    status = read_MPShandle(&lp, fpin, typeMPS, verbose);
    fclose(fpin);
  }
  else
    status = FALSE;
#endif

  return(status);
}

MYBOOL XLI_CALLMODEL xli_writemodel(lprec *lp, char *filename, char *options, MYBOOL results)
{
  MYBOOL status;
  int typeMPS = MPSFIXED;
  int argc, i;
  char **argv, bas = FALSE;

  setarg(options, &argc, &argv);

  lp0 = lp;

  init_lpsolve(lp);

  for(i = 0; i < argc; i++)
    if ((strcmp(argv[i], "-h") == 0) || (strcmp(argv[i], "-help") == 0) || (strcmp(argv[i], "--help") == 0)) {
      lp->report(lp, NEUTRAL, "xli_MPS.xli_writemodel options:\n");
      lp->report(lp, NEUTRAL, "  -free: Generate free MPS format\n");
      lp->report(lp, NEUTRAL, "  -negobjconst: Negate objective function\n");
      lp->report(lp, NEUTRAL, "  -lindo: use LINDO format: semi-cont variables in different order\n");
      lp->report(lp, NEUTRAL, "  -fullprecision: Write numbers in full precision. Only when also -free is specified\n");
      lp->report(lp, NEUTRAL, "  -bas: Write basis file\n");
      return(FALSE);
    }
    else if (strcmp(argv[i], "-free") == 0)
      typeMPS = (typeMPS & ~MPSFIXED) | MPSFREE;
    else if (strcmp(argv[i], "-negobjconst") == 0)
      typeMPS |= MPSNEGOBJCONST;
    else if (strcmp(argv[i], "-lindo") == 0)
      typeMPS |= MPSLINDO;
    else if (strcmp(argv[i], "-fullprecision") == 0)
      typeMPS |= MPSFREEFULLPRECISION;
    else if (strcmp(argv[i], "-bas") == 0)
	  bas = TRUE;
	else {
      lp->report(lp, IMPORTANT, "xli_MPS.xli_writemodel: option %s unsupported.\n", argv[i]);
	  return(FALSE);
	}

  if (bas) {
    if (typeMPS & MPSNEGOBJCONST) {
	  lp->report(lp, IMPORTANT, "xli_MPS.xli_writemodel: option -negobjconst unsupported in combination with option -bas.\n");
	  return(FALSE);
	}
    if (typeMPS & MPSLINDO) {
	  lp->report(lp, IMPORTANT, "xli_MPS.xli_writemodel: option -lindo unsupported in combination with option -bas.\n");
	  return(FALSE);
	}
    if (typeMPS & MPSFREE) {
	  lp->report(lp, IMPORTANT, "xli_MPS.xli_writemodel: option -free unsupported in combination with option -bas.\n");
	  return(FALSE);
	}
    if (typeMPS & MPSFREEFULLPRECISION) {
	  lp->report(lp, IMPORTANT, "xli_MPS.xli_writemodel: option -fullprecision unsupported in combination with option -bas.\n");
	  return(FALSE);
	}
  }
  else if (results) {
    lp->report(lp, IMPORTANT, "xli_MPS.xli_writemodel: option results only supported with option -bas.\n");
	return(FALSE);
  }
  else if (typeMPS & MPSFIXED) {
    if (typeMPS & MPSFREEFULLPRECISION) {
	  lp->report(lp, IMPORTANT, "xli_MPS.xli_writemodel: option -fullprecision unsupported in fixed MPS format.\n");
	  return(FALSE);
	}
  }

  if (bas) {
    if (results)
      status = MPS_writeBAS(lp, typeMPS, filename);
    else {
      status = MPS_readBAS(lp, typeMPS, filename, NULL);

      /* Code basis */
      if(status) {
        lp->set_action(&lp->spx_action, ACTION_REBASE | ACTION_REINVERT | ACTION_RECOMPUTE);
        lp->basis_valid = TRUE;   /* Do not re-initialize basis on entering Solve */
        lp->var_basic[0] = FALSE; /* Set to signal that this is a non-default basis */
      }
    }
  }
  else
    status = MPS_writefile(lp, typeMPS, filename);

  return(status);
}
