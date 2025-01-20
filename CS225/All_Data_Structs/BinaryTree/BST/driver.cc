#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <random>
#include "BST.hpp"

void printTestResult(const std::string& testName, bool passed) {
    std::cout << testName << ": " << (passed ? "PASSED" : "FAILED") << std::endl;
}

template<typename T>
void verifyInOrder(const std::vector<T>& elements) {
    for (size_t i = 1; i < elements.size(); ++i) {
        if (elements[i-1] > elements[i]) {
            throw std::runtime_error("Elements not in order");
        }
    }
}

int main() {
    try {
        // Test 1: Basic Operations
        {
            BST<int> bst;
            printTestResult("Initial Empty Check", bst.empty());
            printTestResult("Initial Size Check", bst.size() == 0);

            // Insert and verify
            bst.insert(5);
            bst.insert(3);
            bst.insert(7);
            bst.insert(1);
            bst.insert(9);

            printTestResult("Size After Insertions", bst.size() == 5);
            printTestResult("Empty After Insertions", !bst.empty());
            printTestResult("Contains Existing", bst.contains(5));
            printTestResult("Not Contains Non-existing", !bst.contains(6));
        }

        // Test 2: Traversal Order
        {
            BST<int> bst;
            std::vector<int> numbers = {5, 3, 7, 1, 4, 6, 8};
            for (int num : numbers) {
                bst.insert(num);
            }

            std::vector<int> inorder;
            bst.inorderTraversal([&inorder](int val) { inorder.push_back(val); });
            
            std::vector<int> expected = numbers;
            std::sort(expected.begin(), expected.end());
            
            printTestResult("Inorder Traversal", inorder == expected);
        }

        // Test 3: Deletion Cases
        {
            BST<int> bst;
            std::vector<int> numbers = {50, 30, 70, 20, 40, 60, 80};
            for (int num : numbers) {
                bst.insert(num);
            }

            // Test leaf deletion
            bst.remove(20);
            printTestResult("Leaf Deletion", !bst.contains(20) && bst.size() == 6);

            // Test single child deletion
            bst.remove(70);
            printTestResult("Single Child Deletion", !bst.contains(70) && bst.contains(80));

            // Test two children deletion
            bst.remove(30);
            printTestResult("Two Children Deletion", !bst.contains(30) && bst.contains(40));
        }

        // Test 4: Edge Cases
        {
            BST<int> bst;
            
            // Empty tree operations
            printTestResult("Remove From Empty", !bst.remove(10));
            printTestResult("Find in Empty", !bst.contains(10));

            // Duplicate insertions
            bst.insert(10);
            bst.insert(10);
            printTestResult("Duplicate Insert Size", bst.size() == 1);
        }

        // Test 5: Copy Constructor and Assignment
        {
            BST<int> original;
            std::vector<int> numbers = {50, 30, 70, 20, 40, 60, 80};
            for (int num : numbers) {
                original.insert(num);
            }

            // Test copy constructor
            BST<int> copied(original);
            
            // Verify copied tree has same elements
            std::vector<int> originalOrder, copiedOrder;
            original.inorderTraversal([&originalOrder](int val) { originalOrder.push_back(val); });
            copied.inorderTraversal([&copiedOrder](int val) { copiedOrder.push_back(val); });
            
            printTestResult("Copy Constructor - Same Elements", originalOrder == copiedOrder);
            printTestResult("Copy Constructor - Same Size", original.size() == copied.size());

            // Modify original and verify copied remains unchanged
            original.insert(90);
            original.remove(30);
            
            printTestResult("Copy Constructor - Independent", !copied.contains(90) && copied.contains(30));

            // Test assignment operator
            BST<int> assigned;
            assigned = copied;
            
            std::vector<int> assignedOrder;
            assigned.inorderTraversal([&assignedOrder](int val) { assignedOrder.push_back(val); });
            
            printTestResult("Assignment Operator - Same Elements", copiedOrder == assignedOrder);
            printTestResult("Assignment Operator - Same Size", copied.size() == assigned.size());
        }

        // Test 6: Move Constructor and Assignment
        {
            BST<int> original;
            std::vector<int> numbers = {50, 30, 70, 20, 40, 60, 80};
            for (int num : numbers) {
                original.insert(num);
            }

            // Capture original size and elements
            size_t originalSize = original.size();
            std::vector<int> originalElements;
            original.inorderTraversal([&originalElements](int val) { originalElements.push_back(val); });

            // Test move constructor
            BST<int> moved(std::move(original));
            
            // Verify moved tree has same elements
            std::vector<int> movedElements;
            moved.inorderTraversal([&movedElements](int val) { movedElements.push_back(val); });
            
            printTestResult("Move Constructor - Correct Elements", originalElements == movedElements);
            printTestResult("Move Constructor - Correct Size", moved.size() == originalSize);
            printTestResult("Move Constructor - Source Empty", original.empty());

            // Test move assignment
            BST<int> moveAssigned;
            moveAssigned = std::move(moved);
            
            std::vector<int> assignedElements;
            moveAssigned.inorderTraversal([&assignedElements](int val) { assignedElements.push_back(val); });
            
            printTestResult("Move Assignment - Correct Elements", originalElements == assignedElements);
            printTestResult("Move Assignment - Correct Size", moveAssigned.size() == originalSize);
            printTestResult("Move Assignment - Source Empty", moved.empty());
        }

        // Test 5: Stress Test
        {
            BST<int> bst;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(1, 1000);

            // Insert 100 random numbers
            std::vector<int> numbers;
            for (int i = 0; i < 100; ++i) {
                int num = dis(gen);
                numbers.push_back(num);
                bst.insert(num);
            }

            // Verify all numbers can be found
            bool allFound = true;
            for (int num : numbers) {
                if (!bst.contains(num)) {
                    allFound = false;
                    break;
                }
            }
            printTestResult("Stress Test - All Elements Found", allFound);

            // Verify inorder traversal is sorted
            std::vector<int> traversal;
            bst.inorderTraversal([&traversal](int val) { traversal.push_back(val); });
            
            bool isSorted = true;
            try {
                verifyInOrder(traversal);
            } catch (...) {
                isSorted = false;
            }
            printTestResult("Stress Test - Inorder Correctness", isSorted);
        }

        std::cout << "\nAll BST tests completed!" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}