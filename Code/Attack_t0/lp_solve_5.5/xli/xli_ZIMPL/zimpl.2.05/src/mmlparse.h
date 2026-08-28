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
/* Line 1248 of yacc.c.  */
#line 246 "src/mmlparse.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif





