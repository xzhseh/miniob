/* Copyright (c) 2021OceanBase and/or its affiliates. All rights reserved.
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

#include "sql/stmt/insert_stmt.h"
#include "common/log/log.h"
#include "sql/parser/value.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

InsertStmt::InsertStmt(Table *table, const Value *values, int value_amount)
    : table_(table), values_(values), value_amount_(value_amount) {}

RC InsertStmt::create(Db *db, InsertSqlNode &inserts, Stmt *&stmt) {
  const char *table_name = inserts.relation_name.c_str();
  if (nullptr == db || nullptr == table_name || inserts.values.empty()) {
    LOG_WARN("invalid argument. db=%p, table_name=%p, value_num=%d",
        db, table_name, static_cast<int>(inserts.values.size()));
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  // check the fields number
  std::vector<Value> &values = inserts.values;
  const int value_num = static_cast<int>(inserts.values.size());
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num() - table_meta.sys_field_num();
  if (field_num != value_num) {
    LOG_WARN("schema mismatch. value num=%d, field num in schema=%d", value_num, field_num);
    return RC::SCHEMA_FIELD_MISSING;
  }

  // check fields type
  const int sys_field_num = table_meta.sys_field_num();
  for (int i = 0; i < value_num; i++) {
    const FieldMeta *field_meta = table_meta.field(i + sys_field_num);
    AttrType field_type = field_meta->type();
    AttrType value_type = values[i].attr_type();
    
    // insert 无法识别 text 和 chars, 需要做转换
    if (value_type == CHARS && field_type == TEXT) {
      value_type = TEXT;
      field_type = TEXT;
      values[i].set_type(TEXT);
    }

    /// NOTE: DO NOT CHANGE/REFACTOR THE CODE BELOW, strange bugs will occur for big-order-by
    /// refer: https://github.com/xzhseh/miniob/pull/23/commits/122869e2f9fd6d88e0b58456fead14aae1fbe1ea
    if (values[i].is_null()) {
      if (!field_meta->is_null()) {
        // If not null is either implicitly / explicitly enabled
        // The null can not be inserted into the field
        return RC::INVALID_ARGUMENT;
      }

      // Set the value to the hard-coded null value
      Value::set_null(values[i], field_type);

      assert(values[i].is_null() && "`values[i]` should persist the `is_null_` property");
      assert(values[i].attr_type() == field_type && "The type should be the same");
    }

    value_type = values[i].attr_type();

    // TODO: try to convert the value type to field type
    if (field_type != value_type) {
      LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
          table_name, field_meta->name(), field_type, value_type);
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }
  }

  // std::cout << "[insert_stmt] ----" << std::endl;
  // for (const auto &v : values) {
  //   std::cout << v.to_string() << " ";
  // }
  // std::cout << std::endl;
  // std::cout << "[insert_stmt] ----" << std::endl;

  // const Value *values_t = inserts.values.data();
  const Value *values_t = values.data();

  // everything alright
  stmt = new InsertStmt(table, values_t, value_num);
  return RC::SUCCESS;
}
