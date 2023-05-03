#ifndef NODE_H
#define NODE_H
#include <string>
using namespace std;

// Use this file to declare your Node type.
// Implement Node member functions and helper functions in Node.cpp.
class Node{
public:
    string val;
    Node();
    Node(const string& value);
    Node(const Node& other);
    ~Node();

    Node* left;
    Node* right;
    size_t count;

    size_t countF(Node* node) const;
    void printF(Node* node) const;
    size_t claerF(Node* node) const;
    void copyF(Node* node, Node* &insertedNode);
};



#endif
