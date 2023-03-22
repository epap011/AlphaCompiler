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
#line 1 "phase2_yacc/src/parser.y"

    #include "yacc_util.h"

#line 75 "phase2_yacc/src/parser.c"

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
  YYSYMBOL_ASSIGN = 3,                     /* ASSIGN  */
  YYSYMBOL_PLUS = 4,                       /* PLUS  */
  YYSYMBOL_MINUS = 5,                      /* MINUS  */
  YYSYMBOL_MUL = 6,                        /* MUL  */
  YYSYMBOL_DIV = 7,                        /* DIV  */
  YYSYMBOL_MOD = 8,                        /* MOD  */
  YYSYMBOL_EQ = 9,                         /* EQ  */
  YYSYMBOL_NEQ = 10,                       /* NEQ  */
  YYSYMBOL_INC = 11,                       /* INC  */
  YYSYMBOL_DEC = 12,                       /* DEC  */
  YYSYMBOL_GT = 13,                        /* GT  */
  YYSYMBOL_LT = 14,                        /* LT  */
  YYSYMBOL_GTE = 15,                       /* GTE  */
  YYSYMBOL_LTE = 16,                       /* LTE  */
  YYSYMBOL_UMINUS = 17,                    /* UMINUS  */
  YYSYMBOL_AND = 18,                       /* AND  */
  YYSYMBOL_OR = 19,                        /* OR  */
  YYSYMBOL_NOT = 20,                       /* NOT  */
  YYSYMBOL_IF = 21,                        /* IF  */
  YYSYMBOL_ELSE = 22,                      /* ELSE  */
  YYSYMBOL_WHILE = 23,                     /* WHILE  */
  YYSYMBOL_FOR = 24,                       /* FOR  */
  YYSYMBOL_FUNCTION = 25,                  /* FUNCTION  */
  YYSYMBOL_RETURN = 26,                    /* RETURN  */
  YYSYMBOL_BREAK = 27,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 28,                  /* CONTINUE  */
  YYSYMBOL_LOCAL = 29,                     /* LOCAL  */
  YYSYMBOL_TRUE = 30,                      /* TRUE  */
  YYSYMBOL_FALSE = 31,                     /* FALSE  */
  YYSYMBOL_NIL = 32,                       /* NIL  */
  YYSYMBOL_LBRACE = 33,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 34,                    /* RBRACE  */
  YYSYMBOL_LCBRACE = 35,                   /* LCBRACE  */
  YYSYMBOL_RCBRACE = 36,                   /* RCBRACE  */
  YYSYMBOL_LPAR = 37,                      /* LPAR  */
  YYSYMBOL_RPAR = 38,                      /* RPAR  */
  YYSYMBOL_SEMI = 39,                      /* SEMI  */
  YYSYMBOL_COMMA = 40,                     /* COMMA  */
  YYSYMBOL_COLON = 41,                     /* COLON  */
  YYSYMBOL_DCOLON = 42,                    /* DCOLON  */
  YYSYMBOL_DOT = 43,                       /* DOT  */
  YYSYMBOL_DDOT = 44,                      /* DDOT  */
  YYSYMBOL_IDENT = 45,                     /* IDENT  */
  YYSYMBOL_STRING = 46,                    /* STRING  */
  YYSYMBOL_INTCONST = 47,                  /* INTCONST  */
  YYSYMBOL_REALCONST = 48,                 /* REALCONST  */
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
  YYSYMBOL_elist = 63,                     /* elist  */
  YYSYMBOL_objectdef = 64,                 /* objectdef  */
  YYSYMBOL_indexed = 65,                   /* indexed  */
  YYSYMBOL_indexedelem = 66,               /* indexedelem  */
  YYSYMBOL_block = 67,                     /* block  */
  YYSYMBOL_funcdef = 68,                   /* funcdef  */
  YYSYMBOL_const = 69,                     /* const  */
  YYSYMBOL_idlist = 70,                    /* idlist  */
  YYSYMBOL_ifstmt = 71,                    /* ifstmt  */
  YYSYMBOL_whilestmt = 72,                 /* whilestmt  */
  YYSYMBOL_forstmt = 73,                   /* forstmt  */
  YYSYMBOL_stmtList = 74,                  /* stmtList  */
  YYSYMBOL_returnstmt = 75,                /* returnstmt  */
  YYSYMBOL_com_indexedelem_opt = 76,       /* com_indexedelem_opt  */
  YYSYMBOL_com_expr_opt = 77,              /* com_expr_opt  */
  YYSYMBOL_semi_opt = 78                   /* semi_opt  */
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
#define YYFINAL  66
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   557

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  87
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  162

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
       0,    30,    30,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    45,    46,    47,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      66,    67,    68,    69,    70,    71,    72,    73,    76,    79,
      80,    81,    82,    83,    86,    87,    88,    89,    92,    93,
      94,    95,    98,    99,   100,   103,   104,   107,   110,   113,
     114,   117,   118,   121,   125,   128,   131,   134,   135,   136,
     137,   138,   139,   142,   143,   144,   147,   149,   151,   153,
     154,   157,   160,   161,   164,   165,   168,   169
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
  "\"end of file\"", "error", "\"invalid token\"", "ASSIGN", "PLUS",
  "MINUS", "MUL", "DIV", "MOD", "EQ", "NEQ", "INC", "DEC", "GT", "LT",
  "GTE", "LTE", "UMINUS", "AND", "OR", "NOT", "IF", "ELSE", "WHILE", "FOR",
  "FUNCTION", "RETURN", "BREAK", "CONTINUE", "LOCAL", "TRUE", "FALSE",
  "NIL", "LBRACE", "RBRACE", "LCBRACE", "RCBRACE", "LPAR", "RPAR", "SEMI",
  "COMMA", "COLON", "DCOLON", "DOT", "DDOT", "IDENT", "STRING", "INTCONST",
  "REALCONST", "$accept", "program", "stmt", "expr", "op", "term",
  "assignexpr", "primary", "lvalue", "member", "call", "callsuffix",
  "normcall", "methodcall", "elist", "objectdef", "indexed", "indexedelem",
  "block", "funcdef", "const", "idlist", "ifstmt", "whilestmt", "forstmt",
  "stmtList", "returnstmt", "com_indexedelem_opt", "com_expr_opt",
  "semi_opt", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-121)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     127,    83,    83,   191,   191,   -32,   -27,   -25,    -6,   191,
       3,    10,    15,  -121,  -121,  -121,   159,    76,  -121,    23,
    -121,  -121,  -121,  -121,    55,   127,   330,  -121,  -121,  -121,
       8,  -121,     1,  -121,  -121,  -121,  -121,  -121,  -121,  -121,
    -121,  -121,    34,    46,     1,    46,   223,    49,    49,   191,
     191,   191,    37,   352,  -121,  -121,  -121,   159,   285,    42,
      50,    54,    63,   408,    44,  -121,  -121,  -121,  -121,  -121,
    -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,
    -121,  -121,  -121,   191,   191,  -121,  -121,   191,   191,    58,
      64,  -121,  -121,  -121,   191,   191,    65,    62,   223,   313,
     429,   446,   369,    69,  -121,  -121,    17,   191,  -121,  -121,
    -121,    67,  -121,  -121,  -121,  -121,   537,   537,   503,    77,
    -121,    79,   520,    81,  -121,    80,    57,   127,   127,   191,
      87,    92,   191,   313,   191,  -121,   191,  -121,  -121,   191,
    -121,  -121,  -121,  -121,   391,    69,    97,   484,  -121,   268,
      96,    99,   191,  -121,   127,  -121,  -121,  -121,  -121,   467,
     127,  -121
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
      79,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    70,    71,    72,    59,     0,    12,     0,
      44,    69,    67,    68,     0,    79,     0,    15,    13,    37,
      39,    47,    40,    41,    10,    11,    43,     4,     5,     6,
       2,     7,     0,    33,     0,    35,    59,    31,    32,     0,
       0,     0,     0,    87,     8,     9,    45,    59,    84,     0,
       0,    82,     0,     0,     0,    46,     1,    80,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,     3,     0,     0,    34,    36,     0,    59,     0,
       0,    53,    55,    56,     0,    59,     0,     0,    59,    84,
       0,     0,     0,    73,    86,    81,    84,     0,    60,    61,
      62,     0,    63,    65,    30,    42,    14,    38,     0,     0,
      48,     0,     0,     0,    50,     0,    84,     0,     0,     0,
      75,     0,     0,    84,     0,    83,    59,    49,    57,    59,
      51,    52,    76,    77,     0,    73,     0,     0,    85,     0,
       0,     0,     0,    74,    79,    66,    64,    54,    58,     0,
       0,    78
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -121,  -121,  -120,    -3,  -121,  -121,  -121,  -121,    14,  -121,
      16,  -121,  -121,  -121,   -86,  -121,  -121,    24,    -5,   -14,
    -121,    -2,  -121,  -121,  -121,     4,  -121,  -121,     7,  -121
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    24,    25,    26,    83,    27,    28,    29,    30,    31,
      32,    91,    92,    93,    59,    33,    60,    61,    34,    35,
      36,   131,    37,    38,    39,    62,    41,   112,   108,   105
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      47,    48,   119,    64,    40,    49,    53,   142,   143,   123,
      50,    84,    51,    58,    63,    43,    45,    44,    44,    85,
      86,    68,    69,    70,    71,    72,    73,    74,    97,    67,
      75,    76,    77,    78,    94,    79,    80,    81,    95,    52,
     161,    87,    54,    99,    96,    88,   100,   101,   102,    55,
     150,    89,    90,   151,   106,    66,    82,   107,   132,     8,
      56,    68,    69,    70,    71,    72,    73,    74,    65,    81,
      75,    76,    77,    78,   103,    79,    80,    81,   109,    87,
     116,   117,   115,    88,   118,    99,   110,     1,     2,    89,
      90,   122,    99,     3,   111,   126,     4,   107,   132,   113,
     125,     8,   134,   120,   133,    12,    13,    14,    15,   121,
     124,    46,    12,    17,   130,   138,   139,   136,    19,   141,
      42,    20,    21,    22,    23,    19,   144,   145,    20,   147,
     146,   149,   154,    99,   157,   135,    99,   158,     1,     2,
     148,   155,     0,   153,     3,     0,     0,     4,     5,   159,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
       0,     0,    16,     0,    17,     0,    18,     0,     0,    19,
       1,     2,    20,    21,    22,    23,     3,     0,     0,     4,
       5,     0,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,     0,     0,    57,     0,    17,     0,    18,     0,
       0,    19,     1,     2,    20,    21,    22,    23,     3,     0,
       0,     4,     0,     0,     0,     0,     0,     0,     0,     0,
      12,    13,    14,    15,     0,     0,    46,     0,    17,     0,
       0,     0,     0,    19,     1,     2,    20,    21,    22,    23,
       3,     0,     0,     4,     0,     0,     0,     0,     0,     0,
       0,     0,    12,    13,    14,    15,     0,     0,    98,     0,
      17,     0,     0,     0,     0,    19,     0,     0,    20,    21,
      22,    23,    68,    69,    70,    71,    72,    73,    74,     0,
       0,    75,    76,    77,    78,     0,    79,    80,    81,    68,
      69,    70,    71,    72,    73,    74,     0,     0,    75,    76,
      77,    78,     0,    79,    80,    81,     0,     0,     0,   132,
       0,     0,     0,     0,     0,     0,     0,    68,    69,    70,
      71,    72,    73,    74,    82,   107,    75,    76,    77,    78,
       0,    79,    80,    81,    68,    69,    70,    71,    72,    73,
      74,     0,     0,    75,    76,    77,    78,     0,    79,    80,
      81,     0,     0,   107,     0,     0,    68,    69,    70,    71,
      72,    73,    74,     0,     0,    75,    76,    77,    78,    82,
      79,    80,    81,    68,    69,    70,    71,    72,    73,    74,
       0,     0,    75,    76,    77,    78,     0,    79,    80,    81,
       0,   104,     0,     0,     0,    68,    69,    70,    71,    72,
      73,    74,     0,     0,    75,    76,    77,    78,   129,    79,
      80,    81,    68,    69,    70,    71,    72,    73,    74,     0,
       0,    75,    76,    77,    78,     0,    79,    80,    81,     0,
     152,     0,     0,    68,    69,    70,    71,    72,    73,    74,
       0,     0,    75,    76,    77,    78,   114,    79,    80,    81,
      68,    69,    70,    71,    72,    73,    74,     0,     0,    75,
      76,    77,    78,     0,    79,    80,    81,   127,     0,     0,
       0,    68,    69,    70,    71,    72,    73,    74,     0,     0,
      75,    76,    77,    78,   128,    79,    80,    81,    68,    69,
      70,    71,    72,    73,    74,     0,     0,    75,    76,    77,
      78,     0,    79,    80,    81,   160,     0,    68,    69,    70,
      71,    72,    73,    74,     0,     0,    75,    76,    77,    78,
     156,    79,    80,    81,    68,    69,    70,    71,    72,    73,
      74,     0,     0,    75,    76,    77,    78,   137,    79,    80,
      81,    68,    69,    70,    71,    72,    73,    74,     0,     0,
      75,    76,    77,    78,   140,    79,    80,    81
};

