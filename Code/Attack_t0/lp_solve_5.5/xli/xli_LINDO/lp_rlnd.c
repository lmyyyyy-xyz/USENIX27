/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with lnd_yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum lnd_yytokentype {
     VAR = 258,
     CONS = 259,
     INTCONS = 260,
     VARIABLEPARANT = 261,
     TITLE = 262,
     INF = 263,
     FRE = 264,
     SEC_SLB = 265,
     SEC_SUB = 266,
     SEC_INT = 267,
     TOK_SIGN = 268,
     RE_OPEQ = 269,
     RE_OPLE = 270,
     RE_OPGE = 271,
     MINIMISE = 272,
     MAXIMISE = 273,
     SUBJECTTO = 274,
     END = 275,
     UNDEFINED = 276
   };
#endif
/* Tokens.  */
#define VAR 258
#define CONS 259
#define INTCONS 260
#define VARIABLEPARANT 261
#define TITLE 262
#define INF 263
#define FRE 264
#define SEC_SLB 265
#define SEC_SUB 266
#define SEC_INT 267
#define TOK_SIGN 268
#define RE_OPEQ 269
#define RE_OPLE 270
#define RE_OPGE 271
#define MINIMISE 272
#define MAXIMISE 273
#define SUBJECTTO 274
#define END 275
#define UNDEFINED 276




/* Copy the first part of user declarations.  */


#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define scanner lnd_yyscanner
#define PARM lnd_yyget_extra(lnd_yyscanner)
#define YYSTYPE int
#define YY_EXTRA_TYPE parse_parm *
#define YY_FATAL_ERROR(msg) lex_fatal_error(PARM, lnd_yyscanner, msg)
#define lnd_yyerror read_error

#include "lpkit.h"
#include "yacc_read.h"

typedef struct parse_vars_s
{
  char HadVar, HadConstraint, Had_lineair_sum, OP, Sign, isign, make_neg, TypeBound;
  char Within_gen_decl;  /* TRUE when we are within an gen declaration */
  char Within_bin_decl;  /* TRUE when we are within an bin declaration */
  char Within_sec_decl;  /* TRUE when we are within a sec declaration */
  char Within_sos_decl;  /* TRUE when we are within a sos declaration */
  char *Last_var, *title;
  REAL f;
} parse_vars;

#ifdef FORTIFY
# include "lp_fortify.h"
#endif

/* let's please C++ users */
#ifdef __cplusplus
extern "C" {
#endif

#if defined MSDOS || defined __MSDOS__ || defined WINDOWS || defined _WINDOWS || defined WIN32 || defined _WIN32
#define YY_NO_UNISTD_H

static int isatty(int f)
{
  return(FALSE);
}

#if !defined _STDLIB_H
# define _STDLIB_H
#endif
#endif

#ifdef __cplusplus
};
#endif

#include "lp_rlnd.inc"

#undef lnd_yylval



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define lnd_yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */


#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 lnd_yytype_uint8;
#else
typedef unsigned char lnd_yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 lnd_yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char lnd_yytype_int8;
#else
typedef short int lnd_yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 lnd_yytype_uint16;
#else
typedef unsigned short int lnd_yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 lnd_yytype_int16;
#else
typedef short int lnd_yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined lnd_yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined lnd_yyoverflow || YYERROR_VERBOSE */


