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
// Created by wangyunlai.wyl on 2021/5/19.
//

#include "storage/index/bplus_tree_index.h"
#include <iomanip>
#include <iostream>
#include <list>
#include "common/log/log.h"

BplusTreeIndex::~BplusTreeIndex() noexcept { close(); }

RC BplusTreeIndex::create(const char *file_name, const IndexMeta &index_meta,
                          std::vector<const FieldMeta *> field_metas) {
  if (inited_) {
    LOG_WARN("Failed to create index due to the index has been created before. file_name:%s, index:%s",
        file_name,
        index_meta.name());
    return RC::RECORD_OPENNED;
  }

  Index::init(index_meta, field_metas);
  vector<AttrType> types;
  vector<int> lengths;
  vector<int> offsets;
  for (size_t i = 0; i < field_metas_.size(); i++) {
    types.push_back(field_metas_[i].type());
    lengths.push_back(field_metas_[i].len());
    offsets.push_back(field_metas_[i].offset());
  }
  RC rc = index_handler_.create(file_name, types, lengths, offsets, index_meta.unique());
  if (RC::SUCCESS != rc) {
    LOG_WARN("Failed to create index_handler, file_name:%s, index:%s, rc:%s",
        file_name,
        index_meta.name(),
        strrc(rc));
    return rc;
  }

  inited_ = true;
  LOG_INFO(
      "Successfully create index, file_name:%s, index:%s, field:%s", file_name, index_meta.name(), index_meta.fields().data());
  return RC::SUCCESS;
}

RC BplusTreeIndex::open(const char *file_name, const IndexMeta &index_meta,
                        std::vector<const FieldMeta *> field_metas) {
  if (inited_) {
    LOG_WARN("Failed to open index due to the index has been initedd before. file_name:%s, index:%s",
        file_name,
        index_meta.name());
    return RC::RECORD_OPENNED;
  }

  Index::init(index_meta, field_metas);

  RC rc = index_handler_.open(file_name);
  if (RC::SUCCESS != rc) {
    LOG_WARN("Failed to open index_handler, file_name:%s, index:%s, rc:%s",
        file_name,
        index_meta.name(),
        strrc(rc));
    return rc;
  }

  inited_ = true;
  LOG_INFO(
      "Successfully open index, file_name:%s, index:%s", file_name, index_meta.name());
  return RC::SUCCESS;
}
void printBinary(char *number, int len) {
  for (int i = 0; i < len; ++i) {
    unsigned char byte = static_cast<unsigned char>(number[i]);
    std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";

    for (int j = 7; j >= 0; --j) {
      std::cout << ((byte >> j) & 1);
    }
    std::cout << " ";
  }
  std::cout << std::dec << std::endl;
}
char *BplusTreeIndex::make_user_key(const char *record, bool &is_null) {
  char *key = (char *)this->index_handler_.alloc();
  if (key == nullptr) {
    LOG_WARN("Failed to alloc memory for key.");
    return nullptr;
  }
  int attr_length{};
  for (const auto &field_meta : field_metas_) {
    memcpy(key + attr_length, record + field_meta.offset(), field_meta.len());
    std::cout << "type: " << field_meta.type() << ", offset: " << field_meta.offset()
              << ", length: " << field_meta.len() << std::endl;
    Value check_null_value;
    check_null_value.set_type(field_meta.type());
    check_null_value.set_data(key + attr_length, field_meta.len());
    if (Value::check_null(check_null_value)) {
      is_null = true;
      std::cout << "make_user_key null" << std::endl;
    } else {
      std::cout << "make_user_key not null" << std::endl;
    }
    attr_length += field_meta.len();
  }
  printBinary(key, attr_length);
  return key;
}

void BplusTreeIndex::free_user_key(char *user_key) { this->index_handler_.free(user_key); }

int BplusTreeIndex::user_key_len() {
  int attr_length{};
  for (const auto &field_meta : field_metas_) {
    attr_length += field_meta.len();
  }
  return attr_length;
}
RC BplusTreeIndex::close() {
  if (inited_) {
    LOG_INFO("Begin to close index, index:%s", index_meta_.name());
    index_handler_.close();
    inited_ = false;
  }
  LOG_INFO("Successfully close index.");
  return RC::SUCCESS;
}
RC BplusTreeIndex::check_unique_constraint(const char *record) {
  RC rc = RC::SUCCESS;
  std::list<RID> rids{};
  bool is_null = false;
  char *user_key = make_user_key(record, is_null);
  index_handler_.get_entry(user_key, user_key_len() + static_cast<int>(sizeof(RID)), rids);
  if (!is_null && !rids.empty() && index_meta_.unique()) {
    rc = RC::CONSTRAINT_UNIQUE;
  }
  free_user_key(user_key);
  return rc;
}

RC BplusTreeIndex::insert_entry(const char *record, const RID *rid) {
  if (check_unique_constraint(record) != RC::SUCCESS) {
    return RC::CONSTRAINT_UNIQUE;
  }
  bool nothing;
  char *user_key = make_user_key(record, nothing);
  RC rc = index_handler_.insert_entry(user_key, rid);
  free_user_key(user_key);
  return rc;
}

RC BplusTreeIndex::delete_entry(const char *record, const RID *rid) {
  bool nothing;
  char *user_key = make_user_key(record, nothing);
  RC rc = index_handler_.delete_entry(user_key, rid);
  free_user_key(user_key);
  return rc;
}

IndexScanner *BplusTreeIndex::create_scanner(const char *left_key, int left_len, bool left_inclusive,
                                             const char *right_key, int right_len, bool right_inclusive) {
  BplusTreeIndexScanner *index_scanner = new BplusTreeIndexScanner(index_handler_);
  RC rc = index_scanner->open(left_key, left_len, left_inclusive, right_key, right_len, right_inclusive);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open index scanner. rc=%d:%s", rc, strrc(rc));
    delete index_scanner;
    return nullptr;
  }
  return index_scanner;
}

RC BplusTreeIndex::sync() { return index_handler_.sync(); }

////////////////////////////////////////////////////////////////////////////////
BplusTreeIndexScanner::BplusTreeIndexScanner(BplusTreeHandler &tree_handler) : tree_scanner_(tree_handler) {}

BplusTreeIndexScanner::~BplusTreeIndexScanner() noexcept { tree_scanner_.close(); }

RC BplusTreeIndexScanner::open(const char *left_key, int left_len, bool left_inclusive, const char *right_key,
                               int right_len, bool right_inclusive) {
  return tree_scanner_.open(left_key, left_len, left_inclusive, right_key, right_len, right_inclusive);
}

RC BplusTreeIndexScanner::next_entry(RID *rid) { return tree_scanner_.next_entry(*rid); }

RC BplusTreeIndexScanner::destroy() {
  delete this;
  return RC::SUCCESS;
}
