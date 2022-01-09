#include <iostream>
#include "graph.h"
#include "dijkstra.h"
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
    SF.printGraph(5, true, 0, 1200);
    
    return 0;
}
