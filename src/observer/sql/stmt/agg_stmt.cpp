/// Create by Zihao Xu on 10/18/2023

#include "sql/stmt/agg_stmt.h"

AggStmt::AggStmt(std::vector<std::pair<const FieldMeta *, int>> aggregate_keys, std::vector<agg> aggregate_types)
    : aggregate_keys_(std::move(aggregate_keys)), aggregate_types_(std::move(aggregate_types)) {}