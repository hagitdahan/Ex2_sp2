//hagitdahan101@gmail.com
//315158568
#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP
#include <iostream>
#include "Graph.hpp"
#include "GraphType.hpp"
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include <cstddef>
#include <string>
using namespace std;
namespace ariel{
    class Algorithms {
    public:
        /**
         * Help function doing depth search in the graph, and all the visited vertices marked True
         * @param g
         * @param vertex
         * @param visited
         */
        static void dfs(Graph&g, int vertex, vector<bool>&visited);
        /**
         * using help func dfs, running DFS from all the vertices
         * @param g
         * @return true if all the vertices visited from all the vertices
         */
        static bool isConnected(Graph&g);
        /**
         * checking the tipe of the graph
         * if negative edge BellmanFord else Dijkstra
         * @param g
         * @param source
         * @param destination
         * @return
         */
        static string shortestPath(Graph&g, int source, int destination);
        /**
         * running DFS and paint the vertices in black when finish if there is Back edge there is a cycle
         * @param vertex
         * @param graph
         * @param colors
         * @param parent
         * @param visited
         * @param type
         * @return
         */
        static string dfsForCycle(int vertex, vector<vector<int>>& graph, vector<string>& colors, vector<int>& parent,vector<int>& visited,GraphType type);
        /**
         * using dfsForCycle to find cycle
         * @param g
         * @return
         */
        static string isContainsCycle(Graph& g);
        /**
         * using painting graph in two color if we can is bipartite else no
         * @param g
         * @return
         */
        static string isBipartite(Graph& g);
        /**
         * using bellman ford then find the cycle by the parent of the vertices
         * @param g
         * @return
         */
        static string negativeCycle(Graph& g);

    };
}
#endif


