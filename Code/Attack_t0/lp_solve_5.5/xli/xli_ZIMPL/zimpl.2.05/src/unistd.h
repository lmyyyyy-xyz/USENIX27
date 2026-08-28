
#if !defined INLINE

#if defined __cplusplus
  #define INLINE inline
#elif defined _WIN32 || defined WIN32
  #define INLINE _inline
#else
  #define INLINE
#endif

#endif


#if defined _WIN32 || defined WIN32

#ifndef R_OK
  #define R_OK   0
#endif
#ifndef fsync
  #define fsync  _commit
#endif
#ifndef finite
  #define finite _finite
#endif


#include <io.h>

/* These are other Windows libraries with functionality from unistd.h */
#if 0
#include <sys/timeb.h>
#include <sys/types.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <process.h>
#include <winsock.h>
#include <float.h>
#endif

#endif
