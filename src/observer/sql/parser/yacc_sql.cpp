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
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.hpp"
#include "sql/parser/lex_sql.h"
#include "sql/expr/expression.h"
#include "event/sql_debug.h"

using namespace std;

string token_name(const char *sql_string, YYLTYPE *llocp)
{
  return string(sql_string + llocp->first_column, llocp->last_column - llocp->first_column + 1);
}

int yyerror(YYLTYPE *llocp, const char *sql_string, ParsedSqlResult *sql_result, yyscan_t scanner, const char *msg)
{
  std::unique_ptr<ParsedSqlNode> error_sql_node = std::make_unique<ParsedSqlNode>(SCF_ERROR);
  error_sql_node->error.error_msg = msg;
  error_sql_node->error.line = llocp->first_line;
  error_sql_node->error.column = llocp->first_column;
  sql_result->add_sql_node(std::move(error_sql_node));
  return 0;
}

ArithmeticExpr *create_arithmetic_expression(ArithmeticExpr::Type type,
                                             Expression *left,
                                             Expression *right,
                                             const char *sql_string,
                                             YYLTYPE *llocp)
{
  ArithmeticExpr *expr = new ArithmeticExpr(type, left, right);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}


#line 116 "yacc_sql.cpp"

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

#include "yacc_sql.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_CREATE = 4,                     /* CREATE  */
  YYSYMBOL_DROP = 5,                       /* DROP  */
  YYSYMBOL_TABLE = 6,                      /* TABLE  */
  YYSYMBOL_TABLES = 7,                     /* TABLES  */
  YYSYMBOL_INDEX = 8,                      /* INDEX  */
  YYSYMBOL_CALC = 9,                       /* CALC  */
  YYSYMBOL_SELECT = 10,                    /* SELECT  */
  YYSYMBOL_DESC = 11,                      /* DESC  */
  YYSYMBOL_SHOW = 12,                      /* SHOW  */
  YYSYMBOL_SYNC = 13,                      /* SYNC  */
  YYSYMBOL_INSERT = 14,                    /* INSERT  */
  YYSYMBOL_DELETE = 15,                    /* DELETE  */
  YYSYMBOL_UPDATE = 16,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 17,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 18,                    /* RBRACE  */
  YYSYMBOL_COMMA = 19,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 20,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 21,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 22,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 23,                     /* INT_T  */
  YYSYMBOL_STRING_T = 24,                  /* STRING_T  */
  YYSYMBOL_TEXT_T = 25,                    /* TEXT_T  */
  YYSYMBOL_FLOAT_T = 26,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 27,                    /* DATE_T  */
  YYSYMBOL_HELP = 28,                      /* HELP  */
  YYSYMBOL_EXIT = 29,                      /* EXIT  */
  YYSYMBOL_DOT = 30,                       /* DOT  */
  YYSYMBOL_INTO = 31,                      /* INTO  */
  YYSYMBOL_VALUES = 32,                    /* VALUES  */
  YYSYMBOL_FROM = 33,                      /* FROM  */
  YYSYMBOL_WHERE = 34,                     /* WHERE  */
  YYSYMBOL_AND = 35,                       /* AND  */
  YYSYMBOL_SET = 36,                       /* SET  */
  YYSYMBOL_UNIQUE = 37,                    /* UNIQUE  */
  YYSYMBOL_ON = 38,                        /* ON  */
  YYSYMBOL_LOAD = 39,                      /* LOAD  */
  YYSYMBOL_DATA = 40,                      /* DATA  */
  YYSYMBOL_INFILE = 41,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 42,                   /* EXPLAIN  */
  YYSYMBOL_EQ = 43,                        /* EQ  */
  YYSYMBOL_LT = 44,                        /* LT  */
  YYSYMBOL_GT = 45,                        /* GT  */
  YYSYMBOL_LE = 46,                        /* LE  */
  YYSYMBOL_GE = 47,                        /* GE  */
  YYSYMBOL_NE = 48,                        /* NE  */
  YYSYMBOL_NOT = 49,                       /* NOT  */
  YYSYMBOL_LIKE = 50,                      /* LIKE  */
  YYSYMBOL_MIN = 51,                       /* MIN  */
  YYSYMBOL_MAX = 52,                       /* MAX  */
  YYSYMBOL_AVG = 53,                       /* AVG  */
  YYSYMBOL_SUM = 54,                       /* SUM  */
  YYSYMBOL_COUNT = 55,                     /* COUNT  */
  YYSYMBOL_INNER = 56,                     /* INNER  */
  YYSYMBOL_JOIN = 57,                      /* JOIN  */
  YYSYMBOL_NULL_IS = 58,                   /* NULL_IS  */
  YYSYMBOL_OB_NULL = 59,                   /* OB_NULL  */
  YYSYMBOL_ORDER = 60,                     /* ORDER  */
  YYSYMBOL_BY = 61,                        /* BY  */
  YYSYMBOL_ASC = 62,                       /* ASC  */
  YYSYMBOL_AS = 63,                        /* AS  */
  YYSYMBOL_IN = 64,                        /* IN  */
  YYSYMBOL_EXISTS = 65,                    /* EXISTS  */
  YYSYMBOL_NUMBER = 66,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 67,                     /* FLOAT  */
  YYSYMBOL_ID = 68,                        /* ID  */
  YYSYMBOL_SSS = 69,                       /* SSS  */
  YYSYMBOL_DATE_STR = 70,                  /* DATE_STR  */
  YYSYMBOL_71_ = 71,                       /* '+'  */
  YYSYMBOL_72_ = 72,                       /* '-'  */
  YYSYMBOL_73_ = 73,                       /* '*'  */
  YYSYMBOL_74_ = 74,                       /* '/'  */
  YYSYMBOL_UMINUS = 75,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 76,                  /* $accept  */
  YYSYMBOL_commands = 77,                  /* commands  */
  YYSYMBOL_command_wrapper = 78,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 79,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 80,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 81,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 82,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 83,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 84,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 85,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 86,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 87,           /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 88,         /* create_index_stmt  */
  YYSYMBOL_attr_name_list = 89,            /* attr_name_list  */
  YYSYMBOL_index_attr = 90,                /* index_attr  */
  YYSYMBOL_index_attr_name_list = 91,      /* index_attr_name_list  */
  YYSYMBOL_drop_index_stmt = 92,           /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 93,         /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 94,             /* attr_def_list  */
  YYSYMBOL_attr_def = 95,                  /* attr_def  */
  YYSYMBOL_null = 96,                      /* null  */
  YYSYMBOL_number = 97,                    /* number  */
  YYSYMBOL_type = 98,                      /* type  */
  YYSYMBOL_insert_stmt = 99,               /* insert_stmt  */
  YYSYMBOL_value_list = 100,               /* value_list  */
  YYSYMBOL_value = 101,                    /* value  */
  YYSYMBOL_delete_stmt = 102,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 103,              /* update_stmt  */
  YYSYMBOL_update_value_list = 104,        /* update_value_list  */
  YYSYMBOL_select_stmt = 105,              /* select_stmt  */
  YYSYMBOL_inner_join_constr = 106,        /* inner_join_constr  */
  YYSYMBOL_inner_join_list = 107,          /* inner_join_list  */
  YYSYMBOL_order_by_clause = 108,          /* order_by_clause  */
  YYSYMBOL_order_by_list = 109,            /* order_by_list  */
  YYSYMBOL_order_by_item = 110,            /* order_by_item  */
  YYSYMBOL_calc_stmt = 111,                /* calc_stmt  */
  YYSYMBOL_expression_list = 112,          /* expression_list  */
  YYSYMBOL_expression = 113,               /* expression  */
  YYSYMBOL_option_as = 114,                /* option_as  */
  YYSYMBOL_select_attr = 115,              /* select_attr  */
  YYSYMBOL_agg = 116,                      /* agg  */
  YYSYMBOL_rel_attr = 117,                 /* rel_attr  */
  YYSYMBOL_attr_list = 118,                /* attr_list  */
  YYSYMBOL_rel_list = 119,                 /* rel_list  */
  YYSYMBOL_where = 120,                    /* where  */
  YYSYMBOL_condition_list = 121,           /* condition_list  */
  YYSYMBOL_condition = 122,                /* condition  */
  YYSYMBOL_in_op = 123,                    /* in_op  */
  YYSYMBOL_comp_op = 124,                  /* comp_op  */
  YYSYMBOL_load_data_stmt = 125,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 126,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 127,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 128             /* opt_semicolon  */
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
typedef yytype_int16 yy_state_t;

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

