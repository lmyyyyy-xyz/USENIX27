#include <stdio.h>
#include <stdlib.h>

#include "lp_lib.h"
#include "lp_network.h"

#ifdef FORTIFY
# include "lp_fortify.h"
#endif

#if (MAJORVERSION > 5) || (MAJORVERSION == 5 && MINORVERSION > 5) /* || (MAJORVERSION == 5 && MINORVERSION == 5 && RELEASE > 0) */
#  define get_nonzeros    lp->lpfunc->get_nonzeros
#  define get_constr_type lp->lpfunc->get_constr_type
#  define is_maxim        lp->lpfunc->is_maxim
#  define get_rh          lp->lpfunc->get_rh
#  define get_epsel       lp->lpfunc->get_epsel
#  define is_maxim        lp->lpfunc->is_maxim
#  define get_mat_byindex lp->lpfunc->get_mat_byindex
#else
#  define get_nonzeros    lp->get_nonzeros
#  define get_constr_type lp->get_constr_type
#  define get_rh          lp->get_rh
#  define get_epsel       lp->get_epsel
#  define is_maxim        lp->is_maxim
#  define get_mat_byindex lp->get_mat_byindex
#endif

STATIC int get_Dimacs_type(char *_Label)
{
  int Result = network_MaxGeoMatch;
  char strDimacs[255], *ptr;

  for (ptr = _Label; *ptr; ptr++)
    *ptr = toupper(*ptr);
  while (Result>network_Unknown) {
    strcpy(strDimacs, get_Dimacs_name(Result, FALSE));
    for (ptr = strDimacs; *ptr; ptr++)
      *ptr = toupper(*ptr);
    if (strcmp(_Label, strDimacs) == 0)
      break;
    Result--;
  }
  return( Result );
}

STATIC char *get_Dimacs_name(int nwtype, MYBOOL longname)
{
  static char *DimacsLongName[network_MaxGeoMatch+1] =
  {"(Unknown)", "Minimum cost flow", "Maximum flow", "Assignment",
   "Maximum weighted edge matching", "Maximum weighted geometric matching"};
  static char *DimacsShortName[network_MaxGeoMatch+1] =
  {"(?)", "MIN", "MAX", "ASN",
   "EDGE", "GEOM"};

  if(longname)
    return( DimacsLongName[nwtype] );
  else
    return( DimacsShortName[nwtype] );
}

int __WINAPI get_network_type(lprec *lp, int *rowset, int *sinkValue)
{
  int    nUnit, nZero, nEqual, nSourcePoM, nSourceMoP,
         i,i1,ii, nrows = lp->rows, ncols = lp->columns,
         Result = network_Unknown;
  MYBOOL ismaxim = is_maxim(lp);
  REAL   val1, val2,
         eps = get_epsel(lp);
  MATrec *mat = lp->matA;

  if((nrows == 0) || (ncols == 0) )
    return( Result );

  /* Check that the matrix columns are all of length 2 and sum to 0;
     (note that we should also permit a truncated network with a single column entry) */
  nZero = 0;
  for(i = 1; (i <= ncols) && (nZero == 0); i++) {
    i1 = mat->col_end[i-1];
    ii = mat->col_end[i];
    if(ii-i1 != 2)
      nZero++;
    else {
      val1 = get_mat_byindex(lp, i1, FALSE, TRUE);
      val2 = get_mat_byindex(lp, i1+1, FALSE, TRUE);
      if(fabs(val1+val2) > eps)
        nZero++;
    }
  }
  if(nZero != 0)
    return( Result );

  /* Check that the matrix contains all unit values */
  ii = get_nonzeros(lp);
  for(i = 0; i < ii; i++) {
    val1 = get_mat_byindex(lp, i, FALSE, TRUE);
    if(fabs(fabs(val1)-1) > eps)
      break;
  }
  if(i < ii)
    return( Result );

 /* Check that the constraints imply a transshipment model (all nodes EQ),
    or a transportation model (allowing LT for net supply/source nodes) */
  nUnit = 0;
  nZero = 0;
  nEqual = 0;
  nSourcePoM = 0;
  nSourceMoP = 0;
  for(i = 1; i <= nrows; i++) {
    val1 = get_rh(lp, i);
    my_roundzero(val1, eps);
    if(lp->orig_rhs[i] == 0)
      nZero++;
    else if(fabs(fabs(val1)-1) < eps)
      nUnit++;
    switch (get_constr_type(lp, i)) {
      case EQ: nEqual++;
               break;
      case LE: if(val1 > 0)
                 nSourceMoP++;  /* Coded -1 o +1 */
               break;
      case GE: if(val1 < 0)
                 nSourcePoM++;  /* Coded +1 o -1 */
               break;
    }
  }

  /* Find if we have a maximum flow model expressed as minimization */
  if(!ismaxim) {
    ii = 0;
    for(i = 1; i <= ncols; i++)
      if(lp->orig_obj[i]>0)
        break;
    ismaxim = (MYBOOL) (i > ncols);
  }

  /* Cannot have a blended network coding model */
  if(ismaxim && (nSourceMoP>0) && (nSourcePoM>0))
    Result = network_MaxFlow;
/*
  if(((nSourceMoP>0) && (nSourcePoM>0)) &&
     !(is_maxim(lp) && (nSourceMoP==1) && (nSourcePoM==1)))
    Result = network_Unknown;
*/
  /* Determine model */
  else if(nSourcePoM+nSourceMoP+nEqual < nrows)
    Result = network_Unknown;
  else if(nUnit == nrows)
    Result = network_Assignment;
/*
  else if(is_maxim(lp) && (nSourcePoM+nSourceMoP+nEqual == nrows) && (nZero == nEqual))
    Result = network_MaxFlow;
*/
  else
    Result = network_MinCost;
  /* Determine node-arc-node coding model */
  if(Result == network_Unknown)
    (*sinkValue) = 0;
  else if(Result == network_MaxFlow) {
    if(nSourceMoP>0)
      (*sinkValue) = +1;
    else
      (*sinkValue) = -1;
  }
  else if(nSourcePoM>0)
    (*sinkValue) = -1;
  else
    (*sinkValue) = +1;
  return( Result );
}

