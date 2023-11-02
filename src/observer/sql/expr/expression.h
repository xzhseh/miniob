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

#pragma once

#include <cstring>
#include <memory>
#include <string>
#include <math.h>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "common/log/log.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"
#include "storage/field/field.h"

class Tuple;

/**
 * @defgroup Expression
 * @brief 表达式
 */

/**
 * @brief 表达式类型
 * @ingroup Expression
 */
enum class ExprType {
  NONE,
  STAR,         ///< 星号，表示所有字段
  FIELD,        ///< 字段。在实际执行时，根据行数据内容提取对应字段的值
  VALUE,        ///< 常量值
  CAST,         ///< 需要做类型转换的表达式
  COMPARISON,   ///< 需要做比较的表达式
  CONJUNCTION,  ///< 多个表达式使用同一种关系(AND或OR)来联结
  ARITHMETIC,   ///< 算术运算
  SUB_QUERY,    ///< 子查询，比如在IN子句中，子查询的结果是一个集合，需要和字段的值做比较
  FUNC,         ///< 函数
};

/**
 * @brief 表达式的抽象描述
 * @ingroup Expression
 * @details 在SQL的元素中，任何需要得出值的元素都可以使用表达式来描述
 * 比如获取某个字段的值、比较运算、类型转换
 * 当然还有一些当前没有实现的表达式，比如算术运算。
 *
 * 通常表达式的值，是在真实的算子运算过程中，拿到具体的tuple后
 * 才能计算出来真实的值。但是有些表达式可能就表示某一个固定的
 * 值，比如ValueExpr。
 */
class Expression {
 public:
  Expression() = default;
  virtual ~Expression() = default;

  /**
   * @brief 根据具体的tuple，来计算当前表达式的值。tuple有可能是一个具体某个表的行数据
   */
  virtual RC get_value(const Tuple &tuple, Value &value) = 0;

  /**
   * @brief 在没有实际运行的情况下，也就是无法获取tuple的情况下，尝试获取表达式的值
   * @details 有些表达式的值是固定的，比如ValueExpr，这种情况下可以直接获取值
   */
  virtual RC try_get_value(Value &value) const { return RC::UNIMPLENMENT; }

  /**
   * @brief 表达式的类型
   * 可以根据表达式类型来转换为具体的子类
   */
  virtual ExprType type() const = 0;

  /**
   * @brief 表达式值的类型
   * @details 一个表达式运算出结果后，只有一个值
   */
  virtual AttrType value_type() const = 0;

  /**
   * @brief 表达式的名字，比如是字段名称，或者用户在执行SQL语句时输入的内容
   */
  virtual std::string name() const { return name_; }
  virtual void set_name(std::string name) { name_ = name; }

  virtual Expression *left() const { return nullptr; }
  virtual Expression *right() const { return nullptr; }

 private:
  std::string name_;
};

/**
 * @brief 字段表达式
 * @ingroup Expression
 */
class FieldExpr : public Expression {
 public:
  FieldExpr() = default;
  FieldExpr(const Table *table, const FieldMeta *field) : field_(table, field) {}
  FieldExpr(const Field &field) : field_(field) {}

  /// For expression evaluation, will be transformed to `Field` in `select_stmt.cpp`
  FieldExpr(const RelAttrSqlNode &rel_attr) : rel_attr_(rel_attr) {}

  virtual ~FieldExpr() = default;

  ExprType type() const override { return ExprType::FIELD; }
  AttrType value_type() const override { return field_.attr_type(); }

  Field &field() { return field_; }

  const Field &field() const { return field_; }

  const char *table_name() const { return field_.table_name(); }

  const char *field_name() const { return field_.field_name(); }

  RC get_value(const Tuple &tuple, Value &value) override;

  void set_agg_value(Value &v) {
    agg_flag_ = true;
    agg_value_ = v;
  }

  Expression *left() const override { return nullptr; }
  Expression *right() const override { return nullptr; }

