#ifndef __GRAPH_GRAPH_HPP
#define __GRAPH_GRAPH_HPP

#include <vector> // for returning connected components and shortest path. We don't use our own Array when it comes to interfaces
#include <algorithm> // for vector reverse

#include "../Array/Array.hpp"
#include "../Stack/Stack.hpp"
#include "../Queue/Queue.hpp"
#include "../PriorityQueue/PriorityQueue.hpp"
#include "../HashMap/HashMap.hpp"
/*
- Three imples
 - Adjacency Matrix O(V^2)
 - Adjacency list: An arr of lists where each entry corres to a vertex and contains all neighbors. O(V+E)
 - Edge list: a list of all edges each represented as a tuple (u,v). O(E)
- BFS and DFS
- all funcs including getconnected, detect cycle, disjoint
*/

#define ADJ_MAT
// #define ADJ_LIST
// #define EDG_LIST


#ifdef ADJ_MAT

// undirected weighted graph

template <typename T>
class Graph {
private:

    Array<int> adjMatrix; // use a 1D array to reduce space complexity by half, as undir graph adjMatrix is symmetric.
    HashMap<T, size_t> map2index;
    HashMap<size_t, T> map2vertex;

    // static const int INF = 0x3f3f3f3f;  don't use this or linker error
    static constexpr int INF = 0x3f3f3f3f;

    /*

    In-class declaration of `static const` with initialization:
    - Only provides value for compile-time uses, i.e. substitution
    - Doesn't automatically allocate storage, i.e. no address for storing it

    Storage allocation is needed when:
    - Taking the address of the constant (&INF), such as pass by/binding a reference
    (in our case, the fill constructor of Array secretly uses const T& to pass the filler)

    3. Two solutions:
    - Provide out-of-class definition: `template <typename T>   const int Graph<T>::INF = 0x3f3f3f3f;`
    - Modern approach: Use `static constexpr` instead. The compiler generates a mem location for a `constexpr` var when needed.
    */

    size_t num_vertices = 0;

    size_t upperTriangleIndex (size_t row_idx, size_t col_idx, size_t n)  const  { // non static member (num_vertices) can't serve as default val
        if (row_idx > col_idx) std::swap(row_idx, col_idx); // Ensure i <= j
        return row_idx*(n + n - row_idx + 1) / 2 + (col_idx - row_idx); // upper triangle, requires row_idx <= col_idx
    }

    bool hasEdge (size_t idx1, size_t idx2) const;

public:

    bool addVertex(const T& vertex);
    bool addEdge(const T& vertex1, const T& vertex2, int weight = 1);

    bool removeVertex(const T& vertex);
    bool removeEdge(const T& vertex1, const T& vertex2);

    bool hasVertex (const T& vertex) const;
    bool hasEdge (const T& vertex1, const T& vertex2) const;

    void bfs(const T& start, const std::function<void(const T&)>& visit) const;
    void dfs(const T& start, const std::function<void(const T&)>& visit) const;

    std::vector<T> shortestPath(const T& start, const T& end) const;
    
    std::vector<std::vector<T>> getConnectedComponents() const;


    bool empty() const;
    size_t size() const;
    size_t edgeCount() const;

};

template <typename T>
bool Graph<T>::addVertex(const T& vertex) {
    if (map2index.contains(vertex))  return false;

    // Special case: Graph empty
    if (!num_vertices)  {
        adjMatrix = Array<int>(1, INF);
        map2index[vertex] = 0;
        map2vertex[0] = vertex;
        num_vertices = 1;
        return true;
    }
    // extend the matrix by 1 row & 1 col
    size_t new_num_vertices = num_vertices + 1;
    size_t new_matrix_size = new_num_vertices * (new_num_vertices + 1) / 2;
    Array<int> ExpandedMatrix(new_matrix_size, INF);

    for (size_t i = 0; i < num_vertices; ++i)   {
        for (size_t j = i; j < num_vertices; ++j)   {
            size_t old_index = upperTriangleIndex(i, j, num_vertices);
            size_t new_index = upperTriangleIndex(i, j, new_num_vertices);
            ExpandedMatrix[new_index] = adjMatrix[old_index];
        }
    }
    adjMatrix = std::move(ExpandedMatrix);

    map2index[vertex] = num_vertices;
    map2vertex[num_vertices] = vertex;
    num_vertices = new_num_vertices;
    return true;
}

template <typename T>
bool Graph<T>::addEdge(const T& vertex1, const T& vertex2, int weight) {
    if (!map2index.contains(vertex1) || !map2index.contains(vertex2)) return false;

    size_t i = map2index[vertex1];
    size_t j = map2index[vertex2];

    int& dist = adjMatrix[upperTriangleIndex(i, j, num_vertices)];
    if (dist != weight) {
        dist = weight;
        return true;
    }
    return false;
}


template <typename T>
bool Graph<T>::removeVertex(const T& vertex)    {
    if (!map2index.contains(vertex))  return false;
    size_t new_num_vertices = num_vertices - 1;
    size_t new_matrix_size = new_num_vertices * (new_num_vertices + 1) / 2;
    Array<int> ShrinkedMatrix(new_matrix_size, INF);

    size_t rmIndex = map2index[vertex];

    for (size_t i = 0; i < num_vertices; ++i)   {
        for (size_t j = i; j < num_vertices; ++j)   {
            if (i == rmIndex || j == rmIndex) continue;
            size_t old_index = upperTriangleIndex(i, j, num_vertices);
            ShrinkedMatrix.push_back(adjMatrix[old_index]);
        }
    }
    adjMatrix = std::move(ShrinkedMatrix);
    num_vertices = new_num_vertices;
    map2index.erase(vertex);
    map2vertex.erase(rmIndex);

    // NOTE: after vertex removal, previous vertex<->index relationship becomes invalid and need to be updated.

    for (auto& pair : map2index)    {
        // key is vertex, val is index
        if (pair.val() > rmIndex)   {
            size_t old_idx = pair.val();
            size_t new_idx = old_idx - 1;

            pair.val() = new_idx;
            map2vertex[new_idx] = pair.key();
        }
    }

    // Remove nullified index after shrinkage
    map2vertex.erase(num_vertices);

    return true;
}

template <typename T>
bool Graph<T>::removeEdge(const T& vertex1, const T& vertex2) {
    // if (!map2index.contains(vertex1) || !map2index.contains(vertex1)) return false;

    size_t i = map2index[vertex1];
    size_t j = map2index[vertex2];

    int& dist = adjMatrix[upperTriangleIndex(i, j, num_vertices)];
    if (dist != INF) {
        dist = INF;
        return true;
    }
    return false;
}


template <typename T>
bool Graph<T>::hasVertex (const T& vertex) const {
    return map2index.contains(vertex);
}

template <typename T>
bool Graph<T>::hasEdge(const T& vertex1, const T& vertex2) const {
    if (!map2index.contains(vertex1) || !map2index.contains(vertex2)) return false;

    size_t i = map2index[vertex1];
    size_t j = map2index[vertex2];

    return adjMatrix[upperTriangleIndex(i, j, num_vertices)] != INF;
}

template <typename T>
bool Graph<T>::hasEdge (size_t idx1, size_t idx2) const { // used internally
    if (idx1 >= num_vertices || idx2 >= num_vertices) return false;
    return adjMatrix[upperTriangleIndex(idx1, idx2, num_vertices)] != INF;
}


template <typename T>
void Graph<T>::dfs(const T& start, const std::function<void(const T&)>& visit) const {
    // complete visit of neighbour's neighbours before another neighbour
    if (!map2index.contains(start)) return;
    Stack<size_t> stack; // index as vertex ptr
    HashMap<size_t, bool> visited;
    size_t current = map2index[start];
    stack.push(current);
    visited[current] = true;

    while (!stack.empty())   {
        current = stack.top();
        stack.pop();
        visit(map2vertex[current]);
        for (size_t i = 0; i < num_vertices; ++i)  {
            if (hasEdge(current, i) && !visited[i]) {
                stack.push(i);
                visited[i] = true;
                // DO NOT set visited to true after the visit() call on that vertex!
                // visited essentially represents whether it has been pushed onto the stack instead of being processed.
            }
        }
    }
}

