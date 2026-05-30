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
#line 7 "src/sql/sql_parser.y"

#include "sql/parser_api.h"

#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

int yylex();
void yyerror(const char* message);

typedef struct yy_buffer_state* YY_BUFFER_STATE;
extern YY_BUFFER_STATE yy_scan_string(const char* text);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);
extern int yylex_destroy();

static Statement* parsedStatement = nullptr;
static std::string parseError;

static Expr* makeBinary(ExprKind kind, Expr* left, Expr* right) {
    auto* expr = new Expr();
    expr->kind = kind;
    expr->lhs.reset(left);
    expr->rhs.reset(right);
    return expr;
}

#line 100 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"

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

#include "sql_parser.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_CREATE = 3,                     /* CREATE  */
  YYSYMBOL_DATABASE = 4,                   /* DATABASE  */
  YYSYMBOL_DROP = 5,                       /* DROP  */
  YYSYMBOL_USE = 6,                        /* USE  */
  YYSYMBOL_TABLE = 7,                      /* TABLE  */
  YYSYMBOL_INSERT = 8,                     /* INSERT  */
  YYSYMBOL_INTO = 9,                       /* INTO  */
  YYSYMBOL_VALUE = 10,                     /* VALUE  */
  YYSYMBOL_VALUES = 11,                    /* VALUES  */
  YYSYMBOL_UPDATE = 12,                    /* UPDATE  */
  YYSYMBOL_SET = 13,                       /* SET  */
  YYSYMBOL_DELETE = 14,                    /* DELETE  */
  YYSYMBOL_FROM = 15,                      /* FROM  */
  YYSYMBOL_SELECT = 16,                    /* SELECT  */
  YYSYMBOL_WHERE = 17,                     /* WHERE  */
  YYSYMBOL_AS = 18,                        /* AS  */
  YYSYMBOL_INT_T = 19,                     /* INT_T  */
  YYSYMBOL_STRING_T = 20,                  /* STRING_T  */
  YYSYMBOL_NOT_NULL = 21,                  /* NOT_NULL  */
  YYSYMBOL_INDEXED = 22,                   /* INDEXED  */
  YYSYMBOL_DEFAULT = 23,                   /* DEFAULT  */
  YYSYMBOL_NULL_T = 24,                    /* NULL_T  */
  YYSYMBOL_BETWEEN = 25,                   /* BETWEEN  */
  YYSYMBOL_LIKE = 26,                      /* LIKE  */
  YYSYMBOL_AND = 27,                       /* AND  */
  YYSYMBOL_OR = 28,                        /* OR  */
  YYSYMBOL_COUNT = 29,                     /* COUNT  */
  YYSYMBOL_SUM = 30,                       /* SUM  */
  YYSYMBOL_AVG = 31,                       /* AVG  */
  YYSYMBOL_EQ = 32,                        /* EQ  */
  YYSYMBOL_NE = 33,                        /* NE  */
  YYSYMBOL_LE = 34,                        /* LE  */
  YYSYMBOL_GE = 35,                        /* GE  */
  YYSYMBOL_LT = 36,                        /* LT  */
  YYSYMBOL_GT = 37,                        /* GT  */
  YYSYMBOL_ASSIGN = 38,                    /* ASSIGN  */
  YYSYMBOL_IDENTIFIER = 39,                /* IDENTIFIER  */
  YYSYMBOL_INT_LITERAL = 40,               /* INT_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 41,            /* STRING_LITERAL  */
  YYSYMBOL_42_ = 42,                       /* ';'  */
  YYSYMBOL_43_ = 43,                       /* '('  */
  YYSYMBOL_44_ = 44,                       /* ')'  */
  YYSYMBOL_45_ = 45,                       /* '.'  */
  YYSYMBOL_46_ = 46,                       /* ','  */
  YYSYMBOL_47_ = 47,                       /* '*'  */
  YYSYMBOL_YYACCEPT = 48,                  /* $accept  */
  YYSYMBOL_input = 49,                     /* input  */
  YYSYMBOL_optional_semicolon = 50,        /* optional_semicolon  */
  YYSYMBOL_statement = 51,                 /* statement  */
  YYSYMBOL_create_database = 52,           /* create_database  */
  YYSYMBOL_drop_database = 53,             /* drop_database  */
  YYSYMBOL_use_database = 54,              /* use_database  */
  YYSYMBOL_create_table = 55,              /* create_table  */
  YYSYMBOL_drop_table = 56,                /* drop_table  */
  YYSYMBOL_insert_statement = 57,          /* insert_statement  */
  YYSYMBOL_value_keyword = 58,             /* value_keyword  */
  YYSYMBOL_update_statement = 59,          /* update_statement  */
  YYSYMBOL_delete_statement = 60,          /* delete_statement  */
  YYSYMBOL_select_statement = 61,          /* select_statement  */
  YYSYMBOL_table_ref = 62,                 /* table_ref  */
  YYSYMBOL_identifier = 63,                /* identifier  */
  YYSYMBOL_identifier_list = 64,           /* identifier_list  */
  YYSYMBOL_column_defs = 65,               /* column_defs  */
  YYSYMBOL_column_def = 66,                /* column_def  */
  YYSYMBOL_column_type = 67,               /* column_type  */
  YYSYMBOL_column_attrs = 68,              /* column_attrs  */
  YYSYMBOL_insert_rows = 69,               /* insert_rows  */
  YYSYMBOL_literal_list = 70,              /* literal_list  */
  YYSYMBOL_literal = 71,                   /* literal  */
  YYSYMBOL_assignments = 72,               /* assignments  */
  YYSYMBOL_assignment = 73,                /* assignment  */
  YYSYMBOL_select_list = 74,               /* select_list  */
  YYSYMBOL_select_item_list = 75,          /* select_item_list  */
  YYSYMBOL_select_item = 76,               /* select_item  */
  YYSYMBOL_opt_alias = 77,                 /* opt_alias  */
  YYSYMBOL_aggregate_function = 78,        /* aggregate_function  */
  YYSYMBOL_condition = 79,                 /* condition  */
  YYSYMBOL_disjunction = 80,               /* disjunction  */
  YYSYMBOL_conjunction = 81,               /* conjunction  */
  YYSYMBOL_predicate = 82,                 /* predicate  */
  YYSYMBOL_operand = 83,                   /* operand  */
  YYSYMBOL_comparison_operator = 84        /* comparison_operator  */
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
#define YYFINAL  38
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   142

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  84
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  152

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   296


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
      43,    44,    47,     2,    46,     2,    45,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    42,
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
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    86,    86,    90,    91,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   107,   117,   127,   137,   149,   159,
     173,   174,   178,   187,   200,   207,   218,   227,   240,   246,
     257,   261,   267,   275,   281,   289,   301,   302,   306,   309,
     313,   318,   327,   333,   341,   347,   355,   356,   357,   361,
     367,   375,   386,   393,   397,   403,   411,   419,   428,   436,
     445,   458,   459,   463,   464,   465,   469,   473,   474,   478,
     479,   483,   484,   495,   506,   518,   523,   528,   537,   538,
     539,   540,   541,   542,   543
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
  "\"end of file\"", "error", "\"invalid token\"", "CREATE", "DATABASE",
  "DROP", "USE", "TABLE", "INSERT", "INTO", "VALUE", "VALUES", "UPDATE",
  "SET", "DELETE", "FROM", "SELECT", "WHERE", "AS", "INT_T", "STRING_T",
  "NOT_NULL", "INDEXED", "DEFAULT", "NULL_T", "BETWEEN", "LIKE", "AND",
  "OR", "COUNT", "SUM", "AVG", "EQ", "NE", "LE", "GE", "LT", "GT",
  "ASSIGN", "IDENTIFIER", "INT_LITERAL", "STRING_LITERAL", "';'", "'('",
  "')'", "'.'", "','", "'*'", "$accept", "input", "optional_semicolon",
  "statement", "create_database", "drop_database", "use_database",
  "create_table", "drop_table", "insert_statement", "value_keyword",
  "update_statement", "delete_statement", "select_statement", "table_ref",
  "identifier", "identifier_list", "column_defs", "column_def",
  "column_type", "column_attrs", "insert_rows", "literal_list", "literal",
  "assignments", "assignment", "select_list", "select_item_list",
  "select_item", "opt_alias", "aggregate_function", "condition",
  "disjunction", "conjunction", "predicate", "operand",
  "comparison_operator", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-102)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     107,    28,    41,   -28,    15,   -28,    44,    32,    70,    49,
    -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,   -28,
     -28,   -28,   -28,  -102,  -102,   -28,    61,    56,   -28,  -102,
    -102,  -102,  -102,    -5,    79,    65,  -102,    59,  -102,  -102,
    -102,  -102,    73,  -102,  -102,    74,   -28,   -28,    97,   -28,
     -28,  -102,   -28,    38,   -16,   -28,   -28,    80,    -9,  -102,
    -102,    17,  -102,   102,   105,  -102,    81,   -24,    35,   -10,
    -102,  -102,    34,   -14,    17,   -28,  -102,  -102,  -102,    17,
      82,  -102,  -102,    96,    99,  -102,    71,  -102,    17,   102,
     102,   -28,  -102,  -102,  -102,  -102,   -28,    88,   -28,  -102,
    -102,  -102,    84,   -28,    17,    17,    42,    42,  -102,  -102,
    -102,  -102,  -102,  -102,  -102,    42,  -102,  -102,  -102,    85,
      63,  -102,  -102,  -102,    87,  -102,  -102,  -102,    99,  -102,
     104,  -102,  -102,   102,  -102,  -102,   -14,   -14,    86,    42,
    -102,  -102,    43,  -102,    90,  -102,  -102,   -14,   -14,  -102,
      46,  -102
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     3,
       5,     6,     7,     8,     9,    10,    11,    12,    13,     0,
       0,     0,     0,    30,    16,     0,     0,    28,     0,    63,
      64,    65,    52,    61,     0,    53,    54,     0,     1,     4,
       2,    14,     0,    15,    18,     0,     0,     0,    24,     0,
       0,    56,     0,     0,     0,     0,     0,     0,    22,    49,
      29,     0,    62,    61,    26,    55,     0,     0,     0,     0,
      33,    31,     0,     0,     0,     0,    48,    46,    47,     0,
      76,    75,    25,    66,    67,    69,     0,    57,     0,    61,
      61,     0,    36,    37,    38,    17,     0,     0,     0,    51,
      23,    50,     0,     0,     0,     0,     0,     0,    78,    80,
      82,    84,    81,    83,    79,     0,    27,    58,    59,     0,
      35,    34,    20,    21,     0,    32,    71,    77,    68,    70,
       0,    74,    72,    61,    39,    40,     0,     0,    19,     0,
      60,    41,     0,    44,     0,    73,    42,     0,     0,    45,
       0,    43
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,
    -102,  -102,  -102,  -102,   -13,    -3,  -102,  -102,    39,  -102,
    -102,  -102,   -12,   -72,  -102,    62,  -102,  -102,    89,   -60,
    -102,   -46,  -102,    30,    33,  -101,  -102
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     8,    40,     9,    10,    11,    12,    13,    14,    15,
     124,    16,    17,    18,    26,    80,    72,    69,    70,    94,
     120,   138,   142,    81,    58,    59,    34,    35,    36,    51,
      37,    82,    83,    84,    85,    86,   115
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      24,    99,    27,    87,    33,   130,   131,    42,    74,    44,
      76,    23,    45,    49,   132,    48,    41,    27,    43,    27,
      90,    91,    27,    23,    25,    27,    77,    78,   100,   117,
     118,    66,    19,   102,    95,    20,    96,    75,   145,    64,
      50,    76,   116,    57,    60,    21,    62,    63,    22,    27,
      33,    67,    68,    71,    92,    93,    23,    77,    78,    28,
      79,    29,    30,    31,   141,   143,    76,    29,    30,    31,
      38,    23,    57,   140,    46,   149,   143,    23,    97,    32,
      98,    23,    77,    78,   134,   135,   136,   146,   119,   147,
     151,    39,   147,    68,    52,   125,   106,   107,   122,   123,
     127,    47,    54,   108,   109,   110,   111,   112,   113,   114,
       1,    53,     2,     3,    61,     4,    55,    56,    73,     5,
      49,     6,    88,     7,   104,    89,   105,   103,   126,   133,
     137,   139,   144,   148,   128,   121,   150,   101,   129,     0,
       0,     0,    65
};

