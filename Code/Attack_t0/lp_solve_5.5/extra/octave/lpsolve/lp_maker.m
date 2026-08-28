#LP_MAKER  Makes mixed integer linear programming problems.
#
#  SYNOPSIS: lp_handle = lp_maker(f,a,b,e,vlb,vub,xint,scalemode,setminim)
#     make the MILP problem
#       max v = f'*x
#         a*x <> b
#           x >= vlb >= 0
#           x <= vub
#           x(int) are integer
#
#  ARGUMENTS: The first four arguments are required:
#           f: n vector of coefficients for a linear objective function.
#           a: m by n matrix representing linear constraints.
#           b: m vector of right sides for the inequality constraints.
#           e: m vector that determines the sense of the inequalities:
#                     e(i) < 0  ==> Less Than
#                     e(i) = 0  ==> Equals
#                     e(i) > 0  ==> Greater Than
#         vlb: n vector of non-negative lower bounds. If empty or omitted,
#              then the lower bounds are set to zero.
#         vub: n vector of upper bounds. May be omitted or empty.
#        xint: vector of integer variables. May be omitted or empty.
#   scalemode: Autoscale flag. Off when 0 or omitted.
#    setminim: Set maximum lp when this flag equals 0 or omitted.
#
#  OUTPUT: lp_handle is an integer handle to the lp created.

function lp_handle = lp_maker(f,a,b,e,vlb,vub,xint,scalemode,setminim)

if nargin == 0
        help lp_solve;
        return;
end

[m,n] = size(a);
lp_handle = octlpsolve('make_lp', m, n);
octlpsolve('set_verbose', lp_handle, 3);
octlpsolve('set_mat', lp_handle, a);
octlpsolve('set_rh_vec', lp_handle, b);
octlpsolve('set_obj_fn', lp_handle, f);
octlpsolve('set_maxim', lp_handle); % default is solving minimum lp.

for i = 1:length(e)
  if e(i) < 0
        con_type = 1;
  elseif e(i) == 0
        con_type = 3;
  else
        con_type = 2;
  end
  octlpsolve('set_constr_type', lp_handle, i, con_type);
end

if nargin > 4
  for i = 1:length(vlb)
    octlpsolve('set_lowbo', lp_handle, i, vlb(i));
  end
end

if nargin > 5
  for i = 1:length(vub)
    octlpsolve('set_upbo', lp_handle, i, vub(i));
  end
end

if nargin > 6
  for i = 1:length(xint)
    octlpsolve('set_int', lp_handle, xint(i), 1);
  end
end

if nargin > 7
  if scalemode ~= 0
    octlpsolve('set_scaling', lp_handle, scalemode);
  end
end

if nargin > 8
  if setminim ~= 0
    octlpsolve('set_minim', lp_handle);
  else
    octlpsolve('set_maxim', lp_handle);
  end
end
