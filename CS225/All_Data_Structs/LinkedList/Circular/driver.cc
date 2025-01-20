#include "Circular.hpp"
#include <iostream>
#include <cassert>
#include <chrono> // For high-resolution clock
using namespace std;

template <typename T>
void PrintList(const CircularLinkedList<T>& list) {
    if (list.GetSize() == 0) {
        cout << "List is empty.\n";
        return;
    }
    auto iter = list.begin();
    do {
        cout << *iter << " ";
        ++iter;
    } while (iter != list.begin());
    cout << endl;
}

int main() {
    // Start measuring time
    auto start_time = std::chrono::high_resolution_clock::now();

    CircularLinkedList<int> list;

    // Test Push_back and PrintList
    cout << "Testing Push_back:\n";
    for (int i = 1; i <= 5; ++i) {
        list.Push_back(i);
    }
    PrintList(list);

    // Test Insert
    cout << "\nTesting Insert:\n";
    list.Insert(0, 0);  // Insert at head
    list.Insert(3, 99); // Insert at middle
    list.Insert(7, 42); // Insert at tail
    PrintList(list);

    // Test Erase
    cout << "\nTesting Erase:\n";
    list.Erase(0);  // Erase head
    list.Erase(2);  // Erase middle
    std::cout << list.GetSize() << endl;
    list.Erase(5);  // Erase tail
    PrintList(list);

    // Test Pop_Front
    cout << "\nTesting Pop_Front:\n";
    while (list.GetSize() > 0) {
        cout << "Popped: " << list.Pop_Front() << endl;
        PrintList(list);
    }

    // Test the big five
    cout << "\nTesting Big Five:\n";
    CircularLinkedList<int> list1;
    for (int i = 1; i <= 3; ++i) {
        list1.Push_back(i);
    }
    PrintList(list1);
    // Copy constructor
    CircularLinkedList<int> list2 = list1;
    cout << "List2 (copy constructor):\n";
    PrintList(list2);

    // Copy assignment
    CircularLinkedList<int> list3;
    list3 = list1;
    cout << "List3 (copy assignment):\n";
    PrintList(list3);

    // Move constructor
    CircularLinkedList<int> list4 = move(list1);
    cout << "List4 (move constructor):\n";
    PrintList(list4);

    // Move assignment
    CircularLinkedList<int> list5;
    list5 = move(list2);
    cout << "List5 (move assignment):\n";
    PrintList(list5);

    // End measuring time
    auto end_time = std::chrono::high_resolution_clock::now();

    // Calculate the duration in milliseconds
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);

    std::cout << "Execution time: " << duration.count() << " ns" << std::endl;

    return 0;
}
