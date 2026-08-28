/* ========================================================================= */
/* NAME  : lp_rlpt.y                                                         */
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
%expect 1

%token VAR CONS INTCONS VARIABLECOLON INF FRE SEC_INT SEC_SEC SEC_SECI TOK_SIGN RE_OPEQ RE_OPLE RE_OPGE MINIMISE MAXIMISE SUBJECTTO BOUNDS UNDEFINED

%token END 0 /* endmarker token - 0 indicates end of parsing */

%{
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define scanner yyscanner
#define PARM yyget_extra(yyscanner)
#define YYSTYPE int
#define YY_EXTRA_TYPE parse_parm *
#define YY_FATAL_ERROR(msg) lex_fatal_error(PARM, yyscanner, msg)
#undef YY_INPUT
#define yyerror read_error

#include "lpkit.h"
#include "yacc_read.h"

typedef struct parse_vars_s
{
  char HadVar, HadConstraint, Had_lineair_sum, HadSign, OP, Sign, isign, isign0, make_neg, objconst;
  char Within_int_decl;  /* TRUE when we are within an gen declaration */
  char Within_gen_decl;  /* TRUE when we are within an gen declaration */
  char Within_bin_decl;  /* TRUE when we are within an bin declaration */
  char Within_sec_decl;  /* TRUE when we are within a sec declaration */
  char Within_sos_decl;  /* TRUE when we are within a sos declaration */
  short SOStype;         /* SOS type */
  int SOSNr;
  int SOSweight;         /* SOS weight */
  int weight;
  char *Last_var, *Last_var0;
  REAL f, f0, f1, f2;
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

#include "lp_rlpt.inc"

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
		  objective_function
                  constraints
		  bounds
                  int_sec_sos_declarations
                  end
		;

/* start objective_function */

/*

 objective_function: objective_function1;
 objective_function1:MAXIMISE of | MINIMISE of;
 of:                 real_of | VARIABLECOLON real_of;
 real_of:            of_lineair_sum;
 of_lineair_sum:     EMPTY | of_lineair_sum1;
 of_lineair_sum1:    of_lineair_term | of_lineair_sum1 of_lineair_term;
 of_lineair_term:    x_SIGN of_lineair_term1
 of_lineair_term1:   REALCONS | VARIABLE VAR_STORE;

*/

objective_function:
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->f = 1;
  pv->f1 = pv->f2 = 0;
}
                  objective_function1
                ;

objective_function1:
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
                | VARIABLECOLON
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if(!add_constraint_name(pp, pv->Last_var))
    YYABORT;
  /* pv->HadConstraint = TRUE; */
}
                  real_of
                ;

real_of:          of_lineair_sum
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if((!pv->objconst) && (pv->f1 + pv->f2 != 0)) {
    yyerror(pp, pp->scanner, "constant in objective not supported");
    YYABORT;
  }
  if(!rhs_store(pp, -(pv->f1 + pv->f2), pv->HadConstraint, pv->HadVar, pv->Had_lineair_sum))
    YYABORT;

  add_row(pp);
  /* pv->HadConstraint = FALSE; */
  pv->HadVar = FALSE;
  pv->isign = 0;
  pv->make_neg = 0;
}
		;

of_lineair_sum  : EMPTY
                | of_lineair_sum1
                ;

of_lineair_sum1	: of_lineair_term
		| of_lineair_sum1
		  of_lineair_term
		;

of_lineair_term :
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->HadSign = FALSE;
}
                  x_SIGN
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if(pv->HadSign) {
    pv->f1 += pv->f2;
    pv->f = 1;
  }
}
                  of_lineair_term1;

of_lineair_term1: REALCONS
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if (    (pv->isign || pv->make_neg)
      && !(pv->isign && pv->make_neg)) /* but not both! */
    pv->f = -pv->f;
  pv->f2 = pv->f;
  pv->isign = 0;
}
                |
		  VARIABLE
                  VAR_STORE
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->f2 = 0;
  pv->f = 1;
}
                ;

/* end objective_function */



/* start constraints */

