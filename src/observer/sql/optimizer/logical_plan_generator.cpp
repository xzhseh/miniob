/* Copyright (c) 2023 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2023/08/16.
//

#include "sql/optimizer/logical_plan_generator.h"
#include <memory>
#include "sql/expr/expression.h"
#include "sql/expr/sub_query_expr.h"
#include "sql/operator/agg_logical_operator.h"
#include "sql/operator/calc_logical_operator.h"
#include "sql/operator/delete_logical_operator.h"
#include "sql/operator/explain_logical_operator.h"
#include "sql/operator/insert_logical_operator.h"
#include "sql/operator/join_logical_operator.h"
#include "sql/operator/logical_operator.h"
#include "sql/operator/order_by_logical_operator.h"
#include "sql/operator/predicate_logical_operator.h"
#include "sql/operator/project_logical_operator.h"
#include "sql/operator/table_get_logical_operator.h"
#include "sql/operator/update_logical_operator.h"
#include "sql/stmt/calc_stmt.h"
#include "sql/stmt/delete_stmt.h"
#include "sql/stmt/explain_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/insert_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/stmt.h"
#include "sql/stmt/update_stmt.h"

using namespace std;

/// Logical plan factory
RC LogicalPlanGenerator::create(Stmt *stmt, unique_ptr<LogicalOperator> &logical_operator) {
  RC rc = RC::SUCCESS;
  switch (stmt->type()) {
    case StmtType::CALC: {
      CalcStmt *calc_stmt = static_cast<CalcStmt *>(stmt);
      rc = create_plan(calc_stmt, logical_operator);
    } break;

    case StmtType::UPDATE: {
      UpdateStmt *update_stmt = static_cast<UpdateStmt *>(stmt);
      rc = create_plan(update_stmt, logical_operator);
    } break;

    case StmtType::SELECT: {
      SelectStmt *select_stmt = static_cast<SelectStmt *>(stmt);
      rc = create_plan(select_stmt, logical_operator);
    } break;

    case StmtType::INSERT: {
      InsertStmt *insert_stmt = static_cast<InsertStmt *>(stmt);
      rc = create_plan(insert_stmt, logical_operator);
    } break;

    case StmtType::DELETE: {
      DeleteStmt *delete_stmt = static_cast<DeleteStmt *>(stmt);
      rc = create_plan(delete_stmt, logical_operator);
    } break;

    case StmtType::EXPLAIN: {
      ExplainStmt *explain_stmt = static_cast<ExplainStmt *>(stmt);
      rc = create_plan(explain_stmt, logical_operator);
    } break;
    default: {
      rc = RC::UNIMPLENMENT;
    }
  }
  return rc;
}

RC LogicalPlanGenerator::create_plan(UpdateStmt *update_stmt, std::unique_ptr<LogicalOperator> &logical_operator) {
  Table *table = update_stmt->table();
  FilterStmt *filter_stmt = update_stmt->filter_stmt();
  std::vector<Field> fields;
  for (int i = table->table_meta().sys_field_num(); i < table->table_meta().field_num(); i++) {
    const FieldMeta *field_meta = table->table_meta().field(i);
    fields.push_back(Field(table, field_meta));
  }
  unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, fields, false /*readonly*/));

  unique_ptr<LogicalOperator> predicate_oper;
  RC rc = create_plan(filter_stmt, predicate_oper);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  unique_ptr<LogicalOperator> update_oper(
      new UpdateLogicalOperator(update_stmt->table(), update_stmt->values(), update_stmt->field_metas()));
  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    update_oper->add_child(std::move(predicate_oper));
  } else {
    update_oper->add_child(std::move(table_get_oper));
  }

  logical_operator = std::move(update_oper);
  return rc;
}

