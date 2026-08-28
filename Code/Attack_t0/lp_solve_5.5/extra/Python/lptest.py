
import lpsolve55

lp = lpsolve55.lpsolve('make_lp', 2, 4)
lpsolve55.lpsolve('set_mat', lp, [[3, 2, 2, 1],[0, 4, 3, 1]])
lpsolve55.lpsolve('set_obj', lp, [2, 3.1, -2, 3] )
lpsolve55.lpsolve('set_rh', lp, [0, 4, 3.3] )
lpsolve55.lpsolve('set_constr_type', lp, 2,lpsolve55.GE)
lpsolve55.lpsolve('set_upbo', lp, 3, 1.5)
lpsolve55.lpsolve('set_lowbo', lp, 1, -10)
lpsolve55.lpsolve('solve', lp)
[goal, variables, duals, ret] = lpsolve55.lpsolve('get_solution', lp)
[constraints, ret] = lpsolve55.lpsolve('get_constraints', lp)
print("goal: ", goal)
print("achieved at:", variables)
print("constraint values:", constraints)
print("dual values:", duals)
