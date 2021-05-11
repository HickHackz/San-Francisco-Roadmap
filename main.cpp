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
    for (int i : SF.nodeID) {
        bool notIn = true;
        for (int j : v) {
            if (j == i) {
                notIn = false;
                break;
            }
        }
        if (notIn) {
            std::cout << "The node is not traversed is" << i << std::endl;
            break;
        }
    }
    return 0;
}
