/* A Bison parser, made by GNU Bison 1.875.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software Foundation, Inc.

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
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

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
     ASGN = 274,
     DO = 275,
     WITH = 276,
     IN = 277,
     TO = 278,
     UNTIL = 279,
     BY = 280,
     FORALL = 281,
     EMPTY_TUPLE = 282,
     EMPTY_SET = 283,
     EXISTS = 284,
     PRIORITY = 285,
     STARTVAL = 286,
     DEFAULT = 287,
     CMP_LE = 288,
     CMP_GE = 289,
     CMP_EQ = 290,
     CMP_LT = 291,
     CMP_GT = 292,
     CMP_NE = 293,
     INFTY = 294,
     AND = 295,
     OR = 296,
     XOR = 297,
     NOT = 298,
     SUM = 299,
     MIN = 300,
     MAX = 301,
     ARGMIN = 302,
     ARGMAX = 303,
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
     FLOOR = 321,
     CEIL = 322,
     LOG = 323,
     LN = 324,
     EXP = 325,
     SQRT = 326,
     RANDOM = 327,
     ORD = 328,
     READ = 329,
     AS = 330,
     SKIP = 331,
     USE = 332,
     COMMENT = 333,
     SUBSETS = 334,
     INDEXSET = 335,
     POWERSET = 336,
     VIF = 337,
     VABS = 338,
     TYPE1 = 339,
     TYPE2 = 340,
     NUMBSYM = 341,
     STRGSYM = 342,
     VARSYM = 343,
     SETSYM = 344,
     NUMBDEF = 345,
     STRGDEF = 346,
     BOOLDEF = 347,
     SETDEF = 348,
     DEFNAME = 349,
     NAME = 350,
     STRG = 351,
     NUMB = 352,
     SCALE = 353,
     SEPARATE = 354,
     UNARY = 355
   };
#endif
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
#define ASGN 274
#define DO 275
#define WITH 276
#define IN 277
#define TO 278
#define UNTIL 279
#define BY 280
#define FORALL 281
#define EMPTY_TUPLE 282
#define EMPTY_SET 283
#define EXISTS 284
#define PRIORITY 285
#define STARTVAL 286
#define DEFAULT 287
#define CMP_LE 288
#define CMP_GE 289
#define CMP_EQ 290
#define CMP_LT 291
#define CMP_GT 292
#define CMP_NE 293
#define INFTY 294
#define AND 295
#define OR 296
#define XOR 297
#define NOT 298
#define SUM 299
#define MIN 300
#define MAX 301
#define ARGMIN 302
#define ARGMAX 303
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
#define FLOOR 321
#define CEIL 322
#define LOG 323
#define LN 324
#define EXP 325
#define SQRT 326
#define RANDOM 327
#define ORD 328
#define READ 329
#define AS 330
#define SKIP 331
#define USE 332
#define COMMENT 333
#define SUBSETS 334
#define INDEXSET 335
#define POWERSET 336
#define VIF 337
#define VABS 338
#define TYPE1 339
#define TYPE2 340
#define NUMBSYM 341
#define STRGSYM 342
#define VARSYM 343
#define SETSYM 344
#define NUMBDEF 345
#define STRGDEF 346
#define BOOLDEF 347
#define SETDEF 348
#define DEFNAME 349
#define NAME 350
#define STRG 351
#define NUMB 352
#define SCALE 353
#define SEPARATE 354
#define UNARY 355




/* Copy the first part of user declarations.  */
#line 1 "src/mmlparse.y"

