/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Meiyi
//

#pragma once

#include <stddef.h>
#include <cassert>
#include <memory>
#include <string>
#include <vector>

#include "sql/parser/value.h"

class Expression;

/// Built-in functions
enum func { FUNC_NONE, FUNC_LENGTH, FUNC_ROUND, FUNC_DATE_FORMAT };

inline std::string func_to_string(func f) {
  std::string ret{""};
  switch (f) {
    case func::FUNC_LENGTH: {
      ret = "length";
    } break;
    case func::FUNC_ROUND: {
      ret = "round";
    } break;
    case func::FUNC_DATE_FORMAT: {
      ret = "date_format";
    } break;
    default:
      assert(false);  // This is impossible
  }
  return ret;
}

/// Aggregate functions
enum agg { NONE, AGG_MIN, AGG_MAX, AGG_AVG, AGG_SUM, AGG_COUNT };

inline std::string agg_to_string(agg a) {
  std::string ret{""};
  switch (a) {
    case agg::AGG_MIN: {
      ret = "MIN";
    } break;
    case agg::AGG_MAX: {
      ret = "MAX";
    } break;
    case agg::AGG_AVG: {
      ret = "AVG";
    } break;
    case agg::AGG_SUM: {
      ret = "SUM";
    } break;
    case agg::AGG_COUNT: {
      ret = "COUNT";
    } break;
    default:
      assert(false);  // This is impossible
  }
  return ret;
}

/**
 * @defgroup SQLParser SQL Parser
 */

/**
 * @brief 描述一个属性
 * @ingroup SQLParser
 * @details 属性，或者说字段(column, field)
 * Rel -> Relation
 * Attr -> Attribute
 */
struct RelAttrSqlNode {
  std::string relation_name;   ///< relation / table name (may be NULL/EMPTY)
  std::string attribute_name;  ///< attribute / column name
  enum agg aggregate_func;     ///< aggregate function (may be NULL/EMPTY)
  bool agg_valid_flag{true};   ///< Whether the parsed aggregate syntax is valid, i.e., COUNT(c1, c2) will be invalid
  std::string alias_name;      ///< alias name (may be NULL/EMPTY)
  bool expr_flag{false};  ///< Whether this rel_attr should be seen / parsed as expression, i.e., arithmetic expression
  Expression *expression{nullptr};  ///< store the possible parsed expression
};

struct RelationSqlNode {
  std::string relation_name;
  std::string alias_name;
  bool is_parent{false};  // for sub query
};

struct IndexAttr {
  std::string attribute_name;
};

/**
 * @brief 描述比较运算符
 * @ingroup SQLParser
 */
enum CompOp {
  EQUAL_TO,     ///< "="
  LESS_EQUAL,   ///< "<="
  NOT_EQUAL,    ///< "<>"
  LESS_THAN,    ///< "<"
  GREAT_EQUAL,  ///< ">="
  GREAT_THAN,   ///< ">"
  LIKE_OP,      ///< "LIKE"
  NOT_LIKE_OP,  ///< "NOT LIKE"
  IS,
  IS_NOT,
  IN_OP,
  NOT_IN,
  EXISTS_OP,
  NOT_EXISTS,
  NO_OP
};

struct SelectSqlNode;
/**
 * @brief 表示一个条件比较
 * @ingroup SQLParser
 * @details 条件比较就是SQL查询中的 where a>b 这种。
 * 一个条件比较是有两部分组成的，称为左边和右边。
 * 左边和右边理论上都可以是任意的数据，比如是字段（属性，列），也可以是数值常量。
 * 这个结构中记录的仅仅支持字段和值。
 */
struct ConditionSqlNode {
  int left_is_attr;                    ///< TRUE if left-hand side is an attribute
                                       ///< 1时，操作符左边是属性名，0时，是属性值
                                       ///< 2时，是子查询
                                       ///< 3时，是常量列表
  std::vector<Value> left_value_list;  ///< const value list for IN/NOT IN,EXISTS/NOT EXISTS
  SelectSqlNode *left_sub_select = {nullptr};
  Value left_value;          ///< left-hand side value if left_is_attr = FALSE
  RelAttrSqlNode left_attr;  ///< left-hand side attribute
  CompOp comp;               ///< comparison operator
  bool is_and{true};
  int right_is_attr;          ///< TRUE if right-hand side is an attribute
                              ///< 1时，操作符右边是属性名，0时，是属性值
                              ///< 2时，是子查询
                              ///< 3时，是常量列表
  RelAttrSqlNode right_attr;  ///< right-hand side attribute if right_is_attr = TRUE 右边的属性
  Value right_value;          ///< right-hand side value if right_is_attr = FALSE

