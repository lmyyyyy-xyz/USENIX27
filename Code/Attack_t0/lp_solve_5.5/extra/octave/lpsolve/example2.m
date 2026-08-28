# lpsolve example2 from the manual.

echo on
lp=octlpsolve('make_lp', 0, 4);
#octlpsolve('set_verbose', lp, 3);
octlpsolve('set_obj_fn', lp, [1, 3, 6.24, 0.1]);
octlpsolve('add_constraint', lp, [0, 78.26, 0, 2.9], 2, 92.3);
octlpsolve('add_constraint', lp, [0.24, 0, 11.31, 0], 1, 14.8);
octlpsolve('add_constraint', lp, [12.68, 0, 0.08, 0.9], 2, 4);
octlpsolve('set_lowbo', lp, [28.6, 0, 0, 18]);
octlpsolve('set_upbo', lp, [Inf, Inf, Inf, 48.98]);
octlpsolve('set_col_name', lp, {'COLONE', 'COLTWO', 'COLTHREE', 'COLFOUR'});
octlpsolve('set_row_name', lp, {'THISROW', 'THATROW', 'LASTROW'});
octlpsolve('write_lp', lp, 'a.lp');
octlpsolve('get_mat', lp)
octlpsolve('solve', lp)
octlpsolve('get_objective', lp)
octlpsolve('get_variables', lp)
octlpsolve('get_constraints', lp)
#octlpsolve('delete_lp', lp);
echo off
