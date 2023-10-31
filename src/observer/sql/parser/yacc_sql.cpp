/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Skeleton implementation for Bison GLR parsers in C

   Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

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

/* C GLR parser skeleton written by Paul Hilfinger.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "glr.c"

/* Pure parsers.  */
#define YYPURE 1






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


#line 103 "yacc_sql.cpp"

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
  YYSYMBOL_ID_DOT_ID_MINUS = 75,           /* ID_DOT_ID_MINUS  */
  YYSYMBOL_MIN_MINUS = 76,                 /* MIN_MINUS  */
  YYSYMBOL_MAX_MINUS = 77,                 /* MAX_MINUS  */
  YYSYMBOL_AVG_MINUS = 78,                 /* AVG_MINUS  */
  YYSYMBOL_SUM_MINUS = 79,                 /* SUM_MINUS  */
  YYSYMBOL_COUNT_MINUS = 80,               /* COUNT_MINUS  */
  YYSYMBOL_81_ = 81,                       /* '+'  */
  YYSYMBOL_82_ = 82,                       /* '-'  */
  YYSYMBOL_83_ = 83,                       /* '*'  */
  YYSYMBOL_84_ = 84,                       /* '/'  */
  YYSYMBOL_UMINUS = 85,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 86,                  /* $accept  */
  YYSYMBOL_commands = 87,                  /* commands  */
  YYSYMBOL_command_wrapper = 88,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 89,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 90,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 91,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 92,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 93,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 94,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 95,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 96,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 97,           /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 98,         /* create_index_stmt  */
  YYSYMBOL_attr_name_list = 99,            /* attr_name_list  */
  YYSYMBOL_index_attr = 100,               /* index_attr  */
  YYSYMBOL_index_attr_name_list = 101,     /* index_attr_name_list  */
  YYSYMBOL_drop_index_stmt = 102,          /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 103,        /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 104,            /* attr_def_list  */
  YYSYMBOL_attr_def = 105,                 /* attr_def  */
  YYSYMBOL_null = 106,                     /* null  */
  YYSYMBOL_number = 107,                   /* number  */
  YYSYMBOL_type = 108,                     /* type  */
  YYSYMBOL_insert_stmt = 109,              /* insert_stmt  */
  YYSYMBOL_value_list = 110,               /* value_list  */
  YYSYMBOL_value = 111,                    /* value  */
  YYSYMBOL_delete_stmt = 112,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 113,              /* update_stmt  */
  YYSYMBOL_update_value_list = 114,        /* update_value_list  */
  YYSYMBOL_select_stmt = 115,              /* select_stmt  */
  YYSYMBOL_inner_join_constr = 116,        /* inner_join_constr  */
  YYSYMBOL_inner_join_list = 117,          /* inner_join_list  */
  YYSYMBOL_group_by_clause = 118,          /* group_by_clause  */
  YYSYMBOL_group_by_list = 119,            /* group_by_list  */
  YYSYMBOL_having = 120,                   /* having  */
  YYSYMBOL_order_by_clause = 121,          /* order_by_clause  */
  YYSYMBOL_order_by_list = 122,            /* order_by_list  */
  YYSYMBOL_order_by_item = 123,            /* order_by_item  */
  YYSYMBOL_calc_stmt = 124,                /* calc_stmt  */
  YYSYMBOL_expression_list = 125,          /* expression_list  */
  YYSYMBOL_expression = 126,               /* expression  */
  YYSYMBOL_option_as = 127,                /* option_as  */
  YYSYMBOL_select_attr = 128,              /* select_attr  */
  YYSYMBOL_agg = 129,                      /* agg  */
  YYSYMBOL_rel_attr = 130,                 /* rel_attr  */
  YYSYMBOL_rel_list = 131,                 /* rel_list  */
  YYSYMBOL_where = 132,                    /* where  */
  YYSYMBOL_condition_list = 133,           /* condition_list  */
  YYSYMBOL_condition = 134,                /* condition  */
  YYSYMBOL_in_op = 135,                    /* in_op  */
  YYSYMBOL_comp_op = 136,                  /* comp_op  */
  YYSYMBOL_load_data_stmt = 137,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 138,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 139,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 140             /* opt_semicolon  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;


/* Default (constant) value used for initialization for null
   right-hand sides.  Unlike the standard yacc.c template, here we set
   the default value of $$ to a zeroed-out value.  Since the default
   value is undefined, this behavior is technically correct.  */
static YYSTYPE yyval_default;
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;



#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


#ifndef YYFREE
# define YYFREE free
#endif
#ifndef YYMALLOC
# define YYMALLOC malloc
#endif
#ifndef YYREALLOC
# define YYREALLOC realloc
#endif

#ifdef __cplusplus
  typedef bool yybool;
# define yytrue true
# define yyfalse false
#else
  /* When we move to stdbool, get rid of the various casts to yybool.  */
  typedef signed char yybool;
# define yytrue 1
# define yyfalse 0
#endif

#ifndef YYSETJMP
# include <setjmp.h>
# define YYJMP_BUF jmp_buf
# define YYSETJMP(Env) setjmp (Env)
/* Pacify Clang and ICC.  */
# define YYLONGJMP(Env, Val)                    \
 do {                                           \
   longjmp (Env, Val);                          \
   YY_ASSERT (0);                               \
 } while (yyfalse)
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

/* The _Noreturn keyword of C11.  */
#ifndef _Noreturn
# if (defined __cplusplus \
      && ((201103 <= __cplusplus && !(__GNUC__ == 4 && __GNUC_MINOR__ == 7)) \
          || (defined _MSC_VER && 1900 <= _MSC_VER)))
#  define _Noreturn [[noreturn]]
# elif ((!defined __cplusplus || defined __clang__) \
        && (201112 <= (defined __STDC_VERSION__ ? __STDC_VERSION__ : 0) \
            || (!defined __STRICT_ANSI__ \
                && (4 < __GNUC__ + (7 <= __GNUC_MINOR__) \
                    || (defined __apple_build_version__ \
                        ? 6000000 <= __apple_build_version__ \
                        : 3 < __clang_major__ + (5 <= __clang_minor__))))))
   /* _Noreturn works as-is.  */
# elif (2 < __GNUC__ + (8 <= __GNUC_MINOR__) || defined __clang__ \
        || 0x5110 <= __SUNPRO_C)
#  define _Noreturn __attribute__ ((__noreturn__))
# elif 1200 <= (defined _MSC_VER ? _MSC_VER : 0)
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn
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

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  83
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   452

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  86
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  55
/* YYNRULES -- Number of rules.  */
#define YYNRULES  157
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  320
/* YYMAXRHS -- Maximum number of symbols on right-hand side of rule.  */
#define YYMAXRHS 10
/* YYMAXLEFT -- Maximum number of symbols to the left of a handle
   accessed by $0, $-1, etc., in any rule.  */
#define YYMAXLEFT 0

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   336

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
       2,     2,    83,    81,     2,    82,     2,    84,     2,     2,
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
      75,    76,    77,    78,    79,    80,    85
};

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   235,   235,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   266,   272,   277,   283,   289,   295,   301,
     308,   314,   322,   335,   349,   360,   368,   371,   384,   394,
     413,   416,   430,   443,   462,   465,   468,   475,   479,   480,
     481,   482,   483,   486,   502,   505,   516,   520,   524,   530,
     536,   544,   556,   579,   606,   609,   622,   640,   645,   660,
     711,   755,   767,   770,   786,   789,   796,   804,   822,   825,
     832,   835,   841,   846,   858,   866,   874,   885,   895,   900,
     912,   915,   918,   921,   924,   928,   931,   936,   944,   958,
     976,   990,  1004,  1018,  1032,  1050,  1053,  1056,  1062,  1075,
    1091,  1097,  1106,  1109,  1112,  1115,  1118,  1124,  1135,  1147,
    1155,  1167,  1179,  1194,  1202,  1205,  1223,  1226,  1233,  1236,
    1241,  1247,  1256,  1370,  1383,  1401,  1414,  1433,  1443,  1455,
    1456,  1457,  1458,  1462,  1463,  1464,  1465,  1466,  1467,  1468,
    1469,  1470,  1471,  1475,  1488,  1496,  1506,  1507
};
#endif

#define YYPACT_NINF (-232)
#define YYTABLE_NINF (-1)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     410,   135,   136,   218,   185,   -39,    39,  -232,    18,    25,
      46,  -232,  -232,  -232,  -232,  -232,    77,    26,   410,   120,
     149,  -232,  -232,  -232,  -232,  -232,  -232,  -232,  -232,  -232,
    -232,  -232,  -232,  -232,  -232,  -232,  -232,  -232,  -232,  -232,
    -232,    87,    89,   160,   100,   102,   218,  -232,  -232,  -232,
    -232,  -232,  -232,  -232,  -232,    88,  -232,  -232,  -232,  -232,
    -232,  -232,  -232,  -232,  -232,   218,  -232,  -232,    22,   164,
    -232,   -40,  -232,   151,   169,  -232,  -232,   116,   117,   153,
     167,   162,  -232,  -232,  -232,  -232,    -7,   154,   140,  -232,
     175,    -5,   -50,   155,  -232,  -232,  -232,   218,   218,   218,
     218,   218,    36,  -232,   158,    19,   198,   197,   161,    55,
     170,   163,    49,   172,   195,   174,  -232,   -40,  -232,  -232,
    -232,    96,    96,  -232,  -232,  -232,    12,   223,   -44,    -2,
      21,   227,   230,   257,  -232,   205,  -232,   219,   182,   232,
     243,  -232,   235,   204,  -232,  -232,   -40,   207,   -40,   196,
     210,   260,   -47,   123,   123,    55,   145,   329,  -232,   -24,
      40,   270,  -232,  -232,  -232,  -232,  -232,    98,   163,   262,
     211,   212,   264,  -232,   266,  -232,   214,   229,   197,   228,
     197,    75,   283,   284,   285,   287,  -232,  -232,  -232,  -232,
    -232,  -232,   -32,  -232,   254,  -232,  -232,   290,   289,   257,
     257,    49,   294,   244,   245,   258,  -232,  -232,   232,    49,
      28,  -232,   300,   301,   212,   -40,   281,   250,   263,   -40,
     263,  -232,  -232,    55,   304,   358,  -232,  -232,  -232,  -232,
      16,   145,    51,  -232,  -232,   306,   267,   197,  -232,  -232,
     307,  -232,  -232,  -232,   163,  -232,   212,  -232,   327,  -232,
     257,   308,   286,  -232,   260,   288,   285,  -232,   299,   112,
     285,   332,   334,   333,   294,   311,  -232,   -11,   232,   301,
    -232,  -232,   257,   123,  -232,   295,   292,  -232,    49,  -232,
     337,  -232,    55,  -232,   197,    67,  -232,   352,  -232,   210,
    -232,   361,     6,   123,   257,  -232,   363,  -232,   285,  -232,
      49,   294,    49,  -232,   123,  -232,  -232,  -232,   364,  -232,
    -232,   366,   367,  -232,  -232,   123,  -232,   294,  -232,  -232
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    25,     0,     0,
       0,    26,    27,    28,    24,    23,     0,     0,     0,     0,
     156,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,     4,     3,    18,    19,
      20,     0,     0,     0,     0,     0,     0,   112,   113,   114,
     115,   116,    60,    56,    57,   105,    58,    59,    98,    99,
     100,   101,   103,   102,   104,     0,    96,    87,    88,     0,
      97,   105,   109,     0,     0,    31,    30,     0,     0,     0,
       0,     0,   154,     1,   157,     2,     0,     0,     0,    29,
       0,     0,     0,     0,   107,   117,    95,     0,     0,     0,
       0,     0,     0,   108,     0,     0,     0,   126,     0,     0,
       0,     0,     0,     0,     0,     0,    94,   105,   119,   106,
      89,    90,    91,    92,    93,   123,     0,     0,   105,   105,
       0,     0,     0,   128,    61,     0,   155,     0,     0,    40,
       0,    67,     0,     0,    38,   118,   105,     0,   105,     0,
      72,   124,     0,     0,     0,     0,     0,     0,   127,   129,
       0,     0,    48,    50,    49,    51,    52,    44,     0,     0,
       0,     0,     0,   120,     0,   122,     0,     0,   126,     0,
     126,   105,     0,     0,    54,     0,   143,   144,   145,   146,
     147,   148,     0,   149,   151,   139,   141,     0,     0,   128,
     128,     0,    64,     0,     0,     0,    45,    43,    40,    39,
       0,    35,     0,    36,     0,   105,     0,     0,    80,   105,
      80,   111,   110,     0,     0,     0,   150,   140,   142,   152,
       0,     0,   132,   130,   131,     0,     0,   126,   153,    47,
       0,    46,    41,    68,     0,    32,     0,    34,     0,   121,
     128,     0,     0,    70,   124,    74,    54,    53,     0,     0,
      54,     0,    96,     0,    64,     0,    62,    44,    40,    36,
      33,    71,   128,     0,   125,     0,    78,    55,     0,   137,
       0,   133,     0,   135,   126,     0,    42,     0,    37,    72,
      81,    82,    84,     0,     0,    69,     0,   134,    54,    63,
       0,    64,     0,    73,     0,    86,    85,    75,    76,    79,
     138,     0,     0,    65,    83,     0,   136,    64,    77,    66
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -232,  -232,   368,  -232,  -232,  -232,  -232,  -232,  -232,  -232,
    -232,  -232,  -232,   168,   142,   121,  -232,  -232,  -186,  -164,
     122,  -232,  -232,  -232,  -231,  -100,  -232,  -232,  -156,  -109,
    -232,   103,  -232,    76,  -232,   173,    90,  -232,  -232,     4,
      -3,   -65,  -232,   393,  -103,   144,  -173,  -185,   105,  -232,
     184,  -232,  -232,  -232,  -232
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,   212,   213,   247,    31,    32,   169,   139,
     207,   240,   167,    33,   224,    66,    34,    35,   237,    36,
     150,   178,   276,   307,   295,   253,   290,   291,    37,    67,
     157,    95,    73,    69,    70,   180,   134,   158,   159,   197,
     198,    38,    39,    40,    85
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      68,    68,   131,   141,   208,   218,   103,   220,    72,   136,
     111,   199,   149,   116,   233,   234,   146,   305,   226,    93,
     140,   117,   242,    93,   181,   277,     4,    94,   152,   280,
     146,    94,    75,   118,   227,   228,   118,   125,   205,   148,
     153,    97,   147,    91,   200,   244,    76,   185,   206,    77,
     182,   183,   145,   140,   125,   184,   112,   201,    78,     4,
     202,    93,    96,   151,   266,   271,    81,   311,   306,    94,
      47,    48,    49,    50,    51,    52,    98,    99,   100,   101,
     268,   173,   287,   175,   300,    53,    54,   289,    56,    57,
     129,   112,   235,   215,    68,   121,   122,   123,   124,    52,
     243,   120,   130,    98,    99,   100,   101,   126,   284,    53,
      54,   299,    56,    57,    52,   204,   145,    79,    92,   127,
      83,   261,   263,   256,    53,    54,    52,    56,    57,   278,
     260,   262,    98,    99,   100,   101,    53,    54,    93,    56,
      57,    41,    44,    42,    45,   313,    94,   205,    80,   140,
     249,    93,    84,    91,   254,     4,   279,   206,    86,    94,
      87,   319,    46,    47,    48,    49,    50,    51,    88,   296,
     292,    89,    43,    90,    47,    48,    49,    50,    51,   100,
     101,   102,   298,    55,   104,   301,   105,   106,   107,   108,
     308,   312,   113,   243,    55,   232,    47,    48,    49,    50,
      51,   292,    46,   110,    52,   162,   163,   164,   165,   166,
     109,   114,   308,   115,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,   119,    65,    91,   128,
     132,   133,   135,   143,   138,    46,    47,    48,    49,    50,
      51,   148,   137,   142,    52,   144,   154,   155,   160,   170,
     161,   168,   171,   176,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,   177,    65,    71,    47,
      48,    49,    50,    51,   156,   172,   203,    52,   174,   179,
     209,   214,   210,   211,   215,   216,   217,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,   219,
      65,   221,   222,   229,   223,   225,   231,   230,    47,    48,
      49,    50,    51,   236,   239,   238,    52,   241,   245,   250,
     246,   251,   257,   252,   264,   267,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,   265,    65,
      47,    48,    49,    50,    51,   270,   272,   273,    52,   226,
     281,   283,   275,   282,   285,   297,   293,   294,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
     302,    65,   186,   187,   188,   189,   190,   191,   192,   193,
     304,   310,   248,   315,   316,   317,    82,   194,   269,   286,
     288,   318,   303,   255,   314,   195,   196,    74,   274,   309,
       0,   186,   187,   188,   189,   190,   191,   258,   193,   259,
      98,    99,   100,   101,     1,     2,   194,     0,     0,     3,
       4,     5,     6,     7,     8,     9,    10,     0,     0,     0,
      11,    12,    13,     0,     0,     0,     0,     0,    14,    15,
       0,     0,     0,     0,     0,     0,    16,     0,     0,    17,
       0,     0,    18
};

