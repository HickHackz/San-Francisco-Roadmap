#include "dijkstra.h"
#include "graph.h"
#include <queue>
#include <map>
#include <cfloat>
#include <algorithm>


vector<int> dijkstra::dijkstraPath(graph Sanfran, int src, int dest){
    std::priority_queue<Node*, std::vector<Node*>, Compare> priority;
    map<int, Node*> nodeMap;
    vector<int> Verticies = Sanfran.getVertices();
    vector<Node*> allWeights;
    for (size_t i = 0; i < Verticies.size(); i++)
    {
        Node *newNode = new Node;
        newNode->nodeId = Verticies.at(i);
        newNode->visited = false;
        newNode->distance = DBL_MAX;
        allWeights.push_back(newNode);
        nodeMap[Verticies.at(i)] = newNode;
        if (Verticies.at(i) == src)
        {
            newNode->distance = 0;
            priority.push(newNode);
        }
    }
 
    //dijkstras using priority queue
    while (dest != priority.top()->nodeId)
        {
            Node *current = priority.top();
            priority.pop();
            if(current->visited == false) 
            {
                vector<int> neighbors = Sanfran.getAdjacentNodes(current->nodeId); //Find adjacent Nodes
                for (size_t i = 0; i < neighbors.size(); i++) 
                {
                    Node *neighbor = nodeMap[neighbors.at(i)];
                    if (neighbor->visited == false)
                    { 
                        double neighborWeight = Sanfran.getEdgeWeight(current->nodeId, neighbor->nodeId);  //find weight from node id
                        if (current->distance + neighborWeight < neighbor-> distance)
                        {
                            neighbor-> previous = current -> nodeId;
                            neighbor-> distance = current->distance + neighborWeight;
                        }
                        priority.push(neighbor);
                    }
                }
                current->visited = true;
            }
        } 
 
    vector<int> nodeShortestPath;
    vector<int> edgeShortestPath;
    Node *finalNode = nodeMap[dest];
    nodeShortestPath.push_back(finalNode->nodeId);
    int i = 0;
    while (nodeShortestPath.back() != src)
    {
        nodeShortestPath.push_back(nodeMap[nodeShortestPath.back()]->previous);
        edgeShortestPath.push_back(Sanfran.getEdge(nodeShortestPath[i], nodeShortestPath[i+1]));
        i++;
    }
    reverse(edgeShortestPath.begin(), edgeShortestPath.end());
    for (size_t i = 0; i < allWeights.size(); i++)
    {
        delete allWeights.at(i);
    }
    return edgeShortestPath;    
}
