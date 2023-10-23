//
// Created by susun on 23-10-23.
//

#ifndef MINIDB_SUB_QUERY_EXPR_H
#define MINIDB_SUB_QUERY_EXPR_H

#include <memory>
#include <string>
#include <vector>

#include "event/sql_event.h"
#include "expression.h"

// select * from t1 where a in (select a from t2);
// select * from t1 where a in (1,2,3);
class SubQueryExpr : public Expression {
 public:
  SubQueryExpr() = default;
  virtual ~SubQueryExpr() = default;

  explicit SubQueryExpr(std::vector<Value> const_value_list);
  SubQueryExpr(std::unique_ptr<ParsedSqlNode> sub_query);

  ExprType type() const override { return ExprType::VALUE; }

  AttrType value_type() const override { return BOOLEANS; }

  RC get_value(const Tuple &tuple, Value &value) const override;

  RC try_get_value(Value &value) const override;

  void set_sub_query_result(const SubResult &sub_result) { sub_result_ = sub_result; }

 private:
  SubResult sub_result_;
  std::unique_ptr<SQLStageEvent> sub_query_event_{nullptr};
};

#endif  // MINIDB_SUB_QUERY_EXPR_H
