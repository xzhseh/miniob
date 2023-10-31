#pragma once
#include <unordered_map>
#include <vector>
#include  "record.h"
class FieldMeta;
class Table;
class ViewMeta {
    public:
    std::unordered_map<RID, std::vector<RID> > rid_map;
    std::vector<Table*> tables;
    std::vector<const FieldMeta*> fields; 
};