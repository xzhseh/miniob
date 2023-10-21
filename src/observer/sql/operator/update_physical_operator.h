#pragma once

#include <utility>

#include "sql/operator/physical_operator.h"

class Trx;
class UpdateStmt;

/**
 * @brief 物理算子，更新
 * @ingroup PhysicalOperator
 */
class UpdatePhysicalOperator : public PhysicalOperator {
 public:
  UpdatePhysicalOperator(Table *table, std::vector<Value> values, std::vector<FieldMeta> field_meta)
      : table_(table), values_(std::move(values)), field_metas_(std::move(field_meta)) {}

  virtual ~UpdatePhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::UPDATE; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override { return nullptr; }

 private:
  Table *table_ = nullptr;
  std::vector<Value> values_;
  std::vector<FieldMeta> field_metas_;
  Trx *trx_ = nullptr;
};