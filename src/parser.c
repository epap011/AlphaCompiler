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
  YYSYMBOL_ASSIGN = 7,                     /* ASSIGN  */
  YYSYMBOL_PLUS = 8,                       /* PLUS  */
  YYSYMBOL_MINUS = 9,                      /* MINUS  */
  YYSYMBOL_MUL = 10,                       /* MUL  */
  YYSYMBOL_DIV = 11,                       /* DIV  */
  YYSYMBOL_MOD = 12,                       /* MOD  */
  YYSYMBOL_EQ = 13,                        /* EQ  */
  YYSYMBOL_NEQ = 14,                       /* NEQ  */
  YYSYMBOL_INC = 15,                       /* INC  */
  YYSYMBOL_DEC = 16,                       /* DEC  */
  YYSYMBOL_GT = 17,                        /* GT  */
  YYSYMBOL_LT = 18,                        /* LT  */
  YYSYMBOL_GTE = 19,                       /* GTE  */
  YYSYMBOL_LTE = 20,                       /* LTE  */
  YYSYMBOL_UMINUS = 21,                    /* UMINUS  */
  YYSYMBOL_AND = 22,                       /* AND  */
  YYSYMBOL_OR = 23,                        /* OR  */
  YYSYMBOL_NOT = 24,                       /* NOT  */
  YYSYMBOL_IF = 25,                        /* IF  */
  YYSYMBOL_ELSE = 26,                      /* ELSE  */
  YYSYMBOL_WHILE = 27,                     /* WHILE  */
  YYSYMBOL_FOR = 28,                       /* FOR  */
  YYSYMBOL_FUNCTION = 29,                  /* FUNCTION  */
  YYSYMBOL_RETURN = 30,                    /* RETURN  */
  YYSYMBOL_BREAK = 31,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 32,                  /* CONTINUE  */
  YYSYMBOL_LOCAL = 33,                     /* LOCAL  */
  YYSYMBOL_TRUE = 34,                      /* TRUE  */
  YYSYMBOL_FALSE = 35,                     /* FALSE  */
  YYSYMBOL_NIL = 36,                       /* NIL  */
  YYSYMBOL_LBRACE = 37,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 38,                    /* RBRACE  */
  YYSYMBOL_LCBRACE = 39,                   /* LCBRACE  */
  YYSYMBOL_RCBRACE = 40,                   /* RCBRACE  */
  YYSYMBOL_LPAR = 41,                      /* LPAR  */
  YYSYMBOL_RPAR = 42,                      /* RPAR  */
  YYSYMBOL_SEMI = 43,                      /* SEMI  */
  YYSYMBOL_COMMA = 44,                     /* COMMA  */
  YYSYMBOL_COLON = 45,                     /* COLON  */
  YYSYMBOL_DCOLON = 46,                    /* DCOLON  */
  YYSYMBOL_DOT = 47,                       /* DOT  */
  YYSYMBOL_DDOT = 48,                      /* DDOT  */
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
#define YYLAST   565

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
       0,    36,    36,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    51,    52,    53,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      72,    73,    74,    75,    76,    77,    78,    79,    82,    85,
      86,    87,    88,    89,    92,    93,    94,    95,    98,    99,
     100,   101,   104,   105,   106,   109,   110,   113,   116,   119,
     120,   123,   124,   127,   131,   134,   137,   140,   141,   142,
     143,   144,   145,   148,   149,   150,   153,   155,   157,   159,
     160,   163,   166,   167,   170,   171,   174,   175
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
  "REALCONST", "STRING", "IDENT", "ASSIGN", "PLUS", "MINUS", "MUL", "DIV",
  "MOD", "EQ", "NEQ", "INC", "DEC", "GT", "LT", "GTE", "LTE", "UMINUS",
  "AND", "OR", "NOT", "IF", "ELSE", "WHILE", "FOR", "FUNCTION", "RETURN",
  "BREAK", "CONTINUE", "LOCAL", "TRUE", "FALSE", "NIL", "LBRACE", "RBRACE",
  "LCBRACE", "RCBRACE", "LPAR", "RPAR", "SEMI", "COMMA", "COLON", "DCOLON",
  "DOT", "DDOT", "$accept", "program", "stmt", "expr", "op", "term",
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

