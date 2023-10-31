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
// Created by Wangyunlai on 2022/6/5.
//

#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "common/rc.h"
#include "sql/expr/expression.h"
#include "sql/stmt/agg_stmt.h"
#include "sql/stmt/stmt.h"
#include "storage/field/field.h"

class FieldMeta;
class FilterStmt;
class Db;
class Table;

struct JoinStmt {
  Field left_field;
  Field right_field;
};

struct OrderByStmt {
  Field field;
  bool asc;
};

/**
 * @brief 表示select语句
 * @ingroup Statement
 */
class SelectStmt : public Stmt {
 public:
  SelectStmt() = default;
  ~SelectStmt() override;

  StmtType type() const override { return StmtType::SELECT; }

 public:
  static RC create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt);

 public:
  [[nodiscard]] const std::vector<Table *> &tables() const { return tables_; }
  [[nodiscard]] const std::vector<Field> &query_fields() const { return query_fields_; }
  [[nodiscard]] const std::vector<JoinStmt> &join_stmts() const { return join_stmts_; }
  [[nodiscard]] FilterStmt *filter_stmt() const { return filter_stmt_; }
  [[nodiscard]] const std::vector<OrderByStmt> &order_by() const { return order_by_; }
  static RC resolve_tables(Db *db, const SelectSqlNode &select_sql, std::vector<Table *> &tables,
                           std::unordered_map<std::string, Table *> &table_map,
                           std::unordered_map<std::string, Table *> &parent_table_map);

  AggStmt *agg_stmt() const { return agg_stmt_; }
  const std::vector<Expression *> & get_select_expr() const { return expressions_; }
  bool get_select_expr_flag() const { return select_expr_flag_; }
  const std::string create_table_name() const { return create_table_name_; }
  const std::string create_view_name() const {return create_view_name_;}
  const std::vector<AttrInfoSqlNode> get_attrs() const { return attrs; }

 private:
  std::vector<Field> query_fields_;
  std::vector<Table *> tables_;
  std::string create_table_name_;
  std::string create_view_name_;
  std::vector<AttrInfoSqlNode> attrs;
  std::vector<JoinStmt> join_stmts_;
  std::vector<OrderByStmt> order_by_;
  FilterStmt *filter_stmt_{nullptr};
  AggStmt *agg_stmt_{nullptr};
  // This will be propagated to projection operator
  std::vector<Expression *> expressions_;
  bool select_expr_flag_{false};
};
