
#include <string.h>
#include "lp_lib.h"
#include "lp_scale.h"
#include "lp_utils.h"
#include "lp_report.h"
#include "lp_wlp.h"

#ifdef FORTIFY
# include "lp_fortify.h"
#endif

#define MAXLEN 255

/* ------------------------------------------------------------------------- */
/* Input and output of lp format model files for lp_solve                    */
/* ------------------------------------------------------------------------- */

static void write_lpcomment(FILE *output, char *string, MYBOOL newlinebefore)
{
  fprintf(output, "%s\\* %s *\\\n", (newlinebefore) ? "\n" : "", string);
}

static void write_line(FILE *output, int *len, char *buf)
{
  int l;

  l = strlen(buf);
  if (*len + l > MAXLEN) {
    fprintf(output, "\n");
    *len = 0;
  }
  if (*buf != ' ')
    *len += fprintf(output, " ");
  *len += fprintf(output, "%s", buf);
}

static MYBOOL write_lprow(lprec *lp, int rowno, FILE *output, int *len)
{
  int     i, ie, j;
  REAL    a;
  MATrec  *mat = lp->matA;
  MYBOOL  rowwritten;
  char buf[256];

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
    if(a == -1)
      strcpy(buf, " -");
    else if(a == 1)
      strcpy(buf, " +");
    else
      sprintf(buf, " %+.12g ", (double)a);
    strcat(buf, get_col_name(lp, j));
    write_line(output, len, buf);
    rowwritten = TRUE;
  }
  return(rowwritten);
}