#define YYPACT_NINF (-120)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      32,  -120,  -120,  -120,  -120,    -1,    -1,   170,   170,   -37,
     -34,   -13,    16,   170,    -9,     3,    43,  -120,  -120,  -120,
      80,   131,  -120,    49,    72,    32,   334,  -120,  -120,  -120,
      83,  -120,    56,  -120,  -120,  -120,  -120,  -120,  -120,  -120,
    -120,  -120,    45,   101,    56,   101,   209,    55,    55,   170,
     170,   170,    41,   351,  -120,  -120,  -120,    80,   294,    52,
      54,    58,    66,   412,    47,  -120,  -120,  -120,  -120,  -120,
    -120,  -120,  -120,  -120,  -120,  -120,  -120,  -120,  -120,  -120,
    -120,  -120,  -120,   170,   170,  -120,  -120,   170,   170,   111,
     112,  -120,  -120,  -120,   170,   170,   122,    91,   209,   311,
     429,   450,   373,   133,  -120,  -120,   248,   170,  -120,  -120,
    -120,   102,  -120,  -120,  -120,  -120,   541,   541,   507,    98,
    -120,   103,   524,   108,  -120,   110,   265,    32,    32,   170,
      99,   114,   170,   311,   170,  -120,   170,  -120,  -120,   170,
    -120,  -120,  -120,  -120,   390,   133,   115,   488,  -120,     7,
     116,   117,   170,  -120,    32,  -120,  -120,  -120,  -120,   467,
      32,  -120
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
      79,    67,    68,    69,    44,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    70,    71,    72,
      59,     0,    12,     0,     0,    79,     0,    15,    13,    37,
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
    -120,  -120,  -119,    -7,  -120,  -120,  -120,  -120,     6,  -120,
      64,  -120,  -120,  -120,   -85,  -120,  -120,    42,    11,   -19,
    -120,    17,  -120,  -120,  -120,    33,  -120,  -120,    28,  -120
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
      47,    48,    64,   119,    49,     4,    53,    50,   142,   143,
     123,    43,    45,    58,    63,    68,    69,    70,    71,    72,
      73,    74,    52,    97,    75,    76,    77,    78,    51,    79,
      80,    81,    16,    40,    54,     1,     2,     3,     4,    99,
      42,   161,   100,   101,   102,    23,    55,     5,     6,    56,
     106,   150,   132,     7,   151,    65,     8,     9,    67,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    44,
      44,    20,    66,    21,    12,    22,   116,   117,    23,    81,
     118,    99,   103,     1,     2,     3,     4,   122,    99,   115,
      84,   126,   109,    94,   110,     5,     6,    95,    85,    86,
     133,     7,   111,    96,     8,     9,   113,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,   120,   121,    57,
      87,    21,   144,    22,    88,   147,    23,   149,   124,    99,
      89,    90,    99,   125,     1,     2,     3,     4,    87,   130,
     138,   134,    88,   145,   139,   159,     5,     6,    89,    90,
     141,   136,     7,   135,   154,     8,   146,   155,   157,   158,
      12,   148,   153,     0,    16,    17,    18,    19,     0,     0,
      46,     0,    21,     1,     2,     3,     4,    23,     0,     0,
       0,     0,     0,     0,     0,     5,     6,     0,     0,     0,
       0,     7,     0,     0,     8,     0,     0,     0,     0,     0,
       0,     0,     0,    16,    17,    18,    19,     0,     0,    46,
       0,    21,     1,     2,     3,     4,    23,     0,     0,     0,
       0,     0,     0,     0,     5,     6,     0,     0,     0,     0,
       7,     0,     0,     8,     0,     0,     0,     0,     0,     0,
       0,     0,    16,    17,    18,    19,     0,     0,    98,     0,
      21,     0,     0,     0,     0,    23,    68,    69,    70,    71,
      72,    73,    74,     0,     0,    75,    76,    77,    78,     0,
      79,    80,    81,    68,    69,    70,    71,    72,    73,    74,
       0,     0,    75,    76,    77,    78,     0,    79,    80,    81,
       0,    82,   107,   132,     0,     0,     0,     0,     0,     0,
       0,     0,    68,    69,    70,    71,    72,    73,    74,   107,
     132,    75,    76,    77,    78,     0,    79,    80,    81,    68,
      69,    70,    71,    72,    73,    74,     0,     0,    75,    76,
      77,    78,     0,    79,    80,    81,     0,    82,   107,     0,
       0,     0,    68,    69,    70,    71,    72,    73,    74,     0,
       0,    75,    76,    77,    78,   107,    79,    80,    81,    68,
      69,    70,    71,    72,    73,    74,     0,     0,    75,    76,
      77,    78,     0,    79,    80,    81,     0,    82,     0,     0,
       0,    68,    69,    70,    71,    72,    73,    74,     0,     0,
      75,    76,    77,    78,   104,    79,    80,    81,    68,    69,
      70,    71,    72,    73,    74,     0,     0,    75,    76,    77,
      78,     0,    79,    80,    81,     0,   129,     0,     0,     0,
      68,    69,    70,    71,    72,    73,    74,     0,     0,    75,
      76,    77,    78,   152,    79,    80,    81,    68,    69,    70,
      71,    72,    73,    74,     0,     0,    75,    76,    77,    78,
       0,    79,    80,    81,   114,     0,     0,     0,    68,    69,
      70,    71,    72,    73,    74,     0,     0,    75,    76,    77,
      78,   127,    79,    80,    81,    68,    69,    70,    71,    72,
      73,    74,     0,     0,    75,    76,    77,    78,     0,    79,
      80,    81,   128,     0,     0,     0,    68,    69,    70,    71,
      72,    73,    74,     0,     0,    75,    76,    77,    78,   160,
      79,    80,    81,     0,     0,    68,    69,    70,    71,    72,
      73,    74,     0,     0,    75,    76,    77,    78,   156,    79,
      80,    81,    68,    69,    70,    71,    72,    73,    74,     0,
       0,    75,    76,    77,    78,   137,    79,    80,    81,    68,
      69,    70,    71,    72,    73,    74,     0,     0,    75,    76,
      77,    78,   140,    79,    80,    81
};

