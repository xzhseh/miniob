//
// Created by susun on 23-10-19.
//

#include "sql/operator/order_by_logical_operator.h"
OrderByLogicalOperator::OrderByLogicalOperator(std::vector<OrderByExpr> order_by_stmts) {
  this->order_by_stmts_ = std::make_shared<std::vector<OrderByExpr>>(std::move(order_by_stmts));
}