static const yytype_int16 yycheck[] =
{
       3,     4,    88,    17,     0,    37,     9,   127,   128,    95,
      37,     3,    37,    16,    17,     1,     2,     1,     2,    11,
      12,     4,     5,     6,     7,     8,     9,    10,    42,    25,
      13,    14,    15,    16,    33,    18,    19,    20,    37,    45,
     160,    33,    39,    46,    43,    37,    49,    50,    51,    39,
     136,    43,    44,   139,    57,     0,    39,    40,    41,    25,
      45,     4,     5,     6,     7,     8,     9,    10,    45,    20,
      13,    14,    15,    16,    37,    18,    19,    20,    36,    33,
      83,    84,    38,    37,    87,    88,    36,    11,    12,    43,
      44,    94,    95,    17,    40,    98,    20,    40,    41,    36,
      38,    25,    35,    45,   107,    29,    30,    31,    32,    45,
      45,    35,    29,    37,    45,    38,    37,    37,    42,    38,
      37,    45,    46,    47,    48,    42,   129,    40,    45,   132,
      38,   134,    35,   136,    38,   111,   139,    38,    11,    12,
     133,   146,    -1,   145,    17,    -1,    -1,    20,    21,   152,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      -1,    -1,    35,    -1,    37,    -1,    39,    -1,    -1,    42,
      11,    12,    45,    46,    47,    48,    17,    -1,    -1,    20,
      21,    -1,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    -1,    -1,    35,    -1,    37,    -1,    39,    -1,
      -1,    42,    11,    12,    45,    46,    47,    48,    17,    -1,
      -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      29,    30,    31,    32,    -1,    -1,    35,    -1,    37,    -1,
      -1,    -1,    -1,    42,    11,    12,    45,    46,    47,    48,
      17,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    29,    30,    31,    32,    -1,    -1,    35,    -1,
      37,    -1,    -1,    -1,    -1,    42,    -1,    -1,    45,    46,
      47,    48,     4,     5,     6,     7,     8,     9,    10,    -1,
      -1,    13,    14,    15,    16,    -1,    18,    19,    20,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,    13,    14,
      15,    16,    -1,    18,    19,    20,    -1,    -1,    -1,    41,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     4,     5,     6,
       7,     8,     9,    10,    39,    40,    13,    14,    15,    16,
      -1,    18,    19,    20,     4,     5,     6,     7,     8,     9,
      10,    -1,    -1,    13,    14,    15,    16,    -1,    18,    19,
      20,    -1,    -1,    40,    -1,    -1,     4,     5,     6,     7,
       8,     9,    10,    -1,    -1,    13,    14,    15,    16,    39,
      18,    19,    20,     4,     5,     6,     7,     8,     9,    10,
      -1,    -1,    13,    14,    15,    16,    -1,    18,    19,    20,
      -1,    39,    -1,    -1,    -1,     4,     5,     6,     7,     8,
       9,    10,    -1,    -1,    13,    14,    15,    16,    39,    18,
      19,    20,     4,     5,     6,     7,     8,     9,    10,    -1,
      -1,    13,    14,    15,    16,    -1,    18,    19,    20,    -1,
      39,    -1,    -1,     4,     5,     6,     7,     8,     9,    10,
      -1,    -1,    13,    14,    15,    16,    38,    18,    19,    20,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,    13,
      14,    15,    16,    -1,    18,    19,    20,    38,    -1,    -1,
      -1,     4,     5,     6,     7,     8,     9,    10,    -1,    -1,
      13,    14,    15,    16,    38,    18,    19,    20,     4,     5,
       6,     7,     8,     9,    10,    -1,    -1,    13,    14,    15,
      16,    -1,    18,    19,    20,    38,    -1,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,    13,    14,    15,    16,
      36,    18,    19,    20,     4,     5,     6,     7,     8,     9,
      10,    -1,    -1,    13,    14,    15,    16,    34,    18,    19,
      20,     4,     5,     6,     7,     8,     9,    10,    -1,    -1,
      13,    14,    15,    16,    34,    18,    19,    20
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    11,    12,    17,    20,    21,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    35,    37,    39,    42,
      45,    46,    47,    48,    50,    51,    52,    54,    55,    56,
      57,    58,    59,    64,    67,    68,    69,    71,    72,    73,
      74,    75,    37,    57,    59,    57,    35,    52,    52,    37,
      37,    37,    45,    52,    39,    39,    45,    35,    52,    63,
      65,    66,    74,    52,    68,    45,     0,    74,     4,     5,
       6,     7,     8,     9,    10,    13,    14,    15,    16,    18,
      19,    20,    39,    53,     3,    11,    12,    33,    37,    43,
      44,    60,    61,    62,    33,    37,    43,    68,    35,    52,
      52,    52,    52,    37,    39,    78,    52,    40,    77,    36,
      36,    40,    76,    36,    38,    38,    52,    52,    52,    63,
      45,    45,    52,    63,    45,    38,    52,    38,    38,    39,
      45,    70,    41,    52,    35,    66,    37,    34,    38,    37,
      34,    38,    51,    51,    52,    40,    38,    52,    77,    52,
      63,    63,    39,    70,    35,    67,    36,    38,    38,    52,
      38,    51
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
      63,    64,    64,    65,    66,    67,    68,    69,    69,    69,
      69,    69,    69,    70,    70,    70,    71,    72,    73,    74,
      74,    75,    76,    76,    77,    77,    78,    78
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
       2,     3,     3,     2,     5,     3,     6,     1,     1,     1,
       1,     1,     1,     0,     3,     1,     5,     5,     9,     0,
       2,     3,     0,     2,     0,     3,     1,     0
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
#line 30 "phase2_yacc/src/parser.y"
                                        {}
#line 1327 "phase2_yacc/src/parser.c"
    break;

  case 3: /* stmt: expr SEMI  */
#line 33 "phase2_yacc/src/parser.y"
                                        {}
#line 1333 "phase2_yacc/src/parser.c"
    break;

  case 4: /* stmt: ifstmt  */
#line 34 "phase2_yacc/src/parser.y"
                                        {}
#line 1339 "phase2_yacc/src/parser.c"
    break;

  case 5: /* stmt: whilestmt  */
#line 35 "phase2_yacc/src/parser.y"
                                        {}
#line 1345 "phase2_yacc/src/parser.c"
    break;

  case 6: /* stmt: forstmt  */
#line 36 "phase2_yacc/src/parser.y"
                                        {}
#line 1351 "phase2_yacc/src/parser.c"
    break;

  case 7: /* stmt: returnstmt  */
#line 37 "phase2_yacc/src/parser.y"
                                        {}
#line 1357 "phase2_yacc/src/parser.c"
    break;

  case 8: /* stmt: BREAK SEMI  */
#line 38 "phase2_yacc/src/parser.y"
                                        {}
#line 1363 "phase2_yacc/src/parser.c"
    break;

  case 9: /* stmt: CONTINUE SEMI  */
#line 39 "phase2_yacc/src/parser.y"
                                        {}
#line 1369 "phase2_yacc/src/parser.c"
    break;

  case 10: /* stmt: block  */
#line 40 "phase2_yacc/src/parser.y"
                                        {}
#line 1375 "phase2_yacc/src/parser.c"
    break;

  case 11: /* stmt: funcdef  */
#line 41 "phase2_yacc/src/parser.y"
                                        {}
#line 1381 "phase2_yacc/src/parser.c"
    break;

  case 12: /* stmt: SEMI  */
#line 42 "phase2_yacc/src/parser.y"
                                        {}
#line 1387 "phase2_yacc/src/parser.c"
    break;

  case 13: /* expr: assignexpr  */
#line 45 "phase2_yacc/src/parser.y"
                                        {}
#line 1393 "phase2_yacc/src/parser.c"
    break;

  case 14: /* expr: expr op expr  */
#line 46 "phase2_yacc/src/parser.y"
                                        {}
#line 1399 "phase2_yacc/src/parser.c"
    break;

  case 15: /* expr: term  */
#line 47 "phase2_yacc/src/parser.y"
                                        {}
#line 1405 "phase2_yacc/src/parser.c"
    break;

  case 16: /* op: PLUS  */
#line 50 "phase2_yacc/src/parser.y"
                                        {}
#line 1411 "phase2_yacc/src/parser.c"
    break;

  case 17: /* op: MINUS  */
#line 51 "phase2_yacc/src/parser.y"
                                        {}
#line 1417 "phase2_yacc/src/parser.c"
    break;

  case 18: /* op: MUL  */
#line 52 "phase2_yacc/src/parser.y"
                                        {}
#line 1423 "phase2_yacc/src/parser.c"
    break;

  case 19: /* op: DIV  */
#line 53 "phase2_yacc/src/parser.y"
                                        {}
#line 1429 "phase2_yacc/src/parser.c"
    break;

  case 20: /* op: MOD  */
#line 54 "phase2_yacc/src/parser.y"
                                        {}
#line 1435 "phase2_yacc/src/parser.c"
    break;

  case 21: /* op: EQ  */
#line 55 "phase2_yacc/src/parser.y"
                                        {}
#line 1441 "phase2_yacc/src/parser.c"
    break;

  case 22: /* op: NEQ  */
#line 56 "phase2_yacc/src/parser.y"
                                        {}
#line 1447 "phase2_yacc/src/parser.c"
    break;

  case 23: /* op: GT  */
#line 57 "phase2_yacc/src/parser.y"
                                        {}
#line 1453 "phase2_yacc/src/parser.c"
    break;

  case 24: /* op: LT  */
#line 58 "phase2_yacc/src/parser.y"
                                        {}
#line 1459 "phase2_yacc/src/parser.c"
    break;

  case 25: /* op: GTE  */
#line 59 "phase2_yacc/src/parser.y"
                                        {}
#line 1465 "phase2_yacc/src/parser.c"
    break;

  case 26: /* op: LTE  */
#line 60 "phase2_yacc/src/parser.y"
                                        {}
#line 1471 "phase2_yacc/src/parser.c"
    break;

  case 27: /* op: AND  */
#line 61 "phase2_yacc/src/parser.y"
                                        {}
#line 1477 "phase2_yacc/src/parser.c"
    break;

  case 28: /* op: OR  */
#line 62 "phase2_yacc/src/parser.y"
                                        {}
#line 1483 "phase2_yacc/src/parser.c"
    break;

  case 29: /* op: NOT  */
#line 63 "phase2_yacc/src/parser.y"
                                        {}
#line 1489 "phase2_yacc/src/parser.c"
    break;

  case 30: /* term: LPAR expr RPAR  */
#line 66 "phase2_yacc/src/parser.y"
                                        {}
#line 1495 "phase2_yacc/src/parser.c"
    break;

  case 31: /* term: UMINUS expr  */
#line 67 "phase2_yacc/src/parser.y"
                                        {}
#line 1501 "phase2_yacc/src/parser.c"
    break;

  case 32: /* term: NOT expr  */
#line 68 "phase2_yacc/src/parser.y"
                                        {}
#line 1507 "phase2_yacc/src/parser.c"
    break;

  case 33: /* term: INC lvalue  */
#line 69 "phase2_yacc/src/parser.y"
                                        {}
#line 1513 "phase2_yacc/src/parser.c"
    break;

  case 34: /* term: lvalue INC  */
#line 70 "phase2_yacc/src/parser.y"
                                        {}
#line 1519 "phase2_yacc/src/parser.c"
    break;

  case 35: /* term: DEC lvalue  */
#line 71 "phase2_yacc/src/parser.y"
                                        {}
#line 1525 "phase2_yacc/src/parser.c"
    break;

  case 36: /* term: lvalue DEC  */
#line 72 "phase2_yacc/src/parser.y"
                                        {}
#line 1531 "phase2_yacc/src/parser.c"
    break;

  case 37: /* term: primary  */
#line 73 "phase2_yacc/src/parser.y"
                                        {}
#line 1537 "phase2_yacc/src/parser.c"
    break;

  case 38: /* assignexpr: lvalue ASSIGN expr  */
#line 76 "phase2_yacc/src/parser.y"
                                        {}
#line 1543 "phase2_yacc/src/parser.c"
    break;

  case 39: /* primary: lvalue  */
#line 79 "phase2_yacc/src/parser.y"
                                        {}
#line 1549 "phase2_yacc/src/parser.c"
    break;

  case 40: /* primary: call  */
#line 80 "phase2_yacc/src/parser.y"
                                        {}
#line 1555 "phase2_yacc/src/parser.c"
    break;

  case 41: /* primary: objectdef  */
#line 81 "phase2_yacc/src/parser.y"
                                        {}
#line 1561 "phase2_yacc/src/parser.c"
    break;

  case 42: /* primary: LPAR funcdef RPAR  */
#line 82 "phase2_yacc/src/parser.y"
                                        {}
#line 1567 "phase2_yacc/src/parser.c"
    break;

  case 43: /* primary: const  */
#line 83 "phase2_yacc/src/parser.y"
                                        {}
#line 1573 "phase2_yacc/src/parser.c"
    break;

  case 44: /* lvalue: IDENT  */
#line 86 "phase2_yacc/src/parser.y"
                                        {}
#line 1579 "phase2_yacc/src/parser.c"
    break;

  case 45: /* lvalue: LOCAL IDENT  */
#line 87 "phase2_yacc/src/parser.y"
                                        {}
#line 1585 "phase2_yacc/src/parser.c"
    break;

  case 46: /* lvalue: DCOLON IDENT  */
#line 88 "phase2_yacc/src/parser.y"
                                        {}
#line 1591 "phase2_yacc/src/parser.c"
    break;

  case 47: /* lvalue: member  */
#line 89 "phase2_yacc/src/parser.y"
                                        {}
#line 1597 "phase2_yacc/src/parser.c"
    break;

  case 48: /* member: lvalue DOT IDENT  */
#line 92 "phase2_yacc/src/parser.y"
                                        {}
#line 1603 "phase2_yacc/src/parser.c"
    break;

  case 49: /* member: lvalue LBRACE expr RBRACE  */
#line 93 "phase2_yacc/src/parser.y"
                                        {}
#line 1609 "phase2_yacc/src/parser.c"
    break;

  case 50: /* member: call DOT IDENT  */
#line 94 "phase2_yacc/src/parser.y"
                                        {}
#line 1615 "phase2_yacc/src/parser.c"
    break;

  case 51: /* member: call LBRACE expr RBRACE  */
#line 95 "phase2_yacc/src/parser.y"
                                        {}
#line 1621 "phase2_yacc/src/parser.c"
    break;


#line 1625 "phase2_yacc/src/parser.c"

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

#line 172 "phase2_yacc/src/parser.y"

