#define LPSOLVEAPIFROMLIB

#include "lp_explicit.h"

static hlpsolve lpsolve = NULL;

#if defined WIN32
#  define lpsolvelib "lpsolve55.dll"
#else
#  define lpsolvelib "liblpsolve55.so"
#endif

int init_lpsolve_lib()
{
  int ret = 1;

  if (lpsolve == NULL) {
    ret = 0;
    if ((lpsolve = open_lpsolve_lib(lpsolvelib)) != NULL)
      ret = init_lpsolve(lpsolve);
  }
  return(ret);
}

void exit_lpsolve_lib()
{
  if (lpsolve != NULL) {
    close_lpsolve_lib(lpsolve);
    lpsolve = NULL;
  }
}

MYBOOL __add_column(lprec *lp, REAL *column)
{
  return(_add_column(lp, column));
}

MYBOOL __add_columnex(lprec *lp, int count, REAL *column, int *rowno)
{
  return(_add_columnex(lp, count, column, rowno));
}

MYBOOL __add_constraint(lprec *lp, REAL *row, int constr_type, REAL rh)
{
  return(_add_constraint(lp, row, constr_type, rh));
}

MYBOOL __add_constraintex(lprec *lp, int count, REAL *row, int *colno, int constr_type, REAL rh)
{
  return(_add_constraintex(lp, count, row, colno, constr_type, rh));
}

MYBOOL __add_lag_con(lprec *lp, REAL *row, int con_type, REAL rhs)
{
  return(_add_lag_con(lp, row, con_type, rhs));
}

int __add_SOS(lprec *lp, char *name, int sostype, int priority, int count, int *sosvars, REAL *weights)
{
  return(_add_SOS(lp, name, sostype, priority, count, sosvars, weights));
}

int __column_in_lp(lprec *lp, REAL *column)
{
  return(_column_in_lp(lp, column));
}

lprec *__copy_lp(lprec *lp)
{
  return(copy_lp(lp));
}

void __default_basis(lprec *lp)
{
  default_basis(lp);
}

MYBOOL __del_column(lprec *lp, int column)
{
  return(_del_column(lp, column));
}

MYBOOL __del_constraint(lprec *lp,int del_row)
{
  return(_del_constraint(lp,del_row));
}

void __delete_lp(lprec *lp)
{
  delete_lp(lp);
}

MYBOOL __dualize_lp(lprec *lp)
{
  return(dualize_lp(lp));
}

void __free_lp(lprec **plp)
{
  free_lp(plp);
}

int __get_anti_degen(lprec *lp)
{
  return(_get_anti_degen(lp));
}

MYBOOL __get_basis(lprec *lp, int *bascolumn, MYBOOL nonbasic)
{
  return(get_basis(lp, bascolumn, nonbasic));
}

int __get_basiscrash(lprec *lp)
{
  return(_get_basiscrash(lp));
}

int __get_bb_depthlimit(lprec *lp)
{
  return(_get_bb_depthlimit(lp));
}

int __get_bb_floorfirst(lprec *lp)
{
  return(_get_bb_floorfirst(lp));
}

int __get_bb_rule(lprec *lp)
{
  return(_get_bb_rule(lp));
}

MYBOOL __get_bounds_tighter(lprec *lp)
{
  return(_get_bounds_tighter(lp));
}

REAL __get_break_at_value(lprec *lp)
{
  return(_get_break_at_value(lp));
}

REAL __get_accuracy(lprec *lp)
{
  return(_get_accuracy(lp));
}

REAL __get_break_numeric_accuracy(lprec *lp)
{
  return(_get_break_numeric_accuracy(lp));
}

char *__get_col_name(lprec *lp, int column)
{
  return(_get_col_name(lp, column));
}

MYBOOL __get_column(lprec *lp, int col_nr, REAL *column)
{
  return(_get_column(lp, col_nr, column));
}

MYBOOL __get_columnex(lprec *lp, int col_nr, REAL *column, int *nzrow)
{
  return(_get_columnex(lp, col_nr, column, nzrow));
}

int __get_constr_type(lprec *lp, int row)
{
  return(_get_constr_type(lp, row));
}

REAL __get_constr_value(lprec *lp, int row, int count, REAL *primsolution, int *nzindex)
{
  return(_get_constr_value(lp, row, count, primsolution, nzindex));
}

