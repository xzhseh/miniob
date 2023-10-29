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
#include "common/lang/string.h"
#include "common/log/log.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/agg_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/db/db.h"
#include "storage/field/field_meta.h"
#include "storage/table/table.h"

SelectStmt::~SelectStmt() {
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

static void wildcard_fields(Table *table, std::vector<Field> &field_metas) {
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num();
  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
    field_metas.emplace_back(table, table_meta.field(i));
  }
}

RC bind_order_by(Db *db, const std::vector<Table *> &tables, const std::vector<OrderBySqlNode> &order_bys,
                 std::vector<OrderByStmt> &order_by_stmts) {
  for (const auto &order_by : order_bys) {
    auto &attr = order_by.order_by_attributes[0];
    bool is_asc = order_by.order_by_asc[0];
    const char *table_name = attr.relation_name.c_str();
    const char *field_name = attr.attribute_name.c_str();

    if (common::is_blank(table_name)) {
      // Table name is empty means that only single table is involved
      if (common::is_blank(field_name)) {
        // Field name is empty
        LOG_WARN("invalid order by. both table and field are blank");
        return RC::INVALID_ARGUMENT;
      }
      // find field in every table
      assert(tables.size() == 1 && "The size of `tables` must be one");
      const FieldMeta *field_meta = nullptr;
      for (Table *table : tables) {
        field_meta = table->table_meta().field(field_name);
        if (nullptr != field_meta) {
          order_by_stmts.push_back({Field(table, field_meta), is_asc});
          break;
        }
      }
      if (nullptr == field_meta) {
        LOG_WARN("no such field. field=%s.%s", tables[0]->name(), field_name);
        return RC::SCHEMA_FIELD_MISSING;
      }
    } else {
      // Table name is not empty eg : select t1.c1 from t1 order by t1.c1
      Table *table = db->find_table(table_name);
      if (nullptr == table) {
        LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
        return RC::SCHEMA_TABLE_NOT_EXIST;
      }

      if (common::is_blank(field_name)) {
        LOG_WARN("invalid order by. field is blank");
        return RC::INVALID_ARGUMENT;
      }

      const FieldMeta *field_meta = table->table_meta().field(field_name);
      if (nullptr == field_meta) {
        LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
        return RC::SCHEMA_FIELD_MISSING;
      }

      order_by_stmts.push_back({Field(table, field_meta), is_asc});
    }
  }

  return RC::SUCCESS;
}

auto get_field(Db *db, const std::vector<Table *> &tables, std::unordered_map<std::string, Table *> *table_map,
               const RelAttrSqlNode &attribute, Field &field) -> RC {
  RC rc = RC::SUCCESS;

  const char *table_name = attribute.relation_name.c_str();
  const char *field_name = attribute.attribute_name.c_str();

  if (common::is_blank(table_name)) {
    if (common::is_blank(field_name)) {
      return RC::INVALID_ARGUMENT;
    }

    for (const auto &table : tables) {
      const FieldMeta *field_meta = table->table_meta().field(field_name);
      if (field_meta != nullptr) {
        field = Field{table, field_meta};
        return rc;
      }
    }

    return RC::SUCCESS;
  } else {
    // Table name is not empty
    auto iter = table_map->find(table_name);
    if (iter == table_map->end()) {
      return RC::INVALID_ARGUMENT;
    }
    const Table *table = iter->second;
    if (table == nullptr) {
      return RC::INVALID_ARGUMENT;
    }

    const FieldMeta *field_meta = table->table_meta().field(field_name);
    if (field_meta == nullptr) {
      return RC::INVALID_ARGUMENT;
    }

    field = Field{table, field_meta};
    return rc;
  }

  assert(false && "This path is impossible");
}

/// Check if every group by key can be found in parsed fields
bool group_by_sanity_check(const std::vector<RelAttrSqlNode> &group_by_keys, const AggStmt &agg_stmt) {
  const auto &fields = agg_stmt.get_fields();
  int count{0};
  bool flag{false};

  bool agg_flag{false};
  bool non_agg_flag{false};

  for (const auto &i_a : agg_stmt.get_is_agg()) {
    if (i_a) {
      agg_flag = true;
    } else {
      non_agg_flag = true;
    }
  }

  if (agg_flag && non_agg_flag && group_by_keys.empty()) {
    return false;
  }

  for (int i = 0; i < fields.size(); ++i) {
    const auto &field = fields[i];

    if (!agg_stmt.get_is_agg()[i]) {
      count += 1;
    }

    for (const auto &g_b_k : group_by_keys) {
      if (common::is_blank(g_b_k.relation_name.c_str())) {
        // Table name is empty
        if (g_b_k.attribute_name == field.field_name()) {
          if (agg_stmt.get_is_agg()[i] || agg_stmt.get_agg_types()[i] != agg::NONE) {
            // Must not be aggregate key
            return false;
          }
          flag = true;
        }
      } else {
        // Group by multiple tables
        if (g_b_k.attribute_name == field.field_name() && g_b_k.relation_name == field.table_name()) {
          if (agg_stmt.get_is_agg()[i] || agg_stmt.get_agg_types()[i] != agg::NONE) {
            // Must not be aggregate key
            return false;
          }
          flag = true;
        }
      }
    }
  }

  if (!flag && !group_by_keys.empty()) {
    return false;
  }

  // Check the number of keys
  if (count != group_by_keys.size() && !group_by_keys.empty()) {
    return false;
  }

  return true;
}

