#ifndef __LINKEDLIST_SINGLY_SINGLY_HPP
#define __LINKEDLIST_SINGLY_SINGLY_HPP
#include <stdexcept>

namespace SinglyNode    {
    template <typename T>
    struct Node {
        T data;
        Node* next;

        Node(T value) : data(value), next(nullptr) {}
        
        Node* Walk_To(int index)  {
            if (index < 0) {
                throw std::out_of_range("Index out of bounds");
            }
            Node* current = this;
            while (index > 0)   {
                current = current->next;
                --index;
            }
            return current; // Safer to return a value than modifying *this
        }
    };
}


template <typename T>
class SinglyLinkedList {
public:
    class iterator  {
    public:
        using Node = SinglyNode::Node;
        iterator(Node<T>* ptr_in);

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

        friend class SinglyLinkedList; // for convenient direct access of SinglyLinkedList attributes

    private:
        Node<T>* ptr_;
        // NOT T*! Otherwise would abuse T: T is the data type in this context.
    };

    SinglyLinkedList(); // default constructor: nullptr
    ~SinglyLinkedList();
    SinglyLinkedList(const SinglyLinkedList& other); // copy constructor
    SinglyLinkedList& operator=(const SinglyLinkedList& other); // copy assignment
    SinglyLinkedList(SinglyLinkedList&& other) noexcept; // move constructor
    SinglyLinkedList& operator=(SinglyLinkedList&& other) noexcept; // move assignment

    T& operator[](int index) const;

    void Push_back(T input);
    void Insert(int index, T input);
    T Pop_Front(); 
    void Erase(int index); // rm elem @ iter
    void Clear();

    int GetSize() const;

    iterator begin()    const;
    iterator end()    const;

private:
    Node<T>* head_;
    Node<T>* tail_; // points to last Node, not null
};


template <typename T>
void SinglyLinkedList<T>::Clear()    {
    tail_ = nullptr; // back to be set to null to avoid dangling
    while (head_)  {
        Node<T>* temp = head_;
        head_ = head_->next;
        delete temp; // frees the mem space used to store the struct -- the data and the ptr head_->next.
        // Note that we do not access any freed mem both in this iteration and next iteration.
        // Explanation: In the next iteration, head_ just holds the value of the old head_->next which is deleted.
        // Don't confuse with a reference. if a obj is freed its reference leads to undefined behavior, but not for its copy.
    } // iterative approach uses less stack space
}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList() : head_(nullptr), tail_(nullptr) {}

template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    Clear();
}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T>& other) : head_(nullptr), tail_(nullptr) {
    Node<T>* current = other.head_;
    while (current != nullptr)   {
        Push_back(current->data);
        current = current->next;
    }
} // copy constructor

template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(const SinglyLinkedList<T>& other)  {
    if (this != &other) {
        Clear();
        Node<T>* current = other.head_;
        while (current != nullptr)   {
            Push_back(current->data);
            current = current->next;
        }
    }
    return *this;
} // copy assignment

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(SinglyLinkedList<T>&& other) noexcept : head_(other.head_), tail_(other.tail_) {
    other.head_ = nullptr;
    other.tail_ = nullptr;
}

template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(SinglyLinkedList<T>&& other) noexcept  {
    if (this != &other) {
        Clear();
        head_ = other.head_;
        tail_ = other.tail_;
        other.head_ = nullptr;
        other.tail_ = nullptr;
    }
    return *this;
}

template <typename T>
T& SinglyLinkedList<T>::operator[](int index)  const  { // O(n) random access
    if (index < 0 || !head_) { // Don't forget the empty list check!
        throw std::out_of_range("Index out of bounds");
    }
    Node<T>* current = head_;
    return (current->Walk_To(index))->data;
}


template <typename T>
void SinglyLinkedList<T>::Push_back(T input)   {
    head_ == nullptr ? head_ = tail_ = new Node(input) : tail_ = tail_->next = new Node(input);
    // Note that cpp chained assignment evaluates from right to left. 
}


