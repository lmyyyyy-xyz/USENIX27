
/*  Modularized simplex basis factorization module - w/interface for lp_solve v5.0+
   ----------------------------------------------------------------------------------
    Author:        Kjell Eikland
    Contact:       kjell.eikland@broadpark.no
    License terms: LGPL.

    Requires:      lp_lib.h   glplib.h      glplib1.c
                                            glplib2.c
                              glpluf.h      glpluf.c
                              glpinv.h      glpinv.c

    Release notes:
    v1.0    1 February 2003     First implementation of the GLPK interface.
    v1.0.1  23 May 2004         Moved mustrefact() function into the BFP structure.
    v1.0.2  5 November 2004     Modified call interface to obtain basis data columns.

   ---------------------------------------------------------------------------------- */


/* Generic include libraries */
#include <stdlib.h>
#include <string.h>

/* Include libraries for this factorization system */
#include "lp_lib.h"
#include "commonlib.h"
#include "lp_glpkLU.h"

/* Include routines common to factorization implementations */
#include "lp_BFP1.c"
#include "lp_BFP2.c"

#ifdef FORTIFY
# include "lp_fortify.h"
#endif


/* MUST MODIFY */
char * BFP_CALLMODEL bfp_name(void)
{
  return( "GLPKLU v4.13" );
}


/* MUST MODIFY */
MYBOOL BFP_CALLMODEL bfp_resize(lprec *lp, int newsize)
{
  INVrec *lu;

  lu = lp->invB;

  /* Increment dimensionality since we put the objective row at the top */
  newsize = newsize + bfp_rowoffset(lp);
  lu->dimalloc = newsize;

  /* Allocate index tracker arrays, LU matrices and various work vectors */
  if(!allocREAL(lp, &lu->value, newsize+BASE, AUTOMATIC))
    return( FALSE );

  /* Data specific to the factorization engine */
  if(lu->LU != NULL)
    glp_inv_delete(lu->LU);
  if(newsize > 0) {
    lu->LU = glp_inv_create(newsize, lp->bfp_pivotmax(lp));
#if 1
    lu->timed_refact = DEF_TIMEDREFACT;
#else
    lu->timed_refact = FALSE;
#endif
  }
  else
    lu->LU = NULL;
  lu->dimcount = newsize;

  return( TRUE );
}


/* MUST MODIFY */
void BFP_CALLMODEL bfp_free(lprec *lp)
{
  INVrec *lu;

  lu = lp->invB;
  if(lu == NULL)
    return;

  /* General arrays */
  FREE(lu->opts);
  FREE(lu->value);

  /* Data specific to the factorization engine */
  glp_inv_delete(lu->LU);

  FREE(lu);
  lp->invB = NULL;
}


/* MUST MODIFY */
int BFP_CALLMODEL bfp_nonzeros(lprec *lp, MYBOOL maximum)
{
  if(maximum == TRUE)
    return(lp->invB->max_LUsize);
  else if(maximum == AUTOMATIC)
    return(lp->invB->max_Bsize);
  else {
    int count;
    count = lp->invB->LU->luf->nnz_v + lp->invB->LU->luf->nnz_v;
    return(count);
  }
}


/* MUST MODIFY (or ignore) */
int BFP_CALLMODEL bfp_memallocated(lprec *lp)
{
  return(0);
}


/* MUST MODIFY */
int BFP_CALLMODEL bfp_preparefactorization(lprec *lp)
{
  INVrec *lu;

  lu = lp->invB;

  /* Finish any outstanding business */
  if(lu->is_dirty == AUTOMATIC)
    lp->bfp_finishfactorization(lp);

  /* Clear or resize the existing LU matrices - specific for the factorization engine */
  if(lu->dimcount != lp->rows + bfp_rowoffset(lp))
    lp->bfp_resize(lp, lp->rows);

  /* Reset additional indicators */
  lp->bfp_updaterefactstats(lp);
  lu->col_pos = 0;

  return(0);

}

/* Local wrapper to get basis column data */
static int GLPK_basic_column(void *_info, int j, int rn[], double bj[])
{
  return(((lprec *) _info)->get_basiscolumn(_info, j, rn, bj));
}

/* MUST MODIFY */
int BFP_CALLMODEL bfp_factorize(lprec *lp, int uservars, int Bsize, MYBOOL *usedpos, MYBOOL final)
{
  static double piv_tol[1+3] = { 0.00, 0.10, 0.30, 0.70 };
  int    n, i;
  int    singularities = 0;

 /* Update dimensions */
  lp->invB->max_Bsize = MAX(lp->invB->max_Bsize, Bsize+(1+lp->rows-uservars));

 /* Refactorize the entire basis matrix */
  for(n = 1; n <= 3; n++) {
    lp->invB->LU->luf->piv_tol = piv_tol[n];
    i = glp_inv_decomp(lp->invB->LU, lp, GLPK_basic_column);
    if(i == 0) break;
  }
  if(i == 0)
    lp->invB->user_colcount = uservars;
  else
    lp->report(lp, CRITICAL, "bfp_factorize: Could not refactorize basis (error code %d)\n", i);

  lp->invB->num_singular += singularities;    /* The total number of singular updates */
  return(singularities);
}