  const RelAttrSqlNode &get_rel_attr() { return rel_attr_; }

  void set_field(const Field &field) { field_ = field; }

 private:
  Field field_;
  RelAttrSqlNode rel_attr_;
  // To deal with agg in expression
  Value agg_value_;
  bool agg_flag_{false};
};

/**
 * @brief 常量值表达式
 * @ingroup Expression
 */
class ValueExpr : public Expression {
 public:
  ValueExpr() = default;
  explicit ValueExpr(const Value &value) : value_(value) {}

  virtual ~ValueExpr() = default;

  RC get_value(const Tuple &tuple, Value &value) override;
  RC try_get_value(Value &value) const override {
    value = value_;
    return RC::SUCCESS;
  }

  ExprType type() const override { return ExprType::VALUE; }

  AttrType value_type() const override { return value_.attr_type(); }

  void get_value(Value &value) const { value = value_; }

  const Value &get_value() const { return value_; }

  Expression *left() const override { return nullptr; }
  Expression *right() const override { return nullptr; }

 private:
  Value value_;
};

class FuncExpr: public Expression {
 public:
  explicit FuncExpr(std::vector<Expression *> &&param_expr_list, func func_type, std::string &alias)
      : param_expr_list_(std::move(param_expr_list)), func_type_(func_type), alias_(alias) {}

  virtual ~FuncExpr() = default;

  ExprType type() const override { return ExprType::FUNC; }

  // FIXME: Ensure this, basically we need to return the return type of the stored function
  AttrType value_type() const override {
    switch (func_type_) {
      case func::FUNC_DATE_FORMAT:
        return AttrType::CHARS;
      case func::FUNC_LENGTH:
        return AttrType::INTS;
      case func::FUNC_ROUND:
        if (param_expr_list_.size() == 2) {
          return AttrType::FLOATS;
        } else {
          return AttrType::INTS;
        }
      default:
          assert(false);
    }
    assert(false);
  }

  std::string getEnglishSuffix(int day) {
    if (day >= 11 && day <= 13) {
      return "th";
    }

    switch (day % 10) {
      case 1: return "st";
      case 2: return "nd";
      case 3: return "rd";
      default: return "th";
    }
  }

  std::string getMonthName(int month) {
    static const std::vector<std::string> months = {
        "", "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    if (month > 0 && month <= 12) {
      return months[month];
    } else {
      return "Invalid";
    }
  }

  std::string mysql_date_format(const std::string &date, const std::string &format) {
    int year, month, day;
    char dash1, dash2;

    std::istringstream dateStream(date);
    dateStream >> year >> dash1 >> month >> dash2 >> day;

    // Check if the date was in the correct format
    if (!dateStream || dash1 != '-' || dash2 != '-') {
      return "Invalid date format";
    }

    std::ostringstream result;
    for (size_t i = 0; i < format.size(); ++i) {
      if (format[i] == '%') {
          if (++i < format.size()) {
          switch (format[i]) {
            case 'Y': // Year with century
              result << std::setw(4) << std::setfill('0') << year;
              break;
            case 'y': // Year without century
              result << std::setw(2) << std::setfill('0') << (year % 100);
              break;
            case 'm': // Month, numeric (00..12)
              result << std::setw(2) << std::setfill('0') << month;
              break;
            case 'd': // Day of the month, numeric (00..31)
              result << std::setw(2) << std::setfill('0') << day;
              break;
            case 'D': // Day of the month with English suffix
              result << day << getEnglishSuffix(day);
              break;
            case 'M': // Full month name
              result << getMonthName(month);
              break;
            // Add more cases for other specifiers as needed.
            default:
              // If the specifier is not recognized, just return it as is.
//              result << '%' << format[i];
              break;
          }
          }
      } else {
          result << format[i];
      }
    }
    return result.str();
  }

  std::string alias_name() const { return alias_; }

  std::vector<Expression *> &get_param_expr_list() { return param_expr_list_; }

