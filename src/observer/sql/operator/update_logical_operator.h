#pragma once

#include "sql/operator/logical_operator.h"

/**
 * @brief 逻辑算子，用于执行updaet语句
 * @ingroup LogicalOperator
 */
class UpdateLogicalOperator : public LogicalOperator
{
public:
  UpdateLogicalOperator(Table *table, std::vector<Value> values, std::vector<FieldMeta> field_meta);

  virtual ~UpdateLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::UPDATE; }
  Table              *table() const { return table_; }

  const std::vector<Value>     &values() const { return values_; }
  const std::vector<FieldMeta> &field_meta() const { return field_metas_; }

private:
  Table                 *table_ = nullptr;
  std::vector<Value>     values_;
  std::vector<FieldMeta> field_metas_;
};