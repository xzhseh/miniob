//
// Created by susun on 23-10-23.
//

#include "sub_query_expr.h"
#include "session/session_stage.h"

SubQueryExpr::SubQueryExpr(std::vector<Value> const_value_list) {
  this->sub_result_.type = SubResultType::CONST_VALUE_LIST;
  this->sub_result_.const_value_list = const_value_list;
}
SubQueryExpr::SubQueryExpr(std::unique_ptr<ParsedSqlNode> sub_query) {
  this->sub_result_.type = SubResultType::SUB_QUERY;
  this->sub_query_event_ = std::make_unique<SQLStageEvent>(std::move(sub_query));
  auto stage = SessionStage::make_stage("SessionStage");
  stage->handle_event(this->sub_query_event_.get());
}
RC SubQueryExpr::get_value(const Tuple &tuple, Value &value) const {
  if (this->sub_result_.type == SubResultType::CONST_VALUE_LIST) {
    value.set_sub_query_result(this->sub_result_);
    return RC::SUCCESS;
  }
  if (this->sub_result_.type == SubResultType::UNDEFINED) {
    return RC::INTERNAL;
  }
  // Handle sub query
  assert(this->sub_result_.type == SubResultType::SUB_QUERY);
  assert(this->sub_query_event_ != nullptr);
  // Project physical operator
  auto &root_oper = this->sub_query_event_->physical_operator();
  std::vector<std::unique_ptr<Tuple>> result_value_list;
  RC rc = root_oper->open(nullptr);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open root operator. rc=%s", strrc(rc));
    return rc;
  }
  Tuple *tuple_ptr = nullptr;
  while (true) {
    rc = root_oper->next();
    tuple_ptr = root_oper->current_tuple();
    if (rc == RC::SUCCESS) {
      result_value_list.push_back(tuple_ptr->copy());
    } else if (rc == RC::RECORD_EOF) {
      break;
    } else {
      LOG_WARN("failed to get next tuple. rc=%s", strrc(rc));
      return rc;
    }
  }
  return RC::SUCCESS;
}