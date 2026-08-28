%LP_SOLVE  Solves mixed integer linear programming problems.
%
%  SYNOPSIS: [obj,x,duals,stat] = lp_solve(f,a,b,e,vlb,vub,xint,scalemode,keep)
%
%     solves the MILP problem
%
%             max v = f'*x
%               a*x <> b
%                 vlb <= x <= vub
%                 x(int) are integer
%
%  ARGUMENTS: The first four arguments are required:
%
%           f: n vector of coefficients for a linear objective function.
%           a: m by n matrix representing linear constraints.
%           b: m vector of right sides for the inequality constraints.
%           e: m vector that determines the sense of the inequalities:
%                     e(i) = -1  ==> Less Than
%                     e(i) =  0  ==> Equals
%                     e(i) =  1  ==> Greater Than
%         vlb: n vector of lower bounds. If empty or omitted,
%              then the lower bounds are set to zero.
%         vub: n vector of upper bounds. May be omitted or empty.
%        xint: vector of integer variables. May be omitted or empty.
%   scalemode: scale flag. Off when 0 or omitted.
%        keep: Flag for keeping the lp problem after it's been solved.
%              If omitted, the lp will be deleted when solved.
%
%  OUTPUT: A nonempty output is returned if a solution is found:
%
%         obj: Optimal value of the objective function.
%           x: Optimal value of the decision variables.
%       duals: solution of the dual problem.

function [obj, x, duals, stat] = lp_solve(f, a, b, e, vlb, vub, xint, scalemode, keep)

  if nargin == 0
          help lp_solve;
          return;
  end

  [m,n] = size(a);
  lp = fmlpsolve('make_lp', m, n);
  fmlpsolve('set_verbose', lp, 3);
  fmlpsolve('set_mat', lp, a);
  fmlpsolve('set_rh_vec', lp, b);
  fmlpsolve('set_obj_fn', lp, f);
  fmlpsolve('set_maxim', lp); % default is solving minimum lp.

  for i = 1:size(e, 2)
    if e(i) < 0
          con_type = 1;
    elseif e(i) == 0
          con_type = 3;
    else
          con_type = 2;
    end
    fmlpsolve('set_constr_type', lp, i, con_type);
  end

  if nargin > 4
    for i = 1:size(vlb, 2)
      fmlpsolve('set_lowbo', lp, i, vlb(i));
    end
  end

  if nargin > 5
    for i = 1:size(vub, 2)
      fmlpsolve('set_upbo', lp, i, vub(i));
    end
  end

  if nargin > 6
    for i = 1:size(xint, 2)
      fmlpsolve('set_int', lp, xint(i), 1);
    end
  end

  if nargin > 7
    if scalemode ~= 0
      fmlpsolve('set_scaling', lp, scalemode);
    end
  end

  result=fmlpsolve('solve', lp);
  if result == 0 | result == 1 | result == 11 | result == 12
    [obj, x, duals] = fmlpsolve('get_solution', lp);
    stat = result;
  else
    obj = [];
    x = [];
    duals = [];
    stat = result;
  end

  if nargin < 9
    fmlpsolve('delete_lp', lp);
  end
