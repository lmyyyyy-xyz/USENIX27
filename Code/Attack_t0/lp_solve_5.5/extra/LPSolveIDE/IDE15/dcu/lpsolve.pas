(*
 *  lp_solve v5 API for Delphi v5,6,7 & FPC compiler v1.9.x
 *  Licence LGPL
 *  Author: Henri Gourvest
 *  email: hgourvest@progdigy.com
 *  homepage: http://www.progdigy.com
 *  date: 07/21/2004
 *
 *  Important information
 *  Solver library is compiled for a different Control Word, you should change
 *  the Delphi control Word to avoid foating point operation errors.
 *                _control87     Set8087CW
 *  Visual Studio $9001F     ->   639
 *  GCC           $8001F     ->   895
 *)

{$I lpsolve.inc}


{$ALIGN ON}
{$MINENUMSIZE 4}
{$IFNDEF FPC}
  {$WEAKPACKAGEUNIT}
{$ELSE}
  {$MODE DELPHI}
{$ENDIF}
{$IFDEF LINUX}
  {$DEFINE UNIX}
{$ENDIF}

unit lpsolve;

interface

const
  MAXLONG = $7FFFFFFF;

type
  PIntArray = ^TIntArray;
  TIntArray = array[0..MAXLONG div SizeOf(Integer)-1] of Integer;

  PFloatArray = ^TFloatArray;
  TFloatArray = array[0..(MAXLONG div SizeOf(Double))-1] of Double;

  PPtrArray = ^TPtrArray;
  TPtrArray = array[0..(MAXLONG div SizeOf(Pointer))-1] of Pointer;

{$IFNDEF FPC}
{$IFDEF VER130}
  THandle = LongWord;
  Pinteger = ^integer;
  PDouble = ^double;
{$ENDIF}
{$ENDIF}

(* MYBOOL *)
const
  _FALSE      = 0;
  _TRUE       = 1;
  _AUTOMATIC  = 2;
  _DYNAMIC    = 4;

(* Prototypes for call-back functions                                        *)
type
{$IFDEF LPS55_UP}
  lphandle_intfunc = function(lp: THandle; userhandle: Pointer): Integer; stdcall;
  lphandlestr_func = procedure(lp: THandle; userhandle: Pointer; buf: PChar); stdcall;
  lphandleint_func = procedure(lp: THandle; userhandle: Pointer; message: Integer); stdcall;
  lphandleint_intfunc = function(lp: THandle; userhandle: Pointer; message: Integer): Integer; stdcall;
{$ELSE}
  ctrlcfunc = function(lp: THandle; userhandle: Pointer): integer; stdcall;
  logfunc = procedure(lp: THandle; userhandle: Pointer; buf: PChar); stdcall;
  msgfunc = procedure(lp: THandle; userhandle: Pointer; message: integer); stdcall;
{$ENDIF}

{$IFDEF LPS55_UP}
  COUNTER = Int64;
{$ELSE}
  COUNTER = Integer;
{$ENDIF}

(* Definition of program constrants                                          *)
const
  SIMPLEX_UNDEFINED       =  0;
  SIMPLEX_Phase1_PRIMAL   =  1;
  SIMPLEX_Phase1_DUAL     =  2;
  SIMPLEX_Phase2_PRIMAL   =  4;
  SIMPLEX_Phase2_DUAL     =  8;
  SIMPLEX_DYNAMIC         = 16;
{$IFDEF LPS55_UP}
  SIMPLEX_AUTODUALIZE     = 32;
{$ENDIF}

  SIMPLEX_PRIMAL_PRIMAL   = SIMPLEX_Phase1_PRIMAL + SIMPLEX_Phase2_PRIMAL;
  SIMPLEX_DUAL_PRIMAL     = SIMPLEX_Phase1_DUAL   + SIMPLEX_Phase2_PRIMAL;
  SIMPLEX_PRIMAL_DUAL     = SIMPLEX_Phase1_PRIMAL + SIMPLEX_Phase2_DUAL;
  SIMPLEX_DUAL_DUAL       = SIMPLEX_Phase1_DUAL   + SIMPLEX_Phase2_DUAL;
  SIMPLEX_DEFAULT         = SIMPLEX_DUAL_PRIMAL;

(* Presolve defines *)
  PRESOLVE_NONE          =      0;
  PRESOLVE_ROWS          =      1;
  PRESOLVE_COLS          =      2;
  PRESOLVE_LINDEP        =      4;
  PRESOLVE_AGGREGATE     =      8;
  PRESOLVE_SPARSER       =     16;
  PRESOLVE_SOS           =     32;
  PRESOLVE_REDUCEMIP     =     64;
{$IFDEF LPS55_UP}
  PRESOLVE_KNAPSACK      =     128;  // Implementation not tested completely
  PRESOLVE_ELIMEQ2       =     256;
  PRESOLVE_IMPLIEDFREE   =     512;
  PRESOLVE_REDUCEGCD     =    1024;
  PRESOLVE_PROBEFIX      =    2048;
  PRESOLVE_PROBEREDUCE   =    4096;
  PRESOLVE_ROWDOMINATE   =    8192;
  PRESOLVE_COLDOMINATE   =   16384;
  PRESOLVE_MERGEROWS     =   32768;
  PRESOLVE_IMPLIEDSLK    =   65536;
  PRESOLVE_COLFIXDUAL    =  131072;
  PRESOLVE_BOUNDS        =  262144;
  PRESOLVE_DUALS         =  524288;
  PRESOLVE_SENSDUALS     = 1048576;
{$ELSE}
  PRESOLVE_DUALS         =     128;
  PRESOLVE_SENSDUALS     =     256;
{$ENDIF}
  PRESOLVE_LASTMASKMODE  = (PRESOLVE_DUALS - 1);

(* Basis crash options *)
  CRASH_NONE              = 0;
  CRASH_NONBASICBOUNDS    = 1;
  CRASH_MOSTFEASIBLE      = 2;
  CRASH_LEASTDEGENERATE   = 3;

(* Strategy codes to avoid or recover from degenerate pivots,
   infeasibility or numeric errors via randomized bound relaxation *)
  ANTIDEGEN_NONE          =   0;
  ANTIDEGEN_FIXEDVARS     =   1;
  ANTIDEGEN_COLUMNCHECK   =   2;
  ANTIDEGEN_STALLING      =   4;
  ANTIDEGEN_NUMFAILURE    =   8;
  ANTIDEGEN_LOSTFEAS      =  16;
  ANTIDEGEN_INFEASIBLE    =  32;
  ANTIDEGEN_DYNAMIC       =  64;
  ANTIDEGEN_DURINGBB      = 128;
{$IFDEF LPS55_UP}
  ANTIDEGEN_RHSPERTURB    = 256;
  ANTIDEGEN_BOUNDFLIP     = 512;
{$ENDIF}
  ANTIDEGEN_DEFAULT       = (ANTIDEGEN_FIXEDVARS or ANTIDEGEN_STALLING or ANTIDEGEN_INFEASIBLE);

(* Constraint type codes *)
  FR                      = 0;
  LE                      = 1;
  GE                      = 2;
  EQ                      = 3;
  OF_                     = 4;

(* Improvement defines *)
{$IFDEF LPS51}
  IMPROVE_NONE            = 0;
  IMPROVE_FTRAN           = 1;
  IMPROVE_BTRAN           = 2;
  IMPROVE_SOLVE           = (IMPROVE_FTRAN + IMPROVE_BTRAN);
  IMPROVE_INVERSE         = 4;
{$ENDIF}
{$IFDEF LPS55}
  IMPROVE_NONE            = 0;
  IMPROVE_SOLUTION        = 1;
  IMPROVE_DUALFEAS        = 2;
  IMPROVE_THETAGAP        = 4;
  IMPROVE_BBSIMPLEX       = 8;
  IMPROVE_DEFAULT         = (IMPROVE_DUALFEAS + IMPROVE_THETAGAP);
  IMPROVE_INVERSE         = (IMPROVE_SOLUTION + IMPROVE_THETAGAP);
{$ENDIF}

(* Scaling types *)
  SCALE_NONE              = 0;
  SCALE_EXTREME           = 1;
  SCALE_RANGE             = 2;
  SCALE_MEAN              = 3;
  SCALE_GEOMETRIC         = 4;
  SCALE_FUTURE1           = 5;
  SCALE_FUTURE2           = 6;
  SCALE_CURTISREID        = 7;   // Override to Curtis-Reid "optimal" scaling

(* Alternative scaling weights *)
  SCALE_LINEAR           =  0;
  SCALE_QUADRATIC        =  8;
  SCALE_LOGARITHMIC      = 16;
  SCALE_USERWEIGHT       = 31;
  SCALE_MAXTYPE          = (SCALE_QUADRATIC-1);

(* Scaling modes *)
  SCALE_POWER2          =  32;   (* As is or rounded to power of 2 *)
  SCALE_EQUILIBRATE     =  64;   (* Make sure that no scaled number is above 1 *)
  SCALE_INTEGERS        = 128;   (* Apply to integer columns/variables *)
  SCALE_DYNUPDATE       = 256;   (* Apply incrementally every solve() *)
{$IFDEF LPS55_UP}
  SCALE_ROWSONLY        = 512;   (* Override any scaling to only scale the rows *)
  SCALE_COLSONLY       = 1024;   (* Override any scaling to only scale the rows *)
{$ENDIF}

