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

#include "sql/stmt/filter_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "common/rc.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

FilterStmt::~FilterStmt() {
  for (FilterUnit *unit : filter_units_) {
    delete unit;
  }
  filter_units_.clear();
}

RC FilterStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
                      const std::vector<RelAttrSqlNode> &rel_attr, const std::vector<RelationSqlNode> &relations,
                      const ConditionSqlNode *conditions, int condition_num, FilterStmt *&stmt) {
  RC rc = RC::SUCCESS;
  stmt = nullptr;

  auto *tmp_stmt = new FilterStmt();
  for (int i = 0; i < condition_num; i++) {
    FilterUnit *filter_unit = nullptr;
    rc = create_filter_unit(db, default_table, tables, rel_attr, relations, conditions[i], filter_unit);
    if (rc != RC::SUCCESS) {
      delete tmp_stmt;
      LOG_WARN("failed to create filter unit. condition index=%d", i);
      return rc;
    }
    tmp_stmt->filter_units_.push_back(filter_unit);
  }

  stmt = tmp_stmt;
  return rc;
}

RC get_table_and_field(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
                       const RelAttrSqlNode &attr, Table *&table, const FieldMeta *&field,
                       const std::vector<RelAttrSqlNode> &rel_attr) {
  if (common::is_blank(attr.relation_name.c_str())) {
    table = default_table;
  } else if (nullptr != tables) {
    auto iter = tables->find(attr.relation_name);
    if (iter != tables->end()) {
      table = iter->second;
    }
  } else {
    table = db->find_table(attr.relation_name.c_str());
  }

  if (nullptr == table) {
    LOG_WARN("No such table: attr.relation_name: %s", attr.relation_name.c_str());
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  field = table->table_meta().field(attr.attribute_name.c_str());
  // Check if alias is used
  for (const auto &query_field : rel_attr) {
    if (query_field.alias_name.empty()) {
      continue;
    }
    // The condition's attribute name is an alias name
    if (query_field.alias_name == attr.attribute_name) {
      field = table->table_meta().field(query_field.attribute_name.c_str());
      break;
    }
  }
  if (nullptr == field) {
    LOG_WARN("no such field in table: table %s, field %s", table->name(), attr.attribute_name.c_str());
    table = nullptr;
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }

  return RC::SUCCESS;
}

RC FilterStmt::create_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
                                  const std::vector<RelAttrSqlNode> &rel_attr,
                                  const std::vector<RelationSqlNode> &relations, const ConditionSqlNode &condition,
                                  FilterUnit *&filter_unit) {
  RC rc = RC::SUCCESS;

  CompOp comp = condition.comp;
  if (comp < EQUAL_TO || comp >= NO_OP) {
    LOG_WARN("invalid compare operator : %d", comp);
    return RC::INVALID_ARGUMENT;
  }

  filter_unit = new FilterUnit;

  if (condition.left_is_attr == 1) {
    Table *table = nullptr;
    const FieldMeta *field = nullptr;
    rc = get_table_and_field(db, default_table, tables, condition.left_attr, table, field, rel_attr);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot find attr");
      return rc;
    }
    FilterObj filter_obj;
    filter_obj.init_attr(Field(table, field));
    filter_unit->set_left(filter_obj);
  } else if (condition.left_is_attr == 0) {
    FilterObj filter_obj;
    filter_obj.init_value(condition.left_value);
    filter_unit->set_left(filter_obj);
  } else if (condition.left_is_attr == 2) {
    // Sub query
    FilterObj filter_obj;
    // It's select stmt
    std::shared_ptr<ParsedSqlNode> sub_query(new ParsedSqlNode);
    sub_query->flag = SqlCommandFlag::SCF_SELECT;
    sub_query->selection = *condition.left_sub_select;
    std::unordered_map<std::string, Table *> new_tables;
    if (sub_query->selection.relations.size() == 1) {
      for (auto &condition_field : sub_query->selection.conditions) {
        auto &left_attr = condition_field.left_attr;
        if (left_attr.relation_name.empty()) {
          left_attr.relation_name = sub_query->selection.relations[0].relation_name;
        }
        // If any condition use parent query's field,it could be alias name all real name
        for (const auto &relation : relations) {
          if (left_attr.relation_name == relation.alias_name) {
            left_attr.relation_name = relation.relation_name;
            new_tables[relation.relation_name] = db->find_table(relation.relation_name.c_str());
          }
          if (left_attr.relation_name == relation.relation_name) {
            left_attr.relation_name = relation.relation_name;
            new_tables[relation.relation_name] = db->find_table(relation.relation_name.c_str());
          }
        }
        auto &right_attr = condition_field.right_attr;
        if (right_attr.relation_name.empty()) {
          right_attr.relation_name = sub_query->selection.relations[0].relation_name;
        }
        for (const auto &relation : relations) {
          if (right_attr.relation_name == relation.alias_name) {
            right_attr.relation_name = relation.relation_name;
            new_tables[relation.relation_name] = db->find_table(relation.relation_name.c_str());
          }
          if (right_attr.relation_name == relation.relation_name) {
            right_attr.relation_name = relation.relation_name;
            new_tables[relation.relation_name] = db->find_table(relation.relation_name.c_str());
          }
        }
      }
    }
    for (auto &table : new_tables) {
      sub_query->selection.relations.push_back(RelationSqlNode{table.first, ""});
    }
    filter_obj.init_sub_query(sub_query);
    filter_unit->set_left(filter_obj);
  } else if (condition.left_is_attr == 3) {
    // const value list
    FilterObj filter_obj;
    std::vector<Value> value_list;
    for (const auto &value : condition.left_value_list) {
      value_list.push_back(value);
    }
    filter_obj.init_value_list(value_list);
    filter_unit->set_left(filter_obj);
  } else {
    LOG_WARN("invalid left_is_attr: %d", condition.left_is_attr);
    return RC::INVALID_ARGUMENT;
  }

  if (condition.right_is_attr == 1) {
    Table *table = nullptr;
    const FieldMeta *field = nullptr;
    rc = get_table_and_field(db, default_table, tables, condition.right_attr, table, field, rel_attr);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot find attr");
      return rc;
    }
    FilterObj filter_obj;
    filter_obj.init_attr(Field(table, field));
    filter_unit->set_right(filter_obj);
  } else if (condition.right_is_attr == 0) {
    FilterObj filter_obj;
    filter_obj.init_value(condition.right_value);
    filter_unit->set_right(filter_obj);
  } else if (condition.right_is_attr == 2) {
    // Sub query
    FilterObj filter_obj;
    // It's select stmt
    std::shared_ptr<ParsedSqlNode> sub_query(new ParsedSqlNode);
    sub_query->flag = SqlCommandFlag::SCF_SELECT;
    sub_query->selection = *condition.right_sub_select;
    std::unordered_map<std::string, Table *> new_tables;
    if (sub_query->selection.relations.size() == 1) {
      for (auto &condition_field : sub_query->selection.conditions) {
        auto &left_attr = condition_field.left_attr;
        if (left_attr.relation_name.empty()) {
          left_attr.relation_name = sub_query->selection.relations[0].relation_name;
        }
        // If any condition use parent query's field,it could be alias name all real name
        for (const auto &relation : relations) {
          if (left_attr.relation_name == relation.alias_name) {
            left_attr.relation_name = relation.relation_name;
            new_tables[relation.relation_name] = db->find_table(relation.relation_name.c_str());
          }
          if (left_attr.relation_name == relation.relation_name) {
            left_attr.relation_name = relation.relation_name;
            new_tables[relation.relation_name] = db->find_table(relation.relation_name.c_str());
          }
        }
        auto &right_attr = condition_field.right_attr;
        if (right_attr.relation_name.empty()) {
          right_attr.relation_name = sub_query->selection.relations[0].relation_name;
        }
        for (const auto &relation : relations) {
          if (right_attr.relation_name == relation.alias_name) {
            right_attr.relation_name = relation.relation_name;
            new_tables[relation.relation_name] = db->find_table(relation.relation_name.c_str());
          }
          if (right_attr.relation_name == relation.relation_name) {
            right_attr.relation_name = relation.relation_name;
            new_tables[relation.relation_name] = db->find_table(relation.relation_name.c_str());
          }
        }
      }
    }
    for (auto &table : new_tables) {
      sub_query->selection.relations.push_back(RelationSqlNode{table.first, ""});
    }
    filter_obj.init_sub_query(sub_query);
    filter_unit->set_right(filter_obj);
  } else if (condition.right_is_attr == 3) {
    // const value list
    FilterObj filter_obj;
    std::vector<Value> value_list;
    for (const auto &value : condition.right_value_list) {
      value_list.push_back(value);
    }
    filter_obj.init_value_list(value_list);
    filter_unit->set_right(filter_obj);
  } else {
    LOG_WARN("invalid right_is_attr: %d", condition.right_is_attr);
    return RC::INVALID_ARGUMENT;
  }

  filter_unit->set_comp(comp);

  // 检查两个类型是否能够比较
  return rc;
}