#if 1

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
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  74
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   321

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  76
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  141
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  284

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   326


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
       2,     2,    73,    71,     2,    72,     2,    74,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    75
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   217,   217,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   248,   254,   259,   265,   271,   277,   283,
     290,   296,   304,   317,   331,   342,   350,   353,   366,   376,
     395,   398,   412,   420,   435,   438,   441,   448,   452,   453,
     454,   455,   456,   459,   475,   478,   489,   493,   497,   503,
     509,   517,   529,   556,   559,   575,   607,   650,   662,   665,
     681,   684,   690,   695,   707,   715,   723,   734,   744,   749,
     760,   763,   766,   769,   772,   776,   779,   788,   791,   796,
     805,   820,   830,   841,   847,   856,   859,   862,   865,   868,
     874,   885,   898,   905,   915,   923,   926,   940,   943,   961,
     964,   970,   973,   978,   985,   997,  1009,  1021,  1033,  1043,
    1058,  1068,  1083,  1095,  1096,  1097,  1098,  1102,  1103,  1104,
    1105,  1106,  1107,  1108,  1109,  1110,  1111,  1115,  1128,  1136,
    1146,  1147
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "CREATE",
  "DROP", "TABLE", "TABLES", "INDEX", "CALC", "SELECT", "DESC", "SHOW",
  "SYNC", "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA",
  "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T", "TEXT_T",
  "FLOAT_T", "DATE_T", "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM",
  "WHERE", "AND", "SET", "UNIQUE", "ON", "LOAD", "DATA", "INFILE",
  "EXPLAIN", "EQ", "LT", "GT", "LE", "GE", "NE", "NOT", "LIKE", "MIN",
  "MAX", "AVG", "SUM", "COUNT", "INNER", "JOIN", "NULL_IS", "OB_NULL",
  "ORDER", "BY", "ASC", "AS", "IN", "EXISTS", "NUMBER", "FLOAT", "ID",
  "SSS", "DATE_STR", "'+'", "'-'", "'*'", "'/'", "UMINUS", "$accept",
  "commands", "command_wrapper", "exit_stmt", "help_stmt", "sync_stmt",
  "begin_stmt", "commit_stmt", "rollback_stmt", "drop_table_stmt",
  "show_tables_stmt", "desc_table_stmt", "create_index_stmt",
  "attr_name_list", "index_attr", "index_attr_name_list",
  "drop_index_stmt", "create_table_stmt", "attr_def_list", "attr_def",
  "null", "number", "type", "insert_stmt", "value_list", "value",
  "delete_stmt", "update_stmt", "update_value_list", "select_stmt",
  "inner_join_constr", "inner_join_list", "order_by_clause",
  "order_by_list", "order_by_item", "calc_stmt", "expression_list",
  "expression", "option_as", "select_attr", "agg", "rel_attr", "attr_list",
  "rel_list", "where", "condition_list", "condition", "in_op", "comp_op",
  "load_data_stmt", "explain_stmt", "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-186)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     178,    13,    36,    43,   150,   -50,    19,  -186,    42,    55,
      29,  -186,  -186,  -186,  -186,  -186,    40,    24,   178,   101,
     108,  -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,
    -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,
    -186,    49,    59,   115,    65,    66,    43,  -186,  -186,  -186,
    -186,  -186,    43,  -186,  -186,    48,  -186,  -186,  -186,  -186,
    -186,   -15,  -186,   105,   123,   134,  -186,  -186,    74,    86,
     119,   126,   121,  -186,  -186,  -186,  -186,   154,   135,   104,
    -186,   136,     5,  -186,    43,    43,    43,    43,    43,   112,
     116,  -186,   117,    31,   182,  -186,   145,   161,   128,   109,
     144,   129,   147,   181,   148,  -186,  -186,    33,    33,  -186,
    -186,   158,  -186,   -34,  -186,    -2,    52,   205,   210,   213,
     212,   221,    77,  -186,   202,  -186,   215,   185,   228,   231,
     183,  -186,  -186,   192,   196,   234,  -186,   186,   212,   182,
      -5,   182,    23,   182,  -186,   109,   245,   214,   -13,  -186,
     230,   109,   260,  -186,  -186,  -186,  -186,  -186,    -3,   129,
     249,   200,   252,   203,   216,   161,   206,   161,    -6,  -186,
     258,    25,   259,   261,   251,   262,  -186,  -186,  -186,  -186,
    -186,  -186,   232,  -186,   229,   173,   -25,  -186,  -186,   264,
      97,    77,   265,   217,   220,   224,  -186,  -186,   228,  -186,
    -186,   269,   270,   200,   250,   222,   233,   158,   233,  -186,
    -186,   223,  -186,  -186,   109,   274,   214,  -186,  -186,  -186,
    -186,  -186,  -186,    -1,    -1,  -186,  -186,  -186,   226,   161,
    -186,  -186,   277,  -186,  -186,  -186,   200,  -186,   278,    77,
     263,   236,  -186,   234,  -186,   280,   251,  -186,   182,   251,
     281,   251,   282,   266,  -186,   -32,   270,  -186,  -186,    77,
     182,  -186,  -186,  -186,   284,  -186,   285,  -186,   109,  -186,
    -186,   196,  -186,   286,     0,  -186,  -186,   265,  -186,   182,
    -186,  -186,  -186,  -186
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    25,     0,     0,
       0,    26,    27,    28,    24,    23,     0,     0,     0,     0,
     140,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,     4,     3,    18,    19,
      20,     0,     0,     0,     0,     0,     0,    60,    56,    57,
      58,    59,     0,    86,    77,    78,    95,    96,    97,    98,
      99,    87,    89,     0,     0,   105,    31,    30,     0,     0,
       0,     0,     0,   138,     1,   141,     2,     0,     0,     0,
      29,     0,     0,    85,     0,     0,     0,     0,     0,     0,
       0,   100,     0,     0,     0,    92,     0,   109,     0,     0,
       0,     0,     0,     0,     0,    84,    79,    80,    81,    82,
      83,    87,    88,    87,   104,    87,     0,     0,     0,     0,
     105,     0,   111,    61,     0,   139,     0,     0,    40,     0,
       0,    38,   101,     0,    68,   107,   102,     0,   105,     0,
       0,     0,     0,     0,   106,     0,     0,     0,     0,   110,
     112,     0,     0,    48,    50,    49,    51,    52,    44,     0,
       0,     0,     0,     0,     0,   109,     0,   109,    87,    90,
       0,     0,     0,     0,    54,     0,   127,   128,   129,   130,
     131,   132,     0,   133,   135,     0,     0,   123,   125,     0,
       0,   111,    63,     0,     0,     0,    45,    43,    40,    39,
      35,     0,    36,     0,     0,     0,    70,    87,    70,   103,
      94,     0,    93,    91,     0,     0,     0,   134,   136,   115,
     117,   124,   126,     0,     0,   114,   116,   113,     0,   109,
     137,    47,     0,    46,    41,    32,     0,    34,     0,   111,
       0,     0,    66,   107,    65,     0,    54,    53,     0,    54,
       0,    54,     0,     0,    62,    44,    36,    33,    67,   111,
       0,   108,    55,   122,     0,   118,     0,   120,     0,    42,
      37,    68,    71,    72,    74,   119,   121,    63,    69,     0,
      76,    75,    64,    73
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -186,  -186,   288,  -186,  -186,  -186,  -186,  -186,  -186,  -186,
    -186,  -186,  -186,   107,    68,    51,  -186,  -186,   110,   152,
      57,  -186,  -186,  -186,  -146,   -98,  -186,  -186,    37,  -143,
    -186,    44,   111,    34,  -186,  -186,   237,    72,  -109,  -186,
       1,    -4,  -100,    73,  -157,  -185,  -186,  -186,  -141,  -186,
    -186,  -186,  -186
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,   201,   202,   237,    31,    32,   160,   128,
     197,   232,   158,    33,   215,    53,    34,    35,   229,    36,
     134,   165,   242,   272,   273,    37,    54,    55,    91,    63,
     117,   148,    95,   167,   123,   149,   150,   189,   185,    38,
      39,    40,    76
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      65,   125,   132,   175,   135,    64,   227,   190,   206,     4,
     208,   280,   209,   114,   194,    89,   136,   195,    66,    41,
     144,    42,   133,   105,   147,   217,    67,   196,   137,    90,
     176,   177,   178,   179,   180,   181,   186,   183,   169,   221,
     222,   114,    44,   136,    45,   184,   195,   174,    90,   114,
      43,   187,   188,   192,   258,   211,   196,    90,    47,   132,
      46,    90,   281,   171,    72,    48,    49,    84,    50,    51,
     138,   139,   254,    68,   271,   248,    85,    86,    87,    88,
     250,   252,    56,    57,    58,    59,    60,   219,    69,   118,
     120,   171,   225,   147,   146,   119,   173,    70,   243,   115,
     262,    74,    47,   264,   116,   266,    87,    88,    71,    48,
      49,    75,    50,    51,   224,    52,   246,    77,    82,    85,
      86,    87,    88,    79,    83,   249,   251,    78,    56,    57,
      58,    59,    60,    80,    81,   170,    47,   172,    92,   120,
      93,   147,    96,    48,    49,    61,    50,    51,    56,    57,
      58,    59,    60,    94,    97,    98,    47,   107,   108,   109,
     110,   147,   100,    48,    49,    61,    50,    51,    47,    99,
     277,   101,   103,   102,   104,    48,    49,   121,    50,    51,
     111,   220,     1,     2,   112,   113,   226,     3,     4,     5,
       6,     7,     8,     9,    10,   122,   124,   127,    11,    12,
      13,    56,    57,    58,    59,    60,    14,    15,   153,   154,
     155,   156,   157,   126,    16,   129,   131,    17,    61,   130,
      18,    90,   140,    62,    56,    57,    58,    59,    60,   141,
     142,   143,    47,    56,    57,    58,    59,    60,   145,    48,
      49,    61,    50,    51,   263,   151,   152,   159,   161,   163,
      61,   162,   164,   166,   168,     4,   274,   176,   177,   178,
     179,   180,   181,   182,   183,   191,   193,   199,   200,   203,
     214,   204,   184,   205,   207,   274,   210,   212,   218,   213,
     216,   223,   217,   233,   228,   230,   231,   235,   239,   236,
     240,   245,   247,   241,   253,   255,   257,   260,   209,   265,
     267,   259,   275,   276,   256,   279,    73,   270,   234,   268,
     238,   198,   269,   283,   282,   278,   261,     0,     0,   244,
       0,   106
};

