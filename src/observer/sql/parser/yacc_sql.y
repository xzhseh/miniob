
%{

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

%}

%define api.pure full
%define parse.error verbose
/** 启用位置标识 **/
%locations
%lex-param { yyscan_t scanner }
/** 这些定义了在yyparse函数中的参数 **/
%parse-param { const char * sql_string }
%parse-param { ParsedSqlResult * sql_result }
%parse-param { void * scanner }

//标识tokens
%token  SEMICOLON
        CREATE
        DROP
        TABLE
        TABLES
        INDEX
        CALC
        SELECT
        DESC
        SHOW
        SYNC
        INSERT
        DELETE
        UPDATE
        LBRACE
        RBRACE
        COMMA
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        INT_T
        STRING_T
        FLOAT_T
        DATE_T
        HELP
        EXIT
        DOT //QUOTE
        INTO
        VALUES
        FROM
        WHERE
        AND
        SET
        ON
        LOAD
        DATA
        INFILE
        EXPLAIN
        EQ
        LT
        GT
        LE
        GE
        NE
        NOT
        LIKE
        MIN
        MAX
        AVG
        SUM
        COUNT
        INNER
        JOIN
        ORDER
        BY
        ASC

/** union 中定义各种数据类型，真实生成的代码也是union类型，所以不能有非POD类型的数据 **/
%union {
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
  std::vector<std::string> *        relation_list;
  std::vector<JoinSqlNode> *        join_list;
  std::vector<UpdateValueNode> *    update_value_list;
  std::vector<OrderBySqlNode> *     order_by_list_type;
  char *                            string;
  int                               number;
  float                             floats;
  enum agg                          agg;
}

%token <number> NUMBER
%token <floats> FLOAT
%token <string> ID
%token <string> SSS
%token <string> DATE_STR
//非终结符

/** type 定义了各种解析后的结果输出的是什么类型。类型对应了 union 中的定义的成员变量名称 **/
%type <number>              type
%type <condition>           condition
%type <value>               value
%type <number>              number
%type <comp>                comp_op
%type <agg>                 agg
%type <rel_attr>            rel_attr
%type <attr_infos>          attr_def_list
%type <attr_info>           attr_def
%type <value_list>          value_list
%type <update_value_list>   update_value_list
%type <order_by_list_type>       order_by_clause
%type <order_by_list_type>       order_by_list
%type <order_by_list_type>       order_by_item
%type <condition_list>      where
%type <condition_list>      condition_list
%type <rel_attr_list>       select_attr
%type <relation_list>       rel_list
%type <rel_attr_list>       attr_list
%type <expression>          expression
%type <expression_list>     expression_list
%type <join_list>           inner_join_list
%type <join_list>           inner_join_constr
%type <sql_node>            calc_stmt
%type <sql_node>            select_stmt
%type <sql_node>            insert_stmt
%type <sql_node>            update_stmt
%type <sql_node>            delete_stmt
%type <sql_node>            create_table_stmt
%type <sql_node>            drop_table_stmt
%type <sql_node>            show_tables_stmt
%type <sql_node>            desc_table_stmt
%type <sql_node>            create_index_stmt
%type <sql_node>            drop_index_stmt
%type <sql_node>            sync_stmt
%type <sql_node>            begin_stmt
%type <sql_node>            commit_stmt
%type <sql_node>            rollback_stmt
%type <sql_node>            load_data_stmt
%type <sql_node>            explain_stmt
%type <sql_node>            set_variable_stmt
%type <sql_node>            help_stmt
%type <sql_node>            exit_stmt
%type <sql_node>            command_wrapper
// commands should be a list but I use a single command instead
%type <sql_node>            commands


%left '+' '-'
%left '*' '/'
%nonassoc UMINUS
%%

commands: command_wrapper opt_semicolon  //commands or sqls. parser starts here.
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>($1);
    sql_result->add_sql_node(std::move(sql_node));
  }
  ;

command_wrapper:
    calc_stmt
  | select_stmt
  | insert_stmt
  | update_stmt
  | delete_stmt
  | create_table_stmt
  | drop_table_stmt
  | show_tables_stmt
  | desc_table_stmt
  | create_index_stmt
  | drop_index_stmt
  | sync_stmt
  | begin_stmt
  | commit_stmt
  | rollback_stmt
  | load_data_stmt
  | explain_stmt
  | set_variable_stmt
  | help_stmt
  | exit_stmt
    ;

