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
  YYSYMBOL_75_ = 75,                       /* '+'  */
  YYSYMBOL_76_ = 76,                       /* '-'  */
  YYSYMBOL_77_ = 77,                       /* '*'  */
  YYSYMBOL_78_ = 78,                       /* '/'  */
  YYSYMBOL_UMINUS = 79,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 80,                  /* $accept  */
  YYSYMBOL_commands = 81,                  /* commands  */
  YYSYMBOL_command_wrapper = 82,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 83,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 84,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 85,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 86,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 87,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 88,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 89,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 90,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 91,           /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 92,         /* create_index_stmt  */
  YYSYMBOL_attr_name_list = 93,            /* attr_name_list  */
  YYSYMBOL_index_attr = 94,                /* index_attr  */
  YYSYMBOL_index_attr_name_list = 95,      /* index_attr_name_list  */
  YYSYMBOL_drop_index_stmt = 96,           /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 97,         /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 98,             /* attr_def_list  */
  YYSYMBOL_attr_def = 99,                  /* attr_def  */
  YYSYMBOL_null = 100,                     /* null  */
  YYSYMBOL_number = 101,                   /* number  */
  YYSYMBOL_type = 102,                     /* type  */
  YYSYMBOL_insert_stmt = 103,              /* insert_stmt  */
  YYSYMBOL_value_list = 104,               /* value_list  */
  YYSYMBOL_value = 105,                    /* value  */
  YYSYMBOL_delete_stmt = 106,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 107,              /* update_stmt  */
  YYSYMBOL_update_value_list = 108,        /* update_value_list  */
  YYSYMBOL_select_stmt = 109,              /* select_stmt  */
  YYSYMBOL_inner_join_constr = 110,        /* inner_join_constr  */
  YYSYMBOL_inner_join_list = 111,          /* inner_join_list  */
  YYSYMBOL_group_by_clause = 112,          /* group_by_clause  */
  YYSYMBOL_group_by_list = 113,            /* group_by_list  */
  YYSYMBOL_having = 114,                   /* having  */
  YYSYMBOL_order_by_clause = 115,          /* order_by_clause  */
  YYSYMBOL_order_by_list = 116,            /* order_by_list  */
  YYSYMBOL_order_by_item = 117,            /* order_by_item  */
  YYSYMBOL_calc_stmt = 118,                /* calc_stmt  */
  YYSYMBOL_expression_list = 119,          /* expression_list  */
  YYSYMBOL_expression = 120,               /* expression  */
  YYSYMBOL_expr_attr = 121,                /* expr_attr  */
  YYSYMBOL_option_as = 122,                /* option_as  */
  YYSYMBOL_select_attr = 123,              /* select_attr  */
  YYSYMBOL_agg = 124,                      /* agg  */
  YYSYMBOL_rel_attr = 125,                 /* rel_attr  */
  YYSYMBOL_condition_attr = 126,           /* condition_attr  */
  YYSYMBOL_attr_list = 127,                /* attr_list  */
  YYSYMBOL_rel_list = 128,                 /* rel_list  */
  YYSYMBOL_where = 129,                    /* where  */
  YYSYMBOL_condition_list = 130,           /* condition_list  */
  YYSYMBOL_condition = 131,                /* condition  */
  YYSYMBOL_in_op = 132,                    /* in_op  */
  YYSYMBOL_comp_op = 133,                  /* comp_op  */
  YYSYMBOL_load_data_stmt = 134,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 135,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 136,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 137             /* opt_semicolon  */
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
#define YYFINAL  79
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   584

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  80
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  180
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  377

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   330


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
       2,     2,    77,    75,     2,    76,     2,    78,     2,     2,
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
      79
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   232,   232,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   263,   269,   274,   280,   286,   292,   298,
     305,   311,   319,   332,   346,   357,   365,   368,   381,   391,
     410,   413,   427,   440,   459,   462,   465,   472,   476,   477,
     478,   479,   480,   483,   499,   502,   513,   517,   521,   527,
     533,   541,   553,   580,   583,   601,   652,   696,   708,   711,
     727,   730,   737,   745,   763,   766,   773,   776,   782,   787,
     799,   807,   815,   826,   836,   841,   852,   855,   858,   861,
     864,   868,   871,   879,   887,   895,   903,   911,   919,   927,
     935,   943,   951,   959,   967,   975,   983,   991,   999,  1016,
    1023,  1031,  1038,  1050,  1053,  1056,  1062,  1075,  1097,  1111,
    1122,  1128,  1137,  1140,  1143,  1146,  1149,  1156,  1166,  1177,
    1189,  1197,  1209,  1223,  1231,  1242,  1255,  1262,  1272,  1280,
    1283,  1297,  1300,  1318,  1321,  1328,  1331,  1336,  1342,  1350,
    1357,  1369,  1382,  1395,  1408,  1421,  1435,  1446,  1462,  1473,
    1489,  1499,  1510,  1511,  1512,  1513,  1517,  1518,  1519,  1520,
    1521,  1522,  1523,  1524,  1525,  1526,  1530,  1543,  1551,  1561,
    1562
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
  "NUMBER", "FLOAT", "ID", "SSS", "DATE_STR", "ID_MINUS", "'+'", "'-'",
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
  "expr_attr", "option_as", "select_attr", "agg", "rel_attr",
  "condition_attr", "attr_list", "rel_list", "where", "condition_list",
  "condition", "in_op", "comp_op", "load_data_stmt", "explain_stmt",
  "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-228)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-114)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     449,    30,    31,   266,   237,   -70,    15,  -228,    59,   -14,
      22,  -228,  -228,  -228,  -228,  -228,    43,    61,   449,   115,
     141,  -228,  -228,  -228,  -228,  -228,  -228,  -228,  -228,  -228,
    -228,  -228,  -228,  -228,  -228,  -228,  -228,  -228,  -228,  -228,
    -228,    82,    87,   153,    97,   113,   266,  -228,  -228,  -228,
    -228,  -228,  -228,  -228,  -228,   151,  -228,  -228,  -228,   266,
     152,  -228,    42,   225,   169,   144,   -23,   256,   155,   172,
     174,  -228,  -228,   125,   130,   168,   165,   171,  -228,  -228,
    -228,  -228,   199,   179,   147,  -228,   185,    60,   154,  -228,
     348,   348,   348,   348,   266,   266,   266,   266,   266,   348,
     348,   348,   348,   166,    85,   167,  -228,  -228,  -228,   170,
     192,   313,  -228,   210,   190,   177,   110,   164,   178,   181,
     212,   182,  -228,  -228,  -228,  -228,  -228,  -228,  -228,  -228,
    -228,  -228,  -228,   -36,   -36,  -228,  -228,  -228,  -228,  -228,
    -228,  -228,  -228,  -228,  -228,    13,    89,  -228,  -228,   -12,
    -228,   127,    47,   253,   254,   257,   259,   267,   339,  -228,
     233,  -228,   255,   232,   274,   270,   224,  -228,  -228,   226,
    -228,   241,   248,   293,   204,   134,   -23,   313,    -3,   313,
       9,   313,  -228,   110,     3,   374,   450,   466,   298,   487,
    -228,   -18,   110,   310,  -228,  -228,  -228,  -228,  -228,     4,
     178,   304,   258,   309,   323,   278,   294,   190,   281,   190,
    -228,   124,   259,   336,    74,   337,   340,   338,   341,   290,
    -228,  -228,  -228,  -228,  -228,  -228,  -228,   312,  -228,   320,
     496,   266,    10,   -21,  -228,  -228,   354,   371,   339,   339,
     359,   308,   311,   322,  -228,  -228,   274,  -228,  -228,   377,
     378,   258,  -228,   358,   334,   346,   -23,   346,   404,  -228,
    -228,   343,  -228,   -23,   110,   398,   513,    89,  -228,  -228,
      78,  -228,   410,  -228,   256,  -228,   104,   411,  -228,  -228,
      54,    54,  -228,   414,  -228,  -228,  -228,   357,   190,  -228,
    -228,   415,  -228,  -228,  -228,   258,  -228,   416,   339,   394,
     375,  -228,   293,   382,  -228,   417,  -228,   338,  -228,    77,
    -228,   367,    34,   268,   368,   513,   338,   429,   338,   430,
      12,   412,  -228,    91,   378,  -228,  -228,   339,   313,  -228,
     395,   392,  -228,   456,  -228,   -23,   121,   454,   455,   110,
     458,  -228,   465,  -228,   110,  -228,  -228,   248,  -228,   467,
       7,   313,   339,  -228,   469,  -228,   397,  -228,   299,  -228,
    -228,  -228,   359,  -228,   313,  -228,  -228,  -228,   470,  -228,
    -228,   472,  -228,  -228,   313,  -228,  -228
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    25,     0,     0,
       0,    26,    27,    28,    24,    23,     0,     0,     0,     0,
     179,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,     4,     3,    18,    19,
      20,     0,     0,     0,     0,     0,     0,   122,   123,   124,
     125,   126,    60,    56,    57,   109,    58,    59,   108,     0,
       0,    83,    84,     0,     0,   113,   113,   127,     0,     0,
     139,    31,    30,     0,     0,     0,     0,     0,   177,     1,
     180,     2,     0,     0,     0,    29,     0,     0,     0,    91,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   115,   128,   116,     0,
       0,     0,   119,     0,   143,     0,     0,     0,     0,     0,
       0,     0,    90,   110,    92,   104,    93,   105,    94,   106,
      95,   107,    85,    86,    87,    88,    89,   100,    96,   101,
      97,   102,    98,   103,    99,     0,   113,   130,   114,   113,
     133,   109,     0,     0,     0,     0,   139,     0,   145,    61,
       0,   178,     0,     0,    40,     0,     0,    38,   111,     0,
     129,     0,    68,   141,   113,     0,   113,     0,     0,     0,
       0,     0,   140,     0,     0,   113,     0,     0,     0,     0,
     144,   146,     0,     0,    48,    50,    49,    51,    52,    44,
       0,     0,     0,     0,     0,     0,     0,   143,     0,   143,
     131,   110,   139,     0,     0,     0,     0,    54,     0,     0,
     134,   166,   167,   168,   169,   170,   171,     0,   172,   174,
       0,     0,     0,     0,   162,   164,     0,     0,   145,   145,
      63,     0,     0,     0,    45,    43,    40,    39,    35,     0,
      36,     0,   112,     0,     0,    76,   113,    76,   113,   117,
     121,     0,   120,   113,     0,     0,     0,   113,   173,   175,
     113,   151,     0,   153,   149,   138,     0,     0,   163,   165,
       0,     0,   150,     0,   152,   147,   148,     0,   143,   176,
      47,     0,    46,    41,    32,     0,    34,     0,   145,     0,
       0,    66,   141,    70,   132,     0,   118,    54,    53,     0,
     135,     0,     0,   136,     0,     0,    54,     0,    54,     0,
       0,     0,    62,    44,    36,    33,    67,   145,     0,   142,
       0,    74,    55,     0,   160,   113,     0,     0,     0,     0,
       0,   156,     0,   158,     0,    42,    37,    68,    77,    78,
      80,     0,     0,    65,     0,   136,     0,   155,   137,   154,
     157,   159,    63,    69,     0,    82,    81,    71,    72,    75,
     161,     0,    64,    79,     0,   137,    73
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -228,  -228,   474,  -228,  -228,  -228,  -228,  -228,  -228,  -228,
    -228,  -228,  -228,   223,   189,   180,  -228,  -228,   260,   301,
     184,  -228,  -228,  -228,  -116,   -67,  -228,  -228,   140,  -178,
    -228,   156,  -228,   131,  -228,   261,   157,  -228,  -228,   423,
       1,   482,   -64,  -228,    -4,    -1,  -221,  -142,   217,  -199,
    -227,   186,  -228,  -182,  -228,  -228,  -228,  -228
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,   249,   250,   296,    31,    32,   201,   164,
     245,   291,   199,    33,   265,    60,    34,    35,   288,    36,
     172,   207,   331,   367,   353,   301,   348,   349,    37,    61,
      67,    63,   107,    68,    64,   156,   189,   112,   209,   159,
     190,   191,   236,   230,    38,    39,    40,    81
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      69,    71,   108,    70,    62,   231,   218,   237,   255,   273,
     257,   285,   286,     4,   182,   150,   284,   238,   365,    74,
      46,   242,    72,   124,   126,   128,   130,   150,   275,   268,
     275,   168,   137,   139,   141,   143,    41,    44,    42,    45,
     105,    97,    98,   169,   171,   278,   279,    87,   106,   161,
     239,   105,   275,   243,    47,    48,    49,    50,    51,   106,
      89,    94,    52,   244,     4,   176,   177,    43,   214,   366,
     259,   326,    53,    54,    55,    56,    57,    58,   122,    59,
     214,   276,   170,   336,   309,   173,   216,   277,   334,   322,
      73,   186,   174,    75,   333,    62,   133,   134,   135,   136,
     347,    77,   317,   319,   261,   336,   153,   155,   311,   154,
     210,   337,   212,    52,    76,    79,   217,    95,    96,    97,
      98,   220,   313,    53,    54,   240,    56,    57,    47,    48,
      49,    50,    51,   339,   314,    95,    96,    97,    98,   355,
     243,   105,   258,  -113,    80,   174,  -113,   170,   270,   106,
     244,   356,   105,    82,   188,   354,   146,   175,    83,   187,
     106,    84,   147,   271,  -110,  -110,  -110,  -110,    85,    52,
     282,   186,   186,   153,   104,   153,   213,   153,   215,    53,
      54,    88,    56,    57,    86,    87,   103,   105,   109,   110,
     105,   332,   302,   111,   304,   106,   113,   307,   106,   306,
     340,   114,   342,   310,   115,   211,   220,   105,   116,    46,
     150,   147,   117,   316,   318,   106,   118,   119,   120,  -109,
    -109,  -109,  -109,   121,   158,   123,   272,    90,    91,    92,
      93,   186,   274,   283,   188,   188,   162,   145,   148,   187,
     187,   149,   157,    47,    48,    49,    50,    51,   160,   163,
     166,    52,   165,   167,    46,   194,   195,   196,   197,   198,
     186,    53,    54,   151,    56,    57,    58,   105,    59,   152,
     178,   310,   359,   179,   180,   106,   192,   362,   181,  -111,
    -111,  -111,  -111,    46,   183,   186,   193,   202,    47,    48,
      49,    50,    51,   200,   188,   203,    52,   204,   205,   187,
      99,   100,   101,   102,   206,   283,    53,    54,    65,    56,
      57,    58,   208,    59,    66,   232,   241,    47,    48,    49,
      50,    51,   247,   188,   153,    52,   251,   350,   187,   248,
      46,    95,    96,    97,    98,    53,    54,    55,    56,    57,
      58,   252,    59,  -111,  -111,  -111,  -111,   153,   188,   253,
     368,   254,   256,   187,   260,   262,   184,   264,   263,   266,
     153,   267,   268,   350,    47,    48,    49,    50,    51,   269,
     153,   280,    52,   368,  -112,  -112,  -112,  -112,   287,   289,
     290,   292,    53,    54,    65,    56,    57,    58,   281,    59,
      47,    48,    49,    50,    51,   294,   298,   295,    52,    47,
      48,    49,    50,    51,   219,   299,   300,    52,    53,    54,
     185,    56,    57,    58,   305,    59,   308,    53,    54,    55,
      56,    57,    47,    48,    49,    50,    51,   312,   321,   315,
      52,   320,   327,   323,   325,   258,   328,   105,   335,   338,
      53,    54,   270,    56,    57,   106,   330,   341,   343,  -109,
    -109,  -109,  -109,     1,     2,   344,   351,   352,     3,     4,
       5,     6,     7,     8,     9,    10,     4,   105,   371,    11,
      12,    13,   357,   358,   297,   106,   360,    14,    15,  -112,
    -112,  -112,  -112,   361,   324,    16,   364,   370,    17,   374,
     375,    18,    78,   221,   222,   223,   224,   225,   226,   227,
     228,   246,   372,   363,   346,   376,   293,   345,   229,   221,
     222,   223,   224,   225,   226,   227,   228,   132,   303,   329,
       0,   373,     0,     0,   229,    90,    91,    92,    93,     0,
     221,   222,   223,   224,   225,   226,   233,   228,   369,     0,
       0,    95,    96,    97,    98,   229,     0,    47,    48,    49,
      50,    51,     0,   234,   235,    52,   221,   222,   223,   224,
     225,   226,   227,   228,     0,    53,    54,   270,    56,    57,
       0,   229,   125,   127,   129,   131,     0,     0,     0,     0,
       0,   138,   140,   142,   144
};

