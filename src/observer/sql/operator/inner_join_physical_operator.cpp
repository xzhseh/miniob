//
// Created by susun on 23-10-17.
//

#include "inner_join_physical_operator.h"

InnerJoinOperator::InnerJoinOperator(std::unique_ptr<Expression> join_condition) : join_condition_(std::move(join_condition)) {
    ASSERT(join_condition_->value_type() == BOOLEANS, "predicate's expression should be BOOLEAN type");
}

RC InnerJoinOperator::open(Trx *trx) {
    if (children_.size() != 2) {
        LOG_WARN("inner operator should have 2 children");
        return RC::INTERNAL;
    }

    RC rc = RC::SUCCESS;
    left_ = children_[0].get();
    right_ = children_[1].get();

    trx_ = trx;

    // Open left and right
    rc = left_->open(trx);
    if (rc != RC::SUCCESS) {
        LOG_WARN("failed to open left child operator: %s", strrc(rc));
        return rc;
    }
    rc = right_->open(trx);
    return rc;
}

RC InnerJoinOperator::next() {
    RC rc = RC::SUCCESS;


    std::vector<Tuple*> left_tuples;
    std::vector<Tuple*> right_tuples;

    // Get all tuples from left
    while (RC::SUCCESS == (rc = left_->next())) {
        Tuple *tuple = left_->current_tuple();
        if (nullptr == tuple) {
            rc = RC::INTERNAL;
            LOG_WARN("failed to get tuple from left operator");
            break;
        }
        left_tuples.push_back(tuple);
    }

    if (rc != RC::SUCCESS && rc != RC::RECORD_EOF ) {
        LOG_WARN("failed to get tuple from left operator: %s", strrc(rc));
        return rc;
    }

    // Get all tuples from right
    while (RC::SUCCESS == (rc = right_->next())) {
        Tuple *tuple = right_->current_tuple();
        if (nullptr == tuple) {
            rc = RC::INTERNAL;
            LOG_WARN("failed to get tuple from right operator");
            break;
        }
        right_tuples.push_back(tuple);
    }

    if (rc != RC::SUCCESS && rc != RC::RECORD_EOF ) {
        LOG_WARN("failed to get tuple from left operator: %s", strrc(rc));
        return rc;
    }

    // Do join
    for (auto left_tuple : left_tuples) {
        for (auto right_tuple : right_tuples) {
            JoinedTuple* tuple = new JoinedTuple();
            tuple->set_left(left_tuple);
            tuple->set_right(right_tuple);
            Value value;
            rc = join_condition_->get_value(*tuple, value);
            if (rc != RC::SUCCESS) {
                LOG_WARN("failed to get value from join condition: %s", strrc(rc));
                return rc;
            }
        }
    }
    return rc;
}
RC InnerJoinOperator::close() {
    return RC::SUCCESS;
}

Tuple *InnerJoinOperator::current_tuple() {
    return nullptr;
}
