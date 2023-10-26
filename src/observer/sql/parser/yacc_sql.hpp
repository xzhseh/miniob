/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_YACC_SQL_HPP_INCLUDED
# define YY_YY_YACC_SQL_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SEMICOLON = 258,               /* SEMICOLON  */
    CREATE = 259,                  /* CREATE  */
    DROP = 260,                    /* DROP  */
    TABLE = 261,                   /* TABLE  */
    TABLES = 262,                  /* TABLES  */
    INDEX = 263,                   /* INDEX  */
    CALC = 264,                    /* CALC  */
    SELECT = 265,                  /* SELECT  */
    DESC = 266,                    /* DESC  */
    SHOW = 267,                    /* SHOW  */
    SYNC = 268,                    /* SYNC  */
    INSERT = 269,                  /* INSERT  */
    DELETE = 270,                  /* DELETE  */
    UPDATE = 271,                  /* UPDATE  */
    LBRACE = 272,                  /* LBRACE  */
    RBRACE = 273,                  /* RBRACE  */
    COMMA = 274,                   /* COMMA  */
    TRX_BEGIN = 275,               /* TRX_BEGIN  */
    TRX_COMMIT = 276,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 277,            /* TRX_ROLLBACK  */
    INT_T = 278,                   /* INT_T  */
    STRING_T = 279,                /* STRING_T  */
    TEXT_T = 280,                  /* TEXT_T  */
    FLOAT_T = 281,                 /* FLOAT_T  */
    DATE_T = 282,                  /* DATE_T  */
    HELP = 283,                    /* HELP  */
    EXIT = 284,                    /* EXIT  */
    DOT = 285,                     /* DOT  */
    INTO = 286,                    /* INTO  */
    VALUES = 287,                  /* VALUES  */
    FROM = 288,                    /* FROM  */
    WHERE = 289,                   /* WHERE  */
    AND = 290,                     /* AND  */
    SET = 291,                     /* SET  */
    UNIQUE = 292,                  /* UNIQUE  */
    ON = 293,                      /* ON  */
    LOAD = 294,                    /* LOAD  */
    DATA = 295,                    /* DATA  */
    INFILE = 296,                  /* INFILE  */
    EXPLAIN = 297,                 /* EXPLAIN  */
    EQ = 298,                      /* EQ  */
    LT = 299,                      /* LT  */
    GT = 300,                      /* GT  */
    LE = 301,                      /* LE  */
    GE = 302,                      /* GE  */
    NE = 303,                      /* NE  */
    NOT = 304,                     /* NOT  */
    LIKE = 305,                    /* LIKE  */
    MIN = 306,                     /* MIN  */
    MAX = 307,                     /* MAX  */
    AVG = 308,                     /* AVG  */
    SUM = 309,                     /* SUM  */
    COUNT = 310,                   /* COUNT  */
    INNER = 311,                   /* INNER  */
    JOIN = 312,                    /* JOIN  */
    NULL_IS = 313,                 /* NULL_IS  */
    OB_NULL = 314,                 /* OB_NULL  */
    ORDER = 315,                   /* ORDER  */
    BY = 316,                      /* BY  */
    ASC = 317,                     /* ASC  */
    AS = 318,                      /* AS  */
    GROUP = 319,                   /* GROUP  */
    HAVING = 320,                  /* HAVING  */
    IN = 321,                      /* IN  */
    EXISTS = 322,                  /* EXISTS  */
    NUMBER = 323,                  /* NUMBER  */
    FLOAT = 324,                   /* FLOAT  */
    ID = 325,                      /* ID  */
    SSS = 326,                     /* SSS  */
    DATE_STR = 327,                /* DATE_STR  */
    UMINUS = 328                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 125 "yacc_sql.y"

  ParsedSqlNode *                   sql_node;
  ConditionSqlNode *                condition;
  Value *                           value;
  enum CompOp                       comp;
  RelAttrSqlNode *                  rel_attr;
  std::vector<AttrInfoSqlNode> *    attr_infos;
  AttrInfoSqlNode *                 attr_info;
  Expression *                      expression;
  std::vector<Expression *> *       expression_list;
  std::vector<Value> *              value_list;
  std::vector<ConditionSqlNode> *   condition_list;
  std::vector<RelAttrSqlNode> *     rel_attr_list;
  std::vector<IndexAttr> *          attr_name_list;
  IndexAttr*                        index_attr;
  std::vector<IndexAttr> *          index_attr_name_list;
  std::vector<RelationSqlNode> *    relation_list;
  std::vector<JoinSqlNode> *        join_list;
  std::vector<UpdateValueNode> *    update_value_list;
  std::vector<OrderBySqlNode> *     order_by_list_type;
  std::vector<RelAttrSqlNode> *     group_by_list_type;
  char *                            string;
  int                               number;
  float                             floats;
  enum agg                          agg;
  bool                              null;

#line 165 "yacc_sql.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif




int yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner);


#endif /* !YY_YY_YACC_SQL_HPP_INCLUDED  */
