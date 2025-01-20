#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <set>
#include <random>
#include <algorithm>
#include "HashMap.hpp"

void printTestResult(const std::string& testName, bool passed) {
    std::cout << testName << ": " << (passed ? "PASSED" : "FAILED") << std::endl;
}

int main() {
    try {
        // Test 1: Basic Operations
        {
            HashMap<std::string, int> Map;
            printTestResult("Initial Empty Check", Map.empty());
            printTestResult("Initial Size Check", Map.size() == 0);

            // Insert and verify
            Map.insert({"apple", 1});
            Map.insert({"banana", 2});
            Map.insert({"cherry", 3});

            printTestResult("Size After Insertions", Map.size() == 3);
            printTestResult("Empty After Insertions", !Map.empty());
            printTestResult("Contains Existing", Map.contains("apple"));
            printTestResult("Not Contains Non-existing", !Map.contains("grape"));
            
            // Access elements
            printTestResult("Correct Value Retrieved", Map["banana"] == 2);
        }

        // Test 2: Modification and Access
        {
            HashMap<std::string, std::string> Map;
            
            // Test operator[]
            Map["key1"] = "value1";
            Map["key2"] = "value2";
            
            // Modify existing value
            Map["key1"] = "modified1";
            
            printTestResult("Value Modification", Map["key1"] == "modified1");
            printTestResult("Unmodified Value", Map["key2"] == "value2");
            
            // Test at() function
            try {
                Map.at("key1") = "modified2";
                printTestResult("At Function Modification", Map["key1"] == "modified2");
                
                Map.at("nonexistent");
                printTestResult("At Function Exception", false);
            } catch (const std::out_of_range&) {
                printTestResult("At Function Exception", true);
            }
        }

        // Test 3: Deletion Cases
        {
            HashMap<int, std::string> Map;
            std::vector<int> keys = {1, 2, 3, 4, 5};
            for (int key : keys) {
                Map.insert({key, "value" + std::to_string(key)});
            }

            // Test single element deletion
            bool removed = Map.erase(3);
            printTestResult("Single Element Deletion", removed && !Map.contains(3));
            printTestResult("Size After Deletion", Map.size() == 4);

            // Test non-existent element deletion
            removed = Map.erase(10);
            printTestResult("Non-existent Element Deletion", !removed);
            
            // Clear all elements
            Map.clear();
            printTestResult("Clear Operation", Map.empty() && Map.size() == 0);
        }

        // Test 4: Iterator Operations
        {
            HashMap<int, int> Map;
            std::vector<std::pair<int, int>> elements = {
                {1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}
            };
            
            for (auto& elem : elements) {
                Map.insert(elem);
            }

            // Test iterator traversal
            std::vector<std::pair<int, int>> traversed;
            for (std::pair<int, int>& elem : Map) {
                traversed.push_back(elem);
            }

            // Sort both vectors for comparison (since hash Map order is not guaranteed)
            std::sort(elements.begin(), elements.end());
            std::sort(traversed.begin(), traversed.end());
            
            printTestResult("Iterator Traversal", elements == traversed);
            
            // Test const iterator
            const HashMap<int, int>& constMap = Map;
            bool constIteratorWorks = true;
            for (const auto& elem : constMap) {
                if (elem.second % 10 != 0) {
                    constIteratorWorks = false;
                    break;
                }
            }
            printTestResult("Const Iterator", constIteratorWorks);
        }

        // Test 5: Copy and Move Operations
        {
            HashMap<std::string, int> original;
            std::vector<std::pair<std::string, int>> elements = {
                {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}
            };
            
            for (auto& elem : elements) {
                original.insert(elem);
            }

            // Test copy constructor
            HashMap<std::string, int> copied(original);
            printTestResult("Copy Constructor - Size", copied.size() == original.size());
        

            bool allCopied = true;
            for (const auto& elem : elements) {
                if (!copied.contains(elem.first) || copied[elem.first] != elem.second) {
                    allCopied = false;
                    break;
                }
            }
            printTestResult("Copy Constructor - Elements", allCopied);

            // Test move constructor
            HashMap<std::string, int> moved(std::move(copied));
            printTestResult("Move Constructor - Source Empty", copied.empty());
            printTestResult("Move Constructor - Size", moved.size() == original.size());
            
            // Test move assignment
            HashMap<std::string, int> moveAssigned;
            moveAssigned = std::move(moved);
            printTestResult("Move Assignment - Source Empty", moved.empty());
            printTestResult("Move Assignment - Size", moveAssigned.size() == original.size());
        }

        // Test 6: Load F and Rehashing
        {
            HashMap<int, int> Map;
            
            // Insert many elements to trigger rehashing
            const int NUM_ELEMENTS = 1000;
            for (int i = 0; i < NUM_ELEMENTS; ++i) {
                Map.insert({i, i * 2});
            }

            // Verify all elements are still accessible
            bool allAccessible = true;
            for (int i = 0; i < NUM_ELEMENTS; ++i) {
                if (!Map.contains(i) || Map[i] != i * 2) {
                    allAccessible = false;
                    break;
                }
            }
            printTestResult("Rehashing - All Elements Accessible", allAccessible);
            
            // Verify load factor is reasonable (assuming max_load_factor is around 0.75)
            float loadFactor = Map.load_factor();
            printTestResult("Load Factor Check", loadFactor < 1.0f);
        }

        // Test 7: Stress Test with Random Operations
        {
            HashMap<int, int> Map;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(1, 10000);
            std::uniform_int_distribution<> op(0, 2); // 0: insert, 1: delete, 2: find

            std::set<int> reference; // Keep track of what should be in the Map
            bool success = true;

            // Perform 1000 random operations
            for (int i = 0; i < 1000; ++i) {
                int value = dis(gen);
                switch (op(gen)) {
                    case 0: // insert
                        Map.insert({value, value});
                        reference.insert(value);
                        break;
                    case 1: // delete
                        Map.erase(value);
                        reference.erase(value);
                        break;
                    case 2: // find
                        if (Map.contains(value) != (reference.find(value) != reference.end())) {
                            success = false;
                        }
                        break;
                }
            }

            printTestResult("Stress Test - Consistency", success);
            std::cout << Map.size() << " " << reference.size() << std::endl;
            printTestResult("Stress Test - Size Consistency", Map.size() == reference.size());
        }

        std::cout << "\nAll HashMap tests completed!" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
