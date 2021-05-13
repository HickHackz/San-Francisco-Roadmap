#include "../cs225/catch/catch.hpp"
#include <iostream>
#include "../graph.h"
#include "../dijkstra.h"
#include "../cs225/PNG.h"
#include <string>
#include <iterator>
#include <vector>
using namespace cs225;

graph establishGraph() {
     graph SF("SF.cnode", "SF.cedge");
     return SF;
}
TEST_CASE("adjanency", "[weight=3]") {
    graph SF("SF.cnode", "SF.cedge");
    REQUIRE(SF.adjacencyList[0][0] == 0);
    REQUIRE(SF.adjacencyList[0][1] == 1);
    REQUIRE(SF.adjacencyList[0][2] == 2);
}
TEST_CASE("DFS traversal", "[weight=1]") {
    graph SF("SF.cnode", "SF.cedge");
    graph::Iterator I = SF.begin();
    std::vector<int> v;
    while (I != SF.end()) {
         v.push_back(*I);
         //std::cout << "The current node is " << *I << std::endl;
         ++I;
    }
    REQUIRE((SF.edgeIDs.size()-(SF.nodeID.size()-1)) == I.backEdges.size());
}
TEST_CASE("Dikstra", "[weight=2]") {
    graph SF("SF.cnode", "SF.cedge");
    dijkstra Dijkstra;
    vector<int> edges = Dijkstra.dijkstraPath(SF, 0, 6);
    REQUIRE(edges[0] == 0);
    REQUIRE(edges[1] == 222877);
}