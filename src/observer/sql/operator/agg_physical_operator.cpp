/// Create by Zihao Xu on 10/18/2023

#include "sql/operator/agg_physical_operator.h"
#include <climits>
#include <unordered_map>
#include "sql/expr/tuple.h"
#include "sql/parser/value.h"

RC AggPhysicalOperator::open(Trx *trx) {
  RC rc = RC::SUCCESS;
  assert(children_.size() == 1 && "aggregate operator should have exactly one child");
  child_ = children_[0].get();
  rc = child_->open(trx);
  return rc;
}

RC AggPhysicalOperator::close() {
  RC rc = RC::SUCCESS;
  assert(next_flag && "`next_flag` should be true");
  if (child_ != nullptr) {
    rc = child_->close();
  }
  return rc;
}

/// FIXME: Refactor this
Value add_value(Value &lhs, Value &rhs) {
  Value ret;
  if (lhs.attr_type() == AttrType::INTS) {
    switch (rhs.attr_type()) {
      case AttrType::INTS: {
        ret.set_int(lhs.get_int() + rhs.get_int());
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
        ret.set_float(lhs.get_float() + rhs.get_float());
      } break;
      default:
        assert(false);  // Unsupported
    }
  } else {
    // Not yet supported
    assert(false);
  }
  return ret;
}

void set_initial_value_for_map(std::unordered_map<agg, Value> &m, AttrType t, agg a_t, Value v) {
  if (m.count(a_t) == 0) {
    Value ret;
    if (a_t == agg::AGG_COUNT) {
      ret.set_int(0);
    } else {
      switch (t) {
        case AttrType::INTS:
          if (a_t == agg::AGG_MIN || a_t == agg::AGG_MAX) {
            ret = v;
          } else {
            // SUM / AVG
            ret.set_int(0);
          }
          break;
        case AttrType::FLOATS:
          if (a_t == agg::AGG_MIN || a_t == agg::AGG_MAX) {
            ret = v;
          } else {
            // SUM / AVG
            ret.set_float(0);
          }
          break;
        case AttrType::CHARS:
          if (a_t == agg::AGG_MIN || a_t == agg::AGG_MAX) {
            ret = v;
          } else {
            assert(false);  // Not yet supported
          }
          break;
        case AttrType::TEXT:
          if (a_t == agg::AGG_MIN || a_t == agg::AGG_MAX) {
            ret = v;
          } else {
            assert(false);  // Not yet supported
          }
          break;
        case AttrType::DATE:
          if (a_t == agg::AGG_MIN || a_t == agg::AGG_MAX) {
            ret = v;
          } else {
            // SUM / AVG
            assert(false);
          }
          break;
        default:
          assert(false);  // Not yet supported
      }
    }
    m[a_t] = ret;
  }
}