/// Find the corresponding fields and bind they to group by statements
RC aggregation_builder(Db *db, const std::vector<Table *> &tables, std::unordered_map<std::string, Table *> *table_map,
                       const std::vector<RelAttrSqlNode> &attributes, AggStmt &agg_stmt) {
  RC rc = RC::SUCCESS;
  std::vector<Field> fields;
  std::vector<bool> is_agg;
  std::vector<agg> agg_types;

  // Should in reverse order
  for (int i = attributes.size() - 1; i >= 0; --i) {
    const auto &attr = attributes[i];

    if (!attr.agg_valid_flag) {
      // Syntax error for the current aggregation
      return RC::INVALID_ARGUMENT;
    }

    if (attr.aggregate_func != agg::NONE) {
      // Is aggregate key
      if (attr.attribute_name == "*") {
        // AGG(*)
        if (attr.aggregate_func != agg::AGG_COUNT) {
          // Should be invalid
          return RC::INVALID_ARGUMENT;
        } else {
          assert(agg::AGG_COUNT == attr.aggregate_func && "Expect agg::AGG_COUNT");
          // Only COUNT(*) is allowed currently
          is_agg.push_back(true);
          agg_types.push_back(agg::AGG_COUNT);
          // Used to distinguish COUNT(*) from others
          fields.push_back({nullptr, nullptr});
          continue;
        }
      } else {
        // AGG(rel_attr)
        Field field;
        rc = get_field(db, tables, table_map, attr, field);
        if (rc != RC::SUCCESS) {
          LOG_WARN("[aggregation_builder] failed to get field %s.", attr.attribute_name.c_str());
          return rc;
        }
        is_agg.push_back(true);
        agg_types.push_back(attr.aggregate_func);
        fields.push_back(field);
      }
    } else {
      if (attr.attribute_name == "*") {
        return RC::SUCCESS;
      }
      // Normal key
      Field field;
      rc = get_field(db, tables, table_map, attr, field);
      if (rc != RC::SUCCESS) {
        LOG_WARN("[aggregation_builder] failed to get field %s.", attr.attribute_name.c_str());
        return rc;
      }
      is_agg.push_back(false);
      agg_types.push_back(agg::NONE);
      fields.push_back(field);
    }
  }

  assert(is_agg.size() == agg_types.size() && agg_types.size() == fields.size() && "Expect the sizes to be the same");

  agg_stmt.set_is_agg(std::move(is_agg));
  agg_stmt.set_agg_types(std::move(agg_types));
  agg_stmt.set_fields(std::move(fields));

  return rc;
}

RC SelectStmt::resolve_tables(Db *db, const SelectSqlNode &select_sql, std::vector<Table *> &tables,
                              std::unordered_map<std::string, Table *> &table_map,
                              std::unordered_map<std::string, Table *> &parent_table_map) {
  for (size_t i = 0; i < select_sql.relations.size(); i++) {
    if (!select_sql.relations[i].is_parent) {
      const char *table_name = select_sql.relations[i].relation_name.c_str();
      const auto &alias = select_sql.relations[i].alias_name;
      // Both table name and alias name will map to the same table
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
      if (!alias.empty()) {
        // check if the alias is conflict with the table name
        if (table_map.find(alias) != table_map.end()) {
          LOG_WARN("alias name conflict. alias=%s", alias.c_str());
          return RC::INVALID_ARGUMENT;
        }
        table_map.insert(std::pair<std::string, Table *>(alias, table));
      }
    } else {
      std::string parent_relation_name = select_sql.relations[i].relation_name;
      parent_table_map[parent_relation_name] = db->find_table(parent_relation_name.c_str());
    }
  }
  return RC::SUCCESS;
}

