#include "Index.h"

// Index Member Functions

int hash_string(const std::string& str) {
    // Returns an integer hash code for the given string
    int hash = 0;
    for (char c : str) {
        hash = hash * 31 + c;
    }
    return hash;
}

HashMap::~HashMap() {
    // Clean up memory when hash map is destroyed
    for (int i = 0; i < TABLE_SIZE; ++i) {
        HashNode* curr = table[i];
        while (curr) {
            HashNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
        table[i] = nullptr;
    }
}

void HashMap::add(const std::string& key, Node* cur) {
    // Adds a new key-value pair to the hash map
    int index = hash_string(key) % TABLE_SIZE;
    HashNode *prev = nullptr;
    HashNode *entry = table[index];

    while (entry != nullptr && entry->key != key) {
        prev = entry;
        entry = entry->next;
    }

    if (entry == nullptr) {
        entry = new HashNode(key, cur);
        if (prev == nullptr) {
            table[index] = entry;
        } else {
            prev->next = entry;
        }
    } else {
        entry->node = cur;
    }

}

Node* HashMap::get(const std::string& key) const {
    // Returns the node associated with the given key, or nullptr if not found
    int index = hash_string(key) % TABLE_SIZE;
    HashNode* curr = table[index];
    while (curr) {
        if (key == curr->key) {
            return curr->node;
        }
        curr = curr->next;
    }
    return nullptr;
}

void HashMap::remove(const std::string& key) {
    // Removes the node associated with the given key
    int index = hash_string(key) % TABLE_SIZE;
    HashNode* curr = table[index];
    HashNode* prev = nullptr;
    while (curr) {
        if (key == curr->key) {
            if (prev)
                prev->next = curr->next;
            else
                table[index] = curr->next;
            delete curr;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}