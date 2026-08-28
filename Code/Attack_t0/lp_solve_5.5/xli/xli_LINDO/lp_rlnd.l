WS   [ \t\r\n]+
LT   [A-Za-z\"#$%&\(/,;\?@_`'\{\}|~]
KR   [A-Za-z0-9\"#$%&\(/,\.;\?@_`'\{\}|~]
DI   [0-9]
INNM {DI}+
NM   (({DI}+\.?{DI}*)|(\.{DI}+))([Ee][-+]?{DI}+)?
VR   {LT}{KR}*
S_OP [-+]+
OPEQ =
OPLE [<]=?
OPGE [>]=?
INF  [ \r\n\t]*[-+][Ii][Nn][Ff]([Ii][Nn][Ii][Tt]([Ee]|[Yy]))?
TITLE [Tt][Ii][Tt][Ll][Ee][ \t][^\r\n]*
FREE [Ff][Rr][Ee][Ee]
MIN  [mM][iI][nN](([iI][mM][iI][zZ][eE])?)
MAX  [mM][aA][xX](([iI][mM][iI][zZ][eE])?)
ST   ([sS][uU][bB][jJ][eE][cC][tT][ ][tT][oO])|([Ss][Uu][Cc][Hh][ ][Tt][Hh][Aa][Tt])|([sS][tT])|([sS][.][tT][.])
INT  ([Ii][Nn][Tt])|([Gg][Ii][Nn])
SLB  [sS][lL][bB]
SUB  [sS][uU][bB]
LBL  {VR}\)
END  [Ee][Nn][Dd]

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

<INITIAL>"!" {
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

<INITIAL>{WS} {
  parse_parm *pp = PARM;

  pp->lineno = yylineno;
}

<INITIAL>{TITLE} {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pp->lineno = yylineno;
  pv->title = yytext + 6;
  while(isspace(*pv->title))
    pv->title++;
  return(TITLE);
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

<INITIAL>{END} {
  parse_parm *pp = PARM;

  pp->lineno = yylineno;
  return(END);
}

<INITIAL>{INNM} {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pp->lineno = yylineno;
  pv->f = atof((char *)yytext);
  return(INTCONS);
} /* f contains the last float */

<INITIAL>{NM} {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pp->lineno = yylineno;
  pv->f = atof((char *)yytext);
  return(CONS);
} /* f contains the last float */

<INITIAL>{INF} {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;
  char *ptr;

  pp->lineno = yylineno;

  pv->f = DEF_INFINITE;
  pv->Sign = 0;
  ptr = (char *)yytext;
  while (isspace(*ptr)) ptr++;
  if(*ptr == '-')
    pv->Sign = 1;
  return(INF);
} /* f contains the last float */

<INITIAL>{FREE} {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pp->lineno = yylineno;
  FREE(pv->Last_var);
  pv->Last_var = strdup((char *)yytext);
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

  pp->lineno = yylineno;
  pv->Within_gen_decl = pv->Within_bin_decl = pv->Within_sec_decl = pv->Within_sos_decl = FALSE;
  if(toupper(*yytext) == 'G')
    pv->Within_gen_decl = TRUE;
  else
    pv->Within_bin_decl = TRUE;
  return(SEC_INT);
}

<INITIAL>{SLB} {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pp->lineno = yylineno;
  pv->Within_gen_decl = pv->Within_bin_decl = pv->Within_sec_decl = pv->Within_sos_decl = FALSE;
  return(SEC_SLB);
}

<INITIAL>{SUB} {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pp->lineno = yylineno;
  pv->Within_gen_decl = pv->Within_bin_decl = pv->Within_sec_decl = pv->Within_sos_decl = FALSE;
  return(SEC_SUB);
}

<INITIAL>{LBL} {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pp->lineno = yylineno;
  FREE(pv->Last_var);
  pv->Last_var = strdup((char *)yytext);
  pv->Last_var[strlen(pv->Last_var) - 1] = 0;
  return(VARIABLEPARANT);
}

<INITIAL>{VR} {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pp->lineno = yylineno;
  FREE(pv->Last_var);
  pv->Last_var = strdup((char *)yytext);
  return(VAR);
}

<INITIAL>{OPEQ} {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pp->lineno = yylineno;
  pv->OP = *yytext;
  return(RE_OPEQ);
}

<INITIAL>{OPLE} {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pp->lineno = yylineno;
  pv->OP = *yytext;
  return(RE_OPLE);
}

<INITIAL>{OPGE} {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pp->lineno = yylineno;
  pv->OP = *yytext;
  return(RE_OPGE);
}

<INITIAL>. {
  report(NULL, CRITICAL, "LEX ERROR : %s lineno %d\n", yytext, yylineno);
  return(UNDEFINED);
}

%%