/// TODO: We definitely need to refactor this part, the current implementation is so embarrassed 😅
RC SelectStmt::create(Db *db, const SelectSqlNode &select_sql, Stmt *&stmt) {
  assert(stmt == nullptr && "`stmt` must be nullptr at the beginning");
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  // collect tables in `from` statement
  std::vector<Table *> tables;
  std::unordered_map<std::string, Table *> table_map;
  std::unordered_map<std::string, Table *> parent_table_map;
  RC rc = resolve_tables(db, select_sql, tables, table_map, parent_table_map);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to resolve tables");
    return rc;
  }

  // collect query fields in `select` statement
  std::vector<Field> query_fields;

  // Resolve the query fields
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
      } else {
        // select t1.c1 from t1;
        auto iter = table_map.find(table_name);
        // Table alias is also in this map
        if (iter == table_map.end()) {
          auto parent_iter = parent_table_map.find(table_name);
          if (parent_iter == parent_table_map.end()) {
            return RC::SCHEMA_FIELD_MISSING;
          }
          // Could resolve by parent relations
          table_map.insert(std::pair<std::string, Table *>(table_name, parent_iter->second));
          iter = table_map.find(table_name);
        }

        Table *table = iter->second;
        if (0 == strcmp(field_name, "*")) {
          // i.e., `select t1.* from t1;`. Though this is essentially the same with `*`.
          wildcard_fields(table, query_fields);
        } else {
          // It's real name ,not alias name
          const FieldMeta *field_meta = table->table_meta().field(field_name);
          if (nullptr == field_meta) {
            LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
            return RC::SCHEMA_FIELD_MISSING;
          }

          query_fields.emplace_back(table, field_meta);
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

      query_fields.emplace_back(table, field_meta);
    }
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
  for (size_t i = 0; i < condition_num; i++) {
    if (conditions[i].comp == CompOp::EQUAL_TO) {
      if (conditions[i].left_is_attr && conditions[i].right_is_attr) {
        // Range the tables
        std::string left_table_name = conditions[i].left_attr.relation_name;
        std::string right_table_name = conditions[i].right_attr.relation_name;
        if (left_table_name != right_table_name) {
          // Join operation
          FilterUnit *filter_unit = nullptr;
          RC rc = FilterStmt::create_filter_unit(db,
                                                 default_table,
                                                 &table_map,
                                                 &parent_table_map,
                                                 select_sql.attributes,
                                                 // Join filter does not need to be considered
                                                 std::vector<RelationSqlNode>(),
                                                 conditions[i],
                                                 filter_unit);
          auto filter_obj_left = filter_unit->left().field;
          auto filter_obj_right = filter_unit->right().field;
          if (rc != RC::SUCCESS) {
            LOG_WARN("failed to create filter unit. condition index=%d", i);
            return rc;
          }

          JoinStmt join_stmt = {filter_obj_left, filter_obj_right};
          join_stmts.push_back(join_stmt);
        }
      }
    }
  }

  // Bind order by
  std::vector<OrderByStmt> order_by_stmts;
  rc = bind_order_by(db, tables, select_sql.order_bys, order_by_stmts);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to bind order by");
    return rc;
  }

  // create filter statement in `where` statement
  FilterStmt *filter_stmt = nullptr;
  rc = FilterStmt::create(db,
                          default_table,
                          &table_map,
                          &parent_table_map,
                          select_sql.attributes,
                          select_sql.relations,
                          select_sql.conditions.data(),
                          static_cast<int>(select_sql.conditions.size()),
                          filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  // create aggregation statement
  AggStmt *agg_stmt = new AggStmt();
  assert(agg_stmt != nullptr && "`agg_stmt must not be nullptr");

  rc = aggregation_builder(db, tables, &table_map, select_sql.attributes, *agg_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to build the aggregation statement.");
    return rc;
  }

  // i.e., select count(id), id from t1; is INVALID
  if (!group_by_sanity_check(select_sql.group_bys, *agg_stmt)) {
    LOG_WARN("invalid group by syntax.");
    return RC::INVALID_ARGUMENT;
  }

  bool agg_flag{false};
  for (const auto &a : agg_stmt->get_is_agg()) {
    if (a == true) {
      agg_flag = true;
      break;
    }
  }

  // Set potential having node
  agg_stmt->set_having(std::move(static_cast<ConditionSqlNode>(select_sql.having)));

  if (!agg_flag) {
    // No need to plan the aggregation node
    agg_stmt = nullptr;
  }

  // everything alright
  SelectStmt *select_stmt = new SelectStmt();

  // TODO add expression copy
  select_stmt->tables_.swap(tables);
  select_stmt->query_fields_.swap(query_fields);
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->agg_stmt_ = agg_stmt;
  select_stmt->join_stmts_ = join_stmts;
  select_stmt->order_by_ = order_by_stmts;
  stmt = select_stmt;
  return RC::SUCCESS;
}