static const yytype_int16 yycheck[] =
{
       4,    99,   111,   146,   113,     4,   191,   148,   165,    10,
     167,    11,    18,    18,    17,    30,    18,    49,    68,     6,
     120,     8,    56,    18,   122,    50,     7,    59,    30,    63,
      43,    44,    45,    46,    47,    48,    49,    50,   138,    64,
      65,    18,     6,    18,     8,    58,    49,   145,    63,    18,
      37,    64,    65,   151,   239,    30,    59,    63,    59,   168,
      17,    63,    62,    68,    40,    66,    67,    19,    69,    70,
      18,    19,   229,    31,   259,   216,    71,    72,    73,    74,
     223,   224,    51,    52,    53,    54,    55,   185,    33,    93,
      94,    68,   190,   191,    17,    94,    73,    68,   207,    68,
     246,     0,    59,   249,    73,   251,    73,    74,    68,    66,
      67,     3,    69,    70,    17,    72,   214,    68,    46,    71,
      72,    73,    74,     8,    52,   223,   224,    68,    51,    52,
      53,    54,    55,    68,    68,   139,    59,   141,    33,   143,
      17,   239,    68,    66,    67,    68,    69,    70,    51,    52,
      53,    54,    55,    19,    68,    36,    59,    85,    86,    87,
      88,   259,    41,    66,    67,    68,    69,    70,    59,    43,
     268,    17,    68,    38,    38,    66,    67,    32,    69,    70,
      68,   185,     4,     5,    68,    68,   190,     9,    10,    11,
      12,    13,    14,    15,    16,    34,    68,    68,    20,    21,
      22,    51,    52,    53,    54,    55,    28,    29,    23,    24,
      25,    26,    27,    69,    36,    68,    68,    39,    68,    38,
      42,    63,    17,    73,    51,    52,    53,    54,    55,    19,
      17,    19,    59,    51,    52,    53,    54,    55,    17,    66,
      67,    68,    69,    70,   248,    43,    31,    19,    17,    57,
      68,    68,    56,    19,    68,    10,   260,    43,    44,    45,
      46,    47,    48,    49,    50,    35,     6,    18,    68,    17,
      19,    68,    58,    57,    68,   279,    18,    18,    49,    18,
      18,    17,    50,    59,    19,    68,    66,    18,    38,    19,
      68,    68,    18,    60,    68,    18,    18,    61,    18,    18,
      18,    38,    18,    18,   236,    19,    18,   256,   198,    43,
     203,   159,   255,   279,   277,   271,   243,    -1,    -1,   208,
      -1,    84
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,     9,    10,    11,    12,    13,    14,    15,
      16,    20,    21,    22,    28,    29,    36,    39,    42,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    92,    93,    99,   102,   103,   105,   111,   125,   126,
     127,     6,     8,    37,     6,     8,    17,    59,    66,    67,
      69,    70,    72,   101,   112,   113,    51,    52,    53,    54,
      55,    68,    73,   115,   116,   117,    68,     7,    31,    33,
      68,    68,    40,    78,     0,     3,   128,    68,    68,     8,
      68,    68,   113,   113,    19,    71,    72,    73,    74,    30,
      63,   114,    33,    17,    19,   118,    68,    68,    36,    43,
      41,    17,    38,    68,    38,    18,   112,   113,   113,   113,
     113,    68,    68,    68,    18,    68,    73,   116,   117,   116,
     117,    32,    34,   120,    68,   101,    69,    68,    95,    68,
      38,    68,   114,    56,   106,   114,    18,    30,    18,    19,
      17,    19,    17,    19,   118,    17,    17,   101,   117,   121,
     122,    43,    31,    23,    24,    25,    26,    27,    98,    19,
      94,    17,    68,    57,    56,   107,    19,   119,    68,   118,
     117,    68,   117,    73,   101,   105,    43,    44,    45,    46,
      47,    48,    49,    50,    58,   124,    49,    64,    65,   123,
     124,    35,   101,     6,    17,    49,    59,    96,    95,    18,
      68,    89,    90,    17,    68,    57,   120,    68,   120,    18,
      18,    30,    18,    18,    19,   100,    18,    50,    49,   101,
     117,    64,    65,    17,    17,   101,   117,   121,    19,   104,
      68,    66,    97,    59,    94,    18,    19,    91,    89,    38,
      68,    60,   108,   114,   108,    68,   101,    18,   124,   101,
     105,   101,   105,    68,   120,    18,    90,    18,   121,    38,
      61,   119,   100,   117,   100,    18,   100,    18,    43,    96,
      91,   121,   109,   110,   117,    18,    18,   101,   107,    19,
      11,    62,   104,   109
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    76,    77,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    88,    89,    90,    91,    91,    92,    93,
      94,    94,    95,    95,    96,    96,    96,    97,    98,    98,
      98,    98,    98,    99,   100,   100,   101,   101,   101,   101,
     101,   102,   103,   104,   104,   105,   105,   106,   107,   107,
     108,   108,   109,   109,   110,   110,   110,   111,   112,   112,
     113,   113,   113,   113,   113,   113,   113,   114,   114,   115,
     115,   115,   115,   115,   115,   116,   116,   116,   116,   116,
     117,   117,   117,   117,   117,   118,   118,   119,   119,   120,
     120,   121,   121,   121,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   123,   123,   123,   123,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   125,   126,   127,
     128,   128
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     2,     8,     9,     2,     1,     0,     3,     5,     7,
       0,     3,     6,     3,     0,     1,     2,     1,     1,     1,
       1,     1,     1,     8,     0,     3,     1,     1,     1,     1,
       1,     4,     8,     0,     5,     8,     8,     5,     0,     6,
       0,     3,     1,     3,     1,     2,     2,     2,     1,     3,
       3,     3,     3,     3,     3,     2,     1,     0,     2,     1,
       5,     6,     2,     6,     6,     1,     1,     1,     1,     1,
       2,     4,     4,     6,     3,     0,     3,     0,     4,     0,
       2,     0,     1,     3,     3,     3,     3,     3,     5,     6,
       5,     6,     5,     1,     2,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     2,     7,     2,     4,
       0,     1
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
        yyerror (&yylloc, sql_string, sql_result, scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, sql_string, sql_result, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, sql_string, sql_result, scanner);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
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
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), sql_string, sql_result, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, sql_string, sql_result, scanner); \
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

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

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yychar = yylex (&yylval, &yylloc, scanner);
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
      yyerror_range[1] = yylloc;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* commands: command_wrapper opt_semicolon  */
