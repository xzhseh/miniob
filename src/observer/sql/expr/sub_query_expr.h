//
// Created by susun on 23-10-23.
//
#pragma once

#ifndef MINIDB_SUB_QUERY_EXPR_H
#define MINIDB_SUB_QUERY_EXPR_H

#include <memory>
#include <string>
#include <vector>

#include "event/sql_event.h"
#include "expression.h"

enum class SubResultType {
  SUB_QUERY,
  CONST_VALUE_LIST,
  UNDEFINED,
};

// select * from t1 where a in (select a from t2);
// select * from t1 where a in (1,2,3);
class SubQueryExpr : public Expression {
 public:
  SubQueryExpr() = default;
  ~SubQueryExpr() override = default;

  explicit SubQueryExpr(const std::vector<Value> &const_value_list);
  explicit SubQueryExpr(const std::shared_ptr<ParsedSqlNode> &sub_query);

  [[nodiscard]] ExprType type() const override { return ExprType::SUB_QUERY; }

  [[nodiscard]] AttrType value_type() const override { return BOOLEANS; }

  RC get_value(const Tuple &tuple, Value &value) const override;

  RC in_or_not(const Value &value, const std::unique_ptr<Expression> &field_expr, bool &result) const;

  // ! Don't call this function, it will return RC::INTERNAL
  RC try_get_value(Value &value) const override;

  RC init();

 private:
  SubResultType type_{SubResultType::UNDEFINED};
  std::vector<Value> const_value_list;             // type == CONST_VALUE_LIST
  std::vector<std::unique_ptr<Tuple>> tuple_list;  // type == SUB_QUERY
  std::unique_ptr<SQLStageEvent> sub_query_event_{nullptr};
  bool inited_{false};
};

#endif  // MINIDB_SUB_QUERY_EXPR_H