exit_stmt:      
    EXIT {
      (void) yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      $$ = new ParsedSqlNode(SCF_EXIT);
    };

help_stmt:
    HELP {
      $$ = new ParsedSqlNode(SCF_HELP);
    };

sync_stmt:
    SYNC {
      $$ = new ParsedSqlNode(SCF_SYNC);
    }
    ;

begin_stmt:
    TRX_BEGIN  {
      $$ = new ParsedSqlNode(SCF_BEGIN);
    }
    ;

commit_stmt:
    TRX_COMMIT {
      $$ = new ParsedSqlNode(SCF_COMMIT);
    }
    ;

rollback_stmt:
    TRX_ROLLBACK  {
      $$ = new ParsedSqlNode(SCF_ROLLBACK);
    }
    ;

drop_table_stmt:    /* drop table 语句的语法解析树 */
    DROP TABLE ID {
      $$ = new ParsedSqlNode(SCF_DROP_TABLE);
      $$->drop_table.relation_name = $3;
      free($3);
    };

show_tables_stmt:
    SHOW TABLES {
      $$ = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
    ;

desc_table_stmt:
    DESC ID  {
      $$ = new ParsedSqlNode(SCF_DESC_TABLE);
      $$->desc_table.relation_name = $2;
      free($2);
    }
    ;

create_index_stmt:    /* create index 语句的语法解析树 */
    CREATE INDEX ID ON ID LBRACE ID RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.index_name = $3;
      create_index.relation_name = $5;
      create_index.attribute_name = $7;
      free($3);
      free($5);
      free($7);
    }
    ;

drop_index_stmt:      /* drop index 语句的语法解析树 */
    DROP INDEX ID ON ID
    {
      $$ = new ParsedSqlNode(SCF_DROP_INDEX);
      $$->drop_index.index_name = $3;
      $$->drop_index.relation_name = $5;
      free($3);
      free($5);
    }
    ;
create_table_stmt:    /* create table 语句的语法解析树 */
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = $$->create_table;
      create_table.relation_name = $3;
      free($3);

      std::vector<AttrInfoSqlNode> *src_attrs = $6;

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
      }
      create_table.attr_infos.emplace_back(*$5);
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete $5;
    }
    ;
attr_def_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA attr_def attr_def_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<AttrInfoSqlNode>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;
attr_def:
    /* i.e., char(255) */
    ID type LBRACE number RBRACE {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = $4;
      free($1);
    }
    | ID type {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType) $2;
      $$->name = $1;
      $$->length = 4;
      free($1);
    }
    ;
number:
    NUMBER { $$ = $1; }
    ;
type:
    INT_T      { $$ = INTS; }
    | STRING_T { $$ = CHARS; }
    | FLOAT_T  { $$ = FLOATS; }
    | DATE_T   { $$ = DATE; }
    ;
insert_stmt:        /*insert   语句的语法解析树*/
    INSERT INTO ID VALUES LBRACE value value_list RBRACE 
    {
      $$ = new ParsedSqlNode(SCF_INSERT);
      $$->insertion.relation_name = $3;
      if ($7 != nullptr) {
        $$->insertion.values.swap(*$7);
      }
      $$->insertion.values.emplace_back(*$6);
      std::reverse($$->insertion.values.begin(), $$->insertion.values.end());
      delete $6;
      free($3);
    }
    ;

