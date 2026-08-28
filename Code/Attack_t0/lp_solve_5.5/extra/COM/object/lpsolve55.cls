VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "lpsolve55"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

'lpsolve version 5 routines

Private Declare Function SetEnvironmentVariableA Lib "kernel32" (ByVal lpname As String, ByVal lpValue As String) As Long
Private Declare Function GetEnvironmentVariableA Lib "kernel32" (ByVal lpname As String, ByVal lpBuffer As String, ByVal nSize As Long) As Long
Private Declare Function lstrlen Lib "kernel32" Alias "lstrlenA" (ByVal lpString As Long) As Long
Private Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (ByVal lpvDest As String, ByVal lpvSource As Long, ByVal NumBytes As Long)

'-----------------------------------------------------------------------------------------------------------------------------

Private Declare Function lpsolve_add_column Lib "lpsolve55.dll" Alias "add_column" (ByVal lp As Long, ByRef column As Double) As Boolean
Private Declare Function lpsolve_add_columnex Lib "lpsolve55.dll" Alias "add_columnex" (ByVal lp As Long, ByVal count As Long, ByRef column As Double, ByRef rowno As Long) As Boolean
Private Declare Function lpsolve_add_constraint Lib "lpsolve55.dll" Alias "add_constraint" (ByVal lp As Long, ByRef row As Double, ByVal constr_type As lpsolve_constr_types, ByVal rh As Double) As Boolean
Private Declare Function lpsolve_add_constraintex Lib "lpsolve55.dll" Alias "add_constraintex" (ByVal lp As Long, ByVal count As Long, ByRef row As Double, ByRef colno As Long, ByVal constr_type As lpsolve_constr_types, ByVal rh As Double) As Boolean
Private Declare Function lpsolve_add_lag_con Lib "lpsolve55.dll" Alias "add_lag_con" (ByVal lp As Long, ByRef row As Double, ByVal con_type As lpsolve_constr_types, ByVal rhs As Double) As Boolean
Private Declare Function lpsolve_add_SOS Lib "lpsolve55.dll" Alias "add_SOS" (ByVal lp As Long, ByVal name As String, ByVal sostype As Long, ByVal priority As Long, ByVal count As Long, ByRef sosvars As Long, ByRef weights As Double) As Long
Private Declare Function lpsolve_column_in_lp Lib "lpsolve55.dll" Alias "column_in_lp" (ByVal lp As Long, ByRef column As Double) As Boolean
Private Declare Function lpsolve_copy_lp Lib "lpsolve55.dll" Alias "copy_lp" (ByVal lp As Long) As Long
Private Declare Sub lpsolve_default_basis Lib "lpsolve55.dll" Alias "default_basis" (ByVal lp As Long)
Private Declare Function lpsolve_del_column Lib "lpsolve55.dll" Alias "del_column" (ByVal lp As Long, ByVal column As Long) As Boolean
Private Declare Function lpsolve_del_constraint Lib "lpsolve55.dll" Alias "del_constraint" (ByVal lp As Long, ByVal del_row As Long) As Boolean
Private Declare Sub lpsolve_delete_lp Lib "lpsolve55.dll" Alias "delete_lp" (ByVal lp As Long)
Private Declare Function lpsolve_dualize_lp Lib "lpsolve55.dll" Alias "dualize_lp" (ByVal lp As Long) As Boolean
Private Declare Function lpsolve_get_accuracy Lib "lpsolve55.dll" Alias "get_accuracy" (ByVal lp As Long) As Double
Private Declare Function lpsolve_get_anti_degen Lib "lpsolve55.dll" Alias "get_anti_degen" (ByVal lp As Long) As lpsolve_anti_degen
Private Declare Function lpsolve_get_basis Lib "lpsolve55.dll" Alias "get_basis" (ByVal lp As Long, ByRef bascolumn As Long, ByVal nonbasic As Boolean) As Boolean
Private Declare Function lpsolve_get_basiscrash Lib "lpsolve55.dll" Alias "get_basiscrash" (ByVal lp As Long) As lpsolve_basiscrash
Private Declare Function lpsolve_get_bb_depthlimit Lib "lpsolve55.dll" Alias "get_bb_depthlimit" (ByVal lp As Long) As Long
Private Declare Function lpsolve_get_bb_floorfirst Lib "lpsolve55.dll" Alias "get_bb_floorfirst" (ByVal lp As Long) As lpsolve_branch
Private Declare Function lpsolve_get_bb_rule Lib "lpsolve55.dll" Alias "get_bb_rule" (ByVal lp As Long) As lpsolve_BBstrategies
Private Declare Function lpsolve_get_bounds_tighter Lib "lpsolve55.dll" Alias "get_bounds_tighter" (ByVal lp As Long) As Boolean
Private Declare Function lpsolve_get_break_at_value Lib "lpsolve55.dll" Alias "get_break_at_value" (ByVal lp As Long) As Double
Private Declare Function lpsolve_get_break_numeric_accuracy Lib "lpsolve55.dll" Alias "get_break_numeric_accuracy" (ByVal lp As Long) As Double
Private Declare Function lpsolve_get_col_name Lib "lpsolve55.dll" Alias "get_col_name" (ByVal lp As Long, ByVal column As Long) As Long
Private Declare Function lpsolve_get_column Lib "lpsolve55.dll" Alias "get_column" (ByVal lp As Long, ByVal col_nr As Long, ByRef column As Double) As Boolean
Private Declare Function lpsolve_get_columnex Lib "lpsolve55.dll" Alias "get_columnex" (ByVal lp As Long, ByVal col_nr As Long, ByRef column As Double, ByRef nzrow As Long) As Long
Private Declare Function lpsolve_get_constr_type Lib "lpsolve55.dll" Alias "get_constr_type" (ByVal lp As Long, ByVal row As Long) As lpsolve_constr_types
Private Declare Function lpsolve_get_constraints Lib "lpsolve55.dll" Alias "get_constraints" (ByVal lp As Long, ByRef constr As Double) As Boolean
Private Declare Function lpsolve_get_constr_value Lib "lpsolve55.dll" Alias "get_constr_value" (ByVal lp As Long, ByVal row As Long, ByVal count As Long, ByRef primsolution As Double, ByRef nzindex As Long) As Double
Private Declare Function lpsolve_get_dual_solution Lib "lpsolve55.dll" Alias "get_dual_solution" (ByVal lp As Long, ByRef rc As Double) As Boolean
Private Declare Function lpsolve_get_epsb Lib "lpsolve55.dll" Alias "get_epsb" (ByVal lp As Long) As Double
Private Declare Function lpsolve_get_epsd Lib "lpsolve55.dll" Alias "get_epsd" (ByVal lp As Long) As Double
Private Declare Function lpsolve_get_epsel Lib "lpsolve55.dll" Alias "get_epsel" (ByVal lp As Long) As Double
Private Declare Function lpsolve_get_epsint Lib "lpsolve55.dll" Alias "get_epsint" (ByVal lp As Long) As Double
Private Declare Function lpsolve_get_epsperturb Lib "lpsolve55.dll" Alias "get_epsperturb" (ByVal lp As Long) As Double
Private Declare Function lpsolve_get_epspivot Lib "lpsolve55.dll" Alias "get_epspivot" (ByVal lp As Long) As Double
Private Declare Function lpsolve_get_improve Lib "lpsolve55.dll" Alias "get_improve" (ByVal lp As Long) As lpsolve_improves
Private Declare Function lpsolve_get_infinite Lib "lpsolve55.dll" Alias "get_infinite" (ByVal lp As Long) As Double
Private Declare Function lpsolve_get_lambda Lib "lpsolve55.dll" Alias "get_lambda" (ByVal lp As Long, ByRef lambda As Double) As Boolean
Private Declare Function lpsolve_get_lowbo Lib "lpsolve55.dll" Alias "get_lowbo" (ByVal lp As Long, ByVal column As Long) As Double
Private Declare Function lpsolve_get_lp_index Lib "lpsolve55.dll" Alias "get_lp_index" (ByVal lp As Long, ByVal orig_index As Long) As Long
Private Declare Function lpsolve_get_lp_name Lib "lpsolve55.dll" Alias "get_lp_name" (ByVal lp As Long) As Long
Private Declare Function lpsolve_get_Lrows Lib "lpsolve55.dll" Alias "get_Lrows" (ByVal lp As Long) As Long
Private Declare Function lpsolve_get_mat Lib "lpsolve55.dll" Alias "get_mat" (ByVal lp As Long, ByVal row As Long, ByVal column As Long) As Double
Private Declare Function lpsolve_get_max_level Lib "lpsolve55.dll" Alias "get_max_level" (ByVal lp As Long) As Long
Private Declare Function lpsolve_get_maxpivot Lib "lpsolve55.dll" Alias "get_maxpivot" (ByVal lp As Long) As Long
Private Declare Function lpsolve_get_mip_gap Lib "lpsolve55.dll" Alias "get_mip_gap" (ByVal lp As Long, ByVal absolute As Boolean) As Double
Private Declare Function lpsolve_get_nameindex Lib "lpsolve55.dll" Alias "get_nameindex" (ByVal lp As Long, ByVal name As String, ByVal isrow As Boolean) As Long
Private Declare Function lpsolve_get_Ncolumns Lib "lpsolve55.dll" Alias "get_Ncolumns" (ByVal lp As Long) As Long
Private Declare Function lpsolve_get_negrange Lib "lpsolve55.dll" Alias "get_negrange" (ByVal lp As Long) As Double
Private Declare Function lpsolve_get_nonzeros Lib "lpsolve55.dll" Alias "get_nonzeros" (ByVal lp As Long) As Long
Private Declare Function lpsolve_get_Norig_columns Lib "lpsolve55.dll" Alias "get_Norig_columns" (ByVal lp As Long) As Long
Private Declare Function lpsolve_get_Norig_rows Lib "lpsolve55.dll" Alias "get_Norig_rows" (ByVal lp As Long) As Long
Private Declare Function lpsolve_get_Nrows Lib "lpsolve55.dll" Alias "get_Nrows" (ByVal lp As Long) As Long
Private Declare Function lpsolve_get_obj_bound Lib "lpsolve55.dll" Alias "get_obj_bound" (ByVal lp As Long) As Double
Private Declare Function lpsolve_get_objective Lib "lpsolve55.dll" Alias "get_objective" (ByVal lp As Long) As Double
Private Declare Function lpsolve_get_orig_index Lib "lpsolve55.dll" Alias "get_orig_index" (ByVal lp As Long, ByVal lp_index As Long) As Long
Private Declare Function lpsolve_get_origcol_name Lib "lpsolve55.dll" Alias "get_origcol_name" (ByVal lp As Long, ByVal column As Long) As Long
Private Declare Function lpsolve_get_origrow_name Lib "lpsolve55.dll" Alias "get_origrow_name" (ByVal lp As Long, ByVal row As Long) As Long
Private Declare Function lpsolve_get_pivoting Lib "lpsolve55.dll" Alias "get_pivoting" (ByVal lp As Long) As lpsolve_piv_rules
Private Declare Function lpsolve_get_presolve Lib "lpsolve55.dll" Alias "get_presolve" (ByVal lp As Long) As lpsolve_presolve
Private Declare Function lpsolve_get_presolveloops Lib "lpsolve55.dll" Alias "get_presolveloops" (ByVal lp As Long) As Long
Private Declare Function lpsolve_get_primal_solution Lib "lpsolve55.dll" Alias "get_primal_solution" (ByVal lp As Long, ByRef pv As Double) As Boolean
Private Declare Function lpsolve_get_print_sol Lib "lpsolve55.dll" Alias "get_print_sol" (ByVal lp As Long) As Long
Private Declare Function lpsolve_get_PseudoCosts Lib "lpsolve55.dll" Alias "get_PseudoCosts" (ByVal lp As Long, ByRef clower As Double, ByRef cupper As Double, ByRef updatelimit As Long) As Boolean
Private Declare Function lpsolve_get_rh Lib "lpsolve55.dll" Alias "get_rh" (ByVal lp As Long, ByVal row As Long) As Double
Private Declare Function lpsolve_get_rh_range Lib "lpsolve55.dll" Alias "get_rh_range" (ByVal lp As Long, ByVal row As Long) As Double
Private Declare Function lpsolve_get_row Lib "lpsolve55.dll" Alias "get_row" (ByVal lp As Long, ByVal row_nr As Long, ByRef row As Double) As Boolean
Private Declare Function lpsolve_get_rowex Lib "lpsolve55.dll" Alias "get_rowex" (ByVal lp As Long, ByVal row_nr As Long, ByRef row As Double, ByRef colno As Long) As Long
Private Declare Function lpsolve_get_row_name Lib "lpsolve55.dll" Alias "get_row_name" (ByVal lp As Long, ByVal row As Long) As Long
Private Declare Function lpsolve_get_scalelimit Lib "lpsolve55.dll" Alias "get_scalelimit" (ByVal lp As Long) As Double
Private Declare Function lpsolve_get_scaling Lib "lpsolve55.dll" Alias "get_scaling" (ByVal lp As Long) As lpsolve_scales
Private Declare Function lpsolve_get_sensitivity_obj Lib "lpsolve55.dll" Alias "get_sensitivity_obj" (ByVal lp As Long, ByRef objfrom As Double, ByRef objtill As Double) As Boolean
Private Declare Function lpsolve_get_sensitivity_objex Lib "lpsolve55.dll" Alias "get_sensitivity_objex" (ByVal lp As Long, ByRef objfrom As Double, ByRef objtill As Double, ByRef objfromvalue As Double, ByRef objtillvalue As Double) As Boolean
Private Declare Function lpsolve_get_sensitivity_rhs Lib "lpsolve55.dll" Alias "get_sensitivity_rhs" (ByVal lp As Long, ByRef duals As Double, ByRef dualsfrom As Double, ByRef dualstill As Double) As Boolean
Private Declare Function lpsolve_get_simplextype Lib "lpsolve55.dll" Alias "get_simplextype" (ByVal lp As Long) As lpsolve_simplextypes
Private Declare Function lpsolve_get_solutioncount Lib "lpsolve55.dll" Alias "get_solutioncount" (ByVal lp As Long) As Long
Private Declare Function lpsolve_get_solutionlimit Lib "lpsolve55.dll" Alias "get_solutionlimit" (ByVal lp As Long) As Long
Private Declare Function lpsolve_get_status Lib "lpsolve55.dll" Alias "get_status" (ByVal lp As Long) As Long
Private Declare Function lpsolve_get_statustext Lib "lpsolve55.dll" Alias "get_statustext" (ByVal lp As Long, ByVal statuscode As Long) As Long
Private Declare Function lpsolve_get_timeout Lib "lpsolve55.dll" Alias "get_timeout" (ByVal lp As Long) As Long
Private Declare Function lpsolve_get_total_iter Lib "lpsolve55.dll" Alias "get_total_iter" (ByVal lp As Long) As Long
Private Declare Function lpsolve_get_total_nodes Lib "lpsolve55.dll" Alias "get_total_nodes" (ByVal lp As Long) As Long
Private Declare Function lpsolve_get_upbo Lib "lpsolve55.dll" Alias "get_upbo" (ByVal lp As Long, ByVal column As Long) As Double
Private Declare Function lpsolve_get_var_branch Lib "lpsolve55.dll" Alias "get_var_branch" (ByVal lp As Long, ByVal column As Long) As lpsolve_branch
Private Declare Function lpsolve_get_var_dualresult Lib "lpsolve55.dll" Alias "get_var_dualresult" (ByVal lp As Long, ByVal index As Long) As Double
Private Declare Function lpsolve_get_var_primalresult Lib "lpsolve55.dll" Alias "get_var_primalresult" (ByVal lp As Long, ByVal index As Long) As Double
Private Declare Function lpsolve_get_var_priority Lib "lpsolve55.dll" Alias "get_var_priority" (ByVal lp As Long, ByVal column As Long) As Long
Private Declare Function lpsolve_get_variables Lib "lpsolve55.dll" Alias "get_variables" (ByVal lp As Long, ByRef var As Double) As Boolean
Private Declare Function lpsolve_get_verbose Lib "lpsolve55.dll" Alias "get_verbose" (ByVal lp As Long) As Long
Private Declare Function lpsolve_get_working_objective Lib "lpsolve55.dll" Alias "get_working_objective" (ByVal lp As Long) As Double
Private Declare Function lpsolve_guess_basis Lib "lpsolve55.dll" Alias "guess_basis" (ByVal lp As Long, ByRef guessvector As Double, ByRef basisvector As Long) As Boolean
Private Declare Function lpsolve_has_BFP Lib "lpsolve55.dll" Alias "has_BFP" (ByVal lp As Long) As Boolean
Private Declare Function lpsolve_has_XLI Lib "lpsolve55.dll" Alias "has_XLI" (ByVal lp As Long) As Boolean
Private Declare Function lpsolve_is_add_rowmode Lib "lpsolve55.dll" Alias "is_add_rowmode" (ByVal lp As Long) As Boolean
Private Declare Function lpsolve_is_anti_degen Lib "lpsolve55.dll" Alias "is_anti_degen" (ByVal lp As Long, ByVal testmask As lpsolve_anti_degen) As Boolean
Private Declare Function lpsolve_is_binary Lib "lpsolve55.dll" Alias "is_binary" (ByVal lp As Long, ByVal column As Long) As Boolean
Private Declare Function lpsolve_is_break_at_first Lib "lpsolve55.dll" Alias "is_break_at_first" (ByVal lp As Long) As Boolean
Private Declare Function lpsolve_is_constr_type Lib "lpsolve55.dll" Alias "is_constr_type" (ByVal lp As Long, ByVal row As Long, ByVal mask As Long) As Boolean
Private Declare Function lpsolve_is_debug Lib "lpsolve55.dll" Alias "is_debug" (ByVal lp As Long) As Boolean
Private Declare Function lpsolve_is_feasible Lib "lpsolve55.dll" Alias "is_feasible" (ByVal lp As Long, ByRef values As Double, ByVal threshold As Double) As Boolean
Private Declare Function lpsolve_is_infinite Lib "lpsolve55.dll" Alias "is_infinite" (ByVal lp As Long, ByVal value As Double) As Boolean
Private Declare Function lpsolve_is_int Lib "lpsolve55.dll" Alias "is_int" (ByVal lp As Long, ByVal column As Long) As Boolean
Private Declare Function lpsolve_is_integerscaling Lib "lpsolve55.dll" Alias "is_integerscaling" (ByVal lp As Long) As Boolean
Private Declare Function lpsolve_is_lag_trace Lib "lpsolve55.dll" Alias "is_lag_trace" (ByVal lp As Long) As Boolean
Private Declare Function lpsolve_is_maxim Lib "lpsolve55.dll" Alias "is_maxim" (ByVal lp As Long) As Boolean
Private Declare Function lpsolve_is_nativeBFP Lib "lpsolve55.dll" Alias "is_nativeBFP" (ByVal lp As Long) As Boolean
Private Declare Function lpsolve_is_nativeXLI Lib "lpsolve55.dll" Alias "is_nativeXLI" (ByVal lp As Long) As Boolean
Private Declare Function lpsolve_is_negative Lib "lpsolve55.dll" Alias "is_negative" (ByVal lp As Long, ByVal column As Long) As Boolean
Private Declare Function lpsolve_is_piv_mode Lib "lpsolve55.dll" Alias "is_piv_mode" (ByVal lp As Long, ByVal testmask As lpsolve_piv_rules) As Boolean
Private Declare Function lpsolve_is_piv_rule Lib "lpsolve55.dll" Alias "is_piv_rule" (ByVal lp As Long, ByVal rule As lpsolve_piv_rules) As Boolean
Private Declare Function lpsolve_is_presolve Lib "lpsolve55.dll" Alias "is_presolve" (ByVal lp As Long, ByVal testmask As lpsolve_presolve) As Boolean
Private Declare Function lpsolve_is_scalemode Lib "lpsolve55.dll" Alias "is_scalemode" (ByVal lp As Long, ByVal testmask As lpsolve_scales) As Boolean
Private Declare Function lpsolve_is_scaletype Lib "lpsolve55.dll" Alias "is_scaletype" (ByVal lp As Long, ByVal scaletype As lpsolve_scales) As Boolean
Private Declare Function lpsolve_is_semicont Lib "lpsolve55.dll" Alias "is_semicont" (ByVal lp As Long, ByVal column As Long) As Boolean
Private Declare Function lpsolve_is_SOS_var Lib "lpsolve55.dll" Alias "is_SOS_var" (ByVal lp As Long, ByVal column As Long) As Boolean
Private Declare Function lpsolve_is_trace Lib "lpsolve55.dll" Alias "is_trace" (ByVal lp As Long) As Boolean
Private Declare Function lpsolve_is_unbounded Lib "lpsolve55.dll" Alias "is_unbounded" (ByVal lp As Long, ByVal column As Long) As Boolean
Private Declare Function lpsolve_is_use_names Lib "lpsolve55.dll" Alias "is_use_names" (ByVal lp As Long, ByVal isrow As Boolean) As Boolean
Private Declare Sub lpsolve_version Lib "lpsolve55.dll" Alias "lp_solve_version" (ByRef majorversion As Long, ByRef minorversion As Long, ByRef release As Long, ByRef build As Long)
Private Declare Function lpsolve_make_lp Lib "lpsolve55.dll" Alias "make_lp" (ByVal rows As Long, ByVal columns As Long) As Long
Private Declare Function lpsolve_resize_lp Lib "lpsolve55.dll" Alias "resize_lp" (ByVal lp As Long, ByVal rows As Long, ByVal columns As Long) As Boolean
Private Declare Sub lpsolve_print_constraints Lib "lpsolve55.dll" Alias "print_constraints" (ByVal lp As Long, ByVal columns As Long)
Private Declare Function lpsolve_print_debugdump Lib "lpsolve55.dll" Alias "print_debugdump" (ByVal lp As Long, ByVal filename As String) As Boolean
Private Declare Sub lpsolve_print_duals Lib "lpsolve55.dll" Alias "print_duals" (ByVal lp As Long)
Private Declare Sub lpsolve_print_lp Lib "lpsolve55.dll" Alias "print_lp" (ByVal lp As Long)
Private Declare Sub lpsolve_print_objective Lib "lpsolve55.dll" Alias "print_objective" (ByVal lp As Long)
Private Declare Sub lpsolve_print_scales Lib "lpsolve55.dll" Alias "print_scales" (ByVal lp As Long)
Private Declare Sub lpsolve_print_solution Lib "lpsolve55.dll" Alias "print_solution" (ByVal lp As Long, ByVal columns As Long)
Private Declare Sub lpsolve_print_str Lib "lpsolve55.dll" Alias "print_str" (ByVal lp As Long, ByVal str As String)
Private Declare Sub lpsolve_print_tableau Lib "lpsolve55.dll" Alias "print_tableau" (ByVal lp As Long)
Private Declare Sub lpsolve_put_abortfunc Lib "lpsolve55.dll" Alias "put_abortfunc" (ByVal lp As Long, ByVal newctrlc As Long, ByVal ctrlchandle As Long)
Private Declare Sub lpsolve_put_logfunc Lib "lpsolve55.dll" Alias "put_logfunc" (ByVal lp As Long, ByVal newlog As Long, ByVal loghandle As Long)
Private Declare Sub lpsolve_put_msgfunc Lib "lpsolve55.dll" Alias "put_msgfunc" (ByVal lp As Long, ByVal newmsg As Long, ByVal msghandle As Long, ByVal mask As lpsolve_msgmask)
Private Declare Function lpsolve_read_basis Lib "lpsolve55.dll" Alias "read_basis" (ByVal lp As Long, ByVal filename As String, ByVal info As String) As Boolean
Private Declare Function lpsolve_read_freeMPS Lib "lpsolve55.dll" Alias "read_freeMPS" (ByVal filename As String, ByVal options As Long) As Long
Private Declare Function lpsolve_read_LP Lib "lpsolve55.dll" Alias "read_LP" (ByVal filename As String, ByVal verbose As Long, ByVal lp_name As String) As Long
Private Declare Function lpsolve_read_MPS Lib "lpsolve55.dll" Alias "read_MPS" (ByVal filename As String, ByVal options As Long) As Long
Private Declare Function lpsolve_read_XLI Lib "lpsolve55.dll" Alias "read_XLI" (ByVal xliname As String, ByVal modelname As String, ByVal dataname As String, ByVal options As String, ByVal verbose As Long) As Long
Private Declare Sub lpsolve_reset_basis Lib "lpsolve55.dll" Alias "reset_basis" (ByVal lp As Long)
Private Declare Sub lpsolve_reset_params Lib "lpsolve55.dll" Alias "reset_params" (ByVal lp As Long)
Private Declare Function lpsolve_read_params Lib "lpsolve55.dll" Alias "read_params" (ByVal lp As Long, ByVal filename As String, ByVal options As String) As Boolean
Private Declare Function lpsolve_set_add_rowmode Lib "lpsolve55.dll" Alias "set_add_rowmode" (ByVal lp As Long, ByVal turnon As Boolean) As Boolean
Private Declare Sub lpsolve_set_anti_degen Lib "lpsolve55.dll" Alias "set_anti_degen" (ByVal lp As Long, ByVal anti_degen As lpsolve_anti_degen)
Private Declare Function lpsolve_set_basis Lib "lpsolve55.dll" Alias "set_basis" (ByVal lp As Long, ByRef bascolumn As Long, ByVal nonbasic As Boolean) As Boolean
Private Declare Sub lpsolve_set_basiscrash Lib "lpsolve55.dll" Alias "set_basiscrash" (ByVal lp As Long, ByVal mode As lpsolve_basiscrash)
Private Declare Sub lpsolve_set_basisvar Lib "lpsolve55.dll" Alias "set_basisvar" (ByVal lp As Long, ByVal basisPos As Long, ByVal enteringCol As Long)
Private Declare Sub lpsolve_set_bb_depthlimit Lib "lpsolve55.dll" Alias "set_bb_depthlimit" (ByVal lp As Long, ByVal bb_maxlevel As Long)
Private Declare Sub lpsolve_set_bb_floorfirst Lib "lpsolve55.dll" Alias "set_bb_floorfirst" (ByVal lp As Long, ByVal bb_floorfirst As lpsolve_branch)
Private Declare Sub lpsolve_set_bb_rule Lib "lpsolve55.dll" Alias "set_bb_rule" (ByVal lp As Long, ByVal bb_rule As lpsolve_BBstrategies)
Private Declare Function lpsolve_set_BFP Lib "lpsolve55.dll" Alias "set_BFP" (ByVal lp As Long, ByVal filename As String) As Boolean
Private Declare Function lpsolve_set_binary Lib "lpsolve55.dll" Alias "set_binary" (ByVal lp As Long, ByVal column As Long, ByVal must_be_bin As Boolean) As Boolean
Private Declare Function lpsolve_set_bounds Lib "lpsolve55.dll" Alias "set_bounds" (ByVal lp As Long, ByVal column As Long, ByVal lower As Double, ByVal upper As Double) As Boolean
Private Declare Sub lpsolve_set_bounds_tighter Lib "lpsolve55.dll" Alias "set_bounds_tighter" (ByVal lp As Long, ByVal tighten As Boolean)
Private Declare Sub lpsolve_set_break_at_first Lib "lpsolve55.dll" Alias "set_break_at_first" (ByVal lp As Long, ByVal break_at_first As Boolean)
Private Declare Sub lpsolve_set_break_at_value Lib "lpsolve55.dll" Alias "set_break_at_value" (ByVal lp As Long, ByVal break_at_value As Double)
Private Declare Sub lpsolve_set_break_numeric_accuracy Lib "lpsolve55.dll" Alias "set_break_numeric_accuracy" (ByVal lp As Long, ByVal accuracy As Double)
Private Declare Function lpsolve_set_col_name Lib "lpsolve55.dll" Alias "set_col_name" (ByVal lp As Long, ByVal column As Long, ByVal new_name As String) As Boolean
Private Declare Function lpsolve_set_column Lib "lpsolve55.dll" Alias "set_column" (ByVal lp As Long, ByVal col_no As Long, ByRef column As Double) As Boolean
Private Declare Function lpsolve_set_columnex Lib "lpsolve55.dll" Alias "set_columnex" (ByVal lp As Long, ByVal col_no As Long, ByVal count As Long, ByRef column As Double, ByRef rowno As Long) As Boolean
Private Declare Function lpsolve_set_constr_type Lib "lpsolve55.dll" Alias "set_constr_type" (ByVal lp As Long, ByVal row As Long, ByVal con_type As lpsolve_constr_types) As Boolean
Private Declare Sub lpsolve_set_debug Lib "lpsolve55.dll" Alias "set_debug" (ByVal lp As Long, ByVal debug_ As Boolean)
Private Declare Sub lpsolve_set_epsb Lib "lpsolve55.dll" Alias "set_epsb" (ByVal lp As Long, ByVal epsb As Double)
Private Declare Sub lpsolve_set_epsd Lib "lpsolve55.dll" Alias "set_epsd" (ByVal lp As Long, ByVal epsd As Double)
Private Declare Sub lpsolve_set_epsel Lib "lpsolve55.dll" Alias "set_epsel" (ByVal lp As Long, ByVal epsel As Double)
Private Declare Sub lpsolve_set_epsint Lib "lpsolve55.dll" Alias "set_epsint" (ByVal lp As Long, ByVal epsint As Double)
Private Declare Sub lpsolve_set_epslevel Lib "lpsolve55.dll" Alias "set_epslevel" (ByVal lp As Long, ByVal epslevel As Long)
Private Declare Sub lpsolve_set_epsperturb Lib "lpsolve55.dll" Alias "set_epsperturb" (ByVal lp As Long, ByVal epsperturb As Double)
Private Declare Sub lpsolve_set_epspivot Lib "lpsolve55.dll" Alias "set_epspivot" (ByVal lp As Long, ByVal epspivot As Double)
Private Declare Sub lpsolve_set_improve Lib "lpsolve55.dll" Alias "set_improve" (ByVal lp As Long, ByVal improve As lpsolve_improves)
Private Declare Sub lpsolve_set_infinite Lib "lpsolve55.dll" Alias "set_infinite" (ByVal lp As Long, ByVal infinite As Double)
Private Declare Function lpsolve_set_int Lib "lpsolve55.dll" Alias "set_int" (ByVal lp As Long, ByVal column As Long, ByVal must_be_int As Boolean) As Boolean
Private Declare Sub lpsolve_set_lag_trace Lib "lpsolve55.dll" Alias "set_lag_trace" (ByVal lp As Long, ByVal lag_trace As Boolean)
Private Declare Function lpsolve_set_lowbo Lib "lpsolve55.dll" Alias "set_lowbo" (ByVal lp As Long, ByVal column As Long, ByVal value As Double) As Boolean
Private Declare Function lpsolve_set_lp_name Lib "lpsolve55.dll" Alias "set_lp_name" (ByVal lp As Long, ByVal lpname As String) As Boolean
Private Declare Function lpsolve_set_mat Lib "lpsolve55.dll" Alias "set_mat" (ByVal lp As Long, ByVal row As Long, ByVal column As Long, ByVal value As Double) As Boolean
Private Declare Sub lpsolve_set_maxim Lib "lpsolve55.dll" Alias "set_maxim" (ByVal lp As Long)
Private Declare Sub lpsolve_set_maxpivot Lib "lpsolve55.dll" Alias "set_maxpivot" (ByVal lp As Long, ByVal max_num_inv As Long)
Private Declare Sub lpsolve_set_minim Lib "lpsolve55.dll" Alias "set_minim" (ByVal lp As Long)
Private Declare Sub lpsolve_set_mip_gap Lib "lpsolve55.dll" Alias "set_mip_gap" (ByVal lp As Long, ByVal absolute As Boolean, ByVal mip_gap As Double)
Private Declare Sub lpsolve_set_negrange Lib "lpsolve55.dll" Alias "set_negrange" (ByVal lp As Long, ByVal negrange As Double)
Private Declare Function lpsolve_set_obj Lib "lpsolve55.dll" Alias "set_obj" (ByVal lp As Long, ByVal column As Long, ByVal value As Double) As Boolean
Private Declare Sub lpsolve_set_obj_bound Lib "lpsolve55.dll" Alias "set_obj_bound" (ByVal lp As Long, ByVal obj_bound As Double)
Private Declare Function lpsolve_set_obj_fn Lib "lpsolve55.dll" Alias "set_obj_fn" (ByVal lp As Long, ByRef row As Double) As Boolean
Private Declare Function lpsolve_set_obj_fnex Lib "lpsolve55.dll" Alias "set_obj_fnex" (ByVal lp As Long, ByVal count As Long, ByRef row As Double, ByRef colno As Long) As Boolean
Private Declare Function lpsolve_set_outputfile Lib "lpsolve55.dll" Alias "set_outputfile" (ByVal lp As Long, ByVal filename As String) As Boolean
Private Declare Sub lpsolve_set_pivoting Lib "lpsolve55.dll" Alias "set_pivoting" (ByVal lp As Long, ByVal piv_rule As lpsolve_piv_rules)
Private Declare Sub lpsolve_set_preferdual Lib "lpsolve55.dll" Alias "set_preferdual" (ByVal lp As Long, ByVal dodual As Boolean)
Private Declare Sub lpsolve_set_presolve Lib "lpsolve55.dll" Alias "set_presolve" (ByVal lp As Long, ByVal do_presolve As lpsolve_presolve, ByVal maxloops As Long)
Private Declare Sub lpsolve_set_print_sol Lib "lpsolve55.dll" Alias "set_print_sol" (ByVal lp As Long, ByVal print_sol As Long)
Private Declare Function lpsolve_set_PseudoCosts Lib "lpsolve55.dll" Alias "set_PseudoCosts" (ByVal lp As Long, ByRef clower As Double, ByRef cupper As Double, ByRef updatelimit As Long) As Boolean
Private Declare Function lpsolve_set_rh Lib "lpsolve55.dll" Alias "set_rh" (ByVal lp As Long, ByVal row As Long, ByVal value As Double) As Boolean
Private Declare Function lpsolve_set_rh_range Lib "lpsolve55.dll" Alias "set_rh_range" (ByVal lp As Long, ByVal row As Long, ByVal deltavalue As Double) As Boolean
Private Declare Sub lpsolve_set_rh_vec Lib "lpsolve55.dll" Alias "set_rh_vec" (ByVal lp As Long, ByRef rh As Double)
Private Declare Function lpsolve_set_row Lib "lpsolve55.dll" Alias "set_row" (ByVal lp As Long, ByVal row_no As Long, ByRef row As Double) As Boolean
Private Declare Function lpsolve_set_row_name Lib "lpsolve55.dll" Alias "set_row_name" (ByVal lp As Long, ByVal row As Long, ByVal new_name As String) As Boolean
Private Declare Function lpsolve_set_rowex Lib "lpsolve55.dll" Alias "set_rowex" (ByVal lp As Long, ByVal row_no As Long, ByVal count As Long, ByRef row As Double, ByRef colno As Long) As Boolean
Private Declare Sub lpsolve_set_scalelimit Lib "lpsolve55.dll" Alias "set_scalelimit" (ByVal lp As Long, ByVal scalelimit As Double)
Private Declare Sub lpsolve_set_scaling Lib "lpsolve55.dll" Alias "set_scaling" (ByVal lp As Long, ByVal scalemode As lpsolve_scales)
Private Declare Function lpsolve_set_semicont Lib "lpsolve55.dll" Alias "set_semicont" (ByVal lp As Long, ByVal column As Long, ByVal must_be_sc As Boolean) As Boolean
Private Declare Sub lpsolve_set_sense Lib "lpsolve55.dll" Alias "set_sense" (ByVal lp As Long, ByVal maximize As Boolean)
Private Declare Sub lpsolve_set_simplextype Lib "lpsolve55.dll" Alias "set_simplextype" (ByVal lp As Long, ByVal simplextype As lpsolve_simplextypes)
Private Declare Sub lpsolve_set_solutionlimit Lib "lpsolve55.dll" Alias "set_solutionlimit" (ByVal lp As Long, ByVal limit As Long)
Private Declare Sub lpsolve_set_timeout Lib "lpsolve55.dll" Alias "set_timeout" (ByVal lp As Long, ByVal sectimeout As Long)
Private Declare Sub lpsolve_set_trace Lib "lpsolve55.dll" Alias "set_trace" (ByVal lp As Long, ByVal trace As Boolean)
Private Declare Function lpsolve_set_unbounded Lib "lpsolve55.dll" Alias "set_unbounded" (ByVal lp As Long, ByVal column As Long) As Boolean
Private Declare Function lpsolve_set_upbo Lib "lpsolve55.dll" Alias "set_upbo" (ByVal lp As Long, ByVal column As Long, ByVal value As Double) As Boolean
Private Declare Sub lpsolve_set_use_names Lib "lpsolve55.dll" Alias "set_use_names" (ByVal lp As Long, ByVal isrow As Boolean, ByVal use_names As Boolean)
Private Declare Function lpsolve_set_var_branch Lib "lpsolve55.dll" Alias "set_var_branch" (ByVal lp As Long, ByVal column As Long, ByVal branch_mode As lpsolve_branch) As Boolean
Private Declare Function lpsolve_set_var_weights Lib "lpsolve55.dll" Alias "set_var_weights" (ByVal lp As Long, ByRef weights As Double) As Boolean
Private Declare Sub lpsolve_set_verbose Lib "lpsolve55.dll" Alias "set_verbose" (ByVal lp As Long, ByVal verbose As Long)
Private Declare Function lpsolve_set_XLI Lib "lpsolve55.dll" Alias "set_XLI" (ByVal lp As Long, ByVal filename As String) As Boolean
Private Declare Function lpsolve_solve Lib "lpsolve55.dll" Alias "solve" (ByVal lp As Long) As lpsolve_return
Private Declare Function lpsolve_str_add_column Lib "lpsolve55.dll" Alias "str_add_column" (ByVal lp As Long, ByVal col_string As String) As Boolean
Private Declare Function lpsolve_str_add_constraint Lib "lpsolve55.dll" Alias "str_add_constraint" (ByVal lp As Long, ByVal row_string As String, ByVal constr_type As lpsolve_constr_types, ByVal rh As Double) As Boolean
Private Declare Function lpsolve_str_add_lag_con Lib "lpsolve55.dll" Alias "str_add_lag_con" (ByVal lp As Long, ByVal row_string As String, ByVal con_type As lpsolve_constr_types, ByVal rhs As Double) As Boolean
Private Declare Function lpsolve_str_set_obj_fn Lib "lpsolve55.dll" Alias "str_set_obj_fn" (ByVal lp As Long, ByVal row_string As String) As Boolean
Private Declare Function lpsolve_str_set_rh_vec Lib "lpsolve55.dll" Alias "str_set_rh_vec" (ByVal lp As Long, ByVal rh_string As String) As Boolean
Private Declare Function lpsolve_time_elapsed Lib "lpsolve55.dll" Alias "time_elapsed" (ByVal lp As Long) As Double
Private Declare Sub lpsolve_unscale Lib "lpsolve55.dll" Alias "unscale" (ByVal lp As Long)
Private Declare Function lpsolve_write_basis Lib "lpsolve55.dll" Alias "write_basis" (ByVal lp As Long, ByVal filename As String) As Boolean
Private Declare Function lpsolve_write_freemps Lib "lpsolve55.dll" Alias "write_freemps" (ByVal lp As Long, ByVal filename As String) As Boolean
Private Declare Function lpsolve_write_lp Lib "lpsolve55.dll" Alias "write_lp" (ByVal lp As Long, ByVal filename As String) As Boolean
Private Declare Function lpsolve_write_mps Lib "lpsolve55.dll" Alias "write_mps" (ByVal lp As Long, ByVal filename As String) As Boolean
Private Declare Function lpsolve_write_XLI Lib "lpsolve55.dll" Alias "write_XLI" (ByVal lp As Long, ByVal filename As String, ByVal options As String, ByVal results As Boolean) As Boolean
Private Declare Function lpsolve_write_params Lib "lpsolve55.dll" Alias "write_params" (ByVal lp As Long, ByVal filename As String, ByVal options As String) As Boolean

