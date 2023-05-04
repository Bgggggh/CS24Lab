#include "Set.h"
#include <stdexcept>
#include <iostream>
using namespace std;

Set::Set() : mRoot(nullptr) {}
Set::Set(const Set& other) : mRoot(nullptr){
    if(other.mRoot){
        

        mRoot = new Node(other.mRoot->val);
        mRoot->copyF(other.mRoot->left, mRoot->left);
        mRoot->copyF(other.mRoot->right, mRoot->right);

    }
}
Set::Set(Set&& other) {
    this->mRoot = other.mRoot;
    other.mRoot = nullptr;
}

Set::~Set() {
    delete mRoot;
    mRoot = NULL;
}

size_t Set::clear(){
   return mRoot -> claerF(mRoot);
}


bool Set::contains(const std::string& value) const{
    Node* curr = mRoot;
    while(curr){
        if(value == curr->val){
            return true;
        }
        else if(value < curr->val){
            curr = curr->left;
        }
        else{
            curr = curr->right;
        }
    }
    return false;
}

size_t Set::count() const{
    return mRoot->countF(mRoot);
}

void Set::debug(){}

size_t Set::insert(const string& value){
    if(contains(value)){
        return 0;
    }
    else{
        if(mRoot == NULL){
        mRoot = new Node(value);
        return 1;
        }
        Node* currNode = mRoot;
        Node* preNode = NULL;
        while(currNode){
            preNode = currNode;
            if(value == currNode -> val){
                return 0;
            }
            else if(value < currNode -> val){
                currNode->count = currNode->count + 1;
                currNode = currNode -> left;
            }
            else if(value > currNode -> val){
                currNode->count = currNode->count + 1;
                currNode = currNode -> right;
            }
        }
        Node* newNode = new Node(value);
        if(value < preNode -> val){
            preNode -> left = newNode;
        }
        else{
            preNode -> right = newNode;
        }
        return 1;
        
    }
    delete mRoot;
    return 0;
}

const std::string& Set::lookup(size_t n) const{
    if(mRoot == nullptr || count() <= n){
        throw std::out_of_range("look up out of range");
    }
    Node* currNode = mRoot;
    size_t ct = 0;
    while(currNode){
        if(currNode->left != NULL) ct = currNode->left->count;
        else ct = 0;
        if(n == ct){
            return currNode -> val;
        }
        else if(n < ct){
            currNode = currNode -> left;
        }
        else{
            n = n - ct - 1;
            currNode = currNode -> right;
        }
    }
    throw std::out_of_range("look up out of range");
}

void Set::print() const {
    mRoot -> printF(mRoot);
    std::cout << std::endl;
}

size_t Set::remove(const std::string& value){
    Node* node = mRoot;
    Node* parent = nullptr;
    bool find = false;
    while(node != nullptr){
        if(node->val == value){
            find = true;
            break;
        }
        else if(node->val > value){
            parent = node;
            node = node-> left;
        }
        else{
            parent = node;
            node = node ->right;
        }

    }
    if(!find){
        return 0;
    }
    size_t num_child = (node->left != nullptr) + (node->right != nullptr);
    if(num_child == 0){
        if(node == mRoot){
            mRoot = nullptr;
        }
        else if(node == parent -> left){
            parent->left = nullptr;
        }
        else{
            parent->right = nullptr;
        }
        delete node;
        return 1;
    }
    else if(num_child ==1){
        Node* child = nullptr;
        if(node->left != nullptr){
            child = node->left;
        }
        else {
            child = node->right;
        }
        if(node == mRoot){
            mRoot = child;
        }
        else if(node == parent -> left){
            parent -> left = child;
        }
        else{
            parent -> right =child;
        }
        return 1;
    }
    else{
         Node* pred_parent = node;
        Node* pred = node->left;
        while (pred->right != nullptr) {
            pred_parent = pred;
            pred = pred->right;
        }
        node->val = pred->val;
        if (pred == pred_parent->left) {
            pred_parent->left = pred->left;
        } else {
            pred_parent->right = pred->left;
        }
        pred->left = nullptr;
        pred->right = nullptr;
        delete pred;
        return 1;
    }
}
