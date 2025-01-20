#ifndef __ARRAY_ARRAY_HPP
#define __ARRAY_ARRAY_HPP
#include <stdexcept>
#include <iostream>

template <typename T>
class Array {
public:
    class iterator  {
    /*
    To conform to the standard iterator interface, the iterator class must define the following type aliases:

    - difference_type: Used to represent the difference between two iterators (already implemented in your operator-).
    - value_type: The type of the elements being iterated over (T in this case).
    - pointer: The type of a pointer to the element (T*).
    - reference: The type of a reference to the element (T&).
    - iterator_category: Specifies the type of iterator (e.g., std::random_access_iterator_tag).
    */
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::random_access_iterator_tag;

        iterator(pointer ptr_in);

        /*
        iterator cls should have:
        > ++ increm op
        > + offsetting op
        > * deref op
        > ==, != (in)eq op, for control conditioning
        */

        iterator& operator++(); // return by ref means pre increm
        iterator& operator--();
        iterator operator+(size_t incr) const; // Note that we want it+incr to return a new incr-ed iter but not modify the original

        reference operator*() const; // return by ref :  could modify through iter as *iter = a;

        bool operator==(iterator rhs) const;
        bool operator!=(iterator rhs) const;

        // Difference operator (required for std::distance)
        difference_type operator-(const iterator& other) const { return ptr_ - other.ptr_; }


        friend class Array; // for convenient direct access of Array attributes

    private:
        pointer ptr_;
    };

    Array(); // default constructor: empty w/ capacity 1
    Array(size_t count, const T& other = T()); // fill constructor
    ~Array();
    Array(const Array& other); // copy constructor
    Array& operator=(const Array& other); // copy assignment
    Array(Array&& other) noexcept; // move constructor
    Array& operator=(Array&& other) noexcept; // move assignment

    T& operator[](size_t index); // overriding [] index offsetting op, return by ref for modif as arr[i] = a;
    const T& operator[](size_t index) const; // a non-const overload

    void push_back(const T& input); // append to end, double capac. size_ ~ n : N_alloc ~ O(log n), amortized O(1) by geometric sum
    void push_back(T&& input);

    void remove(size_t index); // rm elem @ idx, size--
    void clear()    {size_ = 0;}

    size_t size() const;
    size_t capacity() const;
    bool empty() const  {return size_ == 0;}

    void resize(size_t new_size, const T& filler = T()); // move semantics' inapplicable here as repeated assignment & reusing the src is required
    void reserve(size_t new_capacity);

    // For iter controls:
    iterator begin();
    iterator end();

    const iterator begin() const;
    const iterator end() const;

    template <typename... Args>
    void emplace_back(Args&&... args); // additionally templated funcs come last, otherwise other funcs will be affected

private:
    T* arr_;
    size_t size_;
    size_t capacity_;
};

// Let's begin implementing these templated funcs. Remember to always include template <typename T>
// and fully specify scope:: for all funcs as we are outside the classes.

template <typename T>
Array<T>::Array() : arr_(new T[1]), size_(0), capacity_(1) {}

template <typename T>
Array<T>::Array(size_t count, const T& other) : arr_(new T[1]), size_(0), capacity_(1) {
    for (size_t i = 0; i < count; ++i)  {
        push_back(other);
    }
}

template <typename T>
Array<T>::~Array() {
    delete[] arr_;
}

template <typename T>
Array<T>::Array(const Array& other) : arr_(new T[1]), size_(0), capacity_(1) { 
    for (size_t i = 0; i < other.size_; ++i)  {
        push_back(other[i]);
    }
}

template <typename T>
Array<T>& Array<T>::operator=(const Array& other)    {
    if (this != &other) {
        for (size_t i = 0; i < other.size_; ++i)  {
            push_back(other[i]);
        }
    }
    return *this;
}

