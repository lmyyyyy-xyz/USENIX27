
/*  Modularized external language interface module - w/interface for lp_solve v5.0+
    This module is the implementation of the file format for the 1st Dimacs challenge.
   ----------------------------------------------------------------------------------
    Author:        Kjell Eikland
    Contact:       kjell.eikland@broadpark.no
    License terms: LGPL.

    Template used: lp_XLI2.c
    Requires:      lp_lib.h

    Release notes:
    v1.0.0  29 December 2005    First implementation.
   ---------------------------------------------------------------------------------- */

/* Generic include libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "lp_lib.h"

/* Include libraries for this language system */
#include "lp_network.h"
#include "lp_Dimacs.h"

#ifdef FORTIFY
# include "lp_fortify.h"
#endif


/* Include routines common to language interface implementations */
#include "lp_XLI1.c"

/* Local defines and constants */
#define  Dimacs_BUFSIZE  256

static char SpaceChars[3] = {" " "\7"};
/*
static char NumChars[14]  = {"0123456789-+."};
*/

typedef struct _GROSSrec {
  int maxP;
  int minP;
  int maxN;
  int minN;
  int NSLACK;
  int NSINK;
  int NSORC;
  int NSISO;
} GROSSrec;

#if (MAJORVERSION > 5) || (MAJORVERSION == 5 && MINORVERSION > 5) /* || (MAJORVERSION == 5 && MINORVERSION == 5 && RELEASE > 0)*/
#  define get_lowbo        lp->lpfunc->get_lowbo
#  define get_upbo         lp->lpfunc->get_upbo
#  define get_Ncolumns     lp->lpfunc->get_Ncolumns
#  define get_rh           lp->lpfunc->get_rh
#  define get_lp_name      lp->lpfunc->get_lp_name
#  define get_rh_range     lp->lpfunc->get_rh_range
#  define get_constr_type  lp->lpfunc->get_constr_type
#  define get_infinite     lp->lpfunc->get_infinite
#  define get_infinite     lp->lpfunc->get_infinite
#  define get_network_type lp->lpfunc->get_network_type
#  define get_Nrows        lp->lpfunc->get_Nrows
#  define set_bounds       lp->lpfunc->set_bounds
#  define set_constr_type  lp->lpfunc->set_constr_type
#  define set_lowbo        lp->lpfunc->set_lowbo
#  define set_lp_name      lp->lpfunc->set_lp_name
#  define set_rh           lp->lpfunc->set_rh
#  define set_rh_lower     lp->lpfunc->set_rh_lower
#  define set_rh_upper     lp->lpfunc->set_rh_upper
#  define set_sense        lp->lpfunc->set_sense
#  define report           lp->lpfunc->report
#  define add_columnex     lp->lpfunc->add_columnex
#  define resize_lp        lp->lpfunc->resize_lp
#  define is_constr_type   lp->lpfunc->is_constr_type
#  define get_objective    lp->lpfunc->get_objective
#  define get_var_primalresult lp->lpfunc->get_var_primalresult
#  define get_mat          lp->lpfunc->get_mat
#else
#  define get_lowbo        lp->get_lowbo
#  define get_upbo         lp->get_upbo
#  define get_Ncolumns     lp->get_Ncolumns
#  define get_rh           lp->get_rh
#  define get_lp_name      lp->get_lp_name
#  define get_rh_range     lp->get_rh_range
#  define get_constr_type  lp->get_constr_type
#  define get_infinite     lp->get_infinite
#  define get_infinite     lp->get_infinite
#  define get_Nrows        lp->get_Nrows
#  define set_bounds       lp->set_bounds
#  define set_constr_type  lp->set_constr_type
#  define set_lowbo        lp->set_lowbo
#  define set_lp_name      lp->set_lp_name
#  define set_rh           lp->set_rh
#  define set_rh_range     lp->set_rh_range
#  define set_rh_lower(lp, row, a) (get_constr_type(lp, row) == LE) ? set_rh_range(lp, row, get_rh(lp, row) - a) : set_rh(lp, row, a)
#  define set_rh_upper(lp, row, a) (get_constr_type(lp, row) == LE) ? set_rh(lp, row, a) : set_rh_range(lp, row, a - get_rh(lp, row))
#  define set_sense        lp->set_sense
#  define report           lp->report
#  define add_columnex     lp->add_columnex
#  define is_constr_type   lp->is_constr_type
#  define get_objective    lp->get_objective
#  define get_var_primalresult lp->get_var_primalresult
#  define get_mat          lp->get_mat