'-----------------------------------------------------------------------------------------------------------------------------

'possible type of constraints
Public Enum lpsolve_constr_types
    LE = 1
    EQ = 3
    GE = 2
    FR = 0
End Enum

'Possible Scalings
Public Enum lpsolve_scales
    SCALE_EXTREME = 1
    SCALE_RANGE = 2
    SCALE_MEAN = 3
    SCALE_GEOMETRIC = 4
    SCALE_CURTISREID = 7
    SCALE_QUADRATIC = 8
    SCALE_LOGARITHMIC = 16
    SCALE_USERWEIGHT = 31
    SCALE_POWER2 = 32
    SCALE_EQUILIBRATE = 64
    SCALE_INTEGERS = 128
End Enum

'Possible Improvements
Public Enum lpsolve_improves
    IMPROVE_NONE = 0
    IMPROVE_FTRAN = 1
    IMPROVE_SOLUTION = 1
    IMPROVE_DUALFEAS = 2
    IMPROVE_THETAGAP = 4
    IMPROVE_BBSIMPLEX = 8
    IMPROVE_DEFAULT = (IMPROVE_DUALFEAS + IMPROVE_THETAGAP)
    IMPROVE_INVERSE = (IMPROVE_SOLUTION + IMPROVE_THETAGAP)