  std::vector<Value> right_value_list;  ///< const value list for IN/NOT IN,EXISTS/NOT EXISTS
  // Use unique_ptr will cause compile error,hard to handle
  // The memory will leak, but it doesn't matter
  SelectSqlNode *right_sub_select{nullptr};  ///< sub select for IN/NOT IN,EXISTS/NOT EXISTS
  // If the two expressions here is not nullptr, then we will evaluate the where clause based on pure expression
  // Specifically by `get_value`
  Expression *left_expr{nullptr};
  Expression *right_expr{nullptr};

  Expression *left_func_expr{nullptr};
  Expression *right_func_expr{nullptr};
};

struct OrderBySqlNode {
  std::vector<RelAttrSqlNode> order_by_attributes;  ///< order by attributes
  std::vector<bool> order_by_asc;                   ///< order by asc or desc
};

/**
 * @brief 描述一个select语句
 * @ingroup SQLParser
 * @details 一个正常的select语句描述起来比这个要复杂很多，这里做了简化。
 * 一个select语句由三部分组成，分别是select, from, where。
 * select部分表示要查询的字段，from部分表示要查询的表，where部分表示查询的条件。
 * 比如 from 中可以是多个表，也可以是另一个查询语句，这里仅仅支持表，也就是 relations。
 * where 条件 conditions，这里表示使用AND串联起来多个条件。正常的SQL语句会有OR，NOT等，
 * 甚至可以包含复杂的表达式。
 */
struct AttrInfoSqlNode;
struct SelectSqlNode {
  std::vector<RelAttrSqlNode> attributes;    ///< attributes in select clause
  std::vector<RelationSqlNode> relations;    ///< 查询的表
  std::vector<ConditionSqlNode> conditions;  ///< 查询条件，使用AND串联起来多个条件
  std::vector<OrderBySqlNode> order_bys;     ///< order by clause
  std::vector<RelAttrSqlNode> group_bys;     ///< group by clause
  ConditionSqlNode having;                   ///< Currently treat it as a single condition node
  std::vector<Expression *> expressions;     ///< expressions in select clause
  std::vector<ConditionSqlNode *>
      where_expr_vec;  ///< expression in where clause, all needs to be evaluated for filtering
  bool select_expr_flag{false};
  bool where_expr_flag{false};
  // The void * is Tuple *
  std::vector<void *> context_tuples;  ///< context tuples for sub query
  std::string create_table_name = "";
  std::string create_view_name = "";
  std::vector<AttrInfoSqlNode> attr_infos;
  bool func_fast_path{false};

  SelectSqlNode() = default;
  SelectSqlNode(const SelectSqlNode &other) = default;
};

/**
 * @brief 算术表达式计算的语法树
 * @ingroup SQLParser
 */
struct CalcSqlNode {
  std::vector<Expression *> expressions;  ///< calc clause

  ~CalcSqlNode();
};

/**
 * @brief 描述一个insert语句
 * @ingroup SQLParser
 * @details 于Selects类似，也做了很多简化
 */
struct InsertSqlNode {
  std::string relation_name;  ///< Relation to insert into
  std::vector<Value> values;  ///< 要插入的值
};

/**
 * @brief 描述一个join语句
 */
struct JoinSqlNode {
  std::string relation_name;                 ///< Relation to join
  std::vector<ConditionSqlNode> conditions;  ///< Join conditions
};

/**
 * @brief 描述一个delete语句
 * @ingroup SQLParser
 */
struct DeleteSqlNode {
  std::string relation_name;  ///< Relation to delete from
  std::vector<ConditionSqlNode> conditions;
};

struct UpdateValueNode {
  std::string attribute_name;  ///< 更新的字段
  Value value;                 ///< 更新的值
  SelectSqlNode *sub_query{nullptr};
};

;
/**
 * @brief 描述一个update语句
 * @ingroup SQLParser
 */
struct UpdateSqlNode {
  std::string relation_name;                   ///< Relation to update
  std::vector<UpdateValueNode> update_values;  ///< 更新的值
  std::vector<ConditionSqlNode> conditions;
};

/**
 * @brief 描述一个属性
 * @ingroup SQLParser
 * @details 属性，或者说字段(column, field)
 * Rel -> Relation
 * Attr -> Attribute
 */
struct AttrInfoSqlNode {
  AttrType type;     ///< Type of attribute
  std::string name;  ///< Attribute name
  size_t length;     ///< Length of attribute
  // Mysql default the new field is null
  bool is_null;
};

/**
 * @brief 描述一个create table语句
 * @ingroup SQLParser
 * @details 这里也做了很多简化。
 */
