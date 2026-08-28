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
/* Line 1285 of yacc.c.  */
#line 237 "src/mmlparse.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif





