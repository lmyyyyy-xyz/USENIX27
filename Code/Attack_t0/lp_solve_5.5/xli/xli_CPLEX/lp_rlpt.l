WS1  [ \t]*
WS2  [ \t\r\n]*
WS3  {WS1}[\r\n]+
LT   [A-Za-z!\"#$%&\(\)/,;\?@_`'\{\}|~]
KR   [A-Za-z0-9!\"#$%&\(\)/,\.;\?@_`'\{\}|~]
DI   [0-9]
INNM {WS1}{DI}+
NM   {WS1}((({DI}+\.?{DI}*)|(\.{DI}+))([Ee][-+]?{DI}+)?)
VR   {WS1}{LT}{KR}*
S_OP {WS1}[-+]+
OPEQ {WS1}=
OPLE {WS1}[<]=?
OPGE {WS1}[>]=?
INF  {WS2}[-+][Ii][Nn][Ff]([Ii][Nn][Ii][Tt]([Ee]|[Yy]))?
FREE {WS1}[Ff][Rr][Ee][Ee]
MIN  ^{WS1}[mM][iI][nN](([iI][mM][iI][zZ][eE])?|([iI][mM][uU][mM])?)
MAX  ^{WS1}[mM][aA][xX](([iI][mM][iI][zZ][eE])?|([iI][mM][uU][mM])?)
ST   ^{WS1}(([sS][uU][bB][jJ][eE][cC][tT][ ][tT][oO])|([Ss][Uu][Cc][Hh][ ][Tt][Hh][Aa][Tt])|([sS][tT])|([sS][.][tT][.])|([sS][tT][.]))
BD   ^{WS1}[bB][oO][uU][nN][dD][sS]?
INT  ^{WS1}(([Ii][Nn][Tt]([Ee][Gg][Ee][Rr][Ss]?)?)|([Gg][Ee][Nn]([Ee][Rr][Aa][Ll][Ss]?)?)|([Bb][Ii][Nn]([Aa][Rr]([Yy]|([Ii][Ee][Ss])))?))
SEC  ^{WS1}(([Ss][Ee][Mm][Ii]-[Cc][Oo][Nn][Tt][Ii][Nn][Uu][Oo][Uu][Ss])|([Ss][Ee][Mm][Ii])|([Ss][Ee][Mm][Ii][Ss]))
SOS  ^{WS1}[Ss][Oo][Ss]
SOST ^({LBL})?{WS1}[Ss][12]{WS1}::
LBL  {VR}{WS1}:
END  ^{WS1}[Ee][Nn][Dd]

/*
   made reentrant with help of
   http://www.usualcoding.eu/post/2007/09/03/Building-a-reentrant-parser-in-C-with-Flex/Bison
*/

/*
   Note that a minimum version of flex is needed to be able to compile this.
   Older version don't know the reentrant code.
   Version 2.5.4 is not enough. Probably at least v2.5.31 is needed. Tested with v2.5.35
*/

/*
** We want the scanner to be reentrant, therefore generate no global variables.
** That what the 'reentrant' option is for.
** 'bison-bridge' is used to create a bison compatible scanner and share yylval
*/

%option reentrant bison-bridge
%option noyywrap
%option yylineno

%start LINECOMMENT

%%

<INITIAL>"\\" {
  BEGIN LINECOMMENT;
} /* begin skip LINECOMMENT */

<LINECOMMENT>\n {
  BEGIN INITIAL;
} /* end skip LINECOMMENT */

<LINECOMMENT>\r {
  BEGIN INITIAL;
} /* end skip LINECOMMENT */

<LINECOMMENT>. {
}

<INITIAL>{WS3} {
}

<INITIAL>{MIN} {
  parse_parm *pp = PARM;

  pp->lineno = yylineno;
  return(MINIMISE);
}

<INITIAL>{MAX} {
  parse_parm *pp = PARM;

  pp->lineno = yylineno;
  return(MAXIMISE);
}

<INITIAL>{ST} {
  parse_parm *pp = PARM;

  pp->lineno = yylineno;
  return(SUBJECTTO);
}

<INITIAL>{BD} {
  parse_parm *pp = PARM;

  pp->lineno = yylineno;
  return(BOUNDS);
}

<INITIAL>{END} {
  parse_parm *pp = PARM;

  pp->lineno = yylineno;
  return(END);
}

<INITIAL>{INNM} {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;
  char *ptr = (char *)yytext;

  pp->lineno = yylineno;
  while ((isspace(*ptr))) ptr++;
  pv->f = atof(ptr);
  return(INTCONS);
} /* f contains the last float */

<INITIAL>{NM} {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;
  char *ptr = (char *)yytext;

  pp->lineno = yylineno;
  while ((isspace(*ptr))) ptr++;
  pv->f = atof(ptr);
  return(CONS);
} /* f contains the last float */

<INITIAL>{INF} {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;
  char *ptr = (char *)yytext;

  pp->lineno = yylineno;
  pv->f = DEF_INFINITE;
  pv->Sign = 0;
  while (isspace(*ptr)) ptr++;
  if(*ptr == '-')
    pv->Sign = 1;
  return(INF);
} /* f contains the last float */

<INITIAL>{FREE} {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;
  char *ptr = (char *)yytext;

  pp->lineno = yylineno;
  while ((isspace(*ptr))) ptr++;
  FREE(pv->Last_var);
  pv->Last_var = strdup(ptr);
  return(FRE);
}

<INITIAL>{S_OP} {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;
  int x;

  pp->lineno = yylineno;
  pv->Sign = 0;
  for(x = 0; x < yyleng; x++)
    if(yytext[x] == '-' || yytext[x] == '+')
      pv->Sign = (pv->Sign == (yytext[x] == '+'));
  return (TOK_SIGN);
  /* Sign is TRUE if the sign-string
     represents a '-'. Otherwise Sign
     is FALSE */
}

<INITIAL>{INT} {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;
  char *ptr = (char *)yytext;

  pp->lineno = yylineno;
  while ((isspace(*ptr))) ptr++;
  pv->Within_gen_decl = pv->Within_bin_decl = pv->Within_sec_decl = pv->Within_sos_decl = FALSE;
  if((toupper(*ptr) == 'G') || (toupper(*ptr) == 'I'))
    pv->Within_gen_decl = TRUE;
  else
    pv->Within_bin_decl = TRUE;
  return(SEC_INT);
}

<INITIAL>{SEC} {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pp->lineno = yylineno;
  pv->Within_gen_decl = pv->Within_bin_decl = pv->Within_sec_decl = pv->Within_sos_decl = FALSE;
  pv->Within_sec_decl = TRUE;
  return(SEC_SEC);
}

<INITIAL>{SOS} {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pp->lineno = yylineno;
  pv->Within_gen_decl = pv->Within_bin_decl = pv->Within_sec_decl = pv->Within_sos_decl = FALSE;
  pv->Within_sos_decl = TRUE;
  return(SEC_SOS);
}

<INITIAL>{SOST} {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;
  char *ptr = (char *)yytext;

  pp->lineno = yylineno;
  while ((isspace(*ptr))) ptr++;
  FREE(pv->Last_var);
  pv->Last_var = strdup(ptr);
  return(SOSTYPE);
}

<INITIAL>{LBL} {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;
  char *ptr = (char *)yytext;

  pp->lineno = yylineno;
  while ((isspace(*ptr))) ptr++;
  FREE(pv->Last_var);
  pv->Last_var = strdup(ptr);
  ptr = pv->Last_var + strlen(pv->Last_var) - 1;
  while ((ptr > pv->Last_var) && (isspace(ptr[-1]))) ptr--;
  *ptr = 0;
  return(VARIABLECOLON);
}

<INITIAL>{VR} {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;
  char *ptr = (char *)yytext;

  pp->lineno = yylineno;
  while ((isspace(*ptr))) ptr++;
  FREE(pv->Last_var);
  pv->Last_var = strdup(ptr);
  return(VAR);
}

<INITIAL>{OPEQ} {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;
  char *ptr = (char *)yytext;

  pp->lineno = yylineno;
  while ((isspace(*ptr))) ptr++;
  if(ptr>(char *)yytext)
    strcpy((char *)yytext, ptr);
  pv->OP = *yytext;
  return(RE_OPEQ);
}

<INITIAL>{OPLE} {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;
  char *ptr = (char *)yytext;

  pp->lineno = yylineno;
  while ((isspace(*ptr))) ptr++;
  if(ptr>(char *)yytext)
    strcpy((char *)yytext, ptr);
  pv->OP = *yytext;
  return(RE_OPLE);
}

<INITIAL>{OPGE} {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;
  char *ptr = (char *)yytext;

  pp->lineno = yylineno;
  while ((isspace(*ptr))) ptr++;
  if(ptr>(char *)yytext)
    strcpy((char *)yytext, ptr);
  pv->OP = *yytext;
  return(RE_OPGE);
}

<INITIAL>. {
  parse_parm *pp = PARM;

  pp->lineno = yylineno;
  report(NULL, CRITICAL, "LEX ERROR : %s lineno %d\n", yytext, yylineno);
  return(UNDEFINED);
}

%%
