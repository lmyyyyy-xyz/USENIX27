#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#if !defined FALSE
# define FALSE 0
#endif

#if !defined TRUE
# define TRUE 1
#endif

#define options_char '-'

void setarg(char *lpCmdLine,int *argc, char ***argv)
 {
  int i;
  char c,*pointer,*pointer1,spacesinname=FALSE,optionarg;

  *argc=0;
  *argv=NULL;
  if (lpCmdLine!=NULL) {
   pointer=lpCmdLine;
   for (i=0;*pointer;pointer++) {
    if (*pointer=='"') i=1-i;
    if ((i==0) && (isspace((unsigned char) *pointer))) {
     (*argc)++;
     while (isspace((unsigned char) *pointer)) pointer++;
     if (*pointer==0) break;
     pointer--;
    }
   }
   *argv=malloc(((*argc)+1)*sizeof(**argv));
   if (*lpCmdLine) {
    pointer=pointer1=lpCmdLine;
    optionarg=(*pointer==options_char);
    for (*argc=0,i=0;;pointer++) {
     if (*pointer=='"') i=1-i;
     if (((i==0) || (*pointer==0)) && ((((!spacesinname) || (optionarg)) && (isspace((unsigned char) *pointer))) || (*pointer==0))) {
      c=*pointer;
      *pointer=0;
      if ((*pointer1==options_char) && (strcmp(pointer1+1,"s")==0))
       spacesinname=TRUE;
      else {
       (*argv)[*argc]=strdup(pointer1);
       if (((*argv)[*argc][0]=='"') && ((*argv)[*argc][strlen((*argv)[*argc])-1]=='"')) {
        strcpy((*argv)[*argc],(*argv)[*argc]+1);
        (*argv)[*argc][strlen((*argv)[*argc])-1]=0;
       }
       (*argc)++;
      }
      *pointer=c;
      while (isspace((unsigned char) *pointer)) pointer++;
      optionarg=(*pointer==options_char);
      pointer1=pointer--;
      if (*pointer1==0) break;
     }
     if (*pointer==0) break;
    }
   }
  }
 }

void freearg(int argc, char **argv)
{
  int i;

  if(argv!=NULL) {
    for (i=0; i<argc; i++)
      if (argv[i]!=NULL)
        free(argv[i]);
    free(argv);
  }
}
