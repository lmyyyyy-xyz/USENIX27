/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or lpt_yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with lpt_yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define scanner lpt_yyscanner
#define PARM lpt_yyget_extra(lpt_yyscanner)
#define YYSTYPE int
#define YY_EXTRA_TYPE parse_parm *
#define YY_FATAL_ERROR(msg) lex_fatal_error(PARM, lpt_yyscanner, msg)
#undef YY_INPUT
#define lpt_yyerror read_error

#include "lpkit.h"
#include "yacc_read.h"

typedef struct parse_vars_s
{
  char HadVar, HadConstraint, Had_lineair_sum, HadSign, OP, Sign, isign, isign0, make_neg, objconst;
  char Within_gen_decl;  /* TRUE when we are within an gen declaration */
  char Within_bin_decl;  /* TRUE when we are within an bin declaration */
  char Within_sec_decl;  /* TRUE when we are within a sec declaration */
  char Within_sos_decl;  /* TRUE when we are within a sos declaration */
  short SOStype;         /* SOS type */
  int SOSNr;
  int SOSweight;         /* SOS weight */
  int weight;
  char *Last_var;
  REAL f, f0, f1, f2;
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


# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int lpt_yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum lpt_yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    VAR = 258,                     /* VAR  */
    CONS = 259,                    /* CONS  */
    INTCONS = 260,                 /* INTCONS  */
    VARIABLECOLON = 261,           /* VARIABLECOLON  */
    INF = 262,                     /* INF  */
    FRE = 263,                     /* FRE  */
    SEC_INT = 264,                 /* SEC_INT  */
    SEC_SEC = 265,                 /* SEC_SEC  */
    SEC_SOS = 266,                 /* SEC_SOS  */
    SOSTYPE = 267,                 /* SOSTYPE  */
    TOK_SIGN = 268,                /* TOK_SIGN  */
    RE_OPEQ = 269,                 /* RE_OPEQ  */
    RE_OPLE = 270,                 /* RE_OPLE  */
    RE_OPGE = 271,                 /* RE_OPGE  */
    MINIMISE = 272,                /* MINIMISE  */
    MAXIMISE = 273,                /* MAXIMISE  */
    SUBJECTTO = 274,               /* SUBJECTTO  */
    BOUNDS = 275,                  /* BOUNDS  */
    END = 276,                     /* END  */
    UNDEFINED = 277                /* UNDEFINED  */
  };
  typedef enum lpt_yytokentype lpt_yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif




int lpt_yyparse (parse_parm *parm, void *scanner);



/* Symbol kind.  */
enum lpt_yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_VAR = 3,                        /* VAR  */
  YYSYMBOL_CONS = 4,                       /* CONS  */
  YYSYMBOL_INTCONS = 5,                    /* INTCONS  */
  YYSYMBOL_VARIABLECOLON = 6,              /* VARIABLECOLON  */
  YYSYMBOL_INF = 7,                        /* INF  */
  YYSYMBOL_FRE = 8,                        /* FRE  */
  YYSYMBOL_SEC_INT = 9,                    /* SEC_INT  */
  YYSYMBOL_SEC_SEC = 10,                   /* SEC_SEC  */
  YYSYMBOL_SEC_SOS = 11,                   /* SEC_SOS  */
  YYSYMBOL_SOSTYPE = 12,                   /* SOSTYPE  */
  YYSYMBOL_TOK_SIGN = 13,                  /* TOK_SIGN  */
  YYSYMBOL_RE_OPEQ = 14,                   /* RE_OPEQ  */
  YYSYMBOL_RE_OPLE = 15,                   /* RE_OPLE  */
  YYSYMBOL_RE_OPGE = 16,                   /* RE_OPGE  */
  YYSYMBOL_MINIMISE = 17,                  /* MINIMISE  */
  YYSYMBOL_MAXIMISE = 18,                  /* MAXIMISE  */
  YYSYMBOL_SUBJECTTO = 19,                 /* SUBJECTTO  */
  YYSYMBOL_BOUNDS = 20,                    /* BOUNDS  */
  YYSYMBOL_END = 21,                       /* END  */
  YYSYMBOL_UNDEFINED = 22,                 /* UNDEFINED  */
  YYSYMBOL_YYACCEPT = 23,                  /* $accept  */
  YYSYMBOL_EMPTY = 24,                     /* EMPTY  */
  YYSYMBOL_inputfile = 25,                 /* inputfile  */
  YYSYMBOL_26_1 = 26,                      /* $@1  */
  YYSYMBOL_objective_function = 27,        /* objective_function  */
  YYSYMBOL_28_2 = 28,                      /* $@2  */
  YYSYMBOL_objective_function1 = 29,       /* objective_function1  */
  YYSYMBOL_of = 30,                        /* of  */
  YYSYMBOL_31_3 = 31,                      /* $@3  */
  YYSYMBOL_real_of = 32,                   /* real_of  */
  YYSYMBOL_of_lineair_sum = 33,            /* of_lineair_sum  */
  YYSYMBOL_of_lineair_sum1 = 34,           /* of_lineair_sum1  */
  YYSYMBOL_of_lineair_term = 35,           /* of_lineair_term  */
  YYSYMBOL_36_4 = 36,                      /* $@4  */
  YYSYMBOL_37_5 = 37,                      /* $@5  */
  YYSYMBOL_of_lineair_term1 = 38,          /* of_lineair_term1  */
  YYSYMBOL_constraints = 39,               /* constraints  */
  YYSYMBOL_constraints1 = 40,              /* constraints1  */
  YYSYMBOL_41_6 = 41,                      /* $@6  */
  YYSYMBOL_constraints2 = 42,              /* constraints2  */
  YYSYMBOL_constraints3 = 43,              /* constraints3  */
  YYSYMBOL_constraint = 44,                /* constraint  */
  YYSYMBOL_45_7 = 45,                      /* $@7  */
  YYSYMBOL_real_constraint = 46,           /* real_constraint  */
  YYSYMBOL_47_8 = 47,                      /* $@8  */
  YYSYMBOL_x_lineair_sum = 48,             /* x_lineair_sum  */
  YYSYMBOL_lineair_sum = 49,               /* lineair_sum  */
  YYSYMBOL_lineair_term = 50,              /* lineair_term  */
  YYSYMBOL_51_9 = 51,                      /* $@9  */
  YYSYMBOL_RE_OP = 52,                     /* RE_OP  */
  YYSYMBOL_cons_term = 53,                 /* cons_term  */
  YYSYMBOL_bounds = 54,                    /* bounds  */
  YYSYMBOL_x_bounds = 55,                  /* x_bounds  */
  YYSYMBOL_x_bounds1 = 56,                 /* x_bounds1  */
  YYSYMBOL_bound = 57,                     /* bound  */
  YYSYMBOL_58_10 = 58,                     /* $@10  */
  YYSYMBOL_59_11 = 59,                     /* $@11  */
  YYSYMBOL_60_12 = 60,                     /* $@12  */
  YYSYMBOL_61_13 = 61,                     /* $@13  */
  YYSYMBOL_62_14 = 62,                     /* $@14  */
  YYSYMBOL_63_15 = 63,                     /* $@15  */
  YYSYMBOL_bound2 = 64,                    /* bound2  */
  YYSYMBOL_65_16 = 65,                     /* $@16  */
  YYSYMBOL_66_17 = 66,                     /* $@17  */
  YYSYMBOL_67_18 = 67,                     /* $@18  */
  YYSYMBOL_optionalbound = 68,             /* optionalbound  */
  YYSYMBOL_69_19 = 69,                     /* $@19  */
  YYSYMBOL_REALCONS = 70,                  /* REALCONS  */
  YYSYMBOL_RHS_STORE = 71,                 /* RHS_STORE  */
  YYSYMBOL_x_SIGN = 72,                    /* x_SIGN  */
  YYSYMBOL_VAR_STORE = 73,                 /* VAR_STORE  */
  YYSYMBOL_int_sec_sos_declarations = 74,  /* int_sec_sos_declarations  */
  YYSYMBOL_opt_VARIABLES = 75,             /* opt_VARIABLES  */
  YYSYMBOL_VARIABLES = 76,                 /* VARIABLES  */
  YYSYMBOL_SOSVARIABLES = 77,              /* SOSVARIABLES  */
  YYSYMBOL_ONEVARIABLE = 78,               /* ONEVARIABLE  */
  YYSYMBOL_ONESOSVARIABLE = 79,            /* ONESOSVARIABLE  */
  YYSYMBOL_80_20 = 80,                     /* $@20  */
  YYSYMBOL_x_int_declarations = 81,        /* x_int_declarations  */
  YYSYMBOL_int_declarations = 82,          /* int_declarations  */
  YYSYMBOL_int_declaration = 83,           /* int_declaration  */
  YYSYMBOL_84_21 = 84,                     /* $@21  */
  YYSYMBOL_x_sec_declarations = 85,        /* x_sec_declarations  */
  YYSYMBOL_sec_declarations = 86,          /* sec_declarations  */
  YYSYMBOL_sec_declaration = 87,           /* sec_declaration  */
  YYSYMBOL_88_22 = 88,                     /* $@22  */
  YYSYMBOL_x_sos_declarations = 89,        /* x_sos_declarations  */
  YYSYMBOL_sos_declarations = 90,          /* sos_declarations  */
  YYSYMBOL_sos_declaration = 91,           /* sos_declaration  */
  YYSYMBOL_x_single_sos_declarations = 92, /* x_single_sos_declarations  */
  YYSYMBOL_single_sos_declarations = 93,   /* single_sos_declarations  */
  YYSYMBOL_single_sos_declaration = 94,    /* single_sos_declaration  */
  YYSYMBOL_95_23 = 95,                     /* $@23  */
  YYSYMBOL_VARIABLE = 96,                  /* VARIABLE  */
  YYSYMBOL_end = 97                        /* end  */
};
typedef enum lpt_yysymbol_kind_t lpt_yysymbol_kind_t;



