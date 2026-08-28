#if defined WIN32 || defined _WINDOWS || defined WINDOWS
#  if !defined NOODBC
#    define ODBC_DLNAME "odbc32.dll"
#  endif
#  if !defined NOMYSQL
#    define MYSQL_DLNAME "libmysql.dll"
#  endif
#else
# if defined MACOSX
#  if !defined NOODBC
     /* #  define ODBC_DLNAME "libiodbc.dylib" */
#      define ODBC_DLNAME "libodbc.dylib"
#  endif
#  if !defined NOMYSQL
#    define MYSQL_DLNAME "libmysqlclient.dylib"
#  endif
# else
#  if !defined NOODBC
#    define ODBC_DLNAME "libodbc.so"
#  endif
#  if !defined NOMYSQL
#    define MYSQL_DLNAME "libmysqlclient.so"
#  endif
# endif
#endif
