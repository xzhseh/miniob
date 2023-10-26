/// Create by Zihao Xu on 10/18/2023

#pragma once

#include <memory>
#include <unordered_map>
#include <vector>
#include "sql/expr/expression.h"
#include "sql/expr/tuple.h"
#include "sql/operator/physical_operator.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"

/// The self-defined hasher for `Value`
namespace std {

template <>
struct hash<Value> {
  std::size_t operator()(const Value &v) const noexcept {
    std::size_t h = 0;

    // hash the attr_type_
    h ^= hash<AttrType>()(v.attr_type());

    // hash the value based on attr_type_
    switch (v.attr_type()) {
      case INTS:
        h ^= hash<int>()(v.get_int());
        break;
      case FLOATS:
        h ^= hash<float>()(v.get_float());
        break;
      case CHARS:
        h ^= hash<std::string>()(v.get_string());
        break;
      case DATE:
        h ^= hash<int>()(v.get_date());
        break;
      // TODO: add more types that need support for aggregation
      default:
        break;
    }

    return h;
  }
};

}  // namespace std

/// Group by keys, should be unique per aggregation
struct AggregateKey {
  std::vector<Value> keys_;

  /// Check if the keys are equal or not
  auto operator==(const AggregateKey &other) const -> bool {
    for (uint32_t i = 0; i < other.keys_.size(); i++) {
      if (keys_[i].compare(other.keys_[i]) != 0) {
        return false;
      }
    }
    return true;
  }
};

/// Actual value(s) begin aggregated
struct AggregateValue {
  std::vector<Value> values_;
  std::vector<agg> value_types_;
  // The absolute counter
  int count{0};
  // The null counter for each aggregate column, for non-aggregate col this is 0 by default
  std::vector<int> null_count;
};

namespace std {

/** Implements std::hash on AggregateKey */
template <>
struct hash<AggregateKey> {
  auto operator()(const AggregateKey &agg_key) const -> std::size_t {
    std::size_t curr_hash = 0;
    std::hash<Value> value_hasher;  // Assuming Value has a defined std::hash

    for (const auto &key : agg_key.keys_) {
      // Combine the current hash with the hash of the key
      curr_hash ^= value_hasher(key) + 0x9e3779b9 + (curr_hash << 6) + (curr_hash >> 2);
    }

    return curr_hash;
  }
};

}  // namespace std

/// Please note that the child of agg should be exactly one
class AggPhysicalOperator : public PhysicalOperator {
 public:
  AggPhysicalOperator() = default;

  explicit AggPhysicalOperator(PhysicalOperator *child, ConditionSqlNode &&having,
                               const std::vector<FieldExpr> &&field_exprs, const std::vector<bool> &&is_agg_,
                               const std::vector<agg> &&agg_types)
      : child_(child),
        having_(std::move(having)),
        field_exprs_(std::move(field_exprs)),
        is_agg_(std::move(is_agg_)),
        agg_types_(std::move(agg_types)) {}

  ~AggPhysicalOperator() override = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::AGG; }

  RC open(Trx *trx) override;

  RC close() override;

  RC next() override;

  Tuple *current_tuple() override;

  std::string name() const override { return "AGG"; }

  std::string param() const override {
    std::vector<string> ret;
    for (const auto &a : agg_types_) {
      switch (a) {
        case AGG_AVG:
          ret.emplace_back("AGG_AVG");
          break;
        case AGG_MIN:
          ret.emplace_back("AGG_MIN");
          break;
        case AGG_MAX:
          ret.emplace_back("AGG_MAX");
          break;
        case AGG_COUNT:
          ret.emplace_back("AGG_COUNT");
          break;
        case AGG_SUM:
          ret.emplace_back("AGG_SUM");
          break;
        default:
          assert(false);
      }
    }
    std::string ret_str{""};
    for (const auto &s : ret) {
      ret_str += (s + " ");
    }
    return ret_str.substr(0, ret_str.size() - 1);
  }

  std::pair<AggregateKey, AggregateValue> aggregate_key_value_builder(Tuple *tuple);

 private:
  Trx *trx_{nullptr};
  PhysicalOperator *child_{nullptr};
  ValueListTuple tuple_;
  ConditionSqlNode having_;
  std::vector<AggregateKey> output_keys_;
  std::vector<FieldExpr> field_exprs_;
  std::vector<bool> is_agg_;
  std::vector<agg> agg_types_;
  std::unordered_map<AggregateKey, AggregateValue> agg_ht_;
  int count_;
};