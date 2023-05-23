#include <stdexcept>
#include<iostream>
#include "Heap.h"

Heap::Heap(size_t capacity = 10)
    : mData(new Entry[capacity]), mCapacity(capacity), mCount(0)
{}

Heap::Heap(const Heap& other) : mData(new Entry[other.mCapacity]), mCapacity(other.mCapacity), mCount(other.mCount)
{
    std::copy(other.mData, other.mData + other.mCount, mData);
}

Heap::Heap(Heap&& other)
    : mData(other.mData), mCapacity(other.mCapacity), mCount(other.mCount)
{
    other.mData = nullptr;
    other.mCapacity = 0;
    other.mCount = 0;
}

Heap::~Heap()
{
    delete[] mData;
}

size_t Heap::capacity() const
{
    return mCapacity;
}

size_t Heap::count() const
{
    return mCount;
}

const Heap::Entry& Heap::lookup(size_t index) const
{
    if (index >= mCount) {
        throw std::out_of_range("Invalid index");
    }
    return mData[index];
}

Heap::Entry Heap::pop()
{
    if (mCount == 0) {
        throw std::underflow_error("Heap is empty");
    }
    Entry entry = mData[0];
    --mCount;
    mData[0] = mData[mCount];
    size_t index = 0;
    while (true) {
        size_t leftChild = 2 * index + 1;
        size_t rightChild = 2 * index + 2;

        if (leftChild >= mCount){
            break;
        }

        size_t smallest = index;

        if (leftChild < mCount && mData[leftChild].score < mData[smallest].score) {
            smallest = leftChild;
        }
        if (rightChild < mCount && mData[rightChild].score < mData[smallest].score) {
            smallest = rightChild;
        }

        if (smallest == index) {
            break;
        }

        std::swap(mData[index], mData[smallest]);
        index = smallest;
    }
    return entry;
}

Heap::Entry Heap::pushpop(const std::string& value, float score)
{
    if(mCount == 0){
        throw std::underflow_error("Heap is empty");
    }

    Entry entry = { value, score };
    
    std::swap(entry, mData[0]);

    size_t index = 0;
    while (true) {
        size_t leftChild = 2 * index + 1;
        size_t rightChild = 2 * index + 2;

        if (leftChild >= mCount){
            break;
        }

        size_t smallest = index;

        if (leftChild < mCount && mData[leftChild].score < mData[smallest].score) {
            smallest = leftChild;
        }
        if (rightChild < mCount && mData[rightChild].score < mData[smallest].score) {
            smallest = rightChild;
        }

        if (smallest == index) {
            break;
        }

        std::swap(mData[index], mData[smallest]);
        index = smallest;
    }

    return entry;
    
}

void Heap::push(const std::string& value, float score)
{
    if (mCount == mCapacity) {
        throw std::overflow_error("Heap is full.");
    }

    Entry entry = { value, score };
    size_t currentIndex = mCount;
    
    size_t parentIndex = (currentIndex - 1) / 2;

    while (currentIndex > 0 && entry.score < mData[parentIndex].score) {
        mData[currentIndex] = mData[parentIndex];
        currentIndex = parentIndex;
        parentIndex = (currentIndex - 1) / 2;
    }

    mData[currentIndex] = entry;
    mCount++;
}

const Heap::Entry& Heap::top() const
{
    if (mCount == 0) {
        throw std::underflow_error("Heap is empty");
    }
    return mData[0];
}





