#include <iostream>
#include <cassert>
#include <string>
#include "Doubly.hpp"

template <typename T>
void printList(const DoublyLinkedList<T>& list, const std::string& label) {
    std::cout << label << " (size=" << list.GetSize() << "): ";
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void testBigFive() {
    std::cout << "\n=== Testing Big Five ===" << std::endl;
    
    // Test Constructor
    std::cout << "\nTesting Default Constructor" << std::endl;
    DoublyLinkedList<int> list1;
    assert(list1.GetSize() == 0);
    std::cout << "Default constructor passed" << std::endl;

    // Populate list1
    list1.Push_back(1);
    list1.Push_back(2);
    list1.Push_back(3);
    printList(list1, "Original list");

    // Test Copy Constructor
    std::cout << "\nTesting Copy Constructor" << std::endl;
    DoublyLinkedList<int> list2(list1);
    printList(list2, "Copied list");
    assert(list2.GetSize() == list1.GetSize());
    for (int i = 0; i < list1.GetSize(); ++i) {
        assert(list1[i] == list2[i]);
    }
    std::cout << "Copy constructor passed" << std::endl;

    // Test Copy Assignment
    std::cout << "\nTesting Copy Assignment" << std::endl;
    DoublyLinkedList<int> list3;
    list3 = list1;
    printList(list3, "Copy assigned list");
    assert(list3.GetSize() == list1.GetSize());
    for (int i = 0; i < list1.GetSize(); ++i) {
        assert(list1[i] == list3[i]);
    }
    std::cout << "Copy assignment passed" << std::endl;

    // Test Move Constructor
    std::cout << "\nTesting Move Constructor" << std::endl;
    DoublyLinkedList<int> list4(std::move(list2));
    printList(list4, "Move constructed list");
    printList(list2, "Original list after move");
    assert(list2.GetSize() == 0); // Original should be empty after move
    std::cout << "Move constructor passed" << std::endl;

    // Test Move Assignment
    std::cout << "\nTesting Move Assignment" << std::endl;
    DoublyLinkedList<int> list5;
    list5 = std::move(list3);
    printList(list5, "Move assigned list");
    printList(list3, "Original list after move assignment");
    assert(list3.GetSize() == 0); // Original should be empty after move
    std::cout << "Move assignment passed" << std::endl;
}

void testBasicOperations() {
    std::cout << "\n=== Testing Basic Operations ===" << std::endl;
    
    DoublyLinkedList<int> list;
    
    // Test Push_back
    std::cout << "\nTesting Push_back" << std::endl;
    list.Push_back(10);
    list.Push_back(20);
    list.Push_back(30);
    printList(list, "After Push_back");
    assert(list.GetSize() == 3);
    assert(list[0] == 10);
    assert(list[2] == 30);
    
    // Test Insert
    std::cout << "\nTesting Insert" << std::endl;
    list.Insert(1, 15);
    printList(list, "After Insert");
    assert(list.GetSize() == 4);
    assert(list[1] == 15);
    
    // Test Pop_Front
    std::cout << "\nTesting Pop_Front" << std::endl;
    int popped = list.Pop_Front();
    printList(list, "After Pop_Front");
    assert(popped == 10);
    assert(list.GetSize() == 3);
    
    // Test Erase
    std::cout << "\nTesting Erase" << std::endl;
    list.Erase(1);
    printList(list, "After Erase");
    assert(list.GetSize() == 2);
    
    // Test Clear
    std::cout << "\nTesting Clear" << std::endl;
    list.Clear();
    printList(list, "After Clear");
    assert(list.GetSize() == 0);
}

void testIterator() {
    std::cout << "\n=== Testing Iterator ===" << std::endl;
    
    DoublyLinkedList<int> list;
    for (int i = 0; i < 5; ++i) {
        list.Push_back(i * 10);
    }
    
    std::cout << "Forward iteration: ";
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Test iterator arithmetic
    std::cout << "Testing iterator + operator" << std::endl;
    auto it = list.begin();
    auto it2 = it + 2;
    assert(*it2 == 20);
    std::cout << "Iterator arithmetic passed" << std::endl;
}

void testEdgeCases() {
    std::cout << "\n=== Testing Edge Cases ===" << std::endl;
    
    DoublyLinkedList<int> list;
    
    // Test operations on empty list
    std::cout << "Testing operations on empty list" << std::endl;
    try {
        list.Pop_Front();
        assert(false); // Should not reach here
    } catch (const std::out_of_range& e) {
        std::cout << "Expected exception caught: " << e.what() << std::endl;
    }
    
    // Test invalid index access
    try {
        list.Insert(-1, 10);
        assert(false); // Should not reach here
    } catch (const std::out_of_range& e) {
        std::cout << "Expected exception caught: " << e.what() << std::endl;
    }
}

// Helper function to print list backwards using Walk_To
template <typename T>
void printListBackward(const DoublyLinkedList<T>& list, const std::string& label) {
    std::cout << label << " (size=" << list.GetSize() << ") backwards: ";
    if (list.GetSize() == 0) {
        std::cout << "[empty list]";
    } else {
        for (int i = list.GetSize() - 1; i >= 0; --i) {
            std::cout << list[i] << " ";
        }
    }
    std::cout << std::endl;
}

void testBackwardTraversal() {
    std::cout << "\n=== Testing Backward Traversal ===" << std::endl;
    
    DoublyLinkedList<int> list;
    
    // Test with empty list
    std::cout << "\nTesting empty list:" << std::endl;
    printListBackward(list, "Empty list");
    
    // Test with single element
    std::cout << "\nTesting single element:" << std::endl;
    list.Push_back(42);
    printList(list, "Forward");
    printListBackward(list, "Backward");
    
    // Test with multiple elements
    std::cout << "\nTesting multiple elements:" << std::endl;
    list.Push_back(43);
    list.Push_back(44);
    list.Push_back(45);
    printList(list, "Forward");
    printListBackward(list, "Backward");
    
    // Test Walk_To with negative indices
    std::cout << "\nTesting Walk_To with negative indices:" << std::endl;
    try {
        // Testing walking backwards from middle
        int mid_idx = list.GetSize() / 2;
        std::cout << "Walking backwards from index " << mid_idx << ": ";
        for (int i = 0; i <= mid_idx; ++i) {
            std::cout << list[mid_idx - i] << " ";
        }
        std::cout << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    // Test after modifications
    std::cout << "\nTesting after modifications:" << std::endl;
    list.Insert(2, 100);  // Insert in middle
    printList(list, "After insert in middle - Forward");
    printListBackward(list, "After insert in middle - Backward");
    
    list.Erase(2);  // Remove from middle
    printList(list, "After remove from middle - Forward");
    printListBackward(list, "After remove from middle - Backward");
    
    // Test edge cases
    std::cout << "\nTesting edge cases:" << std::endl;
    
    // Remove all but one element
    while (list.GetSize() > 1) {
        list.Pop_Front();
    }
    printList(list, "Single element - Forward");
    printListBackward(list, "Single element - Backward");
    
    // Remove last element
    list.Pop_Front();
    printList(list, "Empty again - Forward");
    printListBackward(list, "Empty again - Backward");
    
    // Test prev pointers after multiple operations
    std::cout << "\nTesting complex operations:" << std::endl;
    list.Push_back(1);
    list.Push_back(2);
    list.Push_back(3);
    list.Insert(1, 4);
    list.Pop_Front();
    list.Erase(1);
    printList(list, "After complex operations - Forward");
    printListBackward(list, "After complex operations - Backward");
}

int main() {
    try {
        testBigFive();
        testBasicOperations();
        testIterator();
        testEdgeCases();
        testBackwardTraversal();
        
        std::cout << "\nAll tests passed successfully!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}