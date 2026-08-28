program demo;

{$APPTYPE CONSOLE}

uses
  SysUtils,
  lpsolve;

var
  Ncol, j, ret: integer;
  colno: PIntArray;
  row: PFloatArray;
  lp: THandle;

begin
  ret := 0;
  colno := nil;
  row := nil;

  (* We will build the model row by row
     So we start with creating a model with 0 rows and 2 columns *)
  Ncol := 2; (* there are two variables in the model *)
  lp := make_lp(0, Ncol);
  if (lp = 0) then
    ret := 1; (* couldn't construct a new model... *)
  (* let us name our variables. Not required, but can be usefull for debugging *)
  set_col_name(lp, 1, 'x');
  set_col_name(lp, 2, 'y');

  if (ret = 0) then
  begin
    (* create space large enough for one row *)
    GetMem(colno, SizeOf(integer) * Ncol);
    GetMem(row, SizeOf(double) * Ncol);
    if ((colno = nil) or (row = nil)) then
      ret := 2;
  end;

  if (ret = 0) then
  begin
    set_add_rowmode(lp, true);  (* makes building the model faster if it is done rows by row *)

    (* construct first row (120 x + 210 y <= 15000) *)
    j := 0;

    colno^[j] := 1; (* first column *)
    row^[j] := 120;
    j := j + 1;

    colno^[j] := 2; (* second column *)
    row^[j] := 210;
    j := j + 1;

    (* add the row to lp_solve *)
    if (not add_constraintex(lp, j, row, colno, LE, 15000)) then
      ret := 3;
  end;

  if (ret = 0) then
  begin
    (* construct second row (110 x + 30 y <= 4000) *)
    j := 0;

    colno^[j] := 1; (* first column *)
    row^[j] := 110;
    j := j + 1;

    colno^[j] := 2; (* second column *)
    row^[j] := 30;
    j := j + 1;

    (* add the row to lp_solve *)
    if (not add_constraintex(lp, j, row, colno, LE, 4000)) then
      ret := 3;
  end;

  if (ret = 0) then
  begin
    (* construct third row (x + y <= 75) *)
    j := 0;

    colno^[j] := 1; (* first column *)
    row^[j] := 1;
    j := j + 1;

    colno^[j] := 2; (* second column *)
    row^[j] := 1;
    j := j + 1;

    (* add the row to lp_solve *)
    if (not add_constraintex(lp, j, row, colno, LE, 75)) then
      ret := 3;
  end;

  if (ret = 0) then
  begin
    set_add_rowmode(lp, false); (* rowmode should be turned off again when done building the model *)

    (* set the objective function (143 x + 60 y) *)
    j := 0;

    colno^[j] := 1; (* first column *)
    row^[j] := 143;
    j := j + 1;

    colno^[j] := 2; (* second column *)
    row^[j] := 60;
    j := j + 1;

    (* set the objective in lp_solve *)
    if (not set_obj_fnex(lp, j, row, colno)) then
      ret := 4;
  end;

  if (ret = 0) then
  begin
    (* set the object direction to maximize *)
    set_maxim(lp);

    (* just out of curioucity, now show the model in lp format on screen *)
    (* this only works if this is a console application. If not, use write_lp and a filename *)
    (* write_LP(lp, stdout); *)
    write_lp(lp, 'model.lp');

    (* I only want to see importand messages on screen while solving *)
    set_verbose(lp, IMPORTANT);

    (* Now let lp_solve calculate a solution *)
    ret := solve(lp);
    if (ret = OPTIMAL) then
      ret := 0
    else
      ret := 5;
  end;

  if (ret = 0) then
  begin
    (* a solution is calculated, now lets get some results *)

    (* objective value *)
    writeln(format('Objective value: %f', [get_objective(lp)]));

    (* variable values *)
    get_variables(lp, row);
    for j := 0 to Ncol-1 do
      writeln(format('%s: %f', [get_col_name(lp, j + 1), row^[j]]));

    (* we are done now *)
  end;

  (* free allocated memory *)
  if (row <> nil) then
    FreeMem(row);
  if (colno <> nil) then
    FreeMem(colno);

  if(lp <> 0) then
  begin
    (* clean up such that all used memory by lp_solve is freeed *)
    delete_lp(lp);
  end;
end.