static const yytype_int16 yycheck[] =
{
       3,     4,   105,   112,   168,   178,    71,   180,     4,   109,
      17,    35,    56,    18,   199,   200,    18,    11,    50,    63,
       4,    71,   208,    63,    71,   256,    10,    71,    30,   260,
      18,    71,    71,    83,    66,    67,    83,    18,    49,    18,
      19,    19,    30,    46,    68,    17,     7,   156,    59,    31,
     153,   154,   117,     4,    18,   155,    63,    17,    33,    10,
     160,    63,    65,   128,   237,   250,    40,   298,    62,    71,
      51,    52,    53,    54,    55,    59,    81,    82,    83,    84,
     244,   146,   268,   148,    17,    69,    70,   272,    72,    73,
      71,    63,   201,    18,    97,    98,    99,   100,   101,    59,
     209,    97,    83,    81,    82,    83,    84,    71,   264,    69,
      70,   284,    72,    73,    59,    17,   181,    71,    30,    83,
       0,   230,   231,   223,    69,    70,    59,    72,    73,    17,
     230,   231,    81,    82,    83,    84,    69,    70,    63,    72,
      73,     6,     6,     8,     8,   301,    71,    49,    71,     4,
     215,    63,     3,   156,   219,    10,   259,    59,    71,    71,
      71,   317,    17,    51,    52,    53,    54,    55,     8,   278,
     273,    71,    37,    71,    51,    52,    53,    54,    55,    83,
      84,    17,   282,    71,    33,   285,    17,    71,    71,    36,
     293,   300,    38,   302,    71,   198,    51,    52,    53,    54,
      55,   304,    17,    41,    59,    23,    24,    25,    26,    27,
      43,    71,   315,    38,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    71,    82,   231,    71,
      32,    34,    71,    38,    71,    17,    51,    52,    53,    54,
      55,    18,    72,    71,    59,    71,    19,    17,    43,     6,
      31,    19,    17,    57,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    56,    82,    83,    51,
      52,    53,    54,    55,    17,    71,     6,    59,    71,    19,
      18,    17,    71,    71,    18,    71,    57,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    71,
      82,    18,    18,    49,    19,    18,    17,    17,    51,    52,
      53,    54,    55,    19,    69,    71,    59,    59,    18,    38,
      19,    71,    18,    60,    18,    18,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    71,    82,
      51,    52,    53,    54,    55,    18,    38,    61,    59,    50,
      18,    18,    64,    19,    43,    18,    61,    65,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      18,    82,    43,    44,    45,    46,    47,    48,    49,    50,
      19,    18,   214,    19,    18,    18,    18,    58,   246,   267,
     269,   315,   289,   220,   304,    66,    67,     4,   254,   294,
      -1,    43,    44,    45,    46,    47,    48,    49,    50,   225,
      81,    82,    83,    84,     4,     5,    58,    -1,    -1,     9,
      10,    11,    12,    13,    14,    15,    16,    -1,    -1,    -1,
      20,    21,    22,    -1,    -1,    -1,    -1,    -1,    28,    29,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,    39,
      -1,    -1,    42
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,     9,    10,    11,    12,    13,    14,    15,
      16,    20,    21,    22,    28,    29,    36,    39,    42,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,   102,   103,   109,   112,   113,   115,   124,   137,   138,
     139,     6,     8,    37,     6,     8,    17,    51,    52,    53,
      54,    55,    59,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    82,   111,   125,   126,   129,
     130,    83,   125,   128,   129,    71,     7,    31,    33,    71,
      71,    40,    88,     0,     3,   140,    71,    71,     8,    71,
      71,   126,    30,    63,    71,   127,   126,    19,    81,    82,
      83,    84,    17,   127,    33,    17,    71,    71,    36,    43,
      41,    17,    63,    38,    71,    38,    18,    71,    83,    71,
     125,   126,   126,   126,   126,    18,    71,    83,    71,    71,
      83,   130,    32,    34,   132,    71,   111,    72,    71,   105,
       4,   115,    71,    38,    71,   127,    18,    30,    18,    56,
     116,   127,    30,    19,    19,    17,    17,   126,   133,   134,
      43,    31,    23,    24,    25,    26,    27,   108,    19,   104,
       6,    17,    71,   127,    71,   127,    57,    56,   117,    19,
     131,    71,   130,   130,   111,   115,    43,    44,    45,    46,
      47,    48,    49,    50,    58,    66,    67,   135,   136,    35,
      68,    17,   111,     6,    17,    49,    59,   106,   105,    18,
      71,    71,    99,   100,    17,    18,    71,    57,   132,    71,
     132,    18,    18,    19,   110,    18,    50,    66,    67,    49,
      17,    17,   126,   133,   133,   115,    19,   114,    71,    69,
     107,    59,   104,   115,    17,    18,    19,   101,    99,   127,
      38,    71,    60,   121,   127,   121,   111,    18,    49,   136,
     111,   115,   111,   115,    18,    71,   132,    18,   105,   100,
      18,   133,    38,    61,   131,    64,   118,   110,    17,   130,
     110,    18,    19,    18,   114,    43,   106,   104,   101,   133,
     122,   123,   130,    61,    65,   120,   115,    18,   111,   132,
      17,   111,    18,   117,    19,    11,    62,   119,   130,   134,
      18,   110,   115,   114,   122,    19,    18,    18,   119,   114
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    86,    87,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    98,    99,   100,   101,   101,   102,   103,
     104,   104,   105,   105,   106,   106,   106,   107,   108,   108,
     108,   108,   108,   109,   110,   110,   111,   111,   111,   111,
     111,   112,   113,   113,   114,   114,   114,   115,   115,   115,
     115,   116,   117,   117,   118,   118,   119,   119,   120,   120,
     121,   121,   122,   122,   123,   123,   123,   124,   125,   125,
     126,   126,   126,   126,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   127,   127,   127,   128,   128,
     128,   128,   129,   129,   129,   129,   129,   130,   130,   130,
     130,   130,   130,   130,   131,   131,   132,   132,   133,   133,
     133,   133,   134,   134,   134,   134,   134,   134,   134,   135,
     135,   135,   135,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   137,   138,   139,   140,   140
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
       1,     4,     8,    10,     0,     5,     7,     5,     8,    10,
       8,     5,     0,     6,     0,     3,     1,     3,     0,     2,
       0,     3,     1,     3,     1,     2,     2,     2,     1,     3,
       3,     3,     3,     3,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     2,     1,     2,     1,
       6,     6,     1,     1,     1,     1,     1,     2,     4,     3,
       5,     7,     5,     3,     0,     4,     0,     2,     0,     1,
       3,     3,     3,     5,     6,     5,     8,     5,     7,     1,
       2,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     2,     7,     2,     4,     0,     1
};


/* YYDPREC[RULE-NUM] -- Dynamic precedence of rule #RULE-NUM (0 if none).  */
static const yytype_int8 yydprec[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0
};

/* YYMERGER[RULE-NUM] -- Index of merging function for rule #RULE-NUM.  */
static const yytype_int8 yymerger[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0
};

/* YYIMMEDIATE[RULE-NUM] -- True iff rule #RULE-NUM is not to be deferred, as
   in the case of predicates.  */
static const yybool yyimmediate[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0
};

/* YYCONFLP[YYPACT[STATE-NUM]] -- Pointer into YYCONFL of start of
   list of conflicting reductions corresponding to action entry for
   state STATE-NUM in yytable.  0 means no conflicts.  The list in
   yyconfl is terminated by a rule number of 0.  */
static const yytype_int8 yyconflp[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0
};

/* YYCONFL[I] -- lists of conflicting rule numbers, each terminated by
   0, pointed into by YYCONFLP.  */
static const short yyconfl[] =
{
       0
};


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

# define YYRHSLOC(Rhs, K) ((Rhs)[K].yystate.yyloc)



#undef yynerrs
#define yynerrs (yystackp->yyerrcnt)
#undef yychar
#define yychar (yystackp->yyrawchar)
#undef yylval
#define yylval (yystackp->yyval)
#undef yylloc
#define yylloc (yystackp->yyloc)


enum { YYENOMEM = -2 };

typedef enum { yyok, yyaccept, yyabort, yyerr, yynomem } YYRESULTTAG;

#define YYCHK(YYE)                              \
  do {                                          \
    YYRESULTTAG yychk_flag = YYE;               \
    if (yychk_flag != yyok)                     \
      return yychk_flag;                        \
  } while (0)

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYMAXDEPTH * sizeof (GLRStackItem)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

/* Minimum number of free items on the stack allowed after an
   allocation.  This is to allow allocation and initialization
   to be completed by functions that call yyexpandGLRStack before the
   stack is expanded, thus insuring that all necessary pointers get
   properly redirected to new data.  */
#define YYHEADROOM 2

#ifndef YYSTACKEXPANDABLE
#  define YYSTACKEXPANDABLE 1
#endif

#if YYSTACKEXPANDABLE
# define YY_RESERVE_GLRSTACK(Yystack)                   \
  do {                                                  \
    if (Yystack->yyspaceLeft < YYHEADROOM)              \
      yyexpandGLRStack (Yystack);                       \
  } while (0)
#else
# define YY_RESERVE_GLRSTACK(Yystack)                   \
  do {                                                  \
    if (Yystack->yyspaceLeft < YYHEADROOM)              \
      yyMemoryExhausted (Yystack);                      \
  } while (0)
#endif

/** State numbers. */
typedef int yy_state_t;

/** Rule numbers. */
typedef int yyRuleNum;

/** Item references. */
typedef short yyItemNum;

typedef struct yyGLRState yyGLRState;
typedef struct yyGLRStateSet yyGLRStateSet;
typedef struct yySemanticOption yySemanticOption;
typedef union yyGLRStackItem yyGLRStackItem;
typedef struct yyGLRStack yyGLRStack;

struct yyGLRState
{
  /** Type tag: always true.  */
  yybool yyisState;
  /** Type tag for yysemantics.  If true, yyval applies, otherwise
   *  yyfirstVal applies.  */
  yybool yyresolved;
  /** Number of corresponding LALR(1) machine state.  */
  yy_state_t yylrState;
  /** Preceding state in this stack */
  yyGLRState* yypred;
  /** Source position of the last token produced by my symbol */
  YYPTRDIFF_T yyposn;
  union {
    /** First in a chain of alternative reductions producing the
     *  nonterminal corresponding to this state, threaded through
     *  yynext.  */
    yySemanticOption* yyfirstVal;
    /** Semantic value for this state.  */
    YYSTYPE yyval;
  } yysemantics;
  /** Source location for this state.  */
  YYLTYPE yyloc;
};

struct yyGLRStateSet
{
  yyGLRState** yystates;
  /** During nondeterministic operation, yylookaheadNeeds tracks which
   *  stacks have actually needed the current lookahead.  During deterministic
   *  operation, yylookaheadNeeds[0] is not maintained since it would merely
   *  duplicate yychar != YYEMPTY.  */
  yybool* yylookaheadNeeds;
  YYPTRDIFF_T yysize;
  YYPTRDIFF_T yycapacity;
};

struct yySemanticOption
{
  /** Type tag: always false.  */
  yybool yyisState;
  /** Rule number for this reduction */
  yyRuleNum yyrule;
  /** The last RHS state in the list of states to be reduced.  */
  yyGLRState* yystate;
  /** The lookahead for this reduction.  */
  int yyrawchar;
  YYSTYPE yyval;
  YYLTYPE yyloc;
  /** Next sibling in chain of options.  To facilitate merging,
   *  options are chained in decreasing order by address.  */
  yySemanticOption* yynext;
};

/** Type of the items in the GLR stack.  The yyisState field
 *  indicates which item of the union is valid.  */
union yyGLRStackItem {
  yyGLRState yystate;
  yySemanticOption yyoption;
};

struct yyGLRStack {
  int yyerrState;
  /* To compute the location of the error token.  */
  yyGLRStackItem yyerror_range[3];

  int yyerrcnt;
  int yyrawchar;
  YYSTYPE yyval;
  YYLTYPE yyloc;

  YYJMP_BUF yyexception_buffer;
  yyGLRStackItem* yyitems;
  yyGLRStackItem* yynextFree;
  YYPTRDIFF_T yyspaceLeft;
  yyGLRState* yysplitPoint;
  yyGLRState* yylastDeleted;
  yyGLRStateSet yytops;
};

#if YYSTACKEXPANDABLE
static void yyexpandGLRStack (yyGLRStack* yystackp);
#endif

_Noreturn static void
yyFail (yyGLRStack* yystackp, YYLTYPE *yylocp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner, const char* yymsg)
{
  if (yymsg != YY_NULLPTR)
    yyerror (yylocp, sql_string, sql_result, scanner, yymsg);
  YYLONGJMP (yystackp->yyexception_buffer, 1);
}

_Noreturn static void
yyMemoryExhausted (yyGLRStack* yystackp)
{
  YYLONGJMP (yystackp->yyexception_buffer, 2);
}

/** Accessing symbol of state YYSTATE.  */
static inline yysymbol_kind_t
yy_accessing_symbol (yy_state_t yystate)
{
  return YY_CAST (yysymbol_kind_t, yystos[yystate]);
}

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
  "NUMBER", "FLOAT", "ID", "SSS", "DATE_STR", "ID_MINUS",
  "ID_DOT_ID_MINUS", "MIN_MINUS", "MAX_MINUS", "AVG_MINUS", "SUM_MINUS",
  "COUNT_MINUS", "'+'", "'-'", "'*'", "'/'", "UMINUS", "$accept",
  "commands", "command_wrapper", "exit_stmt", "help_stmt", "sync_stmt",
  "begin_stmt", "commit_stmt", "rollback_stmt", "drop_table_stmt",
  "show_tables_stmt", "desc_table_stmt", "create_index_stmt",
  "attr_name_list", "index_attr", "index_attr_name_list",
  "drop_index_stmt", "create_table_stmt", "attr_def_list", "attr_def",
  "null", "number", "type", "insert_stmt", "value_list", "value",
  "delete_stmt", "update_stmt", "update_value_list", "select_stmt",
  "inner_join_constr", "inner_join_list", "group_by_clause",
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

/** Left-hand-side symbol for rule #YYRULE.  */
static inline yysymbol_kind_t
yylhsNonterm (yyRuleNum yyrule)
{
  return YY_CAST (yysymbol_kind_t, yyr1[yyrule]);
}

#if YYDEBUG

# ifndef YYFPRINTF
#  define YYFPRINTF fprintf
# endif

# define YY_FPRINTF                             \
  YY_IGNORE_USELESS_CAST_BEGIN YY_FPRINTF_

# define YY_FPRINTF_(Args)                      \
  do {                                          \
    YYFPRINTF Args;                             \
    YY_IGNORE_USELESS_CAST_END                  \
  } while (0)

# define YY_DPRINTF                             \
  YY_IGNORE_USELESS_CAST_BEGIN YY_DPRINTF_

# define YY_DPRINTF_(Args)                      \
  do {                                          \
    if (yydebug)                                \
      YYFPRINTF Args;                           \
    YY_IGNORE_USELESS_CAST_END                  \
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

# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                  \
  do {                                                                  \
    if (yydebug)                                                        \
      {                                                                 \
        YY_FPRINTF ((stderr, "%s ", Title));                            \
        yy_symbol_print (stderr, Kind, Value, Location, sql_string, sql_result, scanner);        \
        YY_FPRINTF ((stderr, "\n"));                                    \
      }                                                                 \
  } while (0)

static inline void
yy_reduce_print (yybool yynormal, yyGLRStackItem* yyvsp, YYPTRDIFF_T yyk,
                 yyRuleNum yyrule, const char * sql_string, ParsedSqlResult * sql_result, void * scanner);

# define YY_REDUCE_PRINT(Args)          \
  do {                                  \
    if (yydebug)                        \
      yy_reduce_print Args;             \
  } while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;

static void yypstack (yyGLRStack* yystackp, YYPTRDIFF_T yyk)
  YY_ATTRIBUTE_UNUSED;
static void yypdumpstack (yyGLRStack* yystackp)
  YY_ATTRIBUTE_UNUSED;

#else /* !YYDEBUG */

# define YY_DPRINTF(Args) do {} while (yyfalse)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_REDUCE_PRINT(Args)

#endif /* !YYDEBUG */

#ifndef yystrlen
# define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
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


/** Fill in YYVSP[YYLOW1 .. YYLOW0-1] from the chain of states starting
 *  at YYVSP[YYLOW0].yystate.yypred.  Leaves YYVSP[YYLOW1].yystate.yypred
 *  containing the pointer to the next state in the chain.  */
static void yyfillin (yyGLRStackItem *, int, int) YY_ATTRIBUTE_UNUSED;
static void
yyfillin (yyGLRStackItem *yyvsp, int yylow0, int yylow1)
{
  int i;
  yyGLRState *s = yyvsp[yylow0].yystate.yypred;
  for (i = yylow0-1; i >= yylow1; i -= 1)
    {
#if YYDEBUG
      yyvsp[i].yystate.yylrState = s->yylrState;
#endif
      yyvsp[i].yystate.yyresolved = s->yyresolved;
      if (s->yyresolved)
        yyvsp[i].yystate.yysemantics.yyval = s->yysemantics.yyval;
      else
        /* The effect of using yyval or yyloc (in an immediate rule) is
         * undefined.  */
        yyvsp[i].yystate.yysemantics.yyfirstVal = YY_NULLPTR;
      yyvsp[i].yystate.yyloc = s->yyloc;
      s = yyvsp[i].yystate.yypred = s->yypred;
    }
}


/** If yychar is empty, fetch the next token.  */
static inline yysymbol_kind_t
yygetToken (int *yycharp, yyGLRStack* yystackp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  yysymbol_kind_t yytoken;
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (*yycharp == YYEMPTY)
    {
      YY_DPRINTF ((stderr, "Reading a token\n"));
      *yycharp = yylex (&yylval, &yylloc, scanner);
    }
  if (*yycharp <= YYEOF)
    {
      *yycharp = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YY_DPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (*yycharp);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }
  return yytoken;
}

/* Do nothing if YYNORMAL or if *YYLOW <= YYLOW1.  Otherwise, fill in
 * YYVSP[YYLOW1 .. *YYLOW-1] as in yyfillin and set *YYLOW = YYLOW1.
 * For convenience, always return YYLOW1.  */
static inline int yyfill (yyGLRStackItem *, int *, int, yybool)
     YY_ATTRIBUTE_UNUSED;
static inline int
yyfill (yyGLRStackItem *yyvsp, int *yylow, int yylow1, yybool yynormal)
{
  if (!yynormal && yylow1 < *yylow)
    {
      yyfillin (yyvsp, *yylow, yylow1);
      *yylow = yylow1;
    }
  return yylow1;
}

/** Perform user action for rule number YYN, with RHS length YYRHSLEN,
 *  and top stack item YYVSP.  YYLVALP points to place to put semantic
 *  value ($$), and yylocp points to place for location information
 *  (@$).  Returns yyok for normal return, yyaccept for YYACCEPT,
 *  yyerr for YYERROR, yyabort for YYABORT, yynomem for YYNOMEM.  */
static YYRESULTTAG
yyuserAction (yyRuleNum yyrule, int yyrhslen, yyGLRStackItem* yyvsp,
              yyGLRStack* yystackp, YYPTRDIFF_T yyk,
              YYSTYPE* yyvalp, YYLTYPE *yylocp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  const yybool yynormal YY_ATTRIBUTE_UNUSED = yystackp->yysplitPoint == YY_NULLPTR;
  int yylow = 1;
  YY_USE (yyvalp);
  YY_USE (yylocp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  YY_USE (yyk);
  YY_USE (yyrhslen);
# undef yyerrok
# define yyerrok (yystackp->yyerrState = 0)
# undef YYACCEPT
# define YYACCEPT return yyaccept
# undef YYABORT
# define YYABORT return yyabort
# undef YYNOMEM
# define YYNOMEM return yynomem
# undef YYERROR
# define YYERROR return yyerrok, yyerr
# undef YYRECOVERING
# define YYRECOVERING() (yystackp->yyerrState != 0)
# undef yyclearin
# define yyclearin (yychar = YYEMPTY)
# undef YYFILL
# define YYFILL(N) yyfill (yyvsp, &yylow, (N), yynormal)
# undef YYBACKUP
# define YYBACKUP(Token, Value)                                              \
  return yyerror (yylocp, sql_string, sql_result, scanner, YY_("syntax error: cannot back up")),     \
         yyerrok, yyerr

  if (yyrhslen == 0)
    *yyvalp = yyval_default;
  else
    *yyvalp = yyvsp[YYFILL (1-yyrhslen)].yystate.yysemantics.yyval;
  /* Default location. */
  YYLLOC_DEFAULT ((*yylocp), (yyvsp - yyrhslen), yyrhslen);
  yystackp->yyerror_range[1].yystate.yyloc = *yylocp;
  /* If yyk == -1, we are running a deferred action on a temporary
     stack.  In that case, YY_REDUCE_PRINT must not play with YYFILL,
     so pretend the stack is "normal". */
  YY_REDUCE_PRINT ((yynormal || yyk == -1, yyvsp, yyk, yyrule, sql_string, sql_result, scanner));
  switch (yyrule)
    {
  case 2: /* commands: command_wrapper opt_semicolon  */
#line 236 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1668 "yacc_sql.cpp"
    break;

  case 23: /* exit_stmt: EXIT  */
#line 266 "yacc_sql.y"
         {
      (void) yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      ((*yyvalp).sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1677 "yacc_sql.cpp"
    break;

  case 24: /* help_stmt: HELP  */
#line 272 "yacc_sql.y"
         {
      ((*yyvalp).sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1685 "yacc_sql.cpp"
    break;

  case 25: /* sync_stmt: SYNC  */
#line 277 "yacc_sql.y"
         {
      ((*yyvalp).sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1693 "yacc_sql.cpp"
    break;

  case 26: /* begin_stmt: TRX_BEGIN  */
#line 283 "yacc_sql.y"
               {
      ((*yyvalp).sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1701 "yacc_sql.cpp"
    break;

  case 27: /* commit_stmt: TRX_COMMIT  */
#line 289 "yacc_sql.y"
               {
      ((*yyvalp).sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1709 "yacc_sql.cpp"
    break;

  case 28: /* rollback_stmt: TRX_ROLLBACK  */
#line 295 "yacc_sql.y"
                  {
      ((*yyvalp).sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1717 "yacc_sql.cpp"
    break;

  case 29: /* drop_table_stmt: DROP TABLE ID  */
#line 301 "yacc_sql.y"
                  {
      ((*yyvalp).sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      ((*yyvalp).sql_node)->drop_table.relation_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string);
      free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
    }
#line 1727 "yacc_sql.cpp"
    break;

  case 30: /* show_tables_stmt: SHOW TABLES  */
#line 308 "yacc_sql.y"
                {
      ((*yyvalp).sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1735 "yacc_sql.cpp"
    break;

  case 31: /* desc_table_stmt: DESC ID  */
#line 314 "yacc_sql.y"
             {
      ((*yyvalp).sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      ((*yyvalp).sql_node)->desc_table.relation_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string);
      free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
    }
#line 1745 "yacc_sql.cpp"
    break;

  case 32: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE attr_name_list RBRACE  */
#line 323 "yacc_sql.y"
    {
      ((*yyvalp).sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = ((*yyvalp).sql_node)->create_index;
      create_index.index_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.string);
      create_index.relation_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.string);
      create_index.attribute_names.swap(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.attr_name_list));
      create_index.is_unique = false;
      free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.string));
      free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.string));
      free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.attr_name_list));
    }
#line 1761 "yacc_sql.cpp"
    break;

  case 33: /* create_index_stmt: CREATE UNIQUE INDEX ID ON ID LBRACE attr_name_list RBRACE  */
#line 336 "yacc_sql.y"
    {
        ((*yyvalp).sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
        CreateIndexSqlNode& create_index = ((*yyvalp).sql_node)->create_index;
        create_index.index_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.string);
        create_index.relation_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.string);
        create_index.attribute_names.swap(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.attr_name_list));
        create_index.is_unique = true;
        free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.string));
        free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.string));
        free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.attr_name_list));
    }
#line 1777 "yacc_sql.cpp"
    break;

  case 34: /* attr_name_list: index_attr index_attr_name_list  */
#line 349 "yacc_sql.y"
                                    {
      if((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.index_attr_name_list) != nullptr) {
        ((*yyvalp).attr_name_list) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.index_attr_name_list);
      } else {
        ((*yyvalp).attr_name_list) = new std::vector<IndexAttr>;
      }
      ((*yyvalp).attr_name_list)->push_back(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.index_attr));
      delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.index_attr);
    }