MYBOOL __get_constraints(lprec *lp, REAL *constr)
{
  return(_get_constraints(lp, constr));
}

MYBOOL __get_dual_solution(lprec *lp, REAL *rc)
{
  return(_get_dual_solution(lp, rc));
}

REAL __get_epsb(lprec *lp)
{
  return(_get_epsb(lp));
}

REAL __get_epsd(lprec *lp)
{
  return(_get_epsd(lp));
}

REAL __get_epsel(lprec *lp)
{
  return(_get_epsel(lp));
}

REAL __get_epsint(lprec *lp)
{
  return(_get_epsint(lp));
}

REAL __get_epsperturb(lprec *lp)
{
  return(_get_epsperturb(lp));
}

REAL __get_epspivot(lprec *lp)
{
  return(_get_epspivot(lp));
}

int __get_improve(lprec *lp)
{
  return(_get_improve(lp));
}

REAL __get_infinite(lprec *lp)
{
  return(_get_infinite(lp));
}

MYBOOL __get_lambda(lprec *lp, REAL *lambda)
{
  return(_get_lambda(lp, lambda));
}

REAL __get_lowbo(lprec *lp, int column)
{
  return(_get_lowbo(lp, column));
}

int __get_lp_index(lprec *lp, int orig_index)
{
  return(_get_lp_index(lp, orig_index));
}

char *__get_lp_name(lprec *lp)
{
  return(_get_lp_name(lp));
}

int __get_Lrows(lprec *lp)
{
  return(_get_Lrows(lp));
}

REAL __get_mat(lprec *lp, int row, int column)
{
  return(_get_mat(lp, row, column));
}

int __get_max_level(lprec *lp)
{
  return(_get_max_level(lp));
}

int __get_maxpivot(lprec *lp)
{
  return(_get_maxpivot(lp));
}

REAL __get_mip_gap(lprec *lp, MYBOOL absolute)
{
  return(_get_mip_gap(lp, absolute));
}

int __get_nameindex(lprec *lp, char *name, MYBOOL isrow)
{
  return(_get_nameindex(lp, name, isrow));
}

int __get_Ncolumns(lprec *lp)
{
  return(_get_Ncolumns(lp));
}

REAL __get_negrange(lprec *lp)
{
  return(_get_negrange(lp));
}

REAL __get_nonzeros(lprec *lp)
{
  return(_get_nonzeros(lp));
}

int __get_Norig_columns(lprec *lp)
{
  return(_get_Norig_columns(lp));
}

int __get_Norig_rows(lprec *lp)
{
  return(_get_Norig_rows(lp));
}

int __get_Nrows(lprec *lp)
{
  return(_get_Nrows(lp));
}

REAL __get_obj_bound(lprec *lp)
{
  return(_get_obj_bound(lp));
}

REAL __get_objective(lprec *lp)
{
  return(_get_objective(lp));
}

int __get_orig_index(lprec *lp, int lp_index)
{
  return(_get_orig_index(lp, lp_index));
}

char *__get_origcol_name(lprec *lp, int column)
{
  return(_get_origcol_name(lp, column));
}

char *__get_origrow_name(lprec *lp, int row)
{
  return(_get_origrow_name(lp, row));
}

int __get_pivoting(lprec *lp)
{
  return(_get_pivoting(lp));
}

int __get_presolve(lprec *lp)
{
  return(_get_presolve(lp));
}

int __get_presolveloops(lprec *lp)
{
  return(_get_presolveloops(lp));
}

MYBOOL __get_primal_solution(lprec *lp, REAL *pv)
{
  return(_get_primal_solution(lp, pv));
}

int __get_print_sol(lprec *lp)
{
  return(_get_print_sol(lp));
}

MYBOOL __get_ptr_constraints(lprec *lp, REAL **constr)
{
  return(_get_ptr_constraints(lp, constr));
}

MYBOOL __get_ptr_dual_solution(lprec *lp, REAL **rc)
{
  return(_get_ptr_dual_solution(lp, rc));
}

MYBOOL __get_ptr_lambda(lprec *lp, REAL **lambda)
{
  return(_get_ptr_lambda(lp, lambda));
}

MYBOOL __get_ptr_primal_solution(lprec *lp, REAL **pv)
{
  return(_get_ptr_primal_solution(lp, pv));
}

MYBOOL __get_ptr_sensitivity_obj(lprec *lp, REAL **objfrom, REAL **objtill)
{
  return(_get_ptr_sensitivity_obj(lp, objfrom, objtill));
}

