#ifndef PRIORITYQUEUE_HPP
#define PRIORITYQUEUE_HPP

#include <stdexcept>
#include <concepts>
#include <iostream>
#include <functional> // for std::less and other compares
#include "./../Heap/Heap.hpp"


template <typename T>
concept Priority = requires(T a, T b) {
    { a <= b } -> std::convertible_to<bool>;
    { a < b } -> std::convertible_to<bool>;
    { a > b } -> std::convertible_to<bool>;
    { a == b } -> std::convertible_to<bool>;
};
/*
concept: C++20 feature.
Imposes a contraint on class. 
Requires the type used to instantiate the class to support certain operations (e.g. addition, comparison)


To impose on a class, write:
template<typename T>
requires SomeConcept<T>
class MyClass { ... };

or the shorthand:

template<SomeConcept T>
class MyClass { ... };

these are required for its function decl as well.
*/

// Min-priority queue

template <typename T, typename Comparator = std::less<T>>
class PriorityQueue {
private:
Heap<T, Comparator> heap; // Don't forget the second type, or will use default and can't take custom comparator!
Comparator comp;

public:

PriorityQueue() = default;

PriorityQueue(Comparator custom_comp) : heap(custom_comp), comp(custom_comp)    {}

// Forwarding functions

void push(const T& input) { heap.push(input); }
const T& top() { return heap.top(); }
void pop() { heap.pop(); }
void clear() { heap.clear(); }

size_t find(const T& input) const { return heap.find(input); }
T& at(size_t idx) { return heap.at(idx); }

size_t size() const noexcept { return heap.size(); }
bool empty() const noexcept { return heap.empty(); }


void decreasePriority(const T& orig_val, const T& new_val);

};

template <typename T, typename Comparator>
void PriorityQueue<T, Comparator>::decreasePriority(const T& orig_val, const T& new_val)    {
    auto idx = heap.find(orig_val); // let value not found throw first
    if (new_val <= orig_val) throw std::invalid_argument("Priority can only be decreased.\n");
    heap.at(idx) = new_val;
    heap.heapifyDown(idx); // Restore heap order
}

#endif // PRIORITYQUEUE_HPP