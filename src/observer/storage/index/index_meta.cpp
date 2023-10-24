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
// Created by Wangyunlai.wyl on 2021/5/18.
//

#include "storage/index/index_meta.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "json/json.h"
#include "storage/field/field_meta.h"
#include "storage/table/table_meta.h"

const static Json::StaticString FIELD_NAME("name");
const static Json::StaticString FIELD_FIELD_NAME("field_name");

RC IndexMeta::init(const char *name, std::vector<const FieldMeta *> fields, bool unique) {
  if (common::is_blank(name)) {
    LOG_ERROR("Failed to init index, name is empty.");
    return RC::INVALID_ARGUMENT;
  }

  name_ = name;
  std::vector<std::string> fields_names;
  for (const auto field : fields) {
    fields_names.push_back(field->name());
  }
  fields_ = fields_names;
  unique_ = unique;
  return RC::SUCCESS;
}

void IndexMeta::to_json(Json::Value &json_value) const {
  json_value[FIELD_NAME] = name_;
  Json::Value fields(Json::arrayValue);
  for (const auto &field : fields_) {
    fields.append(field);
  }
  json_value[FIELD_FIELD_NAME] = fields;
}

RC IndexMeta::from_json(const TableMeta &table, const Json::Value &json_value, IndexMeta &index) {
  const Json::Value &name_value = json_value[FIELD_NAME];
  const Json::Value &field_value = json_value[FIELD_FIELD_NAME];

  if (!name_value.isString()) {
    LOG_ERROR("Index name is not a string. json value=%s", name_value.toStyledString().c_str());
    return RC::INTERNAL;
  }

  if (!field_value.isArray()) {
    LOG_ERROR("Field name of index [%s] is not an array. json value=%s",
            name_value.asCString(),
            field_value.toStyledString().c_str());
    return RC::INTERNAL;
  }

  std::vector<std::string> fields;
  for (const auto &field : field_value) {
    if (!field.isString()) {
      LOG_ERROR("Field name of index [%s] is not a string. json value=%s",
                name_value.asCString(),
                field.toStyledString().c_str());
      return RC::INTERNAL;
    }
    fields.push_back(field.asString());
  }

  std::string indexName = name_value.asString();
  std::vector<const FieldMeta *> fieldMetas;
  for (const auto &fieldName : fields) {
    const FieldMeta *field = table.field(fieldName.c_str());
    if (nullptr == field) {
      LOG_ERROR("Deserialize index [%s]: no such field: %s", indexName.c_str(), fieldName.c_str());
      return RC::SCHEMA_FIELD_MISSING;
    }
    fieldMetas.push_back(field);
  }

  // 在这里初始化 IndexMeta 对象，使用适当的参数
  return index.init(indexName.c_str(), fieldMetas, index.unique());
}

const char *IndexMeta::name() const { return name_.c_str(); }

std::vector<std::string> IndexMeta::fields() const { return fields_; }
bool IndexMeta::unique() const { return unique_; }

void IndexMeta::desc(std::ostream &os) const { os << "index name=" << name_; }
