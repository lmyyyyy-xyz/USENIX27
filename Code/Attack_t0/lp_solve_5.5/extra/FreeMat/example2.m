% lpsolve example2 from the manual.

lp=fmlpsolve('make_lp', 0, 4);
fmlpsolve('set_verbose', lp, 0);
fmlpsolve('set_obj_fn', lp, [1, 3, 6.24, 0.1]);
fmlpsolve('add_constraint', lp, [0, 78.26, 0, 2.9], 2, 92.3);
fmlpsolve('add_constraint', lp, [0.24, 0, 11.31, 0], 1, 14.8);
fmlpsolve('add_constraint', lp, [12.68, 0, 0.08, 0.9], 2, 4);
fmlpsolve('set_lowbo', lp, [28.6, 0, 0, 18]);
fmlpsolve('set_upbo', lp, [1.0e30, 1.0e30, 1.0e30, 48.98]);
%fmlpsolve('set_col_name', lp, {'COLONE', 'COLTWO', 'COLTHREE', 'COLFOUR'});
%fmlpsolve('set_row_name', lp, {'THISROW', 'THATROW', 'LASTROW'});
fmlpsolve('write_lp', lp, 'a.lp');
fmlpsolve('get_mat', lp)
fmlpsolve('solve', lp)
fmlpsolve('get_objective', lp)
fmlpsolve('get_variables', lp)
fmlpsolve('get_constraints', lp)
%fmlpsolve('delete_lp', lp);
