//
// Created by susun on 23-10-23.
//

#include "sub_query_expr.h"
#include "session/session_stage.h"

SubQueryExpr::SubQueryExpr(const std::vector<Value> &const_value_list) {
  this->type_ = SubResultType::CONST_VALUE_LIST;
  this->const_value_list = const_value_list;
}

SubQueryExpr::SubQueryExpr(const std::shared_ptr<ParsedSqlNode> &sub_query,
                           std::unordered_map<std::string, Table *> table_map) {
  this->type_ = SubResultType::SUB_QUERY;
  this->sub_query_node = sub_query;
  this->table_map_ = std::move(table_map);
}
// 受不了了，直接简单粗暴一点
std::vector<std::unique_ptr<Tuple>> parent_tuples;

RC SubQueryExpr::in_or_not(const Value &value, const std::unique_ptr<Expression> &field_expr, bool &result) const {
  std::cout << "Compare value is " << value.to_string() << std::endl;
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

/// @brief Try to get value from sub query
RC SubQueryExpr::get_const_value(Value &value) {
  this->tuple_list.clear();
  if (this->type_ != SubResultType::SUB_QUERY) {
    value.set_int(123);
    return RC::SUCCESS;
  }
  assert(this->type_ == SubResultType::SUB_QUERY);
  SessionStage *stage = dynamic_cast<SessionStage *>(SessionStage::make_stage("SessionStage"));
  auto copy_node = this->sub_query_node.get()->selection;
  std::shared_ptr<ParsedSqlNode> sub_query = std::make_shared<ParsedSqlNode>();
  sub_query->selection = copy_node;
  sub_query->flag = SCF_SELECT;
  this->sub_query_event_ = std::make_unique<SQLStageEvent>(sub_query);
  RC rc = stage->handle_sub_sql(this->sub_query_event_.get());
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to handle sub sql. rc=%s", strrc(rc));
    return rc;
  }
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

  if (!should_return_value) {
    value.set_int(1);
    return RC::SUCCESS;
  }

  if (this->tuple_list.empty()) {
    value.set_int(1919810);
    return RC::SUCCESS;
  }

  if (this->tuple_list.size() != 1) {
    return RC::INTERNAL;
  }

  auto &sub_tuple = this->tuple_list[0];
  if (this->result_schema_.cell_at(0).field_name_length() == 0) {
    // Aggregate function , value list tuple
    rc = sub_tuple->cell_at(0, value);
  } else {
    rc = sub_tuple->find_cell(this->result_schema_.cell_at(0), value);
  }
  this->tuple_list.clear();
  return rc;
}

RC replace_field(std::shared_ptr<ParsedSqlNode> &sub_query, const std::unordered_map<std::string, Table *> &table_map) {
  //  Now we get a sub query parsed sql node, we need to replace the parent field
  for (auto &condition : sub_query->selection.conditions) {
    // select * from t1 where t1.nothing <> (select min(t2.id) from t2 where t2.id > t1.id)
    const auto &left_attr = condition.left_attr;
    const auto &right_attr = condition.right_attr;

    if (condition.left_is_attr == 1) {
      // left is attr
      auto iter = table_map.find(left_attr.relation_name);
      if (iter != table_map.end()) {
        // Replace with value
        auto table = iter->second;
        // Construct a field expression
        const FieldMeta *field = table->table_meta().field(left_attr.attribute_name.c_str());
        Value value;
        auto field_expr = std::make_unique<FieldExpr>(Field(table, field));
        bool is_replaced = false;
        for (const auto &parent_tuple : parent_tuples) {
          RC rc = field_expr->get_value(*parent_tuple, value);
          if (rc == RC::SUCCESS) {
            is_replaced = true;
            break;
          }
        }
        if (!is_replaced) {
          return RC::INTERNAL;
        }
        condition.left_is_attr = 0;
        condition.left_value = value;
      }
    }

    if (condition.right_is_attr == 1) {
      // right is attr
      auto iter = table_map.find(right_attr.relation_name);
      if (iter != table_map.end()) {
        // Replace with value
        auto table = iter->second;
        // Construct a field expression
        const FieldMeta *field = table->table_meta().field(right_attr.attribute_name.c_str());
        Value value;
        auto field_expr = std::make_unique<FieldExpr>(Field(table, field));
        bool is_replaced = false;
        for (const auto &parent_tuple : parent_tuples) {
          RC rc = field_expr->get_value(*parent_tuple, value);
          if (rc == RC::SUCCESS) {
            is_replaced = true;
            break;
          }
        }
        if (!is_replaced) {
          return RC::INTERNAL;
        }
        condition.right_is_attr = 0;
        condition.right_value = value;
      }
    }
  }
  return RC::SUCCESS;
}

RC SubQueryExpr::get_value(const Tuple &tuple, Value &value) {
  this->tuple_list.clear();
  if (this->type_ != SubResultType::SUB_QUERY) {
    value.set_int(123);
    return RC::SUCCESS;
  }
  parent_tuples.emplace_back(tuple.copy());
  assert(this->type_ == SubResultType::SUB_QUERY);
  SessionStage *stage = dynamic_cast<SessionStage *>(SessionStage::make_stage("SessionStage"));
  auto copy_node = this->sub_query_node.get()->selection;
  std::shared_ptr<ParsedSqlNode> sub_query = std::make_shared<ParsedSqlNode>();
  sub_query->selection = copy_node;
  sub_query->flag = SCF_SELECT;
  RC rc = replace_field(sub_query, table_map_);
  this->sub_query_event_ = std::make_unique<SQLStageEvent>(sub_query);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to replace field. rc=%s", strrc(rc));
    return rc;
  }
  rc = stage->handle_sub_sql(this->sub_query_event_.get());
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to handle sub sql. rc=%s", strrc(rc));
    return rc;
  }
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

  parent_tuples.pop_back();

  if (!should_return_value) {
    value.set_int(1);
    return RC::SUCCESS;
  }

  if (this->tuple_list.empty()) {
    value.set_int(1919810);
    return RC::SUCCESS;
  }

  if (this->tuple_list.size() != 1) {
    return RC::INTERNAL;
  }

  auto &sub_tuple = this->tuple_list[0];
  if (this->result_schema_.cell_at(0).field_name_length() == 0) {
    // Aggregate function , value list tuple
    rc = sub_tuple->cell_at(0, value);
  } else {
    rc = sub_tuple->find_cell(this->result_schema_.cell_at(0), value);
  }
  this->tuple_list.clear();
  return rc;
}
