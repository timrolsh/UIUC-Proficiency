#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <algorithm>
#include "Array.hpp"

void printTestResult(const std::string& testName, bool passed) {
    std::cout << testName << ": " << (passed ? "PASSED" : "FAILED") << std::endl;
}

// Helper function to verify vector contents match Array
template<typename T>
bool verifyContents(const Array<T>& arr, const std::vector<T>& expected) {
    if (arr.size() != expected.size()) return false;
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] != expected[i]) return false;
    }
    return true;
}

int main() {
    try {
        // Test 1: Basic Operations
        {
            Array<int> arr;
            printTestResult("Initial Empty Check", arr.empty());
            printTestResult("Initial Size Check", arr.size() == 0);
            printTestResult("Initial Capacity Check", arr.capacity() == 1);

            // Test push_back and size growth
            arr.push_back(1);
            arr.push_back(2);
            arr.push_back(3);

            printTestResult("Size After Insertions", arr.size() == 3);
            printTestResult("Empty After Insertions", !arr.empty());
            printTestResult("Capacity Growth", arr.capacity() >= arr.size());
            
            // Test indexing operator
            printTestResult("Correct Value Retrieved", arr[0] == 1 && arr[1] == 2 && arr[2] == 3);
            
            // Test out of bounds access
            bool exceptionThrown = false;
            try {
                arr[5];
            } catch (const std::out_of_range&) {
                exceptionThrown = true;
            }
            printTestResult("Out of Bounds Exception", exceptionThrown);
        }

        // Test 2: Remove Operation
        {
            Array<std::string> arr;
            arr.push_back("one");
            arr.push_back("two");
            arr.push_back("three");
            arr.push_back("four");

            // Remove from middle
            arr.remove(1);
            std::vector<std::string> expected = {"one", "three", "four"};
            printTestResult("Remove Middle Element", verifyContents(arr, expected));

            // Remove from end
            arr.remove(2);
            expected = {"one", "three"};
            printTestResult("Remove Last Element", verifyContents(arr, expected));

            // Remove from beginning
            arr.remove(0);
            expected = {"three"};
            printTestResult("Remove First Element", verifyContents(arr, expected));
        }

        // Test 3: Resize and Reserve
        {
            Array<int> arr;
            
            // Test resize larger
            arr.resize(5, 42);
            printTestResult("Resize Larger - Size", arr.size() == 5);
            printTestResult("Resize Larger - Value", arr[4] == 42);

            // Test resize smaller
            arr.resize(2);
            printTestResult("Resize Smaller - Size", arr.size() == 2);

            // Test reserve
            size_t oldCapacity = arr.capacity();
            arr.reserve(20);
            printTestResult("Reserve - Capacity Increased", arr.capacity() >= 20);
            printTestResult("Reserve - Size Unchanged", arr.size() == 2);

            // Reserve smaller shouldn't change capacity
            arr.reserve(5);
            printTestResult("Reserve Smaller - Capacity Unchanged", arr.capacity() >= oldCapacity);
        }

        // Test 4: Iterator Operations
        {
            Array<int> arr;
            std::vector<int> values = {1, 2, 3, 4, 5};
            for (int val : values) {
                arr.push_back(val);
            }

            // Test iterator traversal
            std::vector<int> traversed;
            for (const auto& elem : arr) {
                traversed.push_back(elem);
            }
            printTestResult("Iterator Traversal", values == traversed);

            // Test iterator arithmetic
            auto it = arr.begin();
            it = it + 2;
            printTestResult("Iterator Arithmetic", *it == 3);

            // Test iterator comparison
            printTestResult("Iterator Comparison", it != arr.end() && arr.begin() != arr.end());

            // Test const iterator
            const Array<int>& constArr = arr;
            std::vector<int> constTraversed;
            for (const auto& elem : constArr) {
                constTraversed.push_back(elem);
            }
            printTestResult("Const Iterator", values == constTraversed);
        }

        // Test 5: Copy and Move Operations
        {
            Array<std::string> original;
            std::vector<std::string> values = {"one", "two", "three", "four"};
            for (const auto& val : values) {
                original.push_back(val);
            }

            // Test copy constructor
            Array<std::string> copied(original);
            printTestResult("Copy Constructor - Size", copied.size() == original.size());
            printTestResult("Copy Constructor - Contents", verifyContents(copied, values));

            // Modify original and verify copy is independent
            original.push_back("five");
            printTestResult("Copy Independence", copied.size() == values.size());

            // Test move constructor
            Array<std::string> moved(std::move(copied));
            printTestResult("Move Constructor - Size", moved.size() == values.size());
            printTestResult("Move Constructor - Source Empty", copied.empty());
            printTestResult("Move Constructor - Contents", verifyContents(moved, values));

            // Test move assignment
            Array<std::string> moveAssigned;
            moveAssigned = std::move(moved);
            printTestResult("Move Assignment - Size", moveAssigned.size() == values.size());
            printTestResult("Move Assignment - Source Empty", moved.empty());
            printTestResult("Move Assignment - Contents", verifyContents(moveAssigned, values));
        }

        // Test 6: Clear Operation and Capacity Behavior
        {
            Array<double> arr;
            for (int i = 0; i < 10; ++i) {
                arr.push_back(i * 1.5);
            }
            
            size_t originalCapacity = arr.capacity();
            arr.clear();
            
            printTestResult("Clear - Empty", arr.empty());
            printTestResult("Clear - Size Zero", arr.size() == 0);
            printTestResult("Clear - Capacity Unchanged", arr.capacity() == originalCapacity);

            // Test that we can still add elements after clear
            arr.push_back(42.0);
            printTestResult("Clear - Can Add Elements", arr.size() == 1 && arr[0] == 42.0);
        }

        // Test 7: Stress Test with Large Number of Operations
        {
            Array<int> arr;
            std::vector<int> reference;
            bool success = true;

            // Perform many push_back operations
            for (int i = 0; i < 1000; ++i) {
                arr.push_back(i);
                reference.push_back(i);
            }

            // Verify contents
            success = verifyContents(arr, reference);
            printTestResult("Stress Test - Large Number of Insertions", success);

            // Remove half the elements
            for (int i = 0; i < 500; ++i) {
                arr.remove(0);
                reference.erase(reference.begin());
            }

            success = verifyContents(arr, reference);
            printTestResult("Stress Test - Many Removals", success);

            // Test iterator stability
            std::vector<int> iterTraversed;
            for (const auto& elem : arr) {
                iterTraversed.push_back(elem);
            }
            printTestResult("Stress Test - Iterator Stability", iterTraversed == reference);
        }

        std::cout << "\nAll Array tests completed!" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}