template <typename T>
void SinglyLinkedList<T>::Insert(int index, T input)   {
    if (index < 0 || index > GetSize()) {
        throw std::out_of_range("Insert index out of range");
    }
    Node<T>* inserted =  new Node(input);
    if (!head_) head_ = tail_ = inserted;
    Node<T>* current = head_;
    if (!index) {
        inserted->next = head_;
        head_ = inserted;
        return;
    }
    current = current->Walk_To(index - 1);
    Node<T>* temp = current->next;
    inserted->next = temp;
    current->next = inserted;
    if (index == GetSize()) {
        tail_ = inserted; // insert at tail

    }
}


template <typename T>
T SinglyLinkedList<T>::Pop_Front()  {
    if (head_) {
        Node<T>* to_delete = head_;
        T value = head_->data;
        head_ = head_->next;
        delete to_delete;
        return value;
    }
    throw std::out_of_range("LinkedList is empty");
} 


template <typename T>
void SinglyLinkedList<T>::Erase(int index)   {
    // left shift the part after erased index
    if (index < 0 || index >= GetSize())    {
        throw std::out_of_range("Index out of bounds");
    }
    if (index == 0)  {
        Node<T>* temp = head_;
        head_ = head_->next;
        delete temp;
        if (!head_) {// list now empty
            tail_ = nullptr;
        }
        return;
    }
    Node<T>* current = head_;
    // Note: Although current is a shallow copy of head_ and one doesn't affect the other,
    // what they point to is the same and will be affected from either side.
    // Schematic: current -> next <- head_, can modify next through either current->next or head_->next
    // Alternatively one could modify head_ directly while keeping a saved head_.
    current = current->Walk_To(index - 1);
    Node<T>* temp = current->next;
    if (temp->next)  {
        current->next = temp->next;
    }   else    { // erasing tail
        tail_ = current;
        tail_->next = nullptr; // If doesn't set next to null, then upon traversal
                              // iterator will go out of range if end() is set to nullptr.
    }
    delete temp;
}


template <typename T>
int SinglyLinkedList<T>::GetSize() const   {
    int size = 0;
    Node<T>* current = head_;
    while (current)    {
        ++size;
        current = current->next;
    }
    return size;
}


template <typename T>
typename SinglyLinkedList<T>::iterator SinglyLinkedList<T>::begin()    const   {
    return SinglyLinkedList<T>::iterator(head_);
}

template <typename T>
typename SinglyLinkedList<T>::iterator SinglyLinkedList<T>::end()    const   {
    return SinglyLinkedList<T>::iterator(nullptr); // one past end so nullptr not tail_
    /*
    NOTE: IF one wish to use tail->next, then extra handling for empty list is needed or deref nullptr:

    if (!tail_) {  // if list is empty
        return iterator(nullptr);
    }
    return iterator(tail_->next);
    */
}


template <typename T>
SinglyLinkedList<T>::iterator::iterator(Node<T>* ptr_in) : ptr_(ptr_in)  {}

template <typename T>
typename SinglyLinkedList<T>::iterator& SinglyLinkedList<T>::iterator::operator++()   {
    ptr_ = ptr_->next;
    return *this;
}

template <typename T>
typename SinglyLinkedList<T>::iterator SinglyLinkedList<T>::iterator::operator+(int incr) const  {
    if (incr < 0)   {
        throw std::invalid_argument("Increment must be positive");
    }
    auto ptr_copy = ptr_;
    while (incr > 0)    {
        ptr_copy = ptr_copy->next;;
        --incr;
    }
    return SinglyLinkedList<T>::iterator(ptr_copy);
}


template <typename T>
T& SinglyLinkedList<T>::iterator::operator*() const  {
    return ptr_->data;
}


template <typename T>
bool SinglyLinkedList<T>::iterator::operator==(iterator rhs) const  {
    return this->ptr_ == rhs.ptr_;
}

template <typename T>
bool SinglyLinkedList<T>::iterator::operator!=(iterator rhs) const  {
    return this->ptr_ != rhs.ptr_;
}

#endif // __LINKEDLIST_SINGLY_SINGLY_HPP