End Enum

Public Enum lpsolve_piv_rules
    PRICER_FIRSTINDEX = 0
    PRICER_DANTZIG = 1
    PRICER_DEVEX = 2
    PRICER_STEEPESTEDGE = 3
    PRICE_PRIMALFALLBACK = 4
    PRICE_MULTIPLE = 8
    PRICE_PARTIAL = 16
    PRICE_ADAPTIVE = 32
    PRICE_HYBRID = 64
    PRICE_RANDOMIZE = 128
    PRICE_AUTOPARTIALCOLS = 256
    PRICE_AUTOPARTIALROWS = 512
    PRICE_LOOPLEFT = 1024
    PRICE_LOOPALTERNATE = 2048
    PRICE_AUTOPARTIAL = PRICE_AUTOPARTIALCOLS + PRICE_AUTOPARTIALROWS
End Enum

Public Enum lpsolve_presolve
    PRESOLVE_NONE = 0
    PRESOLVE_ROWS = 1
    PRESOLVE_COLS = 2
    PRESOLVE_LINDEP = 4
    PRESOLVE_SOS = 32
    PRESOLVE_REDUCEMIP = 64
    PRESOLVE_KNAPSACK = 128
    PRESOLVE_ELIMEQ2 = 256
    PRESOLVE_IMPLIEDFREE = 512
    PRESOLVE_REDUCEGCD = 1024
    PRESOLVE_PROBEFIX = 2048
    PRESOLVE_PROBEREDUCE = 4096
    PRESOLVE_ROWDOMINATE = 8192
    PRESOLVE_COLDOMINATE = 16384
    PRESOLVE_MERGEROWS = 32768
    PRESOLVE_IMPLIEDSLK = 65536
    PRESOLVE_COLFIXDUAL = 131072
    PRESOLVE_BOUNDS = 262144
    PRESOLVE_DUALS = 524288
    PRESOLVE_SENSDUALS = 1048576
