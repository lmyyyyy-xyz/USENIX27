f = [143, 60, 195];
A = [120, 210, 150.75; 110, 30, 125; 1, 1, 1];
b = [15000, 4000, 75];
lp = lp_maker(f, A, b, [-1, -1, -1], [], [], [], 1, 0);
solvestat = sclpsolve("solve", lp)
sclpsolve("get_objective", lp)
sclpsolve("get_variables", lp)
sclpsolve("delete_lp", lp);
