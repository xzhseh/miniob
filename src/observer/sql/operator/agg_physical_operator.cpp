/// Create by Zihao Xu on 10/18/2023

#include "sql/operator/agg_physical_operator.h"
#include <climits>
#include <memory>
#include <unordered_map>
#include <utility>
#include "common/log/log.h"
#include "sql/expr/tuple.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"

/// FIXME: Refactor this
Value add_value(Value &lhs, Value &rhs) {
  Value ret;

  if (Value::check_null(lhs) && Value::check_null(rhs)) {
    assert(lhs.attr_type() == rhs.attr_type());
    Value::set_null(ret, lhs.attr_type());
    return ret;
  }

  if (lhs.attr_type() == AttrType::INTS) {
    switch (rhs.attr_type()) {
      case AttrType::INTS: {
        if (Value::check_null(lhs)) {
          ret.set_int(rhs.get_int());
        } else if (Value::check_null(rhs)) {
          ret.set_int(lhs.get_int());
        } else {
          ret.set_int(lhs.get_int() + rhs.get_int());
        }
      } break;
      case AttrType::FLOATS: {
        // INT + FLOAT is impossible even for AVG / SUM
        assert(false);
      } break;
      default:
        assert(false);  // Unsupported
    }
  } else if (lhs.attr_type() == AttrType::FLOATS) {
    switch (rhs.attr_type()) {
      case AttrType::FLOATS: {
        if (Value::check_null(lhs)) {
          ret.set_float(rhs.get_float());
        } else if (Value::check_null(rhs)) {
          ret.set_float(lhs.get_float());
        } else {
          ret.set_float(lhs.get_float() + rhs.get_float());
        }
      } break;
      default:
        assert(false);  // Unsupported
    }
  } else {
    // Not yet supported
    LOG_WARN("%s of type %d is not supported.", lhs.to_string().c_str(), lhs.attr_type());
    assert(false);
  }
  return ret;
}

void initialize_agg_value(std::vector<Value> &values, std::vector<agg> &value_types) {
  for (int i = 0; i < values.size(); ++i) {
    Value &v = values[i];
    switch (value_types[i]) {
      case AGG_COUNT: {
        if (v.attr_type() == UNDEFINED) {
          // COUNT(*)
          v.set_int(1);
        } else {
          if (!Value::check_null(v)) {
            v.set_int(1);
          } else {
            // We do NOT count null value for a specific column
            v.set_int(0);
          }
        }
      } break;
      case AGG_MIN:
      case AGG_MAX:
      case AGG_SUM:
      case AGG_AVG: {
        // Do nothing
      } break;
      default:
        assert(false);
    }
  }
}

std::pair<AggregateKey, AggregateValue> AggPhysicalOperator::aggregate_key_value_builder(Tuple *tuple) {
  assert(tuple != nullptr && "`tuple` must not be nullptr");

  AggregateKey a_k{std::vector<Value>()};
  std::vector<Value> values;
  std::vector<agg> value_types;
  std::vector<int> null_count;

  for (int i = 0; i < field_exprs_.size(); ++i) {
    if (field_exprs_[i].field().meta() == nullptr && field_exprs_[i].field().table() == nullptr) {
      // COUNT(*), push a UNDEFINED value into the result
      assert(agg_types_[i] == agg::AGG_COUNT);
      values.push_back({});
      value_types.push_back(agg::AGG_COUNT);
      null_count.push_back(1);
      continue;
    }

    // Get the value from the current field expression
    Value v;
    field_exprs_[i].get_value(*tuple, v);

    if (is_agg_[i]) {
      // Normal aggregation
      values.push_back(v);
      value_types.push_back(agg_types_[i]);
      null_count.push_back((Value::check_null(v)) ? 0 : 1);
    } else {
      // Add to the aggregate keys
      a_k.keys_.push_back(v);
      null_count.push_back(0);
    }
  }

  initialize_agg_value(values, value_types);

  return {a_k, {values, value_types, 1, null_count}};
}

