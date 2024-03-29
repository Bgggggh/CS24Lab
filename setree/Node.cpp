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

void Node::copyF(Node* node, Node* &insertNode){
    if(node == NULL){
        return;
    }
    insertNode = new Node(node->val);
    copyF(node->left, insertNode->left);
    copyF(node->right, insertNode->right);
}

Node::~Node(){
    delete left;
    left = NULL;
    delete right;
    right = NULL;
}

size_t Node::clearF(Node* node) const{
    if(node == NULL){
        return 0;
    }
    size_t count1 = countF(node);
    delete node;
    node = nullptr;
    return count1;
}

size_t Node::countF(Node* node) const {
    if(node ==NULL){
        return 0;
    }
    else{
        return  countF(node -> left) + countF(node -> right) + 1;
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
            cout << " ";
            cout << node -> val;
            cout << " ";
            printF(node -> right);
            cout << ')';
        }
    }

}
