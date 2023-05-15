#ifndef DATASTORE_H
#define DATASTORE_H

#include <string>
#include "Index.h"

// Space to implement a separate datastore class, if you choose to do so.
// This can make things simpler by clearly separating functionality.
// The DataStore is in charge of storing pairs in insertion order.
struct Node {
    std::string key;
    int value;
    Node* prev = nullptr;
    Node* next = nullptr;
};

class DoublyLinkedList {
  private:
    Node* head;
    Node* tail;
    size_t count;
    HashMap map;

  public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    Node* head_ptr() const;
    Node* tail_ptr() const;

    size_t key_count() const;
    void insert(std::string key, int value);
    Node* search(std::string key) const;
    bool remove(std::string key);
};

#endif