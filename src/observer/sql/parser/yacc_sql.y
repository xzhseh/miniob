
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

%define api.pure true
/* %define api.pure full */
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
        TEXT_T
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
        UNIQUE
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
        NULL_IS
        OB_NULL
        ORDER
        BY
        ASC
        AS
        GROUP
        HAVING
	IN
	EXISTS
	OR

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
}

%token <number> NUMBER
%token <floats> FLOAT
%token <string> ID
%token <string> SSS
%token <string> DATE_STR
%token <string> ID_MINUS
%token <string> ID_DOT_ID_MINUS
%token <string> MIN_MINUS
%token <string> MAX_MINUS
%token <string> AVG_MINUS
%token <string> SUM_MINUS
%token <string> COUNT_MINUS
//非终结符

/** type 定义了各种解析后的结果输出的是什么类型。类型对应了 union 中的定义的成员变量名称 **/
%type <number>              type
%type <condition>           condition
%type <value>               value
%type <number>              number
%type <comp>                comp_op
%type <comp>                in_op
%type <index_attr>          index_attr
%type <index_attr_name_list>     index_attr_name_list 
%type <attr_name_list>      attr_name_list           
%type <agg>                 agg
%type <rel_attr>            rel_attr
%type <attr_infos>          attr_def_list
%type <attr_info>           attr_def
%type <value_list>          value_list
%type <update_value_list>   update_value_list
%type <order_by_list_type>  order_by_clause
%type <order_by_list_type>  order_by_list
%type <order_by_list_type>  order_by_item
%type <group_by_list_type>  group_by_clause
%type <group_by_list_type>  group_by_list
%type <condition>           having
%type <condition_list>      where
%type <condition_list>      condition_list
%type <rel_attr_list>       select_attr
%type <relation_list>       rel_list
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
%type <string>              option_as
// commands should be a list but I use a single command instead
%type <sql_node>            commands
%type <null>                null


%left '+' '-'
%left '*' '/'
%nonassoc UMINUS

// Enable glr-parser for ambiguity grammar
%glr-parser

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

create_index_stmt:    /*create index 语句的语法解析树*/
    CREATE INDEX ID ON ID LBRACE attr_name_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.index_name = $3;
      create_index.relation_name = $5;
      create_index.attribute_names.swap(*$7);
      create_index.is_unique = false;
      free($3);
      free($5);
      free($7);
    }
    |
    CREATE UNIQUE INDEX ID ON ID LBRACE attr_name_list RBRACE
    {
        $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
        CreateIndexSqlNode& create_index = $$->create_index;
        create_index.index_name = $4;
        create_index.relation_name = $6;
        create_index.attribute_names.swap(*$8);
        create_index.is_unique = true;
        free($4);
        free($6);
        free($8);
    }
    ;
attr_name_list:
    index_attr index_attr_name_list {
      if($2 != nullptr) {
        $$ = $2;
      } else {
        $$ = new std::vector<IndexAttr>;
      }
      $$->push_back(*$1);
      delete $1;
    }
    ;
index_attr:
  ID {
    $$ = new IndexAttr;
    $$->attribute_name = $1;
    free($1);
  }
  ;
index_attr_name_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA index_attr index_attr_name_list {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<IndexAttr>;
      }

      $$->emplace_back(*$2);
      delete $2;
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
    ID type LBRACE number RBRACE null {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      assert($2 == CHARS && "Expect char(number)");
      if ($6) {
        $$->length = $4 + 10;
      } else {
        $$->length = $4;
      }
      $$->is_null = $6;
      free($1);
    }
    | ID type null {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType) $2;
      $$->name = $1;
      if ($2 == CHARS && $3) {
        $$->length = 10;
      } else {
        $$->length = 4;
      }
      if($$->type == AttrType::TEXT) {
        $$->length = 65535; // need to change
      }
      $$->is_null = $3;
      free($1);
    }
    ;

null:
    // Could be empty
  {
    $$ = true;
  }
  | OB_NULL {
    $$ = true;
  }
  | NOT OB_NULL {
    // Note that we do NOT need to deal with `NOT NULL` here
    // Since this property will be enable if NULL is not explicitly declared
    $$ = false;
  }

number:
    NUMBER { $$ = $1; }
    ;

