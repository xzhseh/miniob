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
// Created by Wangyunlai on 2022/07/05.
//

#include "sql/expr/expression.h"
#include "event/sql_event.h"
#include "session/session_stage.h"
#include "sql/expr/tuple.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"
#include "sub_query_expr.h"

using namespace std;

RC FieldExpr::get_value(const Tuple &tuple, Value &value) {
  if (agg_flag_) {
    value = agg_value_;
    return RC::SUCCESS;
  }
  auto rc = tuple.find_cell(TupleCellSpec(table_name(), field_name()), value);
  if (value.attr_type() == DATE && value.get_date() == -1) {
    rc = RC::INVALID_ARGUMENT;
  }
  if (value.attr_type() == TEXT && strlen(value.get_string().c_str()) > 65535) {
    rc = RC::INVALID_ARGUMENT;
  }
  return rc;
}

RC ValueExpr::get_value(const Tuple &tuple, Value &value) {
  if (value.attr_type() == TEXT && strlen(value.get_string().c_str()) > 65535) {
    return RC::INVALID_ARGUMENT;
  }
  if (value_.attr_type() == DATE && value_.get_date() == -1) {
    return RC::INVALID_ARGUMENT;
  } else {
    value = value_;
    return RC::SUCCESS;
  }
}

/////////////////////////////////////////////////////////////////////////////////
CastExpr::CastExpr(unique_ptr<Expression> child, AttrType cast_type)
    : child_(std::move(child)), cast_type_(cast_type) {}

CastExpr::~CastExpr() {}

RC CastExpr::cast(const Value &value, Value &cast_value) const {
  RC rc = RC::SUCCESS;
  if (this->value_type() == value.attr_type()) {
    cast_value = value;
    return rc;
  }

  switch (cast_type_) {
    case BOOLEANS: {
      bool val = value.get_boolean();
      cast_value.set_boolean(val);
    } break;
    default: {
      rc = RC::INTERNAL;
      LOG_WARN("unsupported convert from type %d to %d", child_->value_type(), cast_type_);
    }
  }
  return rc;
}

RC CastExpr::get_value(const Tuple &tuple, Value &cell) {
  RC rc = child_->get_value(tuple, cell);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return cast(cell, cell);
}

RC CastExpr::try_get_value(Value &value) const {
  RC rc = child_->try_get_value(value);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return cast(value, value);
}

////////////////////////////////////////////////////////////////////////////////

ComparisonExpr::ComparisonExpr(CompOp comp, unique_ptr<Expression> left, unique_ptr<Expression> right)
    : comp_(comp), left_(std::move(left)), right_(std::move(right)) {}

ComparisonExpr::~ComparisonExpr() {}

RC ComparisonExpr::compare_value(const Value &left, const Value &right, bool &result) const {
  if (left.attr_type() == DATE && left.get_date() == -1) {
    return RC::INVALID_ARGUMENT;
  }
  if (right.attr_type() == DATE && right.get_date() == -1) {
    return RC::INVALID_ARGUMENT;
  }
  if (left.attr_type() == TEXT && strlen(left.get_string().c_str()) > 65535) {
    return RC::INVALID_ARGUMENT;
  }
  if (right.attr_type() == TEXT && strlen(right.get_string().c_str()) > 65535) {
    return RC::INVALID_ARGUMENT;
  }

  // std::cout << "[expression] left: " << left.to_string() << " right: " << right.to_string() << std::endl;

  if (left.attr_type() == AttrType::UNDEFINED || right.attr_type() == AttrType::UNDEFINED) {
    return RC::INTERNAL;
  }

  auto left_check_null = Value::check_null(left);
  auto right_check_null = Value::check_null(right);

  // FIXME: Ensure this
  if ((left.is_null() || right.is_null()) || (left_check_null || right_check_null)) {
    if (comp_ == IS) {
      result = (left.is_null() || left_check_null) && (right.is_null() || right_check_null);
      return RC::SUCCESS;
    }
    if (comp_ == IS_NOT) {
      result = (left.is_null() || left_check_null) != (right.is_null() || right_check_null);
      return RC::SUCCESS;
    }
    result = false;
    return RC::SUCCESS;
  }

  RC rc = RC::SUCCESS;
  int cmp_result = left.compare(right);
  result = false;
  switch (comp_) {
    case EQUAL_TO: {
      result = (0 == cmp_result);
    } break;
    case LESS_EQUAL: {
      result = (cmp_result <= 0);
    } break;
    case NOT_EQUAL: {
      result = (cmp_result != 0);
    } break;
    case LESS_THAN: {
      result = (cmp_result < 0);
    } break;
    case GREAT_EQUAL: {
      result = (cmp_result >= 0);
    } break;
    case GREAT_THAN: {
      result = (cmp_result > 0);
    } break;
    case LIKE_OP: {
      rc = left.like(right, result);
    } break;
    case NOT_LIKE_OP: {
      rc = left.like(right, result);
      result = !result;
    } break;
    case IN_OP: {
      rc = this->compare_in(left, result);

    } break;
    case NOT_IN: {
      rc = this->compare_in(left, result);
      result = !result;
    } break;
    case EXISTS_OP: {
      rc = this->compare_in(left, result);
    } break;
    case NOT_EXISTS: {
      rc = this->compare_in(left, result);
      result = !result;
    } break;
    default: {
      LOG_WARN("unsupported comparison. %d", comp_);
      rc = RC::INTERNAL;
    } break;
  }

  return rc;
}

RC ComparisonExpr::try_get_value(Value &cell) const {
  if (left_->type() == ExprType::VALUE && right_->type() == ExprType::VALUE) {
    ValueExpr *left_value_expr = static_cast<ValueExpr *>(left_.get());
    ValueExpr *right_value_expr = static_cast<ValueExpr *>(right_.get());
    const Value &left_cell = left_value_expr->get_value();
    const Value &right_cell = right_value_expr->get_value();

    bool value = false;
    RC rc = compare_value(left_cell, right_cell, value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to compare tuple cells. rc=%s", strrc(rc));
    } else {
      cell.set_boolean(value);
    }
    return rc;
  }

  return RC::INVALID_ARGUMENT;
}

RC ComparisonExpr::get_value(const Tuple &tuple, Value &value) {
  Value left_value;
  Value right_value;

  JoinedTuple::set_find_left_first(true);
  RC rc = left_->get_value(tuple, left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }
  JoinedTuple::set_find_left_first(false);
  rc = right_->get_value(tuple, right_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
    return rc;
  }
  JoinedTuple::set_find_left_first(true);

  bool bool_value = false;
  rc = compare_value(left_value, right_value, bool_value);
  if (rc == RC::SUCCESS) {
    value.set_boolean(bool_value);
  }
  return rc;
}

RC ComparisonExpr::compare_in(const Value &left, bool &result) const {
  RC rc;
  // The right expression must be a sub query expression
  if (right_->type() != ExprType::SUB_QUERY) {
    LOG_WARN("right expression must be a sub query expression");
    rc = RC::INVALID_ARGUMENT;
    return rc;
  }
  auto *sub_query_expr = dynamic_cast<SubQueryExpr *>(right_.get());
  rc = sub_query_expr->in_or_not(left, left_, result);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to check in or not. rc=%s", strrc(rc));
    return rc;
  }
  return RC::SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////
ConjunctionExpr::ConjunctionExpr(Type type, vector<unique_ptr<Expression>> &children)
    : conjunction_type_(type), children_(std::move(children)) {}

RC ConjunctionExpr::get_value(const Tuple &tuple, Value &value) {
  RC rc = RC::SUCCESS;
  if (children_.empty()) {
    value.set_boolean(true);
    return rc;
  }

  Value tmp_value;
  for (const unique_ptr<Expression> &expr : children_) {
    rc = expr->get_value(tuple, tmp_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value by child expression. rc=%s", strrc(rc));
      return rc;
    }
    bool bool_value = tmp_value.get_boolean();
    if ((conjunction_type_ == Type::AND && !bool_value) || (conjunction_type_ == Type::OR && bool_value)) {
      value.set_boolean(bool_value);
      return rc;
    }
  }

  bool default_value = (conjunction_type_ == Type::AND);
  value.set_boolean(default_value);
  return rc;
}

////////////////////////////////////////////////////////////////////////////////

ArithmeticExpr::ArithmeticExpr(ArithmeticExpr::Type type, Expression *left, Expression *right)
    : arithmetic_type_(type), left_(left), right_(right) {}
ArithmeticExpr::ArithmeticExpr(ArithmeticExpr::Type type, unique_ptr<Expression> left, unique_ptr<Expression> right)
    : arithmetic_type_(type), left_(std::move(left)), right_(std::move(right)) {}

AttrType ArithmeticExpr::value_type() const {
  if (!right_) {
    return left_->value_type();
  }

  if (left_->value_type() == AttrType::INTS && right_->value_type() == AttrType::INTS &&
      arithmetic_type_ != Type::DIV) {
    return AttrType::INTS;
  }

  return AttrType::FLOATS;
}

RC ArithmeticExpr::calc_value(const Value &left_value, const Value &right_value, Value &value) const {
  RC rc = RC::SUCCESS;

  if (Value::check_null(left_value) || Value::check_null(right_value)) {
    Value::set_null(value, left_value.attr_type());
    return RC::SUCCESS;
  }

  const AttrType target_type = value_type();

  switch (arithmetic_type_) {
    case Type::ADD: {
      if (target_type == AttrType::INTS) {
        value.set_int(left_value.get_int() + right_value.get_int());
      } else {
        value.set_float(left_value.get_float() + right_value.get_float());
      }
    } break;

    case Type::SUB: {
      if (target_type == AttrType::INTS) {
        value.set_int(left_value.get_int() - right_value.get_int());
      } else {
        value.set_float(left_value.get_float() - right_value.get_float());
      }
    } break;

    case Type::MUL: {
      if (target_type == AttrType::INTS) {
        value.set_int(left_value.get_int() * right_value.get_int());
      } else {
        value.set_float(left_value.get_float() * right_value.get_float());
      }
    } break;

    case Type::DIV: {
      if (target_type == AttrType::INTS) {
        if (right_value.get_int() == 0) {
          // NOTE:
          // 设置为整数最大值是不正确的。通常的做法是设置为NULL，但是当前的miniob没有NULL概念，所以这里设置为整数最大值。
          // value.set_int(numeric_limits<int>::max());
          Value::set_null(value, AttrType::INTS);
        } else {
          value.set_int(left_value.get_int() / right_value.get_int());
        }
      } else {
        if (right_value.get_float() > -EPSILON && right_value.get_float() < EPSILON) {
          // NOTE:
          // 设置为浮点数最大值是不正确的。通常的做法是设置为NULL，但是当前的miniob没有NULL概念，所以这里设置为浮点数最大值。
          // value.set_float(numeric_limits<float>::max());
          Value::set_null(value, AttrType::FLOATS);
        } else {
          value.set_float(left_value.get_float() / right_value.get_float());
        }
      }
    } break;

    case Type::NEGATIVE: {
      if (target_type == AttrType::INTS) {
        value.set_int(-left_value.get_int());
      } else {
        value.set_float(-left_value.get_float());
      }
    } break;

    default: {
      rc = RC::INTERNAL;
      LOG_WARN("unsupported arithmetic type. %d", arithmetic_type_);
    } break;
  }
  return rc;
}

RC ArithmeticExpr::get_value(const Tuple &tuple, Value &value) {
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->get_value(tuple, left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }
  // The expression maybe of `-(expr)`
  if (right_ != nullptr) {
    rc = right_->get_value(tuple, right_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
      return rc;
    }
  } else {
    // FIXME: Ensure this
    right_value.set_int(0);
    right_value.set_type(left_value.attr_type());
  }
  return calc_value(left_value, right_value, value);
}

RC ArithmeticExpr::try_get_value(Value &value) const {
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->try_get_value(left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }

  if (right_) {
    rc = right_->try_get_value(right_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
      return rc;
    }
  }

  return calc_value(left_value, right_value, value);
}
