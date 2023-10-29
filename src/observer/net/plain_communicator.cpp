/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2023/06/25.
//

#include "net/plain_communicator.h"
#include "sql/operator/project_physical_operator.h"
#include "common/io/io.h"
#include "common/log/log.h"
#include "storage/db/db.h"
#include "event/session_event.h"
#include "net/buffered_writer.h"
#include "session/session.h"
#include "sql/expr/tuple.h"
#include "sql/parser/value.h"

PlainCommunicator::PlainCommunicator() {
  send_message_delimiter_.assign(1, '\0');
  debug_message_prefix_.resize(2);
  debug_message_prefix_[0] = '#';
  debug_message_prefix_[1] = ' ';
}

RC PlainCommunicator::read_event(SessionEvent *&event) {
  RC rc = RC::SUCCESS;

  event = nullptr;

  int data_len = 0;
  int read_len = 0;

  const int max_packet_size = 1 << 18;
  std::vector<char> buf(max_packet_size);

  // 持续接收消息，直到遇到'\0'。将'\0'遇到的后续数据直接丢弃没有处理，因为目前仅支持一收一发的模式
  while (true) {
    read_len = ::read(fd_, buf.data() + data_len, max_packet_size - data_len);
    if (read_len < 0) {
      if (errno == EAGAIN) {
        continue;
      }
      break;
    }
    if (read_len == 0) {
      break;
    }

    if (read_len + data_len > max_packet_size) {
      data_len += read_len;
      break;
    }

    bool msg_end = false;
    for (int i = 0; i < read_len; i++) {
      if (buf[data_len + i] == 0) {
        data_len += i + 1;
        msg_end = true;
        break;
      }
    }

    if (msg_end) {
      break;
    }

    data_len += read_len;
  }

  if (data_len > max_packet_size) {
    LOG_WARN("The length of sql exceeds the limitation %d", max_packet_size);
    return RC::IOERR_TOO_LONG;
  }
  if (read_len == 0) {
    LOG_INFO("The peer has been closed %s", addr());
    return RC::IOERR_CLOSE;
  } else if (read_len < 0) {
    LOG_ERROR("Failed to read socket of %s, %s", addr(), strerror(errno));
    return RC::IOERR_READ;
  }

  LOG_INFO("receive command(size=%d): %s", data_len, buf.data());
  event = new SessionEvent(this);
  event->set_query(std::string(buf.data()));
  return rc;
}

RC PlainCommunicator::write_state(SessionEvent *event, bool &need_disconnect) {
  SqlResult *sql_result = event->sql_result();
  const int buf_size = 2048;
  char *buf = new char[buf_size];
  const std::string &state_string = sql_result->state_string();
  if (state_string.empty()) {
    const char *result = (RC::SUCCESS == sql_result->return_code()) ? "SUCCESS" : "FAILURE";
    snprintf(buf, buf_size, "%s\n", result);
  } else {
    snprintf(buf, buf_size, "%s > %s\n", strrc(sql_result->return_code()), state_string.c_str());
  }

  RC rc = writer_->writen(buf, strlen(buf) + 1);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to send data to client. err=%s", strerror(errno));
    need_disconnect = true;
    delete[] buf;
    return RC::IOERR_WRITE;
  }

  need_disconnect = false;
  delete[] buf;

  return RC::SUCCESS;
}

RC PlainCommunicator::write_debug(SessionEvent *request, bool &need_disconnect) {
  if (!session_->sql_debug_on()) {
    return RC::SUCCESS;
  }

  SqlDebug &sql_debug = request->sql_debug();
  const std::list<std::string> &debug_infos = sql_debug.get_debug_infos();
  for (auto &debug_info : debug_infos) {
    RC rc = writer_->writen(debug_message_prefix_.data(), debug_message_prefix_.size());
    if (OB_FAIL(rc)) {
      LOG_WARN("failed to send data to client. err=%s", strerror(errno));
      need_disconnect = true;
      return RC::IOERR_WRITE;
    }

    rc = writer_->writen(debug_info.data(), debug_info.size());
    if (OB_FAIL(rc)) {
      LOG_WARN("failed to send data to client. err=%s", strerror(errno));
      need_disconnect = true;
      return RC::IOERR_WRITE;
    }

    char newline = '\n';
    rc = writer_->writen(&newline, 1);
    if (OB_FAIL(rc)) {
      LOG_WARN("failed to send new line to client. err=%s", strerror(errno));
      need_disconnect = true;
      return RC::IOERR_WRITE;
    }
  }

  need_disconnect = false;
  return RC::SUCCESS;
}

