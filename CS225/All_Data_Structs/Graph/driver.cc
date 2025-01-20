#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <stdexcept>
#include <random>
#include <unordered_set>
#include "Graph.hpp"

void printTestResult(const std::string& testName, bool passed) {
    std::cout << testName << ": " << (passed ? "PASSED" : "FAILED") << std::endl;
}

// Helper function to verify path exists between vertices
template<typename T>
bool verifyPath(const std::vector<T>& path, const Graph<T>& graph) {
    if (path.empty()) return true;
    for (size_t i = 1; i < path.size(); ++i) {
        if (!graph.hasEdge(path[i-1], path[i])) {
            return false;
        }
    }
    return true;
}

int main() {
    try {
        // Test 1: Basic Graph Operations
        {
            Graph<int> graph;
            printTestResult("Initial Empty Check", graph.empty());
            printTestResult("Initial Size Check", graph.size() == 0);
            printTestResult("Initial Edge Count", graph.edgeCount() == 0);

            // Add vertices and verify
            graph.addVertex(1);
            graph.addVertex(2);
            graph.addVertex(3);
            
            printTestResult("Size After Adding Vertices", graph.size() == 3);
            printTestResult("Contains Existing Vertex", graph.hasVertex(1));
            printTestResult("Not Contains Non-existing", !graph.hasVertex(4));
            
            // Add edges and verify
            graph.addEdge(1, 2);
            graph.addEdge(2, 3);
            
            printTestResult("Edge Count After Adding", graph.edgeCount() == 2);
            printTestResult("Has Edge Check", graph.hasEdge(1, 2));
            printTestResult("No Edge Check", !graph.hasEdge(1, 3));
        }

        // Test 2: Graph Traversal
        {
            Graph<int> graph;
            std::vector<int> vertices = {1, 2, 3, 4, 5};
            for (int v : vertices) {
                graph.addVertex(v);
            }
            
            // Create a connected graph
            graph.addEdge(1, 2);
            graph.addEdge(2, 3);
            graph.addEdge(3, 4);
            graph.addEdge(4, 5);
            graph.addEdge(1, 5);

            // Test BFS
            std::vector<int> bfsOrder;
            graph.bfs(1, [&bfsOrder](int v) { bfsOrder.push_back(v); });
            std::cout << bfsOrder.size() << std::endl;
            printTestResult("BFS Visited All Vertices", bfsOrder.size() == vertices.size());
            
            // Test DFS
            std::vector<int> dfsOrder;
            graph.dfs(1, [&dfsOrder](int v) { dfsOrder.push_back(v); });
            printTestResult("DFS Visited All Vertices", dfsOrder.size() == vertices.size());
            
            // Test shortest path
            auto path = graph.shortestPath(1, 4);
            printTestResult("Valid Shortest Path", verifyPath(path, graph));
        }

        // Test 3: Removal Operations
        {
            Graph<int> graph;
            for (int i = 1; i <= 5; ++i) {
                graph.addVertex(i);
            }
            graph.addEdge(1, 2);
            graph.addEdge(2, 3);
            graph.addEdge(3, 4);
            graph.addEdge(4, 5);

            // Test edge removal
            graph.removeEdge(2, 3);
            printTestResult("Edge Removal", !graph.hasEdge(2, 3));
            printTestResult("Edge Count After Removal", graph.edgeCount() == 3);

            // Test vertex removal
            graph.removeVertex(3);
            printTestResult("Vertex Removal", !graph.hasVertex(3));
            printTestResult("Size After Vertex Removal", graph.size() == 4);
            printTestResult("Edge Count After Vertex Removal", graph.edgeCount() == 2);
        }

        // Test 4: Edge Cases
        {
            Graph<std::string> graph;
            
            // Empty graph operations
            printTestResult("Remove From Empty", !graph.removeVertex("A"));
            printTestResult("Find in Empty", !graph.hasVertex("A"));
            
            // Add and remove same vertex multiple times
            graph.addVertex("A");
            graph.addVertex("A");  // Should not add duplicate
            printTestResult("Duplicate Vertex Add", graph.size() == 1);
            
            graph.removeVertex("A");
            graph.removeVertex("A");  // Should not throw
            printTestResult("Multiple Vertex Remove", !graph.hasVertex("A"));
            
            // Self-loops
            graph.addVertex("B");
            graph.addEdge("B", "B");
            printTestResult("Self-Loop Addition", graph.hasEdge("B", "B"));
        }

        // Test 5: Stress Test
        {
            Graph<int> graph;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(1, 100);

            // Add 50 vertices
            std::unordered_set<int> addedVertices;
            for (int i = 0; i < 50; ++i) {
                int vertex = dis(gen);
                graph.addVertex(vertex);
                addedVertices.insert(vertex);
            }

            // Add 100 random edges
            int edgeCount = 0;
            for (int i = 0; i < 100; ++i) {
                auto it1 = addedVertices.begin();
                auto it2 = addedVertices.begin();
                std::advance(it1, dis(gen) % addedVertices.size());
                std::advance(it2, dis(gen) % addedVertices.size());
                
                if (graph.addEdge(*it1, *it2)) {
                    edgeCount++;
                }
            }

            // Verify connectivity
            std::vector<int> visited;
            graph.dfs(*addedVertices.begin(), [&visited](int v) { visited.push_back(v); });
            
            printTestResult("Stress Test - Vertex Count", graph.size() == addedVertices.size());
            printTestResult("Stress Test - Edge Addition", graph.edgeCount() > 0);
            printTestResult("Stress Test - Traversal", !visited.empty());
        }

        // Test 6: Connected Components
        {
            Graph<int> graph;
            // Create two separate components
            // Component 1: 1-2-3
            graph.addVertex(1);
            graph.addVertex(2);
            graph.addVertex(3);
            graph.addEdge(1, 2);
            graph.addEdge(2, 3);

            // Component 2: 4-5
            graph.addVertex(4);
            graph.addVertex(5);
            graph.addEdge(4, 5);

            auto components = graph.getConnectedComponents();
            printTestResult("Connected Components Count", components.size() == 2);
            
            bool componentSizesCorrect = 
                (components[0].size() == 3 && components[1].size() == 2) ||
                (components[0].size() == 2 && components[1].size() == 3);
            printTestResult("Component Sizes", componentSizesCorrect);
        }

        // Test 7: Weighted Graph Shortest Path
        {
        Graph<int> graph;
        
        // Create a weighted graph
        for (int i = 1; i <= 5; ++i) {
            graph.addVertex(i);
        }

        // Add weighted edges to create multiple paths between 1 and 5
        graph.addEdge(1, 2, 2);  // Path 1: 1-2-3-5 (total weight: 7)
        graph.addEdge(2, 3, 2);
        graph.addEdge(3, 5, 3);
        
        graph.addEdge(1, 4, 1);  // Path 2: 1-4-5 (total weight: 4)
        graph.addEdge(4, 5, 3);
        
        // Test shortest path from 1 to 5
        auto path = graph.shortestPath(1, 5);
        
        // Verify the path exists
        printTestResult("Weighted Path Exists", !path.empty());
        
        // Verify it's the shortest path (should be 1-4-5)
        bool correctPath = (path.size() == 3 && 
                        path[0] == 1 && 
                        path[1] == 4 && 
                        path[2] == 5);
        printTestResult("Correct Shortest Path Found", correctPath);
        
        // Test path that doesn't exist
        graph.addVertex(6);  // Isolated vertex
        auto noPath = graph.shortestPath(1, 6);
        printTestResult("No Path Returns Empty", noPath.empty());
        }

        std::cout << "\nAll Graph tests completed!" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
