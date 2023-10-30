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
#define YYPURE 1

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
  YYSYMBOL_GROUP = 64,                     /* GROUP  */
  YYSYMBOL_HAVING = 65,                    /* HAVING  */
  YYSYMBOL_IN = 66,                        /* IN  */
  YYSYMBOL_EXISTS = 67,                    /* EXISTS  */
  YYSYMBOL_OR = 68,                        /* OR  */
  YYSYMBOL_NUMBER = 69,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 70,                     /* FLOAT  */
  YYSYMBOL_ID = 71,                        /* ID  */
  YYSYMBOL_SSS = 72,                       /* SSS  */
  YYSYMBOL_DATE_STR = 73,                  /* DATE_STR  */
  YYSYMBOL_ID_MINUS = 74,                  /* ID_MINUS  */
  YYSYMBOL_MIN_MINUS = 75,                 /* MIN_MINUS  */
  YYSYMBOL_MAX_MINUS = 76,                 /* MAX_MINUS  */
  YYSYMBOL_AVG_MINUS = 77,                 /* AVG_MINUS  */
  YYSYMBOL_SUM_MINUS = 78,                 /* SUM_MINUS  */
  YYSYMBOL_COUNT_MINUS = 79,               /* COUNT_MINUS  */
  YYSYMBOL_80_ = 80,                       /* '+'  */
  YYSYMBOL_81_ = 81,                       /* '-'  */
  YYSYMBOL_82_ = 82,                       /* '*'  */
  YYSYMBOL_83_ = 83,                       /* '/'  */
  YYSYMBOL_UMINUS = 84,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 85,                  /* $accept  */
  YYSYMBOL_commands = 86,                  /* commands  */
  YYSYMBOL_command_wrapper = 87,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 88,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 89,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 90,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 91,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 92,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 93,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 94,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 95,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 96,           /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 97,         /* create_index_stmt  */
  YYSYMBOL_attr_name_list = 98,            /* attr_name_list  */
  YYSYMBOL_index_attr = 99,                /* index_attr  */
  YYSYMBOL_index_attr_name_list = 100,     /* index_attr_name_list  */
  YYSYMBOL_drop_index_stmt = 101,          /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 102,        /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 103,            /* attr_def_list  */
  YYSYMBOL_attr_def = 104,                 /* attr_def  */
  YYSYMBOL_null = 105,                     /* null  */
  YYSYMBOL_number = 106,                   /* number  */
  YYSYMBOL_type = 107,                     /* type  */
  YYSYMBOL_insert_stmt = 108,              /* insert_stmt  */
  YYSYMBOL_value_list = 109,               /* value_list  */
  YYSYMBOL_value = 110,                    /* value  */
  YYSYMBOL_delete_stmt = 111,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 112,              /* update_stmt  */
  YYSYMBOL_update_value_list = 113,        /* update_value_list  */
  YYSYMBOL_select_stmt = 114,              /* select_stmt  */
  YYSYMBOL_inner_join_constr = 115,        /* inner_join_constr  */
  YYSYMBOL_inner_join_list = 116,          /* inner_join_list  */
  YYSYMBOL_group_by_clause = 117,          /* group_by_clause  */
  YYSYMBOL_group_by_list = 118,            /* group_by_list  */
  YYSYMBOL_having = 119,                   /* having  */
  YYSYMBOL_order_by_clause = 120,          /* order_by_clause  */
  YYSYMBOL_order_by_list = 121,            /* order_by_list  */
  YYSYMBOL_order_by_item = 122,            /* order_by_item  */
  YYSYMBOL_calc_stmt = 123,                /* calc_stmt  */
  YYSYMBOL_expression_list = 124,          /* expression_list  */
  YYSYMBOL_expression = 125,               /* expression  */
  YYSYMBOL_option_as = 126,                /* option_as  */
  YYSYMBOL_select_attr = 127,              /* select_attr  */
  YYSYMBOL_agg = 128,                      /* agg  */
  YYSYMBOL_rel_attr = 129,                 /* rel_attr  */
  YYSYMBOL_rel_list = 130,                 /* rel_list  */
  YYSYMBOL_where = 131,                    /* where  */
  YYSYMBOL_condition_list = 132,           /* condition_list  */
  YYSYMBOL_condition = 133,                /* condition  */
  YYSYMBOL_in_op = 134,                    /* in_op  */
  YYSYMBOL_comp_op = 135,                  /* comp_op  */
  YYSYMBOL_load_data_stmt = 136,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 137,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 138,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 139             /* opt_semicolon  */
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
#define YYFINAL  82
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   435

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  85
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  55
/* YYNRULES -- Number of rules.  */
#define YYNRULES  154
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  310

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   335


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
       2,     2,    82,    80,     2,    81,     2,    83,     2,     2,
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
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    84
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   234,   234,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   265,   271,   276,   282,   288,   294,   300,
     307,   313,   321,   334,   348,   359,   367,   370,   383,   393,
     412,   415,   429,   442,   461,   464,   467,   474,   478,   479,
     480,   481,   482,   485,   501,   504,   515,   519,   523,   529,
     535,   543,   555,   582,   585,   603,   608,   623,   674,   718,
     730,   733,   749,   752,   759,   767,   785,   788,   795,   798,
     804,   809,   821,   829,   837,   848,   858,   863,   875,   878,
     881,   884,   887,   891,   894,   899,   907,   922,   936,   950,
     964,   978,   996,   999,  1002,  1008,  1021,  1037,  1043,  1052,
    1055,  1058,  1061,  1064,  1070,  1081,  1093,  1101,  1113,  1125,
    1140,  1148,  1151,  1169,  1172,  1179,  1182,  1187,  1193,  1202,
    1316,  1329,  1347,  1360,  1379,  1389,  1401,  1402,  1403,  1404,
    1408,  1409,  1410,  1411,  1412,  1413,  1414,  1415,  1416,  1417,
    1421,  1434,  1442,  1452,  1453
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
  "ORDER", "BY", "ASC", "AS", "GROUP", "HAVING", "IN", "EXISTS", "OR",
  "NUMBER", "FLOAT", "ID", "SSS", "DATE_STR", "ID_MINUS", "MIN_MINUS",
  "MAX_MINUS", "AVG_MINUS", "SUM_MINUS", "COUNT_MINUS", "'+'", "'-'",
  "'*'", "'/'", "UMINUS", "$accept", "commands", "command_wrapper",
  "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt", "commit_stmt",
  "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "desc_table_stmt", "create_index_stmt", "attr_name_list", "index_attr",
  "index_attr_name_list", "drop_index_stmt", "create_table_stmt",
  "attr_def_list", "attr_def", "null", "number", "type", "insert_stmt",
  "value_list", "value", "delete_stmt", "update_stmt", "update_value_list",
  "select_stmt", "inner_join_constr", "inner_join_list", "group_by_clause",
  "group_by_list", "having", "order_by_clause", "order_by_list",
  "order_by_item", "calc_stmt", "expression_list", "expression",
  "option_as", "select_attr", "agg", "rel_attr", "rel_list", "where",
  "condition_list", "condition", "in_op", "comp_op", "load_data_stmt",
  "explain_stmt", "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-191)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     393,    27,    38,   211,   179,   -48,    30,  -191,    53,    25,
      34,  -191,  -191,  -191,  -191,  -191,    37,    58,   393,   112,
     115,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
    -191,    44,    52,   127,    62,    70,   211,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,  -191,   -15,  -191,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,   211,  -191,  -191,    21,   145,  -191,
     -22,  -191,   118,   159,  -191,  -191,   106,   107,   144,   139,
     143,  -191,  -191,  -191,  -191,    22,   147,   132,  -191,   162,
     -13,   -46,   133,  -191,  -191,  -191,   211,   211,   211,   211,
     211,     0,  -191,   135,    35,   186,   187,   149,   129,   150,
     152,   103,   153,   189,   154,  -191,   -22,  -191,  -191,  -191,
      49,    49,  -191,  -191,  -191,    -1,   217,   -37,    -6,   146,
     210,   219,   242,  -191,   194,  -191,   208,   134,   221,   235,
    -191,   225,   172,  -191,  -191,   -22,   173,   -22,   188,   190,
     228,   -44,    85,    85,   129,   138,   313,  -191,   -14,   129,
     261,  -191,  -191,  -191,  -191,  -191,    75,   152,   250,   198,
     200,   255,  -191,   256,  -191,   202,   218,   187,   205,   187,
      48,   259,   260,   279,   281,  -191,  -191,  -191,  -191,  -191,
    -191,   -36,  -191,   230,  -191,  -191,   283,   274,   242,   242,
     284,   231,   236,   245,  -191,  -191,   221,   103,    28,  -191,
     288,   289,   200,   -22,   269,   238,   262,   -22,   262,  -191,
    -191,   129,   292,   125,  -191,  -191,  -191,  -191,     3,   138,
      45,  -191,  -191,   253,   187,  -191,  -191,   312,  -191,  -191,
    -191,   152,  -191,   200,  -191,   314,  -191,   242,   293,   273,
    -191,   228,   271,   279,  -191,   286,    92,   279,   319,   320,
     322,   295,  -191,   -17,   221,   289,  -191,  -191,   242,    85,
    -191,   280,   277,  -191,   103,  -191,   336,  -191,   129,  -191,
     129,  -191,   346,  -191,   190,  -191,   347,    17,    85,   242,
    -191,   349,  -191,   279,   284,   103,  -191,    85,  -191,  -191,
    -191,   350,  -191,  -191,   352,  -191,  -191,    85,  -191,  -191
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    25,     0,     0,
       0,    26,    27,    28,    24,    23,     0,     0,     0,     0,
     153,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,     4,     3,    18,    19,
      20,     0,     0,     0,     0,     0,     0,   109,   110,   111,
     112,   113,    60,    56,    57,   102,    58,    59,    96,    97,
      98,   100,    99,   101,     0,    94,    85,    86,     0,    95,
     102,   106,     0,     0,    31,    30,     0,     0,     0,     0,
       0,   151,     1,   154,     2,     0,     0,     0,    29,     0,
       0,     0,     0,   104,   114,    93,     0,     0,     0,     0,
       0,     0,   105,     0,     0,     0,   123,     0,     0,     0,
       0,     0,     0,     0,     0,    92,   102,   116,   103,    87,
      88,    89,    90,    91,   120,     0,     0,   102,   102,     0,
       0,     0,   125,    61,     0,   152,     0,     0,    40,     0,
      65,     0,     0,    38,   115,   102,     0,   102,     0,    70,
     121,     0,     0,     0,     0,     0,     0,   124,   126,     0,
       0,    48,    50,    49,    51,    52,    44,     0,     0,     0,
       0,     0,   117,     0,   119,     0,     0,   123,     0,   123,
     102,     0,     0,    54,     0,   140,   141,   142,   143,   144,
     145,     0,   146,   148,   136,   138,     0,     0,   125,   125,
      63,     0,     0,     0,    45,    43,    40,    39,     0,    35,
       0,    36,     0,   102,     0,     0,    78,   102,    78,   108,
     107,     0,     0,     0,   147,   137,   139,   149,     0,     0,
     129,   127,   128,     0,   123,   150,    47,     0,    46,    41,
      66,     0,    32,     0,    34,     0,   118,   125,     0,     0,
      68,   121,    72,    54,    53,     0,     0,    54,     0,    94,
       0,     0,    62,    44,    40,    36,    33,    69,   125,     0,
     122,     0,    76,    55,     0,   134,     0,   130,     0,   132,
       0,    42,     0,    37,    70,    79,    80,    82,     0,     0,
      67,     0,   131,    54,    63,     0,    71,     0,    84,    83,
      73,    74,    77,   135,     0,    64,    81,     0,   133,    75
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -191,  -191,   354,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
    -191,  -191,  -191,   156,   122,   108,  -191,  -191,  -190,  -163,
     111,  -191,  -191,  -191,  -143,   -99,  -191,  -191,    81,  -108,
    -191,    93,  -191,    69,  -191,   160,    84,  -191,  -191,     4,
      -3,   -64,  -191,   378,  -102,   136,  -157,  -188,    94,  -191,
     161,  -191,  -191,  -191,  -191
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,   210,   211,   244,    31,    32,   168,   138,
     205,   237,   166,    33,   222,    65,    34,    35,   234,    36,
     149,   177,   272,   300,   290,   250,   285,   286,    37,    66,
     156,    94,    72,    68,    69,   179,   133,   157,   158,   196,
     197,    38,    39,    40,    84
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      67,    67,   130,   140,   206,   115,   102,   139,    71,   135,
     231,   232,   145,     4,   224,    91,   239,   145,   124,   148,
     216,   198,   218,    74,   151,   116,    92,   180,   298,   146,
     225,   226,   203,    41,    93,    42,   117,    75,   117,   110,
      96,    92,   204,    90,    44,   241,    45,   184,    92,    93,
     181,   182,   144,   124,   199,   183,    93,    92,    77,   267,
     200,    95,    52,   150,    43,    93,   213,    97,    98,    99,
     100,   125,    53,    54,   282,    56,    57,   262,   264,   299,
     284,   172,   126,   174,    76,   111,    47,    48,    49,    50,
      51,   111,   202,    67,   120,   121,   122,   123,    80,   240,
     119,    97,    98,    99,   100,    78,   128,   139,    79,   274,
     273,    92,    82,     4,   276,    85,   144,   129,    83,    93,
     258,   260,   253,    86,   203,    97,    98,    99,   100,   257,
     259,    99,   100,    88,   204,    87,    47,    48,    49,    50,
      51,    89,   139,    47,    48,    49,    50,    51,     4,   246,
     304,   103,    90,   251,   275,    46,    55,   161,   162,   163,
     164,   165,   101,    55,   147,   152,   291,   287,   185,   186,
     187,   188,   189,   190,   255,   192,   104,   105,   106,   293,
     107,   294,   108,   193,   109,   112,   301,   240,    52,    47,
      48,    49,    50,    51,   230,   287,    46,    52,    53,    54,
     114,    56,    57,   113,   118,   301,   127,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,   131,    64,
     134,   132,   136,   137,   141,   143,    90,   142,    46,   153,
      47,    48,    49,    50,    51,   147,   154,   159,    52,   160,
     167,   169,   170,   171,   173,   175,   176,   178,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,   155,
      64,    70,    47,    48,    49,    50,    51,   201,   207,   208,
      52,   209,   212,   214,   213,   215,   217,   219,   220,   227,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,   229,    64,    47,    48,    49,    50,    51,   221,   223,
     228,    52,   235,   233,   238,   236,   242,   247,   243,   248,
     254,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,   249,    64,   261,    47,    48,    49,    50,    51,
     263,   268,   266,    52,   269,   271,   224,   277,   280,   278,
     279,   288,   289,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,   292,    64,   185,   186,   187,   188,
     189,   190,   191,   192,   295,   265,   297,   303,   245,   307,
     308,   193,    81,   283,   281,   305,   309,   296,   252,   194,
     195,   306,    73,   302,   256,     0,     0,   270,     0,     0,
       0,     0,     0,    97,    98,    99,   100,     1,     2,     0,
       0,     0,     3,     4,     5,     6,     7,     8,     9,    10,
       0,     0,     0,    11,    12,    13,     0,     0,     0,     0,
       0,    14,    15,     0,     0,     0,     0,     0,     0,    16,
       0,     0,    17,     0,     0,    18
};

