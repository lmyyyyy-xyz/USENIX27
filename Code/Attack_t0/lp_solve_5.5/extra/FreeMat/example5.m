f = [143 60 195];
A = [120 210 150.75; 110 30 125; 1 1 1];
b = [15000; 4000; 75];
lp = lp_maker(f, A, b, [-1; -1; -1], [], [], [], 1, 0);
solvestat = fmlpsolve('solve', lp)
obj = fmlpsolve('get_objective', lp)
x = fmlpsolve('get_variables', lp)
fmlpsolve('delete_lp', lp);