extern int __WINAPI get_network_type(lprec *lp, int *rowset, int *sinkValue);

MYBOOL __WINAPI resize_lp(lprec *lp, int rows, int columns)
{
  MYBOOL ret;

  ret = lp->resize_lp(lp, rows, columns);

  while ((ret) && (get_Nrows(lp) < rows))
    ret = lp->add_constraintex(lp, 0, NULL, NULL, LE, 0);

  return(ret);
}

#endif

/* static */ MYBOOL is_chsign(lprec *lp, int rownr)
{
  return( (MYBOOL) ((lp->row_type[rownr] & ROWTYPE_CONSTRAINT) == ROWTYPE_CHSIGN) );
}

/* CAN MODIFY */
char * XLI_CALLMODEL xli_name(void)
{
  return( "XLI_Dimacs v1.0" );
}

static int _Dimacs_hook_fn(lprec *lp, char *msg, int verbose)
{
  char *str;

  if ((str = (char *) malloc(strlen(msg) + 1 + 1)) != NULL) {
    sprintf(str, "%s\n", msg);
    report(lp, verbose, str);
    free(str);
    return(TRUE);
  }
  return(FALSE);
}

static int _Dimacs_print_hook_fn(void *lp, char *msg)
{
  return(_Dimacs_hook_fn((lprec *)lp, msg, NORMAL));
}

static int _Dimacs_fault_hook_fn(void *lp, char *msg)
{
  return(_Dimacs_hook_fn((lprec *)lp, msg, IMPORTANT));
}


int my_FindPos(char Target, char *List)
{
  int i = 0;
  while ((List[i]!='\0') && (List[i]!=Target))
    i++;
  if(List[i]==Target)
    return(i);
  else
    return(-1);
}
int my_SubStr(char *Target, char *Source, int bpos, int epos)
{
  epos=epos-bpos+1;
  if(epos>0)
    memmove(Target, Source+bpos, (size_t) epos);
  else
    epos=0;
  Target[epos]='\0';
  return( epos );
}
int my_ReadRec(FILE *input, char *TextIO, int bufsize)
{
  int length = 0;
  bufsize--;
  while (fgets(TextIO, bufsize, input) != NULL) {
    length = (int) strlen(TextIO);
    if((length>1) && (TextIO[length-2] == '\r') && (TextIO[length-1] == '\n')) {
      TextIO[length - 2] = TextIO[length - 1];
      TextIO[--length] = '\0';
    }
    if((length>0) && (TextIO[0]!='c'))
      break;
    length = 0;
  }
  if(ferror(input))
    length = -1;
  else if((length>0) && (TextIO[length-1]=='\n'))
    TextIO[--length] = '\0';
  return( length );
}

/*
 length: Length of TextIO
 _Pos:   Position in TextIO - 0-based
*/
MYBOOL my_NextField(char *TextIO, int length, int *_Pos)
{
  MYBOOL result;
  while (((*_Pos)<length) &&
         (my_FindPos(TextIO[*_Pos], SpaceChars)>=0))
    (*_Pos)++;
  result=(MYBOOL) ((*_Pos)<length);
  if (result)
  while (((*_Pos)<length) &&
         (my_FindPos(TextIO[*_Pos], SpaceChars)<0))
    (*_Pos)++;
  return( result );
}

/*
 _fTarget: Which field requested - 1-based
 _fNow:    Now positioned on field fNow
 _cNow:    Position in TextIO - 0-based
*/
int my_ReadField(char *TextIO, int length, int _fTarget, int *_fNow, int *_cNow, char *result)
{
  int cEnd;
  /* Start from the ending if the target is beyond the current position */
  if ((*_fNow)>_fTarget) {
    (*_fNow)=1;
    (*_cNow)=1;
  }
  /* Otherwise set variables to scan forward from current position */
  else {
    SETMAX((*_fNow),1);
    SETMAX((*_cNow),1);
  }
  /* Scan forward to field before target position && store the ending character
     index which is the starting index of the target field */
  while (((*_fNow)<_fTarget) && my_NextField(TextIO, length, _cNow))
    (*_fNow)++;
  cEnd=(*_cNow);
  /* Scan the characters of the target position to find the ending index */
  while (((*_fNow)<=_fTarget) && my_NextField(TextIO, length, &cEnd))
    (*_fNow)++;

  /* Extract the target field as a string, if desired */
  if(result!=NULL)
  if ((*_cNow)>=length)
    strcpy(result, "0");
  else {
    /* Trim leading and trailing spaces */
    while (((*_cNow)<cEnd) && (my_FindPos(TextIO[*_cNow], SpaceChars)>=0))
      (*_cNow)++;
    length = cEnd-1;
    while (((*_cNow)<length) && (my_FindPos(TextIO[length], SpaceChars)>=0))
      length--;
    /* Get it */
    memmove(result, TextIO+(*_cNow), cEnd-(*_cNow));
  }

  /* Update starting index in preparation for next call, hopefully with a positive delta field index */
  length = cEnd-(*_cNow);
  (*_cNow)=cEnd;
  if(result!=NULL)
    result[length]='\0';
  return( length );
}