MYBOOL __get_ptr_sensitivity_objex(lprec *lp, REAL **objfrom, REAL **objtill, REAL **objfromvalue, REAL **objtillvalue)
{
  return(_get_ptr_sensitivity_objex(lp, objfrom, objtill, objfromvalue, objtillvalue));
}

MYBOOL __get_ptr_sensitivity_rhs(lprec *lp, REAL **duals, REAL **dualsfrom, REAL **dualstill)
{
  return(_get_ptr_sensitivity_rhs(lp, duals, dualsfrom, dualstill));
}

MYBOOL __get_ptr_variables(lprec *lp, REAL **var)
{
  return(_get_ptr_variables(lp, var));
}

REAL __get_rh(lprec *lp, int row)
{
  return(_get_rh(lp, row));
}

REAL __get_rh_range(lprec *lp, int row)
{
  return(_get_rh_range(lp, row));
}

MYBOOL __get_row(lprec *lp, int row_nr, REAL *row)
{
  return(_get_row(lp, row_nr, row));
}

MYBOOL __get_rowex(lprec *lp, int row_nr, REAL *row, int *colno)
{
  return(_get_rowex(lp, row_nr, row, colno));
}

char *__get_row_name(lprec *lp, int row)
{
  return(_get_row_name(lp, row));
}

REAL __get_scalelimit(lprec *lp)
{
  return(_get_scalelimit(lp));
}

int __get_scaling(lprec *lp)
{
  return(_get_scaling(lp));
}

MYBOOL __get_sensitivity_obj(lprec *lp, REAL *objfrom, REAL *objtill)
{
  return(_get_sensitivity_obj(lp, objfrom, objtill));
}

MYBOOL __get_sensitivity_objex(lprec *lp, REAL *objfrom, REAL *objtill, REAL *objfromvalue, REAL *objtillvalue)
{
  return(_get_sensitivity_objex(lp, objfrom, objtill, objfromvalue, objtillvalue));
}

MYBOOL __get_sensitivity_rhs(lprec *lp, REAL *duals, REAL *dualsfrom, REAL *dualstill)
{
  return(_get_sensitivity_rhs(lp, duals, dualsfrom, dualstill));
}

int __get_simplextype(lprec *lp)
{
  return(_get_simplextype(lp));
}

int __get_solutioncount(lprec *lp)
{
  return(_get_solutioncount(lp));
}

int __get_solutionlimit(lprec *lp)
{
  return(_get_solutionlimit(lp));
}

int __get_status(lprec *lp)
{
  return(_get_status(lp));
}

char *__get_statustext(lprec *lp, int statuscode)
{
  return(_get_statustext(lp, statuscode));
}

long __get_timeout(lprec *lp)
{
  return(_get_timeout(lp));
}

int __get_total_iter(lprec *lp)
{
  return(_get_total_iter(lp));
}

int __get_total_nodes(lprec *lp)
{
  return(_get_total_nodes(lp));
}

REAL __get_upbo(lprec *lp, int column)
{
  return(_get_upbo(lp, column));
}

int __get_var_branch(lprec *lp, int column)
{
  return(_get_var_branch(lp, column));
}

REAL __get_var_dualresult(lprec *lp, int index)
{
  return(_get_var_dualresult(lp, index));
}

REAL __get_var_primalresult(lprec *lp, int index)
{
  return(_get_var_primalresult(lp, index));
}

int __get_var_priority(lprec *lp, int column)
{
  return(_get_var_priority(lp, column));
}

MYBOOL __get_variables(lprec *lp, REAL *var)
{
  return(_get_variables(lp, var));
}

int __get_verbose(lprec *lp)
{
  return(_get_verbose(lp));
}

REAL __get_working_objective(lprec *lp)
{
  return(_get_working_objective(lp));
}

MYBOOL __guess_basis(lprec *lp, REAL *guessvector, int *basisvector)
{
  return(_guess_basis(lp, guessvector, basisvector));
}

MYBOOL __has_BFP(lprec *lp)
{
  return(_has_BFP(lp));
}

MYBOOL __has_XLI(lprec *lp)
{
  return(_has_XLI(lp));
}

MYBOOL __is_add_rowmode(lprec *lp)
{
  return(_is_add_rowmode(lp));
}

MYBOOL __is_anti_degen(lprec *lp, int testmask)
{
  return(_is_anti_degen(lp, testmask));
}

