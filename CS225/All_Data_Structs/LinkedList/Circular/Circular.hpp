#ifndef __LINKEDLIST_CIRCULAR_CIRCULAR_HPP
#define __LINKEDLIST_CIRCULAR_CIRCULAR_HPP
#include <stdexcept>

template <typename T>
namespace CircularNode  {
    struct Node {
        T data;
        Node<T>* next;

        Node(const T& value) : data(value), next(nullptr) {}
        
        Node* Walk_To(int index)  {
            if (index < 0) {
                throw std::out_of_range("Index out of bounds");
            }
            Node* current = this;
            while (index > 0)   { // supports any index > 0 walk!
                current = current->next;
                --index;
            }
            return current; // Safer to return a value than modifying *this
        }
    };
}


template <typename T>
class CircularLinkedList {
public:
    class iterator  {
    public:
        using Node = CircularNode::Node;
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

        friend class CircularLinkedList; // for convenient direct access of CircularLinkedList attributes

    private:
        Node<T>* ptr_;
        // NOT T*! Otherwise would abuse T: T is the data type in this context.
    };

    CircularLinkedList(); // default constructor: nullptr
    ~CircularLinkedList();
    CircularLinkedList(const CircularLinkedList& other); // copy constructor
    CircularLinkedList& operator=(const CircularLinkedList& other); // copy assignment
    CircularLinkedList(CircularLinkedList&& other) noexcept; // move constructor
    CircularLinkedList& operator=(CircularLinkedList&& other) noexcept; // move assignment

    T& operator[](int index) const;

    void Push_back(const T& input);
    void Insert(int index, const T& input);
    T Pop_Front(); 
    void Erase(int index);
    void Clear();

    int GetSize() const;
    int GetCapacity() const;

    iterator begin() const;
    iterator end() const;

private:
    Node<T>* head_;
    Node<T>* tail_;
};


template <typename T>
void CircularLinkedList<T>::Clear()    {
    tail_ = nullptr; // back to be set to null to avoid dangling
    Node<T>* current = head_;
    if (head_)  {
        do
        {
            Node<T>* temp = current;
            current = current->next;
            delete temp;
        } while (current != head_);
        head_ = nullptr;
    }
    // frees the mem space used to store the struct -- the data and the ptr head_->next.
    // Note that we do not access any freed mem both in this iteration and next iteration.
    // Explanation: In the next iteration, head_ just holds the value of the old head_->next which is deleted.
    // Don't confuse with a reference. if a obj is freed its reference leads to undefined behavior, but not for its copy.
    // iterative approach uses less stack space
}

template <typename T>
CircularLinkedList<T>::CircularLinkedList() : head_(nullptr), tail_(nullptr) {}

template <typename T>
CircularLinkedList<T>::~CircularLinkedList() {
    Clear();
}

template <typename T>
CircularLinkedList<T>::CircularLinkedList(const CircularLinkedList<T>& other) : head_(nullptr), tail_(nullptr) {
    Node<T>* current = other.head_;
    do
    {
        Push_back(current->data);
        current = current->next;
    }   while(current != other.head_);
} // copy constructor

template <typename T>
CircularLinkedList<T>& CircularLinkedList<T>::operator=(const CircularLinkedList<T>& other)  {
    if (this != &other) { // Note: compare ptr not obj.
        Clear();
        Node<T>* current = other.head_;
        do    
        {
            Push_back(current->data);
            current = current->next;
        }   while(current != other.head_);
    }
    return *this;
} // copy assignment

template <typename T>
CircularLinkedList<T>::CircularLinkedList(CircularLinkedList<T>&& other) noexcept : head_(other.head_), tail_(other.tail_) {
    other.head_ = nullptr;
    other.tail_ = nullptr;
}

