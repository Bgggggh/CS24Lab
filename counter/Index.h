#ifndef INDEX_H
#define INDEX_H

// Space to implement a separate index class, if you choose to do so.
// This can make things simpler by clearly separating functionality.
// The Index is in charge of getting pairs from the DataStore by key.
#include <iostream>

struct Node;

// Represents a node in the graph
struct HashNode {
public:
    std::string key;
    Node* node;
    HashNode* next;
    HashNode(std::string str, Node* cur) : key(str), node(cur), next(nullptr) {}
};

const int TABLE_SIZE = 100;

int hash_string(const std::string& str);

class HashMap {
private:
    HashNode* table;

public:
    HashMap(): table(new HashNode*[TABLE_SIZE]()) {}
    ~HashMap();

    void add(const std::string& key, Node* cur);
    Node* get(const std::string& key) const;
    void remove(const std::string& key);

};

#endif
