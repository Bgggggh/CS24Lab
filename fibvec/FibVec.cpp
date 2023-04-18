#include "FibVec.h"

// This provides exception types:
#include <stdexcept>

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
    if(index <= count()){
        fib_vector[index] = value;
        counts += 1;
    }
    throw std::out_of_range("out of range");
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
    counts += 1;
    reorg();
    //call helper function
    fib_vector[-1] = value;
}

size_t FibVec::remove(size_t index)
{
    if(counts != 0){
        int result = fib_vector[index];
        for(size_t i = index; i < counts; i++){
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
        size += 1;
    }
    else if(counts < size -2){
        size -= 1;
    }
}
