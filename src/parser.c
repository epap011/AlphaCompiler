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
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
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
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/parser.y"

    #include "yacc_util.h"

#line 75 "src/parser.c"

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

#include "parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INTCONST = 3,                   /* INTCONST  */
  YYSYMBOL_REALCONST = 4,                  /* REALCONST  */
  YYSYMBOL_STRING = 5,                     /* STRING  */
  YYSYMBOL_IDENT = 6,                      /* IDENT  */
  YYSYMBOL_ASSIGN = 7,                     /* "="  */
  YYSYMBOL_PLUS = 8,                       /* "+"  */
  YYSYMBOL_MINUS = 9,                      /* "-"  */
  YYSYMBOL_MUL = 10,                       /* "*"  */
  YYSYMBOL_DIV = 11,                       /* "/"  */
  YYSYMBOL_MOD = 12,                       /* "%"  */
  YYSYMBOL_EQ = 13,                        /* "=="  */
  YYSYMBOL_NEQ = 14,                       /* "!="  */
  YYSYMBOL_INC = 15,                       /* "++"  */
  YYSYMBOL_DEC = 16,                       /* "--"  */
  YYSYMBOL_GT = 17,                        /* ">"  */
  YYSYMBOL_LT = 18,                        /* "<"  */
  YYSYMBOL_GTE = 19,                       /* ">="  */
  YYSYMBOL_LTE = 20,                       /* "<="  */
  YYSYMBOL_LBRACE = 21,                    /* "["  */
  YYSYMBOL_RBRACE = 22,                    /* "]"  */
  YYSYMBOL_LCBRACE = 23,                   /* "{"  */
  YYSYMBOL_RCBRACE = 24,                   /* "}"  */
  YYSYMBOL_LPAR = 25,                      /* "("  */
  YYSYMBOL_RPAR = 26,                      /* ")"  */
  YYSYMBOL_SEMI = 27,                      /* ";"  */
  YYSYMBOL_COMMA = 28,                     /* ","  */
  YYSYMBOL_COLON = 29,                     /* ":"  */
  YYSYMBOL_DCOLON = 30,                    /* "::"  */
  YYSYMBOL_DOT = 31,                       /* "."  */
  YYSYMBOL_DDOT = 32,                      /* ".."  */
  YYSYMBOL_UMINUS = 33,                    /* UMINUS  */
  YYSYMBOL_AND = 34,                       /* AND  */
  YYSYMBOL_OR = 35,                        /* OR  */
  YYSYMBOL_NOT = 36,                       /* NOT  */
  YYSYMBOL_IF = 37,                        /* IF  */
  YYSYMBOL_ELSE = 38,                      /* ELSE  */
  YYSYMBOL_WHILE = 39,                     /* WHILE  */
  YYSYMBOL_FOR = 40,                       /* FOR  */
  YYSYMBOL_FUNCTION = 41,                  /* FUNCTION  */
  YYSYMBOL_RETURN = 42,                    /* RETURN  */
  YYSYMBOL_BREAK = 43,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 44,                  /* CONTINUE  */
  YYSYMBOL_LOCAL = 45,                     /* LOCAL  */
  YYSYMBOL_TRUE = 46,                      /* TRUE  */
  YYSYMBOL_FALSE = 47,                     /* FALSE  */
  YYSYMBOL_NIL = 48,                       /* NIL  */
  YYSYMBOL_YYACCEPT = 49,                  /* $accept  */
  YYSYMBOL_program = 50,                   /* program  */
  YYSYMBOL_stmt = 51,                      /* stmt  */
  YYSYMBOL_expr = 52,                      /* expr  */
  YYSYMBOL_op = 53,                        /* op  */
  YYSYMBOL_term = 54,                      /* term  */
  YYSYMBOL_assignexpr = 55,                /* assignexpr  */
  YYSYMBOL_primary = 56,                   /* primary  */
  YYSYMBOL_lvalue = 57,                    /* lvalue  */
  YYSYMBOL_member = 58,                    /* member  */
  YYSYMBOL_call = 59,                      /* call  */
  YYSYMBOL_callsuffix = 60,                /* callsuffix  */
  YYSYMBOL_normcall = 61,                  /* normcall  */
  YYSYMBOL_methodcall = 62,                /* methodcall  */
  YYSYMBOL_com_expr_opt = 63,              /* com_expr_opt  */
  YYSYMBOL_objectdef = 64,                 /* objectdef  */
  YYSYMBOL_elist = 65,                     /* elist  */
  YYSYMBOL_indexed = 66,                   /* indexed  */
  YYSYMBOL_indexedelem = 67,               /* indexedelem  */
  YYSYMBOL_com_indexedelem_opt = 68,       /* com_indexedelem_opt  */
  YYSYMBOL_block = 69,                     /* block  */
  YYSYMBOL_stmtList = 70,                  /* stmtList  */
  YYSYMBOL_funcdef = 71,                   /* funcdef  */
  YYSYMBOL_id_opt = 72,                    /* id_opt  */
  YYSYMBOL_const = 73,                     /* const  */
  YYSYMBOL_idlist = 74,                    /* idlist  */
  YYSYMBOL_com_id_opt = 75,                /* com_id_opt  */
  YYSYMBOL_ifstmt = 76,                    /* ifstmt  */
  YYSYMBOL_else_stml_opt = 77,             /* else_stml_opt  */
  YYSYMBOL_whilestmt = 78,                 /* whilestmt  */
  YYSYMBOL_forstmt = 79,                   /* forstmt  */
  YYSYMBOL_returnstmt = 80,                /* returnstmt  */
  YYSYMBOL_expr_opt = 81                   /* expr_opt  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
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
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
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
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
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
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  68
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   547

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  93
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  161

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   303


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    63,    63,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    78,    79,    80,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      99,   100,   101,   102,   103,   104,   105,   106,   109,   112,
     113,   114,   115,   116,   119,   120,   121,   122,   125,   126,
     127,   128,   131,   132,   133,   136,   137,   140,   143,   146,
     147,   150,   151,   154,   155,   158,   159,   162,   165,   166,
     169,   172,   173,   176,   179,   180,   183,   184,   185,   186,
     187,   188,   191,   192,   195,   196,   199,   202,   203,   206,
     208,   210,   213,   214
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INTCONST",
  "REALCONST", "STRING", "IDENT", "\"=\"", "\"+\"", "\"-\"", "\"*\"",
  "\"/\"", "\"%\"", "\"==\"", "\"!=\"", "\"++\"", "\"--\"", "\">\"",
  "\"<\"", "\">=\"", "\"<=\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\"(\"",
  "\")\"", "\";\"", "\",\"", "\":\"", "\"::\"", "\".\"", "\"..\"",
  "UMINUS", "AND", "OR", "NOT", "IF", "ELSE", "WHILE", "FOR", "FUNCTION",
  "RETURN", "BREAK", "CONTINUE", "LOCAL", "TRUE", "FALSE", "NIL",
  "$accept", "program", "stmt", "expr", "op", "term", "assignexpr",
  "primary", "lvalue", "member", "call", "callsuffix", "normcall",
  "methodcall", "com_expr_opt", "objectdef", "elist", "indexed",
  "indexedelem", "com_indexedelem_opt", "block", "stmtList", "funcdef",
  "id_opt", "const", "idlist", "com_id_opt", "ifstmt", "else_stml_opt",
  "whilestmt", "forstmt", "returnstmt", "expr_opt", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-110)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      60,  -110,  -110,  -110,  -110,    -2,    -2,     9,    60,   108,
    -110,     3,   154,   154,    -5,    -3,     4,    25,   154,     6,
      17,    43,  -110,  -110,  -110,    58,    60,   253,  -110,  -110,
    -110,   136,  -110,    -4,  -110,  -110,  -110,  -110,  -110,  -110,
    -110,  -110,  -110,    18,   -15,    -4,   -15,   154,   282,    38,
      39,    34,    44,   295,    41,  -110,    33,    33,   154,   154,
     154,  -110,    45,   511,    46,  -110,  -110,  -110,  -110,  -110,
    -110,  -110,  -110,  -110,  -110,  -110,  -110,  -110,  -110,  -110,
    -110,  -110,  -110,  -110,  -110,   154,   154,  -110,  -110,   154,
      65,    66,  -110,  -110,  -110,   154,    68,    51,   324,   154,
    -110,  -110,  -110,    57,  -110,  -110,  -110,    59,   337,   366,
     395,    80,  -110,   511,   511,   195,    63,  -110,    69,   224,
      72,  -110,    59,   154,   282,    34,   154,    60,    60,   154,
      67,    83,  -110,  -110,   154,  -110,  -110,   424,  -110,  -110,
      84,    53,  -110,   453,   109,  -110,    94,    92,  -110,  -110,
      60,  -110,   154,    67,  -110,  -110,  -110,   482,  -110,    60,
    -110
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
      71,    76,    77,    78,    44,     0,     0,    63,    71,     0,
      12,     0,     0,     0,     0,     0,     0,    74,    92,     0,
       0,     0,    79,    80,    81,     0,    71,     0,    15,    13,
      37,    39,    47,    40,    41,    10,     2,    11,    43,     4,
       5,     6,     7,     0,    33,     0,    35,     0,    59,     0,
       0,    68,     0,     0,     0,    46,    31,    32,     0,     0,
       0,    75,     0,    93,     0,     8,     9,    45,     1,    72,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,     3,    27,    28,    29,     0,     0,    34,    36,    63,
       0,     0,    53,    55,    56,    63,     0,     0,     0,     0,
      64,    62,    61,     0,    66,    70,    30,    42,     0,     0,
       0,    82,    91,    14,    38,     0,     0,    48,     0,     0,
       0,    50,     0,     0,    59,    68,    63,     0,     0,     0,
      84,     0,    49,    57,    63,    51,    52,     0,    60,    69,
       0,    87,    89,     0,     0,    83,     0,     0,    67,    54,
       0,    86,     0,    84,    73,    58,    88,     0,    85,     0,
      90
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -110,  -110,  -109,    -7,  -110,  -110,  -110,  -110,    30,  -110,
      42,  -110,  -110,  -110,     1,  -110,   -88,  -110,    23,     5,
     -26,     0,    -6,  -110,  -110,  -110,   -32,  -110,  -110,  -110,
    -110,  -110,  -110
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    25,    26,    27,    85,    28,    29,    30,    31,    32,
      33,    92,    93,    94,   100,    34,    49,    50,    51,   104,
      35,    36,    37,    62,    38,   131,   145,    39,   151,    40,
      41,    42,    64
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      48,   116,    53,    54,     4,    56,    57,   120,    52,    55,
      89,    63,     1,     2,     3,     4,    90,    91,   141,   142,
      58,    95,    59,    43,     5,     6,    69,    96,    11,    60,
       7,    61,    47,    65,     9,    44,    46,    97,   140,    11,
      98,   156,    12,    21,    66,    13,   147,    45,    45,    67,
     160,   108,   109,   110,    21,    22,    23,    24,    68,    17,
     101,   102,   103,     1,     2,     3,     4,   107,   105,    84,
     111,   117,   118,   112,   121,     5,     6,   122,   113,   114,
      47,     7,   115,     8,   126,     9,   130,    10,   119,   133,
      11,   150,   124,    12,   134,   144,    13,    14,   136,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,   146,
     149,     1,     2,     3,     4,   153,   137,     8,   155,    48,
     154,   158,   143,     5,     6,   138,   125,    48,     0,     7,
     139,     0,     0,     9,     0,     0,     0,     0,    11,     0,
       0,    12,     0,    86,    13,   157,     0,     0,     0,    17,
       0,    87,    88,    21,    22,    23,    24,     1,     2,     3,
       4,    89,     0,     0,     0,     0,     0,    90,    91,     5,
       6,     0,     0,     0,     0,     7,     0,     0,     0,     9,
       0,     0,     0,     0,    11,     0,     0,    12,     0,     0,
      13,     0,     0,     0,     0,     0,     0,     0,     0,    21,
      22,    23,    24,    70,    71,    72,    73,    74,    75,    76,
       0,     0,    77,    78,    79,    80,     0,     0,     0,     0,
       0,   132,     0,    99,     0,     0,     0,     0,     0,    82,
      83,    84,    70,    71,    72,    73,    74,    75,    76,     0,
       0,    77,    78,    79,    80,     0,     0,     0,     0,     0,
     135,     0,    99,     0,     0,     0,     0,     0,    82,    83,
      84,    70,    71,    72,    73,    74,    75,    76,     0,     0,
      77,    78,    79,    80,     0,     0,     0,     0,     0,     0,
      81,     0,     0,     0,     0,     0,     0,    82,    83,    84,
      70,    71,    72,    73,    74,    75,    76,     0,     0,    77,
      78,    79,    80,    70,    71,    72,    73,    74,    75,    76,
      99,     0,    77,    78,    79,    80,    82,    83,    84,     0,
       0,   106,     0,     0,     0,     0,     0,     0,     0,    82,
      83,    84,    70,    71,    72,    73,    74,    75,    76,     0,
       0,    77,    78,    79,    80,    70,    71,    72,    73,    74,
      75,    76,     0,   123,    77,    78,    79,    80,    82,    83,
      84,     0,     0,   127,     0,     0,     0,     0,     0,     0,
       0,    82,    83,    84,    70,    71,    72,    73,    74,    75,
      76,     0,     0,    77,    78,    79,    80,     0,     0,     0,
       0,     0,   128,     0,     0,     0,     0,     0,     0,     0,
      82,    83,    84,    70,    71,    72,    73,    74,    75,    76,
       0,     0,    77,    78,    79,    80,     0,     0,     0,     0,
       0,     0,   129,     0,     0,     0,     0,     0,     0,    82,
      83,    84,    70,    71,    72,    73,    74,    75,    76,     0,
       0,    77,    78,    79,    80,     0,     0,     0,   148,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    82,    83,
      84,    70,    71,    72,    73,    74,    75,    76,     0,     0,
      77,    78,    79,    80,     0,     0,     0,     0,     0,     0,
     152,     0,     0,     0,     0,     0,     0,    82,    83,    84,
      70,    71,    72,    73,    74,    75,    76,     0,     0,    77,
      78,    79,    80,     0,     0,     0,     0,     0,   159,     0,
       0,     0,     0,     0,     0,     0,    82,    83,    84,    70,
      71,    72,    73,    74,    75,    76,     0,     0,    77,    78,
      79,    80,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    82,    83,    84
};

static const yytype_int16 yycheck[] =
{
       7,    89,     9,     9,     6,    12,    13,    95,     8,     6,
      25,    18,     3,     4,     5,     6,    31,    32,   127,   128,
      25,    25,    25,    25,    15,    16,    26,    31,    30,    25,
      21,     6,    23,    27,    25,     5,     6,    43,   126,    30,
      47,   150,    33,    45,    27,    36,   134,     5,     6,     6,
     159,    58,    59,    60,    45,    46,    47,    48,     0,    41,
      22,    22,    28,     3,     4,     5,     6,    26,    24,    36,
      25,     6,     6,    27,     6,    15,    16,    26,    85,    86,
      23,    21,    89,    23,    25,    25,     6,    27,    95,    26,
      30,    38,    99,    33,    25,    28,    36,    37,    26,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    26,
      26,     3,     4,     5,     6,     6,   123,    23,    26,   126,
     146,   153,   129,    15,    16,   124,   103,   134,    -1,    21,
     125,    -1,    -1,    25,    -1,    -1,    -1,    -1,    30,    -1,
      -1,    33,    -1,     7,    36,   152,    -1,    -1,    -1,    41,
      -1,    15,    16,    45,    46,    47,    48,     3,     4,     5,
       6,    25,    -1,    -1,    -1,    -1,    -1,    31,    32,    15,
      16,    -1,    -1,    -1,    -1,    21,    -1,    -1,    -1,    25,
      -1,    -1,    -1,    -1,    30,    -1,    -1,    33,    -1,    -1,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,
      46,    47,    48,     8,     9,    10,    11,    12,    13,    14,
      -1,    -1,    17,    18,    19,    20,    -1,    -1,    -1,    -1,
      -1,    26,    -1,    28,    -1,    -1,    -1,    -1,    -1,    34,
      35,    36,     8,     9,    10,    11,    12,    13,    14,    -1,
      -1,    17,    18,    19,    20,    -1,    -1,    -1,    -1,    -1,
      26,    -1,    28,    -1,    -1,    -1,    -1,    -1,    34,    35,
      36,     8,     9,    10,    11,    12,    13,    14,    -1,    -1,
      17,    18,    19,    20,    -1,    -1,    -1,    -1,    -1,    -1,
      27,    -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,
       8,     9,    10,    11,    12,    13,    14,    -1,    -1,    17,
      18,    19,    20,     8,     9,    10,    11,    12,    13,    14,
      28,    -1,    17,    18,    19,    20,    34,    35,    36,    -1,
      -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,
      35,    36,     8,     9,    10,    11,    12,    13,    14,    -1,
      -1,    17,    18,    19,    20,     8,     9,    10,    11,    12,
      13,    14,    -1,    29,    17,    18,    19,    20,    34,    35,
      36,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    34,    35,    36,     8,     9,    10,    11,    12,    13,
      14,    -1,    -1,    17,    18,    19,    20,    -1,    -1,    -1,
      -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      34,    35,    36,     8,     9,    10,    11,    12,    13,    14,
      -1,    -1,    17,    18,    19,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,    -1,    34,
      35,    36,     8,     9,    10,    11,    12,    13,    14,    -1,
      -1,    17,    18,    19,    20,    -1,    -1,    -1,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,    35,
      36,     8,     9,    10,    11,    12,    13,    14,    -1,    -1,
      17,    18,    19,    20,    -1,    -1,    -1,    -1,    -1,    -1,
      27,    -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,
       8,     9,    10,    11,    12,    13,    14,    -1,    -1,    17,
      18,    19,    20,    -1,    -1,    -1,    -1,    -1,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,     8,
       9,    10,    11,    12,    13,    14,    -1,    -1,    17,    18,
      19,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    34,    35,    36
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,    15,    16,    21,    23,    25,
      27,    30,    33,    36,    37,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    50,    51,    52,    54,    55,
      56,    57,    58,    59,    64,    69,    70,    71,    73,    76,
      78,    79,    80,    25,    57,    59,    57,    23,    52,    65,
      66,    67,    70,    52,    71,     6,    52,    52,    25,    25,
      25,     6,    72,    52,    81,    27,    27,     6,     0,    70,
       8,     9,    10,    11,    12,    13,    14,    17,    18,    19,
      20,    27,    34,    35,    36,    53,     7,    15,    16,    25,
      31,    32,    60,    61,    62,    25,    31,    71,    52,    28,
      63,    22,    22,    28,    68,    24,    26,    26,    52,    52,
      52,    25,    27,    52,    52,    52,    65,     6,     6,    52,
      65,     6,    26,    29,    52,    67,    25,    26,    26,    27,
       6,    74,    26,    26,    25,    26,    26,    52,    63,    68,
      65,    51,    51,    52,    28,    75,    26,    65,    24,    26,
      38,    77,    27,     6,    69,    26,    51,    52,    75,    26,
      51
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    49,    50,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    52,    52,    52,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      54,    54,    54,    54,    54,    54,    54,    54,    55,    56,
      56,    56,    56,    56,    57,    57,    57,    57,    58,    58,
      58,    58,    59,    59,    59,    60,    60,    61,    62,    63,
      63,    64,    64,    65,    65,    66,    66,    67,    68,    68,
      69,    70,    70,    71,    72,    72,    73,    73,    73,    73,
      73,    73,    74,    74,    75,    75,    76,    77,    77,    78,
      79,    80,    81,    81
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     2,     2,
       1,     1,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     2,     2,     2,     2,     2,     1,     3,     1,
       1,     1,     3,     1,     1,     2,     2,     1,     3,     4,
       3,     4,     4,     2,     6,     1,     1,     3,     5,     0,
       3,     3,     3,     0,     2,     0,     2,     5,     0,     3,
       3,     0,     2,     6,     0,     1,     1,     1,     1,     1,
       1,     1,     0,     2,     0,     3,     6,     0,     2,     5,
       9,     3,     0,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
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
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
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
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: stmtList  */
#line 63 "src/parser.y"
                                        {}
