/* ========================================================================= */
/* NAME  : lp_rlnd.y                                                         */
/* ========================================================================= */

/*
   made reentrant with help of
   http://www.usualcoding.eu/post/2007/09/03/Building-a-reentrant-parser-in-C-with-Flex/Bison
*/

/*
   Note that a minimum version of bison is needed to be able to compile this.
   Older version don't know the reentrant code.
   Version 1.35 is not enough. v1.875 could be ok. Tested with v2.3
*/

%pure-parser
%parse-param {parse_parm *parm}
%parse-param {void *scanner}
%lex-param {yyscan_t *scanner}

%token VAR CONS INTCONS VARIABLEPARANT TITLE INF FRE SEC_SLB SEC_SUB SEC_INT TOK_SIGN RE_OPEQ RE_OPLE RE_OPGE MINIMISE MAXIMISE SUBJECTTO END UNDEFINED


%{
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define scanner yyscanner
#define PARM yyget_extra(yyscanner)
#define YYSTYPE int
#define YY_EXTRA_TYPE parse_parm *
#define YY_FATAL_ERROR(msg) lex_fatal_error(PARM, yyscanner, msg)
#define yyerror read_error

#include "lpkit.h"
#include "yacc_read.h"

typedef struct parse_vars_s
{
  char HadVar, HadConstraint, Had_lineair_sum, OP, Sign, isign, make_neg, TypeBound;
  char Within_gen_decl;  /* TRUE when we are within an gen declaration */
  char Within_bin_decl;  /* TRUE when we are within an bin declaration */
  char Within_sec_decl;  /* TRUE when we are within a sec declaration */
  char Within_sos_decl;  /* TRUE when we are within a sos declaration */
  char *Last_var, *title;
  REAL f;
} parse_vars;

#ifdef FORTIFY
# include "lp_fortify.h"
#endif

/* let's please C++ users */
#ifdef __cplusplus
extern "C" {
#endif

#if defined MSDOS || defined __MSDOS__ || defined WINDOWS || defined _WINDOWS || defined WIN32 || defined _WIN32
#define YY_NO_UNISTD_H

static int isatty(int f)
{
  return(FALSE);
}

#if !defined _STDLIB_H
# define _STDLIB_H
#endif
#endif

#ifdef __cplusplus
};
#endif

#include "lp_rlnd.inc"

#undef yylval

%}

%start inputfile
%%

EMPTY: /* EMPTY */
                ;

inputfile	:
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->isign = 0;
  pv->make_neg = 0;
  pv->Sign = 0;
  pv->HadConstraint = FALSE;
  pv->HadVar = FALSE;
}
                  optional_title
		  objective_function
		  x_constraints
                  end
                  optionals
		;

/* start objective_function */

/*

 objective_function: MAXIMISE of | MINIMISE of;
 of:                 real_of | VARIABLEPARANT real_of;
 real_of:            x_lineair_sum;

*/

objective_function:
                  MAXIMISE
                  of
{
  set_obj_dir(PARM, TRUE);
}
                | MINIMISE
                  of
{
  set_obj_dir(PARM, FALSE);
}
                ;

of              : real_of
                | VARIABLEPARANT
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if(!add_constraint_name(pp, pv->Last_var))
    YYABORT;
  /* pv->HadConstraint = TRUE; */
}
                  real_of
                ;

real_of:          x_lineair_sum
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  add_row(pp);
  /* pv->HadConstraint = FALSE; */
  pv->HadVar = FALSE;
  pv->isign = 0;
  pv->make_neg = 0;
}
		;

/* end objective_function */



/* start constraints */

/*

 constraints:        EMPTY | x_constraints;
 x_constraints:      SUBJECTTO constraints;
 constraints:        constraint | constraints constraint;
 constraint:         real_constraint | VARIABLEPARANT real_constraint;
 real_constraint:    x_lineair_sum RE_OP cons_term RHS_STORE;
 RE_OP:              RE_OPEQ | RE_OPLE | RE_OPGE;
 cons_term:          x_SIGN REALCONS | INF;
 x_lineair_sum:      EMPTY | lineair_sum;
 lineair_sum:        lineair_term | lineair_sum lineair_term;
 lineair_term:       x_SIGN VARIABLE VAR_STORE | x_SIGN REALCONS VARIABLE VAR_STORE;
 x_SIGN:             EMPTY | TOK_SIGN;
 VARIABLE:           VAR;
 REALCONS:           INTCONS | CONS;

*/

