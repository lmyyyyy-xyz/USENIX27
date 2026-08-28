/****************************************************************
Copyright (C) 1997-2000 Lucent Technologies
All Rights Reserved

Permission to use, copy, modify, and distribute this software and
its documentation for any purpose and without fee is hereby
granted, provided that the above copyright notice appear in all
copies and that both that the copyright notice and this
permission notice and warranty disclaimer appear in supporting
documentation, and that the name of Lucent or any of its entities
not be used in advertising or publicity pertaining to
distribution of the software without specific, written prior
permission.

LUCENT DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.
IN NO EVENT SHALL LUCENT OR ANY OF ITS ENTITIES BE LIABLE FOR ANY
SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF
THIS SOFTWARE.
****************************************************************/

/* This driver works with lp_solve 3.x, 4.x, 5.x. */

#include "lpkit.h"
#ifndef MAJORVERSION
#include "patchlevel.h"
#endif

#if !defined MAJORVERSION
# define MAJORVERSION 3
#endif

#if !defined MINORVERSION
# define MINORVERSION 0
#endif

#if MAJORVERSION == 3
# include "lpglob.h"
#endif

#define DEBUGSTARTBASE 0

#if MAJORVERSION >= 5
# define def_scalemode SCALE_MEAN
#elif MAJORVERSION == 4
# define def_scalemode MMSCALING
#else
# define def_scalemode 0
#endif

#define STDIO_H_included
#include "getstub.h"

 static char *wlp = NULL, *wmps = NULL, *wfmps = NULL, *wxli = NULL, *wxliname = NULL, *wxlioptions = NULL, *wparname = NULL, *wparoptions = NULL, *rparname = NULL, *rparoptions = NULL, *bfp = NULL;
 static int scalemode = -1, bb_rule = -1, floor_first = -1, floor_first2 = -1, debug = -1, anti_degen = -1, anti_degen2 = -1, improve = -1, nobj = 1, print_at_invert = -1, print_sol = -1, print_sol2 = -1, prlp = 0, scaling = 0, trace = -1, verbose = -1, write_model_after = FALSE, parse_only = FALSE, max_num_inv = -1, pivoting = -1, presolve1 = 0, basiscrash = -1, preferdual = -1, simplextype = 0, break_at_first = FALSE, bb_maxlevel = -1, solutionlimit = -1, printsol = 0, coldstart = FALSE;
 static long sectimeout = 0;
 static REAL epsint = -1, obj_bound = 1e99, epspivot = -1, epsd = -1, epsb = -1, epsel = -1, epsp = -1, ga = -1, gr = -1, break_at_value = -1;

#if MAJORVERSION >= 4

#if MAJORVERSION == 4
 static char
scalemode_msg[] = "=... scale mode:  one of\n\
  		    0 (default) for numerical range-based scaling\n\
  		    1 for geometric mean scaling\n\
  		    4 for Curtis & Reid scaling\n\
  	       plus\n\
  		    2 for powerscaling (not with 4)\n\
  		    8 to scale \"Lagrange\" variables\n\
  		   16 to scale integer variables";

 static char
bb_msg[] = "=... branch-and-bound rule: one of\n\
  		    0 (default) for lowest indexed non-integer variable\n\
  		    1 for a random non-integer variable\n\
  		    2 for largest deviation from integer\n\
  		    3 for algorithm chooses the most appropriate non-integer\n\
                      variable\n\
  		    4 for median deviation from integer\n\
  		    5 for choose non-integer column which results in largest\n\
                      object value change";

 static char
improve_msg[] = "=... the iterative improvement level: one of\n\
  		    0 (default) improve none\n\
  		    1 improve FTRAN\n\
  		    2 improve BTRAN\n\
  		    3 improve FTRAN + BTRAN";

 static char
pivoting_msg[] = "=... simplex pivot rule: one of\n\
  		    0 select first\n\
  		    3 (default) algorithm chooses the most appropriate pivot\n\
                      row/column\n\
  		    5 choose pivot row/column that results in largest object\n\
                      value change";

# define set_scaling(lp, y) set_scalemode(lp, y)
# define set_bb_floorfirst(lp, floor_first) set_floor_first(lp, floor_first)
# define set_epsint(lp, epsint) set_epsilon(lp, epsint)
# define get_ptr_dual_solution(lp, x1) get_ptr_reduced_costs(lp, x1)
# define set_maxpivot set_max_num_inv
# define set_pivoting(lp, pivoting) set_piv_rule(lp, (MYBOOL) pivoting)
# define set_presolve(lp, presolve) set_do_presolve(lp, (MYBOOL) presolve)
# define set_abs_mip_gap(lp, ga) set_mip_gap(lp, ga);
# define print_solution1(lp) print_solution(lp)
# define print_constraints1(lp) print_constraints(lp)
# define ANTIDEGEN_DEFAULT TRUE
# define def_presolve TRUE
#endif

#if MAJORVERSION >= 5
 static char
scalemode_msg[] = "=... scale mode:  one of\n\
  		    1 for scale to convergence using largest absolute value\n\
  		    2 for scale based on the simple numerical range\n\
  		    3 (default) for numerical range-based scaling\n\
  		    4 for geometric scaling\n\
  		    7 for Curtis & Reid scaling\n\
  	       plus\n\
  		   16 for scale to convergence using logarithmic mean\n\
                      of all values\n\
  		   32 for also do Power scaling\n\
  		   64 to make sure that no scaled number is above 1\n\
  		  128 to scale integer variables";

 static char