template <typename T>
CircularLinkedList<T>& CircularLinkedList<T>::operator=(CircularLinkedList<T>&& other) noexcept  {
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
T& CircularLinkedList<T>::operator[](int index)  const  { // O(n) random access
    if (index < 0 || !head_) { // Don't forget the empty list check!
        throw std::out_of_range("Index out of bounds");
    }
    Node<T>* current = head_;
    return (current->Walk_To(index))->data;
}


template <typename T>
void CircularLinkedList<T>::Push_back(const T& input)   {
    if (!head_)   {
        head_ = tail_ = new Node(input);
        head_->next = tail_->next = head_; 
        return;
    }
    tail_ = tail_->next = new Node(input);
    tail_->next = head_;
}


template <typename T>
void CircularLinkedList<T>::Insert(int index, const T& input)   {
    if (index < 0 || index > GetSize()) {
        throw std::out_of_range("Insert index out of range");
    }
    Node<T>* inserted =  new Node(input);
    if (!head_) {
        head_ = tail_ = inserted;
        head_->next = tail_->next = head_; 
        return;
    }
    if (!index) {
        inserted->next = head_;
        head_ = inserted;
        tail_->next = head_;
        return;
    }
    Node<T>* current = head_->Walk_To(index - 1);
    Node<T>* temp = current->next;
    inserted->next = temp;
    current->next = inserted;
    if (current == tail_) { // Peculiarly, current == tail_ works but index == GetSize() doesn't!
        tail_ = inserted; // insert at tail
        tail_->next = head_;
    }
}


template <typename T>
T CircularLinkedList<T>::Pop_Front()  {
    if (head_) {
        Node<T>* to_delete = head_;
        T value = head_->data;
        head_ == head_->next ? head_ = nullptr : head_ = head_->next; // check if single node left
        !head_ ? tail_ = nullptr : tail_->next = head_;
        delete to_delete;
        return value;
    }
    throw std::out_of_range("LinkedList is empty");
} 


template <typename T>
void CircularLinkedList<T>::Erase(int index)   {
    // left shift the part after erased index
    if (index < 0 || index >= GetSize())    {
        throw std::out_of_range("Index out of bounds");
    }
    if (index == 0)  {
        Node<T>* temp = head_;
        head_ = head_->next;
        tail_->next = head_;
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
    current->next = temp->next; // sewing
    if (temp->next == head_)    { // erasing tail
        tail_ = current;
        tail_->next = head_;
    }
    delete temp;
}


template <typename T>
int CircularLinkedList<T>::GetSize() const   {
    int size = 0;
    Node<T>* current = head_;
    if (current)    {
        do
        {
            ++size;
            current = current->next;
        } while (current != head_);
    }
    return size;
}


template <typename T>
typename CircularLinkedList<T>::iterator CircularLinkedList<T>::begin()    const   {
    return CircularLinkedList<T>::iterator(head_);
}

template <typename T>
typename CircularLinkedList<T>::iterator CircularLinkedList<T>::end()   const   {
    return CircularLinkedList<T>::iterator(head_); // one past last
}


template <typename T>
CircularLinkedList<T>::iterator::iterator(Node<T>* ptr_in) : ptr_(ptr_in)  {}

template <typename T>
typename CircularLinkedList<T>::iterator& CircularLinkedList<T>::iterator::operator++()   {
    ptr_ = ptr_->next;
    return *this;
}

template <typename T>
typename CircularLinkedList<T>::iterator CircularLinkedList<T>::iterator::operator+(int incr) const  {
    if (incr < 0)   {
        throw std::invalid_argument("Increment must be positive");
    }
    auto ptr_copy = ptr_;
    while (incr > 0)    {
        ptr_copy = ptr_copy->next;;
        --incr;
    }
    return CircularLinkedList<T>::iterator(ptr_copy);
}


template <typename T>
T& CircularLinkedList<T>::iterator::operator*() const  {
    return ptr_->data;
}


template <typename T>
bool CircularLinkedList<T>::iterator::operator==(iterator rhs) const  {
    return this->ptr_ == rhs.ptr_;
}

template <typename T>
bool CircularLinkedList<T>::iterator::operator!=(iterator rhs) const  {
    return this->ptr_ != rhs.ptr_;
}

#endif // __LINKEDLIST_CIRCULAR_CIRCULAR_HPP
