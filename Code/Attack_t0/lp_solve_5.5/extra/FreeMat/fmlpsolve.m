%fmlpsolve FreeMat Interface for lpsolve
%
%Usage: ret = fmlpsolve(functionname, arg1, arg2, ...)

function [varargout] = fmlpsolve(varargin)
  if (nargout == 0)
    nargout = 1;
  end

  if (strcomp(computer,'PCWIN'))
    lib = 'fmlpsolve.dll';
  else
    lib = 'fmlpsolve.so';
  end

  n = 0;
  m = 0;
  if (nargin >= 1)
    switch (varargin{1})
    case { 'get_basis', 'get_column', 'get_columnex', 'get_constr_type', 'get_constraints', 'get_dual_solution', 'get_lowbo', 'get_upbo', 'get_primal_solution', 'get_rh', 'get_rh_range', 'get_row', 'get_rowex', 'get_sensitivity_obj', 'get_sensitivity_objex', 'get_sensitivity_rhs', 'get_sensitivity_rhsex', 'get_var_branch', 'get_var_priority', 'get_variables', 'guess_basis', 'is_binary', 'is_free', 'is_unbounded', 'is_int', 'is_negative', 'is_semicont', 'is_SOS_var', 'get_constr_types', 'get_int', 'get_obj_fn', 'get_obj_fun', 'get_reduced_costs', 'get_solution', 'get_mat' }
      lp = varargin{2};
      format = ['int32 &a, string function, ', typeof(lp), ' lp'];
      import(lib,'fmlpsolve','fmlpsolvelib','void',['int32 nargin, int32 nargout, string format, ', format]);
      fmlpsolvelib(2, 1, format, n, 'get_Ncolumns', lp);
      fmlpsolvelib(2, 1, format, m, 'get_Nrows', lp);
    end
    m1 = 1;
    n1 = 1;
    m2 = 1;
    n2 = 1;
    m3 = 1;
    n3 = 1;
    m4 = 1;
    n4 = 1;
    switch (varargin{1})
    case 'get_basis'
      m1 = m;
      if (nargin >= 3)
        if (varargin{3} ~= 0)
          m1 = m1 + n;
        end
      end
    case { 'get_column', 'get_columnex' }
      m1 = 1 + m;
    case 'get_constraints'
      m1 = m;
    case { 'get_row', 'get_obj_fn', 'get_obj_fun' }
      n1 = n;
    case 'get_solution'
      m2 = n;
      m3 = m;
    case { 'get_sensitivity_obj', 'get_sensitivity_objex' }
      n1 = n;
      n2 = n;
      n3 = n;
      n4 = n;
    case 'get_variables'
      m1 = n;
    case { 'get_dual_solution', 'get_reduced_costs', 'guess_basis' }
      m1 = m + n;
    case { 'get_primal_solution' }
      n1 = 1 + m + n;
    case { 'get_sensitivity_rhs', 'get_sensitivity_rhsex' }
      m1 = m + n;
      m2 = m1;
      m3 = m1;
    case { 'get_constr_type', 'get_rh_range', 'get_constr_types' }
      if (nargin == 2)
        m1 = m;
      end
    case 'get_rh'
      if (nargin == 2)
        m1 = 1 + m;
      end
    case { 'is_binary', 'is_free', 'is_unbounded', 'is_int', 'is_negative', 'is_semicont', 'is_SOS_var', 'get_int', 'get_var_priority', 'get_var_branch', 'get_lowbo', 'get_upbo' }
      if (nargin == 2)
        m1 = n;
      end
    case 'get_mat'
      if ((nargin == 2) || (nargin == 3))
        m1 = m;
        n1 = n;
      end
    end

    str = varargin{1};

    switch (str)
    case { 'get_anti_degen', 'get_basiscrash', 'get_bb_floorfirst', 'get_bb_rule', 'get_improve', 'get_pivoting', 'get_presolve', 'get_scaling', 'get_simplextype', 'get_verbose', 'solve', 'get_constr_type', 'get_constr_types', 'get_var_branch' }
      format = ['int32 &a, string function'];
      import(lib,'fmlpsolve','fmlpsolvelib','void',['int32 nargin, int32 nargout, string format, ', format]);
      return_constants = 0;
      fmlpsolvelib(1, 1, format, return_constants, 'return_constants');
      if (return_constants ~= 0)
        str = '<return_constants>';
      end
    end

    switch (str)
    case { '<return_constants>' }
      varargout = { string(ones(1,256)) };
    case { 'lp_solve_version', 'get_statustext', 'get_lp_name', 'get_problem_name', 'get_objective_name', 'get_col_name', 'get_row_name', 'get_origcol_name', 'get_origrow_name' }
      varargout = { string(ones(1,256)) };
    case 'print_handle'
      if ((nargin ~= 2) | (varargin{2} == 0))
        m1 = fmlpsolve('print_handle', 1);
        if (m1 == 0)
          varargout = { [] };
        else
          varargout = { zeros(m1, 1) };
        end
      else
        varargout = { zeros(1, 1) };
      end
    case 'read_basis'
      switch (nargout)
      case 1
        varargout = { zeros(m1, n1) };
      case 2
        varargout = { zeros(m1, n1), string(ones(1,256)) };
      end
    otherwise
      switch (nargout)
      case 1
        varargout = { zeros(m1, n1) };
      case 2
        varargout = { zeros(m1, n1), zeros(m2, n2) };
      case 3
        varargout = { zeros(m1, n1), zeros(m2, n2), zeros(m3, n3) };
      case 4
        varargout = { zeros(m1, n1), zeros(m2, n2), zeros(m3, n3), zeros(m4, n4) };
      otherwise
        varargout = { zeros(m1, n1), zeros(m2, n2), zeros(m3, n3), zeros(m4, n4), zeros(1) };
      end
    end
  else
    varargout = { zeros(1) };
  end
