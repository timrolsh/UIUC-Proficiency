#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <random>
#include <stdexcept>
#include <climits>
#include "PriorityQueue.hpp"

void printTestResult(const std::string& testName, bool passed) {
    std::cout << testName << ": " << (passed ? "PASSED" : "FAILED") << std::endl;
}

template<typename T>
void verifyHeapProperty(const std::vector<T>& elements) {
    for (size_t i = 0; i < elements.size(); ++i) {
        size_t leftChild = 2 * i + 1;
        size_t rightChild = 2 * i + 2;
        
        if (leftChild < elements.size()) {
            if (elements[i] < elements[leftChild]) {
                throw std::runtime_error("Heap property violated at left child");
            }
        }
        if (rightChild < elements.size()) {
            if (elements[i] < elements[rightChild]) {
                throw std::runtime_error("Heap property violated at right child");
            }
        }
    }
}

// Structure to test with decrease priority
struct Node {
    int id;
    int priority;
    
    bool operator<=(const Node& other) const {
        return priority <= other.priority;
    }

    bool operator<(const Node& other) const {
        return priority < other.priority;
    }

    bool operator>(const Node& other) const {
        return !(priority > other.priority);
    }
    
    bool operator==(const Node& other) const {
        return id == other.id;
    }
};

int main() {
    try {
        // Test 1: Basic Operations
        {
            PriorityQueue<int> pq;
            printTestResult("Initial Empty Check", pq.empty());
            printTestResult("Initial Size Check", pq.size() == 0);

            // Push and verify
            pq.push(5);
            pq.push(3);
            pq.push(7);
            pq.push(1);
            pq.push(9);

            printTestResult("Size After Pushes", pq.size() == 5);
            printTestResult("Empty After Pushes", !pq.empty());
            printTestResult("Top Element Check", pq.top() == 1);
        }

        // Test 2: Order Verification
        {
            PriorityQueue<int> pq;
            std::vector<int> numbers = {5, 3, 7, 1, 4, 6, 8};
            for (int num : numbers) {
                pq.push(num);
            }

            std::vector<int> extracted;
            while (!pq.empty()) {
                extracted.push_back(pq.top());
                pq.pop();
            }
            
            std::vector<int> expected = numbers;
            std::sort(expected.begin(), expected.end(), std::less<int>());
            
            printTestResult("Extraction Order", extracted == expected);
        }

        // Test 3: Clear Operation
        {
            PriorityQueue<int> pq;
            std::vector<int> numbers = {50, 30, 70, 20, 40, 60, 80};
            for (int num : numbers) {
                pq.push(num);
            }

            pq.clear();
            printTestResult("Clear - Empty Check", pq.empty());
            printTestResult("Clear - Size Check", pq.size() == 0);

            // Verify can still use after clear
            pq.push(100);
            printTestResult("Push After Clear", pq.top() == 100 && pq.size() == 1);
        }

        // Test 4: Edge Cases
        {
            PriorityQueue<int> pq;
            
            // Empty queue operations
            bool topThrew = false;
            try {
                pq.top();
            } catch (const std::runtime_error&) {
                topThrew = true;
            }
            printTestResult("Top on Empty Throws", topThrew);

            bool popThrew = false;
            try {
                pq.pop();
            } catch (const std::runtime_error&) {
                popThrew = true;
            }
            printTestResult("Pop on Empty Throws", popThrew);

            // Duplicate elements
            pq.push(10);
            pq.push(10);
            printTestResult("Duplicate Push Size", pq.size() == 2);
            printTestResult("Duplicate Top Check", pq.top() == 10);
        }
        
        // Test 5: Custom Comparator
    {
        // Custom comparator that creates a max heap (reverses the default min heap behavior)
        auto maxComp = [](const int& a, const int& b) { return a > b; };
        PriorityQueue<int> minPQ;  // Default min heap
        PriorityQueue<int, decltype(maxComp)> maxPQ(maxComp);  // Max heap with custom comparator

        std::vector<int> numbers = {5, 3, 7, 1, 4};
        
        // Push same numbers to both queues
        for (int num : numbers) {
            minPQ.push(num);
            maxPQ.push(num);
        }
        
        // Verify min heap has smallest element on top
        printTestResult("Min Heap Top", minPQ.top() == 1);
        
        // Verify max heap has largest element on top
        printTestResult("Max Heap Top", maxPQ.top() == 7);
        
        // Extract and verify ordering for min heap
        std::vector<int> minExtracted;
        while (!minPQ.empty()) {
            minExtracted.push_back(minPQ.top());
            minPQ.pop();
        }
        
        std::vector<int> minExpected = numbers;
        std::sort(minExpected.begin(), minExpected.end());  // ascending order
        printTestResult("Min Heap Order", minExtracted == minExpected);
        
        // Extract and verify ordering for max heap
        std::vector<int> maxExtracted;
        while (!maxPQ.empty()) {
            maxExtracted.push_back(maxPQ.top());
            maxPQ.pop();
        }
        
        std::vector<int> maxExpected = numbers;
        std::sort(maxExpected.begin(), maxExpected.end(), maxComp);  // descending order
        printTestResult("Max Heap Order", maxExtracted == maxExpected);

        // Test with custom struct and comparator
        struct Item {
            int value;
            std::string name;
        };
        
        auto itemComp = [](const Item& a, const Item& b) { return a.value < b.value; };
        PriorityQueue<Item, decltype(itemComp)> itemPQ(itemComp);
        
        itemPQ.push(Item{5, "five"});
        itemPQ.push(Item{3, "three"});
        itemPQ.push(Item{7, "seven"});
        
        printTestResult("Custom Struct Min Value", itemPQ.top().value == 3);
        printTestResult("Custom Struct Min Name", itemPQ.top().name == "three");
    }
        // Test 6: Stress Test
        {
            PriorityQueue<int> pq;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(1, 1000);

            // Push 1000 random numbers
            std::vector<int> numbers;
            for (int i = 0; i < 1000; ++i) {
                int num = dis(gen);
                numbers.push_back(num);
                pq.push(num);
            }

            // Verify heap property
            std::vector<int> heap_array;
            while (!pq.empty()) {
                heap_array.push_back(pq.top());
                pq.pop();
            }
            
            bool isOrdered = true;
            for (size_t i = 1; i < heap_array.size(); ++i) {
                if (heap_array[i-1] > heap_array[i]) {
                    isOrdered = false;
                    break;
                }
            }
            printTestResult("Stress Test - Heap Property", isOrdered);
            printTestResult("Stress Test - Size", heap_array.size() == numbers.size());
        }

        
        // Test 7: Move Operations
        {
            PriorityQueue<int> pq1;
            pq1.push(5);
            pq1.push(3);
            pq1.push(7);

            // Move constructor
            PriorityQueue<int> pq2(std::move(pq1));
            printTestResult("Move Constructor - Size", pq2.size() == 3);
            printTestResult("Move Constructor - Original Empty", pq1.empty());
            printTestResult("Move Constructor - Top Element", pq2.top() == 3);

            // Move assignment
            PriorityQueue<int> pq3;
            pq3 = std::move(pq2);
            printTestResult("Move Assignment - Size", pq3.size() == 3);
            printTestResult("Move Assignment - Original Empty", pq2.empty());
            printTestResult("Move Assignment - Top Element", pq3.top() == 3);
        }
        

        // Test 8: Decrease Priority Operations
        {
            std::cout << "\nTesting Decrease Priority Operations:" << std::endl;
            
            // Basic decrease priority
            {
                PriorityQueue<Node> pq;
                Node n1{1, 10};
                Node n2{2, 80};
                Node n3{3, 60};
                
                pq.push(n1);
                pq.push(n2);
                pq.push(n3);
                
                // Decrease priority of n1
                Node updated{1, 500};  // Same id, lower priority
                pq.decreasePriority(n1, updated);
                
                printTestResult("Basic Decrease Priority - Top Element",
                    pq.top().id == 3 && pq.top().priority == 60);
                
            // Edge cases for decrease priority
            {
                PriorityQueue<Node> pq;
                Node n1{1, 100};
                pq.push(n1);
                
                // Test decreasing to same priority
                bool sameThrew = false;
                try {
                    pq.decreasePriority(n1, Node{1, 100});
                } catch (const std::invalid_argument&) {
                    sameThrew = true;
                }
                printTestResult("Decrease to Same Priority Throws",
                    sameThrew);
                
                // Test decreasing to higher priority
                bool higherThrew = false;
                try {
                    pq.decreasePriority(n1, Node{1, 1});
                } catch (const std::invalid_argument&) {
                    higherThrew = true;
                }
                printTestResult("Decrease to Higher Priority Throws",
                    higherThrew);
                
                // Test decreasing non-existent node
                bool nonExistentThrew = false;
                try {
                    pq.decreasePriority(Node{999, 100}, Node{999, 50});
                } catch (const std::runtime_error&) {
                    nonExistentThrew = true;
                }
                printTestResult("Decrease Non-existent Node Throws",
                    nonExistentThrew);
            }
            }
            
        }

        std::cout << "\nAll Priority Queue tests completed!" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
