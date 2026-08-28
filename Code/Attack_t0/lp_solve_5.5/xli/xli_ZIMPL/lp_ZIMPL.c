
/*  Modularized external language interface module - w/interface for lp_solve v5.0+
    This module is the implementation of the Ampl-inspired language ZIMPL.
   ----------------------------------------------------------------------------------
    Author:        Kjell Eikland
    Contact:       kjell.eikland@broadpark.no
    License terms: LGPL, separate licensing terms apply to actual ZIMPL and GMP code,
                   which must be resolved by the user.

    Template used: lp_XLI2.c
    Requires:      lp_lib.h

    Release notes:
    v1.0.0  25 October 2004     First implementation.
    v1.0.1  20 April 2005       Modified license text regarding underlying modules
    v1.0.2  02 April 2006       Updated to Zimpl v2.0.4
    v1.0.3  14 April 2007       Updated to Zimpl v2.0.5 and modularized model read
    v1.0.4  06 Nov   2007       Updated to Zimpl v2.0.6

   ---------------------------------------------------------------------------------- */

/* Generic include libraries */
#include <string.h>

/* Include libraries for this language system */
#include "lp_lib.h"
#include "commonlib.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <setjmp.h>

#include <gmp.h>

#include "lint.h"
#include "bool.h"
#include "mshell.h"
#include "ratlptypes.h"
#include "mme.h"
#include "xlpglue.h"
#include "gmpmisc.h"

#include "ratlp.h"
#include "ratlpstore.h"

#ifdef FORTIFY
# include "lp_fortify.h"
#endif


/* Include routines common to language interface implementations */
#include "lp_XLI1.c"

/* Other definitions and global variables */
typedef FILE* (_cdecl open_func)(const char*, const char*);
typedef int   (_cdecl close_func)(FILE*);

extern int     yydebug;
extern int     yy_flex_debug;

extern jmp_buf zpl_read_env;
extern Bool    is_longjmp_ok;

#if (MAJORVERSION > 5) || (MAJORVERSION == 5 && MINORVERSION > 5) || (MAJORVERSION == 5 && MINORVERSION == 5 && RELEASE > 0)
# define report           lp->lpfunc->report
# define set_lp_name      lp->lpfunc->set_lp_name
# define set_add_rowmode  lp->lpfunc->set_add_rowmode
# define set_sense        lp->lpfunc->set_sense
# define set_row_name     lp->lpfunc->set_row_name
# define set_col_name     lp->lpfunc->set_col_name
# define set_obj_fnex     lp->lpfunc->set_obj_fnex
# define add_constraintex lp->lpfunc->add_constraintex
# define set_rh_range     lp->lpfunc->set_rh_range
# define set_binary       lp->lpfunc->set_binary
# define set_int          lp->lpfunc->set_int
# define get_infinite     lp->lpfunc->get_infinite
# define set_bounds       lp->lpfunc->set_bounds
# define get_nameindex    lp->lpfunc->get_nameindex
# define add_SOS          lp->lpfunc->add_SOS
# define get_Nrows        lp->lpfunc->get_Nrows

# define is_maxim         lp->lpfunc->is_maxim
# define get_rowex        lp->lpfunc->get_rowex
# define get_col_name     lp->lpfunc->get_col_name
# define is_semicont      lp->lpfunc->is_semicont
# define get_lowbo        lp->lpfunc->get_lowbo
# define get_upbo         lp->lpfunc->get_upbo
# define get_rh           lp->lpfunc->get_rh
# define get_lp_name      lp->lpfunc->get_lp_name
# define get_row_name     lp->lpfunc->get_row_name
# define get_rh_range     lp->lpfunc->get_rh_range
# define is_SOS_var       lp->lpfunc->is_SOS_var
#if MAJORVERSION < 6
# define SOS_count        lp->lpfunc->SOS_count
# define is_splitvar      lp->lpfunc->is_splitvar
# define get_SOS          lp->lpfunc->get_SOS
#endif
# define get_constr_type  lp->lpfunc->get_constr_type
# define get_Ncolumns     lp->lpfunc->get_Ncolumns
# define is_int           lp->lpfunc->is_int
#else
# define MEMFREE          FREE
# define my_malloc        malloc
# define my_calloc        calloc
# define my_realloc       realloc
# define report           lp->report
# define set_lp_name      lp->set_lp_name
# define set_add_rowmode  lp->set_add_rowmode
# define set_sense        lp->set_sense
# define set_row_name     lp->set_row_name
# define set_col_name     lp->set_col_name
# define set_obj_fnex     lp->set_obj_fnex
# define add_constraintex lp->add_constraintex
# define set_rh_range     lp->set_rh_range
# define set_binary       lp->set_binary
# define set_int          lp->set_int
# define get_infinite     lp->get_infinite
# define set_bounds       lp->set_bounds
# define get_nameindex    lp->get_nameindex
# define add_SOS          lp->add_SOS
# define get_Nrows        lp->get_Nrows

