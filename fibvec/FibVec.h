#ifndef FIBVEC_H
#define FIBVEC_H

// This provides the size_t type:
#include <cstddef>

class FibVec {
  // Member Variables
private:
    size_t size;
    size_t counts;
    int* fib_vector;
  // Helper Functions

public:
  // Constructor and Destructoe
    FibVec();
    ~FibVec();
  // Member Functions
    size_t capacity() const;
    size_t count() const;
    void insert(int value, size_t index);
    size_t lookup(size_t index) const;
    int pop();
    void push(int value);
    size_t remove(size_t index);
};

// Used by the autograder:
FibVec* create_fibvec();

#endif