static const yytype_int16 yycheck[] =
{
       4,    71,    66,     4,     3,   187,   184,   189,   207,   230,
     209,   238,   239,    10,   156,    18,   237,    35,    11,    33,
      17,    17,     7,    90,    91,    92,    93,    18,    18,    50,
      18,    18,    99,   100,   101,   102,     6,     6,     8,     8,
      63,    77,    78,    30,    56,    66,    67,    46,    71,   116,
      68,    63,    18,    49,    51,    52,    53,    54,    55,    71,
      59,    19,    59,    59,    10,    18,    19,    37,    71,    62,
     212,   298,    69,    70,    71,    72,    73,    74,    18,    76,
      71,    71,   146,    71,   266,   149,    77,    77,   309,   288,
      31,   158,    18,    71,    17,    94,    95,    96,    97,    98,
     327,    40,   280,   281,    30,    71,   110,   111,    30,   110,
     174,    77,   176,    59,    71,     0,   183,    75,    76,    77,
      78,   185,    18,    69,    70,   192,    72,    73,    51,    52,
      53,    54,    55,   315,    30,    75,    76,    77,    78,    18,
      49,    63,    18,    19,     3,    18,    19,   211,    71,    71,
      59,    30,    63,    71,   158,   333,    71,    30,    71,   158,
      71,     8,    77,   230,    75,    76,    77,    78,    71,    59,
     237,   238,   239,   177,    30,   179,   177,   181,   179,    69,
      70,    30,    72,    73,    71,   184,    17,    63,    33,    17,
      63,   307,   256,    19,   258,    71,    71,   264,    71,   263,
     316,    71,   318,   267,    36,    71,   270,    63,    43,    17,
      18,    77,    41,   280,   281,    71,    17,    38,    71,    75,
      76,    77,    78,    38,    34,    71,   230,    75,    76,    77,
      78,   298,   231,   237,   238,   239,    72,    71,    71,   238,
     239,    71,    32,    51,    52,    53,    54,    55,    71,    71,
      38,    59,    71,    71,    17,    23,    24,    25,    26,    27,
     327,    69,    70,    71,    72,    73,    74,    63,    76,    77,
      17,   335,   339,    19,    17,    71,    43,   344,    19,    75,
      76,    77,    78,    17,    17,   352,    31,    17,    51,    52,
      53,    54,    55,    19,   298,    71,    59,    71,    57,   298,
      75,    76,    77,    78,    56,   309,    69,    70,    71,    72,
      73,    74,    19,    76,    77,    17,     6,    51,    52,    53,
      54,    55,    18,   327,   328,    59,    17,   328,   327,    71,
      17,    75,    76,    77,    78,    69,    70,    71,    72,    73,
      74,    18,    76,    75,    76,    77,    78,   351,   352,    71,
     351,    57,    71,   352,    18,    18,    17,    19,    18,    18,
     364,    71,    50,   364,    51,    52,    53,    54,    55,    49,
     374,    17,    59,   374,    75,    76,    77,    78,    19,    71,
      69,    59,    69,    70,    71,    72,    73,    74,    17,    76,
      51,    52,    53,    54,    55,    18,    38,    19,    59,    51,
      52,    53,    54,    55,    30,    71,    60,    59,    69,    70,
      71,    72,    73,    74,    71,    76,    18,    69,    70,    71,
      72,    73,    51,    52,    53,    54,    55,    17,    71,    18,
      59,    17,    38,    18,    18,    18,    61,    63,    71,    71,
      69,    70,    71,    72,    73,    71,    64,    18,    18,    75,
      76,    77,    78,     4,     5,    43,    61,    65,     9,    10,
      11,    12,    13,    14,    15,    16,    10,    63,    71,    20,
      21,    22,    18,    18,   251,    71,    18,    28,    29,    75,
      76,    77,    78,    18,   295,    36,    19,    18,    39,    19,
      18,    42,    18,    43,    44,    45,    46,    47,    48,    49,
      50,   200,   362,   347,   324,   374,   246,   323,    58,    43,
      44,    45,    46,    47,    48,    49,    50,    94,   257,   302,
      -1,   364,    -1,    -1,    58,    75,    76,    77,    78,    -1,
      43,    44,    45,    46,    47,    48,    49,    50,   352,    -1,
      -1,    75,    76,    77,    78,    58,    -1,    51,    52,    53,
      54,    55,    -1,    66,    67,    59,    43,    44,    45,    46,
      47,    48,    49,    50,    -1,    69,    70,    71,    72,    73,
      -1,    58,    90,    91,    92,    93,    -1,    -1,    -1,    -1,
      -1,    99,   100,   101,   102
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,     9,    10,    11,    12,    13,    14,    15,
      16,    20,    21,    22,    28,    29,    36,    39,    42,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    96,    97,   103,   106,   107,   109,   118,   134,   135,
     136,     6,     8,    37,     6,     8,    17,    51,    52,    53,
      54,    55,    59,    69,    70,    71,    72,    73,    74,    76,
     105,   119,   120,   121,   124,    71,    77,   120,   123,   124,
     125,    71,     7,    31,    33,    71,    71,    40,    82,     0,
       3,   137,    71,    71,     8,    71,    71,   120,    30,   120,
      75,    76,    77,    78,    19,    75,    76,    77,    78,    75,
      76,    77,    78,    17,    30,    63,    71,   122,   122,    33,
      17,    19,   127,    71,    71,    36,    43,    41,    17,    38,
      71,    38,    18,    71,   105,   121,   105,   121,   105,   121,
     105,   121,   119,   120,   120,   120,   120,   105,   121,   105,
     121,   105,   121,   105,   121,    71,    71,    77,    71,    71,
      18,    71,    77,   124,   125,   124,   125,    32,    34,   129,
      71,   105,    72,    71,    99,    71,    38,    71,    18,    30,
     122,    56,   110,   122,    18,    30,    18,    19,    17,    19,
      17,    19,   127,    17,    17,    71,   105,   120,   124,   126,
     130,   131,    43,    31,    23,    24,    25,    26,    27,   102,
      19,    98,    17,    71,    71,    57,    56,   111,    19,   128,
     122,    71,   122,   125,    71,   125,    77,   105,   109,    30,
     122,    43,    44,    45,    46,    47,    48,    49,    50,    58,
     133,   133,    17,    49,    66,    67,   132,   133,    35,    68,
     105,     6,    17,    49,    59,   100,    99,    18,    71,    93,
      94,    17,    18,    71,    57,   129,    71,   129,    18,   127,
      18,    30,    18,    18,    19,   104,    18,    71,    50,    49,
      71,   105,   124,   126,   120,    18,    71,    77,    66,    67,
      17,    17,   105,   124,   126,   130,   130,    19,   108,    71,
      69,   101,    59,    98,    18,    19,    95,    93,    38,    71,
      60,   115,   122,   115,   122,    71,   122,   105,    18,   133,
     122,    30,    17,    18,    30,    18,   105,   109,   105,   109,
      17,    71,   129,    18,    94,    18,   130,    38,    61,   128,
      64,   112,   104,    17,   126,    71,    71,    77,    71,   133,
     104,    18,   104,    18,    43,   100,    95,   130,   116,   117,
     125,    61,    65,   114,   109,    18,    30,    18,    18,   105,
      18,    18,   105,   111,    19,    11,    62,   113,   125,   131,
      18,    71,   108,   116,    19,    18,   113
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    80,    81,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    92,    93,    94,    95,    95,    96,    97,
      98,    98,    99,    99,   100,   100,   100,   101,   102,   102,
     102,   102,   102,   103,   104,   104,   105,   105,   105,   105,
     105,   106,   107,   108,   108,   109,   109,   110,   111,   111,
     112,   112,   113,   113,   114,   114,   115,   115,   116,   116,
     117,   117,   117,   118,   119,   119,   120,   120,   120,   120,
     120,   120,   120,   120,   120,   120,   120,   120,   120,   120,
     120,   120,   120,   120,   120,   120,   120,   120,   120,   121,
     121,   121,   121,   122,   122,   122,   123,   123,   123,   123,
     123,   123,   124,   124,   124,   124,   124,   125,   125,   125,
     125,   125,   125,   125,   126,   126,   126,   126,   126,   127,
     127,   128,   128,   129,   129,   130,   130,   130,   130,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   132,   132,   132,   132,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   134,   135,   136,   137,
     137
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
       1,     4,     8,     0,     5,    10,     8,     5,     0,     6,
       0,     3,     1,     3,     0,     2,     0,     3,     1,     3,
       1,     2,     2,     2,     1,     3,     3,     3,     3,     3,
       3,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     1,
       3,     4,     6,     0,     2,     1,     2,     6,     7,     2,
       6,     6,     1,     1,     1,     1,     1,     1,     2,     4,
       3,     5,     7,     3,     2,     4,     4,     6,     3,     0,
       3,     0,     4,     0,     2,     0,     1,     3,     3,     3,
       3,     3,     3,     3,     6,     6,     5,     6,     5,     6,
       5,     7,     1,     2,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     2,     7,     2,     4,     0,
       1
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
#line 233 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1951 "yacc_sql.cpp"
    break;

  case 23: /* exit_stmt: EXIT  */
#line 263 "yacc_sql.y"
         {
      (void) yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1960 "yacc_sql.cpp"
    break;

  case 24: /* help_stmt: HELP  */
#line 269 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1968 "yacc_sql.cpp"
    break;

  case 25: /* sync_stmt: SYNC  */
#line 274 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1976 "yacc_sql.cpp"
    break;

  case 26: /* begin_stmt: TRX_BEGIN  */
#line 280 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1984 "yacc_sql.cpp"
    break;

  case 27: /* commit_stmt: TRX_COMMIT  */
#line 286 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1992 "yacc_sql.cpp"
    break;

  case 28: /* rollback_stmt: TRX_ROLLBACK  */
#line 292 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 2000 "yacc_sql.cpp"
    break;

  case 29: /* drop_table_stmt: DROP TABLE ID  */
#line 298 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2010 "yacc_sql.cpp"
    break;

  case 30: /* show_tables_stmt: SHOW TABLES  */
#line 305 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 2018 "yacc_sql.cpp"
    break;

  case 31: /* desc_table_stmt: DESC ID  */
#line 311 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2028 "yacc_sql.cpp"
    break;

  case 32: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE attr_name_list RBRACE  */
#line 320 "yacc_sql.y"
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
#line 2044 "yacc_sql.cpp"
    break;

  case 33: /* create_index_stmt: CREATE UNIQUE INDEX ID ON ID LBRACE attr_name_list RBRACE  */
#line 333 "yacc_sql.y"
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
#line 2060 "yacc_sql.cpp"
    break;

  case 34: /* attr_name_list: index_attr index_attr_name_list  */
#line 346 "yacc_sql.y"
                                    {
      if((yyvsp[0].index_attr_name_list) != nullptr) {
        (yyval.attr_name_list) = (yyvsp[0].index_attr_name_list);
      } else {
        (yyval.attr_name_list) = new std::vector<IndexAttr>;
      }
      (yyval.attr_name_list)->push_back(*(yyvsp[-1].index_attr));
      delete (yyvsp[-1].index_attr);
    }
#line 2074 "yacc_sql.cpp"
    break;

  case 35: /* index_attr: ID  */
#line 357 "yacc_sql.y"
     {
    (yyval.index_attr) = new IndexAttr;
    (yyval.index_attr)->attribute_name = (yyvsp[0].string);
    free((yyvsp[0].string));
  }
#line 2084 "yacc_sql.cpp"
    break;

  case 36: /* index_attr_name_list: %empty  */
#line 365 "yacc_sql.y"
    {
      (yyval.index_attr_name_list) = nullptr;
    }
#line 2092 "yacc_sql.cpp"
    break;

  case 37: /* index_attr_name_list: COMMA index_attr index_attr_name_list  */
#line 368 "yacc_sql.y"
                                            {
      if ((yyvsp[0].index_attr_name_list) != nullptr) {
        (yyval.index_attr_name_list) = (yyvsp[0].index_attr_name_list);
      } else {
        (yyval.index_attr_name_list) = new std::vector<IndexAttr>;
      }

      (yyval.index_attr_name_list)->emplace_back(*(yyvsp[-1].index_attr));
      delete (yyvsp[-1].index_attr);
    }
#line 2107 "yacc_sql.cpp"
    break;

  case 38: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 382 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2119 "yacc_sql.cpp"
    break;

  case 39: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE  */
#line 392 "yacc_sql.y"
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
#line 2139 "yacc_sql.cpp"
    break;

  case 40: /* attr_def_list: %empty  */
#line 410 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2147 "yacc_sql.cpp"
    break;

  case 41: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 414 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2161 "yacc_sql.cpp"
    break;

  case 42: /* attr_def: ID type LBRACE number RBRACE null  */
#line 427 "yacc_sql.y"
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
#line 2179 "yacc_sql.cpp"
    break;

  case 43: /* attr_def: ID type null  */
#line 440 "yacc_sql.y"
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
#line 2199 "yacc_sql.cpp"
    break;

  case 44: /* null: %empty  */
#line 459 "yacc_sql.y"
  {
    (yyval.null) = false;
  }
#line 2207 "yacc_sql.cpp"
    break;

  case 45: /* null: OB_NULL  */
#line 462 "yacc_sql.y"
            {
    (yyval.null) = true;
  }
#line 2215 "yacc_sql.cpp"
    break;

  case 46: /* null: NOT OB_NULL  */
#line 465 "yacc_sql.y"
                {
    // Note that we do NOT need to deal with `NOT NULL` here
    // Since this property will be enable if NULL is not explicitly declared
    (yyval.null) = false;
  }
#line 2225 "yacc_sql.cpp"
    break;

  case 47: /* number: NUMBER  */
#line 472 "yacc_sql.y"
           { (yyval.number) = (yyvsp[0].number); }
#line 2231 "yacc_sql.cpp"
    break;

  case 48: /* type: INT_T  */
#line 476 "yacc_sql.y"
               { (yyval.number) = INTS; }
#line 2237 "yacc_sql.cpp"
    break;

  case 49: /* type: TEXT_T  */
#line 477 "yacc_sql.y"
                 { (yyval.number) = TEXT; }
#line 2243 "yacc_sql.cpp"
    break;

  case 50: /* type: STRING_T  */
#line 478 "yacc_sql.y"
               { (yyval.number) = CHARS; }
#line 2249 "yacc_sql.cpp"
    break;

  case 51: /* type: FLOAT_T  */
#line 479 "yacc_sql.y"
               { (yyval.number) = FLOATS; }
#line 2255 "yacc_sql.cpp"
    break;

  case 52: /* type: DATE_T  */
#line 480 "yacc_sql.y"
               { (yyval.number) = DATE; }
#line 2261 "yacc_sql.cpp"
    break;

  case 53: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 484 "yacc_sql.y"
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
#line 2277 "yacc_sql.cpp"
    break;

  case 54: /* value_list: %empty  */
#line 499 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2285 "yacc_sql.cpp"
    break;

  case 55: /* value_list: COMMA value value_list  */
#line 502 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2299 "yacc_sql.cpp"
    break;

  case 56: /* value: NUMBER  */
#line 513 "yacc_sql.y"
           {
      (yyval.value) = new Value(static_cast<int>((yyvsp[0].number)));
      (yyloc) = (yylsp[0]);
    }
#line 2308 "yacc_sql.cpp"
    break;

  case 57: /* value: FLOAT  */
#line 517 "yacc_sql.y"
            {
      (yyval.value) = new Value(static_cast<float>((yyvsp[0].floats)));
      (yyloc) = (yylsp[0]);
    }
#line 2317 "yacc_sql.cpp"
    break;

  case 58: /* value: SSS  */
#line 521 "yacc_sql.y"
          {
      /* This is to eliminate the double/single quotes from the input string */
      char *tmp = common::substr((yyvsp[0].string), 1, strlen((yyvsp[0].string)) - 2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2328 "yacc_sql.cpp"
    break;

  case 59: /* value: DATE_STR  */
#line 527 "yacc_sql.y"
               {
      char *tmp = common::substr((yyvsp[0].string), 1, strlen((yyvsp[0].string)) - 2);
      /* Note the length here is by default 10 */
      (yyval.value) = new Value(DATE, tmp);
      free(tmp);
    }
#line 2339 "yacc_sql.cpp"
    break;

  case 60: /* value: OB_NULL  */
#line 533 "yacc_sql.y"
              {
      // Note that we can not get the actual schema of this column right here
      // Will adjust the value to the actual type later
      (yyval.value) = new Value(0);
      (yyval.value)->set_null();
    }
#line 2350 "yacc_sql.cpp"
    break;

  case 61: /* delete_stmt: DELETE FROM ID where  */
#line 542 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2364 "yacc_sql.cpp"
    break;

  case 62: /* update_stmt: UPDATE ID SET ID EQ value update_value_list where  */
#line 554 "yacc_sql.y"
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
#line 2391 "yacc_sql.cpp"
    break;

  case 63: /* update_value_list: %empty  */
#line 580 "yacc_sql.y"
    {
      (yyval.update_value_list) = nullptr;
    }
#line 2399 "yacc_sql.cpp"
    break;

  case 64: /* update_value_list: COMMA ID EQ value update_value_list  */
#line 583 "yacc_sql.y"
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
#line 2417 "yacc_sql.cpp"
    break;

  case 65: /* select_stmt: SELECT select_attr FROM ID option_as rel_list where order_by_clause group_by_clause having  */
#line 602 "yacc_sql.y"
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
#line 2472 "yacc_sql.cpp"
    break;

  case 66: /* select_stmt: SELECT select_attr FROM ID inner_join_constr inner_join_list where order_by_clause  */
#line 653 "yacc_sql.y"
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
#line 2517 "yacc_sql.cpp"
    break;

  case 67: /* inner_join_constr: INNER JOIN ID ON condition_list  */
#line 697 "yacc_sql.y"
    {
      (yyval.join_list) = new std::vector<JoinSqlNode>;
      JoinSqlNode join_node;
      join_node.relation_name = (yyvsp[-2].string);
      join_node.conditions.swap(*(yyvsp[0].condition_list));
      (yyval.join_list)->emplace_back(join_node);
      free((yyvsp[-2].string));
    }
#line 2530 "yacc_sql.cpp"
    break;

  case 68: /* inner_join_list: %empty  */
#line 708 "yacc_sql.y"
    {
      (yyval.join_list) = nullptr;
    }
#line 2538 "yacc_sql.cpp"
    break;

  case 69: /* inner_join_list: INNER JOIN ID ON condition_list inner_join_list  */
#line 712 "yacc_sql.y"
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
#line 2555 "yacc_sql.cpp"
    break;

  case 70: /* group_by_clause: %empty  */
#line 727 "yacc_sql.y"
    {
      (yyval.group_by_list_type) = nullptr;
    }
#line 2563 "yacc_sql.cpp"
    break;

  case 71: /* group_by_clause: GROUP BY group_by_list  */
#line 730 "yacc_sql.y"
                             {
      assert((yyvsp[0].group_by_list_type) != nullptr && "Expect `group_by_list` not to be null");
      (yyval.group_by_list_type) = (yyvsp[0].group_by_list_type);
    }
#line 2572 "yacc_sql.cpp"
    break;

  case 72: /* group_by_list: rel_attr  */
#line 737 "yacc_sql.y"
             {
      assert((yyvsp[0].rel_attr) != nullptr && "Expect `rel_attr` not to be null");

      (yyval.group_by_list_type) = new std::vector<RelAttrSqlNode>;
      (yyval.group_by_list_type)->emplace_back(*(yyvsp[0].rel_attr));

      delete (yyvsp[0].rel_attr);
    }
#line 2585 "yacc_sql.cpp"
    break;

  case 73: /* group_by_list: rel_attr COMMA group_by_list  */
#line 745 "yacc_sql.y"
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
#line 2605 "yacc_sql.cpp"
    break;

  case 74: /* having: %empty  */
#line 763 "yacc_sql.y"
    {
      (yyval.condition) = nullptr;
    }
#line 2613 "yacc_sql.cpp"
    break;

  case 75: /* having: HAVING condition  */
#line 766 "yacc_sql.y"
                       {
      assert((yyvsp[0].condition) != nullptr && "Expect having condition not to be nullptr");
      (yyval.condition) = (yyvsp[0].condition);
    }
#line 2622 "yacc_sql.cpp"
    break;

  case 76: /* order_by_clause: %empty  */
#line 773 "yacc_sql.y"
    {
	(yyval.order_by_list_type) = nullptr;
    }
#line 2630 "yacc_sql.cpp"
    break;

  case 77: /* order_by_clause: ORDER BY order_by_list  */
#line 776 "yacc_sql.y"
                             {
        (yyval.order_by_list_type) = (yyvsp[0].order_by_list_type);
    }
#line 2638 "yacc_sql.cpp"
    break;

  case 78: /* order_by_list: order_by_item  */
#line 782 "yacc_sql.y"
                  {
        (yyval.order_by_list_type) = new std::vector<OrderBySqlNode>;
        (yyval.order_by_list_type)->insert((yyval.order_by_list_type)->begin(), (*(yyvsp[0].order_by_list_type)).begin(), (*(yyvsp[0].order_by_list_type)).end());
        delete (yyvsp[0].order_by_list_type);
    }
#line 2648 "yacc_sql.cpp"
    break;

  case 79: /* order_by_list: order_by_item COMMA order_by_list  */
#line 787 "yacc_sql.y"
                                        {
        if ((yyvsp[0].order_by_list_type) != nullptr) {
            (yyval.order_by_list_type) = (yyvsp[0].order_by_list_type);
        } else {
            (yyval.order_by_list_type) = new std::vector<OrderBySqlNode>;
        }
      (yyval.order_by_list_type)->insert((yyval.order_by_list_type)->begin(), (*(yyvsp[-2].order_by_list_type)).begin(), (*(yyvsp[-2].order_by_list_type)).end());
      delete (yyvsp[-2].order_by_list_type);
    }
#line 2662 "yacc_sql.cpp"
    break;

  case 80: /* order_by_item: rel_attr  */
#line 799 "yacc_sql.y"
             {
        (yyval.order_by_list_type) = new std::vector<OrderBySqlNode>;
        OrderBySqlNode item;
        item.order_by_attributes.emplace_back(*(yyvsp[0].rel_attr));
        item.order_by_asc.emplace_back(true);
        (yyval.order_by_list_type)->emplace_back(item);
        delete (yyvsp[0].rel_attr);
    }
#line 2675 "yacc_sql.cpp"
    break;

  case 81: /* order_by_item: rel_attr ASC  */
#line 807 "yacc_sql.y"
                   {
         	(yyval.order_by_list_type) = new std::vector<OrderBySqlNode>;
                OrderBySqlNode item;
                item.order_by_attributes.emplace_back(*(yyvsp[-1].rel_attr));
                item.order_by_asc.emplace_back(true);
                (yyval.order_by_list_type)->emplace_back(item);
                delete (yyvsp[-1].rel_attr);
    }
#line 2688 "yacc_sql.cpp"
    break;

  case 82: /* order_by_item: rel_attr DESC  */
#line 815 "yacc_sql.y"
                    {
                (yyval.order_by_list_type) = new std::vector<OrderBySqlNode>;
                OrderBySqlNode item;
                item.order_by_attributes.emplace_back(*(yyvsp[-1].rel_attr));
                item.order_by_asc.emplace_back(false);
                (yyval.order_by_list_type)->emplace_back(item);
                delete (yyvsp[-1].rel_attr);
    }
#line 2701 "yacc_sql.cpp"
    break;

  case 83: /* calc_stmt: CALC expression_list  */
#line 827 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2712 "yacc_sql.cpp"
    break;

  case 84: /* expression_list: expression  */
#line 837 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2721 "yacc_sql.cpp"
    break;

  case 85: /* expression_list: expression COMMA expression_list  */
#line 842 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2734 "yacc_sql.cpp"
    break;

  case 86: /* expression: expression '+' expression  */
#line 852 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2742 "yacc_sql.cpp"
    break;

  case 87: /* expression: expression '-' expression  */
#line 855 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2750 "yacc_sql.cpp"
    break;

  case 88: /* expression: expression '*' expression  */
#line 858 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2758 "yacc_sql.cpp"
    break;

  case 89: /* expression: expression '/' expression  */
#line 861 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2766 "yacc_sql.cpp"
    break;

  case 90: /* expression: LBRACE expression RBRACE  */
#line 864 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2775 "yacc_sql.cpp"
    break;

  case 91: /* expression: '-' expression  */
#line 868 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2783 "yacc_sql.cpp"
    break;

  case 92: /* expression: value '+' value  */
#line 871 "yacc_sql.y"
                      {
   assert((yyvsp[-2].value) != nullptr && (yyvsp[0].value) != nullptr && "Expect lhs & rhs not to be nullptr");
         ValueExpr *lhs = new ValueExpr(*(yyvsp[-2].value));
         ValueExpr *rhs = new ValueExpr(*(yyvsp[0].value));
         (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, lhs, rhs, sql_string, &(yyloc));
         delete (yyvsp[-2].value);
         delete (yyvsp[0].value);
    }
#line 2796 "yacc_sql.cpp"
    break;

  case 93: /* expression: value '-' value  */
#line 879 "yacc_sql.y"
                      {
       assert((yyvsp[-2].value) != nullptr && (yyvsp[0].value) != nullptr && "Expect lhs & rhs not to be nullptr");
             ValueExpr *lhs = new ValueExpr(*(yyvsp[-2].value));
             ValueExpr *rhs = new ValueExpr(*(yyvsp[0].value));
             (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, lhs, rhs, sql_string, &(yyloc));
             delete (yyvsp[-2].value);
             delete (yyvsp[0].value);
        }
#line 2809 "yacc_sql.cpp"
    break;

  case 94: /* expression: value '*' value  */
#line 887 "yacc_sql.y"
                      {
       assert((yyvsp[-2].value) != nullptr && (yyvsp[0].value) != nullptr && "Expect lhs & rhs not to be nullptr");
             ValueExpr *lhs = new ValueExpr(*(yyvsp[-2].value));
             ValueExpr *rhs = new ValueExpr(*(yyvsp[0].value));
             (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, lhs, rhs, sql_string, &(yyloc));
             delete (yyvsp[-2].value);
             delete (yyvsp[0].value);
        }
#line 2822 "yacc_sql.cpp"
    break;

  case 95: /* expression: value '/' value  */
#line 895 "yacc_sql.y"
                      {
       assert((yyvsp[-2].value) != nullptr && (yyvsp[0].value) != nullptr && "Expect lhs & rhs not to be nullptr");
             ValueExpr *lhs = new ValueExpr(*(yyvsp[-2].value));
             ValueExpr *rhs = new ValueExpr(*(yyvsp[0].value));
             (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, lhs, rhs, sql_string, &(yyloc));
             delete (yyvsp[-2].value);
             delete (yyvsp[0].value);
        }
#line 2835 "yacc_sql.cpp"
    break;

  case 96: /* expression: expr_attr '+' expr_attr  */
#line 903 "yacc_sql.y"
                              {
      assert((yyvsp[-2].rel_attr) != nullptr && (yyvsp[0].rel_attr) != nullptr && "Expect lhs & rhs not to be nullptr");
      FieldExpr *lhs = new FieldExpr(*(yyvsp[-2].rel_attr));
      FieldExpr *rhs = new FieldExpr(*(yyvsp[0].rel_attr));
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, lhs, rhs, sql_string, &(yyloc));
      delete (yyvsp[-2].rel_attr);
      delete (yyvsp[0].rel_attr);
    }
#line 2848 "yacc_sql.cpp"
    break;

  case 97: /* expression: expr_attr '-' expr_attr  */
#line 911 "yacc_sql.y"
                              {
      assert((yyvsp[-2].rel_attr) != nullptr && (yyvsp[0].rel_attr) != nullptr && "Expect lhs & rhs not to be nullptr");
      FieldExpr *lhs = new FieldExpr(*(yyvsp[-2].rel_attr));
      FieldExpr *rhs = new FieldExpr(*(yyvsp[0].rel_attr));
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, lhs, rhs, sql_string, &(yyloc));
      delete (yyvsp[-2].rel_attr);
      delete (yyvsp[0].rel_attr);
    }
#line 2861 "yacc_sql.cpp"
    break;

  case 98: /* expression: expr_attr '*' expr_attr  */
#line 919 "yacc_sql.y"
                              {
      assert((yyvsp[-2].rel_attr) != nullptr && (yyvsp[0].rel_attr) != nullptr && "Expect lhs & rhs not to be nullptr");
      FieldExpr *lhs = new FieldExpr(*(yyvsp[-2].rel_attr));
      FieldExpr *rhs = new FieldExpr(*(yyvsp[0].rel_attr));
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, lhs, rhs, sql_string, &(yyloc));
      delete (yyvsp[-2].rel_attr);
      delete (yyvsp[0].rel_attr);
    }
#line 2874 "yacc_sql.cpp"
    break;

  case 99: /* expression: expr_attr '/' expr_attr  */
#line 927 "yacc_sql.y"
                              {
      assert((yyvsp[-2].rel_attr) != nullptr && (yyvsp[0].rel_attr) != nullptr && "Expect lhs & rhs not to be nullptr");
      FieldExpr *lhs = new FieldExpr(*(yyvsp[-2].rel_attr));
      FieldExpr *rhs = new FieldExpr(*(yyvsp[0].rel_attr));
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, lhs, rhs, sql_string, &(yyloc));
      delete (yyvsp[-2].rel_attr);
      delete (yyvsp[0].rel_attr);
    }