bb_msg[] = "=... branch-and-bound rule: one of\n\
  		    0 (default) for lowest indexed non-integer variable\n\
  		    1 for selection based on distance from the current bounds\n\
  		    2 for selection based on the largest current bound\n\
  		    3 for selection based on largest fractional value\n\
  		    4 for simple, unweighted pseudo-cost of a variable\n\
  		    5 this is an extended pseudo-costing strategy based on\n\
                      minimizing the number of integer infeasibilities\n\
  		    6 this is an extended pseudo-costing strategy based on\n\
                      maximizing the normal pseudo-cost divided by the\n\
                      number of infeasibilities\n\
  	       plus\n\
  		    8 for weight reverse mode\n\
                   16 when cauto is used, select the oposite direction that\n\
                      autoselect had chosen\n\
  		   32 for greedy mode\n\
  		   64 for pseudo cost mode\n\
  		  128 select the node that has already been selected before\n\
                      the most number of times\n\
  		  256 for randomize mode\n\
  		 1024 when mode 128 is selected, switch off this mode when\n\
                      a first solution is found\n\
  		 2048 for restart mode\n\
  		 4096 select the node that has been selected before the\n\
                      fewest number of times or not at all";

 static char
anti_degen_msg[] = "=... anti-degen handling: one of\n\
  		    0 (default) no anti-degeneracy handling\n\
  		    1 check if there are equality slacks in the basis and\n\
                      try to drive them out in order to reduce chance of\n\
                      degeneracy in Phase 1\n\
                    2 ColumnCheck\n\
                    4 Stalling\n\
                    8 NumFailure\n\
                   16 LostFeas\n\
                   32 Infeasible\n\
                   64 Dynamic\n\
                  128 During BB";

#if MAJORVERSION == 5 && MINORVERSION <= 1
 static char
improve_msg[] = "=... the iterative improvement level: one of\n\
  		    0 (default) improve none\n\
  		    1 improve FTRAN\n\
  		    2 improve BTRAN\n\
  		    3 improve FTRAN + BTRAN\n\
                    4 triggers automatic inverse accuracy control in the dual\n\
                      simplex, and when an error gap is exceeded the basis is\n\
                      reinverted";
#else
 static char
improve_msg[] = "=... the iterative improvement level: one of\n\
  		    0 improve none\n\
  		    1 Running accuracy measurement of solved equations based on\n\
                      Bx=r (primal simplex), remedy is refactorization.\n\
  		    2 Improve initial dual feasibility by bound flips\n\
                      (highly recommended, and default)\n\
  		    4 Low-cost accuracy monitoring in the dual, remedy is refactorization\n\
                    8 By default there is a check for primal/dual feasibility at optimum\n\
                      only for the relaxed problem, this also activates the test at the node level";
#endif

 static char
pivoting_msg[] = "=... simplex pivot rule: one of\n\
  		    0 select first\n\
  		    1 select according to Dantzig\n\
  		    2 (default) select Devex pricing from Paula Harris\n\
  		    3 select steepest edge";

# define set_print_at_invert(lp, print_at_invert) lp = lp
# define set_abs_mip_gap(lp, ga) set_mip_gap(lp, TRUE, ga);
# define set_rel_mip_gap(lp, ga) set_mip_gap(lp, FALSE, ga);
# define print_solution1(lp) print_solution(lp, 1)
# define print_constraints1(lp) print_constraints(lp, 1)
# define auto_scale(lp) lp = lp
# define def_presolve PRESOLVE_ROWS | PRESOLVE_COLS
#endif

 static char
printsol_msg[] = "=... print solution: one of\n\
  		    0 (default) print nothing\n\
  		    1 only objective value \n\
  		    2 obj value+variables\n\
  		    3 obj value+variables+constraints\n\
  		    4 obj value+variables+constraints+duals\n\
  		    5 obj value+variables+constraints+duals+lp model\n\
  		    6 obj value+variables+constraints+duals+lp model+scales\n\
  		    7 obj value+variables+constraints+duals+lp model+scales+\n\
                      lp tableau";

#else /*lp_solve < 4.0*/
 static char
bb_msg[] = "=... branch-and-bound rule: one of\n\
  		    0 (default) for lowest indexed non-integer variable\n\
  		    1 for a random non-integer variable";

 static char
printsol_msg[] = "=... print solution: one of\n\
  		    0 (default) print nothing\n\
  		    2 obj value+variables+constraints\n\
  		    4 obj value+variables+constraints+duals\n\
  		    5 obj value+variables+constraints+duals+lp model\n\
  		    6 obj value+variables+constraints+duals+lp model+scales";

 static char
scalemode_msg[] = "=... scale mode:  one of\n\
  		    0 (default) for numerical range-based scaling";

# define MYBOOL unsigned short
# define REAL double
# define set_bb_rule(lp, bb_rule0) lp->bb_rule = bb_rule0
# define set_bb_floorfirst(lp, floor_first0) lp->floor_first = floor_first0
# define set_debug(lp, debug0) lp->debug = debug0
# define set_anti_degen(lp, anti_degen0) lp->anti_degen = anti_degen0
# define set_epsint(lp, epsint) lp->epsilon = epsint
# define set_epspivot(lp, epspivot) Trej = epspivot
# define set_epsd(lp, epsd0) lp->epsd = epsd0
# define set_epsb(lp, epsb0) lp->epsb = epsb0
# define set_epsel(lp, epsel0) lp->epsel = epsel0
# define set_improve(lp, improve) lp = lp
# define set_obj_bound(lp, obj_bound0) lp->obj_bound = obj_bound0
# define set_print_at_invert(lp, print_at_invert0) lp->print_at_invert = print_at_invert0
# define set_print_sol(lp, print_sol0) lp->print_sol = print_sol0
# define set_trace(lp, trace0) lp->trace = trace0
# define set_verbose(lp, verbose0) lp->verbose = verbose0
# define set_scaling(lp, y) lp = lp
# define get_Ncolumns(lp) lp->columns
# define set_rh_range(lp, row, deltavalue) lp->orig_upbo[row] = deltavalue
# define get_objective(lp) lp->best_solution[0]
# define get_total_iter(lp) lp->total_iter
# define get_max_level(lp) lp->max_level
# define get_total_nodes(lp) lp->total_nodes
# define get_ptr_primal_solution(lp, x1) *x1 = lp->best_solution
# define get_ptr_dual_solution(lp, x1) *x1 = lp->duals
# define print_solution1(lp) print_solution(lp)
# define print_constraints1(lp) print_constraints(lp)
# define SEVERE FALSE
# define NORMAL TRUE
# define BRANCH_FLOOR TRUE
# define BRANCH_AUTOMATIC 2
# define ANTIDEGEN_DEFAULT TRUE
#endif

