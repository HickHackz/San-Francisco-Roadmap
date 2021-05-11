#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <cstdlib>
#include <string>
#include <vector>
#include "graph.h"
#include "edge.h"
graph::Iterator::Iterator() {
    g = NULL;
}
graph::Iterator::Iterator(int s, graph * graphUsed) {
  /** @todo [Part 1] */
  start = s;
  current = start;
  g = graphUsed;
  for (int i : g->nodeID) {
      visited.push_back(false);
  }
  for (int j : g->edgeIDs) {
      exploredEdges.push_back(false);
  }
  //add(start);
  visited[start] = true;
  bool extrpop = false;
  nodeUsed.push(start);
  //current = t->pop();
}

graph::Iterator & graph::Iterator::operator++() {
  /** @todo [Part 1] */
  //t->add(current);
  //visited[current.x][current.y] = true;
  if (!nodeUsed.empty()) {
    int origionalCurrent = current; //check for empty
    if (!extrpop) {
      origionalCurrent = nodeUsed.top();
      nodeUsed.pop();
    }
    else {
      extrpop = false;
    }
    current = origionalCurrent;
    visited[origionalCurrent] = true;
    for (int i : g->incidentEdges(origionalCurrent)) {
        int node = 0;
        if (g->startNode[i] != origionalCurrent) {
            node = g->startNode[i];
        }
        else {
            node = g->endNode[i];
        }
        if (!visited[node]) {
            visited[node] = true;
            nodeUsed.push(node);
            if (exploredEdges[i] == false) {
                exploredEdges[i] = true;
                discoveryEdges.push_back(i);
            }
        }
        else {
            if (exploredEdges[i] == false) {
                exploredEdges[i] = true;
                backEdges.push_back(i);
            }
        }
    }
  if (nodeUsed.empty() == false) {
    current = nodeUsed.top();
  }
//   while (visited[current] && !nodeUsed.empty()) {
//     current = nodeUsed.top();
//     nodeUsed.pop();
//     extrpop = true;
//   }
//   if (visited[current] && nodeUsed.empty()) {
//     current = origionalCurrent;
//   }
//   if (!visited[current] && !(current == origionalCurrent) && nodeUsed.empty()) {
//     nodeUsed.push(current);
//   }
} 
  return *this;
}


/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
int graph::Iterator::operator*() {
  /** @todo [Part 1] */
  return current;
}
bool graph::Iterator::operator!=() {
    if (g == NULL) {
        return false;
    }
    if (nodeUsed.empty()) {
        return false;
    }
    return true;
}
Iterator graph::begin() {
    return Iterator(0, this);
}
Iterator graph::end() {
    return Iterator();
}
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
    std::string str;

    while (std::getline(text, str)){
        if (str.size() > 0) out.push_back(str);
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
           // std::cout << subs << std::endl;
            if (count % 3 == 0) {
                double num = std::stod(&subs[0], &sz);
                int n = int(num);
                nodeID.push_back(n);
                //std::cout << n << std::endl;
            }
            if (count % 3 == 1) {
                double num = std::stod(&subs[0], &sz);
                xLocs.push_back(num);
                //std::cout << num << std::endl;

                iss >> subs;
                num = std::stod(&subs[0], &sz);
                yLocs.push_back(num);
               // std::cout << num << std::endl;
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
                //std::cout << n << std::endl;
            }
            if (count % 4 == 1) {
                double n = std::stod(&subs[0], &sz);
                startNode.push_back(n);
               //std::cout << n << std::endl;
            }
            if (count % 4 == 2) {
                double n = std::stod(&subs[0], &sz);
                endNode.push_back(n);
                //std::cout << n << std::endl;

                iss >> subs;
                n = std::stod(&subs[0], &sz);
                edgeLength.push_back(n);
               // std::cout << n << std::endl;
            }
            
            count += 1;
        } while (iss);
    }
    for (int i : nodeID) {
        std::vector<int> a;
        adjacencyList.push_back(a);
    }
    for (int j : edgeIDs) {
        adjacencyList[startNode[j]].push_back(j);
        adjacencyList[endNode[j]].push_back(j);
    }


std::vector<int> graph::incidentEdges(int c) {
    return adjacencyList[c];
}
bool graph::areAdjecent(int c1, int c2) {
    std::vector<int> edges = incidentEdges(c1);
    for (int i : edges) {
        if (startNode[i] == c2 || endNode[i] == c2) {
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