End Enum

Public Enum lpsolve_anti_degen
    ANTIDEGEN_NONE = 0
    ANTIDEGEN_FIXEDVARS = 1
    ANTIDEGEN_COLUMNCHECK = 2
    ANTIDEGEN_STALLING = 4
    ANTIDEGEN_NUMFAILURE = 8
    ANTIDEGEN_LOSTFEAS = 16
    ANTIDEGEN_INFEASIBLE = 32
    ANTIDEGEN_DYNAMIC = 64
    ANTIDEGEN_DURINGBB = 128
    ANTIDEGEN_RHSPERTURB = 256
    ANTIDEGEN_BOUNDFLIP = 512
End Enum

Public Enum lpsolve_basiscrash
    CRASH_NOTHING = 0
    CRASH_MOSTFEASIBLE = 2
End Enum

Public Enum lpsolve_simplextypes
    SIMPLEX_PRIMAL_PRIMAL = 5
    SIMPLEX_DUAL_PRIMAL = 6
    SIMPLEX_PRIMAL_DUAL = 9
    SIMPLEX_DUAL_DUAL = 10
End Enum

'B&B strategies
Public Enum lpsolve_BBstrategies
    NODE_FIRSTSELECT = 0
    NODE_GAPSELECT = 1
    NODE_RANGESELECT = 2
    NODE_FRACTIONSELECT = 3
    NODE_PSEUDOCOSTSELECT = 4
    NODE_PSEUDONONINTSELECT = 5
    NODE_PSEUDORATIOSELECT = 6
    NODE_USERSELECT = 7
    NODE_WEIGHTREVERSEMODE = 8
    NODE_BRANCHREVERSEMODE = 16
    NODE_GREEDYMODE = 32
    NODE_PSEUDOCOSTMODE = 64
    NODE_DEPTHFIRSTMODE = 128
    NODE_RANDOMIZEMODE = 256
    NODE_GUBMODE = 512
    NODE_DYNAMICMODE = 1024
    NODE_RESTARTMODE = 2048
    NODE_BREADTHFIRSTMODE = 4096
    NODE_AUTOORDER = 8192
    NODE_RCOSTFIXING = 16384
    NODE_STRONGINIT = 32768
End Enum

'possible return values of lp solver
Public Enum lpsolve_return
    NOMEMORY = -2
    OPTIMAL = 0
    SUBOPTIMAL = 1
    INFEASIBLE = 2
    UNBOUNDED = 3
    DEGENERATE = 4
    NUMFAILURE = 5
    USERABORT = 6
    TIMEOUT = 7
    PRESOLVED = 9
    PROCFAIL = 10
    PROCBREAK = 11
    FEASFOUND = 12
    NOFEASFOUND = 13
    ACCURACYERROR = 25
End Enum

'possible branch values
Public Enum lpsolve_branch
    BRANCH_CEILING = 0
    BRANCH_FLOOR = 1
    BRANCH_AUTOMATIC = 2
    BRANCH_DEFAULT = 3
End Enum

'possible message values
Public Enum lpsolve_msgmask
    MSG_PRESOLVE = 1
    MSG_LPFEASIBLE = 8
    MSG_LPOPTIMAL = 16
    MSG_MILPEQUAL = 32
    MSG_MILPFEASIBLE = 128
    MSG_MILPBETTER = 512
End Enum

Private Function SetEnvironmentVariable(name As String, value As String) As Boolean

    SetEnvironmentVariable = SetEnvironmentVariableA(name, value)

End Function

Private Function GetEnvironmentVariable(name As String) As String
    Dim l As Long
    Dim Buf As String

    l = GetEnvironmentVariableA(name, vbNullString, 0)
    If l > 0 Then
        Buf = Space$(l)
        l = GetEnvironmentVariableA(name, Buf, Len(Buf))
        GetEnvironmentVariable = Mid$(Buf, 1, l)
    End If

End Function

Public Function Ptr2Str(ptr As Long) As String
    Dim l As Long

    If ptr = 0 Then
        Ptr2Str = vbNullString
    Else
        l = lstrlen(ptr)
        Ptr2Str = Space$(l)
        CopyMemory Ptr2Str, ptr, l
    End If

End Function

Public Function Init(Optional ByVal dllPath As String = "") As Boolean
    Static bEnvChanged As Boolean
    Dim Path As String
    Dim Buf As String

    If Len(dllPath) = 0 Then
        dllPath = App.Path
    End If
    Buf = dllPath
    If Right$(Buf, 1) <> "\" Then
        Buf = Buf & "\"
    End If
    Buf = Buf & "lpsolve55.dll"
    On Error Resume Next
    Init = (Len(Dir$(Buf, vbNormal)) > 0)
    If Init Then
        If Not bEnvChanged Then
            bEnvChanged = True
            Path = GetEnvironmentVariable("PATH")
            If InStr(1, Path & ";", dllPath & ";", vbTextCompare) = 0 Then
                SetEnvironmentVariable "PATH", dllPath & ";" & Path
            End If
        End If
    End If

End Function

'-----------------------------------------------------------------------------------------------------------------------------

Public Function add_column(ByVal lp As Long, ByRef column As Double) As Boolean

    add_column = (lpsolve_add_column(lp, column) <> 0)

End Function

Public Function add_columnex(ByVal lp As Long, ByVal count As Long, ByRef column As Double, ByRef rowno As Long) As Boolean

    add_columnex = (lpsolve_add_columnex(lp, count, column, rowno) <> 0)

End Function

Public Function add_constraint(ByVal lp As Long, ByRef row As Double, ByVal constr_type As lpsolve_constr_types, ByVal rh As Double) As Boolean

    add_constraint = (lpsolve_add_constraint(lp, row, constr_type, rh) <> 0)

End Function

Public Function add_constraintex(ByVal lp As Long, ByVal count As Long, ByRef row As Double, ByRef colno As Long, ByVal constr_type As lpsolve_constr_types, ByVal rh As Double) As Boolean

    add_constraintex = (lpsolve_add_constraintex(lp, count, row, colno, constr_type, rh) <> 0)

End Function

Public Function add_lag_con(ByVal lp As Long, ByRef row As Double, ByVal con_type As lpsolve_constr_types, ByVal rhs As Double) As Boolean

    add_lag_con = (lpsolve_add_lag_con(lp, row, con_type, rhs) <> 0)

End Function

Public Function add_SOS(ByVal lp As Long, ByVal name As String, ByVal sostype As Long, ByVal priority As Long, ByVal count As Long, ByRef sosvars As Long, ByRef weights As Double) As Long

    add_SOS = lpsolve_add_SOS(lp, name, sostype, priority, count, sosvars, weights)

End Function

Public Function column_in_lp(ByVal lp As Long, ByRef column As Double) As Boolean

    column_in_lp = (lpsolve_column_in_lp(lp, column) <> 0)

End Function

Public Function copy_lp(ByVal lp As Long) As Long

    copy_lp = lpsolve_copy_lp(lp)

End Function

Public Sub default_basis(ByVal lp As Long)

    Call lpsolve_default_basis(lp)

End Sub

Public Function del_column(ByVal lp As Long, ByVal column As Long) As Boolean

    del_column = (lpsolve_del_column(lp, column) <> 0)

End Function

Public Function del_constraint(ByVal lp As Long, ByVal del_row As Long) As Boolean

    del_constraint = (lpsolve_del_constraint(lp, del_row) <> 0)

End Function

Public Sub delete_lp(ByVal lp As Long)

    Call lpsolve_delete_lp(lp)

End Sub

Public Function dualize_lp(ByVal lp As Long) As Boolean

    dualize_lp = (lpsolve_dualize_lp(lp) <> 0)

End Function

Public Function get_anti_degen(ByVal lp As Long) As lpsolve_anti_degen

    get_anti_degen = lpsolve_get_anti_degen(lp)

End Function

Public Function get_basis(ByVal lp As Long, ByRef bascolumn As Long, ByVal nonbasic As Boolean) As Boolean

    get_basis = (lpsolve_get_basis(lp, bascolumn, nonbasic) <> 0)

End Function

Public Function get_basiscrash(ByVal lp As Long) As lpsolve_basiscrash

    get_basiscrash = lpsolve_get_basiscrash(lp)

End Function

Public Function get_bb_depthlimit(ByVal lp As Long) As Long

    get_bb_depthlimit = lpsolve_get_bb_depthlimit(lp)

End Function

Public Function get_bb_floorfirst(ByVal lp As Long) As lpsolve_branch

    get_bb_floorfirst = lpsolve_get_bb_floorfirst(lp)

End Function

Public Function get_bb_rule(ByVal lp As Long) As lpsolve_BBstrategies

    get_bb_rule = lpsolve_get_bb_rule(lp)

End Function

Public Function get_bounds_tighter(ByVal lp As Long) As Boolean

    get_bounds_tighter = (lpsolve_get_bounds_tighter(lp) <> 0)

End Function

Public Function get_break_at_value(ByVal lp As Long) As Double

    get_break_at_value = lpsolve_get_break_at_value(lp)

End Function

Public Function get_col_name(ByVal lp As Long, ByVal column As Long) As String

    get_col_name = Ptr2Str(lpsolve_get_col_name(lp, column))

End Function

Public Function get_column(ByVal lp As Long, ByVal col_nr As Long, ByRef column As Double) As Boolean

    get_column = (lpsolve_get_column(lp, col_nr, column) <> 0)

End Function

Public Function get_columnex(ByVal lp As Long, ByVal col_nr As Long, ByRef column As Double, ByRef nzrow As Long) As Long

    get_columnex = lpsolve_get_columnex(lp, col_nr, column, nzrow)

End Function

Public Function get_constr_type(ByVal lp As Long, ByVal row As Long) As lpsolve_constr_types

    get_constr_type = lpsolve_get_constr_type(lp, row)

End Function

Public Function get_constr_value(ByVal lp As Long, ByVal row As Long, ByVal count As Long, ByRef primsolution As Double, ByRef nzindex As Long) As Double

    get_constr_value = lpsolve_get_constr_value(lp, row, count, primsolution, nzindex)

End Function

Public Function get_constraints(ByVal lp As Long, ByRef constr As Double) As Boolean

    get_constraints = (lpsolve_get_constraints(lp, constr) <> 0)

End Function

Public Function get_dual_solution(ByVal lp As Long, ByRef rc As Double) As Boolean

    get_dual_solution = (lpsolve_get_dual_solution(lp, rc) <> 0)

End Function

Public Function get_epsb(ByVal lp As Long) As Double

    get_epsb = lpsolve_get_epsb(lp)

End Function

Public Function get_epsd(ByVal lp As Long) As Double

    get_epsd = lpsolve_get_epsd(lp)

End Function

Public Function get_epsel(ByVal lp As Long) As Double

    get_epsel = lpsolve_get_epsel(lp)

End Function

Public Function get_epsint(ByVal lp As Long) As Double

    get_epsint = lpsolve_get_epsint(lp)

End Function

Public Function get_epsperturb(ByVal lp As Long) As Double

    get_epsperturb = lpsolve_get_epsperturb(lp)

End Function

Public Function get_epspivot(ByVal lp As Long) As Double

    get_epspivot = lpsolve_get_epspivot(lp)

End Function

Public Function get_improve(ByVal lp As Long) As lpsolve_improves

    get_improve = lpsolve_get_improve(lp)

End Function

Public Function get_infinite(ByVal lp As Long) As Double

    get_infinite = lpsolve_get_infinite(lp)

End Function

