#include <iostream>
#include "graph.h"
#include "dijkstra.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
    cout << "Add your own tests here! Modify main.cpp" << endl;
    graph SF("SF.cnode", "SF.cedge");
    vector<int> edges = SF.getAdjacent(2);
    for (int i : edges) {
    cout << edges[i] << endl;
    }
    return 0;
}
