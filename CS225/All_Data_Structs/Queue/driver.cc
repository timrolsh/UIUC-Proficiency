#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <stdexcept>
#include "Queue.hpp"

void printTestResult(const std::string& testName, bool passed) {
    std::cout << testName << ": " << (passed ? "PASSED" : "FAILED") << std::endl;
}

// Template function to compare queue contents with a vector
template<typename T>
bool compareQueueWithVector(Queue<T>& queue, const std::vector<T>& vec) {
    if (queue.size() != vec.size()) return false;
    
    Queue<T> temp = queue;  // Create a copy to not modify original
    for (const T& item : vec) {
        if (temp.Empty() || temp.front() != item) return false;
        temp.Pop();
    }
    return temp.Empty();
}

int main() {
    try {
        // Test 1: Basic Operations
        {
            Queue<int> queue;
            printTestResult("Initial Empty Check", queue.Empty());
            printTestResult("Initial Size Check", queue.size() == 0);

            // Test Push and front
            queue.Push(1);
            printTestResult("Push Single Element", queue.size() == 1 && queue.front() == 1);
            printTestResult("Not Empty After Push", !queue.Empty());

            // Test Pop
            queue.Pop();
            printTestResult("Empty After Pop", queue.Empty());
            printTestResult("Size After Pop", queue.size() == 0);
        }

        // Test 2: FIFO Order Verification
        {
            Queue<int> queue;
            std::vector<int> numbers = {1, 2, 3, 4, 5};
            
            // Push all numbers
            for (int num : numbers) {
                queue.Push(num);
            }
            
            // Verify FIFO order
            bool orderCorrect = true;
            for (int expected : numbers) {
                if (queue.front() != expected) {
                    orderCorrect = false;
                    break;
                }
                queue.Pop();
            }
            
            printTestResult("FIFO Order", orderCorrect);
            printTestResult("Empty After All Pops", queue.Empty());
        }

        // Test 3: Complex Operations
        {
            Queue<std::string> queue;
            std::vector<std::string> items = {"first", "second", "third"};
            
            // Push items
            for (const auto& item : items) {
                queue.Push(item);
            }
            
            // Mixed operations
            printTestResult("Initial Size", queue.size() == 3);
            printTestResult("Front Check", queue.front() == "first");
            
            queue.Pop();
            queue.Push("fourth");
            
            std::vector<std::string> expected = {"second", "third", "fourth"};
            printTestResult("Complex Operations", compareQueueWithVector(queue, expected));
        }

        // Test 4: Edge Cases
        {
            Queue<int> queue;
            
            // Test Empty queue operations
            bool EmptyQueueException = false;
            try {
                queue.front();
            } catch (const std::out_of_range&) {
                EmptyQueueException = true;
            }
            printTestResult("Front on Empty Queue Exception", EmptyQueueException);
            
            EmptyQueueException = false;
            try {
                queue.Pop();
            } catch (const std::out_of_range&) {
                EmptyQueueException = true;
            }
            printTestResult("Pop on Empty Queue Exception", EmptyQueueException);

            // Test large number of operations
            for (int i = 0; i < 1000; ++i) {
                queue.Push(i);
            }
            printTestResult("Large Push Size Check", queue.size() == 1000);
            
            for (int i = 0; i < 500; ++i) {
                queue.Pop();
            }
            printTestResult("Partial Pop Size Check", queue.size() == 500);
            printTestResult("Front After Partial Pop", queue.front() == 500);
        }

        // Test 5: Copy Operations
        {
            Queue<int> original;
            for (int i = 0; i < 5; ++i) {
                original.Push(i);
            }
            
            // Test copy constructor
            Queue<int> copied(original);
            printTestResult("Copy Constructor - Size", copied.size() == original.size());
            printTestResult("Copy Constructor - Content", 
                          compareQueueWithVector(copied, {0, 1, 2, 3, 4}));
            
            // Test assignment operator
            Queue<int> assigned;
            assigned = original;
            printTestResult("Assignment Operator - Size", assigned.size() == original.size());
            printTestResult("Assignment Operator - Content", 
                          compareQueueWithVector(assigned, {0, 1, 2, 3, 4}));
            
            // Modify copy and verify original is unchanged
            copied.Pop();
            copied.Push(100);
            printTestResult("Original Unchanged After Copy Modification", 
                          compareQueueWithVector(original, {0, 1, 2, 3, 4}));
        }

        // Test 6: Stress Test
        {
            Queue<int> queue;
            const int NUM_OPERATIONS = 10000;
            
            // Alternating Push and Pop
            for (int i = 0; i < NUM_OPERATIONS; ++i) {
                queue.Push(i);
                if (i % 2 == 0) {
                    queue.Pop();
                }
            }
            
            size_t expectedSize = NUM_OPERATIONS - (NUM_OPERATIONS / 2);
            printTestResult("Stress Test - Final Size", queue.size() == expectedSize);
            printTestResult("Stress Test - Front Value", queue.front() == (NUM_OPERATIONS / 2));
        }

        std::cout << "\nAll Queue tests completed!" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Unexpected test failure: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
