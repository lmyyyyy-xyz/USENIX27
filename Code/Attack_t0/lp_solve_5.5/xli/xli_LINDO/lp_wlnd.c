
#include <string.h>
#include "lp_lib.h"
#include "lp_scale.h"
#include "lp_utils.h"
#include "lp_report.h"
#include "lp_wlp.h"

#ifdef FORTIFY
# include "lp_fortify.h"
#endif


/* ------------------------------------------------------------------------- */
/* Input and output of lp format model files for lp_solve                    */
/* ------------------------------------------------------------------------- */

static void write_lpcomment(FILE *output, char *string, MYBOOL newlinebefore)
{
  fprintf(output, "%s! %s\n", (newlinebefore) ? "\n" : "", string);
}

static MYBOOL write_lprow(lprec *lp, int rowno, FILE *output)
{
  int     i, ie, j;
  REAL    a;
  MATrec  *mat = lp->matA;
  MYBOOL  rowwritten;

  if(rowno == 0) {
    i = 1;
    ie = lp->columns+1;
  }
  else {
    i = mat->row_end[rowno-1];
    ie = mat->row_end[rowno];
  }
  rowwritten = FALSE;
  for(; i < ie; i++) {
    if(rowno == 0) {
      j = i;
      a = get_mat(lp, 0, i);
      if(a == 0)
        continue;
    }
    else {
      j = ROW_MAT_COLNR(i);
      a = ROW_MAT_VALUE(i);
      a = my_chsign(is_chsign(lp, rowno), a);
      a = unscaled_mat(lp, a, rowno, j);
    }
    if(is_splitvar(lp, j))
      continue;
if(rowwritten)
  fprintf(output, "\n");
    if(a == -1)
      fprintf(output, " -");
    else if(a == 1)
      fprintf(output, " +");
    else
      fprintf(output, " %+.16g ", (double)a);
    fprintf(output, "%s", get_col_name(lp, j));
    rowwritten = TRUE;
  }
  return(rowwritten);
}

