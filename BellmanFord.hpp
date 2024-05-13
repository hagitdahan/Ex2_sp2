//hagitdahan101@gmail.com
//315158568
#ifndef BELLMANFORD_HPP
#define BELLMANFORD_HPP
#include "Graph.hpp"
#include "Algorithms.hpp"
#include <vector>
#include <limits>
#include <iostream>
#include <algorithm>
using namespace std;
namespace ariel{
    class BellmanFord{
    public:
        /**
         * using bellman ford that we learned and if the graph is undircted checkung the path from 2 sides
         * @param g
         * @param start
         * @param end
         * @return
         */
        static vector<int> ShortestPathB(Graph &g,int start,int end);
        /**
         * using bellman ford and then find the cycle by the parents
         * @param g
         * @return
         */
        static vector<int> findNegativeCycle(Graph& g);
        /**
         * for undirected graph when i need to find witch path is chipper from 2 sides
         * @param path
         * @param adjacencyMatrix
         * @return
         */
        static int CalculatePathCost(vector<int>& path, vector<vector<int>>& adjacencyMatrix);
    };
}
#endif