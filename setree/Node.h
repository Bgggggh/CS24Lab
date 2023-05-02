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
    Node(Node&& other);
    ~Node();
   
    Node& operator = (const Node& other);
    Node& operator = (Node&& other);

    Node* left;
    Node* right;
    int count;
    
};



#endif