void bind_agg_values(std::vector<Value> &lhs, std::vector<Value> &rhs, const std::vector<agg> &value_types) {
  for (int i = 0; i < lhs.size(); ++i) {
    switch (value_types[i]) {
      case AGG_COUNT:
      case AGG_SUM:
      case AGG_AVG: {
        lhs[i] = add_value(lhs[i], rhs[i]);
      } break;
      case AGG_MIN: {
        if (rhs[i].compare(lhs[i]) < 0) {
          lhs[i] = rhs[i];
        }
      } break;
      case AGG_MAX: {
        if (lhs[i].compare(rhs[i]) < 0) {
          lhs[i] = rhs[i];
        }
      } break;
      default:
        assert(false);
    }
  }
}

/// lhs is the original value, rhs is the value being inserted and combined
void insert_and_combine_agg_value(AggregateValue &lhs, AggregateValue &rhs) {
  // Sanity check, comment this out when actual testing
  for (int i = 0; i < lhs.value_types_.size(); ++i) {
    assert(lhs.value_types_[i] == rhs.value_types_[i]);
  }

  bind_agg_values(lhs.values_, rhs.values_, lhs.value_types_);

  lhs.count += rhs.count;

  for (int i = 0; i < lhs.null_count.size(); ++i) {
    lhs.null_count[i] += rhs.null_count[i];
  }
}

RC AggPhysicalOperator::open(Trx *trx) {
  assert(child_ != nullptr && "`child_ must not be nullptr");
  RC rc = child_->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("[AggPhysicalOperator] failed to open child operator");
    return rc;
  }

  // Begin the initialization
  while ((rc = child_->next()) == RC::SUCCESS) {
    Tuple *tuple = child_->current_tuple();

    // First construct the current `AggregateKey` & `AggregateValue`
    auto [a_k, a_v] = aggregate_key_value_builder(tuple);

    // Update `output_keys_`
    // We currently have to traverse the `output_keys` to perform the update
    // This is inefficient but I could not come up with a better solution at present
    // May be refactor in the future
    bool exist_flag{false};
    for (const auto &o_k : output_keys_) {
      if (o_k == a_k) {
        exist_flag = true;
        break;
      }
    }

    if (!exist_flag) {
      output_keys_.push_back(a_k);
    }

    // See if the current key has existed
    if (agg_ht_.contains(a_k)) {
      insert_and_combine_agg_value(agg_ht_[a_k], a_v);
    } else {
      agg_ht_[a_k] = a_v;
    }
  }

  if (rc != RC::RECORD_EOF) {
    LOG_WARN("[AggPhysicalOperator::open] failed to read to the end of the child operator.");
    return rc;
  }

  count_ = output_keys_.size();

  // Note we directly return RC::SUCCESS here, since this is just preprocessing
  return RC::SUCCESS;
}

RC AggPhysicalOperator::close() {
  RC rc = RC::SUCCESS;
  if (child_ != nullptr) {
    rc = child_->close();
  }
  return rc;
}

