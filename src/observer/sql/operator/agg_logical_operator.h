/// Create by Zihao Xu on 10/18/2023

#pragma once

#include "sql/operator/logical_operator.h"
#include "sql/parser/parse_defs.h"
#include "storage/field/field_meta.h"

class AggLogicalOperator : public LogicalOperator {
 public:
  AggLogicalOperator() = delete;

  explicit AggLogicalOperator(const std::vector<Field> &all_keys,
                              const std::vector<std::pair<const FieldMeta *, int>> &aggregate_keys,
                              const std::vector<agg> &aggregate_types);

  virtual ~AggLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::AGG; }

  auto get_all_keys() -> std::vector<Field> & { return all_keys_; }

  auto get_agg_keys() -> std::vector<std::pair<const FieldMeta *, int>> & { return aggregate_keys_; }

  auto get_agg_types() -> std::vector<agg> & { return aggregate_types_; }

 private:
  std::vector<Field> all_keys_;
  std::vector<std::pair<const FieldMeta *, int>> aggregate_keys_;
  std::vector<agg> aggregate_types_;
};