# define is_maxim         lp->is_maxim
# define get_rowex        lp->get_rowex
# define get_col_name     lp->get_col_name
# define is_semicont      lp->is_semicont
# define get_lowbo        lp->get_lowbo
# define get_upbo         lp->get_upbo
# define get_rh           lp->get_rh
# define get_lp_name      lp->get_lp_name
# define get_row_name     lp->get_row_name
# define get_rh_range     lp->get_rh_range
# define is_splitvar(lp, column) FALSE
# define is_SOS_var       lp->is_SOS_var
# define get_constr_type  lp->get_constr_type
# define get_Ncolumns     lp->get_Ncolumns
# define is_int           lp->is_int

int SOS_count(lprec *lp)
{
  if(lp->SOS == NULL)
    return( 0 );
  else
    return( lp->SOS->sos_count );
}

static MYBOOL get_SOS(lprec *lp, int index, char *name, int *sostype, int *priority, int *count, int *sosvars, REAL *weights)
{
  SOSrec *SOS;

  if((index < 1) || (index > SOS_count(lp)))
    return( FALSE );
  SOS = lp->SOS->sos_list[index-1];
  if(name != NULL)
    strcpy(name, SOS->name);
  if(sostype != NULL)
    *sostype = SOS->type;
  if(priority != NULL)
    *priority = SOS->priority;
  if(count != NULL) {
    *count = SOS->size;
    if(sosvars != NULL) {
      int i;
      for(i = 1; i <= *count; i++) {
        sosvars[i-1] = SOS->members[i];
        if(weights != NULL)
          weights[i-1] = SOS->weights[i];
      }
    }
  }
  return( TRUE );
}


#endif

/* CAN MODIFY */
char * XLI_CALLMODEL xli_name(void)
{
  return( "XLI_ZIMPL v" VERSION );
}

static int _ZIMPL_hook_fn(lprec *lp, char *msg)
{
  char *str;

  if ((str = my_malloc(strlen(msg) + 1 + 1)) != NULL) {
    sprintf(str, "%s\n", msg);
    report(lp, NORMAL, str);
    MEMFREE(str);
    return(TRUE);
  }
  return(FALSE);
}

static int _ZIMPL_print_hook_fn(void *lp, char *msg)
{
  return(_ZIMPL_hook_fn((lprec *)lp, msg));
}

static int _ZIMPL_fault_hook_fn(void *lp, char *msg)
{
  return(_ZIMPL_hook_fn((lprec *)lp, msg));
}


/* Actual lpsolve writing function */
#ifndef LPF_NAME_LEN
#define LPF_NAME_LEN  64
#endif

/*
#define vclass class
*/

#define my_prog_load(prog, filename) prog_load(prog, NULL, filename)
#define my_xlp_alloc(model) xlp_alloc(model, FALSE)

