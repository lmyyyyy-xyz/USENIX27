
/* Routines located in lp_XLI1.c; common for all language engines                     */
/* Cfr. lp_XLI.h for definitions                                                      */
/* ---------------------------------------------------------------------------------- */
/* Changes:                                                                           */
/* 13 June 2004      Initial version - KE                                             */
/* 20 April 2005     Added test for compatibility of compiled REAL size - KE          */
/* ---------------------------------------------------------------------------------- */

/* DON'T MODIFY */
MYBOOL XLI_CALLMODEL xli_compatible(lprec *lp, int xliversion, int lpversion, int sizevar)
{
  MYBOOL status = FALSE;
  
  if((lp != NULL) && (xliversion == XLIVERSION) && (sizeof(REAL) == sizevar)) {
#if 0  
    if(lpversion == MAJORVERSION)  /* Forces XLI renewal at lp_solve major version changes */
#endif
      status = TRUE;
  }
  return( status );
}

