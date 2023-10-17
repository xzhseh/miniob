#pragma once

#include "sql/operator/logical_operator.h"

/**
 * @brief 逻辑算子，用于执行updaet语句
 * @ingroup LogicalOperator
 */
class UpdateLogicalOperator : public LogicalOperator 
{
public:
  UpdateLogicalOperator(Table *table, const Value& value, int value_offset);
  virtual ~UpdateLogicalOperator() = default;

  LogicalOperatorType type() const override
  {
    return LogicalOperatorType::UPDATE;
  }
  Table *table() const
  {
    return table_;
  }
  const Value& value() const
  {
    return value_;
  }
  int value_offset() const
  {
    return value_offset_;
  }

private:
  Table *table_ = nullptr;
  const Value& value_;
  int value_offset_ = 0;
};