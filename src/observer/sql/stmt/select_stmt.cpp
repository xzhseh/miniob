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
// Created by Wangyunlai on 2022/6/6.
//

#include "sql/stmt/select_stmt.h"
#include "sql/stmt/agg_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/db/db.h"
#include "storage/field/field_meta.h"
#include "storage/table/table.h"

SelectStmt::~SelectStmt() {
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

/// Basically push all metadata from the specified table to the current `field_metas`
/// Use case: `select count(*) from t1 where t1.c1 = 1;`
static void wildcard_fields(Table *table, std::vector<Field> &field_metas) {
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num();
  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
    field_metas.push_back(Field(table, table_meta.field(i)));
  }
}

static void agg_builder_inner(
    std::vector<Field> &query_fields,
    int &agg_pos,
    std::vector<std::pair<const FieldMeta *, int>> &aggregate_keys,
    std::vector<agg> &aggregate_types,
    const RelAttrSqlNode &relation_attr,
    bool &agg_flag) {

  if (relation_attr.aggregate_func == agg::NONE) {
    // Do nothing if this is not a aggregation
    return;
  }

  agg_flag = true;

  assert(query_fields.size() > 0 && "The size of `query_fields` must greater than zero");
  assert(relation_attr.aggregate_func != agg::NONE);

  aggregate_keys.push_back({query_fields[agg_pos].meta(), query_fields.size() - agg_pos});
  agg_pos = query_fields.size();
  aggregate_types.push_back(relation_attr.aggregate_func);
}