/// Currently we just consider the case with one attribute & one value on each side
bool check_having(Value &v, agg a, const ConditionSqlNode &having, const Field &field, bool force = false) {
  if (having.left_value.attr_type() == AttrType::UNDEFINED && having.right_value.attr_type() == AttrType::UNDEFINED) {
    // No having clause for this group by
    return true;
  }

  if (having.left_is_attr) {
    // having sum(id) comp value
    if (force ||
        (having.left_attr.aggregate_func == a &&
         strcmp((having.left_attr.relation_name.empty()) ? field.table_name() : having.left_attr.relation_name.c_str(),
                field.table_name()) == 0 &&
         strcmp(having.left_attr.attribute_name.c_str(), field.field_name()) == 0)) {
      switch (having.comp) {
        // Note this should be in normal order
        case CompOp::EQUAL_TO:
          return v.compare(having.right_value) == 0;
        case CompOp::GREAT_EQUAL:
          return v.compare(having.right_value) >= 0;
        case CompOp::LESS_EQUAL:
          return v.compare(having.right_value) <= 0;
        case CompOp::GREAT_THAN:
          return v.compare(having.right_value) > 0;
        case CompOp::LESS_THAN:
          return v.compare(having.right_value) < 0;
        default:
          assert(false);  // Not yet support
      }
    } else {
      return true;
    }
  } else if (having.right_is_attr) {
    // having value comp sum(id)
    if (force || (having.right_attr.aggregate_func == a &&
                  strcmp((having.right_attr.relation_name.empty()) ? field.table_name()
                                                                   : having.right_attr.relation_name.c_str(),
                         field.table_name()) == 0 &&
                  strcmp(having.right_attr.attribute_name.c_str(), field.field_name()) == 0)) {
      switch (having.comp) {
        // Note this should be in reverse order
        case CompOp::EQUAL_TO:
          return v.compare(having.left_value) == 0;
        case CompOp::GREAT_EQUAL:
          return v.compare(having.left_value) <= 0;
        case CompOp::LESS_EQUAL:
          return v.compare(having.left_value) >= 0;
        case CompOp::GREAT_THAN:
          return v.compare(having.left_value) < 0;
        case CompOp::LESS_THAN:
          return v.compare(having.left_value) > 0;
        default:
          assert(false);  // Not yet support
      }
    } else {
      return true;
    }
  } else {
    assert(false);
  }
  assert(false);
}

RC AggPhysicalOperator::next() {
  if (output_keys_.empty()) {
    return RC::RECORD_EOF;
  }

  AggregateKey a_k;
  std::vector<Value> cur_key;
  AggregateValue a_v;
  std::vector<Value> cur_value;

  // Perform the having filter
  while (true) {
    // We filter out all the rest of the tuples
    if (output_keys_.empty()) {
      return RC::RECORD_EOF;
    }

    a_k = output_keys_.front();
    cur_key = a_k.keys_;
    a_v = agg_ht_[a_k];
    cur_value = a_v.values_;
    output_keys_.erase(output_keys_.begin());

    if ((having_.left_is_attr && having_.left_attr.attribute_name == "*" &&
         having_.left_attr.aggregate_func == agg::AGG_COUNT) ||
        (having_.right_is_attr && having_.right_attr.attribute_name == "*" &&
         having_.right_attr.aggregate_func == agg::AGG_COUNT)) {
      Value v;
      // std::cout << "current count: " << a_v.count << std::endl;
      v.set_int(a_v.count);
      if (!check_having(v, agg::AGG_COUNT, having_, field_exprs_.front().field(), true)) {
        continue;
      } else {
        break;
      }
    }

    bool check_flag{true};
    auto tmp_value = cur_value;

    for (int i = 0; i < is_agg_.size(); ++i) {
      if (is_agg_[i]) {
        // Only need to check aggregation
        check_flag = check_flag && check_having(tmp_value.front(), agg_types_[i], having_, field_exprs_[i].field());
        tmp_value.erase(tmp_value.begin());
      }
    }

    if (check_flag) {
      break;
    }
  }

  std::vector<Value> output;

  // Basic sanity check
  assert(cur_value.size() + cur_key.size() == is_agg_.size());

  // Construct the output tuple
  for (int i = 0; i < is_agg_.size(); ++i) {
    if (is_agg_[i]) {
      Value front_value = cur_value.front();

      // Finalize the `agg::AGG_AVG`
      if (agg_types_[i] == AGG_AVG) {
        if (front_value.attr_type() == AttrType::INTS) {
          if (!Value::check_null(front_value)) {
            front_value.set_float(front_value.get_int() * 1.0 / a_v.null_count[i]);
          }
        } else if (front_value.attr_type() == AttrType::FLOATS) {
          if (!Value::check_null(front_value)) {
            front_value.set_float(front_value.get_float() / a_v.null_count[i]);
          }
        } else {
          assert(false);
        }
      }

      output.push_back(front_value);
      cur_value.erase(cur_value.begin());
    } else {
      output.push_back(cur_key.front());
      cur_key.erase(cur_key.begin());
    }
  }

  tuple_.set_cells(output);

  return RC::SUCCESS;
}

Tuple *AggPhysicalOperator::current_tuple() { return &tuple_; }