static void lpsolve_write(Lps *ZIMPL, lprec *lp)
{
   const  Var* var;
   const  Con* con;
   const  Nzo* nzo;
   MYBOOL have_separate = FALSE;
   int    cnt;
   int    i, k, n, m;
   char*  name = my_malloc(LPF_NAME_LEN + 1);
   int   *ndx;
   REAL  *val, loB, upB;

   assert(ZIMPL    != NULL);
   assert(lp       != NULL);
   assert(name     != NULL);

   /* Allocate working arrays */
   n = ZIMPL->cons;
   m = ZIMPL->vars;
   ndx = my_malloc((1+m) * sizeof(*ndx));
   val = my_malloc((1+m) * sizeof(*val));

   /* Set problem name and temporary row storage order */
   set_lp_name(lp, ZIMPL->name);
   set_add_rowmode(lp, TRUE);

   /* Add the objective function */
   set_sense(lp, (MYBOOL) (ZIMPL->direct != LP_MIN));
   set_row_name(lp, 0, (ZIMPL->objname == NULL ? "Objective" : ZIMPL->objname));
   for(var = ZIMPL->var_root, cnt = 0; var != NULL; var = var->next)
   {
      /* Always create the variable, even if its coefficient is zero */
      lps_makename(name, LPF_NAME_LEN + 1, var->name, var->number);
      k = var->number + 1;
      set_col_name(lp, k, name);

      /* If coefficient is zero, do not include in objective function */
      if(!mpq_equal(var->cost, const_zero)) {
        ndx[cnt] = k;
        if(mpq_equal(var->cost, const_one))
           val[cnt] = 1;
        else if(mpq_equal(var->cost, const_minus_one))
           val[cnt] = -1;
        else
           val[cnt] = mpq_get_d(var->cost);
        cnt++;
      }
   }
   set_obj_fnex(lp, cnt, val, ndx);

   /* ---------------------------------------------------------------------- */

   /* First loop processes normal constraints,
      second loop processes lazy constraints, if any. */
   for(i = 0; i < 2; i++) {
      for(con = ZIMPL->con_root; con != NULL; con = con->next) {
         if (con->size == 0)
            continue;

         if ((con->flags & LP_FLAG_CON_SEPAR) == LP_FLAG_CON_SEPAR)
         {
            have_separate = TRUE;
            if (i == 0)
               continue;
         }
         else if (i == 1)
            continue;

         for(nzo = con->first, cnt = 0; nzo != NULL; nzo = nzo->con_next)
         {
           k = nzo->var->number + 1;
           ndx[cnt] = k;
           if(mpq_equal(nzo->value, const_one))
             val[cnt] = 1;
           else if (mpq_equal(nzo->value, const_minus_one))
             val[cnt] = -1;
           else
             val[cnt] = mpq_get_d(nzo->value);
           cnt++;
         }
         if(con->type == CON_RANGE) {
           add_constraintex(lp, cnt, val, ndx, GE, mpq_get_d(con->lhs));
           set_rh_range(lp, get_Nrows(lp), mpq_get_d(con->rhs)-mpq_get_d(con->lhs));
         }
         else if(con->type == CON_LHS)
           add_constraintex(lp, cnt, val, ndx, GE, mpq_get_d(con->lhs));
         else if(con->type == CON_RHS)
           add_constraintex(lp, cnt, val, ndx, LE, mpq_get_d(con->rhs));
         else
           add_constraintex(lp, cnt, val, ndx, EQ, mpq_get_d(con->rhs));

         lps_makename(name, LPF_NAME_LEN + 1, con->name, con->number);
         set_row_name(lp, get_Nrows(lp), name);

      }
      /* Shortcut to break out of the loop if there are no lazy constraints. */
      if (!have_separate)
         break;
   }

   /* ---------------------------------------------------------------------- */

   /* Set bounds and variable type. */
   for(var = ZIMPL->var_root; var != NULL; var = var->next) {
      /* A variable without any entries in the matrix or the objective
         function can be ignored. */
      if (var->size == 0 && mpq_equal(var->cost, const_zero))
         continue;

      k = var->number + 1;
      if(var->type == VAR_FIXED) {
        loB = mpq_get_d(var->lower);
        upB = loB;
      }
      else
      {
        /* Check if we have a binary or integer variable */
	switch(var->vclass) {
#if ((ZIMPL_MAJORVERSION > 2) || (ZIMPL_MAJORVERSION == 2 && ZIMPL_MINORVERSION > 05))
#else
	case VAR_BIN:
          set_binary(lp, k, TRUE);
	  break;
#endif
	case VAR_INT:
          set_int(lp, k, TRUE);
	  break;
	}

        if(var->type == VAR_LOWER || var->type == VAR_BOXED)
          loB = mpq_get_d(var->lower);
         else
          loB = -get_infinite(lp);

        if (var->type == VAR_UPPER || var->type == VAR_BOXED)
          upB = mpq_get_d(var->upper);
         else
          upB = get_infinite(lp);
      }
      set_bounds(lp, k, loB, upB);
   }

   /* Add SOS'es, if there are any (feature introduced in v2.0.4) */
   if(xlp_hassos()) {
     Sos* sos;
     Sse* sse;

     for(sos = ZIMPL->sos_root; sos != NULL; sos = sos->next) {
       k = 0;
       for (sse = sos->first; sse != NULL; sse = sse->next) {
         lps_makename(name, LPF_NAME_LEN + 1, sse->var->name, sse->var->number);
         ndx[k] = get_nameindex(lp, name, FALSE);
         val[k] = mpq_get_d(sse->weight);
         k++;
       }
       i = add_SOS(lp, sos->name, sos->type, sos->priority, k, ndx, val);
     }
   }

   /* Free working arrays */
   MEMFREE(name);
   MEMFREE(ndx);
   MEMFREE(val);

   /* Free resources used by the model translator */
/*  lib_set_fault_hook((void *)lp, NULL);
   lib_set_print_hook((void *)lp, NULL); */

   /* Finally transpose the model's A matrix */
   set_add_rowmode(lp, FALSE);

}


