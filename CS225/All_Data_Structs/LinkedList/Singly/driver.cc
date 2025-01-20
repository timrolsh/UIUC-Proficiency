#include <iostream>
#include "Singly.hpp"

void TestSinglyLinkedList() {
    // Create a SinglyLinkedList instance
    SinglyLinkedList<int> list;

    // Test Push_back
    std::cout << "Testing Push_back...\n";
    list.Push_back(10);
    list.Push_back(20);
    list.Push_back(30);

    std::cout << "List after Push_back: ";
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // Test operator[] for random access
    std::cout << "Testing operator[]...\n";
    try {
        std::cout << "Element at index 1: " << list[1] << "\n";
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    // Test Insert
    std::cout << "Testing Insert...\n";
    list.Insert(3, 77); // Insert 15 at index 
    std::cout << "List after Insert: ";
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // Test Pop_Front
    std::cout << "Testing Pop_Front...\n";
    int front = list.Pop_Front();
    std::cout << "Popped front: " << front << "\n";
    std::cout << "List after Pop_Front: ";
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // Test Erase
    std::cout << "Testing Erase...\n";
    list.Erase(2); // Remove element at index 
    std::cout << "List after Erase: ";
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // Test GetSize
    std::cout << "Testing GetSize...\n";
    std::cout << "Current size of the list: " << list.GetSize() << "\n";

    // Test Clear
    std::cout << "Testing Clear...\n";
    list.Clear();
    std::cout << "List after Clear: ";
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "(should be empty)\n";

    // Test exception handling
    std::cout << "Testing exception handling for operator[]...\n";
    try {
        std::cout << "Accessing element at index 0: " << list[0] << "\n";
    } catch (const std::out_of_range& e) {
        std::cerr << "Caught exception: " << e.what() << "\n";
    }
}


void test_default_constructor() {
    SinglyLinkedList<int> list;
    std::cout << "Default Constructor: Size = " << list.GetSize() << "\n";
}

void test_copy_constructor() {
    SinglyLinkedList<int> original;
    original.Push_back(1);
    original.Push_back(2);
    original.Push_back(3);

    SinglyLinkedList<int> copy(original);
    std::cout << "Copy Constructor: ";
    for (auto it = copy.begin(); it != copy.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "(Size = " << copy.GetSize() << ")\n";
}

void test_copy_assignment() {
    SinglyLinkedList<int> original;
    original.Push_back(4);
    original.Push_back(5);
    original.Push_back(6);

    SinglyLinkedList<int> copy;
    copy = original;
    std::cout << "Copy Assignment: ";
    for (auto it = copy.begin(); it != copy.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "(Size = " << copy.GetSize() << ")\n";
}

void test_move_constructor() {
    SinglyLinkedList<int> temporary;
    temporary.Push_back(7);
    temporary.Push_back(8);
    temporary.Push_back(9);

    SinglyLinkedList<int> moved(std::move(temporary));
    std::cout << "Move Constructor: ";
    for (auto it = moved.begin(); it != moved.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "(Size = " << moved.GetSize() << ")\n";
}

void test_move_assignment() {
    SinglyLinkedList<int> temporary;
    temporary.Push_back(10);
    temporary.Push_back(11);
    temporary.Push_back(12);

    SinglyLinkedList<int> moved;
    moved = std::move(temporary);
    std::cout << "Move Assignment: ";
    for (auto it = moved.begin(); it != moved.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "(Size = " << moved.GetSize() << ")\n";
}

int main() {
    TestSinglyLinkedList();

    std::cout << "\n" << "Testing Big Five:\n\n";
    test_default_constructor();
    test_copy_constructor();
    test_copy_assignment();
    test_move_constructor();
    test_move_assignment();
    return 0;
}

