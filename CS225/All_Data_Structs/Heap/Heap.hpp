#ifndef __HEAP_HEAP_HPP
#define __HEAP_HEAP_HPP

#include <stdexcept>
#include "./../Array/Array.hpp"

/* 
Heap is essentially a binary tree, but it's normally implemented as an array!

Tree Node - Array correspondence:

For node arr[p+(-1)+\sum_{r=0}^{n}2^r] = arr[i] (-1 is for 0-based-idxing, p is a 0-based offset),
its children are:
 arr[2p+k+(-1)+\sum_{r=0}^{n+1}2^r] (k = 0, 1)
=arr[2p+k+(-1)+(\sum_{r=0}^{n}2^r)+2^(n+1)]
=arr[2p+k+(-1)+2(\sum_{r=0}^{n}2^r)+1] (Geometric series)
=arr[2i+1+k]
=arr[2i+1] (left) and arr[2i+2] (right)

Min-heap property: arr[i] <= arr[2i+1] && arr[i]<= arr[2i+2]

its parent is:
arr[(i-1)/2] (note that cpp int division auto floors)
*/

// Min-heap
template <typename T, typename Comparator = std::less<T>>
class Heap
{
private:
    Array<T> arr;
    Comparator comp;
public:
    Heap() = default;
    Heap(Comparator custom_comp) : arr(), comp(custom_comp)    {}
    ~Heap() noexcept = default;

    Heap(Heap&& other) = default;
    Heap& operator=(Heap&& other) = default;

    void push(const T& input);

    const T& top();
    void pop();
    void clear() {arr.clear();}

    size_t find(const T& input);
    T& at(size_t idx);

    size_t size() const noexcept;
    bool empty() const noexcept;

    
    void heapifyUp(size_t idx); // restoring heap property after push
    void heapifyDown(size_t idx); // ... after pop
};


template <typename T, typename Comparator>
size_t Heap<T, Comparator>::find(const T& input)    {
    for (auto it = arr.begin(); it != arr.end(); ++it)  {
        if (*it == input) return std::distance(arr.begin(), it); 
    }
    throw std::runtime_error("Value is not present.\n");
}


template <typename T, typename Comparator>
T& Heap<T, Comparator>::at(size_t idx)    {
    return arr[idx];
}


template <typename T, typename Comparator>
void Heap<T, Comparator>::heapifyUp(size_t idx) {// restoring heap property after push 
    while (idx > 0 && comp(arr[idx], arr[(idx - 1) / 2]) /* i.e. !(arr[(idx - 1) / 2] <= arr[idx]) */) { // check > 0 or have issues when reaching the root
        std::swap(arr[idx], arr[(idx - 1) / 2]);
        idx = (idx - 1) / 2;
    }
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::heapifyDown(size_t idx) {// ... after pop
    size_t leftIdx, rightIdx, minIdx;

    while (1)  {
        leftIdx = 2 * idx + 1;
        rightIdx = 2 * idx + 2;
        minIdx = idx;

        if (leftIdx < arr.size() && comp(arr[leftIdx], arr[minIdx]) /*violates heap property*/ ) {
            minIdx = leftIdx;
        }

        if (rightIdx < arr.size() && comp(arr[rightIdx], arr[minIdx]) /*violates heap property*/ ) {
            minIdx = rightIdx;
        }

        if (minIdx == idx) break; // already satisfies, stop heapfying down

        std::swap(arr[idx], arr[minIdx]);
        idx = minIdx;
    }
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::push(const T& input)  {
    arr.push_back(input);
    heapifyUp(arr.size()-1);
}

template <typename T, typename Comparator>
const T& Heap<T, Comparator>::top()  {
    if (arr.empty()) throw std::runtime_error("Heap is empty, cannot top.");
    return arr[0]; // this cannot be const as the arr [] op is not marked const
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::pop() {
    if (arr.empty()) throw std::runtime_error("Heap is empty, cannot pop.");
    std::swap(arr[0], arr[arr.size()-1]);
    arr.remove(arr.size()-1);
    heapifyDown(0);
}

template <typename T, typename Comparator>
size_t Heap<T, Comparator>::size() const noexcept {
    return arr.size();
}

template <typename T, typename Comparator>
bool Heap<T, Comparator>::empty() const noexcept    {
    return arr.empty();
}


#endif // __HEAP_HEAP_HPP