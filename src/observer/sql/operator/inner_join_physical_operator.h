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
// Created by WangYunlai on 2021/6/10.
//

#pragma once

#include "sql/parser/parse.h"
#include "sql/operator/physical_operator.h"

/**
 * @brief 最简单的两表（称为左表、右表）join算子
 * @ingroup PhysicalOperator
 */
class InnerJoinOperator : public PhysicalOperator
{
public:
  explicit InnerJoinOperator(std::unique_ptr<Expression> join_condition);
  ~InnerJoinOperator() override = default;

  virtual PhysicalOperatorType type() const override
  {
    return PhysicalOperatorType::NESTED_LOOP_JOIN;
  }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;
  Tuple *current_tuple() override;

private:

private:
  Trx *trx_ = nullptr;

  PhysicalOperator *left_ = nullptr;
  PhysicalOperator *right_ = nullptr;
  std::unique_ptr<Expression> join_condition_;
  Tuple *left_tuple_ = nullptr;
  Tuple *right_tuple_ = nullptr;
  JoinedTuple joined_tuple_;  //! 当前关联的左右两个tuple
  bool round_done_ = true;    //! 右表遍历的一轮是否结束
  bool right_closed_ = true;  //! 右表算子是否已经关闭
};
