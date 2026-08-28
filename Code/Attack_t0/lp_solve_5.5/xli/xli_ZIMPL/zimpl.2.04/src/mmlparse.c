/* A Bison parser, made by GNU Bison 1.875d.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004 Free Software Foundation, Inc.

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
     DEFSET = 267,
     PRINT = 268,
     CHECK = 269,
     BINARY = 270,
     INTEGER = 271,
     REAL = 272,
     ASGN = 273,
     DO = 274,
     WITH = 275,
     IN = 276,
     TO = 277,
     UNTIL = 278,
     BY = 279,
     FORALL = 280,
     EMPTY_TUPLE = 281,
     EMPTY_SET = 282,
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
     IF = 301,
     THEN = 302,
     ELSE = 303,
     END = 304,
     INTER = 305,
     UNION = 306,
     CROSS = 307,
     SYMDIFF = 308,
     WITHOUT = 309,
     PROJ = 310,
     MOD = 311,
     DIV = 312,
     POW = 313,
     FAC = 314,
     CARD = 315,
     ABS = 316,
     SGN = 317,
     FLOOR = 318,
     CEIL = 319,
     LOG = 320,
     LN = 321,
     EXP = 322,
     SQRT = 323,
     RANDOM = 324,
     ORD = 325,
     READ = 326,
     AS = 327,
     SKIP = 328,
     USE = 329,
     COMMENT = 330,
     SUBSETS = 331,
     INDEXSET = 332,
     POWERSET = 333,
     VIF = 334,
     VABS = 335,
     TYPE1 = 336,
     TYPE2 = 337,
     NUMBSYM = 338,
     STRGSYM = 339,
     VARSYM = 340,
     SETSYM = 341,
     NUMBDEF = 342,
     STRGDEF = 343,
     SETDEF = 344,
     DEFNAME = 345,
     NAME = 346,
     STRG = 347,
     NUMB = 348,
     SCALE = 349,
     SEPARATE = 350
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
#define DEFSET 267
#define PRINT 268
#define CHECK 269
#define BINARY 270
#define INTEGER 271
#define REAL 272
#define ASGN 273
#define DO 274
#define WITH 275
#define IN 276
#define TO 277
#define UNTIL 278
#define BY 279
#define FORALL 280
#define EMPTY_TUPLE 281
#define EMPTY_SET 282
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
#define IF 301
#define THEN 302
#define ELSE 303
#define END 304
#define INTER 305
#define UNION 306
#define CROSS 307
#define SYMDIFF 308
#define WITHOUT 309
#define PROJ 310
#define MOD 311
#define DIV 312
#define POW 313
#define FAC 314
#define CARD 315
#define ABS 316
#define SGN 317
#define FLOOR 318
#define CEIL 319
#define LOG 320
#define LN 321
#define EXP 322
#define SQRT 323
#define RANDOM 324
#define ORD 325
#define READ 326
#define AS 327
#define SKIP 328
#define USE 329
#define COMMENT 330
#define SUBSETS 331
#define INDEXSET 332
#define POWERSET 333
#define VIF 334
#define VABS 335
#define TYPE1 336
#define TYPE2 337
#define NUMBSYM 338
#define STRGSYM 339
#define VARSYM 340
#define SETSYM 341
#define NUMBDEF 342
#define STRGDEF 343
#define SETDEF 344
#define DEFNAME 345
#define NAME 346
#define STRG 347
#define NUMB 348
#define SCALE 349
#define SEPARATE 350




/* Copy the first part of user declarations.  */
#line 1 "src/mmlparse.y"

#pragma ident "@(#) $Id: mmlparse.y,v 1.69 2006/01/19 20:53:06 bzfkocht Exp $"
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
/*lint -e428 -e574 -e525 -e527 -e661 -e662 -e676 */
/*lint -e713 -e717 -e732 -e734 -e737 -e744 -e750 -e751 -e753 -e762 -e764 */
/*lint -e818 -e830 */
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
#line 333 "src/mmlparse.c"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 345 "src/mmlparse.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