/* MUST MODIFY */
MYBOOL BFP_CALLMODEL bfp_finishupdate(lprec *lp, MYBOOL changesign)
/* Was addetacol() in versions of lp_solve before 4.0.1.8 - KE */
{
  int    i, status, deltarows = bfp_rowoffset(lp);
  INVrec *lu;

  lu = lp->invB;
  if(!lu->is_dirty)
    return( FALSE );

  /* Check if we can make use of prepared data */
#if 1
  if(!lu->ispreparedupdate)
#endif
  {
    lp->get_lpcolumn(lp, lu->col_enter, lu->value+deltarows, NULL, NULL);
    lu->value[0] = 0;
    glp_inv_ftran(lu->LU, lu->value, TRUE);
  }

  i = lu->col_pos+deltarows;
  status = glp_inv_update(lu->LU, i);
  lu->ispreparedupdate = FALSE;

  /* Update mapping arrays */
  if(lu->col_leave > lu->dimcount-deltarows)
    lu->user_colcount--;
  if(lu->col_enter > lu->dimcount-deltarows)
    lu->user_colcount++;
  lu->num_pivots++;
  lu->col_pos = 0;
  if(lu->is_dirty != AUTOMATIC)
    lu->is_dirty = FALSE;

  /* Check for update errors and do any corrective action */
  if(status != 0) {
    lu->num_singular++;    /* The total number of singular updates */
    /* Error codes are:

       1 - the adjacent basis matrix is structurally singular, since after
           changing the j-th column of the matrix V by the new column (see
           the algorithm below) the case k1 > k2 occured;
       2 - the factorization is inaccurate, since after transforming the
           k2-th row of the matrix U = P*V*Q, the diagonal element u[k2,k2]
           is zero or close to zero;
       3 - maximal number of updates has been reached;
       4 - overflow of the sparse vector area.

       In all cases, the remedial action is to refactorize/reinvert! */

    lp->invert(lp, INITSOL_USEZERO, FALSE);
  }
  return( TRUE );

} /* bfp_finishupdate */


void BFP_CALLMODEL bfp_ftran_local(lprec *lp, REAL *pcol, MYBOOL prepareupdate)
{
  int    n;
  INVrec *lu = lp->invB;

  if(!lu->LU->valid)
    lp->invert(lp, INITSOL_USEZERO, FALSE);

  n = lu->dimcount;
#ifdef SafeMemLU
  MEMCOPY(lu->value+bfp_rowoffset(lp), pcol, lu->dimcount);
  glp_inv_ftran(lu->LU, lu->value, prepareupdate);
  MEMCOPY(pcol, lu->value+bfp_rowoffset(lp), lu->dimcount);
#else
  glp_inv_ftran(lu->LU, (pcol-bfp_rowoffset(lp)), prepareupdate);
#endif
  lu->ispreparedupdate = prepareupdate;
}


void BFP_CALLMODEL bfp_ftran_normal(lprec *lp, REAL *pcol, int *nzidx)
{
  REAL   roundzero = lp->epsmachine;

  bfp_ftran_local(lp, pcol, FALSE);

  /* Transfer and round small values to zero */
  if(roundzero != 0) {
    int i, n, deltarows = bfp_rowoffset(lp);
    n = lp->invB->dimcount;
    for(i = 1; i <= n; i++)
      my_roundzero(pcol[i-deltarows], roundzero);
  }
}


void BFP_CALLMODEL bfp_ftran_prepare(lprec *lp, REAL *pcol, int *nzidx)
{
  bfp_ftran_local(lp, pcol, TRUE);
}


void BFP_CALLMODEL bfp_btran_normal(lprec *lp, REAL *row, int *nzidx)
{
  int    n;
  INVrec *lu = lp->invB;
  REAL   roundzero = lp->epsmachine;

  if(!lu->LU->valid)
    lp->invert(lp, INITSOL_USEZERO, FALSE);

  n = lu->dimcount;
#ifdef SafeMemLU
  MEMCOPY(lu->value+bfp_rowoffset(lp), row, lu->dimcount);
  glp_inv_btran(lu->LU, lu->value);
  MEMCOPY(row, lu->value+bfp_rowoffset(lp), lu->dimcount);
#else
  glp_inv_btran(lu->LU, (row-bfp_rowoffset(lp)));
#endif

  /* Round small values to zero */
  if(roundzero != 0) {
    int i, deltarows = bfp_rowoffset(lp);
    for(i = 1; i <= n; i++)
      my_roundzero(row[i-deltarows], roundzero);
  }
  lp->invB->ispreparedupdate = FALSE;

}

/* MUST MODIFY - Routine to find maximum rank of equality constraints */
int BFP_CALLMODEL bfp_findredundant(lprec *lp, int items, getcolumnex_func cb, int *maprow, int *mapcol)
{
  /* Are we capable of finding redundancy with this BFP? */
  if((maprow == NULL) && (mapcol == NULL))
    return( 0 );

  /* If so, process */
  return( 0 );
}