value_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA value value_list  { 
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<Value>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;
value:
    NUMBER {
      $$ = new Value(static_cast<int>($1));
      @$ = @1;
    }
    | FLOAT {
      $$ = new Value(static_cast<float>($1));
      @$ = @1;
    }
    | SSS {
      /* This is to eliminate the double/single quotes from the input string */
      char *tmp = common::substr($1, 1, strlen($1) - 2);
      $$ = new Value(tmp);
      free(tmp);
    }
    | DATE_STR {
      char *tmp = common::substr($1, 1, strlen($1) - 2);
      /* Note the length here is by default 10 */
      $$ = new Value(DATE, tmp);
      free(tmp);
    }
    ;
delete_stmt:    /*  delete 语句的语法解析树*/
    DELETE FROM ID where 
    {
      $$ = new ParsedSqlNode(SCF_DELETE);
      $$->deletion.relation_name = $3;
      if ($4 != nullptr) {
        $$->deletion.conditions.swap(*$4);
        delete $4;
      }
      free($3);
    }
    ;
update_stmt:      /*  update 语句的语法解析树*/
    UPDATE ID SET ID EQ value update_value_list where
    {
      $$ = new ParsedSqlNode(SCF_UPDATE);
      $$->update.relation_name = $2;

      UpdateValueNode node;
      node.attribute_name = $4;
      node.value = *$6;

      $$->update.update_values.emplace_back(node);

      if ($7 != nullptr) {
      	$$->update.update_values.insert($$->update.update_values.end(), $7->begin(), $7->end());
	delete $7;
      }

      if ($8!= nullptr) {
        $$->update.conditions.swap(*$8);
        delete $8;
      }
      free($2);
      free($4);
    }
    ;

update_value_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA ID EQ value update_value_list  {
      if ($5 != nullptr) {
	$$ = $5;
      } else {
	$$ = new std::vector<UpdateValueNode>;
      }
      UpdateValueNode node;
      node.attribute_name = $2;
      node.value = *$4;
      $$->emplace_back(node);
      delete $2;
      delete $4;
    }
;

select_stmt:        /*  select 语句的语法解析树*/
    SELECT select_attr FROM ID rel_list where order_by_clause
    {
      $$ = new ParsedSqlNode(SCF_SELECT);
      if ($2 != nullptr) {
        $$->selection.attributes.swap(*$2);
        delete $2;
      }
      if ($5 != nullptr) {
        $$->selection.relations.swap(*$5);
        delete $5;
      }
      $$->selection.relations.push_back($4);
      std::reverse($$->selection.relations.begin(), $$->selection.relations.end());

      if ($6 != nullptr) {
        $$->selection.conditions.swap(*$6);
        delete $6;
      }

      if($7 != nullptr) {
	$$->selection.order_bys.insert($$->selection.order_bys.end(),$7->begin(),$7->end());
	delete $7;
      }
      free($4);
    }
    |
    SELECT select_attr FROM ID inner_join_constr inner_join_list where order_by_clause
        {
          $$ = new ParsedSqlNode(SCF_SELECT);
          if ($2 != nullptr) {
            $$->selection.attributes.swap(*$2);
            delete $2;
          }
          $$->selection.relations.push_back($4);
          delete $4;

          $$->selection.relations.push_back((*$5)[0].relation_name);
          $$->selection.conditions.swap((*$5)[0].conditions);
          delete $5;

          if ($6 != nullptr) {
            std::reverse($6->begin(), $6->end());
	    for (auto &join_relation : *$6) {
	      $$->selection.relations.push_back(join_relation.relation_name);
	      for (auto &condition : join_relation.conditions) {
	      	$$->selection.conditions.emplace_back(condition);
	      }
	    }
	    delete $6;
	  }

          if ($7 != nullptr) {
            $$->selection.conditions.insert($$->selection.conditions.end(),$7->begin(),$7->end());
            delete $7;
          }

          if ($8 != nullptr) {
	    $$->selection.order_bys.insert($$->selection.order_bys.end(),$8->begin(),$8->end());
	    delete $8;
	  }
    }
    ;
inner_join_constr:
    INNER JOIN ID ON condition_list
    {
      $$ = new std::vector<JoinSqlNode>;
      JoinSqlNode join_node;
      join_node.relation_name = $3;
      join_node.conditions.swap(*$5);
      $$->emplace_back(join_node);
      free($3);
    };

inner_join_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | INNER JOIN ID ON condition_list inner_join_list
    {
      if ($6 != nullptr) {
	$$ = $6;
      } else {
	$$ = new std::vector<JoinSqlNode>;
      }
      JoinSqlNode join_node;
      join_node.relation_name = $3;
      join_node.conditions.swap(*$5);
      $$->emplace_back(join_node);
      free($3);
    }
    ;
order_by_clause:
   /* empty */
    {
	$$ = nullptr;
    }
    | ORDER BY order_by_list {
        $$ = $3;
    }
    ;

order_by_list:
    order_by_item {
        $$ = new std::vector<OrderBySqlNode>;
	$$->insert($$->begin(), (*$1).begin(), (*$1).end());
	delete $1;
    }
    | order_by_item COMMA order_by_list {
        if ($3 != nullptr) {
	    $$ = $3;
	} else {
	    $$ = new std::vector<OrderBySqlNode>;
	}
	$$->insert($$->begin(), (*$1).begin(), (*$1).end());
	delete $1;
    }
    ;

order_by_item:
    rel_attr {
        $$ = new std::vector<OrderBySqlNode>;
        OrderBySqlNode item;
        item.order_by_attributes.emplace_back(*$1);
        item.order_by_asc.emplace_back(true);
        $$->emplace_back(item);
        delete $1;
    }
    | rel_attr ASC {
         	$$ = new std::vector<OrderBySqlNode>;
                OrderBySqlNode item;
                item.order_by_attributes.emplace_back(*$1);
                item.order_by_asc.emplace_back(true);
                $$->emplace_back(item);
                delete $1;
    }
    | rel_attr DESC {
                $$ = new std::vector<OrderBySqlNode>;
                OrderBySqlNode item;
                item.order_by_attributes.emplace_back(*$1);
                item.order_by_asc.emplace_back(false);
                $$->emplace_back(item);
                delete $1;
    }
    ;

calc_stmt:
    CALC expression_list
    {
      $$ = new ParsedSqlNode(SCF_CALC);
      std::reverse($2->begin(), $2->end());
      $$->calc.expressions.swap(*$2);
      delete $2;
    }
    ;

expression_list:
    expression
    {
      $$ = new std::vector<Expression*>;
      $$->emplace_back($1);
    }
    | expression COMMA expression_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<Expression *>;
      }
      $$->emplace_back($1);
    }
    ;