/*

 constraints:        EMPTY | constraints1;
 constraints1:       SUBJECTTO constraints2;
 constraints2:       EMPTY | constraints3;
 constraints3:       constraint | constraints3 constraint;
 constraint:         real_constraint | VARIABLECOLON real_constraint;
 real_constraint:    x_lineair_sum RE_OP RHS;
 RE_OP:              RE_OPEQ | RE_OPLE | RE_OPGE;
 RHS:                cons_term RHS_STORE;
 cons_term:          x_SIGN REALCONS | INF;
 x_lineair_sum:      EMPTY | lineair_sum;
 lineair_sum:        lineair_term | lineair_sum lineair_term;
 lineair_term:       x_SIGN VARIABLE VAR_STORE | x_SIGN REALCONS VARIABLE VAR_STORE;
 x_SIGN:             EMPTY | TOK_SIGN;
 VARIABLE:           VAR | FRE;
 REALCONS:           INTCONS | CONS;

*/

constraints     : EMPTY
                | constraints1
                ;

constraints1:     SUBJECTTO
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->HadConstraint = TRUE;
}
                  constraints2
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->HadConstraint = FALSE;
}
                ;

constraints2:   EMPTY
                | constraints3
                ;

constraints3	: constraint
		| constraints3
		  constraint
		;

constraint      : real_constraint
                | VARIABLECOLON
{
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
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if(!store_re_op(pp, pv->OP, pv->HadConstraint, pv->HadVar, pv->Had_lineair_sum))
    YYABORT;
  pv->make_neg = 1;
}
                  RHS
                ;

RHS  		: cons_term
                  RHS_STORE
{
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
                | VARIABLE
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if(pv->OP != '=') {
    yyerror(pp, pp->scanner, "parse error");
    YYABORT;
  }

  if(strcmp(pv->Last_var, "S1") == 0)
    pv->SOStype = 1;
  else if(strcmp(pv->Last_var, "S2") == 0)
    pv->SOStype = 2;
  else {
    yyerror(pp, pp->scanner, "parse error");
    YYABORT;
  }

  pv->f = 1;
}
                  RHS_STORE
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->Had_lineair_sum = TRUE;
  add_sos_row(pp, pv->SOStype);
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
                | x_SIGN
                  INF
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->isign = pv->Sign;
}
                ;

/* end constraints */



/* start bounds */

/*

 bounds:             EMPTY | BOUNDS x_bounds;
 x_bounds:           EMPTY | x_bounds1;
 x_bounds1:          bound | x_bounds1 bound;
 bound:              VARIABLE VAR_STORE bound2 | cons_term RE_OP VARIABLE VAR_STORE RHS_STORE optionalbound;
 VARIABLE:           VAR | FRE;
 bound2:             RE_OP cons_term RHS_STORE | FRE RHS_STORE RHS_STORE;
 cons_term:          x_SIGN REALCONS | INF;
 optionalbound:      EMPTY | RE_OP cons_term RHS_STORE;

*/

bounds:           EMPTY
                | BOUNDS
                  x_bounds
                ;

x_bounds:         EMPTY
                | x_bounds1
                ;

x_bounds1:        bound
                | x_bounds1
                  bound
                ;

bound:            VARIABLE
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->f = 1.0;
  pv->isign = 0;
}
                  VAR_STORE
                  bound2
		| cons_term
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->f0 = pv->f;
  pv->isign0 = pv->isign;
}
		  RE_OP
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if(!store_re_op(pp, pv->OP, pv->HadConstraint, pv->HadVar, pv->Had_lineair_sum))
    YYABORT;
  pv->make_neg = 0;
}
                  VARIABLE
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->isign = 0;
  pv->f = -1.0;
}
                  VAR_STORE
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->isign = pv->isign0;
  pv->f = pv->f0;
}
                  RHS_STORE
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if(!store_bounds(pp, TRUE))
    YYABORT;
}
                  optionalbound
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  /* pv->HadConstraint = FALSE; */
  pv->HadVar = FALSE;
  pv->isign = 0;
  pv->make_neg = 0;
  null_tmp_store(pp, TRUE);
}
                ;

bound2:           RE_OP
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if(!store_re_op(pp, pv->OP, pv->HadConstraint, pv->HadVar, pv->Had_lineair_sum))
    YYABORT;
  pv->make_neg = 1;
}
		  cons_term
                  RHS_STORE
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if(!store_bounds(pp, TRUE))
    YYABORT;
  /* pv->HadConstraint = FALSE; */
  pv->HadVar = FALSE;
  pv->isign = 0;
  pv->make_neg = 0;
  null_tmp_store(pp, TRUE);
}
                | FRE
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