x_constraints:    SUBJECTTO
{ /* SUBJECTTO */
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->HadConstraint = TRUE;
}
                  constraints
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->HadConstraint = FALSE;
}
                ;

constraints	: constraint
		| constraints
		  constraint
		;

constraint      : real_constraint
                | VARIABLEPARANT
{ /* constraint */
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if(!add_constraint_name(pp, pv->Last_var))
    YYABORT;
  /* pv->HadConstraint = TRUE; */
}
                  real_constraint
                ;

real_constraint	: x_lineair_sum
		  RE_OP
{ /* real_constraint 1 */
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if(!store_re_op(pp, pv->OP, pv->HadConstraint, pv->HadVar, pv->Had_lineair_sum))
    YYABORT;
  pv->make_neg = 1;
}
		  cons_term
                  RHS_STORE
{ /* real_constraint 2 */
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->Had_lineair_sum = TRUE;
  add_row(pp);
  /* pv->HadConstraint = FALSE; */
  pv->HadVar = FALSE;
  pv->isign = 0;
  pv->make_neg = 0;
  null_tmp_store(pp, TRUE);
}
		;

x_lineair_sum	: EMPTY
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->HadConstraint = pv->HadVar = TRUE;
}
                | lineair_sum
                ;

lineair_sum	: lineair_term
		| lineair_sum
		  lineair_term
		;

lineair_term	: x_SIGN
                  VARIABLE
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->f = 1.0;
}
                  VAR_STORE
		| x_SIGN
                  REALCONS
		  VARIABLE
                  VAR_STORE
                ;

RE_OP: RE_OPEQ | RE_OPLE | RE_OPGE
                ;

cons_term:        x_SIGN
		  REALCONS
                | INF
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->isign = pv->Sign;
}
                ;

/* end constraints */


/* optionals */

optionals:        EMPTY
                | x_optionals
                ;

x_optionals:      optional
                | x_optionals
                  optional
                ;

optional:         title
                | bound
                | int_declaration
                ;


/* title */

/*

 optional_title:     EMPTY | title;
 title:              TITLE;

*/

title:            TITLE
{ /* title */
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if(!set_title(pp, pv->title))
    YYABORT;
}
                ;

optional_title:   EMPTY
                | title
                ;

/* bounds */

/*

 bound:              boundFR | boundSLB | boundSUB;
 boundFR:            FRE VARIABLE VAR_STORE RHS_STORE RHS_STORE;
 VARIABLE:           VAR;

*/

bound:            boundFR
                | boundSLB
                | boundSUB
                ;

boundFR:          FRE
                  VARIABLE
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->isign = 0;
  pv->make_neg = 0;
  pv->Sign = 0;
  pv->f = 1;
}
                  VAR_STORE
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if(!store_re_op(pp, '>', pv->HadConstraint, pv->HadVar, pv->Had_lineair_sum))
    YYABORT;
  pv->make_neg = 1;
  pv->isign = 0;
  pv->f = -DEF_INFINITE;
}
                  RHS_STORE
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if(!store_bounds(pp, FALSE))
    YYABORT;

  if(!store_re_op(pp, '<', pv->HadConstraint, pv->HadVar, pv->Had_lineair_sum))
    YYABORT;
  pv->f = DEF_INFINITE;
  pv->isign = 0;
}
                  RHS_STORE
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if(!store_bounds(pp, FALSE))
    YYABORT;
  /* pv->HadConstraint = FALSE; */
  pv->HadVar = FALSE;
  pv->isign = 0;
  pv->make_neg = 0;
  null_tmp_store(pp, TRUE);
}
                ;

boundSLB:         SEC_SLB
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->TypeBound = '>';
}
                  boundSB
                ;

boundSUB:         SEC_SUB
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->TypeBound = '<';
}
                  boundSB
                ;

boundSB:          VARIABLE
{ /* boundSB 1 */
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->isign = 0;
  pv->make_neg = 0;
  pv->Sign = 0;
  pv->f = 1;
}
                  VAR_STORE
                  x_SIGN
		  REALCONS
{ /* boundSB 2 */
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if(!store_re_op(pp, pv->TypeBound, pv->HadConstraint, pv->HadVar, pv->Had_lineair_sum))
    YYABORT;
  pv->make_neg = 1;
  /* pv->isign = 0; */
}
                  RHS_STORE
{ /* boundSB 3 */
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if(!store_bounds(pp, FALSE))
    YYABORT;
  /* pv->HadConstraint = FALSE; */
  pv->HadVar = FALSE;
  pv->isign = 0;
  pv->make_neg = 0;
  null_tmp_store(pp, TRUE);
}
                ;

