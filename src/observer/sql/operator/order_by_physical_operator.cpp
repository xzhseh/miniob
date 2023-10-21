//
// Created by susun on 23-10-19.
//

#include "order_by_physical_operator.h"

#include <utility>
OrderByPhysicalOperator::OrderByPhysicalOperator(std::shared_ptr<std::vector<OrderByExpr>> order_by_exprs) {
  this->order_by_exprs_ = std::move(order_by_exprs);
}
RC OrderByPhysicalOperator::open(Trx *trx) {
  PhysicalOperator *child = children_[0].get();
  RC rc = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  return RC::SUCCESS;
}

RC OrderByPhysicalOperator::next() {
  if (children_.empty()) {
    return RC::RECORD_EOF;
  }
  if (construct_) {
    // 0 or 1
    if (result_tuples_.size() < 2) {
      return RC::RECORD_EOF;
    } else {
      result_tuples_.pop_back();
      return RC::SUCCESS;
    }
  }
  // Collect all the tuples from the child operator
  // and store them in the vector.
  RC rc;
  std::vector<std::unique_ptr<Tuple>> result_tuples;
  while ((rc = children_[0]->next()) == RC::SUCCESS) {
    auto copy_row_tuple = children_[0]->current_tuple()->copy();
    result_tuples.push_back(std::move(copy_row_tuple));
  }
  if (rc != RC::RECORD_EOF) {
    LOG_WARN("failed to get next tuple from child operator: %s", strrc(rc));
    return rc;
  }
  std::sort(result_tuples.begin(),
            result_tuples.end(),
            [this](const std::unique_ptr<Tuple> &left, const std::unique_ptr<Tuple> &right) {
              // Because we use pop_back() to get result
              return !this->compare_tuple(left, right);
            });
  this->result_tuples_ = std::move(result_tuples);
  construct_ = true;
  if (this->result_tuples_.size() == 0) {
    return RC::RECORD_EOF;
  } else {
    return RC::SUCCESS;
  }
}

RC OrderByPhysicalOperator::close() {
  if (!children_.empty()) {
    children_[0]->close();
  }
  return RC::SUCCESS;
}

Tuple *OrderByPhysicalOperator::current_tuple() {
  if (result_tuples_.empty()) {
    return nullptr;
  }
  return result_tuples_.back().get();
}

bool OrderByPhysicalOperator::compare_tuple(const std::unique_ptr<Tuple> &left, const std::unique_ptr<Tuple> &right) {
  // Range the order by stmt
  for (const auto &order_by_expr : *order_by_exprs_) {
    // Get the field value
    const auto &expr = order_by_expr.field_expr;
    const auto &is_asc = order_by_expr.asc;
    Value left_value, right_value;
    RC rc = expr->get_value(*left, left_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value from left tuple: %s", strrc(rc));
      return false;
    }
    rc = expr->get_value(*right, right_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value from right tuple: %s", strrc(rc));
      return false;
    }
    // Compare the value
    int compare_result = left_value.compare(right_value);
    if (compare_result == 0) {
      continue;
    }
    if (is_asc) {
      return compare_result < 0;
    } else {
      return compare_result > 0;
    }
  }
  return this->order_by_exprs_->back().asc;
}