(* Pricing methods *)
  PRICER_FIRSTINDEX       = 0;
  PRICER_DANTZIG          = 1;
  PRICER_DEVEX            = 2;
  PRICER_STEEPESTEDGE     = 3;
  PRICER_LASTOPTION       = PRICER_STEEPESTEDGE;

(* Pricing strategies *)
  PRICE_METHODDEFAULT   =    0;
  PRICE_PRIMALFALLBACK  =    4;    (* In case of Steepest Edge, fall back to DEVEX in primal *)
  PRICE_MULTIPLE        =    8;    (* Enable multiple pricing (primal simplex) *)
  PRICE_PARTIAL         =   16;    (* Enable partial pricing (primal simplex) *)
  PRICE_ADAPTIVE        =   32;    (* Temporarily use First Index if cycling is detected *)
  PRICE_HYBRID          =   64;    (* NOT IMPLEMENTED *)
  PRICE_RANDOMIZE       =  128;    (* Adds a small randomization effect to the selected pricer *)
{$IFDEF LPS55_UP}
  PRICE_AUTOPARTIAL     = 256;    (* Detect and use data on the block structure of the model (primal) *)
  PRICE_AUTOMULTIPLE    = 512;    (* Automatically select multiple pricing (primal simplex) *)
{$ELSE}
  PRICE_AUTOPARTIALCOLS =  256;    (* Detect and use data on the block structure of the model (primal) *)
  PRICE_AUTOPARTIALROWS =  512;    (* Detect and use data on the block structure of the model (dual) *)
{$ENDIF}
  PRICE_LOOPLEFT        = 1024;    (* Scan entering/leaving columns left rather than right *)
  PRICE_LOOPALTERNATE   = 2048;    (* Scan entering/leaving columns alternatingly left/right *)
{$IFDEF LPS55_UP}
  PRICE_HARRISTWOPASS   =  4096;    (* Use Harris' primal pivot logic rather than the default *)
  PRICE_FORCEFULL       =  8192;    (* Non-user option to force full pricing *)
  PRICE_TRUENORMINIT    = 16384;    (* Use true norms for Devex and Steepest Edge initializations *)
{$ELSE}
  PRICE_AUTOMULTICOLS   = 4096;    (* Automatically select multiple pricing (primal) *)
  PRICE_AUTOMULTIROWS   = 8192;    (* Automatically select multiple pricing (dual) *)
{$ENDIF}



{$IFDEF LPS55_UP}
  PRICE_STRATEGYMASK    = (PRICE_METHODDEFAULT + PRICE_PRIMALFALLBACK + PRICE_MULTIPLE + PRICE_PARTIAL +
                            PRICE_ADAPTIVE + PRICE_HYBRID + PRICE_RANDOMIZE + PRICE_AUTOPARTIAL +
                            PRICE_AUTOMULTIPLE +  PRICE_HARRISTWOPASS + PRICE_LOOPLEFT + PRICE_LOOPALTERNATE +
                            PRICE_FORCEFULL + PRICE_TRUENORMINIT);
{$ELSE}
  PRICE_AUTOPARTIAL     = (PRICE_AUTOPARTIALCOLS + PRICE_AUTOPARTIALROWS);
  PRICE_AUTOMULTIPLE    = (PRICE_AUTOMULTICOLS + PRICE_AUTOMULTIROWS);
  PRICE_STRATEGYMASK    = (PRICE_METHODDEFAULT + PRICE_PRIMALFALLBACK + PRICE_MULTIPLE + PRICE_PARTIAL +
                            PRICE_ADAPTIVE + PRICE_HYBRID + PRICE_RANDOMIZE + PRICE_AUTOPARTIAL +
                            PRICE_AUTOMULTIPLE + PRICE_LOOPLEFT + PRICE_LOOPALTERNATE);
{$ENDIF}


  PRICER_RANDFACT       = 0.1;

(* B&B strategies *)
  NODE_FIRSTSELECT         =    0;
  NODE_GAPSELECT           =    1;
  NODE_RANGESELECT         =    2;
  NODE_FRACTIONSELECT      =    3;
  NODE_PSEUDOCOSTSELECT    =    4;
  NODE_PSEUDONONINTSELECT  =    5;    (* Kjell Eikland #1 - Minimize B&B depth *)
  NODE_PSEUDORATIOSELECT   =    6;    (* Kjell Eikland #2 - Minimize a "cost/benefit" ratio *)
  NODE_USERSELECT          =    7;
  NODE_WEIGHTREVERSEMODE   =    8;
  NODE_STRATEGYMASK        = (NODE_WEIGHTREVERSEMODE-1); (* Mask for B&B strategies *)
{$IFDEF LPS55_UP}
  NODE_PSEUDOFEASSELECT    = (NODE_PSEUDONONINTSELECT + NODE_WEIGHTREVERSEMODE);
{$ENDIF}
  NODE_BRANCHREVERSEMODE   =   16;
  NODE_GREEDYMODE          =   32;
  NODE_PSEUDOCOSTMODE      =   64;
  NODE_DEPTHFIRSTMODE      =  128;
  NODE_RANDOMIZEMODE       =  256;
  NODE_GUBMODE             =  512;
  NODE_DYNAMICMODE         = 1024;
  NODE_RESTARTMODE         = 2048;
  NODE_BREADTHFIRSTMODE    = 4096;
  NODE_AUTOORDER           = 8192;
{$IFDEF LPS55_UP}
  NODE_RCOSTFIXING         = 16384;
  NODE_STRONGINIT          = 32768;
{$ELSE}
  NODE_PSEUDOFEASSELECT    = (NODE_PSEUDONONINTSELECT+NODE_WEIGHTREVERSEMODE);
{$ENDIF}

  BRANCH_CEILING          = 0;
  BRANCH_FLOOR            = 1;
  BRANCH_AUTOMATIC        = 2;
  BRANCH_DEFAULT          = 3;

(* Solver status values *)
  UNKNOWNERROR            = -5;
  DATAIGNORED             = -4;
  NOBFP                   = -3;
  NOMEMORY                = -2;
  NOTRUN                  = -1;
  OPTIMAL                 =  0;
  SUBOPTIMAL              =  1;
  INFEASIBLE              =  2;
  UNBOUNDED               =  3;
  DEGENERATE              =  4;
  NUMFAILURE              =  5;
  USERABORT               =  6;
  TIMEOUT                 =  7;
  RUNNING                 =  8;
  PRESOLVED               =  9;

(* Branch & Bound and Lagrangean extra status values *)
  PROCFAIL               = 10;
  PROCBREAK              = 11;
  FEASFOUND              = 12;
  NOFEASFOUND            = 13;
{$IFDEF LPS55_UP}
  FATHOMED               = 14;
{$ENDIF}

(* REPORT defines *)
  NEUTRAL                 = 0;
  CRITICAL                = 1;
  SEVERE                  = 2;
  IMPORTANT               = 3;
  NORMAL                  = 4;
  DETAILED                = 5;
  FULL                    = 6;

(* MESSAGE defines *)
  MSG_NONE             =    0;
  MSG_PRESOLVE         =    1;
  MSG_ITERATION        =    2;
  MSG_INVERT           =    4;
  MSG_LPFEASIBLE       =    8;
  MSG_LPOPTIMAL        =   16;
  MSG_LPEQUAL          =   32;
  MSG_LPBETTER         =   64;
  MSG_MILPFEASIBLE     =  128;
  MSG_MILPEQUAL        =  256;
  MSG_MILPBETTER       =  512;
  MSG_MILPSTRATEGY     = 1024;
  MSG_MILPOPTIMAL      = 2048;
  MSG_PERFORMANCE      = 4096;
  MSG_INITPSEUDOCOST   = 8192;


// Parameters constants for short-cut setting of tolerances
// --------------------------------------------------------------------------------------
  EPS_TIGHT                = 0;
  EPS_MEDIUM               = 1;
  EPS_LOOSE                = 2;
  EPS_BAGGY                = 3;
  EPS_DEFAULT              = EPS_TIGHT;

type

(* Routines with UNIQUE implementations for each XLI engine  *)

  xli_name = function: PChar; stdcall;
  xli_readmodel = function(lp: THandle; modelname, dataname, options: PChar; verbose: integer): boolean; stdcall;
  xli_writemodel = function(lp: THandle; filename, options: PChar; results: boolean): boolean; stdcall;

(* Routines SHARED for all XLI implementations; *)

  xli_compatible = function(lp: Thandle; xliversion, lpversion: Integer): boolean; stdcall;


(* User and system function interfaces                                       *)

procedure lp_solve_version(majorversion: Pinteger; minorversion: Pinteger;
  release: Pinteger; build: Pinteger); stdcall;

function make_lp(rows: integer; columns: integer): THandle; stdcall;
function resize_lp(lp: THandle; rows: integer; columns: integer): boolean; stdcall;
function get_status(lp: THandle): integer; stdcall;
function get_statustext(lp: THandle; statuscode: integer): PChar; stdcall;
// Create and initialise a lprec structure defaults

procedure delete_lp(lp: THandle); stdcall;
procedure free_lp(var plp: THandle); stdcall;
// Remove problem from memory

function set_lp_name(lp: THandle; lpname: PChar): boolean; stdcall;
function get_lp_name(lp: THandle): PChar; stdcall;
// Set and get the problem name

function has_BFP(lp: THandle): boolean; stdcall;
function is_nativeBFP(lp: THandle): boolean; stdcall;
function set_BFP(lp: THandle; filename: PChar): boolean; stdcall;
// Set basis factorization engine


function read_XLI(xliname, modelname, dataname, options: PChar; verbose: integer): THandle; stdcall;
function write_XLI(lp: THandle; filename, options: PChar; results: boolean): boolean; stdcall;
function has_XLI(lp: THandle): boolean; stdcall;
function is_nativeXLI(lp: THandle): boolean; stdcall;
function set_XLI(lp: THandle; filename: PChar): boolean; stdcall;
// Set external language interface

function set_obj(lp: THandle; Column: integer; Value: double): boolean; stdcall;
function set_obj_fn(lp: THandle; row: PFloatArray): boolean; stdcall;
function set_obj_fnex(lp: THandle; count: integer; row: PFloatArray;
  colno: PIntArray): boolean; stdcall;
// set the objective function (Row 0) of the matrix
function str_set_obj_fn(lp: THandle; row_string: PChar): boolean; stdcall;
// The same, but with string input
procedure set_sense(lp: THandle; maximize: boolean); stdcall;
procedure set_maxim(lp: THandle); stdcall;
procedure set_minim(lp: THandle); stdcall;
function is_maxim(lp: THandle): boolean; stdcall;
// Set optimization direction for the objective function

function add_constraint(lp: THandle; row: PFloatArray; constr_type: integer; rh: double): boolean; stdcall;
function add_constraintex(lp: THandle; count: integer; row: PFloatArray; colno: PIntArray;
  constr_type: integer; rh: double): boolean; stdcall;
function set_add_rowmode(lp: THandle; turnon: boolean): boolean; stdcall;
function is_add_rowmode(lp: THandle): boolean; stdcall;
{ Add a constraint to the problem, row is the constraint row, rh is the right hand side,
   constr_type is the type of constraint (LE (<=), GE(>=), EQ(=)) }
function str_add_constraint(lp: THandle; row_string : PChar; constr_type: integer; rh: double): boolean; stdcall;
// The same, but with string input

function set_row(lp: THandle; row_no: Integer; row: PFloatArray): boolean; stdcall;
function set_rowex(lp: THandle; row_no, count: Integer; row: PFloatArray; colno: PIntArray): boolean; stdcall;

function get_row(lp: THandle; row_nr: integer; row: PFloatArray): boolean; stdcall;
// Fill row with the row row_nr from the problem

function del_constraint(lp: THandle; del_row: integer): boolean; stdcall;
// Remove constrain nr del_row from the problem

function add_lag_con(lp: THandle; row: PFloatArray; con_type: integer; rhs: double): boolean; stdcall;
// add a Lagrangian constraint of form Row' x contype Rhs
function str_add_lag_con(lp: THandle; row_string: PChar; con_type: integer; rhs: double): boolean; stdcall;
// The same, but with string input
procedure set_lag_trace(lp: THandle; lag_trace: boolean); stdcall;
function is_lag_trace(lp: THandle): boolean; stdcall;
// Set debugging/tracing mode of the Lagrangean solver

function set_constr_type(lp: THandle; row: integer; con_type: integer): boolean; stdcall;
function get_constr_type(lp: THandle; row: integer): integer; stdcall;
function is_constr_type(lp: THandle; row: integer; mask: integer): boolean; stdcall;
// Set the type of constraint in row Row (LE, GE, EQ)

function set_rh(lp: THandle; row: integer; value: double): boolean; stdcall;
function get_rh(lp: THandle; row: integer): double; stdcall;
// Set and get the right hand side of a constraint row
function set_rh_range(lp: THandle; row: integer; deltavalue: double): boolean; stdcall;
function get_rh_range(lp: THandle; row: integer): double; stdcall;
// Set the RHS range; i.e. the lower and upper bounds of a constraint row
procedure set_rh_vec(lp: THandle; rh: PFloatArray); stdcall;
// Set the right hand side vector
function str_set_rh_vec(lp: THandle; rh_string: PChar): boolean; stdcall;
// The same, but with string input

function add_column(lp: THandle; column: PFloatArray): boolean; stdcall;
function add_columnex(lp: THandle; count: integer; column: PFloatArray; rowno: PIntArray): boolean; stdcall;
// Add a column to the problem
function str_add_column(lp: THandle; col_string: PChar): boolean; stdcall;
// The same, but with string input
function set_column(lp: THandle; col_no: Integer; column: PFloatArray): boolean; stdcall;
function set_columnex(lp: THandle; col_no, count: Integer; column: PFloatArray; rowno: PIntArray): boolean; stdcall;

function column_in_lp(lp: THandle; column: PFloatArray): integer; stdcall;
{ Returns the column index if column is already present in lp, otherwise 0.
   (Does not look at bounds and types, only looks at matrix values }
function get_column(lp: THandle; col_nr: integer; column: PFloatArray): boolean; stdcall;
// Fill column with the column col_nr from the problem

function del_column(lp: THandle; column: integer): boolean; stdcall;
// Delete a column

function set_mat(lp: THandle; row: integer; column: integer; value: double): boolean; stdcall;
{ Fill in element (Row,Column) of the matrix
   Row in [0..Rows] and Column in [1..Columns] }
function get_mat(lp: THandle; row: integer; column: integer): double; stdcall;
function get_mat_byindex(lp: THandle; matindex: Integer; isrow, adjustsign: boolean): double; stdcall;
function get_nonzeros(lp: THandle): integer; stdcall;

procedure set_bounds_tighter(lp: THandle; tighten: boolean); stdcall;
function get_bounds_tighter(lp: THandle): boolean; stdcall;
function set_upbo(lp: THandle; column: integer; value: double): boolean; stdcall;
function get_upbo(lp: THandle; column: integer): double; stdcall;
function set_lowbo(lp: THandle; column: integer; value: double): boolean; stdcall;
function get_lowbo(lp: THandle; column: integer): double; stdcall;
function set_bounds(lp: THandle; column: integer; lower: double; upper: double): boolean; stdcall;
function get_bounds(lp: THandle; column: Integer; lower, upper: PFloatArray): boolean; stdcall;

function set_int(lp: THandle; column: integer; must_be_int: boolean): boolean; stdcall;
function is_int(lp: THandle; column: integer): boolean; stdcall;
function set_binary(lp: THandle; column: integer; must_be_bin: boolean): boolean; stdcall;
function is_binary(lp: THandle; column: integer): boolean; stdcall;
function set_semicont(lp: THandle; column: integer; must_be_sc: boolean): boolean; stdcall;
function is_semicont(lp: THandle; column: integer): boolean; stdcall;
function is_negative(lp: THandle; column: integer): boolean; stdcall;
function set_var_weights(lp: THandle; weights: PFloatArray): boolean; stdcall;
function get_var_priority(lp: THandle; column: integer): integer; stdcall;
// Set the type of variable, if must_be_int = TRUE then the variable must be integer

function add_SOS(lp: THandle; name: PChar; sostype: integer; priority: integer;
  count: integer; sosvars: PIntArray; weights: PFloatArray): integer; stdcall;
function is_SOS_var(lp: THandle; column: integer): boolean; stdcall;
// Add SOS constraints

function set_row_name(lp: THandle; row: integer; new_name: PChar): boolean; stdcall;
function get_row_name(lp: THandle; row: integer): PChar; stdcall;
function get_origrow_name(lp: THandle; row: integer): PChar; stdcall;
// Set/Get the name of a constraint row - Get added by KE

function set_col_name(lp: THandle; column: integer; new_name: PChar): boolean; stdcall;
function get_col_name(lp: THandle; column: integer): PChar; stdcall;
function get_origcol_name(lp: THandle; column: integer): PChar; stdcall;
// Set/Get the name of a variable column - Get added by KE

procedure unscale(lp: THandle); stdcall;
// Undo previous scaling of the problem

procedure set_preferdual(lp: THandle; dodual: boolean); stdcall;
procedure set_simplextype(lp: THandle; simplextype: integer); stdcall;
function get_simplextype(lp: THandle): integer; stdcall;
// Set/Get if lp_solve should prefer the dual simplex over the primal -- added by KE

procedure default_basis(lp: THandle); stdcall;
procedure set_basiscrash(lp: THandle; mode: integer); stdcall;
function get_basiscrash(lp: THandle): integer; stdcall;
function set_basis(lp: THandle; bascolumn: PIntArray; nonbasic: boolean): boolean; stdcall;

function is_feasible(lp: THandle; values: PFloatArray; threshold: double): boolean; stdcall;
// returns TRUE if the vector in values is a feasible solution to the lp

function solve(lp: THandle): integer; stdcall;
// Solve the problem

function time_elapsed(lp: THandle): double; stdcall;
// Return the number of seconds since start of solution process

function get_primal_solution(lp: THandle; pv: PFloatArray): boolean; stdcall;
function get_ptr_primal_solution(lp: THandle; var pv: PFloatArray): boolean; stdcall;
function get_dual_solution(lp: THandle; rc: PFloatArray): boolean; stdcall;
function get_ptr_dual_solution(lp: THandle; var rc: PFloatArray): boolean; stdcall;
function get_lambda(lp: THandle; lambda: PFloatArray): boolean; stdcall;
function get_ptr_lambda(lp: THandle; var lambda: PFloatArray): boolean; stdcall;
// Get the primal, dual/reduced costs and Lambda vectors

procedure reset_basis(lp: THandle); stdcall;
// Reset the basis of a problem, can be useful in case of degeneracy - JD

// Read an MPS file
function read_MPS(filename: PChar; verbose: integer): THandle; stdcall; overload;
function read_mps(stream: PInteger; verbose: integer): THandle; stdcall; overload;
// Write a MPS file to output
function write_mps(lp: THandle; filename: PChar): boolean; stdcall; overload;
function write_MPS(lp: THandle; output: PInteger): boolean; stdcall; overload;


function read_freeMPS(filename: PChar; verbose: Integer): THandle; stdcall; overload;
function read_freemps(filename: Pinteger; verbose: Integer): THandle; stdcall; overload;
function write_freemps(lp: THandle; filename: PChar): boolean; stdcall; overload;
function write_freeMPS(lp: THandle; output: PInteger): boolean; stdcall; overload;

function guess_basis(lp: THandle; guessvector: PFloatArray; basisvector: PIntArray): boolean; stdcall;
function read_basis(lp: THandle; filename, info: PChar): boolean; stdcall;
function write_basis(lp: THandle; filename: PChar): boolean; stdcall;

function write_lp(lp: THandle; filename: PChar): boolean; stdcall; overload;
function write_LP(lp: THandle; filename: PInteger): boolean; stdcall; overload;
// Write a LP file to output

function read_lp(filename: Pinteger; verbose: integer; lp_name: PChar): THandle; stdcall; overload;
function read_LP(filename: PChar; verbose: integer; lp_name: PChar): THandle; stdcall; overload;
// Old-style lp format file parser

procedure print_lp(lp: THandle); stdcall;
procedure print_tableau(lp: THandle); stdcall;
// Print the current problem, only useful in very small (test) problems

procedure print_objective(lp: THandle); stdcall;
procedure print_solution(lp: THandle; columns: integer); stdcall;
procedure print_constraints(lp: THandle; columns: integer); stdcall;
// Print the solution to stdout

procedure print_duals(lp: THandle); stdcall;
// Print the dual variables of the solution

procedure print_scales(lp: THandle); stdcall;
// If scaling is used, print the scaling factors

procedure print_str(lp: THandle; str: PChar); stdcall;

procedure set_outputstream(lp: THandle; stream: Pointer); stdcall;
function set_outputfile(lp: THandle; filename: PChar): boolean; stdcall;

procedure set_verbose(lp: THandle; verbose: integer); stdcall;
function get_verbose(lp: THandle): integer; stdcall;

procedure set_timeout(lp: THandle; sectimeout: integer); stdcall;
function get_timeout(lp: THandle): integer; stdcall;

procedure set_print_sol(lp: THandle; print_sol: integer); stdcall;
function get_print_sol(lp: THandle): integer; stdcall;

procedure set_debug(lp: THandle; debug: boolean); stdcall;
function is_debug(lp: THandle): boolean; stdcall;

procedure set_trace(lp: THandle; trace: boolean); stdcall;
function is_trace(lp: THandle): boolean; stdcall;

function print_debugdump(lp: THandle; filename: PChar): boolean; stdcall;

procedure set_anti_degen(lp: THandle; anti_degen: integer); stdcall;
function get_anti_degen(lp: THandle): integer; stdcall;
function is_anti_degen(lp: THandle; testmask: integer): boolean; stdcall;

function get_presolve(lp: THandle): integer; stdcall;
function is_presolve(lp: THandle; testmask: integer): boolean; stdcall;

function get_orig_index(lp: THandle; lp_index: integer): integer; stdcall;
function get_lp_index(lp: THandle; orig_index: integer): integer; stdcall;

procedure set_maxpivot(lp: THandle; max_num_inv: integer); stdcall;
function get_maxpivot(lp: THandle): integer; stdcall;

procedure set_obj_bound(lp: THandle; obj_bound: double); stdcall;
function get_obj_bound(lp: THandle): double; stdcall;

procedure set_mip_gap(lp: THandle; absolute: boolean; mip_gap: double); stdcall;
function get_mip_gap(lp: THandle; absolute: boolean): double; stdcall;

procedure set_bb_rule(lp: THandle; bb_rule: integer); stdcall;
function get_bb_rule(lp: THandle): integer; stdcall;

function set_var_branch(lp: THandle; column: integer; branch_mode: integer): boolean; stdcall;
function get_var_branch(lp: THandle; column: integer): integer; stdcall;

function is_infinite(lp: THandle; value: double): boolean; stdcall;
procedure set_infinite(lp: THandle; infinite: double); stdcall;
function get_infinite(lp: THandle): double; stdcall;

procedure set_epsint(lp: THandle; epsilon: double); stdcall;
function get_epsint(lp: THandle): double; stdcall;

procedure set_epsb(lp: THandle; epsb: double); stdcall;
function get_epsb(lp: THandle): double; stdcall;

procedure set_epsd(lp: THandle; epsd: double); stdcall;
function get_epsd(lp: THandle): double; stdcall;

procedure set_epsel(lp: THandle; epsel: double); stdcall;
function get_epsel(lp: THandle): double; stdcall;

procedure set_scaling(lp: THandle; scalemode: integer); stdcall;
function get_scaling(lp: THandle): integer; stdcall;
function is_scalemode(lp: THandle; testmask: integer): boolean; stdcall;
function is_scaletype(lp: THandle; scaletype: integer): boolean; stdcall;
function is_integerscaling(lp: THandle): boolean; stdcall;
procedure set_scalelimit(lp: THandle; scalelimit: double); stdcall;
function get_scalelimit(lp: THandle): double; stdcall;

procedure set_improve(lp: THandle; improve: integer); stdcall;
function get_improve(lp: THandle): integer; stdcall;

procedure set_pivoting(lp: THandle; piv_rule: integer); stdcall;
function get_pivoting(lp: THandle): integer; stdcall;

function set_partialprice(lp: THandle; blockcount: Integer; blockstart: PIntArray; isrow: boolean): boolean; stdcall;
procedure get_partialprice(lp: THandle; blockcount: PIntArray; blockstart: PIntArray; isrow: boolean); stdcall;

function set_multiprice(lp: THandle; multiblockdiv: Integer): boolean; stdcall;
function get_multiprice(lp: THandle; getabssize: boolean): Integer; stdcall;

function is_piv_mode(lp: THandle; testmask: integer): boolean; stdcall;
function is_piv_rule(lp: THandle; rule: integer): boolean; stdcall;

procedure set_break_at_first(lp: THandle; break_at_first: boolean); stdcall;
function is_break_at_first(lp: THandle): boolean; stdcall;

procedure set_bb_floorfirst(lp: THandle; bb_floorfirst: integer); stdcall;
function get_bb_floorfirst(lp: THandle): integer; stdcall;

procedure set_bb_depthlimit(lp: THandle; bb_maxlevel: integer); stdcall;
function get_bb_depthlimit(lp: THandle): integer; stdcall;

procedure set_break_at_value(lp: THandle; break_at_value: double); stdcall;
function get_break_at_value(lp: THandle): double; stdcall;

procedure set_negrange(lp: THandle; negrange: double); stdcall;
function get_negrange(lp: THandle): double; stdcall;

procedure set_epsperturb(lp: THandle; epsperturb: double); stdcall;
function get_epsperturb(lp: THandle): double; stdcall;

procedure set_epspivot(lp: THandle; epspivot: double); stdcall;
function get_epspivot(lp: THandle): double; stdcall;

function get_max_level(lp: THandle): integer; stdcall;
function get_total_nodes(lp: THandle): COUNTER; stdcall;
function get_total_iter(lp: THandle): COUNTER; stdcall;

function get_objective(lp: THandle): double; stdcall;
function get_working_objective(lp: THandle): double; stdcall;

function get_var_primalresult(lp: THandle; index: integer): double; stdcall;
function get_var_dualresult(lp: THandle; index: integer): double; stdcall;

function get_variables(lp: THandle; var_: PFloatArray): boolean; stdcall;
function get_ptr_variables(lp: THandle; var var_: PFloatArray): boolean; stdcall;

function get_constraints(lp: THandle; constr: PFloatArray): boolean; stdcall;
function get_ptr_constraints(lp: THandle; var constr: PFloatArray): boolean; stdcall;

function get_sensitivity_rhs(lp: THandle; duals, dualsfrom, dualstill: PFloatArray): boolean; stdcall;
function get_ptr_sensitivity_rhs(lp: THandle; var duals, dualsfrom, dualstill: PFloatArray): boolean; stdcall;

function get_sensitivity_obj(lp: THandle; objfrom, objtill: PFloatArray): boolean; stdcall;
function get_sensitivity_objex(lp: THandle; objfrom, objtill, objfromvalue, objtillvalue: PFloatArray): boolean; stdcall;
function get_ptr_sensitivity_obj(lp: THandle; var objfrom, objtill: PFloatArray): boolean; stdcall;
function get_ptr_sensitivity_objex(lp: THandle; var objfrom, objtill, objfromvalue, objtillvalue: PFloatArray): boolean; stdcall;


procedure set_solutionlimit(lp: THandle; limit: integer); stdcall;
function get_solutionlimit(lp: THandle): integer; stdcall;
function get_solutioncount(lp: THandle): integer; stdcall;

function get_Norig_rows(lp: THandle): integer; stdcall;
function get_Nrows(lp: THandle): integer; stdcall;
function get_Lrows(lp: THandle): integer; stdcall;

function get_Norig_columns(lp: THandle): integer; stdcall;
function get_Ncolumns(lp: THandle): integer; stdcall;

function get_nameindex(lp: THandle; varname: PChar; isrow: boolean): Integer; stdcall;


{$IFDEF LPS55_UP}
//function resize_lp(lp: THandle; rows, columns: Integer): boolean; stdcall;
function copy_lp(lp: THandle): THandle; stdcall;
function dualize_lp(lp: THandle): boolean; stdcall;
(* Copy or dualize the lp *)
function get_constr_value(lp: THandle; rownr, count: Integer;
  primsolution: PFloatArray; nzindex: PIntArray): double; stdcall;
function get_columnex(lp: THandle; colnr: Integer; column: PFloatArray;
  nzrow: PIntArray): Integer; stdcall;
function set_unbounded(lp: THandle; colnr: Integer): boolean; stdcall;
function is_unbounded(lp: THandle; colnr: Integer): boolean; stdcall;
function get_basis(lp: THandle; bascolumn: PIntArray; nonbasic: boolean): boolean; stdcall;
function set_basisvar(lp: THandle; basisPos, enteringCol: Integer): Integer; stdcall;
procedure put_bb_nodefunc(lp: THandle; newnode: lphandleint_intfunc; bbnodehandle: Pointer); stdcall;
procedure put_bb_branchfunc(lp: THandle; newbranch: lphandleint_intfunc; bbbranchhandle: Pointer); stdcall;
// Allow the user to override B&B node and branching decisions
procedure put_abortfunc(lp: THandle; newctrlc: lphandle_intfunc; ctrlchandle: Pointer); stdcall;
// Allow the user to define an interruption callback function
procedure put_logfunc(lp: THandle; newlog: lphandlestr_func; loghandle: Pointer); stdcall;
// Allow the user to define a logging function
procedure put_msgfunc(lp: THandle; newmsg: lphandleint_func; msghandle: Pointer; mask: integer); stdcall;
// Allow the user to define an event-driven message/reporting
function write_params(lp: THandle; filename, options: PChar): boolean; stdcall;
function read_params(lp: THandle; filename, options: PChar): boolean; stdcall;
procedure reset_params(lp: THandle); stdcall;
// Read and write parameter file
procedure set_presolve(lp: THandle; presolvemode, maxloops: Integer); stdcall;
function get_presolveloops(lp: THandle): Integer; stdcall;
function set_epslevel(lp: THandle; epslevel: Integer): boolean; stdcall;
function get_rowex(lp: THandle; rownr: Integer; row: PFloatArray; colno: PIntArray): integer; stdcall;
function is_use_names(lp: THandle; isrow: boolean): boolean; stdcall;
procedure set_use_names(lp: THandle; isrow, use_names: boolean); stdcall;
function is_obj_in_basis(lp: THandle): boolean; stdcall;
procedure set_obj_in_basis(lp: THandle; obj_in_basis: boolean); stdcall;
{$ELSE}
function set_free(lp: THandle; column: integer): boolean; stdcall;
function is_free(lp: THandle; column: integer): boolean; stdcall;
// Set the upper and lower bounds of a variable
procedure get_basis(lp: THandle; bascolumn: PIntArray; nonbasic: boolean); stdcall;
// Set/Get basis for a re-solved system - Added by KE
procedure put_abortfunc(lp: THandle; newctrlc: ctrlcfunc; ctrlchandle: Pointer); stdcall;
// Allow the user to define an interruption callback function
procedure put_logfunc(lp: THandle; newlog: logfunc; loghandle: Pointer); stdcall;
// Allow the user to define a logging function
procedure put_msgfunc(lp: THandle; newmsg: msgfunc; msghandle: Pointer; mask: integer); stdcall;
// Allow the user to define an event-driven message/reporting
procedure set_presolve(lp: THandle; do_presolve: integer); stdcall;
{$ENDIF}

implementation

const
{$IFDEF UNIX}
  {$IFDEF LPS51}
    LPSOLVELIB = 'liblpsolve51.so';
  {$ENDIF}
  {$IFDEF LPS55}
    LPSOLVELIB = 'liblpsolve55.so';
  {$ENDIF}
{$ELSE}
  {$IFDEF LPS51}
    LPSOLVELIB = 'lpsolve51.dll';
  {$ENDIF}
  {$IFDEF LPS55}
    LPSOLVELIB = 'lpsolve55.dll';
  {$ENDIF}
{$ENDIF}

procedure lp_solve_version(majorversion: Pinteger; minorversion: Pinteger; release: Pinteger; build: Pinteger); stdcall; external LPSOLVELIB name 'lp_solve_version';
function make_lp(rows: integer; columns: integer): THandle; stdcall; external LPSOLVELIB name 'make_lp';
function resize_lp(lp: THandle; rows: integer; columns: integer): boolean; stdcall; external LPSOLVELIB name 'resize_lp';
function get_statustext(lp: THandle; statuscode: integer): PChar; stdcall; external LPSOLVELIB name 'get_statustext';
procedure delete_lp(lp: THandle); stdcall; external LPSOLVELIB name 'delete_lp';
procedure free_lp(var plp: THandle); stdcall; external LPSOLVELIB name 'free_lp';
function set_lp_name(lp: THandle; lpname: PChar): boolean; stdcall; external LPSOLVELIB name 'set_lp_name';
function get_lp_name(lp: THandle): PChar; stdcall; external LPSOLVELIB name 'get_lp_name';
function has_BFP(lp: THandle): boolean; stdcall; external LPSOLVELIB name 'has_BFP';
function is_nativeBFP(lp: THandle): boolean; stdcall; external LPSOLVELIB name 'is_nativeBFP';
function set_BFP(lp: THandle; filename: PChar): boolean; stdcall; external LPSOLVELIB name 'set_BFP';
function read_XLI(xliname, modelname, dataname, options: PChar; verbose: integer): THandle; stdcall; external LPSOLVELIB name 'read_XLI';
function write_XLI(lp: THandle; filename, options: PChar; results: boolean): boolean; stdcall; external LPSOLVELIB name 'write_XLI';
function has_XLI(lp: THandle): boolean; stdcall; external LPSOLVELIB name 'has_XLI';
function is_nativeXLI(lp: THandle): boolean; stdcall; external LPSOLVELIB name 'is_nativeXLI';
function set_XLI(lp: THandle; filename: PChar): boolean; stdcall; external LPSOLVELIB name 'set_XLI';
function set_obj(lp: THandle; Column: integer; Value: double): boolean; stdcall; external LPSOLVELIB name 'set_obj';
function set_obj_fn(lp: THandle; row: PFloatArray): boolean; stdcall; external LPSOLVELIB name 'set_obj_fn';
function set_obj_fnex(lp: THandle; count: integer; row: PFloatArray; colno: PIntArray): boolean; stdcall; external LPSOLVELIB name 'set_obj_fnex';
function str_set_obj_fn(lp: THandle; row_string: PChar): boolean; stdcall; external LPSOLVELIB name 'str_set_obj_fn';
procedure set_sense(lp: THandle; maximize: boolean); stdcall; external LPSOLVELIB name 'set_sense';
procedure set_maxim(lp: THandle); stdcall; external LPSOLVELIB name 'set_maxim';
procedure set_minim(lp: THandle); stdcall; external LPSOLVELIB name 'set_minim';
function is_maxim(lp: THandle): boolean; stdcall; external LPSOLVELIB name 'is_maxim';
function add_constraint(lp: THandle; row: PFloatArray; constr_type: integer; rh: double): boolean; stdcall; external LPSOLVELIB name 'add_constraint';
function add_constraintex(lp: THandle; count: integer; row: PFloatArray; colno: PIntArray; constr_type: integer; rh: double): boolean; stdcall; external LPSOLVELIB name 'add_constraintex';
function set_add_rowmode(lp: THandle; turnon: boolean): boolean; stdcall; external LPSOLVELIB name 'set_add_rowmode';
function is_add_rowmode(lp: THandle): boolean; stdcall; external LPSOLVELIB name 'is_add_rowmode';
function str_add_constraint(lp: THandle; row_string : PChar;constr_type: integer; rh: double): boolean; stdcall; external LPSOLVELIB name 'str_add_constraint';
function get_row(lp: THandle; row_nr: integer; row: PFloatArray): boolean; stdcall; external LPSOLVELIB name 'get_row';
function del_constraint(lp: THandle; del_row: integer): boolean; stdcall; external LPSOLVELIB name 'del_constraint';
function add_lag_con(lp: THandle; row: PFloatArray; con_type: integer; rhs: double): boolean; stdcall; external LPSOLVELIB name 'add_lag_con';
function str_add_lag_con(lp: THandle; row_string: PChar; con_type: integer; rhs: double): boolean; stdcall; external LPSOLVELIB name 'str_add_lag_con';
procedure set_lag_trace(lp: THandle; lag_trace: boolean); stdcall; external LPSOLVELIB name 'set_lag_trace';
function is_lag_trace(lp: THandle): boolean; stdcall; external LPSOLVELIB name 'is_lag_trace';
function set_constr_type(lp: THandle; row: integer; con_type: integer): boolean; stdcall; external LPSOLVELIB name 'set_constr_type';
function get_constr_type(lp: THandle; row: integer): integer; stdcall; external LPSOLVELIB name 'get_constr_type';
function is_constr_type(lp: THandle; row: integer; mask: integer): boolean; stdcall; external LPSOLVELIB name 'is_constr_type';
function set_rh(lp: THandle; row: integer; value: double): boolean; stdcall; external LPSOLVELIB name 'set_rh';
function get_rh(lp: THandle; row: integer): double; stdcall; external LPSOLVELIB name 'get_rh';
function set_rh_range(lp: THandle; row: integer; deltavalue: double): boolean; stdcall; external LPSOLVELIB name 'set_rh_range';
function get_rh_range(lp: THandle; row: integer): double; stdcall; external LPSOLVELIB name 'get_rh_range';
procedure set_rh_vec(lp: THandle; rh: PFloatArray); stdcall; external LPSOLVELIB name 'set_rh_vec';
function str_set_rh_vec(lp: THandle; rh_string: PChar): boolean; stdcall; external LPSOLVELIB name 'str_set_rh_vec';
function add_column(lp: THandle; column: PFloatArray): boolean; stdcall; external LPSOLVELIB name 'add_column';
function add_columnex(lp: THandle; count: integer; column: PFloatArray; rowno: PIntArray): boolean; stdcall; external LPSOLVELIB name 'add_columnex';
function str_add_column(lp: THandle; col_string: PChar): boolean; stdcall; external LPSOLVELIB name 'str_add_column';
function column_in_lp(lp: THandle; column: PFloatArray): integer; stdcall; external LPSOLVELIB name 'column_in_lp';
function get_column(lp: THandle; col_nr: integer; column: PFloatArray): boolean; stdcall; external LPSOLVELIB name 'get_column';
function del_column(lp: THandle; column: integer): boolean; stdcall; external LPSOLVELIB name 'del_column';
function set_mat(lp: THandle; row: integer; column: integer; value: double): boolean; stdcall; external LPSOLVELIB name 'set_mat';
function get_mat(lp: THandle; row: integer; column: integer): double; stdcall; external LPSOLVELIB name 'get_mat';
function get_mat_byindex(lp: THandle; matindex: Integer; isrow, adjustsign: boolean): double; stdcall; external LPSOLVELIB name 'get_mat_byindex';
procedure set_bounds_tighter(lp: THandle; tighten: boolean); stdcall; external LPSOLVELIB name 'set_bounds_tighter';
function get_bounds_tighter(lp: THandle): boolean; stdcall; external LPSOLVELIB name 'get_bounds_tighter';
function set_upbo(lp: THandle; column: integer; value: double): boolean; stdcall; external LPSOLVELIB name 'set_upbo';
function get_upbo(lp: THandle; column: integer): double; stdcall; external LPSOLVELIB name 'get_upbo';
function set_lowbo(lp: THandle; column: integer; value: double): boolean; stdcall; external LPSOLVELIB name 'set_lowbo';
function get_lowbo(lp: THandle; column: integer): double; stdcall; external LPSOLVELIB name 'get_lowbo';
function set_bounds(lp: THandle; column: integer; lower: double; upper: double): boolean; stdcall; external LPSOLVELIB name 'set_bounds';
function get_bounds(lp: THandle; column: Integer; lower, upper: PFloatArray): boolean; stdcall; external LPSOLVELIB name 'get_bounds';
function set_int(lp: THandle; column: integer; must_be_int: boolean): boolean; stdcall; external LPSOLVELIB name 'set_int';
function is_int(lp: THandle; column: integer): boolean; stdcall; external LPSOLVELIB name 'is_int';
function set_binary(lp: THandle; column: integer; must_be_bin: boolean): boolean; stdcall; external LPSOLVELIB name 'set_binary';
function is_binary(lp: THandle; column: integer): boolean; stdcall; external LPSOLVELIB name 'is_binary';
function set_semicont(lp: THandle; column: integer; must_be_sc: boolean): boolean; stdcall; external LPSOLVELIB name 'set_semicont';
function is_semicont(lp: THandle; column: integer): boolean; stdcall; external LPSOLVELIB name 'is_semicont';
function is_negative(lp: THandle; column: integer): boolean; stdcall; external LPSOLVELIB name 'is_negative';
function set_var_weights(lp: THandle; weights: PFloatArray): boolean; stdcall; external LPSOLVELIB name 'set_var_weights';
function get_var_priority(lp: THandle; column: integer): integer; stdcall; external LPSOLVELIB name 'get_var_priority';
function add_SOS(lp: THandle; name: PChar; sostype: integer; priority: integer; count: integer; sosvars: PIntArray; weights: PFloatArray): integer; stdcall; external LPSOLVELIB name 'add_SOS';
function is_SOS_var(lp: THandle; column: integer): boolean; stdcall; external LPSOLVELIB name 'is_SOS_var';
function set_row_name(lp: THandle; row: integer; new_name: PChar): boolean; stdcall; external LPSOLVELIB name 'set_row_name';
function get_row_name(lp: THandle; row: integer): PChar; stdcall; external LPSOLVELIB name 'get_row_name';
function get_origrow_name(lp: THandle; row: integer): PChar; stdcall; external LPSOLVELIB name 'get_origrow_name';
function set_col_name(lp: THandle; column: integer; new_name: PChar): boolean; stdcall; external LPSOLVELIB name 'set_col_name';
function get_col_name(lp: THandle; column: integer): PChar; stdcall; external LPSOLVELIB name 'get_col_name';
function get_origcol_name(lp: THandle; column: integer): PChar; stdcall; external LPSOLVELIB name 'get_origcol_name';
procedure unscale(lp: THandle); stdcall; external LPSOLVELIB name 'unscale';
procedure set_preferdual(lp: THandle; dodual: boolean); stdcall; external LPSOLVELIB name 'set_preferdual';
procedure set_simplextype(lp: THandle; simplextype: integer); stdcall; external LPSOLVELIB name 'set_simplextype';
function get_simplextype(lp: THandle): integer; stdcall; external LPSOLVELIB name 'get_simplextype';
procedure default_basis(lp: THandle); stdcall; external LPSOLVELIB name 'default_basis';
procedure set_basiscrash(lp: THandle; mode: integer); stdcall; external LPSOLVELIB name 'set_basiscrash';
function get_basiscrash(lp: THandle): integer; stdcall; external LPSOLVELIB name 'get_basiscrash';
function set_basis(lp: THandle; bascolumn: PIntArray; nonbasic: boolean): boolean; stdcall; external LPSOLVELIB name 'set_basis';
function is_feasible(lp: THandle; values: PFloatArray; threshold: double): boolean; stdcall; external LPSOLVELIB name 'is_feasible';
function solve(lp: THandle): integer; stdcall; external LPSOLVELIB name 'solve';
function time_elapsed(lp: THandle): double; stdcall; external LPSOLVELIB name 'time_elapsed';
function get_primal_solution(lp: THandle; pv: PFloatArray): boolean; stdcall; external LPSOLVELIB name 'get_primal_solution';
function get_ptr_primal_solution(lp: THandle; var pv: PFloatArray): boolean; stdcall; external LPSOLVELIB name 'get_ptr_primal_solution';
function get_dual_solution(lp: THandle; rc: PFloatArray): boolean; stdcall; external LPSOLVELIB name 'get_dual_solution';
function get_ptr_dual_solution(lp: THandle; var rc: PFloatArray): boolean; stdcall; external LPSOLVELIB name 'get_ptr_dual_solution';
function get_lambda(lp: THandle; lambda: PFloatArray): boolean; stdcall; external LPSOLVELIB name 'get_lambda';
function get_ptr_lambda(lp: THandle; var lambda: PFloatArray): boolean; stdcall; external LPSOLVELIB name 'get_ptr_lambda';
procedure reset_basis(lp: THandle); stdcall; external LPSOLVELIB name 'reset_basis';
function read_MPS(filename: PChar; verbose: integer): THandle; stdcall; external LPSOLVELIB name 'read_MPS';
function read_mps(stream: PInteger; verbose: integer): THandle; stdcall; external LPSOLVELIB name 'read_mps';
function read_freeMPS(filename: PChar; verbose: Integer): THandle; stdcall; external LPSOLVELIB name 'read_freeMPS';
function read_freemps(filename: Pinteger; verbose: Integer): THandle; stdcall; external LPSOLVELIB name 'read_freemps';
function write_freemps(lp: THandle; filename: PChar): boolean; stdcall; external LPSOLVELIB name 'write_freemps';
function write_freeMPS(lp: THandle; output: PInteger): boolean; stdcall; external LPSOLVELIB name 'write_freeMPS';
function guess_basis(lp: THandle; guessvector: PFloatArray; basisvector: PIntArray): boolean; stdcall; external LPSOLVELIB name 'guess_basis';
function read_basis(lp: THandle; filename, info: PChar): boolean; stdcall; external LPSOLVELIB name 'read_basis';
function write_basis(lp: THandle; filename: PChar): boolean; stdcall; external LPSOLVELIB name 'write_basis';
function write_mps(lp: THandle; filename: PChar): boolean; stdcall; external LPSOLVELIB name 'write_mps';
function write_MPS(lp: THandle; output: PInteger): boolean; stdcall; external LPSOLVELIB name 'write_MPS';
function write_lp(lp: THandle; filename: PChar): boolean; stdcall; external LPSOLVELIB name 'write_lp';
function write_LP(lp: THandle; filename: PInteger): boolean; stdcall; external LPSOLVELIB name 'write_LP';
function read_lp(filename: PInteger; verbose: integer; lp_name: PChar): THandle; stdcall; external LPSOLVELIB name 'read_lp';
function read_LP(filename: PChar; verbose: integer; lp_name: PChar): THandle; stdcall; external LPSOLVELIB name 'read_LP';
procedure print_lp(lp: THandle); stdcall; external LPSOLVELIB name 'print_lp';
procedure print_tableau(lp: THandle); stdcall; external LPSOLVELIB name 'print_tableau';
procedure print_objective(lp: THandle); stdcall; external LPSOLVELIB name 'print_objective';
procedure print_solution(lp: THandle; columns: integer); stdcall; external LPSOLVELIB name 'print_solution';
procedure print_constraints(lp: THandle; columns: integer); stdcall; external LPSOLVELIB name 'print_constraints';
procedure print_duals(lp: THandle); stdcall; external LPSOLVELIB name 'print_duals';
procedure print_scales(lp: THandle); stdcall; external LPSOLVELIB name 'print_scales';
procedure print_str(lp: THandle; str: PChar); stdcall; external LPSOLVELIB name 'print_str';
procedure set_outputstream(lp: THandle; stream: Pointer); stdcall; external LPSOLVELIB name 'set_outputstream';
function set_outputfile(lp: THandle; filename: PChar): boolean; stdcall; external LPSOLVELIB name 'set_outputfile';
procedure set_verbose(lp: THandle; verbose: integer); stdcall; external LPSOLVELIB name 'set_verbose';
function get_verbose(lp: THandle): integer; stdcall; external LPSOLVELIB name 'get_verbose';
procedure set_timeout(lp: THandle; sectimeout: integer); stdcall; external LPSOLVELIB name 'set_timeout';
function get_timeout(lp: THandle): integer; stdcall; external LPSOLVELIB name 'get_timeout';
procedure set_print_sol(lp: THandle; print_sol: integer); stdcall; external LPSOLVELIB name 'set_print_sol';
function get_print_sol(lp: THandle): integer; stdcall; external LPSOLVELIB name 'get_print_sol';
procedure set_debug(lp: THandle; debug: boolean); stdcall; external LPSOLVELIB name 'set_debug';
function is_debug(lp: THandle): boolean; stdcall; external LPSOLVELIB name 'is_debug';
procedure set_trace(lp: THandle; trace: boolean); stdcall; external LPSOLVELIB name 'set_trace';
function is_trace(lp: THandle): boolean; stdcall; external LPSOLVELIB name 'is_trace';
function print_debugdump(lp: THandle; filename: PChar): boolean; stdcall; external LPSOLVELIB name 'print_debugdump';
procedure set_anti_degen(lp: THandle; anti_degen: integer); stdcall; external LPSOLVELIB name 'set_anti_degen';
function get_anti_degen(lp: THandle): integer; stdcall; external LPSOLVELIB name 'get_anti_degen';
function is_anti_degen(lp: THandle; testmask: integer): boolean; stdcall; external LPSOLVELIB name 'is_anti_degen';
function get_presolve(lp: THandle): integer; stdcall; external LPSOLVELIB name 'get_presolve';
function is_presolve(lp: THandle; testmask: integer): boolean; stdcall; external LPSOLVELIB name 'is_presolve';
function get_orig_index(lp: THandle; lp_index: integer): integer; stdcall; external LPSOLVELIB name 'get_orig_index';
function get_lp_index(lp: THandle; orig_index: integer): integer; stdcall; external LPSOLVELIB name 'get_lp_index';
procedure set_maxpivot(lp: THandle; max_num_inv: integer); stdcall; external LPSOLVELIB name 'set_maxpivot';
function get_maxpivot(lp: THandle): integer; stdcall; external LPSOLVELIB name 'get_maxpivot';
procedure set_obj_bound(lp: THandle; obj_bound: double); stdcall; external LPSOLVELIB name 'set_obj_bound';
function get_obj_bound(lp: THandle): double; stdcall; external LPSOLVELIB name 'get_obj_bound';
procedure set_mip_gap(lp: THandle; absolute: boolean; mip_gap: double); stdcall; external LPSOLVELIB name 'set_mip_gap';
function get_mip_gap(lp: THandle; absolute: boolean): double; stdcall; external LPSOLVELIB name 'get_mip_gap';
procedure set_bb_rule(lp: THandle; bb_rule: integer); stdcall; external LPSOLVELIB name 'set_bb_rule';
function get_bb_rule(lp: THandle): integer; stdcall; external LPSOLVELIB name 'get_bb_rule';
function set_var_branch(lp: THandle; column: integer; branch_mode: integer): boolean; stdcall; external LPSOLVELIB name 'set_var_branch';
function get_var_branch(lp: THandle; column: integer): integer; stdcall; external LPSOLVELIB name 'get_var_branch';
procedure set_infinite(lp: THandle; infinite: double); stdcall; external LPSOLVELIB name 'set_infinite';
function get_infinite(lp: THandle): double; stdcall; external LPSOLVELIB name 'get_infinite';
procedure set_epsint(lp: THandle; epsilon: double); stdcall; external LPSOLVELIB name 'set_epsint';
function get_epsint(lp: THandle): double; stdcall; external LPSOLVELIB name 'get_epsint';
procedure set_epsb(lp: THandle; epsb: double); stdcall; external LPSOLVELIB name 'set_epsb';
function get_epsb(lp: THandle): double; stdcall; external LPSOLVELIB name 'get_epsb';
procedure set_epsd(lp: THandle; epsd: double); stdcall; external LPSOLVELIB name 'set_epsd';
function get_epsd(lp: THandle): double; stdcall; external LPSOLVELIB name 'get_epsd';
procedure set_epsel(lp: THandle; epsel: double); stdcall; external LPSOLVELIB name 'set_epsel';
function get_epsel(lp: THandle): double; stdcall; external LPSOLVELIB name 'get_epsel';
procedure set_scaling(lp: THandle; scalemode: integer); stdcall; external LPSOLVELIB name 'set_scaling';
function get_scaling(lp: THandle): integer; stdcall; external LPSOLVELIB name 'get_scaling';
function is_scalemode(lp: THandle; testmask: integer): boolean; stdcall; external LPSOLVELIB name 'is_scalemode';
function is_scaletype(lp: THandle; scaletype: integer): boolean; stdcall; external LPSOLVELIB name 'is_scaletype';
function is_integerscaling(lp: THandle): boolean; stdcall; external LPSOLVELIB name 'is_integerscaling';
procedure set_scalelimit(lp: THandle; scalelimit: double); stdcall; external LPSOLVELIB name 'set_scalelimit';
function get_scalelimit(lp: THandle): double; stdcall; external LPSOLVELIB name 'get_scalelimit';
procedure set_improve(lp: THandle; improve: integer); stdcall; external LPSOLVELIB name 'set_improve';
function get_improve(lp: THandle): integer; stdcall; external LPSOLVELIB name 'get_improve';
procedure set_pivoting(lp: THandle; piv_rule: integer); stdcall; external LPSOLVELIB name 'set_pivoting';
function get_pivoting(lp: THandle): integer; stdcall; external LPSOLVELIB name 'get_pivoting';
function is_piv_mode(lp: THandle; testmask: integer): boolean; stdcall; external LPSOLVELIB name 'is_piv_mode';
function is_piv_rule(lp: THandle; rule: integer): boolean; stdcall; external LPSOLVELIB name 'is_piv_rule';
procedure set_break_at_first(lp: THandle; break_at_first: boolean); stdcall; external LPSOLVELIB name 'set_break_at_first';
function is_break_at_first(lp: THandle): boolean; stdcall; external LPSOLVELIB name 'is_break_at_first';
procedure set_bb_floorfirst(lp: THandle; bb_floorfirst: integer); stdcall; external LPSOLVELIB name 'set_bb_floorfirst';
function get_bb_floorfirst(lp: THandle): integer; stdcall; external LPSOLVELIB name 'get_bb_floorfirst';
procedure set_bb_depthlimit(lp: THandle; bb_maxlevel: integer); stdcall; external LPSOLVELIB name 'set_bb_depthlimit';
function get_bb_depthlimit(lp: THandle): integer; stdcall; external LPSOLVELIB name 'get_bb_depthlimit';
procedure set_break_at_value(lp: THandle; break_at_value: double); stdcall; external LPSOLVELIB name 'set_break_at_value';
function get_break_at_value(lp: THandle): double; stdcall; external LPSOLVELIB name 'get_break_at_value';
procedure set_negrange(lp: THandle; negrange: double); stdcall; external LPSOLVELIB name 'set_negrange';
function get_negrange(lp: THandle): double; stdcall; external LPSOLVELIB name 'get_negrange';
procedure set_epsperturb(lp: THandle; epsperturb: double); stdcall; external LPSOLVELIB name 'set_epsperturb';
function get_epsperturb(lp: THandle): double; stdcall; external LPSOLVELIB name 'get_epsperturb';
procedure set_epspivot(lp: THandle; epspivot: double); stdcall; external LPSOLVELIB name 'set_epspivot';
function get_epspivot(lp: THandle): double; stdcall; external LPSOLVELIB name 'get_epspivot';
function get_max_level(lp: THandle): integer; stdcall; external LPSOLVELIB name 'get_max_level';
function get_total_nodes(lp: THandle): COUNTER; stdcall; external LPSOLVELIB name 'get_total_nodes';
function get_total_iter(lp: THandle): COUNTER; stdcall; external LPSOLVELIB name 'get_total_iter';
function get_objective(lp: THandle): double; stdcall; external LPSOLVELIB name 'get_objective';
function get_working_objective(lp: THandle): double; stdcall; external LPSOLVELIB name 'get_working_objective';
function get_var_primalresult(lp: THandle; index: integer): double; stdcall; external LPSOLVELIB name 'get_var_primalresult';
function get_var_dualresult(lp: THandle; index: integer): double; stdcall; external LPSOLVELIB name 'get_var_dualresult';
function get_variables(lp: THandle; var_: PFloatArray): boolean; stdcall; external LPSOLVELIB name 'get_variables';
function get_ptr_variables(lp: THandle; var var_: PFloatArray): boolean; stdcall; external LPSOLVELIB name 'get_ptr_variables';
function get_constraints(lp: THandle; constr: PFloatArray): boolean; stdcall; external LPSOLVELIB name 'get_constraints';
function get_ptr_constraints(lp: THandle; var constr: PFloatArray): boolean; stdcall; external LPSOLVELIB name 'get_ptr_constraints';
function get_sensitivity_rhs(lp: THandle; duals, dualsfrom, dualstill: PFloatArray): boolean; stdcall; external LPSOLVELIB name 'get_sensitivity_rhs';
function get_ptr_sensitivity_rhs(lp: THandle; var duals, dualsfrom, dualstill: PFloatArray): boolean; stdcall; external LPSOLVELIB name 'get_ptr_sensitivity_rhs';
function get_sensitivity_obj(lp: THandle; objfrom, objtill: PFloatArray): boolean; stdcall; external LPSOLVELIB name 'get_sensitivity_obj';
function get_ptr_sensitivity_obj(lp: THandle; var objfrom, objtill: PFloatArray): boolean; stdcall; external LPSOLVELIB name 'get_ptr_sensitivity_obj';
procedure set_solutionlimit(lp: THandle; limit: integer); stdcall; external LPSOLVELIB name 'set_solutionlimit';
function get_solutionlimit(lp: THandle): integer; stdcall; external LPSOLVELIB name 'get_solutionlimit';
function get_solutioncount(lp: THandle): integer; stdcall; external LPSOLVELIB name 'get_solutioncount';
function get_Norig_rows(lp: THandle): integer; stdcall; external LPSOLVELIB name 'get_Norig_rows';
function get_Nrows(lp: THandle): integer; stdcall; external LPSOLVELIB name 'get_Nrows';
function get_Lrows(lp: THandle): integer; stdcall; external LPSOLVELIB name 'get_Lrows';
function get_Norig_columns(lp: THandle): integer; stdcall; external LPSOLVELIB name 'get_Norig_columns';
function get_Ncolumns(lp: THandle): integer; stdcall; external LPSOLVELIB name 'get_Ncolumns';

function get_nonzeros(lp: THandle): integer; stdcall; external LPSOLVELIB name 'get_nonzeros';
function get_status(lp: THandle): integer; stdcall; external LPSOLVELIB name 'get_status';
function is_infinite(lp: THandle; value: double): boolean; stdcall; external LPSOLVELIB name 'is_infinite';
function set_column(lp: THandle; col_no: Integer; column: PFloatArray): boolean; stdcall; external LPSOLVELIB name 'set_column';
function set_columnex(lp: THandle; col_no, count: Integer; column: PFloatArray; rowno: PIntArray): boolean; stdcall; external LPSOLVELIB name 'set_columnex';
function set_row(lp: THandle; row_no: Integer; row: PFloatArray): boolean; stdcall; external LPSOLVELIB name 'set_row';
function set_rowex(lp: THandle; row_no, count: Integer; row: PFloatArray; colno: PIntArray): boolean; stdcall; external LPSOLVELIB name 'set_rowex';
function get_ptr_sensitivity_objex(lp: THandle; var objfrom, objtill, objfromvalue, objtillvalue: PFloatArray): boolean; stdcall; external LPSOLVELIB name 'get_ptr_sensitivity_objex';
function get_sensitivity_objex(lp: THandle; objfrom, objtill, objfromvalue, objtillvalue: PFloatArray): boolean; stdcall; external LPSOLVELIB name 'get_sensitivity_objex';
function get_nameindex(lp: THandle; varname: PChar; isrow: boolean): Integer; stdcall; external LPSOLVELIB name 'get_nameindex';
function set_partialprice(lp: THandle; blockcount: Integer; blockstart: PIntArray; isrow: boolean): boolean; stdcall; external LPSOLVELIB name 'set_partialprice';
procedure get_partialprice(lp: THandle; blockcount: PIntArray; blockstart: PIntArray; isrow: boolean); stdcall; external LPSOLVELIB name 'get_partialprice';
function set_multiprice(lp: THandle; multiblockdiv: Integer): boolean; stdcall; external LPSOLVELIB name 'set_multiprice';
function get_multiprice(lp: THandle; getabssize: boolean): Integer; stdcall; external LPSOLVELIB name 'get_multiprice';

{$IFDEF LPS55_UP}
//function resize_lp(lp: THandle; rows, columns: Integer): boolean; stdcall; external LPSOLVELIB name 'resize_lp';
function copy_lp(lp: THandle): THandle; stdcall; external LPSOLVELIB name 'copy_lp';
function dualize_lp(lp: THandle): boolean; stdcall; external LPSOLVELIB name 'dualize_lp';
function get_columnex(lp: THandle; colnr: Integer; column: PFloatArray; nzrow: PIntArray): Integer; stdcall; external LPSOLVELIB name 'get_columnex';
function get_constr_value(lp: THandle; rownr, count: Integer; primsolution: PFloatArray; nzindex: PIntArray): double; stdcall; external LPSOLVELIB name 'get_constr_value';
function set_unbounded(lp: THandle; colnr: Integer): boolean; stdcall; external LPSOLVELIB name 'set_unbounded';
function is_unbounded(lp: THandle; colnr: Integer): boolean; stdcall; external LPSOLVELIB name 'is_unbounded';
function get_basis(lp: THandle; bascolumn: PIntArray; nonbasic: boolean): boolean; stdcall; external LPSOLVELIB name 'get_basis';
function set_basisvar(lp: THandle; basisPos, enteringCol: Integer): Integer; stdcall; external LPSOLVELIB name 'set_basisvar';
procedure put_bb_nodefunc(lp: THandle; newnode: lphandleint_intfunc; bbnodehandle: Pointer); stdcall; external LPSOLVELIB name 'put_bb_nodefunc';
procedure put_bb_branchfunc(lp: THandle; newbranch: lphandleint_intfunc; bbbranchhandle: Pointer); stdcall; external LPSOLVELIB name 'put_bb_branchfunc';
function write_params(lp: THandle; filename, options: PChar): boolean; stdcall; external LPSOLVELIB name 'write_params';
function read_params(lp: THandle; filename, options: PChar): boolean; stdcall; external LPSOLVELIB name 'read_params';
procedure reset_params(lp: THandle); stdcall; external LPSOLVELIB name 'reset_params';
function set_epslevel(lp: THandle; epslevel: Integer): boolean; stdcall; external LPSOLVELIB name 'set_epslevel';
function set_pseudocosts(lp: THandle; clower: PFloatArray; cupper: PFloatArray; updatelimit: PIntArray): boolean; stdcall; external LPSOLVELIB name 'set_pseudocosts';
function get_pseudocosts(lp: THandle; clower: PFloatArray; cupper: PFloatArray; updatelimit: PIntArray): boolean; stdcall; external LPSOLVELIB name 'get_pseudocosts';
procedure set_presolve(lp: THandle; presolvemode, maxloops: Integer); stdcall; external LPSOLVELIB name 'set_presolve';
function get_presolveloops(lp: THandle): Integer; stdcall; external LPSOLVELIB name 'get_presolveloops';
procedure put_abortfunc(lp: THandle; newctrlc: lphandle_intfunc; ctrlchandle: Pointer); stdcall; external LPSOLVELIB name 'put_abortfunc';
procedure put_logfunc(lp: THandle; newlog: lphandlestr_func; loghandle: Pointer); stdcall; external LPSOLVELIB name 'put_logfunc';
procedure put_msgfunc(lp: THandle; newmsg: lphandleint_func; msghandle: Pointer; mask: integer); stdcall; external LPSOLVELIB name 'put_msgfunc';
function get_rowex(lp: THandle; rownr: Integer; row: PFloatArray; colno: PIntArray): integer; stdcall; external LPSOLVELIB name 'get_rowex';
function is_use_names(lp: THandle; isrow: boolean): boolean; stdcall; external LPSOLVELIB name 'is_use_names';
procedure set_use_names(lp: THandle; isrow, use_names: boolean); stdcall; external LPSOLVELIB name 'set_use_names';
function is_obj_in_basis(lp: THandle): boolean; stdcall; external LPSOLVELIB name 'is_obj_in_basis';
procedure set_obj_in_basis(lp: THandle; obj_in_basis: boolean); stdcall; external LPSOLVELIB name 'set_obj_in_basis';
{$ELSE}
function set_free(lp: THandle; column: integer): boolean; stdcall; external LPSOLVELIB name 'set_free';
function is_free(lp: THandle; column: integer): boolean; stdcall; external LPSOLVELIB name 'is_free';
procedure set_presolve(lp: THandle; do_presolve: integer); stdcall; external LPSOLVELIB name 'set_presolve';
procedure put_abortfunc(lp: THandle; newctrlc: ctrlcfunc; ctrlchandle: Pointer); stdcall; external LPSOLVELIB name 'put_abortfunc';
procedure put_logfunc(lp: THandle; newlog: logfunc; loghandle: Pointer); stdcall; external LPSOLVELIB name 'put_logfunc';
procedure put_msgfunc(lp: THandle; newmsg: msgfunc; msghandle: Pointer; mask: integer); stdcall; external LPSOLVELIB name 'put_msgfunc';
procedure get_basis(lp: THandle; bascolumn: PIntArray; nonbasic: boolean); stdcall; external LPSOLVELIB name 'get_basis';
{$ENDIF}

end.

