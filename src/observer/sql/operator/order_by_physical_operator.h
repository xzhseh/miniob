//
// Created by susun on 23-10-19.
//

#ifndef MINIDB_ORDER_BY_PHYSICAL_OPERATOR_H
#define MINIDB_ORDER_BY_PHYSICAL_OPERATOR_H

#include "order_by_logical_operator.h"
#include "physical_operator.h"

class OrderByPhysicalOperator : public PhysicalOperator {
 public:
  explicit OrderByPhysicalOperator(std::shared_ptr<std::vector<OrderByExpr>> order_by_exprs);

  ~OrderByPhysicalOperator() override = default;

  [[nodiscard]] PhysicalOperatorType type() const override { return PhysicalOperatorType::ORDER_BY; }

  [[nodiscard]] const auto &order_by_exprs() const { return order_by_exprs_; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;
  Tuple *current_tuple() override;

 private:
  bool compare_tuple(const std::unique_ptr<Tuple> &left, const std::unique_ptr<Tuple> &right);
  std::shared_ptr<std::vector<OrderByExpr>> order_by_exprs_;
  std::vector<std::unique_ptr<Tuple>> result_tuples_;
  bool construct_ = false;
};

#endif  // MINIDB_ORDER_BY_PHYSICAL_OPERATOR_H
