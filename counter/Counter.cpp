#include "Counter.h"

// Counter Member Functions

Counter::Counter() {
    list = new DoublyLinkedList;
}

Counter::~Counter() {
    delete list;
}

size_t Counter::count() const {
    return list->key_count();
}

int Counter::total() const {
    int sum = 0;
    for(auto itr = this->begin(); itr != this->end(); ++itr) {
        sum += itr.value();
    }
    return sum;
}

void Counter::inc(const std::string& key, int by) {
    auto node = list->search(key);
    if (node)
        node->value = node->value + by;
    else
        list->insert(key, 0 + by);
    
}

void Counter::dec(const std::string& key, int by) {
    auto node = list->search(key);
    if (node)
        node->value = node->value - by;
    else
        list->insert(key, 0 - by);
}

void Counter::del(const std::string& key) {
    list->remove(key);
}

int Counter::get(const std::string& key) const{
    auto node = list->search(key);
    if (node)
        return node->value;
    else
        return 0;
}

void Counter::set(const std::string& key, int count) {
    auto node = list->search(key);
    if (node)
        node->value = count;
    else    
        list->insert(key, count);
}

Counter::Iterator Counter::begin() const {
    Counter::Iterator it(list->head_ptr());
    return it;
}

Counter::Iterator Counter::end() const {
    Counter::Iterator it;
    return it;
}