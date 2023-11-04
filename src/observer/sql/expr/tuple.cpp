//
// Created by susun on 23-11-4.
//

#include "tuple.h"
#include <atomic>

std::atomic<bool> find_left_first{true};

RC JoinedTuple::find_cell(const TupleCellSpec &spec, Value &value) const {
  if (find_left_first) {
    RC rc = left_->find_cell(spec, value);
    if (rc == RC::SUCCESS || rc != RC::NOTFOUND) {
      return rc;
    }

    return right_->find_cell(spec, value);
  } else {
    RC rc = right_->find_cell(spec, value);
    if (rc == RC::SUCCESS || rc != RC::NOTFOUND) {
      return rc;
    }

    return left_->find_cell(spec, value);
  }
}

void JoinedTuple::set_find_left_first(bool flag) { find_left_first = flag; }
