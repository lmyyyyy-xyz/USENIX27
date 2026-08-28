% lpsolve example1 from the manual.

lp=fmlpsolve('make_lp', 0, 4);
fmlpsolve('set_verbose', lp, 3);
fmlpsolve('set_obj_fn', lp, [1, 3, 6.24, 0.1]);
fmlpsolve('add_constraint', lp, [0, 78.26, 0, 2.9], 2, 92.3);
fmlpsolve('add_constraint', lp, [0.24, 0, 11.31, 0], 1, 14.8);
fmlpsolve('add_constraint', lp, [12.68, 0, 0.08, 0.9], 2, 4);
fmlpsolve('set_lowbo', lp, 1, 28.6);
fmlpsolve('set_lowbo', lp, 4, 18);
fmlpsolve('set_upbo', lp, 4, 48.98);
fmlpsolve('set_col_name', lp, 1, 'COLONE');
fmlpsolve('set_col_name', lp, 2, 'COLTWO');
fmlpsolve('set_col_name', lp, 3, 'COLTHREE');
fmlpsolve('set_col_name', lp, 4, 'COLFOUR');
fmlpsolve('set_row_name', lp, 1, 'THISROW');
fmlpsolve('set_row_name', lp, 2, 'THATROW');
fmlpsolve('set_row_name', lp, 3, 'LASTROW');
fmlpsolve('write_lp', lp, 'a.lp');
fmlpsolve('get_mat', lp, 1, 2)
fmlpsolve('solve', lp)
fmlpsolve('get_objective', lp)
fmlpsolve('get_variables', lp)
fmlpsolve('get_constraints', lp)
%fmlpsolve('delete_lp', lp);