RC LogicalPlanGenerator::create_plan(CalcStmt *calc_stmt, std::unique_ptr<LogicalOperator> &logical_operator) {
  logical_operator.reset(new CalcLogicalOperator(std::move(calc_stmt->expressions())));
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(SelectStmt *select_stmt, unique_ptr<LogicalOperator> &logical_operator) {
  unique_ptr<LogicalOperator> table_oper(nullptr);

  const std::vector<Table *> &tables = select_stmt->tables();
  const std::vector<Field> &all_fields = select_stmt->query_fields();
  auto join_stmts = select_stmt->join_stmts();
  std::set<std::string> joined_tables;

  for (size_t i = 0; i < tables.size(); i++) {
    Table *table = tables[i];
    std::vector<Field> fields;
    for (const Field &field : all_fields) {
      // How to handle alias? Eg : SELECT tbl.age_before FROM ages AS tbl;
      if (0 == strcmp(field.table_name(), table->name())) {
        fields.push_back(field);
      }
    }

    unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, fields, true /*readonly*/));
    if (table_oper == nullptr) {
      table_oper = std::move(table_get_oper);
    } else {
      // Multiple tables
      unique_ptr<Expression> join_condition;
      // Check if talbe_oper is left and table_get_oper is right
      for (auto join_stmt : join_stmts) {
        if (joined_tables.contains(join_stmt.left_field.table_name()) &&
            join_stmt.right_field.table_name() == tables[i]->name()) {
          unique_ptr<Expression> left(new FieldExpr(join_stmt.left_field));
          unique_ptr<Expression> right(new FieldExpr(join_stmt.right_field));
          join_condition = unique_ptr<Expression>(
              std::make_unique<ComparisonExpr>(CompOp::EQUAL_TO, std::move(left), std::move(right)));
          break;
        }
      }
      JoinLogicalOperator *join_oper = new JoinLogicalOperator(std::move(join_condition));
      join_oper->add_child(std::move(table_oper));
      join_oper->add_child(std::move(table_get_oper));
      table_oper = unique_ptr<LogicalOperator>(join_oper);
    }
    joined_tables.insert(table->name());
  }

  // TODO: Predicate push down? (or later)
  std::unique_ptr<LogicalOperator> predicate_oper;
  RC rc = create_plan(select_stmt->filter_stmt(), predicate_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create predicate logical plan. rc=%s", strrc(rc));
    return rc;
  }

  if (predicate_oper) {
    if (table_oper) {
      predicate_oper->add_child(std::move(table_oper));
    } else {
      return RC::INTERNAL;
    }
  }

  // Create the aggregate logical operator
  std::unique_ptr<LogicalOperator> agg_oper{nullptr};
  if (select_stmt->agg_stmt() != nullptr) {
    auto fields = select_stmt->agg_stmt()->get_fields();
    auto is_agg = select_stmt->agg_stmt()->get_is_agg();
    auto agg_types = select_stmt->agg_stmt()->get_agg_types();
    auto having = select_stmt->agg_stmt()->get_having();
    auto agg_exprs = select_stmt->agg_stmt()->get_agg_exprs();
    std::unique_ptr<AggLogicalOperator> agg_oper_t = std::make_unique<AggLogicalOperator>();
    agg_oper_t->set_fields(std::move(fields));
    agg_oper_t->set_is_agg(std::move(is_agg));
    agg_oper_t->set_agg_types(std::move(agg_types));
    agg_oper_t->set_having(std::move(having));
    agg_oper_t->set_agg_exprs(std::move(agg_exprs));
    agg_oper = std::move(agg_oper_t);
    assert(agg_oper != nullptr);
  }

  if (agg_oper) {
    if (predicate_oper) {
      agg_oper->add_child(std::move(predicate_oper));
    } else if (table_oper) {
      agg_oper->add_child(std::move(table_oper));
    } else {
      return RC::INTERNAL;
    }
  }

  unique_ptr<LogicalOperator> order_by_op;
  if (!select_stmt->order_by().empty()) {
    std::vector<OrderByExpr> order_by_exprs;
    for (auto &order_by_stmt : select_stmt->order_by()) {
      unique_ptr<Expression> field_expr(new FieldExpr(order_by_stmt.field));
      OrderByExpr order_by_expr{std::move(field_expr), order_by_stmt.asc};
      order_by_exprs.emplace_back(std::move(order_by_expr));
    }
    order_by_op = unique_ptr<LogicalOperator>(new OrderByLogicalOperator(std::move(order_by_exprs)));
    if (agg_oper) {
      order_by_op->add_child(std::move(agg_oper));
    } else if (predicate_oper) {
      order_by_op->add_child(std::move(predicate_oper));
    } else if (table_oper) {
      order_by_op->add_child((std::move(table_oper)));
    } else {
      return RC::INTERNAL;
    }
  }

<<<<<<< HEAD
  auto project_op = std::make_unique<ProjectLogicalOperator>(select_stmt->query_fields(), select_stmt->create_table_name(), select_stmt->create_view_name(), select_stmt->get_attrs());
