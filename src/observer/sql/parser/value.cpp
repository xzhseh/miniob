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
// Created by WangYunlai on 2023/06/28.
//

#include "sql/parser/value.h"
#include <cstring>
#include <regex>
#include <sstream>
#include "common/lang/comparator.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "storage/field/field.h"

const char *ATTR_TYPE_NAME[] = {"undefined", "chars", "text", "ints", "floats", "date", "booleans"};

const char *attr_type_to_string(AttrType type) {
  if (type >= UNDEFINED && type <= DATE) {
    return ATTR_TYPE_NAME[type];
  }
  return "unknown";
}
AttrType attr_type_from_string(const char *s) {
  for (unsigned int i = 0; i < sizeof(ATTR_TYPE_NAME) / sizeof(ATTR_TYPE_NAME[0]); i++) {
    if (0 == strcmp(ATTR_TYPE_NAME[i], s)) {
      return (AttrType)i;
    }
  }
  return UNDEFINED;
}

Value::Value(int val) { set_int(val); }

Value::Value(float val) { set_float(val); }

Value::Value(bool val) { set_boolean(val); }

Value::Value(const char *s, int len /*= 0*/) { set_string(s, len); }

bool check_date(int y, int m, int d) {
  static int mon[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  bool leap = (y % 400 == 0 || (y % 100 && y % 4 == 0));
  return y > 0 && ((m > 0) && (m <= 12)) && ((d > 0) && (d <= (((m == 2 && leap) ? 1 : 0) + mon[m])));
}

int date_transform_inner(const char *s, bool force = false) {
  int y;
  int m;
  int d;
  sscanf(s, "%d-%d-%d", &y, &m, &d);
  if (!check_date(y, m, d) && !force) {
    return -1;
  } else {
    return (y * 10000 + m * 100 + d);
  }
}

/// Note that the input `data` is address
void Value::set_data(char *data, int length) {
  switch (attr_type_) {
    case CHARS: {
      set_string(data, length);
      break;
    }
    case TEXT: {
      set_text(data, length);
      break;
    }
    case INTS: {
      num_value_.int_value_ = *(int *)data;
      length_ = length;
      break;
    }
    case FLOATS: {
      num_value_.float_value_ = *(float *)data;
      length_ = length;
      break;
    }
    case BOOLEANS: {
      num_value_.bool_value_ = (*(int *)data != 0);
      length_ = length;
      break;
    }
    case DATE: {
      int date = *(int *)data;
      set_date(date);
      assert(length == 4 && length_ == 4 && "Expect the length of date to be 4");
      break;
    }
    default: {
      LOG_WARN("unknown data type: %d", attr_type_);
      break;
    }
  }
}

void Value::set_text(const char *s, int len) {
  attr_type_ = TEXT;
  if (len > 0) {
    len = strnlen(s, len);
    str_value_.assign(s, len);
  } else {
    str_value_.assign(s);
  }
  length_ = str_value_.length();
}

void Value::set_int(int val) {
  attr_type_ = INTS;
  num_value_.int_value_ = val;
  length_ = sizeof(val);
}

void Value::set_float(float val) {
  attr_type_ = FLOATS;
  num_value_.float_value_ = val;
  length_ = sizeof(val);
}

void Value::set_boolean(bool val) {
  attr_type_ = BOOLEANS;
  num_value_.bool_value_ = val;
  length_ = sizeof(val);
}

void Value::set_string(const char *s, int len /* = 0 */) {
  attr_type_ = CHARS;
  if (len > 0) {
    len = strnlen(s, len);
    str_value_.assign(s, len);
  } else {
    str_value_.assign(s);
  }
  length_ = str_value_.length();
}

void Value::set_date(const char *s) {
  attr_type_ = DATE;
  if (strcmp(s, "9191-91-91") == 0) {
    num_value_.date_value_ = date_transform_inner(s, true);
  } else {
    num_value_.date_value_ = date_transform_inner(s);
  }
  length_ = sizeof(int);
}

void Value::set_date(int val) {
  assert(val != -1 && "Date should be valid");
  attr_type_ = DATE;
  num_value_.date_value_ = val;
  length_ = sizeof(val);
}

void Value::set_value(const Value &value) {
  switch (value.attr_type_) {
    case INTS: {
      set_int(value.get_int());
    } break;
    case FLOATS: {
      set_float(value.get_float());
    } break;
    case CHARS: {
      set_string(value.get_string().c_str());
    } break;
    case TEXT: {
      set_string(value.get_string().c_str());
    } break;
    case BOOLEANS: {
      set_boolean(value.get_boolean());
    } break;
    case DATE: {
      set_date(value.get_date());
      break;
    }
    case UNDEFINED: {
      ASSERT(false, "got an invalid value type");
    } break;
    default:
      assert(false);  // Should not set value to a NULL
  }
}

const char *Value::data() const {
  switch (attr_type_) {
    case CHARS: {
      return str_value_.c_str();
    } break;
    case TEXT: {
      return str_value_.c_str();
    } break;
    default: {
      return (const char *)&num_value_;
    } break;
  }
}

std::string Value::to_string() const {
  std::stringstream os;
  switch (attr_type_) {
    case INTS: {
      os << num_value_.int_value_;
    } break;
    case TEXT: {
      os << str_value_;
    } break;
    case FLOATS: {
      os << common::double_to_str(num_value_.float_value_);
    } break;
    case BOOLEANS: {
      os << num_value_.bool_value_;
    } break;
    case CHARS: {
      os << str_value_;
    } break;
    case DATE: {
      char buf[16] = {0};
      int val = num_value_.date_value_;
      snprintf(buf, 11, "%04d-%02d-%02d", val / 10000, (val % 10000) / 100, val % 100);
      buf[10] = '\0';
      os << buf;
    } break;
    default: {
      LOG_WARN("unsupported attr type: %d", attr_type_);
    } break;
  }
  return os.str();
}

int Value::compare(const Value &other) const {
  if (this->attr_type_ == other.attr_type_) {
    switch (this->attr_type_) {
      case INTS: {
        return common::compare_int((void *)&this->num_value_.int_value_, (void *)&other.num_value_.int_value_);
      } break;
      case FLOATS: {
        return common::compare_float((void *)&this->num_value_.float_value_, (void *)&other.num_value_.float_value_);
      } break;
      case CHARS: {
        return common::compare_string((void *)this->str_value_.c_str(),
                                      this->str_value_.length(),
                                      (void *)other.str_value_.c_str(),
                                      other.str_value_.length());
      } break;
      case TEXT: {
        return common::compare_string((void *)this->str_value_.c_str(),
                                      this->str_value_.length(),
                                      (void *)other.str_value_.c_str(),
                                      other.str_value_.length());
      } break;
      case BOOLEANS: {
        return common::compare_int((void *)&this->num_value_.bool_value_, (void *)&other.num_value_.bool_value_);
      }
      case DATE: {
        return common::compare_int((void *)&this->num_value_.date_value_, (void *)&other.num_value_.date_value_);
      } break;
      default: {
        LOG_WARN("unsupported type: %d", this->attr_type_);
      }
    }
  } else if (this->attr_type_ == INTS && other.attr_type_ == FLOATS) {
    float this_data = this->num_value_.int_value_;
    return common::compare_float((void *)&this_data, (void *)&other.num_value_.float_value_);
  } else if (this->attr_type_ == FLOATS && other.attr_type_ == INTS) {
    float other_data = other.num_value_.int_value_;
    return common::compare_float((void *)&this->num_value_.float_value_, (void *)&other_data);
  } else if (this->attr_type_ == CHARS && other.attr_type_ == FLOATS) {
    float other_data = other.num_value_.float_value_;
    return common::compare_str_with_float(
        (void *)this->str_value_.c_str(), this->str_value_.length(), (void *)&other_data);
  } else if (this->attr_type_ == FLOATS && other.attr_type_ == CHARS) {
    float this_data = this->num_value_.float_value_;
    return -common::compare_str_with_float(
        (void *)other.str_value_.c_str(), other.str_value_.length(), (void *)&this_data);
  } else if (this->attr_type_ == CHARS && other.attr_type_ == INTS) {
    int other_data = other.num_value_.int_value_;
    return common::compare_str_with_int(
        (void *)this->str_value_.c_str(), this->str_value_.length(), (void *)&other_data);
  } else if (this->attr_type_ == INTS && other.attr_type_ == CHARS) {
    int this_data = this->num_value_.int_value_;
    return -common::compare_str_with_int(
        (void *)other.str_value_.c_str(), other.str_value_.length(), (void *)&this_data);
  }
  LOG_WARN("not supported");
  return -1;  // TODO return rc?
}

bool compare_like(const char *str, const char *pattern) {
  LOG_DEBUG("str=%s, pattern=%s", str, pattern);
  char *c = (char *)pattern;
  std::string re;
  while (*c) {
    if (*c == '%') {
      re += "[^']*";
    } else if (*c == '_') {
      re += "[^']";
    } else {
      re += "[";
      re += *c;
      re += "]";
    }
    c++;
  }
  std::regex rule(re);
  return std::regex_match(str, rule);
}

// Compare current value with pattern if the value is `CHARS`
RC Value::like(const Value &pattern, bool &result) const {
  if (this->attr_type_ == CHARS && pattern.attr_type_ == CHARS) {
    result = compare_like(this->str_value_.c_str(), pattern.str_value_.c_str());
    return RC::SUCCESS;
  } else {
    LOG_WARN("not supported");
    return RC::UNIMPLENMENT;
  }
}

int Value::get_int() const {
  switch (attr_type_) {
    case CHARS: {
      try {
        return (int)(std::stol(str_value_));
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to number. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return 0;
      }
    }
    case TEXT: {
      try {
        return (int)(std::stol(str_value_));
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to number. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return 0;
      }
    }
    case INTS: {
      return num_value_.int_value_;
    }
    case FLOATS: {
      return (int)(num_value_.float_value_);
    }
    case BOOLEANS: {
      return (int)(num_value_.bool_value_);
    }
    case DATE: {
      return num_value_.date_value_;
    }
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return 0;
    }
  }
  return 0;
}