Public Function get_lambda(ByVal lp As Long, ByRef lambda As Double) As Boolean

    get_lambda = (lpsolve_get_lambda(lp, lambda) <> 0)

End Function

Public Function get_lowbo(ByVal lp As Long, ByVal column As Long) As Double

    get_lowbo = lpsolve_get_lowbo(lp, column)

End Function

Public Function get_lp_index(ByVal lp As Long, ByVal orig_index As Long) As Long

    get_lp_index = lpsolve_get_lp_index(lp, orig_index)

End Function

Public Function get_lp_name(ByVal lp As Long) As String

    get_lp_name = Ptr2Str(lpsolve_get_lp_name(lp))

End Function

Public Function get_Lrows(ByVal lp As Long) As Long

    get_Lrows = lpsolve_get_Lrows(lp)

End Function

Public Function get_mat(ByVal lp As Long, ByVal row As Long, ByVal column As Long) As Double

    get_mat = lpsolve_get_mat(lp, row, column)

End Function

Public Function get_max_level(ByVal lp As Long) As Long

    get_max_level = lpsolve_get_max_level(lp)

End Function

Public Function get_maxpivot(ByVal lp As Long) As Long

    get_maxpivot = lpsolve_get_maxpivot(lp)

End Function

Public Function get_mip_gap(ByVal lp As Long, ByVal absolute As Boolean) As Double

    get_mip_gap = lpsolve_get_mip_gap(lp, absolute)

End Function

Public Function get_nameindex(ByVal lp As Long, ByVal name As String, ByVal isrow As Boolean) As Long

    get_nameindex = lpsolve_get_nameindex(lp, name, isrow)

End Function

Public Function get_Ncolumns(ByVal lp As Long) As Long

    get_Ncolumns = lpsolve_get_Ncolumns(lp)

End Function

Public Function get_negrange(ByVal lp As Long) As Double

    get_negrange = lpsolve_get_negrange(lp)

End Function

Public Function get_nonzeros(ByVal lp As Long) As Long

    get_nonzeros = lpsolve_get_nonzeros(lp)

End Function

Public Function get_Norig_columns(ByVal lp As Long) As Long

    get_Norig_columns = lpsolve_get_Norig_columns(lp)

End Function

Public Function get_Norig_rows(ByVal lp As Long) As Long

    get_Norig_rows = lpsolve_get_Norig_rows(lp)

End Function

Public Function get_Nrows(ByVal lp As Long) As Long

    get_Nrows = lpsolve_get_Nrows(lp)

End Function

Public Function get_obj_bound(ByVal lp As Long) As Double

    get_obj_bound = lpsolve_get_obj_bound(lp)

End Function

Public Function get_objective(ByVal lp As Long) As Double

    get_objective = lpsolve_get_objective(lp)

End Function

Public Function get_orig_index(ByVal lp As Long, ByVal lp_index As Long) As Long

    get_orig_index = lpsolve_get_orig_index(lp, lp_index)

End Function

Public Function get_origcol_name(ByVal lp As Long, ByVal column As Long) As String

    get_origcol_name = Ptr2Str(lpsolve_get_origcol_name(lp, column))

End Function

Public Function get_origrow_name(ByVal lp As Long, ByVal row As Long) As String

    get_origrow_name = Ptr2Str(lpsolve_get_origrow_name(lp, row))

End Function

Public Function get_pivoting(ByVal lp As Long) As lpsolve_piv_rules

    get_pivoting = lpsolve_get_pivoting(lp)

End Function

Public Function get_presolve(ByVal lp As Long) As lpsolve_presolve

    get_presolve = lpsolve_get_presolve(lp)

End Function

Public Function get_presolveloops(ByVal lp As Long) As Long

    get_presolveloops = lpsolve_get_presolveloops(lp)

End Function

Public Function get_primal_solution(ByVal lp As Long, ByRef pv As Double) As Boolean

    get_primal_solution = (lpsolve_get_primal_solution(lp, pv) <> 0)

End Function

Public Function get_print_sol(ByVal lp As Long) As Long

    get_print_sol = lpsolve_get_print_sol(lp)

End Function

Public Function get_PseudoCosts(ByVal lp As Long, ByRef clower As Double, ByRef cupper As Double, ByRef updatelimit As Long) As Boolean

    get_PseudoCosts = (lpsolve_get_PseudoCosts(lp, clower, cupper, updatelimit) <> 0)

End Function

Public Function get_rh(ByVal lp As Long, ByVal row As Long) As Double

    get_rh = lpsolve_get_rh(lp, row)

End Function

Public Function get_rh_range(ByVal lp As Long, ByVal row As Long) As Double

    get_rh_range = lpsolve_get_rh_range(lp, row)

End Function

Public Function get_row(ByVal lp As Long, ByVal row_nr As Long, ByRef row As Double) As Boolean

    get_row = (lpsolve_get_row(lp, row_nr, row) <> 0)

End Function

Public Function get_rowex(ByVal lp As Long, ByVal row_nr As Long, ByRef row As Double, colno As Long) As Long

    get_rowex = lpsolve_get_rowex(lp, row_nr, row, colno)

End Function

Public Function get_row_name(ByVal lp As Long, ByVal row As Long) As String

    get_row_name = Ptr2Str(lpsolve_get_row_name(lp, row))

End Function

Public Function get_scalelimit(ByVal lp As Long) As Double

    get_scalelimit = lpsolve_get_scalelimit(lp)

End Function

Public Function get_scaling(ByVal lp As Long) As lpsolve_scales

    get_scaling = lpsolve_get_scaling(lp)

End Function

Public Function get_sensitivity_objex(ByVal lp As Long, ByRef objfrom As Double, ByRef objtill As Double, ByRef objfromvalue As Double, ByRef objtillvalue As Double) As Boolean

    get_sensitivity_objex = (lpsolve_get_sensitivity_objex(lp, objfrom, objtill, objfromvalue, objtillvalue) <> 0)

End Function

Public Function get_sensitivity_obj(ByVal lp As Long, ByRef objfrom As Double, ByRef objtill As Double) As Boolean

    get_sensitivity_obj = (lpsolve_get_sensitivity_obj(lp, objfrom, objtill) <> 0)

End Function

Public Function get_sensitivity_rhs(ByVal lp As Long, ByRef duals As Double, ByRef dualsfrom As Double, ByRef dualstill As Double) As Boolean

    get_sensitivity_rhs = (lpsolve_get_sensitivity_rhs(lp, duals, dualsfrom, dualstill) <> 0)

End Function

Public Function get_simplextype(ByVal lp As Long) As lpsolve_simplextypes

    get_simplextype = lpsolve_get_simplextype(lp)

End Function

Public Function get_solutioncount(ByVal lp As Long) As Long

    get_solutioncount = lpsolve_get_solutioncount(lp)

End Function

Public Function get_solutionlimit(ByVal lp As Long) As Long

    get_solutionlimit = lpsolve_get_solutionlimit(lp)

End Function

Public Function get_status(ByVal lp As Long) As Long

    get_status = lpsolve_get_status(lp)

End Function

Public Function get_statustext(ByVal lp As Long, ByVal statuscode As Long) As String

    get_statustext = Ptr2Str(lpsolve_get_statustext(lp, statuscode))

End Function

Public Function get_timeout(ByVal lp As Long) As Long

    get_timeout = lpsolve_get_timeout(lp)

End Function

Public Function get_total_iter(ByVal lp As Long) As Long

    get_total_iter = lpsolve_get_total_iter(lp)

End Function

Public Function get_total_nodes(ByVal lp As Long) As Long

    get_total_nodes = lpsolve_get_total_nodes(lp)

End Function

Public Function get_upbo(ByVal lp As Long, ByVal column As Long) As Double

    get_upbo = lpsolve_get_upbo(lp, column)

End Function

Public Function get_var_branch(ByVal lp As Long, ByVal column As Long) As lpsolve_branch

    get_var_branch = lpsolve_get_var_branch(lp, column)

End Function

Public Function get_var_dualresult(ByVal lp As Long, ByVal index As Long) As Double

    get_var_dualresult = lpsolve_get_var_dualresult(lp, index)

End Function

Public Function get_var_primalresult(ByVal lp As Long, ByVal index As Long) As Double

    get_var_primalresult = lpsolve_get_var_primalresult(lp, index)

End Function

Public Function get_var_priority(ByVal lp As Long, ByVal column As Long) As Long

    get_var_priority = lpsolve_get_var_priority(lp, column)

End Function

Public Function get_variables(ByVal lp As Long, ByRef var As Double) As Boolean

    get_variables = (lpsolve_get_variables(lp, var) <> 0)

End Function

Public Function get_verbose(ByVal lp As Long) As Long

    get_verbose = lpsolve_get_verbose(lp)

End Function

Public Function get_working_objective(ByVal lp As Long) As Double

    get_working_objective = lpsolve_get_working_objective(lp)

End Function

Public Function guess_basis(ByVal lp As Long, ByRef guessvector As Double, ByRef basisvector As Long) As Boolean

    guess_basis = (lpsolve_guess_basis(lp, guessvector, basisvector) <> 0)

End Function

Public Function has_BFP(ByVal lp As Long) As Boolean

    has_BFP = (lpsolve_has_BFP(lp) <> 0)

End Function

Public Function has_XLI(ByVal lp As Long) As Boolean

    has_XLI = (lpsolve_has_XLI(lp) <> 0)

End Function

Public Function is_add_rowmode(ByVal lp As Long) As Boolean

    is_add_rowmode = (lpsolve_is_add_rowmode(lp) <> 0)

End Function

Public Function is_anti_degen(ByVal lp As Long, ByVal testmask As lpsolve_anti_degen) As Boolean

    is_anti_degen = (lpsolve_is_anti_degen(lp, testmask) <> 0)

End Function

Public Function is_binary(ByVal lp As Long, ByVal column As Long) As Boolean

    is_binary = (lpsolve_is_binary(lp, column) <> 0)

End Function

Public Function is_break_at_first(ByVal lp As Long) As Boolean

    is_break_at_first = (lpsolve_is_break_at_first(lp) <> 0)

End Function

Public Function is_constr_type(ByVal lp As Long, ByVal row As Long, ByVal mask As Long) As Boolean

    is_constr_type = (lpsolve_is_constr_type(lp, row, mask) <> 0)

End Function

Public Function is_debug(ByVal lp As Long) As Boolean

    is_debug = (lpsolve_is_debug(lp) <> 0)

End Function

Public Function is_feasible(ByVal lp As Long, ByRef values As Double, ByVal threshold As Double) As Boolean

    is_feasible = (lpsolve_is_feasible(lp, values, threshold) <> 0)

End Function

Public Function is_infinite(ByVal lp As Long, ByVal value As Double) As Boolean

    is_infinite = (lpsolve_is_infinite(lp, value) <> 0)

End Function

Public Function is_int(ByVal lp As Long, ByVal column As Long) As Boolean

    is_int = (lpsolve_is_int(lp, column) <> 0)

End Function

Public Function is_integerscaling(ByVal lp As Long) As Boolean

    is_integerscaling = (lpsolve_is_integerscaling(lp) <> 0)

End Function

