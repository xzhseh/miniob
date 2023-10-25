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
  explicit AggStmt() = default;

  ~AggStmt() = default;

  auto get_fields() const -> const std::vector<Field> & { return fields_; }

  auto get_is_agg() const -> const std::vector<bool> & { return is_agg_; }

  auto get_agg_types() const -> const std::vector<agg> & { return agg_types_; }

  void set_fields(std::vector<Field> &&fields) { fields_ = std::move(fields); }

  void set_is_agg(std::vector<bool> &&is_agg) { is_agg_ = std::move(is_agg); }

  void set_agg_types(std::vector<agg> &&agg_types) { agg_types_ = std::move(agg_types); }

 private:
  std::vector<Field> fields_;
  std::vector<bool> is_agg_;
  std::vector<agg> agg_types_;
};