static MYBOOL is_valid_identifier(const char* s)
{
   assert(s != NULL);

   /* Identifiers start with a letter or a '_' */
   if (!isalpha(*s) || *s == '_')
      return FALSE;

   /* Then letters, digits or '_' can follow. */
   while(isalnum(*++s) || *s == '_')
      ;

   return (*s == '\0');
}

typedef struct _ZimplModel
{
   void       *host;
   Lps        *ZIMPL;
   Prog       *prog;
   Set        *set;
   int         param_count;
   char      **param_table;
   MYBOOL      presolve;
} ZimplModel;

MYBOOL XLI_CALLMODEL xli_getnative(ZimplModel *lp, char *model, char *data, char *options, int lpverbose)
{
   int         c, i;
   MYBOOL      status     = FALSE;
   unsigned long seed = 13021967UL;
   char       *file_name  = NULL, *argoptions = NULL;
   open_func  *openfile   = fopen;
   close_func *closefile  = fclose;

   is_longjmp_ok   = FALSE;

   verbose         = VERB_NORMAL;
   yydebug         = 0;
   yy_flex_debug   = 0;
   file_name       = my_calloc(1, DEF_STRBUFSIZE);

   lp->param_count = 0;
   lp->param_table = my_malloc(sizeof(*lp->param_table));

/* USAGE options
  -b             Enable Bison (Lex parser) debugging output.
  -D name=value  Sets the parameter name to the specified value.
                 This is equivalent with having this line in the ZIMPL program: param name:=val.
  -f             enable flex debugging output.
  -n cm|cn|cf    name column make/name/full
  -O             Try to reduce the generated LP by doing some presolve analysis.
  -s seed        Positive seed number for the random number generator.
  -v[0-5]        Set the verbosity level. 0 is quiet, 1 is default, 2 is verbose, 3 and 4 are chatter, and 5 is debug.
  -V             show version info
*/

   argoptions = options;
   if(argoptions == NULL)
     ;
   else
   {
     while((argoptions = strstr(argoptions, "-")) != NULL) {
       argoptions++;
       if (*argoptions == '\0')
         goto Quit;
       c = *(argoptions++);
       while(*argoptions == ' ')
         argoptions++;

       switch(c)
       {
         case 'b' :       /* Bison debugging output */
           yydebug = 1;
           break;
         case 'D' :       /* User-specified parameter definitions */
           lp->param_table = my_realloc(lp->param_table, (lp->param_count + 1) * sizeof(*lp->param_table));
           lp->param_table[lp->param_count] = strdup(argoptions);
           lp->param_count++;
           argoptions += strlen(argoptions);
           break;
         case 'f' :       /* Enable flex debugging output */
           yy_flex_debug = 1;
           break;
         case 'n' :       /* Column name generation option */
           if ((*argoptions != 'c') || (strlen(argoptions) < 2))
             goto Quit;

           switch(argoptions[1]) {
             case 'm' :
               conname_format(CON_FORM_MAKE);
               argoptions+=2;
               break;
             case 'n' :
               conname_format(CON_FORM_NAME);
	       argoptions+=2;
               break;
             case 'f' :
               conname_format(CON_FORM_FULL);
	       argoptions+=2;
               break;
             default :
               goto Quit;
           }
           break;
         case 'O' :       /* Optimize LP by preprocessing */
           lp->presolve = TRUE;
           break;
         case 'v' :       /* Verbosity level 0-5 */
           i = atoi(argoptions++);
           if (i >= VERB_QUIET && verbose <= VERB_DEBUG)
             verbose = i;
           break;
         case 'V' :
           _ZIMPL_hook_fn(lp->host, "XLI_ZIMPL version " VERSION "\n");
           goto Quit;
         case 's' :
           seed = (unsigned long) strtol(argoptions, &argoptions, 10);
           break;
         default :
           goto Quit;
       }
       while(*argoptions == ' ')
         argoptions++;
       if ((strlen(argoptions) > 0) && (*argoptions != '-'))
         goto Quit;
     }
   }

   /* gmp_init(verbose >= VERB_VERBOSE); */
   str_init();
#if ((ZIMPL_MAJORVERSION > 2) || (ZIMPL_MAJORVERSION == 2 && ZIMPL_MINORVERSION >= 06))
   numb_init();
#else
   numb_init(seed);
#endif
   elem_init();
   set_init();
   mio_init();
   interns_init();
   local_init();

   if(0 == setjmp(zpl_read_env))
     is_longjmp_ok = TRUE;
   else
     goto Quit;

   /* Make symbol to hold entries of internal variables */
   lp->set = set_pseudo_new();
   (void)symbol_new(SYMBOL_NAME_INTERNAL, SYM_VAR, lp->set, 100, NULL);
   set_free(lp->set);

   /* Now store the param defines */
   for(i = 0; i < lp->param_count; i++)
     zpl_add_parameter(lp->param_table[i]);

   /* Next we read in the zpl program(s) */
   lp->prog = prog_new();

   if(strstr(model, "'") == NULL)
     my_prog_load(lp->prog, model);
   else {
     argoptions = model;
     while(sscanf( argoptions, "%255s", file_name) > 0) {
       my_prog_load(lp->prog, file_name);
       argoptions += strlen(file_name);
       while(*argoptions == ' ')
         argoptions++;
     }
   }

   if(prog_is_empty(lp->prog)) {
     _ZIMPL_hook_fn(lp->host, "No ZIMPL program statements to execute.\n");
     goto Quit;
   }
   if(verbose >= VERB_DEBUG)
      prog_print(stderr, lp->prog);

   lp->ZIMPL = my_xlp_alloc(model);

   prog_execute(lp->prog);

   /* Presolve */
   if(lp->presolve && !xlp_presolve()) {
      _ZIMPL_hook_fn(lp->host, "ZIMPL presolve error.\n");
     goto Quit;
   }

   if(verbose >= VERB_NORMAL)
      xlp_stat();

   xlp_scale();
   status = TRUE;

Quit:
   MEMFREE(file_name);
   return( status );

}