#line 218 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1848 "yacc_sql.cpp"
    break;

  case 23: /* exit_stmt: EXIT  */
#line 248 "yacc_sql.y"
         {
      (void) yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1857 "yacc_sql.cpp"
    break;

  case 24: /* help_stmt: HELP  */
#line 254 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1865 "yacc_sql.cpp"
    break;

  case 25: /* sync_stmt: SYNC  */
#line 259 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1873 "yacc_sql.cpp"
    break;

  case 26: /* begin_stmt: TRX_BEGIN  */
#line 265 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1881 "yacc_sql.cpp"
    break;

  case 27: /* commit_stmt: TRX_COMMIT  */
#line 271 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1889 "yacc_sql.cpp"
    break;

  case 28: /* rollback_stmt: TRX_ROLLBACK  */
#line 277 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1897 "yacc_sql.cpp"
    break;

  case 29: /* drop_table_stmt: DROP TABLE ID  */
#line 283 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1907 "yacc_sql.cpp"
    break;

  case 30: /* show_tables_stmt: SHOW TABLES  */
#line 290 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1915 "yacc_sql.cpp"
    break;

  case 31: /* desc_table_stmt: DESC ID  */
#line 296 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1925 "yacc_sql.cpp"
    break;

  case 32: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE attr_name_list RBRACE  */
#line 305 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-5].string);
      create_index.relation_name = (yyvsp[-3].string);
      create_index.attribute_names.swap(*(yyvsp[-1].attr_name_list));
      create_index.is_unique = false;
      free((yyvsp[-5].string));
      free((yyvsp[-3].string));
      free((yyvsp[-1].attr_name_list));
    }
#line 1941 "yacc_sql.cpp"
    break;

  case 33: /* create_index_stmt: CREATE UNIQUE INDEX ID ON ID LBRACE attr_name_list RBRACE  */
#line 318 "yacc_sql.y"
    {
        (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
        CreateIndexSqlNode& create_index = (yyval.sql_node)->create_index;
        create_index.index_name = (yyvsp[-5].string);
        create_index.relation_name = (yyvsp[-3].string);
        create_index.attribute_names.swap(*(yyvsp[-1].attr_name_list));
        create_index.is_unique = true;
        free((yyvsp[-5].string));
        free((yyvsp[-3].string));
        free((yyvsp[-1].attr_name_list));
    }
#line 1957 "yacc_sql.cpp"
    break;

  case 34: /* attr_name_list: index_attr index_attr_name_list  */
#line 331 "yacc_sql.y"
                                    {
      if((yyvsp[0].index_attr_name_list) != nullptr) {
        (yyval.attr_name_list) = (yyvsp[0].index_attr_name_list);
      } else {
        (yyval.attr_name_list) = new std::vector<IndexAttr>;
      }
      (yyval.attr_name_list)->push_back(*(yyvsp[-1].index_attr));
      delete (yyvsp[-1].index_attr);
    }
#line 1971 "yacc_sql.cpp"
    break;

  case 35: /* index_attr: ID  */
#line 342 "yacc_sql.y"
     {
    (yyval.index_attr) = new IndexAttr;
    (yyval.index_attr)->attribute_name = (yyvsp[0].string);
    free((yyvsp[0].string));
  }
#line 1981 "yacc_sql.cpp"
    break;

  case 36: /* index_attr_name_list: %empty  */
#line 350 "yacc_sql.y"
    {
      (yyval.index_attr_name_list) = nullptr;
    }
#line 1989 "yacc_sql.cpp"
    break;

  case 37: /* index_attr_name_list: COMMA index_attr index_attr_name_list  */
#line 353 "yacc_sql.y"
                                            {
      if ((yyvsp[0].index_attr_name_list) != nullptr) {
        (yyval.index_attr_name_list) = (yyvsp[0].index_attr_name_list);
      } else {
        (yyval.index_attr_name_list) = new std::vector<IndexAttr>;
      }

      (yyval.index_attr_name_list)->emplace_back(*(yyvsp[-1].index_attr));
      delete (yyvsp[-1].index_attr);
    }
#line 2004 "yacc_sql.cpp"
    break;

  case 38: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 367 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2016 "yacc_sql.cpp"
    break;

  case 39: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE  */
#line 377 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-4].string);
      free((yyvsp[-4].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-1].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-2].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-2].attr_info);
    }
#line 2036 "yacc_sql.cpp"
    break;

  case 40: /* attr_def_list: %empty  */
#line 395 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2044 "yacc_sql.cpp"
    break;

  case 41: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 399 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2058 "yacc_sql.cpp"
    break;

  case 42: /* attr_def: ID type LBRACE number RBRACE null  */
#line 412 "yacc_sql.y"
                                      {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->is_null = (yyvsp[0].null);
      free((yyvsp[-5].string));
    }
#line 2071 "yacc_sql.cpp"
    break;

  case 43: /* attr_def: ID type null  */
