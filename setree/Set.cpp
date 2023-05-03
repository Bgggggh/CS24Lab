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
                currNode = currNode -> left;
            }
            else if(value > currNode -> val){
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
    return 0;
}

const std::string& Set::lookup(size_t n) const{
    if(mRoot == nullptr || count() <= n){
        throw std::out_of_range("look up out of range");
    }
    Node* currNode = mRoot;
    while(currNode){
        if(n == currNode -> left -> count){
            return currNode -> val;
        }
        else if(n < currNode -> left -> count){
            currNode = currNode -> left;
        }
        else{
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
    return 1;
}

