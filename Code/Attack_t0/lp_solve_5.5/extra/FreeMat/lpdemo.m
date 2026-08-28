% Script to demonstrate use of the lp_solve toolkit

clc;
lp=fmlpsolve('make_lp',0,4);
fmlpsolve('set_verbose', lp, 3);
fmlpsolve('add_constraint',lp,[3, 2, 2, 1],3,4);
fmlpsolve('add_constraint',lp,[0, 4, 3, 1],2,3);
fmlpsolve('set_obj_fn',lp,[2, 3, -2, 3]);
result=fmlpsolve('solve',lp)
obj=fmlpsolve('get_objective', lp)
x=fmlpsolve('get_variables', lp)
pause;

% Change a single element, and maximize

clc;
fmlpsolve('set_mat',lp,2,1,0.5);
fmlpsolve('set_maxim',lp);
result=fmlpsolve('solve',lp)
obj=fmlpsolve('get_objective', lp)
x=fmlpsolve('get_variables', lp)
pause;

% Change RHS

clc;
fmlpsolve('set_rh',lp,1,7.45);
result=fmlpsolve('solve',lp)
obj=fmlpsolve('get_objective', lp)
x=fmlpsolve('get_variables', lp)
pause;

% Set var 4 to an integer

clc;
fmlpsolve('set_int',lp,4,1)
result=fmlpsolve('solve',lp)
obj=fmlpsolve('get_objective', lp)
x=fmlpsolve('get_variables', lp)
pause;

% Put in lower and upper bounds

clc;
fmlpsolve('set_lowbo',lp,2,2);
fmlpsolve('set_upbo',lp,4,5.3);
result=fmlpsolve('solve',lp)
obj=fmlpsolve('get_objective', lp)
x=fmlpsolve('get_variables', lp)
pause;

% Delete a constraint

clc;
fmlpsolve('del_constraint',lp,1);
fmlpsolve('add_constraint',lp,[1, 2, 1, 4],3,8);
result=fmlpsolve('solve',lp)
obj=fmlpsolve('get_objective', lp)
x=fmlpsolve('get_variables', lp)
fmlpsolve('delete_lp',lp)
pause;

%%%%%%%%%%%%%

% More examples

% ex1.lp from the lp_solve distribution

clc;
lp=fmlpsolve('make_lp',2,2);
fmlpsolve('set_verbose', lp, 3);
fmlpsolve('set_mat',lp,[2, 1;-4, 4]);
fmlpsolve('set_obj_fn',lp,[-1, 2]);
fmlpsolve('set_int',lp,[1,1]);
fmlpsolve('set_rh_vec',lp,[5, 5]);
fmlpsolve('set_maxim',lp);
result=fmlpsolve('solve',lp)
obj=fmlpsolve('get_objective', lp)
x=fmlpsolve('get_variables', lp)
fmlpsolve('delete_lp',lp);
pause;

% Example 2

clc;
f = [50, 100];
A = sparse([10, 5;4, 10; 1, 1.5]);
b = [2500, 2000, 450];
e = [-1, -1, -1];

[m,n] = size(A);
lp=fmlpsolve('make_lp',m,n);
fmlpsolve('set_verbose', lp, 3);
fmlpsolve('set_obj_fn',lp,f);
fmlpsolve('set_mat',lp,A);
fmlpsolve('set_rh_vec',lp,b);
fmlpsolve('set_maxim',lp);
result=fmlpsolve('solve',lp)
obj=fmlpsolve('get_objective', lp)
x=fmlpsolve('get_variables', lp)
fmlpsolve('delete_lp',lp);
pause;

% Example 3

clc;

f = -[40, 36];
vub = [8, 10];
A = sparse([5, 3]);
b = [45];
e = 1;

[m,n] = size(A);
lp=fmlpsolve('make_lp',m,n);
fmlpsolve('set_verbose', lp, 3);
fmlpsolve('set_obj_fn',lp,f);
fmlpsolve('set_mat',lp,A);
fmlpsolve('set_rh_vec',lp,b);
fmlpsolve('set_constr_type',lp,1,2);
fmlpsolve('set_upbo',lp,1,8);
fmlpsolve('set_upbo',lp,2,10);
fmlpsolve('set_maxim',lp);
result=fmlpsolve('solve',lp)
obj=fmlpsolve('get_objective', lp)
x=fmlpsolve('get_variables', lp)
fmlpsolve('delete_lp',lp);
pause;