#if !defined AUTOMATIC
# define AUTOMATIC 2
#endif

#if !defined OPTIMAL
# define OPTIMAL 0
#endif

#if !defined MILP_FAIL
# if defined PROCFAIL
#  define MILP_FAIL PROCFAIL
# else
#  define MILP_FAIL 1
# endif
#endif

#if !defined INFEASIBLE
# define INFEASIBLE 2
#endif

#if !defined UNBOUNDED
# define UNBOUNDED 3
#endif

#if !defined FAILURE
# define FAILURE 4
#endif

 static char *
piv_val(Option_Info *oi, keyword *kw, char *v)
{
	pivoting |= Intcast kw->info;
	return v;
	}

 static char *
presolve_val(Option_Info *oi, keyword *kw, char *v)
{
	presolve1 |= Intcast kw->info;
	return v;
	}

 static char *
simplextype_val(Option_Info *oi, keyword *kw, char *v)
{
	simplextype |= Intcast kw->info;
	return v;
	}

 static keyword
keywds[] = {
 KW("bb", I_val, &bb_rule, bb_msg),
 KW("cfirst", IK1_val, &floor_first, "in IPs, take ceiling branch first"),
#if MAJORVERSION >= 4
 KW("cauto", IK1_val, &floor_first2, "in IPs, algorithm decides which branch being taken first"),
#endif
 KW("debug", IK1_val, &debug, "debug mode"),
 KW("degen", IK1_val, &anti_degen, "perturb degeneracies"),
#if MAJORVERSION >= 5
 KW("degenx", I_val, &anti_degen2, anti_degen_msg),
#endif
 KW("eps",   D_val, &epsint, "=... tolerance for rounding to integer"),
#if MAJORVERSION >= 4
 KW("improve", I_val, &improve, improve_msg),
#endif
 KW("objno", I_val, &nobj, "=... objective number: 0 = none, 1 (default) = first"),
 KW("obound", D_val, &obj_bound,
              "=... a lower bound for the objective function\n\
               may speed up the calculations"),
#if MAJORVERSION <= 4
 KW("prinv", IK1_val, &print_at_invert, "print after inverting"),
#endif
 KW("prlp",  IK1_val, &prlp, "print the LP"),
 KW("psols", IK1_val, &print_sol, "print (intermediate) feasible solutions"),
#if MAJORVERSION >= 5
 KW("psolsa", IK1_val, &print_sol2, "print (intermediate) feasible solutions (non-zeros)"),
#endif
 KW("scale", IK1_val, &scaling, "scale the problem"),
 KW("scalemode", I_val, &scalemode, scalemode_msg),
 KW("trace", IK1_val, &trace, "trace pivot selections"),
 KW("verbose", IK1_val, &verbose, "verbose mode"),
 KW("version", Ver_val, 0, "report version details"),
 KW("wantsol", WS_val, 0, WS_desc_ASL),
#if MAJORVERSION >= 5
 KW("coldstart", IK1_val, &coldstart, "ignore starting base"),
#endif

/* lp_solve options */

 KW("wlp", C_val, &wlp, "=... write to LP filename"),
 KW("wmps", C_val, &wmps, "=... write to MPS file in fixed format"),
#if MAJORVERSION >= 5
 KW("wfmps", C_val, &wmps, "=... write to MPS file in free format"),
 KW("wxli", C_val, &wxli, "=... write file with xli library"),
 KW("wxliname", C_val, &wxliname, "=... xli library"),
 KW("wxliopt", C_val, &wxlioptions, "=... options for xli library"),
 KW("wafter", IK1_val, &write_model_after, "write model after solve (usefull if presolve used)"),
#endif
 KW("parse_only", IK1_val, &parse_only, "parse input file but do not solve"),
#if MAJORVERSION > 5 || (MAJORVERSION == 5 && MINORVERSION > 1)
 KW("wparname", C_val, &wparname, "=... parameter file to write options to"),
 KW("wparoptions", C_val, &wparoptions, "=... options parameter file"),
 KW("rparname", C_val, &rparname, "=... parameter file to read options from"),
 KW("rparoptions", C_val, &rparoptions, "=... options parameter file"),
#endif
#if MAJORVERSION >= 4
 KW("r", I_val, &max_num_inv, "=... max nbr of pivots between a re-inversion of the matrix"),
#endif
#if MAJORVERSION >= 4
 KW("piv", I_val, &pivoting, pivoting_msg),
#endif
#if MAJORVERSION >= 5
 KW("pivf", piv_val, PRICE_PRIMALFALLBACK, "in case of Steepest Edge, fall back to DEVEX in primal"),
 KW("pivm", piv_val, PRICE_MULTIPLE, "multiple pricing"),
 KW("piva", piv_val, PRICE_ADAPTIVE, "temporarily use first index if cycling is detected"),
 KW("pivr", piv_val, PRICE_RANDOMIZE, "adds a small randomization effect to the selected pricer"),
#if defined EnablePartialOptimization
 KW("pivp", piv_val, PRICE_AUTOPARTIAL, "enable partial pricing"),
 KW("pivpc", piv_val, PRICE_AUTOPARTIALCOLS, "enable partial pricing on columns"),
 KW("pivpr", piv_val, PRICE_AUTOPARTIALROWS, "enable partial pricing on rows"),
#endif
 KW("pivll", piv_val, PRICE_LOOPLEFT, "scan entering/leaving columns left rather than right"),
 KW("pivla", piv_val, PRICE_LOOPALTERNATE, "scan entering/leaving columns alternatingly left/right"),
#endif
#if MAJORVERSION >= 4
 KW("presolve", presolve_val, def_presolve, "presolve problem before start optimizing"),
#endif
#if MAJORVERSION >= 5
 KW("presolvel", presolve_val, PRESOLVE_LINDEP, "also eliminate linearly dependent rows"),
 KW("presolver", presolve_val, PRESOLVE_REDUCEMIP,
              "if the phase 1 solution process finds that a constraint is\n\
               redundant then this constraint is deleted"),
#endif
#if MAJORVERSION >= 5
 KW("crash", I_val, &basiscrash, "=... determines a starting base: one of\n\
  		    0 (default) none\n\
  		    2 most feasible basis"),
#endif
#if MAJORVERSION >= 5
 KW("prim", IK0_val, &preferdual, "prefer the primal simplex for both phases"),
 KW("dual", IK1_val, &preferdual, "prefer the dual simplex for both phases"),
#endif
#if MAJORVERSION >= 5
 KW("simplexpp", simplextype_val, SIMPLEX_PRIMAL_PRIMAL, "set Phase1 Primal, Phase2 Primal"),
 KW("simplexdp", simplextype_val, SIMPLEX_DUAL_PRIMAL, "set Phase1 Dual, Phase2 Primal"),
 KW("simplexpd", simplextype_val, SIMPLEX_PRIMAL_DUAL, "set Phase1 Primal, Phase2 Dual"),
 KW("simplexdd", simplextype_val, SIMPLEX_DUAL_DUAL, "set Phase1 Dual, Phase2 Dual"),
#endif
 KW("trej",   D_val, &epspivot, "=... minimum pivot value"),
 KW("epsd",   D_val, &epsd, "=... minimum tolerance for reduced costs"),
 KW("epsb",   D_val, &epsb, "=... minimum tolerance for the RHS"),
 KW("epsel",  D_val, &epsel, "=... minimum tolerance for rounding values to zero"),
#if MAJORVERSION >= 4
 KW("epsp",   D_val, &epsp,
              "=... value that is used as perturbation scalar for\n\
               degenerative problems"),
#endif
#if MAJORVERSION >= 4
 KW("timeout", I_val, &sectimeout, "=... timeout after sec seconds when not solution found"),
#endif
#if MAJORVERSION >= 5
 KW("bfp", C_val, &bfp, "=... set basis factorization package"),
#endif
#if MAJORVERSION >= 4
 KW("ga",   D_val, &ga, "=... specifies the absolute MIP gap for branch-and-bound"),
#endif
#if MAJORVERSION >= 5
 KW("gr",   D_val, &gr, "=... specifies the relative MIP gap for branch-and-bound"),
#endif
#if MAJORVERSION >= 4
 KW("f", IK1_val, &break_at_first,
              "specifies that branch-and-bound algorithm stops at first\n\
               found solution"),
#endif
#if MAJORVERSION >= 4
 KW("o",   D_val, &break_at_value,
              "=... specifies that branch-and-bound algorithm stops when\n\
               objective value is better than value"),
#endif
#if MAJORVERSION >= 5
 KW("depth", I_val, &bb_maxlevel, "=... set branch-and-bound depth limit"),
#endif
#if MAJORVERSION >= 5
 KW("n", I_val, &solutionlimit, "=... specify which solution number to return"),
#endif
 KW("printsol", I_val, &printsol, printsol_msg),
 };

 static char lp_solve_Version[48] = "\nAMPL/LP_SOLVE Driver Version 20060830\n";
 static Option_Info Oinfo = { "lpsolve", lp_solve_Version+6, "lpsolve_options",
				keywds, nkeywds, 0, lp_solve_Version+1,
				0,0,0,0,0, 20060830 };

 static SufDecl
