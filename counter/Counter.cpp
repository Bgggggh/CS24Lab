#include "Counter.h"

// Counter Member Functions

Counter::Counter() {
    dict = new DoublyLinkedList();
}

Counter::~Counter() {
    delete dict;
}

size_t Counter::count() const {
    return dict->key_count();
}

int Counter::total() const {
    int sum = 0;
    for(auto itr = this->begin(); itr != this->end(); ++itr) {
        sum += itr.value();
    }
    return sum;
}

void Counter::inc(const std::string& key, int by) {
    auto node = dict->search(key);
    if (node)
        node->value = node->value + by;
    else
        set(key, 0 + by);
}

void Counter::dec(const std::string& key, int by) {
    auto node = dict->search(key);
    if (node)
        node->value = node->value - by;
    else
        set(key, 0 - by);
}

void Counter::del(const std::string& key) {
    dict->remove(key);
}

int Counter::get(const std::string& key) const{
    auto node = dict->search(key);
    if (node)
        return node->value;
    else
        return 0;
}

void Counter::set(const std::string& key, int count) {
    auto node = dict->search(key);
    if (node)
        node->value = count;
    else    
        dict->insert(key, count);
}

Counter::Iterator Counter::begin() const {
    Counter::Iterator it(dict->head_ptr());
    return it;
}

Counter::Iterator Counter::end() const {
    Counter::Iterator it;
    return it;
}