#line 1334 "src/parser.c"
    break;

  case 3: /* stmt: expr ";"  */
#line 66 "src/parser.y"
                                        {}
#line 1340 "src/parser.c"
    break;

  case 4: /* stmt: ifstmt  */
#line 67 "src/parser.y"
                                        {}
#line 1346 "src/parser.c"
    break;

  case 5: /* stmt: whilestmt  */
#line 68 "src/parser.y"
                                        {}
#line 1352 "src/parser.c"
    break;

  case 6: /* stmt: forstmt  */
#line 69 "src/parser.y"
                                        {}
#line 1358 "src/parser.c"
    break;

  case 7: /* stmt: returnstmt  */
#line 70 "src/parser.y"
                                        {}
#line 1364 "src/parser.c"
    break;

  case 8: /* stmt: BREAK ";"  */
#line 71 "src/parser.y"
                                        {}
#line 1370 "src/parser.c"
    break;

  case 9: /* stmt: CONTINUE ";"  */
#line 72 "src/parser.y"
                                        {}
#line 1376 "src/parser.c"
    break;

  case 10: /* stmt: block  */
#line 73 "src/parser.y"
                                        {}
#line 1382 "src/parser.c"
    break;

  case 11: /* stmt: funcdef  */
#line 74 "src/parser.y"
                                        {}
