echo on

# Script to demonstrate use of the lp_solve toolkit

clc;
lp=octlpsolve('make_lp',0,4);
octlpsolve('add_constraint',lp,[3, 2, 2, 1],3,4);
octlpsolve('add_constraint',lp,[0, 4, 3, 1],2,3);
octlpsolve('set_obj_fn',lp,[2, 3, -2, 3]);
result=octlpsolve('solve',lp)
obj=octlpsolve('get_objective', lp)
x=octlpsolve('get_variables', lp)
pause;

# Change a single element, and maximize

clc;
octlpsolve('set_mat',lp,2,1,0.5);
octlpsolve('set_maxim',lp);
result=octlpsolve('solve',lp)
obj=octlpsolve('get_objective', lp)
x=octlpsolve('get_variables', lp)
pause;

# Change RHS

clc;
octlpsolve('set_rh',lp,1,7.45);
result=octlpsolve('solve',lp)
obj=octlpsolve('get_objective', lp)
x=octlpsolve('get_variables', lp)
pause;

# Set var 4 to an integer

clc;
octlpsolve('set_int',lp,4,1)
result=octlpsolve('solve',lp)
obj=octlpsolve('get_objective', lp)
x=octlpsolve('get_variables', lp)
pause;

# Put in lower and upper bounds

clc;
octlpsolve('set_lowbo',lp,2,2);
octlpsolve('set_upbo',lp,4,5.3);
result=octlpsolve('solve',lp)
obj=octlpsolve('get_objective', lp)
x=octlpsolve('get_variables', lp)
pause;

# Delete a constraint

clc;
octlpsolve('del_constraint',lp,1);
octlpsolve('add_constraint',lp,[1, 2, 1, 4],3,8);
result=octlpsolve('solve',lp)
obj=octlpsolve('get_objective', lp)
x=octlpsolve('get_variables', lp)
octlpsolve('delete_lp',lp)
pause;

#%%%%%%%%%%%%

# More examples

# ex1.lp from the lp_solve distribution

clc;
lp=octlpsolve('make_lp',2,2);
octlpsolve('set_mat',lp,[2, 1;-4, 4]);
octlpsolve('set_obj_fn',lp,[-1, 2]);
octlpsolve('set_int',lp,[1,1]);
octlpsolve('set_rh_vec',lp,[5, 5]);
octlpsolve('set_maxim',lp);
result=octlpsolve('solve',lp)
obj=octlpsolve('get_objective', lp)
x=octlpsolve('get_variables', lp)
octlpsolve('delete_lp',lp);
pause;

# Example 2

clc;
f = [50, 100];
A = [10, 5;4, 10; 1, 1.5];
b = [2500, 2000, 450];
e = [-1, -1, -1];

[m,n] = size(A);
lp=octlpsolve('make_lp',m,n);
octlpsolve('set_obj_fn',lp,f);
octlpsolve('set_mat',lp,A);
octlpsolve('set_rh_vec',lp,b);
octlpsolve('set_maxim',lp);
result=octlpsolve('solve',lp)
obj=octlpsolve('get_objective', lp)
x=octlpsolve('get_variables', lp)
octlpsolve('delete_lp',lp);
pause;

# Example 3

clc;

f = -[40, 36];
vub = [8, 10];
A = [5, 3];
b = [45];
e = 1;

[m,n] = size(A);
lp=octlpsolve('make_lp',m,n);
octlpsolve('set_obj_fn',lp,f);
octlpsolve('set_mat',lp,A);
octlpsolve('set_rh_vec',lp,b);
octlpsolve('set_constr_type',lp,1,2);
octlpsolve('set_upbo',lp,1,8);
octlpsolve('set_upbo',lp,2,10);
octlpsolve('set_maxim',lp);
result=octlpsolve('solve',lp)
obj=octlpsolve('get_objective', lp)
x=octlpsolve('get_variables', lp)
octlpsolve('delete_lp',lp);
pause;

# L1 Data fitting example with integer constraint on the intercept

# Generate data

clc;
n = 40;
t = (0:n-1)';
y = 3.5 -.2*t;
y = y + 0.5*randn(size(y));

m = [ones(n,1),t(:)];
a = [m,-m,eye(n)];
f = -[sum(m),sum(-m),2*ones(1,n)];
e = ones(n,1);

vub = [10, 10, 10, 10, 5*ones(1,n)];

[v,x] = lp_solve(f,a,y,e,[],vub,[1,3]);
p = x(1:2)-x(3:4);
err = y-m*p;

plot(t,y,'o',t,m*p);
xlabel('t');
ylabel('y');

disp('Press any key to continue.');
pause;

clc;
# Now solve bigger problem

n = 200;
m = 100;
a = rand(m,n);
idx = find(a<0.8);
a(idx) = zeros(length(idx),1);
a = a;
z = rand(n,1);
b = a*z;

[v,x] = lp_solve(-ones(1,n),a,b,zeros(m,1));

plot(a*x-b);
title('Residuals');
xlabel('Equation Number');

echo off
