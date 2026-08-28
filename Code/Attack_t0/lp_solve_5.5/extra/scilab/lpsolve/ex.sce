// clc
mode(1);

// Test and Demonstrate the use of lp_solve

mode(0);
disp("Press any key to continue.");
halt();
mode(1);

// clc
// Example 1 from the lp_solve distribution
f = [-1,2]';
A = [2,1;-4,4];
b = [5,5];
e = -[1,1];
xint = [1,2];

[v,x] = lp_solve(f,sparse(A),b,e,[],[],xint)

mode(0);
disp("End of Ex1. Expected Solution: v=3, x=[1, 2]. Press any key to continue.");
halt();
mode(1);

// clc
// Example 2
f = [50,100];
A = sparse([10,5;4,10;1,1.5]);
b = [2500,2000,450];
e = [-1,-1,-1];

[v,x] = lp_solve(f,A,b,e)

mode(0);
disp("End of Ex2. Press any key to continue.");
halt();
mode(1);

// clc
// Example 3
f = -[40,36];
vub = [8,10];
A = sparse([5,3]);
b = 45;
e = 1;

[v,x] = lp_solve(f,A,b,e,[],vub)

mode(0);
disp("End of Ex3. Press any key to continue.");
halt();
mode(1);

// clc
// Example 4
f = [10,6,4];
A = [1,1,1;10,4,5;2,2,6];
A = sparse(A);
b = [100,600,300];
e = [-1,-1,-1];
xint = 2;

[v,x] = lp_solve(f,A,b,e,[],[],xint)

mode(0);
disp("End of Ex4. Press any key to continue.");
halt();
mode(1);

// clc
// Example 5
// Integer programming example, page 218 of Ecker & Kupferschmid
f = -[3,-7,-12];
a = [-3,6,8;6,-3,7;-6,3,3];
a = sparse(a);
b = [12,8,5];
e = [-1,-1,-1];
xint = [1,2,3];

[v,x] = lp_solve(f,a,b,e,[],[],xint)

mode(0);
disp("End of Ex5. Press any key to continue.");
halt();
mode(1);

// clc
// Example 6
// 0-1 programming example, page 228 233 of Ecker & Kupferschmid
f = -[2,3,7,7];
a = [1,1,-2,-5;-1,2,1,4];
a = sparse(a);
b = [2,-3];
e = [1,1];
xint = [1,2,3,4];
vub = [1,1,1,1];

[v,x] = lp_solve(f,a,b,e,[],vub,xint)

mode(0);
disp("End of Ex6. Press any key to continue.");
halt();
mode(1);

// clc
// Example 7
// 0-1 programming example, page 238 of Ecker & Kupferschmid
f = -[1,2,3,7,8,8];
a = [5,-3,2,-3,-1,2;-1,0,2,1,3,-3;1,2,-1,0,5,-1];
b = [-5,-1,3];
e = [1,1,1];
xint = [1,2,3,4,5,6];
vub = [1,1,1,1,1,1];

[v,x] = lp_solve(f,sparse(a),b,e,[],vub,xint)

mode(0);
disp("End of Ex7. Press any key to continue.");
halt();
mode(1);

// clc
// Example 8
// A knapsack problem
// The problem is to maximize the sum of objects

n = 5;// Number of objects
f = ones(n,1);

// subject to a constraint not to fill up the bag
a = rand(1,n);
b = 1;
e = -1;
xint = 1:n;
vub = ones(n,1);

[v,x] = lp_solve(f,sparse(a),b,e,[],vub,xint)

mode(0);
disp("End of Ex8. Note that model is random, so solution is also random. Press any key to continue.");
halt();
mode(1);

// clc
// Example 9
// L1 Data fitting example with integer constraint on the intercept
n = 40;
t = (0:n-1)';
y = 3.5-0.2*t;
%v0 = size(y);y = y + 0.5*rand(%v0(1),%v0(2),"normal");

m = [ones(n,1),t(:)];
a = [m,-m,sparse(eye(n,n))];
f = -[sum(m,1),sum(-m,1),2*ones(1,n)];
e = ones(n,1);

vub = [10,10,10,10,5*ones(1,n)];

[v,x] = lp_solve(f,a,y,e,[],vub,[1,3]);

// clc
// Example 11
// ex2.lp from the lp_solve distribution
f = [8,15];
a = [10,21;2,1];
a = sparse(a);
b = [156,22];
e = [-1,-1];
[v,x] = lp_solve(f,a,b,e)
mode(0);
disp("End of Ex11. Expected Solution: v=119.625, x=[9.5625, 2.875]. Press any key to continue.");
halt();
mode(1);

// clc
// Example 12
// ex3.lp from the lp_solve distribution
f = [3,13];
a = [2,9;11,-8];
a = sparse(a);
b = [40,82];
e = [-1,-1];
[v,x] = lp_solve(f,a,b,e)
mode(0);
disp("End of Ex12. Expected Solution: v=58.8, x=[9.2, 2.4]. Press any key to continue.");
halt();
mode(1);

// clc
// Example 13
// ex6.lp from the lp_solve distribution
f = [592,381,273,55,48,37,23];
a = [3534,2356,1767,589,528,451,304];
a = sparse(a);
b = 119567;
e = -1;
xint = [1,2,3,4,5,6,7];
vub = [];
[v,x] = lp_solve(f,a,b,e,[],vub,xint)
mode(0);
disp("End of Ex13. Expected Solution: v=19979, x=[32,2,1,0,0,0,0]. Press any key to continue.");
halt();
mode(1);