#line 1388 "src/parser.c"
    break;

  case 12: /* stmt: ";"  */
#line 75 "src/parser.y"
                                        {}
#line 1394 "src/parser.c"
    break;

  case 13: /* expr: assignexpr  */
#line 78 "src/parser.y"
                                        {}
#line 1400 "src/parser.c"
    break;

  case 14: /* expr: expr op expr  */
#line 79 "src/parser.y"
                                        {}
#line 1406 "src/parser.c"
    break;

  case 15: /* expr: term  */
#line 80 "src/parser.y"
                                        {}
#line 1412 "src/parser.c"
    break;

  case 16: /* op: "+"  */
#line 83 "src/parser.y"
                                        {}
#line 1418 "src/parser.c"
    break;

  case 17: /* op: "-"  */
#line 84 "src/parser.y"
                                        {}
#line 1424 "src/parser.c"
    break;

  case 18: /* op: "*"  */
#line 85 "src/parser.y"
                                        {}
#line 1430 "src/parser.c"
    break;

  case 19: /* op: "/"  */
#line 86 "src/parser.y"
                                        {}
#line 1436 "src/parser.c"
    break;

  case 20: /* op: "%"  */
#line 87 "src/parser.y"
                                        {}
#line 1442 "src/parser.c"
    break;

  case 21: /* op: "=="  */
