VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "lpsolve55ASP"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

Private lpsolve As lpsolve55

Private Sub Class_Initialize()

    Set lpsolve = New lpsolve55

End Sub

Private Sub Class_Terminate()

    Set lpsolve = Nothing

End Sub

Public Function Init(Optional ByVal dllPath As String = "") As Boolean

    Init = lpsolve.Init(dllPath)

End Function

Public Function add_column(ByVal lp As Long, ByRef column As Variant) As Boolean

End Function