RC PlainCommunicator::write_result(SessionEvent *event, bool &need_disconnect) {
  RC rc = write_result_internal(event, need_disconnect);
  if (!need_disconnect) {
    (void)write_debug(event, need_disconnect);
  }
  if (rc == RC::SUCCESS) {
    writer_->flush();  // TODO handle error
  } else {
    write_state(event, need_disconnect);
    writer_->flush();
  }
  return rc;
}

RC PlainCommunicator::write_result_internal(SessionEvent *event, bool &need_disconnect) {
  RC rc = RC::SUCCESS;
  need_disconnect = true;

  SqlResult *sql_result = event->sql_result();

  if (RC::SUCCESS != sql_result->return_code() || !sql_result->has_operator()) {
    return write_state(event, need_disconnect);
  }

  rc = sql_result->open();
  if (OB_FAIL(rc)) {
    sql_result->close();
    sql_result->set_return_code(rc);
    return write_state(event, need_disconnect);
  }
  const TupleSchema &schema = sql_result->tuple_schema();
  const int cell_num = schema.cell_num();
  std::cerr<<"reach here, "<<cell_num<<std::endl;
  ProjectPhysicalOperator* oper =  dynamic_cast<ProjectPhysicalOperator*>(sql_result->get_operator()->get());
  if(nullptr != oper && oper->name() != "") {
      const auto& project_tuple =   oper->get_project_tuple();
      const auto specs =  project_tuple.get_specs();
      std::cerr<<"reach here1, "<<cell_num<<std::endl;
      std::vector<AttrInfoSqlNode> attrs;
      for(int i = 0; i < cell_num; i++) {
        std::cerr<<"checkout"<<std::endl;
        const TupleCellSpec &spec = *specs[i];
        std::cerr<<"checkout"<<std::endl;
        const char* table_name = spec.table_name();
        const char* filed_name = spec.field_name();
        if(nullptr == table_name || nullptr == filed_name) {
          std::cerr<<"null table, name: ";
          exit(0);
        }
        if(session_ == nullptr || session_->get_current_db() == nullptr) {
          std::cerr<<"null err";
        }
        Table* table  = session_->get_current_db()->find_table(table_name);
        if(table == nullptr) {
          std::cerr<<"null err1"<<" table_name"<<table_name;
          exit(0);
        }
        const FieldMeta* field_meta = table->table_meta().field(filed_name);
        if(nullptr == field_meta) {
          std::cout<<"null field meta, name: "<<filed_name;
        }
        AttrInfoSqlNode attr;
        attr.type = field_meta->type();
        attr.name = field_meta->name();
        attr.length = field_meta->len();
        attr.is_null = field_meta->is_null();
        // alis
        const char *alias = schema.cell_at(i).alias();
        if(nullptr != alias || alias[0] != 0) {
          attr.name  = alias;
        }
        attrs.push_back(attr);
        
      }
      rc = session_->get_current_db()->create_table(oper->name().c_str(), cell_num, attrs.data());
      if(OB_FAIL(rc)) {
          sql_result->close();
          sql_result->set_return_code(rc);
          return write_state(event, need_disconnect);
      }
      std::cerr<<"reach here2, "<<cell_num<<std::endl;
      // create table sucess and then insert record
      Table* table = session_->get_current_db()->find_table(oper->name().c_str());
      Tuple *tuple = nullptr;
      // FIXME: may be need check but select success, then insert must success,so some check is ignored
      while (RC::SUCCESS == (rc = sql_result->next_tuple(tuple))) {
          assert(tuple != nullptr);
          assert(cell_num == tuple->cell_num());
          std::cerr<<"reach here3, "<<cell_num<<std::endl;
          std::vector<Value> vals;
          for (int i = 0; i < cell_num; i++) {
             Value value;
             rc = tuple->cell_at(i, value);
             if (rc != RC::SUCCESS) {
                sql_result->close();
                return rc;
             }
             vals.push_back(value);
          }
          Record record;
          rc = table->make_record(cell_num, vals.data(), record);
          rc = table->insert_record(record);
          if (rc != RC::SUCCESS) {
            sql_result->close();
            sql_result->set_return_code(rc);
            return rc;
          }
      }
      std::cerr<<"reach here4, "<<cell_num<<std::endl;
      return RC::SUCCESS;
  }
  

  for (int i = 0; i < cell_num; i++) {
    const TupleCellSpec &spec = schema.cell_at(i);
    const char *alias = spec.alias();
    if (nullptr != alias || alias[0] != 0) {
      if (0 != i) {
        const char *delim = " | ";
        rc = writer_->writen(delim, strlen(delim));
        if (OB_FAIL(rc)) {
          LOG_WARN("failed to send data to client. err=%s", strerror(errno));
          return rc;
        }
      }

      int len = strlen(alias);
      rc = writer_->writen(alias, len);
      if (OB_FAIL(rc)) {
        LOG_WARN("failed to send data to client. err=%s", strerror(errno));
        sql_result->close();
        return rc;
      }
    }
  }

  if (cell_num > 0) {
    char newline = '\n';
    rc = writer_->writen(&newline, 1);
    if (OB_FAIL(rc)) {
      LOG_WARN("failed to send data to client. err=%s", strerror(errno));
      sql_result->close();
      return rc;
    }
  }

  rc = RC::SUCCESS;
  Tuple *tuple = nullptr;
  while (RC::SUCCESS == (rc = sql_result->next_tuple(tuple))) {
    assert(tuple != nullptr);

    int cell_num = tuple->cell_num();
    for (int i = 0; i < cell_num; i++) {
      if (i != 0) {
        const char *delim = " | ";
        rc = writer_->writen(delim, strlen(delim));
        if (OB_FAIL(rc)) {
          LOG_WARN("failed to send data to client. err=%s", strerror(errno));
          sql_result->close();
          return rc;
        }
      }

      Value value;
      rc = tuple->cell_at(i, value);
      if (rc != RC::SUCCESS) {
        sql_result->close();
        return rc;
      }

      std::string cell_str = value.to_string();

      // std::cout << "[plain communicator] current cell_str: " << cell_str << std::endl;

      // Check null here 😅
      if (Value::check_null(value)) {
        cell_str = "NULL";
      }

      rc = writer_->writen(cell_str.data(), cell_str.size());
      if (OB_FAIL(rc)) {
        LOG_WARN("failed to send data to client. err=%s", strerror(errno));
        sql_result->close();
        return rc;
      }
    }

    char newline = '\n';
    rc = writer_->writen(&newline, 1);
    if (OB_FAIL(rc)) {
      LOG_WARN("failed to send data to client. err=%s", strerror(errno));
      sql_result->close();
      return rc;
    }
  }

  if (rc == RC::RECORD_EOF) {
    rc = RC::SUCCESS;
  }

  // FIXME: Ensure this
  if (rc != RC::SUCCESS) {
    sql_result->set_return_code(rc);
    writer_->clear();
    return rc;
  }

  if (cell_num == 0) {
    // 除了select之外，其它的消息通常不会通过operator来返回结果，表头和行数据都是空的
    // 这里针对这种情况做特殊处理，当表头和行数据都是空的时候，就返回处理的结果
    // 可能是insert/delete等操作，不直接返回给客户端数据，这里把处理结果返回给客户端
    RC rc_close = sql_result->close();
    if (rc == RC::SUCCESS) {
      rc = rc_close;
    }
    sql_result->set_return_code(rc);
    return write_state(event, need_disconnect);
  } else {
    rc = writer_->writen(send_message_delimiter_.data(), send_message_delimiter_.size());
    if (OB_FAIL(rc)) {
      LOG_ERROR("Failed to send data back to client. ret=%s, error=%s", strrc(rc), strerror(errno));
      sql_result->close();
      return rc;
    }

    need_disconnect = false;
  }

  RC rc_close = sql_result->close();
  if (OB_SUCC(rc)) {
    rc = rc_close;
  }

  return rc;
}