#line 88 "src/parser.y"
                                        {}
#line 1448 "src/parser.c"
    break;

  case 22: /* op: "!="  */
#line 89 "src/parser.y"
                                        {}
#line 1454 "src/parser.c"
    break;

  case 23: /* op: ">"  */
#line 90 "src/parser.y"
                                        {}
#line 1460 "src/parser.c"
    break;

  case 24: /* op: "<"  */
#line 91 "src/parser.y"
                                        {}
#line 1466 "src/parser.c"
    break;

  case 25: /* op: ">="  */
#line 92 "src/parser.y"
                                        {}
#line 1472 "src/parser.c"
    break;

  case 26: /* op: "<="  */
#line 93 "src/parser.y"
                                        {}
#line 1478 "src/parser.c"
    break;

  case 27: /* op: AND  */
#line 94 "src/parser.y"
                                        {}
#line 1484 "src/parser.c"
    break;

  case 28: /* op: OR  */
#line 95 "src/parser.y"
                                        {}
#line 1490 "src/parser.c"
    break;

  case 29: /* op: NOT  */
#line 96 "src/parser.y"
                                        {}
#line 1496 "src/parser.c"
    break;

  case 30: /* term: "(" expr ")"  */
#line 99 "src/parser.y"
                                        {}
#line 1502 "src/parser.c"
    break;

  case 31: /* term: UMINUS expr  */