#pragma ident "@(#) $Id: mmlparse.y,v 1.76 2006/09/18 09:22:16 bzfkocht Exp $"
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
/*lint -e428 -e525 -e527 -e537 -e574 -e661 -e662 -e676 */
/*lint -e713 -e717 -e732 -e734 -e737 -e744 -e750 -e751 -e753 -e762 -e764 */
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

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 61 "src/mmlparse.y"
typedef union YYSTYPE {
   unsigned int bits;
   Numb*        numb;
   const char*  strg;
   const char*  name;
   Symbol*      sym;
   Define*      def;
   CodeNode*    code;
} YYSTYPE;
/* Line 191 of yacc.c.  */
#line 342 "src/mmlparse.c"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 354 "src/mmlparse.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
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
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  40
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2042

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  113
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  51
/* YYNRULES -- Number of rules. */
#define YYNRULES  260
/* YYNRULES -- Number of states. */
#define YYNSTATES  708

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   355

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     101,   102,   105,   103,   100,   104,     2,   106,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,   108,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   109,     2,   110,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   111,     2,   112,     2,     2,     2,     2,
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
      95,    96,    97,    98,    99,   107
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    11,    13,    15,    17,
      19,    21,    23,    25,    31,    40,    49,    57,    59,    63,
      70,    75,    78,    87,    96,   105,   114,   116,   120,   130,
     139,   145,   147,   149,   150,   153,   165,   175,   184,   191,
     192,   194,   196,   197,   200,   204,   205,   208,   211,   212,
     215,   216,   219,   221,   225,   227,   230,   233,   237,   241,
     246,   252,   258,   264,   269,   274,   279,   284,   291,   298,
     305,   312,   317,   325,   337,   349,   361,   373,   385,   397,
     409,   421,   433,   445,   457,   469,   481,   493,   505,   517,
     525,   533,   541,   549,   553,   557,   561,   565,   569,   573,
     577,   581,   585,   589,   593,   597,   601,   605,   609,   613,
     617,   621,   625,   629,   633,   636,   640,   641,   645,   647,
     649,   651,   653,   655,   657,   661,   665,   669,   673,   677,
     681,   683,   687,   691,   695,   698,   701,   704,   709,   714,
     722,   726,   732,   737,   742,   743,   745,   747,   751,   754,
     757,   760,   763,   768,   773,   776,   777,   780,   783,   788,
     790,   798,   804,   812,   818,   823,   827,   831,   835,   839,
     843,   847,   851,   855,   860,   865,   873,   878,   886,   890,
     894,   898,   902,   908,   914,   921,   926,   934,   939,   942,
     945,   948,   951,   953,   957,   959,   963,   967,   971,   975,
     979,   983,   987,   991,   995,   999,  1003,  1007,  1011,  1015,
    1019,  1022,  1026,  1030,  1035,  1040,  1048,  1050,  1054,  1055,
    1059,  1061,  1065,  1067,  1071,  1075,  1077,  1081,  1085,  1089,
    1093,  1095,  1097,  1099,  1102,  1105,  1110,  1115,  1118,  1122,
    1127,  1132,  1137,  1142,  1147,  1152,  1157,  1162,  1167,  1170,
    1173,  1177,  1184,  1192,  1195,  1198,  1203,  1208,  1213,  1218,
    1223
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short yyrhs[] =
{
     114,     0,    -1,   115,    -1,   123,    -1,   126,    -1,   136,
      -1,   137,    -1,   146,    -1,   118,    -1,   119,    -1,   120,
      -1,   121,    -1,   149,    -1,     3,    95,    19,   153,   108,
      -1,     3,    95,   109,   151,   110,    19,   153,   108,    -1,
       3,    95,   109,   151,   110,    19,   116,   108,    -1,     3,
      95,   109,   110,    19,   116,   108,    -1,   117,    -1,   116,
     100,   117,    -1,    79,   101,   153,   100,   161,   102,    -1,
      81,   101,   153,   102,    -1,   158,   153,    -1,    10,    94,
     101,   122,   102,    19,   161,   108,    -1,    11,    94,   101,
     122,   102,    19,   161,   108,    -1,    12,    94,   101,   122,
     102,    19,   157,   108,    -1,    13,    94,   101,   122,   102,
      19,   153,   108,    -1,    95,    -1,   122,   100,    95,    -1,
       4,    95,   109,   151,   110,    19,   132,   125,   108,    -1,
       4,    95,   109,   151,   110,    19,   161,   108,    -1,     4,
      95,    19,   124,   108,    -1,   132,    -1,   161,    -1,    -1,
      32,   161,    -1,     5,    95,   109,   151,   110,   127,   128,
     129,   130,   131,   108,    -1,     5,    95,   109,   151,   110,
      16,   130,   131,   108,    -1,     5,    95,   127,   128,   129,
     130,   131,   108,    -1,     5,    95,    16,   130,   131,   108,
      -1,    -1,    18,    -1,    17,    -1,    -1,    34,   161,    -1,
      34,   104,    39,    -1,    -1,    33,   161,    -1,    33,    39,
      -1,    -1,    30,   161,    -1,    -1,    31,   161,    -1,   133,
      -1,   132,   100,   133,    -1,   154,    -1,   134,   135,    -1,
     158,   161,    -1,    21,   160,    21,    -1,   134,   160,    21,
      -1,   135,   134,   160,    21,    -1,     6,    95,    20,   143,
     108,    -1,     7,    95,    20,   143,   108,    -1,     8,    95,
      20,   138,   108,    -1,   143,   142,   143,   140,    -1,   143,
     142,   161,   140,    -1,   161,   142,   143,   140,    -1,   161,
     142,   161,   140,    -1,   161,   142,   143,    33,   161,   140,
      -1,   161,   142,   161,    33,   161,   140,    -1,   161,   142,
     143,    34,   161,   140,    -1,   161,   142,   161,    34,   161,
     140,    -1,    26,   151,    20,   138,    -1,    49,   157,    50,
     138,    51,   138,    52,    -1,    82,   139,    50,   143,   142,
     143,    51,   143,   142,   143,    52,    -1,    82,   139,    50,
     161,   142,   143,    51,   143,   142,   143,    52,    -1,    82,
     139,    50,   143,   142,   161,    51,   143,   142,   143,    52,
      -1,    82,   139,    50,   143,   142,   143,    51,   161,   142,
     143,    52,    -1,    82,   139,    50,   143,   142,   143,    51,
     143,   142,   161,    52,    -1,    82,   139,    50,   161,   142,
     161,    51,   143,   142,   143,    52,    -1,    82,   139,    50,
     161,   142,   143,    51,   161,   142,   143,    52,    -1,    82,
     139,    50,   161,   142,   143,    51,   143,   142,   161,    52,
      -1,    82,   139,    50,   143,   142,   161,    51,   161,   142,
     143,    52,    -1,    82,   139,    50,   143,   142,   161,    51,
     143,   142,   161,    52,    -1,    82,   139,    50,   143,   142,
     143,    51,   161,   142,   161,    52,    -1,    82,   139,    50,
     161,   142,   161,    51,   161,   142,   143,    52,    -1,    82,
     139,    50,   161,   142,   161,    51,   143,   142,   161,    52,
      -1,    82,   139,    50,   161,   142,   143,    51,   161,   142,
     161,    52,    -1,    82,   139,    50,   143,   142,   161,    51,
     161,   142,   161,    52,    -1,    82,   139,    50,   161,   142,
     161,    51,   161,   142,   161,    52,    -1,    82,   139,    50,
     143,   142,   143,    52,    -1,    82,   139,    50,   161,   142,
     143,    52,    -1,    82,   139,    50,   143,   142,   161,    52,
      -1,    82,   139,    50,   161,   142,   161,    52,    -1,   143,
      38,   143,    -1,   161,    38,   143,    -1,   143,    38,   161,
      -1,   143,    35,   143,    -1,   161,    35,   143,    -1,   143,
      35,   161,    -1,   143,    33,   143,    -1,   161,    33,   143,
      -1,   143,    33,   161,    -1,   143,    34,   143,    -1,   161,
      34,   143,    -1,   143,    34,   161,    -1,   143,    36,   143,
      -1,   161,    36,   143,    -1,   143,    36,   161,    -1,   143,
      37,   143,    -1,   161,    37,   143,    -1,   143,    37,   161,
      -1,   139,    40,   139,    -1,   139,    41,   139,    -1,   139,
      42,   139,    -1,    43,   139,    -1,   101,   139,   102,    -1,
      -1,   140,   100,   141,    -1,    98,    -1,    99,    -1,    33,
      -1,    34,    -1,    35,    -1,   144,    -1,   143,   103,   144,
      -1,   143,   104,   144,    -1,   143,   103,   162,    -1,   143,
     104,   162,    -1,   161,   103,   144,    -1,   161,   104,   144,
      -1,   145,    -1,   144,   105,   163,    -1,   144,   106,   163,
      -1,   162,   105,   145,    -1,    88,   159,    -1,   103,   145,
      -1,   104,   145,    -1,    83,   101,   143,   102,    -1,    44,
     151,    20,   144,    -1,    49,   157,    50,   143,    51,   143,
      52,    -1,   101,   143,   102,    -1,     9,    95,    20,   147,
     108,    -1,   148,   130,    20,   143,    -1,    26,   151,    20,
     147,    -1,    -1,    84,    -1,    85,    -1,    20,   150,   108,
      -1,    14,   161,    -1,    14,   158,    -1,    14,   153,    -1,
      15,   157,    -1,    26,   151,    20,   150,    -1,   158,    22,
     153,   152,    -1,   153,   152,    -1,    -1,    21,   157,    -1,
      89,   159,    -1,    93,   101,   160,   102,    -1,    28,    -1,
     111,   161,    23,   161,    25,   161,   112,    -1,   111,   161,
      23,   161,   112,    -1,   111,   161,    24,   161,    25,   161,
     112,    -1,   111,   161,    24,   161,   112,    -1,    54,   151,
      20,   153,    -1,   153,    54,   153,    -1,   153,   103,   153,
      -1,   153,    56,   153,    -1,   153,    57,   153,    -1,   153,
     104,   153,    -1,   153,    55,   153,    -1,   153,   105,   153,
      -1,   153,    53,   153,    -1,    53,   151,    20,   153,    -1,
      47,   151,    20,   161,    -1,    47,   101,   161,   102,   151,
      20,   161,    -1,    48,   151,    20,   161,    -1,    48,   101,
     161,   102,   151,    20,   161,    -1,   101,   153,   102,    -1,
     111,   156,   112,    -1,   111,   160,   112,    -1,   111,   151,
     112,    -1,   111,   151,    20,   161,   112,    -1,   111,   151,
      20,   158,   112,    -1,    58,   101,   153,   100,   158,   102,
      -1,    80,   101,    89,   102,    -1,    49,   157,    50,   153,
      51,   153,    52,    -1,    74,   161,    75,   161,    -1,   154,
     155,    -1,    76,   161,    -1,    77,   161,    -1,    78,   161,
      -1,   158,    -1,   156,   100,   158,    -1,   154,    -1,   161,
      35,   161,    -1,   161,    38,   161,    -1,   161,    37,   161,
      -1,   161,    34,   161,    -1,   161,    36,   161,    -1,   161,
      33,   161,    -1,   153,    35,   153,    -1,   153,    38,   153,
      -1,   153,    37,   153,    -1,   153,    34,   153,    -1,   153,
      36,   153,    -1,   153,    33,   153,    -1,   157,    40,   157,
      -1,   157,    41,   157,    -1,   157,    42,   157,    -1,    43,
     157,    -1,   101,   157,   102,    -1,   158,    22,   153,    -1,
      29,   101,   151,   102,    -1,    92,   101,   160,   102,    -1,
      49,   157,    50,   157,    51,   157,    52,    -1,    27,    -1,
      36,   160,    37,    -1,    -1,   109,   160,   110,    -1,   161,
      -1,   160,   100,   161,    -1,   162,    -1,   161,   103,   162,
      -1,   161,   104,   162,    -1,   163,    -1,   162,   105,   163,
      -1,   162,   106,   163,    -1,   162,    59,   163,    -1,   162,
      60,   163,    -1,    97,    -1,    96,    -1,    95,    -1,    86,
     159,    -1,    87,   159,    -1,    90,   101,   160,   102,    -1,
      91,   101,   160,   102,    -1,   163,    62,    -1,   163,    61,
     163,    -1,    63,   101,   153,   102,    -1,    64,   101,   161,
     102,    -1,    65,   101,   161,   102,    -1,    66,   101,   161,
     102,    -1,    67,   101,   161,   102,    -1,    68,   101,   161,
     102,    -1,    69,   101,   161,   102,    -1,    70,   101,   161,
     102,    -1,    71,   101,   161,   102,    -1,   103,   163,    -1,
     104,   163,    -1,   101,   161,   102,    -1,    72,   101,   161,
     100,   161,   102,    -1,    49,   157,    50,   161,    51,   161,
      52,    -1,    45,   151,    -1,    46,   151,    -1,    45,   151,
      20,   162,    -1,    46,   151,    20,   162,    -1,    44,   151,
      20,   162,    -1,    45,   101,   160,   102,    -1,    46,   101,
     160,   102,    -1,    73,   101,   153,   100,   161,   100,   161,
     102,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,   130,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   148,   155,   161,   167,   177,   178,   181,
     184,   190,   199,   208,   217,   226,   235,   238,   248,   251,
     254,   263,   264,   271,   272,   280,   284,   293,   300,   313,
     314,   315,   320,   323,   324,   328,   329,   330,   334,   335,
     339,   340,   348,   349,   352,   353,   357,   361,   365,   368,
     380,   383,   393,   399,   402,   407,   412,   419,   423,   428,
     432,   438,   441,   444,   447,   452,   457,   462,   466,   473,
     480,   486,   492,   498,   503,   511,   519,   527,   534,   544,
     547,   550,   553,   560,   561,   564,   567,   568,   571,   574,
     575,   578,   581,   582,   585,   588,   589,   592,   595,   596,
     599,   602,   603,   604,   605,   606,   610,   611,   615,   616,
     620,   621,   622,   626,   627,   628,   629,   630,   633,   634,
     642,   643,   644,   648,   652,   655,   656,   659,   660,   664,
     667,   675,   681,   684,   690,   691,   692,   700,   704,   705,
     706,   707,   708,   718,   721,   728,   729,   733,   736,   741,
     742,   745,   748,   751,   754,   755,   756,   759,   760,   761,
     764,   765,   768,   769,   770,   773,   776,   779,   782,   783,
     784,   785,   786,   787,   788,   791,   794,   800,   801,   805,
     806,   807,   811,   814,   817,   821,   822,   823,   824,   825,
     826,   827,   828,   829,   830,   831,   832,   833,   834,   835,
     836,   837,   838,   839,   840,   845,   851,   852,   856,   859,
     865,   868,   874,   875,   876,   880,   881,   882,   883,   884,
     888,   889,   890,   893,   896,   899,   904,   909,   910,   912,
     913,   914,   915,   916,   917,   918,   919,   920,   922,   923,
     924,   925,   928,   931,   934,   937,   940,   943,   946,   949,
     952
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DECLSET", "DECLPAR", "DECLVAR", "DECLMIN", 
  "DECLMAX", "DECLSUB", "DECLSOS", "DEFNUMB", "DEFSTRG", "DEFBOOL", 
  "DEFSET", "PRINT", "CHECK", "BINARY", "INTEGER", "REAL", "ASGN", "DO", 
  "WITH", "IN", "TO", "UNTIL", "BY", "FORALL", "EMPTY_TUPLE", "EMPTY_SET", 
  "EXISTS", "PRIORITY", "STARTVAL", "DEFAULT", "CMP_LE", "CMP_GE", 
  "CMP_EQ", "CMP_LT", "CMP_GT", "CMP_NE", "INFTY", "AND", "OR", "XOR", 
  "NOT", "SUM", "MIN", "MAX", "ARGMIN", "ARGMAX", "IF", "THEN", "ELSE", 
  "END", "INTER", "UNION", "CROSS", "SYMDIFF", "WITHOUT", "PROJ", "MOD", 
  "DIV", "POW", "FAC", "CARD", "ABS", "SGN", "FLOOR", "CEIL", "LOG", "LN", 
  "EXP", "SQRT", "RANDOM", "ORD", "READ", "AS", "SKIP", "USE", "COMMENT", 
  "SUBSETS", "INDEXSET", "POWERSET", "VIF", "VABS", "TYPE1", "TYPE2", 
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
static const unsigned short yytoknum[] =
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
      44,    40,    41,    43,    45,    42,    47,   355,    59,    91,
      93,   123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,   113,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   115,   115,   115,   115,   116,   116,   116,
     116,   117,   118,   119,   120,   121,   122,   122,   123,   123,
     123,   124,   124,   125,   125,   126,   126,   126,   126,   127,
     127,   127,   128,   128,   128,   129,   129,   129,   130,   130,
     131,   131,   132,   132,   132,   132,   133,   134,   135,   135,
     136,   136,   137,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   140,   140,   141,   141,
     142,   142,   142,   143,   143,   143,   143,   143,   143,   143,
     144,   144,   144,   144,   145,   145,   145,   145,   145,   145,
     145,   146,   147,   147,   148,   148,   148,   149,   150,   150,
     150,   150,   150,   151,   151,   152,   152,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   154,   154,   155,
     155,   155,   156,   156,   156,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   158,   158,   159,   159,
     160,   160,   161,   161,   161,   162,   162,   162,   162,   162,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     5,     8,     8,     7,     1,     3,     6,
       4,     2,     8,     8,     8,     8,     1,     3,     9,     8,
       5,     1,     1,     0,     2,    11,     9,     8,     6,     0,
       1,     1,     0,     2,     3,     0,     2,     2,     0,     2,
       0,     2,     1,     3,     1,     2,     2,     3,     3,     4,
       5,     5,     5,     4,     4,     4,     4,     6,     6,     6,
       6,     4,     7,    11,    11,    11,    11,    11,    11,    11,
      11,    11,    11,    11,    11,    11,    11,    11,    11,     7,
       7,     7,     7,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     3,     0,     3,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       1,     3,     3,     3,     2,     2,     2,     4,     4,     7,
       3,     5,     4,     4,     0,     1,     1,     3,     2,     2,
       2,     2,     4,     4,     2,     0,     2,     2,     4,     1,
       7,     5,     7,     5,     4,     3,     3,     3,     3,     3,
       3,     3,     3,     4,     4,     7,     4,     7,     3,     3,
       3,     3,     5,     5,     6,     4,     7,     4,     2,     2,
       2,     2,     1,     3,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     3,     3,     4,     4,     7,     1,     3,     0,     3,
       1,     3,     1,     3,     3,     1,     3,     3,     3,     3,
       1,     1,     1,     2,     2,     4,     4,     2,     3,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     2,     2,
       3,     6,     7,     2,     2,     4,     4,     4,     4,     4,
       8
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned short yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     2,     8,     9,    10,    11,     3,
       4,     5,     6,     7,    12,     0,     0,    39,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,     0,     0,     0,     0,    48,    41,    40,     0,    42,
       0,     0,     0,   144,     0,     0,     0,     0,   216,   159,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   218,   218,   218,     0,     0,     0,   232,   231,
     230,     0,     0,     0,     0,   150,   149,   148,   222,   225,
       0,     0,     0,     0,     0,     0,   151,     0,     0,     0,
       0,     0,   155,     0,   147,     0,     0,     0,     0,     0,
       0,     0,     0,    31,    52,     0,    54,     0,    32,     0,
       0,    50,     0,     0,    45,     0,     0,     0,   218,     0,
       0,     0,     0,   123,   130,     0,   222,     0,     0,     0,
       0,     0,     0,     0,     0,   145,   146,     0,    48,    26,
       0,     0,     0,     0,     0,   220,     0,     0,   253,     0,
     254,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   233,   234,   157,     0,     0,     0,     0,     0,
     248,   249,     0,   194,     0,   192,     0,   220,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   237,     0,   210,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     154,     0,    13,     0,     0,     0,     0,     0,    30,     0,
       0,    55,     0,     0,     0,   188,    56,     0,    49,     0,
       0,    39,     0,    43,     0,    48,     0,     0,     0,   134,
       0,     0,   135,   136,     0,     0,    60,     0,     0,     0,
       0,     0,    61,     0,     0,     0,     0,     0,     0,     0,
      62,   120,   121,   122,     0,     0,     0,   141,     0,     0,
       0,     0,     0,     0,   217,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   178,   250,     0,   181,     0,
     179,   180,     0,     0,   172,   165,   170,   167,   168,   166,
     169,   171,   223,   224,   228,   229,   226,   227,   238,     0,
       0,     0,   211,   206,   204,   201,   205,   203,   202,   207,
     208,   209,   212,   200,   198,   195,   199,   197,   196,     0,
     152,   156,   155,     0,     0,     0,    17,     0,     0,    57,
       0,     0,    53,     0,     0,   189,   190,   191,     0,    51,
      38,    48,    42,    44,    47,    46,    50,     0,     0,     0,
     140,   124,   126,   125,   127,   131,   132,   128,   223,   129,
     224,   133,     0,     0,   114,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   116,   116,   116,   116,   144,     0,
      27,     0,     0,     0,     0,   221,   257,   258,   255,   259,
     256,     0,   174,     0,   176,     0,     0,   173,   164,     0,
     239,   240,   241,   242,   243,   244,   245,   246,   247,     0,
       0,   185,   219,   235,   236,   158,     0,     0,   193,     0,
       0,   213,     0,     0,     0,   214,   153,     0,     0,     0,
      16,    21,     0,     0,   187,    58,     0,    33,     0,    50,
      45,     0,   138,   257,     0,     0,   137,    71,     0,     0,
       0,   115,   111,   112,   113,     0,     0,    99,   101,   102,
     104,    96,    98,   105,   107,   108,   110,    93,    95,   100,
     103,    97,   106,   109,    94,    63,    64,     0,     0,    65,
       0,     0,    66,   143,   142,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   183,   182,     0,   161,
       0,   163,     0,     0,     0,    18,    15,    14,    59,     0,
       0,    29,     0,    48,    37,     0,     0,     0,     0,     0,
     116,   116,   116,   116,    22,    23,    24,    25,     0,     0,
       0,     0,   184,   251,     0,     0,     0,     0,     0,    20,
      34,    28,    36,    50,     0,     0,     0,     0,     0,     0,
     118,   119,   117,    67,    69,    68,    70,   175,   177,   186,
     252,     0,   160,   162,   215,     0,     0,   139,    72,     0,
      89,     0,    91,     0,    90,     0,    92,   260,    19,    35,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    73,    77,    76,    83,    75,    82,    81,    87,
      74,    80,    79,    86,    78,    85,    84,    88
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,    13,    14,   395,   396,    15,    16,    17,    18,   160,
      19,   122,   590,    20,    49,   134,   275,   131,   270,   123,
     124,   125,   261,    21,    22,   151,   297,   555,   632,   304,
     298,   143,   144,    23,   157,   158,    24,    39,   111,   250,
     112,   126,   265,   204,   106,   113,   192,   164,   108,    98,
      99
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -425
static const short yypact[] =
{
    1451,   -72,   -50,   -43,   -29,   -16,    -5,    -2,    42,    60,
      76,    85,   220,   156,  -425,  -425,  -425,  -425,  -425,  -425,
    -425,  -425,  -425,  -425,  -425,   -17,    -9,     1,   143,   182,
     194,   205,   157,   163,   169,   177,  1238,  1064,   710,   172,
    -425,   962,   655,  1379,   710,   214,  -425,  -425,   710,   249,
    1789,  1789,  1441,   147,   203,   203,   203,   203,  -425,  -425,
    1850,   710,   724,   873,   896,   933,  1064,   710,   710,   219,
     223,   227,   272,   275,   300,   323,   341,   378,   380,   384,
     390,   407,   195,   195,   195,   419,   434,   462,  -425,  -425,
    -425,  1308,  1850,  1850,  1167,  1937,  -425,   -76,   339,   308,
     509,  1064,  1064,   513,  1064,  1585,   681,   521,   476,  1064,
     962,   510,   196,   530,  -425,   484,   599,   514,  1850,  1064,
    1850,  1850,   519,   531,  -425,   619,   142,  1850,   -76,   537,
    1850,   617,   559,  1911,   644,   710,  1064,   585,   195,  1789,
    1789,  1789,   137,   282,  -425,   315,   726,   241,   710,  1064,
    1728,   579,    54,   108,   710,  -425,  -425,   582,   214,  -425,
      -1,    21,    32,   155,    17,   -76,   672,  1308,   692,  1308,
     694,  1308,   698,  1308,   709,   760,   714,   716,   962,   962,
    1850,  1850,  1850,  1850,  1850,  1850,  1850,  1850,  1850,   962,
     612,  1850,  -425,  -425,  -425,  1850,  1850,  1850,   982,   769,
     685,   685,    -7,   142,   -47,   530,   -31,    24,   962,   962,
     962,   962,   962,   962,   962,   962,  1850,  1850,  1850,  1850,
    1850,  1850,  1850,  -425,   710,  -425,   799,  1850,  1524,    20,
     239,   962,   962,   962,   962,   962,   962,  1064,  1064,  1064,
     962,  1850,  1850,  1850,  1850,  1850,  1850,   855,   220,  1064,
    -425,   962,  -425,   229,   730,    13,   897,   -40,  -425,    47,
    1850,   619,  1850,  1850,  1850,  -425,   -76,   734,   -76,  1850,
     635,   858,  1605,   -76,  1666,   214,   742,   923,  1789,  -425,
     800,   804,  -425,  -425,  1789,  1789,  -425,  1850,  1850,  1789,
    1789,  1789,  -425,   747,   952,  1728,  1728,   958,   562,   568,
    -425,  -425,  -425,  -425,  1789,  1789,   749,  -425,   767,   696,
     778,   786,   795,   797,  -425,  1850,  1850,   246,  1850,   388,
    1850,   831,  1850,   838,  1850,  1308,   962,   962,  1260,  1329,
     915,   921,   943,   950,   954,   957,   967,   999,   209,  1336,
     721,    29,   402,   426,   491,  -425,  -425,  1503,  -425,    47,
    -425,  -425,  1850,  1850,   -33,   280,  1001,   280,   280,   280,
     280,  -425,   339,   339,   308,   308,   308,   308,   308,   722,
    1064,   573,  -425,  1937,  1937,  1937,  1937,  1937,  1937,  -425,
     789,   789,  1937,   -76,   -76,   -76,   -76,   -76,   -76,   962,
    -425,   681,   196,   717,   725,   -41,  -425,   962,   278,  -425,
    1850,  1850,  -425,    19,  1850,   -76,   -76,   -76,  1379,   -76,
    -425,   214,   249,  -425,  -425,   -76,   617,  1789,  1789,  1017,
    -425,   282,   726,   282,   726,   308,   308,   282,   726,   282,
     726,  -425,  1441,  1441,  -425,   141,   318,   357,  1728,  1728,
    1728,  1789,  1789,  1789,  1789,  1789,  1789,  1789,  1789,  1789,
    1789,  1789,  1789,  1789,   352,   315,    62,    92,   147,  1789,
    -425,  1850,  1850,  1064,   962,   -76,   339,  -425,   339,  -425,
     339,   710,   -76,   710,   -76,   976,   178,   728,   728,    47,
    -425,  -425,  -425,  -425,  -425,  -425,  -425,  -425,  -425,  1850,
    1850,  -425,  -425,  -425,  -425,  -425,   733,   607,  -425,     8,
      12,  -425,  1579,   507,   414,  -425,  -425,   962,   962,    47,
    -425,  1937,    69,   671,   -76,  -425,    30,     4,   473,   617,
     644,   743,   282,   726,   234,   236,  -425,  -425,   779,   188,
     429,  -425,  -425,   794,   794,    54,   108,   352,   315,   352,
     315,   352,   315,   352,   315,   352,   315,   352,   315,   352,
     352,   352,   352,   352,   352,   736,   736,  1850,  1850,   736,
    1850,  1850,   736,  -425,   352,   522,   581,   -10,   739,   818,
     833,   962,  1850,   753,  1021,   508,  -425,  -425,  1850,  -425,
    1850,  -425,  1064,  1913,  1932,  -425,  -425,  -425,  -425,  1850,
     748,  -425,   751,   214,  -425,  1789,  1441,  1789,  1789,   485,
     -76,   -76,   -76,   -76,  -425,  -425,  -425,  -425,  1850,  1850,
    1042,   133,  -425,  -425,  1850,   638,   766,   665,  1850,  -425,
     -76,  -425,  -425,   617,   334,   809,   215,   271,   326,   329,
    -425,  -425,  -425,   736,   736,   736,   736,   -76,   -76,  -425,
    -425,  1036,  -425,  -425,  -425,  1060,   755,  -425,  -425,  1789,
    -425,  1789,  -425,  1789,  -425,  1789,  -425,  -425,  -425,  -425,
      54,   108,    54,   108,    54,   108,    54,   108,  1789,  1789,
    1789,  1789,  1789,  1789,  1789,  1789,   379,   383,   389,   394,
     442,   447,   451,   453,   471,   482,   538,   542,   564,   627,
     629,   636,  -425,  -425,  -425,  -425,  -425,  -425,  -425,  -425,
    -425,  -425,  -425,  -425,  -425,  -425,  -425,  -425
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
    -425,  -425,  -425,   467,   368,  -425,  -425,  -425,  -425,  1114,
    -425,  -425,  -425,  -425,   628,   486,   405,  -157,  -410,   528,
     670,  -121,  -425,  -425,  -425,  -424,  -246,  -413,  -425,   -96,
      25,  -264,  -129,  -425,   488,  -425,  -425,   700,   136,   560,
     679,   857,  -425,  -425,   -63,   718,   164,   -89,   -36,   211,
      75
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned short yytable[] =
{
      97,   308,    41,   175,   260,   206,   521,   128,   527,   528,
      43,   282,   283,   347,   145,   145,   153,    45,    46,    47,
     421,   423,   210,    25,   165,   427,   429,   216,   217,   255,
     237,   238,   239,   578,   399,   401,   589,   580,   225,   226,
     515,   229,   556,   559,   562,    26,   247,   352,   353,   434,
     435,   588,    27,   349,   314,   199,   256,   305,   207,   509,
     237,   238,   239,   216,   217,   350,    28,   510,   230,   315,
     213,   214,   215,   277,    58,   142,   147,   152,   317,    29,
     319,   351,   165,    60,   257,   199,   294,   301,   302,   303,
      30,   266,    42,    31,   268,   557,   558,   273,   606,   309,
      44,   310,   341,   281,   259,   348,   342,   343,   344,   592,
      48,   216,   217,   315,   299,   216,   217,   315,   416,   315,
     579,   309,   372,   311,   581,   560,   561,   216,   217,   315,
     315,   165,   309,   165,   312,   321,    32,   323,   371,   492,
     404,   301,   302,   303,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   522,    33,   165,    40,   284,   285,   165,
     165,   165,   431,    50,   280,   284,   285,   200,   201,   509,
      34,   403,   625,   154,   379,   380,   381,   586,   117,    35,
     129,   438,   439,   440,   132,   640,   391,   633,   634,   635,
     636,   165,   532,   533,   534,   289,   290,   166,   168,   170,
     172,   174,    51,   176,   177,   383,   384,   385,   386,   387,
     388,   289,   290,   646,    52,   200,   201,   249,   262,   263,
     264,   301,   302,   303,   165,    53,   405,   406,   407,   572,
     202,   155,   156,   409,    36,    37,   216,   217,   415,   595,
     284,   285,   145,   531,   130,   286,    38,   193,   194,   208,
     209,   210,   211,   212,   519,   309,    58,   313,    54,   299,
     437,   146,   146,   146,    55,    60,   649,   650,   455,   457,
      56,   276,   241,   242,   243,   244,   245,   246,    57,   465,
     114,   216,   217,   133,   293,   595,   472,   572,   474,   476,
     306,   284,   285,   364,   365,   366,   367,   368,   159,   213,
     214,   215,   279,   419,   191,    58,    59,   503,   393,   489,
     394,   497,   216,   217,    60,   516,   499,   500,   284,   285,
     178,   436,   651,   652,   179,    64,    65,   109,   180,   454,
     456,    67,    68,   208,   504,   210,    69,   284,   285,   289,
     290,   346,   216,   217,   284,   285,   315,   201,   467,   292,
     146,   442,   443,   444,   445,   446,   447,   393,    81,   394,
     369,   146,   425,   426,   476,   514,   366,    84,   165,   222,
     223,    87,   518,   181,   289,   290,   182,   653,   654,   110,
     655,   656,   525,   213,   214,   215,   647,   287,   288,    94,
     448,   449,   450,   451,   452,   453,   153,   530,   218,   219,
     567,   183,   299,   299,   299,   536,   538,   540,   542,   544,
     546,   548,   145,   145,   145,   145,   145,   145,   289,   290,
     420,   284,   285,   145,   184,   565,   566,   362,   363,   284,
     285,   692,   289,   290,   305,   693,   623,   284,   285,   597,
     598,   694,   185,   524,   220,   221,   695,   241,   242,   243,
     244,   245,   246,   574,   575,   284,   285,   152,   529,   346,
     289,   290,   301,   302,   303,   572,   535,   537,   539,   541,
     543,   545,   547,   549,   550,   551,   552,   553,   554,   186,
     572,   187,   284,   285,   564,   188,   289,   290,   315,   146,
     469,   189,   284,   285,   696,   422,   424,   289,   290,   697,
     428,   430,   315,   698,   493,   699,   146,   146,   190,   241,
     242,   243,   244,   245,   246,   146,   146,   216,   217,   617,
     195,   600,   601,   700,   602,   603,   315,   466,   494,   468,
     248,   470,   289,   290,   701,   196,   611,   208,   209,   210,
     211,   212,   615,   240,   616,   284,   285,   237,   238,   239,
     289,   290,   251,   620,   284,   285,   289,   290,   582,   145,
     153,   627,   629,   197,   668,   669,   670,   671,   672,   673,
     674,   675,   637,   638,   284,   285,   216,   217,   641,   216,
     217,   591,   645,   630,   631,   289,   290,   213,   214,   215,
     702,   315,   252,   495,   703,   442,   443,   444,   445,   446,
     447,   448,   449,   450,   451,   452,   453,   569,   614,   570,
     224,   216,   217,   661,   227,   663,   704,   665,   253,   667,
     624,   152,   626,   628,   254,   216,   217,   258,   523,   146,
     604,   259,   677,   679,   681,   683,   685,   687,   689,   691,
     118,   284,   285,   146,   146,   289,   290,   267,   269,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   284,   285,   284,   285,   271,
     146,   289,   290,   315,   660,   505,   662,   274,   664,   705,
     666,   706,    58,    59,   216,   217,   278,   300,   707,   605,
     307,    60,   316,   676,   678,   680,   682,   684,   686,   688,
     690,   340,    64,    65,   109,   237,   238,   239,    67,    68,
     216,   217,   318,    69,   320,    95,   105,   644,   322,   577,
     115,   237,   238,   239,   208,   209,   210,   211,   212,   324,
     289,   290,   284,   285,   326,    81,   327,    58,    59,   289,
     290,   216,   217,   410,    84,   105,    60,   223,    87,   398,
     642,    58,    59,   408,    96,   107,   110,    64,    65,   109,
      60,   127,   417,    67,    68,   116,    94,   432,    69,   458,
     198,    64,    65,   109,   213,   214,   215,    67,    68,   587,
     105,   105,    69,   228,   107,   218,   219,   459,   105,   198,
      81,   460,   208,   209,   210,   211,   212,   461,   105,    84,
     237,   238,   239,    87,    81,   462,   146,   146,   146,   146,
     325,   110,   205,    84,   463,   105,   464,    87,   507,   107,
     107,    94,   107,   491,   501,   167,   508,   107,   105,   237,
     596,   291,   221,   215,   438,    94,   599,   107,   608,   237,
     238,   239,   213,   214,   215,   576,   198,   607,   198,   370,
     198,   594,   198,   609,   107,   612,   621,   328,   329,   622,
     146,   648,   146,   659,   146,   512,   146,   107,   339,   216,
     217,   346,   216,   217,   411,    46,    47,   585,   643,   146,
     146,   146,   146,   146,   146,   146,   146,   354,   355,   356,
     357,   358,   359,   360,   361,   237,   238,   239,   520,   412,
      58,    59,   420,   284,   285,   389,   346,   289,   290,    60,
     373,   374,   375,   376,   377,   378,   105,   105,   105,   382,
      64,    65,   109,    58,    59,   593,    67,    68,   105,   402,
     392,    69,    60,   471,   216,   217,   517,   237,   238,   239,
     473,   216,   217,    64,    65,   109,   563,   400,   390,    67,
      68,   203,   506,    81,    69,   107,   107,   107,     0,     0,
      58,    59,    84,   237,   238,   239,    87,   107,     0,    60,
       0,   397,     0,   418,   169,     0,    81,   127,     0,     0,
      64,    65,   109,     0,    94,    84,    67,    68,     0,    87,
      59,    69,   237,   238,   239,     0,     0,   171,   438,   439,
     440,     0,   433,     0,   475,   477,   478,    94,   441,    64,
      65,   109,     0,    81,     0,    67,    68,   481,   216,   217,
      69,     0,    84,   482,   216,   217,    87,   571,     0,   208,
     209,   210,   211,   212,   173,   208,   209,   210,   211,   212,
       0,     0,    81,     0,    94,   483,   216,   217,     0,   502,
       0,    84,   484,   216,   217,    87,   485,   216,   217,   486,
     216,   217,     0,   110,     0,   496,     0,   498,   475,   487,
     216,   217,     0,    94,     0,     0,   511,   513,     0,   213,
     214,   215,     0,     0,   345,   213,   214,   215,   107,     0,
       0,    58,    59,   100,   639,   208,   209,   210,   211,   212,
      60,   488,   216,   217,   213,   214,   215,   101,    61,    62,
      63,    64,    65,   102,     0,     0,   397,    67,    68,   526,
     284,   285,    69,   613,   216,   217,   127,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,   657,   216,
     217,     0,   105,   568,    81,   213,   214,   215,     0,     0,
      82,    83,     0,    84,    85,    86,   103,    87,     0,    88,
      89,    90,   658,   216,   217,   104,     0,    92,    93,   161,
     162,   163,     0,     0,     0,    94,     0,     0,     0,     0,
       0,   107,     0,     0,     0,     0,   583,   584,     0,     0,
       0,     0,     0,     0,    58,    59,     0,   573,     0,     0,
       0,     0,     0,    60,     0,     0,     0,     0,     0,     0,
       0,    61,    62,    63,    64,    65,    66,     0,     0,     0,
      67,    68,     0,     0,     0,    69,     0,   397,     0,     0,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,   120,     0,     0,     0,     0,     0,    81,     0,     0,
     610,     0,     0,    82,    83,     0,    84,    85,    86,     0,
      87,   105,    88,    89,    90,    58,    59,     0,    91,     0,
      92,    93,     0,     0,    60,     0,     0,     0,    94,     0,
       0,     0,    61,    62,    63,    64,    65,    66,     0,     0,
       0,    67,    68,     0,     0,     0,    69,     0,     0,     0,
     107,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,     0,   208,   209,   210,   211,   212,    81,     0,
       0,     0,     0,     0,    82,    83,     0,    84,    85,    86,
       0,    87,     0,    88,    89,    90,    59,     0,     0,    91,
       0,    92,    93,     0,     0,     0,     0,     0,     0,    94,
       0,     0,    61,    62,    63,    64,    65,    66,     0,     0,
     479,    67,    68,   213,   214,   215,    69,     0,     0,     0,
       0,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,   208,   209,   210,   211,   212,     0,    81,   208,
     209,   210,   211,   212,    82,    83,     0,    84,    85,    86,
     118,    87,     0,    88,    89,    90,    58,     0,     0,    91,
       0,    92,    93,     0,     0,    60,     0,     0,     0,    94,
       0,     0,     0,    61,    62,    63,     0,     0,   119,     0,
       0,   480,   213,   214,   215,     0,   490,     0,     0,   213,
     214,   215,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,   120,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    82,    83,   148,     0,    85,
      86,    12,     0,     0,    88,    89,    90,     0,     0,     0,
     121,     0,    92,    93,     0,   135,    62,    63,     0,     0,
     149,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,     0,     0,     0,     0,     0,
       0,     0,     0,   150,   137,     0,     0,    82,    83,   138,
      58,    85,    86,     0,     0,     0,    88,    89,    90,    60,
       0,     0,   139,     0,   140,   141,     0,    61,    62,    63,
       0,     0,   119,     0,     0,     0,     0,   231,   232,   233,
     234,   235,   236,     0,     0,     0,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,   208,   209,   210,
     211,   212,     0,     0,     0,     0,     0,     0,     0,    82,
      83,     0,     0,    85,    86,     0,     0,     0,    88,    89,
      90,     0,     0,     0,   121,     0,    92,    93,     0,     0,
       0,     0,   231,   232,   233,   234,   235,   236,   231,   232,
     233,   234,   235,   236,     0,     0,   345,   213,   214,   215,
     571,     0,   208,   209,   210,   211,   212,     0,   208,   209,
     210,   211,   212,     0,   413,     0,     0,     0,     0,    61,
      62,    63,     0,     0,   119,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,     0,
       0,     0,   213,   214,   215,     0,     0,     0,   213,   214,
     215,    82,    83,     0,     0,    85,    86,     0,     0,     0,
      88,    89,    90,     0,     0,   414,   121,     0,    92,    93,
      61,    62,    63,     0,     0,   119,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    82,    83,     0,     0,    85,    86,     0,     0,
       0,    88,    89,    90,     0,     0,     0,   121,     0,    92,
      93,   295,   135,    62,    63,     0,     0,   136,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   137,     0,     0,    82,    83,   138,     0,    85,    86,
       0,     0,     0,    88,    89,    90,     0,     0,     0,   296,
       0,   140,   141,   135,    62,    63,     0,     0,   136,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   137,     0,     0,    82,    83,   138,     0,    85,
      86,     0,     0,     0,    88,    89,    90,     0,     0,     0,
     139,     0,   140,   141,    61,    62,    63,     0,     0,   119,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    82,    83,     0,     0,
      85,    86,     0,     0,     0,    88,    89,    90,     0,     0,
       0,   121,     0,    92,    93,    61,    62,    63,     0,     0,
     119,     0,     0,     0,     0,     0,   208,   209,   210,   211,
     212,     0,     0,     0,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,   208,   209,   210,   211,   212,
     208,   209,   210,   211,   212,     0,     0,    82,    83,     0,
       0,    85,    86,     0,     0,     0,    88,    89,    90,     0,
       0,     0,   121,   618,    92,   272,   213,   214,   215,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   619,   213,   214,   215,     0,     0,
     213,   214,   215
};

static const short yycheck[] =
{
      36,   158,    19,    66,   125,    94,   416,    43,   432,   433,
      19,   140,   141,    20,    50,    51,    52,    16,    17,    18,
     284,   285,    55,    95,    60,   289,   290,   103,   104,   118,
      40,    41,    42,    25,    21,    75,    32,    25,   101,   102,
      21,   104,   455,   456,   457,    95,   109,    23,    24,   295,
     296,    21,    95,   100,    37,    91,   119,   153,    94,   100,
      40,    41,    42,   103,   104,   112,    95,   108,   104,   100,
     103,   104,   105,   136,    27,    50,    51,    52,   167,    95,
     169,   112,   118,    36,   120,   121,   149,    33,    34,    35,
      95,   127,   109,    95,   130,    33,    34,   133,   108,   100,
     109,   102,   191,   139,   100,   112,   195,   196,   197,   519,
     109,   103,   104,   100,   150,   103,   104,   100,   275,   100,
     112,   100,   102,   102,   112,    33,    34,   103,   104,   100,
     100,   167,   100,   169,   102,   171,    94,   173,   227,   110,
     261,    33,    34,    35,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   417,    94,   191,     0,   103,   104,   195,
     196,   197,   291,    20,   139,   103,   104,    92,    93,   100,
      94,   260,   596,    26,   237,   238,   239,   108,    42,    94,
      44,    40,    41,    42,    48,    52,   249,   600,   601,   602,
     603,   227,   438,   439,   440,   103,   104,    61,    62,    63,
      64,    65,    20,    67,    68,   241,   242,   243,   244,   245,
     246,   103,   104,   623,    20,   140,   141,    21,    76,    77,
      78,    33,    34,    35,   260,    20,   262,   263,   264,    51,
      94,    84,    85,   269,    14,    15,   103,   104,   274,    51,
     103,   104,   278,   102,    30,   108,    26,    83,    84,    53,
      54,    55,    56,    57,   411,   100,    27,   102,   101,   295,
     296,    50,    51,    52,   101,    36,    51,    52,   304,   305,
     101,   135,    33,    34,    35,    36,    37,    38,   101,   315,
     108,   103,   104,    34,   148,    51,   322,    51,   324,   325,
     154,   103,   104,   218,   219,   220,   221,   222,    95,   103,
     104,   105,   138,   278,   109,    27,    28,   370,    79,   100,
      81,   347,   103,   104,    36,   404,   352,   353,   103,   104,
     101,   296,    51,    52,   101,    47,    48,    49,   101,   304,
     305,    53,    54,    53,   370,    55,    58,   103,   104,   103,
     104,   102,   103,   104,   103,   104,   100,   272,   102,   108,
     139,    33,    34,    35,    36,    37,    38,    79,    80,    81,
     224,   150,   287,   288,   400,   401,   291,    89,   404,    61,
      62,    93,   408,   101,   103,   104,   101,    51,    52,   101,
      51,    52,   418,   103,   104,   105,    52,   105,   106,   111,
      33,    34,    35,    36,    37,    38,   432,   433,    59,    60,
     463,   101,   438,   439,   440,   441,   442,   443,   444,   445,
     446,   447,   448,   449,   450,   451,   452,   453,   103,   104,
     102,   103,   104,   459,   101,   461,   462,   216,   217,   103,
     104,    52,   103,   104,   530,    52,   593,   103,   104,   535,
     536,    52,   101,   418,   105,   106,    52,    33,    34,    35,
      36,    37,    38,   489,   490,   103,   104,   432,   433,   102,
     103,   104,    33,    34,    35,    51,   441,   442,   443,   444,
     445,   446,   447,   448,   449,   450,   451,   452,   453,   101,
      51,   101,   103,   104,   459,   101,   103,   104,   100,   278,
     102,   101,   103,   104,    52,   284,   285,   103,   104,    52,
     289,   290,   100,    52,   102,    52,   295,   296,   101,    33,
      34,    35,    36,    37,    38,   304,   305,   103,   104,   582,
     101,   557,   558,    52,   560,   561,   100,   316,   102,   318,
      20,   320,   103,   104,    52,   101,   572,    53,    54,    55,
      56,    57,   578,    22,   580,   103,   104,    40,    41,    42,
     103,   104,    22,   589,   103,   104,   103,   104,    51,   595,
     596,   597,   598,   101,   660,   661,   662,   663,   664,   665,
     666,   667,   608,   609,   103,   104,   103,   104,   614,   103,
     104,   108,   618,    98,    99,   103,   104,   103,   104,   105,
      52,   100,   108,   102,    52,    33,    34,    35,    36,    37,
      38,    33,    34,    35,    36,    37,    38,   471,   100,   473,
     101,   103,   104,   649,   101,   651,    52,   653,    19,   655,
     595,   596,   597,   598,   110,   103,   104,   108,   417,   418,
     108,   100,   668,   669,   670,   671,   672,   673,   674,   675,
      21,   103,   104,   432,   433,   103,   104,   110,    31,   438,
     439,   440,   441,   442,   443,   444,   445,   446,   447,   448,
     449,   450,   451,   452,   453,   103,   104,   103,   104,   110,
     459,   103,   104,   100,   649,   102,   651,    33,   653,    52,
     655,    52,    27,    28,   103,   104,   101,   108,    52,   108,
     108,    36,    20,   668,   669,   670,   671,   672,   673,   674,
     675,    89,    47,    48,    49,    40,    41,    42,    53,    54,
     103,   104,    20,    58,    20,    36,    37,    52,    20,   112,
      41,    40,    41,    42,    53,    54,    55,    56,    57,    20,
     103,   104,   103,   104,    20,    80,    20,    27,    28,   103,
     104,   103,   104,   108,    89,    66,    36,    62,    93,    19,
     112,    27,    28,    19,    36,    37,   101,    47,    48,    49,
      36,    43,    20,    53,    54,   110,   111,    20,    58,    20,
      91,    47,    48,    49,   103,   104,   105,    53,    54,   108,
     101,   102,    58,   104,    66,    59,    60,    20,   109,   110,
      80,    95,    53,    54,    55,    56,    57,    19,   119,    89,
      40,    41,    42,    93,    80,    19,   595,   596,   597,   598,
      50,   101,    94,    89,    19,   136,    19,    93,   101,   101,
     102,   111,   104,   102,   102,   101,   101,   109,   149,    40,
      51,   105,   106,   105,    40,   111,   100,   119,    20,    40,
      41,    42,   103,   104,   105,   112,   167,   108,   169,    50,
     171,   108,   173,    20,   136,   102,   108,   178,   179,   108,
     649,    52,   651,   108,   653,   398,   655,   149,   189,   103,
     104,   102,   103,   104,    16,    17,    18,   509,   112,   668,
     669,   670,   671,   672,   673,   674,   675,   208,   209,   210,
     211,   212,   213,   214,   215,    40,    41,    42,   412,   271,
      27,    28,   102,   103,   104,    50,   102,   103,   104,    36,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
      47,    48,    49,    27,    28,   520,    53,    54,   249,   259,
     251,    58,    36,   102,   103,   104,   408,    40,    41,    42,
     102,   103,   104,    47,    48,    49,   458,    50,   248,    53,
      54,    94,   392,    80,    58,   237,   238,   239,    -1,    -1,
      27,    28,    89,    40,    41,    42,    93,   249,    -1,    36,
      -1,   253,    -1,    50,   101,    -1,    80,   259,    -1,    -1,
      47,    48,    49,    -1,   111,    89,    53,    54,    -1,    93,
      28,    58,    40,    41,    42,    -1,    -1,   101,    40,    41,
      42,    -1,    50,    -1,   325,   326,   327,   111,    50,    47,
      48,    49,    -1,    80,    -1,    53,    54,   102,   103,   104,
      58,    -1,    89,   102,   103,   104,    93,    51,    -1,    53,
      54,    55,    56,    57,   101,    53,    54,    55,    56,    57,
      -1,    -1,    80,    -1,   111,   102,   103,   104,    -1,   370,
      -1,    89,   102,   103,   104,    93,   102,   103,   104,   102,
     103,   104,    -1,   101,    -1,   347,    -1,   349,   389,   102,
     103,   104,    -1,   111,    -1,    -1,   397,   398,    -1,   103,
     104,   105,    -1,    -1,   102,   103,   104,   105,   370,    -1,
      -1,    27,    28,    29,    52,    53,    54,    55,    56,    57,
      36,   102,   103,   104,   103,   104,   105,    43,    44,    45,
      46,    47,    48,    49,    -1,    -1,   398,    53,    54,   102,
     103,   104,    58,   102,   103,   104,   408,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,   102,   103,
     104,    -1,   463,   464,    80,   103,   104,   105,    -1,    -1,
      86,    87,    -1,    89,    90,    91,    92,    93,    -1,    95,
      96,    97,   102,   103,   104,   101,    -1,   103,   104,    55,
      56,    57,    -1,    -1,    -1,   111,    -1,    -1,    -1,    -1,
      -1,   463,    -1,    -1,    -1,    -1,   507,   508,    -1,    -1,
      -1,    -1,    -1,    -1,    27,    28,    -1,   479,    -1,    -1,
      -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    44,    45,    46,    47,    48,    49,    -1,    -1,    -1,
      53,    54,    -1,    -1,    -1,    58,    -1,   509,    -1,    -1,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    -1,    -1,    -1,    -1,    -1,    80,    -1,    -1,
     571,    -1,    -1,    86,    87,    -1,    89,    90,    91,    -1,
      93,   582,    95,    96,    97,    27,    28,    -1,   101,    -1,
     103,   104,    -1,    -1,    36,    -1,    -1,    -1,   111,    -1,
      -1,    -1,    44,    45,    46,    47,    48,    49,    -1,    -1,
      -1,    53,    54,    -1,    -1,    -1,    58,    -1,    -1,    -1,
     582,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    -1,    53,    54,    55,    56,    57,    80,    -1,
      -1,    -1,    -1,    -1,    86,    87,    -1,    89,    90,    91,
      -1,    93,    -1,    95,    96,    97,    28,    -1,    -1,   101,
      -1,   103,   104,    -1,    -1,    -1,    -1,    -1,    -1,   111,
      -1,    -1,    44,    45,    46,    47,    48,    49,    -1,    -1,
     100,    53,    54,   103,   104,   105,    58,    -1,    -1,    -1,
      -1,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    53,    54,    55,    56,    57,    -1,    80,    53,
      54,    55,    56,    57,    86,    87,    -1,    89,    90,    91,
      21,    93,    -1,    95,    96,    97,    27,    -1,    -1,   101,
      -1,   103,   104,    -1,    -1,    36,    -1,    -1,    -1,   111,
      -1,    -1,    -1,    44,    45,    46,    -1,    -1,    49,    -1,
      -1,   102,   103,   104,   105,    -1,   100,    -1,    -1,   103,
     104,   105,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    86,    87,    26,    -1,    90,
      91,    20,    -1,    -1,    95,    96,    97,    -1,    -1,    -1,
     101,    -1,   103,   104,    -1,    44,    45,    46,    -1,    -1,
      49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    82,    83,    -1,    -1,    86,    87,    88,
      27,    90,    91,    -1,    -1,    -1,    95,    96,    97,    36,
      -1,    -1,   101,    -1,   103,   104,    -1,    44,    45,    46,
      -1,    -1,    49,    -1,    -1,    -1,    -1,    33,    34,    35,
      36,    37,    38,    -1,    -1,    -1,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    53,    54,    55,
      56,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,
      87,    -1,    -1,    90,    91,    -1,    -1,    -1,    95,    96,
      97,    -1,    -1,    -1,   101,    -1,   103,   104,    -1,    -1,
      -1,    -1,    33,    34,    35,    36,    37,    38,    33,    34,
      35,    36,    37,    38,    -1,    -1,   102,   103,   104,   105,
      51,    -1,    53,    54,    55,    56,    57,    -1,    53,    54,
      55,    56,    57,    -1,    39,    -1,    -1,    -1,    -1,    44,
      45,    46,    -1,    -1,    49,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    -1,
      -1,    -1,   103,   104,   105,    -1,    -1,    -1,   103,   104,
     105,    86,    87,    -1,    -1,    90,    91,    -1,    -1,    -1,
      95,    96,    97,    -1,    -1,    39,   101,    -1,   103,   104,
      44,    45,    46,    -1,    -1,    49,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    86,    87,    -1,    -1,    90,    91,    -1,    -1,
      -1,    95,    96,    97,    -1,    -1,    -1,   101,    -1,   103,
     104,    43,    44,    45,    46,    -1,    -1,    49,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    83,    -1,    -1,    86,    87,    88,    -1,    90,    91,
      -1,    -1,    -1,    95,    96,    97,    -1,    -1,    -1,   101,
      -1,   103,   104,    44,    45,    46,    -1,    -1,    49,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    83,    -1,    -1,    86,    87,    88,    -1,    90,
      91,    -1,    -1,    -1,    95,    96,    97,    -1,    -1,    -1,
     101,    -1,   103,   104,    44,    45,    46,    -1,    -1,    49,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    86,    87,    -1,    -1,
      90,    91,    -1,    -1,    -1,    95,    96,    97,    -1,    -1,
      -1,   101,    -1,   103,   104,    44,    45,    46,    -1,    -1,
      49,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,    56,
      57,    -1,    -1,    -1,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    53,    54,    55,    56,    57,
      53,    54,    55,    56,    57,    -1,    -1,    86,    87,    -1,
      -1,    90,    91,    -1,    -1,    -1,    95,    96,    97,    -1,
      -1,    -1,   101,   100,   103,   104,   103,   104,   105,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,   103,   104,   105,    -1,    -1,
     103,   104,   105
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    20,   114,   115,   118,   119,   120,   121,   123,
     126,   136,   137,   146,   149,    95,    95,    95,    95,    95,
      95,    95,    94,    94,    94,    94,    14,    15,    26,   150,
       0,    19,   109,    19,   109,    16,    17,    18,   109,   127,
      20,    20,    20,    20,   101,   101,   101,   101,    27,    28,
      36,    44,    45,    46,    47,    48,    49,    53,    54,    58,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    80,    86,    87,    89,    90,    91,    93,    95,    96,
      97,   101,   103,   104,   111,   153,   158,   161,   162,   163,
      29,    43,    49,    92,   101,   153,   157,   158,   161,    49,
     101,   151,   153,   158,   108,   153,   110,   151,    21,    49,
      74,   101,   124,   132,   133,   134,   154,   158,   161,   151,
      30,   130,   151,    34,   128,    44,    49,    83,    88,   101,
     103,   104,   143,   144,   145,   161,   162,   143,    26,    49,
      82,   138,   143,   161,    26,    84,    85,   147,   148,    95,
     122,   122,   122,   122,   160,   161,   151,   101,   151,   101,
     151,   101,   151,   101,   151,   157,   151,   151,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   109,   159,   159,   159,   101,   101,   101,   153,   161,
     163,   163,   151,   154,   156,   158,   160,   161,    53,    54,
      55,    56,    57,   103,   104,   105,   103,   104,    59,    60,
     105,   106,    61,    62,   101,   157,   157,   101,   153,   157,
     161,    33,    34,    35,    36,    37,    38,    40,    41,    42,
      22,    33,    34,    35,    36,    37,    38,   157,    20,    21,
     152,    22,   108,    19,   110,   160,   157,   161,   108,   100,
     134,   135,    76,    77,    78,   155,   161,   110,   161,    31,
     131,   110,   104,   161,    33,   129,   151,   157,   101,   159,
     143,   161,   145,   145,   103,   104,   108,   105,   106,   103,
     104,   105,   108,   151,   157,    43,   101,   139,   143,   161,
     108,    33,    34,    35,   142,   142,   151,   108,   130,   100,
     102,   102,   102,   102,    37,   100,    20,   160,    20,   160,
      20,   161,    20,   161,    20,    50,    20,    20,   153,   153,
     161,   161,   161,   161,   161,   161,   161,   161,   161,   153,
      89,   160,   160,   160,   160,   102,   102,    20,   112,   100,
     112,   112,    23,    24,   153,   153,   153,   153,   153,   153,
     153,   153,   162,   162,   163,   163,   163,   163,   163,   151,
      50,   160,   102,   153,   153,   153,   153,   153,   153,   157,
     157,   157,   153,   161,   161,   161,   161,   161,   161,    50,
     150,   157,   153,    79,    81,   116,   117,   158,    19,    21,
      50,    75,   133,   160,   134,   161,   161,   161,    19,   161,
     108,    16,   127,    39,    39,   161,   130,    20,    50,   143,
     102,   144,   162,   144,   162,   163,   163,   144,   162,   144,
     162,   145,    20,    50,   139,   139,   143,   161,    40,    41,
      42,    50,    33,    34,    35,    36,    37,    38,    33,    34,
      35,    36,    37,    38,   143,   161,   143,   161,    20,    20,
      95,    19,    19,    19,    19,   161,   162,   102,   162,   102,
     162,   102,   161,   102,   161,   153,   161,   153,   153,   100,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   100,
     100,   102,   110,   102,   102,   102,   158,   161,   158,   161,
     161,   102,   153,   157,   161,   102,   152,   101,   101,   100,
     108,   153,   116,   153,   161,    21,   160,   132,   161,   130,
     128,   131,   144,   162,   143,   161,   102,   138,   138,   143,
     161,   102,   139,   139,   139,   143,   161,   143,   161,   143,
     161,   143,   161,   143,   161,   143,   161,   143,   161,   143,
     143,   143,   143,   143,   143,   140,   140,    33,    34,   140,
      33,    34,   140,   147,   143,   161,   161,   157,   153,   151,
     151,    51,    51,   158,   161,   161,   112,   112,    25,   112,
      25,   112,    51,   153,   153,   117,   108,   108,    21,    32,
     125,   108,   131,   129,   108,    51,    51,   142,   142,   100,
     161,   161,   161,   161,   108,   108,   108,   108,    20,    20,
     153,   161,   102,   102,   100,   161,   161,   157,   100,   102,
     161,   108,   108,   130,   143,   138,   143,   161,   143,   161,
      98,    99,   141,   140,   140,   140,   140,   161,   161,    52,
      52,   161,   112,   112,    52,   161,   131,    52,    52,    51,
      52,    51,    52,    51,    52,    51,    52,   102,   102,   108,
     143,   161,   143,   161,   143,   161,   143,   161,   142,   142,
     142,   142,   142,   142,   142,   142,   143,   161,   143,   161,
     143,   161,   143,   161,   143,   161,   143,   161,   143,   161,
     143,   161,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrlab1

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
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)         \
  Current.first_line   = Rhs[1].first_line;      \
  Current.first_column = Rhs[1].first_column;    \
  Current.last_line    = Rhs[N].last_line;       \
  Current.last_column  = Rhs[N].last_column;
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
} while (0)

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (cinluded).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylineno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylineno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
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
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */






/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  /* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

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
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
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

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
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

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
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
#line 130 "src/mmlparse.y"
    { code_set_root(yyvsp[0].code); ;}
    break;

  case 3:
#line 131 "src/mmlparse.y"
    { code_set_root(yyvsp[0].code); ;}
    break;

  case 4:
#line 132 "src/mmlparse.y"
    { code_set_root(yyvsp[0].code); ;}
    break;

  case 5:
#line 133 "src/mmlparse.y"
    { code_set_root(yyvsp[0].code); ;}
    break;

  case 6:
#line 134 "src/mmlparse.y"
    { code_set_root(yyvsp[0].code); ;}
    break;

  case 7:
#line 135 "src/mmlparse.y"
    { code_set_root(yyvsp[0].code); ;}
    break;

  case 8:
#line 136 "src/mmlparse.y"
    { code_set_root(yyvsp[0].code); ;}
    break;

  case 9:
#line 137 "src/mmlparse.y"
    { code_set_root(yyvsp[0].code); ;}
    break;

  case 10:
#line 138 "src/mmlparse.y"
    { code_set_root(yyvsp[0].code); ;}
    break;

  case 11:
#line 139 "src/mmlparse.y"
    { code_set_root(yyvsp[0].code); ;}
    break;

  case 12:
#line 140 "src/mmlparse.y"
    { code_set_root(yyvsp[0].code); ;}
    break;

  case 13:
#line 148 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_newsym_set1, 3,
            code_new_name(yyvsp[-3].name),                                       /* Name */
            code_new_inst(i_idxset_pseudo_new, 1,               /* index set */
               code_new_inst(i_bool_true, 0)),              
            yyvsp[-1].code);                                              /* initial set */
      ;}
    break;

  case 14:
#line 155 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_newsym_set1, 3,
            code_new_name(yyvsp[-6].name),                                       /* Name */
            yyvsp[-4].code,                                                 /* index set */
            yyvsp[-1].code);                                                      /* set */
      ;}
    break;

  case 15:
#line 161 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_newsym_set2, 3,
            code_new_name(yyvsp[-6].name),                                       /* Name */
            yyvsp[-4].code,                                                 /* index set */
            yyvsp[-1].code);                                   /* initial set_entry_list */
      ;}
    break;

  case 16:
#line 167 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_newsym_set2, 3,
            code_new_name(yyvsp[-5].name),                                       /* Name */
            code_new_inst(i_idxset_pseudo_new, 1,               /* index set */
               code_new_inst(i_bool_true, 0)),              
            yyvsp[-1].code);                                   /* initial set_entry_list */
      ;}
    break;

  case 17:
#line 177 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_entry_list_new, 1, yyvsp[0].code); ;}
    break;

  case 18:
#line 178 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_entry_list_add, 2, yyvsp[-2].code, yyvsp[0].code);
      ;}
    break;

  case 19:
#line 181 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_entry_list_subsets, 2, yyvsp[-3].code, yyvsp[-1].code);
      ;}
    break;

  case 20:
#line 184 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_entry_list_powerset, 1, yyvsp[-1].code);
      ;}
    break;

  case 21:
