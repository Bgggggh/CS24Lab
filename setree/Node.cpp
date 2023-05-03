#include "Node.h"
#include <iostream>
using namespace std;
Node::Node() : val(""), left(nullptr), right(nullptr), count(0) {}
Node::Node(const string& val) : val(val), left(nullptr), right(nullptr), count(1) {}
Node::Node(const Node& other) : val(other.val), left(nullptr), right(nullptr), count(other.count){
    if(other.left){
        left = new Node(*other.left);
    }
    else if(other.right){
        right = new Node(*other.right);
    }
}

Node::Node(Node&& other) : val(move(other.val)), left(other.left), right(other.left), count(other.count){
    other.left = nullptr;
    other.right = nullptr;
    other.count = 0;
}

Node::~Node(){
    delete left;
    delete right;
}

size_t Node::claerF(Node* node) const{
    
}

size_t Node::countF(Node* node) const {
    if(node ==NULL){
        return 0;
    }
    else{
        return  countF((node -> left) + (node -> right)) + 1;
    }
}

void Node::printF(Node* node) const{
    if(node == NULL){
        cout << '-';
    }
    else{
        if(node -> left == NULL && node -> right == NULL){
            cout << node -> val;
        }
        else{
            cout << '(';
            printF(node -> left);
            cout << node -> val;
            printF(node -> right);
            cout << ')';
        }
    }
}