#line 100 "src/parser.y"
                                        {}
#line 1508 "src/parser.c"
    break;

  case 32: /* term: NOT expr  */
#line 101 "src/parser.y"
                                        {}
#line 1514 "src/parser.c"
    break;

  case 33: /* term: "++" lvalue  */
#line 102 "src/parser.y"
                                        {}
#line 1520 "src/parser.c"
    break;

  case 34: /* term: lvalue "++"  */
#line 103 "src/parser.y"
                                        {}
#line 1526 "src/parser.c"
    break;

  case 35: /* term: "--" lvalue  */
#line 104 "src/parser.y"
                                        {}
#line 1532 "src/parser.c"
    break;

  case 36: /* term: lvalue "--"  */
#line 105 "src/parser.y"
                                        {}
#line 1538 "src/parser.c"
    break;

  case 37: /* term: primary  */
#line 106 "src/parser.y"
                                        {}
#line 1544 "src/parser.c"
    break;

  case 38: /* assignexpr: lvalue "=" expr  */
#line 109 "src/parser.y"
                                        {}
#line 1550 "src/parser.c"
    break;

  case 39: /* primary: lvalue  */
#line 112 "src/parser.y"
                                        {}
#line 1556 "src/parser.c"
    break;

  case 40: /* primary: call  */
