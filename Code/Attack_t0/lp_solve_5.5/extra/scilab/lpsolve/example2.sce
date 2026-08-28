// lpsolve example2 from the manual.

lp=sclpsolve('make_lp', 0, 4);
// sclpsolve('set_verbose', lp, 3);
sclpsolve('set_obj_fn', lp, [1, 3, 6.24, 0.1]);
sclpsolve('add_constraint', lp, [0, 78.26, 0, 2.9], 2, 92.3);
sclpsolve('add_constraint', lp, [0.24, 0, 11.31, 0], 1, 14.8);
sclpsolve('add_constraint', lp, [12.68, 0, 0.08, 0.9], 2, 4);
sclpsolve('set_lowbo', lp, [28.6, 0, 0, 18]);
sclpsolve('set_upbo', lp, [%inf, %inf, %inf, 48.98]);
sclpsolve('set_col_name', lp, cellstr(['COLONE';'COLTWO';'COLTHREE';'COLFOUR']));
sclpsolve('set_row_name', lp, cellstr(['THISROW';'THATROW';'LASTROW']));
sclpsolve('write_lp', lp, 'a.lp');
sclpsolve('get_mat', lp)
sclpsolve('solve', lp)
sclpsolve('get_objective', lp)
sclpsolve('get_variables', lp)
sclpsolve('get_constraints', lp)
sclpsolve('write_lp', lp, 'a.lp')
//sclpsolve('delete_lp', lp);
