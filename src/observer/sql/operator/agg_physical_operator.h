/// Create by Zihao Xu on 10/18/2023

#pragma once

#include "sql/expr/expression.h"
#include "sql/expr/tuple.h"
#include "sql/operator/physical_operator.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"
#include <unordered_map>

/// Please note that the child of agg should be exactly one
class AggPhysicalOperator : public PhysicalOperator
{
public:
  AggPhysicalOperator() = default;

  explicit AggPhysicalOperator(std::vector<std::pair<const FieldMeta *, int>> &aggregate_keys,
      std::vector<agg> &aggregate_types, std::vector<FieldExpr> &exprs)
      : aggregate_keys_(std::move(aggregate_keys)),
        aggregate_types_(std::move(aggregate_types)),
        exprs_(std::move(exprs))
  {}

  virtual ~AggPhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::AGG; }

  RC open(Trx *trx) override;

  RC close() override;

  RC next() override;

  Tuple *current_tuple() override;

  std::string name() const override { return "AGG"; }

  std::string param() const override
  {
    std::vector<string> ret;
    for (const auto &a : aggregate_types_) {
      switch (a) {
        case AGG_AVG: ret.emplace_back("AGG_AVG"); break;
        case AGG_MIN: ret.emplace_back("AGG_MIN"); break;
        case AGG_MAX: ret.emplace_back("AGG_MAX"); break;
        case AGG_COUNT: ret.emplace_back("AGG_COUNT"); break;
        case AGG_SUM: ret.emplace_back("AGG_SUM"); break;
        default: assert(false);
      }
    }
    std::string ret_str{""};
    for (const auto &s : ret) {
      ret_str += (s + " ");
    }
    return ret_str.substr(0, ret_str.size() - 1);
  }

private:
  Trx              *trx_{nullptr};
  PhysicalOperator *child_{nullptr};
  // FIXME: Refactor this when implementing group by
  ValueListTuple tuple_;
  // FIXME: This needs fix (duplicate aggregate functions)
  std::unordered_map<agg, Value> agg_value_map_;
  // Including the expressions of all fields
  std::vector<FieldExpr>                         exprs_;
  std::vector<std::pair<const FieldMeta *, int>> aggregate_keys_;
  // The number of tuples
  int              avg_n{0};
  bool             next_flag{false};
  std::vector<agg> aggregate_types_;
};