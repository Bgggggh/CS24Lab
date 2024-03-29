#include "DataStore.h"

// DataStore Member Functions
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
}

Node* DoublyLinkedList::search(std::string key) const{
    Node* curr = head;
    while (curr != nullptr) {
        if (curr->key == key) {
            return curr;
        }
        curr = curr->next;
    }
    return nullptr;
}

bool DoublyLinkedList::remove(std::string key) {
    Node* curr = head;
    while (curr != nullptr) {
        if (curr->key == key) {
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
            count--;
            return true;
        }
        curr = curr->next;
    }
    return false;
}