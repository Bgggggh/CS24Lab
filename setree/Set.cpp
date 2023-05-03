#include "Set.h"
#include <stdexcept>
using namespace std;

Set::Set() : mRoot(nullptr) {}
Set::Set(const Set& other) : mRoot(nullptr){
    if(other.mRoot){
        mRoot = new Node(*other.mRoot);
    }
}
Set::Set(Set&& other) : mRoot(other.mRoot){
    other.mRoot = nullptr;
}

Set::~Set() {
    delete mRoot;
}

size_t Set::clear(){
   
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
        else if(value > curr->val){
            curr = curr->right;
        }
        else{
            return false;
        }
    }
}

size_t Set::count() const{
    mRoot->countF(mRoot);
}

void Set::debug() const{}

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
        
        
    }
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
}