#line 420 "yacc_sql.y"
                   {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType) (yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      if((yyval.attr_info)->type == AttrType::TEXT) {
        (yyval.attr_info)->length = 65535; // need to change
      }
      (yyval.attr_info)->is_null = (yyvsp[0].null);
      free((yyvsp[-2].string));
    }
#line 2087 "yacc_sql.cpp"
    break;

  case 44: /* null: %empty  */
#line 435 "yacc_sql.y"
  {
    (yyval.null) = false;
  }
#line 2095 "yacc_sql.cpp"
    break;

  case 45: /* null: OB_NULL  */
#line 438 "yacc_sql.y"
            {
    (yyval.null) = true;
  }
#line 2103 "yacc_sql.cpp"
    break;

  case 46: /* null: NOT OB_NULL  */
#line 441 "yacc_sql.y"
                {
    // Note that we do NOT need to deal with `NOT NULL` here
    // Since this property will be enable if NULL is not explicitly declared
    (yyval.null) = false;
  }
#line 2113 "yacc_sql.cpp"
    break;

  case 47: /* number: NUMBER  */
#line 448 "yacc_sql.y"
           { (yyval.number) = (yyvsp[0].number); }
#line 2119 "yacc_sql.cpp"
    break;

  case 48: /* type: INT_T  */
#line 452 "yacc_sql.y"
               { (yyval.number) = INTS; }
#line 2125 "yacc_sql.cpp"
    break;

  case 49: /* type: TEXT_T  */
#line 453 "yacc_sql.y"
                 { (yyval.number) = TEXT; }
#line 2131 "yacc_sql.cpp"
    break;

  case 50: /* type: STRING_T  */
#line 454 "yacc_sql.y"
               { (yyval.number) = CHARS; }
#line 2137 "yacc_sql.cpp"
    break;

  case 51: /* type: FLOAT_T  */
#line 455 "yacc_sql.y"
               { (yyval.number) = FLOATS; }
#line 2143 "yacc_sql.cpp"
    break;

  case 52: /* type: DATE_T  */
#line 456 "yacc_sql.y"
               { (yyval.number) = DATE; }
#line 2149 "yacc_sql.cpp"
    break;

  case 53: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 460 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-5].string);
      if ((yyvsp[-1].value_list) != nullptr) {
        (yyval.sql_node)->insertion.values.swap(*(yyvsp[-1].value_list));
      }
      (yyval.sql_node)->insertion.values.emplace_back(*(yyvsp[-2].value));
      std::reverse((yyval.sql_node)->insertion.values.begin(), (yyval.sql_node)->insertion.values.end());
      delete (yyvsp[-2].value);
      free((yyvsp[-5].string));
    }
#line 2165 "yacc_sql.cpp"
    break;

  case 54: /* value_list: %empty  */
#line 475 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2173 "yacc_sql.cpp"
    break;

  case 55: /* value_list: COMMA value value_list  */
#line 478 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2187 "yacc_sql.cpp"
    break;

  case 56: /* value: NUMBER  */
#line 489 "yacc_sql.y"
           {
      (yyval.value) = new Value(static_cast<int>((yyvsp[0].number)));
      (yyloc) = (yylsp[0]);
    }
#line 2196 "yacc_sql.cpp"
    break;

  case 57: /* value: FLOAT  */
#line 493 "yacc_sql.y"
            {
      (yyval.value) = new Value(static_cast<float>((yyvsp[0].floats)));
      (yyloc) = (yylsp[0]);
    }
#line 2205 "yacc_sql.cpp"
    break;

  case 58: /* value: SSS  */
#line 497 "yacc_sql.y"
          {
      /* This is to eliminate the double/single quotes from the input string */
      char *tmp = common::substr((yyvsp[0].string), 1, strlen((yyvsp[0].string)) - 2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2216 "yacc_sql.cpp"
    break;

  case 59: /* value: DATE_STR  */
#line 503 "yacc_sql.y"
               {
      char *tmp = common::substr((yyvsp[0].string), 1, strlen((yyvsp[0].string)) - 2);
      /* Note the length here is by default 10 */
      (yyval.value) = new Value(DATE, tmp);
      free(tmp);
    }
#line 2227 "yacc_sql.cpp"
    break;

  case 60: /* value: OB_NULL  */
#line 509 "yacc_sql.y"
              {
      // Note that we can not get the actual schema of this column right here
      // Will adjust the value to the actual type later
      (yyval.value) = new Value(0);
      (yyval.value)->set_null();
    }
#line 2238 "yacc_sql.cpp"
    break;

  case 61: /* delete_stmt: DELETE FROM ID where  */
#line 518 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2252 "yacc_sql.cpp"
    break;

  case 62: /* update_stmt: UPDATE ID SET ID EQ value update_value_list where  */
#line 530 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.relation_name = (yyvsp[-6].string);

      UpdateValueNode node;
      node.attribute_name = (yyvsp[-4].string);
      node.value = *(yyvsp[-2].value);

      (yyval.sql_node)->update.update_values.emplace_back(node);

      if ((yyvsp[-1].update_value_list) != nullptr) {
      	(yyval.sql_node)->update.update_values.insert((yyval.sql_node)->update.update_values.end(), (yyvsp[-1].update_value_list)->begin(), (yyvsp[-1].update_value_list)->end());
	delete (yyvsp[-1].update_value_list);
      }

      if ((yyvsp[0].condition_list)!= nullptr) {
        (yyval.sql_node)->update.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-6].string));
      free((yyvsp[-4].string));
    }
#line 2279 "yacc_sql.cpp"
    break;

  case 63: /* update_value_list: %empty  */
#line 556 "yacc_sql.y"
    {
      (yyval.update_value_list) = nullptr;
    }
#line 2287 "yacc_sql.cpp"
    break;

  case 64: /* update_value_list: COMMA ID EQ value update_value_list  */
#line 559 "yacc_sql.y"
                                           {
      if ((yyvsp[0].update_value_list) != nullptr) {
	(yyval.update_value_list) = (yyvsp[0].update_value_list);
      } else {
	(yyval.update_value_list) = new std::vector<UpdateValueNode>;
      }
      UpdateValueNode node;
      node.attribute_name = (yyvsp[-3].string);
      node.value = *(yyvsp[-1].value);
      (yyval.update_value_list)->emplace_back(node);
      delete (yyvsp[-3].string);
      delete (yyvsp[-1].value);
    }
#line 2305 "yacc_sql.cpp"
    break;

  case 65: /* select_stmt: SELECT select_attr FROM ID option_as rel_list where order_by_clause  */
#line 576 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-6].rel_attr_list) != nullptr) {
        (yyval.sql_node)->selection.attributes.swap(*(yyvsp[-6].rel_attr_list));
        delete (yyvsp[-6].rel_attr_list);
      }
      if ((yyvsp[-2].relation_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap(*(yyvsp[-2].relation_list));
        delete (yyvsp[-2].relation_list);
      }
      RelationSqlNode relation;
      relation.relation_name = (yyvsp[-4].string);
      if((yyvsp[-3].string) != nullptr) {
      	relation.alias_name = (yyvsp[-3].string);
      	free((yyvsp[-3].string));
      }
      (yyval.sql_node)->selection.relations.push_back(relation);
      std::reverse((yyval.sql_node)->selection.relations.begin(), (yyval.sql_node)->selection.relations.end());

      if ((yyvsp[-1].condition_list) != nullptr) {
        (yyval.sql_node)->selection.conditions.swap(*(yyvsp[-1].condition_list));
        delete (yyvsp[-1].condition_list);
      }

      if((yyvsp[0].order_by_list_type) != nullptr) {
	(yyval.sql_node)->selection.order_bys.insert((yyval.sql_node)->selection.order_bys.end(),(yyvsp[0].order_by_list_type)->begin(),(yyvsp[0].order_by_list_type)->end());
	delete (yyvsp[0].order_by_list_type);
      }
      free((yyvsp[-4].string));
    }