/*
  _fNow:  Now positioned on field fNow
*/
int my_CountFields(char *TextIO, int length)
{
  int fNow = 0, cNow = 0, count=0;
  while (cNow<length) {
    count++;
    my_ReadField(TextIO, length, count, &fNow, &cNow, NULL);
  }
  return( count );
}

/*
_fTarget: Which field requested - 1-based
 _fNow:   Now positioned on field fNow
 _cNow:   Position in TextIO - 0-based
*/
int my_IntField(char *TextIO, int length, int _fTarget, int *_fNow, int *_cNow)
{
  static char buf[10];
  my_ReadField(TextIO, length, _fTarget, _fNow, _cNow, buf);
  return( atoi(buf) );
}

/*
_fTarget: Which field requested - 1-based
 _fNow:   Now positioned on field fNow
 _cNow:   Position in TextIO - 0-based
*/
REAL my_NumField(char *TextIO, int length, int _fTarget, int *_fNow, int *_cNow)
{
  static char buf[20];
  my_ReadField(TextIO, length, _fTarget, _fNow, _cNow, buf);
#ifdef INTCOST
  return( (int) atof(buf) );
#else
  return( atof(buf) );
#endif
}

STATIC MYBOOL my_AddNode(lprec *lp, int NodeNo, REAL MaxQ, REAL MinQ, GROSSrec *gross)
{
  MYBOOL status = TRUE;

  /* Set lprec data */
  if(MaxQ==MinQ) {
    status = set_constr_type(lp, NodeNo, EQ) &&
             set_rh(lp, NodeNo, MaxQ);
  }
  else if(MinQ<MaxQ) {
    status = set_constr_type(lp, NodeNo, LE) &&
             set_rh_upper(lp, NodeNo, MaxQ) &&
             set_rh_lower(lp, NodeNo, MinQ);
  }
  else {
    status = set_constr_type(lp, NodeNo, GE) &&
             set_rh_lower(lp, NodeNo, MaxQ) &&
             set_rh_upper(lp, NodeNo, MinQ);
  }
  /* Update statistics */
  if (MaxQ!=0) {
    if (((MaxQ>0) && (MinQ<MaxQ)) ||
        ((MaxQ<0) && (MinQ>MaxQ))) {
      (*gross).NSLACK++;
    }
    if ((*gross).NSLACK>0) {
      if (MinQ<0)
        (*gross).minN=(*gross).minN+MinQ;
      else
        (*gross).minP=(*gross).minP+MinQ;
    }
    /* Update max counts */
    if (MaxQ<0) {
      (*gross).NSINK++;
      (*gross).maxN=(*gross).maxN+MaxQ;
    }
    else if (MaxQ>0) {
      (*gross).NSORC++;
      (*gross).maxP=(*gross).maxP+MaxQ;
    }
    if ((MaxQ>0) ^ (MinQ>0))
      (*gross).NSISO++;
  }
  if(!status)
    report(lp, SEVERE, "my_AddNode: Encountered error in adding node %d\n", NodeNo);

  return( status );
}
STATIC MYBOOL my_AddArc(lprec *lp, int ArcNo, int NodeF, int NodeT, REAL Cost, REAL MaxQ, REAL MinQ)
{
  static int  nzIdx[3];
  static REAL nzVal[3];
  int    nzstart = 0;
  MYBOOL status = FALSE;

  nzIdx[0]=0;
  nzIdx[1]=NodeF;
  nzIdx[2]=NodeT;
  nzVal[0]=Cost;
  nzVal[1]=network_stdNodeSource;
  nzVal[2]=network_stdNodeSink;
  if(Cost==0)
    nzstart++;
  status = add_columnex(lp, 3-nzstart, &nzVal[nzstart], &nzIdx[nzstart]);
  if(status) {
    if(MaxQ<0) {
      if(MinQ>0)
        status = set_lowbo(lp, ArcNo, MinQ);
    }
    else
      status = set_bounds(lp, ArcNo, MinQ, MaxQ);
  }
  if(!status)
    report(lp, SEVERE, "my_AddArc: Encountered error in adding arc %d\n", ArcNo);
  return( status );
}