MYBOOL __is_binary(lprec *lp, int column)
{
  return(_is_binary(lp, column));
}

MYBOOL __is_break_at_first(lprec *lp)
{
  return(_is_break_at_first(lp));
}

MYBOOL __is_constr_type(lprec *lp, int row, int mask)
{
  return(_is_constr_type(lp, row, mask));
}

MYBOOL __is_debug(lprec *lp)
{
  return(_is_debug(lp));
}

MYBOOL __is_feasible(lprec *lp, REAL *values, REAL threshold)
{
  return(_is_feasible(lp, values, threshold));
}

MYBOOL __is_unbounded(lprec *lp, int column)
{
  return(_is_unbounded(lp, column));
}

MYBOOL __is_infinite(lprec *lp, REAL value)
{
  return(_is_infinite(lp, value));
}

MYBOOL __is_int(lprec *lp, int column)
{
  return(_is_int(lp, column));
}

MYBOOL __is_integerscaling(lprec *lp)
{
  return(_is_integerscaling(lp));
}

MYBOOL __is_lag_trace(lprec *lp)
{
  return(_is_lag_trace(lp));
}

MYBOOL __is_maxim(lprec *lp)
{
  return(_is_maxim(lp));
}

MYBOOL __is_nativeBFP(lprec *lp)
{
  return(_is_nativeBFP(lp));
}

MYBOOL __is_nativeXLI(lprec *lp)
{
  return(_is_nativeXLI(lp));
}

MYBOOL __is_negative(lprec *lp, int column)
{
  return(_is_negative(lp, column));
}

MYBOOL __is_piv_mode(lprec *lp, int testmask)
{
  return(_is_piv_mode(lp, testmask));
}

MYBOOL __is_piv_rule(lprec *lp, int rule)
{
  return(_is_piv_rule(lp, rule));
}

MYBOOL __is_presolve(lprec *lp, int testmask)
{
  return(_is_presolve(lp, testmask));
}

MYBOOL __is_scalemode(lprec *lp, int testmask)
{
  return(_is_scalemode(lp, testmask));
}

MYBOOL __is_scaletype(lprec *lp, int scaletype)
{
  return(_is_scaletype(lp, scaletype));
}

MYBOOL __is_semicont(lprec *lp, int column)
{
  return(_is_semicont(lp, column));
}

MYBOOL __is_SOS_var(lprec *lp, int column)
{
  return(_is_SOS_var(lp, column));
}

MYBOOL __is_trace(lprec *lp)
{
  return(_is_trace(lp));
}

MYBOOL __is_use_names(lprec *lp, MYBOOL isrow)
{
  return(_is_use_names(lp, isrow));
}

void __lp_solve_version(int *majorversion, int *minorversion, int *release, int *build)
{
  lp_solve_version(majorversion, minorversion, release, build);
}

lprec *__make_lp(int rows, int columns)
{
  return(_make_lp(rows, columns));
}

void __print_constraints(lprec *lp, int columns)
{
  print_constraints(lp, columns);
}

MYBOOL __print_debugdump(lprec *lp, char *filename)
{
  return(_print_debugdump(lp, filename));
}

void __print_duals(lprec *lp)
{
  print_duals(lp);
}

void __print_lp(lprec *lp)
{
  print_lp(lp);
}

void __print_objective(lprec *lp)
{
  print_objective(lp);
}

void __print_scales(lprec *lp)
{
  print_scales(lp);
}

void __print_solution(lprec *lp, int columns)
{
  print_solution(lp, columns);
}

void __print_str(lprec *lp, char *str)
{
  print_str(lp, str);
}

void __print_tableau(lprec *lp)
{
  print_tableau(lp);
}

void __put_abortfunc(lprec *lp, lphandle_intfunc newctrlc, void *ctrlchandle)
{
  put_abortfunc(lp, newctrlc, ctrlchandle);
}

void __put_logfunc(lprec *lp, lphandlestr_func newlog, void *loghandle)
{
  put_logfunc(lp, newlog, loghandle);
}

void __put_msgfunc(lprec *lp, lphandleint_func newmsg, void *msghandle, int mask)
{
  put_msgfunc(lp, newmsg, msghandle, mask);
}

MYBOOL __read_basis(lprec *lp, char *filename, char *info)
{
  return(_read_basis(lp, filename, info));
}

