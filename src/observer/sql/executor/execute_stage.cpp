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
// Created by Longda on 2021/4/13.
//

#include <sstream>
#include <string>

#include "sql/executor/execute_stage.h"

#include "common/log/log.h"
#include "event/session_event.h"
#include "event/sql_event.h"
#include "event/storage_event.h"
#include "session/session.h"
#include "sql/executor/command_executor.h"
#include "sql/operator/calc_physical_operator.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/stmt.h"
#include "storage/default/default_handler.h"

using namespace std;
using namespace common;

RC ExecuteStage::handle_request(SQLStageEvent *sql_event) {
  RC rc = RC::SUCCESS;
  const unique_ptr<PhysicalOperator> &physical_operator = sql_event->physical_operator();
  if (physical_operator != nullptr) {
    return handle_request_with_physical_operator(sql_event);
  }

  SessionEvent *session_event = sql_event->session_event();

  Stmt *stmt = sql_event->stmt();
  if (stmt != nullptr) {
    CommandExecutor command_executor;
    rc = command_executor.execute(sql_event);
    session_event->sql_result()->set_return_code(rc);
  } else {
    return RC::INTERNAL;
  }
  return rc;
}

TupleSchema create_sub_result_schema(const SelectStmt *select_stmt) {
  TupleSchema schema;
  // FIXME: Refactor this (This is currently hard-coded for aggregation case)
  bool with_table_name = select_stmt->tables().size() > 1;

  // FIXME: Hardcoded for expression
  // if (select_stmt->get_select_expr_flag()) {
  //   for (const auto *expr : select_stmt->get_select_expr()) {
  //     std::cout << "[create_sub_result_schema] current expr: " << expr->name() << std::endl;
  //     schema.append_cell(expr->name().c_str());
  //   }
  //   return schema;
  // }

  // FIXME: Refactor this (This is currently hard-coded for aggregation case)
  if (select_stmt->agg_stmt() != nullptr) {
    // Construct the schema based on the agg_stmt
    // rather than the query_fields at present
    auto &keys = select_stmt->agg_stmt()->get_fields();
    auto &types = select_stmt->agg_stmt()->get_agg_types();
    auto &is_agg = select_stmt->agg_stmt()->get_is_agg();
    size_t n = keys.size();
    for (int i = 0; i < n; ++i) {
      auto &f = keys[i];
      std::string s;
      if (f.table() != nullptr && with_table_name) {
        s += f.table_name();
        s += ".";
      }

      s += (f.meta() == nullptr && f.table() == nullptr) ? "*" : f.field_name();
      if (is_agg[i]) {
        s = std::string(agg_to_string(types[i])) + "(" + s + ")";
      }
      schema.append_cell(s.c_str());
    }
    return schema;
  }

  for (size_t i = 0; i < select_stmt->query_fields().size(); i++) {
    const auto &field = select_stmt->query_fields()[i];
    schema.append_cell(field.table_name(), field.field_name());
  }
  return schema;
}

RC ExecuteStage::handle_request_with_physical_operator(SQLStageEvent *sql_event) {
  RC rc = RC::SUCCESS;

  Stmt *stmt = sql_event->stmt();
  ASSERT(stmt != nullptr, "SQL Statement shouldn't be empty!");

  unique_ptr<PhysicalOperator> &physical_operator = sql_event->physical_operator();
  ASSERT(physical_operator != nullptr, "physical operator should not be null");

  // TODO 这里也可以优化一下，是否可以让physical operator自己设置tuple schema
  TupleSchema schema;
  switch (stmt->type()) {
    case StmtType::SELECT: {
      auto *select_stmt = dynamic_cast<SelectStmt *>(stmt);
      bool with_table_name = select_stmt->tables().size() > 1;

      // FIXME: Hardcoded for expression
      if (select_stmt->get_select_expr_flag()) {
        for (const auto *expr : select_stmt->get_select_expr()) {
          std::cout << "[ExecuteStage::handle_request_with_physical_operator] current expr: " << expr->name()
                    << std::endl;
          // For fast function pass
          FuncExpr *res = dynamic_cast<FuncExpr *>((Expression *)expr);
          if (res && !res->alias_name().empty()) {
            schema.append_cell(res->alias_name().c_str());
          } else {
            schema.append_cell(expr->name().c_str());
          }
        }
        break;
      }

      // FIXME: Refactor this (This is currently hard-coded for aggregation case)
      if (select_stmt->agg_stmt() != nullptr) {
        // Construct the schema based on the agg_stmt
        // rather than the query_fields at present
        auto &keys = select_stmt->agg_stmt()->get_fields();
        auto &types = select_stmt->agg_stmt()->get_agg_types();
        auto &is_agg = select_stmt->agg_stmt()->get_is_agg();
        int n = keys.size();
        for (int i = 0; i < n; ++i) {
          auto &f = keys[i];
          std::string s{""};
          if (f.table() != nullptr && with_table_name) {
            s += f.table_name();
            s += ".";
          }

          s += (f.meta() == nullptr && f.table() == nullptr) ? "*" : f.field_name();
          if (is_agg[i]) {
            s = std::string(agg_to_string(types[i])) + "(" + s + ")";
          }
          schema.append_cell(s.c_str());
        }
        break;
      }
      for (size_t i = 0; i < select_stmt->query_fields().size(); i++) {
        const auto &field = select_stmt->query_fields()[i];
        if (with_table_name) {
          schema.append_cell(field.table_name(), field.field_name());
        } else {
          schema.append_cell(field.field_name());
        }
      }
    } break;

    case StmtType::CALC: {
      CalcPhysicalOperator *calc_operator = static_cast<CalcPhysicalOperator *>(physical_operator.get());
      for (const unique_ptr<Expression> &expr : calc_operator->expressions()) {
        schema.append_cell(expr->name().c_str());
      }
    } break;

    case StmtType::EXPLAIN: {
      schema.append_cell("Query Plan");
    } break;
    default: {
      // 只有select返回结果
    } break;
  }

  SqlResult *sql_result = sql_event->session_event()->sql_result();
  sql_result->set_tuple_schema(schema);
  sql_result->set_operator(std::move(physical_operator));
  return rc;
}