#line 113 "src/parser.y"
                                        {}
#line 1562 "src/parser.c"
    break;

  case 41: /* primary: objectdef  */
#line 114 "src/parser.y"
                                        {}
#line 1568 "src/parser.c"
    break;

  case 42: /* primary: "(" funcdef ")"  */
#line 115 "src/parser.y"
                                        {}
#line 1574 "src/parser.c"
    break;

  case 43: /* primary: const  */
#line 116 "src/parser.y"
                                        {}
#line 1580 "src/parser.c"
    break;

  case 44: /* lvalue: IDENT  */
#line 119 "src/parser.y"
                                        {}
#line 1586 "src/parser.c"
    break;

  case 45: /* lvalue: LOCAL IDENT  */
#line 120 "src/parser.y"
                                        {}
#line 1592 "src/parser.c"
    break;

  case 46: /* lvalue: "::" IDENT  */
#line 121 "src/parser.y"
                                        {}
#line 1598 "src/parser.c"
    break;

  case 47: /* lvalue: member  */
#line 122 "src/parser.y"
                                        {}
#line 1604 "src/parser.c"
    break;

  case 48: /* member: lvalue "." IDENT  */
#line 125 "src/parser.y"
                                        {}
#line 1610 "src/parser.c"
    break;

  case 49: /* member: lvalue "(" expr ")"  */
