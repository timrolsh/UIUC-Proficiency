// Test driver for BinaryTree/AVLTree class
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
#include <random>
#include "AVLTree.hpp"

template<typename T>
void printTestResult(const std::string& testName, bool passed) {
    std::cout << testName << ": " << (passed ? "PASSED" : "FAILED") << std::endl;
}

template<typename T>
bool verifyAVLBalance(const AVLTree<T>& tree) {
    return tree.isBalanced();  // Assuming your AVL implementation has this method
}

template<typename T>
bool verifyHeight(const AVLTree<T>& tree) {
    return tree.verifyHeights();  // Assuming your AVL implementation has this method
}

int main() {
    try {
        // Test 1: Basic Operations with Balance Verification
        {
            AVLTree<int> avl;
            printTestResult("Initial Empty Check", avl.empty());

            // Left-Left Case
            avl.insert(30);
            avl.insert(20);
            avl.insert(10);
            printTestResult("Left-Left Balance", verifyAVLBalance(avl));
            printTestResult("Left-Left Height", verifyHeight(avl));

            avl.clear();

            // Right-Right Case
            avl.insert(10);
            avl.insert(20);
            avl.insert(30);
            printTestResult("Right-Right Balance", verifyAVLBalance(avl));
            printTestResult("Right-Right Height", verifyHeight(avl));

            avl.clear();

            // Left-Right Case
            avl.insert(30);
            avl.insert(10);
            avl.insert(20);
            printTestResult("Left-Right Balance", verifyAVLBalance(avl));
            printTestResult("Left-Right Height", verifyHeight(avl));

            avl.clear();

            // Right-Left Case
            avl.insert(10);
            avl.insert(30);
            avl.insert(20);
            printTestResult("Right-Left Balance", verifyAVLBalance(avl));
            printTestResult("Right-Left Height", verifyHeight(avl));
        }

        // Test 2: Complex Rotation Sequences
        {
            AVLTree<int> avl;
            std::vector<int> insertSequence = {50, 40, 60, 30, 45, 55, 70, 20, 35};
            
            for (int num : insertSequence) {
                avl.insert(num);
                printTestResult("Balance After Insert " + std::to_string(num), 
                              verifyAVLBalance(avl));
            }

            // Verify final structure
            std::vector<int> inorder;
            avl.inorderTraversal([&inorder](int val) { inorder.push_back(val); });
            
            std::vector<int> expected = insertSequence;
            std::sort(expected.begin(), expected.end());
            printTestResult("Final Inorder Correctness", inorder == expected);
        }

        // Test 3: Deletion with Rebalancing
        {
            AVLTree<int> avl;
            std::vector<int> numbers = {50, 30, 70, 20, 40, 60, 80, 15, 25, 35, 45};
            for (int num : numbers) {
                avl.insert(num);
            }

            // Test various deletion cases
            avl.remove(15);  // Leaf node
            printTestResult("Balance After Leaf Deletion", verifyAVLBalance(avl));

            avl.remove(30);  // Internal node with two children
            printTestResult("Balance After Internal Node Deletion", verifyAVLBalance(avl));

            avl.remove(70);  // Root of subtree
            printTestResult("Balance After Subtree Root Deletion", verifyAVLBalance(avl));
        }

        // Test 4: Edge Cases
        {
            AVLTree<int> avl;
            
            // Empty tree operations
            printTestResult("Remove From Empty", !avl.remove(10));
            printTestResult("Find in Empty", !avl.contains(10));

            // Single node
            avl.insert(10);
            printTestResult("Single Node Balance", verifyAVLBalance(avl));

            // Duplicate insertions
            avl.insert(10);
            printTestResult("Duplicate Insert Size", avl.size() == 1);
        }

        // Test 5: Stress Test
        {
            AVLTree<int> avl;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(1, 1000);

            // Insert 100 random numbers
            const int NUM_OPERATIONS = 100;
            std::vector<int> inserted;
            
            // Insert phase
            for (int i = 0; i < NUM_OPERATIONS; ++i) {
                int num = dis(gen);
                inserted.push_back(num);
                avl.insert(num);
                
                if (!verifyAVLBalance(avl)) {
                    throw std::runtime_error("Balance violation detected during insertion");
                }
            }

            // Random remove phase
            std::shuffle(inserted.begin(), inserted.end(), gen);
            for (int i = 0; i < NUM_OPERATIONS / 2; ++i) {
                avl.remove(inserted[i]);
                
                if (!verifyAVLBalance(avl)) {
                    throw std::runtime_error("Balance violation detected during deletion");
                }
            }

            printTestResult("Stress Test - All Operations Maintained Balance", true);

            // Verify final tree properties
            std::vector<int> finalTraversal;
            avl.inorderTraversal([&finalTraversal](int val) { finalTraversal.push_back(val); });
            
            bool isSorted = std::is_sorted(finalTraversal.begin(), finalTraversal.end());
            printTestResult("Stress Test - Final Tree Order", isSorted);
        }

        std::cout << "\nAll AVL Tree tests completed!" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
