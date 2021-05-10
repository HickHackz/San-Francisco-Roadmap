#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
#include <iterator>
#include "edge.h"

class graph {
    private:
        std::vector<int> nodeID;
        std::vector<double> xLocs;
        std::vector<double> yLocs;
        std::vector<int> edgeIDs;
        std::vector<double> edgeLength;
        std::vector<int> startNode;
        std::vector<int> endNode;
        std::vector<std::vector<int>> adjacencyList;
    public:
        std::string file_to_string(const std::string & filename);
        std::vector<std::string> file_to_vector(const std::string & filename);
        graph(const std::string nodeInfo, const std::string edgeInfo);
        std::vector<int> incidentEdges(int Vertex);
        bool areAdjecent(int Vertex1, int Vertex2);
        mutable std::unordered_map<std::string, std::unordered_map<std::string, std::string>> adjacency;
        std::vector<std::string> getVertices() const;
        void addVertex(std::string v);
        void addEdge(std::string start, std::string end);
        edge setEdgeWeightandId(std::string start, std::string end, double weight, std::string id);
        double getEdgeWeight(std::string start, std::string end) const;
        double getEdgeId(std::string start, std::string end) const;
        class Iterator : std::iterator<std::forward_iterator_tag, int> {
            public:
            Iterator();
            Iterator(int s, graph * graphUsed);

            Iterator & operator++();
            int operator*();
            bool operator!=(const graph::Iterator &other);

            /** @todo [Part 1] */
            /** add member functions if neccesary*/

            private:
            /** @todo [Part 1] */
            /** add private members here if neccesary*/
            int start;
            int current;
            std::vector<bool> visited;
            bool extrpop;
            std::stack<int> nodeUsed;
            graph * g;
        };
};