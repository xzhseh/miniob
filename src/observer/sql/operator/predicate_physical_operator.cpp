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
// Created by WangYunlai on 2022/6/27.
//

#include "sql/operator/predicate_physical_operator.h"
#include "common/log/log.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/field/field.h"
#include "storage/record/record.h"

PredicatePhysicalOperator::PredicatePhysicalOperator(std::unique_ptr<Expression> expr, bool is_where_expr) : expression_(std::move(expr)) {
  if (!is_where_expr) {
    ASSERT(expression_->value_type() == BOOLEANS, "predicate's expression should be BOOLEAN type");
  }
}

RC PredicatePhysicalOperator::open(Trx *trx) {
  if (children_.size() != 1) {
    LOG_WARN("predicate operator must has one child");
    return RC::INTERNAL;
  }

  return children_[0]->open(trx);
}

/// Return true if the condition is satisfied, false otherwise
bool filter(ConditionSqlNode *condition, Tuple &tuple) {
  Value lhs;
  Value rhs;

  std::cout << "current tuple: " << tuple.to_string() << std::endl;

  if (condition->left_expr->get_value(tuple, lhs) != RC::SUCCESS) {
    LOG_WARN("[filter] failed to get the left expr value, expr: %s", condition->left_expr->name().c_str());
  }
  if (condition->right_expr->get_value(tuple, rhs) != RC::SUCCESS) {
    LOG_WARN("[filter] failed to get the right expr value, expr: %s", condition->right_expr->name().c_str());
  }

  std::cout << "[filter] left_expr: " << condition->left_expr->name() << std::endl;
  std::cout << "[filter] right_expr: " << condition->right_expr->name() << std::endl;

  std::cout << "[filter] lhs: " << lhs.to_string() << std::endl;
  std::cout << "[filter] rhs: " << rhs.to_string() << std::endl;

  if (Value::check_null(lhs) || Value::check_null(rhs)) {
    return false;
  }

  switch (condition->comp) {
    case CompOp::EQUAL_TO: {
      return lhs.compare(rhs) == 0;
    }
    case CompOp::GREAT_EQUAL: {
      return lhs.compare(rhs) >= 0;
    }
    case CompOp::LESS_EQUAL: {
      return lhs.compare(rhs) <= 0;
    }
    case CompOp::GREAT_THAN: {
      return lhs.compare(rhs) > 0;
    }
    case CompOp::LESS_THAN: {
      return lhs.compare(rhs) < 0;
    }
    case CompOp::NOT_EQUAL: {
      return lhs.compare(rhs) != 0;
    }
    default: assert(false); // Not yet support
  }
}

RC PredicatePhysicalOperator::next() {
  RC rc = RC::SUCCESS;
  PhysicalOperator *oper = children_.front().get();

  while (RC::SUCCESS == (rc = oper->next())) {
    Tuple *tuple = oper->current_tuple();
    if (nullptr == tuple) {
      rc = RC::INTERNAL;
      LOG_WARN("failed to get tuple from operator");
      break;
    }

    if (where_expr_flag_) {
      // Should be expression filter
      bool filter_flag{false};

      for (auto *where_expr_ : where_expr_vec_) {
        if (!filter(where_expr_, *tuple)) {
          filter_flag = true;
          break;
        }
      }

      if (!filter_flag) {
        return RC::SUCCESS;
      } else {
        // Keep filtering out tuples until
        // the first tuple that satisfies the condition appears
        continue;
      }
    }

    Value value;
    rc = expression_->get_value(*tuple, value);
    if (rc != RC::SUCCESS) {
      return rc;
    }

    if (value.get_boolean()) {
      return rc;
    }
  }
  return rc;
}

RC PredicatePhysicalOperator::close() {
  children_[0]->close();
  return RC::SUCCESS;
}

Tuple *PredicatePhysicalOperator::current_tuple() { return children_[0]->current_tuple(); }
