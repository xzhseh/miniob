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
// Created by Wangyunlai on 2022/5/22.
//

#pragma once

#include "common/rc.h"
#include "sql/stmt/stmt.h"

class Table;
class FilterStmt;
/**
 * @brief 更新语句
 * @ingroup Statement
 */
class UpdateStmt : public Stmt 
{
public:
  // FIXME: Please ensure this
  // UpdateStmt() = default;
  UpdateStmt(Table *table,const Value &value, int value_offset, FilterStmt* filter_stmt);
  StmtType type() const override 
  {
    return StmtType::UPDATE;
  }
public:
  static RC create(Db *db, UpdateSqlNode &update_sql, Stmt *&stmt);

public:
  Table *table() const
  {
    return table_;
  }
  const Value& value() const
  {
    return value_;
  }
  int value_offset() const
  {
    return value_offset_;
  }
  FilterStmt* filter_stmt() const 
  {
    return filter_stmt_;
  }

private:
  Table *table_ = nullptr;
  const Value& value_;
  int value_offset_ = 0; //后面修改Record要用，但是多个Record别的字段可能不同，所以只能延迟修改, 这里做了一点改动
  FilterStmt* filter_stmt_ = nullptr;
};