# ifndef YYFREE
#  define YYFREE free
# endif
# ifndef YYMALLOC
#  define YYMALLOC malloc
# endif

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   define YYSTACK_ALLOC alloca
#  endif
# else
#  if defined (alloca) || defined (_ALLOCA_H)
#   define YYSTACK_ALLOC alloca
#  else
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
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
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short int yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short int) + sizeof (YYSTYPE))			\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined (__GNUC__) && 1 < __GNUC__
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
   typedef short int yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  37
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1863

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  108
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  50
/* YYNRULES -- Number of rules. */
#define YYNRULES  250
/* YYNRULES -- Number of states. */
#define YYNSTATES  667

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   350

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      97,    98,   101,    99,    96,   100,     2,   102,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,   103,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   104,     2,   105,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   106,     2,   107,     2,     2,     2,     2,
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
      95
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short int yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    11,    13,    15,    17,
      19,    21,    23,    29,    38,    47,    55,    57,    61,    68,
      73,    76,    85,    94,   103,   105,   109,   119,   129,   135,
     137,   139,   140,   143,   155,   165,   174,   181,   182,   184,
     186,   187,   190,   194,   195,   198,   201,   202,   205,   206,
     209,   211,   215,   217,   220,   223,   227,   231,   236,   242,
     248,   254,   259,   264,   269,   274,   281,   288,   295,   302,
     307,   315,   327,   339,   351,   363,   375,   387,   399,   411,
     423,   435,   447,   459,   471,   483,   495,   507,   515,   523,
     531,   539,   543,   547,   551,   555,   559,   563,   567,   571,
     575,   579,   583,   587,   591,   595,   599,   603,   607,   611,
     615,   619,   623,   626,   630,   631,   635,   637,   639,   641,
     643,   645,   647,   651,   655,   659,   663,   667,   671,   673,
     677,   681,   685,   688,   691,   694,   699,   704,   712,   716,
     722,   727,   732,   733,   735,   737,   741,   744,   747,   750,
     753,   758,   763,   766,   767,   770,   773,   778,   780,   788,
     794,   802,   808,   813,   817,   821,   825,   829,   833,   837,
     841,   845,   850,   854,   858,   862,   866,   872,   878,   885,
     890,   898,   903,   906,   909,   912,   915,   917,   921,   923,
     927,   931,   935,   939,   943,   947,   951,   955,   959,   963,
     967,   971,   975,   979,   983,   986,   990,   994,   999,  1001,
    1005,  1006,  1010,  1012,  1016,  1018,  1022,  1026,  1028,  1032,
    1036,  1040,  1044,  1048,  1050,  1052,  1054,  1057,  1060,  1065,
    1070,  1073,  1078,  1083,  1088,  1093,  1098,  1103,  1108,  1113,
    1118,  1121,  1124,  1128,  1135,  1143,  1148,  1153,  1158,  1163,
    1168
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short int yyrhs[] =
{
     109,     0,    -1,   110,    -1,   117,    -1,   120,    -1,   130,
      -1,   131,    -1,   140,    -1,   113,    -1,   114,    -1,   115,
      -1,   143,    -1,     3,    91,    18,   147,   103,    -1,     3,
      91,   104,   145,   105,    18,   147,   103,    -1,     3,    91,
     104,   145,   105,    18,   111,   103,    -1,     3,    91,   104,
     105,    18,   111,   103,    -1,   112,    -1,   111,    96,   112,
      -1,    76,    97,   147,    96,   155,    98,    -1,    78,    97,
     147,    98,    -1,   152,   147,    -1,    10,    90,    97,   116,
      98,    18,   155,   103,    -1,    11,    90,    97,   116,    98,
      18,   155,   103,    -1,    12,    90,    97,   116,    98,    18,
     147,   103,    -1,    91,    -1,   116,    96,    91,    -1,     4,
      91,   104,   145,   105,    18,   126,   119,   103,    -1,     4,
      91,   104,   145,   105,    18,   155,   119,   103,    -1,     4,
      91,    18,   118,   103,    -1,   126,    -1,   155,    -1,    -1,
      31,   155,    -1,     5,    91,   104,   145,   105,   121,   122,
     123,   124,   125,   103,    -1,     5,    91,   104,   145,   105,
      15,   124,   125,   103,    -1,     5,    91,   121,   122,   123,
     124,   125,   103,    -1,     5,    91,    15,   124,   125,   103,
      -1,    -1,    17,    -1,    16,    -1,    -1,    33,   155,    -1,
      33,   100,    38,    -1,    -1,    32,   155,    -1,    32,    38,
      -1,    -1,    29,   155,    -1,    -1,    30,   155,    -1,   127,
      -1,   126,    96,   127,    -1,   148,    -1,   128,   129,    -1,
     152,   155,    -1,    20,   154,    20,    -1,   128,   154,    20,
      -1,   129,   128,   154,    20,    -1,     6,    91,    19,   137,
     103,    -1,     7,    91,    19,   137,   103,    -1,     8,    91,
      19,   132,   103,    -1,   137,   136,   137,   134,    -1,   137,
     136,   155,   134,    -1,   155,   136,   137,   134,    -1,   155,
     136,   155,   134,    -1,   155,   136,   137,    32,   155,   134,
      -1,   155,   136,   155,    32,   155,   134,    -1,   155,   136,
     137,    33,   155,   134,    -1,   155,   136,   155,    33,   155,
     134,    -1,    25,   145,    19,   132,    -1,    46,   151,    47,
     132,    48,   132,    49,    -1,    79,   133,    47,   137,   136,
     137,    48,   137,   136,   137,    49,    -1,    79,   133,    47,
     155,   136,   137,    48,   137,   136,   137,    49,    -1,    79,
     133,    47,   137,   136,   155,    48,   137,   136,   137,    49,
      -1,    79,   133,    47,   137,   136,   137,    48,   155,   136,
     137,    49,    -1,    79,   133,    47,   137,   136,   137,    48,
     137,   136,   155,    49,    -1,    79,   133,    47,   155,   136,
     155,    48,   137,   136,   137,    49,    -1,    79,   133,    47,
     155,   136,   137,    48,   155,   136,   137,    49,    -1,    79,
     133,    47,   155,   136,   137,    48,   137,   136,   155,    49,
      -1,    79,   133,    47,   137,   136,   155,    48,   155,   136,
     137,    49,    -1,    79,   133,    47,   137,   136,   155,    48,
     137,   136,   155,    49,    -1,    79,   133,    47,   137,   136,
     137,    48,   155,   136,   155,    49,    -1,    79,   133,    47,
     155,   136,   155,    48,   155,   136,   137,    49,    -1,    79,
     133,    47,   155,   136,   155,    48,   137,   136,   155,    49,
      -1,    79,   133,    47,   155,   136,   137,    48,   155,   136,
     155,    49,    -1,    79,   133,    47,   137,   136,   155,    48,
     155,   136,   155,    49,    -1,    79,   133,    47,   155,   136,
     155,    48,   155,   136,   155,    49,    -1,    79,   133,    47,
     137,   136,   137,    49,    -1,    79,   133,    47,   155,   136,
     137,    49,    -1,    79,   133,    47,   137,   136,   155,    49,
      -1,    79,   133,    47,   155,   136,   155,    49,    -1,   137,
      37,   137,    -1,   155,    37,   137,    -1,   137,    37,   155,
      -1,   137,    34,   137,    -1,   155,    34,   137,    -1,   137,
      34,   155,    -1,   137,    32,   137,    -1,   155,    32,   137,
      -1,   137,    32,   155,    -1,   137,    33,   137,    -1,   155,
      33,   137,    -1,   137,    33,   155,    -1,   137,    35,   137,
      -1,   155,    35,   137,    -1,   137,    35,   155,    -1,   137,
      36,   137,    -1,   155,    36,   137,    -1,   137,    36,   155,
      -1,   133,    39,   133,    -1,   133,    40,   133,    -1,   133,
      41,   133,    -1,    42,   133,    -1,    97,   133,    98,    -1,
      -1,   134,    96,   135,    -1,    94,    -1,    95,    -1,    32,
      -1,    33,    -1,    34,    -1,   138,    -1,   137,    99,   138,
      -1,   137,   100,   138,    -1,   137,    99,   156,    -1,   137,
     100,   156,    -1,   155,    99,   138,    -1,   155,   100,   138,
      -1,   139,    -1,   138,   101,   157,    -1,   138,   102,   157,
      -1,   156,   101,   139,    -1,    85,   153,    -1,    99,   139,
      -1,   100,   139,    -1,    80,    97,   137,    98,    -1,    43,
     145,    19,   138,    -1,    46,   151,    47,   137,    48,   137,
      49,    -1,    97,   137,    98,    -1,     9,    91,    19,   141,
     103,    -1,   142,   124,    19,   137,    -1,    25,   145,    19,
     141,    -1,    -1,    81,    -1,    82,    -1,    19,   144,   103,
      -1,    13,   155,    -1,    13,   152,    -1,    13,   147,    -1,
      14,   151,    -1,    25,   145,    19,   144,    -1,   152,    21,
     147,   146,    -1,   147,   146,    -1,    -1,    20,   151,    -1,
      86,   153,    -1,    89,    97,   154,    98,    -1,    27,    -1,
     106,   155,    22,   155,    24,   155,   107,    -1,   106,   155,
      22,   155,   107,    -1,   106,   155,    23,   155,    24,   155,
     107,    -1,   106,   155,    23,   155,   107,    -1,    51,   145,
      19,   147,    -1,   147,    51,   147,    -1,   147,    99,   147,
      -1,   147,    53,   147,    -1,   147,    54,   147,    -1,   147,
     100,   147,    -1,   147,    52,   147,    -1,   147,   101,   147,
      -1,   147,    50,   147,    -1,    50,   145,    19,   147,    -1,
      97,   147,    98,    -1,   106,   150,   107,    -1,   106,   154,
     107,    -1,   106,   145,   107,    -1,   106,   145,    19,   155,
     107,    -1,   106,   145,    19,   152,   107,    -1,    55,    97,
     147,    96,   152,    98,    -1,    77,    97,    86,    98,    -1,
      46,   151,    47,   147,    48,   147,    49,    -1,    71,   155,
      72,   155,    -1,   148,   149,    -1,    73,   155,    -1,    74,
     155,    -1,    75,   155,    -1,   152,    -1,   150,    96,   152,
      -1,   148,    -1,   155,    34,   155,    -1,   155,    37,   155,
      -1,   155,    36,   155,    -1,   155,    33,   155,    -1,   155,
      35,   155,    -1,   155,    32,   155,    -1,   147,    34,   147,
      -1,   147,    37,   147,    -1,   147,    36,   147,    -1,   147,
      33,   147,    -1,   147,    35,   147,    -1,   147,    32,   147,
      -1,   151,    39,   151,    -1,   151,    40,   151,    -1,   151,
      41,   151,    -1,    42,   151,    -1,    97,   151,    98,    -1,
     152,    21,   147,    -1,    28,    97,   145,    98,    -1,    26,
      -1,    35,   154,    36,    -1,    -1,   104,   154,   105,    -1,
     155,    -1,   154,    96,   155,    -1,   156,    -1,   155,    99,
     156,    -1,   155,   100,   156,    -1,   157,    -1,   156,   101,
     157,    -1,   156,   102,   157,    -1,   156,    56,   157,    -1,
     156,    57,   157,    -1,   156,    58,   157,    -1,    93,    -1,
      92,    -1,    91,    -1,    83,   153,    -1,    84,   153,    -1,
      87,    97,   154,    98,    -1,    88,    97,   154,    98,    -1,
     157,    59,    -1,    60,    97,   147,    98,    -1,    61,    97,
     155,    98,    -1,    62,    97,   155,    98,    -1,    63,    97,
     155,    98,    -1,    64,    97,   155,    98,    -1,    65,    97,
     155,    98,    -1,    66,    97,   155,    98,    -1,    67,    97,
     155,    98,    -1,    68,    97,   155,    98,    -1,    99,   157,
      -1,   100,   157,    -1,    97,   155,    98,    -1,    69,    97,
     155,    96,   155,    98,    -1,    46,   151,    47,   155,    48,
     155,    49,    -1,    44,   145,    19,   156,    -1,    45,   145,
      19,   156,    -1,    43,   145,    19,   156,    -1,    44,    97,
     154,    98,    -1,    45,    97,   154,    98,    -1,    70,    97,
     147,    96,   155,    96,   155,    98,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   129,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   146,   153,   159,   165,   175,   176,   179,   182,
     188,   197,   206,   215,   224,   227,   237,   240,   243,   252,
     253,   260,   261,   269,   273,   282,   289,   302,   303,   304,
     309,   312,   313,   317,   318,   319,   323,   324,   328,   329,
     337,   338,   341,   342,   346,   350,   354,   357,   369,   372,
     382,   388,   391,   396,   401,   408,   412,   417,   421,   427,
     430,   433,   436,   441,   446,   451,   455,   462,   469,   475,
     481,   487,   492,   500,   508,   516,   523,   533,   536,   539,
     542,   549,   550,   553,   556,   557,   560,   563,   564,   567,
     570,   571,   574,   577,   578,   581,   584,   585,   588,   591,
     592,   593,   594,   595,   599,   600,   604,   605,   609,   610,
     611,   615,   616,   617,   618,   619,   622,   623,   631,   632,
     633,   637,   641,   644,   645,   648,   649,   653,   656,   664,
     670,   673,   679,   680,   681,   689,   693,   694,   695,   696,
     697,   707,   710,   717,   718,   722,   725,   730,   731,   734,
     737,   740,   743,   744,   745,   748,   749,   750,   753,   754,
     757,   758,   759,   760,   761,   762,   763,   764,   765,   768,
     771,   777,   778,   782,   783,   784,   788,   791,   794,   798,
     799,   800,   801,   802,   803,   804,   805,   806,   807,   808,
     809,   810,   811,   812,   813,   814,   815,   816,   820,   821,
     825,   828,   834,   837,   843,   844,   845,   849,   850,   851,
     852,   853,   854,   858,   859,   860,   863,   866,   869,   874,
     879,   880,   881,   882,   883,   884,   885,   886,   887,   888,
     890,   891,   892,   893,   896,   899,   902,   905,   908,   911,
     914
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DECLSET", "DECLPAR", "DECLVAR",
  "DECLMIN", "DECLMAX", "DECLSUB", "DECLSOS", "DEFNUMB", "DEFSTRG",
  "DEFSET", "PRINT", "CHECK", "BINARY", "INTEGER", "REAL", "ASGN", "DO",
  "WITH", "IN", "TO", "UNTIL", "BY", "FORALL", "EMPTY_TUPLE", "EMPTY_SET",
  "EXISTS", "PRIORITY", "STARTVAL", "DEFAULT", "CMP_LE", "CMP_GE",
  "CMP_EQ", "CMP_LT", "CMP_GT", "CMP_NE", "INFTY", "AND", "OR", "XOR",
  "NOT", "SUM", "MIN", "MAX", "IF", "THEN", "ELSE", "END", "INTER",
  "UNION", "CROSS", "SYMDIFF", "WITHOUT", "PROJ", "MOD", "DIV", "POW",
  "FAC", "CARD", "ABS", "SGN", "FLOOR", "CEIL", "LOG", "LN", "EXP", "SQRT",
  "RANDOM", "ORD", "READ", "AS", "SKIP", "USE", "COMMENT", "SUBSETS",
  "INDEXSET", "POWERSET", "VIF", "VABS", "TYPE1", "TYPE2", "NUMBSYM",
  "STRGSYM", "VARSYM", "SETSYM", "NUMBDEF", "STRGDEF", "SETDEF", "DEFNAME",
  "NAME", "STRG", "NUMB", "SCALE", "SEPARATE", "','", "'('", "')'", "'+'",
  "'-'", "'*'", "'/'", "';'", "'['", "']'", "'{'", "'}'", "$accept",
  "stmt", "decl_set", "set_entry_list", "set_entry", "def_numb",
  "def_strg", "def_set", "name_list", "decl_par", "par_singleton",
  "par_default", "decl_var", "var_type", "lower", "upper", "priority",
  "startval", "cexpr_entry_list", "cexpr_entry", "matrix_head",
  "matrix_body", "decl_obj", "decl_sub", "constraint", "vbool",
  "con_attr_list", "con_attr", "con_type", "vexpr", "vproduct", "vfactor",
  "decl_sos", "soset", "sos_type", "exec_do", "command", "idxset",
  "condition", "sexpr", "read", "read_par", "tuple_list", "lexpr", "tuple",
  "symidx", "cexpr_list", "cexpr", "cproduct", "cfactor", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short int yytoknum[] =
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
     345,   346,   347,   348,   349,   350,    44,    40,    41,    43,
      45,    42,    47,    59,    91,    93,   123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,   108,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   110,   110,   110,   110,   111,   111,   111,   111,
     112,   113,   114,   115,   116,   116,   117,   117,   117,   118,
     118,   119,   119,   120,   120,   120,   120,   121,   121,   121,
     122,   122,   122,   123,   123,   123,   124,   124,   125,   125,
     126,   126,   126,   126,   127,   128,   129,   129,   130,   130,
     131,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   134,   134,   135,   135,   136,   136,
     136,   137,   137,   137,   137,   137,   137,   137,   138,   138,
     138,   138,   139,   139,   139,   139,   139,   139,   139,   140,
     141,   141,   142,   142,   142,   143,   144,   144,   144,   144,
     144,   145,   145,   146,   146,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   148,   148,   149,   149,   149,   150,   150,   150,   151,
     151,   151,   151,   151,   151,   151,   151,   151,   151,   151,
     151,   151,   151,   151,   151,   151,   151,   151,   152,   152,
     153,   153,   154,   154,   155,   155,   155,   156,   156,   156,
     156,   156,   156,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     5,     8,     8,     7,     1,     3,     6,     4,
       2,     8,     8,     8,     1,     3,     9,     9,     5,     1,
       1,     0,     2,    11,     9,     8,     6,     0,     1,     1,
       0,     2,     3,     0,     2,     2,     0,     2,     0,     2,
       1,     3,     1,     2,     2,     3,     3,     4,     5,     5,
       5,     4,     4,     4,     4,     6,     6,     6,     6,     4,
       7,    11,    11,    11,    11,    11,    11,    11,    11,    11,
      11,    11,    11,    11,    11,    11,    11,     7,     7,     7,
       7,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     3,     0,     3,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     1,     3,
       3,     3,     2,     2,     2,     4,     4,     7,     3,     5,
       4,     4,     0,     1,     1,     3,     2,     2,     2,     2,
       4,     4,     2,     0,     2,     2,     4,     1,     7,     5,
       7,     5,     4,     3,     3,     3,     3,     3,     3,     3,
       3,     4,     3,     3,     3,     3,     5,     5,     6,     4,
       7,     4,     2,     2,     2,     2,     1,     3,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     3,     3,     4,     1,     3,
       0,     3,     1,     3,     1,     3,     3,     1,     3,     3,
       3,     3,     3,     1,     1,     1,     2,     2,     4,     4,
       2,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       2,     2,     3,     6,     7,     4,     4,     4,     4,     4,
       8
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     2,     8,     9,    10,     3,     4,     5,
       6,     7,    11,     0,     0,    37,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     1,     0,     0,
       0,     0,    46,    39,    38,     0,    40,     0,     0,     0,
     142,     0,     0,     0,   208,   157,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   210,   210,   210,     0,
       0,     0,   225,   224,   223,     0,     0,     0,     0,   148,
     147,   146,   214,   217,     0,     0,     0,     0,   149,     0,
       0,     0,     0,     0,   153,     0,   145,     0,     0,     0,
       0,     0,     0,     0,     0,    29,    50,     0,    52,     0,
      30,     0,     0,    48,     0,     0,    43,     0,     0,     0,
     210,     0,     0,     0,     0,   121,   128,     0,   214,     0,
       0,     0,     0,     0,     0,     0,     0,   143,   144,     0,
      46,    24,     0,     0,     0,     0,   212,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   226,
     227,   155,     0,     0,     0,     0,     0,   240,   241,     0,
     188,     0,   186,     0,   212,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     230,     0,   204,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   152,     0,    12,     0,     0,
       0,     0,     0,    28,     0,     0,    53,     0,     0,     0,
     182,    54,     0,    47,     0,     0,    37,     0,    41,     0,
      46,     0,     0,     0,   132,     0,     0,   133,   134,     0,
       0,    58,     0,     0,     0,     0,     0,    59,     0,     0,
       0,     0,     0,     0,     0,    60,   118,   119,   120,     0,
       0,     0,   139,     0,     0,     0,     0,     0,   209,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   172,   242,     0,   175,     0,
     173,   174,     0,     0,   170,   163,   168,   165,   166,   164,
     167,   169,   215,   216,   220,   221,   222,   218,   219,     0,
     205,   200,   198,   195,   199,   197,   196,   201,   202,   203,
     206,   194,   192,   189,   193,   191,   190,     0,   150,   154,
     153,     0,     0,     0,    16,     0,     0,    55,     0,     0,
      51,     0,     0,   183,   184,   185,     0,    49,    36,    46,
      40,    42,    45,    44,    48,     0,     0,     0,   138,   122,
     124,   123,   125,   129,   130,   126,   215,   127,   216,   131,
       0,     0,   112,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   114,   114,   114,   114,   142,     0,    25,     0,
       0,     0,   213,   247,   248,   245,   249,   246,     0,     0,
     171,   162,     0,   231,   232,   233,   234,   235,   236,   237,
     238,   239,     0,     0,   179,   211,   228,   229,   156,     0,
       0,   187,     0,     0,   207,   151,     0,     0,     0,    15,
      20,     0,     0,   181,    56,     0,    31,    31,    48,    43,
       0,   136,   247,     0,     0,   135,    69,     0,     0,     0,
     113,   109,   110,   111,     0,     0,    97,    99,   100,   102,
      94,    96,   103,   105,   106,   108,    91,    93,    98,   101,
      95,   104,   107,    92,    61,    62,     0,     0,    63,     0,
       0,    64,   141,   140,     0,     0,     0,     0,     0,     0,
       0,     0,   177,   176,     0,   159,     0,   161,     0,     0,
      17,    14,    13,    57,     0,     0,     0,     0,    46,    35,
       0,     0,     0,     0,     0,   114,   114,   114,   114,    21,
      22,    23,     0,     0,   178,   243,     0,     0,     0,     0,
      19,    32,    26,    27,    34,    48,     0,     0,     0,     0,
       0,     0,   116,   117,   115,    65,    67,    66,    68,   180,
     244,     0,   158,   160,     0,     0,   137,    70,     0,    87,
       0,    89,     0,    88,     0,    90,   250,    18,    33,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    71,    75,    74,    81,    73,    80,    79,    85,    72,
      78,    77,    84,    76,    83,    82,    86
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,    12,    13,   373,   374,    14,    15,    16,   152,    17,
     114,   555,    18,    46,   126,   260,   123,   255,   115,   116,
     117,   246,    19,    20,   143,   282,   524,   594,   289,   283,
     135,   136,    21,   149,   150,    22,    36,   103,   235,   104,
     118,   250,   191,    98,   105,   179,   155,   100,    92,    93
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -409
static const short int yypact[] =
{
    1542,   -37,   -18,    12,    27,    42,    61,   142,   -12,   110,
     133,   188,   249,  -409,  -409,  -409,  -409,  -409,  -409,  -409,
    -409,  -409,  -409,    -5,     6,    19,   239,   287,   294,   332,
     149,   244,   282,  1066,   884,   577,   233,  -409,   728,  1191,
    1136,   577,   333,  -409,  -409,   577,   369,  1647,  1647,  1349,
      62,   291,   291,   291,  -409,  -409,  1705,   577,  1204,  1236,
     884,   577,   577,   308,   311,   313,   316,   318,   331,   343,
     350,   358,   366,   383,   401,   407,   321,   321,   321,   447,
     448,   494,  -409,  -409,  -409,  1284,  1705,  1705,   990,   661,
    -409,   -41,   736,   392,   505,   884,   884,   322,   328,   530,
     139,   884,   728,   588,   191,   595,  -409,   519,   606,   529,
    1705,   884,  1705,  1705,   545,   565,  -409,   681,   540,  1705,
     -41,   603,  1705,   701,   629,  1763,   711,   577,   884,   651,
     321,  1647,  1647,  1647,    67,   169,  -409,   196,   743,   423,
     577,   884,  1589,   672,   185,   202,   577,  -409,  -409,   679,
     333,  -409,   131,   211,   246,   -26,   -41,   762,  1284,   768,
    1284,   776,   467,   787,   797,   728,   728,  1705,  1705,  1705,
    1705,  1705,  1705,  1705,  1705,  1705,   728,   712,  1705,  -409,
    -409,  -409,  1705,  1705,  1705,   759,   589,   392,   392,   -13,
     540,   -54,   595,   -14,    22,   728,   728,   728,   728,   728,
     728,   728,   728,  1705,  1705,  1705,  1705,  1705,  1705,  1705,
    -409,   577,  -409,  1430,    10,    32,   728,   728,   728,   728,
     728,   728,   884,   884,   884,   728,  1705,  1705,  1705,  1705,
    1705,  1705,   678,   188,   884,  -409,   728,  -409,   234,   790,
      -8,   852,   -43,  -409,   156,  1705,   681,  1705,  1705,  1705,
    -409,   -41,   817,   -41,  1705,   733,   713,  1472,   -41,  1530,
     333,   827,   862,  1647,  -409,   763,   779,  -409,  -409,  1647,
    1647,  -409,  1705,  1705,  1647,  1647,  1647,  -409,   845,   939,
    1589,  1589,   953,   483,   552,  -409,  -409,  -409,  -409,  1647,
    1647,   849,  -409,   864,   803,   877,   886,   889,  -409,  1705,
    1705,   364,  1705,   480,  1705,  1284,   728,   728,   770,   789,
     782,   833,   842,   857,   897,   903,   910,   913,   346,   822,
     810,    87,   557,   648,   706,  -409,  -409,  1409,  -409,   156,
    -409,  -409,  1705,  1705,   215,   349,   927,   349,   349,   349,
     349,  -409,   736,   736,   392,   392,   392,   392,   392,   826,
    -409,   661,   661,   661,   661,   661,   661,  -409,   881,   881,
     661,   -41,   -41,   -41,   -41,   -41,   -41,   728,  -409,   328,
     191,   828,   846,   184,  -409,   728,   406,  -409,  1705,  1705,
    -409,     8,  1705,   -41,   -41,   -41,  1136,   -41,  -409,   333,
     369,  -409,  -409,   -41,   701,  1647,  1647,   931,  -409,   169,
     743,   169,   743,   392,   392,   169,   743,   169,   743,  -409,
    1349,  1349,  -409,   223,   402,   454,  1589,  1589,  1589,  1647,
    1647,  1647,  1647,  1647,  1647,  1647,  1647,  1647,  1647,  1647,
    1647,  1647,   225,   196,    29,   265,    62,  1647,  -409,  1705,
    1705,   728,   -41,   736,  -409,   736,  -409,   736,   585,   -28,
     859,   859,   156,  -409,  -409,  -409,  -409,  -409,  -409,  -409,
    -409,  -409,  1705,  1705,  -409,  -409,  -409,  -409,  -409,   851,
     317,  -409,    13,    17,  -409,  -409,   728,   728,   156,  -409,
     661,   190,   653,   -41,  -409,    23,   -22,    15,   701,   711,
     866,   169,   743,    78,   235,  -409,  -409,   917,   155,   174,
    -409,  -409,   935,   935,   185,   202,   225,   196,   225,   196,
     225,   196,   225,   196,   225,   196,   225,   196,   225,   225,
     225,   225,   225,   225,   870,   870,  1705,  1705,   870,  1705,
    1705,   870,  -409,   225,   526,   677,   685,   728,  1705,   887,
     944,   719,  -409,  -409,  1705,  -409,  1705,  -409,   863,   970,
    -409,  -409,  -409,  -409,  1705,   879,   885,   896,   333,  -409,
    1647,  1349,  1647,  1647,   415,   -41,   -41,   -41,   -41,  -409,
    -409,  -409,   593,   -24,  -409,  -409,  1705,   550,   798,  1705,
    -409,   -41,  -409,  -409,  -409,   701,    -9,   938,   132,   227,
     240,   271,  -409,  -409,  -409,   870,   870,   870,   870,  -409,
    -409,   964,  -409,  -409,   986,   901,  -409,  -409,  1647,  -409,
    1647,  -409,  1647,  -409,  1647,  -409,  -409,  -409,  -409,   185,
     202,   185,   202,   185,   202,   185,   202,  1647,  1647,  1647,
    1647,  1647,  1647,  1647,  1647,   204,   281,   312,   354,   432,
     450,   493,   506,   531,   541,   568,   572,   610,   621,   624,
     641,  -409,  -409,  -409,  -409,  -409,  -409,  -409,  -409,  -409,
    -409,  -409,  -409,  -409,  -409,  -409,  -409
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -409,  -409,  -409,   638,   527,  -409,  -409,  -409,   472,  -409,
    -409,   528,  -409,   781,   628,   543,  -149,  -386,   633,   795,
    -100,  -409,  -409,  -409,  -408,  -262,  -403,  -409,   -85,   137,
    -248,  -128,  -409,   611,  -409,  -409,   813,   220,   695,   631,
     961,  -409,  -409,   109,   662,   -30,   -77,   -33,    48,   -48
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned short int yytable[] =
{
      91,   293,   496,   497,   267,   268,   327,   120,   490,   554,
     298,   193,   377,    38,   137,   137,   145,   245,   412,   413,
     538,   399,   401,   156,    40,   600,   405,   407,   484,   379,
     525,   528,   531,   240,    42,    43,    44,   544,   187,   188,
     606,   546,   329,   553,   332,   333,   554,   180,   181,   222,
     223,   224,   186,   330,    23,   194,   203,   204,   203,   204,
     290,   526,   527,   215,   226,   227,   228,   229,   230,   231,
     299,   203,   204,    24,   244,   203,   204,   156,    30,   242,
     186,   301,   299,   303,   187,   188,   251,   146,   299,   253,
     269,   270,   258,   331,   328,   138,   138,   138,   266,    39,
     264,   321,   557,    25,   299,   322,   323,   324,   350,   284,
      41,   394,   203,   204,   203,   204,   203,   204,    26,   299,
     545,   203,   204,    45,   547,   156,   560,   156,   269,   270,
     326,   203,   204,    27,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   147,   148,   156,   382,   491,   409,   156,
     156,   156,    28,   587,   501,   502,   503,   344,   345,   346,
     347,   348,   595,   596,   597,   598,   269,   270,   381,   162,
     271,   226,   227,   228,   229,   230,   231,   269,   270,   138,
     608,   609,    54,   299,   134,   139,   144,   286,   287,   288,
     138,    56,   465,   361,   362,   363,   364,   365,   366,   605,
      31,    33,    34,   560,   212,   214,   286,   287,   288,   188,
     232,   234,   156,    35,   383,   384,   385,   286,   287,   288,
     241,   387,   538,    32,   403,   404,   393,   294,   347,   295,
     137,   269,   270,    29,   286,   287,   288,   262,   203,   204,
     488,   195,   196,   197,   198,   199,    51,   284,   415,    37,
     279,   342,   343,   651,   269,   270,   433,   435,    47,   109,
      54,   121,   416,   417,   418,   124,   442,   197,   265,    56,
     272,   273,   449,   274,   275,   610,   611,   157,   159,   161,
     478,   163,   164,   538,   269,   270,   478,   479,   612,   613,
     200,   201,   202,   551,   470,   274,   275,   529,   530,   472,
     473,   274,   275,   269,   270,   485,    48,   294,   189,   296,
     371,   138,   372,    49,   200,   201,   202,   400,   402,   614,
     615,   500,   406,   408,   269,   270,   274,   275,   138,   138,
     652,   357,   358,   359,   274,   275,   106,   138,   138,   269,
     270,    52,   294,   369,   297,   449,   483,   261,   443,   156,
     445,    50,   447,   487,   216,   217,   218,   219,   220,   221,
     278,   653,   122,   494,   274,   275,   291,   222,   223,   224,
     274,   275,   195,   196,   197,   198,   199,   145,   499,    53,
     274,   275,   151,   284,   284,   284,   505,   507,   509,   511,
     513,   515,   517,   137,   137,   137,   137,   137,   137,   195,
     397,   197,   125,   654,   137,   165,   534,   535,   166,   585,
     167,   269,   270,   168,   290,   169,   203,   204,   414,   562,
     563,   200,   201,   202,   543,   178,   432,   434,   170,   540,
     541,   349,    54,    55,   420,   421,   422,   423,   424,   425,
     171,    56,   462,   492,   138,   203,   204,   172,   200,   201,
     202,   210,   101,   274,   275,   173,    61,    62,   138,   138,
     299,    63,   444,   174,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     175,   655,   371,    75,   372,   138,   426,   427,   428,   429,
     430,   431,    78,   565,   566,    81,   567,   568,   176,   656,
     398,   269,   270,   102,   177,   573,   222,   223,   224,   592,
     593,   577,    88,   578,   305,   420,   421,   422,   423,   424,
     425,   581,   269,   270,   153,   154,   277,   137,   145,   589,
     591,   269,   270,   493,   627,   628,   629,   630,   631,   632,
     633,   634,   657,   601,   182,   183,   604,   144,   498,   274,
     275,   225,   326,   274,   275,   658,   504,   506,   508,   510,
     512,   514,   516,   518,   519,   520,   521,   522,   523,   195,
     196,   197,   198,   199,   533,   620,   299,   622,   446,   624,
     659,   626,   269,   270,   426,   427,   428,   429,   430,   431,
     660,   184,   269,   270,   636,   638,   640,   642,   644,   646,
     648,   650,   211,    54,    55,   274,   275,   233,   138,   138,
     138,   138,    56,   247,   248,   249,   236,   661,   200,   201,
     202,   662,   237,   101,   238,   203,   204,    61,    62,   569,
     269,   270,    63,   537,   239,   195,   196,   197,   198,   199,
     274,   275,   599,   195,   196,   197,   198,   199,   243,   203,
     204,   274,   275,   299,    75,   466,   138,   602,   138,   663,
     138,   244,   138,    78,    89,    97,    81,   269,   270,   107,
     664,   274,   275,   665,   102,   138,   138,   138,   138,   138,
     138,   138,   138,    88,   200,   201,   202,   326,   203,   204,
     666,    97,   200,   201,   202,    90,    99,   586,   144,   588,
     590,   110,   119,   195,   196,   197,   198,   199,   252,   269,
     270,   195,   196,   197,   198,   199,   185,   222,   223,   224,
     274,   275,    99,   269,   270,   367,    97,   213,   389,    43,
      44,   254,    97,   185,   256,   195,   196,   197,   198,   199,
     274,   275,    97,   259,   299,   619,   467,   621,   263,   623,
     192,   625,   200,   201,   202,    55,   552,    99,    99,    97,
     200,   201,   202,    99,   635,   637,   639,   641,   643,   645,
     647,   649,    97,    99,   101,   285,   203,   204,    61,    62,
     570,   300,   292,    63,   200,   201,   202,   302,   571,   185,
      99,   185,   205,   206,   207,   304,   308,   309,   320,   205,
     206,   207,   299,    99,   468,    75,   306,   319,   376,   195,
     196,   197,   198,   199,    78,   576,   307,    81,   203,   204,
     195,   196,   197,   198,   199,   102,   334,   335,   336,   337,
     338,   339,   340,   341,    88,   386,   388,   208,   209,   195,
     196,   197,   198,   199,   276,   209,   395,   351,   352,   353,
     354,   355,   356,    97,    97,    97,   360,   325,   200,   201,
     202,   398,   269,   270,   410,    97,   452,   370,   436,   200,
     201,   202,   195,   196,   197,   198,   199,   326,   274,   275,
     454,   203,   204,   437,    99,    99,    99,   453,   200,   201,
     202,   222,   223,   224,   438,   439,    99,   203,   204,   378,
     375,   222,   223,   224,   440,   603,   119,   441,   464,   396,
      54,    55,    94,   195,   196,   197,   198,   199,   463,    56,
     222,   200,   201,   202,   474,   476,    95,    57,    58,    59,
      60,   455,   203,   204,    61,    62,   448,   450,   451,    63,
     456,   203,   204,   477,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,   457,   203,   204,   542,   579,
     202,    75,   200,   201,   202,   561,   564,    76,    77,   559,
      78,    79,    80,    81,   416,    82,    83,    84,   222,   223,
     224,    96,   582,    86,    87,   574,   411,   607,   583,   469,
      88,   471,   416,   417,   418,   458,   203,   204,   448,   584,
     419,   459,   203,   204,   618,   550,   480,   482,   460,   203,
     204,   461,   203,   204,   481,   556,    54,    55,   489,   486,
     195,   196,   197,   198,   199,    56,   200,   201,   202,   495,
     269,   270,   558,    57,    58,    59,    60,   390,   375,   380,
      61,    62,   575,   203,   204,    63,   368,   532,   119,   190,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,   112,   616,   203,   204,   475,     0,    75,   580,   200,
     201,   202,   536,    76,    77,     0,    78,    79,    80,    81,
       0,    82,    83,    84,   617,   203,   204,    85,     0,    86,
      87,     0,    54,    55,     0,     0,    88,     0,     0,     0,
       0,    56,     0,     0,     0,     0,     0,   548,   549,    57,
      58,    59,    60,     0,   539,     0,    61,    62,     0,     0,
       0,    63,     0,     0,     0,     0,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,     0,     0,     0,
     375,     0,     0,    75,     0,     0,     0,     0,     0,    76,
      77,     0,    78,    79,    80,    81,   110,    82,    83,    84,
       0,     0,    54,    85,     0,    86,    87,     0,   572,     0,
       0,    56,    88,     0,     0,     0,     0,     0,     0,    57,
      58,    59,   111,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,   112,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    54,    55,    76,
      77,     0,     0,    79,    80,     0,    56,    82,    83,    84,
      54,    55,     0,   113,     0,    86,    87,   101,     0,    56,
       0,    61,    62,     0,     0,     0,    63,     0,     0,     0,
     101,     0,     0,     0,    61,    62,     0,     0,     0,    63,
       0,     0,    54,    55,     0,     0,     0,     0,    75,     0,
       0,    56,     0,     0,     0,     0,     0,    78,     0,     0,
      81,    75,   101,     0,     0,     0,    61,    62,   102,     0,
      78,    63,     0,    81,     0,     0,   108,    88,     0,     0,
       0,   158,     0,     0,     0,     0,     0,     0,     0,     0,
      88,    55,     0,    75,     0,     0,     0,     0,     0,     0,
       0,     0,    78,     0,     0,    81,     0,    57,    58,    59,
      60,     0,     0,   160,    61,    62,     0,     0,     0,    63,
       0,     0,    88,     0,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,     0,     0,     0,     0,     0,
       0,    75,     0,     0,     0,     0,     0,    76,    77,     0,
      78,    79,    80,    81,   140,    82,    83,    84,     0,     0,
       0,    85,     0,    86,    87,     0,     0,     0,     0,     0,
      88,     0,   127,    58,    59,   141,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
       0,     0,     0,     0,     0,     0,     0,     0,   142,   129,
       0,     0,    76,    77,   130,    54,    79,    80,     0,     0,
      82,    83,    84,     0,    56,     0,   131,     0,   132,   133,
       0,     0,    57,    58,    59,   111,     0,     0,     0,     0,
       0,     0,   216,   217,   218,   219,   220,   221,     0,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
     195,   196,   197,   198,   199,     0,     0,     0,     0,     0,
       0,     0,    76,    77,     0,     0,    79,    80,     0,     0,
      82,    83,    84,     0,     0,     0,   113,     0,    86,    87,
     391,     0,     0,     0,     0,    57,    58,    59,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   325,   200,
     201,   202,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,     0,     0,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    76,    77,     0,     0,    79,
      80,    11,     0,    82,    83,    84,     0,     0,   392,   113,
       0,    86,    87,    57,    58,    59,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    76,    77,     0,     0,    79,    80,     0,
       0,    82,    83,    84,     0,     0,     0,   113,     0,    86,
      87,   280,   127,    58,    59,   128,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   129,
       0,     0,    76,    77,   130,     0,    79,    80,     0,     0,
      82,    83,    84,     0,     0,     0,   281,     0,   132,   133,
     127,    58,    59,   128,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   129,     0,     0,
      76,    77,   130,     0,    79,    80,     0,     0,    82,    83,
      84,     0,     0,     0,   131,     0,   132,   133,    57,    58,
      59,   111,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    76,    77,
       0,     0,    79,    80,     0,     0,    82,    83,    84,     0,
       0,     0,   113,     0,    86,    87,    57,    58,    59,   111,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    76,    77,     0,     0,
      79,    80,     0,     0,    82,    83,    84,     0,     0,     0,
     113,     0,    86,   257
};

static const short int yycheck[] =
{
      33,   150,   410,   411,   132,   133,    19,    40,   394,    31,
      36,    88,    20,    18,    47,    48,    49,   117,   280,   281,
      48,   269,   270,    56,    18,    49,   274,   275,    20,    72,
     433,   434,   435,   110,    15,    16,    17,    24,    86,    87,
      49,    24,    96,    20,    22,    23,    31,    77,    78,    39,
      40,    41,    85,   107,    91,    88,    99,   100,    99,   100,
     145,    32,    33,    96,    32,    33,    34,    35,    36,    37,
      96,    99,   100,    91,    96,    99,   100,   110,    90,   112,
     113,   158,    96,   160,   132,   133,   119,    25,    96,   122,
      99,   100,   125,   107,   107,    47,    48,    49,   131,   104,
     130,   178,   488,    91,    96,   182,   183,   184,    98,   142,
     104,   260,    99,   100,    99,   100,    99,   100,    91,    96,
     107,    99,   100,   104,   107,   158,    48,   160,    99,   100,
      98,    99,   100,    91,   167,   168,   169,   170,   171,   172,
     173,   174,   175,    81,    82,   178,   246,   395,   276,   182,
     183,   184,    91,   561,   416,   417,   418,   205,   206,   207,
     208,   209,   565,   566,   567,   568,    99,   100,   245,    60,
     103,    32,    33,    34,    35,    36,    37,    99,   100,   131,
      48,    49,    26,    96,    47,    48,    49,    32,    33,    34,
     142,    35,   105,   226,   227,   228,   229,   230,   231,   585,
      90,    13,    14,    48,    95,    96,    32,    33,    34,   257,
     101,    20,   245,    25,   247,   248,   249,    32,    33,    34,
     111,   254,    48,    90,   272,   273,   259,    96,   276,    98,
     263,    99,   100,    91,    32,    33,    34,   128,    99,   100,
     389,    50,    51,    52,    53,    54,    97,   280,   281,     0,
     141,   203,   204,    49,    99,   100,   289,   290,    19,    39,
      26,    41,    39,    40,    41,    45,   299,    52,   131,    35,
     101,   102,   305,    99,   100,    48,    49,    57,    58,    59,
      96,    61,    62,    48,    99,   100,    96,   103,    48,    49,
      99,   100,   101,   103,   327,    99,   100,    32,    33,   332,
     333,    99,   100,    99,   100,   382,    19,    96,    88,    98,
      76,   263,    78,    19,    99,   100,   101,   269,   270,    48,
      49,    98,   274,   275,    99,   100,    99,   100,   280,   281,
      49,   222,   223,   224,    99,   100,   103,   289,   290,    99,
     100,    97,    96,   234,    98,   378,   379,   127,   300,   382,
     302,    19,   304,   386,    32,    33,    34,    35,    36,    37,
     140,    49,    29,   396,    99,   100,   146,    39,    40,    41,
      99,   100,    50,    51,    52,    53,    54,   410,   411,    97,
      99,   100,    91,   416,   417,   418,   419,   420,   421,   422,
     423,   424,   425,   426,   427,   428,   429,   430,   431,    50,
     263,    52,    33,    49,   437,    97,   439,   440,    97,   558,
      97,    99,   100,    97,   499,    97,    99,   100,   281,   504,
     505,    99,   100,   101,   107,   104,   289,   290,    97,   462,
     463,   211,    26,    27,    32,    33,    34,    35,    36,    37,
      97,    35,    96,   395,   396,    99,   100,    97,    99,   100,
     101,    59,    46,    99,   100,    97,    50,    51,   410,   411,
      96,    55,    98,    97,   416,   417,   418,   419,   420,   421,
     422,   423,   424,   425,   426,   427,   428,   429,   430,   431,
      97,    49,    76,    77,    78,   437,    32,    33,    34,    35,
      36,    37,    86,   526,   527,    89,   529,   530,    97,    49,
      98,    99,   100,    97,    97,   538,    39,    40,    41,    94,
      95,   544,   106,   546,    47,    32,    33,    34,    35,    36,
      37,   554,    99,   100,    52,    53,   103,   560,   561,   562,
     563,    99,   100,   396,   619,   620,   621,   622,   623,   624,
     625,   626,    49,   576,    97,    97,   579,   410,   411,    99,
     100,    21,    98,    99,   100,    49,   419,   420,   421,   422,
     423,   424,   425,   426,   427,   428,   429,   430,   431,    50,
      51,    52,    53,    54,   437,   608,    96,   610,    98,   612,
      49,   614,    99,   100,    32,    33,    34,    35,    36,    37,
      49,    97,    99,   100,   627,   628,   629,   630,   631,   632,
     633,   634,    97,    26,    27,    99,   100,    19,   560,   561,
     562,   563,    35,    73,    74,    75,    21,    49,    99,   100,
     101,    49,   103,    46,    18,    99,   100,    50,    51,   103,
      99,   100,    55,    48,   105,    50,    51,    52,    53,    54,
      99,   100,    49,    50,    51,    52,    53,    54,   103,    99,
     100,    99,   100,    96,    77,    98,   608,   107,   610,    49,
     612,    96,   614,    86,    33,    34,    89,    99,   100,    38,
      49,    99,   100,    49,    97,   627,   628,   629,   630,   631,
     632,   633,   634,   106,    99,   100,   101,    98,    99,   100,
      49,    60,    99,   100,   101,    33,    34,   560,   561,   562,
     563,    20,    40,    50,    51,    52,    53,    54,   105,    99,
     100,    50,    51,    52,    53,    54,    85,    39,    40,    41,
      99,   100,    60,    99,   100,    47,    95,    96,    15,    16,
      17,    30,   101,   102,   105,    50,    51,    52,    53,    54,
      99,   100,   111,    32,    96,   608,    98,   610,    97,   612,
      88,   614,    99,   100,   101,    27,   103,    95,    96,   128,
      99,   100,   101,   101,   627,   628,   629,   630,   631,   632,
     633,   634,   141,   111,    46,   103,    99,   100,    50,    51,
     103,    19,   103,    55,    99,   100,   101,    19,   103,   158,
     128,   160,    56,    57,    58,    19,   165,   166,    86,    56,
      57,    58,    96,   141,    98,    77,    19,   176,    18,    50,
      51,    52,    53,    54,    86,    96,    19,    89,    99,   100,
      50,    51,    52,    53,    54,    97,   195,   196,   197,   198,
     199,   200,   201,   202,   106,    18,   103,   101,   102,    50,
      51,    52,    53,    54,   101,   102,    19,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,    98,    99,   100,
     101,    98,    99,   100,    19,   234,    96,   236,    19,    99,
     100,   101,    50,    51,    52,    53,    54,    98,    99,   100,
      98,    99,   100,    19,   222,   223,   224,    98,    99,   100,
     101,    39,    40,    41,    91,    18,   234,    99,   100,    47,
     238,    39,    40,    41,    18,   107,   244,    18,    98,    47,
      26,    27,    28,    50,    51,    52,    53,    54,    96,    35,
      39,    99,   100,   101,    98,    97,    42,    43,    44,    45,
      46,    98,    99,   100,    50,    51,   305,   306,   307,    55,
      98,    99,   100,    97,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    98,    99,   100,   107,    96,
     101,    77,    99,   100,   101,    48,    96,    83,    84,   103,
      86,    87,    88,    89,    39,    91,    92,    93,    39,    40,
      41,    97,   103,    99,   100,    98,    47,    49,   103,   327,
     106,   329,    39,    40,    41,    98,    99,   100,   367,   103,
      47,    98,    99,   100,   103,   478,   375,   376,    98,    99,
     100,    98,    99,   100,   376,   487,    26,    27,   390,   386,
      50,    51,    52,    53,    54,    35,    99,   100,   101,    98,
      99,   100,   489,    43,    44,    45,    46,   256,   376,   244,
      50,    51,    98,    99,   100,    55,   233,   436,   386,    88,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    98,    99,   100,   370,    -1,    77,    98,    99,
     100,   101,   441,    83,    84,    -1,    86,    87,    88,    89,
      -1,    91,    92,    93,    98,    99,   100,    97,    -1,    99,
     100,    -1,    26,    27,    -1,    -1,   106,    -1,    -1,    -1,
      -1,    35,    -1,    -1,    -1,    -1,    -1,   476,   477,    43,
      44,    45,    46,    -1,   452,    -1,    50,    51,    -1,    -1,
      -1,    55,    -1,    -1,    -1,    -1,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    -1,    -1,    -1,
     478,    -1,    -1,    77,    -1,    -1,    -1,    -1,    -1,    83,
      84,    -1,    86,    87,    88,    89,    20,    91,    92,    93,
      -1,    -1,    26,    97,    -1,    99,   100,    -1,   537,    -1,
      -1,    35,   106,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,    27,    83,
      84,    -1,    -1,    87,    88,    -1,    35,    91,    92,    93,
      26,    27,    -1,    97,    -1,    99,   100,    46,    -1,    35,
      -1,    50,    51,    -1,    -1,    -1,    55,    -1,    -1,    -1,
      46,    -1,    -1,    -1,    50,    51,    -1,    -1,    -1,    55,
      -1,    -1,    26,    27,    -1,    -1,    -1,    -1,    77,    -1,
      -1,    35,    -1,    -1,    -1,    -1,    -1,    86,    -1,    -1,
      89,    77,    46,    -1,    -1,    -1,    50,    51,    97,    -1,
      86,    55,    -1,    89,    -1,    -1,   105,   106,    -1,    -1,
      -1,    97,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     106,    27,    -1,    77,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    86,    -1,    -1,    89,    -1,    43,    44,    45,
      46,    -1,    -1,    97,    50,    51,    -1,    -1,    -1,    55,
      -1,    -1,   106,    -1,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    -1,    -1,    -1,    -1,    -1,
      -1,    77,    -1,    -1,    -1,    -1,    -1,    83,    84,    -1,
      86,    87,    88,    89,    25,    91,    92,    93,    -1,    -1,
      -1,    97,    -1,    99,   100,    -1,    -1,    -1,    -1,    -1,
     106,    -1,    43,    44,    45,    46,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,    80,
      -1,    -1,    83,    84,    85,    26,    87,    88,    -1,    -1,
      91,    92,    93,    -1,    35,    -1,    97,    -1,    99,   100,
      -1,    -1,    43,    44,    45,    46,    -1,    -1,    -1,    -1,
      -1,    -1,    32,    33,    34,    35,    36,    37,    -1,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      50,    51,    52,    53,    54,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    83,    84,    -1,    -1,    87,    88,    -1,    -1,
      91,    92,    93,    -1,    -1,    -1,    97,    -1,    99,   100,
      38,    -1,    -1,    -1,    -1,    43,    44,    45,    46,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,    99,
     100,   101,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    -1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    83,    84,    -1,    -1,    87,
      88,    19,    -1,    91,    92,    93,    -1,    -1,    38,    97,
      -1,    99,   100,    43,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    83,    84,    -1,    -1,    87,    88,    -1,
      -1,    91,    92,    93,    -1,    -1,    -1,    97,    -1,    99,
     100,    42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,
      -1,    -1,    83,    84,    85,    -1,    87,    88,    -1,    -1,
      91,    92,    93,    -1,    -1,    -1,    97,    -1,    99,   100,
      43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,    -1,    -1,
      83,    84,    85,    -1,    87,    88,    -1,    -1,    91,    92,
      93,    -1,    -1,    -1,    97,    -1,    99,   100,    43,    44,
      45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    84,
      -1,    -1,    87,    88,    -1,    -1,    91,    92,    93,    -1,
      -1,    -1,    97,    -1,    99,   100,    43,    44,    45,    46,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    83,    84,    -1,    -1,
      87,    88,    -1,    -1,    91,    92,    93,    -1,    -1,    -1,
      97,    -1,    99,   100
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    19,   109,   110,   113,   114,   115,   117,   120,   130,
     131,   140,   143,    91,    91,    91,    91,    91,    91,    91,
      90,    90,    90,    13,    14,    25,   144,     0,    18,   104,
      18,   104,    15,    16,    17,   104,   121,    19,    19,    19,
      19,    97,    97,    97,    26,    27,    35,    43,    44,    45,
      46,    50,    51,    55,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    77,    83,    84,    86,    87,
      88,    89,    91,    92,    93,    97,    99,   100,   106,   147,
     152,   155,   156,   157,    28,    42,    97,   147,   151,   152,
     155,    46,    97,   145,   147,   152,   103,   147,   105,   145,
      20,    46,    71,    97,   118,   126,   127,   128,   148,   152,
     155,   145,    29,   124,   145,    33,   122,    43,    46,    80,
      85,    97,    99,   100,   137,   138,   139,   155,   156,   137,
      25,    46,    79,   132,   137,   155,    25,    81,    82,   141,
     142,    91,   116,   116,   116,   154,   155,   145,    97,   145,
      97,   145,   151,   145,   145,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,   104,   153,
     153,   153,    97,    97,    97,   147,   155,   157,   157,   145,
     148,   150,   152,   154,   155,    50,    51,    52,    53,    54,
      99,   100,   101,    99,   100,    56,    57,    58,   101,   102,
      59,    97,   151,   147,   151,   155,    32,    33,    34,    35,
      36,    37,    39,    40,    41,    21,    32,    33,    34,    35,
      36,    37,   151,    19,    20,   146,    21,   103,    18,   105,
     154,   151,   155,   103,    96,   128,   129,    73,    74,    75,
     149,   155,   105,   155,    30,   125,   105,   100,   155,    32,
     123,   145,   151,    97,   153,   137,   155,   139,   139,    99,
     100,   103,   101,   102,    99,   100,   101,   103,   145,   151,
      42,    97,   133,   137,   155,   103,    32,    33,    34,   136,
     136,   145,   103,   124,    96,    98,    98,    98,    36,    96,
      19,   154,    19,   154,    19,    47,    19,    19,   147,   147,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   147,
      86,   154,   154,   154,   154,    98,    98,    19,   107,    96,
     107,   107,    22,    23,   147,   147,   147,   147,   147,   147,
     147,   147,   156,   156,   157,   157,   157,   157,   157,   145,
      98,   147,   147,   147,   147,   147,   147,   151,   151,   151,
     147,   155,   155,   155,   155,   155,   155,    47,   144,   151,
     147,    76,    78,   111,   112,   152,    18,    20,    47,    72,
     127,   154,   128,   155,   155,   155,    18,   155,   103,    15,
     121,    38,    38,   155,   124,    19,    47,   137,    98,   138,
     156,   138,   156,   157,   157,   138,   156,   138,   156,   139,
      19,    47,   133,   133,   137,   155,    39,    40,    41,    47,
      32,    33,    34,    35,    36,    37,    32,    33,    34,    35,
      36,    37,   137,   155,   137,   155,    19,    19,    91,    18,
      18,    18,   155,   156,    98,   156,    98,   156,   147,   155,
     147,   147,    96,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    96,    96,    98,   105,    98,    98,    98,   152,
     155,   152,   155,   155,    98,   146,    97,    97,    96,   103,
     147,   111,   147,   155,    20,   154,   126,   155,   124,   122,
     125,   138,   156,   137,   155,    98,   132,   132,   137,   155,
      98,   133,   133,   133,   137,   155,   137,   155,   137,   155,
     137,   155,   137,   155,   137,   155,   137,   155,   137,   137,
     137,   137,   137,   137,   134,   134,    32,    33,   134,    32,
      33,   134,   141,   137,   155,   155,   147,    48,    48,   152,
     155,   155,   107,   107,    24,   107,    24,   107,   147,   147,
     112,   103,   103,    20,    31,   119,   119,   125,   123,   103,
      48,    48,   136,   136,    96,   155,   155,   155,   155,   103,
     103,   103,   147,   155,    98,    98,    96,   155,   155,    96,
      98,   155,   103,   103,   103,   124,   137,   132,   137,   155,
     137,   155,    94,    95,   135,   134,   134,   134,   134,    49,
      49,   155,   107,   107,   155,   125,    49,    49,    48,    49,
      48,    49,    48,    49,    48,    49,    98,    98,   103,   137,
     155,   137,   155,   137,   155,   137,   155,   136,   136,   136,
     136,   136,   136,   136,   136,   137,   155,   137,   155,   137,
     155,   137,   155,   137,   155,   137,   155,   137,   155,   137,
     155,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    49
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
# define YYLLOC_DEFAULT(Current, Rhs, N)		\
   ((Current).first_line   = (Rhs)[1].first_line,	\
    (Current).first_column = (Rhs)[1].first_column,	\
    (Current).last_line    = (Rhs)[N].last_line,	\
    (Current).last_column  = (Rhs)[N].last_column)
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
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short int *bottom, short int *top)
#else
static void
yy_stack_print (bottom, top)
    short int *bottom;
    short int *top;
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
  unsigned int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylno);
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

#if defined (YYMAXDEPTH) && YYMAXDEPTH == 0
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
  short int yyssa[YYINITDEPTH];
  short int *yyss = yyssa;
  register short int *yyssp;

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
	short int *yyss1 = yyss;


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
	short int *yyss1 = yyss;
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
#line 129 "src/mmlparse.y"
    { code_set_root(yyvsp[0].code); ;}
    break;

  case 3:
#line 130 "src/mmlparse.y"
    { code_set_root(yyvsp[0].code); ;}
    break;

  case 4:
#line 131 "src/mmlparse.y"
    { code_set_root(yyvsp[0].code); ;}
    break;

  case 5:
#line 132 "src/mmlparse.y"
    { code_set_root(yyvsp[0].code); ;}
    break;

  case 6:
#line 133 "src/mmlparse.y"
    { code_set_root(yyvsp[0].code); ;}
    break;

  case 7:
#line 134 "src/mmlparse.y"
    { code_set_root(yyvsp[0].code); ;}
    break;

  case 8:
#line 135 "src/mmlparse.y"
    { code_set_root(yyvsp[0].code); ;}
    break;

  case 9:
#line 136 "src/mmlparse.y"
    { code_set_root(yyvsp[0].code); ;}
    break;

  case 10:
#line 137 "src/mmlparse.y"
    { code_set_root(yyvsp[0].code); ;}
    break;

  case 11:
#line 138 "src/mmlparse.y"
    { code_set_root(yyvsp[0].code); ;}
    break;

  case 12:
#line 146 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_newsym_set1, 3,
            code_new_name(yyvsp[-3].name),                                       /* Name */
            code_new_inst(i_idxset_pseudo_new, 1,               /* index set */
               code_new_inst(i_bool_true, 0)),              
            yyvsp[-1].code);                                              /* initial set */
      ;}
    break;

  case 13:
#line 153 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_newsym_set1, 3,
            code_new_name(yyvsp[-6].name),                                       /* Name */
            yyvsp[-4].code,                                                 /* index set */
            yyvsp[-1].code);                                                      /* set */
      ;}
    break;

  case 14:
#line 159 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_newsym_set2, 3,
            code_new_name(yyvsp[-6].name),                                       /* Name */
            yyvsp[-4].code,                                                 /* index set */
            yyvsp[-1].code);                                   /* initial set_entry_list */
      ;}
    break;

  case 15:
#line 165 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_newsym_set2, 3,
            code_new_name(yyvsp[-5].name),                                       /* Name */
            code_new_inst(i_idxset_pseudo_new, 1,               /* index set */
               code_new_inst(i_bool_true, 0)),              
            yyvsp[-1].code);                                   /* initial set_entry_list */
      ;}
    break;

  case 16:
#line 175 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_entry_list_new, 1, yyvsp[0].code); ;}
    break;

  case 17:
#line 176 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_entry_list_add, 2, yyvsp[-2].code, yyvsp[0].code);
      ;}
    break;

  case 18:
#line 179 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_entry_list_subsets, 2, yyvsp[-3].code, yyvsp[-1].code);
      ;}
    break;

  case 19:
#line 182 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_entry_list_powerset, 1, yyvsp[-1].code);
      ;}
    break;

  case 20:
#line 188 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_entry, 2, yyvsp[-1].code, yyvsp[0].code); ;}
    break;

  case 21:
#line 197 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_newdef, 3,
            code_new_define(yyvsp[-6].def),
            code_new_inst(i_tuple_new, 1, yyvsp[-4].code),
            yyvsp[-1].code);
      ;}
    break;

  case 22:
#line 206 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_newdef, 3,
            code_new_define(yyvsp[-6].def),
            code_new_inst(i_tuple_new, 1, yyvsp[-4].code),
            yyvsp[-1].code);
      ;}
    break;

  case 23:
#line 215 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_newdef, 3,
            code_new_define(yyvsp[-6].def),
            code_new_inst(i_tuple_new, 1, yyvsp[-4].code),
            yyvsp[-1].code);
      ;}
    break;

  case 24:
#line 224 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_elem_list_new, 1, code_new_name(yyvsp[0].name));
      ;}
    break;

  case 25:
#line 227 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_elem_list_add, 2, yyvsp[-2].code, code_new_name(yyvsp[0].name));
      ;}
    break;

  case 26:
#line 237 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_newsym_para1, 4, code_new_name(yyvsp[-7].name), yyvsp[-5].code, yyvsp[-2].code, yyvsp[-1].code);
      ;}
    break;

  case 27:
#line 240 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_newsym_para2, 4, code_new_name(yyvsp[-7].name), yyvsp[-5].code, yyvsp[-2].code, yyvsp[-1].code);
      ;}
    break;

  case 28:
#line 243 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_newsym_para1, 4,
            code_new_name(yyvsp[-3].name),
            code_new_inst(i_idxset_pseudo_new, 1, code_new_inst(i_bool_true, 0)),
            yyvsp[-1].code,
            code_new_inst(i_nop, 0));
      ;}
    break;

  case 29:
#line 252 "src/mmlparse.y"
    { yyval.code = yyvsp[0].code; ;}
    break;

  case 30:
#line 253 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_entry_list_new, 1,
            code_new_inst(i_entry, 2, code_new_inst(i_tuple_empty, 0), yyvsp[0].code));
      ;}
    break;

  case 31:
#line 260 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_nop, 0); ;}
    break;

  case 32:
#line 261 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_entry, 2, code_new_inst(i_tuple_empty, 0), yyvsp[0].code); ;}
    break;

  case 33:
#line 269 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_newsym_var, 7,
            code_new_name(yyvsp[-9].name), yyvsp[-7].code, yyvsp[-5].code, yyvsp[-4].code, yyvsp[-3].code, yyvsp[-2].code, yyvsp[-1].code);
      ;}
    break;

  case 34:
#line 273 "src/mmlparse.y"
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

  case 35:
#line 282 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_newsym_var, 7,
            code_new_name(yyvsp[-6].name),
            code_new_inst(i_idxset_pseudo_new, 1,
               code_new_inst(i_bool_true, 0)),              
            yyvsp[-5].code, yyvsp[-4].code, yyvsp[-3].code, yyvsp[-2].code, yyvsp[-1].code);
      ;}
    break;

  case 36:
#line 289 "src/mmlparse.y"
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

  case 37:
#line 302 "src/mmlparse.y"
    { yyval.code = code_new_varclass(VAR_CON); ;}
    break;

  case 38:
#line 303 "src/mmlparse.y"
    { yyval.code = code_new_varclass(VAR_CON); ;}
    break;

  case 39:
#line 304 "src/mmlparse.y"
    { yyval.code = code_new_varclass(VAR_INT); ;}
    break;

  case 40:
#line 309 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_bound_new, 1, code_new_numb(numb_new_integer(0)));
      ;}
    break;

  case 41:
#line 312 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bound_new, 1, yyvsp[0].code); ;}
    break;

  case 42:
#line 313 "src/mmlparse.y"
    { yyval.code = code_new_bound(BOUND_MINUS_INFTY); ;}
    break;

  case 43:
#line 317 "src/mmlparse.y"
    { yyval.code = code_new_bound(BOUND_INFTY); ;}
    break;

  case 44:
#line 318 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bound_new, 1, yyvsp[0].code); ;}
    break;

  case 45:
#line 319 "src/mmlparse.y"
    { yyval.code = code_new_bound(BOUND_INFTY); ;}
    break;

  case 46:
#line 323 "src/mmlparse.y"
    { yyval.code = code_new_numb(numb_new_integer(0)); ;}
    break;

  case 47:
#line 324 "src/mmlparse.y"
    { yyval.code = yyvsp[0].code; ;}
    break;

  case 48:
#line 328 "src/mmlparse.y"
    { yyval.code = code_new_numb(numb_new_integer(0)); ;}
    break;

  case 49:
#line 329 "src/mmlparse.y"
    { yyval.code = yyvsp[0].code; ;}
    break;

  case 50:
#line 337 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_entry_list_new, 1, yyvsp[0].code); ;}
    break;

  case 51:
#line 338 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_entry_list_add, 2, yyvsp[-2].code, yyvsp[0].code);
      ;}
    break;

  case 52:
#line 341 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_read, 1, yyvsp[0].code); ;}
    break;

  case 53:
#line 342 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_list_matrix, 2, yyvsp[-1].code, yyvsp[0].code); ;}
    break;

  case 54:
#line 346 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_entry, 2, yyvsp[-1].code, yyvsp[0].code); ;}
    break;

  case 55:
#line 350 "src/mmlparse.y"
    { yyval.code = yyvsp[-1].code; ;}
    break;

  case 56:
#line 354 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_matrix_list_new, 2, yyvsp[-2].code, yyvsp[-1].code);
      ;}
    break;

  case 57:
#line 357 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_matrix_list_add, 3, yyvsp[-3].code, yyvsp[-2].code, yyvsp[-1].code);
      ;}
    break;

  case 58:
#line 369 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_object_min, 2, code_new_name(yyvsp[-3].name), yyvsp[-1].code);
      ;}
    break;

  case 59:
#line 372 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_object_max, 2, code_new_name(yyvsp[-3].name), yyvsp[-1].code);
      ;}
    break;

  case 60:
#line 382 "src/mmlparse.y"
    {
        yyval.code = code_new_inst(i_subto, 2, code_new_name(yyvsp[-3].name), yyvsp[-1].code);
     ;}
    break;

  case 61:
#line 388 "src/mmlparse.y"
    {
        yyval.code = code_new_inst(i_constraint, 4, yyvsp[-3].code, yyvsp[-2].code, yyvsp[-1].code, code_new_bits(yyvsp[0].bits));
     ;}
    break;

  case 62:
#line 391 "src/mmlparse.y"
    {
        yyval.code = code_new_inst(i_constraint, 4, yyvsp[-3].code, yyvsp[-2].code,
           code_new_inst(i_term_expr, 1, yyvsp[-1].code),
           code_new_bits(yyvsp[0].bits));
     ;}
    break;

  case 63:
#line 396 "src/mmlparse.y"
    {
        yyval.code = code_new_inst(i_constraint, 4,
           code_new_inst(i_term_expr, 1, yyvsp[-3].code),
           yyvsp[-2].code, yyvsp[-1].code, code_new_bits(yyvsp[0].bits));
     ;}
    break;

  case 64:
#line 401 "src/mmlparse.y"
    { 
        yyval.code = code_new_inst(i_constraint, 4,
           code_new_inst(i_term_expr, 1, yyvsp[-3].code),
           yyvsp[-2].code,
           code_new_inst(i_term_expr, 1, yyvsp[-1].code),
           code_new_bits(yyvsp[0].bits));
     ;}
    break;

  case 65:
#line 408 "src/mmlparse.y"
    {
        yyval.code = code_new_inst(i_rangeconst, 6, yyvsp[-5].code, yyvsp[-3].code, yyvsp[-1].code, yyvsp[-4].code,
           code_new_contype(CON_RHS), code_new_bits(yyvsp[0].bits)); 
     ;}
    break;

  case 66:
#line 412 "src/mmlparse.y"
    {
        yyval.code = code_new_inst(i_rangeconst, 6, yyvsp[-5].code,
           code_new_inst(i_term_expr, 1, yyvsp[-3].code), yyvsp[-1].code, yyvsp[-4].code,
           code_new_contype(CON_RHS), code_new_bits(yyvsp[0].bits)); 
     ;}
    break;

  case 67:
#line 417 "src/mmlparse.y"
    {
        yyval.code = code_new_inst(i_rangeconst, 6, yyvsp[-1].code, yyvsp[-3].code, yyvsp[-5].code, yyvsp[-4].code,
           code_new_contype(CON_LHS), code_new_bits(yyvsp[0].bits)); 
     ;}
    break;

  case 68:
#line 421 "src/mmlparse.y"
    {
        yyval.code = code_new_inst(i_rangeconst, 6, yyvsp[-1].code,
           code_new_inst(i_term_expr, 1, yyvsp[-3].code),
           yyvsp[-5].code, yyvsp[-4].code,
           code_new_contype(CON_LHS), code_new_bits(yyvsp[0].bits)); 
     ;}
    break;

  case 69:
#line 427 "src/mmlparse.y"
    {
        yyval.code = code_new_inst(i_forall, 2, yyvsp[-2].code, yyvsp[0].code);
     ;}
    break;

  case 70:
#line 430 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_expr_if, 3, yyvsp[-5].code, yyvsp[-3].code, yyvsp[-1].code);
      ;}
    break;

  case 71:
#line 433 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_vif_else, 7, yyvsp[-9].code, yyvsp[-7].code, yyvsp[-6].code, yyvsp[-5].code, yyvsp[-3].code, yyvsp[-2].code, yyvsp[-1].code);
      ;}
    break;

  case 72:
#line 436 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_vif_else, 7, yyvsp[-9].code,
            code_new_inst(i_term_expr, 1, yyvsp[-7].code),
            yyvsp[-6].code, yyvsp[-5].code, yyvsp[-3].code, yyvsp[-2].code, yyvsp[-1].code);
      ;}
    break;

  case 73:
#line 441 "src/mmlparse.y"
    { 
         yyval.code = code_new_inst(i_vif_else, 7, yyvsp[-9].code, yyvsp[-7].code, yyvsp[-6].code,
            code_new_inst(i_term_expr, 1, yyvsp[-5].code),
            yyvsp[-3].code, yyvsp[-2].code, yyvsp[-1].code);
      ;}
    break;

  case 74:
#line 446 "src/mmlparse.y"
    { 
         yyval.code = code_new_inst(i_vif_else, 7, yyvsp[-9].code, yyvsp[-7].code, yyvsp[-6].code, yyvsp[-5].code,
            code_new_inst(i_term_expr, 1, yyvsp[-3].code),
            yyvsp[-2].code, yyvsp[-1].code);
      ;}
    break;

  case 75:
#line 451 "src/mmlparse.y"
    { 
         yyval.code = code_new_inst(i_vif_else, 7, yyvsp[-9].code, yyvsp[-7].code, yyvsp[-6].code, yyvsp[-5].code, yyvsp[-3].code, yyvsp[-2].code,
            code_new_inst(i_term_expr, 1, yyvsp[-1].code));
      ;}
    break;

  case 76:
#line 455 "src/mmlparse.y"
    { /* ??? This is an error */
         yyval.code = code_new_inst(i_vif_else, 7, yyvsp[-9].code,
            code_new_inst(i_term_expr, 1, yyvsp[-7].code),
            yyvsp[-6].code,
            code_new_inst(i_term_expr, 1, yyvsp[-5].code),
            yyvsp[-3].code, yyvsp[-2].code, yyvsp[-1].code);
      ;}
    break;

  case 77:
#line 462 "src/mmlparse.y"
    { 
         yyval.code = code_new_inst(i_vif_else, 7, yyvsp[-9].code,
            code_new_inst(i_term_expr, 1, yyvsp[-7].code),
            yyvsp[-6].code, yyvsp[-5].code,
            code_new_inst(i_term_expr, 1, yyvsp[-3].code),
            yyvsp[-2].code, yyvsp[-1].code);
      ;}
    break;

  case 78:
#line 469 "src/mmlparse.y"
    { 
         yyval.code = code_new_inst(i_vif_else, 7, yyvsp[-9].code,
            code_new_inst(i_term_expr, 1, yyvsp[-7].code),
            yyvsp[-6].code, yyvsp[-5].code, yyvsp[-3].code, yyvsp[-2].code,
            code_new_inst(i_term_expr, 1, yyvsp[-1].code));
      ;}
    break;

  case 79:
#line 475 "src/mmlparse.y"
    { 
         yyval.code = code_new_inst(i_vif_else, 7, yyvsp[-9].code, yyvsp[-7].code, yyvsp[-6].code,
            code_new_inst(i_term_expr, 1, yyvsp[-5].code),
            code_new_inst(i_term_expr, 1, yyvsp[-3].code),
            yyvsp[-2].code, yyvsp[-1].code);
      ;}
    break;

  case 80:
#line 481 "src/mmlparse.y"
    { 
         yyval.code = code_new_inst(i_vif_else, 7, yyvsp[-9].code, yyvsp[-7].code, yyvsp[-6].code,
            code_new_inst(i_term_expr, 1, yyvsp[-5].code),
            yyvsp[-3].code, yyvsp[-2].code,
            code_new_inst(i_term_expr, 1, yyvsp[-1].code));
      ;}
    break;

  case 81:
#line 487 "src/mmlparse.y"
    { /* ??? This is an error */
         yyval.code = code_new_inst(i_vif_else, 7, yyvsp[-9].code, yyvsp[-7].code, yyvsp[-6].code, yyvsp[-5].code,
            code_new_inst(i_term_expr, 1, yyvsp[-3].code), yyvsp[-2].code,
            code_new_inst(i_term_expr, 1, yyvsp[-1].code));
      ;}
    break;

  case 82:
#line 492 "src/mmlparse.y"
    { /* ??? This is an error */
         yyval.code = code_new_inst(i_vif_else, 7, yyvsp[-9].code,
            code_new_inst(i_term_expr, 1, yyvsp[-7].code),
            yyvsp[-6].code,
            code_new_inst(i_term_expr, 1, yyvsp[-5].code),
            code_new_inst(i_term_expr, 1, yyvsp[-3].code),
            yyvsp[-2].code, yyvsp[-1].code);
      ;}
    break;

  case 83:
#line 500 "src/mmlparse.y"
    { /* ??? This is an error */
         yyval.code = code_new_inst(i_vif_else, 7, yyvsp[-9].code,
            code_new_inst(i_term_expr, 1, yyvsp[-7].code),
            yyvsp[-6].code,
            code_new_inst(i_term_expr, 1, yyvsp[-5].code),
            yyvsp[-3].code, yyvsp[-2].code,
            code_new_inst(i_term_expr, 1, yyvsp[-1].code));
      ;}
    break;

  case 84:
#line 508 "src/mmlparse.y"
    { /* ??? This is an error */
         yyval.code = code_new_inst(i_vif_else, 7, yyvsp[-9].code,
            code_new_inst(i_term_expr, 1, yyvsp[-7].code),
            yyvsp[-6].code, yyvsp[-5].code,
            code_new_inst(i_term_expr, 1, yyvsp[-3].code),
            yyvsp[-2].code,
            code_new_inst(i_term_expr, 1, yyvsp[-1].code));
      ;}
    break;

  case 85:
#line 516 "src/mmlparse.y"
    { /* ??? This is an error */
         yyval.code = code_new_inst(i_vif_else, 7, yyvsp[-9].code, yyvsp[-7].code, yyvsp[-6].code,
            code_new_inst(i_term_expr, 1, yyvsp[-5].code),
            code_new_inst(i_term_expr, 1, yyvsp[-3].code),
            yyvsp[-2].code,
            code_new_inst(i_term_expr, 1, yyvsp[-1].code));
      ;}
    break;

  case 86:
#line 523 "src/mmlparse.y"
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

  case 87:
#line 533 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_vif, 4, yyvsp[-5].code, yyvsp[-3].code, yyvsp[-2].code, yyvsp[-1].code);
      ;}
    break;

  case 88:
#line 536 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_vif, 4, yyvsp[-5].code, code_new_inst(i_term_expr, 1, yyvsp[-3].code), yyvsp[-2].code, yyvsp[-1].code);
      ;}
    break;

  case 89:
#line 539 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_vif, 4, yyvsp[-5].code, yyvsp[-3].code, yyvsp[-2].code, code_new_inst(i_term_expr, 1, yyvsp[-1].code));
      ;}
    break;

  case 90:
#line 542 "src/mmlparse.y"
    { /* ??? This is an error */
         yyval.code = code_new_inst(i_vif, 4, yyvsp[-5].code,
            code_new_inst(i_term_expr, 1, yyvsp[-3].code), yyvsp[-2].code, code_new_inst(i_term_expr, 1, yyvsp[-1].code));
      ;}
    break;

  case 91:
#line 549 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_vbool_ne, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 92:
#line 550 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_vbool_ne, 2, code_new_inst(i_term_expr, 1, yyvsp[-2].code), yyvsp[0].code);
      ;}
    break;

  case 93:
#line 553 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_vbool_ne, 2, yyvsp[-2].code, code_new_inst(i_term_expr, 1, yyvsp[0].code));
      ;}
    break;

  case 94:
#line 556 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_vbool_eq, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 95:
#line 557 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_vbool_eq, 2, code_new_inst(i_term_expr, 1, yyvsp[-2].code), yyvsp[0].code);
      ;}
    break;

  case 96:
#line 560 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_vbool_eq, 2, yyvsp[-2].code, code_new_inst(i_term_expr, 1, yyvsp[0].code));
      ;}
    break;

  case 97:
#line 563 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_vbool_le, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 98:
#line 564 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_vbool_le, 2, code_new_inst(i_term_expr, 1, yyvsp[-2].code), yyvsp[0].code);
      ;}
    break;

  case 99:
#line 567 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_vbool_le, 2, yyvsp[-2].code, code_new_inst(i_term_expr, 1, yyvsp[0].code));
      ;}
    break;

  case 100:
#line 570 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_vbool_ge, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 101:
#line 571 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_vbool_ge, 2, code_new_inst(i_term_expr, 1, yyvsp[-2].code), yyvsp[0].code);
      ;}
    break;

  case 102:
#line 574 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_vbool_ge, 2, yyvsp[-2].code, code_new_inst(i_term_expr, 1, yyvsp[0].code));
      ;}
    break;

  case 103:
#line 577 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_vbool_lt, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 104:
#line 578 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_vbool_lt, 2, code_new_inst(i_term_expr, 1, yyvsp[-2].code), yyvsp[0].code);
      ;}
    break;

  case 105:
#line 581 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_vbool_lt, 2, yyvsp[-2].code, code_new_inst(i_term_expr, 1, yyvsp[0].code));
      ;}
    break;

  case 106:
#line 584 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_vbool_gt, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 107:
#line 585 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_vbool_gt, 2, code_new_inst(i_term_expr, 1, yyvsp[-2].code), yyvsp[0].code);
      ;}
    break;

  case 108:
#line 588 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_vbool_gt, 2, yyvsp[-2].code, code_new_inst(i_term_expr, 1, yyvsp[0].code));
      ;}
    break;

  case 109:
#line 591 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_vbool_and, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 110:
#line 592 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_vbool_or,  2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 111:
#line 593 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_vbool_xor, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 112:
#line 594 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_vbool_not, 1, yyvsp[0].code);; ;}
    break;

  case 113:
#line 595 "src/mmlparse.y"
    { yyval.code = yyvsp[-1].code; ;}
    break;

  case 114:
#line 599 "src/mmlparse.y"
    { yyval.bits = 0; ;}
    break;

  case 115:
#line 600 "src/mmlparse.y"
    { yyval.bits = yyvsp[-2].bits | yyvsp[0].bits; ;}
    break;

  case 116:
#line 604 "src/mmlparse.y"
    { yyval.bits = LP_FLAG_CON_SCALE; ;}
    break;

  case 117:
#line 605 "src/mmlparse.y"
    { yyval.bits = LP_FLAG_CON_SEPAR; ;}
    break;

  case 118:
#line 609 "src/mmlparse.y"
    { yyval.code = code_new_contype(CON_RHS); ;}
    break;

  case 119:
#line 610 "src/mmlparse.y"
    { yyval.code = code_new_contype(CON_LHS); ;}
    break;

  case 120:
#line 611 "src/mmlparse.y"
    { yyval.code = code_new_contype(CON_EQUAL); ;}
    break;

  case 121:
#line 615 "src/mmlparse.y"
    { yyval.code = yyvsp[0].code; ;}
    break;

  case 122:
#line 616 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_term_add, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 123:
#line 617 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_term_sub, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 124:
#line 618 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_term_const, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 125:
#line 619 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_term_sub, 2, yyvsp[-2].code, code_new_inst(i_term_expr, 1, yyvsp[0].code));
      ;}
    break;

  case 126:
#line 622 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_term_const, 2, yyvsp[0].code, yyvsp[-2].code); ;}
    break;

  case 127:
#line 623 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_term_sub, 2,
            code_new_inst(i_term_expr, 1, yyvsp[-2].code),
            yyvsp[0].code);
      ;}
    break;

  case 128:
#line 631 "src/mmlparse.y"
    { yyval.code = yyvsp[0].code; ;}
    break;

  case 129:
#line 632 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_term_coeff, 2, yyvsp[-2].code, yyvsp[0].code); /*???*/ ;}
    break;

  case 130:
#line 633 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_term_coeff, 2, yyvsp[-2].code,
            code_new_inst(i_expr_div, 2, code_new_numb(numb_new_integer(1)), yyvsp[0].code));
      ;}
    break;

  case 131:
#line 637 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_term_coeff, 2, yyvsp[0].code, yyvsp[-2].code); ;}
    break;

  case 132:
#line 641 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_symbol_deref, 2, code_new_symbol(yyvsp[-1].sym), yyvsp[0].code);
      ;}
    break;

  case 133:
#line 644 "src/mmlparse.y"
    { yyval.code = yyvsp[0].code; ;}
    break;

  case 134:
#line 645 "src/mmlparse.y"
    { 
         yyval.code = code_new_inst(i_term_coeff, 2, yyvsp[0].code, code_new_numb(numb_new_integer(-1)));
      ;}
    break;

  case 135:
#line 648 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_vabs, 1, yyvsp[-1].code); ;}
    break;

  case 136:
#line 649 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_term_sum, 2, yyvsp[-2].code, yyvsp[0].code);
      ;}
    break;

  case 137:
#line 653 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_expr_if, 3, yyvsp[-5].code, yyvsp[-3].code, yyvsp[-1].code);
      ;}
    break;

  case 138:
#line 656 "src/mmlparse.y"
    { yyval.code = yyvsp[-1].code; ;}
    break;

  case 139:
#line 664 "src/mmlparse.y"
    {
        yyval.code = code_new_inst(i_sos, 2, code_new_name(yyvsp[-3].name), yyvsp[-1].code);
     ;}
    break;

  case 140:
#line 670 "src/mmlparse.y"
    {
        yyval.code = code_new_inst(i_soset, 3, yyvsp[0].code, yyvsp[-3].code, yyvsp[-2].code);
     ;}
    break;

  case 141:
#line 673 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_forall, 2, yyvsp[-2].code, yyvsp[0].code);
      ;}
    break;

  case 142:
#line 679 "src/mmlparse.y"
    { yyval.code = code_new_numb(numb_new_integer(1)); ;}
    break;

  case 143:
#line 680 "src/mmlparse.y"
    { yyval.code = code_new_numb(numb_new_integer(1)); ;}
    break;

  case 144:
#line 681 "src/mmlparse.y"
    { yyval.code = code_new_numb(numb_new_integer(2)); ;}
    break;

  case 145:
