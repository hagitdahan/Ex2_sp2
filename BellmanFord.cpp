//hagitdahan101@gmail.com
//315158568
#include "BellmanFord.hpp"
#include "Algorithms.hpp"
#include "GraphType.hpp"
using namespace std;
namespace ariel{
    vector<int> BellmanFord::ShortestPathB(Graph &g, int start, int end) {
        vector<vector<int>> adjacencyMatrix = g.getAdjancencyMatrix();
        size_t numVertices = g.getNumVertices();
        vector<bool> visited(numVertices, false);
        Algorithms::dfs(g, start, visited);
        vector<int> dist(numVertices, numeric_limits<int>::max());
        dist[size_t(start)] = 0;
        vector<int> parent(numVertices,-1);
        // Relax all edges V-1 times
        for (size_t i = 0; i < numVertices - 1; ++i) {
            for (size_t u = 0; u < numVertices; ++u) {
                for (size_t v = 0; v < numVertices; ++v) {
                    if (adjacencyMatrix[u][v] != 0 && dist[u] !=numeric_limits<int>::max() &&
                        dist[u] + adjacencyMatrix[u][v] < dist[v] && visited[v] == true) {
                        if(g.getGraphType()==GraphType::UNDIRECTED && parent[u] == v) {
                            continue;
                        }
                        dist[v] = dist[u] + adjacencyMatrix[u][v];
                        parent[v]=u;
                    }
                }
            }
        }

        // Check for negative cycles
        for (size_t u = 0; u < numVertices; ++u) {
            for (size_t v = 0; v < numVertices; ++v) {
                if (adjacencyMatrix[u][v] != 0 && dist[u] != numeric_limits<int>::max() &&
                    dist[u] + adjacencyMatrix[u][v] < dist[v]) {
                    if(g.getGraphType()==GraphType::UNDIRECTED && parent[u] == v) {
                        continue;
                    }
                    cerr << "Graph contains negative cycle" << endl;
                    return {}; // Return empty vector indicating negative cycle
                }
            }
        }

        // Build the shortest path vector
        vector<int> shortestPath;
        int currentVertex = end;
        while (currentVertex != start) {
            shortestPath.push_back(currentVertex);
            for (size_t u = 0; u < numVertices; ++u) {
                if (adjacencyMatrix[u][size_t(currentVertex)] != 0 &&
                    dist[u] + adjacencyMatrix[u][size_t(currentVertex)] == dist[size_t(currentVertex)]) {
                    currentVertex = (int)u;
                    break;
                }
            }
        }
        shortestPath.push_back(start);
        reverse(shortestPath.begin(), shortestPath.end());

        return shortestPath;
    }
    vector<int> BellmanFord::findNegativeCycle(Graph& g) {
        vector<int> cycle;
        vector<vector<int>> adjacencyMatrix = g.getAdjancencyMatrix();
        size_t numVertices = g.getNumVertices();
        vector<int> dist(numVertices, numeric_limits<int>::max());
        vector<int> parent(numVertices, -1); // Initialize parent vector with -1 (indicating no parent)

        // Initialize distance of the starting vertex to 0
        int start = 0; // Choose any starting vertex here
        dist[size_t(start)] = 0;

        // Relax all edges V-1 times
        for (size_t i = 0; i < numVertices - 1; ++i) {
            for (size_t u = 0; u < numVertices; ++u) {
                for (size_t v = 0; v < numVertices; ++v) {
                    if (adjacencyMatrix[u][v] != 0 && dist[u] != numeric_limits<int>::max() &&
                        dist[u] + adjacencyMatrix[u][v] < dist[v]) {
                        if(g.getGraphType()==GraphType::UNDIRECTED && parent[u] == v) {
                            continue;
                        }
                        dist[v] = dist[u] + adjacencyMatrix[u][v];
                        parent[v] = u; // Update parent vector
                    }
                }
            }
        }

        // Check for negative cycles
        for (size_t u = 0; u < numVertices; ++u) {
            for (size_t v = 0; v < numVertices; ++v) {
                if (adjacencyMatrix[u][v] != 0 && dist[u] != numeric_limits<int>::max() &&
                    dist[u] + adjacencyMatrix[u][v] < dist[v]) {
                    if(g.getGraphType()==GraphType::UNDIRECTED && parent[u] == v) {
                        continue;
                    }
                    // Found negative cycle, reconstruct it
                    int current = u;
                    while (parent[size_t(current)] != -1 && parent[size_t(current)] != u) { // Stop when cycle is completed
                        cycle.push_back(current);
                        current = parent[size_t(current)];
                    }
                    cycle.push_back(current); // Add the start vertex to complete the cycle
                    reverse(cycle.begin(), cycle.end()); // Reverse the cycle to get the correct order
                    cycle.push_back(current);
                    return cycle;
                }
            }
        }

        // No negative cycle found
        return {};
    }
    int BellmanFord::CalculatePathCost(vector<int>& path, vector<vector<int>>& adjacencyMatrix) {
        int totalCost = 0;
        for (size_t i = 0; i < path.size() - 1; ++i) {
            totalCost += adjacencyMatrix[size_t(path[i])][size_t(path[i + 1])];
        }
        return totalCost;
    }
}

