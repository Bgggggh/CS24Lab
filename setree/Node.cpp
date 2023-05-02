#include "Node.h"
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

Node& Node::operator = (const Node& other){
    if(this != &other){
        val = other.val;
        count = other.count;
        delete left;
        left = nullptr;
        delete right;
        right = nullptr;
        if(other.left){
            left = new Node(*other.left);
        }
        else if(other.right){
            right = new Node(*other.right);
        }
    }
    return *this;
}

Node& Node::operator=(Node&& other) {
    if (this != &other) {
        val = std::move(other.val);
        count = other.count;
        delete left;
        left = other.left;
        other.left = nullptr;
        delete right;
        right = other.right;
        other.right = nullptr;
        other.count = 0;
    }
    return *this;}
