#if defined WIN32 || defined _WINDOWS || defined WINDOWS
#include <windows.h>
#include <sqltypes.h>
#endif

#if defined WIN32 || defined _WINDOWS || defined WINDOWS

#if !defined SQLLEN
#define SQLLEN  SQLINTEGER
#endif

#if !defined SQLULEN
#define SQLULEN SQLUINTEGER
#endif

#endif

#include <glpsql.c>
