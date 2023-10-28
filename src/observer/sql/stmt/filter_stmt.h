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
// Created by Wangyunlai on 2022/5/22.
//

#pragma once

#include <unordered_map>
#include <vector>
#include "sql/expr/expression.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/stmt.h"

class Db;
class Table;
class FieldMeta;

enum class FilterObjType { ATTR, VALUE, VALUE_LIST, SUB_QUERY };

struct FilterObj {
  FilterObjType type;
  Field field;
  Value value;
  // Different usage , so we won't merge them into one.
  std::vector<Value> value_list;
  std::shared_ptr<ParsedSqlNode> sub_query{nullptr};
  std::unordered_map<std::string, Table *> table_map;

  void init_attr(const Field &field) {
    this->type = FilterObjType::ATTR;
    this->field = field;
  }

  void init_value(const Value &value) {
    this->type = FilterObjType::VALUE;
    this->value = value;
  }

  void init_value_list(const std::vector<Value> &value_list) {
    this->type = FilterObjType::VALUE_LIST;
    this->value_list = value_list;
  }

  void init_sub_query(std::shared_ptr<ParsedSqlNode> subQuery) {
    this->type = FilterObjType::SUB_QUERY;
    this->sub_query = std::move(subQuery);
  }
};

class FilterUnit {
 public:
  FilterUnit() = default;
  ~FilterUnit() {}

  void set_comp(CompOp comp) { comp_ = comp; }

  CompOp comp() const { return comp_; }

  void set_left(const FilterObj &obj) { left_ = obj; }
  void set_right(const FilterObj &obj) { right_ = obj; }

  const FilterObj &left() const { return left_; }
  const FilterObj &right() const { return right_; }

  void set_is_and(bool is_and) { is_and_ = is_and; }
  [[nodiscard]] bool is_and() const {
    assert(is_and_ != -1);
    return is_and_;
  }

 private:
  CompOp comp_ = NO_OP;
  // -1 is invalid, 0 is AND, 1 is OR
  int is_and_{-1};
  FilterObj left_;
  FilterObj right_;
};

/**
 * @brief Filter/谓词/过滤语句
 * @ingroup Statement
 */
class FilterStmt {
 public:
  FilterStmt() = default;
  virtual ~FilterStmt();

 public:
  [[nodiscard]] const std::vector<FilterUnit *> &filter_units() const { return filter_units_; }

 public:
  static RC create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
                   std::unordered_map<std::string, Table *> *parent_tables, const std::vector<RelAttrSqlNode> &rel_attr,
                   const std::vector<RelationSqlNode> &relations, const ConditionSqlNode *conditions, int condition_num,
                   FilterStmt *&stmt);

  static RC create_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
                               std::unordered_map<std::string, Table *> *parent_tables,
                               const std::vector<RelAttrSqlNode> &rel_attr,
                               const std::vector<RelationSqlNode> &relations, const ConditionSqlNode &condition,
                               FilterUnit *&filter_unit);

 private:
  std::vector<FilterUnit *> filter_units_;  // 默认当前都是AND关系
};

void resolve_sub_query(SelectSqlNode &sub_node, std::unordered_map<std::string, Table *> *table_map);