struct CreateTableSqlNode {
  std::string relation_name;                ///< Relation name
  std::vector<AttrInfoSqlNode> attr_infos;  ///< attributes
};

/**
 * @brief 描述一个drop table语句
 * @ingroup SQLParser
 */
struct DropTableSqlNode {
  std::string relation_name;  ///< 要删除的表名
};

/**
 * @brief 描述一个create index语句
 * @ingroup SQLParser
 * @details 创建索引时，需要指定索引名，表名，字段名。
 * 正常的SQL语句中，一个索引可能包含了多个字段，这里仅支持一个字段。
 */
struct CreateIndexSqlNode {
  std::string index_name;                  ///< Index name
  std::vector<IndexAttr> attribute_names;  ///< attributes in create index
  std::string relation_name;               ///< Relation name
  bool is_unique;                          ///< unique flag
};

/**
 * @brief 描述一个drop index语句
 * @ingroup SQLParser
 */
struct DropIndexSqlNode {
  std::string index_name;     ///< Index name
  std::string relation_name;  ///< Relation name
};

/**
 * @brief 描述一个desc table语句
 * @ingroup SQLParser
 * @details desc table 是查询表结构信息的语句
 */
struct DescTableSqlNode {
  std::string relation_name;
};

/**
 * @brief 描述一个load data语句
 * @ingroup SQLParser
 * @details 从文件导入数据到表中。文件中的每一行就是一条数据，每行的数据类型、字段个数都与表保持一致
 */
struct LoadDataSqlNode {
  std::string relation_name;
  std::string file_name;
};

/**
 * @brief 设置变量的值
 * @ingroup SQLParser
 * @note 当前还没有查询变量
 */
struct SetVariableSqlNode {
  std::string name;
  Value value;
};

class ParsedSqlNode;

/**
 * @brief 描述一个explain语句
 * @ingroup SQLParser
 * @details 会创建operator的语句，才能用explain输出执行计划。
 * 一个command就是一个语句，比如select语句，insert语句等。
 * 可能改成SqlCommand更合适。
 */
struct ExplainSqlNode {
  std::unique_ptr<ParsedSqlNode> sql_node;
};

/**
 * @brief 解析SQL语句出现了错误
 * @ingroup SQLParser
 * @details 当前解析时并没有处理错误的行号和列号
 */
struct ErrorSqlNode {
  std::string error_msg;
  int line;
  int column;
};

/**
 * @brief 表示一个SQL语句的类型
 * @ingroup SQLParser
 */
enum SqlCommandFlag {
  SCF_ERROR = 0,
  SCF_CALC,
  SCF_SELECT,
  SCF_INSERT,
  SCF_UPDATE,
  SCF_DELETE,
  SCF_CREATE_TABLE,
  SCF_DROP_TABLE,
  SCF_CREATE_INDEX,
  SCF_DROP_INDEX,
  SCF_SYNC,
  SCF_SHOW_TABLES,
  SCF_DESC_TABLE,
  SCF_BEGIN,  ///< 事务开始语句，可以在这里扩展只读事务
  SCF_COMMIT,
  SCF_CLOG_SYNC,
  SCF_ROLLBACK,
  SCF_LOAD_DATA,
  SCF_HELP,
  SCF_EXIT,
  SCF_EXPLAIN,
  SCF_SET_VARIABLE,  ///< 设置变量
};

/**
 * @brief Represents a single SQL query being parsed by frontend
 * Will then be translated to statement / physical plan later
 * @ingroup SQLParser
 */
class ParsedSqlNode {
 public:
  enum SqlCommandFlag flag;
  ErrorSqlNode error;
  CalcSqlNode calc;
  SelectSqlNode selection;
  InsertSqlNode insertion;
  DeleteSqlNode deletion;
  UpdateSqlNode update;
  CreateTableSqlNode create_table;
  DropTableSqlNode drop_table;
  CreateIndexSqlNode create_index;
  DropIndexSqlNode drop_index;
  DescTableSqlNode desc_table;
  LoadDataSqlNode load_data;
  ExplainSqlNode explain;
  SetVariableSqlNode set_variable;

 public:
  ParsedSqlNode();
  explicit ParsedSqlNode(SqlCommandFlag flag);
};

/**
 * @brief Represents the SQL data after syntax / grammar parsing
 * @ingroup SQLParser
 */
class ParsedSqlResult {
 public:
  void add_sql_node(std::unique_ptr<ParsedSqlNode> sql_node);
  std::vector<std::unique_ptr<ParsedSqlNode>> &sql_nodes() { return sql_nodes_; }

 private:
  std::vector<std::unique_ptr<ParsedSqlNode>> sql_nodes_;  ///< 这里记录SQL命令。虽然看起来支持多个，但是当前仅处理一个
};