MYBOOL XLI_CALLMODEL xli_freenative(ZimplModel *lp)
{
  int i;

  if(lp == NULL)
    return( FALSE );

  if(lp->prog != NULL)
    prog_free(lp->prog);

  if(is_longjmp_ok) {
    is_longjmp_ok = FALSE;

    local_exit();
    interns_exit();
    if(lp->ZIMPL != NULL)
      xlp_free();
    mio_exit();
    symbol_exit();
    define_exit();
    set_exit();
    elem_exit();
    numb_exit();
    str_exit();
    /* gmp_exit(); */
  }

  for(i = 0; i < lp->param_count; i++)
    MEMFREE(lp->param_table[i]);
  MEMFREE(lp->param_table);
  return( TRUE );
}

MYBOOL XLI_CALLMODEL xli_readmodel(lprec *lp, char *model, char *data, char *options, int lpverbose)
{
  ZimplModel *ZIMPL = NULL;
  MYBOOL     status = FALSE;

  if(model == NULL)
    goto Done;

  /* Initialize */
  ZIMPL = my_calloc(1, sizeof(*ZIMPL));
  if(ZIMPL == NULL)
    goto Done;
  ZIMPL->host = lp;

  /* Parse the model */
  status = xli_getnative(ZIMPL, model, data, options, lpverbose);
  if(status) {

    /* Write pending messages */
    if(verbose >= VERB_DEBUG)
      symbol_print_all(stderr);

    /* Convert to lp_solve representation */
    lpsolve_write(ZIMPL->ZIMPL, lp);

  }

  /* Now clean up. */
  xli_freenative(ZIMPL);
  MEMFREE(ZIMPL);
  if (lpverbose >= DETAILED)
    mem_display(stderr);

Done:
  return( status );
}

