#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;

TEST_CASE("Test graph addition"){
    //checking regular add like g3=g1+g2
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g1 + g2;
    vector<vector<int>> expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    CHECK(g3.printGraph() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");
    // perform unary addition
    ariel::Graph g4 = +g3;
    vector<vector<int>> expectedGraph2 = {
            {0, 2, 1},
            {2, 0, 3},
            {1, 3, 0}};

    CHECK(g4.printGraph() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");
    //checking addition lika g4+=g4
    g4+=g4;
    CHECK(g4.printGraph() == "[0, 4, 2]\n[4, 0, 6]\n[2, 6, 0]");
    //checking add 1 g4++
    g3=g4++;
    CHECK(g4.printGraph() == "[0, 5, 3]\n[5, 0, 7]\n[3, 7, 0]");
    //g3 get g4 before g4++
    CHECK(g3.printGraph()== "[0, 4, 2]\n[4, 0, 6]\n[2, 6, 0]");
    //checking ++g5
    // Define a graph with known values
    ariel::Graph g5;
    vector<vector<int>> graph4 = {
            {0, 1, 2},
            {3, 0, 5},
            {6, 7, 0}};
    g5.loadGraph(graph4);

    // Apply the prefix increment operator
    //g3 get ++g5
    g3=++g5;
    vector<vector<int>> expected = {
            {0, 2, 3},
            {4, 0, 6},
            {7, 8, 0}};

    vector<vector<int>> matG5 = g5.getAdjancencyMatrix();
    vector<vector<int>> matG3=g3.getAdjancencyMatrix();
    for (size_t i = 0; i < expected.size(); ++i) {
        for (size_t j = 0; j < expected[i].size(); ++j) {
            CHECK_EQ(matG5[i][j], expected[i][j]);
            CHECK_EQ(matG3[i][j], expected[i][j]);
        }
    }
    g3=++++g5;
    vector<vector<int>> expected2 = {
            {0, 4, 5},
            {6, 0, 8},
            {9, 10, 0}};

    vector<vector<int>> matG5_ = g5.getAdjancencyMatrix();
    vector<vector<int>> matG3_=g3.getAdjancencyMatrix();
    for (size_t i = 0; i < expected2.size(); ++i) {
        for (size_t j = 0; j < expected2[i].size(); ++j) {
            CHECK_EQ(matG5_[i][j], expected2[i][j]);
            CHECK_EQ(matG3_[i][j], expected2[i][j]);
        }
    }
}
TEST_CASE("Test graph subtraction"){
    //checking regular subtraction like g3=g1-g2
    ariel::Graph g1;
    vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
            {0, 1, 1},
            {1, 0, 2},
            {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g1 - g2;
    vector<vector<int>> expectedGraph = {
            {0, 0, -1},
            {0, 0, -1},
            {-1, -1, 0}};
    CHECK(g3.printGraph() == "[0, 0, -1]\n[0, 0, -1]\n[-1, -1, 0]");
    // perform unary subtraction
    ariel::Graph g4 = -g3;
    vector<vector<int>> expectedGraph2 = {
            {0, 0, 1},
            {0, 0, 1},
            {1, 1, 0}};

    CHECK(g4.printGraph() == "[0, 0, 1]\n[0, 0, 1]\n[1, 1, 0]");
    //checking subtraction lika g4-=g4
    g4-=g4;
    CHECK(g4.printGraph() == "[0, 0, 0]\n[0, 0, 0]\n[0, 0, 0]");
    //checking add 1 g4++
    g3=g4--;
    CHECK(g4.printGraph() == "[0, 0, 0]\n[0, 0, 0]\n[0, 0, 0]");
    //g3 fet g4 before -- but every edge == 0 so the matrix stay the same
    CHECK(g3.printGraph() == "[0, 0, 0]\n[0, 0, 0]\n[0, 0, 0]");
    //checking --g5
    // Define a graph with known values
    ariel::Graph g5;
    vector<vector<int>> graph4 = {
            {0, 1, 2},
            {3, 0, 5},
            {6, 7, 0}};
    g5.loadGraph(graph4);

    // Apply the prefix increment operator
    //g3 get --g5
    g3=--g5;
    vector<vector<int>> expected = {
            {0, 0, 1},
            {2, 0, 4},
            {5, 6, 0}};

    vector<vector<int>> matG5 = g5.getAdjancencyMatrix();
    vector<vector<int>> matG3=g3.getAdjancencyMatrix();
    for (size_t i = 0; i < expected.size(); ++i) {
        for (size_t j = 0; j < expected[i].size(); ++j) {
            CHECK_EQ(matG5[i][j], expected[i][j]);
            CHECK_EQ(matG3[i][j], expected[i][j]);
        }
    }

}
TEST_CASE("Test graph multiplication"){
    //checking multiple like g4=g1*g2
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g4 = g1 * g2;
    vector<vector<int>> expectedGraph = {
        {0, 0, 2},
        {1, 0, 1},
        {1, 0, 0}};
    CHECK(g4.printGraph() == "[0, 0, 2]\n[1, 0, 1]\n[1, 0, 0]");
    //checking multiple like g4*=2
    g4*=2;
    CHECK(g4.printGraph()== "[0, 0, 4]\n[2, 0, 2]\n[2, 0, 0]");

}
TEST_CASE("Test operators >,<,<=,>="){
    //g2 > g1 because g2 contains g1
    ariel::Graph g1;
    vector<vector<int>> graph = {
            {0, 1},
            {1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
            {0, 1, 1},
            {1, 0, 2},
            {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    CHECK_EQ(g2>g1,true);
    CHECK_EQ(g2>=g1,true);
    CHECK_EQ(g1==g2, false);
    CHECK_EQ(g2<g1, false);
    ariel::Graph g3;
    vector<vector<int>> graph2 = {
            {0, 1},
            {1, 0}};
    g3.loadGraph(graph2);
    CHECK_EQ(g3==g1,true);
    CHECK_EQ(g3>=g1,true);
    ariel::Graph g4;
    vector<vector<int>> graph3 = {
            {0, 3},
            {3, 0}};
    g4.loadGraph(graph3);
    CHECK_EQ(g4!=g3,true);
    CHECK_EQ(g4>=g3,false);
    //g6 > g5 by num of edges
    ariel::Graph g5;
    vector<vector<int>> graph4 = {
            {0, 2, 0},
            {1, 0, 2},
            {0, 0, 0}};
    g1.loadGraph(graph4);
    ariel::Graph g6;
    vector<vector<int>> graph5 = {
            {0, 2, 1},
            {2, 0, 2},
            {1, 2, 0}};
    g2.loadGraph(graph5);
    CHECK_EQ(g6>g5,true);
    CHECK_EQ(g6>=g5,true);
    //g7>g6 by num of vertices
    ariel::Graph g7;
    vector<vector<int>> graph7 = {
            {0, 2, 1, 1},
            {2, 0, 2, 0},
            {1, 2, 0, 1},
            {1, 2, 0, 0}};
    g7.loadGraph(graph7);
    CHECK_EQ(g7>g6,true);
    CHECK_EQ(g7>=g6,true);
}
TEST_CASE("Invalid operations"){
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1, 1},
        {1, 0, 2, 1},
        {1, 2, 0, 1},
        {1, 1, 1, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g5;
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g5.loadGraph(graph2);
    CHECK_THROWS(g5 * g1);
    CHECK_THROWS(g1 * g2);

    // Addition of two graphs with different dimensions
    ariel::Graph g6;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g6.loadGraph(graph3);
    CHECK_THROWS(g1 + g6);
}
TEST_CASE("Algorithms"){
    ariel::Graph g;
    vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);
    //now there is no edge in the graph g so the graph should be not connected
    g--;
    CHECK(ariel::Algorithms::isConnected(g) == false);
    //return g to the start point
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0 -> 1 -> 2");
    //now there is no path from 0 to 2
    g--;
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "No path exists from source to destination.");
    vector<vector<int>> graph2 = {
            {0, 1, 1, 0, 0},
            {1, 0, 1, 0, 0},
            {1, 1, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "No path exists from source to destination.");
    g++;
    //if there is no path and im doing ++ to g, its also return false because when there is no edge im doing nothing
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "No path exists from source to destination.");
    ariel::Graph g2;
    vector<vector<int>> graph3={{0, 1, 0, 0, 0},
                               {0, 0, -5, 0, 0},
                               {2, 0, 0, 0, 0},
                               {0, 0, 0, 0, 2},
                               {0, 0, 0, 0, 0}};
    g2.loadGraph(graph3);
    CHECK(ariel::Algorithms::negativeCycle(g2)=="the Negative Cycle is:1 2 0 1 ");
    ++++++++g2; //like g2=g2+5 now there is no negative cycle
    CHECK(ariel::Algorithms::negativeCycle(g2)=="");
    ariel::Graph g3;
    vector<vector<int>> graph5={{0, 0, 0, 0, 0},
                               {0, 0, 0, 0, 0},
                               {0, 0, 0, 0, 0},
                               {0, 0, 0, 0, 0},
                               {0, 0, 0, 0, 0}};
    g3.loadGraph(graph5);
    //there is no negative cycle
    CHECK(ariel::Algorithms::negativeCycle(g3)=="");
    //now there is
    ariel::Graph g4;
    vector<vector<int>> graph6={{0, 1, 0, 0, 0},
                                {0, 0, -5, 0, 0},
                                {2, 0, 0, 0, 0},
                                {0, 0, 0, 0, 2},
                                {0, 0, 0, 0, 0}};
    g4.loadGraph(graph6);
    g2=g4+g3;
    CHECK(ariel::Algorithms::negativeCycle(g2)=="the Negative Cycle is:1 2 0 1 ");
    ariel::Graph g5;
    vector<vector<int>> graph7 = {
            {0, 1, 1, 0, 0},
            {1, 0, 1, 0, 0},
            {1, 1, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}};
    g5.loadGraph(graph7);
    CHECK(ariel::Algorithms::isContainsCycle(g5) == "The cycle is: 0 -> 1 -> 2 -> 0");
    ariel::Graph g6;
    //now i will sub g6 from g5 then the edge from 1 to 2 will disconnect
    //and the edge between 0 to 1
    vector<vector<int>> graph8 = {
            {0, 1, 1, 0, 0},
            {1, 0, 0, 0, 0},
            {0, 1, 0, 1, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}};
    g6.loadGraph(graph8);
    g2=g5-g6;
    CHECK(ariel::Algorithms::isContainsCycle(g2) == "No cycle exsist");
    vector<vector<int>> graph9 = {
            {0, 1, 1, 0, 0},
            {1, 0, 1, 0, 0},
            {1, 1, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}};
    g6.loadGraph(graph9);
    CHECK(ariel::Algorithms::isContainsCycle(g6) == "The cycle is: 0 -> 1 -> 2 -> 0");
    CHECK(ariel::Algorithms::isBipartite(g6)=="Graph is not bipartite");
    //if i will check on g2 thant not contain odd cycle its wil be true
    CHECK(ariel::Algorithms::isBipartite(g2)=="The Graph is bipartite: A={0 1 3 4 }, B={2 }");

}