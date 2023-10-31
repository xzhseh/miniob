#include "table_view.h"

void view_rebuild_function(std::string view_name) {
    std::unique_ptr<PhysicalOperator>& oper = view_rebuild_map[view_name];
}