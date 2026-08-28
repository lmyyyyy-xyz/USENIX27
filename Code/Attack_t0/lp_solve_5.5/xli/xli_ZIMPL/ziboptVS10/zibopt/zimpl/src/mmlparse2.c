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
     EXISTS = 283,
     PRIORITY = 284,
     STARTVAL = 285,
     DEFAULT = 286,
     CMP_LE = 287,
     CMP_GE = 288,
     CMP_EQ = 289,
     CMP_LT = 290,
     CMP_GT = 291,
     CMP_NE = 292,
     INFTY = 293,
     AND = 294,
     OR = 295,
     XOR = 296,
     NOT = 297,
     SUM = 298,
     MIN = 299,
     MAX = 300,
     ARGMIN = 301,
     ARGMAX = 302,
     PROD = 303,
     IF = 304,
     THEN = 305,
     ELSE = 306,
     END = 307,
     INTER = 308,
     UNION = 309,
     CROSS = 310,
     SYMDIFF = 311,
     WITHOUT = 312,
     PROJ = 313,
     MOD = 314,
     DIV = 315,
     POW = 316,
     FAC = 317,
     CARD = 318,
     ABS = 319,
     SGN = 320,
     ROUND = 321,
     FLOOR = 322,
     CEIL = 323,
     LOG = 324,
     LN = 325,
     EXP = 326,
     SQRT = 327,
     RANDOM = 328,
     ORD = 329,
     READ = 330,
     AS = 331,
     SKIP = 332,
     USE = 333,
     COMMENT = 334,
     MATCH = 335,
     SUBSETS = 336,
     INDEXSET = 337,
     POWERSET = 338,
     VIF = 339,
     VABS = 340,
     TYPE1 = 341,
     TYPE2 = 342,
     LENGTH = 343,
     SUBSTR = 344,
     NUMBSYM = 345,
     STRGSYM = 346,
     VARSYM = 347,
     SETSYM = 348,
     NUMBDEF = 349,
     STRGDEF = 350,
     BOOLDEF = 351,
     SETDEF = 352,
     DEFNAME = 353,
     NAME = 354,
     STRG = 355,
     NUMB = 356,
     SCALE = 357,
     SEPARATE = 358,
     CHECKONLY = 359,
     INDICATOR = 360
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
#define EXISTS 283
#define PRIORITY 284
#define STARTVAL 285
#define DEFAULT 286
#define CMP_LE 287
#define CMP_GE 288
#define CMP_EQ 289
#define CMP_LT 290
#define CMP_GT 291
#define CMP_NE 292
#define INFTY 293
#define AND 294
#define OR 295
#define XOR 296
#define NOT 297
#define SUM 298
#define MIN 299
#define MAX 300
#define ARGMIN 301
#define ARGMAX 302
#define PROD 303
#define IF 304
#define THEN 305
#define ELSE 306
#define END 307
#define INTER 308
#define UNION 309
#define CROSS 310
#define SYMDIFF 311
#define WITHOUT 312
#define PROJ 313
#define MOD 314
#define DIV 315
#define POW 316
#define FAC 317
#define CARD 318
#define ABS 319
#define SGN 320
#define ROUND 321
#define FLOOR 322
#define CEIL 323
#define LOG 324
#define LN 325
#define EXP 326
#define SQRT 327
#define RANDOM 328
#define ORD 329
#define READ 330
#define AS 331
#define SKIP 332
#define USE 333
#define COMMENT 334
#define MATCH 335
#define SUBSETS 336
#define INDEXSET 337
#define POWERSET 338
#define VIF 339
#define VABS 340
#define TYPE1 341
#define TYPE2 342
#define LENGTH 343
#define SUBSTR 344
#define NUMBSYM 345
#define STRGSYM 346
#define VARSYM 347
#define SETSYM 348
#define NUMBDEF 349
#define STRGDEF 350
#define BOOLDEF 351
#define SETDEF 352
#define DEFNAME 353
#define NAME 354
#define STRG 355
#define NUMB 356
#define SCALE 357
#define SEPARATE 358
#define CHECKONLY 359
#define INDICATOR 360




/* Copy the first part of user declarations.  */
#line 1 "src/mmlparse2.y"

