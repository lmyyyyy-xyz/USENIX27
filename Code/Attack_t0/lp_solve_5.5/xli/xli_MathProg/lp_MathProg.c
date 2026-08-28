
/*  Modularized external language interface module - w/interface for lp_solve v5.0+
    This module is the implementation of the Ampl subset language named GNU MathProg.
   ----------------------------------------------------------------------------------
    Author:        Kjell Eikland
    Contact:       kjell.eikland@broadpark.no
    License terms: LGPL.

    Template used: lp_XLI2.c
    Requires:      lp_lib.h

    Release notes:
    v1.0.0  15 June 2004        First implementation.
    v1.0.1   9 July 2004        Added print hook routines to print via lp_solve
                                report routine
    v1.0.2   1 June 2010        Updated to MathProg from GLPK v4.41

   ---------------------------------------------------------------------------------- */

/* Generic include libraries */
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "lp_lib.h"
#include "commonlib.h"

/* Include libraries for this language system */
#include <math.h>
#include "glpapi.h"
#include "glplib.h"
#include "glpmpl.h"
#include "glpdmp.h"

#ifdef FORTIFY
# include "lp_fortify.h"
#endif

#define my_malloc malloc
#define MEMFREE free

/* Include routines common to language interface implementations */
#include "lp_XLI1.c"

/* CAN MODIFY */
char * XLI_CALLMODEL xli_name(void)
{
  return( "XLI_MathProg v4.41" );
}

static int _MathProg_hook_fn(lprec *lp, const char *msg, int verbose)
{
  char *str;

  if ((str = (char *) my_malloc(strlen(msg) + 1 + 1)) != NULL) {
    sprintf(str, "%s\n", msg);
    lp->report(lp, verbose, str);
    MEMFREE(str);
    return(TRUE);
  }
  return(FALSE);
}

static int _MathProg_print_hook_fn(void *lp, const char *msg)
{
  return(_MathProg_hook_fn((lprec *)lp, msg, NORMAL));
}

static int _MathProg_fault_hook_fn(void *lp, char *msg)
{
  return(_MathProg_hook_fn((lprec *)lp, msg, IMPORTANT));
}

void insist(int expression)
{
  assert(expression);
}