#line 2887 "yacc_sql.cpp"
    break;

  case 100: /* expression: expr_attr '+' value  */
#line 935 "yacc_sql.y"
                          {
      assert((yyvsp[-2].rel_attr) != nullptr && (yyvsp[0].value) != nullptr && "Expect lhs & rhs not to be nullptr");
      FieldExpr *lhs = new FieldExpr(*(yyvsp[-2].rel_attr));
      ValueExpr *rhs = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, lhs, rhs, sql_string, &(yyloc));
      delete (yyvsp[-2].rel_attr);
      delete (yyvsp[0].value);
    }
#line 2900 "yacc_sql.cpp"
    break;

  case 101: /* expression: expr_attr '-' value  */
#line 943 "yacc_sql.y"
                          {
assert((yyvsp[-2].rel_attr) != nullptr && (yyvsp[0].value) != nullptr && "Expect lhs & rhs not to be nullptr");
      FieldExpr *lhs = new FieldExpr(*(yyvsp[-2].rel_attr));
      ValueExpr *rhs = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, lhs, rhs, sql_string, &(yyloc));
      delete (yyvsp[-2].rel_attr);
      delete (yyvsp[0].value);
    }
#line 2913 "yacc_sql.cpp"
    break;

  case 102: /* expression: expr_attr '*' value  */
