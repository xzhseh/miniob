#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "sql/operator/physical_operator.h"
std::unordered_map<std::string, std::unique_ptr<PhysicalOperator> > view_rebuild_map;
void view_rebuild_function(std::string view_name);