/* Unqualified %code blocks.  */

#include "lp_rlpt.inc"

#undef lpt_yylval


#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ lpt_yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t lpt_yytype_int8;
#else
typedef signed char lpt_yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ lpt_yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t lpt_yytype_int16;
#else
typedef short lpt_yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ lpt_yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t lpt_yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char lpt_yytype_uint8;
#else
typedef short lpt_yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ lpt_yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t lpt_yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short lpt_yytype_uint16;
#else
typedef int lpt_yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef lpt_yytype_uint8 lpt_yy_state_t;

/* State numbers in computations.  */
typedef int lpt_yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about lpt_yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined lpt_yyoverflow

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined lpt_yyoverflow */

#if (! defined lpt_yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union lpt_yyalloc
{
  lpt_yy_state_t lpt_yyss_alloc;
  YYSTYPE lpt_yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union lpt_yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (lpt_yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T lpt_yynewbytes;                                         \
        YYCOPY (&lpt_yyptr->Stack_alloc, Stack, lpt_yysize);                    \
        Stack = &lpt_yyptr->Stack_alloc;                                    \
        lpt_yynewbytes = lpt_yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        lpt_yyptr += lpt_yynewbytes / YYSIZEOF (*lpt_yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T lpt_yyi;                      \
          for (lpt_yyi = 0; lpt_yyi < (Count); lpt_yyi++)   \
            (Dst)[lpt_yyi] = (Src)[lpt_yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   150

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  23
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  75
/* YYNRULES -- Number of rules.  */
#define YYNRULES  112
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  153

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   277


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by lpt_yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (lpt_yysymbol_kind_t, lpt_yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by lpt_yylex.  */
static const lpt_yytype_int8 lpt_yytranslate[] =
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
      15,    16,    17,    18,    19,    20,    21,    22
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const lpt_yytype_int16 lpt_yyrline[] =
{
       0,    91,    91,    95,    95,   128,   128,   139,   144,   151,
     153,   152,   164,   184,   185,   188,   189,   194,   201,   194,
     212,   224,   260,   261,   265,   264,   280,   281,   284,   285,
     289,   291,   290,   304,   302,   328,   335,   338,   339,   345,
     343,   352,   358,   358,   358,   361,   363,   391,   392,   396,
     397,   400,   401,   406,   405,   416,   424,   433,   441,   449,
     415,   470,   469,   493,   504,   492,   532,   534,   533,   558,
     558,   561,   575,   582,   592,   613,   618,   619,   622,   623,
     627,   628,   632,   641,   652,   651,   669,   670,   673,   674,
     679,   678,   689,   690,   693,   694,   699,   698,   710,   711,
     714,   715,   719,   724,   725,   729,   730,   736,   735,   776,
     776,   781,   782
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (lpt_yysymbol_kind_t, lpt_yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *lpt_yysymbol_name (lpt_yysymbol_kind_t lpt_yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const lpt_yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "VAR", "CONS",
  "INTCONS", "VARIABLECOLON", "INF", "FRE", "SEC_INT", "SEC_SEC",
  "SEC_SOS", "SOSTYPE", "TOK_SIGN", "RE_OPEQ", "RE_OPLE", "RE_OPGE",
  "MINIMISE", "MAXIMISE", "SUBJECTTO", "BOUNDS", "END", "UNDEFINED",
  "$accept", "EMPTY", "inputfile", "$@1", "objective_function", "$@2",
  "objective_function1", "of", "$@3", "real_of", "of_lineair_sum",
  "of_lineair_sum1", "of_lineair_term", "$@4", "$@5", "of_lineair_term1",
  "constraints", "constraints1", "$@6", "constraints2", "constraints3",
  "constraint", "$@7", "real_constraint", "$@8", "x_lineair_sum",
  "lineair_sum", "lineair_term", "$@9", "RE_OP", "cons_term", "bounds",
  "x_bounds", "x_bounds1", "bound", "$@10", "$@11", "$@12", "$@13", "$@14",
  "$@15", "bound2", "$@16", "$@17", "$@18", "optionalbound", "$@19",
  "REALCONS", "RHS_STORE", "x_SIGN", "VAR_STORE",
  "int_sec_sos_declarations", "opt_VARIABLES", "VARIABLES", "SOSVARIABLES",
  "ONEVARIABLE", "ONESOSVARIABLE", "$@20", "x_int_declarations",
  "int_declarations", "int_declaration", "$@21", "x_sec_declarations",
  "sec_declarations", "sec_declaration", "$@22", "x_sos_declarations",
  "sos_declarations", "sos_declaration", "x_single_sos_declarations",
  "single_sos_declarations", "single_sos_declaration", "$@23", "VARIABLE",
  "end", YY_NULLPTR
};

static const char *
lpt_yysymbol_name (lpt_yysymbol_kind_t lpt_yysymbol)
{
  return lpt_yytname[lpt_yysymbol];
}
#endif

#define YYPACT_NINF (-112)

#define lpt_yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-73)

#define lpt_yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const lpt_yytype_int8 lpt_yypact[] =
{
    -112,     5,  -112,  -112,     1,     0,  -112,  -112,     8,  -112,
      30,    30,  -112,    42,    34,  -112,    55,  -112,  -112,  -112,
    -112,  -112,    87,  -112,    26,  -112,  -112,  -112,    58,  -112,
      98,  -112,  -112,   121,   116,  -112,   109,  -112,  -112,  -112,
      84,  -112,  -112,    73,  -112,   101,  -112,  -112,  -112,    49,
      86,    55,  -112,    87,  -112,  -112,  -112,    26,   125,  -112,
    -112,  -112,  -112,  -112,  -112,  -112,  -112,    57,  -112,   121,
    -112,  -112,  -112,    57,  -112,  -112,  -112,  -112,  -112,    88,
      86,  -112,  -112,  -112,   109,  -112,     9,  -112,  -112,  -112,
    -112,    43,  -112,  -112,    57,  -112,  -112,    57,    89,  -112,
    -112,    88,  -112,  -112,  -112,  -112,  -112,  -112,  -112,  -112,
      57,  -112,  -112,  -112,  -112,  -112,  -112,  -112,  -112,    89,
    -112,  -112,  -112,  -112,  -112,  -112,  -112,     9,    79,  -112,
    -112,  -112,  -112,  -112,    79,  -112,  -112,  -112,  -112,  -112,
     105,  -112,  -112,  -112,  -112,  -112,   121,  -112,  -112,  -112,
       9,  -112,  -112
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const lpt_yytype_int8 lpt_yydefact[] =
{
       3,     0,     5,     1,     2,     0,    24,    22,     2,    23,
       2,     2,     6,     2,     2,    47,     2,    10,    13,     8,
       9,    12,    14,    15,     2,     7,    31,    73,    26,    25,
       2,    28,    30,     0,     2,    37,     0,   109,    46,   110,
      49,    55,    48,    50,    51,     0,    53,    90,    86,     2,
       2,    87,    88,     2,    16,    72,    18,     2,    72,    29,
      42,    43,    44,    33,    38,    70,    69,     0,    39,     0,
      52,    45,     2,     2,   112,   111,     4,    96,    92,     2,
      93,    94,    89,    11,     0,    32,     2,     2,     2,    56,
      74,     0,    76,    91,    77,    78,    82,     2,     2,    98,
      75,    99,   100,    95,    19,    20,     2,     2,    41,    40,
       0,    63,    61,    54,    79,    97,   107,   103,   102,   104,
     105,   101,    21,    71,    34,    57,     2,     2,     0,   106,
       2,    64,     2,    84,   108,    80,    83,    58,     2,    62,
       0,    81,     2,    65,    85,    59,     2,    66,    67,    60,
       2,     2,    68
};

/* YYPGOTO[NTERM-NUM].  */
static const lpt_yytype_int8 lpt_yypgoto[] =
{
    -112,    -4,  -112,  -112,  -112,  -112,  -112,   112,  -112,    63,
    -112,  -112,   102,  -112,  -112,  -112,  -112,  -112,  -112,  -112,
    -112,    90,  -112,    68,  -112,  -112,  -112,    93,  -112,   -67,
     -83,  -112,  -112,  -112,   100,  -112,  -112,  -112,  -112,  -112,
    -112,  -112,  -112,  -112,  -112,  -112,  -112,   -34,  -111,    -5,
     -74,  -112,    36,  -112,  -112,    50,    11,  -112,  -112,  -112,
      95,  -112,  -112,  -112,    69,  -112,  -112,  -112,    47,  -112,
    -112,    31,  -112,   -13,  -112
};

/* YYDEFGOTO[NTERM-NUM].  */
static const lpt_yytype_uint8 lpt_yydefgoto[] =
{
       0,    55,     1,     2,     4,     5,    12,    19,    53,    20,
      21,    22,    23,    24,    84,   104,     8,     9,    13,    29,
      30,    31,    57,    32,    86,    33,    34,    35,    88,    63,
      41,    16,    42,    43,    44,    72,    69,   110,   130,   142,
     146,   113,   127,   126,   138,   149,   150,    67,   124,    45,
      91,    49,    93,    94,   134,    95,   135,   140,    50,    51,
      52,    73,    79,    80,    81,    97,   100,   101,   102,   118,
     119,   120,   128,    96,    76
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const lpt_yytype_int16 lpt_yytable[] =
{
       7,    46,    89,   107,    15,     3,    18,    18,    36,    28,
      40,    71,    48,   108,   109,   131,    38,    10,    11,    56,
       6,   139,    27,    68,   112,    36,    58,   143,    14,    36,
      46,   145,   122,   -17,   -17,   -17,    17,    37,   -17,    27,
     152,    38,    39,   -17,   132,    75,    78,    27,    26,    18,
     105,   111,    36,    58,    87,    27,   137,    60,    61,    62,
      37,   -72,   -72,   -72,    47,    39,   -72,   151,    90,    92,
      74,   106,   -35,   -35,   -35,    99,    37,    -2,    -2,   148,
      38,    39,    37,    90,    90,   133,    27,    39,   -72,   -72,
     -17,   -17,   -17,    92,   117,   -17,    77,   125,   -27,    98,
     -17,   116,    90,   123,    26,    65,    66,   -27,   -27,   -27,
     144,    27,    37,    65,    66,   136,    83,    39,   -27,   -27,
      59,   136,   123,    25,    54,    85,    90,    64,   123,    27,
     -36,   -36,   -36,   115,   123,    60,    61,    62,   123,   -35,
     -35,   -35,   147,    70,   114,   141,    82,   123,   121,   103,
     129
};

static const lpt_yytype_uint8 lpt_yycheck[] =
{
       4,    14,    69,    86,     8,     0,    10,    11,    13,    13,
      14,    45,    16,    87,    88,   126,     7,    17,    18,    24,
      19,   132,    13,    36,    91,    30,    30,   138,    20,    34,
      43,   142,   106,     3,     4,     5,     6,     3,     8,    13,
     151,     7,     8,    13,   127,    49,    50,    13,     6,    53,
      84,     8,    57,    57,    67,    13,   130,    14,    15,    16,
       3,     3,     4,     5,     9,     8,     8,   150,    72,    73,
      21,    84,    14,    15,    16,    79,     3,     4,     5,   146,
       7,     8,     3,    87,    88,     6,    13,     8,     4,     5,
       3,     4,     5,    97,    98,     8,    10,   110,     0,    11,
      13,    12,   106,   107,     6,     4,     5,     9,    10,    11,
       5,    13,     3,     4,     5,   128,    53,     8,    20,    21,
      30,   134,   126,    11,    22,    57,   130,    34,   132,    13,
      14,    15,    16,    97,   138,    14,    15,    16,   142,    14,
      15,    16,   146,    43,    94,   134,    51,   151,   101,    80,
     119
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const lpt_yytype_int8 lpt_yystos[] =
{
       0,    25,    26,     0,    27,    28,    19,    24,    39,    40,
      17,    18,    29,    41,    20,    24,    54,     6,    24,    30,
      32,    33,    34,    35,    36,    30,     6,    13,    24,    42,
      43,    44,    46,    48,    49,    50,    72,     3,     7,     8,
      24,    53,    55,    56,    57,    72,    96,     9,    24,    74,
      81,    82,    83,    31,    35,    24,    72,    45,    24,    44,
      14,    15,    16,    52,    50,     4,     5,    70,    96,    59,
      57,    70,    58,    84,    21,    24,    97,    10,    24,    85,
      86,    87,    83,    32,    37,    46,    47,    96,    51,    52,
      24,    73,    24,    75,    76,    78,    96,    88,    11,    24,
      89,    90,    91,    87,    38,    70,    96,    53,    73,    73,
      60,     8,    52,    64,    78,    75,    12,    24,    92,    93,
      94,    91,    73,    24,    71,    96,    66,    65,    95,    94,
      61,    71,    53,     6,    77,    79,    96,    73,    67,    71,
      80,    79,    62,    71,     5,    71,    63,    24,    52,    68,
      69,    53,    71
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const lpt_yytype_int8 lpt_yyr1[] =
{
       0,    23,    24,    26,    25,    28,    27,    29,    29,    30,
      31,    30,    32,    33,    33,    34,    34,    36,    37,    35,
      38,    38,    39,    39,    41,    40,    42,    42,    43,    43,
      44,    45,    44,    47,    46,    48,    48,    49,    49,    51,
      50,    50,    52,    52,    52,    53,    53,    54,    54,    55,
      55,    56,    56,    58,    57,    59,    60,    61,    62,    63,
      57,    65,    64,    66,    67,    64,    68,    69,    68,    70,
      70,    71,    72,    72,    73,    74,    75,    75,    76,    76,
      77,    77,    78,    79,    80,    79,    81,    81,    82,    82,
      84,    83,    85,    85,    86,    86,    88,    87,    89,    89,
      90,    90,    91,    92,    92,    93,    93,    95,    94,    96,
      96,    97,    97
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const lpt_yytype_int8 lpt_yyr2[] =
{
       0,     2,     0,     0,     6,     0,     2,     2,     2,     1,
       0,     3,     1,     1,     1,     1,     2,     0,     0,     4,
       1,     2,     1,     1,     0,     3,     1,     1,     1,     2,
       1,     0,     3,     0,     5,     1,     1,     1,     2,     0,
       4,     4,     1,     1,     1,     2,     1,     1,     2,     1,
       1,     1,     2,     0,     4,     0,     0,     0,     0,     0,
      11,     0,     4,     0,     0,     5,     1,     0,     4,     1,
       1,     1,     1,     1,     1,     3,     1,     1,     1,     2,
       1,     2,     1,     1,     0,     3,     1,     1,     1,     2,
       0,     3,     1,     1,     1,     2,     0,     3,     1,     1,
       1,     2,     2,     1,     1,     1,     2,     0,     3,     1,
       1,     1,     1
};


enum { YYENOMEM = -2 };

#define lpt_yyerrok         (lpt_yyerrstatus = 0)
#define lpt_yyclearin       (lpt_yychar = YYEMPTY)

#define YYACCEPT        goto lpt_yyacceptlab
#define YYABORT         goto lpt_yyabortlab
#define YYERROR         goto lpt_yyerrorlab
#define YYNOMEM         goto lpt_yyexhaustedlab


#define YYRECOVERING()  (!!lpt_yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (lpt_yychar == YYEMPTY)                                        \
      {                                                           \
        lpt_yychar = (Token);                                         \
        lpt_yylval = (Value);                                         \
        YYPOPSTACK (lpt_yylen);                                       \
        lpt_yystate = *lpt_yyssp;                                         \
        goto lpt_yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        lpt_yyerror (parm, scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (lpt_yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (lpt_yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      lpt_yy_symbol_print (stderr,                                            \
                  Kind, Value, parm, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
lpt_yy_symbol_value_print (FILE *lpt_yyo,
                       lpt_yysymbol_kind_t lpt_yykind, YYSTYPE const * const lpt_yyvaluep, parse_parm *parm, void *scanner)
{
  FILE *lpt_yyoutput = lpt_yyo;
  YY_USE (lpt_yyoutput);
  YY_USE (parm);
  YY_USE (scanner);
  if (!lpt_yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (lpt_yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
lpt_yy_symbol_print (FILE *lpt_yyo,
                 lpt_yysymbol_kind_t lpt_yykind, YYSTYPE const * const lpt_yyvaluep, parse_parm *parm, void *scanner)
{
  YYFPRINTF (lpt_yyo, "%s %s (",
             lpt_yykind < YYNTOKENS ? "token" : "nterm", lpt_yysymbol_name (lpt_yykind));

  lpt_yy_symbol_value_print (lpt_yyo, lpt_yykind, lpt_yyvaluep, parm, scanner);
  YYFPRINTF (lpt_yyo, ")");
}

/*------------------------------------------------------------------.
| lpt_yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
lpt_yy_stack_print (lpt_yy_state_t *lpt_yybottom, lpt_yy_state_t *lpt_yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; lpt_yybottom <= lpt_yytop; lpt_yybottom++)
    {
      int lpt_yybot = *lpt_yybottom;
      YYFPRINTF (stderr, " %d", lpt_yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (lpt_yydebug)                                                  \
    lpt_yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
lpt_yy_reduce_print (lpt_yy_state_t *lpt_yyssp, YYSTYPE *lpt_yyvsp,
                 int lpt_yyrule, parse_parm *parm, void *scanner)
{
  int lpt_yylno = lpt_yyrline[lpt_yyrule];
  int lpt_yynrhs = lpt_yyr2[lpt_yyrule];
  int lpt_yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             lpt_yyrule - 1, lpt_yylno);
  /* The symbols being reduced.  */
  for (lpt_yyi = 0; lpt_yyi < lpt_yynrhs; lpt_yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", lpt_yyi + 1);
      lpt_yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+lpt_yyssp[lpt_yyi + 1 - lpt_yynrhs]),
                       &lpt_yyvsp[(lpt_yyi + 1) - (lpt_yynrhs)], parm, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (lpt_yydebug)                          \
    lpt_yy_reduce_print (lpt_yyssp, lpt_yyvsp, Rule, parm, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int lpt_yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
lpt_yydestruct (const char *lpt_yymsg,
            lpt_yysymbol_kind_t lpt_yykind, YYSTYPE *lpt_yyvaluep, parse_parm *parm, void *scanner)
{
  YY_USE (lpt_yyvaluep);
  YY_USE (parm);
  YY_USE (scanner);
  if (!lpt_yymsg)
    lpt_yymsg = "Deleting";
  YY_SYMBOL_PRINT (lpt_yymsg, lpt_yykind, lpt_yyvaluep, lpt_yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (lpt_yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| lpt_yyparse.  |
`----------*/

int
lpt_yyparse (parse_parm *parm, void *scanner)
{
/* Lookahead token kind.  */
int lpt_yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE lpt_yyval_default;)
YYSTYPE lpt_yylval YY_INITIAL_VALUE (= lpt_yyval_default);

    /* Number of syntax errors so far.  */
    int lpt_yynerrs = 0;

    lpt_yy_state_fast_t lpt_yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int lpt_yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow lpt_yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T lpt_yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    lpt_yy_state_t lpt_yyssa[YYINITDEPTH];
    lpt_yy_state_t *lpt_yyss = lpt_yyssa;
    lpt_yy_state_t *lpt_yyssp = lpt_yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE lpt_yyvsa[YYINITDEPTH];
    YYSTYPE *lpt_yyvs = lpt_yyvsa;
    YYSTYPE *lpt_yyvsp = lpt_yyvs;

  int lpt_yyn;
  /* The return value of lpt_yyparse.  */
  int lpt_yyresult;
  /* Lookahead symbol kind.  */
  lpt_yysymbol_kind_t lpt_yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE lpt_yyval;



#define YYPOPSTACK(N)   (lpt_yyvsp -= (N), lpt_yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int lpt_yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  lpt_yychar = YYEMPTY; /* Cause a token to be read.  */

  goto lpt_yysetstate;


/*------------------------------------------------------------.
| lpt_yynewstate -- push a new state, which is found in lpt_yystate.  |
`------------------------------------------------------------*/
lpt_yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  lpt_yyssp++;


/*--------------------------------------------------------------------.
| lpt_yysetstate -- set current state (the top of the stack) to lpt_yystate.  |
`--------------------------------------------------------------------*/
lpt_yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", lpt_yystate));
  YY_ASSERT (0 <= lpt_yystate && lpt_yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *lpt_yyssp = YY_CAST (lpt_yy_state_t, lpt_yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (lpt_yyss, lpt_yyssp);

  if (lpt_yyss + lpt_yystacksize - 1 <= lpt_yyssp)
#if !defined lpt_yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T lpt_yysize = lpt_yyssp - lpt_yyss + 1;

# if defined lpt_yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        lpt_yy_state_t *lpt_yyss1 = lpt_yyss;
        YYSTYPE *lpt_yyvs1 = lpt_yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if lpt_yyoverflow is a macro.  */
        lpt_yyoverflow (YY_("memory exhausted"),
                    &lpt_yyss1, lpt_yysize * YYSIZEOF (*lpt_yyssp),
                    &lpt_yyvs1, lpt_yysize * YYSIZEOF (*lpt_yyvsp),
                    &lpt_yystacksize);
        lpt_yyss = lpt_yyss1;
        lpt_yyvs = lpt_yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= lpt_yystacksize)
        YYNOMEM;
      lpt_yystacksize *= 2;
      if (YYMAXDEPTH < lpt_yystacksize)
        lpt_yystacksize = YYMAXDEPTH;

      {
        lpt_yy_state_t *lpt_yyss1 = lpt_yyss;
        union lpt_yyalloc *lpt_yyptr =
          YY_CAST (union lpt_yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (lpt_yystacksize))));
        if (! lpt_yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (lpt_yyss_alloc, lpt_yyss);
        YYSTACK_RELOCATE (lpt_yyvs_alloc, lpt_yyvs);
#  undef YYSTACK_RELOCATE
        if (lpt_yyss1 != lpt_yyssa)
          YYSTACK_FREE (lpt_yyss1);
      }
# endif

      lpt_yyssp = lpt_yyss + lpt_yysize - 1;
      lpt_yyvsp = lpt_yyvs + lpt_yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, lpt_yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (lpt_yyss + lpt_yystacksize - 1 <= lpt_yyssp)
        YYABORT;
    }
#endif /* !defined lpt_yyoverflow && !defined YYSTACK_RELOCATE */


  if (lpt_yystate == YYFINAL)
    YYACCEPT;

  goto lpt_yybackup;


/*-----------.
| lpt_yybackup.  |
`-----------*/
lpt_yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  lpt_yyn = lpt_yypact[lpt_yystate];
  if (lpt_yypact_value_is_default (lpt_yyn))
    goto lpt_yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (lpt_yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      lpt_yychar = lpt_yylex (&lpt_yylval, scanner);
    }

  if (lpt_yychar <= YYEOF)
    {
      lpt_yychar = YYEOF;
      lpt_yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (lpt_yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      lpt_yychar = YYUNDEF;
      lpt_yytoken = YYSYMBOL_YYerror;
      goto lpt_yyerrlab1;
    }
  else
    {
      lpt_yytoken = YYTRANSLATE (lpt_yychar);
      YY_SYMBOL_PRINT ("Next token is", lpt_yytoken, &lpt_yylval, &lpt_yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  lpt_yyn += lpt_yytoken;
  if (lpt_yyn < 0 || YYLAST < lpt_yyn || lpt_yycheck[lpt_yyn] != lpt_yytoken)
    goto lpt_yydefault;
  lpt_yyn = lpt_yytable[lpt_yyn];
  if (lpt_yyn <= 0)
    {
      if (lpt_yytable_value_is_error (lpt_yyn))
        goto lpt_yyerrlab;
      lpt_yyn = -lpt_yyn;
      goto lpt_yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (lpt_yyerrstatus)
    lpt_yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", lpt_yytoken, &lpt_yylval, &lpt_yylloc);
  lpt_yystate = lpt_yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++lpt_yyvsp = lpt_yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  lpt_yychar = YYEMPTY;
  goto lpt_yynewstate;


/*-----------------------------------------------------------.
| lpt_yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
lpt_yydefault:
  lpt_yyn = lpt_yydefact[lpt_yystate];
  if (lpt_yyn == 0)
    goto lpt_yyerrlab;
  goto lpt_yyreduce;


/*-----------------------------.
| lpt_yyreduce -- do a reduction.  |
`-----------------------------*/
lpt_yyreduce:
  /* lpt_yyn is the number of a rule to reduce with.  */
  lpt_yylen = lpt_yyr2[lpt_yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  lpt_yyval = lpt_yyvsp[1-lpt_yylen];


  YY_REDUCE_PRINT (lpt_yyn);
  switch (lpt_yyn)
    {
  case 3: /* $@1: %empty  */
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

  case 5: /* $@2: %empty  */
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->f = 1;
  pv->f1 = pv->f2 = 0;
}
    break;

  case 7: /* objective_function1: MAXIMISE of  */
{
  set_obj_dir(PARM, TRUE);
}
    break;

  case 8: /* objective_function1: MINIMISE of  */
{
  set_obj_dir(PARM, FALSE);
}
    break;

  case 10: /* $@3: %empty  */
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if(!add_constraint_name(pp, pv->Last_var))
    YYABORT;
  /* pv->HadConstraint = TRUE; */
}
    break;

  case 12: /* real_of: of_lineair_sum  */
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if((!pv->objconst) && (pv->f1 + pv->f2 != 0)) {
    lpt_yyerror(pp, pp->scanner, "constant in objective not supported");
    YYABORT;
  }
  if(!rhs_store(pp, -(pv->f1 + pv->f2), pv->HadConstraint, pv->HadVar, pv->Had_lineair_sum))
    YYABORT;

  add_row(pp);
  /* pv->HadConstraint = FALSE; */
  pv->HadVar = FALSE;
  pv->isign = 0;
  pv->make_neg = 0;
}
    break;

  case 17: /* $@4: %empty  */
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->HadSign = FALSE;
}
    break;

  case 18: /* $@5: %empty  */
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if(pv->HadSign) {
    pv->f1 += pv->f2;
    pv->f = 1;
  }
}
    break;

  case 20: /* of_lineair_term1: REALCONS  */
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if (    (pv->isign || pv->make_neg)
      && !(pv->isign && pv->make_neg)) /* but not both! */
    pv->f = -pv->f;
  pv->f2 = pv->f;
  pv->isign = 0;
}
    break;

  case 21: /* of_lineair_term1: VARIABLE VAR_STORE  */
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->f2 = 0;
  pv->f = 1;
}
    break;

  case 24: /* $@6: %empty  */
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->HadConstraint = TRUE;
}
    break;

  case 25: /* constraints1: SUBJECTTO $@6 constraints2  */
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->HadConstraint = FALSE;
}
    break;

  case 31: /* $@7: %empty  */
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if(!add_constraint_name(pp, pv->Last_var))
    YYABORT;
  /* pv->HadConstraint = TRUE; */
}
    break;

  case 33: /* $@8: %empty  */
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if(!store_re_op(pp, pv->OP, pv->HadConstraint, pv->HadVar, pv->Had_lineair_sum))
    YYABORT;
  pv->make_neg = 1;
}
    break;

  case 34: /* real_constraint: x_lineair_sum RE_OP $@8 cons_term RHS_STORE  */
{
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

  case 35: /* x_lineair_sum: EMPTY  */
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->HadConstraint = pv->HadVar = TRUE;
}
    break;

  case 39: /* $@9: %empty  */
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->f = 1.0;
}
    break;

  case 46: /* cons_term: INF  */
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->isign = pv->Sign;
}
    break;

  case 53: /* $@10: %empty  */
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->f = 1.0;
  pv->isign = 0;
}
    break;

  case 55: /* $@11: %empty  */
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->f0 = pv->f;
  pv->isign0 = pv->isign;
}
    break;

  case 56: /* $@12: %empty  */
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if(!store_re_op(pp, pv->OP, pv->HadConstraint, pv->HadVar, pv->Had_lineair_sum))
    YYABORT;
  pv->make_neg = 0;
}
    break;

  case 57: /* $@13: %empty  */
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->isign = 0;
  pv->f = -1.0;
}
    break;

  case 58: /* $@14: %empty  */
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->isign = pv->isign0;
  pv->f = pv->f0;
}
    break;

  case 59: /* $@15: %empty  */
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if(!store_bounds(pp, TRUE))
    YYABORT;
}
    break;

  case 60: /* bound: cons_term $@11 RE_OP $@12 VARIABLE $@13 VAR_STORE $@14 RHS_STORE $@15 optionalbound  */
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  /* pv->HadConstraint = FALSE; */
  pv->HadVar = FALSE;
  pv->isign = 0;
  pv->make_neg = 0;
  null_tmp_store(pp, TRUE);
}
    break;

  case 61: /* $@16: %empty  */
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if(!store_re_op(pp, pv->OP, pv->HadConstraint, pv->HadVar, pv->Had_lineair_sum))
    YYABORT;
  pv->make_neg = 1;
}
    break;

  case 62: /* bound2: RE_OP $@16 cons_term RHS_STORE  */
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if(!store_bounds(pp, TRUE))
    YYABORT;
  /* pv->HadConstraint = FALSE; */
  pv->HadVar = FALSE;
  pv->isign = 0;
  pv->make_neg = 0;
  null_tmp_store(pp, TRUE);
}
    break;

  case 63: /* $@17: %empty  */
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

  case 64: /* $@18: %empty  */
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

  case 65: /* bound2: FRE $@17 RHS_STORE $@18 RHS_STORE  */
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

  case 67: /* $@19: %empty  */
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if(!store_re_op(pp, (char) ((pv->OP == '<') ? '>' : (pv->OP == '>') ? '<' : pv->OP), (int) pv->HadConstraint, (int) pv->HadVar, (int) pv->Had_lineair_sum))
    YYABORT;
  pv->make_neg = 0;
  pv->isign = 0;
}
    break;

  case 68: /* optionalbound: RE_OP $@19 cons_term RHS_STORE  */
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if(!store_bounds(pp, TRUE))
    YYABORT;
}
    break;

  case 71: /* RHS_STORE: EMPTY  */
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

  case 72: /* x_SIGN: EMPTY  */
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->isign = 0;
}
    break;

  case 73: /* x_SIGN: TOK_SIGN  */
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->isign = pv->Sign;
  pv->HadSign = TRUE;
}
    break;

  case 74: /* VAR_STORE: EMPTY  */
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  if (    (pv->isign || pv->make_neg)
      && !(pv->isign && pv->make_neg)) /* but not both! */
    pv->f = -pv->f;
  if(!var_store(pp, pv->Last_var, pv->f, pv->HadConstraint, pv->HadVar, pv->Had_lineair_sum)) {
    lpt_yyerror(pp, pp->scanner, "var_store failed");
    YYABORT;
  }
  /* pv->HadConstraint |= pv->HadVar; */
  pv->HadVar = TRUE;
  pv->isign = 0;
}
    break;

  case 82: /* ONEVARIABLE: VARIABLE  */
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  storevarandweight(pp, pv->Last_var);
}
    break;

  case 83: /* ONESOSVARIABLE: VARIABLE  */
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->SOSNr++;
  pv->weight = pv->SOSNr;
  storevarandweight(pp, pv->Last_var);
  set_sos_weight(pp, pv->weight, 2);
}
    break;

  case 84: /* $@20: %empty  */
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  storevarandweight(pp, pv->Last_var);
}
    break;

  case 85: /* ONESOSVARIABLE: VARIABLECOLON $@20 INTCONS  */
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  pv->weight = (int) (pv->f + .1);
  set_sos_weight(pp, pv->weight, 2);
}
    break;

  case 90: /* $@21: %empty  */
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  check_int_sec_sos_free_decl(pp, pv->Within_gen_decl ? 1 : pv->Within_bin_decl ? 2 : 0, 0, 0, 0);
}
    break;

  case 96: /* $@22: %empty  */
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  check_int_sec_sos_free_decl(pp, 0, 1, 0, 0);
}
    break;

  case 107: /* $@23: %empty  */
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;
  char buf[16], *ptr, *var;

  check_int_sec_sos_free_decl(pp, 0, 0, 1, 0);
  pv->SOSweight++;
  for (ptr = pv->Last_var; (*ptr) && (*ptr != ':'); ptr++);
  if (ptr[1] == ':') {
    sprintf(buf, "SOS%d", pv->SOSweight);
    var = buf;
    ptr = pv->Last_var;
  }
  else {
    var = ptr + 1;
    while ((ptr > pv->Last_var) && (isspace(ptr[-1]))) ptr--;
    *ptr = 0;
    ptr = var;
    var = pv->Last_var;
    while (isspace(*ptr)) ptr++;
  }
  storevarandweight(pp, var);
  pv->SOStype = ptr[1] - '0';
  set_sos_type(pp, pv->SOStype);
  check_int_sec_sos_free_decl(pp, 0, 0, 2, 0);
  pv->weight = 0;
  pv->SOSNr = 0;
}
    break;

  case 108: /* single_sos_declaration: SOSTYPE $@23 SOSVARIABLES  */
{
  parse_parm *pp = PARM;
  parse_vars *pv = (parse_vars *) pp->parse_vars;

  set_sos_weight(pp, pv->SOSweight, 1);
}
    break;



      default: break;
    }
  /* User semantic actions sometimes alter lpt_yychar, and that requires
     that lpt_yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of lpt_yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering lpt_yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (lpt_yysymbol_kind_t, lpt_yyr1[lpt_yyn]), &lpt_yyval, &lpt_yyloc);

  YYPOPSTACK (lpt_yylen);
  lpt_yylen = 0;

  *++lpt_yyvsp = lpt_yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int lpt_yylhs = lpt_yyr1[lpt_yyn] - YYNTOKENS;
    const int lpt_yyi = lpt_yypgoto[lpt_yylhs] + *lpt_yyssp;
    lpt_yystate = (0 <= lpt_yyi && lpt_yyi <= YYLAST && lpt_yycheck[lpt_yyi] == *lpt_yyssp
               ? lpt_yytable[lpt_yyi]
               : lpt_yydefgoto[lpt_yylhs]);
  }

  goto lpt_yynewstate;


/*--------------------------------------.
| lpt_yyerrlab -- here on detecting error.  |
`--------------------------------------*/
lpt_yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  lpt_yytoken = lpt_yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (lpt_yychar);
  /* If not already recovering from an error, report this error.  */
  if (!lpt_yyerrstatus)
    {
      ++lpt_yynerrs;
      lpt_yyerror (parm, scanner, YY_("syntax error"));
    }

  if (lpt_yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (lpt_yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (lpt_yychar == YYEOF)
            YYABORT;
        }
      else
        {
          lpt_yydestruct ("Error: discarding",
                      lpt_yytoken, &lpt_yylval, parm, scanner);
          lpt_yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto lpt_yyerrlab1;


/*---------------------------------------------------.
| lpt_yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
lpt_yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label lpt_yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++lpt_yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (lpt_yylen);
  lpt_yylen = 0;
  YY_STACK_PRINT (lpt_yyss, lpt_yyssp);
  lpt_yystate = *lpt_yyssp;
  goto lpt_yyerrlab1;


/*-------------------------------------------------------------.
| lpt_yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
lpt_yyerrlab1:
  lpt_yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      lpt_yyn = lpt_yypact[lpt_yystate];
      if (!lpt_yypact_value_is_default (lpt_yyn))
        {
          lpt_yyn += YYSYMBOL_YYerror;
          if (0 <= lpt_yyn && lpt_yyn <= YYLAST && lpt_yycheck[lpt_yyn] == YYSYMBOL_YYerror)
            {
              lpt_yyn = lpt_yytable[lpt_yyn];
              if (0 < lpt_yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (lpt_yyssp == lpt_yyss)
        YYABORT;


      lpt_yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (lpt_yystate), lpt_yyvsp, parm, scanner);
      YYPOPSTACK (1);
      lpt_yystate = *lpt_yyssp;
      YY_STACK_PRINT (lpt_yyss, lpt_yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++lpt_yyvsp = lpt_yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (lpt_yyn), lpt_yyvsp, lpt_yylsp);

  lpt_yystate = lpt_yyn;
  goto lpt_yynewstate;


/*-------------------------------------.
| lpt_yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
lpt_yyacceptlab:
  lpt_yyresult = 0;
  goto lpt_yyreturnlab;


/*-----------------------------------.
| lpt_yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
lpt_yyabortlab:
  lpt_yyresult = 1;
  goto lpt_yyreturnlab;


/*-----------------------------------------------------------.
| lpt_yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
lpt_yyexhaustedlab:
  lpt_yyerror (parm, scanner, YY_("memory exhausted"));
  lpt_yyresult = 2;
  goto lpt_yyreturnlab;


/*----------------------------------------------------------.
| lpt_yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
lpt_yyreturnlab:
  if (lpt_yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      lpt_yytoken = YYTRANSLATE (lpt_yychar);
      lpt_yydestruct ("Cleanup: discarding lookahead",
                  lpt_yytoken, &lpt_yylval, parm, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (lpt_yylen);
  YY_STACK_PRINT (lpt_yyss, lpt_yyssp);
  while (lpt_yyssp != lpt_yyss)
    {
      lpt_yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*lpt_yyssp), lpt_yyvsp, parm, scanner);
      YYPOPSTACK (1);
    }
#ifndef lpt_yyoverflow
  if (lpt_yyss != lpt_yyssa)
    YYSTACK_FREE (lpt_yyss);
#endif

  return lpt_yyresult;
}



static void lpt_yy_delete_allocated_memory(parse_parm *pp)
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
    lpt_yy_delete_buffer(YY_CURRENT_BUFFER); /* comment this line if you have problems with it */
    lpt_yy_init = 1; /* make sure that the next time memory is allocated again */
    lpt_yy_start = 0;
#  else
    /* As of version 2.5.9 Flex  */
    lpt_yylex_destroy(pp->scanner); /* comment this line if you have problems with it */
#  endif
# endif

  FREE(pv->Last_var);
}

static int parse(parse_parm *pp)
{
  return(lpt_yyparse(pp, pp->scanner));
}

lprec *read_lptex(lprec *lp, FILE *filename, int verbose, char *lp_name, char objconst0)
{
  parse_vars *pv;
  lprec *lp1 = NULL;

  CALLOC(pv, 1, parse_vars);
  if (pv != NULL) {
    parse_parm pp;

    memset(&pp, 0, sizeof(pp));
    pp.parse_vars = (void *) pv;

    lpt_yylex_init(&pp.scanner);
    lpt_yyset_extra(&pp, pp.scanner);

    lpt_yyset_in((FILE *) filename, pp.scanner);
    lpt_yyset_out(NULL, pp.scanner);
    pv->objconst = objconst0;
    lp1 = yacc_read(lp, verbose, lp_name, parse, &pp, lpt_yy_delete_allocated_memory);
    FREE(pv);
  }
  return(lp1);
}

lprec * __WINAPI read_lpt(FILE *filename, int verbose, char *lp_name)
{
  return(read_lptex(NULL, filename, verbose, lp_name, FALSE));
}

lprec *read_LPTex(lprec *lp, char *filename, int verbose, char *lp_name, char objconst)
{
  FILE *fpin;

  if((fpin = fopen(filename, "r")) != NULL) {
    lp = read_lptex(lp, fpin, verbose, lp_name, objconst);
    fclose(fpin);
  }
  else
    lp = NULL;
  return(lp);
}

lprec * __WINAPI read_LPT(char *filename, int verbose, char *lp_name)
{
  return(read_LPTex(NULL, filename, verbose, lp_name, FALSE));
}
