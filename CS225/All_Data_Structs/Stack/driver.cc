#include "Stack.hpp"
#include <iostream>
#include <string>
#include <cassert>

// Utility function to print a stack's contents
template<typename T>
void printStack(const Stack<T>& s, const std::string& label) {
    std::cout << label << " (size " << s.GetSize() << "): ";
    for (auto it = s.begin(); it != s.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void testDefaultConstructor() {
    std::cout << "\n=== Testing Default Constructor ===\n";
    Stack<int> s;
    assert(s.GetSize() == 0);
    std::cout << "Default constructor test passed!\n";
}

void testPushAndTop() {
    std::cout << "\n=== Testing Push and Top Operations ===\n";
    Stack<int> s;
    
    s.push(1);
    assert(s.GetSize() == 1);
    assert(s.top() == 1);
    
    s.push(2);
    assert(s.GetSize() == 2);
    assert(s.top() == 2);
    
    s.push(3);
    assert(s.GetSize() == 3);
    assert(s.top() == 3);
    
    printStack(s, "Stack after pushes");
    std::cout << "Push and Top operations test passed!\n";
}

void testPop() {
    std::cout << "\n=== Testing Pop Operation ===\n";
    Stack<int> s;
    
    s.push(1);
    s.push(2);
    s.push(3);
    
    printStack(s, "Before pop");
    s.pop();
    assert(s.GetSize() == 2);
    assert(s.top() == 2);
    
    printStack(s, "After pop");
    std::cout << "Pop operation test passed!\n";
}

void testCopyConstructor() {
    std::cout << "\n=== Testing Copy Constructor ===\n";
    Stack<int> s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);
    
    Stack<int> s2(s1);  // Copy constructor
    
    printStack(s1, "Original stack");
    printStack(s2, "Copied stack");
    
    assert(s1.GetSize() == s2.GetSize());
    
    // Verify deep copy by modifying original
    s1.pop();
    assert(s2.GetSize() == 3);  // s2 should be unchanged
    
    std::cout << "Copy constructor test passed!\n";
}

void testCopyAssignment() {
    std::cout << "\n=== Testing Copy Assignment ===\n";
    Stack<int> s1;
    s1.push(1);
    s1.push(2);
    
    Stack<int> s2;
    s2.push(5);
    
    printStack(s1, "s1 before assignment");
    printStack(s2, "s2 before assignment");
    
    s2 = s1;  // Copy assignment
    
    printStack(s1, "s1 after assignment");
    printStack(s2, "s2 after assignment");
    
    assert(s1.GetSize() == s2.GetSize());
    std::cout << "Copy assignment test passed!\n";
}

void testMoveConstructor() {
    std::cout << "\n=== Testing Move Constructor ===\n";
    Stack<int> s1;
    s1.push(1);
    s1.push(2);
    
    printStack(s1, "Before move");
    Stack<int> s2(std::move(s1));
    
    assert(s1.GetSize() == 0);  // Original should be empty
    assert(s2.GetSize() == 2);  // New stack should have the elements
    
    printStack(s2, "After move");
    std::cout << "Move constructor test passed!\n";
}

void testMoveAssignment() {
    std::cout << "\n=== Testing Move Assignment ===\n";
    Stack<int> s1;
    s1.push(1);
    s1.push(2);
    
    Stack<int> s2;
    s2.push(5);
    
    printStack(s1, "s1 before move");
    printStack(s2, "s2 before move");
    
    s2 = std::move(s1);
    
    assert(s1.GetSize() == 0);  // Original should be empty
    assert(s2.GetSize() == 2);  // New stack should have the elements
    
    printStack(s2, "s2 after move");
    std::cout << "Move assignment test passed!\n";
}

void testIterator() {
    std::cout << "\n=== Testing Iterator ===\n";
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    
    std::cout << "Forward iteration: ";
    for (auto it = s.begin(); it != s.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    
    // Test iterator arithmetic
    auto it = s.begin();
    auto it2 = it + 2;
    assert(*it2 == 1);
    
    std::cout << "Iterator tests passed!\n";
}

int main() {
    try {
        testDefaultConstructor();
        testPushAndTop();
        testPop();
        testCopyConstructor();
        testCopyAssignment();
        testMoveConstructor();
        testMoveAssignment();
        testIterator();
        
        std::cout << "\nAll tests passed successfully!\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
