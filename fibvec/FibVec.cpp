#include "FibVec.h"

// This provides exception types:
#include <stdexcept>
#include <iostream>

FibVec::FibVec(){
    fib_vector = new int[1];
    size = 1;
    counts = 0;
}

FibVec::~FibVec(){
    delete[] fib_vector;
}

size_t FibVec::capacity() const
{
    return size;
}

size_t FibVec::count() const
{
    return counts;
}

size_t FibVec::lookup(size_t index) const
{
    if(index < counts){
        return fib_vector[index];
    }
    throw std::out_of_range("out of range");
}

void FibVec::insert(int value, size_t index)
{
    if(index > counts){
        throw std::out_of_range("out of range");
    }
    else if(index == size){
        reorg();
    }
    for(int i = (int)(counts); i > (int)(index); --i){
        fib_vector[i] = fib_vector[i - 1];
    }
    fib_vector[index] = value;
    counts += 1;
    
}

int FibVec::pop()
{
    if(counts == 0){
        throw std::underflow_error("out of range");
    }
    
    int result = fib_vector[counts - 1];
    counts -= 1;
    reorg();
    //call helper function
    return result;
    
}

void FibVec::push(int value)
{
    reorg();
    //call helper function
    fib_vector[counts] = value;
    counts += 1;

}

size_t FibVec::remove(size_t index)
{
    if(index <= counts){
        int result = fib_vector[index];
        for(size_t i = index; i + 1 < counts; i++){
            fib_vector[i] = fib_vector[i + 1];
        }
        counts -= 1;
        reorg();
        //call helper function
        return result;
    }
    throw std::out_of_range("out of range");
}


FibVec* create_fibvec() {
  // Used by the autograder to make a new FibVec.
  // You shouldn't need to change this.
  return new FibVec();
}


// FibVec Function Implementations
void FibVec::reorg(){
    if(counts > size){
        //size += 1;
        int newSize = 0;
        int num1 = 1;
        int num2 = 1;
        while(newSize <= (int)(size)){
            newSize = num1 + num2;
            num1 = num2;
            num2 = newSize;
        }
        int* storeP = fib_vector;
        fib_vector = new int[newSize];
        for(size_t i = 0; i < counts; i++){
            fib_vector[i] = storeP[i];
        }
        delete[] storeP;
        }
    int num1 = 1;
    int num2 = 1;
    int newSize = 0;
    while(newSize < (int)(size)){
        newSize = num1 + num2;
        num1 = num2;
        num2 = newSize;
    }
    else if((int)(counts) < num1){
        int* storeP = fib_vector;
        fib_vector = new int[num1];
        for(size_t i = 0; i < counts; i++){
            fib_vector[i] = storeP[i];
        }
        delete[] storeP;
    }

}
