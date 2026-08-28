f = [143, 60];
A = [120, 210; 110, 30; 1, 1];
b = [15000, 4000, 75];
lp = lp_maker(f, A, b, [-1, -1, -1], [], [], [], 1, 0);
solvestat = sclpsolve("solve", lp)
sclpsolve("get_objective", lp)
sclpsolve("get_variables", lp)
sclpsolve("delete_lp", lp);
