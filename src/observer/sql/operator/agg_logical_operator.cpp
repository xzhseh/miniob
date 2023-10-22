/// Create by Zihao Xu on 10/18/2023

#include "sql/operator/agg_logical_operator.h"

AggLogicalOperator::AggLogicalOperator(const std::vector<Field> &all_keys,
                                       const std::vector<std::pair<const FieldMeta *, int>> &aggregate_keys,
                                       const std::vector<agg> &aggregate_types)
    : all_keys_(std::move(all_keys)),
      aggregate_keys_(std::move(aggregate_keys)),
      aggregate_types_(std::move(aggregate_types)) {}