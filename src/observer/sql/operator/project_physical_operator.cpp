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
  if (func_fast_path_ && !fun_fast_path_flag_) {
    return RC::SUCCESS;
  }
  if (children_.empty() || fun_fast_path_flag_) {
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
  if (func_fast_path_) {
    assert(select_expr_flag_ && "[ProjectPhysicalOperator::current_tuple] expect `select_expr_flag_` to be true");
    fun_fast_path_flag_ = true;
    std::vector<Value> cells;
    for (auto *expr: select_expr_) {
      Value v;
      std::cout << "[ProjectPhysicalOperator::current_tuple::func_fast_path] current expr: " << expr->name() << std::endl;
      ValueListTuple t; // Just a placeholder
      RC rc = expr->get_value(t, v);
      if (rc != RC::SUCCESS) {
        LOG_WARN("[ProjectPhysicalOperator::current_tuple::func_fast_path] failed to get the value of expression");
        return nullptr;
      }
      cells.push_back(v);
    }
    expr_tuple_.set_cells(cells);
    return &expr_tuple_;
  }

  if (dynamic_cast<ValueListTuple *>(children_[0]->current_tuple()) != nullptr && !select_expr_flag_) {
    // The child is of type aggregation, produce the value tuple
    return children_[0]->current_tuple();
  }

  if (select_expr_flag_) {
    // Construct the `expr_tuple_`
    std::vector<Value> cells;
    std::vector<RID> rids;
    for (auto *expr : select_expr_) {
      Value v;
      // We do NOT support expr like id + age
      RID rid{-1, -1};
      RC rc = expr->get_value(*children_[0]->current_tuple(), v);
      std::cout << "[ProjectPhysicalOperator::current_tuple] current expr: " << expr->name() << " value: " << v.to_string() << std::endl;
      if (rc != RC::SUCCESS) {
        LOG_WARN("[ProjectPhysicalOperator::current_tuple] failed to get the value of expression");
        return nullptr;
      }
      // Try to find the correct rid
      // Note that value may be repetitive and is not unique, so this is currently a sample
      for (int i = 0; i < children_[0]->current_tuple()->cell_num(); ++i) {
        Value t_v;
        children_[0]->current_tuple()->cell_at(i, t_v);
        if (t_v.compare(v) == 0) {
          // This is the correct column for the current value
          rc = children_[0]->current_tuple()->cell_rid(i, rid);
          if (rc != RC::SUCCESS) {
            LOG_WARN("[ProjectPhysicalOperator::current_tuple] failed to get the rid of value: %s.", t_v.to_string().c_str());
            return nullptr;
          }
          break;
        }
      }
      cells.push_back(v);
      rids.push_back(rid);
    }
    expr_tuple_.set_cells(cells);
    bool updatable = false;
    RID rid_not_exist{-1, -1};
    for(int i = 0; i < rids.size(); i++) {
       if(rid_not_exist != rids[i]) {
        updatable = true;
        break;
       }
    } 
    expr_tuple_.set_updatable(updatable);
    expr_tuple_.set_rids(rids);
    return &expr_tuple_;
  }

  tuple_.set_tuple(children_[0]->current_tuple());
  // std::cout << "[project] Current tuple: " << tuple_.to_string() << std::endl;
  return &tuple_;
}

void ProjectPhysicalOperator::add_projection(const Table *table, const FieldMeta *field_meta) {
  // 对单表来说，展示的(alias) 字段总是字段名称，
  // 对多表查询来说，展示的alias 需要带表名字
  // std::cout << "add prjection"
  //           << " " << table->name();
  auto *spec = new TupleCellSpec(table->name(), field_meta->name(), field_meta->name());
  tuple_.add_cell_spec(spec);
}