#line 951 "yacc_sql.y"
                          {
assert((yyvsp[-2].rel_attr) != nullptr && (yyvsp[0].value) != nullptr && "Expect lhs & rhs not to be nullptr");
      FieldExpr *lhs = new FieldExpr(*(yyvsp[-2].rel_attr));
      ValueExpr *rhs = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, lhs, rhs, sql_string, &(yyloc));
      delete (yyvsp[-2].rel_attr);
      delete (yyvsp[0].value);
    }
#line 2926 "yacc_sql.cpp"
    break;

  case 103: /* expression: expr_attr '/' value  */
#line 959 "yacc_sql.y"
                          {
assert((yyvsp[-2].rel_attr) != nullptr && (yyvsp[0].value) != nullptr && "Expect lhs & rhs not to be nullptr");
      FieldExpr *lhs = new FieldExpr(*(yyvsp[-2].rel_attr));
      ValueExpr *rhs = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, lhs, rhs, sql_string, &(yyloc));
      delete (yyvsp[-2].rel_attr);
      delete (yyvsp[0].value);
    }
#line 2939 "yacc_sql.cpp"
    break;

  case 104: /* expression: value '+' expr_attr  */
#line 967 "yacc_sql.y"
                          {
assert((yyvsp[-2].value) != nullptr && (yyvsp[0].rel_attr) != nullptr && "Expect lhs & rhs not to be nullptr");
       ValueExpr *lhs = new ValueExpr(*(yyvsp[-2].value));
       FieldExpr *rhs = new FieldExpr(*(yyvsp[0].rel_attr));
       (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, lhs, rhs, sql_string, &(yyloc));
       delete (yyvsp[-2].value);
       delete (yyvsp[0].rel_attr);
    }