=======
  auto project_op = std::make_unique<ProjectLogicalOperator>(
      select_stmt->query_fields(), select_stmt->create_table_name(), select_stmt->get_attrs());
>>>>>>> main

  if (select_stmt->get_select_expr_flag()) {
    project_op->select_expr_flag_ = true;
    project_op->select_expr_ = select_stmt->get_select_expr();
  }

  if (select_stmt->is_fun_fast_path()) {
    project_op->func_fast_path_ = true;
  }

  // FIXME: Is this enough to identify create table select statement?
  if (select_stmt->create_table_name() != "" || select_stmt->create_view_name() != "") {
    project_op->tables_ = select_stmt->tables();
  }

  unique_ptr<LogicalOperator> project_oper(std::move(project_op));

  if (order_by_op) {
    project_oper->add_child(std::move(order_by_op));
  } else if (agg_oper) {
    project_oper->add_child(std::move(agg_oper));
  } else if (predicate_oper) {
    project_oper->add_child(std::move(predicate_oper));
  } else {
    project_oper->add_child(std::move(table_oper));
  }

  logical_operator.swap(project_oper);
  return RC::SUCCESS;
}

void generate_conjunction(const vector<FilterUnit *> &filter_units, size_t i, vector<unique_ptr<Expression>> &cmp_exprs,
                          unique_ptr<ConjunctionExpr> &conjunction_expr) {
  // Notice : the conditions is reversed : sql: condition1 and/or condition2 and/or condition3
  // After parser : condition3 and/or condition2 and/or condition1
  bool is_and = filter_units[i + 1]->is_and();
  if (is_and) {
    if (conjunction_expr == nullptr) {
      vector<unique_ptr<Expression>> children;
      children.emplace_back(std::move(cmp_exprs[i]));
      children.emplace_back(std::move(cmp_exprs[i + 1]));
      conjunction_expr = make_unique<ConjunctionExpr>(ConjunctionExpr::Type::AND, children);
    } else {
      vector<unique_ptr<Expression>> children;
      children.emplace_back(std::move(conjunction_expr));
      children.emplace_back(std::move(cmp_exprs[i + 1]));
      conjunction_expr = make_unique<ConjunctionExpr>(ConjunctionExpr::Type::AND, children);
    }
  } else {
    if (conjunction_expr == nullptr) {
      vector<unique_ptr<Expression>> children;
      children.emplace_back(std::move(cmp_exprs[i]));
      children.emplace_back(std::move(cmp_exprs[i + 1]));
      conjunction_expr = make_unique<ConjunctionExpr>(ConjunctionExpr::Type::OR, children);
    } else {
      vector<unique_ptr<Expression>> children;
      children.emplace_back(std::move(conjunction_expr));
      children.emplace_back(std::move(cmp_exprs[i + 1]));
      conjunction_expr = make_unique<ConjunctionExpr>(ConjunctionExpr::Type::OR, children);
    }
  }
}

