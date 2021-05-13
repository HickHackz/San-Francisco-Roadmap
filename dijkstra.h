#pragma once
#include <vector>
#include "graph.h"
using namespace std;

class dijkstra {
    public:
        vector<int> dijkstraPath(graph Sanfran, int src, int dest);
        struct Node {
            int nodeId;
            int previous;
            double distance;
            bool visited;
            };
            class Compare
            {
                public:
                    bool operator() (dijkstra::Node *a, dijkstra::Node *b)
                    {
                        return a->distance > b->distance;
                    }
            };
    };