float Value::get_float() const {
  switch (attr_type_) {
    case CHARS: {
      try {
        return std::stof(str_value_);
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to float. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return 0.0;
      }
    } break;
    case TEXT: {
      try {
        return std::stof(str_value_);
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to float. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return 0.0;
      }
    } break;
    case INTS: {
      return float(num_value_.int_value_);
    } break;
    case FLOATS: {
      return num_value_.float_value_;
    } break;
    case BOOLEANS: {
      return float(num_value_.bool_value_);
    } break;
    case DATE: {
      return static_cast<float>(num_value_.date_value_);
    }
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return 0;
    }
  }
  return 0;
}

std::string Value::get_string() const { return this->to_string(); }

bool Value::get_boolean() const {
  switch (attr_type_) {
    case CHARS: {
      try {
        float val = std::stof(str_value_);
        if (val >= EPSILON || val <= -EPSILON) {
          return true;
        }

        int int_val = std::stol(str_value_);
        if (int_val != 0) {
          return true;
        }

        return !str_value_.empty();
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to float or integer. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return !str_value_.empty();
      }
    } break;
    case TEXT: {
      try {
        float val = std::stof(str_value_);
        if (val >= EPSILON || val <= -EPSILON) {
          return true;
        }

        int int_val = std::stol(str_value_);
        if (int_val != 0) {
          return true;
        }

        return !str_value_.empty();
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to float or integer. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return !str_value_.empty();
      }
    } break;
    case INTS: {
      return num_value_.int_value_ != 0;
    } break;
    case FLOATS: {
      float val = num_value_.float_value_;
      return val >= EPSILON || val <= -EPSILON;
    } break;
    case BOOLEANS: {
      return num_value_.bool_value_;
    } break;
    case DATE: {
      return num_value_.date_value_ != 0;
    }
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return false;
    }
  }
  return false;
}
struct NumberFromStr {
  bool float_or_int;
  float float_ = 0;
  int int_ = 0;
  float to_float() {
    if (float_or_int) {
      return float_;
    }
    return int_;
  }
  explicit NumberFromStr(const char *str);
};