#line 1791 "yacc_sql.cpp"
    break;

  case 35: /* index_attr: ID  */
#line 360 "yacc_sql.y"
     {
    ((*yyvalp).index_attr) = new IndexAttr;
    ((*yyvalp).index_attr)->attribute_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string);
    free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
  }
#line 1801 "yacc_sql.cpp"
    break;

  case 36: /* index_attr_name_list: %empty  */
#line 368 "yacc_sql.y"
    {
      ((*yyvalp).index_attr_name_list) = nullptr;
    }
#line 1809 "yacc_sql.cpp"
    break;

  case 37: /* index_attr_name_list: COMMA index_attr index_attr_name_list  */
#line 371 "yacc_sql.y"
                                            {
      if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.index_attr_name_list) != nullptr) {
        ((*yyvalp).index_attr_name_list) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.index_attr_name_list);
      } else {
        ((*yyvalp).index_attr_name_list) = new std::vector<IndexAttr>;
      }

      ((*yyvalp).index_attr_name_list)->emplace_back(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.index_attr));
      delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.index_attr);
    }
#line 1824 "yacc_sql.cpp"
    break;

  case 38: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 385 "yacc_sql.y"
    {
      ((*yyvalp).sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      ((*yyvalp).sql_node)->drop_index.index_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string);
      ((*yyvalp).sql_node)->drop_index.relation_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string);
      free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string));
      free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
    }
#line 1836 "yacc_sql.cpp"
    break;

  case 39: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE  */
#line 395 "yacc_sql.y"
    {
      ((*yyvalp).sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = ((*yyvalp).sql_node)->create_table;
      create_table.relation_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.string);
      free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.string));

      std::vector<AttrInfoSqlNode> *src_attrs = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
      }
      create_table.attr_infos.emplace_back(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.attr_info);
    }
#line 1856 "yacc_sql.cpp"
    break;

  case 40: /* attr_def_list: %empty  */
#line 413 "yacc_sql.y"
    {
      ((*yyvalp).attr_infos) = nullptr;
    }
#line 1864 "yacc_sql.cpp"
    break;

  case 41: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 417 "yacc_sql.y"
    {
      if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.attr_infos) != nullptr) {
        ((*yyvalp).attr_infos) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.attr_infos);
      } else {
        ((*yyvalp).attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      ((*yyvalp).attr_infos)->emplace_back(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.attr_info));
      delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.attr_info);
    }
#line 1878 "yacc_sql.cpp"
    break;

  case 42: /* attr_def: ID type LBRACE number RBRACE null  */
#line 430 "yacc_sql.y"
                                      {
      ((*yyvalp).attr_info) = new AttrInfoSqlNode;
      ((*yyvalp).attr_info)->type = (AttrType)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.number);
      ((*yyvalp).attr_info)->name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.string);
      assert((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.number) == CHARS && "Expect char(number)");
      if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.null)) {
        ((*yyvalp).attr_info)->length = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.number) + 10;
      } else {
        ((*yyvalp).attr_info)->length = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.number);
      }
      ((*yyvalp).attr_info)->is_null = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.null);
      free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.string));
    }
#line 1896 "yacc_sql.cpp"
    break;

  case 43: /* attr_def: ID type null  */
#line 443 "yacc_sql.y"
                   {
      ((*yyvalp).attr_info) = new AttrInfoSqlNode;
      ((*yyvalp).attr_info)->type = (AttrType) (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.number);
      ((*yyvalp).attr_info)->name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string);
      if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.number) == CHARS && (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.null)) {
        ((*yyvalp).attr_info)->length = 10;
      } else {
        ((*yyvalp).attr_info)->length = 4;
      }
      if(((*yyvalp).attr_info)->type == AttrType::TEXT) {
        ((*yyvalp).attr_info)->length = 65535; // need to change
      }
      ((*yyvalp).attr_info)->is_null = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.null);
      free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string));
    }
#line 1916 "yacc_sql.cpp"
    break;

  case 44: /* null: %empty  */
#line 462 "yacc_sql.y"
  {
    ((*yyvalp).null) = true;
  }
#line 1924 "yacc_sql.cpp"
    break;

  case 45: /* null: OB_NULL  */
#line 465 "yacc_sql.y"
            {
    ((*yyvalp).null) = true;
  }
#line 1932 "yacc_sql.cpp"
    break;

  case 46: /* null: NOT OB_NULL  */
#line 468 "yacc_sql.y"
                {
    // Note that we do NOT need to deal with `NOT NULL` here
    // Since this property will be enable if NULL is not explicitly declared
    ((*yyvalp).null) = false;
  }
#line 1942 "yacc_sql.cpp"
    break;

  case 47: /* number: NUMBER  */
#line 475 "yacc_sql.y"
           { ((*yyvalp).number) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.number); }
#line 1948 "yacc_sql.cpp"
    break;

  case 48: /* type: INT_T  */
#line 479 "yacc_sql.y"
               { ((*yyvalp).number) = INTS; }
#line 1954 "yacc_sql.cpp"
    break;

  case 49: /* type: TEXT_T  */
#line 480 "yacc_sql.y"
                 { ((*yyvalp).number) = TEXT; }
#line 1960 "yacc_sql.cpp"
    break;

  case 50: /* type: STRING_T  */
#line 481 "yacc_sql.y"
               { ((*yyvalp).number) = CHARS; }
#line 1966 "yacc_sql.cpp"
    break;

  case 51: /* type: FLOAT_T  */
#line 482 "yacc_sql.y"
               { ((*yyvalp).number) = FLOATS; }
#line 1972 "yacc_sql.cpp"
    break;

  case 52: /* type: DATE_T  */
#line 483 "yacc_sql.y"
               { ((*yyvalp).number) = DATE; }
#line 1978 "yacc_sql.cpp"
    break;

  case 53: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 487 "yacc_sql.y"
    {
      ((*yyvalp).sql_node) = new ParsedSqlNode(SCF_INSERT);
      ((*yyvalp).sql_node)->insertion.relation_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.string);
      if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.value_list) != nullptr) {
        ((*yyvalp).sql_node)->insertion.values.swap(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.value_list));
      }
      ((*yyvalp).sql_node)->insertion.values.emplace_back(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.value));
      std::reverse(((*yyvalp).sql_node)->insertion.values.begin(), ((*yyvalp).sql_node)->insertion.values.end());
      delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.value);
      free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.string));
    }
#line 1994 "yacc_sql.cpp"
    break;

  case 54: /* value_list: %empty  */
#line 502 "yacc_sql.y"
    {
      ((*yyvalp).value_list) = nullptr;
    }
#line 2002 "yacc_sql.cpp"
    break;

  case 55: /* value_list: COMMA value value_list  */
#line 505 "yacc_sql.y"
                              { 
      if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.value_list) != nullptr) {
        ((*yyvalp).value_list) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.value_list);
      } else {
        ((*yyvalp).value_list) = new std::vector<Value>;
      }
      ((*yyvalp).value_list)->emplace_back(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.value));
      delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.value);
    }
#line 2016 "yacc_sql.cpp"
    break;

  case 56: /* value: NUMBER  */
#line 516 "yacc_sql.y"
           {
      ((*yyvalp).value) = new Value(static_cast<int>((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.number)));
      (*yylocp) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc);
    }
#line 2025 "yacc_sql.cpp"
    break;

  case 57: /* value: FLOAT  */
#line 520 "yacc_sql.y"
            {
      ((*yyvalp).value) = new Value(static_cast<float>((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.floats)));
      (*yylocp) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc);
    }
#line 2034 "yacc_sql.cpp"
    break;

  case 58: /* value: SSS  */
#line 524 "yacc_sql.y"
          {
      /* This is to eliminate the double/single quotes from the input string */
      char *tmp = common::substr((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), 1, strlen((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string)) - 2);
      ((*yyvalp).value) = new Value(tmp);
      free(tmp);
    }
#line 2045 "yacc_sql.cpp"
    break;

  case 59: /* value: DATE_STR  */
#line 530 "yacc_sql.y"
               {
      char *tmp = common::substr((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), 1, strlen((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string)) - 2);
      /* Note the length here is by default 10 */
      ((*yyvalp).value) = new Value(DATE, tmp);
      free(tmp);
    }
#line 2056 "yacc_sql.cpp"
    break;

  case 60: /* value: OB_NULL  */
#line 536 "yacc_sql.y"
              {
      // Note that we can not get the actual schema of this column right here
      // Will adjust the value to the actual type later
      ((*yyvalp).value) = new Value(0);
      ((*yyvalp).value)->set_null();
    }
#line 2067 "yacc_sql.cpp"
    break;

  case 61: /* delete_stmt: DELETE FROM ID where  */
#line 545 "yacc_sql.y"
    {
      ((*yyvalp).sql_node) = new ParsedSqlNode(SCF_DELETE);
      ((*yyvalp).sql_node)->deletion.relation_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.string);
      if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.condition_list) != nullptr) {
        ((*yyvalp).sql_node)->deletion.conditions.swap(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.condition_list));
        delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.condition_list);
      }
      free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.string));
    }
#line 2081 "yacc_sql.cpp"
    break;

  case 62: /* update_stmt: UPDATE ID SET ID EQ value update_value_list where  */
#line 557 "yacc_sql.y"
    {
      ((*yyvalp).sql_node) = new ParsedSqlNode(SCF_UPDATE);
      ((*yyvalp).sql_node)->update.relation_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yysemantics.yyval.string);

      UpdateValueNode node;
      node.attribute_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.string);
      node.value = *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.value);

      ((*yyvalp).sql_node)->update.update_values.emplace_back(node);

      if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.update_value_list) != nullptr) {
      	((*yyvalp).sql_node)->update.update_values.insert(((*yyvalp).sql_node)->update.update_values.end(), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.update_value_list)->begin(), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.update_value_list)->end());
	delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.update_value_list);
      }

      if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.condition_list)!= nullptr) {
        ((*yyvalp).sql_node)->update.conditions.swap(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.condition_list));
        delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.condition_list);
      }
      free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yysemantics.yyval.string));
      free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.string));
    }
#line 2108 "yacc_sql.cpp"
    break;

  case 63: /* update_stmt: UPDATE ID SET ID EQ LBRACE select_stmt RBRACE update_value_list where  */
#line 580 "yacc_sql.y"
    {
        ((*yyvalp).sql_node) = new ParsedSqlNode(SCF_UPDATE);
        ((*yyvalp).sql_node)->update.relation_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-8)].yystate.yysemantics.yyval.string);

        UpdateValueNode node;
        node.attribute_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yysemantics.yyval.string);
        node.sub_query = new SelectSqlNode((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.sql_node)->selection);

        ((*yyvalp).sql_node)->update.update_values.emplace_back(node);

        if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.update_value_list) != nullptr) {
            ((*yyvalp).sql_node)->update.update_values.insert(((*yyvalp).sql_node)->update.update_values.end(), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.update_value_list)->begin(), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.update_value_list)->end());
    	    delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.update_value_list);
        }

        if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.condition_list)!= nullptr) {
            ((*yyvalp).sql_node)->update.conditions.swap(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.condition_list));
            delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.condition_list);
        }
        free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-8)].yystate.yysemantics.yyval.string));
        free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yysemantics.yyval.string));
    }
#line 2135 "yacc_sql.cpp"
    break;

  case 64: /* update_value_list: %empty  */
#line 606 "yacc_sql.y"
    {
      ((*yyvalp).update_value_list) = nullptr;
    }
#line 2143 "yacc_sql.cpp"
    break;

  case 65: /* update_value_list: COMMA ID EQ value update_value_list  */
#line 609 "yacc_sql.y"
                                           {
      if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.update_value_list) != nullptr) {
	((*yyvalp).update_value_list) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.update_value_list);
      } else {
	((*yyvalp).update_value_list) = new std::vector<UpdateValueNode>;
      }
      UpdateValueNode node;
      node.attribute_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.string);
      node.value = *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.value);
      ((*yyvalp).update_value_list)->emplace_back(node);
      delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.string);
      delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.value);
    }
#line 2161 "yacc_sql.cpp"
    break;

  case 66: /* update_value_list: COMMA ID EQ LBRACE select_stmt RBRACE update_value_list  */
#line 622 "yacc_sql.y"
                                                               {
      if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.update_value_list) != nullptr) {
      	((*yyvalp).update_value_list) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.update_value_list);
      } else {
      	((*yyvalp).update_value_list) = new std::vector<UpdateValueNode>;
      }
      UpdateValueNode node;
      node.attribute_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.string);
      node.sub_query = new SelectSqlNode((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.sql_node)->selection);
      ((*yyvalp).update_value_list)->emplace_back(node);
      delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.string);
      delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.sql_node);
    }
#line 2179 "yacc_sql.cpp"
    break;

  case 67: /* select_stmt: CREATE TABLE ID AS select_stmt  */
#line 640 "yacc_sql.y"
                                   {
      ((*yyvalp).sql_node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.sql_node);
      ((*yyvalp).sql_node)->selection.create_table_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string);
    }
#line 2188 "yacc_sql.cpp"
    break;

  case 68: /* select_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE select_stmt  */
#line 646 "yacc_sql.y"
    {
      ((*yyvalp).sql_node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.sql_node);
      ((*yyvalp).sql_node)->selection.create_table_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.string);

      std::vector<AttrInfoSqlNode> *src_attrs = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.attr_infos);

      if (src_attrs != nullptr) {
        ((*yyvalp).sql_node)->selection.attr_infos.swap(*src_attrs);
      }
      ((*yyvalp).sql_node)->selection.attr_infos.emplace_back(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.attr_info));
      std::reverse(((*yyvalp).sql_node)->selection.attr_infos.begin(), ((*yyvalp).sql_node)->selection.attr_infos.end());
      delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.attr_info);
    }
#line 2206 "yacc_sql.cpp"
    break;

  case 69: /* select_stmt: SELECT select_attr FROM ID option_as rel_list where order_by_clause group_by_clause having  */
#line 661 "yacc_sql.y"
    {
      ((*yyvalp).sql_node) = new ParsedSqlNode(SCF_SELECT);

      if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-8)].yystate.yysemantics.yyval.rel_attr_list) != nullptr) {
        ((*yyvalp).sql_node)->selection.attributes.swap(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-8)].yystate.yysemantics.yyval.rel_attr_list));
        delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-8)].yystate.yysemantics.yyval.rel_attr_list);
      }

      if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.relation_list) != nullptr) {
        ((*yyvalp).sql_node)->selection.relations.swap(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.relation_list));
        delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.relation_list);
      }

      RelationSqlNode relation;
      relation.relation_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yysemantics.yyval.string);
      free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yysemantics.yyval.string));

      if((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.string) != nullptr) {
      	relation.alias_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.string);
      	free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.string));
      }

      ((*yyvalp).sql_node)->selection.relations.push_back(relation);
      std::reverse(((*yyvalp).sql_node)->selection.relations.begin(), ((*yyvalp).sql_node)->selection.relations.end());

      if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.condition_list) != nullptr) {
        ((*yyvalp).sql_node)->selection.conditions.swap(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.condition_list));
        delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.condition_list);
      }

      if((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.order_by_list_type) != nullptr) {
        ((*yyvalp).sql_node)->selection.order_bys.insert(((*yyvalp).sql_node)->selection.order_bys.end(),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.order_by_list_type)->begin(),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.order_by_list_type)->end());
        delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.order_by_list_type);
      }

      if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.group_by_list_type) != nullptr) {
        ((*yyvalp).sql_node)->selection.group_bys.swap(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.group_by_list_type));
      }

      if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.condition) != nullptr) {
        ((*yyvalp).sql_node)->selection.having = *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.condition);
        delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.condition);
      } else {
        ConditionSqlNode having;
        // To mark the absence of having condition
        having.left_value.set_type(UNDEFINED);
        having.right_value.set_type(UNDEFINED);
        ((*yyvalp).sql_node)->selection.having = having;
      }
    }
#line 2261 "yacc_sql.cpp"
    break;

  case 70: /* select_stmt: SELECT select_attr FROM ID inner_join_constr inner_join_list where order_by_clause  */
#line 712 "yacc_sql.y"
        {
          ((*yyvalp).sql_node) = new ParsedSqlNode(SCF_SELECT);
          if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yysemantics.yyval.rel_attr_list) != nullptr) {
            ((*yyvalp).sql_node)->selection.attributes.swap(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yysemantics.yyval.rel_attr_list));
            delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yysemantics.yyval.rel_attr_list);
          }
          RelationSqlNode relation_node;
          relation_node.relation_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.string);
          ((*yyvalp).sql_node)->selection.relations.push_back(relation_node);
          delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.string);

          RelationSqlNode join_relation_node;
          join_relation_node.relation_name = (*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.join_list))[0].relation_name;
          ((*yyvalp).sql_node)->selection.relations.push_back(join_relation_node);
          ((*yyvalp).sql_node)->selection.conditions.swap((*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.join_list))[0].conditions);
          delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.join_list);

          if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.join_list) != nullptr) {
            std::reverse((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.join_list)->begin(), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.join_list)->end());
	    for (auto &join_relation : *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.join_list)) {
	      RelationSqlNode join_relation_node;
              join_relation_node.relation_name = join_relation.relation_name;
	      ((*yyvalp).sql_node)->selection.relations.push_back(join_relation_node);
	      for (auto &condition : join_relation.conditions) {
	      	((*yyvalp).sql_node)->selection.conditions.emplace_back(condition);
	      }
	    }
	    delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.join_list);
	  }

          if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.condition_list) != nullptr) {
            ((*yyvalp).sql_node)->selection.conditions.insert(((*yyvalp).sql_node)->selection.conditions.end(),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.condition_list)->begin(),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.condition_list)->end());
            delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.condition_list);
          }

          if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.order_by_list_type) != nullptr) {
	    ((*yyvalp).sql_node)->selection.order_bys.insert(((*yyvalp).sql_node)->selection.order_bys.end(),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.order_by_list_type)->begin(),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.order_by_list_type)->end());
	    delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.order_by_list_type);
	  }
        }
#line 2306 "yacc_sql.cpp"
    break;

  case 71: /* inner_join_constr: INNER JOIN ID ON condition_list  */
#line 756 "yacc_sql.y"
    {
      ((*yyvalp).join_list) = new std::vector<JoinSqlNode>;
      JoinSqlNode join_node;
      join_node.relation_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string);
      join_node.conditions.swap(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.condition_list));
      ((*yyvalp).join_list)->emplace_back(join_node);
      free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string));
    }
#line 2319 "yacc_sql.cpp"
    break;

  case 72: /* inner_join_list: %empty  */
#line 767 "yacc_sql.y"
    {
      ((*yyvalp).join_list) = nullptr;
    }
#line 2327 "yacc_sql.cpp"
    break;

  case 73: /* inner_join_list: INNER JOIN ID ON condition_list inner_join_list  */