#if 0
int __WINAPI get_network_type(lprec *lp, int *rowset, int *sinkValue)
{
  int nUnit, nZero, nEqual, nSourcePoM, nSourceMoP,
      i,i1,ii, nrows = lp->rows,
      Result = network_Unknown;
  MATrec *mat = lp->matA;

  if((nrows == 0) || (lp->columns == 0) )
    return( Result );

  /* Check that the matrix columns are all of length 2 and sum to 0;
     (note that we should also permit a truncated network with a single column entry) */
  nZero = 0;
  for(i = 1; i <= lp->columns; i++) {
    i1 = mat->col_end[i-1];
    ii = mat->col_end[i];
    if((ii-i1 != 2) ||
       (COL_MAT_VALUE(i1) + COL_MAT_VALUE(i1+1) != 0)) {
      nZero++;
      break;
    }
  }
  if(nZero != 0)
    return( Result );

  /* Check that the matrix contains all unit values */
  ii = get_nonzeros(lp);
  for(i = 0; i < ii; i++)
    if(fabs(COL_MAT_VALUE(i)) != 1)
      break;
  if(i < ii)
    return( Result );

 /* Check that the constraints imply a transshipment model (all nodes EQ),
    or a transportation model (allowing LT for net supply/source nodes) */
  nUnit = 0;
  nZero = 0;
  nEqual = 0;
  nSourcePoM = 0;
  nSourceMoP = 0;
  for(i = 1; i <= nrows; i++) {
    if(lp->orig_rhs[i] == 0)
      nZero++;
    else if(fabs(lp->orig_rhs[i]) == 1)
      nUnit++;
    switch (get_constr_type(lp, i)) {
      case EQ: nEqual++;
               break;
      case LE: if(lp->orig_rhs[i] > 0) nSourceMoP++;  /* Coded -1 o +1 */
               break;
      case GE: if(lp->orig_rhs[i] < 0) nSourcePoM++;  /* Coded +1 o -1 */
               break;
    }
  }
  /* Cannot have a blended network coding model */
  if((nSourceMoP>0) && (nSourcePoM>0))
    Result = network_Unknown;
  /* Determine model */
  else if(nSourcePoM+nSourceMoP+nEqual < nrows)
    Result = network_Unknown;
  else if(nUnit == nrows)
    Result = network_Assignment;
  else if(is_maxim(lp) && (nEqual == nrows) && (nZero == nrows))
    Result = network_MaxFlow;
  else
    Result = network_MinCost;
  /* Determine node-arc-node coding model */
  if(Result == network_Unknown)
    (*sinkValue) = 0;
  else if(nSourcePoM>0)
    (*sinkValue) = -1;
  else
    (*sinkValue) = +1;
  return( Result );
}
#endif