#if (! defined lnd_yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union lnd_yyalloc
{
  lnd_yytype_int16 lnd_yyss;
  YYSTYPE lnd_yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union lnd_yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (lnd_yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T lnd_yyi;				\
	  for (lnd_yyi = 0; lnd_yyi < (Count); lnd_yyi++)	\
	    (To)[lnd_yyi] = (From)[lnd_yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T lnd_yynewbytes;						\
	YYCOPY (&lnd_yyptr->Stack, Stack, lnd_yysize);				\
	Stack = &lnd_yyptr->Stack;						\
	lnd_yynewbytes = lnd_yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	lnd_yyptr += lnd_yynewbytes / sizeof (*lnd_yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   91

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  22
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  47
/* YYNRULES -- Number of rules.  */
#define YYNRULES  66
/* YYNRULES -- Number of states.  */
#define YYNSTATES  95

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   276

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? lnd_yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const lnd_yytype_uint8 lnd_yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const lnd_yytype_uint8 lnd_yyprhs[] =
{
       0,     0,     3,     4,     5,    12,    15,    18,    20,    21,
      25,    27,    28,    32,    34,    37,    39,    40,    44,    45,
      51,    53,    55,    57,    60,    61,    66,    71,    73,    75,
      77,    80,    82,    84,    86,    88,    91,    93,    95,    97,
      99,   101,   103,   105,   107,   109,   110,   111,   112,   121,
     122,   126,   127,   131,   132,   133,   141,   143,   145,   147,
     149,   151,   153,   155,   156,   160,   162
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const lnd_yytype_int8 lnd_yyrhs[] =
{
      24,     0,    -1,    -1,    -1,    25,    47,    26,    30,    68,
      43,    -1,    18,    27,    -1,    17,    27,    -1,    29,    -1,
      -1,     6,    28,    29,    -1,    37,    -1,    -1,    19,    31,
      32,    -1,    33,    -1,    32,    33,    -1,    35,    -1,    -1,
       6,    34,    35,    -1,    -1,    37,    41,    36,    42,    61,
      -1,    23,    -1,    38,    -1,    39,    -1,    38,    39,    -1,
      -1,    62,    67,    40,    63,    -1,    62,    60,    67,    63,
      -1,    14,    -1,    15,    -1,    16,    -1,    62,    60,    -1,
       8,    -1,    23,    -1,    44,    -1,    45,    -1,    44,    45,
      -1,    46,    -1,    48,    -1,    65,    -1,     7,    -1,    23,
      -1,    46,    -1,    49,    -1,    53,    -1,    55,    -1,    -1,
      -1,    -1,     9,    67,    50,    63,    51,    61,    52,    61,
      -1,    -1,    10,    54,    57,    -1,    -1,    11,    56,    57,
      -1,    -1,    -1,    67,    58,    63,    62,    60,    59,    61,
      -1,     5,    -1,     4,    -1,    23,    -1,    23,    -1,    13,
      -1,    23,    -1,    67,    -1,    -1,    12,    66,    64,    -1,
       3,    -1,    20,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const lnd_yytype_uint16 lnd_yyrline[] =
{
       0,    85,    85,    89,    89,   117,   122,   129,   131,   130,
     142,   180,   179,   195,   196,   200,   202,   201,   215,   213,
     239,   246,   249,   250,   256,   254,   263,   269,   269,   269,
     272,   274,   288,   289,   292,   293,   297,   298,   299,   312,
     322,   323,   336,   337,   338,   343,   353,   364,   341,   392,
     391,   402,   401,   412,   424,   411,   452,   452,   455,   469,
     476,   485,   506,   516,   515,   528,   533
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const lnd_yytname[] =
{
  "$end", "error", "$undefined", "VAR", "CONS", "INTCONS",
  "VARIABLEPARANT", "TITLE", "INF", "FRE", "SEC_SLB", "SEC_SUB", "SEC_INT",
  "TOK_SIGN", "RE_OPEQ", "RE_OPLE", "RE_OPGE", "MINIMISE", "MAXIMISE",
  "SUBJECTTO", "END", "UNDEFINED", "$accept", "EMPTY", "inputfile", "@1",
  "objective_function", "of", "@2", "real_of", "x_constraints", "@3",
  "constraints", "constraint", "@4", "real_constraint", "@5",
  "x_lineair_sum", "lineair_sum", "lineair_term", "@6", "RE_OP",
  "cons_term", "optionals", "x_optionals", "optional", "title",
  "optional_title", "bound", "boundFR", "@7", "@8", "@9", "boundSLB",
  "@10", "boundSUB", "@11", "boundSB", "@12", "@13", "REALCONS",
  "RHS_STORE", "x_SIGN", "VAR_STORE", "ONEVARIABLE", "int_declaration",
  "@14", "VARIABLE", "end", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const lnd_yytype_uint16 lnd_yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const lnd_yytype_uint8 lnd_yyr1[] =
{
       0,    22,    23,    25,    24,    26,    26,    27,    28,    27,
      29,    31,    30,    32,    32,    33,    34,    33,    36,    35,
      37,    37,    38,    38,    40,    39,    39,    41,    41,    41,
      42,    42,    43,    43,    44,    44,    45,    45,    45,    46,
      47,    47,    48,    48,    48,    50,    51,    52,    49,    54,
      53,    56,    55,    58,    59,    57,    60,    60,    61,    62,
      62,    63,    64,    66,    65,    67,    68
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const lnd_yytype_uint8 lnd_yyr2[] =
{
       0,     2,     0,     0,     6,     2,     2,     1,     0,     3,
       1,     0,     3,     1,     2,     1,     0,     3,     0,     5,
       1,     1,     1,     2,     0,     4,     4,     1,     1,     1,
       2,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     0,     0,     8,     0,
       3,     0,     3,     0,     0,     7,     1,     1,     1,     1,
       1,     1,     1,     0,     3,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const lnd_yytype_uint8 lnd_yydefact[] =
{
       3,     0,     2,     1,    39,    40,    41,     0,     2,     2,
       0,     8,    60,    20,     6,     7,    10,    21,    22,     0,
       5,    11,     0,     2,    59,    23,    65,    57,    56,     0,
      24,     2,    66,     2,     9,     2,     2,    16,     2,    13,
      15,     0,     0,    49,    51,    63,    32,     4,    33,    34,
      36,    37,    42,    43,    44,    38,    61,    26,    25,     2,
      14,    27,    28,    29,    18,    45,     0,     0,     0,    35,
      17,     2,     2,    50,    53,    52,    64,    62,    31,     2,
       0,    46,     2,    58,    19,    30,     2,     2,    47,     0,
       2,    54,    48,     2,    55
};

/* YYDEFGOTO[NTERM-NUM].  */
static const lnd_yytype_int8 lnd_yydefgoto[] =
{
      -1,    13,     1,     2,    10,    14,    23,    15,    22,    31,
      38,    39,    59,    40,    71,    16,    17,    18,    36,    64,
      79,    47,    48,    49,    50,     7,    51,    52,    72,    86,
      90,    53,    66,    54,    67,    73,    82,    93,    29,    84,
      19,    57,    76,    55,    68,    74,    33
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -69
static const lnd_yytype_int8 lnd_yypact[] =
{
     -69,     4,    19,   -69,   -69,   -69,   -69,    29,    -1,    -1,
      10,   -69,   -69,    40,   -69,   -69,   -69,     5,   -69,    48,
     -69,   -69,    12,    23,   -69,   -69,   -69,   -69,   -69,    46,
     -69,    15,   -69,    30,   -69,   -69,   -69,   -69,     0,   -69,
     -69,    41,    46,   -69,   -69,   -69,   -69,   -69,    30,   -69,
     -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,    23,
     -69,   -69,   -69,   -69,   -69,   -69,    46,    46,    46,   -69,
     -69,     9,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,
      54,   -69,   -69,   -69,   -69,   -69,   -69,    23,   -69,    54,
     -69,   -69,   -69,   -69,   -69
};

/* YYPGOTO[NTERM-NUM].  */
static const lnd_yytype_int8 lnd_yypgoto[] =
{
     -69,    -2,   -69,   -69,   -69,    45,   -69,    37,   -69,   -69,
     -69,    24,   -69,     2,   -69,   -24,   -69,    47,   -69,   -69,
     -69,   -69,   -69,    17,    61,   -69,   -69,   -69,   -69,   -69,
     -69,   -69,   -69,   -69,   -69,     1,   -69,   -69,   -64,   -63,
     -68,   -34,   -69,   -69,   -69,   -18,   -69
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -60
static const lnd_yytype_int8 lnd_yytable[] =
{
       5,    30,    58,    80,     3,    11,    37,    41,    -2,    -2,
      -2,    35,    12,    12,    41,    24,    85,    78,    12,    89,
     -12,    37,    12,    88,    65,    91,     4,    92,    12,    21,
      94,    46,    32,    56,    56,    41,    12,     4,    81,    42,
      43,    44,    45,   -59,   -59,   -59,     8,     9,    87,    26,
      77,    26,    27,    28,    20,    61,    62,    63,    27,    28,
      34,    70,    60,     6,    25,    69,     0,     0,    75,    24,
      56,     0,     0,     0,     0,     0,     0,    83,     0,     0,
      56,     0,     0,     0,    83,    24,     0,     0,    83,     0,
       0,    83
};

static const lnd_yytype_int8 lnd_yycheck[] =
{
       2,    19,    36,    71,     0,     6,     6,    31,     3,     4,
       5,    29,    13,    13,    38,    17,    80,     8,    13,    87,
      20,     6,    13,    86,    42,    89,     7,    90,    13,    19,
      93,    33,    20,    35,    36,    59,    13,     7,    72,     9,
      10,    11,    12,     3,     4,     5,    17,    18,    82,     3,
      68,     3,     4,     5,     9,    14,    15,    16,     4,     5,
      23,    59,    38,     2,    17,    48,    -1,    -1,    67,    71,
      72,    -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,    -1,
      82,    -1,    -1,    -1,    86,    87,    -1,    -1,    90,    -1,
      -1,    93
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const lnd_yytype_uint8 lnd_yystos[] =
{
       0,    24,    25,     0,     7,    23,    46,    47,    17,    18,
      26,     6,    13,    23,    27,    29,    37,    38,    39,    62,
      27,    19,    30,    28,    23,    39,     3,     4,     5,    60,
      67,    31,    20,    68,    29,    67,    40,     6,    32,    33,
      35,    37,     9,    10,    11,    12,    23,    43,    44,    45,
      46,    48,    49,    53,    55,    65,    23,    63,    63,    34,
      33,    14,    15,    16,    41,    67,    54,    56,    66,    45,
      35,    36,    50,    57,    67,    57,    64,    67,     8,    42,
      62,    63,    58,    23,    61,    60,    51,    63,    61,    62,
      52,    60,    61,    59,    61
};

#define lnd_yyerrok		(lnd_yyerrstatus = 0)
#define lnd_yyclearin	(lnd_yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto lnd_yyacceptlab
#define YYABORT		goto lnd_yyabortlab
#define YYERROR		goto lnd_yyerrorlab


/* Like YYERROR except do call lnd_yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto lnd_yyerrlab

#define YYRECOVERING()  (!!lnd_yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (lnd_yychar == YYEMPTY && lnd_yylen == 1)				\
    {								\
      lnd_yychar = (Token);						\
      lnd_yylval = (Value);						\
      lnd_yytoken = YYTRANSLATE (lnd_yychar);				\
      YYPOPSTACK (1);						\
      goto lnd_yybackup;						\
    }								\
  else								\
    {								\
      lnd_yyerror (parm, scanner, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `lnd_yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX lnd_yylex (&lnd_yylval, YYLEX_PARAM)
#else
# define YYLEX lnd_yylex (&lnd_yylval, scanner)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (lnd_yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (lnd_yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      lnd_yy_symbol_print (stderr,						  \
		  Type, Value, parm, scanner); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
lnd_yy_symbol_value_print (FILE *lnd_yyoutput, int lnd_yytype, YYSTYPE const * const lnd_yyvaluep, parse_parm *parm, void *scanner)
#else
static void
lnd_yy_symbol_value_print (lnd_yyoutput, lnd_yytype, lnd_yyvaluep, parm, scanner)
    FILE *lnd_yyoutput;
    int lnd_yytype;
    YYSTYPE const * const lnd_yyvaluep;
    parse_parm *parm;
    void *scanner;
#endif
{
  if (!lnd_yyvaluep)
    return;
  YYUSE (parm);
  YYUSE (scanner);
# ifdef YYPRINT
  if (lnd_yytype < YYNTOKENS)
    YYPRINT (lnd_yyoutput, lnd_yytoknum[lnd_yytype], *lnd_yyvaluep);
# else
  YYUSE (lnd_yyoutput);
# endif
  switch (lnd_yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
lnd_yy_symbol_print (FILE *lnd_yyoutput, int lnd_yytype, YYSTYPE const * const lnd_yyvaluep, parse_parm *parm, void *scanner)
#else
static void
lnd_yy_symbol_print (lnd_yyoutput, lnd_yytype, lnd_yyvaluep, parm, scanner)
    FILE *lnd_yyoutput;
    int lnd_yytype;
    YYSTYPE const * const lnd_yyvaluep;
    parse_parm *parm;
    void *scanner;
#endif
{
  if (lnd_yytype < YYNTOKENS)
    YYFPRINTF (lnd_yyoutput, "token %s (", lnd_yytname[lnd_yytype]);
  else
    YYFPRINTF (lnd_yyoutput, "nterm %s (", lnd_yytname[lnd_yytype]);

  lnd_yy_symbol_value_print (lnd_yyoutput, lnd_yytype, lnd_yyvaluep, parm, scanner);
  YYFPRINTF (lnd_yyoutput, ")");
}

/*------------------------------------------------------------------.
| lnd_yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
lnd_yy_stack_print (lnd_yytype_int16 *bottom, lnd_yytype_int16 *top)
#else
static void
lnd_yy_stack_print (bottom, top)
    lnd_yytype_int16 *bottom;
    lnd_yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (lnd_yydebug)							\
    lnd_yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
lnd_yy_reduce_print (YYSTYPE *lnd_yyvsp, int lnd_yyrule, parse_parm *parm, void *scanner)
#else
static void
lnd_yy_reduce_print (lnd_yyvsp, lnd_yyrule, parm, scanner)
    YYSTYPE *lnd_yyvsp;
    int lnd_yyrule;
    parse_parm *parm;
    void *scanner;
#endif
{
  int lnd_yynrhs = lnd_yyr2[lnd_yyrule];
  int lnd_yyi;
  unsigned long int lnd_yylno = lnd_yyrline[lnd_yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     lnd_yyrule - 1, lnd_yylno);
  /* The symbols being reduced.  */
  for (lnd_yyi = 0; lnd_yyi < lnd_yynrhs; lnd_yyi++)
    {
      fprintf (stderr, "   $%d = ", lnd_yyi + 1);
      lnd_yy_symbol_print (stderr, lnd_yyrhs[lnd_yyprhs[lnd_yyrule] + lnd_yyi],
		       &(lnd_yyvsp[(lnd_yyi + 1) - (lnd_yynrhs)])
		       		       , parm, scanner);
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (lnd_yydebug)				\
    lnd_yy_reduce_print (lnd_yyvsp, Rule, parm, scanner); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int lnd_yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef lnd_yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define lnd_yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
lnd_yystrlen (const char *lnd_yystr)
#else
static YYSIZE_T
lnd_yystrlen (lnd_yystr)
    const char *lnd_yystr;
#endif
{
  YYSIZE_T lnd_yylen;
  for (lnd_yylen = 0; lnd_yystr[lnd_yylen]; lnd_yylen++)
    continue;
  return lnd_yylen;
}
#  endif
# endif

# ifndef lnd_yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define lnd_yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
lnd_yystpcpy (char *lnd_yydest, const char *lnd_yysrc)
#else
static char *
lnd_yystpcpy (lnd_yydest, lnd_yysrc)
    char *lnd_yydest;
    const char *lnd_yysrc;
#endif
{
  char *lnd_yyd = lnd_yydest;
  const char *lnd_yys = lnd_yysrc;

  while ((*lnd_yyd++ = *lnd_yys++) != '\0')
    continue;

  return lnd_yyd - 1;
}
#  endif
# endif

# ifndef lnd_yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for lnd_yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from lnd_yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
lnd_yytnamerr (char *lnd_yyres, const char *lnd_yystr)
{
  if (*lnd_yystr == '"')
    {
      YYSIZE_T lnd_yyn = 0;
      char const *lnd_yyp = lnd_yystr;

      for (;;)
	switch (*++lnd_yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++lnd_yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (lnd_yyres)
	      lnd_yyres[lnd_yyn] = *lnd_yyp;
	    lnd_yyn++;
	    break;

	  case '"':
	    if (lnd_yyres)
	      lnd_yyres[lnd_yyn] = '\0';
	    return lnd_yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! lnd_yyres)
    return lnd_yystrlen (lnd_yystr);

  return lnd_yystpcpy (lnd_yyres, lnd_yystr) - lnd_yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
lnd_yysyntax_error (char *lnd_yyresult, int lnd_yystate, int lnd_yychar)
{
  int lnd_yyn = lnd_yypact[lnd_yystate];

  if (! (YYPACT_NINF < lnd_yyn && lnd_yyn <= YYLAST))
    return 0;
  else
    {
      int lnd_yytype = YYTRANSLATE (lnd_yychar);
      YYSIZE_T lnd_yysize0 = lnd_yytnamerr (0, lnd_yytname[lnd_yytype]);
      YYSIZE_T lnd_yysize = lnd_yysize0;
      YYSIZE_T lnd_yysize1;
      int lnd_yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *lnd_yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int lnd_yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *lnd_yyfmt;
      char const *lnd_yyf;
      static char const lnd_yyunexpected[] = "syntax error, unexpected %s";
      static char const lnd_yyexpecting[] = ", expecting %s";
      static char const lnd_yyor[] = " or %s";
      char lnd_yyformat[sizeof lnd_yyunexpected
		    + sizeof lnd_yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof lnd_yyor - 1))];
      char const *lnd_yyprefix = lnd_yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int lnd_yyxbegin = lnd_yyn < 0 ? -lnd_yyn : 0;

      /* Stay within bounds of both lnd_yycheck and lnd_yytname.  */
      int lnd_yychecklim = YYLAST - lnd_yyn + 1;
      int lnd_yyxend = lnd_yychecklim < YYNTOKENS ? lnd_yychecklim : YYNTOKENS;
      int lnd_yycount = 1;

      lnd_yyarg[0] = lnd_yytname[lnd_yytype];
      lnd_yyfmt = lnd_yystpcpy (lnd_yyformat, lnd_yyunexpected);

      for (lnd_yyx = lnd_yyxbegin; lnd_yyx < lnd_yyxend; ++lnd_yyx)
	if (lnd_yycheck[lnd_yyx + lnd_yyn] == lnd_yyx && lnd_yyx != YYTERROR)
	  {
	    if (lnd_yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		lnd_yycount = 1;
		lnd_yysize = lnd_yysize0;
		lnd_yyformat[sizeof lnd_yyunexpected - 1] = '\0';
		break;
	      }
	    lnd_yyarg[lnd_yycount++] = lnd_yytname[lnd_yyx];
	    lnd_yysize1 = lnd_yysize + lnd_yytnamerr (0, lnd_yytname[lnd_yyx]);
	    lnd_yysize_overflow |= (lnd_yysize1 < lnd_yysize);
	    lnd_yysize = lnd_yysize1;
	    lnd_yyfmt = lnd_yystpcpy (lnd_yyfmt, lnd_yyprefix);
	    lnd_yyprefix = lnd_yyor;
	  }

      lnd_yyf = YY_(lnd_yyformat);
      lnd_yysize1 = lnd_yysize + lnd_yystrlen (lnd_yyf);
      lnd_yysize_overflow |= (lnd_yysize1 < lnd_yysize);
      lnd_yysize = lnd_yysize1;

      if (lnd_yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (lnd_yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *lnd_yyp = lnd_yyresult;
	  int lnd_yyi = 0;
	  while ((*lnd_yyp = *lnd_yyf) != '\0')
	    {
	      if (*lnd_yyp == '%' && lnd_yyf[1] == 's' && lnd_yyi < lnd_yycount)
		{
		  lnd_yyp += lnd_yytnamerr (lnd_yyp, lnd_yyarg[lnd_yyi++]);
		  lnd_yyf += 2;
		}
	      else
		{
		  lnd_yyp++;
		  lnd_yyf++;
		}
	    }
	}
      return lnd_yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
lnd_yydestruct (const char *lnd_yymsg, int lnd_yytype, YYSTYPE *lnd_yyvaluep, parse_parm *parm, void *scanner)
#else
static void
lnd_yydestruct (lnd_yymsg, lnd_yytype, lnd_yyvaluep, parm, scanner)
    const char *lnd_yymsg;
    int lnd_yytype;
    YYSTYPE *lnd_yyvaluep;
    parse_parm *parm;
    void *scanner;
#endif
{
  YYUSE (lnd_yyvaluep);
  YYUSE (parm);
  YYUSE (scanner);

  if (!lnd_yymsg)
    lnd_yymsg = "Deleting";
  YY_SYMBOL_PRINT (lnd_yymsg, lnd_yytype, lnd_yyvaluep, lnd_yylocationp);

  switch (lnd_yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int lnd_yyparse (void *YYPARSE_PARAM);
#else
int lnd_yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int lnd_yyparse (parse_parm *parm, void *scanner);
#else
int lnd_yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */






/*----------.
| lnd_yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
lnd_yyparse (void *YYPARSE_PARAM)
#else
int
lnd_yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
lnd_yyparse (parse_parm *parm, void *scanner)
#else
int
lnd_yyparse (parm, scanner)
    parse_parm *parm;
    void *scanner;
#endif
#endif
{
  /* The look-ahead symbol.  */
int lnd_yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE lnd_yylval;

/* Number of syntax errors so far.  */
int lnd_yynerrs;

  int lnd_yystate;
  int lnd_yyn;
  int lnd_yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int lnd_yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int lnd_yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char lnd_yymsgbuf[128];
  char *lnd_yymsg = lnd_yymsgbuf;
  YYSIZE_T lnd_yymsg_alloc = sizeof lnd_yymsgbuf;
#endif

  /* Three stacks and their tools:
     `lnd_yyss': related to states,
     `lnd_yyvs': related to semantic values,
     `lnd_yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow lnd_yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  lnd_yytype_int16 lnd_yyssa[YYINITDEPTH];
  lnd_yytype_int16 *lnd_yyss = lnd_yyssa;
  lnd_yytype_int16 *lnd_yyssp;

  /* The semantic value stack.  */
  YYSTYPE lnd_yyvsa[YYINITDEPTH];
  YYSTYPE *lnd_yyvs = lnd_yyvsa;
  YYSTYPE *lnd_yyvsp;



#define YYPOPSTACK(N)   (lnd_yyvsp -= (N), lnd_yyssp -= (N))

  YYSIZE_T lnd_yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE lnd_yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int lnd_yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  lnd_yystate = 0;
  lnd_yyerrstatus = 0;
  lnd_yynerrs = 0;
  lnd_yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  lnd_yyssp = lnd_yyss;
  lnd_yyvsp = lnd_yyvs;

  goto lnd_yysetstate;

/*------------------------------------------------------------.
| lnd_yynewstate -- Push a new state, which is found in lnd_yystate.  |
`------------------------------------------------------------*/
 lnd_yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  lnd_yyssp++;

 lnd_yysetstate:
  *lnd_yyssp = lnd_yystate;

  if (lnd_yyss + lnd_yystacksize - 1 <= lnd_yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T lnd_yysize = lnd_yyssp - lnd_yyss + 1;

#ifdef lnd_yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *lnd_yyvs1 = lnd_yyvs;
	lnd_yytype_int16 *lnd_yyss1 = lnd_yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if lnd_yyoverflow is a macro.  */
	lnd_yyoverflow (YY_("memory exhausted"),
		    &lnd_yyss1, lnd_yysize * sizeof (*lnd_yyssp),
		    &lnd_yyvs1, lnd_yysize * sizeof (*lnd_yyvsp),

		    &lnd_yystacksize);

	lnd_yyss = lnd_yyss1;
	lnd_yyvs = lnd_yyvs1;
      }
#else /* no lnd_yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto lnd_yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= lnd_yystacksize)
	goto lnd_yyexhaustedlab;
      lnd_yystacksize *= 2;
      if (YYMAXDEPTH < lnd_yystacksize)
	lnd_yystacksize = YYMAXDEPTH;

      {
	lnd_yytype_int16 *lnd_yyss1 = lnd_yyss;
	union lnd_yyalloc *lnd_yyptr =
	  (union lnd_yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (lnd_yystacksize));
	if (! lnd_yyptr)
	  goto lnd_yyexhaustedlab;
	YYSTACK_RELOCATE (lnd_yyss);
	YYSTACK_RELOCATE (lnd_yyvs);

#  undef YYSTACK_RELOCATE
	if (lnd_yyss1 != lnd_yyssa)
	  YYSTACK_FREE (lnd_yyss1);
      }
# endif
#endif /* no lnd_yyoverflow */

      lnd_yyssp = lnd_yyss + lnd_yysize - 1;
      lnd_yyvsp = lnd_yyvs + lnd_yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) lnd_yystacksize));

      if (lnd_yyss + lnd_yystacksize - 1 <= lnd_yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", lnd_yystate));

  goto lnd_yybackup;

/*-----------.
| lnd_yybackup.  |
`-----------*/
lnd_yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  lnd_yyn = lnd_yypact[lnd_yystate];
  if (lnd_yyn == YYPACT_NINF)
    goto lnd_yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (lnd_yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      lnd_yychar = YYLEX;
    }

  if (lnd_yychar <= YYEOF)
    {
      lnd_yychar = lnd_yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      lnd_yytoken = YYTRANSLATE (lnd_yychar);
      YY_SYMBOL_PRINT ("Next token is", lnd_yytoken, &lnd_yylval, &lnd_yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  lnd_yyn += lnd_yytoken;
  if (lnd_yyn < 0 || YYLAST < lnd_yyn || lnd_yycheck[lnd_yyn] != lnd_yytoken)
    goto lnd_yydefault;
  lnd_yyn = lnd_yytable[lnd_yyn];
  if (lnd_yyn <= 0)
    {
      if (lnd_yyn == 0 || lnd_yyn == YYTABLE_NINF)
	goto lnd_yyerrlab;
      lnd_yyn = -lnd_yyn;
      goto lnd_yyreduce;
    }

  if (lnd_yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (lnd_yyerrstatus)
    lnd_yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", lnd_yytoken, &lnd_yylval, &lnd_yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (lnd_yychar != YYEOF)
    lnd_yychar = YYEMPTY;

  lnd_yystate = lnd_yyn;
  *++lnd_yyvsp = lnd_yylval;

  goto lnd_yynewstate;


/*-----------------------------------------------------------.
| lnd_yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
lnd_yydefault:
  lnd_yyn = lnd_yydefact[lnd_yystate];
  if (lnd_yyn == 0)
    goto lnd_yyerrlab;
  goto lnd_yyreduce;


/*-----------------------------.
| lnd_yyreduce -- Do a reduction.  |
`-----------------------------*/
lnd_yyreduce:
  /* lnd_yyn is the number of a rule to reduce with.  */
  lnd_yylen = lnd_yyr2[lnd_yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  lnd_yyval = lnd_yyvsp[1-lnd_yylen];


  YY_REDUCE_PRINT (lnd_yyn);
  switch (lnd_yyn)
    {
        case 3:

    {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->isign = 0;
  pv->make_neg = 0;
  pv->Sign = 0;
  pv->HadConstraint = FALSE;
  pv->HadVar = FALSE;
}
    break;

  case 5:

    {
  set_obj_dir(PARM, TRUE);
}
    break;

  case 6:

    {
  set_obj_dir(PARM, FALSE);
}
    break;

  case 8:

    {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if(!add_constraint_name(pp, pv->Last_var))
    YYABORT;
  /* pv->HadConstraint = TRUE; */
}
    break;

  case 10:

    {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  add_row(pp);
  /* pv->HadConstraint = FALSE; */
  pv->HadVar = FALSE;
  pv->isign = 0;
  pv->make_neg = 0;
}
    break;

  case 11:

    { /* SUBJECTTO */
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->HadConstraint = TRUE;
}
    break;

  case 12:

    {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->HadConstraint = FALSE;
}
    break;

  case 16:

    { /* constraint */
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if(!add_constraint_name(pp, pv->Last_var))
    YYABORT;
  /* pv->HadConstraint = TRUE; */
}
    break;

  case 18:

    { /* real_constraint 1 */
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if(!store_re_op(pp, pv->OP, pv->HadConstraint, pv->HadVar, pv->Had_lineair_sum))
    YYABORT;
  pv->make_neg = 1;
}
    break;

  case 19:

    { /* real_constraint 2 */
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->Had_lineair_sum = TRUE;
  add_row(pp);
  /* pv->HadConstraint = FALSE; */
  pv->HadVar = FALSE;
  pv->isign = 0;
  pv->make_neg = 0;
  null_tmp_store(pp, TRUE);
}
    break;

  case 20:

    {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->HadConstraint = pv->HadVar = TRUE;
}
    break;

  case 24:

    {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->f = 1.0;
}
    break;

  case 31:

    {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->isign = pv->Sign;
}
    break;

  case 39:

    { /* title */
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if(!set_title(pp, pv->title))
    YYABORT;
}
    break;

  case 45:

    {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->isign = 0;
  pv->make_neg = 0;
  pv->Sign = 0;
  pv->f = 1;
}
    break;

  case 46:

    {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if(!store_re_op(pp, '>', pv->HadConstraint, pv->HadVar, pv->Had_lineair_sum))
    YYABORT;
  pv->make_neg = 1;
  pv->isign = 0;
  pv->f = -DEF_INFINITE;
}
    break;

  case 47:

    {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if(!store_bounds(pp, FALSE))
    YYABORT;

  if(!store_re_op(pp, '<', pv->HadConstraint, pv->HadVar, pv->Had_lineair_sum))
    YYABORT;
  pv->f = DEF_INFINITE;
  pv->isign = 0;
}
    break;

  case 48:

    {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if(!store_bounds(pp, FALSE))
    YYABORT;
  /* pv->HadConstraint = FALSE; */
  pv->HadVar = FALSE;
  pv->isign = 0;
  pv->make_neg = 0;
  null_tmp_store(pp, TRUE);
}
    break;

  case 49:

    {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->TypeBound = '>';
}
    break;

  case 51:

    {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->TypeBound = '<';
}
    break;

  case 53:

    { /* boundSB 1 */
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->isign = 0;
  pv->make_neg = 0;
  pv->Sign = 0;
  pv->f = 1;
}
    break;

  case 54:

    { /* boundSB 2 */
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if(!store_re_op(pp, pv->TypeBound, pv->HadConstraint, pv->HadVar, pv->Had_lineair_sum))
    YYABORT;
  pv->make_neg = 1;
  /* pv->isign = 0; */
}
    break;

  case 55:

    { /* boundSB 3 */
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if(!store_bounds(pp, FALSE))
    YYABORT;
  /* pv->HadConstraint = FALSE; */
  pv->HadVar = FALSE;
  pv->isign = 0;
  pv->make_neg = 0;
  null_tmp_store(pp, TRUE);
}
    break;

  case 58:

    {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if (    (pv->isign || !pv->make_neg)
      && !(pv->isign && !pv->make_neg)) /* but not both! */
    pv->f = -pv->f;
  if(!rhs_store(pp, pv->f, pv->HadConstraint, pv->HadVar, pv->Had_lineair_sum))
    YYABORT;
  pv->isign = 0;
}
    break;

  case 59:

    {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->isign = 0;
}
    break;

  case 60:

    {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->isign = pv->Sign;
}
    break;

  case 61:

    {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if (    (pv->isign || pv->make_neg)
      && !(pv->isign && pv->make_neg)) /* but not both! */
    pv->f = -pv->f;
  if(!var_store(pp, pv->Last_var, pv->f, pv->HadConstraint, pv->HadVar, pv->Had_lineair_sum)) {
    lnd_yyerror(pp, pp->scanner, "var_store failed");
    YYABORT;
  }
  /* pv->HadConstraint |= pv->HadVar; */
  pv->HadVar = TRUE;
  pv->isign = 0;
}
    break;

  case 62:

    {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  storevarandweight(pp, pv->Last_var);
}
    break;

  case 63:

    {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  check_int_sec_sos_free_decl(pp, pv->Within_gen_decl ? 1 : pv->Within_bin_decl ? 2 : 0, 0, 0, 0);
}
    break;

  case 66:

    {
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->Had_lineair_sum = FALSE;
}
    break;


/* Line 1267 of yacc.c.  */

      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", lnd_yyr1[lnd_yyn], &lnd_yyval, &lnd_yyloc);

  YYPOPSTACK (lnd_yylen);
  lnd_yylen = 0;
  YY_STACK_PRINT (lnd_yyss, lnd_yyssp);

  *++lnd_yyvsp = lnd_yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  lnd_yyn = lnd_yyr1[lnd_yyn];

  lnd_yystate = lnd_yypgoto[lnd_yyn - YYNTOKENS] + *lnd_yyssp;
  if (0 <= lnd_yystate && lnd_yystate <= YYLAST && lnd_yycheck[lnd_yystate] == *lnd_yyssp)
    lnd_yystate = lnd_yytable[lnd_yystate];
  else
    lnd_yystate = lnd_yydefgoto[lnd_yyn - YYNTOKENS];

  goto lnd_yynewstate;


/*------------------------------------.
| lnd_yyerrlab -- here on detecting error |
`------------------------------------*/
lnd_yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!lnd_yyerrstatus)
    {
      ++lnd_yynerrs;
#if ! YYERROR_VERBOSE
      lnd_yyerror (parm, scanner, YY_("syntax error"));
#else
      {
	YYSIZE_T lnd_yysize = lnd_yysyntax_error (0, lnd_yystate, lnd_yychar);
	if (lnd_yymsg_alloc < lnd_yysize && lnd_yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T lnd_yyalloc = 2 * lnd_yysize;
	    if (! (lnd_yysize <= lnd_yyalloc && lnd_yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      lnd_yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (lnd_yymsg != lnd_yymsgbuf)
	      YYSTACK_FREE (lnd_yymsg);
	    lnd_yymsg = (char *) YYSTACK_ALLOC (lnd_yyalloc);
	    if (lnd_yymsg)
	      lnd_yymsg_alloc = lnd_yyalloc;
	    else
	      {
		lnd_yymsg = lnd_yymsgbuf;
		lnd_yymsg_alloc = sizeof lnd_yymsgbuf;
	      }
	  }

	if (0 < lnd_yysize && lnd_yysize <= lnd_yymsg_alloc)
	  {
	    (void) lnd_yysyntax_error (lnd_yymsg, lnd_yystate, lnd_yychar);
	    lnd_yyerror (parm, scanner, lnd_yymsg);
	  }
	else
	  {
	    lnd_yyerror (parm, scanner, YY_("syntax error"));
	    if (lnd_yysize != 0)
	      goto lnd_yyexhaustedlab;
	  }
      }
#endif
    }



  if (lnd_yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (lnd_yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (lnd_yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  lnd_yydestruct ("Error: discarding",
		      lnd_yytoken, &lnd_yylval, parm, scanner);
	  lnd_yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto lnd_yyerrlab1;


/*---------------------------------------------------.
| lnd_yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
lnd_yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label lnd_yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto lnd_yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (lnd_yylen);
  lnd_yylen = 0;
  YY_STACK_PRINT (lnd_yyss, lnd_yyssp);
  lnd_yystate = *lnd_yyssp;
  goto lnd_yyerrlab1;


/*-------------------------------------------------------------.
| lnd_yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
lnd_yyerrlab1:
  lnd_yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      lnd_yyn = lnd_yypact[lnd_yystate];
      if (lnd_yyn != YYPACT_NINF)
	{
	  lnd_yyn += YYTERROR;
	  if (0 <= lnd_yyn && lnd_yyn <= YYLAST && lnd_yycheck[lnd_yyn] == YYTERROR)
	    {
	      lnd_yyn = lnd_yytable[lnd_yyn];
	      if (0 < lnd_yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (lnd_yyssp == lnd_yyss)
	YYABORT;


      lnd_yydestruct ("Error: popping",
		  lnd_yystos[lnd_yystate], lnd_yyvsp, parm, scanner);
      YYPOPSTACK (1);
      lnd_yystate = *lnd_yyssp;
      YY_STACK_PRINT (lnd_yyss, lnd_yyssp);
    }

  if (lnd_yyn == YYFINAL)
    YYACCEPT;

  *++lnd_yyvsp = lnd_yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", lnd_yystos[lnd_yyn], lnd_yyvsp, lnd_yylsp);

  lnd_yystate = lnd_yyn;
  goto lnd_yynewstate;


/*-------------------------------------.
| lnd_yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
lnd_yyacceptlab:
  lnd_yyresult = 0;
  goto lnd_yyreturn;

/*-----------------------------------.
| lnd_yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
lnd_yyabortlab:
  lnd_yyresult = 1;
  goto lnd_yyreturn;

#ifndef lnd_yyoverflow
/*-------------------------------------------------.
| lnd_yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
lnd_yyexhaustedlab:
  lnd_yyerror (parm, scanner, YY_("memory exhausted"));
  lnd_yyresult = 2;
  /* Fall through.  */
#endif

lnd_yyreturn:
  if (lnd_yychar != YYEOF && lnd_yychar != YYEMPTY)
     lnd_yydestruct ("Cleanup: discarding lookahead",
		 lnd_yytoken, &lnd_yylval, parm, scanner);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (lnd_yylen);
  YY_STACK_PRINT (lnd_yyss, lnd_yyssp);
  while (lnd_yyssp != lnd_yyss)
    {
      lnd_yydestruct ("Cleanup: popping",
		  lnd_yystos[*lnd_yyssp], lnd_yyvsp, parm, scanner);
      YYPOPSTACK (1);
    }
#ifndef lnd_yyoverflow
  if (lnd_yyss != lnd_yyssa)
    YYSTACK_FREE (lnd_yyss);
#endif
#if YYERROR_VERBOSE
  if (lnd_yymsg != lnd_yymsgbuf)
    YYSTACK_FREE (lnd_yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (lnd_yyresult);
}





static void lnd_yy_delete_allocated_memory(parse_parm *pp)
{
  parse_vars *pv = (parse_vars *) pp->parse_vars;
  /* free memory allocated by flex. Otherwise some memory is not freed.
     This is a bit tricky. There is not much documentation about this, but a lot of
     reports of memory that keeps allocated */

  /* If you get errors on this function call, just comment it. This will only result
     in some memory that is not being freed. */

# if defined YY_CURRENT_BUFFER
    /* flex defines the macro YY_CURRENT_BUFFER, so you should only get here if lp_rlp.h is
       generated by flex */
    /* lex doesn't define this macro and thus should not come here, but lex doesn't has
       this memory leak also ...*/

#  if 0
    /* older versions of flex */
    lnd_yy_delete_buffer(YY_CURRENT_BUFFER); /* comment this line if you have problems with it */
    lnd_yy_init = 1; /* make sure that the next time memory is allocated again */
    lnd_yy_start = 0;
#  else
    /* As of version 2.5.9 Flex  */
    lnd_yylex_destroy(pp->scanner); /* comment this line if you have problems with it */
#  endif
# endif

  FREE(pv->Last_var);
}

static int parse(parse_parm *pp)
{
  return(lnd_yyparse(pp, pp->scanner));
}

lprec *read_lndex(lprec *lp, FILE *filename, int verbose, char *lp_name)
{
  parse_vars *pv;
  lprec *lp1 = NULL;

  CALLOC(pv, 1, parse_vars);
  if (pv != NULL) {
    parse_parm pp;

    memset(&pp, 0, sizeof(pp));
    pp.parse_vars = (void *) pv;

    lnd_yylex_init(&pp.scanner);
    lnd_yyset_extra(&pp, pp.scanner);

    lnd_yyset_in((FILE *) filename, pp.scanner);
    lnd_yyset_out(NULL, pp.scanner);

    lp1 = yacc_read(lp, verbose, lp_name, parse, &pp, lnd_yy_delete_allocated_memory);
    FREE(pv);
  }
  return(lp1);
}

lprec * __WINAPI read_lnd(FILE *filename, int verbose, char *lp_name)
{
  return(read_lndex(NULL, filename, verbose, lp_name));
}

lprec *read_LNDex(lprec *lp, char *filename, int verbose, char *lp_name)
{
  FILE *fpin;

  if((fpin = fopen(filename, "r")) != NULL) {
    lp = read_lndex(lp, fpin, verbose, lp_name);
    fclose(fpin);
  }
  else
    lp = NULL;
  return(lp);
}

lprec * __WINAPI read_LND(char *filename, int verbose, char *lp_name)
{
  return(read_LNDex(NULL, filename, verbose, lp_name));
}