#line 190 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_entry, 2, yyvsp[-1].code, yyvsp[0].code); ;}
    break;

  case 22:
#line 199 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_newdef, 3,
            code_new_define(yyvsp[-6].def),
            code_new_inst(i_tuple_new, 1, yyvsp[-4].code),
            yyvsp[-1].code);
      ;}
    break;

  case 23:
#line 208 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_newdef, 3,
            code_new_define(yyvsp[-6].def),
            code_new_inst(i_tuple_new, 1, yyvsp[-4].code),
            yyvsp[-1].code);
      ;}
    break;

  case 24:
#line 217 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_newdef, 3,
            code_new_define(yyvsp[-6].def),
            code_new_inst(i_tuple_new, 1, yyvsp[-4].code),
            yyvsp[-1].code);
      ;}
    break;

  case 25:
#line 226 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_newdef, 3,
            code_new_define(yyvsp[-6].def),
            code_new_inst(i_tuple_new, 1, yyvsp[-4].code),
            yyvsp[-1].code);
      ;}
    break;

  case 26:
#line 235 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_elem_list_new, 1, code_new_name(yyvsp[0].name));
      ;}
    break;

  case 27:
#line 238 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_elem_list_add, 2, yyvsp[-2].code, code_new_name(yyvsp[0].name));
      ;}
    break;

  case 28:
#line 248 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_newsym_para1, 4, code_new_name(yyvsp[-7].name), yyvsp[-5].code, yyvsp[-2].code, yyvsp[-1].code);
      ;}
    break;

  case 29:
#line 251 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_newsym_para2, 4, code_new_name(yyvsp[-6].name), yyvsp[-4].code, yyvsp[-1].code, code_new_inst(i_nop, 0));
      ;}
    break;

  case 30:
#line 254 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_newsym_para1, 4,
            code_new_name(yyvsp[-3].name),
            code_new_inst(i_idxset_pseudo_new, 1, code_new_inst(i_bool_true, 0)),
            yyvsp[-1].code,
            code_new_inst(i_nop, 0));
      ;}
    break;

  case 31:
#line 263 "src/mmlparse.y"
    { yyval.code = yyvsp[0].code; ;}
    break;

  case 32:
#line 264 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_entry_list_new, 1,
            code_new_inst(i_entry, 2, code_new_inst(i_tuple_empty, 0), yyvsp[0].code));
      ;}
    break;

  case 33:
#line 271 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_nop, 0); ;}
    break;

  case 34:
#line 272 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_entry, 2, code_new_inst(i_tuple_empty, 0), yyvsp[0].code); ;}
    break;

  case 35:
#line 280 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_newsym_var, 7,
            code_new_name(yyvsp[-9].name), yyvsp[-7].code, yyvsp[-5].code, yyvsp[-4].code, yyvsp[-3].code, yyvsp[-2].code, yyvsp[-1].code);
      ;}
    break;

  case 36:
#line 284 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_newsym_var, 7,
            code_new_name(yyvsp[-7].name),
            yyvsp[-5].code,
            code_new_varclass(VAR_BIN),
            code_new_inst(i_bound_new, 1, code_new_numb(numb_new_integer(0))),
            code_new_inst(i_bound_new, 1, code_new_numb(numb_new_integer(1))),
            yyvsp[-2].code, yyvsp[-1].code);
      ;}
    break;

  case 37:
#line 293 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_newsym_var, 7,
            code_new_name(yyvsp[-6].name),
            code_new_inst(i_idxset_pseudo_new, 1,
               code_new_inst(i_bool_true, 0)),              
            yyvsp[-5].code, yyvsp[-4].code, yyvsp[-3].code, yyvsp[-2].code, yyvsp[-1].code);
      ;}
    break;

  case 38:
#line 300 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_newsym_var, 7,
            code_new_name(yyvsp[-4].name),
            code_new_inst(i_idxset_pseudo_new, 1,
               code_new_inst(i_bool_true, 0)),              
            code_new_varclass(VAR_BIN),
            code_new_inst(i_bound_new, 1, code_new_numb(numb_new_integer(0))),
            code_new_inst(i_bound_new, 1, code_new_numb(numb_new_integer(1))),
            yyvsp[-2].code, yyvsp[-1].code);
      ;}
    break;

  case 39:
#line 313 "src/mmlparse.y"
    { yyval.code = code_new_varclass(VAR_CON); ;}
    break;

  case 40:
#line 314 "src/mmlparse.y"
    { yyval.code = code_new_varclass(VAR_CON); ;}
    break;

  case 41:
#line 315 "src/mmlparse.y"
    { yyval.code = code_new_varclass(VAR_INT); ;}
    break;

  case 42:
#line 320 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_bound_new, 1, code_new_numb(numb_new_integer(0)));
      ;}
    break;

  case 43:
#line 323 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bound_new, 1, yyvsp[0].code); ;}
    break;

  case 44:
#line 324 "src/mmlparse.y"
    { yyval.code = code_new_bound(BOUND_MINUS_INFTY); ;}
    break;

  case 45:
#line 328 "src/mmlparse.y"
    { yyval.code = code_new_bound(BOUND_INFTY); ;}
    break;

  case 46:
#line 329 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bound_new, 1, yyvsp[0].code); ;}
    break;

  case 47:
#line 330 "src/mmlparse.y"
    { yyval.code = code_new_bound(BOUND_INFTY); ;}
    break;

  case 48:
#line 334 "src/mmlparse.y"
    { yyval.code = code_new_numb(numb_new_integer(0)); ;}
    break;

  case 49:
#line 335 "src/mmlparse.y"
    { yyval.code = yyvsp[0].code; ;}
    break;

  case 50:
#line 339 "src/mmlparse.y"
    { yyval.code = code_new_numb(numb_new_integer(0)); ;}
    break;

  case 51:
#line 340 "src/mmlparse.y"
    { yyval.code = yyvsp[0].code; ;}
    break;

  case 52:
#line 348 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_entry_list_new, 1, yyvsp[0].code); ;}
    break;

  case 53:
#line 349 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_entry_list_add, 2, yyvsp[-2].code, yyvsp[0].code);
      ;}
    break;

  case 54:
#line 352 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_read, 1, yyvsp[0].code); ;}
    break;

  case 55:
#line 353 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_list_matrix, 2, yyvsp[-1].code, yyvsp[0].code); ;}
    break;

  case 56:
#line 357 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_entry, 2, yyvsp[-1].code, yyvsp[0].code); ;}
    break;

  case 57:
#line 361 "src/mmlparse.y"
    { yyval.code = yyvsp[-1].code; ;}
    break;

  case 58:
#line 365 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_matrix_list_new, 2, yyvsp[-2].code, yyvsp[-1].code);
      ;}
    break;

  case 59:
#line 368 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_matrix_list_add, 3, yyvsp[-3].code, yyvsp[-2].code, yyvsp[-1].code);
      ;}
    break;

  case 60:
#line 380 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_object_min, 2, code_new_name(yyvsp[-3].name), yyvsp[-1].code);
      ;}
    break;

  case 61:
#line 383 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_object_max, 2, code_new_name(yyvsp[-3].name), yyvsp[-1].code);
      ;}
    break;

  case 62:
#line 393 "src/mmlparse.y"
    {
        yyval.code = code_new_inst(i_subto, 2, code_new_name(yyvsp[-3].name), yyvsp[-1].code);
     ;}
    break;

  case 63:
#line 399 "src/mmlparse.y"
    {
        yyval.code = code_new_inst(i_constraint, 4, yyvsp[-3].code, yyvsp[-2].code, yyvsp[-1].code, code_new_bits(yyvsp[0].bits));
     ;}
    break;

  case 64:
#line 402 "src/mmlparse.y"
    {
        yyval.code = code_new_inst(i_constraint, 4, yyvsp[-3].code, yyvsp[-2].code,
           code_new_inst(i_term_expr, 1, yyvsp[-1].code),
           code_new_bits(yyvsp[0].bits));
     ;}
    break;

  case 65:
#line 407 "src/mmlparse.y"
    {
        yyval.code = code_new_inst(i_constraint, 4,
           code_new_inst(i_term_expr, 1, yyvsp[-3].code),
           yyvsp[-2].code, yyvsp[-1].code, code_new_bits(yyvsp[0].bits));
     ;}
    break;

  case 66:
#line 412 "src/mmlparse.y"
    { 
        yyval.code = code_new_inst(i_constraint, 4,
           code_new_inst(i_term_expr, 1, yyvsp[-3].code),
           yyvsp[-2].code,
           code_new_inst(i_term_expr, 1, yyvsp[-1].code),
           code_new_bits(yyvsp[0].bits));
     ;}
    break;

  case 67:
#line 419 "src/mmlparse.y"
    {
        yyval.code = code_new_inst(i_rangeconst, 6, yyvsp[-5].code, yyvsp[-3].code, yyvsp[-1].code, yyvsp[-4].code,
           code_new_contype(CON_RHS), code_new_bits(yyvsp[0].bits)); 
     ;}
    break;

  case 68:
#line 423 "src/mmlparse.y"
    {
        yyval.code = code_new_inst(i_rangeconst, 6, yyvsp[-5].code,
           code_new_inst(i_term_expr, 1, yyvsp[-3].code), yyvsp[-1].code, yyvsp[-4].code,
           code_new_contype(CON_RHS), code_new_bits(yyvsp[0].bits)); 
     ;}
    break;

  case 69:
#line 428 "src/mmlparse.y"
    {
        yyval.code = code_new_inst(i_rangeconst, 6, yyvsp[-1].code, yyvsp[-3].code, yyvsp[-5].code, yyvsp[-4].code,
           code_new_contype(CON_LHS), code_new_bits(yyvsp[0].bits)); 
     ;}
    break;

  case 70:
#line 432 "src/mmlparse.y"
    {
        yyval.code = code_new_inst(i_rangeconst, 6, yyvsp[-1].code,
           code_new_inst(i_term_expr, 1, yyvsp[-3].code),
           yyvsp[-5].code, yyvsp[-4].code,
           code_new_contype(CON_LHS), code_new_bits(yyvsp[0].bits)); 
     ;}
    break;

  case 71:
#line 438 "src/mmlparse.y"
    {
        yyval.code = code_new_inst(i_forall, 2, yyvsp[-2].code, yyvsp[0].code);
     ;}
    break;

  case 72:
#line 441 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_expr_if, 3, yyvsp[-5].code, yyvsp[-3].code, yyvsp[-1].code);
      ;}
    break;

  case 73:
#line 444 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_vif_else, 7, yyvsp[-9].code, yyvsp[-7].code, yyvsp[-6].code, yyvsp[-5].code, yyvsp[-3].code, yyvsp[-2].code, yyvsp[-1].code);
      ;}
    break;

  case 74:
#line 447 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_vif_else, 7, yyvsp[-9].code,
            code_new_inst(i_term_expr, 1, yyvsp[-7].code),
            yyvsp[-6].code, yyvsp[-5].code, yyvsp[-3].code, yyvsp[-2].code, yyvsp[-1].code);
      ;}
    break;

  case 75:
#line 452 "src/mmlparse.y"
    { 
         yyval.code = code_new_inst(i_vif_else, 7, yyvsp[-9].code, yyvsp[-7].code, yyvsp[-6].code,
            code_new_inst(i_term_expr, 1, yyvsp[-5].code),
            yyvsp[-3].code, yyvsp[-2].code, yyvsp[-1].code);
      ;}
    break;

  case 76:
#line 457 "src/mmlparse.y"
    { 
         yyval.code = code_new_inst(i_vif_else, 7, yyvsp[-9].code, yyvsp[-7].code, yyvsp[-6].code, yyvsp[-5].code,
            code_new_inst(i_term_expr, 1, yyvsp[-3].code),
            yyvsp[-2].code, yyvsp[-1].code);
      ;}
    break;

  case 77:
#line 462 "src/mmlparse.y"
    { 
         yyval.code = code_new_inst(i_vif_else, 7, yyvsp[-9].code, yyvsp[-7].code, yyvsp[-6].code, yyvsp[-5].code, yyvsp[-3].code, yyvsp[-2].code,
            code_new_inst(i_term_expr, 1, yyvsp[-1].code));
      ;}
    break;

  case 78:
#line 466 "src/mmlparse.y"
    { /* ??? This is an error */
         yyval.code = code_new_inst(i_vif_else, 7, yyvsp[-9].code,
            code_new_inst(i_term_expr, 1, yyvsp[-7].code),
            yyvsp[-6].code,
            code_new_inst(i_term_expr, 1, yyvsp[-5].code),
            yyvsp[-3].code, yyvsp[-2].code, yyvsp[-1].code);
      ;}
    break;

  case 79:
#line 473 "src/mmlparse.y"
    { 
         yyval.code = code_new_inst(i_vif_else, 7, yyvsp[-9].code,
            code_new_inst(i_term_expr, 1, yyvsp[-7].code),
            yyvsp[-6].code, yyvsp[-5].code,
            code_new_inst(i_term_expr, 1, yyvsp[-3].code),
            yyvsp[-2].code, yyvsp[-1].code);
      ;}
    break;

  case 80:
#line 480 "src/mmlparse.y"
    { 
         yyval.code = code_new_inst(i_vif_else, 7, yyvsp[-9].code,
            code_new_inst(i_term_expr, 1, yyvsp[-7].code),
            yyvsp[-6].code, yyvsp[-5].code, yyvsp[-3].code, yyvsp[-2].code,
            code_new_inst(i_term_expr, 1, yyvsp[-1].code));
      ;}
    break;

  case 81:
#line 486 "src/mmlparse.y"
    { 
         yyval.code = code_new_inst(i_vif_else, 7, yyvsp[-9].code, yyvsp[-7].code, yyvsp[-6].code,
            code_new_inst(i_term_expr, 1, yyvsp[-5].code),
            code_new_inst(i_term_expr, 1, yyvsp[-3].code),
            yyvsp[-2].code, yyvsp[-1].code);
      ;}
    break;

  case 82:
#line 492 "src/mmlparse.y"
    { 
         yyval.code = code_new_inst(i_vif_else, 7, yyvsp[-9].code, yyvsp[-7].code, yyvsp[-6].code,
            code_new_inst(i_term_expr, 1, yyvsp[-5].code),
            yyvsp[-3].code, yyvsp[-2].code,
            code_new_inst(i_term_expr, 1, yyvsp[-1].code));
      ;}
    break;

  case 83:
#line 498 "src/mmlparse.y"
    { /* ??? This is an error */
         yyval.code = code_new_inst(i_vif_else, 7, yyvsp[-9].code, yyvsp[-7].code, yyvsp[-6].code, yyvsp[-5].code,
            code_new_inst(i_term_expr, 1, yyvsp[-3].code), yyvsp[-2].code,
            code_new_inst(i_term_expr, 1, yyvsp[-1].code));
      ;}
    break;

  case 84:
#line 503 "src/mmlparse.y"
    { /* ??? This is an error */
         yyval.code = code_new_inst(i_vif_else, 7, yyvsp[-9].code,
            code_new_inst(i_term_expr, 1, yyvsp[-7].code),
            yyvsp[-6].code,
            code_new_inst(i_term_expr, 1, yyvsp[-5].code),
            code_new_inst(i_term_expr, 1, yyvsp[-3].code),
            yyvsp[-2].code, yyvsp[-1].code);
      ;}
    break;

  case 85:
#line 511 "src/mmlparse.y"
    { /* ??? This is an error */
         yyval.code = code_new_inst(i_vif_else, 7, yyvsp[-9].code,
            code_new_inst(i_term_expr, 1, yyvsp[-7].code),
            yyvsp[-6].code,
            code_new_inst(i_term_expr, 1, yyvsp[-5].code),
            yyvsp[-3].code, yyvsp[-2].code,
            code_new_inst(i_term_expr, 1, yyvsp[-1].code));
      ;}
    break;

  case 86:
#line 519 "src/mmlparse.y"
    { /* ??? This is an error */
         yyval.code = code_new_inst(i_vif_else, 7, yyvsp[-9].code,
            code_new_inst(i_term_expr, 1, yyvsp[-7].code),
            yyvsp[-6].code, yyvsp[-5].code,
            code_new_inst(i_term_expr, 1, yyvsp[-3].code),
            yyvsp[-2].code,
            code_new_inst(i_term_expr, 1, yyvsp[-1].code));
      ;}
    break;

  case 87:
#line 527 "src/mmlparse.y"
    { /* ??? This is an error */
         yyval.code = code_new_inst(i_vif_else, 7, yyvsp[-9].code, yyvsp[-7].code, yyvsp[-6].code,
            code_new_inst(i_term_expr, 1, yyvsp[-5].code),
            code_new_inst(i_term_expr, 1, yyvsp[-3].code),
            yyvsp[-2].code,
            code_new_inst(i_term_expr, 1, yyvsp[-1].code));
      ;}
    break;

  case 88:
#line 534 "src/mmlparse.y"
    { /* ??? This is an error */
         yyval.code = code_new_inst(i_vif_else, 7, yyvsp[-9].code,
            code_new_inst(i_term_expr, 1, yyvsp[-7].code),
            yyvsp[-6].code,
            code_new_inst(i_term_expr, 1, yyvsp[-5].code),
            code_new_inst(i_term_expr, 1, yyvsp[-3].code),
            yyvsp[-2].code,
            code_new_inst(i_term_expr, 1, yyvsp[-1].code));
      ;}
    break;

  case 89:
#line 544 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_vif, 4, yyvsp[-5].code, yyvsp[-3].code, yyvsp[-2].code, yyvsp[-1].code);
      ;}
    break;

  case 90:
#line 547 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_vif, 4, yyvsp[-5].code, code_new_inst(i_term_expr, 1, yyvsp[-3].code), yyvsp[-2].code, yyvsp[-1].code);
      ;}
    break;

  case 91:
#line 550 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_vif, 4, yyvsp[-5].code, yyvsp[-3].code, yyvsp[-2].code, code_new_inst(i_term_expr, 1, yyvsp[-1].code));
      ;}
    break;

  case 92:
#line 553 "src/mmlparse.y"
    { /* ??? This is an error */
         yyval.code = code_new_inst(i_vif, 4, yyvsp[-5].code,
            code_new_inst(i_term_expr, 1, yyvsp[-3].code), yyvsp[-2].code, code_new_inst(i_term_expr, 1, yyvsp[-1].code));
      ;}
    break;

  case 93:
#line 560 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_vbool_ne, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 94:
#line 561 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_vbool_ne, 2, code_new_inst(i_term_expr, 1, yyvsp[-2].code), yyvsp[0].code);
      ;}
    break;

  case 95:
#line 564 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_vbool_ne, 2, yyvsp[-2].code, code_new_inst(i_term_expr, 1, yyvsp[0].code));
      ;}
    break;

  case 96:
#line 567 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_vbool_eq, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 97:
#line 568 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_vbool_eq, 2, code_new_inst(i_term_expr, 1, yyvsp[-2].code), yyvsp[0].code);
      ;}
    break;

  case 98:
#line 571 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_vbool_eq, 2, yyvsp[-2].code, code_new_inst(i_term_expr, 1, yyvsp[0].code));
      ;}
    break;

  case 99:
#line 574 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_vbool_le, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 100:
#line 575 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_vbool_le, 2, code_new_inst(i_term_expr, 1, yyvsp[-2].code), yyvsp[0].code);
      ;}
    break;

  case 101:
#line 578 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_vbool_le, 2, yyvsp[-2].code, code_new_inst(i_term_expr, 1, yyvsp[0].code));
      ;}
    break;

  case 102:
#line 581 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_vbool_ge, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 103:
#line 582 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_vbool_ge, 2, code_new_inst(i_term_expr, 1, yyvsp[-2].code), yyvsp[0].code);
      ;}
    break;

  case 104:
#line 585 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_vbool_ge, 2, yyvsp[-2].code, code_new_inst(i_term_expr, 1, yyvsp[0].code));
      ;}
    break;

  case 105:
#line 588 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_vbool_lt, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 106:
#line 589 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_vbool_lt, 2, code_new_inst(i_term_expr, 1, yyvsp[-2].code), yyvsp[0].code);
      ;}
    break;

  case 107:
#line 592 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_vbool_lt, 2, yyvsp[-2].code, code_new_inst(i_term_expr, 1, yyvsp[0].code));
      ;}
    break;

  case 108:
#line 595 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_vbool_gt, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 109:
#line 596 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_vbool_gt, 2, code_new_inst(i_term_expr, 1, yyvsp[-2].code), yyvsp[0].code);
      ;}
    break;

  case 110:
#line 599 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_vbool_gt, 2, yyvsp[-2].code, code_new_inst(i_term_expr, 1, yyvsp[0].code));
      ;}
    break;

  case 111:
#line 602 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_vbool_and, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 112:
#line 603 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_vbool_or,  2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 113:
#line 604 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_vbool_xor, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 114:
#line 605 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_vbool_not, 1, yyvsp[0].code);; ;}
    break;

  case 115:
#line 606 "src/mmlparse.y"
    { yyval.code = yyvsp[-1].code; ;}
    break;

  case 116:
#line 610 "src/mmlparse.y"
    { yyval.bits = 0; ;}
    break;

  case 117:
#line 611 "src/mmlparse.y"
    { yyval.bits = yyvsp[-2].bits | yyvsp[0].bits; ;}
    break;

  case 118:
#line 615 "src/mmlparse.y"
    { yyval.bits = LP_FLAG_CON_SCALE; ;}
    break;

  case 119:
#line 616 "src/mmlparse.y"
    { yyval.bits = LP_FLAG_CON_SEPAR; ;}
    break;

  case 120:
#line 620 "src/mmlparse.y"
    { yyval.code = code_new_contype(CON_RHS); ;}
    break;

  case 121:
#line 621 "src/mmlparse.y"
    { yyval.code = code_new_contype(CON_LHS); ;}
    break;

  case 122:
#line 622 "src/mmlparse.y"
    { yyval.code = code_new_contype(CON_EQUAL); ;}
    break;

  case 123:
#line 626 "src/mmlparse.y"
    { yyval.code = yyvsp[0].code; ;}
    break;

  case 124:
#line 627 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_term_add, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 125:
#line 628 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_term_sub, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 126:
#line 629 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_term_const, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 127:
#line 630 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_term_sub, 2, yyvsp[-2].code, code_new_inst(i_term_expr, 1, yyvsp[0].code));
      ;}
    break;

  case 128:
#line 633 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_term_const, 2, yyvsp[0].code, yyvsp[-2].code); ;}
    break;

  case 129:
#line 634 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_term_sub, 2,
            code_new_inst(i_term_expr, 1, yyvsp[-2].code),
            yyvsp[0].code);
      ;}
    break;

  case 130:
#line 642 "src/mmlparse.y"
    { yyval.code = yyvsp[0].code; ;}
    break;

  case 131:
#line 643 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_term_coeff, 2, yyvsp[-2].code, yyvsp[0].code); /*???*/ ;}
    break;

  case 132:
#line 644 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_term_coeff, 2, yyvsp[-2].code,
            code_new_inst(i_expr_div, 2, code_new_numb(numb_new_integer(1)), yyvsp[0].code));
      ;}
    break;

  case 133:
#line 648 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_term_coeff, 2, yyvsp[0].code, yyvsp[-2].code); ;}
    break;

  case 134:
#line 652 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_symbol_deref, 2, code_new_symbol(yyvsp[-1].sym), yyvsp[0].code);
      ;}
    break;

  case 135:
#line 655 "src/mmlparse.y"
    { yyval.code = yyvsp[0].code; ;}
    break;

  case 136:
#line 656 "src/mmlparse.y"
    { 
         yyval.code = code_new_inst(i_term_coeff, 2, yyvsp[0].code, code_new_numb(numb_new_integer(-1)));
      ;}
    break;

  case 137:
#line 659 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_vabs, 1, yyvsp[-1].code); ;}
    break;

  case 138:
#line 660 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_term_sum, 2, yyvsp[-2].code, yyvsp[0].code);
      ;}
    break;

  case 139:
#line 664 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_expr_if, 3, yyvsp[-5].code, yyvsp[-3].code, yyvsp[-1].code);
      ;}
    break;

  case 140:
#line 667 "src/mmlparse.y"
    { yyval.code = yyvsp[-1].code; ;}
    break;

  case 141:
#line 675 "src/mmlparse.y"
    {
        yyval.code = code_new_inst(i_sos, 2, code_new_name(yyvsp[-3].name), yyvsp[-1].code);
     ;}
    break;

  case 142:
#line 681 "src/mmlparse.y"
    {
        yyval.code = code_new_inst(i_soset, 3, yyvsp[0].code, yyvsp[-3].code, yyvsp[-2].code);
     ;}
    break;

  case 143:
#line 684 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_forall, 2, yyvsp[-2].code, yyvsp[0].code);
      ;}
    break;

  case 144:
#line 690 "src/mmlparse.y"
    { yyval.code = code_new_numb(numb_new_integer(1)); ;}
    break;

  case 145:
#line 691 "src/mmlparse.y"
    { yyval.code = code_new_numb(numb_new_integer(1)); ;}
    break;

  case 146:
#line 692 "src/mmlparse.y"
    { yyval.code = code_new_numb(numb_new_integer(2)); ;}
    break;

  case 147:
#line 700 "src/mmlparse.y"
    { yyval.code = yyvsp[-1].code; ;}
    break;

  case 148:
#line 704 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_print, 1, yyvsp[0].code); ;}
    break;

  case 149:
#line 705 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_print, 1, yyvsp[0].code); ;}
    break;

  case 150:
#line 706 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_print, 1, yyvsp[0].code); ;}
    break;

  case 151:
#line 707 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_check, 1, yyvsp[0].code); ;}
    break;

  case 152:
#line 708 "src/mmlparse.y"
    {
        yyval.code = code_new_inst(i_forall, 2, yyvsp[-2].code, yyvsp[0].code);
     ;}
    break;

  case 153:
#line 718 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_idxset_new, 3, yyvsp[-3].code, yyvsp[-1].code, yyvsp[0].code);
      ;}
    break;

  case 154:
#line 721 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_idxset_new, 3,
            code_new_inst(i_tuple_empty, 0), yyvsp[-1].code, yyvsp[0].code);
      ;}
    break;

  case 155:
#line 728 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bool_true, 0); ;}
    break;

  case 156:
#line 729 "src/mmlparse.y"
    { yyval.code = yyvsp[0].code; ;}
    break;

  case 157:
#line 733 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_symbol_deref, 2, code_new_symbol(yyvsp[-1].sym), yyvsp[0].code);
      ;}
    break;

  case 158:
#line 736 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_define_deref, 2,
            code_new_define(yyvsp[-3].def),
            code_new_inst(i_tuple_new, 1, yyvsp[-1].code));
      ;}
    break;

  case 159:
#line 741 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_set_empty, 1, code_new_size(0)); ;}
    break;

  case 160:
#line 742 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_set_range2, 3, yyvsp[-5].code, yyvsp[-3].code, yyvsp[-1].code);
      ;}
    break;

  case 161:
#line 745 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_set_range2, 3, yyvsp[-3].code, yyvsp[-1].code, code_new_numb(numb_new_integer(1)));
      ;}
    break;

  case 162:
#line 748 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_set_range, 3, yyvsp[-5].code, yyvsp[-3].code, yyvsp[-1].code);
      ;}
    break;

  case 163:
#line 751 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_set_range, 3, yyvsp[-3].code, yyvsp[-1].code, code_new_numb(numb_new_integer(1)));
      ;}
    break;

  case 164:
#line 754 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_set_union2, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 165:
#line 755 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_set_union, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 166:
#line 756 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_set_union, 2, yyvsp[-2].code, yyvsp[0].code);
      ;}
    break;

  case 167:
#line 759 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_set_sdiff, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 168:
#line 760 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_set_minus, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 169:
#line 761 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_set_minus, 2, yyvsp[-2].code, yyvsp[0].code);
      ;}
    break;

  case 170:
#line 764 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_set_cross, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 171:
#line 765 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_set_cross, 2, yyvsp[-2].code, yyvsp[0].code);
      ;}
    break;

  case 172:
#line 768 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_set_inter, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 173:
#line 769 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_set_inter2, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 174:
#line 770 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_set_argmin, 3, code_new_numb(numb_new_integer(1)), yyvsp[-2].code, yyvsp[0].code);
      ;}
    break;

  case 175:
#line 773 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_set_argmin, 3, yyvsp[-4].code, yyvsp[-2].code, yyvsp[0].code);
      ;}
    break;

  case 176:
#line 776 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_set_argmax, 3, code_new_numb(numb_new_integer(1)), yyvsp[-2].code, yyvsp[0].code);
      ;}
    break;

  case 177:
#line 779 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_set_argmax, 3, yyvsp[-4].code, yyvsp[-2].code, yyvsp[0].code);
      ;}
    break;

  case 178:
#line 782 "src/mmlparse.y"
    { yyval.code = yyvsp[-1].code; ;}
    break;

  case 179:
#line 783 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_set_new_tuple, 1, yyvsp[-1].code); ;}
    break;

  case 180:
#line 784 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_set_new_elem, 1, yyvsp[-1].code); ;}
    break;

  case 181:
#line 785 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_set_idxset, 1, yyvsp[-1].code); ;}
    break;

  case 182:
#line 786 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_set_expr, 2, yyvsp[-3].code, yyvsp[-1].code); ;}
    break;

  case 183:
#line 787 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_set_expr, 2, yyvsp[-3].code, yyvsp[-1].code); ;}
    break;

  case 184:
#line 788 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_set_proj, 2, yyvsp[-3].code, yyvsp[-1].code);
       ;}
    break;

  case 185:
#line 791 "src/mmlparse.y"
    {
          yyval.code = code_new_inst(i_set_indexset, 1, code_new_symbol(yyvsp[-1].sym));
       ;}
    break;

  case 186:
#line 794 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_expr_if, 3, yyvsp[-5].code, yyvsp[-3].code, yyvsp[-1].code);
      ;}
    break;

  case 187:
#line 800 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_read_new, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 188:
#line 801 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_read_param, 2, yyvsp[-1].code, yyvsp[0].code); ;}
    break;

  case 189:
#line 805 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_read_skip, 1, yyvsp[0].code); ;}
    break;

  case 190:
#line 806 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_read_use, 1, yyvsp[0].code); ;}
    break;

  case 191:
#line 807 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_read_comment, 1, yyvsp[0].code); ;}
    break;

  case 192:
#line 811 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_tuple_list_new, 1, yyvsp[0].code);
      ;}
    break;

  case 193:
#line 814 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_tuple_list_add, 2, yyvsp[-2].code, yyvsp[0].code);
      ;}
    break;

  case 194:
#line 817 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_read, 1, yyvsp[0].code); ;}
    break;

  case 195:
#line 821 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bool_eq, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 196:
#line 822 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bool_ne, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 197:
#line 823 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bool_gt, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 198:
#line 824 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bool_ge, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 199:
#line 825 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bool_lt, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 200:
#line 826 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bool_le, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 201:
#line 827 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bool_seq, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 202:
#line 828 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bool_sneq, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 203:
#line 829 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bool_subs, 2, yyvsp[0].code, yyvsp[-2].code); ;}
    break;

  case 204:
#line 830 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bool_sseq, 2, yyvsp[0].code, yyvsp[-2].code); ;}
    break;

  case 205:
#line 831 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bool_subs, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 206:
#line 832 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bool_sseq, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 207:
#line 833 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bool_and, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 208:
#line 834 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bool_or,  2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 209:
#line 835 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bool_xor, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 210:
#line 836 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bool_not, 1, yyvsp[0].code); ;}
    break;

  case 211:
#line 837 "src/mmlparse.y"
    { yyval.code = yyvsp[-1].code; ;}
    break;

  case 212:
#line 838 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bool_is_elem, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 213:
#line 839 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bool_exists, 1, yyvsp[-1].code); ;}
    break;

  case 214:
#line 840 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_define_deref, 2,
            code_new_define(yyvsp[-3].def),
            code_new_inst(i_tuple_new, 1, yyvsp[-1].code));
      ;}
    break;

  case 215:
#line 845 "src/mmlparse.y"
    {
        yyval.code = code_new_inst(i_expr_if, 3, yyvsp[-5].code, yyvsp[-3].code, yyvsp[-1].code);
     ;}
    break;

  case 216:
#line 851 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_tuple_empty, 0); ;}
    break;

  case 217:
#line 852 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_tuple_new, 1, yyvsp[-1].code);  ;}
    break;

  case 218:
#line 856 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_tuple_empty, 0);
      ;}
    break;

  case 219:
#line 859 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_tuple_new, 1, yyvsp[-1].code);
      ;}
    break;

  case 220:
#line 865 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_elem_list_new, 1, yyvsp[0].code);
      ;}
    break;

  case 221:
#line 868 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_elem_list_add, 2, yyvsp[-2].code, yyvsp[0].code);
      ;}
    break;

  case 222:
#line 874 "src/mmlparse.y"
    { yyval.code = yyvsp[0].code; ;}
    break;

  case 223:
#line 875 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_expr_add, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 224:
#line 876 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_expr_sub, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 225:
#line 880 "src/mmlparse.y"
    { yyval.code = yyvsp[0].code; ;}
    break;

  case 226:
#line 881 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_expr_mul, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 227:
#line 882 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_expr_div, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 228:
#line 883 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_expr_mod, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 229:
#line 884 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_expr_intdiv, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 230:
#line 888 "src/mmlparse.y"
    { yyval.code = code_new_numb(yyvsp[0].numb); ;}
    break;

  case 231:
#line 889 "src/mmlparse.y"
    { yyval.code = code_new_strg(yyvsp[0].strg);  ;}
    break;

  case 232:
#line 890 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_local_deref, 1, code_new_name(yyvsp[0].name));
      ;}
    break;

  case 233:
#line 893 "src/mmlparse.y"
    { 
         yyval.code = code_new_inst(i_symbol_deref, 2, code_new_symbol(yyvsp[-1].sym), yyvsp[0].code);
      ;}
    break;

  case 234:
#line 896 "src/mmlparse.y"
    { 
         yyval.code = code_new_inst(i_symbol_deref, 2, code_new_symbol(yyvsp[-1].sym), yyvsp[0].code);
      ;}
    break;

  case 235:
#line 899 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_define_deref, 2,
            code_new_define(yyvsp[-3].def),
            code_new_inst(i_tuple_new, 1, yyvsp[-1].code));
      ;}
    break;

  case 236:
#line 904 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_define_deref, 2,
            code_new_define(yyvsp[-3].def),
            code_new_inst(i_tuple_new, 1, yyvsp[-1].code));
      ;}
    break;

  case 237:
#line 909 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_expr_fac, 1, yyvsp[-1].code); ;}
    break;

  case 238:
#line 910 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_expr_pow, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 239:
#line 912 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_expr_card, 1, yyvsp[-1].code); ;}
    break;

  case 240:
#line 913 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_expr_abs, 1, yyvsp[-1].code); ;}
    break;

  case 241:
#line 914 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_expr_sgn, 1, yyvsp[-1].code); ;}
    break;

  case 242:
#line 915 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_expr_floor, 1, yyvsp[-1].code); ;}
    break;

  case 243:
#line 916 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_expr_ceil, 1, yyvsp[-1].code); ;}
    break;

  case 244:
#line 917 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_expr_log, 1, yyvsp[-1].code); ;}
    break;

  case 245:
#line 918 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_expr_ln, 1, yyvsp[-1].code); ;}
    break;

  case 246:
#line 919 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_expr_exp, 1, yyvsp[-1].code); ;}
    break;

  case 247:
#line 920 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_expr_sqrt, 1, yyvsp[-1].code); ;}
    break;

  case 248:
#line 922 "src/mmlparse.y"
    { yyval.code = yyvsp[0].code; ;}
    break;

  case 249:
#line 923 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_expr_neg, 1, yyvsp[0].code); ;}
    break;

  case 250:
#line 924 "src/mmlparse.y"
    { yyval.code = yyvsp[-1].code; ;}
    break;

  case 251:
#line 925 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_expr_rand, 2, yyvsp[-3].code, yyvsp[-1].code);
      ;}
    break;

  case 252:
#line 928 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_expr_if, 3, yyvsp[-5].code, yyvsp[-3].code, yyvsp[-1].code);
      ;}
    break;

  case 253:
#line 931 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_expr_sglmin, 1, yyvsp[0].code);
      ;}
    break;

  case 254:
#line 934 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_expr_sglmax, 1, yyvsp[0].code);
      ;}
    break;

  case 255:
#line 937 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_expr_min, 2, yyvsp[-2].code, yyvsp[0].code);
      ;}
    break;

  case 256:
#line 940 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_expr_max, 2, yyvsp[-2].code, yyvsp[0].code);
      ;}
    break;

  case 257:
#line 943 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_expr_sum, 2, yyvsp[-2].code, yyvsp[0].code);
      ;}
    break;

  case 258:
#line 946 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_expr_min2, 1, yyvsp[-1].code);
      ;}
    break;

  case 259:
#line 949 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_expr_max2, 1, yyvsp[-1].code);
      ;}
    break;

  case 260:
#line 952 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_expr_ord, 3, yyvsp[-5].code, yyvsp[-3].code, yyvsp[-1].code);
      ;}
    break;


    }

/* Line 991 of yacc.c.  */
#line 3779 "src/mmlparse.c"

  yyvsp -= yylen;
  yyssp -= yylen;


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
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("syntax error, unexpected ") + 1;
	  yysize += yystrlen (yytname[yytype]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        {
	  /* Pop the error token.  */
          YYPOPSTACK;
	  /* Pop the rest of the stack.  */
	  while (yyss < yyssp)
	    {
	      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
	      yydestruct (yystos[*yyssp], yyvsp);
	      YYPOPSTACK;
	    }
	  YYABORT;
        }

      YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
      yydestruct (yytoken, &yylval);
      yychar = YYEMPTY;

    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab2;


/*----------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action.  |
`----------------------------------------------------*/
yyerrlab1:

  /* Suppress GCC warning that yyerrlab1 is unused when no action
     invokes YYERROR.  */
#if defined (__GNUC_MINOR__) && 2093 <= (__GNUC__ * 1000 + __GNUC_MINOR__)
  __attribute__ ((__unused__))
#endif


  goto yyerrlab2;


/*---------------------------------------------------------------.
| yyerrlab2 -- pop states until the error token can be shifted.  |
`---------------------------------------------------------------*/
yyerrlab2:
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

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      yyvsp--;
      yystate = *--yyssp;

      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


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
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}