template <typename T>
void Graph<T>::bfs(const T& start, const std::function<void(const T&)>& visit) const {
    // complete visit of all neighbours before neighbour's neighbours
    if (!map2index.contains(start)) return;
    Queue<size_t> queue; // index as vertex ptr
    HashMap<size_t, bool> visited;
    size_t current = map2index[start];
    queue.push(current);
    visited[current] = true;

    while (!queue.empty())   {
        current = queue.front();
        queue.pop();
        visit(map2vertex[current]);
        for (size_t i = 0; i < num_vertices; ++i)  {
            if (hasEdge(current, i) && !visited[i]) {
                queue.push(i);
                visited[i] = true;
            }
        }
    }
}


template <typename T>
std::vector<T> Graph<T>::shortestPath(const T& start, const T& end) const {
    bool isUnweighted = true;
    bool isPositiveDefinite = true;
    for (auto weight : adjMatrix)   {
        if (weight < 0) {
            isPositiveDefinite = false;
        }   else if (weight != INF && weight != 1)   {
            isUnweighted = false;
        }   
    }

    for (auto weight : adjMatrix)   {
        if (weight != INF && weight != 1)   {
            isUnweighted = false;
        }
    }

    std::vector<T> path;

    if (isUnweighted)   {
        // Use BFS search:

        if (!map2index.contains(start) || !map2index.contains(end)) return path;

        Queue<size_t> queue; // index as vertex ptr
        HashMap<size_t, bool> visited;
        HashMap<size_t, int> distance;
        HashMap<size_t, size_t> parent;

        size_t start_idx = map2index[start];
        size_t end_idx = map2index[end];

        size_t current = start_idx;

        queue.push(current);
        visited[current] = true;
        distance[current] = 0;

        while (!queue.empty())   {
            if (visited.contains(end_idx)) break;
            current = queue.front();
            queue.pop();
            for (size_t i = 0; i < num_vertices; ++i)  {
                if (hasEdge(current, i) && !visited[i]) {
                    queue.push(i);
                    visited[i] = true;
                    distance[i] = distance[current] + 1;
                    parent[i] = current;
                }
            }
        }
        
        current = end_idx;
        while (1)    {
            path.push_back(map2vertex[current]);
            if (current == start_idx) break;
            current = parent[current];
        }

        std::reverse(path.begin(), path.end());
        return path;
    }   else if (isPositiveDefinite)
    {
        /* 
        Dijkstra's Algorithm:

        def: dist(a) := shortest distance from a source vertex to vertex a
             w(u, v) := weight of edge (u, v)

        input: src vertex; src vertex, end vertex
        output: vec of dist(each vertex); shortest path from src to end

        Base case: dist(src) = 0
        Recursive case: dist(v) = min_{\forall u: hasEdge(u, v)} (dist(u) + w(u, v))

        But there seems to be a "deadlock" issue w/ this recursion: w/out further info, one requires all dist(u)
        to compute dist(v), while dist(u) may not be availiable and needs dist(v) to compute.

        Formulation:
        def: dist*(a) := an upper bound of dist(a), refered to as the tentative distance 
        
        - Initialize all dist*(v) with a large value and consider all v unfinalized.
        - A vertex a is finalized when its dist* is guaranteed to be the true shortest distance.

        - Update/Improve dist*(v) Upon neighbour finalization: 
            \forall v: if \exists u: dist*(v) < dist(u) + w(u, v) && u: hasEdge(u, v) && u is finalized: dist*(v) <- dist(u) + w(u, v)
        
        Central Claim:
        - Greedy Approach Leads to Global Optima: finalizing a vertex v when: dist*(v) = min_{\forall u: unfinalized} (dist*(u)) yields dist(v), 
            regardless of whether all u's are finalized or not.

        Proof by Contradiction:
        - Assume: we have chosen a vertex v as above. 
        - Assume: claim incorrect, i.e. dist(v) < dist*(v), and the shortest path P(v) passes through at least one unfinalized vertex.
        - Let x be the first unfinalized predecessor of v in the shortest path. dist(x) <= dist(v)
        - Let y be the immediate predecessor of x. By def of shortest path: dist(x) = dist(y) + w(y, x)
            - Note: optimal substructure property: A subpath of a shortest path P is a shortest path. 
                Proof: if a subpath is not the shortest, one could replace it and thus shorten the shortest path P. Contradicts. QED.
        - Since y is finalized, dist*(y) = dist(y). 
            According to Dijkstra update rule, dist*(x) <= dist*(y) + w(y, x) (positive-definiteness) = dist(y) + w(y, x) = dist(x) -> dist*(x) <= dist(x)
        - By def of v: dist*(v) <= dist*(x).
        - Chaining above relations:
            dist*(x) <= dist(x) <= dist(v) < dist*(v) <= dist*(x)
          ->dist*(x) < dist*(x). Contradicts. QED.

        - Summary: Dijkstra is a greedy algorithm, i.e. it makes a series of locally optimal choices. Yet is it not straightforward 
            how a greedy algorithm arrives at a global optima. In proving so, the following properties are demanded:
            - Positive-definite property of weights
                - if there exists negative edges, then the above proof to the Central Claim would fail.
            - Optimal substructure property of shortest paths

        */

        if (!map2index.contains(start) || !map2index.contains(end)) return path;
         
        PriorityQueue<std::pair<int, size_t>> pq; // (dist, index). Leverage std::pair default lexicographic ordering.
        HashMap<size_t, bool> finalized;
        HashMap<size_t, int> dist;
        HashMap<size_t, size_t> parent;

        size_t start_idx = map2index[start];
        size_t end_idx = map2index[end];

        dist[start_idx] = 0;

        for (size_t i = 1; i < num_vertices; ++i)   {
            dist[i] = INF;
        }

        size_t current = start_idx;
        pq.push(std::make_pair(dist[current], current));

        // NOTE: we don't have to push everything onto the pq, as vertices w/out any finalized neighbour are "out of consideration"
        //       -- they are guaranteed to be not min. Only push vertices w/ at least one finalized neighbour.

        // update:
        while (!pq.empty()) {
            current = pq.top().second;
            pq.pop();
            finalized[current] = true;
            if (current == end_idx) break;
            for (size_t i = 0; i < num_vertices; ++i)   {
                if (finalized[i]) continue; // Skip already processed nodes

                auto update = dist[current] + adjMatrix[upperTriangleIndex(current, i, num_vertices)];
                if (hasEdge(current, i) && dist[i] > update)    {
                    dist[i] = update;
                    pq.push(std::make_pair(dist[i], i));
                    parent[i] = current; // track path
                }
            }
        }

        if (dist[end_idx] == INF) return path; // not connected, return empty path

        current = end_idx;
        while (1)    {
            path.push_back(map2vertex[current]);
            if (current == start_idx) break;
            current = parent[current];
        }

        std::reverse(path.begin(), path.end());

        return path;

    }
    

    return path;
}