/* CAN MODIFY */
MYBOOL XLI_CALLMODEL xli_readmodel(lprec *lp, char *model, char *data, char *options, int verbose)
{
  MPL     *mpl;
  int     ret, m, n, i, ii, j, *ndx, len, kind, type;
  double  lb, ub, *val;
  char    *output = NULL;
  MYBOOL  status = FALSE;

  /* create and initialize the translator database */
  mpl = mpl_initialize();

  /* set hook for print function */
/*  lib_set_fault_hook((void *)lp, &_MathProg_fault_hook_fn);
  lib_set_print_hook((void *)lp, &_MathProg_print_hook_fn);*/
  //lib_fault_hook((void *)lp, &_MathProg_fault_hook_fn);
  //lib_fault_hook(&_MathProg_fault_hook_fn, (void *)lp); /* (obsolete) */
  //lib_print_hook((void *)lp, &_MathProg_print_hook_fn);
  //lib_print_hook(&_MathProg_print_hook_fn, (void *)lp);
  //lib_term_hook(&_MathProg_print_hook_fn, (void *)lp);
  glp_term_hook(&_MathProg_print_hook_fn, (void *)lp);

  /* read model section and optional data section */
  ret = mpl_read_model(mpl, model, data != NULL);
  if (ret == 4) goto done;
  insist(ret == 1 || ret == 2);
  //assert(NULL);

  /* read data section, if necessary */
  if (data != NULL) {
    insist(ret == 1);
    ret = mpl_read_data(mpl, data);
    if (ret == 4) goto done;
    insist(ret == 2);
  }

  /* generate model */
  ret = mpl_generate(mpl, output);
  if (ret == 4) goto done;
  insist(ret == 3);

  /* set problem name and temporary row storage order */
  lp->set_lp_name(lp, mpl_get_prob_name(mpl));
  lp->set_add_rowmode(lp, TRUE);

  /* build columns (variables) */
  n = mpl_get_num_cols(mpl);
  for (j = 1; j <= n; j++) {

    /* set column name */
    lp->set_col_name(lp, j, mpl_get_col_name(mpl, j));

    /* set column kind */
    kind = mpl_get_col_kind(mpl, j);
    switch (kind) {
      case MPL_NUM: break;
      case MPL_INT:
      case MPL_BIN: lp->set_int(lp, j, TRUE);
                    break;
      default:      insist(kind != kind);
    }

    /* set column bounds */
    type = mpl_get_col_bnds(mpl, j, &lb, &ub);
    switch (type) {
      case MPL_FR: break;
      case MPL_LO: break;
      case MPL_UP: break;
      case MPL_DB: break;
      case MPL_FX: break;
      default:     insist(type != type);
    }
    if (kind == MPL_BIN) {
      if (type == MPL_FR || type == MPL_UP || lb < 0.0) lb = 0.0;
      if (type == MPL_FR || type == MPL_LO || ub > 1.0) ub = 1.0;
      type = MPL_DB;
    }
    if (type == MPL_DB && fabs(lb - ub) < 1e-9 * (1.0 + fabs(lb))) {
      type = MPL_FX;
      if (fabs(lb) <= fabs(ub)) ub = lb; else lb = ub;
    }
    if(type == MPL_FR)
      lp->set_unbounded(lp, j);
    else if(type == MPL_UP) {
      lp->set_unbounded(lp, j);
      lp->set_upbo(lp, j, ub);
    }
    else if(type == MPL_LO)
      lp->set_lowbo(lp, j, lb);
    else {
      lp->set_upbo(lp, j, ub);
      lp->set_lowbo(lp, j, lb);
    }
  }

  /* allocate working arrays */
  ndx = (int *) my_malloc((1+n) * sizeof(*ndx));
  val = (double *) my_malloc((1+n) * sizeof(*val));

  /* build objective function (the first objective is used) */
  m = mpl_get_num_rows(mpl);
  for (i = 1; i <= m; i++) {

    kind = mpl_get_row_kind(mpl, i);
    if (kind == MPL_MIN || kind == MPL_MAX) {

      /* set optimization direction */
      lp->set_sense(lp, (MYBOOL) (kind == MPL_MAX) );

      /* set objective coefficients */
      len = mpl_get_mat_row(mpl, i, ndx, val);
      lp->set_obj_fnex(lp, len, val+1, ndx+1);

      /* set constant term */
      lp->set_rh(lp, 0, mpl_get_row_c0(mpl, i));

      /* set objective name */
      lp->set_row_name(lp, 0, mpl_get_row_name(mpl, i));

      break;
    }
  }

  /* build rows (constraints) */
  ii = 0;
  for (i = 1; i <= m; i++) {

    /* select constraint rows only */
    kind = mpl_get_row_kind(mpl, i);
    if (kind == MPL_MIN || kind == MPL_MAX)
      continue;

    /* set row bounds */
    type = mpl_get_row_bnds(mpl, i, &lb, &ub);
    switch (type) {
      case MPL_FR: break;
      case MPL_LO: break;
      case MPL_UP: break;
      case MPL_DB: break;
      case MPL_FX: break;
      default:     insist(type != type);
    }
    if(type == MPL_FR)
      continue;
    if (type == MPL_DB && fabs(lb - ub) < 1e-9 * (1.0 + fabs(lb))) {
      type = MPL_FX;
      if (fabs(lb) <= fabs(ub))
        ub = lb;
      else
        lb = ub;
    }
    if(type == MPL_UP || type == MPL_DB) {
      if(type == MPL_DB)
        lb = ub-lb;
      else
        lb = -1;
      type = ROWTYPE_LE;
    }
    else if(type == MPL_LO) {
      ub = lb;
      lb = -1;
      type = ROWTYPE_GE;
    }
    else if(type == MPL_FX) {
      lb = -1;
      type = ROWTYPE_EQ;
    }

    /* adjust for non-zero constant term in the constraint */
    ub -= mpl_get_row_c0(mpl, i);

    /* set constraint coefficients */
    len = mpl_get_mat_row(mpl, i, ndx, val);
    lp->add_constraintex(lp, len, val+1, ndx+1, type, ub);
    ii++;
    if(lb > 0)
      lp->set_rh_range(lp, ii, lb);

    /* set constraint name */
    lp->set_row_name(lp, ii, mpl_get_row_name(mpl, i));

  }

  /* set status and free working arrays */
  status = TRUE;
  MEMFREE(ndx);
  MEMFREE(val);

  /* free resources used by the model translator */
done:
/*  lib_set_fault_hook((void *)lp, NULL);
  lib_set_print_hook((void *)lp, NULL); */
  //lib_fault_hook((void *)lp, NULL);
  //lib_print_hook((void *)lp, NULL);
  //lib_term_hook(NULL, (void *) lp);
  glp_term_hook(NULL, (void *) lp);

  mpl_terminate(mpl);

  /* finally transpose the model A matrix */
  lp->set_add_rowmode(lp, FALSE);

  return( status );
}

/* ------------------------------------------------------------------------- */
/*  Write model in MathProg format                                           */
/* ------------------------------------------------------------------------- */

#define is_int          lp->is_int
#define get_lowbo       lp->get_lowbo
#define get_upbo        lp->get_upbo
#define get_col_name    lp->get_col_name
#define get_Ncolumns    lp->get_Ncolumns
#define get_row_name    lp->get_row_name
#define get_rh          lp->get_rh
#define is_maxim        lp->is_maxim
#define get_lp_name     lp->get_lp_name
#define get_rowex       lp->get_rowex
#define get_rh_range    lp->get_rh_range
#define get_constr_type lp->get_constr_type
#define get_infinite    lp->get_infinite
#define get_Nrows       lp->get_Nrows
#define report          lp->report

#define is_splitvar(lp, column) FALSE

static void write_lpcomment(FILE *output, char *string, MYBOOL newlinebefore)
{
  fprintf(output, "%s/* %s */\n", (newlinebefore) ? "\n" : "", string);
}

