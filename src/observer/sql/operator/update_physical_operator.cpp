#include "common/log/log.h"
#include "sql/operator/update_physical_operator.h"
#include "storage/record/record.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"
#include "sql/stmt/delete_stmt.h"

RC UpdatePhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }
  std::unique_ptr<PhysicalOperator> &child = children_[0];
  RC                                 rc    = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }
  trx_ = trx;

  return RC::SUCCESS;
}

RC UpdatePhysicalOperator::next()
{
  RC rc = RC::SUCCESS;
  if (children_.empty()) {
    return RC::RECORD_EOF;
  }

  PhysicalOperator *child      = children_[0].get();
  const TableMeta  &table_meta = table_->table_meta();
  while (RC::SUCCESS == (rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }

    auto  *row_tuple   = dynamic_cast<RowTuple *>(tuple);
    Record old_record  = row_tuple->record();
    int    record_size = table_meta.record_size();
    char  *data        = new char[record_size];
    memcpy(data, old_record.data(), record_size);

    for (size_t i = 0; i < values_.size(); ++i) {
      const Value     &value      = values_[i];
      const FieldMeta &field_meta = field_metas_[i];
      int              offset     = field_meta.offset();
      if (value.length() > field_meta.len()) {
        LOG_WARN("value length is too long: %d, %d", value.length(), field_meta.len());
        return RC::INVALID_ARGUMENT;
      }
      for (int j = 0; j < value.length(); ++j) {
        data[offset + j] = value.data()[j];
      }
      if (value.attr_type() == AttrType::CHARS && value.length() < field_meta.len()) {
        data[offset + value.length()] = '\0';
      }
    }
    Record new_record;
    new_record.set_rid(old_record.rid());
    new_record.set_data(data, record_size);

    rc = table_->update_record(old_record, new_record);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to update:delete record: %s", strrc(rc));
      return rc;
    }
  }

  return RC::RECORD_EOF;
}

RC UpdatePhysicalOperator::close()
{
  if (!children_.empty()) {
    children_[0]->close();
  }
  return RC::SUCCESS;
}