static void write_lpcomment(FILE *output, char *string, MYBOOL newlinebefore)
{
  fprintf(output, "%s# %s\n", (newlinebefore) ? "\n" : "", string);
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
  MYBOOL ok = FALSE;
  REAL   constant_term, lowbo, upbo, rh, rh_range, infinite;
  FILE   *output = stdout;
  char   *ptr;
  char buf[256];
  int sostype, priority, count, *sosvars;
  REAL *weights;

  Ncolumns = get_Ncolumns(lp);
  Nrows = get_Nrows(lp);

  for(i = 1; i <= Ncolumns; i++)
    if(!is_splitvar(lp, i)) {
      if(is_semicont(lp, i)) {
        report(lp, IMPORTANT, "Model contains semi-continious variables. Unable to generate a ZIMPL model.");
        return(FALSE);
      }
/*
      if(is_SOS_var(lp, i)) {
        report(lp, IMPORTANT, "Model contains SOS variables. Unable to generate a ZIMPL model.");
        return(FALSE);
      }
*/
    }

  ok = (MYBOOL) ((filename == NULL) || ((output = fopen(filename,"w")) != NULL));
  if(!ok)
    return(ok);
  if(filename == NULL && lp->outstream != NULL)
    output = lp->outstream;

  ok = TRUE;

  /* Write name of model */
  ptr = get_lp_name(lp);
  if((ptr != NULL) && (*ptr))
    write_lpcomment(output, ptr, ok = FALSE);

  constant_term = get_rh(lp, 0);

  infinite = get_infinite(lp);

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
      if(lowbo != -infinite)
        fprintf(output, " >= %.12g", lowbo);
      else
        fprintf(output, " >= -infinity");
      if(upbo != infinite)
        fprintf(output, " <= %.12g", upbo);
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
    fprintf(output, "subto");
    ptr = get_row_name(lp, j);
    if((ptr != NULL) && (*ptr))
      fprintf(output, " %s", ptr);
    fprintf(output, ": ");

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
      fprintf(output, " ==");
    else if(constr_type == GE)
      fprintf(output, " >=");
    else
      fprintf(output, " <=");
    fprintf(output, " %.12g;\n", rh);
  }

  /* Write optional SOS section */
  for(ok = FALSE, i = 1; get_SOS(lp, i, buf, &sostype, &priority, &count, NULL, NULL); i++)
    if ((count) && ((sostype == 1) || (sostype == 2))) {
      if (!ok) {
        write_lpcomment(output, "SOS definitions", TRUE);
        ok = TRUE;
      }
      sosvars = (int *) my_malloc(count * sizeof(*sosvars));
      weights = (REAL *) my_malloc(count * sizeof(*weights));
      get_SOS(lp, i, buf, &sostype, &priority, &count, sosvars, weights);
      fprintf(output, "sos s%d: type%d priority %d:", i, sostype, priority);
      for(j = 0; j < count; j++)
        fprintf(output, " %+.12g * %s",
		weights[j],
                get_col_name(lp, sosvars[j]));
      MEMFREE(weights);
      MEMFREE(sosvars);
      fprintf(output, ";\n");
    }

  ok = TRUE;

  if(filename != NULL)
    fclose(output);
  return( ok );

}
