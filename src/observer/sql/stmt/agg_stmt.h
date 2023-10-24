/// Create by Zihao Xu on 10/18/2023

#pragma once

#include <vector>

#include "common/rc.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/stmt.h"
#include "storage/field/field.h"
#include "storage/field/field_meta.h"

class AggStmt {
 public:
  AggStmt() = delete;

  explicit AggStmt(std::vector<std::pair<const FieldMeta *, int>> aggregate_keys, std::vector<agg> aggregate_types);

  /// Note that we do not need to free the `FieldMeta *`, since we only hold the reference
  ~AggStmt() = default;

  auto get_keys() -> const std::vector<std::pair<const FieldMeta *, int>> & { return aggregate_keys_; }

  auto get_types() -> const std::vector<agg> & { return aggregate_types_; }

  auto get_group_by_keys() -> const std::vector<Field> & { return group_by_keys_; }

  void set_group_by_keys(std::vector<Field> &&group_by_keys) { group_by_keys_ = std::move(group_by_keys); }

 private:
  // FIXME: Any other way / more efficiently to store the aggregation key / type?

  // Currently storing format:
  //   1. The begin key `field_` (used to compare later)
  //   2. How many keys are there for this aggregation (including the begin key)
  std::vector<std::pair<const FieldMeta *, int>> aggregate_keys_;

  // `aggregate_types_.size()` === `aggregate_keys_.size()`
  std::vector<agg> aggregate_types_;

  // The unique keys to perform group by
  std::vector<Field> group_by_keys_;
};