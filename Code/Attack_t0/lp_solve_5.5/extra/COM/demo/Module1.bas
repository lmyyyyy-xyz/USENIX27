Attribute VB_Name = "Module1"
Option Explicit

Private lpsolve As lpsolve55COM.lpsolve55

' This demo program expects that the lpsolve dll is in the same directory as the project or in a directory of the path.
' Note that the lpsolve dll is not a COM object, so don't try to reference it, that will not work.

' The VB interface to version 5 is different than from version 4. This to make it more 'object oriented'
' The definition is no longer in a bas module, but in a class that must be instantiated.
' That way, the lpsolve_ prefix from every routine can be removed and is it the same as in the docs

Sub Main()

    Set lpsolve = New lpsolve55

    Debug.Print CurDir$
    lpsolve.Init "."

    Test

    Set lpsolve = Nothing

End Sub

Private Sub logfunc(ByVal lp As Long, ByVal userhandle As Long, ByVal pBuf As Long)
    Dim Buf As String

    Buf = lpsolve.Ptr2Str(pBuf)

    Debug.Print Buf;

End Sub

Private Function ctrlcfunc(ByVal lp As Long, ByVal userhandle As Long) As Long

    'If set to True, then solve is aborted and returncode will indicate this.
    'ctrlcfunc = True

End Function

Private Sub msgfunc(ByVal lp As Long, ByVal userhandle As Long, ByVal message As lpsolve_msgmask)

    'Debug.Print message

End Sub