#line 771 "yacc_sql.y"
    {
      if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.join_list) != nullptr) {
	((*yyvalp).join_list) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.join_list);
      } else {
	((*yyvalp).join_list) = new std::vector<JoinSqlNode>;
      }
      JoinSqlNode join_node;
      join_node.relation_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.string);
      join_node.conditions.swap(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.condition_list));
      ((*yyvalp).join_list)->emplace_back(join_node);
      free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.string));
    }
#line 2344 "yacc_sql.cpp"
    break;

  case 74: /* group_by_clause: %empty  */
#line 786 "yacc_sql.y"
    {
      ((*yyvalp).group_by_list_type) = nullptr;
    }
#line 2352 "yacc_sql.cpp"
    break;

  case 75: /* group_by_clause: GROUP BY group_by_list  */
#line 789 "yacc_sql.y"
                             {
      assert((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.group_by_list_type) != nullptr && "Expect `group_by_list` not to be null");
      ((*yyvalp).group_by_list_type) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.group_by_list_type);
    }
#line 2361 "yacc_sql.cpp"
    break;

  case 76: /* group_by_list: rel_attr  */
#line 796 "yacc_sql.y"
             {
      assert((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.rel_attr) != nullptr && "Expect `rel_attr` not to be null");

      ((*yyvalp).group_by_list_type) = new std::vector<RelAttrSqlNode>;
      ((*yyvalp).group_by_list_type)->emplace_back(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.rel_attr));

      delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.rel_attr);
    }
#line 2374 "yacc_sql.cpp"
    break;

  case 77: /* group_by_list: rel_attr COMMA group_by_list  */
#line 804 "yacc_sql.y"
                                   {
      assert((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.rel_attr) != nullptr && (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.group_by_list_type) != nullptr && "Expect all item not to be null");

      if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.group_by_list_type) != nullptr) {
        ((*yyvalp).group_by_list_type) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.group_by_list_type);
      } else {
        ((*yyvalp).group_by_list_type) = new std::vector<RelAttrSqlNode>;
      }

      // Note that the order of group by item should be reversed
      // But since the order does not matter, just keep it simple at present
      ((*yyvalp).group_by_list_type)->emplace_back(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.rel_attr));

      delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.rel_attr);
    }
#line 2394 "yacc_sql.cpp"
    break;

  case 78: /* having: %empty  */
#line 822 "yacc_sql.y"
    {
      ((*yyvalp).condition) = nullptr;
    }
#line 2402 "yacc_sql.cpp"
    break;

  case 79: /* having: HAVING condition  */
#line 825 "yacc_sql.y"
                       {
      assert((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.condition) != nullptr && "Expect having condition not to be nullptr");
      ((*yyvalp).condition) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.condition);
    }
#line 2411 "yacc_sql.cpp"
    break;

  case 80: /* order_by_clause: %empty  */
#line 832 "yacc_sql.y"
    {
	((*yyvalp).order_by_list_type) = nullptr;
    }
#line 2419 "yacc_sql.cpp"
    break;

  case 81: /* order_by_clause: ORDER BY order_by_list  */
#line 835 "yacc_sql.y"
                             {
        ((*yyvalp).order_by_list_type) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.order_by_list_type);
    }
#line 2427 "yacc_sql.cpp"
    break;

  case 82: /* order_by_list: order_by_item  */
#line 841 "yacc_sql.y"
                  {
        ((*yyvalp).order_by_list_type) = new std::vector<OrderBySqlNode>;
        ((*yyvalp).order_by_list_type)->insert(((*yyvalp).order_by_list_type)->begin(), (*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.order_by_list_type)).begin(), (*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.order_by_list_type)).end());
        delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.order_by_list_type);
    }
#line 2437 "yacc_sql.cpp"
    break;

  case 83: /* order_by_list: order_by_item COMMA order_by_list  */
#line 846 "yacc_sql.y"
                                        {
        if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.order_by_list_type) != nullptr) {
            ((*yyvalp).order_by_list_type) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.order_by_list_type);
        } else {
            ((*yyvalp).order_by_list_type) = new std::vector<OrderBySqlNode>;
        }
      ((*yyvalp).order_by_list_type)->insert(((*yyvalp).order_by_list_type)->begin(), (*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.order_by_list_type)).begin(), (*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.order_by_list_type)).end());
      delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.order_by_list_type);
    }
#line 2451 "yacc_sql.cpp"
    break;

  case 84: /* order_by_item: rel_attr  */
#line 858 "yacc_sql.y"
             {
        ((*yyvalp).order_by_list_type) = new std::vector<OrderBySqlNode>;
        OrderBySqlNode item;
        item.order_by_attributes.emplace_back(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.rel_attr));
        item.order_by_asc.emplace_back(true);
        ((*yyvalp).order_by_list_type)->emplace_back(item);
        delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.rel_attr);
    }
#line 2464 "yacc_sql.cpp"
    break;

  case 85: /* order_by_item: rel_attr ASC  */
#line 866 "yacc_sql.y"
                   {
         	((*yyvalp).order_by_list_type) = new std::vector<OrderBySqlNode>;
                OrderBySqlNode item;
                item.order_by_attributes.emplace_back(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.rel_attr));
                item.order_by_asc.emplace_back(true);
                ((*yyvalp).order_by_list_type)->emplace_back(item);
                delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.rel_attr);
    }
#line 2477 "yacc_sql.cpp"
    break;

  case 86: /* order_by_item: rel_attr DESC  */
#line 874 "yacc_sql.y"
                    {
                ((*yyvalp).order_by_list_type) = new std::vector<OrderBySqlNode>;
                OrderBySqlNode item;
                item.order_by_attributes.emplace_back(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.rel_attr));
                item.order_by_asc.emplace_back(false);
                ((*yyvalp).order_by_list_type)->emplace_back(item);
                delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.rel_attr);
    }
#line 2490 "yacc_sql.cpp"
    break;

  case 87: /* calc_stmt: CALC expression_list  */
#line 886 "yacc_sql.y"
    {
      ((*yyvalp).sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.expression_list)->begin(), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.expression_list)->end());
      ((*yyvalp).sql_node)->calc.expressions.swap(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.expression_list));
      delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.expression_list);
    }
#line 2501 "yacc_sql.cpp"
    break;

  case 88: /* expression_list: expression  */
#line 896 "yacc_sql.y"
    {
      ((*yyvalp).expression_list) = new std::vector<Expression*>;
      ((*yyvalp).expression_list)->emplace_back((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.expression));
    }
#line 2510 "yacc_sql.cpp"
    break;

  case 89: /* expression_list: expression COMMA expression_list  */
#line 901 "yacc_sql.y"
    {
      if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.expression_list) != nullptr) {
        ((*yyvalp).expression_list) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.expression_list);
      } else {
        ((*yyvalp).expression_list) = new std::vector<Expression *>;
      }
      ((*yyvalp).expression_list)->emplace_back((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.expression));
    }
#line 2523 "yacc_sql.cpp"
    break;

  case 90: /* expression: expression '+' expression  */
#line 912 "yacc_sql.y"
                              {
      ((*yyvalp).expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.expression), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.expression), sql_string, &(*yylocp));
    }
#line 2531 "yacc_sql.cpp"
    break;

  case 91: /* expression: expression '-' expression  */
#line 915 "yacc_sql.y"
                                {
      ((*yyvalp).expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.expression), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.expression), sql_string, &(*yylocp));
    }
#line 2539 "yacc_sql.cpp"
    break;

  case 92: /* expression: expression '*' expression  */
#line 918 "yacc_sql.y"
                                {
      ((*yyvalp).expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.expression), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.expression), sql_string, &(*yylocp));
    }
#line 2547 "yacc_sql.cpp"
    break;

  case 93: /* expression: expression '/' expression  */
#line 921 "yacc_sql.y"
                                {
      ((*yyvalp).expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.expression), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.expression), sql_string, &(*yylocp));
    }
#line 2555 "yacc_sql.cpp"
    break;

  case 94: /* expression: LBRACE expression RBRACE  */
#line 924 "yacc_sql.y"
                               {
      ((*yyvalp).expression) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.expression);
      ((*yyvalp).expression)->set_name(token_name(sql_string, &(*yylocp)));
    }
#line 2564 "yacc_sql.cpp"
    break;

  case 95: /* expression: '-' expression  */
#line 928 "yacc_sql.y"
                                  {
      ((*yyvalp).expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.expression), nullptr, sql_string, &(*yylocp));
    }
#line 2572 "yacc_sql.cpp"
    break;

  case 96: /* expression: value  */
#line 931 "yacc_sql.y"
            {
      ((*yyvalp).expression) = new ValueExpr(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.value));
      ((*yyvalp).expression)->set_name(token_name(sql_string, &(*yylocp)));
      delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.value);
    }
#line 2582 "yacc_sql.cpp"
    break;

  case 97: /* expression: rel_attr  */
#line 936 "yacc_sql.y"
               {
      // The actual field will be parsed in select statement
      ((*yyvalp).expression) = new FieldExpr(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.rel_attr));
      ((*yyvalp).expression)->set_name(token_name(sql_string, &(*yylocp)));
    }
#line 2592 "yacc_sql.cpp"
    break;

  case 98: /* expression: ID_MINUS  */
#line 944 "yacc_sql.y"
               {
      char *ptr = strchr((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), '-');
      assert(ptr != nullptr && "Expect `ptr` not to be nullptr");
      *ptr = '\0';
      RelAttrSqlNode rel_attr;
      rel_attr.attribute_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string);
      rel_attr.aggregate_func = agg::NONE;
      FieldExpr *f_expr = new FieldExpr(rel_attr);
      int v = atoi(ptr + 1);
      Value value;
      value.set_int(v);
      ValueExpr *value_expr = new ValueExpr(value);
      ((*yyvalp).expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, f_expr, value_expr, sql_string, &(*yylocp));
    }
#line 2611 "yacc_sql.cpp"
    break;

  case 99: /* expression: ID_DOT_ID_MINUS  */
#line 958 "yacc_sql.y"
                      {
          char *ptr = strchr((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), '-');
          assert(ptr != nullptr && "Expect `ptr` not to be nullptr");
          *ptr = '\0';
          char *ptr1 = strchr((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), '.');
          *ptr1 = '\0';
          RelAttrSqlNode rel_attr;
          rel_attr.relation_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string);
          rel_attr.attribute_name = (ptr1 + 1);
          rel_attr.aggregate_func = agg::NONE;
          FieldExpr *f_expr = new FieldExpr(rel_attr);
          int v = atoi(ptr + 1);
          Value value;
          value.set_int(v);
          ValueExpr *value_expr = new ValueExpr(value);
          ((*yyvalp).expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, f_expr, value_expr, sql_string, &(*yylocp));
        }
#line 2633 "yacc_sql.cpp"
    break;

  case 100: /* expression: MIN_MINUS  */
#line 976 "yacc_sql.y"
                {
          char *ptr = strchr((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), '-');
          assert(ptr != nullptr && "Expect `ptr` not to be nullptr");
          *(ptr - 1) = '\0';
          RelAttrSqlNode rel_attr;
          rel_attr.attribute_name = ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string) + 4);
          rel_attr.aggregate_func = AGG_MIN;
          FieldExpr *f_expr = new FieldExpr(rel_attr);
          int v = atoi(ptr + 1);
          Value value;
          value.set_int(v);
          ValueExpr *value_expr = new ValueExpr(value);
          ((*yyvalp).expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, f_expr, value_expr, sql_string, &(*yylocp));
        }
#line 2652 "yacc_sql.cpp"
    break;

  case 101: /* expression: MAX_MINUS  */
#line 990 "yacc_sql.y"
                {
   char *ptr = strchr((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), '-');
             assert(ptr != nullptr && "Expect `ptr` not to be nullptr");
             *(ptr - 1) = '\0';
             RelAttrSqlNode rel_attr;
             rel_attr.attribute_name = ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string) + 4);
             rel_attr.aggregate_func = AGG_MAX;
             FieldExpr *f_expr = new FieldExpr(rel_attr);
             int v = atoi(ptr + 1);
             Value value;
             value.set_int(v);
             ValueExpr *value_expr = new ValueExpr(value);
             ((*yyvalp).expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, f_expr, value_expr, sql_string, &(*yylocp));
    }
#line 2671 "yacc_sql.cpp"
    break;

  case 102: /* expression: SUM_MINUS  */
#line 1004 "yacc_sql.y"
                {
   char *ptr = strchr((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), '-');
             assert(ptr != nullptr && "Expect `ptr` not to be nullptr");
             *(ptr - 1) = '\0';
             RelAttrSqlNode rel_attr;
             rel_attr.attribute_name = ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string) + 4);
             rel_attr.aggregate_func = AGG_SUM;
             FieldExpr *f_expr = new FieldExpr(rel_attr);
             int v = atoi(ptr + 1);
             Value value;
             value.set_int(v);
             ValueExpr *value_expr = new ValueExpr(value);
             ((*yyvalp).expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, f_expr, value_expr, sql_string, &(*yylocp));
    }
#line 2690 "yacc_sql.cpp"
    break;

  case 103: /* expression: AVG_MINUS  */
#line 1018 "yacc_sql.y"
                {
   char *ptr = strchr((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), '-');
             assert(ptr != nullptr && "Expect `ptr` not to be nullptr");
             *(ptr - 1) = '\0';
             RelAttrSqlNode rel_attr;
             rel_attr.attribute_name = ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string) + 4);
             rel_attr.aggregate_func = AGG_AVG;
             FieldExpr *f_expr = new FieldExpr(rel_attr);
             int v = atoi(ptr + 1);
             Value value;
             value.set_int(v);
             ValueExpr *value_expr = new ValueExpr(value);
             ((*yyvalp).expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, f_expr, value_expr, sql_string, &(*yylocp));
    }
#line 2709 "yacc_sql.cpp"
    break;

  case 104: /* expression: COUNT_MINUS  */
#line 1032 "yacc_sql.y"
                  {
   char *ptr = strchr((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), '-');
             assert(ptr != nullptr && "Expect `ptr` not to be nullptr");
             *(ptr - 1) = '\0';
             RelAttrSqlNode rel_attr;
             rel_attr.attribute_name = ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string) + 6);
             rel_attr.aggregate_func = AGG_COUNT;
             FieldExpr *f_expr = new FieldExpr(rel_attr);
             int v = atoi(ptr + 1);
             Value value;
             value.set_int(v);
             ValueExpr *value_expr = new ValueExpr(value);
             ((*yyvalp).expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, f_expr, value_expr, sql_string, &(*yylocp));
    }
#line 2728 "yacc_sql.cpp"
    break;

  case 105: /* option_as: %empty  */
#line 1050 "yacc_sql.y"
    {
      ((*yyvalp).string) = nullptr;
    }
#line 2736 "yacc_sql.cpp"
    break;

  case 106: /* option_as: AS ID  */
#line 1053 "yacc_sql.y"
            {
      ((*yyvalp).string) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string);
    }
#line 2744 "yacc_sql.cpp"
    break;

  case 107: /* option_as: ID  */
#line 1056 "yacc_sql.y"
         {
      ((*yyvalp).string) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string);
    }
#line 2752 "yacc_sql.cpp"
    break;

  case 108: /* select_attr: '*' option_as  */
#line 1062 "yacc_sql.y"
                  {
      ((*yyvalp).rel_attr_list) = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.relation_name  = "";
      attr.attribute_name = "*";
      attr.aggregate_func = agg::NONE;
      if((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string) != nullptr) {
      	attr.agg_valid_flag = false;
      	free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
      }
      ((*yyvalp).rel_attr_list)->emplace_back(attr);
    }
#line 2769 "yacc_sql.cpp"
    break;

  case 109: /* select_attr: expression_list  */
#line 1075 "yacc_sql.y"
                      {
      ((*yyvalp).rel_attr_list) = new std::vector<RelAttrSqlNode>;
      for (auto *expr : *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.expression_list)) {
        RelAttrSqlNode rel_attr;
        if (dynamic_cast<FieldExpr *>(expr) != nullptr) {
          // The expression is field expression
          rel_attr = dynamic_cast<FieldExpr *>(expr)->get_rel_attr();
        } else {
          rel_attr.expr_flag = true;
          rel_attr.expression = expr;
        }
        ((*yyvalp).rel_attr_list)->push_back(rel_attr);
      }
    }
#line 2788 "yacc_sql.cpp"
    break;

  case 110: /* select_attr: agg LBRACE rel_attr COMMA rel_attr RBRACE  */
#line 1091 "yacc_sql.y"
                                               {
      ((*yyvalp).rel_attr_list) = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.agg_valid_flag = false;
      ((*yyvalp).rel_attr_list)->emplace_back(attr);
    }
#line 2799 "yacc_sql.cpp"
    break;

  case 111: /* select_attr: agg LBRACE '*' COMMA rel_attr RBRACE  */
#line 1097 "yacc_sql.y"
                                            {
      ((*yyvalp).rel_attr_list) = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.agg_valid_flag = false;
      ((*yyvalp).rel_attr_list)->emplace_back(attr);
    }
#line 2810 "yacc_sql.cpp"
    break;

  case 112: /* agg: MIN  */
#line 1106 "yacc_sql.y"
        {
      ((*yyvalp).agg) = agg::AGG_MIN;
    }
#line 2818 "yacc_sql.cpp"
    break;

  case 113: /* agg: MAX  */
#line 1109 "yacc_sql.y"
          {
      ((*yyvalp).agg) = agg::AGG_MAX;
    }
#line 2826 "yacc_sql.cpp"
    break;

  case 114: /* agg: AVG  */
#line 1112 "yacc_sql.y"
          {
      ((*yyvalp).agg) = agg::AGG_AVG;
    }
#line 2834 "yacc_sql.cpp"
    break;

  case 115: /* agg: SUM  */
#line 1115 "yacc_sql.y"
          {
      ((*yyvalp).agg) = agg::AGG_SUM;
    }
#line 2842 "yacc_sql.cpp"
    break;

  case 116: /* agg: COUNT  */
#line 1118 "yacc_sql.y"
            {
      ((*yyvalp).agg) = agg::AGG_COUNT;
    }
#line 2850 "yacc_sql.cpp"
    break;

  case 117: /* rel_attr: ID option_as  */
#line 1124 "yacc_sql.y"
                 {
      ((*yyvalp).rel_attr) = new RelAttrSqlNode;
      ((*yyvalp).rel_attr)->relation_name = "";
      ((*yyvalp).rel_attr)->attribute_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.string);
      ((*yyvalp).rel_attr)->aggregate_func = agg::NONE;
      if((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string) != nullptr) {
      	((*yyvalp).rel_attr)->alias_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string);
      	free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
      }
      free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.string));
    }
#line 2866 "yacc_sql.cpp"
    break;

  case 118: /* rel_attr: ID DOT ID option_as  */
#line 1135 "yacc_sql.y"
                          {
      ((*yyvalp).rel_attr) = new RelAttrSqlNode;
      ((*yyvalp).rel_attr)->relation_name  = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.string);
      ((*yyvalp).rel_attr)->attribute_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.string);
      ((*yyvalp).rel_attr)->aggregate_func = agg::NONE;
      if((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string) != nullptr) {
        ((*yyvalp).rel_attr)->alias_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string);
        free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
      }
      free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.string));
      free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.string));
    }
#line 2883 "yacc_sql.cpp"
    break;

  case 119: /* rel_attr: ID DOT '*'  */
#line 1147 "yacc_sql.y"
                 {
      ((*yyvalp).rel_attr) = new RelAttrSqlNode;
      ((*yyvalp).rel_attr)->relation_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string);
      ((*yyvalp).rel_attr)->attribute_name = "*";
      ((*yyvalp).rel_attr)->aggregate_func = agg::NONE;
      free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string));
    }
#line 2895 "yacc_sql.cpp"
    break;

  case 120: /* rel_attr: agg LBRACE ID RBRACE option_as  */
#line 1155 "yacc_sql.y"
                                     {
      ((*yyvalp).rel_attr) = new RelAttrSqlNode;
      ((*yyvalp).rel_attr)->relation_name = "";
      ((*yyvalp).rel_attr)->attribute_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string);
      ((*yyvalp).rel_attr)->aggregate_func = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.agg);
      if((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string) != nullptr)
      {
      	((*yyvalp).rel_attr)->alias_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string);
      	free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
      }
      free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string));
    }