template <typename T>
Array<T>::Array(Array<T>&& other) noexcept : arr_(other.arr_), size_(other.size_), capacity_(other.capacity_)  {
    other.arr_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

template <typename T>
Array<T>& Array<T>::operator=(Array<T>&& other) noexcept  {
    if (this != &other) {
        delete[] arr_;
        arr_ = other.arr_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.arr_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

template <typename T>
T& Array<T>::operator[](size_t index)   {
    if (index >= size_) {
        throw std::out_of_range("Index out of bounds");
    }
    return arr_[index]; // ptrs have built-in [] op
}


template <typename T>
const T& Array<T>::operator[](size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Index out of bounds");
    }
    return arr_[index];
}


template <typename T>
void Array<T>::push_back(const T& input)   {
    if (capacity_ == size_) {
        capacity_ ? capacity_ *= 2 : capacity_ += 1; // IMPORTANT: handles moved-from arrs
        auto temp = new T[capacity_];
        // O(n) copying is inevitable for resizing and move semantics cannot be use to optimize: NO auto temp = std::move(*this)
        // as resizing is essentially allocing new mem space and we don't want to transfer ownership of old mem space which has no effect at all.
        for (size_t i = 0; i < size_; ++i)  {
            temp[i] = std::move(arr_[i]); // However one could use std::move here to optimize copying of individual arr elem
            // note that arr elements could be nontrivial objs as well
            // compiler copy elison will NOT come into effect here as the RHS is not a rvalue
        }
        delete[] arr_;
        arr_ = temp;
    }
    arr_[size_] = input;
    size_++;
}


template <typename T>
void Array<T>::push_back(T&& input)   { // rvalue overload
    if (capacity_ == size_) {
        capacity_ *= 2;
        auto temp = new T[capacity_];
        // O(n) copying is inevitable for resizing and move semantics cannot be use to optimize: NO auto temp = std::move(*this)
        // as resizing is essentially allocing new mem space and we don't want to transfer ownership of old mem space which has no effect at all.
        for (size_t i = 0; i < size_; ++i)  {
            temp[i] = std::move(arr_[i]); // However one could use std::move here to optimize copying of individual arr elem
            // note that arr elements could be nontrivial objs as well
            // compiler copy elison will NOT come into effect here as the RHS is not a rvalue
        }
        delete[] arr_;
        arr_ = temp;
    }
    arr_[size_] = std::move(input);
    size_++;
}

template <typename T>
template <typename... Args>
void Array<T>::emplace_back(Args&&... args) {
    if (capacity_ == size_) {
        capacity_ ? capacity_ *= 2 : capacity_ += 1;
        auto temp = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            temp[i] = std::move(arr_[i]); // Move existing elements
        }
        delete[] arr_;
        arr_ = temp;
    }
    // Construct the new element in-place using perfect forwarding
    new (&arr_[size_]) T(std::forward<Args>(args)...);
    size_++;
}


template <typename T>
void Array<T>::remove(size_t index)   {
    auto iter = this->begin() + index;
    // left shift the part after removed index
    for (auto it = iter; (it + 1) != this->end(); ++it)    { // Note the loop termination condition
        *it = *(it + 1); // last elem is unchanged yet will go obsolete
    }
    size_--;
}

template <typename T>
void Array<T>::resize(size_t new_size, const T& filler)   {
    if (new_size == size_) return;
    if (new_size < size_) {
        size_ = new_size;
        return;
    }
    
    for (size_t i = size_; i < new_size; ++i)  {
        push_back(filler);
    }

    // A heap buffer overflow occurs when a program writes data beyond the bounds of allocated heap memory.
}

template <typename T>
void Array<T>::reserve(size_t new_capacity)   {
    if (new_capacity <= capacity_) return;

    auto temp = new T[new_capacity]; // this is not exception safe, so it goes first
    
    for (size_t i = 0; i < size_; ++i)  {
        temp[i] = std::move(arr_[i]);
    }

    delete[] arr_;

    capacity_ = new_capacity;
    arr_ = temp;
}


template <typename T>
size_t Array<T>::size() const   {
    return size_;
}

template <typename T>
size_t Array<T>::capacity() const   {
    return capacity_;
}


template <typename T>
typename Array<T>::iterator Array<T>::begin()  {
    return Array<T>::iterator(arr_);
}

template <typename T>
typename Array<T>::iterator Array<T>::end()  {
    return Array<T>::iterator(arr_ + size_);
}


template <typename T>
const typename Array<T>::iterator Array<T>::begin() const  {
    return Array<T>::iterator(arr_);
}

template <typename T>
const typename Array<T>::iterator Array<T>::end() const  {
    return Array<T>::iterator(arr_ + size_);
}


template <typename T>
Array<T>::iterator::iterator(T* ptr_in) : ptr_(ptr_in)  {}

template <typename T>
typename Array<T>::iterator& Array<T>::iterator::operator++()   {
    ++(this->ptr_); // ptrs have built-in ++ and + op
    return *this; // for void func this line is omitted; yet one wants to enable the use *(it++)
                  // so we let the func return the modified obj which is simply *this.
}

template <typename T>
typename Array<T>::iterator& Array<T>::iterator::operator--()   {
    --(this->ptr_);
    return *this;
}

template <typename T>
typename Array<T>::iterator Array<T>::iterator::operator+(size_t incr) const {
    return Array<T>::iterator((this->ptr_) + incr);
}


template <typename T>
typename Array<T>::iterator::reference Array<T>::iterator::operator*() const  {
    return *(this->ptr_);
}


template <typename T>
bool Array<T>::iterator::operator==(iterator rhs) const  {
    return this->ptr_ == rhs.ptr_;
}

template <typename T>
bool Array<T>::iterator::operator!=(iterator rhs) const  {
    return this->ptr_ != rhs.ptr_;
}


#endif // __ARRAY_ARRAY_HPP