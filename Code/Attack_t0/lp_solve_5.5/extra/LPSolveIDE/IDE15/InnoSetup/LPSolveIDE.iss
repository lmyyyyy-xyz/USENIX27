; -- LPSolveIDE.iss --

[Setup]
AppVerName=LPSolve IDE 5.5.2.14
AppVersion=5.5.2.14
VersionInfoVersion=5.5.2.14
AppPublisherURL=https://github.com/lp-solve/lp_solve
OutputBaseFilename=LPSolveIDESetup55

AppCopyright=Copyright (C) 1991, 2025 Free Software Foundation, Inc.

AppName=LPSolve IDE
AppPublisher=Free Software Foundation, Inc.
DefaultDirName={pf}\LPSolve IDE
DefaultGroupName=LPSolve IDE
UninstallDisplayIcon={app}\LpSolveIDE.exe
Compression=lzma
SolidCompression=yes
OutputDir=.
LicenseFile=LGPL.txt
ChangesAssociations=yes

[Files]
Source: "..\bin\xerces-c_2_3_0.dll"; DestDir: "{sys}"; Flags: sharedfile
Source: "..\bin\Xalan-C_1_6_0.dll"; DestDir: "{sys}"; Flags: sharedfile
Source: "..\bin\zlib1.dll"; DestDir: "{sys}"; Flags: sharedfile

Source: "..\bin\LpSolveIDE.exe"; DestDir: "{app}"
Source: "..\bin\LpSolveIDE.ini"; DestDir: "{app}"
Source: "..\bin\default.lpo"; DestDir: "{app}"
Source: "_tmpfile"; DestDir: "{app}"
Source: "..\bin\lp_solve55.chm"; DestDir: "{app}"
Source: "..\bin\lpsolve55.dll"; DestDir: "{app}"
Source: "..\bin\xli_CPLEX.dll"; DestDir: "{app}"
Source: "..\bin\xli_DIMACS.dll"; DestDir: "{app}"
Source: "..\bin\xli_LINDO.dll"; DestDir: "{app}"
Source: "..\bin\xli_MPS.dll"; DestDir: "{app}"
Source: "..\bin\xli_LPFML.dll"; DestDir: "{app}"
Source: "..\bin\xli_MathProg.dll"; DestDir: "{app}"
Source: "..\bin\xli_XPRESS.dll"; DestDir: "{app}"
Source: "..\bin\xli_ZIMPL.dll"; DestDir: "{app}"
Source: "..\bin\bfp_etaPFI.dll"; DestDir: "{app}"
Source: "..\bin\bfp_LUSOL.dll"; DestDir: "{app}"
Source: "..\bin\bfp_GLPK.dll"; DestDir: "{app}"

Source: "..\bin\Testdir\*"; DestDir: "{app}\Testdir"

[Registry]
Root: HKCR; Subkey: ".lp"; ValueType: string; ValueName: ""; ValueData: "LPFile"; Flags: uninsdeletevalue; Tasks: LPFile
Root: HKCR; Subkey: "LPFile"; ValueType: string; ValueName: ""; ValueData: "LP File"; Flags: uninsdeletekey; Tasks: LPFile
Root: HKCR; Subkey: "LPFile\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\LpSolveIDE.exe,0"; Tasks: LPFile
Root: HKCR; Subkey: "LPFile\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\LpSolveIDE.exe"" ""%1"""; Tasks: LPFile

Root: HKCR; Subkey: ".mps"; ValueType: string; ValueName: ""; ValueData: "MPSFile"; Flags: uninsdeletevalue; Tasks: MPSFile
Root: HKCR; Subkey: "MPSFile"; ValueType: string; ValueName: ""; ValueData: "MPS File"; Flags: uninsdeletekey; Tasks: MPSFile
Root: HKCR; Subkey: "MPSFile\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\LpSolveIDE.exe,0"; Tasks: MPSFile
Root: HKCR; Subkey: "MPSFile\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\LpSolveIDE.exe"" ""%1"""; Tasks: MPSFile

Root: HKCR; Subkey: ".mod"; ValueType: string; ValueName: ""; ValueData: "MathProgFile"; Flags: uninsdeletevalue; Tasks: MathProgFile
Root: HKCR; Subkey: "MathProgFile"; ValueType: string; ValueName: ""; ValueData: "MathProg File"; Flags: uninsdeletekey; Tasks: MathProgFile
Root: HKCR; Subkey: "MathProgFile\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\LpSolveIDE.exe,0"; Tasks: MathProgFile
Root: HKCR; Subkey: "MathProgFile\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\LpSolveIDE.exe"" ""%1"""; Tasks: MathProgFile