#pragma ident "@(#) $Id: mmlparse2.y,v 1.7 2010/06/13 12:37:40 bzfkocht Exp $"
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*   File....: mmlparse.y                                                    */
/*   Name....: MML Parser                                                    */
/*   Author..: Thorsten Koch                                                 */
/*   Copyright by Author, All rights reserved                                */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*
 * Copyright (C) 2001-2010 by Thorsten Koch <koch@zib.de>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
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
#include "numb.h"
#include "elem.h"
#include "tuple.h"
#include "mme.h"
#include "set.h"
#include "symbol.h"
#include "entry.h"
#include "idxset.h"
#include "rdefpar.h"
#include "bound.h"
#include "define.h"
#include "mono.h"
#include "term.h"
#include "list.h"
#include "stmt.h"
#include "local.h"
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
#line 76 "src/mmlparse2.y"
{
   unsigned int bits;
   Numb*        numb;
   const char*  strg;
   const char*  name;
   Symbol*      sym;
   Define*      def;
   CodeNode*    code;
}
/* Line 187 of yacc.c.  */
#line 388 "src/mmlparse2.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 401 "src/mmlparse2.c"

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
#define YYLAST   2763

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  118
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  287
/* YYNRULES -- Number of states.  */
#define YYNSTATES  817

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
     113,   114,   108,   106,   112,   107,     2,   115,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,   109,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   110,     2,   111,     2,     2,     2,     2,     2,     2,
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
     105
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    11,    13,    15,    17,
      19,    21,    23,    25,    31,    40,    49,    57,    59,    63,
      70,    79,    84,    87,    96,   105,   114,   123,   125,   129,
     139,   148,   154,   156,   158,   160,   161,   164,   174,   181,
     190,   196,   206,   213,   225,   234,   235,   237,   240,   241,
     244,   248,   258,   268,   269,   272,   275,   284,   293,   294,
     297,   298,   301,   303,   307,   309,   312,   315,   319,   323,
     328,   334,   340,   346,   351,   356,   361,   366,   373,   380,
     387,   394,   399,   407,   420,   433,   446,   459,   472,   485,
     498,   511,   524,   537,   550,   563,   576,   589,   602,   615,
     624,   633,   642,   651,   655,   659,   663,   667,   671,   675,
     679,   683,   687,   691,   695,   699,   703,   707,   711,   715,
     719,   723,   727,   731,   735,   738,   742,   743,   747,   749,
     751,   753,   755,   757,   759,   761,   763,   767,   771,   775,
     779,   783,   787,   789,   793,   797,   801,   805,   807,   810,
     813,   815,   819,   824,   827,   832,   840,   844,   850,   855,
     860,   861,   863,   865,   869,   872,   875,   878,   881,   884,
     889,   891,   893,   899,   903,   905,   909,   913,   917,   921,
     925,   929,   931,   936,   938,   942,   946,   951,   954,   959,
     962,   970,   976,   984,   990,   995,  1003,  1008,  1016,  1020,
    1024,  1028,  1032,  1038,  1044,  1051,  1056,  1064,  1069,  1072,
    1075,  1078,  1081,  1084,  1086,  1090,  1092,  1096,  1100,  1104,
    1108,  1112,  1116,  1120,  1124,  1128,  1132,  1136,  1140,  1144,
    1148,  1152,  1155,  1159,  1163,  1168,  1173,  1181,  1184,  1188,
    1189,  1193,  1195,  1199,  1201,  1205,  1209,  1211,  1215,  1219,
    1223,  1227,  1232,  1234,  1237,  1240,  1242,  1246,  1251,  1256,
    1261,  1266,  1271,  1273,  1275,  1277,  1280,  1283,  1288,  1293,
    1296,  1301,  1306,  1311,  1316,  1321,  1326,  1331,  1336,  1341,
    1346,  1350,  1355,  1364,  1371,  1379,  1388,  1393
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     119,     0,    -1,   120,    -1,   128,    -1,   131,    -1,   141,
      -1,   142,    -1,   153,    -1,   123,    -1,   124,    -1,   125,
      -1,   126,    -1,   156,    -1,     3,    99,    20,   160,   109,
      -1,     3,    99,   110,   158,   111,    20,   160,   109,    -1,
       3,    99,   110,   158,   111,    20,   121,   109,    -1,     3,
      99,   110,   111,    20,   121,   109,    -1,   122,    -1,   121,
     112,   122,    -1,    81,   113,   160,   112,   171,   114,    -1,
      81,   113,   160,   112,   171,   112,   171,   114,    -1,    83,
     113,   160,   114,    -1,   168,   160,    -1,    10,    98,   113,
     127,   114,    20,   171,   109,    -1,    11,    98,   113,   127,
     114,    20,   171,   109,    -1,    12,    98,   113,   127,   114,
      20,   167,   109,    -1,    13,    98,   113,   127,   114,    20,
     160,   109,    -1,    99,    -1,   127,   112,    99,    -1,     4,
      99,   110,   158,   111,    20,   137,   130,   109,    -1,     4,
      99,   110,   158,   111,    20,   171,   109,    -1,     4,    99,
      20,   129,   109,    -1,     4,    -1,   137,    -1,   171,    -1,
      -1,    31,   171,    -1,     5,    99,   110,   158,   111,   132,
     133,   134,   109,    -1,     5,    99,   132,   133,   134,   109,
      -1,     5,    99,   110,   158,   111,    19,    16,   109,    -1,
       5,    99,    19,    16,   109,    -1,     5,    99,   110,   158,
     111,    16,   135,   136,   109,    -1,     5,    99,    16,   135,
     136,   109,    -1,     5,    99,   110,   158,   111,    17,   133,
     134,   135,   136,   109,    -1,     5,    99,    17,   133,   134,
     135,   136,   109,    -1,    -1,    18,    -1,    19,    17,    -1,
      -1,    33,   171,    -1,    33,   107,    38,    -1,    33,    49,
     167,    50,   171,    51,   107,    38,    52,    -1,    33,    49,
     167,    50,   107,    38,    51,   171,    52,    -1,    -1,    32,
     171,    -1,    32,    38,    -1,    32,    49,   167,    50,   171,
      51,    38,    52,    -1,    32,    49,   167,    50,    38,    51,
     171,    52,    -1,    -1,    29,   171,    -1,    -1,    30,   171,
      -1,   138,    -1,   137,   112,   138,    -1,   164,    -1,   139,
     140,    -1,   168,   171,    -1,    22,   170,    22,    -1,   139,
     170,    22,    -1,   140,   139,   170,    22,    -1,     6,    99,
      21,   148,   109,    -1,     7,    99,    21,   148,   109,    -1,
       8,    99,    21,   143,   109,    -1,   148,   147,   148,   145,
      -1,   148,   147,   171,   145,    -1,   171,   147,   148,   145,
      -1,   171,   147,   171,   145,    -1,   171,   147,   148,    32,
     171,   145,    -1,   171,   147,   171,    32,   171,   145,    -1,
     171,   147,   148,    33,   171,   145,    -1,   171,   147,   171,
      33,   171,   145,    -1,    27,   158,    21,   143,    -1,    49,
     167,    50,   143,    51,   143,    52,    -1,    84,   144,    50,
     148,   147,   148,    51,   148,   147,   148,    52,   145,    -1,
      84,   144,    50,   171,   147,   148,    51,   148,   147,   148,
      52,   145,    -1,    84,   144,    50,   148,   147,   171,    51,
     148,   147,   148,    52,   145,    -1,    84,   144,    50,   148,
     147,   148,    51,   171,   147,   148,    52,   145,    -1,    84,
     144,    50,   148,   147,   148,    51,   148,   147,   171,    52,
     145,    -1,    84,   144,    50,   171,   147,   171,    51,   148,
     147,   148,    52,   145,    -1,    84,   144,    50,   171,   147,
     148,    51,   171,   147,   148,    52,   145,    -1,    84,   144,
      50,   171,   147,   148,    51,   148,   147,   171,    52,   145,
      -1,    84,   144,    50,   148,   147,   171,    51,   171,   147,
     148,    52,   145,    -1,    84,   144,    50,   148,   147,   171,
      51,   148,   147,   171,    52,   145,    -1,    84,   144,    50,
     148,   147,   148,    51,   171,   147,   171,    52,   145,    -1,
      84,   144,    50,   171,   147,   171,    51,   171,   147,   148,
      52,   145,    -1,    84,   144,    50,   171,   147,   171,    51,
     148,   147,   171,    52,   145,    -1,    84,   144,    50,   171,
     147,   148,    51,   171,   147,   171,    52,   145,    -1,    84,
     144,    50,   148,   147,   171,    51,   171,   147,   171,    52,
     145,    -1,    84,   144,    50,   171,   147,   171,    51,   171,
     147,   171,    52,   145,    -1,    84,   144,    50,   148,   147,
     148,    52,   145,    -1,    84,   144,    50,   171,   147,   148,
      52,   145,    -1,    84,   144,    50,   148,   147,   171,    52,
     145,    -1,    84,   144,    50,   171,   147,   171,    52,   145,
      -1,   148,    37,   148,    -1,   171,    37,   148,    -1,   148,
      37,   171,    -1,   148,    34,   148,    -1,   171,    34,   148,
      -1,   148,    34,   171,    -1,   148,    32,   148,    -1,   171,
      32,   148,    -1,   148,    32,   171,    -1,   148,    33,   148,
      -1,   171,    33,   148,    -1,   148,    33,   171,    -1,   148,
      35,   148,    -1,   171,    35,   148,    -1,   148,    35,   171,
      -1,   148,    36,   148,    -1,   171,    36,   148,    -1,   148,
      36,   171,    -1,   144,    39,   144,    -1,   144,    40,   144,
      -1,   144,    41,   144,    -1,    42,   144,    -1,   113,   144,
     114,    -1,    -1,   145,   112,   146,    -1,   102,    -1,   103,
      -1,   104,    -1,   105,    -1,    32,    -1,    33,    -1,    34,
      -1,   149,    -1,   148,   106,   149,    -1,   148,   107,   149,
      -1,   148,   106,   172,    -1,   148,   107,   172,    -1,   171,
     106,   149,    -1,   171,   107,   149,    -1,   150,    -1,   149,
     108,   173,    -1,   149,   115,   173,    -1,   172,   108,   150,
      -1,   149,   108,   150,    -1,   151,    -1,   106,   150,    -1,
     107,   150,    -1,   152,    -1,   152,    61,   173,    -1,    43,
     158,    21,   149,    -1,    92,   169,    -1,    85,   113,   148,
     114,    -1,    49,   167,    50,   148,    51,   148,    52,    -1,
     113,   148,   114,    -1,     9,    99,    21,   154,   109,    -1,
     155,   135,    21,   148,    -1,    27,   158,    21,   154,    -1,
      -1,    86,    -1,    87,    -1,    21,   157,   109,    -1,    14,
     170,    -1,    14,   168,    -1,    14,   160,    -1,    14,    92,
      -1,    15,   167,    -1,    27,   158,    21,   157,    -1,   159,
      -1,   160,    -1,   168,    23,   160,    22,   167,    -1,   168,
      23,   160,    -1,   161,    -1,   160,    54,   161,    -1,   160,
     106,   161,    -1,   160,    56,   161,    -1,   160,   107,   161,
      -1,   160,    57,   161,    -1,   160,    53,   161,    -1,   162,
      -1,    54,   158,    21,   162,    -1,   163,    -1,   162,    55,
     163,    -1,   162,   108,   163,    -1,    53,   158,    21,   163,
      -1,    93,   169,    -1,    97,   113,   170,   114,    -1,   116,
     117,    -1,   116,   171,    24,   171,    26,   171,   117,    -1,
     116,   171,    24,   171,   117,    -1,   116,   171,    25,   171,
      26,   171,   117,    -1,   116,   171,    25,   171,   117,    -1,
      46,   158,    21,   171,    -1,    46,   113,   171,   114,   158,
      21,   171,    -1,    47,   158,    21,   171,    -1,    47,   113,
     171,   114,   158,    21,   171,    -1,   113,   160,   114,    -1,
     116,   166,   117,    -1,   116,   170,   117,    -1,   116,   158,
     117,    -1,   116,   158,    21,   171,   117,    -1,   116,   158,
      21,   168,   117,    -1,    58,   113,   160,   112,   168,   114,
      -1,    82,   113,    93,   114,    -1,    49,   167,    50,   160,
      51,   160,    52,    -1,    75,   171,    76,   171,    -1,   164,
     165,    -1,    77,   171,    -1,    78,   171,    -1,    79,   171,
      -1,    80,   171,    -1,   168,    -1,   166,   112,   168,    -1,
     164,    -1,   171,    34,   171,    -1,   171,    37,   171,    -1,
     171,    36,   171,    -1,   171,    33,   171,    -1,   171,    35,
     171,    -1,   171,    32,   171,    -1,   160,    34,   160,    -1,
     160,    37,   160,    -1,   160,    36,   160,    -1,   160,    33,
     160,    -1,   160,    35,   160,    -1,   160,    32,   160,    -1,
     167,    39,   167,    -1,   167,    40,   167,    -1,   167,    41,
     167,    -1,    42,   167,    -1,   113,   167,   114,    -1,   168,
      23,   160,    -1,    28,   113,   158,   114,    -1,    96,   113,
     170,   114,    -1,    49,   167,    50,   167,    51,   167,    52,
      -1,    35,    36,    -1,    35,   170,    36,    -1,    -1,   110,
     170,   111,    -1,   171,    -1,   170,   112,   171,    -1,   172,
      -1,   171,   106,   172,    -1,   171,   107,   172,    -1,   173,
      -1,   172,   108,   173,    -1,   172,   115,   173,    -1,   172,
      59,   173,    -1,   172,    60,   173,    -1,    48,   158,    21,
     173,    -1,   174,    -1,   106,   174,    -1,   107,   174,    -1,
     175,    -1,   175,    61,   173,    -1,    43,   158,    21,   172,
      -1,    44,   159,    21,   173,    -1,    45,   159,    21,   173,
      -1,    44,   113,   158,   114,    -1,    45,   113,   158,   114,
      -1,   101,    -1,   100,    -1,    99,    -1,    90,   169,    -1,
      91,   169,    -1,    94,   113,   170,   114,    -1,    95,   113,
     170,   114,    -1,   175,    62,    -1,    63,   113,   160,   114,
      -1,    64,   113,   171,   114,    -1,    65,   113,   171,   114,
      -1,    66,   113,   171,   114,    -1,    67,   113,   171,   114,
      -1,    68,   113,   171,   114,    -1,    69,   113,   171,   114,
      -1,    70,   113,   171,   114,    -1,    71,   113,   171,   114,
      -1,    72,   113,   171,   114,    -1,   113,   171,   114,    -1,
      88,   113,   171,   114,    -1,    89,   113,   171,   112,   171,
     112,   171,   114,    -1,    73,   113,   171,   112,   171,   114,
      -1,    49,   167,    50,   171,    51,   171,    52,    -1,    74,
     113,   160,   112,   171,   112,   171,   114,    -1,    44,   113,
     170,   114,    -1,    45,   113,   170,   114,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   144,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   162,   169,   175,   181,   191,   192,   195,
     198,   201,   207,   216,   225,   234,   243,   252,   255,   265,
     268,   271,   278,   281,   282,   289,   290,   298,   305,   314,
     324,   335,   344,   354,   358,   368,   369,   370,   374,   377,
     378,   379,   384,   392,   393,   394,   395,   400,   408,   409,
     413,   414,   422,   423,   426,   427,   431,   435,   439,   442,
     454,   457,   467,   473,   476,   481,   486,   493,   497,   502,
     506,   512,   515,   518,   521,   526,   531,   536,   540,   547,
     554,   560,   566,   572,   577,   585,   594,   603,   611,   622,
     625,   629,   634,   642,   643,   646,   649,   650,   653,   656,
     657,   660,   663,   664,   667,   670,   671,   674,   677,   678,
     681,   684,   685,   686,   687,   688,   692,   693,   697,   698,
     699,   700,   704,   705,   706,   710,   711,   712,   713,   714,
     717,   718,   726,   727,   728,   732,   733,   737,   738,   739,
     745,   746,   749,   755,   763,   764,   767,   775,   781,   784,
     790,   791,   792,   800,   804,   805,   806,   807,   808,   809,
     819,   820,   827,   830,   836,   837,   838,   841,   842,   845,
     846,   849,   850,   854,   855,   856,   859,   863,   866,   871,
     872,   875,   878,   881,   884,   887,   890,   893,   896,   897,
     898,   899,   900,   901,   902,   905,   908,   914,   915,   919,
     920,   921,   922,   926,   929,   932,   936,   937,   938,   939,
     940,   941,   942,   943,   944,   945,   946,   947,   948,   949,
     950,   951,   952,   953,   954,   955,   960,   966,   967,   971,
     974,   980,   983,   989,   990,   991,   995,   996,   997,   998,
     999,  1000,  1006,  1007,  1008,  1012,  1013,  1014,  1017,  1020,
    1023,  1026,  1032,  1033,  1034,  1037,  1040,  1043,  1048,  1053,
    1054,  1055,  1056,  1057,  1058,  1059,  1060,  1061,  1062,  1063,
    1065,  1066,  1067,  1070,  1073,  1076,  1079,  1082
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
  "EXISTS", "PRIORITY", "STARTVAL", "DEFAULT", "CMP_LE", "CMP_GE",
  "CMP_EQ", "CMP_LT", "CMP_GT", "CMP_NE", "INFTY", "AND", "OR", "XOR",
  "NOT", "SUM", "MIN", "MAX", "ARGMIN", "ARGMAX", "PROD", "IF", "THEN",
  "ELSE", "END", "INTER", "UNION", "CROSS", "SYMDIFF", "WITHOUT", "PROJ",
  "MOD", "DIV", "POW", "FAC", "CARD", "ABS", "SGN", "ROUND", "FLOOR",
  "CEIL", "LOG", "LN", "EXP", "SQRT", "RANDOM", "ORD", "READ", "AS",
  "SKIP", "USE", "COMMENT", "MATCH", "SUBSETS", "INDEXSET", "POWERSET",
  "VIF", "VABS", "TYPE1", "TYPE2", "LENGTH", "SUBSTR", "NUMBSYM",
  "STRGSYM", "VARSYM", "SETSYM", "NUMBDEF", "STRGDEF", "BOOLDEF", "SETDEF",
  "DEFNAME", "NAME", "STRG", "NUMB", "SCALE", "SEPARATE", "CHECKONLY",
  "INDICATOR", "'+'", "'-'", "'*'", "';'", "'['", "']'", "','", "'('",
  "')'", "'/'", "'{'", "'}'", "$accept", "stmt", "decl_set",
  "set_entry_list", "set_entry", "def_numb", "def_strg", "def_bool",
  "def_set", "name_list", "decl_par", "par_singleton", "par_default",
  "decl_var", "var_type", "lower", "upper", "priority", "startval",
  "cexpr_entry_list", "cexpr_entry", "matrix_head", "matrix_body",
  "decl_obj", "decl_sub", "constraint", "vbool", "con_attr_list",
  "con_attr", "con_type", "vexpr", "vproduct", "vfactor", "vexpo", "vval",
  "decl_sos", "soset", "sos_type", "exec_do", "command", "idxset",
  "pure_idxset", "sexpr", "sunion", "sproduct", "sval", "read", "read_par",
  "tuple_list", "lexpr", "tuple", "symidx", "cexpr_list", "cexpr",
  "cproduct", "cfactor", "cexpo", "cval", 0
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
     355,   356,   357,   358,   359,   360,    43,    45,    42,    59,
      91,    93,    44,    40,    41,    47,   123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   118,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   120,   120,   120,   120,   121,   121,   121,
     121,   121,   122,   123,   124,   125,   126,   127,   127,   128,
     128,   128,   128,   129,   129,   130,   130,   131,   131,   131,
     131,   131,   131,   131,   131,   132,   132,   132,   133,   133,
     133,   133,   133,   134,   134,   134,   134,   134,   135,   135,
     136,   136,   137,   137,   137,   137,   138,   139,   140,   140,
     141,   141,   142,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   145,   145,   146,   146,
     146,   146,   147,   147,   147,   148,   148,   148,   148,   148,
     148,   148,   149,   149,   149,   149,   149,   150,   150,   150,
     151,   151,   151,   152,   152,   152,   152,   153,   154,   154,
     155,   155,   155,   156,   157,   157,   157,   157,   157,   157,
     158,   158,   159,   159,   160,   160,   160,   160,   160,   160,
     160,   161,   161,   162,   162,   162,   162,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   164,   164,   165,
     165,   165,   165,   166,   166,   166,   167,   167,   167,   167,
     167,   167,   167,   167,   167,   167,   167,   167,   167,   167,
     167,   167,   167,   167,   167,   167,   167,   168,   168,   169,
     169,   170,   170,   171,   171,   171,   172,   172,   172,   172,
     172,   172,   173,   173,   173,   174,   174,   174,   174,   174,
     174,   174,   175,   175,   175,   175,   175,   175,   175,   175,
     175,   175,   175,   175,   175,   175,   175,   175,   175,   175,
     175,   175,   175,   175,   175,   175,   175,   175
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     5,     8,     8,     7,     1,     3,     6,
       8,     4,     2,     8,     8,     8,     8,     1,     3,     9,
       8,     5,     1,     1,     1,     0,     2,     9,     6,     8,
       5,     9,     6,    11,     8,     0,     1,     2,     0,     2,
       3,     9,     9,     0,     2,     2,     8,     8,     0,     2,
       0,     2,     1,     3,     1,     2,     2,     3,     3,     4,
       5,     5,     5,     4,     4,     4,     4,     6,     6,     6,
       6,     4,     7,    12,    12,    12,    12,    12,    12,    12,
      12,    12,    12,    12,    12,    12,    12,    12,    12,     8,
       8,     8,     8,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     3,     0,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     1,     3,     3,     3,     3,     1,     2,     2,
       1,     3,     4,     2,     4,     7,     3,     5,     4,     4,
       0,     1,     1,     3,     2,     2,     2,     2,     2,     4,
       1,     1,     5,     3,     1,     3,     3,     3,     3,     3,
       3,     1,     4,     1,     3,     3,     4,     2,     4,     2,
       7,     5,     7,     5,     4,     7,     4,     7,     3,     3,
       3,     3,     5,     5,     6,     4,     7,     4,     2,     2,
       2,     2,     2,     1,     3,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     3,     3,     4,     4,     7,     2,     3,     0,
       3,     1,     3,     1,     3,     3,     1,     3,     3,     3,
       3,     4,     1,     2,     2,     1,     3,     4,     4,     4,
       4,     4,     1,     1,     1,     2,     2,     4,     4,     2,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       3,     4,     8,     6,     7,     8,     4,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     0,    32,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     2,     8,     9,    10,    11,     3,
       4,     5,     6,     7,    12,     0,     0,    45,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,     0,     0,     0,     0,    58,    48,    46,     0,     0,
      48,     0,     0,     0,   160,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   239,   239,   167,   239,     0,
       0,     0,   264,   263,   262,     0,     0,     0,     0,   166,
     174,   181,   183,   165,   164,   241,   243,   246,   252,   255,
       0,     0,     0,     0,     0,     0,   168,     0,     0,     0,
       0,     0,   170,   171,     0,   163,     0,     0,     0,     0,
       0,     0,     0,     0,    33,    62,     0,    64,     0,    34,
       0,     0,    60,     0,    53,     0,    47,     0,    53,     0,
       0,     0,   239,     0,     0,     0,     0,   135,   142,   147,
     150,     0,   243,     0,     0,     0,     0,     0,     0,     0,
       0,   161,   162,     0,    58,    27,     0,     0,     0,     0,
     237,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   265,   266,   187,     0,     0,     0,   253,   254,
       0,     0,   189,     0,   215,     0,   213,     0,   241,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   269,     0,   231,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    13,     0,     0,     0,     0,     0,    31,     0,
       0,    65,     0,     0,     0,     0,   208,    66,     0,    59,
       0,     0,     0,     0,    49,     0,    58,    40,    45,     0,
       0,     0,     0,   153,     0,     0,   148,   149,     0,     0,
       0,     0,    70,     0,     0,     0,     0,     0,     0,    71,
       0,     0,     0,     0,     0,     0,     0,    72,   132,   133,
     134,     0,     0,     0,   157,     0,     0,     0,     0,     0,
       0,   238,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   198,   280,     0,
     201,     0,   199,   200,     0,     0,   180,   175,   177,   179,
     176,   178,   184,   185,   242,   244,   245,   249,   250,   247,
     248,   256,     0,     0,     0,   232,   227,   225,   222,   226,
     224,   223,   228,   229,   230,   233,   221,   219,   216,   220,
     218,   217,     0,   169,   173,     0,     0,     0,    17,     0,
       0,    67,     0,     0,    63,     0,     0,   209,   210,   211,
     212,     0,    61,    42,     0,    50,    55,     0,    54,    60,
      58,    48,     0,    48,    38,     0,     0,     0,     0,     0,
       0,   156,   136,   138,   137,   139,   146,   143,   144,   151,
     140,   244,   141,   245,   145,     0,     0,   124,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   126,   126,   126,
     126,   160,     0,    28,     0,     0,     0,     0,   257,   260,
     286,   258,   261,   287,   259,     0,   194,     0,   196,   251,
       0,     0,   186,   182,     0,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,     0,     0,   205,   281,     0,
     240,   267,   268,   188,     0,     0,   214,     0,     0,   234,
       0,     0,     0,   235,     0,     0,     0,    16,     0,    22,
       0,     0,   207,    68,     0,    35,     0,     0,     0,     0,
      60,    53,     0,    53,   152,   257,     0,     0,   154,     0,
       0,    81,     0,     0,     0,   125,   121,   122,   123,     0,
       0,   109,   111,   112,   114,   106,   108,   115,   117,   118,
     120,   103,   105,   110,   113,   107,   116,   119,   104,    73,
      74,     0,     0,    75,     0,     0,    76,   159,   158,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   203,   202,     0,   191,     0,   193,     0,   172,     0,
       0,    18,    15,    14,    69,     0,     0,    30,     0,     0,
       0,    44,     0,    58,    39,     0,     0,     0,     0,     0,
       0,     0,     0,   126,   126,   126,   126,    23,    24,    25,
      26,     0,     0,     0,     0,   204,   283,     0,     0,     0,
       0,     0,     0,    21,    36,    29,     0,     0,     0,     0,
      41,    60,    37,     0,     0,     0,     0,     0,     0,     0,
     128,   129,   130,   131,   127,    77,    79,    78,    80,   195,
     197,   206,   284,     0,     0,   190,   192,   236,     0,     0,
       0,     0,     0,     0,   155,    82,     0,   126,     0,   126,
       0,   126,     0,   126,   285,   282,     0,    19,     0,     0,
       0,     0,    43,     0,     0,    99,     0,     0,   101,     0,
       0,   100,     0,     0,   102,     0,    52,    51,    57,    56,
       0,     0,     0,     0,     0,     0,     0,     0,    20,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   126,   126,   126,   126,   126,
     126,    83,    87,    86,    93,    85,    92,    91,    97,    84,
      90,    89,    96,    88,    95,    94,    98
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    13,    14,   427,   428,    15,    16,    17,    18,   176,
      19,   133,   646,    20,    50,   144,   296,   142,   291,   134,
     135,   136,   281,    21,    22,   167,   324,   609,   704,   331,
     325,   157,   158,   159,   160,    23,   173,   174,    24,    39,
     121,   122,   123,   100,   101,   102,   137,   286,   225,   116,
     124,   212,   104,   118,   106,   107,   108,   109
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -455
static const yytype_int16 yypact[] =
{
    1589,   -22,     4,    21,    61,    95,   101,   107,   -30,   112,
     123,   138,   336,   240,  -455,  -455,  -455,  -455,  -455,  -455,
    -455,  -455,  -455,  -455,  -455,   -16,    -1,    24,   224,   267,
     325,   347,   188,   261,   264,   285,  1391,  1161,  1001,   283,
    -455,  2647,   816,  1036,  1001,   378,   379,  -455,    71,  1001,
     379,  2166,  2166,  1237,    72,   320,   320,   320,   320,  1628,
    1001,    -9,    -7,  1104,  1533,  1001,  1161,  1001,  1001,   323,
     328,   348,   381,   388,   395,   407,   412,   471,   474,   495,
     503,   516,   530,   539,   542,   555,   555,  -455,   555,   558,
     578,   590,  -455,  -455,  -455,  2618,  2618,  2046,  1316,  1138,
    -455,    88,  -455,  -455,   602,   178,     6,  -455,  -455,   360,
     609,  1161,  1161,   610,  1161,   959,   817,   723,    39,  1161,
    2647,   730,  -455,  1138,   739,  -455,   512,   760,   688,  2332,
    1161,  2332,  2332,   691,   698,  -455,   789,  1322,  2332,   178,
     736,  2332,   824,  2392,   829,   773,  -455,   774,   829,  1001,
    1161,   791,   555,  2219,  2219,  2166,   167,   -55,  -455,  -455,
     865,   398,   329,   569,  1001,  1161,  2106,   827,   238,   324,
    1001,  -455,  -455,   832,   378,  -455,   141,   203,   353,   373,
    -455,    10,   931,  1465,   960,  1465,   961,  2046,   964,  2046,
     965,   967,   658,   969,   976,  2647,  2647,  2332,  2332,  2332,
    2332,  2332,  2332,  2332,  2332,  2332,  2332,  2647,   913,  2332,
    2332,  2332,  -455,  -455,  -455,  2332,  2332,  2332,  -455,  -455,
     266,   248,  -455,   -19,  1322,    -4,   739,    85,    25,  2647,
    2647,  2647,  2647,  2647,  2647,   663,   663,  2332,  2332,  2332,
    2565,  2565,  2565,  2565,  2565,  -455,  1001,  -455,   809,  2332,
     246,    42,    22,  2647,  2647,  2647,  2647,  2647,  2647,  1161,
    1161,  1161,  2647,  2332,  2332,  2332,  2332,  2332,  2332,   838,
     336,  2647,  -455,    44,   990,     5,  1012,   116,  -455,   982,
    2332,   789,  2332,  2332,  2332,  2332,  -455,   178,   998,   178,
    2332,   910,  1161,  1867,   178,  1688,   378,  -455,  1402,   918,
    1009,  1028,  2166,  -455,   389,   389,  -455,  -455,   416,   450,
    2166,  2166,  -455,  2272,  2565,  2565,  2166,  2166,  2272,  -455,
    1013,  1120,  2106,  2106,  1133,   769,   808,  -455,  -455,  -455,
    -455,  2166,  2166,  1014,  -455,  1017,   974,  1029,  1040,  1043,
    1057,  -455,  2332,   975,   404,  2565,   983,   536,  2565,   550,
    2332,   599,  2332,  2565,  2046,   663,   979,   836,   422,   702,
     766,   780,   814,   915,   917,   950,   968,  1041,   -15,   877,
    1004,  1169,   287,   462,   622,   674,   678,  -455,  -455,  1568,
    -455,   982,  -455,  -455,  2332,  2332,  -455,  -455,  -455,  -455,
    -455,  -455,  -455,  -455,   178,     6,     6,  -455,  -455,  -455,
    -455,  -455,  1007,  1161,   788,  -455,  1138,  1138,  1138,  1138,
    1138,  1138,  -455,  1054,  1054,  1138,   178,   178,   178,   178,
     178,   178,  2647,  -455,   204,  1010,  1015,    75,  -455,  2647,
     591,  -455,  2332,  2332,  -455,    29,  2332,   178,   178,   178,
     178,  1036,   178,  -455,  1137,  -455,  -455,  1161,   178,   824,
     378,   379,   579,   379,  -455,  2166,  2166,  1206,  1001,  1161,
    2166,  -455,   -55,   329,   -55,   329,  -455,  -455,  -455,  -455,
     -55,   329,   -55,   329,  -455,  1237,  1237,  -455,   228,   304,
     456,  2106,  2106,  2106,  2166,  2166,  2166,  2166,  2166,  2166,
    2166,  2166,  2166,  2166,  2166,  2166,  2166,   506,   398,   272,
     280,    72,  2166,  -455,  2332,  2332,  1161,  2647,     6,  -455,
    -455,  -455,  -455,  -455,  -455,  1001,   178,  1001,   178,  -455,
     547,   157,  -455,    88,   982,  -455,  -455,  -455,  -455,  -455,
    -455,  -455,  -455,  -455,  -455,  2332,  2332,  -455,  -455,  2332,
    -455,  -455,  -455,  -455,  1016,   -37,  -455,   -17,     9,  -455,
     761,   566,   626,  -455,  1161,  2647,  2647,  -455,   982,  1138,
     153,  1059,   178,  -455,    30,   -11,   631,  2452,  1140,   987,
     824,   829,  1020,   829,   -55,   329,   258,   277,  -455,  1111,
    1248,  -455,  1083,   144,   201,  -455,  -455,  1113,  1113,   238,
     324,   506,   398,   506,   398,   506,   398,   506,   398,   506,
     398,   506,   398,   506,   506,   506,   506,   506,   506,  1042,
    1042,  2332,  2332,  1042,  2332,  2332,  1042,  -455,   506,   652,
     801,   286,  1415,  1135,  1143,  2647,  2332,  1053,  1209,   420,
     527,  -455,  -455,  2332,  -455,  2332,  -455,  1161,   817,  1184,
     453,  -455,  -455,  -455,  -455,  2332,  1060,  -455,  1926,   296,
    1748,  -455,  1075,   378,  -455,  1076,  2166,  2166,  2166,  1237,
    2166,  2166,  1348,   178,   178,   178,   178,  -455,  -455,  -455,
    -455,  2332,  2332,  1034,   186,  -455,  -455,  2332,  2332,    31,
      65,   472,  2332,  -455,   178,  -455,  1142,  2512,  1147,   366,
    -455,   824,  -455,   307,   329,  1150,   357,   364,   391,   431,
    -455,  -455,  -455,  -455,  -455,  1042,  1042,  1042,  1042,   178,
     178,  -455,  -455,  1228,  1233,  -455,  -455,  -455,   810,  2332,
    1985,  2332,  1808,  1090,  -455,  -455,  2166,  -455,  2166,  -455,
    2166,  -455,  2166,  -455,  -455,  -455,  2332,  -455,   319,  1159,
     465,  1160,  -455,   238,   324,  1042,   238,   324,  1042,   238,
     324,  1042,   238,   324,  1042,  1242,  -455,  -455,  -455,  -455,
    2166,  2166,  2166,  2166,  2166,  2166,  2166,  2166,  -455,   487,
     525,   563,   575,   595,   635,   637,   641,   643,   731,   777,
     812,   844,   873,   892,   897,  -455,  -455,  -455,  -455,  -455,
    -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,
    -455,  1042,  1042,  1042,  1042,  1042,  1042,  1042,  1042,  1042,
    1042,  1042,  1042,  1042,  1042,  1042,  1042
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -455,  -455,  -455,   783,   660,  -455,  -455,  -455,  -455,   889,
    -455,  -455,  -455,  -455,   923,   -47,  -138,  -173,  -435,   775,
     957,  -124,  -455,  -455,  -455,  -454,  -292,   168,  -455,  -161,
     279,  -272,  -106,  -455,  -455,  -455,   738,  -455,  -455,   972,
     -31,   618,   716,  1163,   890,  -211,  1155,  -455,  -455,    74,
     741,    -2,    26,   -36,    59,   -24,   -90,  -455
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
     105,   335,   379,   148,    41,   218,   219,   139,   332,   633,
     299,   128,   280,   140,   569,   161,   161,   169,   147,    43,
     645,   581,   582,   105,   392,   393,    59,   431,    59,   182,
     477,   478,   188,   190,   191,   635,   193,   194,   462,   464,
      45,    46,    47,    48,   470,   472,   341,   306,   307,   384,
     385,   563,   644,   313,   263,   264,   265,   266,   267,   268,
     314,   221,   228,   218,   219,   240,   241,   223,    32,   238,
     239,   263,   264,   265,   266,   267,   268,    25,   252,    59,
     632,   259,   260,   261,   213,   181,   214,   145,   146,   238,
     239,   238,   239,   105,    42,   277,   221,   535,   380,   170,
     634,   279,   287,    26,   183,   289,   185,   294,   381,    44,
     162,   162,   162,   382,   242,   238,   239,   237,   300,   309,
      27,   243,   237,   449,   227,   425,   636,   426,   238,   239,
     326,   238,   239,   320,    49,   652,   378,   238,   239,   333,
     192,   237,   237,   235,   522,   238,   239,   105,   715,   105,
     303,   349,   343,   351,   346,   275,   405,   436,   171,   172,
      28,   359,   360,   361,   362,   363,   364,   365,   366,   367,
     368,   238,   239,   371,   372,   105,   328,   329,   330,   105,
     105,   105,   716,   574,   557,   247,   248,   558,   251,   586,
     587,   588,   433,   269,    29,   656,   236,   237,   306,   307,
      30,   394,   383,   219,   276,   695,    31,   466,   626,   344,
      33,   347,   474,   105,   162,   402,   397,   398,   399,   400,
     401,    34,   238,   239,   301,   162,   554,   416,   417,   418,
     419,   420,   421,   328,   329,   330,    35,   373,   712,   321,
      40,   374,   375,   376,   105,    51,   437,   438,   439,   440,
     310,   311,   626,   336,   442,   337,   723,   229,   230,   448,
     231,   232,   642,   238,   239,   558,   161,   481,   482,   483,
     328,   329,   330,   310,   311,   404,   312,   570,   253,   254,
     255,   256,   257,   258,   238,   239,   326,   480,    52,   467,
     468,   469,   238,   239,   399,   498,   500,   395,   396,   229,
     230,    55,   231,   232,   611,   612,   435,   316,   317,   656,
     233,   234,   614,   615,   516,   336,   518,   338,   521,   229,
     230,   511,   231,   232,   514,   259,   260,   261,   626,   519,
     156,   163,   168,   412,   413,   414,   485,   486,   487,   488,
     489,   490,   585,   545,   310,   311,    53,   687,   547,   548,
      36,    37,   233,   234,   238,   239,   328,   329,   330,   724,
     377,   162,   378,    38,   310,   311,   444,   552,    54,   463,
     465,   756,   233,   234,    56,   471,   473,    57,   310,   311,
     377,   162,   162,   316,   317,   574,   316,   317,   240,   241,
     162,   162,   125,   238,   239,   669,   521,   562,    58,   539,
     105,   508,   238,   239,   571,   566,   573,   141,   726,   727,
     310,   311,   143,   310,   311,   728,   729,   722,   461,   175,
     577,   244,   245,   332,   161,   238,   239,   579,   660,   661,
     316,   317,   458,   653,   308,   655,   195,   318,   459,   169,
     584,   196,   730,   731,   243,   326,   326,   326,   590,   592,
     594,   596,   598,   600,   602,   161,   161,   161,   161,   161,
     161,   197,   564,   310,   311,   336,   161,   339,   619,   620,
     316,   317,   238,   239,   151,   229,   230,   551,   231,   232,
     691,   152,   732,   733,   623,   336,   624,   340,   491,   492,
     493,   494,   495,   496,   198,   304,   305,   310,   311,   628,
     629,   199,   460,   630,   316,   317,   229,   230,   200,   231,
     232,   259,   260,   261,   575,   162,   237,   758,   510,   162,
     201,   568,   310,   311,   717,   202,   238,   239,   233,   234,
     461,   649,   677,   580,   162,   162,   525,   316,   317,   785,
     162,   162,   162,   162,   162,   162,   162,   162,   162,   162,
     162,   162,   162,   162,   162,   162,   316,   317,   219,   233,
     234,   162,   316,   317,   378,   229,   230,   683,   231,   232,
     378,   238,   239,   540,   237,   663,   664,   786,   665,   666,
     621,   457,   760,   761,   203,   762,   763,   204,   764,   765,
     674,   766,   767,   310,   311,   572,   146,   679,   625,   680,
     229,   230,   479,   231,   232,   259,   260,   261,   205,   684,
     497,   499,   310,   311,   689,   787,   206,   637,   233,   234,
     161,   272,   161,   169,   697,   699,    59,   788,   638,   207,
     219,   316,   317,   238,   239,   709,   710,    63,    64,   678,
     119,   713,   714,   208,    67,    68,   718,   789,   237,    69,
     513,   674,   209,   233,   234,   210,   238,   239,   263,   264,
     265,   266,   267,   268,   515,   211,   610,   613,   616,   310,
     311,   215,   425,    82,   426,   310,   311,   626,   319,   184,
     186,   316,   317,   738,    88,   740,   674,   790,    91,   791,
     744,   216,   747,   792,   750,   793,   753,   259,   260,   261,
     755,   310,   311,   217,   120,   238,   239,    98,   354,    63,
      64,   681,   119,   517,   237,   162,   694,   162,   162,   162,
     162,    69,   246,   249,   770,   772,   774,   776,   778,   780,
     782,   784,   238,   239,   237,   576,   541,   238,   239,   308,
     647,   316,   317,   310,   311,    82,   262,   316,   317,   310,
     311,   270,    99,   115,   168,   583,    88,   126,   238,   239,
      91,   667,   271,   589,   591,   593,   595,   597,   599,   601,
     603,   604,   605,   606,   607,   608,   120,   103,   117,    98,
     273,   618,   115,   794,   138,   162,   237,   162,   542,   162,
     237,   162,   543,   253,   254,   255,   256,   257,   258,   274,
     278,   485,   486,   487,   488,   489,   490,   117,   238,   239,
     279,   129,   625,   220,   229,   230,   526,   231,   232,   162,
     162,   162,   162,   162,   162,   162,   162,   115,   115,   795,
     250,   705,   706,   707,   708,   115,   220,   316,   317,   226,
     491,   492,   493,   494,   495,   496,   115,   288,   259,   260,
     261,    59,   117,   117,   290,   117,   259,   260,   261,   403,
     117,   295,    63,    64,   796,   119,   115,   233,   234,    67,
      68,   117,   238,   239,    69,   310,   311,   259,   260,   261,
     527,   115,   297,   310,   311,   298,   238,   239,   422,   229,
     230,   117,   231,   232,   528,   745,   797,   748,    82,   751,
     237,   754,   553,   220,   302,   220,   117,   238,   239,    88,
     668,   357,   358,    91,   316,   317,   238,   239,   316,   317,
     238,   239,   736,   369,   737,   798,   315,   127,   529,   120,
     229,   230,    98,   231,   232,   693,   327,   576,   168,   696,
     698,   334,   233,   234,   799,   177,   178,   179,   524,   800,
     310,   311,   342,   801,   802,   803,   804,   805,   806,   807,
     808,   809,   810,   811,   812,   813,   814,   815,   816,   406,
     407,   408,   409,   410,   411,   115,   115,   115,   415,   316,
     317,   345,   348,   233,   234,   350,   352,   424,   353,   536,
     355,   253,   254,   255,   256,   257,   258,   356,   310,   311,
     117,   117,   117,   316,   317,   743,   370,   746,   115,   749,
     430,   752,   229,   230,   429,   231,   232,    59,   441,   443,
     138,   238,   239,   238,   239,    63,    64,   454,   119,   530,
     455,   531,    67,   117,   475,   501,    59,    69,   502,   769,
     771,   773,   775,   777,   779,   781,   783,    63,    64,   504,
     119,   259,   260,   261,    67,    68,   238,   239,   129,    69,
     505,    82,   432,   506,   532,   233,   234,   259,   260,   261,
     520,    59,    88,   503,   238,   239,    91,   507,   456,    60,
      61,    62,   533,    82,    65,   130,   711,   229,   230,   509,
     231,   232,   120,   259,    88,    98,   651,   512,    91,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,   131,   229,   230,   120,   231,   232,    98,   537,   550,
     544,   549,   546,   555,    83,    84,    85,    86,   556,   654,
      89,    90,   657,   631,   659,    92,    93,    94,   520,    59,
     233,   234,    95,    96,   117,   559,   561,   238,   239,   132,
      63,    64,   481,   119,   662,   534,   671,    67,    68,   259,
     260,   261,    69,   115,   672,   233,   234,   675,   643,   685,
     476,   429,   481,   482,   483,   115,   259,   260,   261,   259,
     260,   261,   138,   484,   690,   692,    82,   567,   117,   110,
     650,   229,   230,   719,   231,   232,    59,    88,   721,   742,
     117,    91,   725,   111,    60,    61,    62,    63,    64,    65,
     112,   757,   759,   560,    67,    68,   565,   187,   641,    69,
      98,   453,   115,   622,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,   434,   229,   230,   617,
     231,   232,   423,    82,   233,   234,   523,   117,     0,    83,
      84,    85,    86,   224,    88,    89,    90,   113,    91,     0,
      92,    93,    94,     0,   164,   627,     0,    95,    96,     0,
     115,   639,   640,     0,   114,   238,   239,    98,     0,     0,
     149,    61,    62,   538,     0,    65,   165,   259,   260,   261,
     233,   234,     0,     0,     0,   117,   682,     0,   658,   429,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,   310,   311,     0,   238,   239,     0,     0,     0,
     578,   166,   151,   676,     0,    83,    84,    85,    86,   152,
       0,    89,    90,     0,   238,   239,    92,    93,    94,   238,
     239,   673,   734,   153,   154,     0,     0,   735,   238,   239,
     155,    59,     0,   115,     0,     0,   768,     0,     0,    60,
      61,    62,    63,    64,    65,    66,     0,     0,     0,    67,
      68,     0,     0,     0,    69,     0,     0,     0,   117,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,   131,   386,   387,   388,   389,   390,   391,    82,   282,
     283,   284,   285,     0,    83,    84,    85,    86,     0,    88,
      89,    90,     0,    91,     0,    92,    93,    94,   450,   451,
      47,   452,    95,    96,     0,     0,    59,     0,     0,    97,
       0,     0,    98,   222,    60,    61,    62,    63,    64,    65,
      66,     0,     0,     0,    67,    68,     0,     0,     0,    69,
     700,   701,   702,   703,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,     0,     0,   229,   230,
       0,   231,   232,    82,     0,     0,     0,     0,     0,    83,
      84,    85,    86,    87,    88,    89,    90,     0,    91,     0,
      92,    93,    94,     0,     0,     0,     0,    95,    96,     0,
      59,     0,     0,     0,    97,     0,     0,    98,    60,    61,
      62,    63,    64,    65,    66,     0,     0,     0,    67,    68,
       0,   233,   234,    69,   670,     0,     0,     0,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
       0,     0,     0,     0,     0,     0,     0,    82,     0,     0,
       0,     0,     0,    83,    84,    85,    86,     0,    88,    89,
      90,     0,    91,     0,    92,    93,    94,     0,    59,     0,
       0,    95,    96,     0,     0,     0,     0,     0,    97,    63,
      64,    98,   119,     0,     0,     0,    67,    68,     0,     0,
       0,    69,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    59,     0,     0,     0,     0,     0,     0,
      12,    60,    61,    62,     0,    82,    65,   130,     0,     0,
       0,     0,     0,     0,     0,     0,    88,     0,     0,     0,
      91,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,     0,     0,     0,   189,     0,     0,    98,
       0,     0,     0,     0,     0,     0,    83,    84,    85,    86,
       0,     0,    89,    90,   180,     0,     0,    92,    93,    94,
       0,    60,    61,    62,    95,    96,    65,   130,     0,     0,
       0,   132,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    83,    84,    85,    86,
       0,     0,    89,    90,     0,     0,   446,    92,    93,    94,
       0,    60,    61,    62,    95,    96,    65,   447,     0,     0,
       0,   132,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    83,    84,    85,    86,
       0,     0,    89,    90,     0,     0,   688,    92,    93,    94,
       0,    60,    61,    62,    95,    96,    65,   130,     0,     0,
       0,   132,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    83,    84,    85,    86,
       0,     0,    89,    90,     0,     0,   741,    92,    93,    94,
       0,    60,    61,    62,    95,    96,    65,   130,     0,     0,
       0,   132,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    83,    84,    85,    86,
       0,     0,    89,    90,     0,   445,     0,    92,    93,    94,
      60,    61,    62,     0,    95,    96,   130,     0,     0,     0,
       0,   132,     0,     0,     0,     0,     0,     0,     0,     0,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    83,    84,    85,    86,     0,
       0,    89,    90,     0,   686,     0,    92,    93,    94,    60,
      61,    62,     0,     0,     0,   130,     0,     0,     0,     0,
     132,     0,     0,     0,     0,     0,     0,     0,     0,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    83,    84,    85,    86,     0,     0,
      89,    90,     0,   739,     0,    92,    93,    94,    60,    61,
      62,     0,     0,     0,   130,     0,     0,     0,     0,   132,
       0,     0,     0,     0,     0,     0,     0,     0,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    83,    84,    85,    86,     0,     0,    89,
      90,     0,     0,     0,    92,    93,    94,     0,     0,    60,
      61,    62,    63,    64,    65,    66,     0,     0,   132,    67,
      68,     0,     0,     0,    69,     0,     0,     0,     0,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,     0,     0,     0,     0,     0,     0,     0,    82,     0,
       0,     0,     0,     0,    83,    84,    85,    86,     0,    88,
      89,    90,     0,    91,     0,    92,    93,    94,   322,   149,
      61,    62,    95,    96,    65,   150,     0,     0,     0,    97,
       0,     0,    98,     0,     0,     0,     0,     0,     0,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   151,     0,     0,    83,    84,    85,    86,   152,     0,
      89,    90,     0,     0,     0,    92,    93,    94,     0,   149,
      61,    62,   153,   154,    65,   150,     0,     0,     0,   323,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   151,     0,     0,    83,    84,    85,    86,   152,     0,
      89,    90,   149,    61,    62,    92,    93,    94,   150,     0,
       0,     0,   153,   154,     0,     0,     0,     0,     0,   155,
       0,     0,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   151,     0,     0,    83,    84,    85,
      86,   152,     0,    89,    90,   149,    61,    62,    92,    93,
      94,   150,     0,     0,     0,   304,   305,     0,     0,     0,
       0,     0,   155,     0,     0,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   151,     0,     0,
      83,    84,    85,    86,   152,     0,    89,    90,     0,     0,
       0,    92,    93,    94,     0,    60,    61,    62,   153,   154,
      65,   130,     0,     0,     0,   155,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      83,    84,    85,    86,     0,     0,    89,    90,     0,     0,
       0,    92,    93,    94,     0,    60,    61,    62,    95,    96,
      65,   292,     0,     0,     0,   132,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      83,    84,    85,    86,     0,     0,    89,    90,     0,     0,
       0,    92,    93,    94,     0,    60,    61,    62,    95,   293,
      65,   130,     0,     0,     0,   132,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      83,    84,    85,    86,     0,     0,    89,    90,     0,     0,
       0,    92,    93,    94,     0,    60,    61,    62,    95,   648,
      65,   130,     0,     0,     0,   132,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      83,    84,    85,    86,     0,     0,    89,    90,    60,    61,
      62,    92,    93,    94,   130,     0,     0,     0,    95,   720,
       0,     0,     0,     0,     0,   132,     0,     0,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    83,    84,    85,    86,     0,     0,    89,
      90,    60,    61,    62,    92,    93,    94,   130,     0,     0,
       0,    95,    96,     0,     0,     0,     0,     0,   132,     0,
       0,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    63,    64,     0,   119,     0,     0,     0,
      67,    68,     0,     0,     0,    69,    83,    84,    85,    86,
       0,     0,    89,    90,     0,     0,     0,    92,    93,    94,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    82,
       0,   132,     0,     0,     0,     0,     0,     0,     0,     0,
      88,     0,     0,     0,    91,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     120,     0,     0,    98
};

