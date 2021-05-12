#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
#include <iterator>

class graph {
    private:
        
    public:
        std::vector<int> nodeID;
        std::vector<double> xLocs;
        std::vector<double> yLocs;
        std::vector<int> edgeIDs;
        std::vector<double> edgeLength;
        std::vector<int> startNode;
        std::vector<int> endNode;
        std::vector<std::vector<int>> adjacencyList;
        std::string file_to_string(const std::string & filename);
        std::vector<std::string> file_to_vector(const std::string & filename);
        graph(const std::string nodeInfo, const std::string edgeInfo);
        std::vector<int> incidentEdges(int Vertex) const;
        bool areAdjecent(int Vertex1, int Vertex2);
        mutable std::unordered_map<std::string, std::unordered_map<std::string, std::string>> adjacency;
        std::vector<int> getVertices() const;
        std::vector<int> getAdjacentNodes(int source) const;
        double getEdge(int source, int destination) const;
        double getEdgeWeight(int source, int destination) const;
        class Iterator : std::iterator<std::forward_iterator_tag, int> {
            public:
            Iterator();
            Iterator(int s, graph * graphUsed);

            Iterator & operator++();
            int operator*();
            bool operator!=(const graph::Iterator &other);
            std::vector<bool> exploredEdges;
            std::vector<int> discoveryEdges;
            std::vector<int> backEdges;
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
        Iterator begin();
        Iterator end();
};