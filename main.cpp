#include <iostream>
#include "graph.h"
#include "cs225/PNG.h"
#include <string>
#include <iterator>
#include <vector>
using namespace std;

int main()
{
    // Write your own main here
    cout << "Add your own tests here! Modify main.cpp" << endl;
    graph SF("SF.cnode", "SF.cedge");
    graph::Iterator I = SF.begin();
    std::vector<int> v;
    while (I != SF.end()) {
         v.push_back(*I);
         //std::cout << "The current node is " << *I << std::endl;
         ++I;
    }
    // for (int i : SF.nodeID) {
    //     bool notIn = true;
    //     for (int j : v) {
    //         if (j == i) {
    //             notIn = false;
    //             break;
    //         }
    //     }
    //     if (notIn) {
    //         std::cout << "The node is not traversed is" << i << std::endl;
    //         break;
    //     }
    // }
    std::vector<int> first = SF.adjacencyList[0];
    std::vector<int> second = SF.adjacencyList[451];
    for (int i : first) {
        std::cout << "The edges adjcent to 0 include " << i << std::endl;
    }
    for (int i : second) {
        std::cout << "The edges adjcent to 451 include " << i << std::endl;
    }
    std::cout << "The number of edges are " << SF.edgeIDs.size() << std::endl;
    std::cout << "The number of nodes are " << SF.nodeID.size() << std::endl;
    std::cout << "The number of back edges are " << I.backEdges.size() << std::endl;
    return 0;
}