expression:
    expression '+' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::ADD, $1, $3, sql_string, &@$);
    }
    | expression '-' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::SUB, $1, $3, sql_string, &@$);
    }
    | expression '*' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::MUL, $1, $3, sql_string, &@$);
    }
    | expression '/' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::DIV, $1, $3, sql_string, &@$);
    }
    | LBRACE expression RBRACE {
      $$ = $2;
      $$->set_name(token_name(sql_string, &@$));
    }
    | '-' expression %prec UMINUS {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, $2, nullptr, sql_string, &@$);
    }
    | value {
      $$ = new ValueExpr(*$1);
      $$->set_name(token_name(sql_string, &@$));
      delete $1;
    }
    ;

select_attr:
    '*' {
      $$ = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.relation_name  = "";
      attr.attribute_name = "*";
      attr.aggregate_func = agg::NONE;
      $$->emplace_back(attr);
    }
    // TODO: Add the syntax for cases like `select agg(c1), count(*) from t1;`
    | agg LBRACE '*' RBRACE attr_list {
      /* AGG_FUNC(*) */
      $$ = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.relation_name = "";
      attr.attribute_name = "*";
      attr.aggregate_func = $1;
      $$->emplace_back(attr);
      if ($5 != nullptr) {
        for (const auto &e : *$5) {
          $$->emplace_back(e);
        }
      }
      delete $5;
    }
    | rel_attr COMMA agg LBRACE '*' RBRACE {
      /* AGG_FUNC(*) */
      $$ = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.relation_name = "";
      attr.attribute_name = "*";
      attr.aggregate_func = $3;
      $$->emplace_back(attr);
      $$->emplace_back(*$1);
    }
    | rel_attr attr_list {
      /* Implicity AGG in `rel_attr` */
      if ($2 != nullptr) {
        $$ = $2;
      } else {
        $$ = new std::vector<RelAttrSqlNode>;
      }
      $$->emplace_back(*$1);
      delete $1;
    }
    // FIXME: Memory leak
    | agg LBRACE rel_attr COMMA rel_attr RBRACE {
      $$ = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.agg_valid_flag = false;
      $$->emplace_back(attr);
    }
    | agg LBRACE '*' COMMA rel_attr RBRACE {
      $$ = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.agg_valid_flag = false;
      $$->emplace_back(attr);
    }
    ;