Private Sub Test()
    Dim lp As Long
    Dim Major As Long, Minor As Long, release As Long, build As Long
    Dim row() As Double
    Dim lower() As Double
    Dim upper() As Double
    Dim Col() As Double
    Dim Arry() As Double

    With lpsolve
        lp = .make_lp(0, 4)

        .version Major, Minor, release, build

        'let's first demonstrate the logfunc callback feature
        'completely optional of course
        .put_logfunc lp, AddressOf logfunc, 0
        .print_str lp, "lp_solve " & Major & "." & Minor & "." & release & "." & build & " demo" & vbLf & vbLf
        .solve lp 'just to see that a message is send via the logfunc routine ...
        'ok, that is enough, no more callback
        .put_logfunc lp, 0, 0

        'Now redirect all output to a file
        .set_outputfile lp, App.Path & "\result.txt"

        'set an abort function. Again optional
        .put_abortfunc lp, AddressOf ctrlcfunc, 0

        'set a message function. Again optional
        .put_msgfunc lp, AddressOf msgfunc, 0, MSG_PRESOLVE + MSG_LPFEASIBLE + MSG_LPOPTIMAL + MSG_MILPEQUAL + MSG_MILPFEASIBLE + MSG_MILPBETTER

        .print_str lp, "lp_solve " & Major & "." & Minor & "." & release & "." & build & " demo" & vbLf & vbLf
        .print_str lp, "This demo will show most of the features of lp_solve " & Major & "." & Minor & "." & release & "." & build & vbLf

        .print_str lp, vbLf & "We start by creating a new problem with 4 variables and 0 constraints" & vbLf
        .print_str lp, "We use: lp = make_lp(0, 4)" & vbLf

        .set_timeout lp, 0

        .print_str lp, "We can show the current problem with print_lp lp" & vbLf
        .print_lp lp

        .print_str lp, "Now we add some constraints" & vbLf
        .print_str lp, "add_constraint lp, Array(3, 2, 2, 1), LE, 4" & vbLf
        FillArray row, Array(3, 2, 2, 1)
        .add_constraint lp, row(0), LE, 4
        .print_lp lp

        .print_str lp, "add_constraint lp, Array(0, 4, 3, 1), GE, 3" & vbLf
        FillArray row, Array(0, 4, 3, 1)
        .add_constraint lp, row(0), GE, 3
        .print_lp lp

        .print_str lp, "Set the objective function" & vbLf
        .print_str lp, "set_obj_fn lp, Array(2, 3, -2, 3)" & vbLf
        FillArray row, Array(2, 3, -2, 3)
        .set_obj_fn lp, row(0)
        .print_lp lp

        .print_str lp, "Now solve the problem with print_str lp, solve(lp)" & vbLf
        .print_str lp, .solve(lp) & ": " & .get_objective(lp) & vbLf

        ReDim Col(1 To .get_Ncolumns(lp))
        .get_variables lp, Col(1)

        ReDim row(1 To .get_Nrows(lp))
        .get_constraints lp, row(1)

        ReDim Arry(0 To .get_Ncolumns(lp) + .get_Nrows(lp))
        .get_dual_solution lp, Arry(0)

        ReDim Arry(1 To .get_Ncolumns(lp) + .get_Nrows(lp)), lower(1 To .get_Ncolumns(lp) + .get_Nrows(lp)), upper(1 To .get_Ncolumns(lp) + .get_Nrows(lp))
        .get_sensitivity_rhs lp, Arry(1), lower(1), upper(1)

        ReDim lower(0 To .get_Ncolumns(lp)), upper(0 To .get_Ncolumns(lp))
        .get_sensitivity_obj lp, lower(0), upper(0)

        .print_str lp, "The value is 0, this means we found an optimal solution" & vbLf
        .print_str lp, "We can display this solution with print_objective lp and print_solution lp" & vbLf
        .print_objective lp
        .print_solution lp, 1
        .print_constraints lp, 1

        .print_str lp, "The dual variables of the solution are printed with" & vbLf
        .print_str lp, "print_duals lp" & vbLf
        .print_duals lp

        .print_str lp, "We can change a single element in the matrix with" & vbLf
        .print_str lp, "set_mat lp, 2, 1, 0.5" & vbLf
        .set_mat lp, 2, 1, 0.5
        .print_lp lp

        .print_str lp, "If we want to maximize the objective function use set_maxim lp" & vbLf
        .set_maxim lp
        .print_lp lp

        .print_str lp, "after solving this gives us:" & vbLf
        .solve lp
        .print_objective lp
        .print_solution lp, 1
        .print_constraints lp, 1
        .print_duals lp

        .print_str lp, "Change the value of a rhs element with set_rh lp, 1, 7.45" & vbLf
        .set_rh lp, 1, 7.45
        .print_lp lp
        .solve lp
        .print_objective lp
        .print_solution lp, 1
        .print_constraints lp, 1

        .print_str lp, "We change C4 to the integer type with" & vbLf
        .print_str lp, "set_int lp, 4, True" & vbLf
        .set_int lp, 4, True
        .print_lp lp

        .print_str lp, "We set branch & bound debugging on with set_debug lp, 1" & vbLf

        .set_debug lp, 1
        .print_str lp, "and solve..." & vbLf

        .solve lp
        .print_objective lp
        .print_solution lp, 1
        .print_constraints lp, 1

        .print_str lp, "We can set bounds on the variables with" & vbLf
        .print_str lp, "set_lowbo lp, 2, 2 & set_upbo lp, 4, 5.3" & vbLf
        .set_lowbo lp, 2, 2
        .set_upbo lp, 4, 5.3
        .print_lp lp

        .solve lp
        .print_objective lp
        .print_solution lp, 1
        .print_constraints lp, 1

        .print_str lp, "Now remove a constraint with del_constraint lp, 1" & vbLf
        .del_constraint lp, 1
        .print_lp lp
        .print_str lp, "Add an equality constraint" & vbLf
        FillArray row, Array(1, 2, 1, 4)
        .add_constraint lp, row(0), EQ, 8
        .print_lp lp

        .print_str lp, "A column can be added with:" & vbLf
        .print_str lp, "add_column lp, Array(3, 2, 2)" & vbLf
        FillArray Col, Array(3, 2, 2)
        .add_column lp, Col(1)
        .print_lp lp

        .print_str lp, "A column can be removed with:" & vbLf
        .print_str lp, "del_column lp, 3" & vbLf
        .del_column lp, 3
        .print_lp lp

        .print_str lp, "We can use automatic scaling with:" & vbLf
        .print_str lp, "set_scaling lp, SCALE_MEAN" & vbLf
        .set_scaling lp, SCALE_MEAN
        .print_lp lp

        .print_str lp, "The function get_mat(lp, row, column) returns a single" & vbLf
        .print_str lp, "matrix element" & vbLf
        .print_str lp, "get_mat(lp, 2, 3), get_mat(lp, 1, 1) gives " & .get_mat(lp, 2, 3) & ", " & .get_mat(lp, 1, 1) & vbLf
        .print_str lp, "Notice that get_mat returns the value of the original unscaled problem" & vbLf

        .print_str lp, "If there are any integer type variables, then only the rows are scaled" & vbLf
        .print_str lp, "set_int lp, 3, False" & vbLf
        .set_int lp, 3, False
        .print_lp lp

        .solve lp
        .print_str lp, "print_objective, print_solution gives the solution to the original problem" & vbLf
        .print_objective lp
        .print_solution lp, 1
        .print_constraints lp, 1

        .print_str lp, "Scaling is turned off with unscale lp" & vbLf
        .unscale lp
        .print_lp lp

        .print_str lp, "Now turn B&B debugging off and simplex tracing on with" & vbLf
        .print_str lp, "set_debug lp, False, set_trace lp, True and solve lp" & vbLf
        .set_debug lp, False
        .set_trace lp, True

        .solve lp
        .print_str lp, "Where possible, lp_solve will start at the last found basis" & vbLf
        .print_str lp, "We can reset the problem to the initial basis with" & vbLf
        .print_str lp, "default_basis lp. Now solve it again..." & vbLf

        .default_basis lp
        .solve lp

        .print_str lp, "It is possible to give variables and constraints names" & vbLf
        .print_str lp, "set_row_name lp, 1, ""speed"" & set_col_name lp, 2, ""money""" & vbLf
        .set_row_name lp, 1, "speed"
        .set_col_name lp, 2, "money"
        .print_lp lp
        .print_str lp, "As you can see, all column and rows are assigned default names" & vbLf
        .print_str lp, "If a column or constraint is deleted, the names shift place also:" & vbLf

        .print_str lp, "del_column lp, 1" & vbLf
        .del_column lp, 1
        .print_lp lp

        .write_lp lp, App.Path & "\lp.lp"
        .write_mps lp, App.Path & "\lp.mps"

        .set_outputfile lp, vbNullString

        .delete_lp lp

        lp = .read_LP(App.Path & "\lp.lp", False, "test")
        If lp = 0 Then
            MsgBox "Can't find lp.lp, stopping"
            Exit Sub
        End If

        .set_outputfile lp, App.Path & "\result2.txt"

        .print_str lp, "An lp structure can be created and read from a .lp file" & vbLf
        .print_str lp, "lp = .read_LP(""demo_lag.lp"", False, ""test"")" & vbLf
        .print_str lp, "The verbose option is disabled" & vbLf

        .print_str lp, "lp is now:" & vbLf
        .print_lp lp

        .print_str lp, "solution:" & vbLf
        .set_debug lp, 1
        .solve lp
        .set_debug lp, 0
        .print_objective lp
        .print_solution lp, 1
        .print_constraints lp, 1

        .write_lp lp, App.Path & "\lp.lp"
        .write_mps lp, App.Path & "\lp.mps"

        .set_outputfile lp, vbNullString

        .delete_lp lp
    End With

End Sub

Private Sub FillArray(Arry() As Double, v As Variant)
    Dim i As Integer
    Dim j As Integer

    ReDim Arry(0 To UBound(v) - LBound(v) + 1)
    j = 0
    For i = LBound(v) To UBound(v)
        j = j + 1
        Arry(j) = v(i)
    Next

End Sub