  RC func_evaluate(const Tuple &tuple, Value &value) {
    RC rc = RC::SUCCESS;
    switch (func_type_) {
      case func::FUNC_LENGTH: {
        if (param_expr_list_.size() != 1) {
          return RC::INVALID_ARGUMENT;
        }

        Value v;
        rc = param_expr_list_[0]->get_value(tuple, v);
        if (rc != RC::SUCCESS) {
          LOG_WARN("[FuncExpr::func_evaluate::func_length] failed to get the value from param_expr_list");
          return rc;
        }
        if (v.attr_type() != AttrType::CHARS) {
          return RC::INVALID_ARGUMENT;
        }
        int length = v.get_string().size();
        value.set_int(length);
      } break;
      case func::FUNC_ROUND: {
        if (param_expr_list_.size() > 2) {
          return RC::INVALID_ARGUMENT;
        }

        if (param_expr_list_.size() == 1) {
          Value v;
          rc = param_expr_list_[0]->get_value(tuple, v);
          if (v.attr_type() != AttrType::FLOATS) {
            return RC::INVALID_ARGUMENT;
          }
          assert(rc == RC::SUCCESS);
          value.set_int(round(v.get_float()));
          return rc;
        }

        Value num;
        Value precision;
        // Note, in reverse order
        rc = param_expr_list_[1]->get_value(tuple, num);
        if (rc != RC::SUCCESS) {
          LOG_WARN("[FuncExpr::func_evaluate::func_round] failed to get the value from param_expr_list");
          return rc;
        }
        rc = param_expr_list_[0]->get_value(tuple, precision);
        if (rc != RC::SUCCESS) {
          LOG_WARN("[FuncExpr::func_evaluate::func_round] failed to get the value from param_expr_list");
          return rc;
        }
        if (num.attr_type() != AttrType::FLOATS || precision.attr_type() != AttrType::INTS) {
          return RC::INVALID_ARGUMENT;
        }
        double mul = pow(10.0, precision.get_int());
        double res = round(num.get_float() * mul) / mul;
        value.set_float(res);
      } break;
      case func::FUNC_DATE_FORMAT: {
        /// i.e., `SELECT DATE_FORMAT("2017-06-15", "%Y")`
        if (param_expr_list_.size() != 2) {
          return RC::INVALID_ARGUMENT;
        }

        Value date_str;
        Value format;

        rc = param_expr_list_[1]->get_value(tuple, date_str);
        if (rc != RC::SUCCESS) {
          LOG_WARN("[FuncExpr::func_evaluate::func_date_format] failed to get the value from param_expr_list");
          return rc;
        }

        rc = param_expr_list_[0]->get_value(tuple, format);
        if (rc != RC::SUCCESS) {
          LOG_WARN("[FuncExpr::func_evaluate::func_date_format] failed to get the value from param_expr_list");
          return rc;
        }

        // Type sanity check
        if (date_str.attr_type() != AttrType::DATE || format.attr_type() != AttrType::CHARS) {
          return rc;
        }

        value.set_string(mysql_date_format(date_str.get_string(), format.get_string()).c_str());
      } break;
      default: {
        return RC::INVALID_ARGUMENT;
      }
    }
    return rc;
  }

  RC get_value(const Tuple &tuple, Value &value) override {
    RC rc = func_evaluate(tuple, value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("[FuncExpr::func_evaluate] invalid argument: %s.", value.to_string().c_str());
      return rc;
    }
    return RC::SUCCESS;
  }

  Expression *left() const override { return nullptr; }
  Expression *right() const override { return nullptr; }

 private:
  std::vector<Expression *> param_expr_list_;
  func func_type_;
  std::string alias_{""};
};

/**
 * @brief 类型转换表达式
 * @ingroup Expression
 */
class CastExpr : public Expression {
 public:
  CastExpr(std::unique_ptr<Expression> child, AttrType cast_type);
  virtual ~CastExpr();

