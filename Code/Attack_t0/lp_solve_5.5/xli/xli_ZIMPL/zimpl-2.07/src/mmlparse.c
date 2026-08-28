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

/* All symbols defined below should begin with yy or YY, to avoid
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
   enum yytokentype {
     DECLSET = 258,
     DECLPAR = 259,
     DECLVAR = 260,
     DECLMIN = 261,
     DECLMAX = 262,
     DECLSUB = 263,
     DECLSOS = 264,
     DEFNUMB = 265,
     DEFSTRG = 266,
     DEFBOOL = 267,
     DEFSET = 268,
     PRINT = 269,
     CHECK = 270,
     BINARY = 271,
     INTEGER = 272,
     REAL = 273,
     IMPLICIT = 274,
     ASGN = 275,
     DO = 276,
     WITH = 277,
     IN = 278,
     TO = 279,
     UNTIL = 280,
     BY = 281,
     FORALL = 282,
     EMPTY_TUPLE = 283,
     EMPTY_SET = 284,
     EXISTS = 285,
     PRIORITY = 286,
     STARTVAL = 287,
     DEFAULT = 288,
     CMP_LE = 289,
     CMP_GE = 290,
     CMP_EQ = 291,
     CMP_LT = 292,
     CMP_GT = 293,
     CMP_NE = 294,
     INFTY = 295,
     AND = 296,
     OR = 297,
     XOR = 298,
     NOT = 299,
     SUM = 300,
     MIN = 301,
     MAX = 302,
     ARGMIN = 303,
     ARGMAX = 304,
     PROD = 305,
     IF = 306,
     THEN = 307,
     ELSE = 308,
     END = 309,
     INTER = 310,
     UNION = 311,
     CROSS = 312,
     SYMDIFF = 313,
     WITHOUT = 314,
     PROJ = 315,
     MOD = 316,
     DIV = 317,
     POW = 318,
     FAC = 319,
     CARD = 320,
     ABS = 321,
     SGN = 322,
     FLOOR = 323,
     CEIL = 324,
     LOG = 325,
     LN = 326,
     EXP = 327,
     SQRT = 328,
     RANDOM = 329,
     ORD = 330,
     READ = 331,
     AS = 332,
     SKIP = 333,
     USE = 334,
     COMMENT = 335,
     MATCH = 336,
     SUBSETS = 337,
     INDEXSET = 338,
     POWERSET = 339,
     VIF = 340,
     VABS = 341,
     TYPE1 = 342,
     TYPE2 = 343,
     LENGTH = 344,
     SUBSTR = 345,
     NUMBSYM = 346,
     STRGSYM = 347,
     VARSYM = 348,
     SETSYM = 349,
     NUMBDEF = 350,
     STRGDEF = 351,
     BOOLDEF = 352,
     SETDEF = 353,
     DEFNAME = 354,
     NAME = 355,
     STRG = 356,
     NUMB = 357,
     SCALE = 358,
     SEPARATE = 359,
     UNARY = 360
   };
#endif
/* Tokens.  */
#define DECLSET 258
#define DECLPAR 259
#define DECLVAR 260
#define DECLMIN 261
#define DECLMAX 262
#define DECLSUB 263
#define DECLSOS 264
#define DEFNUMB 265
#define DEFSTRG 266
#define DEFBOOL 267
#define DEFSET 268
#define PRINT 269
#define CHECK 270
#define BINARY 271
#define INTEGER 272
#define REAL 273
#define IMPLICIT 274
#define ASGN 275
#define DO 276
#define WITH 277
#define IN 278
#define TO 279
#define UNTIL 280
#define BY 281
#define FORALL 282
#define EMPTY_TUPLE 283
#define EMPTY_SET 284
#define EXISTS 285
#define PRIORITY 286
#define STARTVAL 287
#define DEFAULT 288
#define CMP_LE 289
#define CMP_GE 290
#define CMP_EQ 291
#define CMP_LT 292
#define CMP_GT 293
#define CMP_NE 294
#define INFTY 295
#define AND 296
#define OR 297
#define XOR 298
#define NOT 299
#define SUM 300
#define MIN 301
#define MAX 302
#define ARGMIN 303
#define ARGMAX 304
#define PROD 305
#define IF 306
#define THEN 307
#define ELSE 308
#define END 309
#define INTER 310
#define UNION 311
#define CROSS 312
#define SYMDIFF 313
#define WITHOUT 314
#define PROJ 315
#define MOD 316
#define DIV 317
#define POW 318
#define FAC 319
#define CARD 320
#define ABS 321
#define SGN 322
#define FLOOR 323
#define CEIL 324
#define LOG 325
#define LN 326
#define EXP 327
#define SQRT 328
#define RANDOM 329
#define ORD 330
#define READ 331
#define AS 332
#define SKIP 333
#define USE 334
#define COMMENT 335
#define MATCH 336
#define SUBSETS 337
#define INDEXSET 338
#define POWERSET 339
#define VIF 340
#define VABS 341
#define TYPE1 342
#define TYPE2 343
#define LENGTH 344
#define SUBSTR 345
#define NUMBSYM 346
#define STRGSYM 347
#define VARSYM 348
#define SETSYM 349
#define NUMBDEF 350
#define STRGDEF 351
#define BOOLDEF 352
#define SETDEF 353
#define DEFNAME 354
#define NAME 355
#define STRG 356
#define NUMB 357
#define SCALE 358
#define SEPARATE 359
#define UNARY 360




/* Copy the first part of user declarations.  */
#line 1 "src/mmlparse.y"

#pragma ident "@(#) $Id: mmlparse.y,v 1.85 2007/07/25 12:52:21 bzfkocht Exp $"
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*   File....: mmlparse.y                                                    */
/*   Name....: MML Parser                                                    */
/*   Author..: Thorsten Koch                                                 */
/*   Copyright by Author, All rights reserved                                */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*
 * Copyright (C) 2001 by Thorsten Koch <koch@zib.de>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */
/*lint -e428 -e514 -e525 -e527 -e537 -e568 -e574 -e659 -e661 -e662 -e676 -e685 */
/*lint -e713 -e717 -e732 -e734 -e737 -e744 -e750 -e751 -e753 -e762 -e764 -e778 */
/*lint -e810 -e818 -e830 */
/*lint -esym(530,yylen) */
/*lint -esym(563,yyerrorlab) */   
/*lint -esym(746,__yy_memcpy) -esym(516,__yy_memcpy) */
/*lint -esym(718,yylex) -esym(746,yylex) */
/*lint -esym(644,yyval,yylval) -esym(550,yynerrs) */
/*lint -esym(553,__GNUC__)  -esym(578,yylen) */
/*lint -esym(768,bits) -esym(553,YYSTACK_USE_ALLOCA) */ 
   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "bool.h"
#include "mshell.h"
#include "ratlptypes.h"
#include "mme.h"
#include "code.h"
#include "inst.h"
   
#define YYERROR_VERBOSE 1