#line 2912 "yacc_sql.cpp"
    break;

  case 121: /* rel_attr: agg LBRACE ID DOT ID RBRACE option_as  */
#line 1167 "yacc_sql.y"
                                            {
      ((*yyvalp).rel_attr) = new RelAttrSqlNode;
      ((*yyvalp).rel_attr)->relation_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.string);
      ((*yyvalp).rel_attr)->attribute_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string);
      ((*yyvalp).rel_attr)->aggregate_func = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yysemantics.yyval.agg);
      if((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string) != nullptr) {
      	((*yyvalp).rel_attr)->alias_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string);
      	free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
      }
      free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.string));
      free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string));
    }
#line 2929 "yacc_sql.cpp"
    break;

  case 122: /* rel_attr: agg LBRACE '*' RBRACE option_as  */
#line 1179 "yacc_sql.y"
                                      {
      ((*yyvalp).rel_attr) = new RelAttrSqlNode;

      // Construct the aggregation attribute
      ((*yyvalp).rel_attr)->relation_name = "";
      ((*yyvalp).rel_attr)->attribute_name = "*";
      ((*yyvalp).rel_attr)->aggregate_func = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.agg);

      if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string) != nullptr) {
       ((*yyvalp).rel_attr)->alias_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string);
       free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
      }
    }
#line 2947 "yacc_sql.cpp"
    break;

  case 123: /* rel_attr: agg LBRACE RBRACE  */
#line 1194 "yacc_sql.y"
                        {
      ((*yyvalp).rel_attr) = new RelAttrSqlNode;
      ((*yyvalp).rel_attr)->agg_valid_flag = false;
    }
#line 2956 "yacc_sql.cpp"
    break;

  case 124: /* rel_list: %empty  */
#line 1202 "yacc_sql.y"
    {
      ((*yyvalp).relation_list) = nullptr;
    }
#line 2964 "yacc_sql.cpp"
    break;

  case 125: /* rel_list: COMMA ID option_as rel_list  */
#line 1205 "yacc_sql.y"
                                  {
      if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.relation_list) != nullptr) {
        ((*yyvalp).relation_list) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.relation_list);
      } else {
        ((*yyvalp).relation_list) = new std::vector<RelationSqlNode>;
      }
      RelationSqlNode relation;
      relation.relation_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string);
      if((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.string) != nullptr) {
      	relation.alias_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.string);
      		free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.string));
      }
      ((*yyvalp).relation_list)->push_back(relation);
      free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string));
    }
#line 2984 "yacc_sql.cpp"
    break;

  case 126: /* where: %empty  */
#line 1223 "yacc_sql.y"
    {
      ((*yyvalp).condition_list) = nullptr;
    }
#line 2992 "yacc_sql.cpp"
    break;

  case 127: /* where: WHERE condition_list  */
#line 1226 "yacc_sql.y"
                           {
      ((*yyvalp).condition_list) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.condition_list);
    }
#line 3000 "yacc_sql.cpp"
    break;

  case 128: /* condition_list: %empty  */
#line 1233 "yacc_sql.y"
    {
      ((*yyvalp).condition_list) = nullptr;
    }
#line 3008 "yacc_sql.cpp"
    break;

  case 129: /* condition_list: condition  */
#line 1236 "yacc_sql.y"
                {
      ((*yyvalp).condition_list) = new std::vector<ConditionSqlNode>;
      ((*yyvalp).condition_list)->emplace_back(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.condition));
      delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.condition);
    }
#line 3018 "yacc_sql.cpp"
    break;

  case 130: /* condition_list: condition AND condition_list  */
#line 1241 "yacc_sql.y"
                                   {
      ((*yyvalp).condition_list) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.condition_list);
      (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.condition)->is_and = true;
      ((*yyvalp).condition_list)->emplace_back(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.condition));
      delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.condition);
    }
#line 3029 "yacc_sql.cpp"
    break;

  case 131: /* condition_list: condition OR condition_list  */
#line 1247 "yacc_sql.y"
                                  {
      ((*yyvalp).condition_list) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.condition_list);
      (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.condition)->is_and = false;
      ((*yyvalp).condition_list)->emplace_back(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.condition));
      delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.condition);
    }
#line 3040 "yacc_sql.cpp"
    break;

  case 132: /* condition: expression comp_op expression  */
#line 1256 "yacc_sql.y"
                                  {
      FieldExpr *f_lhs = dynamic_cast<FieldExpr *>((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.expression));
      ValueExpr *v_lhs = dynamic_cast<ValueExpr *>((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.expression));
      FieldExpr *f_rhs = dynamic_cast<FieldExpr *>((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.expression));
      ValueExpr *v_rhs = dynamic_cast<ValueExpr *>((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.expression));

      ((*yyvalp).condition) = new ConditionSqlNode;

      if (f_lhs && f_rhs) {
        // Field comp Field
        ((*yyvalp).condition)->left_is_attr = 1;
        ((*yyvalp).condition)->right_is_attr = 1;

        ((*yyvalp).condition)->comp = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.comp);

        ((*yyvalp).condition)->left_attr = f_lhs->get_rel_attr();
        ((*yyvalp).condition)->right_attr = f_rhs->get_rel_attr();

        delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.expression);
        delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.expression);
      } else if (f_lhs && v_rhs) {
        // Field comp Value
        ((*yyvalp).condition)->left_is_attr = 1;
        ((*yyvalp).condition)->right_is_attr = 0;

        ((*yyvalp).condition)->comp = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.comp);

        ((*yyvalp).condition)->left_attr = f_lhs->get_rel_attr();
        ((*yyvalp).condition)->right_value = v_rhs->get_value();

        delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.expression);
        delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.expression);
      } else if (v_lhs && f_rhs) {
        // Value comp Field
        ((*yyvalp).condition)->left_is_attr = 0;
        ((*yyvalp).condition)->right_is_attr = 1;

        ((*yyvalp).condition)->comp = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.comp);

        ((*yyvalp).condition)->left_value = v_lhs->get_value();
        ((*yyvalp).condition)->right_attr = f_rhs->get_rel_attr();

        delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.expression);
        delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.expression);
      } else if (v_lhs && v_rhs) {
        // Value comp Value
        ((*yyvalp).condition)->left_is_attr = 0;
        ((*yyvalp).condition)->right_is_attr = 0;

        ((*yyvalp).condition)->comp = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.comp);

        ((*yyvalp).condition)->left_value = v_lhs->get_value();
        ((*yyvalp).condition)->right_value = v_rhs->get_value();

        delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.expression);
        delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.expression);
      } else if (f_lhs && (!f_rhs && !v_rhs)) {
        // Field comp Expression
        ((*yyvalp).condition)->left_is_attr = 1;
        ((*yyvalp).condition)->right_is_attr = 0;

        ((*yyvalp).condition)->comp = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.comp);

        ((*yyvalp).condition)->left_attr = f_lhs->get_rel_attr();
        ((*yyvalp).condition)->right_expr = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.expression);

        delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.expression);
      } else if (v_lhs && (!f_rhs && !v_rhs)) {
        // Value comp Expression
        ((*yyvalp).condition)->left_is_attr = 0;
        ((*yyvalp).condition)->right_is_attr = 0;

        ((*yyvalp).condition)->comp = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.comp);

        ((*yyvalp).condition)->left_value = v_lhs->get_value();
        ((*yyvalp).condition)->right_expr = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.expression);

        delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.expression);
      } else if ((!f_lhs && !v_lhs) && f_rhs) {
        // Expression comp Field
        ((*yyvalp).condition)->left_is_attr = 0;
        ((*yyvalp).condition)->right_is_attr = 1;

        ((*yyvalp).condition)->comp = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.comp);

        ((*yyvalp).condition)->left_expr = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.expression);
        ((*yyvalp).condition)->right_attr = f_rhs->get_rel_attr();

        delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.expression);
      } else if ((!f_lhs && !v_lhs) && v_rhs) {
        // Expression comp Value
        ((*yyvalp).condition)->left_is_attr = 0;
        ((*yyvalp).condition)->right_is_attr = 0;

        ((*yyvalp).condition)->comp = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.comp);

        ((*yyvalp).condition)->left_expr = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.expression);
        ((*yyvalp).condition)->right_value = v_rhs->get_value();

        delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.expression);
      } else if (!f_lhs && !v_lhs && !f_rhs && !v_rhs) {
        // Expression comp Expression
        ((*yyvalp).condition)->left_is_attr = 0;
        ((*yyvalp).condition)->right_is_attr = 0;

        ((*yyvalp).condition)->comp = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.comp);

        ((*yyvalp).condition)->left_expr = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.expression);
        ((*yyvalp).condition)->right_expr = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.expression);
      } else {
        assert(false && "This path is impossible");
      }
    }
#line 3158 "yacc_sql.cpp"
    break;

  case 133: /* condition: expression in_op LBRACE select_stmt RBRACE  */
#line 1371 "yacc_sql.y"
    {
    FieldExpr *lhs = dynamic_cast<FieldExpr *>((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.expression));
          assert(lhs != nullptr && "Expect lhs to be `FieldExpr *`");
      ((*yyvalp).condition) = new ConditionSqlNode;
      ((*yyvalp).condition)->left_is_attr = 1;
      ((*yyvalp).condition)->left_attr = lhs->get_rel_attr();
      ((*yyvalp).condition)->right_is_attr = 2;
      ((*yyvalp).condition)->right_sub_select = new SelectSqlNode((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.sql_node)->selection);
      ((*yyvalp).condition)->comp = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.comp);
      delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.expression);
    }
#line 3174 "yacc_sql.cpp"
    break;

  case 134: /* condition: expression in_op LBRACE value value_list RBRACE  */
#line 1384 "yacc_sql.y"
    {
    FieldExpr *lhs = dynamic_cast<FieldExpr *>((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.expression));
          assert(lhs != nullptr && "Expect lhs to be `FieldExpr *`");
      ((*yyvalp).condition) = new ConditionSqlNode;
      ((*yyvalp).condition)->left_is_attr = 1;
      ((*yyvalp).condition)->left_attr = lhs->get_rel_attr();
      ((*yyvalp).condition)->right_is_attr = 3;
      if((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.value_list) != nullptr) {
	((*yyvalp).condition)->right_value_list.swap(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.value_list));
	delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.value_list);
      }
      ((*yyvalp).condition)->right_value_list.push_back(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.value));
      ((*yyvalp).condition)->comp = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.comp);
      delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.expression);
      delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.value);
    }
#line 3195 "yacc_sql.cpp"
    break;

  case 135: /* condition: expression comp_op LBRACE select_stmt RBRACE  */
#line 1402 "yacc_sql.y"
    {
      FieldExpr *lhs = dynamic_cast<FieldExpr *>((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.expression));
      assert(lhs != nullptr && "Expect lhs to be `FieldExpr *`");
      ((*yyvalp).condition) = new ConditionSqlNode;
      ((*yyvalp).condition)->left_is_attr = 1;
      ((*yyvalp).condition)->left_attr = lhs->get_rel_attr();
      ((*yyvalp).condition)->right_is_attr = 2;
      ((*yyvalp).condition)->right_sub_select = new SelectSqlNode((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.sql_node)->selection);
      ((*yyvalp).condition)->comp = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.comp);
      delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.expression);
    }
#line 3211 "yacc_sql.cpp"
    break;

  case 136: /* condition: expression comp_op LBRACE value COMMA value value_list RBRACE  */
#line 1415 "yacc_sql.y"
    {
      FieldExpr *lhs = dynamic_cast<FieldExpr *>((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yysemantics.yyval.expression));
      assert(lhs != nullptr && "Expect lhs to be `FieldExpr *`");
      ((*yyvalp).condition) = new ConditionSqlNode;
      ((*yyvalp).condition)->left_is_attr = 1;
      ((*yyvalp).condition)->left_attr = lhs->get_rel_attr();
      ((*yyvalp).condition)->right_is_attr = 3;
      if((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.value_list) != nullptr) {
      	((*yyvalp).condition)->right_value_list.swap(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.value_list));
      	delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.value_list);
      }
      ((*yyvalp).condition)->right_value_list.push_back(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.value));
      ((*yyvalp).condition)->right_value_list.push_back(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.value));
      ((*yyvalp).condition)->comp = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yysemantics.yyval.comp);
      delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yysemantics.yyval.expression);
      delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.value);
      delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.value);
      }
#line 3234 "yacc_sql.cpp"
    break;

  case 137: /* condition: LBRACE select_stmt RBRACE comp_op rel_attr  */
#line 1434 "yacc_sql.y"
      {
	((*yyvalp).condition) = new ConditionSqlNode;
	((*yyvalp).condition)->left_is_attr = 2;
	((*yyvalp).condition)->left_sub_select = new SelectSqlNode((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.sql_node)->selection);
	((*yyvalp).condition)->right_is_attr = 1;
	((*yyvalp).condition)->right_attr = *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.rel_attr);
	((*yyvalp).condition)->comp = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.comp);
	delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.rel_attr);
      }
#line 3248 "yacc_sql.cpp"
    break;

  case 138: /* condition: LBRACE select_stmt RBRACE comp_op LBRACE select_stmt RBRACE  */
#line 1444 "yacc_sql.y"
      {
      	((*yyvalp).condition) = new ConditionSqlNode;
      	((*yyvalp).condition)->left_is_attr = 2;
      	((*yyvalp).condition)->left_sub_select = new SelectSqlNode((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.sql_node)->selection);
      	((*yyvalp).condition)->right_is_attr = 2;
      	((*yyvalp).condition)->right_sub_select = new SelectSqlNode((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.sql_node)->selection);
      	((*yyvalp).condition)->comp = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.comp);
      }
#line 3261 "yacc_sql.cpp"
    break;

  case 139: /* in_op: IN  */
#line 1455 "yacc_sql.y"
       { ((*yyvalp).comp) = IN_OP; }
#line 3267 "yacc_sql.cpp"
    break;

  case 140: /* in_op: NOT IN  */
#line 1456 "yacc_sql.y"
             { ((*yyvalp).comp) = NOT_IN; }
#line 3273 "yacc_sql.cpp"
    break;

  case 141: /* in_op: EXISTS  */
#line 1457 "yacc_sql.y"
             { ((*yyvalp).comp) = EXISTS_OP; }
#line 3279 "yacc_sql.cpp"
    break;

  case 142: /* in_op: NOT EXISTS  */
#line 1458 "yacc_sql.y"
                 { ((*yyvalp).comp) = NOT_EXISTS; }
#line 3285 "yacc_sql.cpp"
    break;

  case 143: /* comp_op: EQ  */
#line 1462 "yacc_sql.y"
         { ((*yyvalp).comp) = EQUAL_TO; }
#line 3291 "yacc_sql.cpp"
    break;

  case 144: /* comp_op: LT  */
#line 1463 "yacc_sql.y"
         { ((*yyvalp).comp) = LESS_THAN; }
#line 3297 "yacc_sql.cpp"
    break;

  case 145: /* comp_op: GT  */
#line 1464 "yacc_sql.y"
         { ((*yyvalp).comp) = GREAT_THAN; }
#line 3303 "yacc_sql.cpp"
    break;

  case 146: /* comp_op: LE  */
#line 1465 "yacc_sql.y"
         { ((*yyvalp).comp) = LESS_EQUAL; }
#line 3309 "yacc_sql.cpp"
    break;

  case 147: /* comp_op: GE  */
#line 1466 "yacc_sql.y"
         { ((*yyvalp).comp) = GREAT_EQUAL; }
#line 3315 "yacc_sql.cpp"
    break;

  case 148: /* comp_op: NE  */
#line 1467 "yacc_sql.y"
         { ((*yyvalp).comp) = NOT_EQUAL; }
#line 3321 "yacc_sql.cpp"
    break;

  case 149: /* comp_op: LIKE  */
#line 1468 "yacc_sql.y"
           { ((*yyvalp).comp) = LIKE_OP;}
#line 3327 "yacc_sql.cpp"
    break;

  case 150: /* comp_op: NOT LIKE  */
#line 1469 "yacc_sql.y"
               { ((*yyvalp).comp) = NOT_LIKE_OP;}
#line 3333 "yacc_sql.cpp"
    break;

  case 151: /* comp_op: NULL_IS  */
#line 1470 "yacc_sql.y"
              { ((*yyvalp).comp) = IS; }
#line 3339 "yacc_sql.cpp"
    break;

  case 152: /* comp_op: NULL_IS NOT  */
#line 1471 "yacc_sql.y"
                  { ((*yyvalp).comp) = IS_NOT; }
#line 3345 "yacc_sql.cpp"
    break;

  case 153: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1476 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.string), 1, strlen((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.string)) - 2);
      
      ((*yyvalp).sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      ((*yyvalp).sql_node)->load_data.relation_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string);
      ((*yyvalp).sql_node)->load_data.file_name = tmp_file_name;
      free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
      free(tmp_file_name);
    }
#line 3359 "yacc_sql.cpp"
    break;

  case 154: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1489 "yacc_sql.y"
    {
      ((*yyvalp).sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      ((*yyvalp).sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.sql_node));
    }
#line 3368 "yacc_sql.cpp"
    break;

  case 155: /* set_variable_stmt: SET ID EQ value  */
#line 1497 "yacc_sql.y"
    {
      ((*yyvalp).sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      ((*yyvalp).sql_node)->set_variable.name  = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string);
      ((*yyvalp).sql_node)->set_variable.value = *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.value);
      free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string));
      delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.value);
    }
#line 3380 "yacc_sql.cpp"
    break;


#line 3384 "yacc_sql.cpp"

      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yylhsNonterm (yyrule), yyvalp, yylocp);

  return yyok;
# undef yyerrok
# undef YYABORT
# undef YYACCEPT
# undef YYNOMEM
# undef YYERROR
# undef YYBACKUP
# undef yyclearin
# undef YYRECOVERING
}


static void
yyuserMerge (int yyn, YYSTYPE* yy0, YYSTYPE* yy1)
{
  YY_USE (yy0);
  YY_USE (yy1);

  switch (yyn)
    {

      default: break;
    }
}

                              /* Bison grammar-table manipulation.  */

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

/** Number of symbols composing the right hand side of rule #RULE.  */
static inline int
yyrhsLength (yyRuleNum yyrule)
{
  return yyr2[yyrule];
}

static void
yydestroyGLRState (char const *yymsg, yyGLRState *yys, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  if (yys->yyresolved)
    yydestruct (yymsg, yy_accessing_symbol (yys->yylrState),
                &yys->yysemantics.yyval, &yys->yyloc, sql_string, sql_result, scanner);
  else
    {
#if YYDEBUG
      if (yydebug)
        {
          if (yys->yysemantics.yyfirstVal)
            YY_FPRINTF ((stderr, "%s unresolved", yymsg));
          else
            YY_FPRINTF ((stderr, "%s incomplete", yymsg));
          YY_SYMBOL_PRINT ("", yy_accessing_symbol (yys->yylrState), YY_NULLPTR, &yys->yyloc);
        }
#endif

      if (yys->yysemantics.yyfirstVal)
        {
          yySemanticOption *yyoption = yys->yysemantics.yyfirstVal;
          yyGLRState *yyrh;
          int yyn;
          for (yyrh = yyoption->yystate, yyn = yyrhsLength (yyoption->yyrule);
               yyn > 0;
               yyrh = yyrh->yypred, yyn -= 1)
            yydestroyGLRState (yymsg, yyrh, sql_string, sql_result, scanner);
        }
    }
}

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

/** True iff LR state YYSTATE has only a default reduction (regardless
 *  of token).  */
static inline yybool
yyisDefaultedState (yy_state_t yystate)
{
  return yypact_value_is_default (yypact[yystate]);
}

/** The default reduction for YYSTATE, assuming it has one.  */
static inline yyRuleNum
yydefaultAction (yy_state_t yystate)
{
  return yydefact[yystate];
}

#define yytable_value_is_error(Yyn) \
  0