MYBOOL __EXPORT_TYPE __WINAPI write_lnd(lprec *lp, char *filename)
{
  int    i, j, Ncolumns, Nrows;
  MYBOOL ok = FALSE, ok2;
  REAL   constant_term;
  FILE   *output = stdout;
  char   *ptr;

#ifdef Paranoia
  if(lp->matA->is_roworder) {
    report(lp, IMPORTANT, "write_lnd: Cannot write to LP file while in row entry mode.\n");
    return(FALSE);
  }
#endif
  if(!mat_validate(lp->matA)) {
    report(lp, IMPORTANT, "write_lnd: Could not validate the data matrix.\n");
    return(FALSE);
  }

  Ncolumns = get_Ncolumns(lp);
  Nrows = get_Nrows(lp);

  for(i = 1; i <= Ncolumns; i++)
    if(!is_splitvar(lp, i)) {
      if(is_semicont(lp, i)) {
        report(lp, IMPORTANT, "Model contains semi-continious variables. Unable to generate a LINDO model.");
        return(FALSE);
      }
      if(is_SOS_var(lp, i)) {
        report(lp, IMPORTANT, "Model contains SOS variables. Unable to generate a LINDO model.");
        return(FALSE);
      }
    }

  ok = (MYBOOL) ((filename == NULL) || ((output = fopen(filename,"w")) != NULL));
  if(!ok)
    return(ok);
  if(filename == NULL && lp->outstream != NULL)
    output = lp->outstream;

  /* Write name of model */
  ptr = get_lp_name(lp);
  if((ptr != NULL) && (*ptr))
    fprintf(output, "TITLE %s\n\n", ptr);

  /* Write the objective function */
  write_lpcomment(output, "Objective function", FALSE);
  if(is_maxim(lp))
    fprintf(output, "MAXIMIZE\n");
  else
    fprintf(output, "MINIMIZE\n");

  if((!write_lprow(lp, 0, output)) && (Ncolumns >= 1))
    fprintf(output, " 0 %s", get_col_name(lp, 1));


  constant_term = get_rh(lp, 0);
  if(constant_term)
    fprintf(output, " +constant_term");
  fprintf(output, "\n");

  /* Write constraints */
  if(lp->rows > 0) {
    write_lpcomment(output, "Constraints", TRUE);
    fprintf(output, "SUBJECT TO\n");
  }
  for(j = 1; j <= lp->rows; j++) {
    if(lp->names_used && (lp->row_name[j] != NULL))
      ptr = get_row_name(lp, j);
    else
      ptr = NULL;
    if((ptr != NULL) && (*ptr))
      fprintf(output, " %s)", ptr);

    if((!write_lprow(lp, j, output)) && (Ncolumns >= 1))
      /* fprintf(output, " 0 %s", get_col_name(lp, 1)) */;

    if((lp->orig_upbo[j]) && (lp->orig_upbo[j] < lp->infinite))
      fprintf(output, " %sUBND%d", (is_chsign(lp, j)) ? "-" : "+", j);
    if((lp->orig_upbo[j] == 0) || ((lp->orig_upbo[j]) && (lp->orig_upbo[j] < lp->infinite)))
      fprintf(output, " =");
    else if(is_chsign(lp, j))
      fprintf(output, " >=");
    else
      fprintf(output, " <=");
/*
    if(fabs(get_rh(lp, j) + lp->infinite) < 1)
      fprintf(output, " -Inf;\n");
    else */
      fprintf(output, " %.16g\n", get_rh(lp, j));
  }

  fprintf(output, "\nEND\n");

  /* Write bounds on variables */
  ok2 = FALSE;
  if(constant_term) {
    write_lpcomment(output, "Variable bounds", TRUE);
    fprintf(output, "SLB constant_term %.16g\n", constant_term);
    fprintf(output, "SUB constant_term %.16g\n", constant_term);
    ok2 = TRUE;
  }
  for(i = lp->rows + 1; i <= lp->sum; i++)
    if(!is_splitvar(lp, i - lp->rows)) {
      if(lp->orig_lowbo[i] == lp->orig_upbo[i]) {
	if(!ok2) {
	  write_lpcomment(output, "Variable bounds", TRUE);
	  ok2 = TRUE;
	}
        fprintf(output, "SUB %s %.16g\n", get_col_name(lp, i - lp->rows), get_upbo(lp, i - lp->rows));
      }
      else {
	if(lp->orig_lowbo[i] != 0) {
	  if(!ok2) {
	    write_lpcomment(output, "Variable bounds", TRUE);
	    ok2 = TRUE;
	  }
	  if(lp->orig_lowbo[i] == -lp->infinite)
	    fprintf(output, "FREE %s\n", get_col_name(lp, i - lp->rows));
	  else
	    fprintf(output, "SLB %s %.16g\n", get_col_name(lp, i - lp->rows),
		    (double)lp->orig_lowbo[i] * (lp->scaling_used && (lp->orig_lowbo[i] != -lp->infinite) ? lp->scalars[i] : 1.0));
	}
	if(lp->orig_upbo[i] != lp->infinite) {
	  if(!ok2) {
	    write_lpcomment(output, "Variable bounds", TRUE);
	    ok2 = TRUE;
	  }
	  fprintf(output, "SUB %s %.16g\n", get_col_name(lp, i - lp->rows),
		  (double)lp->orig_upbo[i] * (lp->scaling_used ? lp->scalars[i] : 1.0));
	}
      }
    }

  /* Write the ranged part of the constraint, if specified */
  for(j = 1; j <= lp->rows; j++) {
    if ((lp->orig_upbo[j]) && (lp->orig_upbo[j] < lp->infinite)) {
      if(!ok2) {
	write_lpcomment(output, "Variable bounds", TRUE);
	ok2 = TRUE;
      }
      fprintf(output, "SUB UBND%d %g\n",
	              j,
                      (lp->orig_upbo[j] /* -lp->orig_rhs[j] */) / (lp->scaling_used ? lp->scalars[j] : 1.0));
    }
  }

  /* Write optional integer section */
  if(lp->int_vars > 0) {
    write_lpcomment(output, "Integer definitions", TRUE);
    for(i = 1; i <= lp->columns; i++)
      if((!is_splitvar(lp, i)) && (is_int(lp, i)))
	fprintf(output, "GIN %s\n", get_col_name(lp, i));
  }

  ok = TRUE;

  if(filename != NULL)
    fclose(output);
  return(ok);
}

MYBOOL __WINAPI write_LND(lprec *lp, FILE *output)
{
  set_outputstream(lp, output);
  return(write_lnd(lp, NULL));
}