#line 2340 "yacc_sql.cpp"
    break;

  case 66: /* select_stmt: SELECT select_attr FROM ID inner_join_constr inner_join_list where order_by_clause  */
#line 608 "yacc_sql.y"
        {
          (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
          if ((yyvsp[-6].rel_attr_list) != nullptr) {
            (yyval.sql_node)->selection.attributes.swap(*(yyvsp[-6].rel_attr_list));
            delete (yyvsp[-6].rel_attr_list);
          }
          RelationSqlNode relation_node;
          relation_node.relation_name = (yyvsp[-4].string);
          (yyval.sql_node)->selection.relations.push_back(relation_node);
          delete (yyvsp[-4].string);

          RelationSqlNode join_relation_node;
          join_relation_node.relation_name = (*(yyvsp[-3].join_list))[0].relation_name;
          (yyval.sql_node)->selection.relations.push_back(join_relation_node);
          (yyval.sql_node)->selection.conditions.swap((*(yyvsp[-3].join_list))[0].conditions);
          delete (yyvsp[-3].join_list);

          if ((yyvsp[-2].join_list) != nullptr) {
            std::reverse((yyvsp[-2].join_list)->begin(), (yyvsp[-2].join_list)->end());
	    for (auto &join_relation : *(yyvsp[-2].join_list)) {
	      RelationSqlNode join_relation_node;
              join_relation_node.relation_name = join_relation.relation_name;
	      (yyval.sql_node)->selection.relations.push_back(join_relation_node);
	      for (auto &condition : join_relation.conditions) {
	      	(yyval.sql_node)->selection.conditions.emplace_back(condition);
	      }
	    }
	    delete (yyvsp[-2].join_list);
	  }

          if ((yyvsp[-1].condition_list) != nullptr) {
            (yyval.sql_node)->selection.conditions.insert((yyval.sql_node)->selection.conditions.end(),(yyvsp[-1].condition_list)->begin(),(yyvsp[-1].condition_list)->end());
            delete (yyvsp[-1].condition_list);
          }

          if ((yyvsp[0].order_by_list_type) != nullptr) {
	    (yyval.sql_node)->selection.order_bys.insert((yyval.sql_node)->selection.order_bys.end(),(yyvsp[0].order_by_list_type)->begin(),(yyvsp[0].order_by_list_type)->end());
	    delete (yyvsp[0].order_by_list_type);
	  }
    }
#line 2385 "yacc_sql.cpp"
    break;

  case 67: /* inner_join_constr: INNER JOIN ID ON condition_list  */
#line 651 "yacc_sql.y"
    {
      (yyval.join_list) = new std::vector<JoinSqlNode>;
      JoinSqlNode join_node;
      join_node.relation_name = (yyvsp[-2].string);
      join_node.conditions.swap(*(yyvsp[0].condition_list));
      (yyval.join_list)->emplace_back(join_node);
      free((yyvsp[-2].string));
    }
#line 2398 "yacc_sql.cpp"
    break;

  case 68: /* inner_join_list: %empty  */
#line 662 "yacc_sql.y"
    {
      (yyval.join_list) = nullptr;
    }
#line 2406 "yacc_sql.cpp"
    break;

  case 69: /* inner_join_list: INNER JOIN ID ON condition_list inner_join_list  */
#line 666 "yacc_sql.y"
    {
      if ((yyvsp[0].join_list) != nullptr) {
	(yyval.join_list) = (yyvsp[0].join_list);
      } else {
	(yyval.join_list) = new std::vector<JoinSqlNode>;
      }
      JoinSqlNode join_node;
      join_node.relation_name = (yyvsp[-3].string);
      join_node.conditions.swap(*(yyvsp[-1].condition_list));
      (yyval.join_list)->emplace_back(join_node);
      free((yyvsp[-3].string));
    }
#line 2423 "yacc_sql.cpp"
    break;

  case 70: /* order_by_clause: %empty  */
#line 681 "yacc_sql.y"
    {
	(yyval.order_by_list_type) = nullptr;
    }
#line 2431 "yacc_sql.cpp"
    break;

  case 71: /* order_by_clause: ORDER BY order_by_list  */
#line 684 "yacc_sql.y"
                             {
        (yyval.order_by_list_type) = (yyvsp[0].order_by_list_type);
    }
#line 2439 "yacc_sql.cpp"
    break;

  case 72: /* order_by_list: order_by_item  */
#line 690 "yacc_sql.y"
                  {
        (yyval.order_by_list_type) = new std::vector<OrderBySqlNode>;
	(yyval.order_by_list_type)->insert((yyval.order_by_list_type)->begin(), (*(yyvsp[0].order_by_list_type)).begin(), (*(yyvsp[0].order_by_list_type)).end());
	delete (yyvsp[0].order_by_list_type);
    }
#line 2449 "yacc_sql.cpp"
    break;

  case 73: /* order_by_list: order_by_item COMMA order_by_list  */
#line 695 "yacc_sql.y"
                                        {
        if ((yyvsp[0].order_by_list_type) != nullptr) {
	    (yyval.order_by_list_type) = (yyvsp[0].order_by_list_type);
	} else {
	    (yyval.order_by_list_type) = new std::vector<OrderBySqlNode>;
	}
	(yyval.order_by_list_type)->insert((yyval.order_by_list_type)->begin(), (*(yyvsp[-2].order_by_list_type)).begin(), (*(yyvsp[-2].order_by_list_type)).end());
	delete (yyvsp[-2].order_by_list_type);
    }
#line 2463 "yacc_sql.cpp"
    break;

  case 74: /* order_by_item: rel_attr  */
#line 707 "yacc_sql.y"
             {
        (yyval.order_by_list_type) = new std::vector<OrderBySqlNode>;
        OrderBySqlNode item;
        item.order_by_attributes.emplace_back(*(yyvsp[0].rel_attr));
        item.order_by_asc.emplace_back(true);
        (yyval.order_by_list_type)->emplace_back(item);
        delete (yyvsp[0].rel_attr);
    }
#line 2476 "yacc_sql.cpp"
    break;

  case 75: /* order_by_item: rel_attr ASC  */
#line 715 "yacc_sql.y"
                   {
         	(yyval.order_by_list_type) = new std::vector<OrderBySqlNode>;
                OrderBySqlNode item;
                item.order_by_attributes.emplace_back(*(yyvsp[-1].rel_attr));
                item.order_by_asc.emplace_back(true);
                (yyval.order_by_list_type)->emplace_back(item);
                delete (yyvsp[-1].rel_attr);
    }
#line 2489 "yacc_sql.cpp"
    break;

  case 76: /* order_by_item: rel_attr DESC  */
#line 723 "yacc_sql.y"
                    {
                (yyval.order_by_list_type) = new std::vector<OrderBySqlNode>;
                OrderBySqlNode item;
                item.order_by_attributes.emplace_back(*(yyvsp[-1].rel_attr));
                item.order_by_asc.emplace_back(false);
                (yyval.order_by_list_type)->emplace_back(item);
                delete (yyvsp[-1].rel_attr);
    }
#line 2502 "yacc_sql.cpp"
    break;

  case 77: /* calc_stmt: CALC expression_list  */
#line 735 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2513 "yacc_sql.cpp"
    break;

  case 78: /* expression_list: expression  */
#line 745 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2522 "yacc_sql.cpp"
    break;

  case 79: /* expression_list: expression COMMA expression_list  */
#line 750 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2535 "yacc_sql.cpp"
    break;

  case 80: /* expression: expression '+' expression  */
#line 760 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2543 "yacc_sql.cpp"
    break;

  case 81: /* expression: expression '-' expression  */
#line 763 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2551 "yacc_sql.cpp"
    break;

  case 82: /* expression: expression '*' expression  */
#line 766 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2559 "yacc_sql.cpp"
    break;

  case 83: /* expression: expression '/' expression  */
#line 769 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2567 "yacc_sql.cpp"
    break;

  case 84: /* expression: LBRACE expression RBRACE  */
#line 772 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2576 "yacc_sql.cpp"
    break;

  case 85: /* expression: '-' expression  */
#line 776 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2584 "yacc_sql.cpp"
    break;

  case 86: /* expression: value  */
#line 779 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2594 "yacc_sql.cpp"
    break;

  case 87: /* option_as: %empty  */
#line 788 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2602 "yacc_sql.cpp"
    break;

  case 88: /* option_as: AS ID  */
#line 791 "yacc_sql.y"
            {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2610 "yacc_sql.cpp"
    break;

  case 89: /* select_attr: '*'  */
#line 796 "yacc_sql.y"
        {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.relation_name  = "";
      attr.attribute_name = "*";
      attr.aggregate_func = agg::NONE;
      (yyval.rel_attr_list)->emplace_back(attr);
    }
#line 2623 "yacc_sql.cpp"
    break;

  case 90: /* select_attr: agg LBRACE '*' RBRACE attr_list  */
#line 805 "yacc_sql.y"
                                       {
      /* AGG_FUNC(*) */
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.relation_name = "";
      attr.attribute_name = "*";
      attr.aggregate_func = (yyvsp[-4].agg);
      (yyval.rel_attr_list)->emplace_back(attr);
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        for (const auto &e : *(yyvsp[0].rel_attr_list)) {
          (yyval.rel_attr_list)->emplace_back(e);
        }
      }
      delete (yyvsp[0].rel_attr_list);
    }
#line 2643 "yacc_sql.cpp"
    break;

  case 91: /* select_attr: rel_attr COMMA agg LBRACE '*' RBRACE  */
#line 820 "yacc_sql.y"
                                           {
      /* AGG_FUNC(*) */
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.relation_name = "";
      attr.attribute_name = "*";
      attr.aggregate_func = (yyvsp[-3].agg);
      (yyval.rel_attr_list)->emplace_back(attr);
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-5].rel_attr));
    }