lprec *__read_LP(char *filename, int verbose, char *lp_name)
{
  return(_read_LP(filename, verbose, lp_name));
}

lprec *__read_lp(FILE *filename, int verbose, char *lp_name)
{
  return(_read_lp(filename, verbose, lp_name));
}

lprec *__read_MPS(char *filename, int options)
{
  return(_read_MPS(filename, options));
}

lprec *__read_mps(FILE *filename, int options)
{
  return(_read_mps(filename, options));
}

lprec *__read_freeMPS(char *filename, int options)
{
  return(_read_freeMPS(filename, options));
}

lprec *__read_freemps(FILE *filename, int options)
{
  return(_read_freemps(filename, options));
}

MYBOOL __read_params(lprec *lp, char *filename, char *options)
{
  return(_read_params(lp, filename, options));
}

lprec *__read_XLI(char *xliname, char *modelname, char *dataname, char *options, int verbose)
{
  return(_read_XLI(xliname, modelname, dataname, options, verbose));
}

void __reset_basis(lprec *lp)
{
  reset_basis(lp);
}

void __reset_params(lprec *lp)
{
  reset_params(lp);
}

MYBOOL __resize_lp(lprec *lp, int rows, int columns)
{
  return(_resize_lp(lp, rows, columns));
}

MYBOOL __set_add_rowmode(lprec *lp, MYBOOL turnon)
{
  return(_set_add_rowmode(lp, turnon));
}

void __set_anti_degen(lprec *lp, int anti_degen)
{
  set_anti_degen(lp, anti_degen);
}

MYBOOL __set_basis(lprec *lp, int *bascolumn, MYBOOL nonbasic)
{
  return(_set_basis(lp, bascolumn, nonbasic));
}

void __set_basiscrash(lprec *lp, int mode)
{
  set_basiscrash(lp, mode);
}

void __set_basisvar(lprec *lp, int basisPos, int enteringCol)
{
  set_basisvar(lp, basisPos, enteringCol);
}

void __set_bb_depthlimit(lprec *lp, int bb_maxlevel)
{
  set_bb_depthlimit(lp, bb_maxlevel);
}

void __set_bb_floorfirst(lprec *lp, int bb_floorfirst)
{
  set_bb_floorfirst(lp, bb_floorfirst);
}

void __set_bb_rule(lprec *lp, int bb_rule)
{
  set_bb_rule(lp, bb_rule);
}

MYBOOL __set_BFP(lprec *lp, char *filename)
{
  return(_set_BFP(lp, filename));
}

MYBOOL __set_binary(lprec *lp, int column, MYBOOL must_be_bin)
{
  return(_set_binary(lp, column, must_be_bin));
}

MYBOOL __set_bounds(lprec *lp, int column, REAL lower, REAL upper)
{
  return(_set_bounds(lp, column, lower, upper));
}

void __set_bounds_tighter(lprec *lp, MYBOOL tighten)
{
  set_bounds_tighter(lp, tighten);
}

void __set_break_at_first(lprec *lp, MYBOOL break_at_first)
{
  set_break_at_first(lp, break_at_first);
}

void __set_break_at_value(lprec *lp, REAL break_at_value)
{
  set_break_at_value(lp, break_at_value);
}

MYBOOL __set_column(lprec *lp, int col_no, REAL *column)
{
  return(_set_column(lp, col_no, column));
}

MYBOOL __set_columnex(lprec *lp, int col_no, int count, REAL *column, int *rowno)
{
  return(_set_columnex(lp, col_no, count, column, rowno));
}

MYBOOL __set_col_name(lprec *lp, int column, char *new_name)
{
  return(_set_col_name(lp, column, new_name));
}

MYBOOL __set_constr_type(lprec *lp, int row, int con_type)
{
  return(_set_constr_type(lp, row, con_type));
}

void __set_debug(lprec *lp, MYBOOL debug)
{
  set_debug(lp, debug);
}

void __set_epsb(lprec *lp, REAL epsb)
{
  set_epsb(lp, epsb);
}

void __set_epsd(lprec *lp, REAL epsd)
{
  set_epsd(lp, epsd);
}

void __set_epsel(lprec *lp, REAL epsel)
{
  set_epsel(lp, epsel);
}

void __set_epsint(lprec *lp, REAL epsint)
{
  set_epsint(lp, epsint);
}

