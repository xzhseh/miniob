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
  /// For expression evaluation, will be transformed to `Field` in `select_stmt.cpp`
  FuncExpr(const RelAttrSqlNode &rel_attr, func func_type, std::string &alias)
      : rel_attr_(rel_attr), func_type_(func_type), is_value_(false), alias_(alias) {}

  FuncExpr(const Value &value, func func_type, std::string &alias)
      : v_expr_(value), func_type_(func_type), is_value_(true), alias_(alias) {}

  virtual ~FuncExpr() = default;

  ExprType type() const override { return ExprType::FUNC; }

  // FIXME: Ensure this, basically we need to return the return type of the stored function
  AttrType value_type() const override {
    return field_.attr_type();
  }

  bool is_value() { return is_value_; }

  Field &field() { return field_; }

  const Field &field() const { return field_; }

  const char *table_name() const { return field_.table_name(); }

  const char *field_name() const { return field_.field_name(); }

  std::string alias_name() const { return alias_; }

  RC func_evaluate(Value &value) {
    switch (func_type_) {
      case func::FUNC_LENGTH: {
        if (value.attr_type() != AttrType::CHARS) {
          return RC::INVALID_ARGUMENT;
        }
        int length = value.get_string().size();
        value.set_int(length);
      } break;
      case func::FUNC_ROUND: {
        if (value.attr_type() != AttrType::FLOATS) {
          return RC::INVALID_ARGUMENT;
        }
        // FIXME: Ensure this
        int round = (int) value.get_float();
        value.set_int(round);
      } break;
      case func::FUNC_DATE_FORMAT: {
        if (value.attr_type() != AttrType::DATE) {
          return RC::INVALID_ARGUMENT;
        }
        // FIXME: implement this function
        int round = (int) value.get_float();
        value.set_int(round);
      } break;
      default: {
        return RC::INVALID_ARGUMENT;
      }
    }
    return RC::SUCCESS;
  }

  RC get_value(const Tuple &tuple, Value &value) override {
    RC rc = RC::SUCCESS;
    if (is_value_) {
      rc = v_expr_.get_value(tuple, value);
    } else {
      rc = f_expr_.get_value(tuple, value);
    }
    if (rc != RC::SUCCESS) {
      LOG_WARN("[FuncExpr::get_value] failed to get the value from underlying expression");
      return rc;
    }
    rc = func_evaluate(value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("[FuncExpr::func_evaluate] invalid argument: %s.", value.to_string().c_str());
      return rc;
    }
    return rc;
  }

  void set_agg_value(Value &v) {
    agg_flag_ = true;
    agg_value_ = v;
  }

  Expression *left() const override { return nullptr; }
  Expression *right() const override { return nullptr; }

  const RelAttrSqlNode &get_rel_attr() { return rel_attr_; }

  void set_field(const Field &field) { field_ = field; }

 private:
  FieldExpr f_expr_;
  ValueExpr v_expr_;
  bool is_value_{false};
  Field field_;
  RelAttrSqlNode rel_attr_;
  // To deal with agg in expression
  Value agg_value_;
  bool agg_flag_{false};
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