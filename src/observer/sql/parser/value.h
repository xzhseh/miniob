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
// Created by Wangyunlai 2023/6/27
//

#pragma once

#include <string>
#include "common/rc.h"

/// Note that after adding the null flag
/// Unfortunately we need to add 1 byte for each type 😅
/// In the future we could possibly figure out if there is other solution for this
enum AttrType {
  UNDEFINED,
  CHARS,          ///< string type
  INTS,           ///< int type (4 + 1 bytes)
  FLOATS,         ///< float type (4 + 1 bytes)
  DATE,           ///< date type (4 + 1 bytes)
  BOOLEANS,       ///< boolean type (currently used internally, will not be parsed by parser)
};

const char *attr_type_to_string(AttrType type);
AttrType attr_type_from_string(const char *s);

/**
 * @brief Class Value
 * 
 */
class Value {
public:
  Value(AttrType attr_type, char *data, int length = 4) : attr_type_(attr_type) {
    if (attr_type == DATE) {
      this->set_date(data);
    } else {
      this->set_data(data, length);
    }
  }

  explicit Value(int val);
  explicit Value(float val);
  explicit Value(bool val);
  explicit Value(const char *s, int len = 0);

  Value() = default;
  Value(const Value &other) = default;
  Value &operator=(const Value &other) = default;

  static bool check_null(const Value &v) {
    switch (v.attr_type()) {
      case INTS:
        return v.get_int() == 1919810;
      case FLOATS:
        return v.get_float() == 114.514;
      case CHARS:
        return strcmp(v.get_string().c_str(), "xzhseh") == 0;
      case DATE:
        return v.get_date() == 20021030;
      default: assert(false);
    }
  }

  void set_type(AttrType type) {
    this->attr_type_ = type;
  }

  void set_data(const char *data, int length) {
    this->set_data(const_cast<char *>(data), length);
  }

  void set_null() {
    is_null_ = true;
  }

  bool is_null() const {
    return is_null_;
  }

  void set_data(char *data, int length);
  void set_int(int val);
  void set_float(float val);
  void set_boolean(bool val);
  void set_string(const char *s, int len = 0);
  void set_date(int val);
  void set_date(const char *s);
  void set_value(const Value &value);

  std::string to_string() const;

  int compare(const Value &other) const;
  RC          like(const Value &other, bool &result) const;

  const char *data() const;

  int length() const {
    return length_;
  }

  AttrType attr_type() const {
    return attr_type_;
  }

public:
  /**
   * 获取对应的值
   * 如果当前的类型与期望获取的类型不符，就会执行转换操作
   */
  int get_int() const;
  float get_float() const;
  std::string get_string() const;
  bool get_boolean() const;
  int get_date() const;

private:
  AttrType attr_type_ = UNDEFINED;

  // The length of the current stored value
  int length_{0};

  union {
    int int_value_;
    float float_value_;
    int date_value_;
    bool bool_value_;
  } num_value_;

  // The string value
  std::string str_value_;

  // The null flag
  // In two cases this will be `false`
  //   1. Explicitly declare `not null`
  //   2. Does NOT explicitly declare `null`
  bool is_null_{false};
};