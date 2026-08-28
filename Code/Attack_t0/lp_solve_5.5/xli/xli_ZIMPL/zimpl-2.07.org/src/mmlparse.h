/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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
/* Line 1529 of yacc.c.  */
#line 269 "src/mmlparse.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



