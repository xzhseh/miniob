#include "sql/operator/update_logical_operator.h"

UpdateLogicalOperator::UpdateLogicalOperator(Table *table, const Value& value, int value_offset)
    : table_(table), value_(value), value_offset_(value_offset) {}