#line 2952 "yacc_sql.cpp"
    break;

  case 105: /* expression: value '-' expr_attr  */
#line 975 "yacc_sql.y"
                          {
assert((yyvsp[-2].value) != nullptr && (yyvsp[0].rel_attr) != nullptr && "Expect lhs & rhs not to be nullptr");
       ValueExpr *lhs = new ValueExpr(*(yyvsp[-2].value));
       FieldExpr *rhs = new FieldExpr(*(yyvsp[0].rel_attr));
       (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, lhs, rhs, sql_string, &(yyloc));
       delete (yyvsp[-2].value);
       delete (yyvsp[0].rel_attr);
    }
#line 2965 "yacc_sql.cpp"
    break;

  case 106: /* expression: value '*' expr_attr  */
#line 983 "yacc_sql.y"
                          {
assert((yyvsp[-2].value) != nullptr && (yyvsp[0].rel_attr) != nullptr && "Expect lhs & rhs not to be nullptr");
       ValueExpr *lhs = new ValueExpr(*(yyvsp[-2].value));
       FieldExpr *rhs = new FieldExpr(*(yyvsp[0].rel_attr));
       (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, lhs, rhs, sql_string, &(yyloc));
       delete (yyvsp[-2].value);
       delete (yyvsp[0].rel_attr);
    }
