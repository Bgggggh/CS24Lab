#include "Counter.h"

// Counter::Iterator Member Functions

const std::string& Counter::Iterator::key() const {
    return curr_node->key;
}

int Counter::Iterator::value() const {
    return curr_node->value;
}

Counter::Iterator& Counter::Iterator::operator ++ () {
    curr_node = curr_node->next;
    
    return *this;
}

bool      Counter::Iterator::operator == (const Iterator& other) const {
    return curr_node == other.curr_node;
}

bool      Counter::Iterator::operator != (const Iterator& other) const {
    return curr_node != other.curr_node;
}