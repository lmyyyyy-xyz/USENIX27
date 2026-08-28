function lpsolve(f, a, b, e, vlb = [], vub = [], xint = [], scalemode = 0, keep = 0)
##LPSOLVE  Solves mixed integer linear programming problems.
##
##  SYNOPSIS: {obj, x, duals, stat} = lpsolve(f,a,b,e,vlb,vub,xint,scalemode,keep)
##
##     solves the MILP problem
##
##             max v = f'*x
##               a*x <> b
##                 vlb <= x <= vub
##                 x(int) are integer
##
##  ARGUMENTS: The first four arguments are required:
##
##           f: n vector of coefficients for a linear objective function.
##           a: m by n matrix representing linear constraints.
##           b: m vector of right sides for the inequality constraints.
##           e: m vector that determines the sense of the inequalities:
##                     e(i) = -1  ==> Less Than
##                     e(i) =  0  ==> Equals
##                     e(i) =  1  ==> Greater Than
##         vlb: n vector of lower bounds. If empty or omitted,
##              then the lower bounds are set to zero.
##         vub: n vector of upper bounds. May be omitted or empty.
##        xint: vector of integer variables. May be omitted or empty.
##   scalemode: scale flag. Off when 0 or omitted.
##        keep: Flag for keeping the lp problem after it's been solved.
##              If omitted, the lp will be deleted when solved.
##
##  OUTPUT: A nonempty output is returned if a solution is found:
##
##         obj: Optimal value of the objective function.
##           x: Optimal value of the decision variables.
##       duals: solution of the dual problem.

  m = rows(a);
  n = cols(a);
  lp = eulpsolve("make_lp", m, n);
  eulpsolve("set_verbose", lp, 3);
  eulpsolve("set_mat", lp, a);
  eulpsolve("set_rh_vec", lp, b);
  eulpsolve("set_obj_fn", lp, f);
  eulpsolve("set_maxim", lp); // default is solving minimum lp.

  for i = 1 to max(rows(e),cols(e))
    if e(i) < 0 then
          contype = 1;
    elseif e(i) == 0 then
          contype = 3;
    else
          contype = 2;
    endif
    eulpsolve("set_constr_type", lp, i, contype);
  end

  for i = 1 to max(rows(vlb),cols(vlb))
    eulpsolve("set_lowbo", lp, i, vlb(i));
  end

  for i = 1 to max(rows(vub),cols(vub))
    eulpsolve("set_upbo", lp, i, vub(i));
  end

  for i = 1 to max(rows(xint),cols(xint))
    eulpsolve("set_int", lp, xint(i), 1);
  end

  if scalemode <> 0 then
    eulpsolve("set_scaling", lp, scalemode);
  endif

  result=eulpsolve("solve", lp);
  if result == 0 || result == 1 || result == 11 || result == 12 then
    {obj, x, duals} = eulpsolve("get_solution", lp);
    stat = result;
  else
    obj = [];
    x = [];
    duals = [];
    stat = result;
  endif

  if keep == 0 then
    eulpsolve("delete_lp", lp);
  endif

  return {obj,x,duals,stat}

endfunction
