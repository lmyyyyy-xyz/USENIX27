#if defined WIN32 || defined _WIN32
#include <stdio.h>

FILE *popen(char *filename, char *mode)
{
	return(fopen(filename, mode));
}

int pclose(FILE *fp)
{
        return(fclose(fp));
}
#endif
