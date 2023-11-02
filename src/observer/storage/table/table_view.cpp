#include "table_view.h"
#include "common/log/log.h"
#include "event/session_event.h"
#include "sql/expr/tuple.h"
#include "sql/operator/project_physical_operator.h"
#include "sql/parser/value.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"
#include "storage/db/db.h"
#include "common/global_context.h"
Db* current_db;
std::unordered_map<std::string, std::unique_ptr<PhysicalOperator> > view_rebuild_map;
static RC get_fields_name_from_expr(Db *db, Expression *expr, std::vector<std::string> &expr_names_vec) {
  RC rc = RC::SUCCESS;
  if (expr == nullptr) {
    return RC::INVALID_ARGUMENT;
  }
  if (expr->type() == ExprType::FIELD) {
    FieldExpr *f_expr = dynamic_cast<FieldExpr *>(expr);
    assert(f_expr != nullptr && "Expect `f_expr` not to be nullptr");
    expr_names_vec.push_back(f_expr->field().field_name());
  }
  // Recursively transformation the child expression, if exists any
  if (expr->left() != nullptr) {
    rc = get_fields_name_from_expr(db, expr->left(), expr_names_vec);
  }
  if (expr->right() != nullptr) {
    rc = get_fields_name_from_expr(db, expr->right(), expr_names_vec);
  }
  return rc;
}

static std::vector<std::string> split_string(const std::string &s) {
  std::istringstream iss(s);
  std::vector<std::string> tokens;
  std::string token;
  while (iss >> token) {
    tokens.push_back(token);
  }
  return tokens;
}
RC next_tuple(Tuple*& tuple, ProjectPhysicalOperator* oper) {
    RC rc = oper->next();
    if(rc != RC::SUCCESS) {
        return rc;
    }
    tuple = oper->current_tuple();
    return rc;
}