suftab[] = {
	{ "sstatus", 0, ASL_Sufkind_var, 0 },
	{ "sstatus", 0, ASL_Sufkind_con, 0 }
	};

static void sortkeywds()
{
  int i, j;
  keyword keywd;

  for (i = 0; i < sizeof(keywds)/sizeof(*keywds) - 1; i++)
    for (j = i + 1; j < sizeof(keywds)/sizeof(*keywds); j++)
      if (strcmp(keywds[i].name, keywds[j].name) > 0) {
        keywd = keywds[i];
	keywds[i] = keywds[j];
	keywds[j] = keywd;
      }
}

#if MAJORVERSION < 4
static void write_lp(lprec *lp, char *filename0)
{
  FILE *output;

  if ((output = fopen(filename0, "w")) != NULL) {
    write_LP(lp, output);
    fclose(output);
  }
}

static void write_mps(lprec *lp, char *filename0)
{
  FILE *output;

  if ((output = fopen(filename0, "w")) != NULL) {
    write_MPS(lp, output);
    fclose(output);
  }
}
#endif

static void write_model(lprec *lp, char *wlp, char *wmps, char *wfmps, char *wxli, char *wxliname, char *wxlioptions)
{
  if(wlp != NULL)
    write_lp(lp, wlp);

  if(wmps != NULL)
    write_mps(lp, wmps);

#if MAJORVERSION >= 5
  if(wfmps != NULL)
    write_freemps(lp, wfmps);
#endif

#if MAJORVERSION >= 5
  if(wxli != NULL) {
    if(set_XLI(lp, wxliname)) {
      write_XLI(lp, wxli, wxlioptions, FALSE);
      set_XLI(lp, NULL);
    }
  }
#endif
}