Public Function is_lag_trace(ByVal lp As Long) As Boolean

    is_lag_trace = (lpsolve_is_lag_trace(lp) <> 0)

End Function

Public Function is_maxim(ByVal lp As Long) As Boolean

    is_maxim = (lpsolve_is_maxim(lp) <> 0)

End Function

Public Function is_nativeBFP(ByVal lp As Long) As Boolean

    is_nativeBFP = (lpsolve_is_nativeBFP(lp) <> 0)

End Function

Public Function is_nativeXLI(ByVal lp As Long) As Boolean

    is_nativeXLI = (lpsolve_is_nativeXLI(lp) <> 0)

End Function

Public Function is_negative(ByVal lp As Long, ByVal column As Long) As Boolean

    is_negative = (lpsolve_is_negative(lp, column) <> 0)

End Function

Public Function is_piv_mode(ByVal lp As Long, ByVal testmask As lpsolve_piv_rules) As Boolean

    is_piv_mode = (lpsolve_is_piv_mode(lp, testmask) <> 0)

End Function

Public Function is_piv_rule(ByVal lp As Long, ByVal rule As lpsolve_piv_rules) As Boolean

    is_piv_rule = (lpsolve_is_piv_rule(lp, rule) <> 0)

End Function

Public Function is_presolve(ByVal lp As Long, ByVal testmask As lpsolve_presolve) As Boolean

    is_presolve = (lpsolve_is_presolve(lp, testmask) <> 0)

End Function

Public Function is_scalemode(ByVal lp As Long, ByVal testmask As lpsolve_scales) As Boolean

    is_scalemode = (lpsolve_is_scalemode(lp, testmask) <> 0)

End Function

Public Function is_scaletype(ByVal lp As Long, ByVal scaletype As lpsolve_scales) As Boolean

    is_scaletype = (lpsolve_is_scaletype(lp, scaletype) <> 0)

End Function

Public Function is_semicont(ByVal lp As Long, ByVal column As Long) As Boolean

    is_semicont = (lpsolve_is_semicont(lp, column) <> 0)

End Function

Public Function is_SOS_var(ByVal lp As Long, ByVal column As Long) As Boolean

    is_SOS_var = (lpsolve_is_SOS_var(lp, column) <> 0)

End Function

Public Function is_trace(ByVal lp As Long) As Boolean

    is_trace = (lpsolve_is_trace(lp) <> 0)

End Function

Public Function is_unbounded(ByVal lp As Long, ByVal column As Long) As Boolean

    is_unbounded = (lpsolve_is_unbounded(lp, column) <> 0)

End Function

Public Function is_use_names(ByVal lp As Long, ByVal isrow As Boolean) As Boolean

    is_use_names = (lpsolve_is_use_names(lp, isrow) <> 0)

End Function

Public Sub version(ByRef majorversion As Long, ByRef minorversion As Long, ByRef release As Long, ByRef build As Long)

    Call lpsolve_version(majorversion, minorversion, release, build)

End Sub

Public Function make_lp(ByVal rows As Long, ByVal columns As Long) As Long

    make_lp = lpsolve_make_lp(rows, columns)

End Function

Public Function resize_lp(ByVal lp As Long, ByVal rows As Long, ByVal columns As Long) As Long

    resize_lp = (lpsolve_resize_lp(lp, rows, columns) <> 0)

End Function

Public Sub print_constraints(ByVal lp As Long, ByVal columns As Long)

    Call lpsolve_print_constraints(lp, columns)

End Sub

Public Function print_debugdump(ByVal lp As Long, ByVal filename As String) As Boolean

    print_debugdump = (lpsolve_print_debugdump(lp, filename) <> 0)

End Function

Public Sub print_duals(ByVal lp As Long)

    Call lpsolve_print_duals(lp)

End Sub

Public Sub print_lp(ByVal lp As Long)

    Call lpsolve_print_lp(lp)

End Sub

Public Sub print_objective(ByVal lp As Long)

    Call lpsolve_print_objective(lp)

End Sub

Public Sub print_scales(ByVal lp As Long)

    Call lpsolve_print_scales(lp)

End Sub

Public Sub print_solution(ByVal lp As Long, ByVal columns As Long)

    Call lpsolve_print_solution(lp, columns)

End Sub

Public Sub print_str(ByVal lp As Long, ByVal str As String)

    Call lpsolve_print_str(lp, str)

End Sub

Public Sub print_tableau(ByVal lp As Long)

    Call lpsolve_print_tableau(lp)

End Sub

Public Sub put_abortfunc(ByVal lp As Long, ByVal newctrlc As Long, ByVal ctrlchandle As Long)

    Call lpsolve_put_abortfunc(lp, newctrlc, ctrlchandle)

End Sub

Public Sub put_logfunc(ByVal lp As Long, ByVal newlog As Long, ByVal loghandle As Long)

    Call lpsolve_put_logfunc(lp, newlog, loghandle)

End Sub

Public Sub put_msgfunc(ByVal lp As Long, ByVal newmsg As Long, ByVal msghandle As Long, ByVal mask As lpsolve_msgmask)

    Call lpsolve_put_msgfunc(lp, newmsg, msghandle, mask)

End Sub

Public Function read_basis(ByVal lp As Long, ByVal filename As String, ByVal info As String) As Boolean

    read_basis = (lpsolve_read_basis(lp, filename, info) <> 0)

End Function

Public Function read_freeMPS(ByVal filename As String, ByVal options As Long) As Long

    read_freeMPS = lpsolve_read_freeMPS(filename, options)

End Function

Public Function read_LP(ByVal filename As String, ByVal verbose As Long, ByVal lp_name As String) As Long

    read_LP = lpsolve_read_LP(filename, verbose, lp_name)

End Function

Public Function read_MPS(ByVal filename As String, ByVal options As Long) As Long

    read_MPS = lpsolve_read_MPS(filename, options)

End Function

Public Function read_XLI(ByVal xliname As String, ByVal modelname As String, ByVal dataname As String, ByVal options As String, ByVal verbose As Long) As Long

    read_XLI = lpsolve_read_XLI(xliname, modelname, dataname, options, verbose)

End Function

Public Function read_params(ByVal lp As Long, ByVal filename As String, ByVal options As String) As Boolean

    read_params = (lpsolve_read_params(lp, filename, options) <> 0)

End Function

Public Sub reset_basis(ByVal lp As Long)

    Call lpsolve_reset_basis(lp)

End Sub

Public Sub reset_params(ByVal lp As Long)

    Call lpsolve_reset_params(lp)

End Sub

Public Function set_add_rowmode(ByVal lp As Long, ByVal turnon As Boolean) As Boolean

    set_add_rowmode = (lpsolve_set_add_rowmode(lp, turnon) <> 0)

End Function

Public Sub set_anti_degen(ByVal lp As Long, ByVal anti_degen As lpsolve_anti_degen)

    Call lpsolve_set_anti_degen(lp, anti_degen)

End Sub

Public Function set_basis(ByVal lp As Long, ByRef bascolumn As Long, ByVal nonbasic As Boolean) As Boolean

    set_basis = (lpsolve_set_basis(lp, bascolumn, nonbasic) <> 0)

End Function

Public Sub set_basiscrash(ByVal lp As Long, ByVal mode As lpsolve_basiscrash)

    Call lpsolve_set_basiscrash(lp, mode)

End Sub

Public Sub set_basisvar(ByVal lp As Long, ByVal basisPos As Long, ByVal enteringCol As Long)

    Call lpsolve_set_basisvar(lp, basisPos, enteringCol)

End Sub

Public Sub set_bb_depthlimit(ByVal lp As Long, ByVal bb_maxlevel As Long)

    Call lpsolve_set_bb_depthlimit(lp, bb_maxlevel)

End Sub

Public Sub set_bb_floorfirst(ByVal lp As Long, ByVal bb_floorfirst As lpsolve_branch)

    Call lpsolve_set_bb_floorfirst(lp, bb_floorfirst)

End Sub

Public Sub set_bb_rule(ByVal lp As Long, ByVal bb_rule As lpsolve_BBstrategies)

    Call lpsolve_set_bb_rule(lp, bb_rule)

End Sub

Public Function set_BFP(ByVal lp As Long, ByVal filename As String) As Boolean

    set_BFP = (lpsolve_set_BFP(lp, filename) <> 0)

End Function

Public Function set_binary(ByVal lp As Long, ByVal column As Long, ByVal must_be_bin As Boolean) As Boolean

    set_binary = (lpsolve_set_binary(lp, column, must_be_bin) <> 0)

End Function

Public Function set_bounds(ByVal lp As Long, ByVal column As Long, ByVal lower As Double, ByVal upper As Double) As Boolean

    set_bounds = (lpsolve_set_bounds(lp, column, lower, upper) <> 0)

End Function

Public Sub set_bounds_tighter(ByVal lp As Long, ByVal tighten As Boolean)

    Call lpsolve_set_bounds_tighter(lp, tighten)

End Sub

Public Sub set_break_at_first(ByVal lp As Long, ByVal break_at_first As Boolean)

    Call lpsolve_set_break_at_first(lp, break_at_first)

End Sub

Public Sub set_break_at_value(ByVal lp As Long, ByVal break_at_value As Double)

    Call lpsolve_set_break_at_value(lp, break_at_value)

End Sub

Public Function set_col_name(ByVal lp As Long, ByVal column As Long, ByVal new_name As String) As Boolean

    set_col_name = (lpsolve_set_col_name(lp, column, new_name) <> 0)

End Function

Public Function set_column(ByVal lp As Long, ByVal col_no As Long, ByRef column As Double) As Boolean

    set_column = (lpsolve_set_column(lp, col_no, column) <> 0)

End Function

Public Function set_columnex(ByVal lp As Long, ByVal col_no As Long, ByVal count As Long, ByRef column As Double, ByRef rowno As Long) As Boolean

    set_columnex = (lpsolve_set_columnex(lp, col_no, count, column, rowno) <> 0)

End Function

Public Function set_constr_type(ByVal lp As Long, ByVal row As Long, ByVal con_type As lpsolve_constr_types) As Boolean

    set_constr_type = (lpsolve_set_constr_type(lp, row, con_type) <> 0)

End Function

Public Sub set_debug(ByVal lp As Long, ByVal debug_ As Boolean)

    Call lpsolve_set_debug(lp, debug_)

End Sub

Public Sub set_epsb(ByVal lp As Long, ByVal epsb As Double)

    Call lpsolve_set_epsb(lp, epsb)

End Sub

Public Sub set_epsd(ByVal lp As Long, ByVal epsd As Double)

    Call lpsolve_set_epsd(lp, epsd)

End Sub

Public Sub set_epsel(ByVal lp As Long, ByVal epsel As Double)

    Call lpsolve_set_epsel(lp, epsel)

End Sub

Public Sub set_epsint(ByVal lp As Long, ByVal epsint As Double)

    Call lpsolve_set_epsint(lp, epsint)

End Sub

Public Sub set_epslevel(ByVal lp As Long, ByVal epslevel As Long)

    Call lpsolve_set_epslevel(lp, epslevel)

End Sub

