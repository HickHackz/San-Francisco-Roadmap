#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>
class graph {
    private:
        vector<int> nodeID;
        vector<double> xLocs;
        vector<double> yLocs;
        vector<int> edgeIDs;
        vector<double> edgeLength;
        vector<int> startNode;
        vector<int> endNode;
    public:
        std::string file_to_string(const std::string & filename);
        std::vector<std::string> file_to_vector(const std::string & filename);
        graph(const std::string nodeInfo, const std::string edgeInfo);

}