static const yytype_int16 yycheck[] =
{
       3,     4,   104,   111,   167,    18,    70,     4,     4,   108,
     198,   199,    18,    10,    50,    30,   206,    18,    18,    56,
     177,    35,   179,    71,    30,    71,    63,    71,    11,    30,
      66,    67,    49,     6,    71,     8,    82,     7,    82,    17,
      19,    63,    59,    46,     6,    17,     8,   155,    63,    71,
     152,   153,   116,    18,    68,   154,    71,    63,    33,   247,
     159,    64,    59,   127,    37,    71,    18,    80,    81,    82,
      83,    71,    69,    70,   264,    72,    73,   234,   241,    62,
     268,   145,    82,   147,    31,    63,    51,    52,    53,    54,
      55,    63,    17,    96,    97,    98,    99,   100,    40,   207,
      96,    80,    81,    82,    83,    71,    71,     4,    71,    17,
     253,    63,     0,    10,   257,    71,   180,    82,     3,    71,
     228,   229,   221,    71,    49,    80,    81,    82,    83,   228,
     229,    82,    83,    71,    59,     8,    51,    52,    53,    54,
      55,    71,     4,    51,    52,    53,    54,    55,    10,   213,
     293,    33,   155,   217,   256,    17,    71,    23,    24,    25,
      26,    27,    17,    71,    18,    19,   274,   269,    43,    44,
      45,    46,    47,    48,    49,    50,    17,    71,    71,   278,
      36,   280,    43,    58,    41,    38,   288,   295,    59,    51,
      52,    53,    54,    55,   197,   297,    17,    59,    69,    70,
      38,    72,    73,    71,    71,   307,    71,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    32,    81,
      71,    34,    72,    71,    71,    71,   229,    38,    17,    19,
      51,    52,    53,    54,    55,    18,    17,    43,    59,    31,
      19,     6,    17,    71,    71,    57,    56,    19,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    17,
      81,    82,    51,    52,    53,    54,    55,     6,    18,    71,
      59,    71,    17,    71,    18,    57,    71,    18,    18,    49,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    17,    81,    51,    52,    53,    54,    55,    19,    18,
      17,    59,    71,    19,    59,    69,    18,    38,    19,    71,
      18,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    60,    81,    71,    51,    52,    53,    54,    55,
      18,    38,    18,    59,    61,    64,    50,    18,    43,    19,
      18,    61,    65,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    18,    81,    43,    44,    45,    46,
      47,    48,    49,    50,    18,   243,    19,    18,   212,    19,
      18,    58,    18,   265,   263,   294,   307,   284,   218,    66,
      67,   297,     4,   289,   223,    -1,    -1,   251,    -1,    -1,
      -1,    -1,    -1,    80,    81,    82,    83,     4,     5,    -1,
      -1,    -1,     9,    10,    11,    12,    13,    14,    15,    16,
      -1,    -1,    -1,    20,    21,    22,    -1,    -1,    -1,    -1,
      -1,    28,    29,    -1,    -1,    -1,    -1,    -1,    -1,    36,
      -1,    -1,    39,    -1,    -1,    42
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,     9,    10,    11,    12,    13,    14,    15,
      16,    20,    21,    22,    28,    29,    36,    39,    42,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,   101,   102,   108,   111,   112,   114,   123,   136,   137,
     138,     6,     8,    37,     6,     8,    17,    51,    52,    53,
      54,    55,    59,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    81,   110,   124,   125,   128,   129,
      82,   124,   127,   128,    71,     7,    31,    33,    71,    71,
      40,    87,     0,     3,   139,    71,    71,     8,    71,    71,
     125,    30,    63,    71,   126,   125,    19,    80,    81,    82,
      83,    17,   126,    33,    17,    71,    71,    36,    43,    41,
      17,    63,    38,    71,    38,    18,    71,    82,    71,   124,
     125,   125,   125,   125,    18,    71,    82,    71,    71,    82,
     129,    32,    34,   131,    71,   110,    72,    71,   104,     4,
     114,    71,    38,    71,   126,    18,    30,    18,    56,   115,
     126,    30,    19,    19,    17,    17,   125,   132,   133,    43,
      31,    23,    24,    25,    26,    27,   107,    19,   103,     6,
      17,    71,   126,    71,   126,    57,    56,   116,    19,   130,
      71,   129,   129,   110,   114,    43,    44,    45,    46,    47,
      48,    49,    50,    58,    66,    67,   134,   135,    35,    68,
     110,     6,    17,    49,    59,   105,   104,    18,    71,    71,
      98,    99,    17,    18,    71,    57,   131,    71,   131,    18,
      18,    19,   109,    18,    50,    66,    67,    49,    17,    17,
     125,   132,   132,    19,   113,    71,    69,   106,    59,   103,
     114,    17,    18,    19,   100,    98,   126,    38,    71,    60,
     120,   126,   120,   110,    18,    49,   135,   110,   114,   110,
     114,    71,   131,    18,   104,    99,    18,   132,    38,    61,
     130,    64,   117,   109,    17,   129,   109,    18,    19,    18,
      43,   105,   103,   100,   132,   121,   122,   129,    61,    65,
     119,   114,    18,   110,   110,    18,   116,    19,    11,    62,
     118,   129,   133,    18,   109,   113,   121,    19,    18,   118
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    85,    86,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    97,    98,    99,   100,   100,   101,   102,
     103,   103,   104,   104,   105,   105,   105,   106,   107,   107,
     107,   107,   107,   108,   109,   109,   110,   110,   110,   110,
     110,   111,   112,   113,   113,   114,   114,   114,   114,   115,
     116,   116,   117,   117,   118,   118,   119,   119,   120,   120,
     121,   121,   122,   122,   122,   123,   124,   124,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   126,   126,   126,   127,   127,   127,   127,   128,
     128,   128,   128,   128,   129,   129,   129,   129,   129,   129,
     129,   130,   130,   131,   131,   132,   132,   132,   132,   133,
     133,   133,   133,   133,   133,   133,   134,   134,   134,   134,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     136,   137,   138,   139,   139
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
       1,     4,     8,     0,     5,     5,     8,    10,     8,     5,
       0,     6,     0,     3,     1,     3,     0,     2,     0,     3,
       1,     3,     1,     2,     2,     2,     1,     3,     3,     3,
       3,     3,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     2,     1,     2,     1,     6,     6,     1,
       1,     1,     1,     1,     2,     4,     3,     5,     7,     5,
       3,     0,     4,     0,     2,     0,     1,     3,     3,     3,
       5,     6,     5,     8,     5,     7,     1,     2,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     2,
       7,     2,     4,     0,     1
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
#line 235 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1893 "yacc_sql.cpp"
    break;

  case 23: /* exit_stmt: EXIT  */
#line 265 "yacc_sql.y"
         {
      (void) yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1902 "yacc_sql.cpp"
    break;

  case 24: /* help_stmt: HELP  */
#line 271 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1910 "yacc_sql.cpp"
    break;

  case 25: /* sync_stmt: SYNC  */
#line 276 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1918 "yacc_sql.cpp"
    break;

  case 26: /* begin_stmt: TRX_BEGIN  */
#line 282 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1926 "yacc_sql.cpp"
    break;

  case 27: /* commit_stmt: TRX_COMMIT  */
#line 288 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1934 "yacc_sql.cpp"
    break;

  case 28: /* rollback_stmt: TRX_ROLLBACK  */
#line 294 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1942 "yacc_sql.cpp"
    break;

  case 29: /* drop_table_stmt: DROP TABLE ID  */
#line 300 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1952 "yacc_sql.cpp"
    break;

  case 30: /* show_tables_stmt: SHOW TABLES  */
#line 307 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1960 "yacc_sql.cpp"
    break;

  case 31: /* desc_table_stmt: DESC ID  */
#line 313 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1970 "yacc_sql.cpp"
    break;

  case 32: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE attr_name_list RBRACE  */
#line 322 "yacc_sql.y"
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
#line 1986 "yacc_sql.cpp"
    break;

  case 33: /* create_index_stmt: CREATE UNIQUE INDEX ID ON ID LBRACE attr_name_list RBRACE  */
#line 335 "yacc_sql.y"
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
#line 2002 "yacc_sql.cpp"
    break;

  case 34: /* attr_name_list: index_attr index_attr_name_list  */
#line 348 "yacc_sql.y"
                                    {
      if((yyvsp[0].index_attr_name_list) != nullptr) {
        (yyval.attr_name_list) = (yyvsp[0].index_attr_name_list);
      } else {
        (yyval.attr_name_list) = new std::vector<IndexAttr>;
      }
      (yyval.attr_name_list)->push_back(*(yyvsp[-1].index_attr));
      delete (yyvsp[-1].index_attr);
    }
#line 2016 "yacc_sql.cpp"
    break;

  case 35: /* index_attr: ID  */
#line 359 "yacc_sql.y"
     {
    (yyval.index_attr) = new IndexAttr;
    (yyval.index_attr)->attribute_name = (yyvsp[0].string);
    free((yyvsp[0].string));
  }
#line 2026 "yacc_sql.cpp"
    break;

  case 36: /* index_attr_name_list: %empty  */
#line 367 "yacc_sql.y"
    {
      (yyval.index_attr_name_list) = nullptr;
    }
#line 2034 "yacc_sql.cpp"
    break;

  case 37: /* index_attr_name_list: COMMA index_attr index_attr_name_list  */
#line 370 "yacc_sql.y"
                                            {
      if ((yyvsp[0].index_attr_name_list) != nullptr) {
        (yyval.index_attr_name_list) = (yyvsp[0].index_attr_name_list);
      } else {
        (yyval.index_attr_name_list) = new std::vector<IndexAttr>;
      }

      (yyval.index_attr_name_list)->emplace_back(*(yyvsp[-1].index_attr));
      delete (yyvsp[-1].index_attr);
    }
#line 2049 "yacc_sql.cpp"
    break;

  case 38: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 384 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2061 "yacc_sql.cpp"
    break;

  case 39: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE  */
#line 394 "yacc_sql.y"
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
#line 2081 "yacc_sql.cpp"
    break;

  case 40: /* attr_def_list: %empty  */
#line 412 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2089 "yacc_sql.cpp"
    break;

  case 41: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 416 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2103 "yacc_sql.cpp"
    break;

  case 42: /* attr_def: ID type LBRACE number RBRACE null  */
#line 429 "yacc_sql.y"
                                      {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      assert((yyvsp[-4].number) == CHARS && "Expect char(number)");
      if ((yyvsp[0].null)) {
        (yyval.attr_info)->length = (yyvsp[-2].number) + 10;
      } else {
        (yyval.attr_info)->length = (yyvsp[-2].number);
      }
      (yyval.attr_info)->is_null = (yyvsp[0].null);
      free((yyvsp[-5].string));
    }
#line 2121 "yacc_sql.cpp"
    break;

  case 43: /* attr_def: ID type null  */
#line 442 "yacc_sql.y"
                   {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType) (yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      if ((yyvsp[-1].number) == CHARS && (yyvsp[0].null)) {
        (yyval.attr_info)->length = 10;
      } else {
        (yyval.attr_info)->length = 4;
      }
      if((yyval.attr_info)->type == AttrType::TEXT) {
        (yyval.attr_info)->length = 65535; // need to change
      }
      (yyval.attr_info)->is_null = (yyvsp[0].null);
      free((yyvsp[-2].string));
    }
#line 2141 "yacc_sql.cpp"
    break;

  case 44: /* null: %empty  */
#line 461 "yacc_sql.y"
  {
    (yyval.null) = false;
  }
#line 2149 "yacc_sql.cpp"
    break;

  case 45: /* null: OB_NULL  */
#line 464 "yacc_sql.y"
            {
    (yyval.null) = true;
  }
#line 2157 "yacc_sql.cpp"
    break;

  case 46: /* null: NOT OB_NULL  */
#line 467 "yacc_sql.y"
                {
    // Note that we do NOT need to deal with `NOT NULL` here
    // Since this property will be enable if NULL is not explicitly declared
    (yyval.null) = false;
  }
#line 2167 "yacc_sql.cpp"
    break;

  case 47: /* number: NUMBER  */
#line 474 "yacc_sql.y"
           { (yyval.number) = (yyvsp[0].number); }
#line 2173 "yacc_sql.cpp"
    break;

  case 48: /* type: INT_T  */
#line 478 "yacc_sql.y"
               { (yyval.number) = INTS; }
#line 2179 "yacc_sql.cpp"
    break;

  case 49: /* type: TEXT_T  */
#line 479 "yacc_sql.y"
                 { (yyval.number) = TEXT; }
#line 2185 "yacc_sql.cpp"
    break;

  case 50: /* type: STRING_T  */
#line 480 "yacc_sql.y"
               { (yyval.number) = CHARS; }
#line 2191 "yacc_sql.cpp"
    break;

  case 51: /* type: FLOAT_T  */
#line 481 "yacc_sql.y"
               { (yyval.number) = FLOATS; }
#line 2197 "yacc_sql.cpp"
    break;

  case 52: /* type: DATE_T  */
#line 482 "yacc_sql.y"
               { (yyval.number) = DATE; }
#line 2203 "yacc_sql.cpp"
    break;

  case 53: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 486 "yacc_sql.y"
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
#line 2219 "yacc_sql.cpp"
    break;

  case 54: /* value_list: %empty  */
#line 501 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2227 "yacc_sql.cpp"
    break;

  case 55: /* value_list: COMMA value value_list  */
#line 504 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2241 "yacc_sql.cpp"
    break;

  case 56: /* value: NUMBER  */
#line 515 "yacc_sql.y"
           {
      (yyval.value) = new Value(static_cast<int>((yyvsp[0].number)));
      (yyloc) = (yylsp[0]);
    }
#line 2250 "yacc_sql.cpp"
    break;

  case 57: /* value: FLOAT  */
#line 519 "yacc_sql.y"
            {
      (yyval.value) = new Value(static_cast<float>((yyvsp[0].floats)));
      (yyloc) = (yylsp[0]);
    }
#line 2259 "yacc_sql.cpp"
    break;

  case 58: /* value: SSS  */
#line 523 "yacc_sql.y"
          {
      /* This is to eliminate the double/single quotes from the input string */
      char *tmp = common::substr((yyvsp[0].string), 1, strlen((yyvsp[0].string)) - 2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2270 "yacc_sql.cpp"
    break;

  case 59: /* value: DATE_STR  */
#line 529 "yacc_sql.y"
               {
      char *tmp = common::substr((yyvsp[0].string), 1, strlen((yyvsp[0].string)) - 2);
      /* Note the length here is by default 10 */
      (yyval.value) = new Value(DATE, tmp);
      free(tmp);
    }
#line 2281 "yacc_sql.cpp"
    break;

  case 60: /* value: OB_NULL  */
#line 535 "yacc_sql.y"
              {
      // Note that we can not get the actual schema of this column right here
      // Will adjust the value to the actual type later
      (yyval.value) = new Value(0);
      (yyval.value)->set_null();
    }
#line 2292 "yacc_sql.cpp"
    break;

  case 61: /* delete_stmt: DELETE FROM ID where  */
#line 544 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2306 "yacc_sql.cpp"
    break;

  case 62: /* update_stmt: UPDATE ID SET ID EQ value update_value_list where  */
#line 556 "yacc_sql.y"
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
#line 2333 "yacc_sql.cpp"
    break;

  case 63: /* update_value_list: %empty  */
#line 582 "yacc_sql.y"
    {
      (yyval.update_value_list) = nullptr;
    }
#line 2341 "yacc_sql.cpp"
    break;

  case 64: /* update_value_list: COMMA ID EQ value update_value_list  */
#line 585 "yacc_sql.y"
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
#line 2359 "yacc_sql.cpp"
    break;

  case 65: /* select_stmt: CREATE TABLE ID AS select_stmt  */
#line 603 "yacc_sql.y"
                                   {
      (yyval.sql_node) = (yyvsp[0].sql_node);
      (yyval.sql_node)->selection.create_table_name = (yyvsp[-2].string);
    }
#line 2368 "yacc_sql.cpp"
    break;

  case 66: /* select_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE select_stmt  */
#line 609 "yacc_sql.y"
    {
      (yyval.sql_node) = (yyvsp[0].sql_node);
      (yyval.sql_node)->selection.create_table_name = (yyvsp[-5].string);

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-2].attr_infos);

      if (src_attrs != nullptr) {
        (yyval.sql_node)->selection.attr_infos.swap(*src_attrs);
      }
      (yyval.sql_node)->selection.attr_infos.emplace_back(*(yyvsp[-3].attr_info));
      std::reverse((yyval.sql_node)->selection.attr_infos.begin(), (yyval.sql_node)->selection.attr_infos.end());
      delete (yyvsp[-3].attr_info);
    }
#line 2386 "yacc_sql.cpp"
    break;

  case 67: /* select_stmt: SELECT select_attr FROM ID option_as rel_list where order_by_clause group_by_clause having  */
#line 624 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);

      if ((yyvsp[-8].rel_attr_list) != nullptr) {
        (yyval.sql_node)->selection.attributes.swap(*(yyvsp[-8].rel_attr_list));
        delete (yyvsp[-8].rel_attr_list);
      }

      if ((yyvsp[-4].relation_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap(*(yyvsp[-4].relation_list));
        delete (yyvsp[-4].relation_list);
      }

      RelationSqlNode relation;
      relation.relation_name = (yyvsp[-6].string);
      free((yyvsp[-6].string));

      if((yyvsp[-5].string) != nullptr) {
      	relation.alias_name = (yyvsp[-5].string);
      	free((yyvsp[-5].string));
      }

      (yyval.sql_node)->selection.relations.push_back(relation);
      std::reverse((yyval.sql_node)->selection.relations.begin(), (yyval.sql_node)->selection.relations.end());

      if ((yyvsp[-3].condition_list) != nullptr) {
        (yyval.sql_node)->selection.conditions.swap(*(yyvsp[-3].condition_list));
        delete (yyvsp[-3].condition_list);
      }

      if((yyvsp[-2].order_by_list_type) != nullptr) {
        (yyval.sql_node)->selection.order_bys.insert((yyval.sql_node)->selection.order_bys.end(),(yyvsp[-2].order_by_list_type)->begin(),(yyvsp[-2].order_by_list_type)->end());
        delete (yyvsp[-2].order_by_list_type);
      }

      if ((yyvsp[-1].group_by_list_type) != nullptr) {
        (yyval.sql_node)->selection.group_bys.swap(*(yyvsp[-1].group_by_list_type));
      }

      if ((yyvsp[0].condition) != nullptr) {
        (yyval.sql_node)->selection.having = *(yyvsp[0].condition);
        delete (yyvsp[0].condition);
      } else {
        ConditionSqlNode having;
        // To mark the absence of having condition
        having.left_value.set_type(UNDEFINED);
        having.right_value.set_type(UNDEFINED);
        (yyval.sql_node)->selection.having = having;
      }
    }
#line 2441 "yacc_sql.cpp"
    break;

  case 68: /* select_stmt: SELECT select_attr FROM ID inner_join_constr inner_join_list where order_by_clause  */
#line 675 "yacc_sql.y"
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
#line 2486 "yacc_sql.cpp"
    break;

  case 69: /* inner_join_constr: INNER JOIN ID ON condition_list  */
#line 719 "yacc_sql.y"
    {
      (yyval.join_list) = new std::vector<JoinSqlNode>;
      JoinSqlNode join_node;
      join_node.relation_name = (yyvsp[-2].string);
      join_node.conditions.swap(*(yyvsp[0].condition_list));
      (yyval.join_list)->emplace_back(join_node);
      free((yyvsp[-2].string));
    }
#line 2499 "yacc_sql.cpp"
    break;

  case 70: /* inner_join_list: %empty  */
#line 730 "yacc_sql.y"
    {
      (yyval.join_list) = nullptr;
    }
#line 2507 "yacc_sql.cpp"
    break;

  case 71: /* inner_join_list: INNER JOIN ID ON condition_list inner_join_list  */
#line 734 "yacc_sql.y"
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
#line 2524 "yacc_sql.cpp"
    break;

  case 72: /* group_by_clause: %empty  */
#line 749 "yacc_sql.y"
    {
      (yyval.group_by_list_type) = nullptr;
    }
#line 2532 "yacc_sql.cpp"
    break;

  case 73: /* group_by_clause: GROUP BY group_by_list  */
#line 752 "yacc_sql.y"
                             {
      assert((yyvsp[0].group_by_list_type) != nullptr && "Expect `group_by_list` not to be null");
      (yyval.group_by_list_type) = (yyvsp[0].group_by_list_type);
    }
#line 2541 "yacc_sql.cpp"
    break;

  case 74: /* group_by_list: rel_attr  */
#line 759 "yacc_sql.y"
             {
      assert((yyvsp[0].rel_attr) != nullptr && "Expect `rel_attr` not to be null");

      (yyval.group_by_list_type) = new std::vector<RelAttrSqlNode>;
      (yyval.group_by_list_type)->emplace_back(*(yyvsp[0].rel_attr));

      delete (yyvsp[0].rel_attr);
    }
#line 2554 "yacc_sql.cpp"
    break;

  case 75: /* group_by_list: rel_attr COMMA group_by_list  */
#line 767 "yacc_sql.y"
                                   {
      assert((yyvsp[-2].rel_attr) != nullptr && (yyvsp[0].group_by_list_type) != nullptr && "Expect all item not to be null");

      if ((yyvsp[0].group_by_list_type) != nullptr) {
        (yyval.group_by_list_type) = (yyvsp[0].group_by_list_type);
      } else {
        (yyval.group_by_list_type) = new std::vector<RelAttrSqlNode>;
      }

      // Note that the order of group by item should be reversed
      // But since the order does not matter, just keep it simple at present
      (yyval.group_by_list_type)->emplace_back(*(yyvsp[-2].rel_attr));

      delete (yyvsp[-2].rel_attr);
    }
#line 2574 "yacc_sql.cpp"
    break;

  case 76: /* having: %empty  */
#line 785 "yacc_sql.y"
    {
      (yyval.condition) = nullptr;
    }
#line 2582 "yacc_sql.cpp"
    break;

  case 77: /* having: HAVING condition  */
#line 788 "yacc_sql.y"
                       {
      assert((yyvsp[0].condition) != nullptr && "Expect having condition not to be nullptr");
      (yyval.condition) = (yyvsp[0].condition);
    }
#line 2591 "yacc_sql.cpp"
    break;

  case 78: /* order_by_clause: %empty  */
#line 795 "yacc_sql.y"
    {
	(yyval.order_by_list_type) = nullptr;
    }
#line 2599 "yacc_sql.cpp"
    break;

  case 79: /* order_by_clause: ORDER BY order_by_list  */
#line 798 "yacc_sql.y"
                             {
        (yyval.order_by_list_type) = (yyvsp[0].order_by_list_type);
    }
#line 2607 "yacc_sql.cpp"
    break;

  case 80: /* order_by_list: order_by_item  */
#line 804 "yacc_sql.y"
                  {
        (yyval.order_by_list_type) = new std::vector<OrderBySqlNode>;
        (yyval.order_by_list_type)->insert((yyval.order_by_list_type)->begin(), (*(yyvsp[0].order_by_list_type)).begin(), (*(yyvsp[0].order_by_list_type)).end());
        delete (yyvsp[0].order_by_list_type);
    }
#line 2617 "yacc_sql.cpp"
    break;

  case 81: /* order_by_list: order_by_item COMMA order_by_list  */
#line 809 "yacc_sql.y"
                                        {
        if ((yyvsp[0].order_by_list_type) != nullptr) {
            (yyval.order_by_list_type) = (yyvsp[0].order_by_list_type);
        } else {
            (yyval.order_by_list_type) = new std::vector<OrderBySqlNode>;
        }
      (yyval.order_by_list_type)->insert((yyval.order_by_list_type)->begin(), (*(yyvsp[-2].order_by_list_type)).begin(), (*(yyvsp[-2].order_by_list_type)).end());
      delete (yyvsp[-2].order_by_list_type);
    }
#line 2631 "yacc_sql.cpp"
    break;

  case 82: /* order_by_item: rel_attr  */
#line 821 "yacc_sql.y"
             {
        (yyval.order_by_list_type) = new std::vector<OrderBySqlNode>;
        OrderBySqlNode item;
        item.order_by_attributes.emplace_back(*(yyvsp[0].rel_attr));
        item.order_by_asc.emplace_back(true);
        (yyval.order_by_list_type)->emplace_back(item);
        delete (yyvsp[0].rel_attr);
    }
#line 2644 "yacc_sql.cpp"
    break;

  case 83: /* order_by_item: rel_attr ASC  */
#line 829 "yacc_sql.y"
                   {
         	(yyval.order_by_list_type) = new std::vector<OrderBySqlNode>;
                OrderBySqlNode item;
                item.order_by_attributes.emplace_back(*(yyvsp[-1].rel_attr));
                item.order_by_asc.emplace_back(true);
                (yyval.order_by_list_type)->emplace_back(item);
                delete (yyvsp[-1].rel_attr);
    }
#line 2657 "yacc_sql.cpp"
    break;

  case 84: /* order_by_item: rel_attr DESC  */
#line 837 "yacc_sql.y"
                    {
                (yyval.order_by_list_type) = new std::vector<OrderBySqlNode>;
                OrderBySqlNode item;
                item.order_by_attributes.emplace_back(*(yyvsp[-1].rel_attr));
                item.order_by_asc.emplace_back(false);
                (yyval.order_by_list_type)->emplace_back(item);
                delete (yyvsp[-1].rel_attr);
    }
#line 2670 "yacc_sql.cpp"
    break;

  case 85: /* calc_stmt: CALC expression_list  */
#line 849 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2681 "yacc_sql.cpp"
    break;

  case 86: /* expression_list: expression  */
#line 859 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2690 "yacc_sql.cpp"
    break;

  case 87: /* expression_list: expression COMMA expression_list  */
#line 864 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2703 "yacc_sql.cpp"
    break;

  case 88: /* expression: expression '+' expression  */
#line 875 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2711 "yacc_sql.cpp"
    break;

  case 89: /* expression: expression '-' expression  */
#line 878 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2719 "yacc_sql.cpp"
    break;

  case 90: /* expression: expression '*' expression  */
#line 881 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2727 "yacc_sql.cpp"
    break;

  case 91: /* expression: expression '/' expression  */
#line 884 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2735 "yacc_sql.cpp"
    break;

  case 92: /* expression: LBRACE expression RBRACE  */
#line 887 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2744 "yacc_sql.cpp"
    break;

  case 93: /* expression: '-' expression  */
#line 891 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2752 "yacc_sql.cpp"
    break;

  case 94: /* expression: value  */
#line 894 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2762 "yacc_sql.cpp"
    break;

  case 95: /* expression: rel_attr  */
#line 899 "yacc_sql.y"
               {
      // The actual field will be parsed in select statement
      (yyval.expression) = new FieldExpr(*(yyvsp[0].rel_attr));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2772 "yacc_sql.cpp"
    break;

  case 96: /* expression: ID_MINUS  */
#line 907 "yacc_sql.y"
               {
      char *ptr = strchr((yyvsp[0].string), '-');
      assert(ptr != nullptr && "Expect `ptr` not to be nullptr");
      *ptr = '\0';
      RelAttrSqlNode rel_attr;
      rel_attr.attribute_name = (yyvsp[0].string);
      rel_attr.aggregate_func = agg::NONE;
      FieldExpr *f_expr = new FieldExpr(rel_attr);
      int v = atoi(ptr + 1);
      Value value;
      value.set_int(v);
      ValueExpr *value_expr = new ValueExpr(value);
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, f_expr, value_expr, sql_string, &(yyloc));
    }
#line 2791 "yacc_sql.cpp"
    break;

  case 97: /* expression: MIN_MINUS  */
#line 922 "yacc_sql.y"
                {
          char *ptr = strchr((yyvsp[0].string), '-');
          assert(ptr != nullptr && "Expect `ptr` not to be nullptr");
          *(ptr - 1) = '\0';
          RelAttrSqlNode rel_attr;
          rel_attr.attribute_name = ((yyvsp[0].string) + 4);
          rel_attr.aggregate_func = AGG_MIN;
          FieldExpr *f_expr = new FieldExpr(rel_attr);
          int v = atoi(ptr + 1);
          Value value;
          value.set_int(v);
          ValueExpr *value_expr = new ValueExpr(value);
          (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, f_expr, value_expr, sql_string, &(yyloc));
        }
#line 2810 "yacc_sql.cpp"
    break;

  case 98: /* expression: MAX_MINUS  */
#line 936 "yacc_sql.y"
                {
   char *ptr = strchr((yyvsp[0].string), '-');
             assert(ptr != nullptr && "Expect `ptr` not to be nullptr");
             *(ptr - 1) = '\0';
             RelAttrSqlNode rel_attr;
             rel_attr.attribute_name = ((yyvsp[0].string) + 4);
             rel_attr.aggregate_func = AGG_MAX;
             FieldExpr *f_expr = new FieldExpr(rel_attr);
             int v = atoi(ptr + 1);
             Value value;
             value.set_int(v);
             ValueExpr *value_expr = new ValueExpr(value);
             (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, f_expr, value_expr, sql_string, &(yyloc));
    }
#line 2829 "yacc_sql.cpp"
    break;

  case 99: /* expression: SUM_MINUS  */
#line 950 "yacc_sql.y"
                {
   char *ptr = strchr((yyvsp[0].string), '-');
             assert(ptr != nullptr && "Expect `ptr` not to be nullptr");
             *(ptr - 1) = '\0';
             RelAttrSqlNode rel_attr;
             rel_attr.attribute_name = ((yyvsp[0].string) + 4);
             rel_attr.aggregate_func = AGG_SUM;
             FieldExpr *f_expr = new FieldExpr(rel_attr);
             int v = atoi(ptr + 1);
             Value value;
             value.set_int(v);
             ValueExpr *value_expr = new ValueExpr(value);
             (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, f_expr, value_expr, sql_string, &(yyloc));
    }
#line 2848 "yacc_sql.cpp"
    break;

  case 100: /* expression: AVG_MINUS  */
#line 964 "yacc_sql.y"
                {
   char *ptr = strchr((yyvsp[0].string), '-');
             assert(ptr != nullptr && "Expect `ptr` not to be nullptr");
             *(ptr - 1) = '\0';
             RelAttrSqlNode rel_attr;
             rel_attr.attribute_name = ((yyvsp[0].string) + 4);
             rel_attr.aggregate_func = AGG_AVG;
             FieldExpr *f_expr = new FieldExpr(rel_attr);
             int v = atoi(ptr + 1);
             Value value;
             value.set_int(v);
             ValueExpr *value_expr = new ValueExpr(value);
             (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, f_expr, value_expr, sql_string, &(yyloc));
    }
#line 2867 "yacc_sql.cpp"
    break;

  case 101: /* expression: COUNT_MINUS  */
#line 978 "yacc_sql.y"
                  {
   char *ptr = strchr((yyvsp[0].string), '-');
             assert(ptr != nullptr && "Expect `ptr` not to be nullptr");
             *(ptr - 1) = '\0';
             RelAttrSqlNode rel_attr;
             rel_attr.attribute_name = ((yyvsp[0].string) + 6);
             rel_attr.aggregate_func = AGG_COUNT;
             FieldExpr *f_expr = new FieldExpr(rel_attr);
             int v = atoi(ptr + 1);
             Value value;
             value.set_int(v);
             ValueExpr *value_expr = new ValueExpr(value);
             (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, f_expr, value_expr, sql_string, &(yyloc));
    }
#line 2886 "yacc_sql.cpp"
    break;

  case 102: /* option_as: %empty  */
#line 996 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2894 "yacc_sql.cpp"
    break;

  case 103: /* option_as: AS ID  */
#line 999 "yacc_sql.y"
            {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2902 "yacc_sql.cpp"
    break;

  case 104: /* option_as: ID  */
#line 1002 "yacc_sql.y"
         {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2910 "yacc_sql.cpp"
    break;

  case 105: /* select_attr: '*' option_as  */
#line 1008 "yacc_sql.y"
                  {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.relation_name  = "";
      attr.attribute_name = "*";
      attr.aggregate_func = agg::NONE;
      if((yyvsp[0].string) != nullptr) {
      	attr.agg_valid_flag = false;
      	free((yyvsp[0].string));
      }
      (yyval.rel_attr_list)->emplace_back(attr);
    }
#line 2927 "yacc_sql.cpp"
    break;

  case 106: /* select_attr: expression_list  */
#line 1021 "yacc_sql.y"
                      {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      for (auto *expr : *(yyvsp[0].expression_list)) {
        RelAttrSqlNode rel_attr;
        if (dynamic_cast<FieldExpr *>(expr) != nullptr) {
          // The expression is field expression
          rel_attr = dynamic_cast<FieldExpr *>(expr)->get_rel_attr();
        } else {
          rel_attr.expr_flag = true;
          rel_attr.expression = expr;
        }
        (yyval.rel_attr_list)->push_back(rel_attr);
      }
    }
#line 2946 "yacc_sql.cpp"
    break;

  case 107: /* select_attr: agg LBRACE rel_attr COMMA rel_attr RBRACE  */
#line 1037 "yacc_sql.y"
                                               {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.agg_valid_flag = false;
      (yyval.rel_attr_list)->emplace_back(attr);
    }
#line 2957 "yacc_sql.cpp"
    break;

  case 108: /* select_attr: agg LBRACE '*' COMMA rel_attr RBRACE  */
#line 1043 "yacc_sql.y"
                                            {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.agg_valid_flag = false;
      (yyval.rel_attr_list)->emplace_back(attr);
    }
#line 2968 "yacc_sql.cpp"
    break;

  case 109: /* agg: MIN  */
#line 1052 "yacc_sql.y"
        {
      (yyval.agg) = agg::AGG_MIN;
    }
#line 2976 "yacc_sql.cpp"
    break;

  case 110: /* agg: MAX  */
#line 1055 "yacc_sql.y"
          {
      (yyval.agg) = agg::AGG_MAX;
    }
#line 2984 "yacc_sql.cpp"
    break;

  case 111: /* agg: AVG  */
#line 1058 "yacc_sql.y"
          {
      (yyval.agg) = agg::AGG_AVG;
    }
#line 2992 "yacc_sql.cpp"
    break;

  case 112: /* agg: SUM  */
#line 1061 "yacc_sql.y"
          {
      (yyval.agg) = agg::AGG_SUM;
    }
#line 3000 "yacc_sql.cpp"
    break;

  case 113: /* agg: COUNT  */
#line 1064 "yacc_sql.y"
            {
      (yyval.agg) = agg::AGG_COUNT;
    }
#line 3008 "yacc_sql.cpp"
    break;

  case 114: /* rel_attr: ID option_as  */
#line 1070 "yacc_sql.y"
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
#line 3024 "yacc_sql.cpp"
    break;

  case 115: /* rel_attr: ID DOT ID option_as  */
#line 1081 "yacc_sql.y"
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
#line 3041 "yacc_sql.cpp"
    break;

  case 116: /* rel_attr: ID DOT '*'  */
#line 1093 "yacc_sql.y"
                 {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = "*";
      (yyval.rel_attr)->aggregate_func = agg::NONE;
      free((yyvsp[-2].string));
    }
#line 3053 "yacc_sql.cpp"
    break;

  case 117: /* rel_attr: agg LBRACE ID RBRACE option_as  */
#line 1101 "yacc_sql.y"
                                     {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name = "";
      (yyval.rel_attr)->attribute_name = (yyvsp[-2].string);
      (yyval.rel_attr)->aggregate_func = (yyvsp[-4].agg);
      if((yyvsp[0].string) != nullptr)
      {
      	(yyval.rel_attr)->alias_name = (yyvsp[0].string);
      	free((yyvsp[0].string));
      }
      free((yyvsp[-2].string));
    }
#line 3070 "yacc_sql.cpp"
    break;

  case 118: /* rel_attr: agg LBRACE ID DOT ID RBRACE option_as  */
#line 1113 "yacc_sql.y"
                                            {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name = (yyvsp[-4].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[-2].string);
      (yyval.rel_attr)->aggregate_func = (yyvsp[-6].agg);
      if((yyvsp[0].string) != nullptr) {
      	(yyval.rel_attr)->alias_name = (yyvsp[0].string);
      	free((yyvsp[0].string));
      }
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
    }
#line 3087 "yacc_sql.cpp"
    break;

  case 119: /* rel_attr: agg LBRACE '*' RBRACE option_as  */
#line 1125 "yacc_sql.y"
                                      {
      (yyval.rel_attr) = new RelAttrSqlNode;

      // Construct the aggregation attribute
      (yyval.rel_attr)->relation_name = "";
      (yyval.rel_attr)->attribute_name = "*";
      (yyval.rel_attr)->aggregate_func = (yyvsp[-4].agg);

      if ((yyvsp[0].string) != nullptr) {
       (yyval.rel_attr)->alias_name = (yyvsp[0].string);
       free((yyvsp[0].string));
      }
    }
#line 3105 "yacc_sql.cpp"
    break;

  case 120: /* rel_attr: agg LBRACE RBRACE  */
#line 1140 "yacc_sql.y"
                        {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->agg_valid_flag = false;
    }
#line 3114 "yacc_sql.cpp"
    break;

  case 121: /* rel_list: %empty  */
#line 1148 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 3122 "yacc_sql.cpp"
    break;

  case 122: /* rel_list: COMMA ID option_as rel_list  */
#line 1151 "yacc_sql.y"
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
#line 3142 "yacc_sql.cpp"
    break;

  case 123: /* where: %empty  */
#line 1169 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3150 "yacc_sql.cpp"
    break;

  case 124: /* where: WHERE condition_list  */
#line 1172 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 3158 "yacc_sql.cpp"
    break;

  case 125: /* condition_list: %empty  */
#line 1179 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3166 "yacc_sql.cpp"
    break;

  case 126: /* condition_list: condition  */
#line 1182 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 3176 "yacc_sql.cpp"
    break;

  case 127: /* condition_list: condition AND condition_list  */
#line 1187 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyvsp[-2].condition)->is_and = true;
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3187 "yacc_sql.cpp"
    break;

  case 128: /* condition_list: condition OR condition_list  */
#line 1193 "yacc_sql.y"
                                  {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyvsp[-2].condition)->is_and = false;
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3198 "yacc_sql.cpp"
    break;

  case 129: /* condition: expression comp_op expression  */
#line 1202 "yacc_sql.y"
                                  {
      FieldExpr *f_lhs = dynamic_cast<FieldExpr *>((yyvsp[-2].expression));
      ValueExpr *v_lhs = dynamic_cast<ValueExpr *>((yyvsp[-2].expression));
      FieldExpr *f_rhs = dynamic_cast<FieldExpr *>((yyvsp[0].expression));
      ValueExpr *v_rhs = dynamic_cast<ValueExpr *>((yyvsp[0].expression));

      (yyval.condition) = new ConditionSqlNode;

      if (f_lhs && f_rhs) {
        // Field comp Field
        (yyval.condition)->left_is_attr = 1;
        (yyval.condition)->right_is_attr = 1;

        (yyval.condition)->comp = (yyvsp[-1].comp);

        (yyval.condition)->left_attr = f_lhs->get_rel_attr();
        (yyval.condition)->right_attr = f_rhs->get_rel_attr();

        delete (yyvsp[-2].expression);
        delete (yyvsp[0].expression);
      } else if (f_lhs && v_rhs) {
        // Field comp Value
        (yyval.condition)->left_is_attr = 1;
        (yyval.condition)->right_is_attr = 0;

        (yyval.condition)->comp = (yyvsp[-1].comp);

        (yyval.condition)->left_attr = f_lhs->get_rel_attr();
        (yyval.condition)->right_value = v_rhs->get_value();

        delete (yyvsp[-2].expression);
        delete (yyvsp[0].expression);
      } else if (v_lhs && f_rhs) {
        // Value comp Field
        (yyval.condition)->left_is_attr = 0;
        (yyval.condition)->right_is_attr = 1;

        (yyval.condition)->comp = (yyvsp[-1].comp);

        (yyval.condition)->left_value = v_lhs->get_value();
        (yyval.condition)->right_attr = f_rhs->get_rel_attr();

        delete (yyvsp[-2].expression);
        delete (yyvsp[0].expression);
      } else if (v_lhs && v_rhs) {
        // Value comp Value
        (yyval.condition)->left_is_attr = 0;
        (yyval.condition)->right_is_attr = 0;

        (yyval.condition)->comp = (yyvsp[-1].comp);

        (yyval.condition)->left_value = v_lhs->get_value();
        (yyval.condition)->right_value = v_rhs->get_value();

        delete (yyvsp[-2].expression);
        delete (yyvsp[0].expression);
      } else if (f_lhs && (!f_rhs && !v_rhs)) {
        // Field comp Expression
        (yyval.condition)->left_is_attr = 1;
        (yyval.condition)->right_is_attr = 0;

        (yyval.condition)->comp = (yyvsp[-1].comp);

        (yyval.condition)->left_attr = f_lhs->get_rel_attr();
        (yyval.condition)->right_expr = (yyvsp[0].expression);

        delete (yyvsp[-2].expression);
      } else if (v_lhs && (!f_rhs && !v_rhs)) {
        // Value comp Expression
        (yyval.condition)->left_is_attr = 0;
        (yyval.condition)->right_is_attr = 0;

        (yyval.condition)->comp = (yyvsp[-1].comp);

        (yyval.condition)->left_value = v_lhs->get_value();
        (yyval.condition)->right_expr = (yyvsp[0].expression);

        delete (yyvsp[-2].expression);
      } else if ((!f_lhs && !v_lhs) && f_rhs) {
        // Expression comp Field
        (yyval.condition)->left_is_attr = 0;
        (yyval.condition)->right_is_attr = 1;

        (yyval.condition)->comp = (yyvsp[-1].comp);

        (yyval.condition)->left_expr = (yyvsp[-2].expression);
        (yyval.condition)->right_attr = f_rhs->get_rel_attr();

        delete (yyvsp[0].expression);
      } else if ((!f_lhs && !v_lhs) && v_rhs) {
        // Expression comp Value
        (yyval.condition)->left_is_attr = 0;
        (yyval.condition)->right_is_attr = 0;

        (yyval.condition)->comp = (yyvsp[-1].comp);

        (yyval.condition)->left_expr = (yyvsp[-2].expression);
        (yyval.condition)->right_value = v_rhs->get_value();

        delete (yyvsp[0].expression);
      } else if (!f_lhs && !v_lhs && !f_rhs && !v_rhs) {
        // Expression comp Expression
        (yyval.condition)->left_is_attr = 0;
        (yyval.condition)->right_is_attr = 0;

        (yyval.condition)->comp = (yyvsp[-1].comp);

        (yyval.condition)->left_expr = (yyvsp[-2].expression);
        (yyval.condition)->right_expr = (yyvsp[0].expression);
      } else {
        assert(false && "This path is impossible");
      }
    }
#line 3316 "yacc_sql.cpp"
    break;

  case 130: /* condition: expression in_op LBRACE select_stmt RBRACE  */
#line 1317 "yacc_sql.y"
    {
    FieldExpr *lhs = dynamic_cast<FieldExpr *>((yyvsp[-4].expression));
          assert(lhs != nullptr && "Expect lhs to be `FieldExpr *`");
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = lhs->get_rel_attr();
      (yyval.condition)->right_is_attr = 2;
      (yyval.condition)->right_sub_select = new SelectSqlNode((yyvsp[-1].sql_node)->selection);
      (yyval.condition)->comp = (yyvsp[-3].comp);
      delete (yyvsp[-4].expression);
    }
#line 3332 "yacc_sql.cpp"
    break;

  case 131: /* condition: expression in_op LBRACE value value_list RBRACE  */
#line 1330 "yacc_sql.y"
    {
    FieldExpr *lhs = dynamic_cast<FieldExpr *>((yyvsp[-5].expression));
          assert(lhs != nullptr && "Expect lhs to be `FieldExpr *`");
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = lhs->get_rel_attr();
      (yyval.condition)->right_is_attr = 3;
      if((yyvsp[-1].value_list) != nullptr) {
	(yyval.condition)->right_value_list.swap(*(yyvsp[-1].value_list));
	delete (yyvsp[-1].value_list);
      }
      (yyval.condition)->right_value_list.push_back(*(yyvsp[-2].value));
      (yyval.condition)->comp = (yyvsp[-4].comp);
      delete (yyvsp[-5].expression);
      delete (yyvsp[-2].value);
    }
#line 3353 "yacc_sql.cpp"
    break;

  case 132: /* condition: expression comp_op LBRACE select_stmt RBRACE  */
#line 1348 "yacc_sql.y"
    {
      FieldExpr *lhs = dynamic_cast<FieldExpr *>((yyvsp[-4].expression));
      assert(lhs != nullptr && "Expect lhs to be `FieldExpr *`");
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = lhs->get_rel_attr();
      (yyval.condition)->right_is_attr = 2;
      (yyval.condition)->right_sub_select = new SelectSqlNode((yyvsp[-1].sql_node)->selection);
      (yyval.condition)->comp = (yyvsp[-3].comp);
      delete (yyvsp[-4].expression);
    }
#line 3369 "yacc_sql.cpp"
    break;

  case 133: /* condition: expression comp_op LBRACE value COMMA value value_list RBRACE  */
#line 1361 "yacc_sql.y"
    {
      FieldExpr *lhs = dynamic_cast<FieldExpr *>((yyvsp[-7].expression));
      assert(lhs != nullptr && "Expect lhs to be `FieldExpr *`");
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = lhs->get_rel_attr();
      (yyval.condition)->right_is_attr = 3;
      if((yyvsp[-1].value_list) != nullptr) {
      	(yyval.condition)->right_value_list.swap(*(yyvsp[-1].value_list));
      	delete (yyvsp[-1].value_list);
      }
      (yyval.condition)->right_value_list.push_back(*(yyvsp[-2].value));
      (yyval.condition)->right_value_list.push_back(*(yyvsp[-4].value));
      (yyval.condition)->comp = (yyvsp[-6].comp);
      delete (yyvsp[-7].expression);
      delete (yyvsp[-4].value);
      delete (yyvsp[-2].value);
      }
#line 3392 "yacc_sql.cpp"
    break;

  case 134: /* condition: LBRACE select_stmt RBRACE comp_op rel_attr  */
#line 1380 "yacc_sql.y"
      {
	(yyval.condition) = new ConditionSqlNode;
	(yyval.condition)->left_is_attr = 2;
	(yyval.condition)->left_sub_select = new SelectSqlNode((yyvsp[-3].sql_node)->selection);
	(yyval.condition)->right_is_attr = 1;
	(yyval.condition)->right_attr = *(yyvsp[0].rel_attr);
	(yyval.condition)->comp = (yyvsp[-1].comp);
	delete (yyvsp[0].rel_attr);
      }
#line 3406 "yacc_sql.cpp"
    break;

  case 135: /* condition: LBRACE select_stmt RBRACE comp_op LBRACE select_stmt RBRACE  */
#line 1390 "yacc_sql.y"
      {
      	(yyval.condition) = new ConditionSqlNode;
      	(yyval.condition)->left_is_attr = 2;
      	(yyval.condition)->left_sub_select = new SelectSqlNode((yyvsp[-5].sql_node)->selection);
      	(yyval.condition)->right_is_attr = 2;
      	(yyval.condition)->right_sub_select = new SelectSqlNode((yyvsp[-1].sql_node)->selection);
      	(yyval.condition)->comp = (yyvsp[-3].comp);
      }
#line 3419 "yacc_sql.cpp"
    break;

  case 136: /* in_op: IN  */
#line 1401 "yacc_sql.y"
       { (yyval.comp) = IN_OP; }
#line 3425 "yacc_sql.cpp"
    break;

  case 137: /* in_op: NOT IN  */
#line 1402 "yacc_sql.y"
             { (yyval.comp) = NOT_IN; }
#line 3431 "yacc_sql.cpp"
    break;

  case 138: /* in_op: EXISTS  */
#line 1403 "yacc_sql.y"
             { (yyval.comp) = EXISTS_OP; }
#line 3437 "yacc_sql.cpp"
    break;

  case 139: /* in_op: NOT EXISTS  */
#line 1404 "yacc_sql.y"
                 { (yyval.comp) = NOT_EXISTS; }
#line 3443 "yacc_sql.cpp"
    break;

  case 140: /* comp_op: EQ  */
#line 1408 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3449 "yacc_sql.cpp"
    break;

  case 141: /* comp_op: LT  */
#line 1409 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3455 "yacc_sql.cpp"
    break;

  case 142: /* comp_op: GT  */
#line 1410 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3461 "yacc_sql.cpp"
    break;

  case 143: /* comp_op: LE  */
#line 1411 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3467 "yacc_sql.cpp"
    break;

  case 144: /* comp_op: GE  */
#line 1412 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3473 "yacc_sql.cpp"
    break;

  case 145: /* comp_op: NE  */
#line 1413 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3479 "yacc_sql.cpp"
    break;

  case 146: /* comp_op: LIKE  */
#line 1414 "yacc_sql.y"
           { (yyval.comp) = LIKE_OP;}
#line 3485 "yacc_sql.cpp"
    break;

  case 147: /* comp_op: NOT LIKE  */
#line 1415 "yacc_sql.y"
               { (yyval.comp) = NOT_LIKE_OP;}
#line 3491 "yacc_sql.cpp"
    break;

  case 148: /* comp_op: NULL_IS  */
#line 1416 "yacc_sql.y"
              { (yyval.comp) = IS; }
#line 3497 "yacc_sql.cpp"
    break;

  case 149: /* comp_op: NULL_IS NOT  */
#line 1417 "yacc_sql.y"
                  { (yyval.comp) = IS_NOT; }
#line 3503 "yacc_sql.cpp"
    break;

  case 150: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1422 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3517 "yacc_sql.cpp"
    break;

  case 151: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1435 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3526 "yacc_sql.cpp"
    break;

  case 152: /* set_variable_stmt: SET ID EQ value  */
#line 1443 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3538 "yacc_sql.cpp"
    break;


#line 3542 "yacc_sql.cpp"

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

#line 1455 "yacc_sql.y"

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