/*lint -sem(yyerror, 1p && nulterm(1), r_no) */ 
extern void yyerror(const char* s);
 


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
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
typedef union YYSTYPE
#line 61 "src/mmlparse.y"
{
   unsigned int bits;
   Numb*        numb;
   const char*  strg;
   const char*  name;
   Symbol*      sym;
   Define*      def;
   CodeNode*    code;
}
/* Line 193 of yacc.c.  */
#line 373 "src/mmlparse.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 386 "src/mmlparse.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
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

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
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
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  40
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2557

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  118
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  274
/* YYNRULES -- Number of states.  */
#define YYNSTATES  765

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   360

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     106,   107,   110,   108,   105,   109,     2,   111,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,   113,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   114,     2,   115,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   116,     2,   117,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     112
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    11,    13,    15,    17,
      19,    21,    23,    25,    31,    40,    49,    57,    59,    63,
      70,    75,    78,    87,    96,   105,   114,   116,   120,   130,
     139,   145,   147,   149,   151,   152,   155,   165,   172,   181,
     187,   197,   204,   216,   225,   226,   228,   231,   232,   235,
     239,   249,   259,   260,   263,   266,   275,   284,   285,   288,
     289,   292,   294,   298,   300,   303,   306,   310,   314,   319,
     325,   331,   337,   342,   347,   352,   357,   364,   371,   378,
     385,   390,   398,   410,   422,   434,   446,   458,   470,   482,
     494,   506,   518,   530,   542,   554,   566,   578,   590,   598,
     606,   614,   622,   626,   630,   634,   638,   642,   646,   650,
     654,   658,   662,   666,   670,   674,   678,   682,   686,   690,
     694,   698,   702,   706,   709,   713,   714,   718,   720,   722,
     724,   726,   728,   730,   734,   738,   742,   746,   750,   754,
     756,   760,   764,   768,   771,   774,   777,   782,   787,   795,
     799,   805,   810,   815,   816,   818,   820,   824,   827,   830,
     833,   836,   839,   844,   849,   852,   853,   856,   859,   864,
     867,   875,   881,   889,   895,   900,   904,   908,   912,   916,
     920,   924,   928,   932,   937,   942,   950,   955,   963,   967,
     971,   975,   979,   985,   991,   998,  1003,  1011,  1016,  1019,
    1022,  1025,  1028,  1031,  1033,  1037,  1039,  1043,  1047,  1051,
    1055,  1059,  1063,  1067,  1071,  1075,  1079,  1083,  1087,  1091,
    1095,  1099,  1102,  1106,  1110,  1115,  1120,  1128,  1131,  1135,
    1136,  1140,  1142,  1146,  1148,  1152,  1156,  1158,  1162,  1166,
    1170,  1174,  1176,  1178,  1180,  1183,  1186,  1191,  1196,  1199,
    1203,  1208,  1213,  1218,  1223,  1228,  1233,  1238,  1243,  1248,
    1251,  1254,  1258,  1263,  1272,  1279,  1287,  1290,  1293,  1298,
    1303,  1308,  1313,  1318,  1323
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     119,     0,    -1,   120,    -1,   128,    -1,   131,    -1,   141,
      -1,   142,    -1,   151,    -1,   123,    -1,   124,    -1,   125,
      -1,   126,    -1,   154,    -1,     3,   100,    20,   158,   113,
      -1,     3,   100,   114,   156,   115,    20,   158,   113,    -1,
       3,   100,   114,   156,   115,    20,   121,   113,    -1,     3,
     100,   114,   115,    20,   121,   113,    -1,   122,    -1,   121,
     105,   122,    -1,    82,   106,   158,   105,   166,   107,    -1,
      84,   106,   158,   107,    -1,   163,   158,    -1,    10,    99,
     106,   127,   107,    20,   166,   113,    -1,    11,    99,   106,
     127,   107,    20,   166,   113,    -1,    12,    99,   106,   127,
     107,    20,   162,   113,    -1,    13,    99,   106,   127,   107,
      20,   158,   113,    -1,   100,    -1,   127,   105,   100,    -1,
       4,   100,   114,   156,   115,    20,   137,   130,   113,    -1,
       4,   100,   114,   156,   115,    20,   166,   113,    -1,     4,
     100,    20,   129,   113,    -1,     4,    -1,   137,    -1,   166,
      -1,    -1,    33,   166,    -1,     5,   100,   114,   156,   115,
     132,   133,   134,   113,    -1,     5,   100,   132,   133,   134,
     113,    -1,     5,   100,   114,   156,   115,    19,    16,   113,
      -1,     5,   100,    19,    16,   113,    -1,     5,   100,   114,
     156,   115,    16,   135,   136,   113,    -1,     5,   100,    16,
     135,   136,   113,    -1,     5,   100,   114,   156,   115,    17,
     133,   134,   135,   136,   113,    -1,     5,   100,    17,   133,
     134,   135,   136,   113,    -1,    -1,    18,    -1,    19,    17,
      -1,    -1,    35,   166,    -1,    35,   109,    40,    -1,    35,
      51,   162,    52,   166,    53,   109,    40,    54,    -1,    35,
      51,   162,    52,   109,    40,    53,   166,    54,    -1,    -1,
      34,   166,    -1,    34,    40,    -1,    34,    51,   162,    52,
     166,    53,    40,    54,    -1,    34,    51,   162,    52,    40,
      53,   166,    54,    -1,    -1,    31,   166,    -1,    -1,    32,
     166,    -1,   138,    -1,   137,   105,   138,    -1,   159,    -1,
     139,   140,    -1,   163,   166,    -1,    22,   165,    22,    -1,
     139,   165,    22,    -1,   140,   139,   165,    22,    -1,     6,
     100,    21,   148,   113,    -1,     7,   100,    21,   148,   113,
      -1,     8,   100,    21,   143,   113,    -1,   148,   147,   148,
     145,    -1,   148,   147,   166,   145,    -1,   166,   147,   148,
     145,    -1,   166,   147,   166,   145,    -1,   166,   147,   148,
      34,   166,   145,    -1,   166,   147,   166,    34,   166,   145,
      -1,   166,   147,   148,    35,   166,   145,    -1,   166,   147,
     166,    35,   166,   145,    -1,    27,   156,    21,   143,    -1,
      51,   162,    52,   143,    53,   143,    54,    -1,    85,   144,
      52,   148,   147,   148,    53,   148,   147,   148,    54,    -1,
      85,   144,    52,   166,   147,   148,    53,   148,   147,   148,
      54,    -1,    85,   144,    52,   148,   147,   166,    53,   148,
     147,   148,    54,    -1,    85,   144,    52,   148,   147,   148,
      53,   166,   147,   148,    54,    -1,    85,   144,    52,   148,
     147,   148,    53,   148,   147,   166,    54,    -1,    85,   144,
      52,   166,   147,   166,    53,   148,   147,   148,    54,    -1,
      85,   144,    52,   166,   147,   148,    53,   166,   147,   148,
      54,    -1,    85,   144,    52,   166,   147,   148,    53,   148,
     147,   166,    54,    -1,    85,   144,    52,   148,   147,   166,
      53,   166,   147,   148,    54,    -1,    85,   144,    52,   148,
     147,   166,    53,   148,   147,   166,    54,    -1,    85,   144,
      52,   148,   147,   148,    53,   166,   147,   166,    54,    -1,
      85,   144,    52,   166,   147,   166,    53,   166,   147,   148,
      54,    -1,    85,   144,    52,   166,   147,   166,    53,   148,
     147,   166,    54,    -1,    85,   144,    52,   166,   147,   148,
      53,   166,   147,   166,    54,    -1,    85,   144,    52,   148,
     147,   166,    53,   166,   147,   166,    54,    -1,    85,   144,
      52,   166,   147,   166,    53,   166,   147,   166,    54,    -1,
      85,   144,    52,   148,   147,   148,    54,    -1,    85,   144,
      52,   166,   147,   148,    54,    -1,    85,   144,    52,   148,
     147,   166,    54,    -1,    85,   144,    52,   166,   147,   166,
      54,    -1,   148,    39,   148,    -1,   166,    39,   148,    -1,
     148,    39,   166,    -1,   148,    36,   148,    -1,   166,    36,
     148,    -1,   148,    36,   166,    -1,   148,    34,   148,    -1,
     166,    34,   148,    -1,   148,    34,   166,    -1,   148,    35,
     148,    -1,   166,    35,   148,    -1,   148,    35,   166,    -1,
     148,    37,   148,    -1,   166,    37,   148,    -1,   148,    37,
     166,    -1,   148,    38,   148,    -1,   166,    38,   148,    -1,
     148,    38,   166,    -1,   144,    41,   144,    -1,   144,    42,
     144,    -1,   144,    43,   144,    -1,    44,   144,    -1,   106,
     144,   107,    -1,    -1,   145,   105,   146,    -1,   103,    -1,
     104,    -1,    34,    -1,    35,    -1,    36,    -1,   149,    -1,
     148,   108,   149,    -1,   148,   109,   149,    -1,   148,   108,
     167,    -1,   148,   109,   167,    -1,   166,   108,   149,    -1,
     166,   109,   149,    -1,   150,    -1,   149,   110,   168,    -1,
     149,   111,   168,    -1,   167,   110,   150,    -1,    93,   164,
      -1,   108,   150,    -1,   109,   150,    -1,    86,   106,   148,
     107,    -1,    45,   156,    21,   149,    -1,    51,   162,    52,
     148,    53,   148,    54,    -1,   106,   148,   107,    -1,     9,
     100,    21,   152,   113,    -1,   153,   135,    21,   148,    -1,
      27,   156,    21,   152,    -1,    -1,    87,    -1,    88,    -1,
      21,   155,   113,    -1,    14,   165,    -1,    14,   163,    -1,
      14,   158,    -1,    14,    93,    -1,    15,   162,    -1,    27,
     156,    21,   155,    -1,   163,    23,   158,   157,    -1,   158,
     157,    -1,    -1,    22,   162,    -1,    94,   164,    -1,    98,
     106,   165,   107,    -1,   116,   117,    -1,   116,   166,    24,
     166,    26,   166,   117,    -1,   116,   166,    24,   166,   117,
      -1,   116,   166,    25,   166,    26,   166,   117,    -1,   116,
     166,    25,   166,   117,    -1,    56,   156,    21,   158,    -1,
     158,    56,   158,    -1,   158,   108,   158,    -1,   158,    58,
     158,    -1,   158,    59,   158,    -1,   158,   109,   158,    -1,
     158,    57,   158,    -1,   158,   110,   158,    -1,   158,    55,
     158,    -1,    55,   156,    21,   158,    -1,    48,   156,    21,
     166,    -1,    48,   106,   166,   107,   156,    21,   166,    -1,
      49,   156,    21,   166,    -1,    49,   106,   166,   107,   156,
      21,   166,    -1,   106,   158,   107,    -1,   116,   161,   117,
      -1,   116,   165,   117,    -1,   116,   156,   117,    -1,   116,
     156,    21,   166,   117,    -1,   116,   156,    21,   163,   117,
      -1,    60,   106,   158,   105,   163,   107,    -1,    83,   106,
      94,   107,    -1,    51,   162,    52,   158,    53,   158,    54,
      -1,    76,   166,    77,   166,    -1,   159,   160,    -1,    78,
     166,    -1,    79,   166,    -1,    80,   166,    -1,    81,   166,
      -1,   163,    -1,   161,   105,   163,    -1,   159,    -1,   166,
      36,   166,    -1,   166,    39,   166,    -1,   166,    38,   166,
      -1,   166,    35,   166,    -1,   166,    37,   166,    -1,   166,
      34,   166,    -1,   158,    36,   158,    -1,   158,    39,   158,
      -1,   158,    38,   158,    -1,   158,    35,   158,    -1,   158,
      37,   158,    -1,   158,    34,   158,    -1,   162,    41,   162,
      -1,   162,    42,   162,    -1,   162,    43,   162,    -1,    44,
     162,    -1,   106,   162,   107,    -1,   163,    23,   158,    -1,
      30,   106,   156,   107,    -1,    97,   106,   165,   107,    -1,
      51,   162,    52,   162,    53,   162,    54,    -1,    37,    38,
      -1,    37,   165,    38,    -1,    -1,   114,   165,   115,    -1,
     166,    -1,   165,   105,   166,    -1,   167,    -1,   166,   108,
     167,    -1,   166,   109,   167,    -1,   168,    -1,   167,   110,
     168,    -1,   167,   111,   168,    -1,   167,    61,   168,    -1,
     167,    62,   168,    -1,   102,    -1,   101,    -1,   100,    -1,
      91,   164,    -1,    92,   164,    -1,    95,   106,   165,   107,
      -1,    96,   106,   165,   107,    -1,   168,    64,    -1,   168,
      63,   168,    -1,    65,   106,   158,   107,    -1,    66,   106,
     166,   107,    -1,    67,   106,   166,   107,    -1,    68,   106,
     166,   107,    -1,    69,   106,   166,   107,    -1,    70,   106,
     166,   107,    -1,    71,   106,   166,   107,    -1,    72,   106,
     166,   107,    -1,    73,   106,   166,   107,    -1,   108,   168,
      -1,   109,   168,    -1,   106,   166,   107,    -1,    89,   106,
     166,   107,    -1,    90,   106,   166,   105,   166,   105,   166,
     107,    -1,    74,   106,   166,   105,   166,   107,    -1,    51,
     162,    52,   166,    53,   166,    54,    -1,    46,   156,    -1,
      47,   156,    -1,    46,   156,    21,   167,    -1,    47,   156,
      21,   167,    -1,    45,   156,    21,   167,    -1,    50,   156,
      21,   167,    -1,    46,   106,   165,   107,    -1,    47,   106,
     165,   107,    -1,    75,   106,   158,   105,   166,   105,   166,
     107,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   131,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   149,   156,   162,   168,   178,   179,   182,
     185,   191,   200,   209,   218,   227,   236,   239,   249,   252,
     255,   262,   265,   266,   273,   274,   282,   289,   298,   308,
     319,   328,   338,   342,   352,   353,   354,   358,   361,   362,
     363,   368,   376,   377,   378,   379,   384,   392,   393,   397,
     398,   406,   407,   410,   411,   415,   419,   423,   426,   438,
     441,   451,   457,   460,   465,   470,   477,   481,   486,   490,
     496,   499,   502,   505,   510,   515,   520,   524,   531,   538,
     544,   550,   556,   561,   569,   577,   585,   592,   602,   605,
     608,   611,   618,   619,   622,   625,   626,   629,   632,   633,
     636,   639,   640,   643,   646,   647,   650,   653,   654,   657,
     660,   661,   662,   663,   664,   668,   669,   673,   674,   678,
     679,   680,   684,   685,   686,   687,   688,   691,   692,   700,
     701,   702,   706,   710,   713,   714,   717,   718,   722,   725,
     733,   739,   742,   748,   749,   750,   758,   762,   763,   764,
     765,   766,   767,   777,   780,   787,   788,   792,   795,   800,
     801,   804,   807,   810,   813,   814,   815,   818,   819,   820,
     823,   824,   827,   828,   829,   832,   835,   838,   841,   842,
     843,   844,   845,   846,   847,   850,   853,   859,   860,   864,
     865,   866,   867,   871,   874,   877,   881,   882,   883,   884,
     885,   886,   887,   888,   889,   890,   891,   892,   893,   894,
     895,   896,   897,   898,   899,   900,   905,   911,   912,   916,
     919,   925,   928,   934,   935,   936,   940,   941,   942,   943,
     944,   948,   949,   950,   953,   956,   959,   964,   969,   970,
     972,   973,   974,   975,   976,   977,   978,   979,   980,   982,
     983,   984,   985,   986,   989,   992,   995,   998,  1001,  1004,
    1007,  1010,  1013,  1016,  1019
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DECLSET", "DECLPAR", "DECLVAR",
  "DECLMIN", "DECLMAX", "DECLSUB", "DECLSOS", "DEFNUMB", "DEFSTRG",
  "DEFBOOL", "DEFSET", "PRINT", "CHECK", "BINARY", "INTEGER", "REAL",
  "IMPLICIT", "ASGN", "DO", "WITH", "IN", "TO", "UNTIL", "BY", "FORALL",
  "EMPTY_TUPLE", "EMPTY_SET", "EXISTS", "PRIORITY", "STARTVAL", "DEFAULT",
  "CMP_LE", "CMP_GE", "CMP_EQ", "CMP_LT", "CMP_GT", "CMP_NE", "INFTY",
  "AND", "OR", "XOR", "NOT", "SUM", "MIN", "MAX", "ARGMIN", "ARGMAX",
  "PROD", "IF", "THEN", "ELSE", "END", "INTER", "UNION", "CROSS",
  "SYMDIFF", "WITHOUT", "PROJ", "MOD", "DIV", "POW", "FAC", "CARD", "ABS",
  "SGN", "FLOOR", "CEIL", "LOG", "LN", "EXP", "SQRT", "RANDOM", "ORD",
  "READ", "AS", "SKIP", "USE", "COMMENT", "MATCH", "SUBSETS", "INDEXSET",
  "POWERSET", "VIF", "VABS", "TYPE1", "TYPE2", "LENGTH", "SUBSTR",
  "NUMBSYM", "STRGSYM", "VARSYM", "SETSYM", "NUMBDEF", "STRGDEF",
  "BOOLDEF", "SETDEF", "DEFNAME", "NAME", "STRG", "NUMB", "SCALE",
  "SEPARATE", "','", "'('", "')'", "'+'", "'-'", "'*'", "'/'", "UNARY",
  "';'", "'['", "']'", "'{'", "'}'", "$accept", "stmt", "decl_set",
  "set_entry_list", "set_entry", "def_numb", "def_strg", "def_bool",
  "def_set", "name_list", "decl_par", "par_singleton", "par_default",
  "decl_var", "var_type", "lower", "upper", "priority", "startval",
  "cexpr_entry_list", "cexpr_entry", "matrix_head", "matrix_body",
  "decl_obj", "decl_sub", "constraint", "vbool", "con_attr_list",
  "con_attr", "con_type", "vexpr", "vproduct", "vfactor", "decl_sos",
  "soset", "sos_type", "exec_do", "command", "idxset", "condition",
  "sexpr", "read", "read_par", "tuple_list", "lexpr", "tuple", "symidx",
  "cexpr_list", "cexpr", "cproduct", "cfactor", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,    44,    40,    41,    43,    45,
      42,    47,   360,    59,    91,    93,   123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   118,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   120,   120,   120,   120,   121,   121,   121,
     121,   122,   123,   124,   125,   126,   127,   127,   128,   128,
     128,   128,   129,   129,   130,   130,   131,   131,   131,   131,
     131,   131,   131,   131,   132,   132,   132,   133,   133,   133,
     133,   133,   134,   134,   134,   134,   134,   135,   135,   136,
     136,   137,   137,   137,   137,   138,   139,   140,   140,   141,
     141,   142,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   145,   145,   146,   146,   147,
     147,   147,   148,   148,   148,   148,   148,   148,   148,   149,
     149,   149,   149,   150,   150,   150,   150,   150,   150,   150,
     151,   152,   152,   153,   153,   153,   154,   155,   155,   155,
     155,   155,   155,   156,   156,   157,   157,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   159,   159,   160,
     160,   160,   160,   161,   161,   161,   162,   162,   162,   162,
     162,   162,   162,   162,   162,   162,   162,   162,   162,   162,
     162,   162,   162,   162,   162,   162,   162,   163,   163,   164,
     164,   165,   165,   166,   166,   166,   167,   167,   167,   167,
     167,   168,   168,   168,   168,   168,   168,   168,   168,   168,
     168,   168,   168,   168,   168,   168,   168,   168,   168,   168,
     168,   168,   168,   168,   168,   168,   168,   168,   168,   168,
     168,   168,   168,   168,   168
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     5,     8,     8,     7,     1,     3,     6,
       4,     2,     8,     8,     8,     8,     1,     3,     9,     8,
       5,     1,     1,     1,     0,     2,     9,     6,     8,     5,
       9,     6,    11,     8,     0,     1,     2,     0,     2,     3,
       9,     9,     0,     2,     2,     8,     8,     0,     2,     0,
       2,     1,     3,     1,     2,     2,     3,     3,     4,     5,
       5,     5,     4,     4,     4,     4,     6,     6,     6,     6,
       4,     7,    11,    11,    11,    11,    11,    11,    11,    11,
      11,    11,    11,    11,    11,    11,    11,    11,     7,     7,
       7,     7,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     3,     0,     3,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     1,
       3,     3,     3,     2,     2,     2,     4,     4,     7,     3,
       5,     4,     4,     0,     1,     1,     3,     2,     2,     2,
       2,     2,     4,     4,     2,     0,     2,     2,     4,     2,
       7,     5,     7,     5,     4,     3,     3,     3,     3,     3,
       3,     3,     3,     4,     4,     7,     4,     7,     3,     3,
       3,     3,     5,     5,     6,     4,     7,     4,     2,     2,
       2,     2,     2,     1,     3,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     3,     3,     4,     4,     7,     2,     3,     0,
       3,     1,     3,     1,     3,     3,     1,     3,     3,     3,
       3,     1,     1,     1,     2,     2,     4,     4,     2,     3,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     2,
       2,     3,     4,     8,     6,     7,     2,     2,     4,     4,
       4,     4,     4,     4,     8
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     0,    31,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     2,     8,     9,    10,    11,     3,
       4,     5,     6,     7,    12,     0,     0,    44,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,     0,     0,     0,     0,    57,    47,    45,     0,     0,
      47,     0,     0,     0,   153,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   229,   229,   160,   229,     0,     0,
       0,   243,   242,   241,     0,     0,     0,     0,   159,   158,
     157,   231,   233,   236,     0,     0,     0,     0,     0,     0,
     161,     0,     0,     0,     0,     0,   165,     0,   156,     0,
       0,     0,     0,     0,     0,     0,     0,    32,    61,     0,
      63,     0,    33,     0,     0,    59,     0,    52,     0,    46,
       0,    52,     0,     0,     0,   229,     0,     0,     0,     0,
     132,   139,     0,   233,     0,     0,     0,     0,     0,     0,
       0,     0,   154,   155,     0,    57,    26,     0,     0,     0,
       0,   227,     0,     0,     0,   266,     0,   267,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   244,   245,   167,     0,     0,     0,     0,     0,
     259,   260,   169,     0,   205,     0,   203,     0,   231,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   248,     0,   221,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   164,     0,    13,     0,     0,     0,     0,     0,
      30,     0,     0,    64,     0,     0,     0,     0,   198,    65,
       0,    58,     0,     0,     0,     0,    48,     0,    57,    39,
      44,     0,     0,     0,     0,   143,     0,     0,   144,   145,
       0,     0,    69,     0,     0,     0,     0,     0,    70,     0,
       0,     0,     0,     0,     0,     0,    71,   129,   130,   131,
       0,     0,     0,   150,     0,     0,     0,     0,     0,     0,
     228,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   188,   261,     0,   191,     0,   189,   190,
       0,     0,   182,   175,   180,   177,   178,   176,   179,   181,
     232,   234,   235,   239,   240,   237,   238,   249,     0,     0,
       0,   222,   217,   215,   212,   216,   214,   213,   218,   219,
     220,   223,   211,   209,   206,   210,   208,   207,     0,   162,
     166,   165,     0,     0,     0,    17,     0,     0,    66,     0,
       0,    62,     0,     0,   199,   200,   201,   202,     0,    60,
      41,     0,    49,    54,     0,    53,    59,    57,    47,     0,
      47,    37,     0,     0,     0,   149,   133,   135,   134,   136,
     140,   141,   137,   234,   138,   235,   142,     0,     0,   123,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   125,
     125,   125,   125,   153,     0,    27,     0,     0,     0,     0,
     270,   272,   268,   273,   269,     0,   184,     0,   186,   271,
       0,     0,   183,   174,     0,   250,   251,   252,   253,   254,
     255,   256,   257,   258,     0,     0,   195,   262,     0,   230,
     246,   247,   168,     0,     0,   204,     0,     0,   224,     0,
       0,     0,   225,   163,     0,     0,     0,    16,    21,     0,
       0,   197,    67,     0,    34,     0,     0,     0,     0,    59,
      52,     0,    52,   147,   270,     0,     0,   146,    80,     0,
       0,     0,   124,   120,   121,   122,     0,     0,   108,   110,
     111,   113,   105,   107,   114,   116,   117,   119,   102,   104,
     109,   112,   106,   115,   118,   103,    72,    73,     0,     0,
      74,     0,     0,    75,   152,   151,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   193,   192,
       0,   171,     0,   173,     0,     0,     0,    18,    15,    14,
      68,     0,     0,    29,     0,     0,     0,    43,     0,    57,
      38,     0,     0,     0,     0,     0,     0,   125,   125,   125,
     125,    22,    23,    24,    25,     0,     0,     0,     0,   194,
     264,     0,     0,     0,     0,     0,     0,    20,    35,    28,
       0,     0,     0,     0,    40,    59,    36,     0,     0,     0,
       0,     0,     0,   127,   128,   126,    76,    78,    77,    79,
     185,   187,   196,   265,     0,     0,   170,   172,   226,     0,
       0,     0,     0,     0,     0,   148,    81,     0,    98,     0,
     100,     0,    99,     0,   101,   274,   263,    19,     0,     0,
       0,     0,    42,     0,     0,     0,     0,     0,     0,     0,
       0,    51,    50,    56,    55,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    82,
      86,    85,    92,    84,    91,    90,    96,    83,    89,    88,
      95,    87,    94,    93,    97
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    13,    14,   414,   415,    15,    16,    17,    18,   167,
      19,   126,   622,    20,    50,   137,   288,   135,   283,   127,
     128,   129,   273,    21,    22,   158,   313,   586,   675,   320,
     314,   150,   151,    23,   164,   165,    24,    39,   115,   262,
     116,   130,   278,   215,   110,   111,   202,   100,   112,   102,
     103
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -453
static const yytype_int16 yypact[] =
{
    1721,   -26,   -13,     5,    27,    31,    48,    80,    96,   103,
     112,   138,   245,   253,  -453,  -453,  -453,  -453,  -453,  -453,
    -453,  -453,  -453,  -453,  -453,    -6,     6,    -8,   226,   244,
     279,   293,   168,   186,   190,   241,  1387,  1163,  1050,   208,
    -453,  2066,   708,   984,  1050,   301,   316,  -453,   215,  1050,
     316,  2188,  2188,  1248,    86,   264,   264,   264,   264,  1648,
    1050,  1066,  1079,  1449,  1462,  1050,  1163,  1050,  1050,   261,
     272,   276,   284,   312,   346,   350,   358,   378,   389,   436,
     453,   464,   469,   472,   298,   298,  -453,   298,   476,   518,
     531,  -453,  -453,  -453,  1581,  2253,  2253,  1314,   861,  -453,
     547,   198,   105,   438,   549,  1163,  1163,   552,  1163,   909,
     353,   639,   364,  1163,  2066,   643,    20,   664,  -453,   591,
     696,   604,  2253,  1163,  2253,  2253,   599,   617,  -453,   717,
     857,  2253,   198,   631,  2253,   716,  2318,   724,   671,  -453,
     673,   724,  1050,  1163,   686,   298,  2188,  2188,  2188,   422,
     426,  -453,   406,   275,   661,  1050,  1163,  2123,   680,   178,
     247,  1050,  -453,  -453,   685,   301,  -453,   -56,   -34,    38,
     156,  -453,     9,   786,  1581,   789,  1581,   791,  1581,   792,
    1581,   797,   824,   521,   832,   836,  2066,  2066,  2253,  2253,
    2253,  2253,  2253,  2253,  2253,  2253,  2253,  2066,   768,  2253,
    2253,  2253,  -453,  -453,  -453,  2253,  2253,  2253,   571,   504,
     813,   813,  -453,     1,   857,   -61,   664,   -48,     3,  2066,
    2066,  2066,  2066,  2066,  2066,  2066,  2066,  2253,  2253,  2253,
    2253,  2253,  2253,  2253,  2253,  -453,  1050,  -453,   808,  2253,
     170,    12,    28,  2066,  2066,  2066,  2066,  2066,  2066,  1163,
    1163,  1163,  2066,  2253,  2253,  2253,  2253,  2253,  2253,   846,
     245,  1163,  -453,  2066,  -453,    15,   843,    -1,   870,   -18,
    -453,   853,  2253,   717,  2253,  2253,  2253,  2253,  -453,   198,
     871,   198,  2253,   793,  1163,  1713,   198,  1778,   301,  -453,
     810,   801,   884,   941,  2188,  -453,   563,   777,  -453,  -453,
    2188,  2188,  -453,  2253,  2253,  2188,  2188,  2188,  -453,   889,
     970,  2123,  2123,  1020,   432,   509,  -453,  -453,  -453,  -453,
    2188,  2188,   902,  -453,   911,   830,   921,   922,   929,   931,
    -453,  2253,   221,  2253,   256,  2253,   916,  2253,   919,  2253,
    2253,  1581,  2066,  2066,   816,  1416,   932,   938,   974,  1000,
    1004,  1038,  1067,  1089,   530,  1192,   848,  1108,   747,   -45,
     380,   385,   482,  -453,  -453,  1516,  -453,   853,  -453,  -453,
    2253,  2253,   396,   135,  1112,   135,   135,   135,   135,  -453,
     198,   105,   105,   438,   438,   438,   438,   438,   849,  1163,
     487,  -453,   861,   861,   861,   861,   861,   861,  -453,   917,
     917,   861,   198,   198,   198,   198,   198,   198,  2066,  -453,
     353,    20,   854,   856,   137,  -453,  2066,   748,  -453,  2253,
    2253,  -453,    10,  2253,   198,   198,   198,   198,   984,   198,
    -453,  1116,  -453,  -453,  1163,   198,   716,   301,   316,   681,
     316,  -453,  2188,  2188,  1117,  -453,   426,   275,   426,   275,
     438,   438,   426,   275,   426,   275,  -453,  1248,  1248,  -453,
      39,   232,   338,  2123,  2123,  2123,  2188,  2188,  2188,  2188,
    2188,  2188,  2188,  2188,  2188,  2188,  2188,  2188,  2188,   646,
     406,   200,   311,    86,  2188,  -453,  2253,  2253,  1163,  2066,
     105,  -453,   105,  -453,   105,  1050,   198,  1050,   198,  -453,
     441,   249,   885,   885,   853,  -453,  -453,  -453,  -453,  -453,
    -453,  -453,  -453,  -453,  2253,  2253,  -453,  -453,  2253,  -453,
    -453,  -453,  -453,   863,   536,  -453,    17,    24,  -453,   844,
     730,   424,  -453,  -453,  2066,  2066,   853,  -453,   861,   185,
     652,   198,  -453,    11,     2,   692,  2383,  1137,   868,   716,
     724,   881,   724,   426,   275,   257,   306,  -453,  -453,   954,
     115,   148,  -453,  -453,   967,   967,   178,   247,   646,   406,
     646,   406,   646,   406,   646,   406,   646,   406,   646,   406,
     646,   646,   646,   646,   646,   646,   905,   905,  2253,  2253,
     905,  2253,  2253,   905,  -453,   646,   712,   735,    -4,  1010,
     994,   999,  2066,  2253,   925,  1136,   760,   799,  -453,  -453,
    2253,  -453,  2253,  -453,  1163,  1336,  1493,  -453,  -453,  -453,
    -453,  2253,   920,  -453,  1843,   404,  1908,  -453,   923,   301,
    -453,   930,  2188,  1248,  2188,  2188,   663,   198,   198,   198,
     198,  -453,  -453,  -453,  -453,  2253,  2253,  1096,    14,  -453,
    -453,  2253,  2253,   560,   678,    42,  2253,  -453,   198,  -453,
     989,  2448,   995,   430,  -453,   716,  -453,    85,  1016,   271,
     296,   335,   372,  -453,  -453,  -453,   905,   905,   905,   905,
     198,   198,  -453,  -453,  1173,  1176,  -453,  -453,  -453,  1182,
    2253,  1973,  2253,  2038,   951,  -453,  -453,  2188,  -453,  2188,
    -453,  2188,  -453,  2188,  -453,  -453,  -453,  -453,   146,  1017,
     234,  1023,  -453,   178,   247,   178,   247,   178,   247,   178,
     247,  -453,  -453,  -453,  -453,  2188,  2188,  2188,  2188,  2188,
    2188,  2188,  2188,   300,   315,   449,   475,   514,   523,   525,
     532,   534,   565,   567,   597,   606,   612,   632,   634,  -453,
    -453,  -453,  -453,  -453,  -453,  -453,  -453,  -453,  -453,  -453,
    -453,  -453,  -453,  -453,  -453
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -453,  -453,  -453,   672,   542,  -453,  -453,  -453,  -453,  1247,
    -453,  -453,  -453,  -453,   798,   -47,  -139,  -164,  -432,   669,
     820,  -111,  -453,  -453,  -453,  -452,  -266,  -451,  -453,  -112,
      50,  -281,  -135,  -453,   619,  -453,  -453,   840,   255,   693,
     753,  1027,  -453,  -453,   225,   773,   -51,    88,   -36,   260,
     -55
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
     101,   324,   291,   141,   548,   558,   559,   132,    45,    46,
      47,    48,   298,   299,    41,   152,   152,   160,   272,   446,
     448,   418,   365,   101,   452,   454,    43,   370,   371,   587,
     590,   593,   542,   620,   203,   621,   204,   249,   250,   251,
     210,   211,   261,   610,   367,   459,   460,   330,   321,   325,
     612,   326,    59,   249,   250,   251,   368,   227,   209,   420,
     227,   218,   253,   254,   255,   256,   257,   258,   683,   369,
     519,   325,   242,   327,    25,   219,   220,   221,   222,   223,
     463,   464,   465,   249,   250,   251,   101,    26,   269,   209,
     228,   229,   210,   211,   295,   279,   688,   412,   281,   413,
     286,   149,   154,   159,   227,    27,    49,   271,    42,   643,
     297,   228,   229,   161,   227,   227,   227,   628,   366,   391,
      44,   315,   228,   229,   436,   228,   229,    28,   224,   225,
     226,    29,   228,   229,   611,   364,   228,   229,   101,   695,
     101,   613,   336,   325,   338,   328,   562,   172,    30,   317,
     318,   319,   346,   347,   348,   349,   350,   351,   352,   353,
     354,   553,   423,   357,   358,   101,   230,   231,   632,   101,
     101,   101,   456,   162,   163,   383,   384,   385,   386,   387,
      31,   668,   317,   318,   319,   217,   676,   677,   678,   679,
     219,   380,   221,   300,   301,    32,   296,   563,   564,   565,
     721,   603,    33,   101,   243,   244,   245,   246,   247,   248,
     267,    34,   317,   318,   319,   232,   233,   402,   403,   404,
     405,   406,   407,   300,   301,   219,   220,   221,   222,   223,
     211,   138,   139,   694,   588,   589,   101,    35,   424,   425,
     426,   427,   536,   224,   225,   226,   429,    51,   450,   451,
     537,   435,   385,    40,   228,   229,   305,   306,   152,    36,
      37,   325,   332,   329,   334,    52,   467,   468,   469,   470,
     471,   472,    38,   549,    55,   315,   462,   363,   224,   225,
     226,   317,   318,   319,   480,   482,   300,   301,   723,   359,
     536,   183,    56,   360,   361,   362,    57,   121,   618,   133,
      53,   496,   603,   498,   140,   501,   228,   229,   300,   301,
     632,   153,   153,   153,    54,   173,   175,   177,   179,   181,
     182,   118,   184,   185,   697,   698,   227,   390,   491,   524,
     237,   238,   134,   241,   526,   527,   230,   231,   259,   445,
     300,   301,   228,   229,   444,   591,   592,    58,   268,   699,
     700,   136,   213,   531,   749,   305,   306,   228,   229,   603,
     422,   227,   461,   493,   166,   300,   301,   186,   293,   750,
     479,   481,   473,   474,   475,   476,   477,   478,   187,   300,
     301,   310,   188,   501,   541,   307,   233,   101,   701,   702,
     189,   550,   545,   552,   249,   250,   251,   292,   253,   254,
     255,   256,   257,   258,   305,   306,   153,   556,   300,   301,
     309,   629,   201,   631,   305,   306,   322,   153,   190,   305,
     306,   160,   561,   305,   306,   703,   704,   315,   315,   315,
     567,   569,   571,   573,   575,   577,   579,   152,   152,   152,
     152,   152,   152,   300,   301,   364,   305,   306,   152,   321,
     596,   597,   191,   221,   634,   635,   192,   661,   253,   254,
     255,   256,   257,   258,   193,   665,   467,   468,   469,   470,
     471,   472,   228,   229,   398,   399,   400,   603,   605,   606,
     305,   306,   607,   693,   194,   227,   410,   520,   381,   382,
     227,   388,   521,   555,   602,   195,   219,   220,   221,   222,
     223,   234,   235,   751,   224,   225,   226,   159,   560,   431,
     625,   543,   228,   229,   305,   306,   566,   568,   570,   572,
     574,   576,   578,   580,   581,   582,   583,   584,   585,   752,
     300,   301,   228,   229,   595,   302,   303,   304,   228,   229,
     300,   301,   196,   473,   474,   475,   476,   477,   478,   224,
     225,   226,   637,   638,   153,   639,   640,   300,   301,   197,
     447,   449,   249,   250,   251,   453,   455,   648,   753,   211,
     198,   153,   153,   341,   653,   199,   654,   754,   200,   755,
     153,   153,   205,   305,   306,   658,   756,   227,   757,   522,
     663,   490,   227,   492,   532,   494,   152,   160,   670,   672,
     499,   725,   726,   727,   728,   729,   730,   731,   732,   680,
     681,   364,   228,   229,   530,   684,   685,   305,   306,   758,
     689,   759,   300,   301,   206,   648,   219,   220,   221,   222,
     223,   305,   306,   300,   301,   514,   211,   207,   228,   229,
     305,   306,   300,   301,   228,   229,   219,   220,   221,   222,
     223,   760,   227,   609,   708,   236,   710,   648,   239,   547,
     761,   714,   252,   716,   260,   718,   762,   720,   228,   229,
     445,   300,   301,   305,   306,   300,   301,   686,   363,   224,
     225,   226,   667,   159,   669,   671,   763,   263,   764,   734,
     736,   738,   740,   742,   744,   746,   748,   551,   139,   224,
     225,   226,   554,   153,   264,   305,   306,   219,   220,   221,
     222,   223,   270,   598,   300,   301,   265,   153,   153,   266,
     305,   306,   271,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   122,
     300,   301,   305,   306,   153,    59,   280,   713,   282,   715,
     600,   717,   601,   719,   300,   301,    63,    64,   287,   113,
     224,   225,   226,    67,    68,   619,   673,   674,    69,   300,
     301,   249,   250,   251,   308,   733,   735,   737,   739,   741,
     743,   745,   747,   614,   289,    59,   228,   229,   290,    98,
     109,    81,   294,   316,   119,   687,    63,    64,   323,   113,
     228,   229,    87,    67,    68,   623,    90,   331,    69,    99,
     333,   117,   335,   337,   114,   117,   131,   117,   339,   109,
     228,   229,   117,   120,    97,   641,   437,   438,    47,   439,
     412,    81,   413,   117,   117,   117,   117,   117,   117,   655,
     117,   117,    87,   228,   229,   340,    90,   208,   642,   249,
     250,   251,   518,   342,   114,   228,   229,   343,   109,   109,
     389,   240,   356,   417,    97,   651,   109,   208,   228,   229,
     216,   219,   220,   221,   222,   223,   109,   235,   243,   244,
     245,   246,   247,   248,   364,   305,   306,   249,   250,   251,
      59,   428,   153,   153,   153,   153,   109,   602,   408,   219,
     220,   221,   222,   223,   652,   442,   430,   228,   229,   109,
     457,   249,   250,   251,   441,   117,   219,   220,   221,   222,
     223,   504,   419,   483,   224,   225,   226,   208,   117,   208,
     485,   208,   484,   208,   117,   274,   275,   276,   277,   344,
     345,   486,   487,   243,   244,   245,   246,   247,   248,   488,
     355,   489,   224,   225,   226,   516,   528,   153,   249,   153,
     534,   153,   535,   153,   219,   220,   221,   222,   223,   224,
     225,   226,   372,   373,   374,   375,   376,   377,   378,   379,
     608,   627,   249,   250,   251,   153,   153,   153,   153,   153,
     153,   153,   153,   443,   630,   226,   392,   393,   394,   395,
     396,   397,   109,   109,   109,   401,   122,   633,   463,   117,
     636,   249,   250,   251,   109,   645,   411,   224,   225,   226,
     646,    59,   458,   495,   228,   229,   497,   228,   229,    60,
      61,    62,   649,   659,    65,   123,   664,   109,   416,   506,
     228,   229,   690,   666,   131,   507,   228,   229,   692,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
     124,   463,   464,   465,   712,   219,   220,   221,   222,   223,
     696,   722,   466,    82,    83,    84,    85,   724,   617,    88,
      89,   508,   228,   229,    91,    92,    93,    59,   440,   539,
     125,   421,    95,    96,   500,   502,   503,   544,    63,    64,
     409,   113,   594,    59,   533,    67,    68,   509,   228,   229,
      69,   510,   228,   229,    63,    64,    59,   113,   224,   225,
     226,    67,    68,   644,   214,     0,    69,    63,    64,     0,
     113,     0,     0,    81,    67,    68,     0,     0,   523,    69,
     525,     0,   529,     0,    87,   511,   228,   229,    90,    81,
     682,   219,   220,   221,   222,   223,   114,   249,   250,   251,
      87,   500,    81,     0,    90,     0,    97,     0,   546,   538,
     540,     0,   174,    87,   512,   228,   229,    90,   249,   250,
     251,     0,    97,     0,     0,   176,     0,   109,     0,   626,
     416,     0,     0,   104,     0,    97,   513,   228,   229,     0,
      59,   131,     0,     0,   224,   225,   226,   105,    60,    61,
      62,    63,    64,    65,   106,   517,   228,   229,    67,    68,
     224,   225,   226,    69,   557,   300,   301,     0,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,     0,
       0,   109,   599,   650,   228,   229,    81,   219,   220,   221,
     222,   223,    82,    83,    84,    85,     0,    87,    88,    89,
     107,    90,     0,    91,    92,    93,     0,     0,   117,   108,
     117,    95,    96,     0,     0,   155,     0,   604,     0,    97,
     705,   228,   229,   706,   228,   229,     0,   615,   616,   707,
     228,   229,     0,   142,    61,    62,     0,   515,    65,   156,
     224,   225,   226,   168,   169,   170,     0,     0,     0,   416,
       0,     0,     0,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   157,   144,     0,     0,    82,    83,    84,
      85,   145,     0,    88,    89,     0,     0,     0,    91,    92,
      93,    59,     0,     0,   146,   647,   147,   148,     0,    60,
      61,    62,    63,    64,    65,    66,     0,   109,     0,    67,
      68,     0,     0,     0,    69,     0,     0,     0,     0,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
     124,   219,   220,   221,   222,   223,     0,    81,     0,     0,
       0,     0,     0,    82,    83,    84,    85,     0,    87,    88,
      89,     0,    90,     0,    91,    92,    93,     0,     0,     0,
      94,     0,    95,    96,    59,     0,     0,     0,     0,     0,
      97,   212,    60,    61,    62,    63,    64,    65,    66,     0,
       0,   656,    67,    68,   224,   225,   226,    69,     0,     0,
       0,     0,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,     0,     0,     0,     0,     0,     0,     0,
      81,   219,   220,   221,   222,   223,    82,    83,    84,    85,
      86,    87,    88,    89,     0,    90,    59,    91,    92,    93,
       0,     0,     0,    94,     0,    95,    96,    63,    64,    59,
     113,     0,     0,    97,    67,    68,     0,     0,     0,    69,
      63,    64,     0,   113,     0,     0,     0,    67,    68,     0,
       0,     0,    69,   505,   224,   225,   226,     0,     0,     0,
       0,     0,    81,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    87,     0,    81,     0,    90,   219,   220,
     221,   222,   223,    59,     0,   178,    87,     0,     0,     0,
      90,    60,    61,    62,     0,    97,    65,   123,   180,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    97,     0,
       0,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,     0,     0,     0,     0,     0,     0,     0,     0,
     657,   224,   225,   226,     0,    82,    83,    84,    85,     0,
       0,    88,    89,     0,     0,     0,    91,    92,    93,     0,
       0,     0,   125,     0,    95,    96,    60,    61,    62,    63,
      64,    65,    66,     0,     0,     0,    67,    68,     0,     0,
       0,    69,     0,     0,     0,     0,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,     0,     0,     0,
       0,     0,     0,     0,    81,     0,     0,     0,     0,     0,
      82,    83,    84,    85,     0,    87,    88,    89,     0,    90,
       0,    91,    92,    93,     0,     0,   171,    94,     0,    95,
      96,     0,     0,    60,    61,    62,     0,    97,    65,   123,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,     0,     0,    82,    83,    84,
      85,     0,    12,    88,    89,     0,     0,     0,    91,    92,
      93,     0,     0,   432,   125,     0,    95,    96,    60,    61,
      62,     0,     0,    65,   123,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    82,    83,    84,    85,     0,     0,    88,    89,
       0,     0,     0,    91,    92,    93,     0,     0,   433,   125,
       0,    95,    96,    60,    61,    62,     0,     0,    65,   434,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    82,    83,    84,
      85,     0,     0,    88,    89,     0,     0,     0,    91,    92,
      93,     0,     0,   660,   125,     0,    95,    96,    60,    61,
      62,     0,     0,    65,   123,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    82,    83,    84,    85,     0,     0,    88,    89,
       0,     0,     0,    91,    92,    93,     0,     0,   662,   125,
       0,    95,    96,    60,    61,    62,     0,     0,    65,   123,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    82,    83,    84,
      85,     0,     0,    88,    89,     0,     0,     0,    91,    92,
      93,     0,     0,   709,   125,     0,    95,    96,    60,    61,
      62,     0,     0,    65,   123,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    82,    83,    84,    85,     0,     0,    88,    89,
       0,     0,     0,    91,    92,    93,     0,     0,   711,   125,
       0,    95,    96,    60,    61,    62,     0,     0,    65,   123,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    63,    64,     0,   113,     0,     0,
       0,    67,    68,     0,     0,     0,    69,    82,    83,    84,
      85,     0,     0,    88,    89,     0,     0,     0,    91,    92,
      93,     0,     0,     0,   125,     0,    95,    96,     0,    81,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      87,     0,     0,     0,    90,     0,     0,   311,   142,    61,
      62,     0,   114,    65,   143,     0,     0,     0,     0,     0,
       0,     0,    97,     0,     0,     0,     0,     0,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   144,
       0,     0,    82,    83,    84,    85,   145,     0,    88,    89,
       0,     0,     0,    91,    92,    93,     0,     0,     0,   312,
       0,   147,   148,   142,    61,    62,     0,     0,    65,   143,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   144,     0,     0,    82,    83,    84,
      85,   145,     0,    88,    89,     0,     0,     0,    91,    92,
      93,     0,     0,     0,   146,     0,   147,   148,    60,    61,
      62,     0,     0,    65,   123,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    82,    83,    84,    85,     0,     0,    88,    89,
       0,     0,     0,    91,    92,    93,     0,     0,     0,   125,
       0,    95,    96,    60,    61,    62,     0,     0,    65,   284,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    82,    83,    84,
      85,     0,     0,    88,    89,     0,     0,     0,    91,    92,
      93,     0,     0,     0,   125,     0,    95,   285,    60,    61,
      62,     0,     0,    65,   123,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    82,    83,    84,    85,     0,     0,    88,    89,
       0,     0,     0,    91,    92,    93,     0,     0,     0,   125,
       0,    95,   624,    60,    61,    62,     0,     0,    65,   123,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    82,    83,    84,
      85,     0,     0,    88,    89,     0,     0,     0,    91,    92,
      93,     0,     0,     0,   125,     0,    95,   691
};

