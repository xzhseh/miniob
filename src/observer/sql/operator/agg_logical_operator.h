/// Create by Zihao Xu on 10/18/2023

#pragma once

#include "sql/operator/logical_operator.h"
#include "sql/parser/parse_defs.h"
#include "storage/field/field.h"
#include "storage/field/field_meta.h"

class AggLogicalOperator : public LogicalOperator {
 public:
  explicit AggLogicalOperator() = default;

  virtual ~AggLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::AGG; }

  auto get_fields() const -> const std::vector<Field> & { return fields_; }

  auto get_is_agg() const -> const std::vector<bool> & { return is_agg_; }

  auto get_agg_types() const -> const std::vector<agg> & { return agg_types_; }

  auto get_having() const -> const ConditionSqlNode & { return having_; }

  void set_fields(std::vector<Field> &&fields) { fields_ = std::move(fields); }

  void set_is_agg(std::vector<bool> &&is_agg) { is_agg_ = std::move(is_agg); }

  void set_agg_types(std::vector<agg> &&agg_types) { agg_types_ = std::move(agg_types); }

  void set_having(ConditionSqlNode &&having) { having_ = std::move(having); }

 private:
  std::vector<Field> fields_;
  std::vector<bool> is_agg_;
  std::vector<agg> agg_types_;
  ConditionSqlNode having_;
};