void __set_epsperturb(lprec *lp, REAL epsperturb)
{
  set_epsperturb(lp, epsperturb);
}

void __set_epspivot(lprec *lp, REAL epspivot)
{
  set_epspivot(lp, epspivot);
}

MYBOOL __set_epslevel(lprec *lp, int epslevel)
{
  return(set_epslevel(lp, epslevel));
}

MYBOOL __set_unbounded(lprec *lp, int column)
{
  return(_set_unbounded(lp, column));
}

void __set_improve(lprec *lp, int improve)
{
  set_improve(lp, improve);
}

void __set_infinite(lprec *lp, REAL infinite)
{
  set_infinite(lp, infinite);
}

MYBOOL __set_int(lprec *lp, int column, MYBOOL must_be_int)
{
  return(_set_int(lp, column, must_be_int));
}

void __set_lag_trace(lprec *lp, MYBOOL lag_trace)
{
  set_lag_trace(lp, lag_trace);
}

MYBOOL __set_lowbo(lprec *lp, int column, REAL value)
{
  return(_set_lowbo(lp, column, value));
}

MYBOOL __set_lp_name(lprec *lp, char *lpname)
{
  return(_set_lp_name(lp, lpname));
}

MYBOOL __set_mat(lprec *lp, int row, int column, REAL value)
{
  return(_set_mat(lp, row, column, value));
}

void __set_maxim(lprec *lp)
{
  set_maxim(lp);
}

void __set_maxpivot(lprec *lp, int max_num_inv)
{
  set_maxpivot(lp, max_num_inv);
}

void __set_minim(lprec *lp)
{
  set_minim(lp);
}

void __set_mip_gap(lprec *lp, MYBOOL absolute, REAL mip_gap)
{
  set_mip_gap(lp, absolute, mip_gap);
}

void __set_negrange(lprec *lp, REAL negrange)
{
  set_negrange(lp, negrange);
}

MYBOOL __set_obj(lprec *lp, int Column, REAL Value)
{
  return(_set_obj(lp, Column, Value));
}

void __set_obj_bound(lprec *lp, REAL obj_bound)
{
  set_obj_bound(lp, obj_bound);
}

MYBOOL __set_obj_fn(lprec *lp, REAL *row)
{
  return(_set_obj_fn(lp, row));
}

MYBOOL __set_obj_fnex(lprec *lp, int count, REAL *row, int *colno)
{
  return(_set_obj_fnex(lp, count, row, colno));
}

MYBOOL __set_outputfile(lprec *lp, char *filename)
{
  return(_set_outputfile(lp, filename));
}

void __set_outputstream(lprec *lp, FILE *stream)
{
  set_outputstream(lp, stream);
}

void __set_pivoting(lprec *lp, int piv_rule)
{
  set_pivoting(lp, piv_rule);
}

void __set_preferdual(lprec *lp, MYBOOL dodual)
{
  set_preferdual(lp, dodual);
}

void __set_presolve(lprec *lp, int do_presolve, int maxloops)
{
  set_presolve(lp, do_presolve, maxloops);
}

void __set_print_sol(lprec *lp, int print_sol)
{
  set_print_sol(lp, print_sol);
}

MYBOOL __set_rh(lprec *lp, int row, REAL value)
{
  return(_set_rh(lp, row, value));
}

MYBOOL __set_rh_range(lprec *lp, int row, REAL deltavalue)
{
  return(_set_rh_range(lp, row, deltavalue));
}

void __set_rh_vec(lprec *lp, REAL *rh)
{
  set_rh_vec(lp, rh);
}

MYBOOL __set_row(lprec *lp, int row_no, REAL *row)
{
  return(_set_row(lp, row_no, row));
}

MYBOOL __set_rowex(lprec *lp, int row_no, int count, REAL *row, int *colno)
{
  return(_set_rowex(lp, row_no, count, row, colno));
}

MYBOOL __set_row_name(lprec *lp, int row, char *new_name)
{
  return(_set_row_name(lp, row, new_name));
}

void __set_scalelimit(lprec *lp, REAL scalelimit)
{
  set_scalelimit(lp, scalelimit);
}

void __set_scaling(lprec *lp, int scalemode)
{
  set_scaling(lp, scalemode);
}

MYBOOL __set_semicont(lprec *lp, int column, MYBOOL must_be_sc)
{
  return(_set_semicont(lp, column, must_be_sc));
}