/* end bounds */



REALCONS: INTCONS | CONS
                ;

RHS_STORE:        EMPTY
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if (    (pv->isign || !pv->make_neg)
      && !(pv->isign && !pv->make_neg)) /* but not both! */
    pv->f = -pv->f;
  if(!rhs_store(pp, pv->f, pv->HadConstraint, pv->HadVar, pv->Had_lineair_sum))
    YYABORT;
  pv->isign = 0;
}
                ;

x_SIGN:           EMPTY
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->isign = 0;
}
                | TOK_SIGN
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->isign = pv->Sign;
}
                ;

VAR_STORE:        EMPTY
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if (    (pv->isign || pv->make_neg)
      && !(pv->isign && pv->make_neg)) /* but not both! */
    pv->f = -pv->f;
  if(!var_store(pp, pv->Last_var, pv->f, pv->HadConstraint, pv->HadVar, pv->Had_lineair_sum)) {
    yyerror(pp, pp->scanner, "var_store failed");
    YYABORT;
  }
  /* pv->HadConstraint |= pv->HadVar; */
  pv->HadVar = TRUE;
  pv->isign = 0;
}
                ;


/* start int_declaration */

ONEVARIABLE:      VARIABLE
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  storevarandweight(pp, pv->Last_var);
}
                ;

int_declaration:  SEC_INT
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  check_int_sec_sos_free_decl(pp, pv->Within_gen_decl ? 1 : pv->Within_bin_decl ? 2 : 0, 0, 0, 0);
}
                  ONEVARIABLE
                ;

/* end int_sec_sos_declarations */


VARIABLE:         VAR
                ;

/* start end */

end:              END
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->Had_lineair_sum = FALSE;
}
                ;

/* end end */

%%

static void yy_delete_allocated_memory(parse_parm *pp)
{
  parse_vars *pv = (parse_vars *) pp->parse_vars;
  /* free memory allocated by flex. Otherwise some memory is not freed.
     This is a bit tricky. There is not much documentation about this, but a lot of
     reports of memory that keeps allocated */

  /* If you get errors on this function call, just comment it. This will only result
     in some memory that is not being freed. */

# if defined YY_CURRENT_BUFFER
    /* flex defines the macro YY_CURRENT_BUFFER, so you should only get here if lp_rlp.h is
       generated by flex */
    /* lex doesn't define this macro and thus should not come here, but lex doesn't has
       this memory leak also ...*/

#  if 0
    /* older versions of flex */
    yy_delete_buffer(YY_CURRENT_BUFFER); /* comment this line if you have problems with it */
    yy_init = 1; /* make sure that the next time memory is allocated again */
    yy_start = 0;
#  else
    /* As of version 2.5.9 Flex  */
    yylex_destroy(pp->scanner); /* comment this line if you have problems with it */
#  endif
# endif

  FREE(pv->Last_var);
}

static int parse(parse_parm *pp)
{
  return(yyparse(pp, pp->scanner));
}

lprec *read_lndex(lprec *lp, FILE *filename, int verbose, char *lp_name)
{
  parse_vars *pv;
  lprec *lp1 = NULL;

  CALLOC(pv, 1, parse_vars);
  if (pv != NULL) {
    parse_parm pp;

    memset(&pp, 0, sizeof(pp));
    pp.parse_vars = (void *) pv;

    yylex_init(&pp.scanner);
    yyset_extra(&pp, pp.scanner);

    yyset_in((FILE *) filename, pp.scanner);
    yyset_out(NULL, pp.scanner);

    lp1 = yacc_read(lp, verbose, lp_name, parse, &pp, yy_delete_allocated_memory);
    FREE(pv);
  }
  return(lp1);
}

lprec * __WINAPI read_lnd(FILE *filename, int verbose, char *lp_name)
{
  return(read_lndex(NULL, filename, verbose, lp_name));
}

lprec *read_LNDex(lprec *lp, char *filename, int verbose, char *lp_name)
{
  FILE *fpin;

  if((fpin = fopen(filename, "r")) != NULL) {
    lp = read_lndex(lp, fpin, verbose, lp_name);
    fclose(fpin);
  }
  else
    lp = NULL;
  return(lp);
}

lprec * __WINAPI read_LND(char *filename, int verbose, char *lp_name)
{
  return(read_LNDex(NULL, filename, verbose, lp_name));
}