#line 2658 "yacc_sql.cpp"
    break;

  case 92: /* select_attr: rel_attr attr_list  */
#line 830 "yacc_sql.y"
                         {
      /* Implicity AGG in `rel_attr` */
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].rel_attr));
      delete (yyvsp[-1].rel_attr);
    }
#line 2673 "yacc_sql.cpp"
    break;

  case 93: /* select_attr: agg LBRACE rel_attr COMMA rel_attr RBRACE  */
#line 841 "yacc_sql.y"
                                                {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.agg_valid_flag = false;
      (yyval.rel_attr_list)->emplace_back(attr);
    }
#line 2684 "yacc_sql.cpp"
    break;

  case 94: /* select_attr: agg LBRACE '*' COMMA rel_attr RBRACE  */
#line 847 "yacc_sql.y"
                                           {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.agg_valid_flag = false;
      (yyval.rel_attr_list)->emplace_back(attr);
    }
#line 2695 "yacc_sql.cpp"
    break;

  case 95: /* agg: MIN  */
#line 856 "yacc_sql.y"
        {
      (yyval.agg) = agg::AGG_MIN;
    }
#line 2703 "yacc_sql.cpp"
    break;

  case 96: /* agg: MAX  */
#line 859 "yacc_sql.y"
          {
      (yyval.agg) = agg::AGG_MAX;
    }
#line 2711 "yacc_sql.cpp"
    break;

  case 97: /* agg: AVG  */
#line 862 "yacc_sql.y"
          {
      (yyval.agg) = agg::AGG_AVG;
    }
#line 2719 "yacc_sql.cpp"
    break;

  case 98: /* agg: SUM  */
#line 865 "yacc_sql.y"
          {
      (yyval.agg) = agg::AGG_SUM;
    }
#line 2727 "yacc_sql.cpp"
    break;

  case 99: /* agg: COUNT  */
#line 868 "yacc_sql.y"
            {
      (yyval.agg) = agg::AGG_COUNT;
    }
#line 2735 "yacc_sql.cpp"
    break;

  case 100: /* rel_attr: ID option_as  */
#line 874 "yacc_sql.y"
                 {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name = "";
      (yyval.rel_attr)->attribute_name = (yyvsp[-1].string);
      (yyval.rel_attr)->aggregate_func = agg::NONE;
      if((yyvsp[0].string) != nullptr) {
      	(yyval.rel_attr)->alias_name = (yyvsp[0].string);
      	free((yyvsp[0].string));
      }
      free((yyvsp[-1].string));
    }
#line 2751 "yacc_sql.cpp"
    break;

  case 101: /* rel_attr: ID DOT ID option_as  */
#line 885 "yacc_sql.y"
                          {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-3].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[-1].string);
      (yyval.rel_attr)->aggregate_func = agg::NONE;
      if((yyvsp[0].string) != nullptr) {
	(yyval.rel_attr)->alias_name = (yyvsp[0].string);
	free((yyvsp[0].string));
      }
      free((yyvsp[-3].string));
      free((yyvsp[-1].string));
    }
#line 2768 "yacc_sql.cpp"
    break;

  case 102: /* rel_attr: agg LBRACE ID RBRACE  */
#line 898 "yacc_sql.y"
                           {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name = "";
      (yyval.rel_attr)->attribute_name = (yyvsp[-1].string);
      (yyval.rel_attr)->aggregate_func = (yyvsp[-3].agg);
      free((yyvsp[-1].string));
    }
#line 2780 "yacc_sql.cpp"
    break;

  case 103: /* rel_attr: agg LBRACE ID DOT ID RBRACE  */
#line 905 "yacc_sql.y"
                                  {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name = (yyvsp[-3].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[-1].string);
      (yyval.rel_attr)->aggregate_func = (yyvsp[-5].agg);
      free((yyvsp[-3].string));
      free((yyvsp[-1].string));
    }
#line 2793 "yacc_sql.cpp"
    break;

  case 104: /* rel_attr: agg LBRACE RBRACE  */
#line 915 "yacc_sql.y"
                        {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->agg_valid_flag = false;
    }
#line 2802 "yacc_sql.cpp"
    break;

  case 105: /* attr_list: %empty  */
#line 923 "yacc_sql.y"
    {
      (yyval.rel_attr_list) = nullptr;
    }
#line 2810 "yacc_sql.cpp"
    break;

  case 106: /* attr_list: COMMA rel_attr attr_list  */
#line 926 "yacc_sql.y"
                               {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }

      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].rel_attr));
      delete (yyvsp[-1].rel_attr);
    }
#line 2825 "yacc_sql.cpp"
    break;

  case 107: /* rel_list: %empty  */
#line 940 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 2833 "yacc_sql.cpp"
    break;

  case 108: /* rel_list: COMMA ID option_as rel_list  */
#line 943 "yacc_sql.y"
                                  {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<RelationSqlNode>;
      }
      RelationSqlNode relation;
      relation.relation_name = (yyvsp[-2].string);
      if((yyvsp[-1].string) != nullptr) {
      	relation.alias_name = (yyvsp[-1].string);
      		free((yyvsp[-1].string));
      }
      (yyval.relation_list)->push_back(relation);
      free((yyvsp[-2].string));
    }
#line 2853 "yacc_sql.cpp"
    break;

  case 109: /* where: %empty  */
