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
// Created by WangYunlai on 2022/07/01.
//

#include "sql/operator/project_physical_operator.h"
#include "common/log/log.h"
#include "sql/expr/tuple.h"
#include "storage/record/record.h"
#include "storage/table/table.h"

RC ProjectPhysicalOperator::open(Trx *trx) {
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  PhysicalOperator *child = children_[0].get();
  RC rc = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  return RC::SUCCESS;
}

RC ProjectPhysicalOperator::next() {
  if (children_.empty()) {
    return RC::RECORD_EOF;
  }
  return children_[0]->next();
}

RC ProjectPhysicalOperator::close() {
  if (!children_.empty()) {
    children_[0]->close();
  }
  return RC::SUCCESS;
}
Tuple *ProjectPhysicalOperator::current_tuple() {
  // std::cout << "[project] Current children tuple: " << children_[0]->current_tuple()->to_string() << std::endl;
  if (dynamic_cast<ValueListTuple *>(children_[0]->current_tuple()) != nullptr) {
    // The child is of type aggregation, produce the value tuple
    return children_[0]->current_tuple();
  }

  if (select_expr_flag_) {
    // Construct the `expr_tuple_`
    std::vector<Value> cells;
    for (auto *expr: select_expr_) {
      Value v;
      RC rc = expr->get_value(*children_[0]->current_tuple(), v);
      if (rc != RC::SUCCESS) {
        LOG_WARN("[ProjectPhysicalOperator::current_tuple] failed to get the value of expression");
        return nullptr;
      }
      cells.push_back(v);
    }
    expr_tuple_.set_cells(cells);
    return &expr_tuple_;
  }

  tuple_.set_tuple(children_[0]->current_tuple());
  // std::cout << "[project] Current tuple: " << tuple_.to_string() << std::endl;
  return &tuple_;
}

void ProjectPhysicalOperator::add_projection(const Table *table, const FieldMeta *field_meta) {
  // 对单表来说，展示的(alias) 字段总是字段名称，
  // 对多表查询来说，展示的alias 需要带表名字
  auto *spec = new TupleCellSpec(table->name(), field_meta->name(), field_meta->name());
  tuple_.add_cell_spec(spec);
}