/** The action to take in YYSTATE on seeing YYTOKEN.
 *  Result R means
 *    R < 0:  Reduce on rule -R.
 *    R = 0:  Error.
 *    R > 0:  Shift to state R.
 *  Set *YYCONFLICTS to a pointer into yyconfl to a 0-terminated list
 *  of conflicting reductions.
 */
static inline int
yygetLRActions (yy_state_t yystate, yysymbol_kind_t yytoken, const short** yyconflicts)
{
  int yyindex = yypact[yystate] + yytoken;
  if (yytoken == YYSYMBOL_YYerror)
    {
      // This is the error token.
      *yyconflicts = yyconfl;
      return 0;
    }
  else if (yyisDefaultedState (yystate)
           || yyindex < 0 || YYLAST < yyindex || yycheck[yyindex] != yytoken)
    {
      *yyconflicts = yyconfl;
      return -yydefact[yystate];
    }
  else if (! yytable_value_is_error (yytable[yyindex]))
    {
      *yyconflicts = yyconfl + yyconflp[yyindex];
      return yytable[yyindex];
    }
  else
    {
      *yyconflicts = yyconfl + yyconflp[yyindex];
      return 0;
    }
}

/** Compute post-reduction state.
 * \param yystate   the current state
 * \param yysym     the nonterminal to push on the stack
 */
static inline yy_state_t
yyLRgotoState (yy_state_t yystate, yysymbol_kind_t yysym)
{
  int yyr = yypgoto[yysym - YYNTOKENS] + yystate;
  if (0 <= yyr && yyr <= YYLAST && yycheck[yyr] == yystate)
    return yytable[yyr];
  else
    return yydefgoto[yysym - YYNTOKENS];
}

static inline yybool
yyisShiftAction (int yyaction)
{
  return 0 < yyaction;
}

static inline yybool
yyisErrorAction (int yyaction)
{
  return yyaction == 0;
}

                                /* GLRStates */

/** Return a fresh GLRStackItem in YYSTACKP.  The item is an LR state
 *  if YYISSTATE, and otherwise a semantic option.  Callers should call
 *  YY_RESERVE_GLRSTACK afterwards to make sure there is sufficient
 *  headroom.  */

static inline yyGLRStackItem*
yynewGLRStackItem (yyGLRStack* yystackp, yybool yyisState)
{
  yyGLRStackItem* yynewItem = yystackp->yynextFree;
  yystackp->yyspaceLeft -= 1;
  yystackp->yynextFree += 1;
  yynewItem->yystate.yyisState = yyisState;
  return yynewItem;
}

/** Add a new semantic action that will execute the action for rule
 *  YYRULE on the semantic values in YYRHS to the list of
 *  alternative actions for YYSTATE.  Assumes that YYRHS comes from
 *  stack #YYK of *YYSTACKP. */
static void
yyaddDeferredAction (yyGLRStack* yystackp, YYPTRDIFF_T yyk, yyGLRState* yystate,
                     yyGLRState* yyrhs, yyRuleNum yyrule)
{
  yySemanticOption* yynewOption =
    &yynewGLRStackItem (yystackp, yyfalse)->yyoption;
  YY_ASSERT (!yynewOption->yyisState);
  yynewOption->yystate = yyrhs;
  yynewOption->yyrule = yyrule;
  if (yystackp->yytops.yylookaheadNeeds[yyk])
    {
      yynewOption->yyrawchar = yychar;
      yynewOption->yyval = yylval;
      yynewOption->yyloc = yylloc;
    }
  else
    yynewOption->yyrawchar = YYEMPTY;
  yynewOption->yynext = yystate->yysemantics.yyfirstVal;
  yystate->yysemantics.yyfirstVal = yynewOption;

  YY_RESERVE_GLRSTACK (yystackp);
}

                                /* GLRStacks */

/** Initialize YYSET to a singleton set containing an empty stack.  */
static yybool
yyinitStateSet (yyGLRStateSet* yyset)
{
  yyset->yysize = 1;
  yyset->yycapacity = 16;
  yyset->yystates
    = YY_CAST (yyGLRState**,
               YYMALLOC (YY_CAST (YYSIZE_T, yyset->yycapacity)
                         * sizeof yyset->yystates[0]));
  if (! yyset->yystates)
    return yyfalse;
  yyset->yystates[0] = YY_NULLPTR;
  yyset->yylookaheadNeeds
    = YY_CAST (yybool*,
               YYMALLOC (YY_CAST (YYSIZE_T, yyset->yycapacity)
                         * sizeof yyset->yylookaheadNeeds[0]));
  if (! yyset->yylookaheadNeeds)
    {
      YYFREE (yyset->yystates);
      return yyfalse;
    }
  memset (yyset->yylookaheadNeeds,
          0,
          YY_CAST (YYSIZE_T, yyset->yycapacity) * sizeof yyset->yylookaheadNeeds[0]);
  return yytrue;
}

static void yyfreeStateSet (yyGLRStateSet* yyset)
{
  YYFREE (yyset->yystates);
  YYFREE (yyset->yylookaheadNeeds);
}

/** Initialize *YYSTACKP to a single empty stack, with total maximum
 *  capacity for all stacks of YYSIZE.  */
static yybool
yyinitGLRStack (yyGLRStack* yystackp, YYPTRDIFF_T yysize)
{
  yystackp->yyerrState = 0;
  yynerrs = 0;
  yystackp->yyspaceLeft = yysize;
  yystackp->yyitems
    = YY_CAST (yyGLRStackItem*,
               YYMALLOC (YY_CAST (YYSIZE_T, yysize)
                         * sizeof yystackp->yynextFree[0]));
  if (!yystackp->yyitems)
    return yyfalse;
  yystackp->yynextFree = yystackp->yyitems;
  yystackp->yysplitPoint = YY_NULLPTR;
  yystackp->yylastDeleted = YY_NULLPTR;
  return yyinitStateSet (&yystackp->yytops);
}


#if YYSTACKEXPANDABLE
# define YYRELOC(YYFROMITEMS, YYTOITEMS, YYX, YYTYPE)                   \
  &((YYTOITEMS)                                                         \
    - ((YYFROMITEMS) - YY_REINTERPRET_CAST (yyGLRStackItem*, (YYX))))->YYTYPE

/** If *YYSTACKP is expandable, extend it.  WARNING: Pointers into the
    stack from outside should be considered invalid after this call.
    We always expand when there are 1 or fewer items left AFTER an
    allocation, so that we can avoid having external pointers exist
    across an allocation.  */
static void
yyexpandGLRStack (yyGLRStack* yystackp)
{
  yyGLRStackItem* yynewItems;
  yyGLRStackItem* yyp0, *yyp1;
  YYPTRDIFF_T yynewSize;
  YYPTRDIFF_T yyn;
  YYPTRDIFF_T yysize = yystackp->yynextFree - yystackp->yyitems;
  if (YYMAXDEPTH - YYHEADROOM < yysize)
    yyMemoryExhausted (yystackp);
  yynewSize = 2*yysize;
  if (YYMAXDEPTH < yynewSize)
    yynewSize = YYMAXDEPTH;
  yynewItems
    = YY_CAST (yyGLRStackItem*,
               YYMALLOC (YY_CAST (YYSIZE_T, yynewSize)
                         * sizeof yynewItems[0]));
  if (! yynewItems)
    yyMemoryExhausted (yystackp);
  for (yyp0 = yystackp->yyitems, yyp1 = yynewItems, yyn = yysize;
       0 < yyn;
       yyn -= 1, yyp0 += 1, yyp1 += 1)
    {
      *yyp1 = *yyp0;
      if (*YY_REINTERPRET_CAST (yybool *, yyp0))
        {
          yyGLRState* yys0 = &yyp0->yystate;
          yyGLRState* yys1 = &yyp1->yystate;
          if (yys0->yypred != YY_NULLPTR)
            yys1->yypred =
              YYRELOC (yyp0, yyp1, yys0->yypred, yystate);
          if (! yys0->yyresolved && yys0->yysemantics.yyfirstVal != YY_NULLPTR)
            yys1->yysemantics.yyfirstVal =
              YYRELOC (yyp0, yyp1, yys0->yysemantics.yyfirstVal, yyoption);
        }
      else
        {
          yySemanticOption* yyv0 = &yyp0->yyoption;
          yySemanticOption* yyv1 = &yyp1->yyoption;
          if (yyv0->yystate != YY_NULLPTR)
            yyv1->yystate = YYRELOC (yyp0, yyp1, yyv0->yystate, yystate);
          if (yyv0->yynext != YY_NULLPTR)
            yyv1->yynext = YYRELOC (yyp0, yyp1, yyv0->yynext, yyoption);
        }
    }
  if (yystackp->yysplitPoint != YY_NULLPTR)
    yystackp->yysplitPoint = YYRELOC (yystackp->yyitems, yynewItems,
                                      yystackp->yysplitPoint, yystate);

  for (yyn = 0; yyn < yystackp->yytops.yysize; yyn += 1)
    if (yystackp->yytops.yystates[yyn] != YY_NULLPTR)
      yystackp->yytops.yystates[yyn] =
        YYRELOC (yystackp->yyitems, yynewItems,
                 yystackp->yytops.yystates[yyn], yystate);
  YYFREE (yystackp->yyitems);
  yystackp->yyitems = yynewItems;
  yystackp->yynextFree = yynewItems + yysize;
  yystackp->yyspaceLeft = yynewSize - yysize;
}
#endif

static void
yyfreeGLRStack (yyGLRStack* yystackp)
{
  YYFREE (yystackp->yyitems);
  yyfreeStateSet (&yystackp->yytops);
}

/** Assuming that YYS is a GLRState somewhere on *YYSTACKP, update the
 *  splitpoint of *YYSTACKP, if needed, so that it is at least as deep as
 *  YYS.  */
static inline void
yyupdateSplit (yyGLRStack* yystackp, yyGLRState* yys)
{
  if (yystackp->yysplitPoint != YY_NULLPTR && yystackp->yysplitPoint > yys)
    yystackp->yysplitPoint = yys;
}

/** Invalidate stack #YYK in *YYSTACKP.  */
static inline void
yymarkStackDeleted (yyGLRStack* yystackp, YYPTRDIFF_T yyk)
{
  if (yystackp->yytops.yystates[yyk] != YY_NULLPTR)
    yystackp->yylastDeleted = yystackp->yytops.yystates[yyk];
  yystackp->yytops.yystates[yyk] = YY_NULLPTR;
}

/** Undelete the last stack in *YYSTACKP that was marked as deleted.  Can
    only be done once after a deletion, and only when all other stacks have
    been deleted.  */
static void
yyundeleteLastStack (yyGLRStack* yystackp)
{
  if (yystackp->yylastDeleted == YY_NULLPTR || yystackp->yytops.yysize != 0)
    return;
  yystackp->yytops.yystates[0] = yystackp->yylastDeleted;
  yystackp->yytops.yysize = 1;
  YY_DPRINTF ((stderr, "Restoring last deleted stack as stack #0.\n"));
  yystackp->yylastDeleted = YY_NULLPTR;
}

static inline void
yyremoveDeletes (yyGLRStack* yystackp)
{
  YYPTRDIFF_T yyi, yyj;
  yyi = yyj = 0;
  while (yyj < yystackp->yytops.yysize)
    {
      if (yystackp->yytops.yystates[yyi] == YY_NULLPTR)
        {
          if (yyi == yyj)
            YY_DPRINTF ((stderr, "Removing dead stacks.\n"));
          yystackp->yytops.yysize -= 1;
        }
      else
        {
          yystackp->yytops.yystates[yyj] = yystackp->yytops.yystates[yyi];
          /* In the current implementation, it's unnecessary to copy
             yystackp->yytops.yylookaheadNeeds[yyi] since, after
             yyremoveDeletes returns, the parser immediately either enters
             deterministic operation or shifts a token.  However, it doesn't
             hurt, and the code might evolve to need it.  */
          yystackp->yytops.yylookaheadNeeds[yyj] =
            yystackp->yytops.yylookaheadNeeds[yyi];
          if (yyj != yyi)
            YY_DPRINTF ((stderr, "Rename stack %ld -> %ld.\n",
                        YY_CAST (long, yyi), YY_CAST (long, yyj)));
          yyj += 1;
        }
      yyi += 1;
    }
}

/** Shift to a new state on stack #YYK of *YYSTACKP, corresponding to LR
 * state YYLRSTATE, at input position YYPOSN, with (resolved) semantic
 * value *YYVALP and source location *YYLOCP.  */
static inline void
yyglrShift (yyGLRStack* yystackp, YYPTRDIFF_T yyk, yy_state_t yylrState,
            YYPTRDIFF_T yyposn,
            YYSTYPE* yyvalp, YYLTYPE* yylocp)
{
  yyGLRState* yynewState = &yynewGLRStackItem (yystackp, yytrue)->yystate;

  yynewState->yylrState = yylrState;
  yynewState->yyposn = yyposn;
  yynewState->yyresolved = yytrue;
  yynewState->yypred = yystackp->yytops.yystates[yyk];
  yynewState->yysemantics.yyval = *yyvalp;
  yynewState->yyloc = *yylocp;
  yystackp->yytops.yystates[yyk] = yynewState;

  YY_RESERVE_GLRSTACK (yystackp);
}

/** Shift stack #YYK of *YYSTACKP, to a new state corresponding to LR
 *  state YYLRSTATE, at input position YYPOSN, with the (unresolved)
 *  semantic value of YYRHS under the action for YYRULE.  */
static inline void
yyglrShiftDefer (yyGLRStack* yystackp, YYPTRDIFF_T yyk, yy_state_t yylrState,
                 YYPTRDIFF_T yyposn, yyGLRState* yyrhs, yyRuleNum yyrule)
{
  yyGLRState* yynewState = &yynewGLRStackItem (yystackp, yytrue)->yystate;
  YY_ASSERT (yynewState->yyisState);

  yynewState->yylrState = yylrState;
  yynewState->yyposn = yyposn;
  yynewState->yyresolved = yyfalse;
  yynewState->yypred = yystackp->yytops.yystates[yyk];
  yynewState->yysemantics.yyfirstVal = YY_NULLPTR;
  yystackp->yytops.yystates[yyk] = yynewState;

  /* Invokes YY_RESERVE_GLRSTACK.  */
  yyaddDeferredAction (yystackp, yyk, yynewState, yyrhs, yyrule);
}

#if YYDEBUG

/*----------------------------------------------------------------------.
| Report that stack #YYK of *YYSTACKP is going to be reduced by YYRULE. |
`----------------------------------------------------------------------*/

static inline void
yy_reduce_print (yybool yynormal, yyGLRStackItem* yyvsp, YYPTRDIFF_T yyk,
                 yyRuleNum yyrule, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  int yynrhs = yyrhsLength (yyrule);
  int yylow = 1;
  int yyi;
  YY_FPRINTF ((stderr, "Reducing stack %ld by rule %d (line %d):\n",
               YY_CAST (long, yyk), yyrule - 1, yyrline[yyrule]));
  if (! yynormal)
    yyfillin (yyvsp, 1, -yynrhs);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YY_FPRINTF ((stderr, "   $%d = ", yyi + 1));
      yy_symbol_print (stderr,
                       yy_accessing_symbol (yyvsp[yyi - yynrhs + 1].yystate.yylrState),
                       &yyvsp[yyi - yynrhs + 1].yystate.yysemantics.yyval,
                       &(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL ((yyi + 1) - (yynrhs))].yystate.yyloc)                       , sql_string, sql_result, scanner);
      if (!yyvsp[yyi - yynrhs + 1].yystate.yyresolved)
        YY_FPRINTF ((stderr, " (unresolved)"));
      YY_FPRINTF ((stderr, "\n"));
    }
}
#endif

/** Pop the symbols consumed by reduction #YYRULE from the top of stack
 *  #YYK of *YYSTACKP, and perform the appropriate semantic action on their
 *  semantic values.  Assumes that all ambiguities in semantic values
 *  have been previously resolved.  Set *YYVALP to the resulting value,
 *  and *YYLOCP to the computed location (if any).  Return value is as
 *  for userAction.  */
static inline YYRESULTTAG
yydoAction (yyGLRStack* yystackp, YYPTRDIFF_T yyk, yyRuleNum yyrule,
            YYSTYPE* yyvalp, YYLTYPE *yylocp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  int yynrhs = yyrhsLength (yyrule);

  if (yystackp->yysplitPoint == YY_NULLPTR)
    {
      /* Standard special case: single stack.  */
      yyGLRStackItem* yyrhs
        = YY_REINTERPRET_CAST (yyGLRStackItem*, yystackp->yytops.yystates[yyk]);
      YY_ASSERT (yyk == 0);
      yystackp->yynextFree -= yynrhs;
      yystackp->yyspaceLeft += yynrhs;
      yystackp->yytops.yystates[0] = & yystackp->yynextFree[-1].yystate;
      return yyuserAction (yyrule, yynrhs, yyrhs, yystackp, yyk,
                           yyvalp, yylocp, sql_string, sql_result, scanner);
    }
  else
    {
      yyGLRStackItem yyrhsVals[YYMAXRHS + YYMAXLEFT + 1];
      yyGLRState* yys = yyrhsVals[YYMAXRHS + YYMAXLEFT].yystate.yypred
        = yystackp->yytops.yystates[yyk];
      int yyi;
      if (yynrhs == 0)
        /* Set default location.  */
        yyrhsVals[YYMAXRHS + YYMAXLEFT - 1].yystate.yyloc = yys->yyloc;
      for (yyi = 0; yyi < yynrhs; yyi += 1)
        {
          yys = yys->yypred;
          YY_ASSERT (yys);
        }
      yyupdateSplit (yystackp, yys);
      yystackp->yytops.yystates[yyk] = yys;
      return yyuserAction (yyrule, yynrhs, yyrhsVals + YYMAXRHS + YYMAXLEFT - 1,
                           yystackp, yyk, yyvalp, yylocp, sql_string, sql_result, scanner);
    }
}

/** Pop items off stack #YYK of *YYSTACKP according to grammar rule YYRULE,
 *  and push back on the resulting nonterminal symbol.  Perform the
 *  semantic action associated with YYRULE and store its value with the
 *  newly pushed state, if YYFORCEEVAL or if *YYSTACKP is currently
 *  unambiguous.  Otherwise, store the deferred semantic action with
 *  the new state.  If the new state would have an identical input
 *  position, LR state, and predecessor to an existing state on the stack,
 *  it is identified with that existing state, eliminating stack #YYK from
 *  *YYSTACKP.  In this case, the semantic value is
 *  added to the options for the existing state's semantic value.
 */
static inline YYRESULTTAG
yyglrReduce (yyGLRStack* yystackp, YYPTRDIFF_T yyk, yyRuleNum yyrule,
             yybool yyforceEval, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYPTRDIFF_T yyposn = yystackp->yytops.yystates[yyk]->yyposn;

  if (yyforceEval || yystackp->yysplitPoint == YY_NULLPTR)
    {
      YYSTYPE yyval;
      YYLTYPE yyloc;

      YYRESULTTAG yyflag = yydoAction (yystackp, yyk, yyrule, &yyval, &yyloc, sql_string, sql_result, scanner);
      if (yyflag == yyerr && yystackp->yysplitPoint != YY_NULLPTR)
        YY_DPRINTF ((stderr,
                     "Parse on stack %ld rejected by rule %d (line %d).\n",
                     YY_CAST (long, yyk), yyrule - 1, yyrline[yyrule]));
      if (yyflag != yyok)
        return yyflag;
      yyglrShift (yystackp, yyk,
                  yyLRgotoState (yystackp->yytops.yystates[yyk]->yylrState,
                                 yylhsNonterm (yyrule)),
                  yyposn, &yyval, &yyloc);
    }
  else
    {
      YYPTRDIFF_T yyi;
      int yyn;
      yyGLRState* yys, *yys0 = yystackp->yytops.yystates[yyk];
      yy_state_t yynewLRState;

      for (yys = yystackp->yytops.yystates[yyk], yyn = yyrhsLength (yyrule);
           0 < yyn; yyn -= 1)
        {
          yys = yys->yypred;
          YY_ASSERT (yys);
        }
      yyupdateSplit (yystackp, yys);
      yynewLRState = yyLRgotoState (yys->yylrState, yylhsNonterm (yyrule));
      YY_DPRINTF ((stderr,
                   "Reduced stack %ld by rule %d (line %d); action deferred.  "
                   "Now in state %d.\n",
                   YY_CAST (long, yyk), yyrule - 1, yyrline[yyrule],
                   yynewLRState));
      for (yyi = 0; yyi < yystackp->yytops.yysize; yyi += 1)
        if (yyi != yyk && yystackp->yytops.yystates[yyi] != YY_NULLPTR)
          {
            yyGLRState *yysplit = yystackp->yysplitPoint;
            yyGLRState *yyp = yystackp->yytops.yystates[yyi];
            while (yyp != yys && yyp != yysplit && yyp->yyposn >= yyposn)
              {
                if (yyp->yylrState == yynewLRState && yyp->yypred == yys)
                  {
                    yyaddDeferredAction (yystackp, yyk, yyp, yys0, yyrule);
                    yymarkStackDeleted (yystackp, yyk);
                    YY_DPRINTF ((stderr, "Merging stack %ld into stack %ld.\n",
                                 YY_CAST (long, yyk), YY_CAST (long, yyi)));
                    return yyok;
                  }
                yyp = yyp->yypred;
              }
          }
      yystackp->yytops.yystates[yyk] = yys;
      yyglrShiftDefer (yystackp, yyk, yynewLRState, yyposn, yys0, yyrule);
    }
  return yyok;
}