#line 2978 "yacc_sql.cpp"
    break;

  case 107: /* expression: value '/' expr_attr  */
#line 991 "yacc_sql.y"
                          {
assert((yyvsp[-2].value) != nullptr && (yyvsp[0].rel_attr) != nullptr && "Expect lhs & rhs not to be nullptr");
       ValueExpr *lhs = new ValueExpr(*(yyvsp[-2].value));
       FieldExpr *rhs = new FieldExpr(*(yyvsp[0].rel_attr));
       (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, lhs, rhs, sql_string, &(yyloc));
       delete (yyvsp[-2].value);
       delete (yyvsp[0].rel_attr);
    }
#line 2991 "yacc_sql.cpp"
    break;

  case 108: /* expression: ID_MINUS  */
#line 999 "yacc_sql.y"
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
#line 3010 "yacc_sql.cpp"
    break;

  case 109: /* expr_attr: ID  */
#line 1016 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name = "";
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      (yyval.rel_attr)->aggregate_func = agg::NONE;
      free((yyvsp[0].string));
    }
#line 3022 "yacc_sql.cpp"
    break;

  case 110: /* expr_attr: ID DOT ID  */
#line 1023 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      (yyval.rel_attr)->aggregate_func = agg::NONE;
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3035 "yacc_sql.cpp"
    break;

  case 111: /* expr_attr: agg LBRACE ID RBRACE  */