MYBOOL __EXPORT_TYPE __WINAPI write_lpt(lprec *lp, char *filename, char objconst)
{
  int    i, j, b, len;
  MYBOOL ok = FALSE, ok2;
  REAL   a, objconst_term;
  FILE   *output = stdout;
  char   *ptr, buf[256];

#ifdef Paranoia
  if(lp->matA->is_roworder) {
    report(lp, IMPORTANT, "write_lpt: Cannot write to LP file while in row entry mode.\n");
    return(FALSE);
  }
#endif
  if(!mat_validate(lp->matA)) {
    report(lp, IMPORTANT, "write_lpt: Could not validate the data matrix.\n");
    return(FALSE);
  }

  ok = (MYBOOL) ((filename == NULL) || ((output = fopen(filename,"w")) != NULL));
  if(!ok)
    return(ok);
  if(filename == NULL && lp->outstream != NULL)
    output = lp->outstream;

  /* Write name of model */
  ptr = get_lp_name(lp);
  if(ptr != NULL)
    if(*ptr)
      write_lpcomment(output, ptr, FALSE);
    else
      ptr = NULL;

  /* Write the objective function */
  write_lpcomment(output, "Objective function", (MYBOOL) (ptr != NULL));
  if(is_maxim(lp))
    fprintf(output, "Maximize\n");
  else
    fprintf(output, "Minimize\n");

  len = 0;
  if(lp->names_used && (lp->row_name[0] != NULL))
    ptr = get_row_name(lp, 0);
  else
    ptr = NULL;
  if((ptr != NULL) && (*ptr))
    len += fprintf(output, " %s:", ptr);
  objconst_term = get_rh(lp, 0);
  if(objconst_term) {
    if(objconst) {
      sprintf(buf, " %+.12g", objconst_term);
      objconst_term = 0;
    }
    else
      strcpy(buf, " +objconst_term");
    write_line(output, &len, buf);
  }
  if((!write_lprow(lp, 0, output, &len)) && (get_Ncolumns(lp) >= 1))
    /* len += fprintf(output, " 0 %s", get_col_name(lp, 1)) */;
  fprintf(output, "\n");

  /* Write constraints */
  if(lp->rows > 0) {
    write_lpcomment(output, "Constraints", TRUE);
    fprintf(output, "Subject To\n");
  }
  for(j = 1; j <= lp->rows; j++) {
    len = 0;
    if(lp->names_used && (lp->row_name[j] != NULL))
      ptr = get_row_name(lp, j);
    else
      ptr = NULL;
    if((ptr != NULL) && (*ptr))
      len += fprintf(output, " %s:", ptr);

    if((!write_lprow(lp, j, output, &len)) && (get_Ncolumns(lp) >= 1))
      /* len += fprintf(output, " 0 %s", get_col_name(lp, 1)) */;

    if(lp->orig_upbo[j] == 0)
      write_line(output, &len, " =");
    else if(is_chsign(lp, j))
      write_line(output, &len, " >=");
    else
      write_line(output, &len, " <=");

    if(fabs(get_rh(lp, j) + lp->infinite) < 1)
      write_line(output, &len, " -Inf;\n");
    else {
      sprintf(buf, " %.12g", get_rh(lp, j));
      write_line(output, &len, buf);
      fprintf(output, "\n");
    }

    /* Write the ranged part of the constraint, if specified */
    if ((lp->orig_upbo[j]) && (lp->orig_upbo[j] < lp->infinite)) {
      len = 0;
      if((ptr != NULL) && (*ptr))
        len += fprintf(output, " %*s ", (int) strlen(ptr), "");
      if((!write_lprow(lp, j, output, &len)) && (get_Ncolumns(lp) >= 1))
        len += fprintf(output, " 0 %s", get_col_name(lp, 1));
      write_line(output, &len, (is_chsign(lp, j)) ? " <=" : " >=");
      sprintf(buf, " %g",
                   (lp->orig_upbo[j]-lp->orig_rhs[j]) * (is_chsign(lp, j) ? 1.0 : -1.0) / (lp->scaling_used ? lp->scalars[j] : 1.0));
      write_line(output, &len, buf);
      fprintf(output, "\n");
    }
  }

  /* Write optional SOS section */
  if(SOS_count(lp) > 0) {
    SOSgroup *SOS = lp->SOS;
    write_lpcomment(output, "SOS definitions", TRUE);
    for(b = 0, i = 0; i < SOS->sos_count; /* b = lp->sos_list[i]->priority, */ i++) {
      len = 0;
      len += fprintf(output, "%s:",
	             (SOS->sos_list[i]->name == NULL) || (*SOS->sos_list[i]->name==0) ? "SOS" : SOS->sos_list[i]->name);
      for(j = 1; j <= SOS->sos_list[i]->size; /* a = lp->sos_list[i]->weights[j], */ j++) {
	  sprintf(buf, "+%.12g %s",
                  SOS->sos_list[i]->weights[j],
		  get_col_name(lp, SOS->sos_list[i]->members[j]));
        write_line(output, &len, buf);
      }
      len += fprintf(output, " = S%d", SOS->sos_list[i]->type);
      fprintf(output, "\n");
    }
  }

  /* Write bounds on variables */
  ok2 = FALSE;
  if(objconst_term) {
    write_lpcomment(output, "Variable bounds", TRUE);
    fprintf(output, "Bounds\n");
    fprintf(output, " objconst_term = %.12g\n", objconst_term);
    ok2 = TRUE;
  }
  for(i = lp->rows + 1; i <= lp->sum; i++)
    if(!is_splitvar(lp, i - lp->rows)) {
      if(lp->orig_lowbo[i] == lp->orig_upbo[i]) {
	if(!ok2) {
	  write_lpcomment(output, "Variable bounds", TRUE);
	  fprintf(output, "Bounds\n");
	  ok2 = TRUE;
	}
        fprintf(output, " %s = %.12g\n", get_col_name(lp, i - lp->rows), get_upbo(lp, i - lp->rows));
      }
      else {
	if(lp->orig_lowbo[i] != 0) {
	  if(!ok2) {
	    write_lpcomment(output, "Variable bounds", TRUE);
	    fprintf(output, "Bounds\n");
	    ok2 = TRUE;
	  }
	  if(lp->orig_lowbo[i] == -lp->infinite)
	    fprintf(output, " %s >= -Inf\n", get_col_name(lp, i - lp->rows));
	  else
	    fprintf(output, " %s >= %.12g\n", get_col_name(lp, i - lp->rows),
		    (double)lp->orig_lowbo[i] * (lp->scaling_used && (lp->orig_lowbo[i] != -lp->infinite) ? lp->scalars[i] : 1.0));
	}
	if(lp->orig_upbo[i] != lp->infinite) {
	  if(!ok2) {
	    write_lpcomment(output, "Variable bounds", TRUE);
	    fprintf(output, "Bounds\n");
	    ok2 = TRUE;
	  }
	  fprintf(output, " %s <= %.12g\n", get_col_name(lp, i - lp->rows),
		  (double)lp->orig_upbo[i] * (lp->scaling_used ? lp->scalars[i] : 1.0));
	}
      }
    }

  /* Write optional integer section */
  if(lp->int_vars > 0) {
    write_lpcomment(output, "Integer definitions", TRUE);
    i = 1;
    while(i <= lp->columns && !is_int(lp, i))
      i++;
    if(i <= lp->columns) {
      fprintf(output, "Generals\n");
      len = 0;
      for(; i <= lp->columns; i++)
        if((!is_splitvar(lp, i)) && (is_int(lp, i))) {
  	  sprintf(buf, " %s", get_col_name(lp, i));
          write_line(output, &len, buf);
        }
      fprintf(output, "\n");
    }
  }

  /* Write optional SEC section */
  if(lp->sc_vars > 0) {
    write_lpcomment(output, "Semi-continuous variables", TRUE);
    i = 1;
    while(i <= lp->columns && !is_semicont(lp, i))
      i++;
    if(i <= lp->columns) {
      fprintf(output, "Semi-continuous\n");
      len = 0;
      for(; i <= lp->columns; i++)
        if((!is_splitvar(lp, i)) && (is_semicont(lp, i))) {
  	  sprintf(buf, " %s", get_col_name(lp, i));
          write_line(output, &len, buf);
        }
      fprintf(output, "\n");
    }
  }

  fprintf(output, "\nEnd\n");
  ok = TRUE;

  if(filename != NULL)
    fclose(output);
  return(ok);
}

MYBOOL __WINAPI write_LPT(lprec *lp, FILE *output, char objconst)
{
  set_outputstream(lp, output);
  return(write_lpt(lp, NULL, objconst));
}
