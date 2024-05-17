//hagitdahan101@gmail.com
//315158568
#include "Graph.hpp"
#include "GraphType.hpp"
using namespace std;
namespace ariel{

    Graph::Graph(): numOfVertices(0), numEdges(0), adjancencyMatrix(), graphType(GraphType::UNDIRECTED), weightType(WeightType::UNWEIGHTED), edgeType(EdgeType::NON_NEGATIVE) {}
    //copy contructor
    Graph::Graph(const Graph& other) :
            numOfVertices(other.numOfVertices),
            numEdges(other.numEdges),
            adjancencyMatrix(other.adjancencyMatrix),
            graphType(other.graphType),
            weightType(other.weightType),
            edgeType(other.edgeType) {
    }

    const vector<vector<int>> Graph::getAdjancencyMatrix() const{return adjancencyMatrix;}
    bool Graph::isValid(const vector<vector<int>>& matrix){
        // Check if the matrix is square
        size_t size = matrix.size();
        for(size_t j=0;j<size;j++) {
            {
                if (matrix[j].size() != size) {
                    return false;
                }
            }
        }
        //check if there is edge in adj[i][i]
        for(size_t i=0;i<size;i++){
            for(size_t j=0;j<size;j++){
                if(matrix[i][j]!=0 && i==j) return false;
            }
        }
        if(size==1) return false;
        return true;

    }
    void Graph::loadGraph(const vector<vector<int>> &matrix) {
        // Check if the graph is a square matrix
        if (!isValid(matrix)) {
            throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
        }

        // Load the graph data
        try {
            numOfVertices = matrix.size();
            adjancencyMatrix = matrix;

            // Count the number of edges if needed
            numEdges = 0;
            for (size_t i = 0; i < numOfVertices; ++i) {
                for (size_t j = 0; j < numOfVertices; ++j) {
                    if (adjancencyMatrix[i][j] != 0) {
                        ++numEdges;
                    }
                }
            }
            graphType = GraphType::UNDIRECTED;
            // Check if the graph is directed
            for (size_t i = 0; i < numOfVertices; ++i) {
                for (size_t j = 0; j < numOfVertices; ++j) {
                    if (adjancencyMatrix[i][j] != adjancencyMatrix[j][i]) {
                        graphType = GraphType::DIRECTED;
                        break;
                    }
                }
            }
            if(graphType==GraphType::UNDIRECTED) this->numEdges=this->numEdges/2;
            edgeType = EdgeType::NON_NEGATIVE;
            // Check if there are negative edges
            for (size_t i = 0; i < numOfVertices; ++i) {
                for (size_t j = 0; j < numOfVertices; ++j) {
                    if (adjancencyMatrix[i][j] < 0) {
                        edgeType = EdgeType::ALLOW_NEGATIVE;
                        break;
                    }
                }
            }
            weightType = WeightType::UNWEIGHTED;
            // Check if the edges are weighted
            for (size_t i = 0; i < numOfVertices; ++i) {
                for (size_t j = 0; j < numOfVertices; ++j) {
                    if (adjancencyMatrix[i][j] != 1 && adjancencyMatrix[i][j] != 0) {
                        weightType = WeightType::WEIGHTED;
                        break;
                    }
                }
            }
        } catch (const exception& e) {
            // Handle any exceptions thrown during graph loading
            cerr << "Error loading graph: " << e.what() << endl;
            throw; // Re-throw the exception
        }

    }
    size_t Graph::getNumVertices()const{return this->numOfVertices;}
    vector<int> Graph::getNeighbors(int vertex){
        vector<int> neighbors;
        for (size_t i = 0; i < adjancencyMatrix[size_t(vertex)].size(); ++i) {
            if (adjancencyMatrix[size_t(vertex)][i] != 0) {
                neighbors.push_back(i);
            }
        }
        return neighbors;
    }
    GraphType Graph::getGraphType(){return this->graphType;}
    WeightType Graph::getWeightType(){return this->weightType;}
    EdgeType Graph::getEdgeType(){return this->edgeType;}
    int Graph::getWeight(int u,int v){return adjancencyMatrix[size_t(u)][size_t(v)];}
    int Graph::getNumEdges()const {return this->numEdges;}
    /**
     * Help function to check if two graphs have the same dimensions
     * @param other
     * @return
     */
    bool Graph::sameSize(const Graph& other) const {
        //vector<vector<int>> adj1=g1.getAdjancencyMatrix();
        const vector<vector<int>> &adj2=other.getAdjancencyMatrix();
        // Check if both graphs have the same dimensions
        if (adjancencyMatrix.size() != adj2.size() ||
            adjancencyMatrix[0].size() != adj2[0].size()) {
            std::cerr << "Error: Graphs must have the same dimensions for addition." << std::endl;
            return false;
        }
        return true;
    }
    /**
     * overload operator << to print graph on the terminal
     * @param out
     * @param g
     * @return
     */
    std::ostream& operator<<(std::ostream& out, const Graph& g) {
        vector<vector<int>> adjacencyMatrix = g.getAdjancencyMatrix();
        for (size_t i = 0; i < adjacencyMatrix.size(); ++i) {
            out << "[";
            for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j) {
                out << adjacencyMatrix[i][j];
                if (j < adjacencyMatrix[i].size() - 1) {
                    out << ", ";
                }
            }
            out << "]";
            if (i < adjacencyMatrix.size() - 1) {
                out << endl; // Add a newline after each row except the last one
            }
        }
        return out;
    }
    string Graph::printGraph() const {
        stringstream ss;
        ss << *this; // Utilize the existing operator<< overload
        return ss.str();
    }
    /**
     * Overload + operator to add two graphs
     * @param otherGraph
     * @return
     */
    Graph Graph::operator+(const Graph& otherGraph)const{
        if (!sameSize(otherGraph)) {
            throw invalid_argument("Error: Graphs must have the same dimensions for addition.");
        } else {
            Graph res;
            vector<vector<int>> resultMatrix;
            // Add corresponding elements of the adjacency matrices
            for (size_t i = 0; i < adjancencyMatrix.size(); ++i) {
                vector<int> row;
                for (size_t j = 0; j < adjancencyMatrix[i].size(); ++j) {
                    row.push_back(adjancencyMatrix[i][j] + otherGraph.adjancencyMatrix[i][j]);
                }
                resultMatrix.push_back(row);
            }

            res.loadGraph(resultMatrix);
            return res;
        }
    }
    /**
     * overload operator + (unary)
     * @return
     */
    Graph Graph::operator+() const{
        return Graph(*this);
    }
    /**
     * overload operator +=
     * @param otherGraph
     * @return update this
     */
    Graph Graph::operator+=(const Graph& otherGraph){
        if (!sameSize(otherGraph)) {
            throw invalid_argument("Error: Graphs must have the same dimensions for addition.");
        } else {
            vector<vector<int>> adjother=otherGraph.getAdjancencyMatrix();
            // Add corresponding elements of the adjacency matrices
            for (size_t i = 0; i < adjancencyMatrix.size(); ++i) {
                for (size_t j = 0; j < adjancencyMatrix[i].size(); ++j) {
                    this->adjancencyMatrix[i][j]+=adjother[i][j];
                }
            }
            return *this;
        }
    }
    /**
   * Overload - operator to subtract two graphs
   * @param otherGraph
   * @return
   */
    Graph Graph::operator-(const Graph& otherGraph)const{
        if (!sameSize(otherGraph)) {
            throw invalid_argument("Error: Graphs must have the same dimensions for addition.");
        } else {
            Graph res;
            vector<vector<int>> resultMatrix;
            // Add corresponding elements of the adjacency matrices
            for (size_t i = 0; i < adjancencyMatrix.size(); ++i) {
                vector<int> row;
                for (size_t j = 0; j < adjancencyMatrix[i].size(); ++j) {
                    row.push_back(adjancencyMatrix[i][j] - otherGraph.adjancencyMatrix[i][j]);
                }
                resultMatrix.push_back(row);
            }

            res.loadGraph(resultMatrix);
            return res;
        }
    }
    /**
 * overload operator - (unary)
 * @return
 */
    Graph Graph::operator-() const{
        Graph ans(*this);
        for (size_t i = 0; i < adjancencyMatrix.size(); ++i) {
            for (size_t j = 0; j < adjancencyMatrix[i].size(); ++j) {
                ans.adjancencyMatrix[i][j]*=-1;
            }
        }
        return ans;
    }
    /**
    * overload operator -=
    * @param otherGraph
    * @return update this
    */
    Graph Graph::operator-=(const Graph& otherGraph){
        if (!sameSize(otherGraph)) {
            throw invalid_argument("Error: Graphs must have the same dimensions for addition.");
        } else {
            vector<vector<int>> adjother=otherGraph.getAdjancencyMatrix();
            // Add corresponding elements of the adjacency matrices
            for (size_t i = 0; i < adjancencyMatrix.size(); ++i) {
                for (size_t j = 0; j < adjancencyMatrix[i].size(); ++j) {
                    this->adjancencyMatrix[i][j]-=adjother[i][j];
                }
            }
            return *this;
        }
    }

    /**
     * Checking if the current graph contains another graph
     * @param other
     * @return true if yes else false
     */
    bool Graph::isContaine(const Graph& other) const {
        //if the number of vertices in other big then this return false
        if(numOfVertices<other.numOfVertices)return false;
        // Determine the number of vertices to iterate over (minimum of the two graphs)
        size_t minVertices = std::min(numOfVertices, other.numOfVertices);

        // Check if each edge of the other graph exists in this graph
        for (size_t u = 0; u < minVertices; ++u) {
            for (size_t v = 0; v < minVertices; ++v) {
                // Check if the edge in the other graph exists
                if (other.adjancencyMatrix[u][v] != 0) {
                    // Check if the edge in this graph differs
                    if (adjancencyMatrix[u][v] != other.adjancencyMatrix[u][v]) {
                        return false;
                    }
                }
            }
        }
        return true;
    }
    /**
     * Checking if current graph contains other
     * @param other
     * @return
     */
    bool Graph::operator>(const Graph& other) const{
        //here im checking if this graph contains other graph
        if (isContaine(other)) {
            return true;
        }
        //here im checking if other graph contains this graph
        if (other.isContaine(*this)) {
            return false;
        }
        //checking by num f edges
        int numEdgesG1 = getNumEdges();
        int numEdgesG2 = other.getNumEdges();
        if (numEdgesG1 != numEdgesG2) {
            return (numEdgesG2 > numEdgesG1);
        }
        //checking by num of vertices
        size_t orderG1 = numOfVertices;
        size_t orderG2 = other.getNumVertices();
        return (orderG2 > orderG1);
    }
    /**
   * overload operator >= between two graph objects
   * @param other
   * @return true if other contain / equal to this graph
   */
    bool Graph::operator>=(const Graph& other) const{
        if (isContaine(other)) {
            return true;
        }
        return *this == other || numEdges > other.numEdges;
    }
    /**
   * Checking if other graph contains current
   * @param other
   * @return
   */
    bool Graph::operator<(const Graph& other)const
    {
        //here im checking if other graph contain this graph
        if (other.isContaine(*this)) {
            return true;
        }
        //here im checking if this graph contains other graph
        if (isContaine(other)) {
            return false;
        }
        //checking by num f edges
        int numEdgesG1 = getNumEdges();
        int numEdgesG2 = other.getNumEdges();
        if (numEdgesG1 != numEdgesG2) {
            return (numEdgesG2 < numEdgesG1);
        }
        //checking by num of vertices
        size_t orderG1 = numOfVertices;
        size_t orderG2 = other.getNumVertices();
        return (orderG2 < orderG1);

    }
    /**
    * overload operator <= between two graph objects
    * @param other
    * @return true if other contain / equal to this graph
    */
    bool Graph::operator<=(const Graph& other) const {
        if (other.isContaine(*this)) {
            return true;
        }
        return *this == other || numEdges < other.numEdges;
    }
    /**
    * overload operator == between two graph objects
    * @param other
    * @return
    */
    bool Graph::operator==(const Graph& other) const {
        return adjancencyMatrix == other.adjancencyMatrix;
    }
    /**
     * overload operator != between two graph objects
     * @param other
     * @return
     */
    bool Graph::operator!=(const Graph& other) const {
        return !(*this == other);
    }
    /**
     * overload operator ++graph
     * @return
     */
    Graph& Graph::operator++(){
        for (size_t i = 0; i < numOfVertices; ++i) {
            for (size_t j = 0; j < numOfVertices; ++j) {
                if(this->adjancencyMatrix[i][j]==0)continue;
                this->adjancencyMatrix[i][j]++;
            }
        }
        return *this;
    }
    /**
     * overload operator graph++
     * @return
     */
    Graph Graph::operator++(int){
        Graph res(*this);
        vector<vector<int>> resultMatrix(numOfVertices, vector<int>(numOfVertices, 0));
        for (size_t i = 0; i < numOfVertices; ++i) {
            for (size_t j = 0; j < numOfVertices; ++j) {
                if(this->adjancencyMatrix[i][j]==0)continue;
                resultMatrix[i][j]= this->adjancencyMatrix[i][j]++;
            }
        }
        res.loadGraph(resultMatrix);
        return res;
    }
    /**
     * overload operator --graph
     * @return
     */
    Graph& Graph::operator--(){
        for (size_t i = 0; i < numOfVertices; ++i) {
            for (size_t j = 0; j < numOfVertices; ++j) {
                if(this->adjancencyMatrix[i][j]==0)continue;
                this->adjancencyMatrix[i][j]--;
            }
        }
        return *this;
    }
    /**
     * overload operator graph--
     * @return
     */
    Graph Graph::operator--(int){
        Graph res(*this);
        vector<vector<int>> resultMatrix(numOfVertices, vector<int>(numOfVertices, 0));
        for (size_t i = 0; i < numOfVertices; ++i) {
            for (size_t j = 0; j < numOfVertices; ++j) {
                if(this->adjancencyMatrix[i][j]==0)continue;
                resultMatrix[i][j]= this->adjancencyMatrix[i][j]--;
            }
        }
        res.loadGraph(resultMatrix);
        return res;
    }
    /**
     * Doing multiple between two graphs size should by the same
     * @param other
     * @return new object graph after the multiplaction
     */
    Graph Graph::operator*(const Graph& other) const{
        // Check if the matrices are compatible for multiplication
        if (adjancencyMatrix[0].size() != other.adjancencyMatrix.size()) {
            throw std::invalid_argument("Error: Matrices are not compatible for multiplication.");
        }

        // Create a new matrix for the result
        vector<vector<int>> resultMatrix(adjancencyMatrix.size(), vector<int>(other.adjancencyMatrix[0].size(), 0));

        // Perform matrix multiplication
        for (size_t i = 0; i < adjancencyMatrix.size(); ++i) {
            for (size_t j = 0; j < other.adjancencyMatrix[0].size(); ++j) {
                for (size_t k = 0; k < adjancencyMatrix[0].size(); ++k) {
                    if(i==j) continue;
                    resultMatrix[i][j] += adjancencyMatrix[i][k] * other.adjancencyMatrix[k][j];
                }
            }
        }

        // Create a new graph and load the result matrix into it
        Graph resultGraph(*this);
        resultGraph.loadGraph(resultMatrix);

        return resultGraph;

    }
    /**
     * Doing multiple of number with graph
     * @param number
     * @return the same object after the multiplaction
     */
    Graph& Graph::operator*=(const double number){
        for (size_t i = 0; i < adjancencyMatrix.size(); ++i) {
            for (size_t j = 0; j < adjancencyMatrix[i].size(); ++j) {
                //if(adjancencyMatrix[i][j]==0)continue;
                adjancencyMatrix[i][j] *= number;
            }
        }
        return *this;
    }




}