void view_rebuild_function(std::string view_name) {
    // FIXME: reopen may be bug
    RC rc;
    Trx* trx = GCTX.trx_kit_->create_trx(current_db->clog_manager());
    trx->start_if_need();
    std::unique_ptr<PhysicalOperator>& ptr = view_rebuild_map[view_name];
    ProjectPhysicalOperator *oper = dynamic_cast<ProjectPhysicalOperator *>(ptr.get());
    if (oper != nullptr && oper->name() != "") {
    current_db->drop_table(oper->name().c_str());
    oper->close();
    oper->open(trx);
    if (oper->select_expr_flag_) {
      std::vector<AttrInfoSqlNode> expr_table_attrs;
      // The select statement contains expression
      assert(oper->select_expr_.size() > 0);
      assert(oper->tables_.size() > 0);
      vector<Table*> tables;
      vector<const FieldMeta*> fields;

      for (auto *expr : oper->select_expr_) {
        // Each expression will correspond to a specific tuple cell
        std::cout << "[PlainCommunicator::write_result_internal] current expr: " << expr->name() << std::endl;
        std::vector<std::string> expr_vec;
        rc = get_fields_name_from_expr(current_db, expr, expr_vec);
        std::vector<std::string> expr_alias_vec = split_string(expr->name());
        AttrInfoSqlNode expr_attr;

        if (expr_vec.size() > 1) {
          // There must be an alias for identification purpose
          assert(expr_alias_vec[expr_alias_vec.size() - 2] == "as");
          expr_attr.name = expr_vec.back();
        } else {
          assert(expr_vec.size() == 1);
          expr_attr.name = expr_vec[0];
        }

        FieldMeta *expr_field_meta{nullptr};

        // Note that this should be the same for single col / multi col expression
        for (const auto &t : oper->tables_) {
          expr_field_meta = (FieldMeta*) t->table_meta().field(expr_vec[0].c_str());
          if (expr_field_meta == nullptr) {
            continue;
          }
        }
        if (expr_field_meta == nullptr) {
          LOG_WARN("[PlainCommunicator::write_result_internal] failed to retrieve field meta for col: %s.", expr_vec[0].c_str());
        }

        expr_attr.type = expr_field_meta->type();
        expr_attr.length = expr_field_meta->len();
        expr_attr.is_null = expr_field_meta->is_null();

        expr_table_attrs.push_back(expr_attr);
      }

      rc = current_db->create_table(oper->name().c_str(), oper->select_expr_.size(), expr_table_attrs.data());
      if (rc != RC::SUCCESS) {
        LOG_WARN("[PlainCommunicator::write_result_internal] failed to create table %s.", oper->name().c_str());
      }

      Table *expr_table = current_db->find_table(oper->name().c_str());
      assert(expr_table != nullptr);
      while ((rc = oper->next()) == RC::SUCCESS) {
        ValueListTuple *expr_tuple = dynamic_cast<ValueListTuple *>(oper->current_tuple());
        assert(expr_tuple != nullptr);
        Record record;
        rc = expr_table->make_record(oper->select_expr_.size(), expr_tuple->get_cells().data(), record);
        if (rc != RC::SUCCESS) {
          LOG_WARN("[PlainCommunicator::write_result_internal] failed to make record");
        }
        rc = expr_table->insert_record(record);
        if (rc != RC::SUCCESS) {
          LOG_WARN("[PlainCommunicator::write_result_internal] failed to insert record");
          oper->close();
          current_db->drop_table(oper->name().c_str());
        }
      }
      expr_table->meta_.tables = tables;
      expr_table->meta_.fields = fields;  
      expr_table->set_view_flag(true);
      rc = oper->close();
      return;
    }
    vector<Table*> tables;
    vector<const FieldMeta*> fields;
    const auto &project_tuple = oper->get_project_tuple();
    const auto specs = project_tuple.get_specs();
    int cell_num = project_tuple.cell_num();
    std::vector<AttrInfoSqlNode> attrs;
    if (oper->attrs_.size() == 0) {
      std::cout << "hi!" << std::endl;
      for (int i = 0; i < cell_num; i++) {
        const TupleCellSpec &spec = *specs[i];
        const char *table_name = spec.table_name();
        const char *filed_name = spec.field_name();
        Table *table = current_db->find_table(table_name);
        if (table == nullptr) {
          return;
        }
        tables.push_back(table);
        const FieldMeta *field_meta = table->table_meta().field(filed_name);
        if (nullptr == field_meta) {
          // std::cout << "null field meta, name: " << filed_name;
        }
        fields.push_back(field_meta);
        AttrInfoSqlNode attr;
        attr.type = field_meta->type();
        attr.name = field_meta->name();
        attr.length = field_meta->len();
        attr.is_null = field_meta->is_null();
        // alis
//        const char *alias = schema.cell_at(i).alias();
//        if (nullptr != alias || alias[0] != 0) {
//          attr.name = alias;
//        }
        attrs.push_back(attr);
      }
    } else {
      attrs = oper->attrs_;
    }
    std::string name = oper->name().c_str();
    LOG_WARN("boring %s", name.c_str());
    rc = current_db->create_table(name.c_str(), cell_num, attrs.data());
    if (OB_FAIL(rc)) {
      oper->close();
      return;
    }
    // create table sucess and then insert record
    Table *table = current_db->find_table(oper->name().c_str());
    Tuple *tuple = nullptr;
    // FIXME: may be need check but select success, then insert must success,so some check is ignored
    while (RC::SUCCESS == (rc = next_tuple(tuple, oper))) {
      assert(tuple != nullptr);
      // assert(cell_num == tuple->cell_num());
      std::vector<Value> vals;
      std::vector<RID> rids;
      for (int i = 0; i < cell_num; i++) {
        Value value;
        rc = tuple->cell_at(i, value);
        if (rc != RC::SUCCESS) {
          oper->close();
          return;
        }
        RID rid;
        rc = tuple->cell_rid(i, rid);
        if (rc != RC::SUCCESS) {
          oper->close();
          return;
        }        
        vals.push_back(value);
        rids.push_back(rid);
      }
      Record record;
      rc = table->make_record(cell_num, vals.data(), record);
      rc = table->insert_record(record);
      table->meta_.rid_map[record.rid()] = rids;
      if (rc != RC::SUCCESS) {
        oper->close();
        current_db->drop_table(oper->name().c_str());
        return;
      }
      if (rc != RC::SUCCESS) {
        oper->close();
        current_db->drop_table(oper->name().c_str());
      }
    }
    table->meta_.tables = tables;
    table->meta_.fields = fields;   
    table->set_view_flag(true);
    RC rc_close = oper->close();
    trx->commit();
    return;
  }
  LOG_PANIC("no reach");
}