//
// Created by susun on 23-10-19.
//

#include "order_by_physical_operator.h"

#include <chrono>
#include <execution>
#include <utility>
#include "sql/parser/value.h"

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
  std::vector<SortItem> result_tuples;
  const size_t value_size = order_by_exprs_->size();
  // Start measuring the execution time
  auto start_time = std::chrono::steady_clock::now();
  while ((rc = children_[0]->next()) == RC::SUCCESS) {
    auto copy_row_tuple = children_[0]->current_tuple()->copy();
    std::vector<Value> values(value_size);
    for (size_t i = 0; i < value_size; i++) {
      const auto &expr = (*order_by_exprs_)[i].field_expr;
      rc = expr->get_value(*copy_row_tuple.get(), values[i]);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to get value from left tuple: %s", strrc(rc));
        return rc;
      }
    }
    result_tuples.emplace_back(SortItem{std::move(values), std::move(copy_row_tuple)});
  }
  // Stop measuring the execution time
  auto end_time = std::chrono::steady_clock::now();

  // Calculate the duration in milliseconds
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

  // Print the duration
  printf("Code execution time: %ld ms\n", duration);
  if (rc != RC::RECORD_EOF) {
    LOG_WARN("failed to get next tuple from child operator: %s", strrc(rc));
    return rc;
  }

  std::sort(std::execution::par_unseq,
            result_tuples.begin(),
            result_tuples.end(),
            [this](const SortItem &left, SortItem &right) {
              // Because we use pop_back() to get result
              return !this->compare_tuple(left, right);
            });
  // Stop measuring the execution time
  end_time = std::chrono::steady_clock::now();

  // Calculate the duration in milliseconds
  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

  // Print the duration
  LOG_WARN("Code execution time: %ld ms\n", duration);
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
  return result_tuples_.back().tuple.get();
}

bool OrderByPhysicalOperator::compare_tuple(const SortItem &left, const SortItem &right) {
  // Range the order by stmt
  for (size_t i = 0; i < order_by_exprs_->size(); i++) {
    const auto &order_by_expr = (*order_by_exprs_)[i];
    // Get the field value
    const auto &expr = order_by_expr.field_expr;
    const auto &is_asc = order_by_expr.asc;
    const auto &left_value = left.values[i];
    const auto &right_value = right.values[i];
    if (Value::check_null(left_value) && !Value::check_null(right_value)) {
      // NULL < NOT NULL
      // Regardless of ASC / DESC
      return (is_asc);
    } else if (!Value::check_null(left_value) && Value::check_null(right_value)) {
      // Same as above
      // NOT NULL > NULL
      return !(is_asc);
    } else if (Value::check_null(left_value) && Value::check_null(right_value)) {
      // NULL equal to NULL
      continue;
    }

    // Compare the value
    int compare_result = left_value.compare(right_value);
    if (compare_result == 0) {
      continue;
    }
    if (compare_result < 0) {
      // Left is less than right
      return is_asc;
    } else {
      // Left is greater than right
      return !is_asc;
    }
  }
  return true;
}