#line 961 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2861 "yacc_sql.cpp"
    break;

  case 110: /* where: WHERE condition_list  */
#line 964 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 2869 "yacc_sql.cpp"
    break;

  case 111: /* condition_list: %empty  */
#line 970 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2877 "yacc_sql.cpp"
    break;

  case 112: /* condition_list: condition  */
#line 973 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 2887 "yacc_sql.cpp"
    break;

  case 113: /* condition_list: condition AND condition_list  */
#line 978 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 2897 "yacc_sql.cpp"
    break;

  case 114: /* condition: rel_attr comp_op value  */
#line 986 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].rel_attr);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_value = *(yyvsp[0].value);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].rel_attr);
      delete (yyvsp[0].value);
    }
#line 2913 "yacc_sql.cpp"
    break;

  case 115: /* condition: value comp_op value  */
#line 998 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_value = *(yyvsp[-2].value);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_value = *(yyvsp[0].value);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].value);
      delete (yyvsp[0].value);
    }
#line 2929 "yacc_sql.cpp"
    break;

  case 116: /* condition: rel_attr comp_op rel_attr  */
#line 1010 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].rel_attr);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].rel_attr);
      delete (yyvsp[0].rel_attr);
    }
#line 2945 "yacc_sql.cpp"
    break;

  case 117: /* condition: value comp_op rel_attr  */
#line 1022 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_value = *(yyvsp[-2].value);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].value);
      delete (yyvsp[0].rel_attr);
    }
#line 2961 "yacc_sql.cpp"
    break;

  case 118: /* condition: rel_attr in_op LBRACE select_stmt RBRACE  */
#line 1034 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-4].rel_attr);
      (yyval.condition)->right_is_attr = 2;
      (yyval.condition)->right_sub_select = new SelectSqlNode((yyvsp[-1].sql_node)->selection);
      (yyval.condition)->comp = (yyvsp[-3].comp);
      delete (yyvsp[-4].rel_attr);
    }
#line 2975 "yacc_sql.cpp"
    break;

  case 119: /* condition: rel_attr in_op LBRACE value value_list RBRACE  */
#line 1044 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-5].rel_attr);
      (yyval.condition)->right_is_attr = 3;
      if((yyvsp[-1].value_list) != nullptr) {
	(yyval.condition)->right_value_list.swap(*(yyvsp[-1].value_list));
	delete (yyvsp[-1].value_list);
      }
      (yyval.condition)->right_value_list.push_back(*(yyvsp[-2].value));
      (yyval.condition)->comp = (yyvsp[-4].comp);
      delete (yyvsp[-5].rel_attr);
      delete (yyvsp[-2].value);
    }
#line 2994 "yacc_sql.cpp"
    break;

  case 120: /* condition: rel_attr comp_op LBRACE select_stmt RBRACE  */
#line 1059 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-4].rel_attr);
      (yyval.condition)->right_is_attr = 2;
      (yyval.condition)->right_sub_select = new SelectSqlNode((yyvsp[-1].sql_node)->selection);
      (yyval.condition)->comp = (yyvsp[-3].comp);
      delete (yyvsp[-4].rel_attr);
    }
#line 3008 "yacc_sql.cpp"
    break;

  case 121: /* condition: rel_attr comp_op LBRACE value value_list RBRACE  */
#line 1069 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-5].rel_attr);
      (yyval.condition)->right_is_attr = 3;
      if((yyvsp[-1].value_list) != nullptr) {
      	(yyval.condition)->right_value_list.swap(*(yyvsp[-1].value_list));
      	delete (yyvsp[-1].value_list);
      }
      (yyval.condition)->right_value_list.push_back(*(yyvsp[-2].value));
      (yyval.condition)->comp = (yyvsp[-4].comp);
      delete (yyvsp[-5].rel_attr);
      delete (yyvsp[-2].value);
      }
#line 3027 "yacc_sql.cpp"
    break;

  case 122: /* condition: LBRACE select_stmt RBRACE comp_op rel_attr  */
#line 1084 "yacc_sql.y"
      {
	(yyval.condition) = new ConditionSqlNode;
	(yyval.condition)->left_is_attr = 2;
	(yyval.condition)->left_sub_select = new SelectSqlNode((yyvsp[-3].sql_node)->selection);
	(yyval.condition)->right_is_attr = 1;
	(yyval.condition)->right_attr = *(yyvsp[0].rel_attr);
	(yyval.condition)->comp = (yyvsp[-1].comp);
	delete (yyvsp[0].rel_attr);
      }
#line 3041 "yacc_sql.cpp"
    break;

  case 123: /* in_op: IN  */
#line 1095 "yacc_sql.y"
       { (yyval.comp) = IN_OP; }
#line 3047 "yacc_sql.cpp"
    break;

  case 124: /* in_op: NOT IN  */
#line 1096 "yacc_sql.y"
             { (yyval.comp) = NOT_IN; }
#line 3053 "yacc_sql.cpp"
    break;

  case 125: /* in_op: EXISTS  */
#line 1097 "yacc_sql.y"
             { (yyval.comp) = EXISTS_OP; }
#line 3059 "yacc_sql.cpp"
    break;

  case 126: /* in_op: NOT EXISTS  */
#line 1098 "yacc_sql.y"
                 { (yyval.comp) = NOT_EXISTS; }
#line 3065 "yacc_sql.cpp"
    break;

  case 127: /* comp_op: EQ  */
#line 1102 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3071 "yacc_sql.cpp"
    break;

  case 128: /* comp_op: LT  */
#line 1103 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3077 "yacc_sql.cpp"
    break;

  case 129: /* comp_op: GT  */
#line 1104 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3083 "yacc_sql.cpp"
    break;

  case 130: /* comp_op: LE  */
#line 1105 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3089 "yacc_sql.cpp"
    break;

  case 131: /* comp_op: GE  */
#line 1106 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3095 "yacc_sql.cpp"
    break;

  case 132: /* comp_op: NE  */
#line 1107 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3101 "yacc_sql.cpp"
    break;

  case 133: /* comp_op: LIKE  */
#line 1108 "yacc_sql.y"
           { (yyval.comp) = LIKE_OP;}
#line 3107 "yacc_sql.cpp"
    break;

  case 134: /* comp_op: NOT LIKE  */
#line 1109 "yacc_sql.y"
               { (yyval.comp) = NOT_LIKE_OP;}
#line 3113 "yacc_sql.cpp"
    break;

  case 135: /* comp_op: NULL_IS  */
#line 1110 "yacc_sql.y"
              { (yyval.comp) = IS; }
#line 3119 "yacc_sql.cpp"
    break;

  case 136: /* comp_op: NULL_IS NOT  */
#line 1111 "yacc_sql.y"
                  { (yyval.comp) = IS_NOT; }
#line 3125 "yacc_sql.cpp"
    break;

  case 137: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1116 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3139 "yacc_sql.cpp"
    break;

  case 138: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1129 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3148 "yacc_sql.cpp"
    break;

  case 139: /* set_variable_stmt: SET ID EQ value  */
#line 1137 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3160 "yacc_sql.cpp"
    break;


#line 3164 "yacc_sql.cpp"

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
  *++yylsp = yyloc;

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
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (&yylloc, sql_string, sql_result, scanner, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

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
  yyerror (&yylloc, sql_string, sql_result, scanner, YY_("memory exhausted"));
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
                  yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 1149 "yacc_sql.y"

//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, ParsedSqlResult *sql_result) {
  yyscan_t scanner;
  yylex_init(&scanner);
  scan_string(s, scanner);
  int result = yyparse(s, sql_result, scanner);
  yylex_destroy(scanner);
  return result;
}