static const yytype_int16 yycheck[] =
{
       3,    73,     5,    63,     7,   106,   107,    20,    17,    22,
      24,    39,    25,    18,   115,    28,    19,    20,    21,    22,
      44,    45,    25,    39,     9,    28,    40,    41,    74,    89,
      90,    47,     4,    79,    44,     7,    46,    46,   139,    52,
      45,    24,    88,    46,    47,     4,    49,    50,     7,    52,
      53,    54,    55,    56,    19,    20,    39,    40,    41,    15,
      43,    29,    30,    31,   136,   137,    24,    29,    30,    31,
       0,    39,    75,   133,    13,   147,   148,    39,    44,    47,
      46,    39,    40,    41,    21,    22,    23,    44,    91,    46,
      44,    42,    46,    96,    15,    98,    25,    26,    10,    11,
     103,    45,    43,    32,    33,    34,    35,    36,    37,    38,
       3,    46,     5,     6,    17,     8,    43,    43,    38,    12,
      18,    14,    17,    16,    28,    44,    27,    45,    44,    44,
      43,    27,    46,    43,   104,    96,   148,    75,   105,    -1,
      -1,    -1,    53
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     5,     6,     8,    12,    14,    16,    49,    51,
      52,    53,    54,    55,    56,    57,    59,    60,    61,     4,
       7,     4,     7,    39,    63,     9,    62,    63,    15,    29,
      30,    31,    47,    63,    74,    75,    76,    78,     0,    42,
      50,    63,    62,    63,    62,    62,    13,    45,    62,    18,
      45,    77,    15,    46,    43,    43,    43,    63,    72,    73,
      63,    17,    63,    63,    62,    76,    47,    63,    63,    65,
      66,    63,    64,    38,    17,    46,    24,    40,    41,    43,
      63,    71,    79,    80,    81,    82,    83,    77,    17,    44,
      44,    45,    19,    20,    67,    44,    46,    44,    46,    71,
      79,    73,    79,    45,    28,    27,    25,    26,    32,    33,
      34,    35,    36,    37,    38,    84,    79,    77,    77,    63,
      68,    66,    10,    11,    58,    63,    44,    63,    81,    82,
      83,    83,    83,    44,    21,    22,    23,    43,    69,    27,
      77,    71,    70,    71,    46,    83,    44,    46,    43,    71,
      70,    44
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    48,    49,    50,    50,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    52,    53,    54,    55,    56,    57,
      58,    58,    59,    59,    60,    60,    61,    61,    62,    62,
      63,    64,    64,    65,    65,    66,    67,    67,    68,    68,
      68,    68,    69,    69,    70,    70,    71,    71,    71,    72,
      72,    73,    74,    74,    75,    75,    76,    76,    76,    76,
      76,    77,    77,    78,    78,    78,    79,    80,    80,    81,
      81,    82,    82,    82,    82,    83,    83,    83,    84,    84,
      84,    84,    84,    84,    84
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     0,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     2,     6,     3,     8,
       1,     1,     4,     6,     3,     5,     4,     6,     1,     3,
       1,     1,     3,     1,     3,     3,     1,     1,     0,     2,
       2,     3,     3,     5,     1,     3,     1,     1,     1,     1,
       3,     3,     1,     1,     1,     3,     2,     4,     5,     5,
       7,     0,     2,     1,     1,     1,     1,     1,     3,     1,
       3,     3,     3,     5,     3,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1
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
  case 2: /* input: statement optional_semicolon  */
#line 86 "src/sql/sql_parser.y"
                                 { parsedStatement = (yyvsp[-1].statement); }
#line 1278 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 14: /* create_database: CREATE DATABASE identifier  */
#line 107 "src/sql/sql_parser.y"
                               {
        auto* statement = new Statement();
        statement->kind = StatementKind::CreateDatabase;
        statement->databaseName = *(yyvsp[0].text);
        delete (yyvsp[0].text);
        (yyval.statement) = statement;
    }
#line 1290 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 15: /* drop_database: DROP DATABASE identifier  */
#line 117 "src/sql/sql_parser.y"
                             {
        auto* statement = new Statement();
        statement->kind = StatementKind::DropDatabase;
        statement->databaseName = *(yyvsp[0].text);
        delete (yyvsp[0].text);
        (yyval.statement) = statement;
    }
#line 1302 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 16: /* use_database: USE identifier  */
#line 127 "src/sql/sql_parser.y"
                   {
        auto* statement = new Statement();
        statement->kind = StatementKind::UseDatabase;
        statement->databaseName = *(yyvsp[0].text);
        delete (yyvsp[0].text);
        (yyval.statement) = statement;
    }
#line 1314 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 17: /* create_table: CREATE TABLE table_ref '(' column_defs ')'  */
#line 137 "src/sql/sql_parser.y"
                                               {
        auto* statement = new Statement();
        statement->kind = StatementKind::CreateTable;
        statement->table = std::move(*(yyvsp[-3].table_ref));
        statement->columnDefs = std::move(*(yyvsp[-1].column_defs));
        delete (yyvsp[-3].table_ref);
        delete (yyvsp[-1].column_defs);
        (yyval.statement) = statement;
    }
#line 1328 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 18: /* drop_table: DROP TABLE table_ref  */
#line 149 "src/sql/sql_parser.y"
                         {
        auto* statement = new Statement();
        statement->kind = StatementKind::DropTable;
        statement->table = std::move(*(yyvsp[0].table_ref));
        delete (yyvsp[0].table_ref);
        (yyval.statement) = statement;
    }
#line 1340 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 19: /* insert_statement: INSERT INTO table_ref '(' identifier_list ')' value_keyword insert_rows  */
#line 159 "src/sql/sql_parser.y"
                                                                            {
        auto* statement = new Statement();
        statement->kind = StatementKind::Insert;
        statement->table = std::move(*(yyvsp[-5].table_ref));
        statement->insertColumns = std::move(*(yyvsp[-3].identifiers));
        statement->insertRows = std::move(*(yyvsp[0].row_values));
        delete (yyvsp[-5].table_ref);
        delete (yyvsp[-3].identifiers);
        delete (yyvsp[0].row_values);
        (yyval.statement) = statement;
    }
#line 1356 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 22: /* update_statement: UPDATE table_ref SET assignments  */
#line 178 "src/sql/sql_parser.y"
                                     {
        auto* statement = new Statement();
        statement->kind = StatementKind::Update;
        statement->table = std::move(*(yyvsp[-2].table_ref));
        statement->assignments = std::move(*(yyvsp[0].assignments));
        delete (yyvsp[-2].table_ref);
        delete (yyvsp[0].assignments);
        (yyval.statement) = statement;
    }
#line 1370 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 23: /* update_statement: UPDATE table_ref SET assignments WHERE condition  */
#line 187 "src/sql/sql_parser.y"
                                                     {
        auto* statement = new Statement();
        statement->kind = StatementKind::Update;
        statement->table = std::move(*(yyvsp[-4].table_ref));
        statement->assignments = std::move(*(yyvsp[-2].assignments));
        statement->where.reset((yyvsp[0].expr));
        delete (yyvsp[-4].table_ref);
        delete (yyvsp[-2].assignments);
        (yyval.statement) = statement;
    }
#line 1385 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 24: /* delete_statement: DELETE FROM table_ref  */
#line 200 "src/sql/sql_parser.y"
                          {
        auto* statement = new Statement();
        statement->kind = StatementKind::DeleteRows;
        statement->table = std::move(*(yyvsp[0].table_ref));
        delete (yyvsp[0].table_ref);
        (yyval.statement) = statement;
    }
#line 1397 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 25: /* delete_statement: DELETE FROM table_ref WHERE condition  */
#line 207 "src/sql/sql_parser.y"
                                          {
        auto* statement = new Statement();
        statement->kind = StatementKind::DeleteRows;
        statement->table = std::move(*(yyvsp[-2].table_ref));
        statement->where.reset((yyvsp[0].expr));
        delete (yyvsp[-2].table_ref);
        (yyval.statement) = statement;
    }
#line 1410 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 26: /* select_statement: SELECT select_list FROM table_ref  */
#line 218 "src/sql/sql_parser.y"
                                      {
        auto* statement = new Statement();
        statement->kind = StatementKind::SelectRows;
        statement->selectItems = std::move(*(yyvsp[-2].select_items));
        statement->table = std::move(*(yyvsp[0].table_ref));
        delete (yyvsp[-2].select_items);
        delete (yyvsp[0].table_ref);
        (yyval.statement) = statement;
    }
#line 1424 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 27: /* select_statement: SELECT select_list FROM table_ref WHERE condition  */
#line 227 "src/sql/sql_parser.y"
                                                      {
        auto* statement = new Statement();
        statement->kind = StatementKind::SelectRows;
        statement->selectItems = std::move(*(yyvsp[-4].select_items));
        statement->table = std::move(*(yyvsp[-2].table_ref));
        statement->where.reset((yyvsp[0].expr));
        delete (yyvsp[-4].select_items);
        delete (yyvsp[-2].table_ref);
        (yyval.statement) = statement;
    }
#line 1439 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 28: /* table_ref: identifier  */
#line 240 "src/sql/sql_parser.y"
               {
        auto* ref = new TableRef();
        ref->table = *(yyvsp[0].text);
        delete (yyvsp[0].text);
        (yyval.table_ref) = ref;
    }
#line 1450 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 29: /* table_ref: identifier '.' identifier  */
#line 246 "src/sql/sql_parser.y"
                              {
        auto* ref = new TableRef();
        ref->database = *(yyvsp[-2].text);
        ref->table = *(yyvsp[0].text);
        delete (yyvsp[-2].text);
        delete (yyvsp[0].text);
        (yyval.table_ref) = ref;
    }
#line 1463 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 30: /* identifier: IDENTIFIER  */
#line 257 "src/sql/sql_parser.y"
               { (yyval.text) = (yyvsp[0].text); }
#line 1469 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 31: /* identifier_list: identifier  */
#line 261 "src/sql/sql_parser.y"
               {
        auto* list = new std::vector<std::string>();
        list->push_back(*(yyvsp[0].text));
        delete (yyvsp[0].text);
        (yyval.identifiers) = list;
    }
#line 1480 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 32: /* identifier_list: identifier_list ',' identifier  */
#line 267 "src/sql/sql_parser.y"
                                   {
        (yyvsp[-2].identifiers)->push_back(*(yyvsp[0].text));
        delete (yyvsp[0].text);
        (yyval.identifiers) = (yyvsp[-2].identifiers);
    }
#line 1490 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 33: /* column_defs: column_def  */
#line 275 "src/sql/sql_parser.y"
               {
        auto* list = new std::vector<ColumnDef>();
        list->push_back(std::move(*(yyvsp[0].column_def)));
        delete (yyvsp[0].column_def);
        (yyval.column_defs) = list;
    }
#line 1501 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 34: /* column_defs: column_defs ',' column_def  */
#line 281 "src/sql/sql_parser.y"
                               {
        (yyvsp[-2].column_defs)->push_back(std::move(*(yyvsp[0].column_def)));
        delete (yyvsp[0].column_def);
        (yyval.column_defs) = (yyvsp[-2].column_defs);
    }
#line 1511 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 35: /* column_def: identifier column_type column_attrs  */
#line 289 "src/sql/sql_parser.y"
                                        {
        (yyvsp[0].column_def)->name = *(yyvsp[-2].text);
        (yyvsp[0].column_def)->type = (yyvsp[-1].field_type);
        if ((yyvsp[0].column_def)->indexed) {
            (yyvsp[0].column_def)->notNull = true;
        }
        delete (yyvsp[-2].text);
        (yyval.column_def) = (yyvsp[0].column_def);
    }
#line 1525 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 36: /* column_type: INT_T  */
#line 301 "src/sql/sql_parser.y"
          { (yyval.field_type) = FieldType::Int; }
#line 1531 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 37: /* column_type: STRING_T  */
#line 302 "src/sql/sql_parser.y"
             { (yyval.field_type) = FieldType::String; }
#line 1537 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 38: /* column_attrs: %empty  */
#line 306 "src/sql/sql_parser.y"
           {
        (yyval.column_def) = new ColumnDef();
    }
#line 1545 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 39: /* column_attrs: column_attrs NOT_NULL  */
#line 309 "src/sql/sql_parser.y"
                          {
        (yyvsp[-1].column_def)->notNull = true;
        (yyval.column_def) = (yyvsp[-1].column_def);
    }
#line 1554 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 40: /* column_attrs: column_attrs INDEXED  */
#line 313 "src/sql/sql_parser.y"
                         {
        (yyvsp[-1].column_def)->indexed = true;
        (yyvsp[-1].column_def)->notNull = true;
        (yyval.column_def) = (yyvsp[-1].column_def);
    }
#line 1564 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 41: /* column_attrs: column_attrs DEFAULT literal  */
#line 318 "src/sql/sql_parser.y"
                                 {
        (yyvsp[-2].column_def)->hasDefault = true;
        (yyvsp[-2].column_def)->defaultValue = std::move(*(yyvsp[0].value));
        delete (yyvsp[0].value);
        (yyval.column_def) = (yyvsp[-2].column_def);
    }
#line 1575 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 42: /* insert_rows: '(' literal_list ')'  */
#line 327 "src/sql/sql_parser.y"
                         {
        auto* rows = new std::vector<std::vector<Value>>();
        rows->push_back(std::move(*(yyvsp[-1].values)));
        delete (yyvsp[-1].values);
        (yyval.row_values) = rows;
    }
#line 1586 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 43: /* insert_rows: insert_rows ',' '(' literal_list ')'  */
#line 333 "src/sql/sql_parser.y"
                                         {
        (yyvsp[-4].row_values)->push_back(std::move(*(yyvsp[-1].values)));
        delete (yyvsp[-1].values);
        (yyval.row_values) = (yyvsp[-4].row_values);
    }
#line 1596 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 44: /* literal_list: literal  */
#line 341 "src/sql/sql_parser.y"
            {
        auto* list = new std::vector<Value>();
        list->push_back(std::move(*(yyvsp[0].value)));
        delete (yyvsp[0].value);
        (yyval.values) = list;
    }
#line 1607 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 45: /* literal_list: literal_list ',' literal  */
#line 347 "src/sql/sql_parser.y"
                             {
        (yyvsp[-2].values)->push_back(std::move(*(yyvsp[0].value)));
        delete (yyvsp[0].value);
        (yyval.values) = (yyvsp[-2].values);
    }
#line 1617 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 46: /* literal: INT_LITERAL  */
#line 355 "src/sql/sql_parser.y"
                { (yyval.value) = (yyvsp[0].value); }
#line 1623 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 47: /* literal: STRING_LITERAL  */
#line 356 "src/sql/sql_parser.y"
                   { (yyval.value) = (yyvsp[0].value); }
#line 1629 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 48: /* literal: NULL_T  */
#line 357 "src/sql/sql_parser.y"
           { (yyval.value) = new Value(Value::null()); }
#line 1635 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 49: /* assignments: assignment  */
#line 361 "src/sql/sql_parser.y"
               {
        auto* list = new std::vector<Assignment>();
        list->push_back(std::move(*(yyvsp[0].assignment)));
        delete (yyvsp[0].assignment);
        (yyval.assignments) = list;
    }
#line 1646 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 50: /* assignments: assignments ',' assignment  */
#line 367 "src/sql/sql_parser.y"
                               {
        (yyvsp[-2].assignments)->push_back(std::move(*(yyvsp[0].assignment)));
        delete (yyvsp[0].assignment);
        (yyval.assignments) = (yyvsp[-2].assignments);
    }
#line 1656 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 51: /* assignment: identifier ASSIGN literal  */
#line 375 "src/sql/sql_parser.y"
                              {
        auto* assignment = new Assignment();
        assignment->column = *(yyvsp[-2].text);
        assignment->value = std::move(*(yyvsp[0].value));
        delete (yyvsp[-2].text);
        delete (yyvsp[0].value);
        (yyval.assignment) = assignment;
    }
#line 1669 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 52: /* select_list: '*'  */
#line 386 "src/sql/sql_parser.y"
        {
        auto* list = new std::vector<SelectItem>();
        SelectItem item;
        item.star = true;
        list->push_back(item);
        (yyval.select_items) = list;
    }
#line 1681 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 53: /* select_list: select_item_list  */
#line 393 "src/sql/sql_parser.y"
                     { (yyval.select_items) = (yyvsp[0].select_items); }
#line 1687 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 54: /* select_item_list: select_item  */
#line 397 "src/sql/sql_parser.y"
                {
        auto* list = new std::vector<SelectItem>();
        list->push_back(std::move(*(yyvsp[0].select_item)));
        delete (yyvsp[0].select_item);
        (yyval.select_items) = list;
    }
#line 1698 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 55: /* select_item_list: select_item_list ',' select_item  */
#line 403 "src/sql/sql_parser.y"
                                     {
        (yyvsp[-2].select_items)->push_back(std::move(*(yyvsp[0].select_item)));
        delete (yyvsp[0].select_item);
        (yyval.select_items) = (yyvsp[-2].select_items);
    }
#line 1708 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 56: /* select_item: identifier opt_alias  */
#line 411 "src/sql/sql_parser.y"
                         {
        auto* item = new SelectItem();
        item->column = *(yyvsp[-1].text);
        item->alias = *(yyvsp[0].text);
        delete (yyvsp[-1].text);
        delete (yyvsp[0].text);
        (yyval.select_item) = item;
    }
#line 1721 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 57: /* select_item: identifier '.' identifier opt_alias  */
#line 419 "src/sql/sql_parser.y"
                                        {
        auto* item = new SelectItem();
        item->column = *(yyvsp[-1].text);
        item->alias = *(yyvsp[0].text);
        delete (yyvsp[-3].text);
        delete (yyvsp[-1].text);
        delete (yyvsp[0].text);
        (yyval.select_item) = item;
    }
#line 1735 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 58: /* select_item: aggregate_function '(' '*' ')' opt_alias  */
#line 428 "src/sql/sql_parser.y"
                                             {
        auto* item = new SelectItem();
        item->aggregate = (yyvsp[-4].aggregate_kind);
        item->aggregateStar = true;
        item->alias = *(yyvsp[0].text);
        delete (yyvsp[0].text);
        (yyval.select_item) = item;
    }
#line 1748 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 59: /* select_item: aggregate_function '(' identifier ')' opt_alias  */
#line 436 "src/sql/sql_parser.y"
                                                    {
        auto* item = new SelectItem();
        item->aggregate = (yyvsp[-4].aggregate_kind);
        item->column = *(yyvsp[-2].text);
        item->alias = *(yyvsp[0].text);
        delete (yyvsp[-2].text);
        delete (yyvsp[0].text);
        (yyval.select_item) = item;
    }
#line 1762 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 60: /* select_item: aggregate_function '(' identifier '.' identifier ')' opt_alias  */
#line 445 "src/sql/sql_parser.y"
                                                                   {
        auto* item = new SelectItem();
        item->aggregate = (yyvsp[-6].aggregate_kind);
        item->column = *(yyvsp[-2].text);
        item->alias = *(yyvsp[0].text);
        delete (yyvsp[-4].text);
        delete (yyvsp[-2].text);
        delete (yyvsp[0].text);
        (yyval.select_item) = item;
    }
#line 1777 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 61: /* opt_alias: %empty  */
#line 458 "src/sql/sql_parser.y"
           { (yyval.text) = new std::string(); }
#line 1783 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 62: /* opt_alias: AS identifier  */
#line 459 "src/sql/sql_parser.y"
                  { (yyval.text) = (yyvsp[0].text); }
#line 1789 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 63: /* aggregate_function: COUNT  */
#line 463 "src/sql/sql_parser.y"
          { (yyval.aggregate_kind) = AggregateKind::Count; }
#line 1795 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 64: /* aggregate_function: SUM  */
#line 464 "src/sql/sql_parser.y"
        { (yyval.aggregate_kind) = AggregateKind::Sum; }
#line 1801 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 65: /* aggregate_function: AVG  */
#line 465 "src/sql/sql_parser.y"
        { (yyval.aggregate_kind) = AggregateKind::Avg; }
#line 1807 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 66: /* condition: disjunction  */
#line 469 "src/sql/sql_parser.y"
                { (yyval.expr) = (yyvsp[0].expr); }
#line 1813 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 67: /* disjunction: conjunction  */
#line 473 "src/sql/sql_parser.y"
                { (yyval.expr) = (yyvsp[0].expr); }
#line 1819 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 68: /* disjunction: disjunction OR conjunction  */
#line 474 "src/sql/sql_parser.y"
                               { (yyval.expr) = makeBinary(ExprKind::Or, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1825 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 69: /* conjunction: predicate  */
#line 478 "src/sql/sql_parser.y"
              { (yyval.expr) = (yyvsp[0].expr); }
#line 1831 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 70: /* conjunction: conjunction AND predicate  */
#line 479 "src/sql/sql_parser.y"
                              { (yyval.expr) = makeBinary(ExprKind::And, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1837 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 71: /* predicate: '(' condition ')'  */
#line 483 "src/sql/sql_parser.y"
                      { (yyval.expr) = (yyvsp[-1].expr); }
#line 1843 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 72: /* predicate: operand comparison_operator operand  */
#line 484 "src/sql/sql_parser.y"
                                        {
        auto* expr = new Expr();
        expr->kind = ExprKind::Compare;
        expr->left = std::move(*(yyvsp[-2].operand));
        expr->op = *(yyvsp[-1].text);
        expr->right = std::move(*(yyvsp[0].operand));
        delete (yyvsp[-2].operand);
        delete (yyvsp[-1].text);
        delete (yyvsp[0].operand);
        (yyval.expr) = expr;
    }
#line 1859 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 73: /* predicate: operand BETWEEN operand AND operand  */
#line 495 "src/sql/sql_parser.y"
                                        {
        auto* expr = new Expr();
        expr->kind = ExprKind::Between;
        expr->left = std::move(*(yyvsp[-4].operand));
        expr->right = std::move(*(yyvsp[-2].operand));
        expr->high = std::move(*(yyvsp[0].operand));
        delete (yyvsp[-4].operand);
        delete (yyvsp[-2].operand);
        delete (yyvsp[0].operand);
        (yyval.expr) = expr;
    }
#line 1875 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 74: /* predicate: operand LIKE operand  */
#line 506 "src/sql/sql_parser.y"
                         {
        auto* expr = new Expr();
        expr->kind = ExprKind::Like;
        expr->left = std::move(*(yyvsp[-2].operand));
        expr->right = std::move(*(yyvsp[0].operand));
        delete (yyvsp[-2].operand);
        delete (yyvsp[0].operand);
        (yyval.expr) = expr;
    }
#line 1889 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 75: /* operand: literal  */
#line 518 "src/sql/sql_parser.y"
            {
        auto* operand = new Operand(Operand::fromLiteral(std::move(*(yyvsp[0].value))));
        delete (yyvsp[0].value);
        (yyval.operand) = operand;
    }
#line 1899 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 76: /* operand: identifier  */
#line 523 "src/sql/sql_parser.y"
               {
        auto* operand = new Operand(Operand::fromColumn(*(yyvsp[0].text)));
        delete (yyvsp[0].text);
        (yyval.operand) = operand;
    }
#line 1909 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 77: /* operand: identifier '.' identifier  */
#line 528 "src/sql/sql_parser.y"
                              {
        auto* operand = new Operand(Operand::fromColumn(*(yyvsp[0].text)));
        delete (yyvsp[-2].text);
        delete (yyvsp[0].text);
        (yyval.operand) = operand;
    }
#line 1920 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 78: /* comparison_operator: EQ  */
#line 537 "src/sql/sql_parser.y"
       { (yyval.text) = new std::string("=="); }
#line 1926 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 79: /* comparison_operator: ASSIGN  */
#line 538 "src/sql/sql_parser.y"
           { (yyval.text) = new std::string("="); }
#line 1932 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 80: /* comparison_operator: NE  */
#line 539 "src/sql/sql_parser.y"
       { (yyval.text) = new std::string("!="); }
#line 1938 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 81: /* comparison_operator: LT  */
#line 540 "src/sql/sql_parser.y"
       { (yyval.text) = new std::string("<"); }
#line 1944 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 82: /* comparison_operator: LE  */
#line 541 "src/sql/sql_parser.y"
       { (yyval.text) = new std::string("<="); }
#line 1950 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 83: /* comparison_operator: GT  */
#line 542 "src/sql/sql_parser.y"
       { (yyval.text) = new std::string(">"); }
#line 1956 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;

  case 84: /* comparison_operator: GE  */
#line 543 "src/sql/sql_parser.y"
       { (yyval.text) = new std::string(">="); }
#line 1962 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"
    break;


#line 1966 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.cpp"

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

#line 546 "src/sql/sql_parser.y"


void yyerror(const char* message) {
    parseError = message ? message : "syntax error";
}

Statement parseSqlStatement(const std::string& source) {
    parsedStatement = nullptr;
    parseError.clear();

    YY_BUFFER_STATE buffer = yy_scan_string(source.c_str());
    int rc = 0;
    try {
        rc = yyparse();
    } catch (...) {
        yy_delete_buffer(buffer);
        yylex_destroy();
        delete parsedStatement;
        parsedStatement = nullptr;
        throw;
    }
    yy_delete_buffer(buffer);
    yylex_destroy();

    if (rc != 0 || !parsedStatement) {
        throw std::runtime_error(parseError.empty() ? "syntax error" : parseError);
    }

    Statement result = std::move(*parsedStatement);
    delete parsedStatement;
    parsedStatement = nullptr;
    return result;
}
