//hagitdahan101@gmail.com
//315158568
#include "Algorithms.hpp"
#include "BellmanFord.hpp"
#include "Dijkstra.hpp"
#include "Graph.hpp"
#include "GraphType.hpp"
#include <vector>
using namespace std;
namespace ariel{
    void Algorithms::dfs(Graph &g, int vertex, vector<bool> &visited) {
        visited[size_t(vertex)] = true;
        const vector<int> &neighbors = g.getNeighbors(vertex);
        for (int neighbor : neighbors) {
            if (!visited[size_t(neighbor)]) {
                dfs(g, neighbor, visited);
            }
        }
    }
    bool Algorithms::isConnected(Graph &g) {
        const vector<vector<int>> matrix=g.getAdjancencyMatrix();
        size_t numVertices=g.getNumVertices();
        for (int i = 0; i < numVertices; ++i) {
            vector<bool> visited(numVertices, false);
            Algorithms::dfs(g, i, visited);

            // Check if all vertices are visited
            bool allVisited = true;
            for (bool v : visited) {
                if (!v) {
                    allVisited = false;
                    break;
                }
            }
            if (!allVisited) {
                return false; // Graph is not strongly connected
            }
        }

        return true; // Graph is strongly connected
    }
    string Algorithms::shortestPath(Graph& g, int source, int destination) {
        int totalWeight1=0;
        int totalWeight2=0;
        vector<vector<int>> adjMat=g.getAdjancencyMatrix();
        if(g.getNumEdges()==0) return "-1";
        if(g.getEdgeType()==EdgeType::ALLOW_NEGATIVE){
            vector<int> shortest= vector<int>(g.getNumVertices());
            vector<int> shortest2= vector<int>(g.getNumVertices());
            shortest=BellmanFord::ShortestPathB(g,source,destination);
            if(shortest.empty()) return "-1";
            totalWeight1=BellmanFord::CalculatePathCost(shortest,adjMat);
            if(g.getGraphType()==GraphType::UNDIRECTED) {
                shortest2 = BellmanFord::ShortestPathB(g, destination, source);
                totalWeight2 = BellmanFord::CalculatePathCost(shortest2, adjMat);

                if (totalWeight1 <= totalWeight2) {
                    string pathStr = to_string(shortest.at(0));
                    for (size_t i = 1; i < shortest.size(); ++i) {
                        pathStr += "->" + to_string(shortest.at(i));
                    }
                    return pathStr;
                }
                reverse(shortest2.begin(), shortest2.end());
                string pathStr = to_string(shortest2.at(0));
                for (size_t i = 1; i < shortest2.size(); ++i) {
                    pathStr += "->" + to_string(shortest2.at(i));
                }
                return pathStr;
            }
            string pathStr = to_string(shortest.at(0));
            for (size_t i = 1; i < shortest.size(); ++i) {
                pathStr += "->" + to_string(shortest.at(i));
            }
            return pathStr;
        }
        else {
            string path=Dijkstra::shortestPathDijkstra(g,source,destination);
            return path;

        }

    }
    string Algorithms::dfsForCycle(int vertex, vector<vector<int>>& graph, vector<string>& colors, vector<int>& parent,vector<int>&visited,GraphType type) {
        colors[size_t(vertex)] = "GRAY";
        visited[size_t(vertex)]=1;
        // Visit all neighbors of the current vertex
        for (size_t neighbor = 0; neighbor < graph.size(); ++neighbor) {
            if (graph[size_t(vertex)][neighbor] != 0) { // There is an edge from vertex to neighbor
                if (colors[neighbor] == "GRAY") { // Found a back edge, cycle detected
                    if (type == GraphType::UNDIRECTED && parent[size_t(vertex)] == neighbor) {
                        // Skip the edge if it is an undirected graph and the neighbor is the parent
                        continue;
                    }
                    string cycle = to_string(neighbor);
                    int current = vertex;
                    while (current != neighbor) {
                        cycle = to_string(current) + " -> " + cycle;
                        current = parent[size_t(current)];
                    }
                    cycle = to_string(neighbor) + " -> " +cycle; // Complete the cycle
                    return cycle;
                } else if (colors[neighbor] == "WHITE") { // Neighbor hasn't been visited yet
                    parent[neighbor] = vertex; // Update parent vertex
                    string cycle = dfsForCycle(neighbor, graph, colors, parent, visited, type); // Recursively explore the neighbor
                    if (!cycle.empty()) {
                        return cycle;
                    }
                }
            }
        }
        colors[size_t(vertex)] = "BLACK"; // All neighbors visited, mark vertex as done
        return ""; // No cycle found
    }
    string Algorithms::isContainsCycle(Graph& g) {
        vector<vector<int>> adj=g.getAdjancencyMatrix();
        size_t numOfVertices=g.getNumVertices();
        vector<string> colors(numOfVertices, "WHITE"); // Initialize all vertices as white (unvisited)
        vector<int> visited(numOfVertices,0);
        vector<int> parent(numOfVertices,-1);
        GraphType type = g.getGraphType();
        // Perform DFS from each vertex if it hasn't been visited yet
        for (int i = 0; i < numOfVertices; ++i) {
            if (colors[size_t(i)] == "WHITE") {
                string cycle = dfsForCycle(i, adj, colors, parent,visited,type);
                if (!cycle.empty()){
                    return "The cycle is: " +cycle;
                }
            }
        }

        return "No cycle exsist"; // No cycle found
    }
    string Algorithms::isBipartite(Graph& g) {
        size_t n = g.getNumVertices(); // Number of vertices
        vector<vector<int>> adj=g.getAdjancencyMatrix();
        vector<string> color(n, "WHITE");  // Vector to store the color of each vertex
        vector<int> groupA; //the BLUE vertex
        vector<int> groupB; //the RED vertex
        for (size_t u = 0; u < n; ++u) {
            if (color[u] == "WHITE") {
                color[u] = "BLUE";  // Start vertex is colored BLUE
                groupA.push_back(u);
                queue<int> Q;
                Q.push(u);          // Initialize queue with start vertex

                while (!Q.empty()) {
                    int u = Q.front();
                    Q.pop();
                    for (size_t v = 0; v < n; ++v) {
                        if (adj[size_t(u)][v] !=0) { // If there is an edge between u and v
                            if (color[v] == color[size_t(u)]) {  // If adjacent vertices have the same color, not bipartite
                                return "Graph is not bipartite";
                            }
                            if (color[v] == "WHITE") {
                                if (color[size_t(u)] == "BLUE") {
                                    color[v] = "RED";
                                    groupB.push_back(v);
                                } else {
                                    color[v] = "BLUE";
                                    groupA.push_back(v);
                                }
                                Q.push(v);  // Enqueue v
                            }
                        }
                    }
                }
            }
        }
        string groups="The Graph is bipartite: A={";
        for (int vertex : groupA) {
            groups += to_string(vertex) + " ";
        }
        groups+="}, B={";
        for (int vertex : groupB) {
            groups += to_string(vertex) + " ";
        }
        groups+="}";
        return groups;
    }
    string Algorithms::negativeCycle(Graph& g){
        vector<int> cycle= BellmanFord::findNegativeCycle(g);
        if (!cycle.empty()){
            string cyclePth="the Negative Cycle is:";
            for (int vertex : cycle) {
                cyclePth += to_string(vertex) + " ";
            }
            return cyclePth;
        }
        return "";

    }

}