static const yytype_int16 yycheck[] =
{
      36,   165,   141,    50,   436,   457,   458,    43,    16,    17,
      18,    19,   147,   148,    20,    51,    52,    53,   129,   300,
     301,    22,    21,    59,   305,   306,    20,    24,    25,   480,
     481,   482,    22,    22,    85,    33,    87,    41,    42,    43,
      95,    96,    22,    26,   105,   311,   312,    38,   160,   105,
      26,   107,    37,    41,    42,    43,   117,   105,    94,    77,
     105,    97,    34,    35,    36,    37,    38,    39,    54,   117,
     115,   105,   108,   107,   100,    55,    56,    57,    58,    59,
      41,    42,    43,    41,    42,    43,   122,   100,   124,   125,
     108,   109,   147,   148,   145,   131,    54,    82,   134,    84,
     136,    51,    52,    53,   105,   100,   114,   105,   114,   113,
     146,   108,   109,    27,   105,   105,   105,   549,   117,   107,
     114,   157,   108,   109,   288,   108,   109,   100,   108,   109,
     110,   100,   108,   109,   117,   107,   108,   109,   174,    54,
     176,   117,   178,   105,   180,   107,   107,    59,   100,    34,
      35,    36,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   442,   273,   199,   200,   201,    61,    62,    53,   205,
     206,   207,   307,    87,    88,   230,   231,   232,   233,   234,
     100,   633,    34,    35,    36,    97,   637,   638,   639,   640,
      55,   227,    57,   108,   109,    99,   146,   463,   464,   465,
      54,    53,    99,   239,    34,    35,    36,    37,    38,    39,
     122,    99,    34,    35,    36,   110,   111,   253,   254,   255,
     256,   257,   258,   108,   109,    55,    56,    57,    58,    59,
     285,    16,    17,   665,    34,    35,   272,    99,   274,   275,
     276,   277,   105,   108,   109,   110,   282,    21,   303,   304,
     113,   287,   307,     0,   108,   109,   108,   109,   294,    14,
      15,   105,   174,   107,   176,    21,    34,    35,    36,    37,
      38,    39,    27,   437,   106,   311,   312,   107,   108,   109,
     110,    34,    35,    36,   320,   321,   108,   109,    54,   201,
     105,    66,   106,   205,   206,   207,   106,    42,   113,    44,
      21,   337,    53,   339,    49,   341,   108,   109,   108,   109,
      53,    51,    52,    53,    21,    60,    61,    62,    63,    64,
      65,   113,    67,    68,    53,    54,   105,   239,   107,   365,
     105,   106,    31,   108,   370,   371,    61,    62,   113,   107,
     108,   109,   108,   109,   294,    34,    35,   106,   123,    53,
      54,    35,    97,   389,    54,   108,   109,   108,   109,    53,
     272,   105,   312,   107,   100,   108,   109,   106,   143,    54,
     320,   321,    34,    35,    36,    37,    38,    39,   106,   108,
     109,   156,   106,   419,   420,   110,   111,   423,    53,    54,
     106,   438,   428,   440,    41,    42,    43,   142,    34,    35,
      36,    37,    38,    39,   108,   109,   146,   443,   108,   109,
     155,   550,   114,   552,   108,   109,   161,   157,   106,   108,
     109,   457,   458,   108,   109,    53,    54,   463,   464,   465,
     466,   467,   468,   469,   470,   471,   472,   473,   474,   475,
     476,   477,   478,   108,   109,   107,   108,   109,   484,   561,
     486,   487,   106,    57,   566,   567,   106,    53,    34,    35,
      36,    37,    38,    39,   106,   629,    34,    35,    36,    37,
      38,    39,   108,   109,   249,   250,   251,    53,   514,   515,
     108,   109,   518,    53,   106,   105,   261,   107,   228,   229,
     105,   236,   107,   443,    53,   106,    55,    56,    57,    58,
      59,    63,    64,    54,   108,   109,   110,   457,   458,   284,
     546,   423,   108,   109,   108,   109,   466,   467,   468,   469,
     470,   471,   472,   473,   474,   475,   476,   477,   478,    54,
     108,   109,   108,   109,   484,   113,   110,   111,   108,   109,
     108,   109,   106,    34,    35,    36,    37,    38,    39,   108,
     109,   110,   588,   589,   294,   591,   592,   108,   109,   106,
     300,   301,    41,    42,    43,   305,   306,   603,    54,   624,
     106,   311,   312,    52,   610,   106,   612,    54,   106,    54,
     320,   321,   106,   108,   109,   621,    54,   105,    54,   107,
     626,   331,   105,   333,   107,   335,   632,   633,   634,   635,
     340,   713,   714,   715,   716,   717,   718,   719,   720,   645,
     646,   107,   108,   109,   389,   651,   652,   108,   109,    54,
     656,    54,   108,   109,   106,   661,    55,    56,    57,    58,
      59,   108,   109,   108,   109,   105,   691,   106,   108,   109,
     108,   109,   108,   109,   108,   109,    55,    56,    57,    58,
      59,    54,   105,   117,   690,   106,   692,   693,   106,   434,
      54,   697,    23,   699,    21,   701,    54,   703,   108,   109,
     107,   108,   109,   108,   109,   108,   109,   117,   107,   108,
     109,   110,   632,   633,   634,   635,    54,    23,    54,   725,
     726,   727,   728,   729,   730,   731,   732,    16,    17,   108,
     109,   110,   442,   443,   113,   108,   109,    55,    56,    57,
      58,    59,   113,   488,   108,   109,    20,   457,   458,   115,
     108,   109,   105,   463,   464,   465,   466,   467,   468,   469,
     470,   471,   472,   473,   474,   475,   476,   477,   478,    22,
     108,   109,   108,   109,   484,    37,   115,   697,    32,   699,
     495,   701,   497,   703,   108,   109,    48,    49,    34,    51,
     108,   109,   110,    55,    56,   113,   103,   104,    60,   108,
     109,    41,    42,    43,   113,   725,   726,   727,   728,   729,
     730,   731,   732,    53,   113,    37,   108,   109,   115,    36,
      37,    83,   106,   113,    41,   117,    48,    49,   113,    51,
     108,   109,    94,    55,    56,   113,    98,    21,    60,    36,
      21,    38,    21,    21,   106,    42,    43,    44,    21,    66,
     108,   109,    49,   115,   116,   113,    16,    17,    18,    19,
      82,    83,    84,    60,    61,    62,    63,    64,    65,   614,
      67,    68,    94,   108,   109,    21,    98,    94,   113,    41,
      42,    43,   105,    21,   106,   108,   109,    21,   105,   106,
      52,   108,    94,    20,   116,   105,   113,   114,   108,   109,
      97,    55,    56,    57,    58,    59,   123,    64,    34,    35,
      36,    37,    38,    39,   107,   108,   109,    41,    42,    43,
      37,    20,   632,   633,   634,   635,   143,    53,    52,    55,
      56,    57,    58,    59,   105,    21,   113,   108,   109,   156,
      21,    41,    42,    43,   113,   142,    55,    56,    57,    58,
      59,   105,    52,    21,   108,   109,   110,   174,   155,   176,
     100,   178,    21,   180,   161,    78,    79,    80,    81,   186,
     187,    20,    20,    34,    35,    36,    37,    38,    39,    20,
     197,    20,   108,   109,   110,   107,   107,   697,    41,   699,
     106,   701,   106,   703,    55,    56,    57,    58,    59,   108,
     109,   110,   219,   220,   221,   222,   223,   224,   225,   226,
     117,   113,    41,    42,    43,   725,   726,   727,   728,   729,
     730,   731,   732,    52,   113,   110,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,    22,    53,    41,   236,
     105,    41,    42,    43,   261,    21,   263,   108,   109,   110,
      21,    37,    52,   107,   108,   109,   107,   108,   109,    45,
      46,    47,   107,   113,    50,    51,   113,   284,   265,   107,
     108,   109,    53,   113,   271,   107,   108,   109,    53,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    41,    42,    43,   113,    55,    56,    57,    58,    59,
      54,    54,    52,    89,    90,    91,    92,    54,   536,    95,
      96,   107,   108,   109,   100,   101,   102,    37,   290,   417,
     106,   271,   108,   109,   341,   342,   343,   428,    48,    49,
     260,    51,   483,    37,   411,    55,    56,   107,   108,   109,
      60,   107,   108,   109,    48,    49,    37,    51,   108,   109,
     110,    55,    56,   113,    97,    -1,    60,    48,    49,    -1,
      51,    -1,    -1,    83,    55,    56,    -1,    -1,   365,    60,
     367,    -1,   389,    -1,    94,   107,   108,   109,    98,    83,
      54,    55,    56,    57,    58,    59,   106,    41,    42,    43,
      94,   408,    83,    -1,    98,    -1,   116,    -1,    52,   416,
     417,    -1,   106,    94,   107,   108,   109,    98,    41,    42,
      43,    -1,   116,    -1,    -1,   106,    -1,   434,    -1,    52,
     417,    -1,    -1,    30,    -1,   116,   107,   108,   109,    -1,
      37,   428,    -1,    -1,   108,   109,   110,    44,    45,    46,
      47,    48,    49,    50,    51,   107,   108,   109,    55,    56,
     108,   109,   110,    60,   107,   108,   109,    -1,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    -1,
      -1,   488,   489,   107,   108,   109,    83,    55,    56,    57,
      58,    59,    89,    90,    91,    92,    -1,    94,    95,    96,
      97,    98,    -1,   100,   101,   102,    -1,    -1,   495,   106,
     497,   108,   109,    -1,    -1,    27,    -1,   504,    -1,   116,
     107,   108,   109,   107,   108,   109,    -1,   534,   535,   107,
     108,   109,    -1,    45,    46,    47,    -1,   105,    50,    51,
     108,   109,   110,    56,    57,    58,    -1,    -1,    -1,   536,
      -1,    -1,    -1,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    85,    86,    -1,    -1,    89,    90,    91,
      92,    93,    -1,    95,    96,    -1,    -1,    -1,   100,   101,
     102,    37,    -1,    -1,   106,   602,   108,   109,    -1,    45,
      46,    47,    48,    49,    50,    51,    -1,   614,    -1,    55,
      56,    -1,    -1,    -1,    60,    -1,    -1,    -1,    -1,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    55,    56,    57,    58,    59,    -1,    83,    -1,    -1,
      -1,    -1,    -1,    89,    90,    91,    92,    -1,    94,    95,
      96,    -1,    98,    -1,   100,   101,   102,    -1,    -1,    -1,
     106,    -1,   108,   109,    37,    -1,    -1,    -1,    -1,    -1,
     116,   117,    45,    46,    47,    48,    49,    50,    51,    -1,
      -1,   105,    55,    56,   108,   109,   110,    60,    -1,    -1,
      -1,    -1,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      83,    55,    56,    57,    58,    59,    89,    90,    91,    92,
      93,    94,    95,    96,    -1,    98,    37,   100,   101,   102,
      -1,    -1,    -1,   106,    -1,   108,   109,    48,    49,    37,
      51,    -1,    -1,   116,    55,    56,    -1,    -1,    -1,    60,
      48,    49,    -1,    51,    -1,    -1,    -1,    55,    56,    -1,
      -1,    -1,    60,   107,   108,   109,   110,    -1,    -1,    -1,
      -1,    -1,    83,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    94,    -1,    83,    -1,    98,    55,    56,
      57,    58,    59,    37,    -1,   106,    94,    -1,    -1,    -1,
      98,    45,    46,    47,    -1,   116,    50,    51,   106,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   116,    -1,
      -1,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     107,   108,   109,   110,    -1,    89,    90,    91,    92,    -1,
      -1,    95,    96,    -1,    -1,    -1,   100,   101,   102,    -1,
      -1,    -1,   106,    -1,   108,   109,    45,    46,    47,    48,
      49,    50,    51,    -1,    -1,    -1,    55,    56,    -1,    -1,
      -1,    60,    -1,    -1,    -1,    -1,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    83,    -1,    -1,    -1,    -1,    -1,
      89,    90,    91,    92,    -1,    94,    95,    96,    -1,    98,
      -1,   100,   101,   102,    -1,    -1,    38,   106,    -1,   108,
     109,    -1,    -1,    45,    46,    47,    -1,   116,    50,    51,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    -1,    -1,    89,    90,    91,
      92,    -1,    21,    95,    96,    -1,    -1,    -1,   100,   101,
     102,    -1,    -1,    40,   106,    -1,   108,   109,    45,    46,
      47,    -1,    -1,    50,    51,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    90,    91,    92,    -1,    -1,    95,    96,
      -1,    -1,    -1,   100,   101,   102,    -1,    -1,    40,   106,
      -1,   108,   109,    45,    46,    47,    -1,    -1,    50,    51,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    90,    91,
      92,    -1,    -1,    95,    96,    -1,    -1,    -1,   100,   101,
     102,    -1,    -1,    40,   106,    -1,   108,   109,    45,    46,
      47,    -1,    -1,    50,    51,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    90,    91,    92,    -1,    -1,    95,    96,
      -1,    -1,    -1,   100,   101,   102,    -1,    -1,    40,   106,
      -1,   108,   109,    45,    46,    47,    -1,    -1,    50,    51,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    90,    91,
      92,    -1,    -1,    95,    96,    -1,    -1,    -1,   100,   101,
     102,    -1,    -1,    40,   106,    -1,   108,   109,    45,    46,
      47,    -1,    -1,    50,    51,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    90,    91,    92,    -1,    -1,    95,    96,
      -1,    -1,    -1,   100,   101,   102,    -1,    -1,    40,   106,
      -1,   108,   109,    45,    46,    47,    -1,    -1,    50,    51,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    48,    49,    -1,    51,    -1,    -1,
      -1,    55,    56,    -1,    -1,    -1,    60,    89,    90,    91,
      92,    -1,    -1,    95,    96,    -1,    -1,    -1,   100,   101,
     102,    -1,    -1,    -1,   106,    -1,   108,   109,    -1,    83,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      94,    -1,    -1,    -1,    98,    -1,    -1,    44,    45,    46,
      47,    -1,   106,    50,    51,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   116,    -1,    -1,    -1,    -1,    -1,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,
      -1,    -1,    89,    90,    91,    92,    93,    -1,    95,    96,
      -1,    -1,    -1,   100,   101,   102,    -1,    -1,    -1,   106,
      -1,   108,   109,    45,    46,    47,    -1,    -1,    50,    51,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    86,    -1,    -1,    89,    90,    91,
      92,    93,    -1,    95,    96,    -1,    -1,    -1,   100,   101,
     102,    -1,    -1,    -1,   106,    -1,   108,   109,    45,    46,
      47,    -1,    -1,    50,    51,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    90,    91,    92,    -1,    -1,    95,    96,
      -1,    -1,    -1,   100,   101,   102,    -1,    -1,    -1,   106,
      -1,   108,   109,    45,    46,    47,    -1,    -1,    50,    51,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    90,    91,
      92,    -1,    -1,    95,    96,    -1,    -1,    -1,   100,   101,
     102,    -1,    -1,    -1,   106,    -1,   108,   109,    45,    46,
      47,    -1,    -1,    50,    51,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    90,    91,    92,    -1,    -1,    95,    96,
      -1,    -1,    -1,   100,   101,   102,    -1,    -1,    -1,   106,
      -1,   108,   109,    45,    46,    47,    -1,    -1,    50,    51,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    90,    91,
      92,    -1,    -1,    95,    96,    -1,    -1,    -1,   100,   101,
     102,    -1,    -1,    -1,   106,    -1,   108,   109
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    21,   119,   120,   123,   124,   125,   126,   128,
     131,   141,   142,   151,   154,   100,   100,   100,   100,   100,
     100,   100,    99,    99,    99,    99,    14,    15,    27,   155,
       0,    20,   114,    20,   114,    16,    17,    18,    19,   114,
     132,    21,    21,    21,    21,   106,   106,   106,   106,    37,
      45,    46,    47,    48,    49,    50,    51,    55,    56,    60,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    83,    89,    90,    91,    92,    93,    94,    95,    96,
      98,   100,   101,   102,   106,   108,   109,   116,   158,   163,
     165,   166,   167,   168,    30,    44,    51,    97,   106,   158,
     162,   163,   166,    51,   106,   156,   158,   163,   113,   158,
     115,   156,    22,    51,    76,   106,   129,   137,   138,   139,
     159,   163,   166,   156,    31,   135,    35,   133,    16,    17,
     156,   133,    45,    51,    86,    93,   106,   108,   109,   148,
     149,   150,   166,   167,   148,    27,    51,    85,   143,   148,
     166,    27,    87,    88,   152,   153,   100,   127,   127,   127,
     127,    38,   165,   156,   106,   156,   106,   156,   106,   156,
     106,   156,   156,   162,   156,   156,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   114,   164,   164,   164,   106,   106,   106,   158,   166,
     168,   168,   117,   156,   159,   161,   163,   165,   166,    55,
      56,    57,    58,    59,   108,   109,   110,   105,   108,   109,
      61,    62,   110,   111,    63,    64,   106,   162,   162,   106,
     158,   162,   166,    34,    35,    36,    37,    38,    39,    41,
      42,    43,    23,    34,    35,    36,    37,    38,    39,   162,
      21,    22,   157,    23,   113,    20,   115,   165,   162,   166,
     113,   105,   139,   140,    78,    79,    80,    81,   160,   166,
     115,   166,    32,   136,    51,   109,   166,    34,   134,   113,
     115,   134,   156,   162,   106,   164,   148,   166,   150,   150,
     108,   109,   113,   110,   111,   108,   109,   110,   113,   156,
     162,    44,   106,   144,   148,   166,   113,    34,    35,    36,
     147,   147,   156,   113,   135,   105,   107,   107,   107,   107,
      38,    21,   165,    21,   165,    21,   166,    21,   166,    21,
      21,    52,    21,    21,   158,   158,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   158,    94,   166,   166,   165,
     165,   165,   165,   107,   107,    21,   117,   105,   117,   117,
      24,    25,   158,   158,   158,   158,   158,   158,   158,   158,
     166,   167,   167,   168,   168,   168,   168,   168,   156,    52,
     165,   107,   158,   158,   158,   158,   158,   158,   162,   162,
     162,   158,   166,   166,   166,   166,   166,   166,    52,   155,
     162,   158,    82,    84,   121,   122,   163,    20,    22,    52,
      77,   138,   165,   139,   166,   166,   166,   166,    20,   166,
     113,   162,    40,    40,    51,   166,   135,    16,    17,    19,
     132,   113,    21,    52,   148,   107,   149,   167,   149,   167,
     168,   168,   149,   167,   149,   167,   150,    21,    52,   144,
     144,   148,   166,    41,    42,    43,    52,    34,    35,    36,
      37,    38,    39,    34,    35,    36,    37,    38,    39,   148,
     166,   148,   166,    21,    21,   100,    20,    20,    20,    20,
     167,   107,   167,   107,   167,   107,   166,   107,   166,   167,
     158,   166,   158,   158,   105,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   105,   105,   107,   107,   105,   115,
     107,   107,   107,   163,   166,   163,   166,   166,   107,   158,
     162,   166,   107,   157,   106,   106,   105,   113,   158,   121,
     158,   166,    22,   165,   137,   166,    52,   162,   136,   135,
     133,    16,   133,   149,   167,   148,   166,   107,   143,   143,
     148,   166,   107,   144,   144,   144,   148,   166,   148,   166,
     148,   166,   148,   166,   148,   166,   148,   166,   148,   166,
     148,   148,   148,   148,   148,   148,   145,   145,    34,    35,
     145,    34,    35,   145,   152,   148,   166,   166,   162,   158,
     156,   156,    53,    53,   163,   166,   166,   166,   117,   117,
      26,   117,    26,   117,    53,   158,   158,   122,   113,   113,
      22,    33,   130,   113,   109,   166,    52,   113,   136,   134,
     113,   134,    53,    53,   147,   147,   105,   166,   166,   166,
     166,   113,   113,   113,   113,    21,    21,   158,   166,   107,
     107,   105,   105,   166,   166,   162,   105,   107,   166,   113,
      40,    53,    40,   166,   113,   135,   113,   148,   143,   148,
     166,   148,   166,   103,   104,   146,   145,   145,   145,   145,
     166,   166,    54,    54,   166,   166,   117,   117,    54,   166,
      53,   109,    53,    53,   136,    54,    54,    53,    54,    53,
      54,    53,    54,    53,    54,   107,   107,   107,   166,    40,
     166,    40,   113,   148,   166,   148,   166,   148,   166,   148,
     166,    54,    54,    54,    54,   147,   147,   147,   147,   147,
     147,   147,   147,   148,   166,   148,   166,   148,   166,   148,
     166,   148,   166,   148,   166,   148,   166,   148,   166,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
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


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
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

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
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
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */






/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  /* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;

  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 131 "src/mmlparse.y"
    { code_set_root((yyvsp[(1) - (1)].code)); ;}
    break;

  case 3:
#line 132 "src/mmlparse.y"
    { code_set_root((yyvsp[(1) - (1)].code)); ;}
    break;

  case 4:
#line 133 "src/mmlparse.y"
    { code_set_root((yyvsp[(1) - (1)].code)); ;}
    break;

  case 5:
#line 134 "src/mmlparse.y"
    { code_set_root((yyvsp[(1) - (1)].code)); ;}
    break;

  case 6:
#line 135 "src/mmlparse.y"
    { code_set_root((yyvsp[(1) - (1)].code)); ;}
    break;

  case 7:
#line 136 "src/mmlparse.y"
    { code_set_root((yyvsp[(1) - (1)].code)); ;}
    break;

  case 8:
#line 137 "src/mmlparse.y"
    { code_set_root((yyvsp[(1) - (1)].code)); ;}
    break;

  case 9:
#line 138 "src/mmlparse.y"
    { code_set_root((yyvsp[(1) - (1)].code)); ;}
    break;

  case 10:
#line 139 "src/mmlparse.y"
    { code_set_root((yyvsp[(1) - (1)].code)); ;}
    break;

  case 11:
#line 140 "src/mmlparse.y"
    { code_set_root((yyvsp[(1) - (1)].code)); ;}
    break;

  case 12:
#line 141 "src/mmlparse.y"
    { code_set_root((yyvsp[(1) - (1)].code)); ;}
    break;

  case 13:
#line 149 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_newsym_set1, 3,
            code_new_name((yyvsp[(2) - (5)].name)),                                       /* Name */
            code_new_inst(i_idxset_pseudo_new, 1,               /* index set */
               code_new_inst(i_bool_true, 0)),              
            (yyvsp[(4) - (5)].code));                                              /* initial set */
      ;}
    break;

  case 14:
#line 156 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_newsym_set1, 3,
            code_new_name((yyvsp[(2) - (8)].name)),                                       /* Name */
            (yyvsp[(4) - (8)].code),                                                 /* index set */
            (yyvsp[(7) - (8)].code));                                                      /* set */
      ;}
    break;

  case 15:
#line 162 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_newsym_set2, 3,
            code_new_name((yyvsp[(2) - (8)].name)),                                       /* Name */
            (yyvsp[(4) - (8)].code),                                                 /* index set */
            (yyvsp[(7) - (8)].code));                                   /* initial set_entry_list */
      ;}
    break;

  case 16:
#line 168 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_newsym_set2, 3,
            code_new_name((yyvsp[(2) - (7)].name)),                                       /* Name */
            code_new_inst(i_idxset_pseudo_new, 1,               /* index set */
               code_new_inst(i_bool_true, 0)),              
            (yyvsp[(6) - (7)].code));                                   /* initial set_entry_list */
      ;}
    break;

  case 17:
#line 178 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_entry_list_new, 1, (yyvsp[(1) - (1)].code)); ;}
    break;

  case 18:
#line 179 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_entry_list_add, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 19:
#line 182 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_entry_list_subsets, 2, (yyvsp[(3) - (6)].code), (yyvsp[(5) - (6)].code));
      ;}
    break;

  case 20:
#line 185 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_entry_list_powerset, 1, (yyvsp[(3) - (4)].code));
      ;}
    break;

  case 21:
#line 191 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_entry, 2, (yyvsp[(1) - (2)].code), (yyvsp[(2) - (2)].code)); ;}
    break;

  case 22:
#line 200 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_newdef, 3,
            code_new_define((yyvsp[(2) - (8)].def)),
            code_new_inst(i_tuple_new, 1, (yyvsp[(4) - (8)].code)),
            (yyvsp[(7) - (8)].code));
      ;}
    break;

  case 23:
#line 209 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_newdef, 3,
            code_new_define((yyvsp[(2) - (8)].def)),
            code_new_inst(i_tuple_new, 1, (yyvsp[(4) - (8)].code)),
            (yyvsp[(7) - (8)].code));
      ;}
    break;

  case 24:
#line 218 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_newdef, 3,
            code_new_define((yyvsp[(2) - (8)].def)),
            code_new_inst(i_tuple_new, 1, (yyvsp[(4) - (8)].code)),
            (yyvsp[(7) - (8)].code));
      ;}
    break;

  case 25:
#line 227 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_newdef, 3,
            code_new_define((yyvsp[(2) - (8)].def)),
            code_new_inst(i_tuple_new, 1, (yyvsp[(4) - (8)].code)),
            (yyvsp[(7) - (8)].code));
      ;}
    break;

  case 26:
#line 236 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_elem_list_new, 1, code_new_name((yyvsp[(1) - (1)].name)));
      ;}
    break;

  case 27:
#line 239 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_elem_list_add, 2, (yyvsp[(1) - (3)].code), code_new_name((yyvsp[(3) - (3)].name)));
      ;}
    break;

  case 28:
#line 249 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_newsym_para1, 4, code_new_name((yyvsp[(2) - (9)].name)), (yyvsp[(4) - (9)].code), (yyvsp[(7) - (9)].code), (yyvsp[(8) - (9)].code));
      ;}
    break;

  case 29:
#line 252 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_newsym_para2, 4, code_new_name((yyvsp[(2) - (8)].name)), (yyvsp[(4) - (8)].code), (yyvsp[(7) - (8)].code), code_new_inst(i_nop, 0));
      ;}
    break;

  case 30:
#line 255 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_newsym_para1, 4,
            code_new_name((yyvsp[(2) - (5)].name)),
            code_new_inst(i_idxset_pseudo_new, 1, code_new_inst(i_bool_true, 0)),
            (yyvsp[(4) - (5)].code),
            code_new_inst(i_nop, 0));
      ;}
    break;

  case 31:
#line 262 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_nop, 0); ;}
    break;

  case 32:
#line 265 "src/mmlparse.y"
    { (yyval.code) = (yyvsp[(1) - (1)].code); ;}
    break;

  case 33:
#line 266 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_entry_list_new, 1,
            code_new_inst(i_entry, 2, code_new_inst(i_tuple_empty, 0), (yyvsp[(1) - (1)].code)));
      ;}
    break;

  case 34:
#line 273 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_nop, 0); ;}
    break;

  case 35:
#line 274 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_entry, 2, code_new_inst(i_tuple_empty, 0), (yyvsp[(2) - (2)].code)); ;}
    break;

  case 36:
#line 282 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_newsym_var, 7,
            code_new_name((yyvsp[(2) - (9)].name)),
            (yyvsp[(4) - (9)].code), (yyvsp[(6) - (9)].code), (yyvsp[(7) - (9)].code), (yyvsp[(8) - (9)].code),
            code_new_numb(numb_new_integer(0)),
            code_new_numb(numb_new_integer(0)));
      ;}
    break;

  case 37:
#line 289 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_newsym_var, 7,
            code_new_name((yyvsp[(2) - (6)].name)),
            code_new_inst(i_idxset_pseudo_new, 1,
               code_new_inst(i_bool_true, 0)),              
            (yyvsp[(3) - (6)].code), (yyvsp[(4) - (6)].code), (yyvsp[(5) - (6)].code),
            code_new_numb(numb_new_integer(0)),
            code_new_numb(numb_new_integer(0)));
      ;}
    break;

  case 38:
#line 298 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_newsym_var, 7,
            code_new_name((yyvsp[(2) - (8)].name)),
            (yyvsp[(4) - (8)].code),
            code_new_varclass(VAR_IMP),
            code_new_inst(i_bound_new, 1, code_new_numb(numb_new_integer(0))),
            code_new_inst(i_bound_new, 1, code_new_numb(numb_new_integer(1))),
            code_new_numb(numb_new_integer(0)),
            code_new_numb(numb_new_integer(0)));
      ;}
    break;

  case 39:
#line 308 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_newsym_var, 7,
            code_new_name((yyvsp[(2) - (5)].name)),
            code_new_inst(i_idxset_pseudo_new, 1,
               code_new_inst(i_bool_true, 0)),              
            code_new_varclass(VAR_IMP),
            code_new_inst(i_bound_new, 1, code_new_numb(numb_new_integer(0))),
            code_new_inst(i_bound_new, 1, code_new_numb(numb_new_integer(1))),
            code_new_numb(numb_new_integer(0)),
            code_new_numb(numb_new_integer(0)));
      ;}
    break;

  case 40:
#line 319 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_newsym_var, 7,
            code_new_name((yyvsp[(2) - (9)].name)),
            (yyvsp[(4) - (9)].code),
            code_new_varclass(VAR_INT),
            code_new_inst(i_bound_new, 1, code_new_numb(numb_new_integer(0))),
            code_new_inst(i_bound_new, 1, code_new_numb(numb_new_integer(1))),
            (yyvsp[(7) - (9)].code), (yyvsp[(8) - (9)].code));
      ;}
    break;

  case 41:
#line 328 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_newsym_var, 7,
            code_new_name((yyvsp[(2) - (6)].name)),
            code_new_inst(i_idxset_pseudo_new, 1,
               code_new_inst(i_bool_true, 0)),              
            code_new_varclass(VAR_INT),
            code_new_inst(i_bound_new, 1, code_new_numb(numb_new_integer(0))),
            code_new_inst(i_bound_new, 1, code_new_numb(numb_new_integer(1))),
            (yyvsp[(4) - (6)].code), (yyvsp[(5) - (6)].code));
      ;}
    break;

  case 42:
#line 338 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_newsym_var, 7,
            code_new_name((yyvsp[(2) - (11)].name)), (yyvsp[(4) - (11)].code), code_new_varclass(VAR_INT), (yyvsp[(7) - (11)].code), (yyvsp[(8) - (11)].code), (yyvsp[(9) - (11)].code), (yyvsp[(10) - (11)].code));
      ;}
    break;

  case 43:
#line 342 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_newsym_var, 7,
            code_new_name((yyvsp[(2) - (8)].name)),
            code_new_inst(i_idxset_pseudo_new, 1,
               code_new_inst(i_bool_true, 0)),              
            code_new_varclass(VAR_INT), (yyvsp[(4) - (8)].code), (yyvsp[(5) - (8)].code), (yyvsp[(6) - (8)].code), (yyvsp[(7) - (8)].code));
      ;}
    break;

  case 44:
#line 352 "src/mmlparse.y"
    { (yyval.code) = code_new_varclass(VAR_CON); ;}
    break;

  case 45:
#line 353 "src/mmlparse.y"
    { (yyval.code) = code_new_varclass(VAR_CON); ;}
    break;

  case 46:
#line 354 "src/mmlparse.y"
    { (yyval.code) = code_new_varclass(VAR_IMP); ;}
    break;

  case 47:
#line 358 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_bound_new, 1, code_new_numb(numb_new_integer(0)));
      ;}
    break;

  case 48:
#line 361 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_bound_new, 1, (yyvsp[(2) - (2)].code)); ;}
    break;

  case 49:
#line 362 "src/mmlparse.y"
    { (yyval.code) = code_new_bound(BOUND_MINUS_INFTY); ;}
    break;

  case 50:
#line 363 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_expr_if, 3, (yyvsp[(3) - (9)].code),
            code_new_inst(i_bound_new, 1, (yyvsp[(5) - (9)].code)),
            code_new_bound(BOUND_MINUS_INFTY));
      ;}
    break;

  case 51:
#line 368 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_expr_if, 3, (yyvsp[(3) - (9)].code),
            code_new_bound(BOUND_MINUS_INFTY),
            code_new_inst(i_bound_new, 1, (yyvsp[(8) - (9)].code)));
      ;}
    break;

  case 52:
#line 376 "src/mmlparse.y"
    { (yyval.code) = code_new_bound(BOUND_INFTY); ;}
    break;

  case 53:
#line 377 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_bound_new, 1, (yyvsp[(2) - (2)].code)); ;}
    break;

  case 54:
#line 378 "src/mmlparse.y"
    { (yyval.code) = code_new_bound(BOUND_INFTY); ;}
    break;

  case 55:
#line 379 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_expr_if, 3, (yyvsp[(3) - (8)].code),
            code_new_inst(i_bound_new, 1, (yyvsp[(5) - (8)].code)),
            code_new_bound(BOUND_INFTY));
      ;}
    break;

  case 56:
#line 384 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_expr_if, 3, (yyvsp[(3) - (8)].code),
            code_new_bound(BOUND_INFTY),
            code_new_inst(i_bound_new, 1, (yyvsp[(7) - (8)].code)));
      ;}
    break;

  case 57:
#line 392 "src/mmlparse.y"
    { (yyval.code) = code_new_numb(numb_new_integer(0)); ;}
    break;

  case 58:
#line 393 "src/mmlparse.y"
    { (yyval.code) = (yyvsp[(2) - (2)].code); ;}
    break;

  case 59:
#line 397 "src/mmlparse.y"
    { (yyval.code) = code_new_numb(numb_new_integer(0)); ;}
    break;

  case 60:
#line 398 "src/mmlparse.y"
    { (yyval.code) = (yyvsp[(2) - (2)].code); ;}
    break;

  case 61:
#line 406 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_entry_list_new, 1, (yyvsp[(1) - (1)].code)); ;}
    break;

  case 62:
#line 407 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_entry_list_add, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 63:
#line 410 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_read, 1, (yyvsp[(1) - (1)].code)); ;}
    break;

  case 64:
#line 411 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_list_matrix, 2, (yyvsp[(1) - (2)].code), (yyvsp[(2) - (2)].code)); ;}
    break;

  case 65:
#line 415 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_entry, 2, (yyvsp[(1) - (2)].code), (yyvsp[(2) - (2)].code)); ;}
    break;

  case 66:
#line 419 "src/mmlparse.y"
    { (yyval.code) = (yyvsp[(2) - (3)].code); ;}
    break;

  case 67:
#line 423 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_matrix_list_new, 2, (yyvsp[(1) - (3)].code), (yyvsp[(2) - (3)].code));
      ;}
    break;

  case 68:
#line 426 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_matrix_list_add, 3, (yyvsp[(1) - (4)].code), (yyvsp[(2) - (4)].code), (yyvsp[(3) - (4)].code));
      ;}
    break;

  case 69:
#line 438 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_object_min, 2, code_new_name((yyvsp[(2) - (5)].name)), (yyvsp[(4) - (5)].code));
      ;}
    break;

  case 70:
#line 441 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_object_max, 2, code_new_name((yyvsp[(2) - (5)].name)), (yyvsp[(4) - (5)].code));
      ;}
    break;

  case 71:
#line 451 "src/mmlparse.y"
    {
        (yyval.code) = code_new_inst(i_subto, 2, code_new_name((yyvsp[(2) - (5)].name)), (yyvsp[(4) - (5)].code));
     ;}
    break;

  case 72:
#line 457 "src/mmlparse.y"
    {
        (yyval.code) = code_new_inst(i_constraint, 4, (yyvsp[(1) - (4)].code), (yyvsp[(2) - (4)].code), (yyvsp[(3) - (4)].code), code_new_bits((yyvsp[(4) - (4)].bits)));
     ;}
    break;

  case 73:
#line 460 "src/mmlparse.y"
    {
        (yyval.code) = code_new_inst(i_constraint, 4, (yyvsp[(1) - (4)].code), (yyvsp[(2) - (4)].code),
           code_new_inst(i_term_expr, 1, (yyvsp[(3) - (4)].code)),
           code_new_bits((yyvsp[(4) - (4)].bits)));
     ;}
    break;

  case 74:
#line 465 "src/mmlparse.y"
    {
        (yyval.code) = code_new_inst(i_constraint, 4,
           code_new_inst(i_term_expr, 1, (yyvsp[(1) - (4)].code)),
           (yyvsp[(2) - (4)].code), (yyvsp[(3) - (4)].code), code_new_bits((yyvsp[(4) - (4)].bits)));
     ;}
    break;

  case 75:
#line 470 "src/mmlparse.y"
    { 
        (yyval.code) = code_new_inst(i_constraint, 4,
           code_new_inst(i_term_expr, 1, (yyvsp[(1) - (4)].code)),
           (yyvsp[(2) - (4)].code),
           code_new_inst(i_term_expr, 1, (yyvsp[(3) - (4)].code)),
           code_new_bits((yyvsp[(4) - (4)].bits)));
     ;}
    break;

  case 76:
#line 477 "src/mmlparse.y"
    {
        (yyval.code) = code_new_inst(i_rangeconst, 6, (yyvsp[(1) - (6)].code), (yyvsp[(3) - (6)].code), (yyvsp[(5) - (6)].code), (yyvsp[(2) - (6)].code),
           code_new_contype(CON_RHS), code_new_bits((yyvsp[(6) - (6)].bits))); 
     ;}
    break;

  case 77:
#line 481 "src/mmlparse.y"
    {
        (yyval.code) = code_new_inst(i_rangeconst, 6, (yyvsp[(1) - (6)].code),
           code_new_inst(i_term_expr, 1, (yyvsp[(3) - (6)].code)), (yyvsp[(5) - (6)].code), (yyvsp[(2) - (6)].code),
           code_new_contype(CON_RHS), code_new_bits((yyvsp[(6) - (6)].bits))); 
     ;}
    break;

  case 78:
#line 486 "src/mmlparse.y"
    {
        (yyval.code) = code_new_inst(i_rangeconst, 6, (yyvsp[(5) - (6)].code), (yyvsp[(3) - (6)].code), (yyvsp[(1) - (6)].code), (yyvsp[(2) - (6)].code),
           code_new_contype(CON_LHS), code_new_bits((yyvsp[(6) - (6)].bits))); 
     ;}
    break;

  case 79:
#line 490 "src/mmlparse.y"
    {
        (yyval.code) = code_new_inst(i_rangeconst, 6, (yyvsp[(5) - (6)].code),
           code_new_inst(i_term_expr, 1, (yyvsp[(3) - (6)].code)),
           (yyvsp[(1) - (6)].code), (yyvsp[(2) - (6)].code),
           code_new_contype(CON_LHS), code_new_bits((yyvsp[(6) - (6)].bits))); 
     ;}
    break;

  case 80:
#line 496 "src/mmlparse.y"
    {
        (yyval.code) = code_new_inst(i_forall, 2, (yyvsp[(2) - (4)].code), (yyvsp[(4) - (4)].code));
     ;}
    break;

  case 81:
#line 499 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_expr_if, 3, (yyvsp[(2) - (7)].code), (yyvsp[(4) - (7)].code), (yyvsp[(6) - (7)].code));
      ;}
    break;

  case 82:
#line 502 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_vif_else, 7, (yyvsp[(2) - (11)].code), (yyvsp[(4) - (11)].code), (yyvsp[(5) - (11)].code), (yyvsp[(6) - (11)].code), (yyvsp[(8) - (11)].code), (yyvsp[(9) - (11)].code), (yyvsp[(10) - (11)].code));
      ;}
    break;

  case 83:
#line 505 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_vif_else, 7, (yyvsp[(2) - (11)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(4) - (11)].code)),
            (yyvsp[(5) - (11)].code), (yyvsp[(6) - (11)].code), (yyvsp[(8) - (11)].code), (yyvsp[(9) - (11)].code), (yyvsp[(10) - (11)].code));
      ;}
    break;

  case 84:
#line 510 "src/mmlparse.y"
    { 
         (yyval.code) = code_new_inst(i_vif_else, 7, (yyvsp[(2) - (11)].code), (yyvsp[(4) - (11)].code), (yyvsp[(5) - (11)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(6) - (11)].code)),
            (yyvsp[(8) - (11)].code), (yyvsp[(9) - (11)].code), (yyvsp[(10) - (11)].code));
      ;}
    break;

  case 85:
#line 515 "src/mmlparse.y"
    { 
         (yyval.code) = code_new_inst(i_vif_else, 7, (yyvsp[(2) - (11)].code), (yyvsp[(4) - (11)].code), (yyvsp[(5) - (11)].code), (yyvsp[(6) - (11)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(8) - (11)].code)),
            (yyvsp[(9) - (11)].code), (yyvsp[(10) - (11)].code));
      ;}
    break;

  case 86:
#line 520 "src/mmlparse.y"
    { 
         (yyval.code) = code_new_inst(i_vif_else, 7, (yyvsp[(2) - (11)].code), (yyvsp[(4) - (11)].code), (yyvsp[(5) - (11)].code), (yyvsp[(6) - (11)].code), (yyvsp[(8) - (11)].code), (yyvsp[(9) - (11)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(10) - (11)].code)));
      ;}
    break;

  case 87:
#line 524 "src/mmlparse.y"
    { /* ??? This is an error */
         (yyval.code) = code_new_inst(i_vif_else, 7, (yyvsp[(2) - (11)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(4) - (11)].code)),
            (yyvsp[(5) - (11)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(6) - (11)].code)),
            (yyvsp[(8) - (11)].code), (yyvsp[(9) - (11)].code), (yyvsp[(10) - (11)].code));
      ;}
    break;

  case 88:
#line 531 "src/mmlparse.y"
    { 
         (yyval.code) = code_new_inst(i_vif_else, 7, (yyvsp[(2) - (11)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(4) - (11)].code)),
            (yyvsp[(5) - (11)].code), (yyvsp[(6) - (11)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(8) - (11)].code)),
            (yyvsp[(9) - (11)].code), (yyvsp[(10) - (11)].code));
      ;}
    break;

  case 89:
#line 538 "src/mmlparse.y"
    { 
         (yyval.code) = code_new_inst(i_vif_else, 7, (yyvsp[(2) - (11)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(4) - (11)].code)),
            (yyvsp[(5) - (11)].code), (yyvsp[(6) - (11)].code), (yyvsp[(8) - (11)].code), (yyvsp[(9) - (11)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(10) - (11)].code)));
      ;}
    break;

  case 90:
#line 544 "src/mmlparse.y"
    { 
         (yyval.code) = code_new_inst(i_vif_else, 7, (yyvsp[(2) - (11)].code), (yyvsp[(4) - (11)].code), (yyvsp[(5) - (11)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(6) - (11)].code)),
            code_new_inst(i_term_expr, 1, (yyvsp[(8) - (11)].code)),
            (yyvsp[(9) - (11)].code), (yyvsp[(10) - (11)].code));
      ;}
    break;

  case 91:
#line 550 "src/mmlparse.y"
    { 
         (yyval.code) = code_new_inst(i_vif_else, 7, (yyvsp[(2) - (11)].code), (yyvsp[(4) - (11)].code), (yyvsp[(5) - (11)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(6) - (11)].code)),
            (yyvsp[(8) - (11)].code), (yyvsp[(9) - (11)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(10) - (11)].code)));
      ;}
    break;

  case 92:
#line 556 "src/mmlparse.y"
    { /* ??? This is an error */
         (yyval.code) = code_new_inst(i_vif_else, 7, (yyvsp[(2) - (11)].code), (yyvsp[(4) - (11)].code), (yyvsp[(5) - (11)].code), (yyvsp[(6) - (11)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(8) - (11)].code)), (yyvsp[(9) - (11)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(10) - (11)].code)));
      ;}
    break;

  case 93:
#line 561 "src/mmlparse.y"
    { /* ??? This is an error */
         (yyval.code) = code_new_inst(i_vif_else, 7, (yyvsp[(2) - (11)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(4) - (11)].code)),
            (yyvsp[(5) - (11)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(6) - (11)].code)),
            code_new_inst(i_term_expr, 1, (yyvsp[(8) - (11)].code)),
            (yyvsp[(9) - (11)].code), (yyvsp[(10) - (11)].code));
      ;}
    break;

  case 94:
#line 569 "src/mmlparse.y"
    { /* ??? This is an error */
         (yyval.code) = code_new_inst(i_vif_else, 7, (yyvsp[(2) - (11)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(4) - (11)].code)),
            (yyvsp[(5) - (11)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(6) - (11)].code)),
            (yyvsp[(8) - (11)].code), (yyvsp[(9) - (11)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(10) - (11)].code)));
      ;}
    break;

  case 95:
#line 577 "src/mmlparse.y"
    { /* ??? This is an error */
         (yyval.code) = code_new_inst(i_vif_else, 7, (yyvsp[(2) - (11)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(4) - (11)].code)),
            (yyvsp[(5) - (11)].code), (yyvsp[(6) - (11)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(8) - (11)].code)),
            (yyvsp[(9) - (11)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(10) - (11)].code)));
      ;}
    break;

  case 96:
#line 585 "src/mmlparse.y"
    { /* ??? This is an error */
         (yyval.code) = code_new_inst(i_vif_else, 7, (yyvsp[(2) - (11)].code), (yyvsp[(4) - (11)].code), (yyvsp[(5) - (11)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(6) - (11)].code)),
            code_new_inst(i_term_expr, 1, (yyvsp[(8) - (11)].code)),
            (yyvsp[(9) - (11)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(10) - (11)].code)));
      ;}
    break;

  case 97:
#line 592 "src/mmlparse.y"
    { /* ??? This is an error */
         (yyval.code) = code_new_inst(i_vif_else, 7, (yyvsp[(2) - (11)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(4) - (11)].code)),
            (yyvsp[(5) - (11)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(6) - (11)].code)),
            code_new_inst(i_term_expr, 1, (yyvsp[(8) - (11)].code)),
            (yyvsp[(9) - (11)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(10) - (11)].code)));
      ;}
    break;

  case 98:
#line 602 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_vif, 4, (yyvsp[(2) - (7)].code), (yyvsp[(4) - (7)].code), (yyvsp[(5) - (7)].code), (yyvsp[(6) - (7)].code));
      ;}
    break;

  case 99:
#line 605 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_vif, 4, (yyvsp[(2) - (7)].code), code_new_inst(i_term_expr, 1, (yyvsp[(4) - (7)].code)), (yyvsp[(5) - (7)].code), (yyvsp[(6) - (7)].code));
      ;}
    break;

  case 100:
#line 608 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_vif, 4, (yyvsp[(2) - (7)].code), (yyvsp[(4) - (7)].code), (yyvsp[(5) - (7)].code), code_new_inst(i_term_expr, 1, (yyvsp[(6) - (7)].code)));
      ;}
    break;

  case 101:
#line 611 "src/mmlparse.y"
    { /* ??? This is an error */
         (yyval.code) = code_new_inst(i_vif, 4, (yyvsp[(2) - (7)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(4) - (7)].code)), (yyvsp[(5) - (7)].code), code_new_inst(i_term_expr, 1, (yyvsp[(6) - (7)].code)));
      ;}
    break;

  case 102:
#line 618 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_vbool_ne, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 103:
#line 619 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_vbool_ne, 2, code_new_inst(i_term_expr, 1, (yyvsp[(1) - (3)].code)), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 104:
#line 622 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_vbool_ne, 2, (yyvsp[(1) - (3)].code), code_new_inst(i_term_expr, 1, (yyvsp[(3) - (3)].code)));
      ;}
    break;

  case 105:
#line 625 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_vbool_eq, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 106:
#line 626 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_vbool_eq, 2, code_new_inst(i_term_expr, 1, (yyvsp[(1) - (3)].code)), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 107:
#line 629 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_vbool_eq, 2, (yyvsp[(1) - (3)].code), code_new_inst(i_term_expr, 1, (yyvsp[(3) - (3)].code)));
      ;}
    break;

  case 108:
#line 632 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_vbool_le, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 109:
#line 633 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_vbool_le, 2, code_new_inst(i_term_expr, 1, (yyvsp[(1) - (3)].code)), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 110:
#line 636 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_vbool_le, 2, (yyvsp[(1) - (3)].code), code_new_inst(i_term_expr, 1, (yyvsp[(3) - (3)].code)));
      ;}
    break;

  case 111:
#line 639 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_vbool_ge, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 112:
#line 640 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_vbool_ge, 2, code_new_inst(i_term_expr, 1, (yyvsp[(1) - (3)].code)), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 113:
#line 643 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_vbool_ge, 2, (yyvsp[(1) - (3)].code), code_new_inst(i_term_expr, 1, (yyvsp[(3) - (3)].code)));
      ;}
    break;

  case 114:
#line 646 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_vbool_lt, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 115:
#line 647 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_vbool_lt, 2, code_new_inst(i_term_expr, 1, (yyvsp[(1) - (3)].code)), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 116:
#line 650 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_vbool_lt, 2, (yyvsp[(1) - (3)].code), code_new_inst(i_term_expr, 1, (yyvsp[(3) - (3)].code)));
      ;}
    break;

  case 117:
#line 653 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_vbool_gt, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 118:
#line 654 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_vbool_gt, 2, code_new_inst(i_term_expr, 1, (yyvsp[(1) - (3)].code)), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 119:
#line 657 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_vbool_gt, 2, (yyvsp[(1) - (3)].code), code_new_inst(i_term_expr, 1, (yyvsp[(3) - (3)].code)));
      ;}
    break;

  case 120:
#line 660 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_vbool_and, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 121:
#line 661 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_vbool_or,  2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 122:
#line 662 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_vbool_xor, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 123:
#line 663 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_vbool_not, 1, (yyvsp[(2) - (2)].code));; ;}
    break;

  case 124:
#line 664 "src/mmlparse.y"
    { (yyval.code) = (yyvsp[(2) - (3)].code); ;}
    break;

  case 125:
#line 668 "src/mmlparse.y"
    { (yyval.bits) = 0; ;}
    break;

  case 126:
#line 669 "src/mmlparse.y"
    { (yyval.bits) = (yyvsp[(1) - (3)].bits) | (yyvsp[(3) - (3)].bits); ;}
    break;

  case 127:
#line 673 "src/mmlparse.y"
    { (yyval.bits) = LP_FLAG_CON_SCALE; ;}
    break;

  case 128:
#line 674 "src/mmlparse.y"
    { (yyval.bits) = LP_FLAG_CON_SEPAR; ;}
    break;

  case 129:
#line 678 "src/mmlparse.y"
    { (yyval.code) = code_new_contype(CON_RHS); ;}
    break;

  case 130:
#line 679 "src/mmlparse.y"
    { (yyval.code) = code_new_contype(CON_LHS); ;}
    break;

  case 131:
#line 680 "src/mmlparse.y"
    { (yyval.code) = code_new_contype(CON_EQUAL); ;}
    break;

  case 132:
#line 684 "src/mmlparse.y"
    { (yyval.code) = (yyvsp[(1) - (1)].code); ;}
    break;

  case 133:
#line 685 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_term_add, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 134:
#line 686 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_term_sub, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 135:
#line 687 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_term_const, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 136:
#line 688 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_term_sub, 2, (yyvsp[(1) - (3)].code), code_new_inst(i_term_expr, 1, (yyvsp[(3) - (3)].code)));
      ;}
    break;

  case 137:
#line 691 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_term_const, 2, (yyvsp[(3) - (3)].code), (yyvsp[(1) - (3)].code)); ;}
    break;

  case 138:
#line 692 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_term_sub, 2,
            code_new_inst(i_term_expr, 1, (yyvsp[(1) - (3)].code)),
            (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 139:
#line 700 "src/mmlparse.y"
    { (yyval.code) = (yyvsp[(1) - (1)].code); ;}
    break;

  case 140:
#line 701 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_term_coeff, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); /*???*/ ;}
    break;

  case 141:
#line 702 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_term_coeff, 2, (yyvsp[(1) - (3)].code),
            code_new_inst(i_expr_div, 2, code_new_numb(numb_new_integer(1)), (yyvsp[(3) - (3)].code)));
      ;}
    break;

  case 142:
#line 706 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_term_coeff, 2, (yyvsp[(3) - (3)].code), (yyvsp[(1) - (3)].code)); ;}
    break;

  case 143:
#line 710 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_symbol_deref, 2, code_new_symbol((yyvsp[(1) - (2)].sym)), (yyvsp[(2) - (2)].code));
      ;}
    break;

  case 144:
#line 713 "src/mmlparse.y"
    { (yyval.code) = (yyvsp[(2) - (2)].code); ;}
    break;

  case 145:
#line 714 "src/mmlparse.y"
    { 
         (yyval.code) = code_new_inst(i_term_coeff, 2, (yyvsp[(2) - (2)].code), code_new_numb(numb_new_integer(-1)));
      ;}
    break;

  case 146:
#line 717 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_vabs, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 147:
#line 718 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_term_sum, 2, (yyvsp[(2) - (4)].code), (yyvsp[(4) - (4)].code));
      ;}
    break;

  case 148:
#line 722 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_expr_if, 3, (yyvsp[(2) - (7)].code), (yyvsp[(4) - (7)].code), (yyvsp[(6) - (7)].code));
      ;}
    break;

  case 149:
#line 725 "src/mmlparse.y"
    { (yyval.code) = (yyvsp[(2) - (3)].code); ;}
    break;

  case 150:
#line 733 "src/mmlparse.y"
    {
        (yyval.code) = code_new_inst(i_sos, 2, code_new_name((yyvsp[(2) - (5)].name)), (yyvsp[(4) - (5)].code));
     ;}
    break;

  case 151:
#line 739 "src/mmlparse.y"
    {
        (yyval.code) = code_new_inst(i_soset, 3, (yyvsp[(4) - (4)].code), (yyvsp[(1) - (4)].code), (yyvsp[(2) - (4)].code));
     ;}
    break;

  case 152:
#line 742 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_forall, 2, (yyvsp[(2) - (4)].code), (yyvsp[(4) - (4)].code));
      ;}
    break;

  case 153:
#line 748 "src/mmlparse.y"
    { (yyval.code) = code_new_numb(numb_new_integer(1)); ;}
    break;

  case 154:
#line 749 "src/mmlparse.y"
    { (yyval.code) = code_new_numb(numb_new_integer(1)); ;}
    break;

  case 155:
#line 750 "src/mmlparse.y"
    { (yyval.code) = code_new_numb(numb_new_integer(2)); ;}
    break;

  case 156:
#line 758 "src/mmlparse.y"
    { (yyval.code) = (yyvsp[(2) - (3)].code); ;}
    break;

  case 157:
#line 762 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_print, 1, (yyvsp[(2) - (2)].code)); ;}
    break;

  case 158:
#line 763 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_print, 1, (yyvsp[(2) - (2)].code)); ;}
    break;

  case 159:
#line 764 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_print, 1, (yyvsp[(2) - (2)].code)); ;}
    break;

  case 160:
#line 765 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_print, 1, code_new_symbol((yyvsp[(2) - (2)].sym))); ;}
    break;

  case 161:
#line 766 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_check, 1, (yyvsp[(2) - (2)].code)); ;}
    break;

  case 162:
#line 767 "src/mmlparse.y"
    {
        (yyval.code) = code_new_inst(i_forall, 2, (yyvsp[(2) - (4)].code), (yyvsp[(4) - (4)].code));
     ;}
    break;

  case 163:
#line 777 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_idxset_new, 3, (yyvsp[(1) - (4)].code), (yyvsp[(3) - (4)].code), (yyvsp[(4) - (4)].code));
      ;}
    break;

  case 164:
#line 780 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_idxset_new, 3,
            code_new_inst(i_tuple_empty, 0), (yyvsp[(1) - (2)].code), (yyvsp[(2) - (2)].code));
      ;}
    break;

  case 165:
#line 787 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_bool_true, 0); ;}
    break;

  case 166:
#line 788 "src/mmlparse.y"
    { (yyval.code) = (yyvsp[(2) - (2)].code); ;}
    break;

  case 167:
#line 792 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_symbol_deref, 2, code_new_symbol((yyvsp[(1) - (2)].sym)), (yyvsp[(2) - (2)].code));
      ;}
    break;

  case 168:
#line 795 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_define_deref, 2,
            code_new_define((yyvsp[(1) - (4)].def)),
            code_new_inst(i_tuple_new, 1, (yyvsp[(3) - (4)].code)));
      ;}
    break;

  case 169:
#line 800 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_set_empty, 1, code_new_size(0)); ;}
    break;

  case 170:
#line 801 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_set_range2, 3, (yyvsp[(2) - (7)].code), (yyvsp[(4) - (7)].code), (yyvsp[(6) - (7)].code));
      ;}
    break;

  case 171:
#line 804 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_set_range2, 3, (yyvsp[(2) - (5)].code), (yyvsp[(4) - (5)].code), code_new_numb(numb_new_integer(1)));
      ;}
    break;

  case 172:
#line 807 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_set_range, 3, (yyvsp[(2) - (7)].code), (yyvsp[(4) - (7)].code), (yyvsp[(6) - (7)].code));
      ;}
    break;

  case 173:
#line 810 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_set_range, 3, (yyvsp[(2) - (5)].code), (yyvsp[(4) - (5)].code), code_new_numb(numb_new_integer(1)));
      ;}
    break;

  case 174:
#line 813 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_set_union2, 2, (yyvsp[(2) - (4)].code), (yyvsp[(4) - (4)].code)); ;}
    break;

  case 175:
#line 814 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_set_union, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 176:
#line 815 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_set_union, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 177:
#line 818 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_set_sdiff, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 178:
#line 819 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_set_minus, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 179:
#line 820 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_set_minus, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 180:
#line 823 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_set_cross, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 181:
#line 824 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_set_cross, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 182:
#line 827 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_set_inter, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 183:
#line 828 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_set_inter2, 2, (yyvsp[(2) - (4)].code), (yyvsp[(4) - (4)].code)); ;}
    break;

  case 184:
#line 829 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_set_argmin, 3, code_new_numb(numb_new_integer(1)), (yyvsp[(2) - (4)].code), (yyvsp[(4) - (4)].code));
      ;}
    break;

  case 185:
#line 832 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_set_argmin, 3, (yyvsp[(3) - (7)].code), (yyvsp[(5) - (7)].code), (yyvsp[(7) - (7)].code));
      ;}
    break;

  case 186:
#line 835 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_set_argmax, 3, code_new_numb(numb_new_integer(1)), (yyvsp[(2) - (4)].code), (yyvsp[(4) - (4)].code));
      ;}
    break;

  case 187:
#line 838 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_set_argmax, 3, (yyvsp[(3) - (7)].code), (yyvsp[(5) - (7)].code), (yyvsp[(7) - (7)].code));
      ;}
    break;

  case 188:
#line 841 "src/mmlparse.y"
    { (yyval.code) = (yyvsp[(2) - (3)].code); ;}
    break;

  case 189:
#line 842 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_set_new_tuple, 1, (yyvsp[(2) - (3)].code)); ;}
    break;

  case 190:
#line 843 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_set_new_elem, 1, (yyvsp[(2) - (3)].code)); ;}
    break;

  case 191:
#line 844 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_set_idxset, 1, (yyvsp[(2) - (3)].code)); ;}
    break;

  case 192:
#line 845 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_set_expr, 2, (yyvsp[(2) - (5)].code), (yyvsp[(4) - (5)].code)); ;}
    break;

  case 193:
#line 846 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_set_expr, 2, (yyvsp[(2) - (5)].code), (yyvsp[(4) - (5)].code)); ;}
    break;

  case 194:
#line 847 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_set_proj, 2, (yyvsp[(3) - (6)].code), (yyvsp[(5) - (6)].code));
       ;}
    break;

  case 195:
#line 850 "src/mmlparse.y"
    {
          (yyval.code) = code_new_inst(i_set_indexset, 1, code_new_symbol((yyvsp[(3) - (4)].sym)));
       ;}
    break;

  case 196:
#line 853 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_expr_if, 3, (yyvsp[(2) - (7)].code), (yyvsp[(4) - (7)].code), (yyvsp[(6) - (7)].code));
      ;}
    break;

  case 197:
#line 859 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_read_new, 2, (yyvsp[(2) - (4)].code), (yyvsp[(4) - (4)].code)); ;}
    break;

  case 198:
#line 860 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_read_param, 2, (yyvsp[(1) - (2)].code), (yyvsp[(2) - (2)].code)); ;}
    break;

  case 199:
#line 864 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_read_skip, 1, (yyvsp[(2) - (2)].code)); ;}
    break;

  case 200:
#line 865 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_read_use, 1, (yyvsp[(2) - (2)].code)); ;}
    break;

  case 201:
#line 866 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_read_comment, 1, (yyvsp[(2) - (2)].code)); ;}
    break;

  case 202:
#line 867 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_read_match, 1, (yyvsp[(2) - (2)].code)); ;}
    break;

  case 203:
#line 871 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_tuple_list_new, 1, (yyvsp[(1) - (1)].code));
      ;}
    break;

  case 204:
#line 874 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_tuple_list_add, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 205:
#line 877 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_read, 1, (yyvsp[(1) - (1)].code)); ;}
    break;

  case 206:
#line 881 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_bool_eq, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 207:
#line 882 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_bool_ne, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 208:
#line 883 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_bool_gt, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 209:
#line 884 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_bool_ge, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 210:
#line 885 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_bool_lt, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 211:
#line 886 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_bool_le, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 212:
#line 887 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_bool_seq, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 213:
#line 888 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_bool_sneq, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 214:
#line 889 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_bool_subs, 2, (yyvsp[(3) - (3)].code), (yyvsp[(1) - (3)].code)); ;}
    break;

  case 215:
#line 890 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_bool_sseq, 2, (yyvsp[(3) - (3)].code), (yyvsp[(1) - (3)].code)); ;}
    break;

  case 216:
#line 891 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_bool_subs, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 217:
#line 892 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_bool_sseq, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 218:
#line 893 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_bool_and, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 219:
#line 894 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_bool_or,  2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 220:
#line 895 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_bool_xor, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 221:
#line 896 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_bool_not, 1, (yyvsp[(2) - (2)].code)); ;}
    break;

  case 222:
#line 897 "src/mmlparse.y"
    { (yyval.code) = (yyvsp[(2) - (3)].code); ;}
    break;

  case 223:
#line 898 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_bool_is_elem, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 224:
#line 899 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_bool_exists, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 225:
#line 900 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_define_deref, 2,
            code_new_define((yyvsp[(1) - (4)].def)),
            code_new_inst(i_tuple_new, 1, (yyvsp[(3) - (4)].code)));
      ;}
    break;

  case 226:
#line 905 "src/mmlparse.y"
    {
        (yyval.code) = code_new_inst(i_expr_if, 3, (yyvsp[(2) - (7)].code), (yyvsp[(4) - (7)].code), (yyvsp[(6) - (7)].code));
     ;}
    break;

  case 227:
#line 911 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_tuple_empty, 0); ;}
    break;

  case 228:
#line 912 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_tuple_new, 1, (yyvsp[(2) - (3)].code));  ;}
    break;

  case 229:
#line 916 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_tuple_empty, 0);
      ;}
    break;

  case 230:
#line 919 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_tuple_new, 1, (yyvsp[(2) - (3)].code));
      ;}
    break;

  case 231:
#line 925 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_elem_list_new, 1, (yyvsp[(1) - (1)].code));
      ;}
    break;

  case 232:
#line 928 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_elem_list_add, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 233:
#line 934 "src/mmlparse.y"
    { (yyval.code) = (yyvsp[(1) - (1)].code); ;}
    break;

  case 234:
#line 935 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_expr_add, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 235:
#line 936 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_expr_sub, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 236:
#line 940 "src/mmlparse.y"
    { (yyval.code) = (yyvsp[(1) - (1)].code); ;}
    break;

  case 237:
#line 941 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_expr_mul, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 238:
#line 942 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_expr_div, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 239:
#line 943 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_expr_mod, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 240:
#line 944 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_expr_intdiv, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 241:
#line 948 "src/mmlparse.y"
    { (yyval.code) = code_new_numb((yyvsp[(1) - (1)].numb)); ;}
    break;

  case 242:
#line 949 "src/mmlparse.y"
    { (yyval.code) = code_new_strg((yyvsp[(1) - (1)].strg));  ;}
    break;

  case 243:
#line 950 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_local_deref, 1, code_new_name((yyvsp[(1) - (1)].name)));
      ;}
    break;

  case 244:
#line 953 "src/mmlparse.y"
    { 
         (yyval.code) = code_new_inst(i_symbol_deref, 2, code_new_symbol((yyvsp[(1) - (2)].sym)), (yyvsp[(2) - (2)].code));
      ;}
    break;

  case 245:
#line 956 "src/mmlparse.y"
    { 
         (yyval.code) = code_new_inst(i_symbol_deref, 2, code_new_symbol((yyvsp[(1) - (2)].sym)), (yyvsp[(2) - (2)].code));
      ;}
    break;

  case 246:
#line 959 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_define_deref, 2,
            code_new_define((yyvsp[(1) - (4)].def)),
            code_new_inst(i_tuple_new, 1, (yyvsp[(3) - (4)].code)));
      ;}
    break;

  case 247:
#line 964 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_define_deref, 2,
            code_new_define((yyvsp[(1) - (4)].def)),
            code_new_inst(i_tuple_new, 1, (yyvsp[(3) - (4)].code)));
      ;}
    break;

  case 248:
#line 969 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_expr_fac, 1, (yyvsp[(1) - (2)].code)); ;}
    break;

  case 249:
#line 970 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_expr_pow, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 250:
#line 972 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_expr_card, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 251:
#line 973 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_expr_abs, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 252:
#line 974 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_expr_sgn, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 253:
#line 975 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_expr_floor, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 254:
#line 976 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_expr_ceil, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 255:
#line 977 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_expr_log, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 256:
#line 978 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_expr_ln, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 257:
#line 979 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_expr_exp, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 258:
#line 980 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_expr_sqrt, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 259:
#line 982 "src/mmlparse.y"
    { (yyval.code) = (yyvsp[(2) - (2)].code); ;}
    break;

  case 260:
#line 983 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_expr_neg, 1, (yyvsp[(2) - (2)].code)); ;}
    break;

  case 261:
#line 984 "src/mmlparse.y"
    { (yyval.code) = (yyvsp[(2) - (3)].code); ;}
    break;

  case 262:
#line 985 "src/mmlparse.y"
    { (yyval.code) = code_new_inst(i_expr_length, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 263:
#line 986 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_expr_substr, 3, (yyvsp[(3) - (8)].code), (yyvsp[(5) - (8)].code), (yyvsp[(7) - (8)].code));
      ;}
    break;

  case 264:
#line 989 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_expr_rand, 2, (yyvsp[(3) - (6)].code), (yyvsp[(5) - (6)].code));
      ;}
    break;

  case 265:
#line 992 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_expr_if, 3, (yyvsp[(2) - (7)].code), (yyvsp[(4) - (7)].code), (yyvsp[(6) - (7)].code));
      ;}
    break;

  case 266:
#line 995 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_expr_sglmin, 1, (yyvsp[(2) - (2)].code));
      ;}
    break;

  case 267:
#line 998 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_expr_sglmax, 1, (yyvsp[(2) - (2)].code));
      ;}
    break;

  case 268:
#line 1001 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_expr_min, 2, (yyvsp[(2) - (4)].code), (yyvsp[(4) - (4)].code));
      ;}
    break;

  case 269:
#line 1004 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_expr_max, 2, (yyvsp[(2) - (4)].code), (yyvsp[(4) - (4)].code));
      ;}
    break;

  case 270:
#line 1007 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_expr_sum, 2, (yyvsp[(2) - (4)].code), (yyvsp[(4) - (4)].code));
      ;}
    break;

  case 271:
#line 1010 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_expr_prod, 2, (yyvsp[(2) - (4)].code), (yyvsp[(4) - (4)].code));
      ;}
    break;

  case 272:
#line 1013 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_expr_min2, 1, (yyvsp[(3) - (4)].code));
      ;}
    break;

  case 273:
#line 1016 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_expr_max2, 1, (yyvsp[(3) - (4)].code));
      ;}
    break;

  case 274:
#line 1019 "src/mmlparse.y"
    {
         (yyval.code) = code_new_inst(i_expr_ord, 3, (yyvsp[(3) - (8)].code), (yyvsp[(5) - (8)].code), (yyvsp[(7) - (8)].code));
      ;}
    break;


/* Line 1267 of yacc.c.  */
#line 4389 "src/mmlparse.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