type:
    INT_T      { $$ = INTS; }
    | TEXT_T     { $$ = TEXT; }
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
    | OB_NULL {
      // Note that we can not get the actual schema of this column right here
      // Will adjust the value to the actual type later
      $$ = new Value(0);
      $$->set_null();
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
    | UPDATE ID SET ID EQ LBRACE select_stmt RBRACE update_value_list where
    {
        $$ = new ParsedSqlNode(SCF_UPDATE);
        $$->update.relation_name = $2;

        UpdateValueNode node;
        node.attribute_name = $4;
        node.sub_query = new SelectSqlNode($7->selection);

        $$->update.update_values.emplace_back(node);

        if ($9 != nullptr) {
            $$->update.update_values.insert($$->update.update_values.end(), $9->begin(), $9->end());
    	    delete $9;
        }

        if ($10!= nullptr) {
            $$->update.conditions.swap(*$10);
            delete $10;
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
    | COMMA ID EQ LBRACE select_stmt RBRACE update_value_list  {
      if ($7 != nullptr) {
      	$$ = $7;
      } else {
      	$$ = new std::vector<UpdateValueNode>;
      }
      UpdateValueNode node;
      node.attribute_name = $2;
      node.sub_query = new SelectSqlNode($5->selection);
      $$->emplace_back(node);
      delete $2;
      delete $5;
    }
;

select_stmt:        /*  select 语句的语法解析树*/
    // FIXME: Please ensure the order of group by and order by
    // Currently group by is placed after order by to prevent renaming issue.
    CREATE TABLE ID AS select_stmt {
      $$ = $5;
      $$->selection.create_table_name = $3;
    }
    |
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE select_stmt 
    {
      $$ = $8;
      $$->selection.create_table_name = $3;

      std::vector<AttrInfoSqlNode> *src_attrs = $6;

      if (src_attrs != nullptr) {
        $$->selection.attr_infos.swap(*src_attrs);
      }
      $$->selection.attr_infos.emplace_back(*$5);
      std::reverse($$->selection.attr_infos.begin(), $$->selection.attr_infos.end());
      delete $5;
    }
    |
    SELECT select_attr FROM ID option_as rel_list where order_by_clause group_by_clause having
    {
      $$ = new ParsedSqlNode(SCF_SELECT);

      if ($2 != nullptr) {
        $$->selection.attributes.swap(*$2);
        delete $2;
      }

      if ($6 != nullptr) {
        $$->selection.relations.swap(*$6);
        delete $6;
      }

      RelationSqlNode relation;
      relation.relation_name = $4;
      free($4);

      if($5 != nullptr) {
      	relation.alias_name = $5;
      	free($5);
      }

      $$->selection.relations.push_back(relation);
      std::reverse($$->selection.relations.begin(), $$->selection.relations.end());

      if ($7 != nullptr) {
        $$->selection.conditions.swap(*$7);
        delete $7;
      }

      if($8 != nullptr) {
        $$->selection.order_bys.insert($$->selection.order_bys.end(),$8->begin(),$8->end());
        delete $8;
      }

      if ($9 != nullptr) {
        $$->selection.group_bys.swap(*$9);
      }

      if ($10 != nullptr) {
        $$->selection.having = *$10;
        delete $10;
      } else {
        ConditionSqlNode having;
        // To mark the absence of having condition
        having.left_value.set_type(UNDEFINED);
        having.right_value.set_type(UNDEFINED);
        $$->selection.having = having;
      }
    }
    | SELECT select_attr FROM ID inner_join_constr inner_join_list where order_by_clause
        {
          $$ = new ParsedSqlNode(SCF_SELECT);
          if ($2 != nullptr) {
            $$->selection.attributes.swap(*$2);
            delete $2;
          }
          RelationSqlNode relation_node;
          relation_node.relation_name = $4;
          $$->selection.relations.push_back(relation_node);
          delete $4;

          RelationSqlNode join_relation_node;
          join_relation_node.relation_name = (*$5)[0].relation_name;
          $$->selection.relations.push_back(join_relation_node);
          $$->selection.conditions.swap((*$5)[0].conditions);
          delete $5;

          if ($6 != nullptr) {
            std::reverse($6->begin(), $6->end());
	    for (auto &join_relation : *$6) {
	      RelationSqlNode join_relation_node;
              join_relation_node.relation_name = join_relation.relation_name;
	      $$->selection.relations.push_back(join_relation_node);
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

group_by_clause:
    {
      $$ = nullptr;
    }
    | GROUP BY group_by_list {
      assert($3 != nullptr && "Expect `group_by_list` not to be null");
      $$ = $3;
    }
    ;

group_by_list:
    rel_attr {
      assert($1 != nullptr && "Expect `rel_attr` not to be null");

      $$ = new std::vector<RelAttrSqlNode>;
      $$->emplace_back(*$1);

      delete $1;
    }
    | rel_attr COMMA group_by_list {
      assert($1 != nullptr && $3 != nullptr && "Expect all item not to be null");

      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<RelAttrSqlNode>;
      }

      // Note that the order of group by item should be reversed
      // But since the order does not matter, just keep it simple at present
      $$->emplace_back(*$1);

      delete $1;
    }
    ;

having:
    {
      $$ = nullptr;
    }
    | HAVING condition {
      assert($2 != nullptr && "Expect having condition not to be nullptr");
      $$ = $2;
    }

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
    | rel_attr {
      // The actual field will be parsed in select statement
      $$ = new FieldExpr(*$1);
      $$->set_name(token_name(sql_string, &@$));
    }
    // Resolve cases like `id1-2 > 3`
    // FIXME: The below expressions have not been set name, we could set name if needed
    // i.e., f_expr->set_name(...)
    | ID_MINUS {
      char *ptr = strchr($1, '-');
      assert(ptr != nullptr && "Expect `ptr` not to be nullptr");
      *ptr = '\0';
      RelAttrSqlNode rel_attr;
      rel_attr.attribute_name = $1;
      rel_attr.aggregate_func = agg::NONE;
      FieldExpr *f_expr = new FieldExpr(rel_attr);
      int v = atoi(ptr + 1);
      Value value;
      value.set_int(v);
      ValueExpr *value_expr = new ValueExpr(value);
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::SUB, f_expr, value_expr, sql_string, &@$);
    }
    | ID_DOT_ID_MINUS {
          char *ptr = strchr($1, '-');
          assert(ptr != nullptr && "Expect `ptr` not to be nullptr");
          *ptr = '\0';
          char *ptr1 = strchr($1, '.');
          *ptr1 = '\0';
          RelAttrSqlNode rel_attr;
          rel_attr.relation_name = $1;
          rel_attr.attribute_name = (ptr1 + 1);
          rel_attr.aggregate_func = agg::NONE;
          FieldExpr *f_expr = new FieldExpr(rel_attr);
          int v = atoi(ptr + 1);
          Value value;
          value.set_int(v);
          ValueExpr *value_expr = new ValueExpr(value);
          $$ = create_arithmetic_expression(ArithmeticExpr::Type::SUB, f_expr, value_expr, sql_string, &@$);
        }
    // Resolve cases like `MIN(id1)-2 > 3`
    | MIN_MINUS {
          char *ptr = strchr($1, '-');
          assert(ptr != nullptr && "Expect `ptr` not to be nullptr");
          *(ptr - 1) = '\0';
          RelAttrSqlNode rel_attr;
          rel_attr.attribute_name = ($1 + 4);
          rel_attr.aggregate_func = AGG_MIN;
          FieldExpr *f_expr = new FieldExpr(rel_attr);
          int v = atoi(ptr + 1);
          Value value;
          value.set_int(v);
          ValueExpr *value_expr = new ValueExpr(value);
          $$ = create_arithmetic_expression(ArithmeticExpr::Type::SUB, f_expr, value_expr, sql_string, &@$);
        }
    | MAX_MINUS {
   char *ptr = strchr($1, '-');
             assert(ptr != nullptr && "Expect `ptr` not to be nullptr");
             *(ptr - 1) = '\0';
             RelAttrSqlNode rel_attr;
             rel_attr.attribute_name = ($1 + 4);
             rel_attr.aggregate_func = AGG_MAX;
             FieldExpr *f_expr = new FieldExpr(rel_attr);
             int v = atoi(ptr + 1);
             Value value;
             value.set_int(v);
             ValueExpr *value_expr = new ValueExpr(value);
             $$ = create_arithmetic_expression(ArithmeticExpr::Type::SUB, f_expr, value_expr, sql_string, &@$);
    }
    | SUM_MINUS {
   char *ptr = strchr($1, '-');
             assert(ptr != nullptr && "Expect `ptr` not to be nullptr");
             *(ptr - 1) = '\0';
             RelAttrSqlNode rel_attr;
             rel_attr.attribute_name = ($1 + 4);
             rel_attr.aggregate_func = AGG_SUM;
             FieldExpr *f_expr = new FieldExpr(rel_attr);
             int v = atoi(ptr + 1);
             Value value;
             value.set_int(v);
             ValueExpr *value_expr = new ValueExpr(value);
             $$ = create_arithmetic_expression(ArithmeticExpr::Type::SUB, f_expr, value_expr, sql_string, &@$);
    }
    | AVG_MINUS {
   char *ptr = strchr($1, '-');
             assert(ptr != nullptr && "Expect `ptr` not to be nullptr");
             *(ptr - 1) = '\0';
             RelAttrSqlNode rel_attr;
             rel_attr.attribute_name = ($1 + 4);
             rel_attr.aggregate_func = AGG_AVG;
             FieldExpr *f_expr = new FieldExpr(rel_attr);
             int v = atoi(ptr + 1);
             Value value;
             value.set_int(v);
             ValueExpr *value_expr = new ValueExpr(value);
             $$ = create_arithmetic_expression(ArithmeticExpr::Type::SUB, f_expr, value_expr, sql_string, &@$);
    }
    | COUNT_MINUS {
   char *ptr = strchr($1, '-');
             assert(ptr != nullptr && "Expect `ptr` not to be nullptr");
             *(ptr - 1) = '\0';
             RelAttrSqlNode rel_attr;
             rel_attr.attribute_name = ($1 + 6);
             rel_attr.aggregate_func = AGG_COUNT;
             FieldExpr *f_expr = new FieldExpr(rel_attr);
             int v = atoi(ptr + 1);
             Value value;
             value.set_int(v);
             ValueExpr *value_expr = new ValueExpr(value);
             $$ = create_arithmetic_expression(ArithmeticExpr::Type::SUB, f_expr, value_expr, sql_string, &@$);
    }
    ;

option_as:
    /* empty */
    {
      $$ = nullptr;
    }
    | AS ID {
      $$ = $2;
    }
    | ID {
      $$ = $1;
    }
    ;

select_attr:
    '*' option_as {
      $$ = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.relation_name  = "";
      attr.attribute_name = "*";
      attr.aggregate_func = agg::NONE;
      if($2 != nullptr) {
      	attr.agg_valid_flag = false;
      	free($2);
      }
      $$->emplace_back(attr);
    }
    // FIXME: Ensure the sequence / order of the final results
    | expression_list {
      $$ = new std::vector<RelAttrSqlNode>;
      for (auto *expr : *$1) {
        RelAttrSqlNode rel_attr;
        if (dynamic_cast<FieldExpr *>(expr) != nullptr) {
          // The expression is field expression
          rel_attr = dynamic_cast<FieldExpr *>(expr)->get_rel_attr();
        } else {
          rel_attr.expr_flag = true;
          rel_attr.expression = expr;
        }
        $$->push_back(rel_attr);
      }
    }
    // FIXME: Memory leak
    // Note that the following is only for invalid agg syntax
    | agg LBRACE rel_attr COMMA rel_attr RBRACE{
      $$ = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.agg_valid_flag = false;
      $$->emplace_back(attr);
    }
    | agg LBRACE '*' COMMA rel_attr RBRACE  {
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
    ID option_as {
      $$ = new RelAttrSqlNode;
      $$->relation_name = "";
      $$->attribute_name = $1;
      $$->aggregate_func = agg::NONE;
      if($2 != nullptr) {
      	$$->alias_name = $2;
      	free($2);
      }
      free($1);
    }
    | ID DOT ID option_as {
      $$ = new RelAttrSqlNode;
      $$->relation_name  = $1;
      $$->attribute_name = $3;
      $$->aggregate_func = agg::NONE;
      if($4 != nullptr) {
        $$->alias_name = $4;
        free($4);
      }
      free($1);
      free($3);
    }
    | ID DOT '*' {
      $$ = new RelAttrSqlNode;
      $$->relation_name = $1;
      $$->attribute_name = "*";
      $$->aggregate_func = agg::NONE;
      free($1);
    }
    // TODO : Add alias name for agg ?
    | agg LBRACE ID RBRACE option_as {
      $$ = new RelAttrSqlNode;
      $$->relation_name = "";
      $$->attribute_name = $3;
      $$->aggregate_func = $1;
      if($5 != nullptr)
      {
      	$$->alias_name = $5;
      	free($5);
      }
      free($3);
    }
    | agg LBRACE ID DOT ID RBRACE option_as {
      $$ = new RelAttrSqlNode;
      $$->relation_name = $3;
      $$->attribute_name = $5;
      $$->aggregate_func = $1;
      if($7 != nullptr) {
      	$$->alias_name = $7;
      	free($7);
      }
      free($3);
      free($5);
    }
    | agg LBRACE '*' RBRACE option_as {
      $$ = new RelAttrSqlNode;

      // Construct the aggregation attribute
      $$->relation_name = "";
      $$->attribute_name = "*";
      $$->aggregate_func = $1;

      if ($5 != nullptr) {
       $$->alias_name = $5;
       free($5);
      }
    }
    // Invalid syntax, miniob requires the output to be FAILURE
    // So we must at least parse the syntax here 😅
    | agg LBRACE RBRACE {
      $$ = new RelAttrSqlNode;
      $$->agg_valid_flag = false;
    }
    ;

rel_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA ID option_as rel_list {
      if ($4 != nullptr) {
        $$ = $4;
      } else {
        $$ = new std::vector<RelationSqlNode>;
      }
      RelationSqlNode relation;
      relation.relation_name = $2;
      if($3 != nullptr) {
      	relation.alias_name = $3;
      		free($3);
      }
      $$->push_back(relation);
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
      $1->is_and = true;
      $$->emplace_back(*$1);
      delete $1;
    }
    | condition OR condition_list {
      $$ = $3;
      $1->is_and = false;
      $$->emplace_back(*$1);
      delete $1;
    }
    ;

condition:
    expression comp_op expression {
      FieldExpr *f_lhs = dynamic_cast<FieldExpr *>($1);
      ValueExpr *v_lhs = dynamic_cast<ValueExpr *>($1);
      FieldExpr *f_rhs = dynamic_cast<FieldExpr *>($3);
      ValueExpr *v_rhs = dynamic_cast<ValueExpr *>($3);

      $$ = new ConditionSqlNode;

      if (f_lhs && f_rhs) {
        // Field comp Field
        $$->left_is_attr = 1;
        $$->right_is_attr = 1;

        $$->comp = $2;

        $$->left_attr = f_lhs->get_rel_attr();
        $$->right_attr = f_rhs->get_rel_attr();

        delete $1;
        delete $3;
      } else if (f_lhs && v_rhs) {
        // Field comp Value
        $$->left_is_attr = 1;
        $$->right_is_attr = 0;

        $$->comp = $2;

        $$->left_attr = f_lhs->get_rel_attr();
        $$->right_value = v_rhs->get_value();

        delete $1;
        delete $3;
      } else if (v_lhs && f_rhs) {
        // Value comp Field
        $$->left_is_attr = 0;
        $$->right_is_attr = 1;

        $$->comp = $2;

        $$->left_value = v_lhs->get_value();
        $$->right_attr = f_rhs->get_rel_attr();

        delete $1;
        delete $3;
      } else if (v_lhs && v_rhs) {
        // Value comp Value
        $$->left_is_attr = 0;
        $$->right_is_attr = 0;

        $$->comp = $2;

        $$->left_value = v_lhs->get_value();
        $$->right_value = v_rhs->get_value();

        delete $1;
        delete $3;
      } else if (f_lhs && (!f_rhs && !v_rhs)) {
        // Field comp Expression
        $$->left_is_attr = 1;
        $$->right_is_attr = 0;

        $$->comp = $2;

        $$->left_attr = f_lhs->get_rel_attr();
        $$->right_expr = $3;

        delete $1;
      } else if (v_lhs && (!f_rhs && !v_rhs)) {
        // Value comp Expression
        $$->left_is_attr = 0;
        $$->right_is_attr = 0;

        $$->comp = $2;

        $$->left_value = v_lhs->get_value();
        $$->right_expr = $3;

        delete $1;
      } else if ((!f_lhs && !v_lhs) && f_rhs) {
        // Expression comp Field
        $$->left_is_attr = 0;
        $$->right_is_attr = 1;

        $$->comp = $2;

        $$->left_expr = $1;
        $$->right_attr = f_rhs->get_rel_attr();

        delete $3;
      } else if ((!f_lhs && !v_lhs) && v_rhs) {
        // Expression comp Value
        $$->left_is_attr = 0;
        $$->right_is_attr = 0;

        $$->comp = $2;

        $$->left_expr = $1;
        $$->right_value = v_rhs->get_value();

        delete $3;
      } else if (!f_lhs && !v_lhs && !f_rhs && !v_rhs) {
        // Expression comp Expression
        $$->left_is_attr = 0;
        $$->right_is_attr = 0;

        $$->comp = $2;

        $$->left_expr = $1;
        $$->right_expr = $3;
      } else {
        assert(false && "This path is impossible");
      }
    }
    // | rel_attr in_op LBRACE select_stmt RBRACE
    | expression in_op LBRACE select_stmt RBRACE
    {
    FieldExpr *lhs = dynamic_cast<FieldExpr *>($1);
          assert(lhs != nullptr && "Expect lhs to be `FieldExpr *`");
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = lhs->get_rel_attr();
      $$->right_is_attr = 2;
      $$->right_sub_select = new SelectSqlNode($4->selection);
      $$->comp = $2;
      delete $1;
    }
    // | rel_attr in_op LBRACE value value_list RBRACE
    | expression in_op LBRACE value value_list RBRACE
    {
    FieldExpr *lhs = dynamic_cast<FieldExpr *>($1);
          assert(lhs != nullptr && "Expect lhs to be `FieldExpr *`");
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = lhs->get_rel_attr();
      $$->right_is_attr = 3;
      if($5 != nullptr) {
	$$->right_value_list.swap(*$5);
	delete $5;
      }
      $$->right_value_list.push_back(*$4);
      $$->comp = $2;
      delete $1;
      delete $4;
    }
    // | rel_attr comp_op LBRACE select_stmt RBRACE
    | expression comp_op LBRACE select_stmt RBRACE
    {
      FieldExpr *lhs = dynamic_cast<FieldExpr *>($1);
      assert(lhs != nullptr && "Expect lhs to be `FieldExpr *`");
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = lhs->get_rel_attr();
      $$->right_is_attr = 2;
      $$->right_sub_select = new SelectSqlNode($4->selection);
      $$->comp = $2;
      delete $1;
    }
    // | rel_attr comp_op LBRACE value value_list RBRACE
    | expression comp_op LBRACE value COMMA value value_list RBRACE
    {
      FieldExpr *lhs = dynamic_cast<FieldExpr *>($1);
      assert(lhs != nullptr && "Expect lhs to be `FieldExpr *`");
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = lhs->get_rel_attr();
      $$->right_is_attr = 3;
      if($7 != nullptr) {
      	$$->right_value_list.swap(*$7);
      	delete $7;
      }
      $$->right_value_list.push_back(*$6);
      $$->right_value_list.push_back(*$4);
      $$->comp = $2;
      delete $1;
      delete $4;
      delete $6;
      }
      | LBRACE select_stmt RBRACE comp_op rel_attr
      {
	$$ = new ConditionSqlNode;
	$$->left_is_attr = 2;
	$$->left_sub_select = new SelectSqlNode($2->selection);
	$$->right_is_attr = 1;
	$$->right_attr = *$5;
	$$->comp = $4;
	delete $5;
      }
      | LBRACE select_stmt RBRACE comp_op LBRACE select_stmt RBRACE
      {
      	$$ = new ConditionSqlNode;
      	$$->left_is_attr = 2;
      	$$->left_sub_select = new SelectSqlNode($2->selection);
      	$$->right_is_attr = 2;
      	$$->right_sub_select = new SelectSqlNode($6->selection);
      	$$->comp = $4;
      }
    ;

in_op:
    IN { $$ = IN_OP; }
    | NOT IN { $$ = NOT_IN; }
    | EXISTS { $$ = EXISTS_OP; }
    | NOT EXISTS { $$ = NOT_EXISTS; }
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
    | NULL_IS { $$ = IS; }
    | NULL_IS NOT { $$ = IS_NOT; }
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