/// Basically we will extract all possible tuples from the child operator
/// And make the basic aggregation at present
RC AggPhysicalOperator::next() {
  bool g_null_flag{false};
  if (next_flag) {
    return RC::RECORD_EOF;
  }
  RC rc = RC::SUCCESS;
  while ((rc = child_->next()) == RC::SUCCESS) {
    bool null_flag{false};
    Tuple *tuple = child_->current_tuple();
    // for (const auto &field_expr : exprs_) {
    for (int i = 0; i < aggregate_keys_.size(); ++i) {
      if (null_flag) {
        break;
      }
      for (const auto &field_expr : exprs_) {
        auto &[field_meta, n] = aggregate_keys_[i];
        if (field_expr.field().meta() == field_meta) {
          assert(n >= 1);
          if (n > 1) {
            if (aggregate_types_[i] != agg::AGG_COUNT) {
              rc = RC::INVALID_ARGUMENT;
              return rc;
            }
            // COUNT(*)
            if (agg_value_map_.count(agg::AGG_COUNT) == 0) {
              Value t;
              t.set_int(0);
              agg_value_map_[agg::AGG_COUNT] = t;
            }
            Value v = agg_value_map_[agg::AGG_COUNT];
            agg_value_map_[agg::AGG_COUNT].set_int(v.get_int() + 1);
          } else {
            // Other aggregate function, without `*`
            assert(n == 1);
            Value v;
            field_expr.get_value(*tuple, v);
            set_initial_value_for_map(agg_value_map_, v.attr_type(), aggregate_types_[i], v);
            // FIXME: Ensure the sequence of this and the `set_initial_value_for_map`
            if (Value::check_null(v)) {
              null_flag = true;
              g_null_flag = true;
              break;
            }
            switch (aggregate_types_[i]) {
              case agg::AGG_COUNT: {
                if (agg_value_map_.count(agg::AGG_COUNT) == 0) {
                  Value t;
                  t.set_int(0);
                  agg_value_map_[agg::AGG_COUNT] = t;
                }
                v = agg_value_map_[agg::AGG_COUNT];
                agg_value_map_[agg::AGG_COUNT].set_int(v.get_int() + 1);
              } break;
              case agg::AGG_MIN: {
                auto v_t = agg_value_map_[agg::AGG_MIN];
                // FIXME: Ensure this
                // std::cout << "[agg::min] Current v: " << v.to_string() << std::endl;
                // std::cout << "[agg::min] Current v_t: " << v_t.to_string() << std::endl;
                if (v.compare(v_t) < 0) {
                  agg_value_map_[agg::AGG_MIN] = v;
                }
              } break;
              case agg::AGG_MAX: {
                auto v_t = agg_value_map_[agg::AGG_MAX];
                // FIXME: Ensure this
                // std::cout << "[agg::max] Current v: " << v.to_string() << std::endl;
                // std::cout << "[agg::max] Current v_t: " << v_t.to_string() << std::endl;
                if (v.compare(v_t) > 0) {
                  agg_value_map_[agg::AGG_MAX] = v;
                }
              } break;
              case agg::AGG_SUM: {
                auto v_t = agg_value_map_[agg::AGG_SUM];
                auto res = add_value(v, v_t);
                agg_value_map_[agg::AGG_SUM] = res;
              } break;
              case agg::AGG_AVG: {
                // TODO: Refactor this
                auto v_t = agg_value_map_[agg::AGG_AVG];
                // std::cout << "[agg::avg] Current v: " << v.to_string() << std::endl;
                // std::cout << "[agg::avg] Current v_t: " << v_t.to_string() << std::endl;
                auto res = add_value(v, v_t);
                agg_value_map_[agg::AGG_AVG] = res;
              } break;
              default:
                assert(false);  // This is impossible
            }
          }
          // TODO: Please note this
          break;
        }
      }
    }
    if (!null_flag) {
      avg_n += 1;
    }
  }

  std::cout << "Current avg_n: " << avg_n << std::endl;

  // For agg::AGG_AVG
  if (agg_value_map_.count(agg::AGG_AVG) == 1) {
    auto &v_t = agg_value_map_[agg::AGG_AVG];
    if (v_t.attr_type() == AttrType::INTS) {
      if (g_null_flag && v_t.get_int() == 0) {
        v_t.set_float(114.514);
      } else {
        v_t.set_float(v_t.get_int() * 1.0 / avg_n);
      }
    } else if (v_t.attr_type() == AttrType::FLOATS) {
      if (g_null_flag && v_t.get_float() == 0) {
        v_t.set_float(114.514);
      } else {
        v_t.set_float(v_t.get_float() / avg_n);
      }
    } else {
      assert(false);  // Not yet support
    }
  }

  // For agg::AGG_SUM
  if (agg_value_map_.count(agg::AGG_SUM) == 1) {
    auto &v_t = agg_value_map_[agg::AGG_SUM];
    if (v_t.attr_type() == AttrType::INTS) {
      if (g_null_flag && v_t.get_int() == 0) {
        v_t.set_int(1919810);
      }
    } else if (v_t.attr_type() == AttrType::FLOATS) {
      if (g_null_flag && v_t.get_float() == 0) {
        v_t.set_float(114.514);
      }
    } else {
      assert(false);  // Not yet support
    }
  }

  std::vector<Value> ret;
  for (int i = 0; i < aggregate_types_.size(); ++i) {
    ret.push_back(agg_value_map_[aggregate_types_[i]]);
  }
  tuple_.set_cells(ret);
  // std::cout << "[agg] Current tuple: " << tuple_.to_string() << std::endl;
  if (rc == RC::RECORD_EOF) {
    rc = RC::SUCCESS;
  }
  next_flag = true;
  return rc;
}

Tuple *AggPhysicalOperator::current_tuple() { return &tuple_; }