static YYPTRDIFF_T
yysplitStack (yyGLRStack* yystackp, YYPTRDIFF_T yyk)
{
  if (yystackp->yysplitPoint == YY_NULLPTR)
    {
      YY_ASSERT (yyk == 0);
      yystackp->yysplitPoint = yystackp->yytops.yystates[yyk];
    }
  if (yystackp->yytops.yycapacity <= yystackp->yytops.yysize)
    {
      YYPTRDIFF_T state_size = YYSIZEOF (yystackp->yytops.yystates[0]);
      YYPTRDIFF_T half_max_capacity = YYSIZE_MAXIMUM / 2 / state_size;
      if (half_max_capacity < yystackp->yytops.yycapacity)
        yyMemoryExhausted (yystackp);
      yystackp->yytops.yycapacity *= 2;

      {
        yyGLRState** yynewStates
          = YY_CAST (yyGLRState**,
                     YYREALLOC (yystackp->yytops.yystates,
                                (YY_CAST (YYSIZE_T, yystackp->yytops.yycapacity)
                                 * sizeof yynewStates[0])));
        if (yynewStates == YY_NULLPTR)
          yyMemoryExhausted (yystackp);
        yystackp->yytops.yystates = yynewStates;
      }

      {
        yybool* yynewLookaheadNeeds
          = YY_CAST (yybool*,
                     YYREALLOC (yystackp->yytops.yylookaheadNeeds,
                                (YY_CAST (YYSIZE_T, yystackp->yytops.yycapacity)
                                 * sizeof yynewLookaheadNeeds[0])));
        if (yynewLookaheadNeeds == YY_NULLPTR)
          yyMemoryExhausted (yystackp);
        yystackp->yytops.yylookaheadNeeds = yynewLookaheadNeeds;
      }
    }
  yystackp->yytops.yystates[yystackp->yytops.yysize]
    = yystackp->yytops.yystates[yyk];
  yystackp->yytops.yylookaheadNeeds[yystackp->yytops.yysize]
    = yystackp->yytops.yylookaheadNeeds[yyk];
  yystackp->yytops.yysize += 1;
  return yystackp->yytops.yysize - 1;
}

/** True iff YYY0 and YYY1 represent identical options at the top level.
 *  That is, they represent the same rule applied to RHS symbols
 *  that produce the same terminal symbols.  */
static yybool
yyidenticalOptions (yySemanticOption* yyy0, yySemanticOption* yyy1)
{
  if (yyy0->yyrule == yyy1->yyrule)
    {
      yyGLRState *yys0, *yys1;
      int yyn;
      for (yys0 = yyy0->yystate, yys1 = yyy1->yystate,
           yyn = yyrhsLength (yyy0->yyrule);
           yyn > 0;
           yys0 = yys0->yypred, yys1 = yys1->yypred, yyn -= 1)
        if (yys0->yyposn != yys1->yyposn)
          return yyfalse;
      return yytrue;
    }
  else
    return yyfalse;
}

/** Assuming identicalOptions (YYY0,YYY1), destructively merge the
 *  alternative semantic values for the RHS-symbols of YYY1 and YYY0.  */
static void
yymergeOptionSets (yySemanticOption* yyy0, yySemanticOption* yyy1)
{
  yyGLRState *yys0, *yys1;
  int yyn;
  for (yys0 = yyy0->yystate, yys1 = yyy1->yystate,
       yyn = yyrhsLength (yyy0->yyrule);
       0 < yyn;
       yys0 = yys0->yypred, yys1 = yys1->yypred, yyn -= 1)
    {
      if (yys0 == yys1)
        break;
      else if (yys0->yyresolved)
        {
          yys1->yyresolved = yytrue;
          yys1->yysemantics.yyval = yys0->yysemantics.yyval;
        }
      else if (yys1->yyresolved)
        {
          yys0->yyresolved = yytrue;
          yys0->yysemantics.yyval = yys1->yysemantics.yyval;
        }
      else
        {
          yySemanticOption** yyz0p = &yys0->yysemantics.yyfirstVal;
          yySemanticOption* yyz1 = yys1->yysemantics.yyfirstVal;
          while (yytrue)
            {
              if (yyz1 == *yyz0p || yyz1 == YY_NULLPTR)
                break;
              else if (*yyz0p == YY_NULLPTR)
                {
                  *yyz0p = yyz1;
                  break;
                }
              else if (*yyz0p < yyz1)
                {
                  yySemanticOption* yyz = *yyz0p;
                  *yyz0p = yyz1;
                  yyz1 = yyz1->yynext;
                  (*yyz0p)->yynext = yyz;
                }
              yyz0p = &(*yyz0p)->yynext;
            }
          yys1->yysemantics.yyfirstVal = yys0->yysemantics.yyfirstVal;
        }
    }
}

/** Y0 and Y1 represent two possible actions to take in a given
 *  parsing state; return 0 if no combination is possible,
 *  1 if user-mergeable, 2 if Y0 is preferred, 3 if Y1 is preferred.  */
static int
yypreference (yySemanticOption* y0, yySemanticOption* y1)
{
  yyRuleNum r0 = y0->yyrule, r1 = y1->yyrule;
  int p0 = yydprec[r0], p1 = yydprec[r1];

  if (p0 == p1)
    {
      if (yymerger[r0] == 0 || yymerger[r0] != yymerger[r1])
        return 0;
      else
        return 1;
    }
  if (p0 == 0 || p1 == 0)
    return 0;
  if (p0 < p1)
    return 3;
  if (p1 < p0)
    return 2;
  return 0;
}

static YYRESULTTAG
yyresolveValue (yyGLRState* yys, yyGLRStack* yystackp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner);


/** Resolve the previous YYN states starting at and including state YYS
 *  on *YYSTACKP. If result != yyok, some states may have been left
 *  unresolved possibly with empty semantic option chains.  Regardless
 *  of whether result = yyok, each state has been left with consistent
 *  data so that yydestroyGLRState can be invoked if necessary.  */
static YYRESULTTAG
yyresolveStates (yyGLRState* yys, int yyn,
                 yyGLRStack* yystackp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  if (0 < yyn)
    {
      YY_ASSERT (yys->yypred);
      YYCHK (yyresolveStates (yys->yypred, yyn-1, yystackp, sql_string, sql_result, scanner));
      if (! yys->yyresolved)
        YYCHK (yyresolveValue (yys, yystackp, sql_string, sql_result, scanner));
    }
  return yyok;
}

/** Resolve the states for the RHS of YYOPT on *YYSTACKP, perform its
 *  user action, and return the semantic value and location in *YYVALP
 *  and *YYLOCP.  Regardless of whether result = yyok, all RHS states
 *  have been destroyed (assuming the user action destroys all RHS
 *  semantic values if invoked).  */
static YYRESULTTAG
yyresolveAction (yySemanticOption* yyopt, yyGLRStack* yystackp,
                 YYSTYPE* yyvalp, YYLTYPE *yylocp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  yyGLRStackItem yyrhsVals[YYMAXRHS + YYMAXLEFT + 1];
  int yynrhs = yyrhsLength (yyopt->yyrule);
  YYRESULTTAG yyflag =
    yyresolveStates (yyopt->yystate, yynrhs, yystackp, sql_string, sql_result, scanner);
  if (yyflag != yyok)
    {
      yyGLRState *yys;
      for (yys = yyopt->yystate; yynrhs > 0; yys = yys->yypred, yynrhs -= 1)
        yydestroyGLRState ("Cleanup: popping", yys, sql_string, sql_result, scanner);
      return yyflag;
    }

  yyrhsVals[YYMAXRHS + YYMAXLEFT].yystate.yypred = yyopt->yystate;
  if (yynrhs == 0)
    /* Set default location.  */
    yyrhsVals[YYMAXRHS + YYMAXLEFT - 1].yystate.yyloc = yyopt->yystate->yyloc;
  {
    int yychar_current = yychar;
    YYSTYPE yylval_current = yylval;
    YYLTYPE yylloc_current = yylloc;
    yychar = yyopt->yyrawchar;
    yylval = yyopt->yyval;
    yylloc = yyopt->yyloc;
    yyflag = yyuserAction (yyopt->yyrule, yynrhs,
                           yyrhsVals + YYMAXRHS + YYMAXLEFT - 1,
                           yystackp, -1, yyvalp, yylocp, sql_string, sql_result, scanner);
    yychar = yychar_current;
    yylval = yylval_current;
    yylloc = yylloc_current;
  }
  return yyflag;
}

#if YYDEBUG
static void
yyreportTree (yySemanticOption* yyx, int yyindent)
{
  int yynrhs = yyrhsLength (yyx->yyrule);
  int yyi;
  yyGLRState* yys;
  yyGLRState* yystates[1 + YYMAXRHS];
  yyGLRState yyleftmost_state;

  for (yyi = yynrhs, yys = yyx->yystate; 0 < yyi; yyi -= 1, yys = yys->yypred)
    yystates[yyi] = yys;
  if (yys == YY_NULLPTR)
    {
      yyleftmost_state.yyposn = 0;
      yystates[0] = &yyleftmost_state;
    }
  else
    yystates[0] = yys;

  if (yyx->yystate->yyposn < yys->yyposn + 1)
    YY_FPRINTF ((stderr, "%*s%s -> <Rule %d, empty>\n",
                 yyindent, "", yysymbol_name (yylhsNonterm (yyx->yyrule)),
                 yyx->yyrule - 1));
  else
    YY_FPRINTF ((stderr, "%*s%s -> <Rule %d, tokens %ld .. %ld>\n",
                 yyindent, "", yysymbol_name (yylhsNonterm (yyx->yyrule)),
                 yyx->yyrule - 1, YY_CAST (long, yys->yyposn + 1),
                 YY_CAST (long, yyx->yystate->yyposn)));
  for (yyi = 1; yyi <= yynrhs; yyi += 1)
    {
      if (yystates[yyi]->yyresolved)
        {
          if (yystates[yyi-1]->yyposn+1 > yystates[yyi]->yyposn)
            YY_FPRINTF ((stderr, "%*s%s <empty>\n", yyindent+2, "",
                         yysymbol_name (yy_accessing_symbol (yystates[yyi]->yylrState))));
          else
            YY_FPRINTF ((stderr, "%*s%s <tokens %ld .. %ld>\n", yyindent+2, "",
                         yysymbol_name (yy_accessing_symbol (yystates[yyi]->yylrState)),
                         YY_CAST (long, yystates[yyi-1]->yyposn + 1),
                         YY_CAST (long, yystates[yyi]->yyposn)));
        }
      else
        yyreportTree (yystates[yyi]->yysemantics.yyfirstVal, yyindent+2);
    }
}
#endif

static YYRESULTTAG
yyreportAmbiguity (yySemanticOption* yyx0,
                   yySemanticOption* yyx1, YYLTYPE *yylocp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YY_USE (yyx0);
  YY_USE (yyx1);

#if YYDEBUG
  YY_FPRINTF ((stderr, "Ambiguity detected.\n"));
  YY_FPRINTF ((stderr, "Option 1,\n"));
  yyreportTree (yyx0, 2);
  YY_FPRINTF ((stderr, "\nOption 2,\n"));
  yyreportTree (yyx1, 2);
  YY_FPRINTF ((stderr, "\n"));
#endif

  yyerror (yylocp, sql_string, sql_result, scanner, YY_("syntax is ambiguous"));
  return yyabort;
}

/** Resolve the locations for each of the YYN1 states in *YYSTACKP,
 *  ending at YYS1.  Has no effect on previously resolved states.
 *  The first semantic option of a state is always chosen.  */
static void
yyresolveLocations (yyGLRState *yys1, int yyn1,
                    yyGLRStack *yystackp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  if (0 < yyn1)
    {
      yyresolveLocations (yys1->yypred, yyn1 - 1, yystackp, sql_string, sql_result, scanner);
      if (!yys1->yyresolved)
        {
          yyGLRStackItem yyrhsloc[1 + YYMAXRHS];
          int yynrhs;
          yySemanticOption *yyoption = yys1->yysemantics.yyfirstVal;
          YY_ASSERT (yyoption);
          yynrhs = yyrhsLength (yyoption->yyrule);
          if (0 < yynrhs)
            {
              yyGLRState *yys;
              int yyn;
              yyresolveLocations (yyoption->yystate, yynrhs,
                                  yystackp, sql_string, sql_result, scanner);
              for (yys = yyoption->yystate, yyn = yynrhs;
                   yyn > 0;
                   yys = yys->yypred, yyn -= 1)
                yyrhsloc[yyn].yystate.yyloc = yys->yyloc;
            }
          else
            {
              /* Both yyresolveAction and yyresolveLocations traverse the GSS
                 in reverse rightmost order.  It is only necessary to invoke
                 yyresolveLocations on a subforest for which yyresolveAction
                 would have been invoked next had an ambiguity not been
                 detected.  Thus the location of the previous state (but not
                 necessarily the previous state itself) is guaranteed to be
                 resolved already.  */
              yyGLRState *yyprevious = yyoption->yystate;
              yyrhsloc[0].yystate.yyloc = yyprevious->yyloc;
            }
          YYLLOC_DEFAULT ((yys1->yyloc), yyrhsloc, yynrhs);
        }
    }
}

/** Resolve the ambiguity represented in state YYS in *YYSTACKP,
 *  perform the indicated actions, and set the semantic value of YYS.
 *  If result != yyok, the chain of semantic options in YYS has been
 *  cleared instead or it has been left unmodified except that
 *  redundant options may have been removed.  Regardless of whether
 *  result = yyok, YYS has been left with consistent data so that
 *  yydestroyGLRState can be invoked if necessary.  */
static YYRESULTTAG
yyresolveValue (yyGLRState* yys, yyGLRStack* yystackp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  yySemanticOption* yyoptionList = yys->yysemantics.yyfirstVal;
  yySemanticOption* yybest = yyoptionList;
  yySemanticOption** yypp;
  yybool yymerge = yyfalse;
  YYSTYPE yyval;
  YYRESULTTAG yyflag;
  YYLTYPE *yylocp = &yys->yyloc;

  for (yypp = &yyoptionList->yynext; *yypp != YY_NULLPTR; )
    {
      yySemanticOption* yyp = *yypp;

      if (yyidenticalOptions (yybest, yyp))
        {
          yymergeOptionSets (yybest, yyp);
          *yypp = yyp->yynext;
        }
      else
        {
          switch (yypreference (yybest, yyp))
            {
            case 0:
              yyresolveLocations (yys, 1, yystackp, sql_string, sql_result, scanner);
              return yyreportAmbiguity (yybest, yyp, yylocp, sql_string, sql_result, scanner);
              break;
            case 1:
              yymerge = yytrue;
              break;
            case 2:
              break;
            case 3:
              yybest = yyp;
              yymerge = yyfalse;
              break;
            default:
              /* This cannot happen so it is not worth a YY_ASSERT (yyfalse),
                 but some compilers complain if the default case is
                 omitted.  */
              break;
            }
          yypp = &yyp->yynext;
        }
    }

  if (yymerge)
    {
      yySemanticOption* yyp;
      int yyprec = yydprec[yybest->yyrule];
      yyflag = yyresolveAction (yybest, yystackp, &yyval, yylocp, sql_string, sql_result, scanner);
      if (yyflag == yyok)
        for (yyp = yybest->yynext; yyp != YY_NULLPTR; yyp = yyp->yynext)
          {
            if (yyprec == yydprec[yyp->yyrule])
              {
                YYSTYPE yyval_other;
                YYLTYPE yydummy;
                yyflag = yyresolveAction (yyp, yystackp, &yyval_other, &yydummy, sql_string, sql_result, scanner);
                if (yyflag != yyok)
                  {
                    yydestruct ("Cleanup: discarding incompletely merged value for",
                                yy_accessing_symbol (yys->yylrState),
                                &yyval, yylocp, sql_string, sql_result, scanner);
                    break;
                  }
                yyuserMerge (yymerger[yyp->yyrule], &yyval, &yyval_other);
              }
          }
    }
  else
    yyflag = yyresolveAction (yybest, yystackp, &yyval, yylocp, sql_string, sql_result, scanner);

  if (yyflag == yyok)
    {
      yys->yyresolved = yytrue;
      yys->yysemantics.yyval = yyval;
    }
  else
    yys->yysemantics.yyfirstVal = YY_NULLPTR;
  return yyflag;
}

static YYRESULTTAG
yyresolveStack (yyGLRStack* yystackp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  if (yystackp->yysplitPoint != YY_NULLPTR)
    {
      yyGLRState* yys;
      int yyn;

      for (yyn = 0, yys = yystackp->yytops.yystates[0];
           yys != yystackp->yysplitPoint;
           yys = yys->yypred, yyn += 1)
        continue;
      YYCHK (yyresolveStates (yystackp->yytops.yystates[0], yyn, yystackp
                             , sql_string, sql_result, scanner));
    }
  return yyok;
}

/** Called when returning to deterministic operation to clean up the extra
 * stacks. */
static void
yycompressStack (yyGLRStack* yystackp)
{
  /* yyr is the state after the split point.  */
  yyGLRState *yyr;

  if (yystackp->yytops.yysize != 1 || yystackp->yysplitPoint == YY_NULLPTR)
    return;

  {
    yyGLRState *yyp, *yyq;
    for (yyp = yystackp->yytops.yystates[0], yyq = yyp->yypred, yyr = YY_NULLPTR;
         yyp != yystackp->yysplitPoint;
         yyr = yyp, yyp = yyq, yyq = yyp->yypred)
      yyp->yypred = yyr;
  }

  yystackp->yyspaceLeft += yystackp->yynextFree - yystackp->yyitems;
  yystackp->yynextFree = YY_REINTERPRET_CAST (yyGLRStackItem*, yystackp->yysplitPoint) + 1;
  yystackp->yyspaceLeft -= yystackp->yynextFree - yystackp->yyitems;
  yystackp->yysplitPoint = YY_NULLPTR;
  yystackp->yylastDeleted = YY_NULLPTR;

  while (yyr != YY_NULLPTR)
    {
      yystackp->yynextFree->yystate = *yyr;
      yyr = yyr->yypred;
      yystackp->yynextFree->yystate.yypred = &yystackp->yynextFree[-1].yystate;
      yystackp->yytops.yystates[0] = &yystackp->yynextFree->yystate;
      yystackp->yynextFree += 1;
      yystackp->yyspaceLeft -= 1;
    }
}