static const yytype_int16 yycheck[] =
{
      36,   174,    21,    50,    20,    95,    96,    43,   169,    26,
     148,    42,   136,    44,   449,    51,    52,    53,    49,    20,
      31,   475,   476,    59,   235,   236,    35,    22,    35,    60,
     322,   323,    63,    64,    65,    26,    67,    68,   310,   311,
      16,    17,    18,    19,   316,   317,    36,   153,   154,    24,
      25,    22,    22,   108,    32,    33,    34,    35,    36,    37,
     115,    97,    98,   153,   154,    59,    60,    98,    98,   106,
     107,    32,    33,    34,    35,    36,    37,    99,   114,    35,
     117,    39,    40,    41,    86,    59,    88,    16,    17,   106,
     107,   106,   107,   129,   110,   131,   132,   112,   117,    27,
     117,   112,   138,    99,   113,   141,   113,   143,   112,   110,
      51,    52,    53,   117,   108,   106,   107,   112,   149,   155,
      99,   115,   112,   296,    98,    81,   117,    83,   106,   107,
     166,   106,   107,   164,   110,   570,   114,   106,   107,   170,
      66,   112,   112,    55,   355,   106,   107,   183,   117,   185,
     152,   187,   183,   189,   185,   129,   114,   281,    86,    87,
      99,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   106,   107,   209,   210,   211,    32,    33,    34,   215,
     216,   217,   117,   455,   109,   111,   112,   112,   114,   481,
     482,   483,    76,   119,    99,    51,   108,   112,   304,   305,
      99,   237,   117,   293,   130,   659,    99,   313,    51,   183,
      98,   185,   318,   249,   155,   246,   240,   241,   242,   243,
     244,    98,   106,   107,   150,   166,    22,   263,   264,   265,
     266,   267,   268,    32,    33,    34,    98,   211,    52,   165,
       0,   215,   216,   217,   280,    21,   282,   283,   284,   285,
     106,   107,    51,   112,   290,   114,   691,    53,    54,   295,
      56,    57,   109,   106,   107,   112,   302,    39,    40,    41,
      32,    33,    34,   106,   107,   249,   109,   450,    32,    33,
      34,    35,    36,    37,   106,   107,   322,   323,    21,   313,
     314,   315,   106,   107,   318,   331,   332,   238,   239,    53,
      54,   113,    56,    57,    32,    33,   280,   106,   107,    51,
     106,   107,    32,    33,   350,   112,   352,   114,   354,    53,
      54,   345,    56,    57,   348,    39,    40,    41,    51,   353,
      51,    52,    53,   259,   260,   261,    32,    33,    34,    35,
      36,    37,   114,   379,   106,   107,    21,    51,   384,   385,
      14,    15,   106,   107,   106,   107,    32,    33,    34,    52,
     114,   302,   114,    27,   106,   107,   292,   403,    21,   310,
     311,    52,   106,   107,   113,   316,   317,   113,   106,   107,
     114,   322,   323,   106,   107,   657,   106,   107,    59,    60,
     331,   332,   109,   106,   107,   109,   432,   433,   113,   112,
     436,   342,   106,   107,   451,   441,   453,    29,    51,    52,
     106,   107,    33,   106,   107,    51,    52,    51,   114,    99,
     456,    61,    62,   584,   460,   106,   107,   458,   589,   590,
     106,   107,    43,   571,   155,   573,   113,   108,    49,   475,
     476,   113,    51,    52,   115,   481,   482,   483,   484,   485,
     486,   487,   488,   489,   490,   491,   492,   493,   494,   495,
     496,   113,   436,   106,   107,   112,   502,   114,   504,   505,
     106,   107,   106,   107,    85,    53,    54,   403,    56,    57,
     653,    92,    51,    52,   515,   112,   517,   114,    32,    33,
      34,    35,    36,    37,   113,   106,   107,   106,   107,   535,
     536,   113,   113,   539,   106,   107,    53,    54,   113,    56,
      57,    39,    40,    41,   455,   456,   112,    52,   114,   460,
     113,   447,   106,   107,    52,   113,   106,   107,   106,   107,
     114,   567,   112,   459,   475,   476,   114,   106,   107,    52,
     481,   482,   483,   484,   485,   486,   487,   488,   489,   490,
     491,   492,   493,   494,   495,   496,   106,   107,   648,   106,
     107,   502,   106,   107,   114,    53,    54,   114,    56,    57,
     114,   106,   107,   111,   112,   611,   612,    52,   614,   615,
     506,   302,   743,   744,   113,   746,   747,   113,   749,   750,
     626,   752,   753,   106,   107,    16,    17,   633,    51,   635,
      53,    54,   323,    56,    57,    39,    40,    41,   113,   645,
     331,   332,   106,   107,   650,    52,   113,    51,   106,   107,
     656,   109,   658,   659,   660,   661,    35,    52,   554,   113,
     720,   106,   107,   106,   107,   671,   672,    46,    47,   112,
      49,   677,   678,   113,    53,    54,   682,    52,   112,    58,
     114,   687,   113,   106,   107,   113,   106,   107,    32,    33,
      34,    35,    36,    37,   114,   110,   498,   499,   500,   106,
     107,   113,    81,    82,    83,   106,   107,    51,   109,    61,
      62,   106,   107,   719,    93,   721,   722,    52,    97,    52,
     726,   113,   728,    52,   730,    52,   732,    39,    40,    41,
     736,   106,   107,   113,   113,   106,   107,   116,    50,    46,
      47,   637,    49,   114,   112,   656,   657,   658,   659,   660,
     661,    58,   113,   113,   760,   761,   762,   763,   764,   765,
     766,   767,   106,   107,   112,   456,   114,   106,   107,   460,
     109,   106,   107,   106,   107,    82,    23,   106,   107,   106,
     107,    21,    36,    37,   475,   476,    93,    41,   106,   107,
      97,   109,    23,   484,   485,   486,   487,   488,   489,   490,
     491,   492,   493,   494,   495,   496,   113,    36,    37,   116,
      20,   502,    66,    52,    43,   726,   112,   728,   114,   730,
     112,   732,   114,    32,    33,    34,    35,    36,    37,   111,
     109,    32,    33,    34,    35,    36,    37,    66,   106,   107,
     112,    22,    51,    97,    53,    54,   114,    56,    57,   760,
     761,   762,   763,   764,   765,   766,   767,   111,   112,    52,
     114,   663,   664,   665,   666,   119,   120,   106,   107,    98,
      32,    33,    34,    35,    36,    37,   130,   111,    39,    40,
      41,    35,   111,   112,    30,   114,    39,    40,    41,    50,
     119,    32,    46,    47,    52,    49,   150,   106,   107,    53,
      54,   130,   106,   107,    58,   106,   107,    39,    40,    41,
     114,   165,   109,   106,   107,   111,   106,   107,    50,    53,
      54,   150,    56,    57,   114,   727,    52,   729,    82,   731,
     112,   733,   114,   187,   113,   189,   165,   106,   107,    93,
     109,   195,   196,    97,   106,   107,   106,   107,   106,   107,
     106,   107,   112,   207,   114,    52,    61,   111,   114,   113,
      53,    54,   116,    56,    57,   656,   109,   658,   659,   660,
     661,   109,   106,   107,    52,    56,    57,    58,   112,    52,
     106,   107,    21,   785,   786,   787,   788,   789,   790,   791,
     792,   793,   794,   795,   796,   797,   798,   799,   800,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   106,
     107,    21,    21,   106,   107,    21,    21,   271,    21,   112,
      21,    32,    33,    34,    35,    36,    37,    21,   106,   107,
     259,   260,   261,   106,   107,   726,    93,   728,   292,   730,
      20,   732,    53,    54,   273,    56,    57,    35,    20,   109,
     279,   106,   107,   106,   107,    46,    47,   109,    49,   114,
      21,   114,    53,   292,    21,    21,    35,    58,    21,   760,
     761,   762,   763,   764,   765,   766,   767,    46,    47,    20,
      49,    39,    40,    41,    53,    54,   106,   107,    22,    58,
      20,    82,    50,    20,   114,   106,   107,    39,    40,    41,
     354,    35,    93,    99,   106,   107,    97,    20,    50,    43,
      44,    45,   114,    82,    48,    49,    52,    53,    54,   114,
      56,    57,   113,    39,    93,   116,   109,   114,    97,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    53,    54,   113,    56,    57,   116,   114,   403,
     379,   114,   381,   113,    88,    89,    90,    91,   113,   109,
      94,    95,    21,   117,    51,    99,   100,   101,   422,    35,
     106,   107,   106,   107,   403,   429,   430,   106,   107,   113,
      46,    47,    39,    49,   112,   114,    21,    53,    54,    39,
      40,    41,    58,   447,    21,   106,   107,   114,   109,   109,
      50,   430,    39,    40,    41,   459,    39,    40,    41,    39,
      40,    41,   441,    50,   109,   109,    82,    50,   447,    28,
      50,    53,    54,    51,    56,    57,    35,    93,    51,   109,
     459,    97,    52,    42,    43,    44,    45,    46,    47,    48,
      49,    52,    52,   430,    53,    54,   441,   113,   558,    58,
     116,   298,   506,   507,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,   279,    53,    54,   501,
      56,    57,   270,    82,   106,   107,   356,   506,    -1,    88,
      89,    90,    91,    98,    93,    94,    95,    96,    97,    -1,
      99,   100,   101,    -1,    27,   524,    -1,   106,   107,    -1,
     554,   555,   556,    -1,   113,   106,   107,   116,    -1,    -1,
      43,    44,    45,   114,    -1,    48,    49,    39,    40,    41,
     106,   107,    -1,    -1,    -1,   554,   112,    -1,    50,   558,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,   106,   107,    -1,   106,   107,    -1,    -1,    -1,
     114,    84,    85,   114,    -1,    88,    89,    90,    91,    92,
      -1,    94,    95,    -1,   106,   107,    99,   100,   101,   106,
     107,   625,   114,   106,   107,    -1,    -1,   114,   106,   107,
     113,    35,    -1,   637,    -1,    -1,   114,    -1,    -1,    43,
      44,    45,    46,    47,    48,    49,    -1,    -1,    -1,    53,
      54,    -1,    -1,    -1,    58,    -1,    -1,    -1,   637,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,   229,   230,   231,   232,   233,   234,    82,    77,
      78,    79,    80,    -1,    88,    89,    90,    91,    -1,    93,
      94,    95,    -1,    97,    -1,    99,   100,   101,    16,    17,
      18,    19,   106,   107,    -1,    -1,    35,    -1,    -1,   113,
      -1,    -1,   116,   117,    43,    44,    45,    46,    47,    48,
      49,    -1,    -1,    -1,    53,    54,    -1,    -1,    -1,    58,
     102,   103,   104,   105,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    -1,    -1,    53,    54,
      -1,    56,    57,    82,    -1,    -1,    -1,    -1,    -1,    88,
      89,    90,    91,    92,    93,    94,    95,    -1,    97,    -1,
      99,   100,   101,    -1,    -1,    -1,    -1,   106,   107,    -1,
      35,    -1,    -1,    -1,   113,    -1,    -1,   116,    43,    44,
      45,    46,    47,    48,    49,    -1,    -1,    -1,    53,    54,
      -1,   106,   107,    58,   109,    -1,    -1,    -1,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,
      -1,    -1,    -1,    88,    89,    90,    91,    -1,    93,    94,
      95,    -1,    97,    -1,    99,   100,   101,    -1,    35,    -1,
      -1,   106,   107,    -1,    -1,    -1,    -1,    -1,   113,    46,
      47,   116,    49,    -1,    -1,    -1,    53,    54,    -1,    -1,
      -1,    58,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    35,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    43,    44,    45,    -1,    82,    48,    49,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    93,    -1,    -1,    -1,
      97,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    -1,    -1,    -1,   113,    -1,    -1,   116,
      -1,    -1,    -1,    -1,    -1,    -1,    88,    89,    90,    91,
      -1,    -1,    94,    95,    36,    -1,    -1,    99,   100,   101,
      -1,    43,    44,    45,   106,   107,    48,    49,    -1,    -1,
      -1,   113,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    88,    89,    90,    91,
      -1,    -1,    94,    95,    -1,    -1,    38,    99,   100,   101,
      -1,    43,    44,    45,   106,   107,    48,    49,    -1,    -1,
      -1,   113,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    88,    89,    90,    91,
      -1,    -1,    94,    95,    -1,    -1,    38,    99,   100,   101,
      -1,    43,    44,    45,   106,   107,    48,    49,    -1,    -1,
      -1,   113,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    88,    89,    90,    91,
      -1,    -1,    94,    95,    -1,    -1,    38,    99,   100,   101,
      -1,    43,    44,    45,   106,   107,    48,    49,    -1,    -1,
      -1,   113,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    88,    89,    90,    91,
      -1,    -1,    94,    95,    -1,    38,    -1,    99,   100,   101,
      43,    44,    45,    -1,   106,   107,    49,    -1,    -1,    -1,
      -1,   113,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    88,    89,    90,    91,    -1,
      -1,    94,    95,    -1,    38,    -1,    99,   100,   101,    43,
      44,    45,    -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,
     113,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    89,    90,    91,    -1,    -1,
      94,    95,    -1,    38,    -1,    99,   100,   101,    43,    44,
      45,    -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,   113,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    89,    90,    91,    -1,    -1,    94,
      95,    -1,    -1,    -1,    99,   100,   101,    -1,    -1,    43,
      44,    45,    46,    47,    48,    49,    -1,    -1,   113,    53,
      54,    -1,    -1,    -1,    58,    -1,    -1,    -1,    -1,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,
      -1,    -1,    -1,    -1,    88,    89,    90,    91,    -1,    93,
      94,    95,    -1,    97,    -1,    99,   100,   101,    42,    43,
      44,    45,   106,   107,    48,    49,    -1,    -1,    -1,   113,
      -1,    -1,   116,    -1,    -1,    -1,    -1,    -1,    -1,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    85,    -1,    -1,    88,    89,    90,    91,    92,    -1,
      94,    95,    -1,    -1,    -1,    99,   100,   101,    -1,    43,
      44,    45,   106,   107,    48,    49,    -1,    -1,    -1,   113,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    85,    -1,    -1,    88,    89,    90,    91,    92,    -1,
      94,    95,    43,    44,    45,    99,   100,   101,    49,    -1,
      -1,    -1,   106,   107,    -1,    -1,    -1,    -1,    -1,   113,
      -1,    -1,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    85,    -1,    -1,    88,    89,    90,
      91,    92,    -1,    94,    95,    43,    44,    45,    99,   100,
     101,    49,    -1,    -1,    -1,   106,   107,    -1,    -1,    -1,
      -1,    -1,   113,    -1,    -1,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,    -1,    -1,
      88,    89,    90,    91,    92,    -1,    94,    95,    -1,    -1,
      -1,    99,   100,   101,    -1,    43,    44,    45,   106,   107,
      48,    49,    -1,    -1,    -1,   113,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      88,    89,    90,    91,    -1,    -1,    94,    95,    -1,    -1,
      -1,    99,   100,   101,    -1,    43,    44,    45,   106,   107,
      48,    49,    -1,    -1,    -1,   113,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      88,    89,    90,    91,    -1,    -1,    94,    95,    -1,    -1,
      -1,    99,   100,   101,    -1,    43,    44,    45,   106,   107,
      48,    49,    -1,    -1,    -1,   113,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      88,    89,    90,    91,    -1,    -1,    94,    95,    -1,    -1,
      -1,    99,   100,   101,    -1,    43,    44,    45,   106,   107,
      48,    49,    -1,    -1,    -1,   113,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      88,    89,    90,    91,    -1,    -1,    94,    95,    43,    44,
      45,    99,   100,   101,    49,    -1,    -1,    -1,   106,   107,
      -1,    -1,    -1,    -1,    -1,   113,    -1,    -1,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    89,    90,    91,    -1,    -1,    94,
      95,    43,    44,    45,    99,   100,   101,    49,    -1,    -1,
      -1,   106,   107,    -1,    -1,    -1,    -1,    -1,   113,    -1,
      -1,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    46,    47,    -1,    49,    -1,    -1,    -1,
      53,    54,    -1,    -1,    -1,    58,    88,    89,    90,    91,
      -1,    -1,    94,    95,    -1,    -1,    -1,    99,   100,   101,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,
      -1,   113,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      93,    -1,    -1,    -1,    97,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     113,    -1,    -1,   116
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    21,   119,   120,   123,   124,   125,   126,   128,
     131,   141,   142,   153,   156,    99,    99,    99,    99,    99,
      99,    99,    98,    98,    98,    98,    14,    15,    27,   157,
       0,    20,   110,    20,   110,    16,    17,    18,    19,   110,
     132,    21,    21,    21,    21,   113,   113,   113,   113,    35,
      43,    44,    45,    46,    47,    48,    49,    53,    54,    58,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    82,    88,    89,    90,    91,    92,    93,    94,
      95,    97,    99,   100,   101,   106,   107,   113,   116,   160,
     161,   162,   163,   168,   170,   171,   172,   173,   174,   175,
      28,    42,    49,    96,   113,   160,   167,   168,   171,    49,
     113,   158,   159,   160,   168,   109,   160,   111,   158,    22,
      49,    75,   113,   129,   137,   138,   139,   164,   168,   171,
     158,    29,   135,    33,   133,    16,    17,   158,   133,    43,
      49,    85,    92,   106,   107,   113,   148,   149,   150,   151,
     152,   171,   172,   148,    27,    49,    84,   143,   148,   171,
      27,    86,    87,   154,   155,    99,   127,   127,   127,   127,
      36,   170,   158,   113,   159,   113,   159,   113,   158,   113,
     158,   158,   167,   158,   158,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   110,   169,   169,   169,   113,   113,   113,   174,   174,
     160,   171,   117,   158,   164,   166,   168,   170,   171,    53,
      54,    56,    57,   106,   107,    55,   108,   112,   106,   107,
      59,    60,   108,   115,    61,    62,   113,   167,   167,   113,
     160,   167,   171,    32,    33,    34,    35,    36,    37,    39,
      40,    41,    23,    32,    33,    34,    35,    36,    37,   167,
      21,    23,   109,    20,   111,   170,   167,   171,   109,   112,
     139,   140,    77,    78,    79,    80,   165,   171,   111,   171,
      30,   136,    49,   107,   171,    32,   134,   109,   111,   134,
     158,   167,   113,   169,   106,   107,   150,   150,   148,   171,
     106,   107,   109,   108,   115,    61,   106,   107,   108,   109,
     158,   167,    42,   113,   144,   148,   171,   109,    32,    33,
      34,   147,   147,   158,   109,   135,   112,   114,   114,   114,
     114,    36,    21,   158,   170,    21,   158,   170,    21,   171,
      21,   171,    21,    21,    50,    21,    21,   160,   160,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   160,
      93,   171,   171,   170,   170,   170,   170,   114,   114,    21,
     117,   112,   117,   117,    24,    25,   161,   161,   161,   161,
     161,   161,   163,   163,   171,   172,   172,   173,   173,   173,
     173,   173,   158,    50,   170,   114,   160,   160,   160,   160,
     160,   160,   167,   167,   167,   160,   171,   171,   171,   171,
     171,   171,    50,   157,   160,    81,    83,   121,   122,   168,
      20,    22,    50,    76,   138,   170,   139,   171,   171,   171,
     171,    20,   171,   109,   167,    38,    38,    49,   171,   135,
      16,    17,    19,   132,   109,    21,    50,   148,    43,    49,
     113,   114,   149,   172,   149,   172,   150,   173,   173,   173,
     149,   172,   149,   172,   150,    21,    50,   144,   144,   148,
     171,    39,    40,    41,    50,    32,    33,    34,    35,    36,
      37,    32,    33,    34,    35,    36,    37,   148,   171,   148,
     171,    21,    21,    99,    20,    20,    20,    20,   172,   114,
     114,   173,   114,   114,   173,   114,   171,   114,   171,   173,
     160,   171,   163,   162,   112,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   112,   112,   114,   114,   112,
     111,   114,   114,   114,   168,   171,   168,   171,   171,   114,
     160,   167,   171,   114,    22,   113,   113,   109,   112,   160,
     121,   160,   171,    22,   170,   137,   171,    50,   167,   136,
     135,   133,    16,   133,   149,   172,   148,   171,   114,   158,
     167,   143,   143,   148,   171,   114,   144,   144,   144,   148,
     171,   148,   171,   148,   171,   148,   171,   148,   171,   148,
     171,   148,   171,   148,   148,   148,   148,   148,   148,   145,
     145,    32,    33,   145,    32,    33,   145,   154,   148,   171,
     171,   167,   160,   158,   158,    51,    51,   168,   171,   171,
     171,   117,   117,    26,   117,    26,   117,    51,   167,   160,
     160,   122,   109,   109,    22,    31,   130,   109,   107,   171,
      50,   109,   136,   134,   109,   134,    51,    21,    50,    51,
     147,   147,   112,   171,   171,   171,   171,   109,   109,   109,
     109,    21,    21,   160,   171,   114,   114,   112,   112,   171,
     171,   167,   112,   114,   171,   109,    38,    51,    38,   171,
     109,   135,   109,   148,   172,   143,   148,   171,   148,   171,
     102,   103,   104,   105,   146,   145,   145,   145,   145,   171,
     171,    52,    52,   171,   171,   117,   117,    52,   171,    51,
     107,    51,    51,   136,    52,    52,    51,    52,    51,    52,
      51,    52,    51,    52,   114,   114,   112,   114,   171,    38,
     171,    38,   109,   148,   171,   145,   148,   171,   145,   148,
     171,   145,   148,   171,   145,   171,    52,    52,    52,    52,
     147,   147,   147,   147,   147,   147,   147,   147,   114,   148,
     171,   148,   171,   148,   171,   148,   171,   148,   171,   148,
     171,   148,   171,   148,   171,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145
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
#line 144 "src/mmlparse2.y"
    { code_set_root((yyvsp[(1) - (1)].code)); ;}
    break;

  case 3:
#line 145 "src/mmlparse2.y"
    { code_set_root((yyvsp[(1) - (1)].code)); ;}
    break;

  case 4:
#line 146 "src/mmlparse2.y"
    { code_set_root((yyvsp[(1) - (1)].code)); ;}
    break;

  case 5:
#line 147 "src/mmlparse2.y"
    { code_set_root((yyvsp[(1) - (1)].code)); ;}
    break;

  case 6:
#line 148 "src/mmlparse2.y"
    { code_set_root((yyvsp[(1) - (1)].code)); ;}
    break;

  case 7:
#line 149 "src/mmlparse2.y"
    { code_set_root((yyvsp[(1) - (1)].code)); ;}
    break;

  case 8:
#line 150 "src/mmlparse2.y"
    { code_set_root((yyvsp[(1) - (1)].code)); ;}
    break;

  case 9:
#line 151 "src/mmlparse2.y"
    { code_set_root((yyvsp[(1) - (1)].code)); ;}
    break;

  case 10:
#line 152 "src/mmlparse2.y"
    { code_set_root((yyvsp[(1) - (1)].code)); ;}
    break;

  case 11:
#line 153 "src/mmlparse2.y"
    { code_set_root((yyvsp[(1) - (1)].code)); ;}
    break;

  case 12:
#line 154 "src/mmlparse2.y"
    { code_set_root((yyvsp[(1) - (1)].code)); ;}
    break;

  case 13:
#line 162 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_newsym_set1, 3,
            code_new_name((yyvsp[(2) - (5)].name)),                                       /* Name */
            code_new_inst(i_idxset_pseudo_new, 1,               /* index set */
               code_new_inst(i_bool_true, 0)),              
            (yyvsp[(4) - (5)].code));                                              /* initial set */
      ;}
    break;

  case 14:
#line 169 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_newsym_set1, 3,
            code_new_name((yyvsp[(2) - (8)].name)),                                       /* Name */
            (yyvsp[(4) - (8)].code),                                                 /* index set */
            (yyvsp[(7) - (8)].code));                                                      /* set */
      ;}
    break;

  case 15:
#line 175 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_newsym_set2, 3,
            code_new_name((yyvsp[(2) - (8)].name)),                                       /* Name */
            (yyvsp[(4) - (8)].code),                                                 /* index set */
            (yyvsp[(7) - (8)].code));                                   /* initial set_entry_list */
      ;}
    break;

  case 16:
#line 181 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_newsym_set2, 3,
            code_new_name((yyvsp[(2) - (7)].name)),                                       /* Name */
            code_new_inst(i_idxset_pseudo_new, 1,               /* index set */
               code_new_inst(i_bool_true, 0)),              
            (yyvsp[(6) - (7)].code));                                   /* initial set_entry_list */
      ;}
    break;

  case 17:
#line 191 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_entry_list_new, 1, (yyvsp[(1) - (1)].code)); ;}
    break;

  case 18:
#line 192 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_entry_list_add, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 19:
#line 195 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_entry_list_subsets, 3, (yyvsp[(3) - (6)].code), (yyvsp[(5) - (6)].code), code_new_numb(numb_new_integer(-1)));
      ;}
    break;

  case 20:
#line 198 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_entry_list_subsets, 3, (yyvsp[(3) - (8)].code), (yyvsp[(5) - (8)].code), (yyvsp[(7) - (8)].code));
      ;}
    break;

  case 21:
#line 201 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_entry_list_powerset, 1, (yyvsp[(3) - (4)].code));
      ;}
    break;

  case 22:
#line 207 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_entry, 2, (yyvsp[(1) - (2)].code), (yyvsp[(2) - (2)].code)); ;}
    break;

  case 23:
#line 216 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_newdef, 3,
            code_new_define((yyvsp[(2) - (8)].def)),
            code_new_inst(i_tuple_new, 1, (yyvsp[(4) - (8)].code)),
            (yyvsp[(7) - (8)].code));
      ;}
    break;

  case 24:
#line 225 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_newdef, 3,
            code_new_define((yyvsp[(2) - (8)].def)),
            code_new_inst(i_tuple_new, 1, (yyvsp[(4) - (8)].code)),
            (yyvsp[(7) - (8)].code));
      ;}
    break;

  case 25:
#line 234 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_newdef, 3,
            code_new_define((yyvsp[(2) - (8)].def)),
            code_new_inst(i_tuple_new, 1, (yyvsp[(4) - (8)].code)),
            (yyvsp[(7) - (8)].code));
      ;}
    break;

  case 26:
#line 243 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_newdef, 3,
            code_new_define((yyvsp[(2) - (8)].def)),
            code_new_inst(i_tuple_new, 1, (yyvsp[(4) - (8)].code)),
            (yyvsp[(7) - (8)].code));
      ;}
    break;

  case 27:
#line 252 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_elem_list_new, 1, code_new_name((yyvsp[(1) - (1)].name)));
      ;}
    break;

  case 28:
#line 255 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_elem_list_add, 2, (yyvsp[(1) - (3)].code), code_new_name((yyvsp[(3) - (3)].name)));
      ;}
    break;

  case 29:
#line 265 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_newsym_para1, 4, code_new_name((yyvsp[(2) - (9)].name)), (yyvsp[(4) - (9)].code), (yyvsp[(7) - (9)].code), (yyvsp[(8) - (9)].code));
      ;}
    break;

  case 30:
#line 268 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_newsym_para2, 4, code_new_name((yyvsp[(2) - (8)].name)), (yyvsp[(4) - (8)].code), (yyvsp[(7) - (8)].code), code_new_inst(i_nop, 0));
      ;}
    break;

  case 31:
#line 271 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_newsym_para1, 4,
            code_new_name((yyvsp[(2) - (5)].name)),
            code_new_inst(i_idxset_pseudo_new, 1, code_new_inst(i_bool_true, 0)),
            (yyvsp[(4) - (5)].code),
            code_new_inst(i_nop, 0));
      ;}
    break;

  case 32:
#line 278 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_nop, 0); ;}
    break;

  case 33:
#line 281 "src/mmlparse2.y"
    { (yyval.code) = (yyvsp[(1) - (1)].code); ;}
    break;

  case 34:
#line 282 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_entry_list_new, 1,
            code_new_inst(i_entry, 2, code_new_inst(i_tuple_empty, 0), (yyvsp[(1) - (1)].code)));
      ;}
    break;

  case 35:
#line 289 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_nop, 0); ;}
    break;

  case 36:
#line 290 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_entry, 2, code_new_inst(i_tuple_empty, 0), (yyvsp[(2) - (2)].code)); ;}
    break;

  case 37:
#line 298 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_newsym_var, 7,
            code_new_name((yyvsp[(2) - (9)].name)),
            (yyvsp[(4) - (9)].code), (yyvsp[(6) - (9)].code), (yyvsp[(7) - (9)].code), (yyvsp[(8) - (9)].code),
            code_new_numb(numb_new_integer(0)),
            code_new_numb(numb_new_integer(0)));
      ;}
    break;

  case 38:
#line 305 "src/mmlparse2.y"
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

  case 39:
#line 314 "src/mmlparse2.y"
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

  case 40:
#line 324 "src/mmlparse2.y"
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

  case 41:
#line 335 "src/mmlparse2.y"
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

  case 42:
#line 344 "src/mmlparse2.y"
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

  case 43:
#line 354 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_newsym_var, 7,
            code_new_name((yyvsp[(2) - (11)].name)), (yyvsp[(4) - (11)].code), code_new_varclass(VAR_INT), (yyvsp[(7) - (11)].code), (yyvsp[(8) - (11)].code), (yyvsp[(9) - (11)].code), (yyvsp[(10) - (11)].code));
      ;}
    break;

  case 44:
#line 358 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_newsym_var, 7,
            code_new_name((yyvsp[(2) - (8)].name)),
            code_new_inst(i_idxset_pseudo_new, 1,
               code_new_inst(i_bool_true, 0)),              
            code_new_varclass(VAR_INT), (yyvsp[(4) - (8)].code), (yyvsp[(5) - (8)].code), (yyvsp[(6) - (8)].code), (yyvsp[(7) - (8)].code));
      ;}
    break;

  case 45:
#line 368 "src/mmlparse2.y"
    { (yyval.code) = code_new_varclass(VAR_CON); ;}
    break;

  case 46:
#line 369 "src/mmlparse2.y"
    { (yyval.code) = code_new_varclass(VAR_CON); ;}
    break;

  case 47:
#line 370 "src/mmlparse2.y"
    { (yyval.code) = code_new_varclass(VAR_IMP); ;}
    break;

  case 48:
#line 374 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_bound_new, 1, code_new_numb(numb_new_integer(0)));
      ;}
    break;

  case 49:
#line 377 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_bound_new, 1, (yyvsp[(2) - (2)].code)); ;}
    break;

  case 50:
#line 378 "src/mmlparse2.y"
    { (yyval.code) = code_new_bound(BOUND_MINUS_INFTY); ;}
    break;

  case 51:
#line 379 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_expr_if, 3, (yyvsp[(3) - (9)].code),
            code_new_inst(i_bound_new, 1, (yyvsp[(5) - (9)].code)),
            code_new_bound(BOUND_MINUS_INFTY));
      ;}
    break;

  case 52:
#line 384 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_expr_if, 3, (yyvsp[(3) - (9)].code),
            code_new_bound(BOUND_MINUS_INFTY),
            code_new_inst(i_bound_new, 1, (yyvsp[(8) - (9)].code)));
      ;}
    break;

  case 53:
#line 392 "src/mmlparse2.y"
    { (yyval.code) = code_new_bound(BOUND_INFTY); ;}
    break;

  case 54:
#line 393 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_bound_new, 1, (yyvsp[(2) - (2)].code)); ;}
    break;

  case 55:
#line 394 "src/mmlparse2.y"
    { (yyval.code) = code_new_bound(BOUND_INFTY); ;}
    break;

  case 56:
#line 395 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_expr_if, 3, (yyvsp[(3) - (8)].code),
            code_new_inst(i_bound_new, 1, (yyvsp[(5) - (8)].code)),
            code_new_bound(BOUND_INFTY));
      ;}
    break;

  case 57:
#line 400 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_expr_if, 3, (yyvsp[(3) - (8)].code),
            code_new_bound(BOUND_INFTY),
            code_new_inst(i_bound_new, 1, (yyvsp[(7) - (8)].code)));
      ;}
    break;

  case 58:
#line 408 "src/mmlparse2.y"
    { (yyval.code) = code_new_numb(numb_new_integer(0)); ;}
    break;

  case 59:
#line 409 "src/mmlparse2.y"
    { (yyval.code) = (yyvsp[(2) - (2)].code); ;}
    break;

  case 60:
#line 413 "src/mmlparse2.y"
    { (yyval.code) = code_new_numb(numb_new_integer(0)); ;}
    break;

  case 61:
#line 414 "src/mmlparse2.y"
    { (yyval.code) = (yyvsp[(2) - (2)].code); ;}
    break;

  case 62:
#line 422 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_entry_list_new, 1, (yyvsp[(1) - (1)].code)); ;}
    break;

  case 63:
#line 423 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_entry_list_add, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 64:
#line 426 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_read, 1, (yyvsp[(1) - (1)].code)); ;}
    break;

  case 65:
#line 427 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_list_matrix, 2, (yyvsp[(1) - (2)].code), (yyvsp[(2) - (2)].code)); ;}
    break;

  case 66:
#line 431 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_entry, 2, (yyvsp[(1) - (2)].code), (yyvsp[(2) - (2)].code)); ;}
    break;

  case 67:
#line 435 "src/mmlparse2.y"
    { (yyval.code) = (yyvsp[(2) - (3)].code); ;}
    break;

  case 68:
#line 439 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_matrix_list_new, 2, (yyvsp[(1) - (3)].code), (yyvsp[(2) - (3)].code));
      ;}
    break;

  case 69:
#line 442 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_matrix_list_add, 3, (yyvsp[(1) - (4)].code), (yyvsp[(2) - (4)].code), (yyvsp[(3) - (4)].code));
      ;}
    break;

  case 70:
#line 454 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_object_min, 2, code_new_name((yyvsp[(2) - (5)].name)), (yyvsp[(4) - (5)].code));
      ;}
    break;

  case 71:
#line 457 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_object_max, 2, code_new_name((yyvsp[(2) - (5)].name)), (yyvsp[(4) - (5)].code));
      ;}
    break;

  case 72:
#line 467 "src/mmlparse2.y"
    {
        (yyval.code) = code_new_inst(i_subto, 2, code_new_name((yyvsp[(2) - (5)].name)), (yyvsp[(4) - (5)].code));
     ;}
    break;

  case 73:
#line 473 "src/mmlparse2.y"
    {
        (yyval.code) = code_new_inst(i_constraint, 4, (yyvsp[(1) - (4)].code), (yyvsp[(2) - (4)].code), (yyvsp[(3) - (4)].code), code_new_bits((yyvsp[(4) - (4)].bits)));
     ;}
    break;

  case 74:
#line 476 "src/mmlparse2.y"
    {
        (yyval.code) = code_new_inst(i_constraint, 4, (yyvsp[(1) - (4)].code), (yyvsp[(2) - (4)].code),
           code_new_inst(i_term_expr, 1, (yyvsp[(3) - (4)].code)),
           code_new_bits((yyvsp[(4) - (4)].bits)));
     ;}
    break;

  case 75:
#line 481 "src/mmlparse2.y"
    {
        (yyval.code) = code_new_inst(i_constraint, 4,
           code_new_inst(i_term_expr, 1, (yyvsp[(1) - (4)].code)),
           (yyvsp[(2) - (4)].code), (yyvsp[(3) - (4)].code), code_new_bits((yyvsp[(4) - (4)].bits)));
     ;}
    break;

  case 76:
#line 486 "src/mmlparse2.y"
    { 
        (yyval.code) = code_new_inst(i_constraint, 4,
           code_new_inst(i_term_expr, 1, (yyvsp[(1) - (4)].code)),
           (yyvsp[(2) - (4)].code),
           code_new_inst(i_term_expr, 1, (yyvsp[(3) - (4)].code)),
           code_new_bits((yyvsp[(4) - (4)].bits)));
     ;}
    break;

  case 77:
#line 493 "src/mmlparse2.y"
    {
        (yyval.code) = code_new_inst(i_rangeconst, 6, (yyvsp[(1) - (6)].code), (yyvsp[(3) - (6)].code), (yyvsp[(5) - (6)].code), (yyvsp[(2) - (6)].code),
           code_new_contype(CON_RHS), code_new_bits((yyvsp[(6) - (6)].bits))); 
     ;}
    break;

  case 78:
#line 497 "src/mmlparse2.y"
    {
        (yyval.code) = code_new_inst(i_rangeconst, 6, (yyvsp[(1) - (6)].code),
           code_new_inst(i_term_expr, 1, (yyvsp[(3) - (6)].code)), (yyvsp[(5) - (6)].code), (yyvsp[(2) - (6)].code),
           code_new_contype(CON_RHS), code_new_bits((yyvsp[(6) - (6)].bits))); 
     ;}
    break;

  case 79:
#line 502 "src/mmlparse2.y"
    {
        (yyval.code) = code_new_inst(i_rangeconst, 6, (yyvsp[(5) - (6)].code), (yyvsp[(3) - (6)].code), (yyvsp[(1) - (6)].code), (yyvsp[(2) - (6)].code),
           code_new_contype(CON_LHS), code_new_bits((yyvsp[(6) - (6)].bits))); 
     ;}
    break;

  case 80:
#line 506 "src/mmlparse2.y"
    {
        (yyval.code) = code_new_inst(i_rangeconst, 6, (yyvsp[(5) - (6)].code),
           code_new_inst(i_term_expr, 1, (yyvsp[(3) - (6)].code)),
           (yyvsp[(1) - (6)].code), (yyvsp[(2) - (6)].code),
           code_new_contype(CON_LHS), code_new_bits((yyvsp[(6) - (6)].bits))); 
     ;}
    break;

  case 81:
#line 512 "src/mmlparse2.y"
    {
        (yyval.code) = code_new_inst(i_forall, 2, (yyvsp[(2) - (4)].code), (yyvsp[(4) - (4)].code));
     ;}
    break;

  case 82:
#line 515 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_expr_if, 3, (yyvsp[(2) - (7)].code), (yyvsp[(4) - (7)].code), (yyvsp[(6) - (7)].code));
      ;}
    break;

  case 83:
#line 518 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_vif_else, 8, (yyvsp[(2) - (12)].code), (yyvsp[(4) - (12)].code), (yyvsp[(5) - (12)].code), (yyvsp[(6) - (12)].code), (yyvsp[(8) - (12)].code), (yyvsp[(9) - (12)].code), (yyvsp[(10) - (12)].code), code_new_bits((yyvsp[(12) - (12)].bits)));
      ;}
    break;

  case 84:
#line 521 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_vif_else, 8, (yyvsp[(2) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(4) - (12)].code)),
            (yyvsp[(5) - (12)].code), (yyvsp[(6) - (12)].code), (yyvsp[(8) - (12)].code), (yyvsp[(9) - (12)].code), (yyvsp[(10) - (12)].code), code_new_bits((yyvsp[(12) - (12)].bits)));
      ;}
    break;

  case 85:
#line 526 "src/mmlparse2.y"
    { 
         (yyval.code) = code_new_inst(i_vif_else, 8, (yyvsp[(2) - (12)].code), (yyvsp[(4) - (12)].code), (yyvsp[(5) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(6) - (12)].code)),
            (yyvsp[(8) - (12)].code), (yyvsp[(9) - (12)].code), (yyvsp[(10) - (12)].code), code_new_bits((yyvsp[(12) - (12)].bits)));
      ;}
    break;

  case 86:
#line 531 "src/mmlparse2.y"
    { 
         (yyval.code) = code_new_inst(i_vif_else, 8, (yyvsp[(2) - (12)].code), (yyvsp[(4) - (12)].code), (yyvsp[(5) - (12)].code), (yyvsp[(6) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(8) - (12)].code)),
            (yyvsp[(9) - (12)].code), (yyvsp[(10) - (12)].code), code_new_bits((yyvsp[(12) - (12)].bits)));
      ;}
    break;

  case 87:
#line 536 "src/mmlparse2.y"
    { 
         (yyval.code) = code_new_inst(i_vif_else, 8, (yyvsp[(2) - (12)].code), (yyvsp[(4) - (12)].code), (yyvsp[(5) - (12)].code), (yyvsp[(6) - (12)].code), (yyvsp[(8) - (12)].code), (yyvsp[(9) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(10) - (12)].code)), code_new_bits((yyvsp[(12) - (12)].bits)));
      ;}
    break;

  case 88:
#line 540 "src/mmlparse2.y"
    { /* ??? This is an error */
         (yyval.code) = code_new_inst(i_vif_else, 8, (yyvsp[(2) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(4) - (12)].code)),
            (yyvsp[(5) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(6) - (12)].code)),
            (yyvsp[(8) - (12)].code), (yyvsp[(9) - (12)].code), (yyvsp[(10) - (12)].code), code_new_bits((yyvsp[(12) - (12)].bits)));
      ;}
    break;

  case 89:
#line 547 "src/mmlparse2.y"
    { 
         (yyval.code) = code_new_inst(i_vif_else, 8, (yyvsp[(2) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(4) - (12)].code)),
            (yyvsp[(5) - (12)].code), (yyvsp[(6) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(8) - (12)].code)),
            (yyvsp[(9) - (12)].code), (yyvsp[(10) - (12)].code), code_new_bits((yyvsp[(12) - (12)].bits)));
      ;}
    break;

  case 90:
#line 554 "src/mmlparse2.y"
    { 
         (yyval.code) = code_new_inst(i_vif_else, 8, (yyvsp[(2) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(4) - (12)].code)),
            (yyvsp[(5) - (12)].code), (yyvsp[(6) - (12)].code), (yyvsp[(8) - (12)].code), (yyvsp[(9) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(10) - (12)].code)), code_new_bits((yyvsp[(12) - (12)].bits)));
      ;}
    break;

  case 91:
#line 560 "src/mmlparse2.y"
    { 
         (yyval.code) = code_new_inst(i_vif_else, 8, (yyvsp[(2) - (12)].code), (yyvsp[(4) - (12)].code), (yyvsp[(5) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(6) - (12)].code)),
            code_new_inst(i_term_expr, 1, (yyvsp[(8) - (12)].code)),
            (yyvsp[(9) - (12)].code), (yyvsp[(10) - (12)].code), code_new_bits((yyvsp[(12) - (12)].bits)));
      ;}
    break;

  case 92:
#line 566 "src/mmlparse2.y"
    { 
         (yyval.code) = code_new_inst(i_vif_else, 8, (yyvsp[(2) - (12)].code), (yyvsp[(4) - (12)].code), (yyvsp[(5) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(6) - (12)].code)),
            (yyvsp[(8) - (12)].code), (yyvsp[(9) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(10) - (12)].code)), code_new_bits((yyvsp[(12) - (12)].bits)));
      ;}
    break;

  case 93:
#line 572 "src/mmlparse2.y"
    { /* ??? This is an error */
         (yyval.code) = code_new_inst(i_vif_else, 8, (yyvsp[(2) - (12)].code), (yyvsp[(4) - (12)].code), (yyvsp[(5) - (12)].code), (yyvsp[(6) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(8) - (12)].code)), (yyvsp[(9) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(10) - (12)].code)), code_new_bits((yyvsp[(12) - (12)].bits)));
      ;}
    break;

  case 94:
#line 577 "src/mmlparse2.y"
    { /* ??? This is an error */
         (yyval.code) = code_new_inst(i_vif_else, 8, (yyvsp[(2) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(4) - (12)].code)),
            (yyvsp[(5) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(6) - (12)].code)),
            code_new_inst(i_term_expr, 1, (yyvsp[(8) - (12)].code)),
            (yyvsp[(9) - (12)].code), (yyvsp[(10) - (12)].code), code_new_bits((yyvsp[(12) - (12)].bits)));
      ;}
    break;

  case 95:
#line 585 "src/mmlparse2.y"
    { /* ??? This is an error */
         (yyval.code) = code_new_inst(i_vif_else, 8, (yyvsp[(2) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(4) - (12)].code)),
            (yyvsp[(5) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(6) - (12)].code)),
            (yyvsp[(8) - (12)].code), (yyvsp[(9) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(10) - (12)].code)), 
            code_new_bits((yyvsp[(12) - (12)].bits)));
      ;}
    break;

  case 96:
#line 594 "src/mmlparse2.y"
    { /* ??? This is an error */
         (yyval.code) = code_new_inst(i_vif_else, 8, (yyvsp[(2) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(4) - (12)].code)),
            (yyvsp[(5) - (12)].code), (yyvsp[(6) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(8) - (12)].code)),
            (yyvsp[(9) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(10) - (12)].code)), 
            code_new_bits((yyvsp[(12) - (12)].bits)));
      ;}
    break;

  case 97:
#line 603 "src/mmlparse2.y"
    { /* ??? This is an error */
         (yyval.code) = code_new_inst(i_vif_else, 8, (yyvsp[(2) - (12)].code), (yyvsp[(4) - (12)].code), (yyvsp[(5) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(6) - (12)].code)),
            code_new_inst(i_term_expr, 1, (yyvsp[(8) - (12)].code)),
            (yyvsp[(9) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(10) - (12)].code)), 
            code_new_bits((yyvsp[(12) - (12)].bits)));
      ;}
    break;

  case 98:
#line 611 "src/mmlparse2.y"
    { /* ??? This is an error */
         (yyval.code) = code_new_inst(i_vif_else, 8, (yyvsp[(2) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(4) - (12)].code)),
            (yyvsp[(5) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(6) - (12)].code)),
            code_new_inst(i_term_expr, 1, (yyvsp[(8) - (12)].code)),
            (yyvsp[(9) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(10) - (12)].code)), 
            code_new_bits((yyvsp[(12) - (12)].bits)));
      ;}
    break;

  case 99:
#line 622 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_vif, 5, (yyvsp[(2) - (8)].code), (yyvsp[(4) - (8)].code), (yyvsp[(5) - (8)].code), (yyvsp[(6) - (8)].code), code_new_bits((yyvsp[(8) - (8)].bits)));
      ;}
    break;

  case 100:
#line 625 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_vif, 5, (yyvsp[(2) - (8)].code), 
            code_new_inst(i_term_expr, 1, (yyvsp[(4) - (8)].code)), (yyvsp[(5) - (8)].code), (yyvsp[(6) - (8)].code), code_new_bits((yyvsp[(8) - (8)].bits)));
      ;}
    break;

  case 101:
#line 629 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_vif, 5, (yyvsp[(2) - (8)].code), 
            (yyvsp[(4) - (8)].code), (yyvsp[(5) - (8)].code), code_new_inst(i_term_expr, 1, (yyvsp[(6) - (8)].code)), 
            code_new_bits((yyvsp[(8) - (8)].bits)));
      ;}
    break;

  case 102:
#line 634 "src/mmlparse2.y"
    { /* ??? This is an error */
         (yyval.code) = code_new_inst(i_vif, 5, (yyvsp[(2) - (8)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(4) - (8)].code)), (yyvsp[(5) - (8)].code), 
            code_new_inst(i_term_expr, 1, (yyvsp[(6) - (8)].code)), code_new_bits((yyvsp[(8) - (8)].bits)));
      ;}
    break;

  case 103:
#line 642 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_vbool_ne, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 104:
#line 643 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_vbool_ne, 2, code_new_inst(i_term_expr, 1, (yyvsp[(1) - (3)].code)), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 105:
#line 646 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_vbool_ne, 2, (yyvsp[(1) - (3)].code), code_new_inst(i_term_expr, 1, (yyvsp[(3) - (3)].code)));
      ;}
    break;

  case 106:
#line 649 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_vbool_eq, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 107:
#line 650 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_vbool_eq, 2, code_new_inst(i_term_expr, 1, (yyvsp[(1) - (3)].code)), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 108:
#line 653 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_vbool_eq, 2, (yyvsp[(1) - (3)].code), code_new_inst(i_term_expr, 1, (yyvsp[(3) - (3)].code)));
      ;}
    break;

  case 109:
#line 656 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_vbool_le, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 110:
#line 657 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_vbool_le, 2, code_new_inst(i_term_expr, 1, (yyvsp[(1) - (3)].code)), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 111:
#line 660 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_vbool_le, 2, (yyvsp[(1) - (3)].code), code_new_inst(i_term_expr, 1, (yyvsp[(3) - (3)].code)));
      ;}
    break;

  case 112:
#line 663 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_vbool_ge, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 113:
#line 664 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_vbool_ge, 2, code_new_inst(i_term_expr, 1, (yyvsp[(1) - (3)].code)), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 114:
#line 667 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_vbool_ge, 2, (yyvsp[(1) - (3)].code), code_new_inst(i_term_expr, 1, (yyvsp[(3) - (3)].code)));
      ;}
    break;

  case 115:
#line 670 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_vbool_lt, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 116:
#line 671 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_vbool_lt, 2, code_new_inst(i_term_expr, 1, (yyvsp[(1) - (3)].code)), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 117:
#line 674 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_vbool_lt, 2, (yyvsp[(1) - (3)].code), code_new_inst(i_term_expr, 1, (yyvsp[(3) - (3)].code)));
      ;}
    break;

  case 118:
#line 677 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_vbool_gt, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 119:
#line 678 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_vbool_gt, 2, code_new_inst(i_term_expr, 1, (yyvsp[(1) - (3)].code)), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 120:
#line 681 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_vbool_gt, 2, (yyvsp[(1) - (3)].code), code_new_inst(i_term_expr, 1, (yyvsp[(3) - (3)].code)));
      ;}
    break;

  case 121:
#line 684 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_vbool_and, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 122:
#line 685 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_vbool_or,  2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 123:
#line 686 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_vbool_xor, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 124:
#line 687 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_vbool_not, 1, (yyvsp[(2) - (2)].code)); ;}
    break;

  case 125:
#line 688 "src/mmlparse2.y"
    { (yyval.code) = (yyvsp[(2) - (3)].code); ;}
    break;

  case 126:
#line 692 "src/mmlparse2.y"
    { (yyval.bits) = 0; ;}
    break;

  case 127:
#line 693 "src/mmlparse2.y"
    { (yyval.bits) = (yyvsp[(1) - (3)].bits) | (yyvsp[(3) - (3)].bits); ;}
    break;

  case 128:
#line 697 "src/mmlparse2.y"
    { (yyval.bits) = LP_FLAG_CON_SCALE; ;}
    break;

  case 129:
#line 698 "src/mmlparse2.y"
    { (yyval.bits) = LP_FLAG_CON_SEPAR; ;}
    break;

  case 130:
#line 699 "src/mmlparse2.y"
    { (yyval.bits) = LP_FLAG_CON_CHECK; ;}
    break;

  case 131:
#line 700 "src/mmlparse2.y"
    { (yyval.bits) = LP_FLAG_CON_INDIC; ;}
    break;

  case 132:
#line 704 "src/mmlparse2.y"
    { (yyval.code) = code_new_contype(CON_RHS); ;}
    break;

  case 133:
#line 705 "src/mmlparse2.y"
    { (yyval.code) = code_new_contype(CON_LHS); ;}
    break;

  case 134:
#line 706 "src/mmlparse2.y"
    { (yyval.code) = code_new_contype(CON_EQUAL); ;}
    break;

  case 135:
#line 710 "src/mmlparse2.y"
    { (yyval.code) = (yyvsp[(1) - (1)].code); ;}
    break;

  case 136:
#line 711 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_term_add, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 137:
#line 712 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_term_sub, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 138:
#line 713 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_term_const, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 139:
#line 714 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_term_sub, 2, (yyvsp[(1) - (3)].code), code_new_inst(i_term_expr, 1, (yyvsp[(3) - (3)].code)));
      ;}
    break;

  case 140:
#line 717 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_term_const, 2, (yyvsp[(3) - (3)].code), (yyvsp[(1) - (3)].code)); ;}
    break;

  case 141:
#line 718 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_term_sub, 2,
            code_new_inst(i_term_expr, 1, (yyvsp[(1) - (3)].code)),
            (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 142:
#line 726 "src/mmlparse2.y"
    { (yyval.code) = (yyvsp[(1) - (1)].code); ;}
    break;

  case 143:
#line 727 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_term_coeff, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));  ;}
    break;

  case 144:
#line 728 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_term_coeff, 2, (yyvsp[(1) - (3)].code),
            code_new_inst(i_expr_div, 2, code_new_numb(numb_new_integer(1)), (yyvsp[(3) - (3)].code)));
      ;}
    break;

  case 145:
#line 732 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_term_coeff, 2, (yyvsp[(3) - (3)].code), (yyvsp[(1) - (3)].code)); ;}
    break;

  case 146:
#line 733 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_term_mul, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 148:
#line 738 "src/mmlparse2.y"
    { (yyval.code) = (yyvsp[(2) - (2)].code); ;}
    break;

  case 149:
#line 739 "src/mmlparse2.y"
    { 
         (yyval.code) = code_new_inst(i_term_coeff, 2, (yyvsp[(2) - (2)].code), code_new_numb(numb_new_integer(-1)));
      ;}
    break;

  case 150:
#line 745 "src/mmlparse2.y"
    { (yyval.code) = (yyvsp[(1) - (1)].code); ;}
    break;

  case 151:
#line 746 "src/mmlparse2.y"
    { 
         (yyval.code) = code_new_inst(i_term_power, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 152:
#line 749 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_term_sum, 2, (yyvsp[(2) - (4)].code), (yyvsp[(4) - (4)].code));
      ;}
    break;

  case 153:
#line 755 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_symbol_deref, 2, code_new_symbol((yyvsp[(1) - (2)].sym)), (yyvsp[(2) - (2)].code));
      ;}
    break;

  case 154:
#line 763 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_vabs, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 155:
#line 764 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_expr_if, 3, (yyvsp[(2) - (7)].code), (yyvsp[(4) - (7)].code), (yyvsp[(6) - (7)].code));
      ;}
    break;

  case 156:
#line 767 "src/mmlparse2.y"
    { (yyval.code) = (yyvsp[(2) - (3)].code); ;}
    break;

  case 157:
#line 775 "src/mmlparse2.y"
    {
        (yyval.code) = code_new_inst(i_sos, 2, code_new_name((yyvsp[(2) - (5)].name)), (yyvsp[(4) - (5)].code));
     ;}
    break;

  case 158:
#line 781 "src/mmlparse2.y"
    {
        (yyval.code) = code_new_inst(i_soset, 3, (yyvsp[(4) - (4)].code), (yyvsp[(1) - (4)].code), (yyvsp[(2) - (4)].code));
     ;}
    break;

  case 159:
#line 784 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_forall, 2, (yyvsp[(2) - (4)].code), (yyvsp[(4) - (4)].code));
      ;}
    break;

  case 160:
#line 790 "src/mmlparse2.y"
    { (yyval.code) = code_new_numb(numb_new_integer(1)); ;}
    break;

  case 161:
#line 791 "src/mmlparse2.y"
    { (yyval.code) = code_new_numb(numb_new_integer(1)); ;}
    break;

  case 162:
#line 792 "src/mmlparse2.y"
    { (yyval.code) = code_new_numb(numb_new_integer(2)); ;}
    break;

  case 163:
#line 800 "src/mmlparse2.y"
    { (yyval.code) = (yyvsp[(2) - (3)].code); ;}
    break;

  case 164:
#line 804 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_print, 1, (yyvsp[(2) - (2)].code)); ;}
    break;

  case 165:
#line 805 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_print, 1, (yyvsp[(2) - (2)].code)); ;}
    break;

  case 166:
#line 806 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_print, 1, (yyvsp[(2) - (2)].code)); ;}
    break;

  case 167:
#line 807 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_print, 1, code_new_symbol((yyvsp[(2) - (2)].sym))); ;}
    break;

  case 168:
#line 808 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_check, 1, (yyvsp[(2) - (2)].code)); ;}
    break;

  case 169:
#line 809 "src/mmlparse2.y"
    {
        (yyval.code) = code_new_inst(i_forall, 2, (yyvsp[(2) - (4)].code), (yyvsp[(4) - (4)].code));
     ;}
    break;

  case 170:
#line 819 "src/mmlparse2.y"
    { (yyval.code) = (yyvsp[(1) - (1)].code); ;}
    break;

  case 171:
#line 820 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_idxset_new, 3,
            code_new_inst(i_tuple_empty, 0), (yyvsp[(1) - (1)].code), code_new_inst(i_bool_true, 0));
      ;}
    break;

  case 172:
#line 827 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_idxset_new, 3, (yyvsp[(1) - (5)].code), (yyvsp[(3) - (5)].code), (yyvsp[(5) - (5)].code));
      ;}
    break;

  case 173:
#line 830 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_idxset_new, 3, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code), code_new_inst(i_bool_true, 0));
      ;}
    break;

  case 175:
#line 837 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_set_union, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 176:
#line 838 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_set_union, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 177:
#line 841 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_set_sdiff, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 178:
#line 842 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_set_minus, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 179:
#line 845 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_set_minus, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 180:
#line 846 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_set_inter, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 182:
#line 850 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_set_union2, 2, (yyvsp[(2) - (4)].code), (yyvsp[(4) - (4)].code)); ;}
    break;

  case 184:
#line 855 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_set_cross, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 185:
#line 856 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_set_cross, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 186:
#line 859 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_set_inter2, 2, (yyvsp[(2) - (4)].code), (yyvsp[(4) - (4)].code)); ;}
    break;

  case 187:
#line 863 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_symbol_deref, 2, code_new_symbol((yyvsp[(1) - (2)].sym)), (yyvsp[(2) - (2)].code));
      ;}
    break;

  case 188:
#line 866 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_define_deref, 2,
            code_new_define((yyvsp[(1) - (4)].def)),
            code_new_inst(i_tuple_new, 1, (yyvsp[(3) - (4)].code)));
      ;}
    break;

  case 189:
#line 871 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_set_empty, 1, code_new_size(0)); ;}
    break;

  case 190:
#line 872 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_set_range2, 3, (yyvsp[(2) - (7)].code), (yyvsp[(4) - (7)].code), (yyvsp[(6) - (7)].code));
      ;}
    break;

  case 191:
#line 875 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_set_range2, 3, (yyvsp[(2) - (5)].code), (yyvsp[(4) - (5)].code), code_new_numb(numb_new_integer(1)));
      ;}
    break;

  case 192:
#line 878 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_set_range, 3, (yyvsp[(2) - (7)].code), (yyvsp[(4) - (7)].code), (yyvsp[(6) - (7)].code));
      ;}
    break;

  case 193:
#line 881 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_set_range, 3, (yyvsp[(2) - (5)].code), (yyvsp[(4) - (5)].code), code_new_numb(numb_new_integer(1)));
      ;}
    break;

  case 194:
#line 884 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_set_argmin, 3, code_new_numb(numb_new_integer(1)), (yyvsp[(2) - (4)].code), (yyvsp[(4) - (4)].code));
      ;}
    break;

  case 195:
#line 887 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_set_argmin, 3, (yyvsp[(3) - (7)].code), (yyvsp[(5) - (7)].code), (yyvsp[(7) - (7)].code));
      ;}
    break;

  case 196:
#line 890 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_set_argmax, 3, code_new_numb(numb_new_integer(1)), (yyvsp[(2) - (4)].code), (yyvsp[(4) - (4)].code));
      ;}
    break;

  case 197:
#line 893 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_set_argmax, 3, (yyvsp[(3) - (7)].code), (yyvsp[(5) - (7)].code), (yyvsp[(7) - (7)].code));
      ;}
    break;

  case 198:
#line 896 "src/mmlparse2.y"
    { (yyval.code) = (yyvsp[(2) - (3)].code); ;}
    break;

  case 199:
#line 897 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_set_new_tuple, 1, (yyvsp[(2) - (3)].code)); ;}
    break;

  case 200:
#line 898 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_set_new_elem, 1, (yyvsp[(2) - (3)].code)); ;}
    break;

  case 201:
#line 899 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_set_idxset, 1, (yyvsp[(2) - (3)].code)); ;}
    break;

  case 202:
#line 900 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_set_expr, 2, (yyvsp[(2) - (5)].code), (yyvsp[(4) - (5)].code)); ;}
    break;

  case 203:
#line 901 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_set_expr, 2, (yyvsp[(2) - (5)].code), (yyvsp[(4) - (5)].code)); ;}
    break;

  case 204:
#line 902 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_set_proj, 2, (yyvsp[(3) - (6)].code), (yyvsp[(5) - (6)].code));
       ;}
    break;

  case 205:
#line 905 "src/mmlparse2.y"
    {
          (yyval.code) = code_new_inst(i_set_indexset, 1, code_new_symbol((yyvsp[(3) - (4)].sym)));
       ;}
    break;

  case 206:
#line 908 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_expr_if, 3, (yyvsp[(2) - (7)].code), (yyvsp[(4) - (7)].code), (yyvsp[(6) - (7)].code));
      ;}
    break;

  case 207:
#line 914 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_read_new, 2, (yyvsp[(2) - (4)].code), (yyvsp[(4) - (4)].code)); ;}
    break;

  case 208:
#line 915 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_read_param, 2, (yyvsp[(1) - (2)].code), (yyvsp[(2) - (2)].code)); ;}
    break;

  case 209:
#line 919 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_read_skip, 1, (yyvsp[(2) - (2)].code)); ;}
    break;

  case 210:
#line 920 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_read_use, 1, (yyvsp[(2) - (2)].code)); ;}
    break;

  case 211:
#line 921 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_read_comment, 1, (yyvsp[(2) - (2)].code)); ;}
    break;

  case 212:
#line 922 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_read_match, 1, (yyvsp[(2) - (2)].code)); ;}
    break;

  case 213:
#line 926 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_tuple_list_new, 1, (yyvsp[(1) - (1)].code));
      ;}
    break;

  case 214:
#line 929 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_tuple_list_add, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 215:
#line 932 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_read, 1, (yyvsp[(1) - (1)].code)); ;}
    break;

  case 216:
#line 936 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_bool_eq, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 217:
#line 937 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_bool_ne, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 218:
#line 938 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_bool_gt, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 219:
#line 939 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_bool_ge, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 220:
#line 940 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_bool_lt, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 221:
#line 941 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_bool_le, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 222:
#line 942 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_bool_seq, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 223:
#line 943 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_bool_sneq, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 224:
#line 944 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_bool_subs, 2, (yyvsp[(3) - (3)].code), (yyvsp[(1) - (3)].code)); ;}
    break;

  case 225:
#line 945 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_bool_sseq, 2, (yyvsp[(3) - (3)].code), (yyvsp[(1) - (3)].code)); ;}
    break;

  case 226:
#line 946 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_bool_subs, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 227:
#line 947 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_bool_sseq, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 228:
#line 948 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_bool_and, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 229:
#line 949 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_bool_or,  2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 230:
#line 950 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_bool_xor, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 231:
#line 951 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_bool_not, 1, (yyvsp[(2) - (2)].code)); ;}
    break;

  case 232:
#line 952 "src/mmlparse2.y"
    { (yyval.code) = (yyvsp[(2) - (3)].code); ;}
    break;

  case 233:
#line 953 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_bool_is_elem, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 234:
#line 954 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_bool_exists, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 235:
#line 955 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_define_deref, 2,
            code_new_define((yyvsp[(1) - (4)].def)),
            code_new_inst(i_tuple_new, 1, (yyvsp[(3) - (4)].code)));
      ;}
    break;

  case 236:
#line 960 "src/mmlparse2.y"
    {
        (yyval.code) = code_new_inst(i_expr_if, 3, (yyvsp[(2) - (7)].code), (yyvsp[(4) - (7)].code), (yyvsp[(6) - (7)].code));
     ;}
    break;

  case 237:
#line 966 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_tuple_empty, 0); ;}
    break;

  case 238:
#line 967 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_tuple_new, 1, (yyvsp[(2) - (3)].code));  ;}
    break;

  case 239:
#line 971 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_tuple_empty, 0);
      ;}
    break;

  case 240:
#line 974 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_tuple_new, 1, (yyvsp[(2) - (3)].code));
      ;}
    break;

  case 241:
#line 980 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_elem_list_new, 1, (yyvsp[(1) - (1)].code));
      ;}
    break;

  case 242:
#line 983 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_elem_list_add, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 243:
#line 989 "src/mmlparse2.y"
    { (yyval.code) = (yyvsp[(1) - (1)].code); ;}
    break;

  case 244:
#line 990 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_add, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 245:
#line 991 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_sub, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 246:
#line 995 "src/mmlparse2.y"
    { (yyval.code) = (yyvsp[(1) - (1)].code); ;}
    break;

  case 247:
#line 996 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_mul, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 248:
#line 997 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_div, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 249:
#line 998 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_mod, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 250:
#line 999 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_intdiv, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 251:
#line 1000 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_expr_prod, 2, (yyvsp[(2) - (4)].code), (yyvsp[(4) - (4)].code));
      ;}
    break;

  case 253:
#line 1007 "src/mmlparse2.y"
    { (yyval.code) = (yyvsp[(2) - (2)].code); ;}
    break;

  case 254:
#line 1008 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_neg, 1, (yyvsp[(2) - (2)].code)); ;}
    break;

  case 256:
#line 1013 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_pow, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 257:
#line 1014 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_expr_sum, 2, (yyvsp[(2) - (4)].code), (yyvsp[(4) - (4)].code));
      ;}
    break;

  case 258:
#line 1017 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_expr_min, 2, (yyvsp[(2) - (4)].code), (yyvsp[(4) - (4)].code));
      ;}
    break;

  case 259:
#line 1020 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_expr_max, 2, (yyvsp[(2) - (4)].code), (yyvsp[(4) - (4)].code));
      ;}
    break;

  case 260:
#line 1023 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_expr_sglmin, 1, (yyvsp[(3) - (4)].code));
         ;}
    break;

  case 261:
#line 1026 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_expr_sglmax, 1, (yyvsp[(3) - (4)].code));
      ;}
    break;

  case 262:
#line 1032 "src/mmlparse2.y"
    { (yyval.code) = code_new_numb((yyvsp[(1) - (1)].numb)); ;}
    break;

  case 263:
#line 1033 "src/mmlparse2.y"
    { (yyval.code) = code_new_strg((yyvsp[(1) - (1)].strg));  ;}
    break;

  case 264:
#line 1034 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_local_deref, 1, code_new_name((yyvsp[(1) - (1)].name)));
      ;}
    break;

  case 265:
#line 1037 "src/mmlparse2.y"
    { 
         (yyval.code) = code_new_inst(i_symbol_deref, 2, code_new_symbol((yyvsp[(1) - (2)].sym)), (yyvsp[(2) - (2)].code));
      ;}
    break;

  case 266:
#line 1040 "src/mmlparse2.y"
    { 
         (yyval.code) = code_new_inst(i_symbol_deref, 2, code_new_symbol((yyvsp[(1) - (2)].sym)), (yyvsp[(2) - (2)].code));
      ;}
    break;

  case 267:
#line 1043 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_define_deref, 2,
            code_new_define((yyvsp[(1) - (4)].def)),
            code_new_inst(i_tuple_new, 1, (yyvsp[(3) - (4)].code)));
      ;}
    break;

  case 268:
#line 1048 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_define_deref, 2,
            code_new_define((yyvsp[(1) - (4)].def)),
            code_new_inst(i_tuple_new, 1, (yyvsp[(3) - (4)].code)));
      ;}
    break;

  case 269:
#line 1053 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_fac, 1, (yyvsp[(1) - (2)].code)); ;}
    break;

  case 270:
#line 1054 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_card, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 271:
#line 1055 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_abs, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 272:
#line 1056 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_sgn, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 273:
#line 1057 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_round, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 274:
#line 1058 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_floor, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 275:
#line 1059 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_ceil, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 276:
#line 1060 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_log, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 277:
#line 1061 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_ln, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 278:
#line 1062 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_exp, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 279:
#line 1063 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_sqrt, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 280:
#line 1065 "src/mmlparse2.y"
    { (yyval.code) = (yyvsp[(2) - (3)].code); ;}
    break;

  case 281:
#line 1066 "src/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_length, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 282:
#line 1067 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_expr_substr, 3, (yyvsp[(3) - (8)].code), (yyvsp[(5) - (8)].code), (yyvsp[(7) - (8)].code));
      ;}
    break;

  case 283:
#line 1070 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_expr_rand, 2, (yyvsp[(3) - (6)].code), (yyvsp[(5) - (6)].code));
      ;}
    break;

  case 284:
#line 1073 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_expr_if, 3, (yyvsp[(2) - (7)].code), (yyvsp[(4) - (7)].code), (yyvsp[(6) - (7)].code));
      ;}
    break;

  case 285:
#line 1076 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_expr_ord, 3, (yyvsp[(3) - (8)].code), (yyvsp[(5) - (8)].code), (yyvsp[(7) - (8)].code));
      ;}
    break;

  case 286:
#line 1079 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_expr_min2, 1, (yyvsp[(3) - (4)].code));
      ;}
    break;

  case 287:
#line 1082 "src/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_expr_max2, 1, (yyvsp[(3) - (4)].code));
      ;}
    break;


/* Line 1267 of yacc.c.  */
#line 4521 "src/mmlparse2.c"
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