#line 689 "src/mmlparse.y"
    { yyval.code = yyvsp[-1].code; ;}
    break;

  case 146:
#line 693 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_print, 1, yyvsp[0].code); ;}
    break;

  case 147:
#line 694 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_print, 1, yyvsp[0].code); ;}
    break;

  case 148:
#line 695 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_print, 1, yyvsp[0].code); ;}
    break;

  case 149:
#line 696 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_check, 1, yyvsp[0].code); ;}
    break;

  case 150:
#line 697 "src/mmlparse.y"
    {
        yyval.code = code_new_inst(i_forall, 2, yyvsp[-2].code, yyvsp[0].code);
     ;}
    break;

  case 151:
#line 707 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_idxset_new, 3, yyvsp[-3].code, yyvsp[-1].code, yyvsp[0].code);
      ;}
    break;

  case 152:
#line 710 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_idxset_new, 3,
            code_new_inst(i_tuple_empty, 0), yyvsp[-1].code, yyvsp[0].code);
      ;}
    break;

  case 153:
#line 717 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bool_true, 0); ;}
    break;

  case 154:
#line 718 "src/mmlparse.y"
    { yyval.code = yyvsp[0].code; ;}
    break;

  case 155:
#line 722 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_symbol_deref, 2, code_new_symbol(yyvsp[-1].sym), yyvsp[0].code);
      ;}
    break;

  case 156:
#line 725 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_define_deref, 2,
            code_new_define(yyvsp[-3].def),
            code_new_inst(i_tuple_new, 1, yyvsp[-1].code));
      ;}
    break;

  case 157:
#line 730 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_set_empty, 1, code_new_size(0)); ;}
    break;

  case 158:
#line 731 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_set_range2, 3, yyvsp[-5].code, yyvsp[-3].code, yyvsp[-1].code);
      ;}
    break;

  case 159:
#line 734 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_set_range2, 3, yyvsp[-3].code, yyvsp[-1].code, code_new_numb(numb_new_integer(1)));
      ;}
    break;

  case 160:
#line 737 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_set_range, 3, yyvsp[-5].code, yyvsp[-3].code, yyvsp[-1].code);
      ;}
    break;

  case 161:
#line 740 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_set_range, 3, yyvsp[-3].code, yyvsp[-1].code, code_new_numb(numb_new_integer(1)));
      ;}
    break;

  case 162:
#line 743 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_set_union2, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 163:
#line 744 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_set_union, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 164:
#line 745 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_set_union, 2, yyvsp[-2].code, yyvsp[0].code);
      ;}
    break;

  case 165:
#line 748 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_set_sdiff, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 166:
#line 749 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_set_minus, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 167:
#line 750 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_set_minus, 2, yyvsp[-2].code, yyvsp[0].code);
      ;}
    break;

  case 168:
#line 753 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_set_cross, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 169:
#line 754 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_set_cross, 2, yyvsp[-2].code, yyvsp[0].code);
      ;}
    break;

  case 170:
#line 757 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_set_inter, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 171:
#line 758 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_set_inter2, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 172:
#line 759 "src/mmlparse.y"
    { yyval.code = yyvsp[-1].code; ;}
    break;

  case 173:
#line 760 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_set_new_tuple, 1, yyvsp[-1].code); ;}
    break;

  case 174:
#line 761 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_set_new_elem, 1, yyvsp[-1].code); ;}
    break;

  case 175:
#line 762 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_set_idxset, 1, yyvsp[-1].code); ;}
    break;

  case 176:
#line 763 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_set_expr, 2, yyvsp[-3].code, yyvsp[-1].code); ;}
    break;

  case 177:
#line 764 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_set_expr, 2, yyvsp[-3].code, yyvsp[-1].code); ;}
    break;

  case 178:
#line 765 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_set_proj, 2, yyvsp[-3].code, yyvsp[-1].code);
       ;}
    break;

  case 179:
#line 768 "src/mmlparse.y"
    {
          yyval.code = code_new_inst(i_set_indexset, 1, code_new_symbol(yyvsp[-1].sym));
       ;}
    break;

  case 180:
#line 771 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_expr_if, 3, yyvsp[-5].code, yyvsp[-3].code, yyvsp[-1].code);
      ;}
    break;

  case 181:
#line 777 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_read_new, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 182:
#line 778 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_read_param, 2, yyvsp[-1].code, yyvsp[0].code); ;}
    break;

  case 183:
#line 782 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_read_skip, 1, yyvsp[0].code); ;}
    break;

  case 184:
#line 783 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_read_use, 1, yyvsp[0].code); ;}
    break;

  case 185:
#line 784 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_read_comment, 1, yyvsp[0].code); ;}
    break;

  case 186:
#line 788 "src/mmlparse.y"
    {
          yyval.code = code_new_inst(i_tuple_list_new, 1, yyvsp[0].code);
       ;}
    break;

  case 187:
#line 791 "src/mmlparse.y"
    {
          yyval.code = code_new_inst(i_tuple_list_add, 2, yyvsp[-2].code, yyvsp[0].code);
       ;}
    break;

  case 188:
#line 794 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_read, 1, yyvsp[0].code); ;}
    break;

  case 189:
#line 798 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bool_eq, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 190:
#line 799 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bool_ne, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 191:
#line 800 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bool_gt, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 192:
#line 801 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bool_ge, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 193:
#line 802 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bool_lt, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 194:
#line 803 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bool_le, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 195:
#line 804 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bool_seq, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 196:
#line 805 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bool_sneq, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 197:
#line 806 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bool_subs, 2, yyvsp[0].code, yyvsp[-2].code); ;}
    break;

  case 198:
#line 807 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bool_sseq, 2, yyvsp[0].code, yyvsp[-2].code); ;}
    break;

  case 199:
#line 808 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bool_subs, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 200:
#line 809 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bool_sseq, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 201:
#line 810 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bool_and, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 202:
#line 811 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bool_or,  2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 203:
#line 812 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bool_xor, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 204:
#line 813 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bool_not, 1, yyvsp[0].code); ;}
    break;

  case 205:
#line 814 "src/mmlparse.y"
    { yyval.code = yyvsp[-1].code; ;}
    break;

  case 206:
#line 815 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bool_is_elem, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 207:
#line 816 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_bool_exists, 1, yyvsp[-1].code); ;}
    break;

  case 208:
#line 820 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_tuple_empty, 0); ;}
    break;

  case 209:
#line 821 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_tuple_new, 1, yyvsp[-1].code);  ;}
    break;

  case 210:
#line 825 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_tuple_empty, 0);
      ;}
    break;

  case 211:
#line 828 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_tuple_new, 1, yyvsp[-1].code);
      ;}
    break;

  case 212:
#line 834 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_elem_list_new, 1, yyvsp[0].code);
      ;}
    break;

  case 213:
#line 837 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_elem_list_add, 2, yyvsp[-2].code, yyvsp[0].code);
      ;}
    break;

  case 214:
#line 843 "src/mmlparse.y"
    { yyval.code = yyvsp[0].code; ;}
    break;

  case 215:
#line 844 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_expr_add, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 216:
#line 845 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_expr_sub, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 217:
#line 849 "src/mmlparse.y"
    { yyval.code = yyvsp[0].code; ;}
    break;

  case 218:
#line 850 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_expr_mul, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 219:
#line 851 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_expr_div, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 220:
#line 852 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_expr_mod, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 221:
#line 853 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_expr_intdiv, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 222:
#line 854 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_expr_pow, 2, yyvsp[-2].code, yyvsp[0].code); ;}
    break;

  case 223:
#line 858 "src/mmlparse.y"
    { yyval.code = code_new_numb(yyvsp[0].numb); ;}
    break;

  case 224:
#line 859 "src/mmlparse.y"
    { yyval.code = code_new_strg(yyvsp[0].strg);  ;}
    break;

  case 225:
#line 860 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_local_deref, 1, code_new_name(yyvsp[0].name));
      ;}
    break;

  case 226:
#line 863 "src/mmlparse.y"
    { 
         yyval.code = code_new_inst(i_symbol_deref, 2, code_new_symbol(yyvsp[-1].sym), yyvsp[0].code);
      ;}
    break;

  case 227:
#line 866 "src/mmlparse.y"
    { 
         yyval.code = code_new_inst(i_symbol_deref, 2, code_new_symbol(yyvsp[-1].sym), yyvsp[0].code);
      ;}
    break;

  case 228:
#line 869 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_define_deref, 2,
            code_new_define(yyvsp[-3].def),
            code_new_inst(i_tuple_new, 1, yyvsp[-1].code));
      ;}
    break;

  case 229:
#line 874 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_define_deref, 2,
            code_new_define(yyvsp[-3].def),
            code_new_inst(i_tuple_new, 1, yyvsp[-1].code));
      ;}
    break;

  case 230:
#line 879 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_expr_fac, 1, yyvsp[-1].code); ;}
    break;

  case 231:
#line 880 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_expr_card, 1, yyvsp[-1].code); ;}
    break;

  case 232:
#line 881 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_expr_abs, 1, yyvsp[-1].code); ;}
    break;

  case 233:
#line 882 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_expr_sgn, 1, yyvsp[-1].code); ;}
    break;

  case 234:
#line 883 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_expr_floor, 1, yyvsp[-1].code); ;}
    break;

  case 235:
#line 884 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_expr_ceil, 1, yyvsp[-1].code); ;}
    break;

  case 236:
#line 885 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_expr_log, 1, yyvsp[-1].code); ;}
    break;

  case 237:
#line 886 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_expr_ln, 1, yyvsp[-1].code); ;}
    break;

  case 238:
#line 887 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_expr_exp, 1, yyvsp[-1].code); ;}
    break;

  case 239:
#line 888 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_expr_sqrt, 1, yyvsp[-1].code); ;}
    break;

  case 240:
#line 890 "src/mmlparse.y"
    { yyval.code = yyvsp[0].code; ;}
    break;

  case 241:
#line 891 "src/mmlparse.y"
    { yyval.code = code_new_inst(i_expr_neg, 1, yyvsp[0].code); ;}
    break;

  case 242:
#line 892 "src/mmlparse.y"
    { yyval.code = yyvsp[-1].code; ;}
    break;

  case 243:
#line 893 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_expr_rand, 2, yyvsp[-3].code, yyvsp[-1].code);
      ;}
    break;

  case 244:
#line 896 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_expr_if, 3, yyvsp[-5].code, yyvsp[-3].code, yyvsp[-1].code);
      ;}
    break;

  case 245:
#line 899 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_expr_min, 2, yyvsp[-2].code, yyvsp[0].code);
      ;}
    break;

  case 246:
#line 902 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_expr_max, 2, yyvsp[-2].code, yyvsp[0].code);
      ;}
    break;

  case 247:
#line 905 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_expr_sum, 2, yyvsp[-2].code, yyvsp[0].code);
      ;}
    break;

  case 248:
#line 908 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_expr_min2, 1, yyvsp[-1].code);
      ;}
    break;

  case 249:
#line 911 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_expr_max2, 1, yyvsp[-1].code);
      ;}
    break;

  case 250:
#line 914 "src/mmlparse.y"
    {
         yyval.code = code_new_inst(i_expr_ord, 3, yyvsp[-5].code, yyvsp[-3].code, yyvsp[-1].code);
      ;}
    break;


    }

/* Line 1010 of yacc.c.  */
#line 3644 "src/mmlparse.c"

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
	  const char* yyprefix;
	  char *yymsg;
	  int yyx;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 0;

	  yyprefix = ", expecting ";
	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		yysize += yystrlen (yyprefix) + yystrlen (yytname [yyx]);
		yycount += 1;
		if (yycount == 5)
		  {
		    yysize = 0;
		    break;
		  }
	      }
	  yysize += (sizeof ("syntax error, unexpected ")
		     + yystrlen (yytname[yytype]));
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yyprefix = ", expecting ";
		  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			yyp = yystpcpy (yyp, yyprefix);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yyprefix = " or ";
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

      if (yychar <= YYEOF)
        {
          /* If at end of input, pop the error token,
	     then the rest of the stack, then return failure.  */
	  if (yychar == YYEOF)
	     for (;;)
	       {
		 YYPOPSTACK;
		 if (yyssp == yyss)
		   YYABORT;
		 YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
		 yydestruct (yystos[*yyssp], yyvsp);
	       }
        }
      else
	{
	  YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
	  yydestruct (yytoken, &yylval);
	  yychar = YYEMPTY;

	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

#ifdef __GNUC__
  /* Pacify GCC when the user code never invokes YYERROR and the label
     yyerrorlab therefore never appears in user code.  */
  if (0)
     goto yyerrorlab;
#endif

  yyvsp -= yylen;
  yyssp -= yylen;
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

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      YYPOPSTACK;
      yystate = *yyssp;
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



