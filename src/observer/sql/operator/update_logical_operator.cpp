#include "sql/operator/update_logical_operator.h"

UpdateLogicalOperator::UpdateLogicalOperator(Table *table, std::vector<Value> values, std::vector<FieldMeta> field_meta)
    : table_(table), values_(values), field_metas_(field_meta)
{}
