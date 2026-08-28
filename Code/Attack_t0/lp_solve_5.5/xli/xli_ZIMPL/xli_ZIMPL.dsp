# Microsoft Developer Studio Project File - Name="xli_ZIMPL DLL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=xli_ZIMPL DLL - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE
!MESSAGE NMAKE /f "xli_ZIMPL DLL.mak".
!MESSAGE
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE
!MESSAGE NMAKE /f "xli_ZIMPL DLL.mak" CFG="xli_ZIMPL DLL - Win32 Debug"
!MESSAGE
!MESSAGE Possible choices for configuration are:
!MESSAGE
!MESSAGE "xli_ZIMPL DLL - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "xli_ZIMPL DLL - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "xli_ZIMPL DLL - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /I ".\" /I "..\" /I "..\..\" /I "..\..\shared" /I ".\zimpl\src" /I "d:\zlib-1.2.1" /I "d:\gmp-4.1.4" /I "zimpl.2.05\src" /ZI /W3 /Od /D "WIN32;_DEBUG;_WINDOWS;_USRDLL;RoleIsExternalLanguageEngine;LANGUAGE_ACTIVE=LANGUAGE_ZIMPL;inline=_inline;ZLIB_DLL;ZEXPORT=__cdecl" /D "_CRT_SECURE_NO_DEPRECATE" /D "_CRT_NONSTDC_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_MBCS" /Gm /Zp8  /Gz /TC /GZ /c /GX
# ADD CPP /nologo /MTd /I ".\" /I "..\" /I "..\..\" /I "..\..\shared" /I ".\zimpl\src" /I "d:\zlib-1.2.1" /I "d:\gmp-4.1.4" /I "zimpl.2.05\src" /ZI /W3 /Od /D "WIN32;_DEBUG;_WINDOWS;_USRDLL;RoleIsExternalLanguageEngine;LANGUAGE_ACTIVE=LANGUAGE_ZIMPL;inline=_inline;ZLIB_DLL;ZEXPORT=__cdecl" /D "_CRT_SECURE_NO_DEPRECATE" /D "_CRT_NONSTDC_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_MBCS" /Gm /Zp8  /Gz /TC /GZ /c /GX
# ADD BASE MTL /nologo /win32
# ADD MTL /nologo /win32
# ADD BASE RSC /l 1033
# ADD RSC /l 1033
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib gmpDebug.lib zdll.lib /nologo /dll /out:"Debug\xli_ZIMPL.dll" /incremental:yes /libpath:"d:\zlib-1.2.1\lib.old" /libpath:"D:\zlib\lib" /libpath:"d:\gmp-4.1.4\Debug" /def:"..\lp_XLI.def" /debug /pdb:"Debug\xli_ZIMPL.pdb" /pdbtype:sept /subsystem:windows /implib:"$(OutDir)/xli_ZIMPL.lib" /machine:ix86
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib gmpDebug.lib zdll.lib /nologo /dll /out:"Debug\xli_ZIMPL.dll" /incremental:yes /libpath:"d:\zlib-1.2.1\lib.old" /libpath:"D:\zlib\lib" /libpath:"d:\gmp-4.1.4\Debug" /def:"..\lp_XLI.def" /debug /pdb:"Debug\xli_ZIMPL.pdb" /pdbtype:sept /subsystem:windows /implib:"$(OutDir)/xli_ZIMPL.lib" /machine:ix86

!ELSEIF  "$(CFG)" == "xli_ZIMPL DLL - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /I ".\" /I "..\" /I "..\..\" /I "..\..\shared" /I ".\zimpl\src" /I "d:\zlib-1.2.1" /I "d:\gmp-4.1.4" /I "zimpl.2.05\src" /W3 /Oi /Ot /Oy /D "WIN32;NDEBUG;_WINDOWS;_USRDLL;RoleIsExternalLanguageEngine;LANGUAGE_ACTIVE=LANGUAGE_ZIMPL;inline=_inline;ZLIB_DLL;ZEXPORT=__cdecl" /D "_CRT_SECURE_NO_DEPRECATE" /D "_CRT_NONSTDC_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_MBCS" /GF /Zp8 /Gy  /Gz /TC /c /GX
# ADD CPP /nologo /MT /I ".\" /I "..\" /I "..\..\" /I "..\..\shared" /I ".\zimpl\src" /I "d:\zlib-1.2.1" /I "d:\gmp-4.1.4" /I "zimpl.2.05\src" /W3 /Oi /Ot /Oy /D "WIN32;NDEBUG;_WINDOWS;_USRDLL;RoleIsExternalLanguageEngine;LANGUAGE_ACTIVE=LANGUAGE_ZIMPL;inline=_inline;ZLIB_DLL;ZEXPORT=__cdecl" /D "_CRT_SECURE_NO_DEPRECATE" /D "_CRT_NONSTDC_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_MBCS" /GF /Zp8 /Gy  /Gz /TC /c /GX
# ADD BASE MTL /nologo /win32
# ADD MTL /nologo /win32
# ADD BASE RSC /l 1033
# ADD RSC /l 1033
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib gmp.lib zdll.lib /nologo /dll /out:"Release\xli_ZIMPL.dll" /incremental:no /libpath:"d:\zlib-1.2.1\lib.old" /libpath:"D:\zlib\lib" /libpath:"d:\gmp-4.1.4\Release" /def:"..\lp_XLI.def" /debug /pdbtype:sept /subsystem:windows /opt:ref /opt:icf /implib:"$(OutDir)/xli_ZIMPL.lib" /machine:ix86
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib gmp.lib zdll.lib /nologo /dll /out:"Release\xli_ZIMPL.dll" /incremental:no /libpath:"d:\zlib-1.2.1\lib.old" /libpath:"D:\zlib\lib" /libpath:"d:\gmp-4.1.4\Release" /def:"..\lp_XLI.def" /debug /pdbtype:sept /subsystem:windows /opt:ref /opt:icf /implib:"$(OutDir)/xli_ZIMPL.lib" /machine:ix86

