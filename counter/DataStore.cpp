#include "DataStore.h"

// DataStore Member Functions
DoublyLinkedList::DoublyLinkedList() {
    Node* head = nullptr;
    Node* tail = nullptr;
    size_t count = 0;
    HashMap map = {};
}

DoublyLinkedList::~DoublyLinkedList() {
    Node* curr = head;
    while(curr) {
        Node* temp = curr;
        curr = curr->next;
        delete temp;
    }
}

Node* DoublyLinkedList::head_ptr() const {
    return head;
}

Node* DoublyLinkedList::tail_ptr() const {
    return tail;
}

size_t DoublyLinkedList::key_count() const {
    return count;
}

void DoublyLinkedList::insert(std::string key, int value) {
    Node* new_node = new Node();
    new_node->key = key;
    new_node->value = value;

    if (head == nullptr) {
        head = new_node;
        tail = new_node;
    } else {
        tail->next = new_node;
        new_node->prev = tail;
        tail = new_node;
    }
    count++;
    map.add(key, new_node);
}

Node* DoublyLinkedList::search(std::string key) const{
    return map.get(key);
}

bool DoublyLinkedList::remove(std::string key) {
    auto curr = map.get(key);
    if (curr == nullptr)
        return false;
    count--;
    if (curr == head) {
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
    } else if (curr == tail) {
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        }
    } else {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
    }
    delete curr;
    map.remove(key);
    return true;
}
