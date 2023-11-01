#pragma once
#include <unordered_map>
#include <vector>
#include  "storage/record/record.h"
#include "table.h"
class FieldMeta;
class Table;
class ViewMeta {
    public:
    ViewMeta() = default;
    std::unordered_map<RID, std::vector<RID>, RID::HashFunction, RID::EqualityFunction> rid_map;
    std::vector<Table*> tables;
    std::vector<const FieldMeta*> fields; 
};