  ExprType type() const override { return ExprType::CAST; }
  RC get_value(const Tuple &tuple, Value &value) override;

  RC try_get_value(Value &value) const override;

  AttrType value_type() const override { return cast_type_; }

  std::unique_ptr<Expression> &child() { return child_; }

  // FIXME: Ensure this
  Expression *left() const override { return child_.get(); }
  Expression *right() const override { return nullptr; }

 private:
  RC cast(const Value &value, Value &cast_value) const;

 private:
  std::unique_ptr<Expression> child_;  ///< 从这个表达式转换
  AttrType cast_type_;                 ///< 想要转换成这个类型
};

/**
 * @brief 比较表达式
 * @ingroup Expression
 */
class ComparisonExpr : public Expression {
 public:
  ComparisonExpr(CompOp comp, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);
  virtual ~ComparisonExpr();

  ExprType type() const override { return ExprType::COMPARISON; }

  RC get_value(const Tuple &tuple, Value &value) override;

  AttrType value_type() const override { return BOOLEANS; }

  CompOp comp() const { return comp_; }

  std::unique_ptr<Expression> &left() { return left_; }
  std::unique_ptr<Expression> &right() { return right_; }

  Expression *left() const override { return left_.get(); }
  Expression *right() const override { return right_.get(); }

  /**
   * 尝试在没有tuple的情况下获取当前表达式的值
   * 在优化的时候，可能会使用到
   */
  RC try_get_value(Value &value) const override;

  /**
   * compare the two tuple cells
   * @param value the result of comparison
   */
  RC compare_value(const Value &left, const Value &right, bool &value) const;

 private:
  RC compare_in(const Value &left, bool &result) const;
  CompOp comp_;
  std::unique_ptr<Expression> left_;
  std::unique_ptr<Expression> right_;
};

/**
 * @brief 联结表达式
 * @ingroup Expression
 * 多个表达式使用同一种关系(AND或OR)来联结
 * 当前miniob仅有AND操作
 */
class ConjunctionExpr : public Expression {
 public:
  enum class Type {
    AND,
    OR,
  };

 public:
  ConjunctionExpr(Type type, std::vector<std::unique_ptr<Expression>> &children);
  virtual ~ConjunctionExpr() = default;

  ExprType type() const override { return ExprType::CONJUNCTION; }

  AttrType value_type() const override { return BOOLEANS; }

  RC get_value(const Tuple &tuple, Value &value) override;

  Type conjunction_type() const { return conjunction_type_; }

  std::vector<std::unique_ptr<Expression>> &children() { return children_; }

  // FIXME: Ensure this
  Expression *left() const override { return nullptr; }
  Expression *right() const override { return nullptr; }

 private:
  Type conjunction_type_;
  std::vector<std::unique_ptr<Expression>> children_;
};

/**
 * @brief 算术表达式
 * @ingroup Expression
 */
class ArithmeticExpr : public Expression {
 public:
  enum class Type {
    ADD,
    SUB,
    MUL,
    DIV,
    NEGATIVE,
  };

 public:
  ArithmeticExpr(Type type, Expression *left, Expression *right);
  ArithmeticExpr(Type type, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);
  virtual ~ArithmeticExpr() = default;

  ExprType type() const override { return ExprType::ARITHMETIC; }

  AttrType value_type() const override;

  RC get_value(const Tuple &tuple, Value &value) override;
  RC try_get_value(Value &value) const override;

  Type arithmetic_type() const { return arithmetic_type_; }

  std::unique_ptr<Expression> &left() { return left_; }
  std::unique_ptr<Expression> &right() { return right_; }

  Expression *left() const override { return left_.get(); }
  Expression *right() const override { return right_.get(); }

 private:
  RC calc_value(const Value &left_value, const Value &right_value, Value &value) const;

 private:
  Type arithmetic_type_;
  std::unique_ptr<Expression> left_;
  std::unique_ptr<Expression> right_;
};