Root: HKCR; Subkey: ".zpl"; ValueType: string; ValueName: ""; ValueData: "ZIMPLFile"; Flags: uninsdeletevalue; Tasks: ZIMPLFile
Root: HKCR; Subkey: "ZIMPLFile"; ValueType: string; ValueName: ""; ValueData: "ZIMPL File"; Flags: uninsdeletekey; Tasks: ZIMPLFile
Root: HKCR; Subkey: "ZIMPLFile\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\LpSolveIDE.exe,0"; Tasks: ZIMPLFile
Root: HKCR; Subkey: "ZIMPLFile\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\LpSolveIDE.exe"" ""%1"""; Tasks: ZIMPLFile

Root: HKCR; Subkey: ".lpt"; ValueType: string; ValueName: ""; ValueData: "CPLEXFile"; Flags: uninsdeletevalue; Tasks: CPLEXFile
Root: HKCR; Subkey: "CPLEXFile"; ValueType: string; ValueName: ""; ValueData: "CPLEX File"; Flags: uninsdeletekey; Tasks: CPLEXFile
Root: HKCR; Subkey: "CPLEXFile\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\LpSolveIDE.exe,0"; Tasks: CPLEXFile
Root: HKCR; Subkey: "CPLEXFile\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\LpSolveIDE.exe"" ""%1"""; Tasks: CPLEXFile

Root: HKCR; Subkey: ".ltx"; ValueType: string; ValueName: ""; ValueData: "LINDOFile"; Flags: uninsdeletevalue; Tasks: LINDOFile
Root: HKCR; Subkey: "LINDOFile"; ValueType: string; ValueName: ""; ValueData: "LINDO File"; Flags: uninsdeletekey; Tasks: LINDOFile
Root: HKCR; Subkey: "LINDOFile\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\LpSolveIDE.exe,0"; Tasks: LINDOFile
Root: HKCR; Subkey: "LINDOFile\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\LpSolveIDE.exe"" ""%1"""; Tasks: LINDOFile

Root: HKCR; Subkey: ".lpx"; ValueType: string; ValueName: ""; ValueData: "XpressFile"; Flags: uninsdeletevalue; Tasks: XpressFile
Root: HKCR; Subkey: "XpressFile"; ValueType: string; ValueName: ""; ValueData: "Xpress File"; Flags: uninsdeletekey; Tasks: XpressFile
Root: HKCR; Subkey: "XpressFile\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\LpSolveIDE.exe,0"; Tasks: XpressFile
Root: HKCR; Subkey: "XpressFile\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\LpSolveIDE.exe"" ""%1"""; Tasks: XpressFile

Root: HKCR; Subkey: ".net"; ValueType: string; ValueName: ""; ValueData: "DIMACSFile"; Flags: uninsdeletevalue; Tasks: DIMACSFile
Root: HKCR; Subkey: "DIMACSFile"; ValueType: string; ValueName: ""; ValueData: "DIMACS File"; Flags: uninsdeletekey; Tasks: DIMACSFile
Root: HKCR; Subkey: "DIMACSFile\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\LpSolveIDE.exe,0"; Tasks: DIMACSFile
Root: HKCR; Subkey: "DIMACSFile\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\LpSolveIDE.exe"" ""%1"""; Tasks: DIMACSFile

[Tasks]
GroupDescription: "Additional icons:"; Name: desktopicon; Description: "Create a &desktop icon"
GroupDescription: "Additional icons:"; Name: quicklaunchicon; Description: "Create a &Quick Launch icon"

GroupDescription: "File associations:"; Name: LPFile;       Description: "lp_solve   (.lp)"
GroupDescription: "File associations:"; Name: MPSFile;      Description: "MPS         (.mps)"
GroupDescription: "File associations:"; Name: MathProgFile; Description: "MathProg (.mod)"
GroupDescription: "File associations:"; Name: ZIMPLFile;    Description: "ZIMPL      (.zpl)"
GroupDescription: "File associations:"; Name: CPLEXFile;    Description: "CPLEX     (.lpt)"
GroupDescription: "File associations:"; Name: LINDOFile;    Description: "LINDO     (.ltx)"
GroupDescription: "File associations:"; Name: XpressFile;   Description: "Xpress    (.lpx)"
GroupDescription: "File associations:"; Name: DIMACSFile;   Description: "DIMACS   (.net)"

[Icons]
Name: "{group}\LPSolve IDE"; Filename: "{app}\LpSolveIDE.exe"
Name: "{commondesktop}\LPSolve IDE"; Filename: "{app}\LpSolveIDE.exe"; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\LpSolve IDE"; Filename: "{app}\LpSolveIDE.exe"; Tasks: quicklaunchicon

[Run]
Filename: "{app}\LpSolveIDE.exe"; Description: "Launch LPSolve IDE"; WorkingDir: "{app}"; Flags: postinstall nowait

