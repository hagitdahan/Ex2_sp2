//hagitdahan101@gmail.com
//315158568
#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP
#include "Graph.hpp"
#include <iostream>
#include <cstddef>
#include <vector>
#include <queue>
#include <limits>

using namespace std;
namespace ariel{
    class Dijkstra{
    public:
        /**
         * using dijkstra to find shortest path for praph without negative edges.
         * @param g
         * @param source
         * @param destination
         * @return
         */
        static string shortestPathDijkstra(Graph& g, int source, int destination);
    };
}
#endif