#line 126 "src/parser.y"
                                        {}
#line 1616 "src/parser.c"
    break;

  case 50: /* member: call "." IDENT  */
#line 127 "src/parser.y"
                                        {}
#line 1622 "src/parser.c"
    break;

  case 51: /* member: call "(" expr ")"  */
#line 128 "src/parser.y"
                                        {}
#line 1628 "src/parser.c"
    break;

  case 52: /* call: call "(" elist ")"  */
#line 131 "src/parser.y"
                                            {}
#line 1634 "src/parser.c"
    break;

  case 53: /* call: lvalue callsuffix  */
#line 132 "src/parser.y"
                                            {}
#line 1640 "src/parser.c"
    break;

  case 54: /* call: "(" funcdef ")" "(" elist ")"  */
#line 133 "src/parser.y"
                                            {}
#line 1646 "src/parser.c"
    break;

  case 55: /* callsuffix: normcall  */
#line 136 "src/parser.y"
                         {}
#line 1652 "src/parser.c"
    break;

  case 56: /* callsuffix: methodcall  */
#line 137 "src/parser.y"
                         {}
#line 1658 "src/parser.c"
    break;

  case 57: /* normcall: "(" elist ")"  */
#line 140 "src/parser.y"
                            {}
#line 1664 "src/parser.c"
    break;

  case 58: /* methodcall: ".." IDENT "(" elist ")"  */