RC LogicalPlanGenerator::create_plan(FilterStmt *filter_stmt, unique_ptr<LogicalOperator> &logical_operator) {
  if (filter_stmt->is_where_expr()) {
    auto predicate_oper = std::make_unique<PredicateLogicalOperator>();
    predicate_oper->where_expr_flag_ = true;
    predicate_oper->where_expr_vec_ = filter_stmt->get_where_expr();
    logical_operator = std::move(predicate_oper);
    return RC::SUCCESS;
  }

  std::vector<unique_ptr<Expression>> cmp_exprs;
  const std::vector<FilterUnit *> &filter_units = filter_stmt->filter_units();
  for (const FilterUnit *filter_unit : filter_units) {
    const FilterObj &filter_obj_left = filter_unit->left();
    const FilterObj &filter_obj_right = filter_unit->right();

    // Left is attr and value. Const value list and sub query are not supported yet.
    unique_ptr<Expression> left = nullptr;
    switch (filter_obj_left.type) {
      case FilterObjType::ATTR:
        left = unique_ptr<Expression>(new FieldExpr(filter_obj_left.field));
        break;
      case FilterObjType::VALUE:
        left = unique_ptr<Expression>(new ValueExpr(filter_obj_left.value));
        break;
      case FilterObjType::VALUE_LIST:
        left = unique_ptr<Expression>(new SubQueryExpr(filter_obj_left.value_list));
        break;
      case FilterObjType::SUB_QUERY:
        left = unique_ptr<Expression>(new SubQueryExpr(filter_obj_left.sub_query, filter_obj_left.table_map));
        break;
      default:
        assert(false);
    }

    if (left->type() == ExprType::SUB_QUERY) {
      SubQueryExpr *sub_query_expr = dynamic_cast<SubQueryExpr *>(left.get());
      CompOp comp_op = filter_unit->comp();
      if (comp_op == IN_OP || comp_op == NOT_IN) {
        sub_query_expr->set_return_value(false);
      } else {
        sub_query_expr->set_return_value(true);
      }
    }

    unique_ptr<Expression> right = nullptr;
    switch (filter_obj_right.type) {
      case FilterObjType::ATTR:
        right = unique_ptr<Expression>(new FieldExpr(filter_obj_right.field));
        break;
      case FilterObjType::VALUE:
        right = unique_ptr<Expression>(new ValueExpr(filter_obj_right.value));
        break;
      case FilterObjType::VALUE_LIST:
        right = unique_ptr<Expression>(new SubQueryExpr(filter_obj_right.value_list));
        break;
      case FilterObjType::SUB_QUERY:
        right = unique_ptr<Expression>(new SubQueryExpr(filter_obj_right.sub_query, filter_obj_right.table_map));
        break;
      default:
        assert(false);
    }

    if (right->type() == ExprType::SUB_QUERY) {
      auto *sub_query_expr = dynamic_cast<SubQueryExpr *>(right.get());
      CompOp comp_op = filter_unit->comp();
      if (comp_op == IN_OP || comp_op == NOT_IN) {
        sub_query_expr->set_return_value(false);
      } else {
        sub_query_expr->set_return_value(true);
      }
    }
    assert(right != nullptr);

    ComparisonExpr *cmp_expr = new ComparisonExpr(filter_unit->comp(), std::move(left), std::move(right));
    cmp_exprs.emplace_back(cmp_expr);
  }
  // So we could use it like a queue
  unique_ptr<PredicateLogicalOperator> predicate_oper;
  unique_ptr<ConjunctionExpr> conjunction_expr = nullptr;
  for (size_t i = 0; cmp_exprs.size() >= 2 && i < cmp_exprs.size() - 1; i++) {
    generate_conjunction(filter_units, i, cmp_exprs, conjunction_expr);
  }
  if (conjunction_expr != nullptr) {
    predicate_oper = std::make_unique<PredicateLogicalOperator>(std::move(conjunction_expr));
  } else if (!cmp_exprs.empty()) {
    predicate_oper = std::make_unique<PredicateLogicalOperator>(std::move(cmp_exprs[0]));
  }

  logical_operator = std::move(predicate_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(InsertStmt *insert_stmt, unique_ptr<LogicalOperator> &logical_operator) {
  Table *table = insert_stmt->table();
  vector<Value> values(insert_stmt->values(), insert_stmt->values() + insert_stmt->value_amount());

  InsertLogicalOperator *insert_operator = new InsertLogicalOperator(table, values);
  logical_operator.reset(insert_operator);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(DeleteStmt *delete_stmt, unique_ptr<LogicalOperator> &logical_operator) {
  Table *table = delete_stmt->table();
  FilterStmt *filter_stmt = delete_stmt->filter_stmt();
  std::vector<Field> fields;
  for (int i = table->table_meta().sys_field_num(); i < table->table_meta().field_num(); i++) {
    const FieldMeta *field_meta = table->table_meta().field(i);
    fields.push_back(Field(table, field_meta));
  }
  unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, fields, false /*readonly*/));

  unique_ptr<LogicalOperator> predicate_oper;
  RC rc = create_plan(filter_stmt, predicate_oper);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  unique_ptr<LogicalOperator> delete_oper(new DeleteLogicalOperator(table));

  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    delete_oper->add_child(std::move(predicate_oper));
  } else {
    delete_oper->add_child(std::move(table_get_oper));
  }

  logical_operator = std::move(delete_oper);
  return rc;
}

RC LogicalPlanGenerator::create_plan(ExplainStmt *explain_stmt, unique_ptr<LogicalOperator> &logical_operator) {
  Stmt *child_stmt = explain_stmt->child();
  unique_ptr<LogicalOperator> child_oper;
  RC rc = create(child_stmt, child_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create explain's child operator. rc=%s", strrc(rc));
    return rc;
  }

  logical_operator = unique_ptr<LogicalOperator>(new ExplainLogicalOperator);
  logical_operator->add_child(std::move(child_oper));
  return rc;
}
