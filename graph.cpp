#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <graph.h>
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
        istringstream iss(row);
        do {
            std::string subs;
            iss >> subs;
            double num = double(subs);
            if (count % 3 == 0) {
                int n = int(num);
                nodeID.push_back(n);
            }
            if (count % 3 == 1) {
                xLocs.push_back(num);
            }
            if (count % 3 == 2) {
                yLocs.push_back(num);
            }
            count += 1;
        } while (iss);

    }
    for (unsigned i = 0; i < edgeI.size(); i++) {
        std::string row = edgeI[i];
        int count = 0;
        istringstream iss(row);
        do {
            std::string subs;
            iss >> subs;
            double num = double(subs);
            int n = int(num);
            if (count % 4 == 0) {
                //int n = int(num);
                edgeIDs.push_back(n);
            }
            if (count % 4 == 1) {
                startNode.push_back(n);
            }
            if (count % 4 == 2) {
                endNode.push_back(n);
            }
            if (count % 4 == 3) {
                edgeLength.push_back(num);
            }
            count += 1;
        } while (iss);
    }

}
std::vector<int> graph::incidentEdges(int Vertex) {
    std::vector<int> result;
    for (unsigned i = 0; i < edgeIDs.size(); i++) {
        if (startNode[i] == Vertex || endNode[i] == Vertex) {
            result.push_back(edgeIDs[i]);
        }
    }
    return result;
}
bool graph::areAdjecent(int Vertex1, int Vertex2) {
    std::vector<int> edges = incidentEdges(Vertex1);
    for (int i : edges) {
        if (startNode[i] == Vertex2 || endNode[i] == Vertex2) {
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