void __set_sense(lprec *lp, MYBOOL maximize)
{
  set_sense(lp, maximize);
}

void __set_simplextype(lprec *lp, int simplextype)
{
  set_simplextype(lp, simplextype);
}

void __set_solutionlimit(lprec *lp, int limit)
{
  set_solutionlimit(lp, limit);
}

void __set_timeout(lprec *lp, long sectimeout)
{
  set_timeout(lp, sectimeout);
}

void __set_trace(lprec *lp, MYBOOL trace)
{
  set_trace(lp, trace);
}

MYBOOL __set_upbo(lprec *lp, int column, REAL value)
{
  return(_set_upbo(lp, column, value));
}

void __set_use_names(lprec *lp, MYBOOL isrow, MYBOOL use_names)
{
  _set_use_names(lp, isrow, use_names);
}

MYBOOL __set_var_branch(lprec *lp, int column, int branch_mode)
{
  return(_set_var_branch(lp, column, branch_mode));
}

MYBOOL __set_var_weights(lprec *lp, REAL *weights)
{
  return(_set_var_weights(lp, weights));
}

void __set_verbose(lprec *lp, int verbose)
{
  set_verbose(lp, verbose);
}

MYBOOL __set_XLI(lprec *lp, char *filename)
{
  return(_set_XLI(lp, filename));
}

int __solve(lprec *lp)
{
  return(_solve(lp));
}

MYBOOL __str_add_column(lprec *lp, char *col_string)
{
  return(_str_add_column(lp, col_string));
}

MYBOOL __str_add_constraint(lprec *lp, char *row_string ,int constr_type, REAL rh)
{
  return(_str_add_constraint(lp, row_string ,constr_type, rh));
}

MYBOOL __str_add_lag_con(lprec *lp, char *row_string, int con_type, REAL rhs)
{
  return(_str_add_lag_con(lp, row_string, con_type, rhs));
}

MYBOOL __str_set_obj_fn(lprec *lp, char *row_string)
{
  return(_str_set_obj_fn(lp, row_string));
}

MYBOOL __str_set_rh_vec(lprec *lp, char *rh_string)
{
  return(_str_set_rh_vec(lp, rh_string));
}

REAL __time_elapsed(lprec *lp)
{
  return(_time_elapsed(lp));
}

void __unscale(lprec *lp)
{
  unscale(lp);
}

MYBOOL __write_basis(lprec *lp, char *filename)
{
  return(_write_basis(lp, filename));
}

MYBOOL __write_lp(lprec *lp, char *filename)
{
  return(_write_lp(lp, filename));
}

MYBOOL __write_mps(lprec *lp, char *filename)
{
  return(_write_mps(lp, filename));
}

MYBOOL __write_MPS(lprec *lp, FILE *output)
{
  return(_write_MPS(lp, output));
}

MYBOOL __write_freemps(lprec *lp, char *filename)
{
  return(_write_freemps(lp, filename));
}

MYBOOL __write_freeMPS(lprec *lp, FILE *output)
{
  return(_write_freeMPS(lp, output));
}

MYBOOL __write_params(lprec *lp, char *filename, char *options)
{
  return(_write_params(lp, filename, options));
}

MYBOOL __write_XLI(lprec *lp, char *filename, char *options, MYBOOL results)
{
  return(_write_XLI(lp, filename, options, results));
}

/* typedef void   (mylogfunc)(lprec *lp, void *userhandle, char *buf); */
static mylogfunc *_newlog;

static void _mylog(lprec *lp, void *userhandle, char *buf)
{
  _newlog(lp, userhandle, buf);
}

static void __WINAPI mylog(lprec *lp, void *userhandle, char *buf)
{
  _newlog(lp, userhandle, buf);
}

void putlogfunc(lprec *lp, mylogfunc newlog, void *loghandle)
{
  _newlog = newlog;
  _put_logfunc(lp, mylog, loghandle);
}





/* typedef void   (myabortfunc)(lprec *lp, void *userhandle); */
static myabortfunc *_newabort;

static int _myabort(lprec *lp, void *userhandle)
{
  return(_newabort(lp, userhandle));
}

static int __WINAPI myabort(lprec *lp, void *userhandle)
{
  return(_newabort(lp, userhandle));
}

void putabortfunc(lprec *lp, myabortfunc newabort, void *aborthandle)
{
  _newabort = newabort;
  _put_abortfunc(lp, myabort, aborthandle);
}
