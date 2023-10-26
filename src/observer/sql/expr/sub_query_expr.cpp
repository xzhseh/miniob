//
// Created by susun on 23-10-23.
//

#include "sub_query_expr.h"
#include "session/session_stage.h"

SubQueryExpr::SubQueryExpr(const std::vector<Value> &const_value_list) {
  this->type_ = SubResultType::CONST_VALUE_LIST;
  this->const_value_list = const_value_list;
}

SubQueryExpr::SubQueryExpr(const std::shared_ptr<ParsedSqlNode> &sub_query) {
  this->type_ = SubResultType::SUB_QUERY;
  this->sub_query_event_ = std::make_unique<SQLStageEvent>(sub_query);
}

RC SubQueryExpr::in_or_not(const Value &value, const std::unique_ptr<Expression> &field_expr, bool &result) const {
  if (this->type_ == SubResultType::UNDEFINED) {
    return RC::INTERNAL;
  }
  if (this->type_ == SubResultType::CONST_VALUE_LIST) {
    for (auto &const_value : this->const_value_list) {
      if (field_expr->type() == ExprType::FIELD) {
        if (value.compare(const_value) == 0) {
          result = true;
          return RC::SUCCESS;
        }
      } else {
        LOG_WARN("unsupported expr type. type=%d", static_cast<int>(field_expr->type()));
        return RC::INTERNAL;
      }
    }
    result = false;
    return RC::SUCCESS;
  }
  if (this->type_ == SubResultType::SUB_QUERY) {
    for (auto &tuple : this->tuple_list) {
      if (field_expr->type() == ExprType::FIELD) {
        Value sub_value;
        RC rc = tuple->find_cell(this->result_schema_.cell_at(0), sub_value);
        if (rc != RC::SUCCESS) {
          LOG_WARN("failed to get field value. rc=%s", strrc(rc));
          return rc;
        }
        if (sub_value.compare(value) == 0) {
          result = true;
          return RC::SUCCESS;
        }
      } else {
        LOG_WARN("unsupported expr type. type=%d", static_cast<int>(field_expr->type()));
        return RC::INTERNAL;
      }
    }
    result = false;
    return RC::SUCCESS;
  }
  return RC::INTERNAL;
}

RC SubQueryExpr::try_get_value(Value &value) const { return RC::INTERNAL; }

RC SubQueryExpr::init() {
  if (this->inited_) {
    return RC::SUCCESS;
  }
  if (this->sub_query_event_ == nullptr) {
    return RC::SUCCESS;
  }
  if (this->type_ == SubResultType::UNDEFINED) {
    return RC::INTERNAL;
  }
  SessionStage *stage = dynamic_cast<SessionStage *>(SessionStage::make_stage("SessionStage"));
  RC rc = stage->handle_sub_sql(this->sub_query_event_.get());
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to handle sub sql. rc=%s", strrc(rc));
    return rc;
  }
  // Handle sub query
  assert(this->type_ == SubResultType::SUB_QUERY);
  assert(this->sub_query_event_ != nullptr);
  // Project physical operator
  auto &root_oper = this->sub_query_event_->physical_operator();
  auto select_stmt = dynamic_cast<SelectStmt *>(this->sub_query_event_->stmt());
  this->result_schema_ = create_sub_result_schema(select_stmt);
  if (result_schema_.cell_num() != 1) {
    return RC::INTERNAL;
  }
  rc = root_oper->open(nullptr);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open root operator. rc=%s", strrc(rc));
    return rc;
  }
  Tuple *tuple_ptr = nullptr;
  while (true) {
    rc = root_oper->next();
    if (rc == RC::RECORD_EOF) {
      break;
    }
    if (rc == RC::SUCCESS) {
      tuple_ptr = root_oper->current_tuple();
      auto copy_tuple = tuple_ptr->copy();
      assert(copy_tuple != nullptr);
      this->tuple_list.emplace_back(std::move(copy_tuple));
    } else {
      LOG_WARN("failed to get next tuple. rc=%s", strrc(rc));
      return rc;
    }
  }
  root_oper->close();
  return RC::SUCCESS;
}

RC SubQueryExpr::get_value(const Tuple &tuple, Value &value) const {
  if (!should_return_value) {
    value.set_int(1);
    return RC::SUCCESS;
  }
  // For : select * from ssq_1 where (select ssq_2.id from ssq_2 where col2 = 47) = id;
  // !!! Not for IN and EXIST compare
  if (this->tuple_list.empty()) {
    value.set_int(1919810);
    return RC::SUCCESS;
  }

  if (this->tuple_list.size() != 1) {
    return RC::INTERNAL;
  }

  auto &sub_tuple = this->tuple_list[0];
  RC rc = RC::SUCCESS;
  if (this->result_schema_.cell_at(0).alias() != nullptr) {
    // Aggregate function , value list tuple
    rc = sub_tuple->cell_at(0, value);
  } else {
    rc = sub_tuple->find_cell(this->result_schema_.cell_at(0), value);
  }
  return rc;
}