RC SelectStmt::create(Db *db, const SelectSqlNode &select_sql, Stmt *&stmt) {
  assert(stmt == nullptr && "`stmt` must be nullptr at the beginning");

  if (db == nullptr) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  // collect tables in `from` statement
  std::vector<Table *> tables;
  std::unordered_map<std::string, Table *> table_map;

  for (size_t i = 0; i < select_sql.relations.size(); i++) {
    const char *table_name = select_sql.relations[i].c_str();
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    tables.push_back(table);
    table_map.insert(std::pair<std::string, Table *>(table_name, table));
  }

  // collect query fields in `select` statement
  std::vector<Field> query_fields;

  // For aggregation
  std::vector<std::pair<const FieldMeta *, int>> aggregate_keys;
  std::vector<agg> aggregate_types;
  int agg_pos = 0;
  bool agg_flag{false};

  for (int i = static_cast<int>(select_sql.attributes.size()) - 1; i >= 0; i--) {
    const RelAttrSqlNode &relation_attr = select_sql.attributes[i];
    if (!relation_attr.agg_valid_flag) {
      // Invalid syntax
      return RC::INVALID_ARGUMENT;
    }

    if (common::is_blank(relation_attr.relation_name.c_str()) &&
        0 == strcmp(relation_attr.attribute_name.c_str(), "*")) {
      // If the current field is wildcard. (i.e., COUNT(*))
      for (Table *table : tables) {
        // We basically need all the metadata from all the underlying tables
        wildcard_fields(table, query_fields);
      }

      // Possibly aggregation on `*`
      agg_builder_inner(query_fields, agg_pos, aggregate_keys, aggregate_types, relation_attr, agg_flag);

    } else if (!common::is_blank(relation_attr.relation_name.c_str())) {
      // If the table name is not null. (i.e., `select t1.c1 from t1;`)
      const char *table_name = relation_attr.relation_name.c_str();
      const char *field_name = relation_attr.attribute_name.c_str();

      if (0 == strcmp(table_name, "*")) {
        if (0 != strcmp(field_name, "*")) {
          // Only `*.*` is permitted, but to be honest I do not know why to use this though. 🤣
          LOG_WARN("invalid field name while table is *. attr=%s", field_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
        for (Table *table : tables) {
          wildcard_fields(table, query_fields);
        }

        // Essentially the same as `*` cases for aggregation
        agg_builder_inner(query_fields, agg_pos, aggregate_keys, aggregate_types, relation_attr, agg_flag);

      } else {
        auto iter = table_map.find(table_name);
        if (iter == table_map.end()) {
          LOG_WARN("no such table in from list: %s", table_name);
          return RC::SCHEMA_FIELD_MISSING;
        }

        Table *table = iter->second;
        if (0 == strcmp(field_name, "*")) {
          // i.e., `select t1.* from t1;`. Though this is essentially the same with `*`.
          wildcard_fields(table, query_fields);
          agg_builder_inner(query_fields, agg_pos, aggregate_keys, aggregate_types, relation_attr, agg_flag);
        } else {
          const FieldMeta *field_meta = table->table_meta().field(field_name);
          if (nullptr == field_meta) {
            LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
            return RC::SCHEMA_FIELD_MISSING;
          }

          query_fields.push_back(Field(table, field_meta));
          agg_builder_inner(query_fields, agg_pos, aggregate_keys, aggregate_types, relation_attr, agg_flag);
        }
      }
    } else {
      // Only the column name is available. (i.e., `select c1 from t1;`)
      if (tables.size() != 1) {
        // Basically this is saying, i.e., `select c1 from t1 natural join t1;` is invalid.
        // Though this is a perfectly valid SQL syntax.
        LOG_WARN("invalid. I do not know the attr's table. attr=%s", relation_attr.attribute_name.c_str());
        return RC::SCHEMA_FIELD_MISSING;
      }

      assert(tables.size() == 1);

      Table *table = tables[0];
      const FieldMeta *field_meta = table->table_meta().field(relation_attr.attribute_name.c_str());
      if (nullptr == field_meta) {
        LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), relation_attr.attribute_name.c_str());
        return RC::SCHEMA_FIELD_MISSING;
      }

      query_fields.push_back(Field(table, field_meta));
      agg_builder_inner(query_fields, agg_pos, aggregate_keys, aggregate_types, relation_attr, agg_flag);
    }
  }

  if (agg_flag) {
    // Need to reverse the query_fields
    query_fields = {query_fields.rbegin(), query_fields.rend()};
  }

  LOG_INFO("got %d tables in from stmt and %d fields in query stmt", tables.size(), query_fields.size());

  Table *default_table = nullptr;
  if (tables.size() == 1) {
    default_table = tables[0];
  }


auto conditions = select_sql.conditions.data();
auto condition_num = select_sql.conditions.size();
// Check every equal-to condition ,then range the tables
// To check if we can do any join operation
std::vector<JoinStmt> join_stmts;
for(size_t i = 0 ;i < condition_num;i++) {
 if(conditions[i].comp == CompOp::EQUAL_TO) {
   if(conditions[i].left_is_attr && conditions[i].right_is_attr) {
     // Range the tables
     std::string left_table_name = conditions[i].left_attr.relation_name;
     std::string right_table_name = conditions[i].right_attr.relation_name;
     if(left_table_name != right_table_name) {
       // Join operation
       FilterUnit *filter_unit = nullptr;
       RC rc = FilterStmt::create_filter_unit(db, default_table, &table_map, conditions[i], filter_unit);
       auto filter_obj_left = filter_unit->left().field;
       auto filter_obj_right = filter_unit->right().field;
         if (rc != RC::SUCCESS) {
            LOG_WARN("failed to create filter unit. condition index=%d", i);
            return rc;
         }

       JoinStmt join_stmt = {filter_obj_left,filter_obj_right};
       join_stmts.push_back(join_stmt);
     }
   }
 }
}


  // create filter statement in `where` statement
  FilterStmt *filter_stmt = nullptr;
  RC rc = FilterStmt::create(db,
      default_table,
      &table_map,
      select_sql.conditions.data(),
      static_cast<int>(select_sql.conditions.size()),
      filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  // create aggregation statement
  AggStmt *agg_stmt{nullptr};
  if (agg_flag) {
    agg_stmt = new AggStmt{aggregate_keys, aggregate_types};
    assert(agg_stmt != nullptr && "`agg_stmt` must not be nullptr");
  }

  // everything alright
  SelectStmt *select_stmt = new SelectStmt();

  // TODO add expression copy
  select_stmt->tables_.swap(tables);
  select_stmt->query_fields_.swap(query_fields);
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->agg_stmt_ = agg_stmt;
  select_stmt->join_stmts_ = join_stmts;
  stmt = select_stmt;
  return RC::SUCCESS;
}