%printf('m = %d, n = %d, m1 = %d, n1 = %d\n', m, n, m1, n1);

%varargin{:}
%varargout{:}

  str = '';
  j = 0;

  for (i = 1 : nargout)
    m = size(varargout{i}, 1);
    n = size(varargout{i}, 2);
    t = typeof(varargout{i});
    %if ((isscalar(varargout{i})) | ((isstr(varargout{i})) & (m == 1)))
    if ((m == 1) & ((n == 1) | (strcomp(t, 'string') == 1)))
      j = j + 1;
      str = [str, ', ', t, ' &a', num2str(j)];
    %elseif (isvector(varargout{i}))
    elseif (m == 1)
      j = j + 1;
      str = [str, ', ', t, '[', num2str(n), '] &a', num2str(j)];
    else
      j = j + 1;
      str = [str, ', ', t, '[', num2str(m), '*', num2str(n), '] &a', num2str(j)];
    end
  end

  for (i = 1 : nargin)
    switch (class(varargin{1}))
    case {'uint8','int8','uint16','int16','uint32','int32','uint64','int64','float','double','string'}
    otherwise
      error(['Input argument ', num2str(i), ' is of unsupported type (', class(varargin{i}), ')' ]);
    end
    m = size(varargin{i}, 1);
    n = size(varargin{i}, 2);
    t = typeof(varargin{i});
    %if ((isscalar(varargin{i})) | ((isstr(varargin{i})) & (m == 1)))
    if ((m == 1) & ((n == 1) | (strcomp(t, 'string') == 1)))
      j = j + 1;
      str = [str, ', ', t, ' a', num2str(j)];
    %elseif (isvector(varargin{i}))
    elseif (m == 1)
      j = j + 1;
      str = [str, ', ', t, '[', num2str(n), '] a', num2str(j)];
    else
      j = j + 1;
      str = [str, ', ', t, '[', num2str(m), '*', num2str(n), '] a', num2str(j)];
    end
  end

  format = str(3:size(str, 2));
%printf('format = %s\n', format);
  if (nargin > 0)
%['int32 nargin, int32 nargout, string format, ', format]
    import(lib,'fmlpsolve','fmlpsolvelib','void',['int32 nargin, int32 nargout, string format, ', format]);
%varargin{:}
%varargout{:}
%varargout
%{ varargin{:}, varargout{:} }

%{ varargin, varargout }

%    fmlpsolvelib(nargin, nargout, format, varargout{:}, varargin{:});
    switch (nargout)
    case 0
      fmlpsolvelib(nargin, nargout, format, varargin{:});
    case 1
      fmlpsolvelib(nargin, nargout, format, varargout{1}, varargin{:});
    case 2
      fmlpsolvelib(nargin, nargout, format, varargout{1}, varargout{2}, varargin{:});
    case 3
      fmlpsolvelib(nargin, nargout, format, varargout{1}, varargout{2}, varargout{3}, varargin{:});
    case 4
      fmlpsolvelib(nargin, nargout, format, varargout{1}, varargout{2}, varargout{3}, varargout{4}, varargin{:});
    case 5
      fmlpsolvelib(nargin, nargout, format, varargout{1}, varargout{2}, varargout{3}, varargout{4}, varargout{5}, varargin{:});
    end
    %if (isstr(varargout{1}))
    if (strcomp(typeof(varargout{1}), 'string') == 1)
      if ((size(varargout{1}, 2) > 0) & (varargout{1}(1) == 1))
        varargout{1} = '';
      end
    end
    switch (varargin{1})
    case 'get_mat'
      if (nargin == 3)
        if (varargin{3} ~= 0)
          varargout{1} = sparse(varargout{1});
        end
      end
    end
  else
    import(lib,'fmlpsolve','fmlpsolvelib','void','int32 nargin, int32 nargout, string format');
    fmlpsolvelib(0, 0, '');
  end
%varargout{:}
  %varargout = { format };

