//
// Created by susun on 23-10-19.
//

#ifndef MINIDB_ORDER_BY_LOGICAL_OPERATOR_H
#define MINIDB_ORDER_BY_LOGICAL_OPERATOR_H

#include "sql/expr/expression.h"
#include "sql/operator/logical_operator.h"
#include "sql/stmt/select_stmt.h"

struct OrderByExpr {
  std::unique_ptr<Expression> field_expr;
  bool asc;
};

class OrderByLogicalOperator : public LogicalOperator {
 public:
  explicit OrderByLogicalOperator(std::vector<OrderByExpr> order_by_stmts);

  ~OrderByLogicalOperator() override = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::ORDER_BY; }

  std::shared_ptr<std::vector<OrderByExpr>> order_by_exprs() const { return this->order_by_stmts_; }

 private:
  std::shared_ptr<std::vector<OrderByExpr>> order_by_stmts_;
};

#endif  // MINIDB_ORDER_BY_LOGICAL_OPERATOR_H
