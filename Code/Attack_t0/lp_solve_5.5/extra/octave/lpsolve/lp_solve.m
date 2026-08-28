#LP_SOLVE  Solves mixed integer linear programming problems.
#
#  SYNOPSIS: [obj,x,duals] = lp_solve(f,a,b,e,vlb,vub,xint,scalemode,keep)
#
#     solves the MILP problem
#
#             max v = f'*x
#               a*x <> b
#                 vlb <= x <= vub
#                 x(int) are integer
#
#  ARGUMENTS: The first four arguments are required:
#
#           f: n vector of coefficients for a linear objective function.
#           a: m by n matrix representing linear constraints.
#           b: m vector of right sides for the inequality constraints.
#           e: m vector that determines the sense of the inequalities:
#                     e(i) = -1  ==> Less Than
#                     e(i) =  0  ==> Equals
#                     e(i) =  1  ==> Greater Than
#         vlb: n vector of lower bounds. If empty or omitted,
#              then the lower bounds are set to zero.
#         vub: n vector of upper bounds. May be omitted or empty.
#        xint: vector of integer variables. May be omitted or empty.
#   scalemode: scale flag. Off when 0 or omitted.
#        keep: Flag for keeping the lp problem after it's been solved.
#              If omitted, the lp will be deleted when solved.
#
#  OUTPUT: A nonempty output is returned if a solution is found:
#
#         obj: Optimal value of the objective function.
#           x: Optimal value of the decision variables.
#       duals: solution of the dual problem.

function [obj, x, duals] = lp_solve(f, a, b, e, vlb, vub, xint, scalemode, keep)

if nargin == 0
        help lp_solve;
        return;
end

[m,n] = size(a);
lp = octlpsolve('make_lp', m, n);
octlpsolve('set_verbose', lp, 3);
octlpsolve('set_mat', lp, a);
octlpsolve('set_rh_vec', lp, b);
octlpsolve('set_obj_fn', lp, f);
octlpsolve('set_maxim', lp); % default is solving minimum lp.

for i = 1:length(e)
  if e(i) < 0
        con_type = 1;
  elseif e(i) == 0
        con_type = 3;
  else
        con_type = 2;
  end
  octlpsolve('set_constr_type', lp, i, con_type);
end

if nargin > 4
  for i = 1:length(vlb)
    octlpsolve('set_lowbo', lp, i, vlb(i));
  end
end

if nargin > 5
  for i = 1:length(vub)
    octlpsolve('set_upbo', lp, i, vub(i));
  end
end

if nargin > 6
  for i = 1:length(xint)
    octlpsolve('set_int', lp, xint(i), 1);
  end
end

if nargin > 7
  if scalemode ~= 0
    octlpsolve('set_scaling', lp, scalemode);
  end
end

result=octlpsolve('solve', lp);
if result == 0 | result == 1 | result == 11 | result == 12
  [obj, x, duals] = octlpsolve('get_solution', lp);
end

if nargin < 9
  octlpsolve('delete_lp', lp);
end
