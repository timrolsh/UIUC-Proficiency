#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <random>
#include "Heap.hpp"

void printTestResult(const std::string& testName, bool passed) {
    std::cout << testName << ": " << (passed ? "PASSED" : "FAILED") << std::endl;
}

template<typename T>
void verifyHeapProperty(const std::vector<T>& elements) {
    for (size_t i = 0; i < elements.size(); ++i) {
        size_t leftChild = 2 * i + 1;
        size_t rightChild = 2 * i + 2;
        
        if (leftChild < elements.size()) {
            if (elements[i] > elements[leftChild]) {
                throw std::runtime_error("Heap property violated with left child");
            }
        }
        
        if (rightChild < elements.size()) {
            if (elements[i] > elements[rightChild]) {
                throw std::runtime_error("Heap property violated with right child");
            }
        }
    }
}

int main() {
    try {
        // Test 1: Basic Operations
        {
            Heap<int> heap;
            printTestResult("Initial Empty Check", heap.empty());
            printTestResult("Initial Size Check", heap.size() == 0);

            // Insert and verify
            heap.push(5);
            heap.push(3);
            heap.push(7);
            heap.push(1);
            heap.push(9);

            printTestResult("Size After Insertions", heap.size() == 5);
            printTestResult("Empty After Insertions", !heap.empty());
            printTestResult("Top Element", heap.top() == 1);  // Min heap
        }

        // Test 2: Heap Order Property
        {
            Heap<int> heap;
            std::vector<int> numbers = {5, 3, 7, 1, 4, 6, 8};
            for (int num : numbers) {
                heap.push(num);
            }

            std::vector<int> extracted;
            while (!heap.empty()) {
                extracted.push_back(heap.top());
                heap.pop();
            }
            
            std::vector<int> expected = numbers;
            std::sort(expected.begin(), expected.end());
            
            printTestResult("Heap Order Property", extracted == expected);
        }

        // Test 3: Pop Operations
        {
            Heap<int> heap;
            std::vector<int> numbers = {50, 30, 70, 20, 40, 60, 80};
            for (int num : numbers) {
                heap.push(num);
            }

            // Test multiple pops
            int prevTop = heap.top();
            heap.pop();
            printTestResult("Pop Operation", heap.top() > prevTop);

            size_t initialSize = heap.size();
            heap.pop();
            printTestResult("Size After Pop", heap.size() == initialSize - 1);
        }

        // Test 4: Edge Cases
        {
            Heap<int> heap;
            
            // Empty heap operations
            try {
                heap.top();
                printTestResult("Top on Empty Heap", false);
            } catch (const std::runtime_error&) {
                printTestResult("Top on Empty Heap", true);
            }

            try {
                heap.pop();
                printTestResult("Pop from Empty Heap", false);
            } catch (const std::runtime_error&) {
                printTestResult("Pop from Empty Heap", true);
            }

            // Single element
            heap.push(10);
            printTestResult("Single Element Top", heap.top() == 10);
            heap.pop();
            printTestResult("Empty After Single Pop", heap.empty());
        }

        // Test 5: Stress Test
        {
            Heap<int> heap;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(1, 1000);

            // Insert 100 random numbers
            std::vector<int> numbers;
            for (int i = 0; i < 100; ++i) {
                int num = dis(gen);
                numbers.push_back(num);
                heap.push(num);
            }

            // Verify heap property
            std::vector<int> heapContents;
            while (!heap.empty()) {
                heapContents.push_back(heap.top());
                heap.pop();
            }

            bool isOrdered = true;
            for (size_t i = 1; i < heapContents.size(); ++i) {
                if (heapContents[i-1] > heapContents[i]) {
                    isOrdered = false;
                    break;
                }
            }
            printTestResult("Stress Test - Heap Order", isOrdered);
            
            // Test rebuilding heap
            Heap<int> rebuiltHeap;
            for (int num : numbers) {
                rebuiltHeap.push(num);
            }
            printTestResult("Stress Test - Rebuild Size", rebuiltHeap.size() == numbers.size());
        }

        std::cout << "\nAll Heap tests completed!" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
