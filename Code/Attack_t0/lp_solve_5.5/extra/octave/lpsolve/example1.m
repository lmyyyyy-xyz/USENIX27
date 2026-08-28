# lpsolve example1 from the manual.

echo on
lp=octlpsolve('make_lp', 0, 4);
octlpsolve('set_verbose', lp, 3);
octlpsolve('set_obj_fn', lp, [1, 3, 6.24, 0.1]);
octlpsolve('add_constraint', lp, [0, 78.26, 0, 2.9], 2, 92.3);
octlpsolve('add_constraint', lp, [0.24, 0, 11.31, 0], 1, 14.8);
octlpsolve('add_constraint', lp, [12.68, 0, 0.08, 0.9], 2, 4);
octlpsolve('set_lowbo', lp, 1, 28.6);
octlpsolve('set_lowbo', lp, 4, 18);
octlpsolve('set_upbo', lp, 4, 48.98);
octlpsolve('set_col_name', lp, 1, 'COLONE');
octlpsolve('set_col_name', lp, 2, 'COLTWO');
octlpsolve('set_col_name', lp, 3, 'COLTHREE');
octlpsolve('set_col_name', lp, 4, 'COLFOUR');
octlpsolve('set_row_name', lp, 1, 'THISROW');
octlpsolve('set_row_name', lp, 2, 'THATROW');
octlpsolve('set_row_name', lp, 3, 'LASTROW');
octlpsolve('write_lp', lp, 'a.lp');
octlpsolve('get_mat', lp, 1, 2)
octlpsolve('solve', lp)
octlpsolve('get_objective', lp)
octlpsolve('get_variables', lp)
octlpsolve('get_constraints', lp)
#octlpsolve('delete_lp', lp);
echo off
