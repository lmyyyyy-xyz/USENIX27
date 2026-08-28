program demo;

{$APPTYPE CONSOLE}

uses
  SysUtils,
  lpsolve;

var
  majorversion, minorversion, release, build: integer;
  lp: THandle;

procedure press_ret;
begin
  writeln('[return]');
  readln;
end;

procedure error;
begin
  writeln('error');
  if (lp <> 0) then
    delete_lp(lp);
  readln;
  halt(1);
end;


begin
  lp_solve_version(@majorversion, @minorversion, @release, @build);
  writeln(format('lp_solve %d.%d.%d.%d demo', [majorversion, minorversion, release, build]));
  writeln(format('This demo will show most of the features of lp_solve %d.%d.%d.%d', [majorversion, minorversion, release, build]));
  press_ret;
  writeln('We start by creating a new problem with 4 variables and 0 constraints');
  writeln('We use: lp := make_lp(0, 4);');
  lp := make_lp(0, 4);
  if (lp = 0) then
    error;
  press_ret();

  writeln('We can show the current problem with print_lp(lp)');
  print_lp(lp);
  press_ret();
  writeln('Now we add some constraints');
  writeln('str_add_constraint(lp, ''3 2 2 1'', LE, 4)');
  writeln('This is the string version of add_constraint. For the normal version');
  writeln('of add_constraint see the help file');
  if (not str_add_constraint(lp, '3 2 2 1', LE, 4)) then
    error;
  print_lp(lp);
  press_ret();
  writeln('str_add_constraint(lp, ''0 4 3 1'', GE, 3)');
  if (not str_add_constraint(lp, '0 4 3 1', GE, 3)) then
    error;
  print_lp(lp);
  press_ret();
  writeln('Set the objective function');
  writeln('str_set_obj_fn(lp, ''2 3 -2 3'')');
  if (not str_set_obj_fn(lp, '2 3 -2 3')) then
    error;
  print_lp(lp);
  press_ret();
  writeln('Now solve the problem with writeln(solve(lp));');
  writeln(format('%d', [solve(lp)]));
  press_ret();
  writeln('The value is 0, this means we found an optimal solution');
  writeln('We can display this solution with print_objective(lp) and print_solution(lp)');
  print_objective(lp);
  print_solution(lp, 1);
  print_constraints(lp, 1);

  press_ret();
  writeln('The dual variables of the solution are printed with');
  writeln('print_duals(lp);');
  print_duals(lp);
  press_ret();
  writeln('We can change a single element in the matrix with');
  writeln('set_mat(lp, 2, 1, 0.5)');
  if (not set_mat(lp, 2, 1, 0.5)) then
    error;
  print_lp(lp);
  press_ret();
  writeln('If we want to maximize the objective function use set_maxim(lp);');
  set_maxim(lp);
  print_lp(lp);
  press_ret();
  writeln('after solving this gives us:');
  solve(lp);
  print_objective(lp);
  print_solution(lp, 1);
  print_constraints(lp, 1);
  print_duals(lp);
  press_ret();
  writeln('Change the value of a rhs element with set_rh(lp, 1, 7.45)');
  set_rh(lp, 1, 7.45);
  print_lp(lp);
  solve(lp);
  print_objective(lp);
  print_solution(lp, 1);
  print_constraints(lp, 1);
  press_ret();
  writeln(format('We change %s to the integer type with', [get_col_name(lp, 4)]));
  writeln('set_int(lp, 4, TRUE)');
  set_int(lp, 4, true);
  print_lp(lp);
  writeln('We set branch & bound debugging on with set_debug(lp, TRUE)');
  set_debug(lp, true);
  writeln('and solve...');
  press_ret();
  solve(lp);
  print_objective(lp);
  print_solution(lp, 1);
  print_constraints(lp, 1);
  press_ret();
  writeln('We can set bounds on the variables with');
  writeln('set_lowbo(lp,2,2); & set_upbo(lp,4,5.3)');
  set_lowbo(lp,2,2);
  set_upbo(lp,4,5.3);
  print_lp(lp);
  press_ret();
  solve(lp);
  print_objective(lp);
  print_solution(lp, 1);
  print_constraints(lp, 1);
  press_ret();
  writeln('Now remove a constraint with del_constraint(lp, 1)');
  del_constraint(lp,1);
  print_lp(lp);
  writeln('Add an equality constraint');
  if (not str_add_constraint(lp, '1 2 1 4', EQ, 8)) then
    error;
  print_lp(lp);
  press_ret();
  writeln('A column can be added with:');
  writeln('str_add_column(lp,''3 2 2'');');
  if (not str_add_column(lp,'3 2 2')) then
    error;
  print_lp(lp);
  press_ret();
  writeln('A column can be removed with:');
  writeln('del_column(lp,3);');
  del_column(lp,3);
  print_lp(lp);
  press_ret();
  writeln('We can use automatic scaling with:');
  writeln('set_scaling(lp, SCALE_MEAN);');
  set_scaling(lp, SCALE_MEAN);
  print_lp(lp);
  press_ret();
  writeln('The function get_mat(lp: THandle; row: Integer; column: Integer) returns a single');
  writeln('matrix element');
  writeln('writeln(format(''%f %f'', [get_mat(lp, 2, 3), get_mat(lp, 1, 1)])); give');
  writeln(format('%f %f', [get_mat(lp, 2, 3), get_mat(lp, 1, 1)]));
  writeln('Notice that get_mat returns the value of the original unscaled problem');
  press_ret();
  writeln('If there are any integer type variables, then only the rows are scaled');
  writeln('set_int(lp,3,FALSE);');
  writeln('set_scaling(lp, SCALE_MEAN);');
  set_scaling(lp, SCALE_MEAN);
  set_int(lp, 3, false);
  print_lp(lp);
  press_ret();
  solve(lp);
  writeln('print_objective, print_solution gives the solution to the original problem');
  print_objective(lp);
  print_solution(lp, 1);
  print_constraints(lp, 1);
  press_ret();
  writeln('Scaling is turned off with unscale(lp);');
  unscale(lp);
  print_lp(lp);
  press_ret();
  writeln('Now turn B&B debugging off and simplex tracing on with');
  writeln('set_debug(lp, FALSE), set_trace(lp, TRUE) and solve(lp)');
  set_debug(lp, false);
  set_trace(lp, false);
  press_ret();
  solve(lp);
  writeln('Where possible, lp_solve will start at the last found basis');
  writeln('We can reset the problem to the initial basis with');
  writeln('default_basis(lp). Now solve it again...');
  press_ret();
  default_basis(lp);
  solve(lp);

  writeln('It is possible to give variables and constraints names');
  writeln('set_row_name(lp,1, ''speed''); & set_col_name(lp, 2, ''money'')');
  if (not set_row_name(lp,1,'speed')) then
    error;
  if (not set_col_name(lp,2,'money')) then
    error;
  print_lp(lp);
  writeln('As you can see, all column and rows are assigned default names');
  writeln('If a column or constraint is deleted, the names shift place also:');
  press_ret();
  writeln('del_column(lp,1);');
  del_column(lp,1);
  print_lp(lp);
  press_ret();

  delete_lp(lp);

  writeln('A lp structure can be created and read from a .lp file');
  writeln('lp = read_lp(''lp.lp'', TRUE);');
  writeln('The verbose option is used');
  lp := read_LP(PChar('lp.lp'), CRITICAL, PChar('test'));
  if (lp = 0) then
    error;
  press_ret();
  writeln('lp is now:');
  print_lp(lp);

  press_ret();
  writeln('solution:');
  set_debug(lp, true);
  solve(lp);
  set_debug(lp, false);
  print_objective(lp);
  print_solution(lp, 1);
  print_constraints(lp, 1);
  press_ret();
  writeln('You can see that branch & bound was used in this problem');
  delete_lp(lp);
  press_ret();
end.