#line 1031 "yacc_sql.y"
                           {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name = "";
      (yyval.rel_attr)->attribute_name = (yyvsp[-1].string);
      (yyval.rel_attr)->aggregate_func = (yyvsp[-3].agg);
      free((yyvsp[-1].string));
    }
#line 3047 "yacc_sql.cpp"
    break;

  case 112: /* expr_attr: agg LBRACE ID DOT ID RBRACE  */
#line 1038 "yacc_sql.y"
                                  {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-3].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[-1].string);
      (yyval.rel_attr)->aggregate_func = (yyvsp[-5].agg);
      free((yyvsp[-3].string));
      free((yyvsp[-1].string));
    }
#line 3060 "yacc_sql.cpp"
    break;

  case 113: /* option_as: %empty  */
#line 1050 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 3068 "yacc_sql.cpp"
    break;

  case 114: /* option_as: AS ID  */
#line 1053 "yacc_sql.y"
            {
      (yyval.string) = (yyvsp[0].string);
    }
#line 3076 "yacc_sql.cpp"
    break;

  case 115: /* option_as: ID  */
#line 1056 "yacc_sql.y"
         {
      (yyval.string) = (yyvsp[0].string);
    }
#line 3084 "yacc_sql.cpp"
    break;

  case 116: /* select_attr: '*' option_as  */
#line 1062 "yacc_sql.y"
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
#line 3101 "yacc_sql.cpp"
    break;

  case 117: /* select_attr: agg LBRACE '*' RBRACE option_as attr_list  */
#line 1075 "yacc_sql.y"
                                                  {
      /* AGG_FUNC(*) */
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }


      // Construct the aggregation attribute
      RelAttrSqlNode attr;
      attr.relation_name = "";
      attr.attribute_name = "*";
      attr.aggregate_func = (yyvsp[-5].agg);

      if((yyvsp[-1].string) != nullptr) {
      	attr.alias_name = (yyvsp[-1].string);
      	free((yyvsp[-1].string));
      }

      (yyval.rel_attr_list)->emplace_back(attr);
    }
#line 3128 "yacc_sql.cpp"
    break;

  case 118: /* select_attr: rel_attr COMMA agg LBRACE '*' RBRACE option_as  */
#line 1097 "yacc_sql.y"
                                                     {
      /* AGG_FUNC(*) */
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.relation_name = "";
      attr.attribute_name = "*";
      attr.aggregate_func = (yyvsp[-4].agg);
      if((yyvsp[0].string) != nullptr) {
           attr.alias_name = (yyvsp[0].string);
           free((yyvsp[0].string));
      }
      (yyval.rel_attr_list)->emplace_back(attr);
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-6].rel_attr));
    }
#line 3147 "yacc_sql.cpp"
    break;

  case 119: /* select_attr: rel_attr attr_list  */
#line 1111 "yacc_sql.y"
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
#line 3162 "yacc_sql.cpp"
    break;

  case 120: /* select_attr: agg LBRACE rel_attr COMMA rel_attr RBRACE  */
#line 1122 "yacc_sql.y"
                                               {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.agg_valid_flag = false;
      (yyval.rel_attr_list)->emplace_back(attr);
    }
#line 3173 "yacc_sql.cpp"
    break;

  case 121: /* select_attr: agg LBRACE '*' COMMA rel_attr RBRACE  */
#line 1128 "yacc_sql.y"
                                            {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.agg_valid_flag = false;
      (yyval.rel_attr_list)->emplace_back(attr);
    }
#line 3184 "yacc_sql.cpp"
    break;

  case 122: /* agg: MIN  */
#line 1137 "yacc_sql.y"
        {
      (yyval.agg) = agg::AGG_MIN;
    }
#line 3192 "yacc_sql.cpp"
    break;

  case 123: /* agg: MAX  */
#line 1140 "yacc_sql.y"
          {
      (yyval.agg) = agg::AGG_MAX;
    }
#line 3200 "yacc_sql.cpp"
    break;

  case 124: /* agg: AVG  */
#line 1143 "yacc_sql.y"
          {
      (yyval.agg) = agg::AGG_AVG;
    }
#line 3208 "yacc_sql.cpp"
    break;

  case 125: /* agg: SUM  */
#line 1146 "yacc_sql.y"
          {
      (yyval.agg) = agg::AGG_SUM;
    }
#line 3216 "yacc_sql.cpp"
    break;

  case 126: /* agg: COUNT  */
#line 1149 "yacc_sql.y"
            {
      (yyval.agg) = agg::AGG_COUNT;
    }
#line 3224 "yacc_sql.cpp"
    break;

  case 127: /* rel_attr: expression  */
#line 1156 "yacc_sql.y"
               {
      // Unfortunately we could not grab the parsed `RelAttrSqlNode` inside the expression
      // This will be handled through `select_stmt.cpp`
      // Also note that this may contain agg function, which also need to be parsed and resolved
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name = "";
      (yyval.rel_attr)->attribute_name = "";
      (yyval.rel_attr)->expr_flag = true;
      (yyval.rel_attr)->expression = (yyvsp[0].expression);
    }
#line 3239 "yacc_sql.cpp"
    break;

  case 128: /* rel_attr: ID option_as  */
#line 1166 "yacc_sql.y"
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
#line 3255 "yacc_sql.cpp"
    break;

  case 129: /* rel_attr: ID DOT ID option_as  */
#line 1177 "yacc_sql.y"
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
#line 3272 "yacc_sql.cpp"
    break;

  case 130: /* rel_attr: ID DOT '*'  */
#line 1189 "yacc_sql.y"
                 {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = "*";
      (yyval.rel_attr)->aggregate_func = agg::NONE;
      free((yyvsp[-2].string));
    }
#line 3284 "yacc_sql.cpp"
    break;

  case 131: /* rel_attr: agg LBRACE ID RBRACE option_as  */
#line 1197 "yacc_sql.y"
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
#line 3301 "yacc_sql.cpp"
    break;

  case 132: /* rel_attr: agg LBRACE ID DOT ID RBRACE option_as  */
#line 1209 "yacc_sql.y"
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
#line 3318 "yacc_sql.cpp"
    break;

  case 133: /* rel_attr: agg LBRACE RBRACE  */
#line 1223 "yacc_sql.y"
                        {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->agg_valid_flag = false;
    }
#line 3327 "yacc_sql.cpp"
    break;

  case 134: /* condition_attr: ID option_as  */
#line 1231 "yacc_sql.y"
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
#line 3343 "yacc_sql.cpp"
    break;

  case 135: /* condition_attr: ID DOT ID option_as  */
#line 1242 "yacc_sql.y"
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
#line 3360 "yacc_sql.cpp"
    break;

  case 136: /* condition_attr: agg LBRACE ID RBRACE  */
#line 1255 "yacc_sql.y"
                               {
          (yyval.rel_attr) = new RelAttrSqlNode;
          (yyval.rel_attr)->relation_name = "";
          (yyval.rel_attr)->attribute_name = (yyvsp[-1].string);
          (yyval.rel_attr)->aggregate_func = (yyvsp[-3].agg);
          free((yyvsp[-1].string));
        }
#line 3372 "yacc_sql.cpp"
    break;

  case 137: /* condition_attr: agg LBRACE ID DOT ID RBRACE  */
#line 1262 "yacc_sql.y"
                                      {
          (yyval.rel_attr) = new RelAttrSqlNode;
          (yyval.rel_attr)->relation_name = (yyvsp[-3].string);
          (yyval.rel_attr)->attribute_name = (yyvsp[-1].string);
          (yyval.rel_attr)->aggregate_func = (yyvsp[-5].agg);
          free((yyvsp[-3].string));
          free((yyvsp[-1].string));
        }
#line 3385 "yacc_sql.cpp"
    break;

  case 138: /* condition_attr: agg LBRACE RBRACE  */
#line 1272 "yacc_sql.y"
                            {
          (yyval.rel_attr) = new RelAttrSqlNode;
          (yyval.rel_attr)->agg_valid_flag = false;
        }
#line 3394 "yacc_sql.cpp"
    break;

  case 139: /* attr_list: %empty  */