static const yytype_int16 yycheck[] =
{
       7,     8,    21,    88,    41,     6,    13,    41,   127,   128,
      95,     5,     6,    20,    21,     8,     9,    10,    11,    12,
      13,    14,     6,    42,    17,    18,    19,    20,    41,    22,
      23,    24,    33,     0,    43,     3,     4,     5,     6,    46,
      41,   160,    49,    50,    51,    46,    43,    15,    16,     6,
      57,   136,    45,    21,   139,     6,    24,    25,    25,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,     5,
       6,    39,     0,    41,    29,    43,    83,    84,    46,    24,
      87,    88,    41,     3,     4,     5,     6,    94,    95,    42,
       7,    98,    40,    37,    40,    15,    16,    41,    15,    16,
     107,    21,    44,    47,    24,    25,    40,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,     6,     6,    39,
      37,    41,   129,    43,    41,   132,    46,   134,     6,   136,
      47,    48,   139,    42,     3,     4,     5,     6,    37,     6,
      42,    39,    41,    44,    41,   152,    15,    16,    47,    48,
      42,    41,    21,   111,    39,    24,    42,   146,    42,    42,
      29,   133,   145,    -1,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    41,     3,     4,     5,     6,    46,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    15,    16,    -1,    -1,    -1,
      -1,    21,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    33,    34,    35,    36,    -1,    -1,    39,
      -1,    41,     3,     4,     5,     6,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    15,    16,    -1,    -1,    -1,    -1,
      21,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    34,    35,    36,    -1,    -1,    39,    -1,
      41,    -1,    -1,    -1,    -1,    46,     8,     9,    10,    11,
      12,    13,    14,    -1,    -1,    17,    18,    19,    20,    -1,
      22,    23,    24,     8,     9,    10,    11,    12,    13,    14,
      -1,    -1,    17,    18,    19,    20,    -1,    22,    23,    24,
      -1,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     8,     9,    10,    11,    12,    13,    14,    44,
      45,    17,    18,    19,    20,    -1,    22,    23,    24,     8,
       9,    10,    11,    12,    13,    14,    -1,    -1,    17,    18,
      19,    20,    -1,    22,    23,    24,    -1,    43,    44,    -1,
      -1,    -1,     8,     9,    10,    11,    12,    13,    14,    -1,
      -1,    17,    18,    19,    20,    44,    22,    23,    24,     8,
       9,    10,    11,    12,    13,    14,    -1,    -1,    17,    18,
      19,    20,    -1,    22,    23,    24,    -1,    43,    -1,    -1,
      -1,     8,     9,    10,    11,    12,    13,    14,    -1,    -1,
      17,    18,    19,    20,    43,    22,    23,    24,     8,     9,
      10,    11,    12,    13,    14,    -1,    -1,    17,    18,    19,
      20,    -1,    22,    23,    24,    -1,    43,    -1,    -1,    -1,
       8,     9,    10,    11,    12,    13,    14,    -1,    -1,    17,
      18,    19,    20,    43,    22,    23,    24,     8,     9,    10,
      11,    12,    13,    14,    -1,    -1,    17,    18,    19,    20,
      -1,    22,    23,    24,    42,    -1,    -1,    -1,     8,     9,
      10,    11,    12,    13,    14,    -1,    -1,    17,    18,    19,
      20,    42,    22,    23,    24,     8,     9,    10,    11,    12,
      13,    14,    -1,    -1,    17,    18,    19,    20,    -1,    22,
      23,    24,    42,    -1,    -1,    -1,     8,     9,    10,    11,
      12,    13,    14,    -1,    -1,    17,    18,    19,    20,    42,
      22,    23,    24,    -1,    -1,     8,     9,    10,    11,    12,
      13,    14,    -1,    -1,    17,    18,    19,    20,    40,    22,
      23,    24,     8,     9,    10,    11,    12,    13,    14,    -1,
      -1,    17,    18,    19,    20,    38,    22,    23,    24,     8,
       9,    10,    11,    12,    13,    14,    -1,    -1,    17,    18,
      19,    20,    38,    22,    23,    24
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,    15,    16,    21,    24,    25,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      39,    41,    43,    46,    50,    51,    52,    54,    55,    56,
      57,    58,    59,    64,    67,    68,    69,    71,    72,    73,
      74,    75,    41,    57,    59,    57,    39,    52,    52,    41,
      41,    41,     6,    52,    43,    43,     6,    39,    52,    63,
      65,    66,    74,    52,    68,     6,     0,    74,     8,     9,
      10,    11,    12,    13,    14,    17,    18,    19,    20,    22,
      23,    24,    43,    53,     7,    15,    16,    37,    41,    47,
      48,    60,    61,    62,    37,    41,    47,    68,    39,    52,
      52,    52,    52,    41,    43,    78,    52,    44,    77,    40,
      40,    44,    76,    40,    42,    42,    52,    52,    52,    63,
       6,     6,    52,    63,     6,    42,    52,    42,    42,    43,
       6,    70,    45,    52,    39,    66,    41,    38,    42,    41,
      38,    42,    51,    51,    52,    44,    42,    52,    77,    52,
      63,    63,    43,    70,    39,    67,    40,    42,    42,    52,
      42,    51
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
#line 36 "src/parser.y"
                                        {}
#line 1329 "src/parser.c"
    break;

  case 3: /* stmt: expr SEMI  */
#line 39 "src/parser.y"
                                        {}
#line 1335 "src/parser.c"
    break;

  case 4: /* stmt: ifstmt  */
#line 40 "src/parser.y"
                                        {}
#line 1341 "src/parser.c"
    break;

  case 5: /* stmt: whilestmt  */
#line 41 "src/parser.y"
                                        {}
#line 1347 "src/parser.c"
    break;

  case 6: /* stmt: forstmt  */
#line 42 "src/parser.y"
                                        {}
#line 1353 "src/parser.c"
    break;

  case 7: /* stmt: returnstmt  */
#line 43 "src/parser.y"
                                        {}
#line 1359 "src/parser.c"
    break;

  case 8: /* stmt: BREAK SEMI  */
#line 44 "src/parser.y"
                                        {}
#line 1365 "src/parser.c"
    break;

  case 9: /* stmt: CONTINUE SEMI  */
#line 45 "src/parser.y"
                                        {}
#line 1371 "src/parser.c"
    break;

  case 10: /* stmt: block  */
#line 46 "src/parser.y"
                                        {}
#line 1377 "src/parser.c"
    break;

  case 11: /* stmt: funcdef  */
#line 47 "src/parser.y"
                                        {}
#line 1383 "src/parser.c"
    break;

  case 12: /* stmt: SEMI  */
#line 48 "src/parser.y"
                                        {}
#line 1389 "src/parser.c"
    break;

  case 13: /* expr: assignexpr  */
#line 51 "src/parser.y"
                                        {}
#line 1395 "src/parser.c"
    break;

  case 14: /* expr: expr op expr  */
#line 52 "src/parser.y"
                                        {}
#line 1401 "src/parser.c"
    break;

  case 15: /* expr: term  */
#line 53 "src/parser.y"
                                        {}
#line 1407 "src/parser.c"
    break;

  case 16: /* op: PLUS  */
#line 56 "src/parser.y"
                                        {}
#line 1413 "src/parser.c"
    break;

  case 17: /* op: MINUS  */
#line 57 "src/parser.y"
                                        {}
#line 1419 "src/parser.c"
    break;

  case 18: /* op: MUL  */
#line 58 "src/parser.y"
                                        {}
#line 1425 "src/parser.c"
    break;

  case 19: /* op: DIV  */
#line 59 "src/parser.y"
                                        {}
#line 1431 "src/parser.c"
    break;

  case 20: /* op: MOD  */
#line 60 "src/parser.y"
                                        {}
#line 1437 "src/parser.c"
    break;

  case 21: /* op: EQ  */
#line 61 "src/parser.y"
                                        {}
#line 1443 "src/parser.c"
    break;

  case 22: /* op: NEQ  */
#line 62 "src/parser.y"
                                        {}
#line 1449 "src/parser.c"
    break;

  case 23: /* op: GT  */
#line 63 "src/parser.y"
                                        {}
#line 1455 "src/parser.c"
    break;

  case 24: /* op: LT  */
#line 64 "src/parser.y"
                                        {}
#line 1461 "src/parser.c"
    break;

  case 25: /* op: GTE  */
#line 65 "src/parser.y"
                                        {}
#line 1467 "src/parser.c"
    break;

  case 26: /* op: LTE  */
#line 66 "src/parser.y"
                                        {}
#line 1473 "src/parser.c"
    break;

  case 27: /* op: AND  */
#line 67 "src/parser.y"
                                        {}
#line 1479 "src/parser.c"
    break;

  case 28: /* op: OR  */
#line 68 "src/parser.y"
                                        {}
#line 1485 "src/parser.c"
    break;

  case 29: /* op: NOT  */
#line 69 "src/parser.y"
                                        {}
#line 1491 "src/parser.c"
    break;

  case 30: /* term: LPAR expr RPAR  */
#line 72 "src/parser.y"
                                        {}
#line 1497 "src/parser.c"
    break;

  case 31: /* term: UMINUS expr  */
#line 73 "src/parser.y"
                                        {}
#line 1503 "src/parser.c"
    break;

  case 32: /* term: NOT expr  */
#line 74 "src/parser.y"
                                        {}
#line 1509 "src/parser.c"
    break;

  case 33: /* term: INC lvalue  */
#line 75 "src/parser.y"
                                        {}
#line 1515 "src/parser.c"
    break;

  case 34: /* term: lvalue INC  */
#line 76 "src/parser.y"
                                        {}
#line 1521 "src/parser.c"
    break;

  case 35: /* term: DEC lvalue  */
#line 77 "src/parser.y"
                                        {}
#line 1527 "src/parser.c"
    break;

  case 36: /* term: lvalue DEC  */
#line 78 "src/parser.y"
                                        {}
#line 1533 "src/parser.c"
    break;

  case 37: /* term: primary  */
#line 79 "src/parser.y"
                                        {}
#line 1539 "src/parser.c"
    break;

  case 38: /* assignexpr: lvalue ASSIGN expr  */
#line 82 "src/parser.y"
                                        {}
#line 1545 "src/parser.c"
    break;

  case 39: /* primary: lvalue  */
#line 85 "src/parser.y"
                                        {}
#line 1551 "src/parser.c"
    break;

  case 40: /* primary: call  */
#line 86 "src/parser.y"
                                        {}
#line 1557 "src/parser.c"
    break;

  case 41: /* primary: objectdef  */
#line 87 "src/parser.y"
                                        {}
#line 1563 "src/parser.c"
    break;

  case 42: /* primary: LPAR funcdef RPAR  */
#line 88 "src/parser.y"
                                        {}
#line 1569 "src/parser.c"
    break;

  case 43: /* primary: const  */
#line 89 "src/parser.y"
                                        {}
#line 1575 "src/parser.c"
    break;

  case 44: /* lvalue: IDENT  */
#line 92 "src/parser.y"
                                        {}
#line 1581 "src/parser.c"
    break;

  case 45: /* lvalue: LOCAL IDENT  */
#line 93 "src/parser.y"
                                        {}
#line 1587 "src/parser.c"
    break;

  case 46: /* lvalue: DCOLON IDENT  */
#line 94 "src/parser.y"
                                        {}
#line 1593 "src/parser.c"
    break;

  case 47: /* lvalue: member  */
#line 95 "src/parser.y"
                                        {}
#line 1599 "src/parser.c"
    break;

  case 48: /* member: lvalue DOT IDENT  */
#line 98 "src/parser.y"
                                        {}
#line 1605 "src/parser.c"
    break;

  case 49: /* member: lvalue LBRACE expr RBRACE  */
#line 99 "src/parser.y"
                                        {}
#line 1611 "src/parser.c"
    break;

  case 50: /* member: call DOT IDENT  */
#line 100 "src/parser.y"
                                        {}
#line 1617 "src/parser.c"
    break;

  case 51: /* member: call LBRACE expr RBRACE  */
#line 101 "src/parser.y"
                                        {}
#line 1623 "src/parser.c"
    break;


#line 1627 "src/parser.c"

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

#line 178 "src/parser.y"

