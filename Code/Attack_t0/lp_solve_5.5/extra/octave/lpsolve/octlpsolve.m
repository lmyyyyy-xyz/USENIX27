# octlpsolve  interface to the lp_solve 5.5 toolkit. Please see
# reference guide for more information.
#
# octlpsolve is a low-level interface to the lp_solve toolkit. It may be called
# directly, or may be used to build higher level functions for solving
# various kinds of linear and mixed-integer linear programs. It uses an
# integer handle to point to a linear program.
#
#     return = octlpsolve('add_column', lp_handle, [column])
#
#     return = octlpsolve('add_columnex', lp_handle, [column])
#
#     return = octlpsolve('add_constraint', lp_handle, [row], constr_type, rh)
#
#     return = octlpsolve('add_constraintex', lp_handle, [row], constr_type, rh)
#
#     return = octlpsolve('add_SOS', lp_handle, name, sostype, priority, [sosvars], [weights])
#
#     return = octlpsolve('column_in_lp', lp_handle, [column])
#
#     octlpsolve('default_basis', lp_handle)
#
#     return = octlpsolve('del_column', lp_handle, column)
#
#     return = octlpsolve('del_constraint', lp_handle, del_row)
#
#     octlpsolve('delete_lp', lp_handle)
#
#     octlpsolve('free_lp', lp_handle)
#
#     return = octlpsolve('get_anti_degen', lp_handle)
#
#     [bascolumn] = octlpsolve('get_basis', lp_handle {, nonbasic})
#
#     return = octlpsolve('get_basiscrash', lp_handle)
#
#     return = octlpsolve('get_bb_depthlimit', lp_handle)
#
#     return = octlpsolve('get_bb_floorfirst', lp_handle)
#
#     return = octlpsolve('get_bb_rule', lp_handle)
#
#     return = octlpsolve('get_bounds_tighter', lp_handle)
#
#     return = octlpsolve('get_break_at_value', lp_handle)
#
#     name = octlpsolve('get_col_name', lp_handle, column)
#
#     [names] = octlpsolve('get_col_name', lp_handle)
#
#     [column, return] = octlpsolve('get_column', lp_handle, col_nr)
#
#     return = octlpsolve('get_constr_type', lp_handle, row)
#
#     [constr_type] = octlpsolve('get_constr_type', lp_handle)
#
#     [constr, return] = octlpsolve('get_constraints', lp_handle)
#
#     [duals, return] = octlpsolve('get_dual_solution', lp_handle)
#
#     return = octlpsolve('get_epsb', lp_handle)
#
#     return = octlpsolve('get_epsd', lp_handle)
#
#     return = octlpsolve('get_epsel', lp_handle)
#
#     return = octlpsolve('get_epsint', lp_handle)
#
#     return = octlpsolve('get_epsperturb', lp_handle)
#
#     return = octlpsolve('get_epspivot', lp_handle)
#
#     return = octlpsolve('get_improve', lp_handle)
#
#     return = octlpsolve('get_infinite', lp_handle)
#
#     return = octlpsolve('get_lowbo', lp_handle, column)
#
#     [return] = octlpsolve('get_lowbo', lp_handle)
#
#     return = octlpsolve('get_lp_index', lp_handle, orig_index)
#
#     name = octlpsolve('get_lp_name', lp_handle)
#
#     value = octlpsolve('get_mat', lp_handle, row, col)
#
#     [matrix, return] = octlpsolve('get_mat', lp_handle)
#
#     return = octlpsolve('get_max_level', lp_handle)
#
#     return = octlpsolve('get_maxpivot', lp_handle)
#
#     return = octlpsolve('get_mip_gap', lp_handle, absolute)
#
#     return = octlpsolve('get_nameindex', lp_handle, name, isrow)
#
#     return = octlpsolve('get_Ncolumns', lp_handle)
#
#     return = octlpsolve('get_negrange', lp_handle)
#
#     return = octlpsolve('get_nonzeros', lp_handle)
#
#     return = octlpsolve('get_Norig_columns', lp_handle)
#
#     return = octlpsolve('get_Norig_rows', lp_handle)
#
#     return = octlpsolve('get_Nrows', lp_handle)
#
#     return = octlpsolve('get_obj_bound', lp_handle)
#
#     [row_vec, return] = octlpsolve('get_obj_fn', lp_handle)
#
#     [row_vec, return] = octlpsolve('get_obj_fun', lp_handle)
#
#     return = octlpsolve('get_objective', lp_handle)
#
#     name = octlpsolve('get_objective_name', lp_handle)
#
#     return = octlpsolve('get_orig_index', lp_handle, lp_index)
#
#     name = octlpsolve('get_origcol_name', lp_handle, column)
#
#     [names] = octlpsolve('get_origcol_name', lp_handle)
#
#     name = octlpsolve('get_origrow_name', lp_handle, row)
#
#     [names] = octlpsolve('get_origrow_name', lp_handle)
#
#     return = octlpsolve('get_pivoting', lp_handle)
#
#     return = octlpsolve('get_presolve', lp_handle)
#
#     [pv, return] = octlpsolve('get_primal_solution', lp_handle)
#
#     return = octlpsolve('get_print_sol', lp_handle)
#
#     return = octlpsolve('get_rh', lp_handle, row)
#
#     [rh] = octlpsolve('get_rh', lp_handle)
#
#     return = octlpsolve('get_rh_range', lp_handle, row)
#
#     [rh_ranges] = octlpsolve('get_rh_range', lp_handle)
#
#     [row, return] = octlpsolve('get_row', lp_handle, row_nr)
#
#     name = octlpsolve('get_row_name', lp_handle, row)
#
#     [names] = octlpsolve('get_row_name', lp_handle)
#
#     return = octlpsolve('get_scalelimit', lp_handle)
#
#     return = octlpsolve('get_scaling', lp_handle)
#
#     [objfrom, objtill, objfromvalue, objtillvalue, return] = octlpsolve('get_sensitivity_obj', lp_handle)
#
#     [objfrom, objtill, objfromvalue, objtillvalue, return] = octlpsolve('get_sensitivity_objex', lp_handle)
#
#     [duals, dualsfrom, dualstill, return] = octlpsolve('get_sensitivity_rhs', lp_handle)
#
#     [duals, dualsfrom, dualstill, return] = octlpsolve('get_sensitivity_rhsex', lp_handle)
#
#     return = octlpsolve('get_simplextype', lp_handle)
#
#     [obj, x, duals, return] = octlpsolve('get_solution', lp_handle)
#
#     return = octlpsolve('get_solutioncount', lp_handle)
#
#     return = octlpsolve('get_solutionlimit', lp_handle)
#
#     return = octlpsolve('get_status', lp_handle)
#
#     return = octlpsolve('get_statustext', lp_handle, statuscode)
#
#     return = octlpsolve('get_timeout', lp_handle)
#
#     return = octlpsolve('get_total_iter', lp_handle)
#
#     return = octlpsolve('get_total_nodes', lp_handle)
#
#     return = octlpsolve('get_upbo', lp_handle, column)
#
#     [upbo] = octlpsolve('get_upbo', lp_handle)
#
#     return = octlpsolve('get_var_branch', lp_handle, column)
#
#     [var_branch] = octlpsolve('get_var_branch', lp_handle)
#
#     return = octlpsolve('get_var_dualresult', lp_handle, index)
#
#     return = octlpsolve('get_var_primalresult', lp_handle, index)
#
#     return = octlpsolve('get_var_priority', lp_handle, column)
#
#     [var_priority] = octlpsolve('get_var_priority', lp_handle)
#
#     [var, return] = octlpsolve('get_variables', lp_handle)
#
#     return = octlpsolve('get_verbose', lp_handle)
#
#     return = octlpsolve('get_working_objective', lp_handle)
#
#     [bascolumn, return] = octlpsolve('guess_basis', lp_handle, guessvector)
#
#     return = octlpsolve('has_BFP', lp_handle)
#
#     return = octlpsolve('has_XLI', lp_handle)
#
#     return = octlpsolve('is_add_rowmode', lp_handle)
#
#     return = octlpsolve('is_anti_degen', lp_handle, testmask)
#
#     return = octlpsolve('is_binary', lp_handle, column)
#
#     [binary] = octlpsolve('is_binary', lp_handle)
#
#     return = octlpsolve('is_break_at_first', lp_handle)
#
#     return = octlpsolve('is_constr_type', lp_handle, row, mask)
#
#     return = octlpsolve('is_debug', lp_handle)
#
#     return = octlpsolve('is_feasible', lp_handle, [values] {, threshold})
#
#     return = octlpsolve('is_free', lp_handle, column)
#
#     [free] = octlpsolve('is_free', lp_handle)
#
#     return = octlpsolve('is_infinite', lp_handle, value)
#
#     return = octlpsolve('is_int', lp_handle, column)
#
#     [int] = octlpsolve('is_int', lp_handle)
#
#     return = octlpsolve('is_integerscaling', lp_handle)
#
#     return = octlpsolve('is_maxim', lp_handle)
#
#     return = octlpsolve('is_nativeBFP', lp_handle)
#
#     return = octlpsolve('is_nativeXLI', lp_handle)
#
#     return = octlpsolve('is_negative', lp_handle, column)
#
#     [negative] = octlpsolve('is_negative', lp_handle)
#
#     return = octlpsolve('is_piv_mode', lp_handle, testmask)
#
#     return = octlpsolve('is_piv_rule', lp_handle, rule)
#
#     return = octlpsolve('is_presolve', lp_handle, testmask)
#
#     return = octlpsolve('is_scalemode', lp_handle, testmask)
#
#     return = octlpsolve('is_scaletype', lp_handle, scaletype)
#
#     return = octlpsolve('is_semicont', lp_handle, column)
#
#     [semicont] = octlpsolve('is_semicont', lp_handle)
#
#     return = octlpsolve('is_SOS_var', lp_handle, column)
#
#     [SOS_var] = octlpsolve('is_SOS_var', lp_handle)
#
#     return = octlpsolve('is_trace', lp_handle)
#
#     versionstring = octlpsolve('lp_solve_version')
#
#     lp_handle = octlpsolve('make_lp', rows, columns)
#
#     octlpsolve('print_constraints', lp_handle {, columns})
#
#     return = octlpsolve('print_debugdump', lp_handle, filename)
#
#     octlpsolve('print_duals', lp_handle)
#
#     octlpsolve('print_lp', lp_handle)
#
#     octlpsolve('print_objective', lp_handle)
#
#     octlpsolve('print_scales', lp_handle)
#
#     octlpsolve('print_solution', lp_handle {, columns})
#
#     octlpsolve('print_str', lp_handle, str)
#
#     octlpsolve('print_tableau', lp_handle)
#
#     [handle_vec] = octlpsolve('print_handle')
#
#     lp_handle = octlpsolve('read_freeMPS', filename {, verbose})
#
#     lp_handle = octlpsolve('read_lp_file', filename {, verbose {, lp_name}})
#
#     lp_handle = octlpsolve('read_lp', filename {, verbose {, lp_name}})
#
#     lp_handle = octlpsolve('read_LP', filename {, verbose {, lp_name}})
#
#     lp_handle = octlpsolve('read_mps', filename {, verbose})
#
#     lp_handle = octlpsolve('read_MPS', filename {, verbose})
#
#     lp_handle = octlpsolve('read_XLI', xliname, modelname {, dataname {, options {, verbose}}}
#
#     return = octlpsolve('set_add_rowmode', lp_handle, turnon)
#
#     octlpsolve('set_anti_degen', lp_handle, anti_degen)
#
#     return = octlpsolve('set_basis', lp_handle, [bascolumn], nonbasic)
#
#     octlpsolve('set_basiscrash', lp_handle, mode)
#
#     octlpsolve('set_bb_depthlimit', lp_handle, bb_maxlevel)
#
#     octlpsolve('set_bb_floorfirst', lp_handle, bb_floorfirst)
#
#     octlpsolve('set_bb_rule', lp_handle, bb_rule)
#
#     return = octlpsolve('set_BFP', lp_handle, filename)
#
#     return = octlpsolve('set_binary', lp_handle, column, must_be_bin)
#
#     return = octlpsolve('set_binary', lp_handle, [must_be_bin])
#
#     return = octlpsolve('set_bounds', lp_handle, column, lower, upper)
#
#     return = octlpsolve('set_bounds', lp_handle, [lower], [upper])
#
#     octlpsolve('set_bounds_tighter', lp_handle, tighten)
#
#     octlpsolve('set_break_at_first', lp_handle, break_at_first)
#
#     octlpsolve('set_break_at_value', lp_handle, break_at_value)
#
#     return = octlpsolve('set_col_name', lp_handle, column, name)
#
#     return = octlpsolve('set_col_name', lp_handle, [names])
#
#     return = octlpsolve('set_column', lp_handle, col_no, [column])
#
#     return = octlpsolve('set_columnex', lp_handle, col_no, [column])
#
#     return = octlpsolve('set_constr_type', lp_handle, row, con_type)
#
#     return = octlpsolve('set_constr_type', lp_handle, [con_type])
#
#     octlpsolve('set_debug', lp_handle, debug)
#
#     octlpsolve('set_epsb', lp_handle, epsb)
#
#     octlpsolve('set_epsd', lp_handle, epsd)
#
#     octlpsolve('set_epsel', lp_handle, epsel)
#
#     octlpsolve('set_epsint', lp_handle, epsint)
#
#     octlpsolve('set_epsperturb', lp_handle, epsperturb)
#
#     octlpsolve('set_epspivot', lp_handle, epspivot)
#
#     return = octlpsolve('set_free', lp_handle, column)
#
#     octlpsolve('set_improve', lp_handle, improve)
#
#     octlpsolve('set_infinite', lp_handle, infinite)
#
#     return = octlpsolve('set_int', lp_handle, column, must_be_int)
#
#     return = octlpsolve('set_int', lp_handle, [must_be_int])
#
#     return = octlpsolve('set_lowbo', lp_handle, column, value)
#
#     return = octlpsolve('set_lowbo', lp_handle, [values])
#
#     return = octlpsolve('set_lp_name', lp_handle, name)
#
#     return = octlpsolve('set_mat', lp_handle, [matrix])
#
#     return = octlpsolve('set_mat', lp_handle, row, column, value)
#
#     octlpsolve('set_maxim', lp_handle)
#
#     octlpsolve('set_maxpivot', max_num_inv)
#
#     octlpsolve('set_minim', lp_handle)
#
#     octlpsolve('set_mip_gap', lp_handle, absolute, mip_gap)
#
#     octlpsolve('set_negrange', negrange)
#
#     return = octlpsolve('set_obj', lp_handle, column, value)
#
#     return = octlpsolve('set_obj', lp_handle, [values])
#
#     octlpsolve('set_obj_bound', lp_handle, obj_bound)
#
#     return = octlpsolve('set_obj_fn', lp_handle, [row])
#
#     return = octlpsolve('set_obj_fnex', lp_handle, [row])
#
#     return = octlpsolve('set_outputfile', lp_handle, filename)
#
#     octlpsolve('set_pivoting', lp_handle, pivoting)
#
#     octlpsolve('set_preferdual', lp_handle, dodual)
#
#     octlpsolve('set_presolve', lp_handle, do_presolve)
#
#     octlpsolve('set_print_sol', lp_handle, print_sol)
#
#     return = octlpsolve('set_rh', lp_handle, row, value)
#
#     return = octlpsolve('set_rh', lp_handle, [values])
#
#     return = octlpsolve('set_rh_range', lp_handle, row, deltavalue)
#
#     return = octlpsolve('set_rh_range', lp_handle, [deltavalues])
#
#     octlpsolve('set_rh_vec', lp_handle, [rh])
#
#     return = octlpsolve('set_row', lp_handle, row_no, [row])
#
#     return = octlpsolve('set_rowex', lp_handle, row_no, [row])
#
#     return = octlpsolve('set_row_name', lp_handle, row, name)
#
#     return = octlpsolve('set_row_name', lp_handle, [names])
#
#     octlpsolve('set_scalelimit', lp_handle, scalelimit)
#
#     octlpsolve('set_scaling', lp_handle, scalemode)
#
#     return = octlpsolve('set_semicont', lp_handle, column, must_be_sc)
#
#     return = octlpsolve('set_semicont', lp_handle, [must_be_sc])
#
#     octlpsolve('set_sense', lp_handle, maximize)
#
#     octlpsolve('set_simplextype', lp_handle, simplextype)
#
#     octlpsolve('set_solutionlimit', lp_handle, simplextype)
#
#     octlpsolve('set_timeout', lp_handle, sectimeout)
#
#     octlpsolve('set_trace', lp_handle, trace)
#
#     return = octlpsolve('set_upbo', lp_handle, column, value)
#
#     return = octlpsolve('set_upbo', lp_handle, [values])
#
#     return = octlpsolve('set_var_branch', lp_handle, column, branch_mode)
#
#     return = octlpsolve('set_var_branch', lp_handle, [branch_mode])
#
#     return = octlpsolve('set_var_weights', lp_handle, [weights])
#
#     octlpsolve('set_verbose', lp_handle, verbose)
#
#     return = octlpsolve('set_XLI', lp_handle, filename)
#
#     result = octlpsolve('solve', lp_handle)
#
#     return = octlpsolve('time_elapsed', lp_handle)
#
#     octlpsolve('unscale', lp_handle)
#
#     return = octlpsolve('write_freemps', lp_handle, filename)
#
#     return = octlpsolve('write_freeMPS', lp_handle, filename)
#
#     return = octlpsolve('write_lp', lp_handle, filename)
#
#     return = octlpsolve('write_LP', lp_handle, filename)
#
#     return = octlpsolve('write_mps', lp_handle, filename)
#
#     return = octlpsolve('write_MPS', lp_handle, filename)
#
#     return = octlpsolve('write_XLI', lp_handle, filename {, options {, results}})
#

disp('octlpsolve driver not found !!!');
disp('Check if octlpsolve.oct is on your system and in a directory known to Octave.');
disp('Press enter to see the paths where Octave looks for the driver.');
pause
path
error('octlpsolve.oct not found');
