#include "FibVec.h"

// This provides exception types:
#include <stdexcept>

FibVec::FibVec(){
    fib_vector = new int[1];
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
    if(index < counts){
        fib_vector[index] = value;
    }
    throw std::out_of_range("out of range");
}

int FibVec::pop()
{
    if(counts != 0){
        
    }
}

void FibVec::push(int value)
{
    
}

size_t FibVec::remove(size_t index)
{
    
}


FibVec* create_fibvec() {
  // Used by the autograder to make a new FibVec.
  // You shouldn't need to change this.
  return new FibVec();
}


// FibVec Function Implementations
