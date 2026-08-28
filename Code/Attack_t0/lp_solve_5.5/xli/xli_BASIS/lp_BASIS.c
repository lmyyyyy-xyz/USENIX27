
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

/* Include routines common to language interface implementations */
#include "lp_XLI1.c"

#if defined _MSC_VER
# define vsnprintf _vsnprintf
#endif

/* Various reporting functions for lp_solve                                  */
/* ------------------------------------------------------------------------- */

int SOS_count(lprec *lp)
{
  return( 0 );
}

MYBOOL is_splitvar(lprec *lp, int column)
{
   return(FALSE);
}

REAL unscaled_value(lprec *lp, REAL value, int index)
{
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
  return( "XLI_BASIS v1.0" );
}

MYBOOL XLI_CALLMODEL xli_readmodel(lprec *lp, char *model, char *data, char *options, int verbose)
{
  return(FALSE);
}

MYBOOL XLI_CALLMODEL xli_writemodel(lprec *lp, char *filename, char *options, MYBOOL results)
{
  MYBOOL status = TRUE;

  init_lpsolve(lp);

  if (results)
    status = MPS_writeBAS(lp, ((options == NULL) || (strstr(options, "free") == NULL)) ? MPSFIXED : MPSFREE, filename);
  else {
    status = MPS_readBAS(lp, ((options == NULL) || (strstr(options, "free") == NULL)) ? MPSFIXED : MPSFREE, filename, NULL);

    /* Code basis */
    if(status) {
      lp->set_action(&lp->spx_action, ACTION_REBASE | ACTION_REINVERT | ACTION_RECOMPUTE);
      lp->basis_valid = TRUE;   /* Do not re-initialize basis on entering Solve */
      lp->var_basic[0] = FALSE; /* Set to signal that this is a non-default basis */
    }
  }

  return(status);
}
