mode(1)

// Script to demonstrate use of the lp_solve toolkit

//clc
lp = sclpsolve("make_lp",0,4);
sclpsolve("add_constraint",lp,[3,2,2,1],3,4);
sclpsolve("add_constraint",lp,[0,4,3,1],2,3);
sclpsolve("set_obj_fn",lp,[2,3,-2,3]);
result = sclpsolve("solve",lp)
obj = sclpsolve("get_objective",lp)
x = sclpsolve("get_variables",lp)
halt();

// Change a single element, and maximize

//clc
sclpsolve("set_mat",lp,2,1,0.5);
sclpsolve("set_maxim",lp);
result = sclpsolve("solve",lp)
obj = sclpsolve("get_objective",lp)
x = sclpsolve("get_variables",lp)
halt();

// Change RHS

//clc
sclpsolve("set_rh",lp,1,7.45);
result = sclpsolve("solve",lp)
obj = sclpsolve("get_objective",lp)
x = sclpsolve("get_variables",lp)
halt();

// Set var 4 to an integer

//clc
sclpsolve("set_int",lp,4,1)
result = sclpsolve("solve",lp)
obj = sclpsolve("get_objective",lp)
x = sclpsolve("get_variables",lp)
halt();

// Put in lower and upper bounds

//clc
sclpsolve("set_lowbo",lp,2,2);
sclpsolve("set_upbo",lp,4,5.3);
result = sclpsolve("solve",lp)
obj = sclpsolve("get_objective",lp)
x = sclpsolve("get_variables",lp)
halt();

// Delete a constraint

//clc
sclpsolve("del_constraint",lp,1);
sclpsolve("add_constraint",lp,[1,2,1,4],3,8);
result = sclpsolve("solve",lp)
obj = sclpsolve("get_objective",lp)
x = sclpsolve("get_variables",lp)
sclpsolve("delete_lp",lp)
halt();

//%%%%%%%%%%%%

// More examples

// ex1.lp from the lp_solve distribution

//clc
lp = sclpsolve("make_lp",2,2);
sclpsolve("set_mat",lp,[2,1;-4,4]);
sclpsolve("set_obj_fn",lp,[-1,2]);
sclpsolve("set_int",lp,[1,1]);
sclpsolve("set_rh_vec",lp,[5,5]);
sclpsolve("set_maxim",lp);
result = sclpsolve("solve",lp)
obj = sclpsolve("get_objective",lp)
x = sclpsolve("get_variables",lp)
sclpsolve("delete_lp",lp);
halt();

// Example 2

//clc
f = [50,100];
A = sparse([10,5;4,10;1,1.5]);
b = [2500,2000,450];
e = [-1,-1,-1];

[m,n] = size(A);
lp = sclpsolve("make_lp",m,n);
sclpsolve("set_obj_fn",lp,f);
sclpsolve("set_mat",lp,mtlb_sparse(A));
sclpsolve("set_rh_vec",lp,b);
sclpsolve("set_maxim",lp);
result = sclpsolve("solve",lp)
obj = sclpsolve("get_objective",lp)
x = sclpsolve("get_variables",lp)
sclpsolve("delete_lp",lp);
halt();

// Example 3

//clc

f = -[40,36];
vub = [8,10];
A = sparse([5,3]);
b = 45;
e = 1;

[m,n] = size(A);
lp = sclpsolve("make_lp",m,n);
sclpsolve("set_obj_fn",lp,f);
sclpsolve("set_mat",lp,mtlb_sparse(A));
sclpsolve("set_rh_vec",lp,b);
sclpsolve("set_constr_type",lp,1,2);
sclpsolve("set_upbo",lp,1,8);
sclpsolve("set_upbo",lp,2,10);
sclpsolve("set_maxim",lp);
result = sclpsolve("solve",lp)
obj = sclpsolve("get_objective",lp)
x = sclpsolve("get_variables",lp)
sclpsolve("delete_lp",lp);
halt();

mode(0)
