function lpmaker(f, a, b, e, vlb = [], vub = [], xint = [], scalemode = 0, setminim = 0)
##LPMAKER  Makes mixed integer linear programming problems.
##
##  SYNOPSIS: lp_handle = lpmaker(f,a,b,e,vlb,vub,xint,scalemode,setminim)
##     make the MILP problem
##       max v = f'*x
##         a*x <> b
##           vlb <= x <= vub
##           x(int) are integer
##
##  ARGUMENTS: The first four arguments are required:
##           f: n vector of coefficients for a linear objective function.
##           a: m by n matrix representing linear constraints.
##           b: m vector of right sides for the inequality constraints.
##           e: m vector that determines the sense of the inequalities:
##                     e(i) < 0  ==> Less Than
##                     e(i) = 0  ==> Equals
##                     e(i) > 0  ==> Greater Than
##         vlb: n vector of non-negative lower bounds. If empty or omitted,
##              then the lower bounds are set to zero.
##         vub: n vector of upper bounds. May be omitted or empty.
##        xint: vector of integer variables. May be omitted or empty.
##   scalemode: Autoscale flag. Off when 0 or omitted.
##    setminim: Set maximum lp when this flag equals 0 or omitted.
##
##  OUTPUT: lp_handle is an integer handle to the lp created.

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

  if setminim <> 0 then
    eulpsolve("set_minim", lp);
  else
    eulpsolve("set_maxim", lp);
  endif

  return lp

endfunction