Public Sub set_epsperturb(ByVal lp As Long, ByVal epsperturb As Double)

    Call lpsolve_set_epsperturb(lp, epsperturb)

End Sub

Public Sub set_epspivot(ByVal lp As Long, ByVal epspivot As Double)

    Call lpsolve_set_epspivot(lp, epspivot)

End Sub

Public Sub set_improve(ByVal lp As Long, ByVal improve As lpsolve_improves)

    Call lpsolve_set_improve(lp, improve)

End Sub

Public Sub set_infinite(ByVal lp As Long, ByVal infinite As Double)

    Call lpsolve_set_infinite(lp, infinite)

End Sub

Public Function set_int(ByVal lp As Long, ByVal column As Long, ByVal must_be_int As Boolean) As Boolean

    set_int = (lpsolve_set_int(lp, column, must_be_int) <> 0)

End Function

Public Sub set_lag_trace(ByVal lp As Long, ByVal lag_trace As Boolean)

    Call lpsolve_set_lag_trace(lp, lag_trace)

End Sub

Public Function set_lowbo(ByVal lp As Long, ByVal column As Long, ByVal value As Double) As Boolean

    set_lowbo = (lpsolve_set_lowbo(lp, column, value) <> 0)

End Function

Public Function set_lp_name(ByVal lp As Long, ByVal lpname As String) As Boolean

    set_lp_name = (lpsolve_set_lp_name(lp, lpname) <> 0)

End Function

Public Function set_mat(ByVal lp As Long, ByVal row As Long, ByVal column As Long, ByVal value As Double) As Boolean

    set_mat = (lpsolve_set_mat(lp, row, column, value) <> 0)

End Function

Public Sub set_maxim(ByVal lp As Long)

    Call lpsolve_set_maxim(lp)

End Sub

Public Sub set_maxpivot(ByVal lp As Long, ByVal max_num_inv As Long)

    Call lpsolve_set_maxpivot(lp, max_num_inv)

End Sub

Public Sub set_minim(ByVal lp As Long)

    Call lpsolve_set_minim(lp)

End Sub

Public Sub set_mip_gap(ByVal lp As Long, ByVal absolute As Boolean, ByVal mip_gap As Double)

    Call lpsolve_set_mip_gap(lp, absolute, mip_gap)

End Sub

Public Sub set_negrange(ByVal lp As Long, ByVal negrange As Double)

    Call lpsolve_set_negrange(lp, negrange)

End Sub

Public Function set_obj(ByVal lp As Long, ByVal column As Long, ByVal value As Double) As Boolean

    set_obj = (lpsolve_set_obj(lp, column, value) <> 0)

End Function

Public Sub set_obj_bound(ByVal lp As Long, ByVal obj_bound As Double)

    Call lpsolve_set_obj_bound(lp, obj_bound)

End Sub

Public Function set_obj_fn(ByVal lp As Long, ByRef row As Double) As Boolean

    set_obj_fn = (lpsolve_set_obj_fn(lp, row) <> 0)

End Function

Public Function set_obj_fnex(ByVal lp As Long, ByVal count As Long, ByRef row As Double, ByRef colno As Long) As Boolean

    set_obj_fnex = (lpsolve_set_obj_fnex(lp, count, row, colno) <> 0)

End Function

Public Function set_outputfile(ByVal lp As Long, ByVal filename As String) As Boolean

    set_outputfile = (lpsolve_set_outputfile(lp, filename) <> 0)

End Function

Public Sub set_pivoting(ByVal lp As Long, ByVal piv_rule As lpsolve_piv_rules)

    Call lpsolve_set_pivoting(lp, piv_rule)

End Sub

Public Sub set_preferdual(ByVal lp As Long, ByVal dodual As Boolean)

    Call lpsolve_set_preferdual(lp, dodual)

End Sub

Public Sub set_presolve(ByVal lp As Long, ByVal do_presolve As lpsolve_presolve, ByVal maxloops As Long)

    Call lpsolve_set_presolve(lp, do_presolve, maxloops)

End Sub

Public Sub set_print_sol(ByVal lp As Long, ByVal print_sol As Long)

    Call lpsolve_set_print_sol(lp, print_sol)

End Sub

Public Function set_PseudoCosts(ByVal lp As Long, ByRef clower As Double, ByRef cupper As Double, ByRef updatelimit As Long) As Boolean

    set_PseudoCosts = (lpsolve_set_PseudoCosts(lp, clower, cupper, updatelimit) <> 0)

End Function

Public Function set_rh(ByVal lp As Long, ByVal row As Long, ByVal value As Double) As Boolean

    set_rh = (lpsolve_set_rh(lp, row, value) <> 0)

End Function

Public Function set_rh_range(ByVal lp As Long, ByVal row As Long, ByVal deltavalue As Double) As Boolean

    set_rh_range = (lpsolve_set_rh_range(lp, row, deltavalue) <> 0)

End Function

Public Sub set_rh_vec(ByVal lp As Long, ByRef rh As Double)

    Call lpsolve_set_rh_vec(lp, rh)

End Sub

Public Function set_row(ByVal lp As Long, ByVal row_no As Long, ByRef row As Double) As Boolean

    set_row = (lpsolve_set_row(lp, row_no, row) <> 0)

End Function

Public Function set_row_name(ByVal lp As Long, ByVal row As Long, ByVal new_name As String) As Boolean

    set_row_name = (lpsolve_set_row_name(lp, row, new_name) <> 0)

End Function

Public Function set_rowex(ByVal lp As Long, ByVal row_no As Long, ByVal count As Long, ByRef row As Double, ByRef colno As Long) As Boolean

    set_rowex = (lpsolve_set_rowex(lp, row_no, count, row, colno) <> 0)

End Function

Public Sub set_scalelimit(ByVal lp As Long, ByVal scalelimit As Double)

    Call lpsolve_set_scalelimit(lp, scalelimit)

End Sub

Public Sub set_scaling(ByVal lp As Long, ByVal scalemode As lpsolve_scales)

    Call lpsolve_set_scaling(lp, scalemode)

End Sub

Public Function set_semicont(ByVal lp As Long, ByVal column As Long, ByVal must_be_sc As Boolean) As Boolean

    set_semicont = (lpsolve_set_semicont(lp, column, must_be_sc) <> 0)

End Function

Public Sub set_sense(ByVal lp As Long, ByVal maximize As Boolean)

    Call lpsolve_set_sense(lp, maximize)

End Sub

Public Sub set_simplextype(ByVal lp As Long, ByVal simplextype As lpsolve_simplextypes)

    Call lpsolve_set_simplextype(lp, simplextype)

End Sub

Public Sub set_solutionlimit(ByVal lp As Long, ByVal limit As Long)

    Call lpsolve_set_solutionlimit(lp, limit)

End Sub

Public Sub set_timeout(ByVal lp As Long, ByVal sectimeout As Long)

    Call lpsolve_set_timeout(lp, sectimeout)

End Sub

Public Sub set_trace(ByVal lp As Long, ByVal trace As Boolean)

    Call lpsolve_set_trace(lp, trace)

End Sub

Public Function set_unbounded(ByVal lp As Long, ByVal column As Long) As Boolean

    set_unbounded = (lpsolve_set_unbounded(lp, column) <> 0)

End Function

Public Function set_upbo(ByVal lp As Long, ByVal column As Long, ByVal value As Double) As Boolean

    set_upbo = (lpsolve_set_upbo(lp, column, value) <> 0)

End Function

Public Sub set_use_names(ByVal lp As Long, ByVal isrow As Boolean, use_names As Boolean)

    Call lpsolve_set_use_names(lp, isrow, use_names)

End Sub

Public Function set_var_branch(ByVal lp As Long, ByVal column As Long, ByVal branch_mode As lpsolve_branch) As Boolean

    set_var_branch = (lpsolve_set_var_branch(lp, column, branch_mode) <> 0)

End Function

Public Function set_var_weights(ByVal lp As Long, ByRef weights As Double) As Boolean

    set_var_weights = (lpsolve_set_var_weights(lp, weights) <> 0)

End Function

Public Sub set_verbose(ByVal lp As Long, ByVal verbose As Long)

    Call lpsolve_set_verbose(lp, verbose)

End Sub

Public Function set_XLI(ByVal lp As Long, ByVal filename As String) As Boolean

    set_XLI = (lpsolve_set_XLI(lp, filename) <> 0)

End Function

Public Function solve(ByVal lp As Long) As lpsolve_return

    solve = lpsolve_solve(lp)

End Function

Public Function str_add_column(ByVal lp As Long, ByVal col_string As String) As Boolean

    str_add_column = (lpsolve_str_add_column(lp, col_string) <> 0)

End Function

Public Function str_add_constraint(ByVal lp As Long, ByVal row_string As String, ByVal constr_type As lpsolve_constr_types, ByVal rh As Double) As Boolean

    str_add_constraint = (lpsolve_str_add_constraint(lp, row_string, constr_type, rh) <> 0)

End Function

Public Function str_add_lag_con(ByVal lp As Long, ByVal row_string As String, ByVal con_type As lpsolve_constr_types, ByVal rhs As Double) As Boolean

    str_add_lag_con = (lpsolve_str_add_lag_con(lp, row_string, con_type, rhs) <> 0)

End Function

Public Function str_set_obj_fn(ByVal lp As Long, ByVal row_string As String) As Boolean

    str_set_obj_fn = (lpsolve_str_set_obj_fn(lp, row_string) <> 0)

End Function

Public Function str_set_rh_vec(ByVal lp As Long, ByVal rh_string As String) As Boolean

    str_set_rh_vec = (lpsolve_str_set_rh_vec(lp, rh_string) <> 0)

End Function

Public Function time_elapsed(ByVal lp As Long) As Double

    time_elapsed = lpsolve_time_elapsed(lp)

End Function

Public Sub unscale(ByVal lp As Long)

    Call lpsolve_unscale(lp)

End Sub

Public Function write_basis(ByVal lp As Long, ByVal filename As String) As Boolean

    write_basis = (lpsolve_write_basis(lp, filename) <> 0)

End Function

Public Function write_freemps(ByVal lp As Long, ByVal filename As String) As Boolean

    write_freemps = (lpsolve_write_freemps(lp, filename) <> 0)

End Function

Public Function write_lp(ByVal lp As Long, ByVal filename As String) As Boolean

    write_lp = (lpsolve_write_lp(lp, filename) <> 0)

End Function

Public Function write_mps(ByVal lp As Long, ByVal filename As String) As Boolean

    write_mps = (lpsolve_write_mps(lp, filename) <> 0)

End Function

Public Function write_XLI(ByVal lp As Long, ByVal filename As String, ByVal options As String, ByVal results As Boolean) As Boolean

    write_XLI = (lpsolve_write_XLI(lp, filename, options, results) <> 0)

End Function

Public Function write_params(ByVal lp As Long, ByVal filename As String, ByVal options As String) As Boolean

    write_params = (lpsolve_write_params(lp, filename, options) <> 0)

End Function

'-----------------------------------------------------------------------------------------------------------------------------

Private Sub Class_Initialize()

    Init

End Sub
