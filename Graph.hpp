//hagitdahan101@gmail.com
//315158568
#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <vector>
#include <cstddef>
#include <iostream>
#include "GraphType.hpp"
#include <sstream>
using namespace std;
namespace ariel{
    class Graph{
    public:
        Graph();
        Graph(const Graph& other);
        bool isValid(const vector<vector<int>>& matrix);
        void loadGraph(const vector<vector<int>>& matrix);
        vector<int> getNeighbors(int vertex);
        const vector<vector<int>> getAdjancencyMatrix()const;
        size_t getNumVertices()const;
        GraphType getGraphType();
        WeightType getWeightType();
        EdgeType getEdgeType();
        int getWeight(int u,int v);
        int getNumEdges()const;
        bool sameSize(const Graph &other)const;
        friend std::ostream& operator<<(std::ostream& out,const Graph &g);
        string printGraph() const;
        Graph operator+(const Graph& otherGraph)const;
        Graph operator+() const;
        Graph operator+=(const Graph& otherGraph);
        Graph operator-(const Graph& otherGraph)const;
        Graph operator-() const;
        Graph operator-=(const Graph& otherGraph);

        bool isContaine(const Graph& other) const;
        bool operator>(const Graph& other) const;
        bool operator>=(const Graph& other) const;
        bool operator<(const Graph& other) const;
        bool operator<=(const Graph& other) const;
        bool operator!=(const Graph& other) const;
        bool operator==(const Graph& other) const;

        Graph& operator++();
        Graph operator++(int);
        Graph& operator--();
        Graph operator--(int);

        Graph operator*(const Graph& other) const;
        Graph&operator*=(double number);


    private:
        vector <vector<int>> adjancencyMatrix;
        size_t numOfVertices;
        int numEdges;
        GraphType graphType;
        WeightType weightType;
        EdgeType edgeType;


    };
}
#endif