#line 143 "src/parser.y"
                                       {}
#line 1670 "src/parser.c"
    break;

  case 61: /* objectdef: "[" indexed "]"  */
#line 150 "src/parser.y"
                              {}
#line 1676 "src/parser.c"
    break;

  case 62: /* objectdef: "[" elist "]"  */
#line 151 "src/parser.y"
                              {}
#line 1682 "src/parser.c"
    break;

  case 66: /* indexed: indexedelem com_indexedelem_opt  */
#line 159 "src/parser.y"
                                              {}
#line 1688 "src/parser.c"
    break;

  case 67: /* indexedelem: "{" expr ":" expr "}"  */
#line 162 "src/parser.y"
                                        {}
#line 1694 "src/parser.c"
    break;

  case 69: /* com_indexedelem_opt: "," indexedelem com_indexedelem_opt  */
#line 166 "src/parser.y"
                                                          {}
#line 1700 "src/parser.c"
    break;

  case 70: /* block: "{" stmtList "}"  */
#line 169 "src/parser.y"
                                   {}
#line 1706 "src/parser.c"
    break;

  case 72: /* stmtList: stmt stmtList  */
#line 173 "src/parser.y"
                                {}
#line 1712 "src/parser.c"
    break;

  case 73: /* funcdef: FUNCTION id_opt "(" idlist ")" block  */
#line 176 "src/parser.y"
                                                       {}
#line 1718 "src/parser.c"
    break;

  case 75: /* id_opt: IDENT  */
#line 180 "src/parser.y"
                {}
#line 1724 "src/parser.c"
    break;

  case 76: /* const: INTCONST  */
#line 183 "src/parser.y"
                            {}
#line 1730 "src/parser.c"
    break;

  case 77: /* const: REALCONST  */
#line 184 "src/parser.y"
                            {}
#line 1736 "src/parser.c"
    break;

  case 78: /* const: STRING  */
#line 185 "src/parser.y"
                            {}
#line 1742 "src/parser.c"
    break;

  case 79: /* const: TRUE  */
#line 186 "src/parser.y"
                            {}
#line 1748 "src/parser.c"
    break;

  case 80: /* const: FALSE  */
#line 187 "src/parser.y"
                            {}
#line 1754 "src/parser.c"
    break;

  case 81: /* const: NIL  */
#line 188 "src/parser.y"
                            {}
#line 1760 "src/parser.c"
    break;

  case 83: /* idlist: IDENT com_id_opt  */
#line 192 "src/parser.y"
                                   {}
#line 1766 "src/parser.c"
    break;

  case 85: /* com_id_opt: "," IDENT com_id_opt  */
#line 196 "src/parser.y"
                                       {}
#line 1772 "src/parser.c"
    break;

  case 86: /* ifstmt: IF "(" expr ")" stmt else_stml_opt  */
#line 199 "src/parser.y"
                                                     {}
#line 1778 "src/parser.c"
    break;


#line 1782 "src/parser.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 217 "src/parser.y"
