/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/5/22.
//

#include "sql/stmt/update_stmt.h"
#include "common/log/log.h"
#include "sql/expr/sub_query_expr.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

UpdateStmt::UpdateStmt(Table *table, std::vector<Value> values, std::vector<FieldMeta> field_meta,
                       FilterStmt *filter_stmt)
    : table_(table), values_(values), field_metas_(field_meta), filter_stmt_(filter_stmt) {}

RC get_sub_query_value(Db *db, const SelectSqlNode &sub_query, Value &value) {
  std::unordered_map<std::string, Table *> table_map;
  //  std::unordered_map<std::string, Table *> parent_table_map;
  //  std::vector<Table *> tables;
  //  RC rc = SelectStmt::resolve_tables(db, sub_query, tables, table_map, parent_table_map);
  //  if (rc != RC::SUCCESS) {
  //    LOG_WARN("failed to resolve tables. rc=%d:%s", rc, strrc(rc));
  //    return rc;
  //  }
  std::shared_ptr<ParsedSqlNode> sub_query_node(new ParsedSqlNode);
  sub_query_node->flag = SCF_SELECT;
  sub_query_node->selection = sub_query;
  SubQueryExpr sub_query_expr(sub_query_node, table_map);
  // Should return value
  sub_query_expr.set_return_value(true);
  return sub_query_expr.get_const_value(value);
}

RC UpdateStmt::create(Db *db, UpdateSqlNode &update, Stmt *&stmt) {
  const char *table_name = update.relation_name.c_str();
  if (nullptr == db || nullptr == table_name) {
    LOG_WARN("invalid argument. db=%p, table_name=%p",
        db, table_name);
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  const TableMeta &table_meta = table->table_meta();

  // field meta --> value
  // eg: update table_name set field1 = value1, field2 = value2 where condition
  std::vector<Value> values;
  std::vector<FieldMeta> field_metas;

  for (auto &[update_attr, update_value_node, update_sub_query] : update.update_values) {
    const FieldMeta *field_meta = table_meta.field(update_attr.c_str());
    if (nullptr == field_meta) {
      LOG_WARN("field not exist");
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }
    Value update_value;
    if (update_sub_query) {
      RC rc = get_sub_query_value(db, *update_sub_query, update_value);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to get sub query value. rc=%d:%s", rc, strrc(rc));
        return rc;
      }
      if (Value::check_null(update_value)) {
        update_value.set_null();
      }
    } else {
      update_value = update_value_node;
    }

    // Check if update_attr and update_value are of the same type
    AttrType field_type = field_meta->type();

    if (update_value.is_null()) {
      if (!field_meta->is_null()) {
        // If not null is either implicitly / explicitly enabled
        // The null can not be inserted into the field
        return RC::INVALID_ARGUMENT;
      }

      // Set the value to the hard-coded null value
      Value::set_null(update_value, field_type);
    }

    AttrType value_type = update_value.attr_type();
    if (value_type == CHARS && field_type == TEXT) {
      value_type = TEXT;
      field_type = TEXT;
      update_value.set_type(TEXT);
    }

    if (field_type != value_type) {
      Value cast_result;
      if (!update_value.cast_to(field_type, cast_result)) {
        LOG_WARN("failed to cast value. field_type=%d, value_type=%d", field_type, value_type);
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
      // Cast successfully
      update_value = cast_result;
    }
    values.push_back(update_value);
    field_metas.push_back(*field_meta);
  }

  // Generate the where condition filter
  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table *>(std::string(table_name), table));
  FilterStmt *filter_stmt = nullptr;
  // Update does not support alias
  std::vector<RelAttrSqlNode> empty_rel_attr;
  RC rc = FilterStmt::create(db,
                             table,
                             &table_map,
                             nullptr,
                             empty_rel_attr,
                             // Do nothing now, future support
                             std::vector<RelationSqlNode>(),
                             update.conditions.data(),
                             static_cast<int>(update.conditions.size()),
                             filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  // Create new update stmt
  stmt = new UpdateStmt(table, values, field_metas, filter_stmt);
  return RC::SUCCESS;
}
