#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>
#include "graph.h"
#include "edge.h"

std::string graph::file_to_string(const std::string & filename) {
    std::ifstream text(filename);
	
	std::stringstream strStream;
	if (text.is_open()) {
		strStream << text.rdbuf();
	}

	return strStream.str();
}
std::vector<std::string> graph::file_to_vector(const std::string & filename) {
    std::ifstream text(filename);
	std::vector<std::string> out;

	if (text.is_open()) {
		std::istream_iterator<std::string> iter(text);
		while (!text.eof()) {
			out.push_back(*iter);
			++iter;
		}
	}

	return out;
}
graph::graph(const std::string nodeInfo, const std::string edgeInfo) {
    std::vector<std::string> nodesI = file_to_vector(nodeInfo);
    std::vector<std::string> edgeI = file_to_vector(edgeInfo);
    for (unsigned i = 0; i < nodesI.size(); i++) {
        std::string row = nodesI[i];
        int count = 0;
        std::istringstream iss(row);
        std::string::size_type sz = 0;
        std::string subs;

        do {
            iss >> subs;
            std::cout << subs << std::endl;
            if (count % 3 == 0) {
                double num = std::stod(&subs[0], &sz);
                int n = int(num);
                nodeID.push_back(n);
                std::cout << n << std::endl;
            }
            if (count % 3 == 1) {
                double num = std::stod(&subs[0], &sz);
                xLocs.push_back(num);
                std::cout << num << std::endl;
            }
            if (count % 3 == 2) {
                double num = std::stod(&subs[0], &sz);
                yLocs.push_back(num);
                std::cout << num << std::endl;
            }
            count += 1;
        } while (iss);

    }
    for (unsigned i = 0; i < edgeI.size(); i++) {
        std::string row = edgeI[i];
        int count = 0;
        std::istringstream iss(row);
        std::string::size_type sz = 0;
        std::string subs;

        do {
            iss >> subs;
            double num = std::stod(subs, &sz);
            int n = int(num);
            if (count % 4 == 0) {
                //int n = int(num);
                double n = std::stod(&subs[0], &sz);
                edgeIDs.push_back(n);
                std::cout << n << std::endl;
            }
            if (count % 4 == 1) {
                double n = std::stod(&subs[0], &sz);
                edgeLength.push_back(n);
                std::cout << n << std::endl;
            }
            if (count % 4 == 2) {
                double n = std::stod(&subs[0], &sz);
                startNode.push_back(n);
                std::cout << n << std::endl;
            }
            if (count % 4 == 3) {
                double n = std::stod(&subs[0], &sz);
                endNode.push_back(n);
                std::cout << n << std::endl;
            }
            count += 1;
        } while (iss);
    }

}

std::vector<int> graph::incidentEdges(int std::string) {
    std::vector<int> result;
    for (unsigned i = 0; i < edgeIDs.size(); i++) {
        if (startNode[i] == std::string || endNode[i] == std::string) {
            result.push_back(edgeIDs[i]);
        }
    }
    return result;
}
bool graph::areAdjecent(int std::string1, int std::string2) {
    std::vector<int> edges = incidentEdges(std::string1);
    for (int i : edges) {
        if (startNode[i] == std::string2 || endNode[i] == std::string2) {
            return true;
        }
    }
    return false;
}

std::vector<std::string> Graph::getVertices() const
{
 vector<std::string> vertices;

 for(auto it = adjacency.begin(); it != adjacency.end(); it++)
 {
    vertices.push_back(it->first);
 }

 return vertices;
}

void graph::addVertex(std::string v)
{
    adjacency[v] = unordered_map<std::string, std::string>();
}

void graph::addEdge(std::string start, std::string end)
{
    if(adjacency.find(start) != adjacency.end() && adjacency[start].find(end)!= adjacency[start].end())
    {
        return;
    }

    if(adjacency.find(start) == adjacency.end())
    {
        adjacency[start] = unordered_map<std::string, std::string>();
    }

    adjacency[start][end] = edge(start, end);
    if(adjacency.find(end)== adjacency.end())
    {
        adjacency[end] = unordered_map<std::string, std::string>();
    }
}

edge graph::setEdgeWeightAndId(std::string start, std::string end, double weight, std::string id)
{
    edge e = adjacency[start][end];
    edge ret(start, end, weight, id);
    adjacency[start][end] = ret;
    return ret;
}

double Graph::getEdgeWeight(std::string start, std::string end) const
{
    return adjacency[start][end].getWeight();
}

edge graph::getEdgeId(std::string start , std::string end) const
{
    Edge e = adjacency[source][destination].getId();
    return e;
}

