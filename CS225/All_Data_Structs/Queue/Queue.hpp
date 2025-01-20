#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <stdexcept>
// LinkedList based Queue
namespace QueueNode {
    template <typename T>
    struct Node {
        T data;
        Node* next;

        Node(T value, Node* under) : data(value), next(under) {}
    };
}



template <typename T>
class Queue {
public:
    using Node = typename QueueNode::Node<T>;
    class iterator  {
    public:
        using Node = typename QueueNode::Node<T>;
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

        friend class Queue; // for convenient direct access of Queue attributes

    private:
        Node* ptr_;
    };

    Queue(); // default constructor: nullptr
    ~Queue();
    Queue(const Queue& other); // copy constructor
    Queue& operator=(const Queue& other); // copy assignment
    Queue(Queue&& other) noexcept; // move constructor
    Queue& operator=(Queue&& other) noexcept; // move assignment

    void push(T input);
    const T& front() const;
    void pop();
    void Clear();
    bool empty() const;

    size_t size() const;

    iterator begin()    const;
    iterator end()    const;

private:
    Node* front_;
    size_t size_;
};

template <typename T>
bool Queue<T>::empty() const {
    return size_ == 0;
}

template <typename T>
void Queue<T>::Clear()    {
    while (size_ > 0)    {
        pop();
        // Note that pop already decrements size_!
    }
}

template <typename T>
Queue<T>::Queue() : front_(nullptr), size_(0) {}

template <typename T>
Queue<T>::~Queue() {
    Clear();
}

template <typename T>
Queue<T>::Queue(const Queue<T>& other) : front_(nullptr), size_(0) {
    Node* current = other.front_;
    size_t size = other.size_;
    while (size > 0)   {
        push(current->data);
        current = current->next;
        --size;
    }
    size_ = other.size_;
} // copy constructor

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other)  {
    if (this != &other) {
        Clear();
        Node* current = other.front_;
        size_t size = other.size_;
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
Queue<T>::Queue(Queue<T>&& other) noexcept : front_(other.front_), size_(other.size_) {
    other.front_ = nullptr;
    other.size_ = 0;
}

template <typename T>
Queue<T>& Queue<T>::operator=(Queue<T>&& other) noexcept  {
    if (this != &other) {
        Clear();
        front_ = other.front_;
        size_ = other.size_;
        other.front_ = nullptr;
        other.size_ = 0;
    }
    return *this;
}


template <typename T>
void Queue<T>::push(T input)   {
    ++size_;
    if (front_ == nullptr) {
        front_ = new Node(input, nullptr);
        return;
    }
    Node* current = front_;
    while (current->next)   {
        current = current->next;
    }
    current->next = new Node(input, nullptr);
    /*
    When we write Node(input, nullptr) without the explicit Node as new Node(input, nullptr),
    the compiler doesn't know that nullptr should be treated as which Node<specifictype>*.
    By specifying Node, when you use new Node(input, nullptr), the compiler has a clear place (T) to "pass" the type information
    after the compiler process the first arg input, e.g. it's an int,
    the entire constructor call becomes: new Node<int>(input, nullptr);
    The compiler can now treat nullptr as a pointer to Node<int>.
    */
}


template <typename T>
const T& Queue<T>::front() const {
    if (front_) {
        return front_->data;
    }
    throw std::out_of_range("Queue is empty");
} 


template <typename T>
void Queue<T>::pop()  {
    if (front_) {
        Node* to_delete = front_;
        front_ = front_->next;
        delete to_delete;
        --size_;
        return;
    }
    throw std::out_of_range("Queue is empty");
} 


template <typename T>
size_t Queue<T>::size() const   {
    return size_;
}


template <typename T>
typename Queue<T>::iterator Queue<T>::begin()    const   {
    return Queue<T>::iterator(front_);
}

template <typename T>
typename Queue<T>::iterator Queue<T>::end()    const   {
    return Queue<T>::iterator(nullptr); // one past end so nullptr
}


template <typename T>
Queue<T>::iterator::iterator(Node* ptr_in) : ptr_(ptr_in)  {}

template <typename T>
typename Queue<T>::iterator& Queue<T>::iterator::operator++()   {
    ptr_ = ptr_->next;
    return *this;
}

template <typename T>
typename Queue<T>::iterator Queue<T>::iterator::operator+(int incr) const  {
    if (incr < 0)   {
        throw std::invalid_argument("Increment must be positive");
    }
    auto ptr_copy = ptr_;
    while (incr > 0)    {
        ptr_copy = ptr_copy->next;;
        --incr;
    }
    return Queue<T>::iterator(ptr_copy);
}


template <typename T>
T& Queue<T>::iterator::operator*() const  {
    return ptr_->data;
}


template <typename T>
bool Queue<T>::iterator::operator==(iterator rhs) const  {
    return this->ptr_ == rhs.ptr_;
}

template <typename T>
bool Queue<T>::iterator::operator!=(iterator rhs) const  {
    return this->ptr_ != rhs.ptr_;
}

#endif
