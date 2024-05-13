//hagitdahan101@gmail.com
//315158568
#include "Dijkstra.hpp"
using namespace std;
namespace ariel{
    string Dijkstra::shortestPathDijkstra(Graph& g, int source, int destination){
        size_t numVertices = g.getNumVertices();
        vector<int> dist(numVertices, numeric_limits<int>::max());
        vector<bool> visited(numVertices, false);
        vector<int> prev(numVertices, -1);

        dist[size_t(source)] = 0;

        for (size_t i = 0; i < numVertices - 1; ++i) {
            int u = -1;
            int minDist = numeric_limits<int>::max();
            for (size_t v = 0; v < numVertices; ++v) {
                if (!visited[v] && dist[v] < minDist) {
                    u = v;
                    minDist = dist[v];
                }
            }
            if (u == -1) break;
            visited[size_t(u)] = true;

            for (size_t v = 0; v < numVertices; ++v) {
                int weight = g.getWeight(u,v);
                if (weight != 0 && dist[size_t(u)] + weight < dist[v]) {
                    dist[v] = dist[size_t(u)] + weight;
                    prev[v] = u;
                }
            }
        }

        if (prev[size_t(destination)] == -1) {
            return "No path exists from source to destination.";
        }

        string path = to_string(destination);
        int current = destination;
        while (prev[size_t(current)] != -1) {
            current = prev[size_t(current)];
            path = to_string(current) + " -> " + path;
        }

        return path;
    }
}