template <typename T>
std::vector<std::vector<T>> Graph<T>::getConnectedComponents() const {
    /*
    Algorithm GetConnectedComponents(graph):
    Init visited = empty hashmap
    Init components = empty vec of vec
    
    For each vertex in graph:
        If vertex is not in visited:

            Init current_component = empty vec
            
            BFS(vertex, mark as visited + append to current_component):

        Append current_component to components
    Return components
    */

   HashMap<size_t, bool> visited;
   std::vector<std::vector<T>> components;

   for (size_t i = 0; i < num_vertices; ++i)   {
        if (!visited[i])    {
            std::vector<T> current_component;
            auto& start = map2vertex[i]; // Reference safe because map2vertex can't be modified in a const function
            bfs(start, [&visited, &current_component, this](const T& vertex) {
                visited[map2index[vertex]] = true;
                current_component.push_back(vertex);
            });
            components.push_back(current_component);
        }
   }
   return components;
}


template <typename T>
bool Graph<T>::empty() const {
    return num_vertices == 0;
}

template <typename T>
size_t Graph<T>::size() const {
    return num_vertices;
}

template <typename T>
size_t Graph<T>::edgeCount() const {
    size_t count = 0;
    for (const auto& elem : adjMatrix)  {
        if (elem != INF) ++count; // upper triangle ensures no double counting
        // Why we don't maintain a edge count member is because it's tricky to account for
        // the edge count during vertex removal.
    }
    return count;
}


#elif defined(ADJ_LIST)


#elif defined(EDG_LIST)







#endif // imple toggle

#endif // __GRAPH_GRAPH_HPP
