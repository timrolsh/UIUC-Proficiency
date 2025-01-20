#ifndef STACK_HPP
#define STACK_HPP
#include <stdexcept>
// LinkedList based Stack
namespace StackNode {
    template <typename T>
    struct Node {
    T data;
    Node* next;

    Node(T value, Node* under) : data(value), next(under) {}
    };
}


template <typename T>
class Stack {
public:
    using Node = typename StackNode::Node<T>; // this will apply to member func implementations outside of class as well!
    class iterator  {
    public:
        iterator(Node* ptr_in);

        /*
        iterator cls should have:
        > ++ increm op
        > + offsetting op
        > * deref op
        > ==, != (in)eq op, for control conditioning
        */

        iterator& operator++(); // return by ref means pre increm
        iterator operator+(int incr) const; // Note that we want it+incr to return a new incr-ed iter but not modify the original

        T& operator*() const; // return by ref :  could modify through iter as *iter = a;

        bool operator==(iterator rhs) const;
        bool operator!=(iterator rhs) const;

        friend class Stack; // for convenient direct access of Stack attributes

    private:
        Node* ptr_;
    };

    Stack(); // default constructor: nullptr
    ~Stack();
    Stack(const Stack& other); // copy constructor
    Stack& operator=(const Stack& other); // copy assignment
    Stack(Stack&& other) noexcept; // move constructor
    Stack& operator=(Stack&& other) noexcept; // move assignment

    void push(T input);
    const T& top() const;
    void pop();
    void Clear();
    bool empty() const;

    int GetSize() const;

    iterator begin()    const;
    iterator end()    const;

private:
    Node* SP_;
    int size_;
};

template <typename T>
bool Stack<T>::empty() const {
    return size_ == 0;
}

template <typename T>
void Stack<T>::Clear()    {
    while (size_ > 0)    {
        pop();
        // Note that pop already decrements size_!
    }
}

template <typename T>
Stack<T>::Stack() : SP_(nullptr), size_(0) {}

template <typename T>
Stack<T>::~Stack() {
    Clear();
}

template <typename T>
Stack<T>::Stack(const Stack<T>& other) : SP_(nullptr), size_(0) {
    Node* current = other.SP_;
    int size = other.size_;
    while (size > 0)   {
        push(current->data);
        current = current->next;
        --size;
    }
    size_ = other.size_;
} // copy constructor

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other)  {
    if (this != &other) {
        Clear();
        Node* current = other.SP_;
        int size = other.size_;
        while (size > 0)   {
            push(current->data);
            current = current->next;
            --size;
        }
        size_ = other.size_;
    }
    return *this;
} // copy assignment

template <typename T>
Stack<T>::Stack(Stack<T>&& other) noexcept : SP_(other.SP_), size_(other.size_) {
    other.SP_ = nullptr;
    other.size_ = 0;
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack<T>&& other) noexcept  {
    if (this != &other) {
        Clear();
        SP_ = other.SP_;
        size_ = other.size_;
        other.SP_ = nullptr;
        other.size_ = 0;
    }
    return *this;
}


template <typename T>
void Stack<T>::push(T input)   {
    ++size_;
    if (SP_ == nullptr) {
        SP_ = new Node(input, nullptr);
        return;
    }
    SP_ = new Node(input, SP_);
}


template <typename T>
const T& Stack<T>::top() const {
    if (SP_) {
        return SP_->data;
    }
    throw std::out_of_range("Stack is empty");
} 


template <typename T>
void Stack<T>::pop()  {
    if (SP_) {
        Node* to_delete = SP_;
        SP_ = SP_->next;
        delete to_delete;
        --size_;
        return;
    }
    throw std::out_of_range("Stack is empty");
} 


template <typename T>
int Stack<T>::GetSize() const   {
    return size_;
}


template <typename T>
typename Stack<T>::iterator Stack<T>::begin()    const   {
    return Stack<T>::iterator(SP_);
}

template <typename T>
typename Stack<T>::iterator Stack<T>::end()    const   {
    return Stack<T>::iterator(nullptr); // one past end so nullptr
}


template <typename T>
Stack<T>::iterator::iterator(Node* ptr_in) : ptr_(ptr_in)  {}

template <typename T>
typename Stack<T>::iterator& Stack<T>::iterator::operator++()   {
    ptr_ = ptr_->next;
    return *this;
}

template <typename T>
typename Stack<T>::iterator Stack<T>::iterator::operator+(int incr) const  {
    if (incr < 0)   {
        throw std::invalid_argument("Increment must be positive");
    }
    auto ptr_copy = ptr_;
    while (incr > 0)    {
        ptr_copy = ptr_copy->next;;
        --incr;
    }
    return Stack<T>::iterator(ptr_copy);
}


template <typename T>
T& Stack<T>::iterator::operator*() const  {
    return ptr_->data;
}


template <typename T>
bool Stack<T>::iterator::operator==(iterator rhs) const  {
    return this->ptr_ == rhs.ptr_;
}

template <typename T>
bool Stack<T>::iterator::operator!=(iterator rhs) const  {
    return this->ptr_ != rhs.ptr_;
}

#endif