#line 1280 "yacc_sql.y"
    {
      (yyval.rel_attr_list) = nullptr;
    }
#line 3402 "yacc_sql.cpp"
    break;

  case 140: /* attr_list: COMMA rel_attr attr_list  */
#line 1283 "yacc_sql.y"
                               {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }

      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].rel_attr));
      delete (yyvsp[-1].rel_attr);
    }
#line 3417 "yacc_sql.cpp"
    break;

  case 141: /* rel_list: %empty  */
#line 1297 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 3425 "yacc_sql.cpp"
    break;

  case 142: /* rel_list: COMMA ID option_as rel_list  */
#line 1300 "yacc_sql.y"
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
#line 3445 "yacc_sql.cpp"
    break;

  case 143: /* where: %empty  */
#line 1318 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3453 "yacc_sql.cpp"
    break;

  case 144: /* where: WHERE condition_list  */
#line 1321 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 3461 "yacc_sql.cpp"
    break;

  case 145: /* condition_list: %empty  */
#line 1328 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3469 "yacc_sql.cpp"
    break;

  case 146: /* condition_list: condition  */
#line 1331 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 3479 "yacc_sql.cpp"
    break;

  case 147: /* condition_list: condition AND condition_list  */
#line 1336 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyvsp[-2].condition)->is_and = true;
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3490 "yacc_sql.cpp"
    break;

  case 148: /* condition_list: condition OR condition_list  */
#line 1342 "yacc_sql.y"
                                  {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyvsp[-2].condition)->is_and = false;
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3501 "yacc_sql.cpp"
    break;

  case 149: /* condition: expression comp_op expression  */
#line 1351 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_expr = (yyvsp[-2].expression);
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3512 "yacc_sql.cpp"
    break;

  case 150: /* condition: condition_attr comp_op value  */
#line 1358 "yacc_sql.y"
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
#line 3528 "yacc_sql.cpp"
    break;

  case 151: /* condition: value comp_op value  */
#line 1370 "yacc_sql.y"
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
#line 3544 "yacc_sql.cpp"
    break;

  case 152: /* condition: condition_attr comp_op condition_attr  */
#line 1383 "yacc_sql.y"
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
#line 3560 "yacc_sql.cpp"
    break;

  case 153: /* condition: value comp_op condition_attr  */
#line 1396 "yacc_sql.y"
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
#line 3576 "yacc_sql.cpp"
    break;

  case 154: /* condition: agg LBRACE '*' RBRACE comp_op value  */
#line 1408 "yacc_sql.y"
                                          {
      (yyval.condition) = new ConditionSqlNode;
      RelAttrSqlNode left;
      left.attribute_name = "*";
      left.aggregate_func = AGG_COUNT;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = left;
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_value = *(yyvsp[0].value);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[0].value);
    }
#line 3594 "yacc_sql.cpp"
    break;

  case 155: /* condition: value comp_op agg LBRACE '*' RBRACE  */
#line 1421 "yacc_sql.y"
                                          {
      (yyval.condition) = new ConditionSqlNode;
      RelAttrSqlNode right;
      right.attribute_name = "*";
      right.aggregate_func = AGG_COUNT;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_value = *(yyvsp[-5].value);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = right;
      (yyval.condition)->comp = (yyvsp[-4].comp);

      delete (yyvsp[-5].value);
    }
#line 3612 "yacc_sql.cpp"
    break;

  case 156: /* condition: condition_attr in_op LBRACE select_stmt RBRACE  */
#line 1436 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-4].rel_attr);
      (yyval.condition)->right_is_attr = 2;
      (yyval.condition)->right_sub_select = new SelectSqlNode((yyvsp[-1].sql_node)->selection);
      (yyval.condition)->comp = (yyvsp[-3].comp);
      delete (yyvsp[-4].rel_attr);
    }
#line 3626 "yacc_sql.cpp"
    break;

  case 157: /* condition: condition_attr in_op LBRACE value value_list RBRACE  */
#line 1447 "yacc_sql.y"
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
#line 3645 "yacc_sql.cpp"
    break;

  case 158: /* condition: condition_attr comp_op LBRACE select_stmt RBRACE  */
#line 1463 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-4].rel_attr);
      (yyval.condition)->right_is_attr = 2;
      (yyval.condition)->right_sub_select = new SelectSqlNode((yyvsp[-1].sql_node)->selection);
      (yyval.condition)->comp = (yyvsp[-3].comp);
      delete (yyvsp[-4].rel_attr);
    }
#line 3659 "yacc_sql.cpp"
    break;

  case 159: /* condition: condition_attr comp_op LBRACE value value_list RBRACE  */
#line 1474 "yacc_sql.y"
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
#line 3678 "yacc_sql.cpp"
    break;

  case 160: /* condition: LBRACE select_stmt RBRACE comp_op condition_attr  */
#line 1490 "yacc_sql.y"
      {
	(yyval.condition) = new ConditionSqlNode;
	(yyval.condition)->left_is_attr = 2;
	(yyval.condition)->left_sub_select = new SelectSqlNode((yyvsp[-3].sql_node)->selection);
	(yyval.condition)->right_is_attr = 1;
	(yyval.condition)->right_attr = *(yyvsp[0].rel_attr);
	(yyval.condition)->comp = (yyvsp[-1].comp);
	delete (yyvsp[0].rel_attr);
      }
#line 3692 "yacc_sql.cpp"
    break;

  case 161: /* condition: LBRACE select_stmt RBRACE comp_op LBRACE select_stmt RBRACE  */
#line 1500 "yacc_sql.y"
      {
      	(yyval.condition) = new ConditionSqlNode;
      	(yyval.condition)->left_is_attr = 2;
      	(yyval.condition)->left_sub_select = new SelectSqlNode((yyvsp[-5].sql_node)->selection);
      	(yyval.condition)->right_is_attr = 2;
      	(yyval.condition)->right_sub_select = new SelectSqlNode((yyvsp[-1].sql_node)->selection);
      	(yyval.condition)->comp = (yyvsp[-3].comp);
      }
#line 3705 "yacc_sql.cpp"
    break;

  case 162: /* in_op: IN  */
#line 1510 "yacc_sql.y"
       { (yyval.comp) = IN_OP; }
#line 3711 "yacc_sql.cpp"
    break;

  case 163: /* in_op: NOT IN  */
#line 1511 "yacc_sql.y"
             { (yyval.comp) = NOT_IN; }
#line 3717 "yacc_sql.cpp"
    break;

  case 164: /* in_op: EXISTS  */
#line 1512 "yacc_sql.y"
             { (yyval.comp) = EXISTS_OP; }
#line 3723 "yacc_sql.cpp"
    break;

  case 165: /* in_op: NOT EXISTS  */
#line 1513 "yacc_sql.y"
                 { (yyval.comp) = NOT_EXISTS; }
#line 3729 "yacc_sql.cpp"
    break;

  case 166: /* comp_op: EQ  */
#line 1517 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3735 "yacc_sql.cpp"
    break;

  case 167: /* comp_op: LT  */
#line 1518 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3741 "yacc_sql.cpp"
    break;

  case 168: /* comp_op: GT  */
#line 1519 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3747 "yacc_sql.cpp"
    break;

  case 169: /* comp_op: LE  */
#line 1520 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3753 "yacc_sql.cpp"
    break;

  case 170: /* comp_op: GE  */
#line 1521 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3759 "yacc_sql.cpp"
    break;

  case 171: /* comp_op: NE  */
#line 1522 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3765 "yacc_sql.cpp"
    break;

  case 172: /* comp_op: LIKE  */
#line 1523 "yacc_sql.y"
           { (yyval.comp) = LIKE_OP;}
#line 3771 "yacc_sql.cpp"
    break;

  case 173: /* comp_op: NOT LIKE  */
#line 1524 "yacc_sql.y"
               { (yyval.comp) = NOT_LIKE_OP;}
#line 3777 "yacc_sql.cpp"
    break;

  case 174: /* comp_op: NULL_IS  */
#line 1525 "yacc_sql.y"
              { (yyval.comp) = IS; }
#line 3783 "yacc_sql.cpp"
    break;

  case 175: /* comp_op: NULL_IS NOT  */
#line 1526 "yacc_sql.y"
                  { (yyval.comp) = IS_NOT; }
#line 3789 "yacc_sql.cpp"
    break;

  case 176: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1531 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3803 "yacc_sql.cpp"
    break;

  case 177: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1544 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3812 "yacc_sql.cpp"
    break;

  case 178: /* set_variable_stmt: SET ID EQ value  */
#line 1552 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3824 "yacc_sql.cpp"
    break;


#line 3828 "yacc_sql.cpp"

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

#line 1564 "yacc_sql.y"

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
