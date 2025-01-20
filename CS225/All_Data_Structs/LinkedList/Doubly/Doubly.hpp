#ifndef __LINKEDLIST_Doubly_Doubly_HPP
#define __LINKEDLIST_Doubly_Doubly_HPP
#include <stdexcept>

namespace DoublyNode    {
    template <typename T>
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node(T value) : data(value), next(nullptr), prev(nullptr) {}
        
        Node* Walk_To(int index)  {
            Node* current = this;
            try
            {
                while (index < 0)   {
                    current = current->prev;
                    ++index;
                }
                while (index > 0)   {
                    current = current->next;
                    --index;
                }
                return current; // Safer to return a value than modifying *this
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << " index out of bounds" << '\n';
            }
            
        }
    };
}

template <typename T>
class DoublyLinkedList {
public:
    class iterator  {
    public:
        using Node = DoublyNode::Node;
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

        friend class DoublyLinkedList; // for convenient direct access of DoublyLinkedList attributes

    private:
        Node<T>* ptr_;
        // NOT T*! Otherwise would abuse T: T is the data type in this context.
    };

    DoublyLinkedList(); // default constructor: nullptr
    ~DoublyLinkedList();
    DoublyLinkedList(const DoublyLinkedList& other); // copy constructor
    DoublyLinkedList& operator=(const DoublyLinkedList& other); // copy assignment
    DoublyLinkedList(DoublyLinkedList&& other) noexcept; // move constructor
    DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept; // move assignment

    T& operator[](int index) const;

    void Push_back(T input);
    void Insert(int index, T input);
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
void DoublyLinkedList<T>::Clear()    {
    tail_ = nullptr; // back to be set to null to avoid dangling
    while (head_) {
        Node<T>* temp = head_;
        head_ = head_->next;
        delete temp; // if one uses current to traverse and delete, then one has to set head_ to nullptr at the end!
    }
}
    // delete temp frees the mem space used to store the struct -- the data and the ptr head_->next.
    // Note that we do not access any freed mem both in this iteration and next iteration.
    // Explanation: In the next iteration, head_ just holds the value of the old head_->next which is freed.
    // Don't confuse with a reference. if a obj is freed its reference leads to undefined behavior, but not for its copy.
    // iterative approach uses less stack space


template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head_(nullptr), tail_(nullptr) {}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    Clear();
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other) : head_(nullptr), tail_(nullptr) {
    Node<T>* current = other.head_;
    while (current) {
        Push_back(current->data);
        current = current->next;       
    }
} // copy constructor

template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& other)  {
    if (this != &other) { // Note: compare ptr not obj.
        Clear();
        Node<T>* current = other.head_;
        while (current) {
            Push_back(current->data);
            current = current->next;       
        }
    }
    return *this;
} // copy assignment

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList<T>&& other) noexcept : head_(other.head_), tail_(other.tail_) {
    other.head_ = nullptr;
    other.tail_ = nullptr;
}

template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(DoublyLinkedList<T>&& other) noexcept  {
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
T& DoublyLinkedList<T>::operator[](int index)  const  { // O(n) random access
    if (index < 0 || !head_) { // Don't forget the empty list check!
        throw std::out_of_range("Index out of bounds");
    }
    Node<T>* current = head_;
    return (current->Walk_To(index))->data;
}


template <typename T>
void DoublyLinkedList<T>::Push_back(T input)   {
    if (!head_)   {
        head_ = tail_ = new Node(input);
        return;
    }
    tail_->prev = tail_;
    tail_ = tail_->next = new Node(input);
}


template <typename T>
void DoublyLinkedList<T>::Insert(int index, T input)   {
    if (index < 0 || index > GetSize()) {
        throw std::out_of_range("Insert index out of range");
    }
    Node<T>* inserted =  new Node(input);
    if (!head_) {
        head_ = tail_ = inserted;
        return;
    }
    if (!index) {
        inserted->next = head_;
        head_ = inserted;
        return;
    }
    Node<T>* current = head_->Walk_To(index - 1);
    Node<T>* temp = current->next;
    inserted->next = temp;
    inserted->prev = current;
    current->next = inserted;
    if (current == tail_) { // Peculiarly, current == tail_ works but index == GetSize() doesn't!
        tail_->prev = tail_; 
        tail_ = inserted; // insert at tail
    }
}


template <typename T>
T DoublyLinkedList<T>::Pop_Front()  {
    if (head_) {
        Node<T>* to_delete = head_;
        T value = head_->data;
        head_ = head_->next;
        head_ ? head_->prev = nullptr : tail_ = nullptr;
        delete to_delete;
        return value;
    }
    throw std::out_of_range("LinkedList is empty");
} 


template <typename T>
void DoublyLinkedList<T>::Erase(int index)   {
    // left shift the part after erased index
    if (index < 0 || index >= GetSize())    {
        throw std::out_of_range("Index out of bounds");
    }
    if (index == 0)  {
        Node<T>* temp = head_;
        head_ = head_->next;
        head_ ? head_->prev = nullptr : tail_ = nullptr;
        delete temp;
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
        tail_->next = nullptr;
    }
    delete temp;
}


template <typename T>
int DoublyLinkedList<T>::GetSize() const   {
    int size = 0;
    Node<T>* current = head_;
    while (current) {
        ++size;
        current = current->next;       
    }
    return size;
}


template <typename T>
typename DoublyLinkedList<T>::iterator DoublyLinkedList<T>::begin()    const   {
    return DoublyLinkedList<T>::iterator(head_);
}

template <typename T>
typename DoublyLinkedList<T>::iterator DoublyLinkedList<T>::end()   const   {
    return DoublyLinkedList<T>::iterator(nullptr); // one past last
}


template <typename T>
DoublyLinkedList<T>::iterator::iterator(Node<T>* ptr_in) : ptr_(ptr_in)  {}

template <typename T>
typename DoublyLinkedList<T>::iterator& DoublyLinkedList<T>::iterator::operator++()   {
    ptr_ = ptr_->next;
    return *this;
}

template <typename T>
typename DoublyLinkedList<T>::iterator DoublyLinkedList<T>::iterator::operator+(int incr) const  {
    if (incr < 0)   {
        throw std::invalid_argument("Increment must be positive");
    }
    auto ptr_copy = ptr_;
    while (incr > 0)    {
        ptr_copy = ptr_copy->next;
        --incr;
    }
    return DoublyLinkedList<T>::iterator(ptr_copy);
}


template <typename T>
T& DoublyLinkedList<T>::iterator::operator*() const  {
    return ptr_->data;
}


template <typename T>
bool DoublyLinkedList<T>::iterator::operator==(iterator rhs) const  {
    return this->ptr_ == rhs.ptr_;
}

template <typename T>
bool DoublyLinkedList<T>::iterator::operator!=(iterator rhs) const  {
    return this->ptr_ != rhs.ptr_;
}

#endif // __LINKEDLIST_Doubly_Doubly_HPP