optionalbound:    EMPTY
                | RE_OP
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if(!store_re_op(pp, (char) ((pv->OP == '<') ? '>' : (pv->OP == '>') ? '<' : pv->OP), (int) pv->HadConstraint, (int) pv->HadVar, (int) pv->Had_lineair_sum))
    YYABORT;
  pv->make_neg = 0;
  pv->isign = 0;
}
                  cons_term
                  RHS_STORE
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if(!store_bounds(pp, TRUE))
    YYABORT;
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
  pv->HadSign = TRUE;
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


/* start int_sec_sos_declarations */

int_sec_sos_declarations: x_int_declarations
                          x_sec_declarations
                          x_seci_declarations
                ;

VARIABLES:        ONEVARIABLE
                | VARIABLES
                  ONEVARIABLE
                ;

SECVARIABLES:     ONESECVARIABLE
                | SECVARIABLES
                  ONESECVARIABLE
                ;

ONEVARIABLE:      VARIABLE
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  storevarandweight(pp, pv->Last_var);
}
                ;

ONESECVARIABLE:   VARIABLE
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  FREE(pv->Last_var0);
  pv->Last_var0 = strdup(pv->Last_var);
}
                  OPTIONALGE
                ;

OPTIONALGE:       EMPTY
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  storevarandweight(pp, pv->Last_var0);
  FREE(pv->Last_var0);
}
                | RE_OPGE
                  x_SIGN
                  REALCONS
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  storevarandweight(pp, pv->Last_var0);
  if (pv->isign)
    pv->f = -pv->f;
  pv->isign = 0;
  set_sec_threshold(pp, pv->Last_var0, pv->f);
  FREE(pv->Last_var0);
}
                ;

x_int_declarations:
                  EMPTY
                | int_declarations
                ;

int_declarations: int_declaration
                | int_declarations
                  int_declaration
                ;

int_declaration: SEC_INT
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  check_int_sec_sos_free_decl(pp, pv->Within_gen_decl ? 1 : pv->Within_bin_decl ? 2 : pv->Within_int_decl ? 3 : 0, 0, 0, 0);
}
                 VARIABLES
                ;

x_sec_declarations:
                 EMPTY
                | sec_declarations
                ;

sec_declarations: sec_declaration
                | sec_declarations
                  sec_declaration
                ;

sec_declaration: SEC_SEC
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  check_int_sec_sos_free_decl(pp, 0, 1, 0, 0);
}
                 SECVARIABLES
                ;

x_seci_declarations:
                 EMPTY
                | seci_declarations
                ;

seci_declarations:
                  seci_declaration
                | seci_declarations
                  seci_declaration
                ;

seci_declaration: SEC_SECI
{
  parse_parm *pp = PARM;

  check_int_sec_sos_free_decl(pp, 1, 1, 0, 0);
}
                 SECVARIABLES
                ;

/* end int_sec_sos_declarations */


VARIABLE: VAR | FRE
                ;

/* start end */

end:              EMPTY
                | END
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
    /* flex defines the macro YY_CURRENT_BUFFER, so you should only get here if lp_rlpt.inc is
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
  FREE(pv->Last_var0);
}

static int parse(parse_parm *pp)
{
  return(yyparse(pp, pp->scanner));
}

lprec *read_lptex(lprec *lp, FILE *filename, int verbose, char *lp_name, char objconst0)
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
    pv->objconst = objconst0;
    lp1 = yacc_read(lp, verbose, lp_name, parse, &pp, yy_delete_allocated_memory);
    FREE(pv);
  }
  return(lp1);
}

lprec * __WINAPI read_lpt(FILE *filename, int verbose, char *lp_name)
{
  return(read_lptex(NULL, filename, verbose, lp_name, FALSE));
}

lprec *read_LPTex(lprec *lp, char *filename, int verbose, char *lp_name, char objconst)
{
  FILE *fpin;

  if((fpin = fopen(filename, "r")) != NULL) {
    lp = read_lptex(lp, fpin, verbose, lp_name, objconst);
    fclose(fpin);
  }
  else
    lp = NULL;
  return(lp);
}

lprec * __WINAPI read_LPT(char *filename, int verbose, char *lp_name)
{
  return(read_LPTex(NULL, filename, verbose, lp_name, FALSE));
}