static MYBOOL write_lprow(lprec *lp, int rowno, FILE *output)
{
  int     i, ie, j, Ncolumns, *colno = NULL;
  REAL    a, *row = NULL;
  MYBOOL  first = TRUE;

  Ncolumns = get_Ncolumns(lp);
  if(Ncolumns) {
    colno = (int *) my_malloc(Ncolumns * sizeof(*colno));
    row = (REAL *) my_malloc(Ncolumns * sizeof(*row));
  }
  if((colno == NULL) || (row == NULL)) {
    MEMFREE(colno);
    MEMFREE(row);
    return(FALSE);
  }
  ie = get_rowex(lp, rowno, row, colno);
  for(i = 0; i < ie; i++) {
    a = row[i];
    if(a == 0)
      continue;
    j = colno[i];
    if(is_splitvar(lp, j))
      continue;
    if(!first)
      fputc(' ', output);
    else
      first = FALSE;
    if(a == -1)
      fprintf(output, "-");
    else if(a == 1)
      fprintf(output, "+");
    else
      fprintf(output, "%+.12g*", (double)a);
    fprintf(output, "%s", get_col_name(lp, j));
  }

  MEMFREE(row);
  MEMFREE(colno);

  return((MYBOOL) (ie > 0));

}

/* CAN MODIFY */
MYBOOL XLI_CALLMODEL xli_writemodel(lprec *lp, char *filename, char *options, MYBOOL results)
{
  int    i, j, Ncolumns, Nrows, constr_type;
  REAL   constant_term, lowbo, upbo, rh, rh_range, infinite;
  char   *ptr;
  FILE   *output = stdout;
  MYBOOL ok = FALSE;

  if(lp->sc_vars > 0) {
    report(lp, IMPORTANT, "Cannot generate MathProg model - Model has semi-continuous variables.");
    return( ok );
  }
  if(lp->SOS != NULL) {
    report(lp, IMPORTANT, "Cannot generate MathProg model - Model contains SOS.");
    return( ok );
  }

  ok = (MYBOOL) ((filename == NULL) || ((output = fopen(filename,"w")) != NULL));
  if(!ok)
    return( ok );
  if((filename == NULL) && (lp->outstream != NULL))
    output = lp->outstream;

  /* Write name of model */
  ptr = get_lp_name(lp);
  if((ptr != NULL) && (*ptr))
    write_lpcomment(output, ptr, ok = FALSE);

  constant_term = get_rh(lp, 0);

  infinite = get_infinite(lp);
  Ncolumns = get_Ncolumns(lp);
  Nrows = get_Nrows(lp);

  /* Write variables of model */
  write_lpcomment(output, "Variable definitions", (MYBOOL) !ok);
  for(i = 1; i <= Ncolumns; i++)
    if(!is_splitvar(lp, i)) {
      ptr = get_col_name(lp, i);
      lowbo = get_lowbo(lp, i);
      upbo = get_upbo(lp, i);
      fprintf(output, "var %s", ptr);
      if((i != 0) && (is_int(lp, i)))
        fprintf(output, " integer");
      if(lowbo == upbo)
        fprintf(output, " = %.12g", lowbo);
      else {
        if(lowbo != -infinite)
          fprintf(output, " >= %.12g", lowbo);
        if(upbo != infinite)
          fprintf(output, " <= %.12g", upbo);
      }
      fprintf(output, ";\n");
    }
  fprintf(output, "\n");

  /* Write the objective function */
  write_lpcomment(output, "Objective function", (MYBOOL) !ok);
  if(is_maxim(lp))
    fprintf(output, "maximize obj: ");
  else
    fprintf(output, "minimize obj: ");

  write_lprow(lp, 0, output);
  if(constant_term)
    fprintf(output, " +%.12g", constant_term);
  fprintf(output, ";\n");

  /* Write constraints */
  if(Nrows > 0) {
    write_lpcomment(output, "Constraints", TRUE);
  }
  for(j = 1; j <= Nrows; j++) {
    ptr = get_row_name(lp, j);
    if((ptr != NULL) && (*ptr))
      fprintf(output, "%s: ", ptr);

    /* Write the ranged part of the constraint, if specified */
    rh = get_rh(lp, j);
    constr_type = get_constr_type(lp, j);
    if(constr_type == EQ)
      rh_range = 0;
    else
      rh_range = get_rh_range(lp, j);
    if ((rh_range) && (rh_range < infinite))
      fprintf(output, "%+.12g %s ",
              rh + ((constr_type == LE) ? -rh_range : rh_range),
              (constr_type == LE) ? "<=" : ">=");

    if((!write_lprow(lp, j, output)) && (Ncolumns >= 1))
      fprintf(output, "0*%s", get_col_name(lp, 1));

    if(constr_type == EQ)
      fprintf(output, " =");
    else if(constr_type == GE)
      fprintf(output, " >=");
    else
      fprintf(output, " <=");
    fprintf(output, " %.12g;\n", rh);
  }

  ok = TRUE;

  if(filename != NULL)
    fclose(output);
  return( ok );
}