#if MAJORVERSION >= 5
int *bascolumn;

static void __WINAPI msgfunction(lprec *lp, void *userhandle, int msg)
{
  switch(msg) {
  case MSG_LPOPTIMAL:
    if(get_basis(lp, bascolumn, TRUE))
        *bascolumn = 1;
    else
        *bascolumn = -1;
    break;
  }
}
#endif

int
main(int argc, char **argv)
{
	char *stub;
	ASL *asl;
	FILE *nl;
	lprec *lp;
	ograd *og;
	int ct, i, intmin, j, j0, j1, k, nalt, rc;
	real *LU, *c, lb, objadj, *rshift, *shift, t, ub, *x, *x0, *x1;
	char buf[256];
	typedef struct { char *msg; int code; } Sol_info;
	void *SI;
        char hasint = FALSE;
#if MAJORVERSION >= 5
	int *varstat, *A_rownos1;
	real *A_vals1, infinite;
	SufDesc *csd, *vsd;
	MYBOOL ret;
#else
	int *is;
	MYBOOL *basis, *lower;
#endif
	static Sol_info solinfo[] = {
		{ "optimal", 0 },
		{ "integer programming failure", 502 },
		{ "infeasible", 200 },
		{ "unbounded", 300 },
		{ "failure", 501 },
		{ "unknown", 500 },
                { "suboptimal", 100 }
		};

	sortkeywds();

#ifdef PATCHLEVEL
	snprintf(lp_solve_Version+15, sizeof(lp_solve_Version)-15,
		"%.*s", (int)sizeof(lp_solve_Version)-16, PATCHLEVEL);
#else
	lp_solve_version(&i, &j, &j0, &j1);
	snprintf(lp_solve_Version+15, sizeof(lp_solve_Version)-15,
		"%d.%d.%d.%d", i, j, j0, j1);
#endif
	asl = ASL_alloc(ASL_read_f);
	stub = getstub(&argv, &Oinfo);
	if (!stub)
		usage_ASL(&Oinfo, 1);
	nl = jac0dim(stub, 0);
	SI = sos_add(nl,0);
	suf_declare(suftab, sizeof(suftab)/sizeof(SufDecl));

	/* set A_vals to get the constraints column-wise */
#if MAJORVERSION >= 5
	A_vals = (real *)M1alloc((1 + nzc)*sizeof(real));
	A_vals++;
	varstat = (int*)M1alloc((n_con + n_var)*sizeof(int));
	csd = suf_iput("sstatus", ASL_Sufkind_con, varstat);
	vsd = suf_iput("sstatus", ASL_Sufkind_var, varstat + n_con );
#else
	A_vals = (real *)M1alloc(nzc*sizeof(real));
#endif

	f_read(nl,0);

	sos_finish(&SI, 0, &j, 0, 0, 0, 0, 0);

	lp = make_lp(n_con, 0);

#if MAJORVERSION > 5 || (MAJORVERSION == 5 && MINORVERSION > 1)
        if (rparname != NULL)
          read_params(lp, rparname, rparoptions);
#endif

        set_verbose(lp, SEVERE);

	Oinfo.uinfo = (char *)lp;
	if (getopts(argv, &Oinfo))
		return 1;

        if (bb_rule != -1)
        	set_bb_rule(lp, (short) bb_rule);

        if (floor_first != -1)
                set_bb_floorfirst(lp, BRANCH_FLOOR);

        if (floor_first2 != -1)
                set_bb_floorfirst(lp, BRANCH_AUTOMATIC);

        if (debug != -1)
                set_debug(lp, TRUE);

        if (anti_degen != -1)
                set_anti_degen(lp, ANTIDEGEN_DEFAULT);
#if MAJORVERSION >= 5
        if (anti_degen2 != -1)
                set_anti_degen(lp, (short) anti_degen2);
#endif

        if (epsint >= 0)
                set_epsint(lp, epsint);

        if (improve >= 0)
                set_improve(lp, (short) improve);

        if (obj_bound != 1e99)
                set_obj_bound(lp, obj_bound);

        if (print_at_invert != -1)
                set_print_at_invert(lp, (short) print_at_invert);

        if (print_sol != -1)
                set_print_sol(lp, (short) print_sol);

        if (print_sol2 != -1)
                set_print_sol(lp, AUTOMATIC);

        if (trace != -1)
                set_trace(lp, (MYBOOL) trace);

        if (verbose != -1)
                set_verbose(lp, (short) NORMAL);

#if MAJORVERSION >= 4
        if (max_num_inv != -1)
                set_maxpivot(lp, max_num_inv);
#endif

#if MAJORVERSION >= 4
        if (pivoting != -1)
                set_pivoting(lp, pivoting);
#endif

#if MAJORVERSION >= 4
        if (presolve1)
                set_presolve(lp, presolve1
#if MAJORVERSION > 5 || (MAJORVERSION == 5 && MINORVERSION > 1)
                             , get_presolveloops(lp)
#endif
                            );
#endif

#if MAJORVERSION >= 5
        if (basiscrash != -1)
                set_basiscrash(lp, basiscrash);
#endif

#if MAJORVERSION >= 5
        if (preferdual != -1)
                set_preferdual(lp, (MYBOOL) preferdual);
#endif

#if MAJORVERSION >= 5
        if (simplextype)
                set_simplextype(lp, simplextype);
#endif

        if (epspivot != -1)
                set_epspivot(lp, epspivot);

        if (epsd != -1)
                set_epsd(lp, epsd);

        if (epsb != -1)
                set_epsb(lp, epsb);

        if (epsel != -1)
                set_epsel(lp, epsel);

#if MAJORVERSION >= 4
        if (epsp != -1)
                set_epsperturb(lp, epsp);
#endif

#if MAJORVERSION >= 4
        if (sectimeout)
                set_timeout(lp, sectimeout);
#endif

#if MAJORVERSION >= 5
        if (bfp != NULL)
                set_BFP(lp, bfp);
#endif

#if MAJORVERSION >= 4
        if (ga != -1)
                set_abs_mip_gap(lp, ga);
#endif

#if MAJORVERSION >= 5
        if (gr != -1)
                set_rel_mip_gap(lp, gr);
#endif

#if MAJORVERSION >= 4
        if (break_at_first)
                set_break_at_first(lp, TRUE);
#endif

#if MAJORVERSION >= 4
        if (break_at_value != -1)
                set_break_at_value(lp, break_at_value);
#endif

#if MAJORVERSION >= 5
        if (bb_maxlevel != -1)
                set_bb_depthlimit(lp, bb_maxlevel);
#endif

#if MAJORVERSION >= 5
        if (solutionlimit != -1)
                set_solutionlimit(lp, solutionlimit);
#endif

	i = n_var + n_con + 1;
	x = (real*)M1alloc(i*sizeof(real));	/* scratch vector */
	memset(x, 0, i*sizeof(real));
	x0 = x++;
	c = x + n_con;

	/* supply objective */

	objadj = 0;
	if (--nobj >= 0 && nobj < n_obj) {
		for(og = Ograd[nobj]; og; og = og->next)
			c[og->varno] = og->coef;
		if (objtype[nobj])
			set_maxim(lp);
		objadj = objconst(nobj);
		}

	/* supply columns and variable bounds */

	LU = LUv;
	intmin = n_var - (nbv + niv);
	j1 = nalt = 0;
	rshift = shift = 0;
#if MAJORVERSION >= 5
	/* Version 5 has its own handling of negative restrictions and splitting of negative variables
	   so all the hard stuf that was done in previous versions is not needed.
	   Also version 5 allows to provide the data as AMPL does, ie only the non-zero values
	   via add_columnex and this is faster than with add_column.
	   Another reason for changing this is for the starting base handling. Is much easier because
	   number of columns provided to lp_solve is equal to number of columns known by ampl.
	   The only two 'messy' things are that add_columnex uses the first element of the provided array
	   for the objective function value while AMPL keeps this data in a separate vector.
	   However this is solved by using the last element of the previous column and for safety it
	   is even restored again afterwards. Also the rownumbers are 1-indexed in lp_solve while in AMPL
	   they are 0-based */

	infinite = get_infinite(lp);
	A_rownos1 = (int*)M1alloc((1 + A_colstarts[n_var])*sizeof(int));
	for(i = A_colstarts[n_var]; i >= 1; i--)
	    A_rownos1[i] = A_rownos[i - 1] + 1;
	A_vals1 = A_vals - 1;
	for(i = 1; i <= n_var; i++, LU += 2) {
		lb = LU[0];
		ub = LU[1];
		if (lb <= negInfinity) /* AMPL's -infinity */
		    lb = -infinite;    /* to lp_solve's -infinity */
		if (ub >= Infinity)    /* AMPL's infinity */
		    ub = infinite;     /* to lp_solve's infinity */
		j0 = j1;
		j1 = A_colstarts[i];
		t = *A_vals1;
		*A_vals1 = *c++;	/* cost coefficient */
		k = *A_rownos1;
		*A_rownos1 = 0;
		add_columnex(lp, 1 + j1 - j0, A_vals1, A_rownos1);
		*A_rownos1 = k;
		*A_vals1 = t;
		A_rownos1 += j1 - j0;
		A_vals1 += j1 - j0;
		if (lb)
		    set_lowbo(lp, i, lb);
		if (ub < infinite)
		    set_upbo(lp, i, ub);
		if (i > intmin) {
		    set_int(lp, i, TRUE);
                    hasint = TRUE;
                }
	}
#else /* MAJORVERSION < 5 */
	for(i = 1; i <= n_var; i++, LU += 2) {
		lb = LU[0];
		ub = LU[1];
		j0 = j1;
		j1 = A_colstarts[i];
		*x0 = *c++;	/* cost coefficient */
		if (lb <= negInfinity && ub < Infinity) {
			/* negate this variable */
			nalt++;
			lb = -ub;
			ub = -LU[0];
			for(j = j0; j < j1; j++)
				x[A_rownos[j]] = -A_vals[j];
			*x0 = -*x0;
			add_column(lp, x0);
			if (lb)
				goto shift_check;
			}
		else {
			for(j = j0; j < j1; j++)
				x[A_rownos[j]] = A_vals[j];
			add_column(lp, x0);
			if (lb <= negInfinity) {
				nalt++;
				if (i > intmin) {
					set_int(lp, get_Ncolumns(lp), TRUE);
                                        hasint = TRUE;
                                }
				/* split free variable */
				*x0 = -*x0;
				for(j = j0; j < j1; j++)
					x[A_rownos[j]] *= -1.;
				add_column(lp,x0);
				}
			else if (lb) {
 shift_check:
				if (lb > 0)
					set_lowbo(lp, get_Ncolumns(lp), lb);
				else {
					if (!rshift) {
						rshift = (real*)M1zapalloc(
						  (n_var+n_con)*sizeof(real));
						shift = rshift + n_con - 1;
						}
					shift[i] = lb;
					for(j = j0; j < j1; j++) {
						k = A_rownos[j];
						rshift[k] += lb*x[k];
						}
					if (ub < Infinity)
						ub -= lb;
					objadj += lb**x0;
					}
				}
			if (ub < Infinity)
				set_upbo(lp, get_Ncolumns(lp), ub);
			}
		for(j = j0; j < j1; j++)
			x[A_rownos[j]] = 0;
		if (i > intmin) {
			set_int(lp, get_Ncolumns(lp), TRUE);
                        hasint = TRUE;
                }
		}
#endif

	if (objadj) {
#if MAJORVERSION >= 4
	        /* don't need an extra column for that! */
	        /* also makes it easier for setting a base */
		set_rh(lp, 0, objadj);
#else
	        /* add a fixed variable to adjust the objective value */
		*x0 = objadj;
		add_column(lp, x0);
		set_lowbo(lp, i, 1.);
		set_upbo(lp, i, 1.);
#endif
		}

	/* supply constraint rhs */

	LU = LUrhs;
	for(i = 1; i <= n_con; i++, LU += 2) {
		t = LU[0];
		if (t == LU[1])
			ct = EQ;
		else if (t <= negInfinity) {
			t = LU[1];
			ct = LE;
			if (t >= Infinity) {
#if MAJORVERSION >= 5
				ct = FR;
				t = 0;
#else
				/* This is possible only with effort: */
				/* one must turn presolve off and */
				/* explicitly specify a constraint */
				/* with infinite bounds. */
				fprintf(Stderr,
					"Sorry, can't handle free rows.\n");
				exit(1);
#endif
				}
			}
		else
			ct = GE;
		set_rh(lp, i, rshift ? t - *rshift++ : t);
		set_constr_type(lp, i, (short) ct);
		if (ct == GE && LU[1] < Infinity)
			set_rh_range(lp, i, LU[1] - t);
		}

	if (prlp)
		print_lp(lp);

        if (printsol >= 5)
          	print_lp(lp);

	if ((scaling) || (scalemode != -1)) {
                if (scalemode == -1)
                        scalemode = def_scalemode;
		set_scaling(lp, (short) scalemode);
		auto_scale(lp);
		}

        if(!write_model_after)
          	write_model(lp, wlp, wmps, wfmps, wxli, wxliname, wxlioptions);

        if ((parse_only) && (write_model_after) && (!sectimeout))
        	sectimeout = 1;

#if MAJORVERSION >= 5
	/* version 5 can provide a starting base ... so let's do that, if allowed */
	bascolumn = (int*)M1alloc((1 + n_con + n_var)*sizeof(int));
        *bascolumn = 0;

#if DEBUGSTARTBASE >= 1
	printf("ASL_Sufkind_input: %d, %d\n", csd->kind & ASL_Sufkind_input, vsd->kind & ASL_Sufkind_input);
#endif

	if((!coldstart) && (csd->kind & ASL_Sufkind_input) && (vsd->kind & ASL_Sufkind_input)) {
#if DEBUGSTARTBASE >= 1
		printf("starting base constraints: %d\n", n_con);
		printf("starting base variables: %d\n", n_var);
#endif
#if DEBUGSTARTBASE >= 2
		printf("varstat in:\n");
		for (j=0; j < n_con + n_var; j++)
		    printf("%d\n", varstat[j]);
#endif

                j = 0;
                k = n_con;
		ret = TRUE;
                for (i = 0; (i < n_con + n_var) && (ret); i++)
		    switch (varstat[i]) {
                    case 0: /* no status assigned */
                        if (i < n_con)
                            if (j >= n_con)
    				ret = FALSE;
    			    else
    				bascolumn[++j] = -(i + 1);
			else
                            if (k >= n_con + n_var)
    				ret = FALSE;
    			    else
    				bascolumn[++k] = -(i + 1);
                        break;
		    case 1: /* basic */
		    case 2: /* super basic */
			if (j >= n_con)
			    ret = FALSE;
			else
			    bascolumn[++j] = -(i + 1);
			break;
		    case 3: /* non basic lower bound */
		    case 5: /* non basic at equal lower and upper bound */
		    case 6: /* non basic between bounds */
			if (k >= n_con + n_var)
			    ret = FALSE;
			else
			    bascolumn[++k] = -(i + 1);
                        break;
		    case 4: /* non basic upper bound */
			if (k >= n_con + n_var)
			    ret = FALSE;
			else
			    bascolumn[++k] = +(i + 1);
			break;
		    }

		if (ret)
		    ret = set_basis(lp, bascolumn, TRUE);
		else
		    ret = -1;

#if DEBUGSTARTBASE >= 1
		printf("n_con + n_var = %d\n", n_con + n_var);
		printf("set_basis: %d\n", ret);
#endif
#if DEBUGSTARTBASE >= 2
		for (j=1; j<= n_con + n_var; j++)
		    printf("%d\n", bascolumn[j]);
#endif
	}
#else /* MAJORVERSION < 5 */
	/* Unfortunately, there seems to be no way to suggest */
	/* a starting basis to lp_solve; thus we must ignore  */
	/* any incoming .sstatus values. */
#endif

#if MAJORVERSION > 5 || (MAJORVERSION == 5 && MINORVERSION > 1)
        if (wparname != NULL)
          write_params(lp, wparname, wparoptions);
#endif

        if ((!parse_only) || (write_model_after)) {
#if MAJORVERSION >= 4
  		if(sectimeout>0)
    			set_timeout(lp, sectimeout);
#endif
#if MAJORVERSION >= 5
		put_msgfunc(lp, msgfunction, NULL, MSG_LPOPTIMAL);
#endif
          	rc = solve(lp);
        }

        if (parse_only)
                rc = -1;
        else {
        	if (printsol >= 6)
    			print_scales(lp);
        }

        if(write_model_after)
    		write_model(lp, wlp, wmps, wfmps, wxli, wxliname, wxlioptions);

        switch (rc) {
        case OPTIMAL:
#if defined FEASFOUND
        case FEASFOUND:
#endif
                rc = 0;

#if MAJORVERSION >= 4
                if (printsol >= 1)
                  	print_objective(lp);
#endif

                if (printsol >= 2)
                  	print_solution1(lp);

#if MAJORVERSION >= 4
                if (printsol >= 3)
                  	print_constraints1(lp);
#endif

                if (printsol >= 4)
                  	print_duals(lp);
                break;
        case MILP_FAIL:
                rc = 1;
                break;
        case INFEASIBLE:
#if defined NOFEASFOUND
        case NOFEASFOUND:
#endif
                rc = 2;
                break;
        case UNBOUNDED:
                rc = 3;
                break;
        case FAILURE:
                rc = 4;
                break;
#if defined SUBOPTIMAL
        case SUBOPTIMAL:
                rc = 6;
                break;
#endif
        default:
                rc = 5;
                break;
        }

#if MAJORVERSION >= 4
        if ((!parse_only) && (printsol >= 7))
      		print_tableau(lp);
#endif

	solve_result_num = solinfo[rc].code;
	i = sprintf(buf, "%s: %s", Oinfo.bsname, solinfo[rc].msg);
	if (rc == 0)
		i += sprintf(buf+i, ", objective %.*g", obj_prec(),
			get_objective(lp));
        if (!parse_only) {
  		i += sprintf(buf+i,"\n%d simplex iterations", (long)get_total_iter(lp));
		if (get_max_level(lp) > 1 || get_total_nodes(lp) > 1)
			sprintf(buf+i, "\n%d branch & bound nodes: depth %d",
				(int)get_total_nodes(lp), get_max_level(lp));

        	/* Prepare to report solution: deal with split free variables. */

                get_ptr_primal_solution(lp, &x1);
                x1 += lp->rows+1;
        	if (nalt || shift) {
        		x = x0;
        		LU = LUv;
        		for(i = 0; i < n_var; i++, LU += 2) {
        			if (LU[0] > negInfinity)
        				x[i] = *x1++;
        			else if (LU[1] < Infinity)
        				x[i] = -*x1++;
        			else {
        				x[i] = x1[0] - x1[1];
        				x1 += 2;
        				}
        			if (shift)
        				x[i] += *++shift;
        			}
        		}
        	else
        		x = x1;

#if DEBUGSTARTBASE >= 1
		printf("solinfo[rc].code = %d\n", solinfo[rc].code);
#endif

        	if (solinfo[rc].code < 500
#if MAJORVERSION >= 5
                    /* version 5+ can also provide a base when there are integers */
#else
                    /* older versions can't provide a base when there are integers */
                    && !(nbv + niv)
#endif
                   ) {
        		/* return .sstatus values */

#if MAJORVERSION >= 5
			/* basis already returned in bascolumn via message function if there are integer
			   variables. Is so if *bascolumn is TRUE. In the other case, call get_basis */
			if (*bascolumn == 0)
			    if (get_basis(lp, bascolumn, TRUE))
                                *bascolumn = 1;
                            else
                                *bascolumn = -1;
                        if (*bascolumn == 1) {
#if DEBUGSTARTBASE >= 2
                            printf("get_basis:\n");
    			    for (i = 1; i <= n_con + n_var; i++)
    				printf("%d\n", bascolumn[i]);
#endif
    			    for (i = 1; i <= n_con; i++)
    				varstat[abs(*(++bascolumn)) - 1] = 1; /* basic */
    			    for (i = 1; i <= n_var; i++)
    				varstat[abs(bascolumn[i]) - 1] = bascolumn[i] < 0 ? 3 : 4; /* non basic */
                        }
                        else
                            memset(varstat, 0, (n_con + n_var) * sizeof(*varstat));

#else /* MAJORVERSION < 5 */
		        /* the messy way */
#if DEBUGSTARTBASE >= 2
			int *varstat;
#endif

#if MAJORVERSION >= 5
                        basis = lp->is_basic;
        		lower = lp->is_lower;
#else
        		basis = lp->basis;
        		lower = lp->lower;
#endif
        		is = M1alloc((n_var + n_con)*sizeof(int));
#if DEBUGSTARTBASE >= 2
			varstat=is;
#endif
        		suf_iput("sstatus", ASL_Sufkind_con, is);
        		for(i = 0; i < n_con; i++) {
        			j = *++lower;
        			*is++ = *++basis ? 1 : j ? 3 : 4;
        			}
        		suf_iput("sstatus", ASL_Sufkind_var, is);
        		LU = LUv;
        		for(i = 0; i < n_var; i++, LU += 2) {
        			j0 = *++basis;
        			j1 = *++lower;
        			if (LU[0] > negInfinity)
        				j = j0 ? 1 : j1 ? 3 : 4;
        			else if (LU[1] < Infinity)
        				j = j0 ? 1 : j1 ? 4 : 3;
        			else {
        				++lower;
        				j = *++basis || j0;
        				}
        			*is++ = j;
        			}
#endif

#if DEBUGSTARTBASE >= 2
			printf("varstat out:\n");
			for (i = 0; i < n_var + n_con; i++)
			    printf("%d\n",varstat[i]);
#endif
        	}

                if(!hasint)
                    get_ptr_dual_solution(lp, &x1);
                else
                    x1 = NULL;
        	write_sol(buf, x, (x1 != NULL) ? x1+1 : NULL, &Oinfo);
        }
        else
                write_sol(buf, NULL, NULL, &Oinfo);

	/* The following calls would only be needed */
	/* if execution were to continue... */
	delete_lp(lp);
	ASL_free(&asl);
	return 0;
	}