/* CAN MODIFY */
MYBOOL XLI_CALLMODEL xli_readmodel(lprec *lp, char *model, char *data, char *options, int verbose)
{
  MYBOOL status = FALSE,
         *defined = NULL;
  char   TextIO[Dimacs_BUFSIZE];
  char   FieldVal[Dimacs_BUFSIZE];
  int    length, NODES, ARCS;
  int    I,J,K,L1,NF;
  int    fNow,cNow;
  int    I1,I2;
  int    Q1,Q2;
  int    ThisModel;
  GROSSrec gross;

  FILE   *fpin = fopen(model, "r");
  if(fpin == NULL) {
    report(lp, SEVERE, "xli_readmodel: Could not find the model file '%s'\n", model);
    return( status );
  }
  if (feof(fpin))
    goto Done;

  MEMCLEAR(&gross, 1);
  length=my_ReadRec(fpin, TextIO, Dimacs_BUFSIZE);
  if (TextIO[0]!='p') {
    report(lp, SEVERE, "xli_readmodel: '%s' does not seem to be a Dimacs-format file\n", model);
    goto Done;
  }
  I=my_FindPos(' ', TextIO);
  do {
    I++;
  } while (TextIO[I]==' ');
  length=my_SubStr(TextIO, TextIO, I,length-1); /* Remove problem key lead */

  /* Determine model type */
  I=my_FindPos(' ', TextIO);
  my_SubStr(FieldVal, TextIO, 0, I-1);
  ThisModel=get_Dimacs_type(FieldVal);
  if ((ThisModel==network_Unknown) || (ThisModel==network_MaxEdgeMatch) || (ThisModel==network_MaxGeoMatch))
    goto Done;

  /* Get model dimension */
  fNow=0;
  cNow=I;
  NODES=my_IntField(TextIO, length, 1, &fNow,&cNow);
  ARCS=my_IntField(TextIO, length, 2, &fNow,&cNow);
  defined = (MYBOOL *) calloc(NODES+1,sizeof(MYBOOL));
  if(defined == NULL)
    goto Done;
  if (ARCS==0)
    ARCS=10*NODES;

  /* Make sure that the model is resized and set to full row dimensionality */
  if (!resize_lp(lp, NODES, ARCS))
    goto Done;
  for (K=1; K<=NODES; K++)
    set_constr_type(lp, K, EQ);

  /* Define the model proper */
  set_lp_name(lp, model);
  set_sense(lp, (MYBOOL) (ThisModel==network_MaxFlow));

  /* Now read nodes */
  length=my_ReadRec(fpin, TextIO, Dimacs_BUFSIZE);
  NF=my_CountFields(TextIO, length);
  K=0;
  while ((K<NODES) && (TextIO[0]=='n')) {  /* nODES */
    K++;
    fNow=0;
    cNow=0;
    I=my_IntField(TextIO, length, 1, &fNow,&cNow);
    defined[I]=TRUE;
    switch (ThisModel) {
      case network_MinCost: {
                    if ((NF==3) || (NF==5)) {    /* Read minimum node data */
                      L1=1;
                      Q1=my_IntField(TextIO, length, 2, &fNow,&cNow);
                      Q2=my_IntField(TextIO, length, 2+L1, &fNow,&cNow);
                    }
                    else {
                      L1=0;
                      Q2=my_IntField(TextIO, length, 2+L1, &fNow,&cNow);
                      /* Never allow unsatisfied demand node in default format */
                      if (Q2<0)
                        Q1=Q2;
                      else
                        Q1=0;
                    }
                    if (!my_AddNode(lp, I, Q2,Q1, &gross)) goto Done;
                    break;
                  }
      case network_MaxFlow: {
                    my_ReadField(TextIO, length, 2, &fNow, &cNow, FieldVal);
                    if (strcmp(FieldVal,"source")==0)
                      strcpy(FieldVal, "s");
                    else if ((strcmp(FieldVal,"sink")==0) || (strcmp(FieldVal,"demand")==0))
                      strcpy(FieldVal, "t");
                    if ((strlen(FieldVal)!=1) || ((FieldVal[0]!='s') && (FieldVal[0]!='t')))
                      goto Done;
                    Q2=MAXINT32/3;
                    if (((FieldVal[0]=='s') &&
                         !my_AddNode(lp, I, Q2,0, &gross)) ||
                        ((FieldVal[0]=='t') &&
                         !my_AddNode(lp, I, -Q2,0, &gross))) goto Done;
                    break;
                  }
      case network_Assignment: if (!my_AddNode(lp, I, 1,1, &gross)) goto Done; /* Supply only! */
                               break;
    }
    length=my_ReadRec(fpin, TextIO, Dimacs_BUFSIZE);
  }

  /* DO MODEL-SPECIFIC ADDITIONS */
  if (ThisModel==network_Assignment) {  /* Add sink nodes (supply added above) */
    for (I=K+1; I<=NODES; I++) {
      if (!my_AddNode(lp, I, -1,-1, &gross))
        goto Done;
    }
  }
  else {                                /* Assume that remainder are transshipment nodes */
    for (J=1; J<=NODES; J++) {
      if (!defined[J] && !my_AddNode(lp, J, 0,0, &gross))
        goto Done;
    }
  }

  /* RESET FLEX NODES IF THE MODEL HAS NET FLOW OF ZERO; THIS IS DIMACS! */
  Q2=gross.maxP+gross.maxN;
  Q1=gross.maxP+gross.minN;
/* Q1=(gross.maxP-gross.minP) + (gross.minN-gross.maxN); */
#if 1
  if ((ThisModel != network_MaxFlow) &&
      ((Q2==0) && ((NF==2) || (NF==4) || (Q1==0)))) {
    for (I=1; I<=NODES; I++)
      if(!is_constr_type(lp, I, EQ))
        set_constr_type(lp, I, EQ);
    gross.NSLACK=0;
  }
#endif

  /* READ ARC DEFINITIONS */
  K=0;
  while ((K<ARCS) && (TextIO[0]=='a')) {  /* aRCS */
    K++;
    fNow=0;
    cNow=0;
    I1=my_IntField(TextIO, length, 1, &fNow,&cNow);
    I2=my_IntField(TextIO, length, 2, &fNow,&cNow);
    switch (ThisModel) {
      case network_MinCost: {
                    Q1=my_IntField(TextIO, length, 3, &fNow,&cNow);
                    Q2=my_IntField(TextIO, length, 4, &fNow,&cNow);
                    if (!my_AddArc(lp, K, I1,I2,
                                          my_NumField(TextIO, length, 5, &fNow,&cNow),
                                          Q2,Q1)) goto Done;
                    break;
                  }
      case network_MaxFlow: {
                    Q2=my_IntField(TextIO, length, 3, &fNow,&cNow);
                    if (!my_AddArc(lp, K, I1,I2,
                                          1,
                                          Q2,0)) goto Done;
                    break;
                  }
      case network_Assignment: if (!my_AddArc(lp, K, I1,I2,
                                                     my_NumField(TextIO, length, 3, &fNow,&cNow),
                                                     1,0)) goto Done;
                                break;
    }
    length=my_ReadRec(fpin, TextIO, Dimacs_BUFSIZE);
  }

  status=TRUE;

Done:
  FREE(defined);
  fclose(fpin);
#if 0
  xli_writemodel(lp, "testtt.dim", NULL, FALSE);
#endif
  return( status );
}

