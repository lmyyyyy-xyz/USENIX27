#if 0

#include <stdlib.h>
#include <stdio.h>

#include "zlib.h"

gzFile gzopen(const char *path, const char *mode)
{
    return(fopen(path, mode));
}

int gzclose(gzFile file)
{
    return(fclose(file));
}

char*  gzgets(gzFile file, char *buf, int len)
{
    return(fgets(buf, len, file));
}

#endif