static YYRESULTTAG
yyprocessOneStack (yyGLRStack* yystackp, YYPTRDIFF_T yyk,
                   YYPTRDIFF_T yyposn, YYLTYPE *yylocp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  while (yystackp->yytops.yystates[yyk] != YY_NULLPTR)
    {
      yy_state_t yystate = yystackp->yytops.yystates[yyk]->yylrState;
      YY_DPRINTF ((stderr, "Stack %ld Entering state %d\n",
                   YY_CAST (long, yyk), yystate));

      YY_ASSERT (yystate != YYFINAL);

      if (yyisDefaultedState (yystate))
        {
          YYRESULTTAG yyflag;
          yyRuleNum yyrule = yydefaultAction (yystate);
          if (yyrule == 0)
            {
              YY_DPRINTF ((stderr, "Stack %ld dies.\n", YY_CAST (long, yyk)));
              yymarkStackDeleted (yystackp, yyk);
              return yyok;
            }
          yyflag = yyglrReduce (yystackp, yyk, yyrule, yyimmediate[yyrule], sql_string, sql_result, scanner);
          if (yyflag == yyerr)
            {
              YY_DPRINTF ((stderr,
                           "Stack %ld dies "
                           "(predicate failure or explicit user error).\n",
                           YY_CAST (long, yyk)));
              yymarkStackDeleted (yystackp, yyk);
              return yyok;
            }
          if (yyflag != yyok)
            return yyflag;
        }
      else
        {
          yysymbol_kind_t yytoken = yygetToken (&yychar, yystackp, sql_string, sql_result, scanner);
          const short* yyconflicts;
          const int yyaction = yygetLRActions (yystate, yytoken, &yyconflicts);
          yystackp->yytops.yylookaheadNeeds[yyk] = yytrue;

          for (/* nothing */; *yyconflicts; yyconflicts += 1)
            {
              YYRESULTTAG yyflag;
              YYPTRDIFF_T yynewStack = yysplitStack (yystackp, yyk);
              YY_DPRINTF ((stderr, "Splitting off stack %ld from %ld.\n",
                           YY_CAST (long, yynewStack), YY_CAST (long, yyk)));
              yyflag = yyglrReduce (yystackp, yynewStack,
                                    *yyconflicts,
                                    yyimmediate[*yyconflicts], sql_string, sql_result, scanner);
              if (yyflag == yyok)
                YYCHK (yyprocessOneStack (yystackp, yynewStack,
                                          yyposn, yylocp, sql_string, sql_result, scanner));
              else if (yyflag == yyerr)
                {
                  YY_DPRINTF ((stderr, "Stack %ld dies.\n", YY_CAST (long, yynewStack)));
                  yymarkStackDeleted (yystackp, yynewStack);
                }
              else
                return yyflag;
            }

          if (yyisShiftAction (yyaction))
            break;
          else if (yyisErrorAction (yyaction))
            {
              YY_DPRINTF ((stderr, "Stack %ld dies.\n", YY_CAST (long, yyk)));
              yymarkStackDeleted (yystackp, yyk);
              break;
            }
          else
            {
              YYRESULTTAG yyflag = yyglrReduce (yystackp, yyk, -yyaction,
                                                yyimmediate[-yyaction], sql_string, sql_result, scanner);
              if (yyflag == yyerr)
                {
                  YY_DPRINTF ((stderr,
                               "Stack %ld dies "
                               "(predicate failure or explicit user error).\n",
                               YY_CAST (long, yyk)));
                  yymarkStackDeleted (yystackp, yyk);
                  break;
                }
              else if (yyflag != yyok)
                return yyflag;
            }
        }
    }
  return yyok;
}

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYSTACKP, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  */
static int
yypcontext_expected_tokens (const yyGLRStack* yystackp,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[yystackp->yytops.yystates[0]->yylrState];
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

static int
yy_syntax_error_arguments (const yyGLRStack* yystackp,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  yysymbol_kind_t yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
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
  if (yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yystackp,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}



static void
yyreportSyntaxError (yyGLRStack* yystackp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  if (yystackp->yyerrState != 0)
    return;
  {
  yybool yysize_overflow = yyfalse;
  char* yymsg = YY_NULLPTR;
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount
    = yy_syntax_error_arguments (yystackp, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    yyMemoryExhausted (yystackp);

  switch (yycount)
    {
#define YYCASE_(N, S)                   \
      case N:                           \
        yyformat = S;                   \
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
        YYPTRDIFF_T yysz
          = yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (YYSIZE_MAXIMUM - yysize < yysz)
          yysize_overflow = yytrue;
        else
          yysize += yysz;
      }
  }

  if (!yysize_overflow)
    yymsg = YY_CAST (char *, YYMALLOC (YY_CAST (YYSIZE_T, yysize)));

  if (yymsg)
    {
      char *yyp = yymsg;
      int yyi = 0;
      while ((*yyp = *yyformat))
        {
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
      yyerror (&yylloc, sql_string, sql_result, scanner, yymsg);
      YYFREE (yymsg);
    }
  else
    {
      yyerror (&yylloc, sql_string, sql_result, scanner, YY_("syntax error"));
      yyMemoryExhausted (yystackp);
    }
  }
  yynerrs += 1;
}

/* Recover from a syntax error on *YYSTACKP, assuming that *YYSTACKP->YYTOKENP,
   yylval, and yylloc are the syntactic category, semantic value, and location
   of the lookahead.  */
static void
yyrecoverSyntaxError (yyGLRStack* yystackp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  if (yystackp->yyerrState == 3)
    /* We just shifted the error token and (perhaps) took some
       reductions.  Skip tokens until we can proceed.  */
    while (yytrue)
      {
        yysymbol_kind_t yytoken;
        int yyj;
        if (yychar == YYEOF)
          yyFail (yystackp, &yylloc, sql_string, sql_result, scanner, YY_NULLPTR);
        if (yychar != YYEMPTY)
          {
            /* We throw away the lookahead, but the error range
               of the shifted error token must take it into account.  */
            yyGLRState *yys = yystackp->yytops.yystates[0];
            yyGLRStackItem yyerror_range[3];
            yyerror_range[1].yystate.yyloc = yys->yyloc;
            yyerror_range[2].yystate.yyloc = yylloc;
            YYLLOC_DEFAULT ((yys->yyloc), yyerror_range, 2);
            yytoken = YYTRANSLATE (yychar);
            yydestruct ("Error: discarding",
                        yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
            yychar = YYEMPTY;
          }
        yytoken = yygetToken (&yychar, yystackp, sql_string, sql_result, scanner);
        yyj = yypact[yystackp->yytops.yystates[0]->yylrState];
        if (yypact_value_is_default (yyj))
          return;
        yyj += yytoken;
        if (yyj < 0 || YYLAST < yyj || yycheck[yyj] != yytoken)
          {
            if (yydefact[yystackp->yytops.yystates[0]->yylrState] != 0)
              return;
          }
        else if (! yytable_value_is_error (yytable[yyj]))
          return;
      }

  /* Reduce to one stack.  */
  {
    YYPTRDIFF_T yyk;
    for (yyk = 0; yyk < yystackp->yytops.yysize; yyk += 1)
      if (yystackp->yytops.yystates[yyk] != YY_NULLPTR)
        break;
    if (yyk >= yystackp->yytops.yysize)
      yyFail (yystackp, &yylloc, sql_string, sql_result, scanner, YY_NULLPTR);
    for (yyk += 1; yyk < yystackp->yytops.yysize; yyk += 1)
      yymarkStackDeleted (yystackp, yyk);
    yyremoveDeletes (yystackp);
    yycompressStack (yystackp);
  }

  /* Pop stack until we find a state that shifts the error token.  */
  yystackp->yyerrState = 3;
  while (yystackp->yytops.yystates[0] != YY_NULLPTR)
    {
      yyGLRState *yys = yystackp->yytops.yystates[0];
      int yyj = yypact[yys->yylrState];
      if (! yypact_value_is_default (yyj))
        {
          yyj += YYSYMBOL_YYerror;
          if (0 <= yyj && yyj <= YYLAST && yycheck[yyj] == YYSYMBOL_YYerror
              && yyisShiftAction (yytable[yyj]))
            {
              /* Shift the error token.  */
              int yyaction = yytable[yyj];
              /* First adjust its location.*/
              YYLTYPE yyerrloc;
              yystackp->yyerror_range[2].yystate.yyloc = yylloc;
              YYLLOC_DEFAULT (yyerrloc, (yystackp->yyerror_range), 2);
              YY_SYMBOL_PRINT ("Shifting", yy_accessing_symbol (yyaction),
                               &yylval, &yyerrloc);
              yyglrShift (yystackp, 0, yyaction,
                          yys->yyposn, &yylval, &yyerrloc);
              yys = yystackp->yytops.yystates[0];
              break;
            }
        }
      yystackp->yyerror_range[1].yystate.yyloc = yys->yyloc;
      if (yys->yypred != YY_NULLPTR)
        yydestroyGLRState ("Error: popping", yys, sql_string, sql_result, scanner);
      yystackp->yytops.yystates[0] = yys->yypred;
      yystackp->yynextFree -= 1;
      yystackp->yyspaceLeft += 1;
    }
  if (yystackp->yytops.yystates[0] == YY_NULLPTR)
    yyFail (yystackp, &yylloc, sql_string, sql_result, scanner, YY_NULLPTR);
}

#define YYCHK1(YYE)                             \
  do {                                          \
    switch (YYE) {                              \
    case yyok:     break;                       \
    case yyabort:  goto yyabortlab;             \
    case yyaccept: goto yyacceptlab;            \
    case yyerr:    goto yyuser_error;           \
    case yynomem:  goto yyexhaustedlab;         \
    default:       goto yybuglab;               \
    }                                           \
  } while (0)

/*----------.
| yyparse.  |
`----------*/

int
yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  int yyresult;
  yyGLRStack yystack;
  yyGLRStack* const yystackp = &yystack;
  YYPTRDIFF_T yyposn;

  YY_DPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY;
  yylval = yyval_default;
  yylloc = yyloc_default;

  if (! yyinitGLRStack (yystackp, YYINITDEPTH))
    goto yyexhaustedlab;
  switch (YYSETJMP (yystack.yyexception_buffer))
    {
    case 0: break;
    case 1: goto yyabortlab;
    case 2: goto yyexhaustedlab;
    default: goto yybuglab;
    }
  yyglrShift (&yystack, 0, 0, 0, &yylval, &yylloc);
  yyposn = 0;

  while (yytrue)
    {
      /* For efficiency, we have two loops, the first of which is
         specialized to deterministic operation (single stack, no
         potential ambiguity).  */
      /* Standard mode. */
      while (yytrue)
        {
          yy_state_t yystate = yystack.yytops.yystates[0]->yylrState;
          YY_DPRINTF ((stderr, "Entering state %d\n", yystate));
          if (yystate == YYFINAL)
            goto yyacceptlab;
          if (yyisDefaultedState (yystate))
            {
              yyRuleNum yyrule = yydefaultAction (yystate);
              if (yyrule == 0)
                {
                  yystack.yyerror_range[1].yystate.yyloc = yylloc;
                  yyreportSyntaxError (&yystack, sql_string, sql_result, scanner);
                  goto yyuser_error;
                }
              YYCHK1 (yyglrReduce (&yystack, 0, yyrule, yytrue, sql_string, sql_result, scanner));
            }
          else
            {
              yysymbol_kind_t yytoken = yygetToken (&yychar, yystackp, sql_string, sql_result, scanner);
              const short* yyconflicts;
              int yyaction = yygetLRActions (yystate, yytoken, &yyconflicts);
              if (*yyconflicts)
                /* Enter nondeterministic mode.  */
                break;
              if (yyisShiftAction (yyaction))
                {
                  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
                  yychar = YYEMPTY;
                  yyposn += 1;
                  yyglrShift (&yystack, 0, yyaction, yyposn, &yylval, &yylloc);
                  if (0 < yystack.yyerrState)
                    yystack.yyerrState -= 1;
                }
              else if (yyisErrorAction (yyaction))
                {
                  yystack.yyerror_range[1].yystate.yyloc = yylloc;
                  /* Issue an error message unless the scanner already
                     did. */
                  if (yychar != YYerror)
                    yyreportSyntaxError (&yystack, sql_string, sql_result, scanner);
                  goto yyuser_error;
                }
              else
                YYCHK1 (yyglrReduce (&yystack, 0, -yyaction, yytrue, sql_string, sql_result, scanner));
            }
        }

      /* Nondeterministic mode. */
      while (yytrue)
        {
          yysymbol_kind_t yytoken_to_shift;
          YYPTRDIFF_T yys;

          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            yystackp->yytops.yylookaheadNeeds[yys] = yychar != YYEMPTY;

          /* yyprocessOneStack returns one of three things:

              - An error flag.  If the caller is yyprocessOneStack, it
                immediately returns as well.  When the caller is finally
                yyparse, it jumps to an error label via YYCHK1.

              - yyok, but yyprocessOneStack has invoked yymarkStackDeleted
                (&yystack, yys), which sets the top state of yys to NULL.  Thus,
                yyparse's following invocation of yyremoveDeletes will remove
                the stack.

              - yyok, when ready to shift a token.

             Except in the first case, yyparse will invoke yyremoveDeletes and
             then shift the next token onto all remaining stacks.  This
             synchronization of the shift (that is, after all preceding
             reductions on all stacks) helps prevent double destructor calls
             on yylval in the event of memory exhaustion.  */

          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            YYCHK1 (yyprocessOneStack (&yystack, yys, yyposn, &yylloc, sql_string, sql_result, scanner));
          yyremoveDeletes (&yystack);
          if (yystack.yytops.yysize == 0)
            {
              yyundeleteLastStack (&yystack);
              if (yystack.yytops.yysize == 0)
                yyFail (&yystack, &yylloc, sql_string, sql_result, scanner, YY_("syntax error"));
              YYCHK1 (yyresolveStack (&yystack, sql_string, sql_result, scanner));
              YY_DPRINTF ((stderr, "Returning to deterministic operation.\n"));
              yystack.yyerror_range[1].yystate.yyloc = yylloc;
              yyreportSyntaxError (&yystack, sql_string, sql_result, scanner);
              goto yyuser_error;
            }

          /* If any yyglrShift call fails, it will fail after shifting.  Thus,
             a copy of yylval will already be on stack 0 in the event of a
             failure in the following loop.  Thus, yychar is set to YYEMPTY
             before the loop to make sure the user destructor for yylval isn't
             called twice.  */
          yytoken_to_shift = YYTRANSLATE (yychar);
          yychar = YYEMPTY;
          yyposn += 1;
          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            {
              yy_state_t yystate = yystack.yytops.yystates[yys]->yylrState;
              const short* yyconflicts;
              int yyaction = yygetLRActions (yystate, yytoken_to_shift,
                              &yyconflicts);
              /* Note that yyconflicts were handled by yyprocessOneStack.  */
              YY_DPRINTF ((stderr, "On stack %ld, ", YY_CAST (long, yys)));
              YY_SYMBOL_PRINT ("shifting", yytoken_to_shift, &yylval, &yylloc);
              yyglrShift (&yystack, yys, yyaction, yyposn,
                          &yylval, &yylloc);
              YY_DPRINTF ((stderr, "Stack %ld now in state %d\n",
                           YY_CAST (long, yys),
                           yystack.yytops.yystates[yys]->yylrState));
            }

          if (yystack.yytops.yysize == 1)
            {
              YYCHK1 (yyresolveStack (&yystack, sql_string, sql_result, scanner));
              YY_DPRINTF ((stderr, "Returning to deterministic operation.\n"));
              yycompressStack (&yystack);
              break;
            }
        }
      continue;
    yyuser_error:
      yyrecoverSyntaxError (&yystack, sql_string, sql_result, scanner);
      yyposn = yystack.yytops.yystates[0]->yyposn;
    }

 yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;

 yybuglab:
  YY_ASSERT (yyfalse);
  goto yyabortlab;

 yyabortlab:
  yyresult = 1;
  goto yyreturnlab;

 yyexhaustedlab:
  yyerror (&yylloc, sql_string, sql_result, scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;

 yyreturnlab:
  if (yychar != YYEMPTY)
    yydestruct ("Cleanup: discarding lookahead",
                YYTRANSLATE (yychar), &yylval, &yylloc, sql_string, sql_result, scanner);

  /* If the stack is well-formed, pop the stack until it is empty,
     destroying its entries as we go.  But free the stack regardless
     of whether it is well-formed.  */
  if (yystack.yyitems)
    {
      yyGLRState** yystates = yystack.yytops.yystates;
      if (yystates)
        {
          YYPTRDIFF_T yysize = yystack.yytops.yysize;
          YYPTRDIFF_T yyk;
          for (yyk = 0; yyk < yysize; yyk += 1)
            if (yystates[yyk])
              {
                while (yystates[yyk])
                  {
                    yyGLRState *yys = yystates[yyk];
                    yystack.yyerror_range[1].yystate.yyloc = yys->yyloc;
                    if (yys->yypred != YY_NULLPTR)
                      yydestroyGLRState ("Cleanup: popping", yys, sql_string, sql_result, scanner);
                    yystates[yyk] = yys->yypred;
                    yystack.yynextFree -= 1;
                    yystack.yyspaceLeft += 1;
                  }
                break;
              }
        }
      yyfreeGLRStack (&yystack);
    }

  return yyresult;
}

/* DEBUGGING ONLY */
#if YYDEBUG
/* Print *YYS and its predecessors. */
static void
yy_yypstack (yyGLRState* yys)
{
  if (yys->yypred)
    {
      yy_yypstack (yys->yypred);
      YY_FPRINTF ((stderr, " -> "));
    }
  YY_FPRINTF ((stderr, "%d@%ld", yys->yylrState, YY_CAST (long, yys->yyposn)));
}

/* Print YYS (possibly NULL) and its predecessors. */
static void
yypstates (yyGLRState* yys)
{
  if (yys == YY_NULLPTR)
    YY_FPRINTF ((stderr, "<null>"));
  else
    yy_yypstack (yys);
  YY_FPRINTF ((stderr, "\n"));
}

/* Print the stack #YYK.  */
static void
yypstack (yyGLRStack* yystackp, YYPTRDIFF_T yyk)
{
  yypstates (yystackp->yytops.yystates[yyk]);
}

/* Print all the stacks.  */
static void
yypdumpstack (yyGLRStack* yystackp)
{
#define YYINDEX(YYX)                                                    \
  YY_CAST (long,                                                        \
           ((YYX)                                                       \
            ? YY_REINTERPRET_CAST (yyGLRStackItem*, (YYX)) - yystackp->yyitems \
            : -1))

  yyGLRStackItem* yyp;
  for (yyp = yystackp->yyitems; yyp < yystackp->yynextFree; yyp += 1)
    {
      YY_FPRINTF ((stderr, "%3ld. ",
                   YY_CAST (long, yyp - yystackp->yyitems)));
      if (*YY_REINTERPRET_CAST (yybool *, yyp))
        {
          YY_ASSERT (yyp->yystate.yyisState);
          YY_ASSERT (yyp->yyoption.yyisState);
          YY_FPRINTF ((stderr, "Res: %d, LR State: %d, posn: %ld, pred: %ld",
                       yyp->yystate.yyresolved, yyp->yystate.yylrState,
                       YY_CAST (long, yyp->yystate.yyposn),
                       YYINDEX (yyp->yystate.yypred)));
          if (! yyp->yystate.yyresolved)
            YY_FPRINTF ((stderr, ", firstVal: %ld",
                         YYINDEX (yyp->yystate.yysemantics.yyfirstVal)));
        }
      else
        {
          YY_ASSERT (!yyp->yystate.yyisState);
          YY_ASSERT (!yyp->yyoption.yyisState);
          YY_FPRINTF ((stderr, "Option. rule: %d, state: %ld, next: %ld",
                       yyp->yyoption.yyrule - 1,
                       YYINDEX (yyp->yyoption.yystate),
                       YYINDEX (yyp->yyoption.yynext)));
        }
      YY_FPRINTF ((stderr, "\n"));
    }

  YY_FPRINTF ((stderr, "Tops:"));
  {
    YYPTRDIFF_T yyi;
    for (yyi = 0; yyi < yystackp->yytops.yysize; yyi += 1)
      YY_FPRINTF ((stderr, "%ld: %ld; ", YY_CAST (long, yyi),
                   YYINDEX (yystackp->yytops.yystates[yyi])));
    YY_FPRINTF ((stderr, "\n"));
  }
#undef YYINDEX
}
#endif

#undef yylval
#undef yychar
#undef yynerrs
#undef yylloc




#line 1509 "yacc_sql.y"

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