!ENDIF

# Begin Target

# Name "xli_ZIMPL DLL - Win32 Debug"
# Name "xli_ZIMPL DLL - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;def;odl;idl;hpj;bat;asm;asmx"
# Begin Source File

SOURCE=.\zimpl\src\_bound.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_code.c
# End Source File
# Begin Source File

SOURCE=..\..\shared\commonlib.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_conname.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_define.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_elem.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_entry.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_gmpmisc.c
# End Source File
# Begin Source File

SOURCE=.\gzip.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_hash.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_heap.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_idxset.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_inst.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_iread.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_list.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_load.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_local.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_metaio.c
# End Source File
# Begin Source File

SOURCE=..\lp_XLI.def
# End Source File
# Begin Source File

SOURCE=.\lp_ZIMPL.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_mmlparse.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_mmlscan.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_mshell.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_numbgmp.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_prog.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_rathumwrite.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_ratlpfwrite.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_ratlpstore.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_ratmpswrite.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_ratmstwrite.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_ratordwrite.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_ratpresolve.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_ratsoswrite.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_rdefpar.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_set4.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_setempty.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_setlist.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_setmulti.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_setprod.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_setpseudo.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_setrange.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_source.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_stmt.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_strstore.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_symbol.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_term.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_tuple.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_vinst.c
# End Source File
# Begin Source File

SOURCE=.\xli_ZIMPL.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_xlpglue.c
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\_zimpllib.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;inc;xsd"
# Begin Source File

SOURCE=.\zimpl\src\bool.h
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\code.h
# End Source File
# Begin Source File

SOURCE=..\..\shared\commonlib.h
# End Source File
# Begin Source File

SOURCE=d:\gmp-4.1.4\gmp.h
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\gmpmisc.h
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\inst.h
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\lint.h
# End Source File
# Begin Source File

SOURCE=..\..\lp_crash.h
# End Source File
# Begin Source File

SOURCE=..\..\lp_Hash.h
# End Source File
# Begin Source File

SOURCE=..\..\lp_lib.h
# End Source File
# Begin Source File

SOURCE=..\..\lp_lp.h
# End Source File
# Begin Source File

SOURCE=..\..\lp_matrix.h
# End Source File
# Begin Source File

SOURCE=..\..\lp_mipbb.h
# End Source File
# Begin Source File

SOURCE=..\..\lp_MPS.h
# End Source File
# Begin Source File

SOURCE=..\..\lp_presolve.h
# End Source File
# Begin Source File

SOURCE=..\..\lp_pricePSE.h
# End Source File
# Begin Source File

SOURCE=..\..\lp_report.h
# End Source File
# Begin Source File

SOURCE=..\..\lp_scale.h
# End Source File
# Begin Source File

SOURCE=..\..\lp_simplex.h
# End Source File
# Begin Source File

SOURCE=..\..\lp_solve.h
# End Source File
# Begin Source File

SOURCE=..\..\lp_SOS.h
# End Source File
# Begin Source File

SOURCE=..\..\lp_utils.h
# End Source File
# Begin Source File

SOURCE=.\lp_ZIMPL.h
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\mme.h
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\mmlparse.h
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\mshell.h
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\ratlp.h
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\ratlpstore.h
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\ratlptypes.h
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\set4.h
# End Source File
# Begin Source File

SOURCE=.\xli_ZIMPL.h
# End Source File
# Begin Source File

SOURCE=.\zimpl\src\xlpglue.h
# End Source File
# Begin Source File

SOURCE=d:\zlib-1.2.1\zlib.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "rc;ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe;resx"
# End Group
# End Target
# End Project