NumberFromStr::NumberFromStr(const char *str) {
  int state = 0;  // 0 整数 1小数
  char *c = (char *)str;
  int float_jw = 10;
  while (*c) {
    if (*c >= '0' && *c <= '9') {
      if (state == 0) {
        int_ *= 10;
        int_ += *c - '0';
      } else {
        float_ += 1.0 * (*c - '0') / float_jw;
        float_jw *= 10;
      }
    } else if (*c == '.') {
      state = 1;
      float_ = int_;
    } else {
      break;
    }
    c++;
  }
  float_or_int = state;
}

int Value::get_date() const {
  assert(attr_type_ == DATE && "Currently expect `attr_type_` to be of type `DATE`");
  return num_value_.date_value_;
}
bool Value::cast_to(const AttrType &target_type, Value &result) const {
  // Null value cast
  if (Value::check_null(*this)) {
    return false;
  }
  // Same type cast
  if (this->attr_type_ == target_type) {
    result = *this;
    return true;
  }
  // Char --> int
  if (this->attr_type_ == CHARS && target_type == INTS) {
    auto conv = NumberFromStr(this->str_value_.c_str());
    if (conv.float_or_int) {
      result.set_float(conv.float_);
    } else {
      result.set_int(conv.int_);
    }
    return true;
  }
  // int --> float
  if (this->attr_type_ == INTS && target_type == FLOATS) {
    result.set_float(this->num_value_.int_value_);
    return true;
  }
  // float --> int
  if (this->attr_type_ == FLOATS && target_type == INTS) {
    result.set_int(this->num_value_.float_value_);
    return true;
  }
  // float --> char
  if (this->attr_type_ == FLOATS && target_type == CHARS) {
    result.set_string(common::double_to_str(this->num_value_.float_value_).c_str());
    return true;
  }
  // int --> char
  if (this->attr_type_ == INTS && target_type == CHARS) {
    result.set_string(std::to_string(this->num_value_.int_value_).c_str());
    return true;
  }
  return false;
}
