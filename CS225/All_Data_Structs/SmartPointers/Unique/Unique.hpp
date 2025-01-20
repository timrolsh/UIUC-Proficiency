#ifndef __SMARTPOINTERS_UNIQUE_UNIQUE_HPP
#define __SMARTPOINTERS_UNIQUE_UNIQUE_HPP
#include <cassert>
#include <stdexcept>

template <typename T>
class MyUniquePtr<T>    {
public:
    
    ~MyUniquePtr()  {delete ptr_;};
    MyUniquePtr(const MyUniquePtr& other) = delete;
    MyUniquePtr& operator=(const MyUniquePtr& other) = delete;
    // delete tells the compiler that the constructor should not be generated, used, or called
    // under any circumstances, otherwise compilation error.
    // No copy construct & assign



private:
    T* ptr_;
    explicit MyUniquePtr(T* ptr) noexcept : ptr_(ptr) {};
    // marking as explicit 
}

#endif // __SMARTPOINTERS_UNIQUE_UNIQUE_HPP