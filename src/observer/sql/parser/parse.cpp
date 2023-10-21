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
// Created by Meiyi
//

#include "sql/parser/parse.h"
#include <mutex>
#include "common/log/log.h"
#include "sql/expr/expression.h"

RC parse(char *st, ParsedSqlNode *sqln);

CalcSqlNode::~CalcSqlNode() {
  for (Expression *expr : expressions) {
    delete expr;
  }
  expressions.clear();
}

ParsedSqlNode::ParsedSqlNode() : flag(SCF_ERROR) {}

ParsedSqlNode::ParsedSqlNode(SqlCommandFlag _flag) : flag(_flag) {}

void ParsedSqlResult::add_sql_node(std::unique_ptr<ParsedSqlNode> sql_node) {
  sql_nodes_.emplace_back(std::move(sql_node));
}

////////////////////////////////////////////////////////////////////////////////

int sql_parse(const char *st, ParsedSqlResult *sql_result);

/// Note that this is the entry point that will call `yyparse()`
/// Which is essentially the same as `sql_parse()` here, to begin the parsing part
/// The final output would be stored in the `sql_result` here.
RC parse(const char *st, ParsedSqlResult *sql_result) {
  sql_parse(st, sql_result);
  return RC::SUCCESS;
}