agg:
    MIN {
      $$ = agg::AGG_MIN;
    }
    | MAX {
      $$ = agg::AGG_MAX;
    }
    | AVG {
      $$ = agg::AGG_AVG;
    }
    | SUM {
      $$ = agg::AGG_SUM;
    }
    | COUNT {
      $$ = agg::AGG_COUNT;
    }
    ;

rel_attr:
    ID {
      $$ = new RelAttrSqlNode;
      $$->relation_name = "";
      $$->attribute_name = $1;
      $$->aggregate_func = agg::NONE;
      free($1);
    }
    | ID DOT ID {
      $$ = new RelAttrSqlNode;
      $$->relation_name  = $1;
      $$->attribute_name = $3;
      $$->aggregate_func = agg::NONE;
      free($1);
      free($3);
    }
    | agg LBRACE ID RBRACE {
      $$ = new RelAttrSqlNode;
      $$->relation_name = "";
      $$->attribute_name = $3;
      $$->aggregate_func = $1;
      free($3);
    }
    | agg LBRACE ID DOT ID RBRACE {
      $$ = new RelAttrSqlNode;
      $$->relation_name = $3;
      $$->attribute_name = $5;
      $$->aggregate_func = $1;
      free($3);
      free($5);
    }
    // Invalid syntax, miniob requires the output to be FAILURE
    // So we must at least parse the syntax here 😅
    | agg LBRACE RBRACE {
      $$ = new RelAttrSqlNode;
      $$->agg_valid_flag = false;
    }
    ;

attr_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA rel_attr attr_list {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<RelAttrSqlNode>;
      }

      $$->emplace_back(*$2);
      delete $2;
    }
    ;

rel_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA ID rel_list {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<std::string>;
      }

      $$->push_back($2);
      free($2);
    }
    ;
where:
    /* empty */
    {
      $$ = nullptr;
    }
    | WHERE condition_list {
      $$ = $2;  
    }
    ;
condition_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | condition {
      $$ = new std::vector<ConditionSqlNode>;
      $$->emplace_back(*$1);
      delete $1;
    }
    | condition AND condition_list {
      $$ = $3;
      $$->emplace_back(*$1);
      delete $1;
    }
    ;
condition:
    rel_attr comp_op value
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = *$1;
      $$->right_is_attr = 0;
      $$->right_value = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }
    | value comp_op value 
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 0;
      $$->left_value = *$1;
      $$->right_is_attr = 0;
      $$->right_value = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }
    | rel_attr comp_op rel_attr
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = *$1;
      $$->right_is_attr = 1;
      $$->right_attr = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }
    | value comp_op rel_attr
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 0;
      $$->left_value = *$1;
      $$->right_is_attr = 1;
      $$->right_attr = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }
    ;

comp_op:
      EQ { $$ = EQUAL_TO; }
    | LT { $$ = LESS_THAN; }
    | GT { $$ = GREAT_THAN; }
    | LE { $$ = LESS_EQUAL; }
    | GE { $$ = GREAT_EQUAL; }
    | NE { $$ = NOT_EQUAL; }
    | LIKE { $$ = LIKE_OP;}
    | NOT LIKE { $$ = NOT_LIKE_OP;}
    ;

load_data_stmt:
    LOAD DATA INFILE SSS INTO TABLE ID 
    {
      char *tmp_file_name = common::substr($4, 1, strlen($4) - 2);
      
      $$ = new ParsedSqlNode(SCF_LOAD_DATA);
      $$->load_data.relation_name = $7;
      $$->load_data.file_name = tmp_file_name;
      free($7);
      free(tmp_file_name);
    }
    ;

explain_stmt:
    EXPLAIN command_wrapper
    {
      $$ = new ParsedSqlNode(SCF_EXPLAIN);
      $$->explain.sql_node = std::unique_ptr<ParsedSqlNode>($2);
    }
    ;

set_variable_stmt:
    SET ID EQ value
    {
      $$ = new ParsedSqlNode(SCF_SET_VARIABLE);
      $$->set_variable.name  = $2;
      $$->set_variable.value = *$4;
      free($2);
      delete $4;
    }
    ;

opt_semicolon: /*empty*/
    | SEMICOLON
    ;
%%
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