/* ------------------------------------------------------------------------- */
/*  Write model in Dimacs format                                             */
/* ------------------------------------------------------------------------- */

static void __VACALL write_Dimacs(FILE *output, char *format, ...)
{
  va_list ap;

  va_start(ap, format);
  vfprintf(output, format, ap);
  va_end(ap);
  fprintf(output, "\n");
  if(output == stdout)
    fflush(output);
}

/* CAN MODIFY */
MYBOOL XLI_CALLMODEL xli_writemodel(lprec *lp, char *filename, char *options, MYBOOL results)
{
  int    i, j, Ncolumns, Nrows,
         nwtype, sinkValue, NodeF, NodeT, NodeF0;
  REAL   constant_term, upbo, infinite, a;
  char   *ptr, strDimacs[255], *argoptions = NULL, c;
  FILE   *output = stdout;
  MATrec *mat = lp->matA;
  MYBOOL ok = FALSE, nz = FALSE;

  /* Check that we have a properly structured network model */
  nwtype = get_network_type(lp, NULL, &sinkValue);
  if(nwtype == network_Unknown) {
    report(lp, IMPORTANT, "Cannot generate Dimacs model - The constraints do not form an incidence matrix.");
    return( ok );
  }
  else if(lp->sc_vars > 0) {
    report(lp, IMPORTANT, "Cannot generate Dimacs model - Model has semi-continuous variables.");
    return( ok );
  }
  else if(lp->SOS != NULL) {
    report(lp, IMPORTANT, "Cannot generate Dimacs model - Model contains SOS.");
    return( ok );
  }
  if(!results) {
    constant_term = get_rh(lp, 0);
    if(constant_term != 0)
      report(lp, IMPORTANT, "Warning: Ignored constant term in the objective function.");
  }

  /* Prepare the destination file */
  ok = (MYBOOL) ((filename == NULL) || ((output = fopen(filename,"w")) != NULL));
  if(!ok)
    return( ok );
  if((filename == NULL) && (lp->outstream != NULL))
    output = lp->outstream;

/* USAGE options
  -nz            Only output non-zero values
*/

   argoptions = options;
   if(argoptions == NULL)
     ;
   else
   {
     while ((argoptions = strstr(argoptions, "-")) != NULL) {
       argoptions++;
       if (*argoptions == '\0')
         goto Quit;
       /* c = atoi(argoptions); */
       c = *(argoptions++);
       while(*argoptions == ' ')
         argoptions++;

       switch(c)
       {
         case 'n' :
           if ((*argoptions != 'z') || (strlen(argoptions) != 1))
             goto Quit;

           argoptions++;
           nz = TRUE;
           break;
         default :
           goto Quit;
       }
       while(*argoptions == ' ')
         argoptions++;
       if ((strlen(argoptions) > 0) && (*argoptions != '-'))
         goto Quit;
     }
   }

  /* Write name of model */
  ptr = get_lp_name(lp);
  if((ptr != NULL) && (*ptr)) {
    write_Dimacs(output, DimacsCommentFmt, ptr);
    write_Dimacs(output, DimacsCommentFmt, "");
  }

  infinite = get_infinite(lp);
  Ncolumns = get_Ncolumns(lp);
  Nrows = get_Nrows(lp);

  /* Write any comment lines */
  switch (nwtype) {
    case network_MinCost:
      sprintf(strDimacs, "Dimacs-format minimum cost flow %s file", (results) ? "result" : "model");
      break;
    case network_MaxFlow:
      sprintf(strDimacs, "Dimacs-format maximum flow %s file", (results) ? "result" : "model");
      break;
    case network_Assignment:
      sprintf(strDimacs, "Dimacs-format network assignment %s file", (results) ? "result" : "model");
      break;
  }
  write_Dimacs(output, DimacsCommentFmt, strDimacs);

  if(results) {
    write_Dimacs(output, DimacsCommentFmt, "generated by lp_solve");

    /* solution */
    write_Dimacs(output, DimacsCommentFmt, "");
    write_Dimacs(output, DimacsCommentFmt, "Solution");
    switch (nwtype) {
      case network_MinCost:
	a = get_objective(lp);
        break;
      case network_MaxFlow:
	for (a = 0.0, i=1; i<=Nrows; i++) {
	  upbo = get_rh(lp, i)*sinkValue;
	  if (upbo>0) {
	    NodeF0 = i;
	    for (i=1; i<=Ncolumns; i++) {
	      j=mat->col_end[i-1];
	      NodeF=COL_MAT_ROWNR(j);
	      NodeT=COL_MAT_ROWNR(j+1);
	      if(COL_MAT_VALUE(j)*sinkValue < 0) {
		j=NodeF;
		NodeF=NodeT;
		NodeT=j;
	      }
	      if(NodeF == NodeF0)
		a += get_var_primalresult(lp, Nrows + i) * get_mat(lp, 0, i);
	    }
	  }
	}
        break;
      case network_Assignment:
	a = get_objective(lp);
        break;
    }
    write_Dimacs(output, DimacsSolutionFmt, a);
  }
  else {
    /* First, write the number of nodes and arcs */
    write_Dimacs(output, DimacsCommentFmt, "");
    write_Dimacs(output, DimacsCommentFmt, "Problem dimensions <Nodes> <Arcs>");
    strcpy(strDimacs, get_Dimacs_name(nwtype, FALSE));
    for (ptr = strDimacs; *ptr; ptr++)
      *ptr = tolower(*ptr);
    write_Dimacs(output, DimacsProblemFmt, strDimacs, Nrows, Ncolumns);
  }

  if(!results) {
    /* Secondly, write node supply/demand data */
    write_Dimacs(output, DimacsCommentFmt, "");
    switch (nwtype) {
      case network_MinCost:    write_Dimacs(output, DimacsCommentFmt, "Node definitions <ID> <-Demand/+Supply>");
                               break;
      case network_MaxFlow:    write_Dimacs(output, DimacsCommentFmt, "Node definitions <ID> <s/t (source/sink)>");
                               break;
      case network_Assignment: write_Dimacs(output, DimacsCommentFmt, "Node definitions <ID>");
                               break;
    }
    for (i=1; i<=Nrows; i++) {
      upbo = get_rh(lp, i)*sinkValue;
      if (upbo!=0)
      switch (nwtype) {
        case network_MinCost:    write_Dimacs(output, DimacsMinCostNodeFmt, i, (int) upbo);
                                 break;
        case network_MaxFlow:    write_Dimacs(output, DimacsMaxFlowNodeFmt, i, ((upbo<0) ? "t" : "s"));
                                 break;
        case network_Assignment: if (upbo>0)
                                   write_Dimacs(output, DimacsAssignmentNodeFmt, i);
                                 break;
      }
    }
  }

  if(!results) {
    /* Thirdly, write arc data */
    write_Dimacs(output, DimacsCommentFmt, "");
    switch (nwtype) {
      case network_MinCost:    write_Dimacs(output, DimacsCommentFmt, "Arc definitions <From> <To> <MinFlow> <Capacity> <Cost>");
                               break;
      case network_MaxFlow:    write_Dimacs(output, DimacsCommentFmt, "Arc definitions <From> <To> <Capacity>");
                               break;
      case network_Assignment: write_Dimacs(output, DimacsCommentFmt, "Arc definitions <From> <To> <Cost>");
                               break;
    }
  }
  else {
    write_Dimacs(output, DimacsCommentFmt, "");
    if(nz)
      write_Dimacs(output, DimacsCommentFmt, "Only non-zero flows are written");
    write_Dimacs(output, DimacsCommentFmt, "SRC DST FLOW");
  }

  for (i=1; i<=Ncolumns; i++) {
    j=mat->col_end[i-1];
    NodeF=COL_MAT_ROWNR(j);
    NodeT=COL_MAT_ROWNR(j+1);
    a=COL_MAT_VALUE(j);
    a=my_chsign(is_chsign(lp, NodeF), COL_MAT_VALUE(j));
    if(a*sinkValue < 0) {
      j=NodeF;
      NodeF=NodeT;
      NodeT=j;
    }
    if(!results) {
      upbo=get_upbo(lp, i);
      if (upbo>=infinite)
        upbo=-1;
      switch (nwtype) {
        case network_MinCost:    write_Dimacs(output, DimacsMinCostArcFmt,
                                              NodeF,NodeT, (int) get_lowbo(lp, i),(int) upbo, lp->orig_obj[i]);
                                 break;
        case network_MaxFlow:    write_Dimacs(output, DimacsMaxFlowArcFmt,
                                              NodeF,NodeT, (int) upbo);
                                 break;
        case network_Assignment: write_Dimacs(output, DimacsAssignmentArcFmt,
                                              NodeF,NodeT, lp->orig_obj[i]);
                                 break;
      }
    }
    else {
      a = get_var_primalresult(lp, Nrows + i);
      if((a != 0) || (!nz))
        write_Dimacs(output, DimacsFlowFmt, NodeF, NodeT, a);
    }
  }

  /* Wrap up */
  write_Dimacs(output, DimacsCommentFmt, "");
  write_Dimacs(output, DimacsCommentFmt, "End of file");

  ok = TRUE;

Quit:

  if(filename != NULL)
    fclose(output);

  return( ok );
}

