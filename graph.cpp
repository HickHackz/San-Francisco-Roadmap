#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <cstdlib>
#include <string>
#include <vector>
#include "graph.h"
#include "cs225/PNG.h"
#include <math.h>
#include "dijkstra.h"
graph::Iterator::Iterator()
{
    g = NULL;
}
graph::Iterator::Iterator(int s, graph *graphUsed)
{
    /** @todo [Part 1] */
    start = s;
    current = start;
    g = graphUsed;
    for (int i : g->nodeID)
    {
        visited.push_back(false);
    }
    for (int j : g->edgeIDs)
    {
        exploredEdges.push_back(false);
    }
    //add(start);
    visited[start] = true;
    bool extrpop = false;
    nodeUsed.push(start);
    //current = t->pop();
}

graph::Iterator &graph::Iterator::operator++()
{
    /** @todo [Part 1] */
    //t->add(current);
    //visited[current.x][current.y] = true;
    if (!nodeUsed.empty())
    {
        int origionalCurrent = current; //check for empty
        if (!extrpop)
        {
            origionalCurrent = nodeUsed.top();
            nodeUsed.pop();
        }
        else
        {
            extrpop = false;
        }
        current = origionalCurrent;
        visited[origionalCurrent] = true;
        for (int i : g->incidentEdges(origionalCurrent))
        {
            int node = 0;
            if (g->startNode[i] != origionalCurrent)
            {
                node = g->startNode[i];
            }
            else
            {
                node = g->endNode[i];
            }
            if (!visited[node])
            {
                visited[node] = true;
                nodeUsed.push(node);
                if (exploredEdges[i] == false)
                {
                    exploredEdges[i] = true;
                    discoveryEdges.push_back(i);
                }
            }
            else
            {
                if (exploredEdges[i] == false)
                {
                    exploredEdges[i] = true;
                    backEdges.push_back(i);
                }
            }
        }
        if (nodeUsed.empty() == false)
        {
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
int graph::Iterator::operator*()
{
    /** @todo [Part 1] */
    return current;
}
bool graph::Iterator::operator!=(const graph::Iterator &other)
{
    if (g == NULL)
    {
        return false;
    }
    if (nodeUsed.empty())
    {
        return false;
    }
    return true;
}
graph::Iterator graph::begin()
{
    return Iterator(0, this);
}
graph::Iterator graph::end()
{
    return Iterator();
}
std::string graph::file_to_string(const std::string &filename)
{
    std::ifstream text(filename);

    std::stringstream strStream;
    if (text.is_open())
    {
        strStream << text.rdbuf();
    }

    return strStream.str();
}
std::vector<std::string> graph::file_to_vector(const std::string &filename)
{
    std::ifstream text(filename);
    std::vector<std::string> out;
    std::string str;

    while (std::getline(text, str))
    {
        if (str.size() > 0)
            out.push_back(str);
    }
    return out;
}
graph::graph(const std::string nodeInfo, const std::string edgeInfo)
{
    std::vector<std::string> nodesI = file_to_vector(nodeInfo);
    std::vector<std::string> edgeI = file_to_vector(edgeInfo);
    for (unsigned i = 0; i < nodesI.size(); i++)
    {
        std::string row = nodesI[i];
        int count = 0;
        std::istringstream iss(row);
        std::string::size_type sz = 0;
        std::string subs;

        do
        {
            iss >> subs;
            // std::cout << subs << std::endl;
            if (count % 3 == 0)
            {
                double num = std::stod(&subs[0], &sz);
                int n = int(num);
                nodeID.push_back(n);
                //std::cout << n << std::endl;
            }
            if (count % 3 == 1)
            {
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
    for (unsigned i = 0; i < edgeI.size(); i++)
    {
        std::string row = edgeI[i];
        int count = 0;
        std::istringstream iss(row);
        std::string::size_type sz = 0;
        std::string subs;

        do
        {
            iss >> subs;
            double num = std::stod(subs, &sz);
            int n = int(num);
            if (count % 4 == 0)
            {
                //int n = int(num);
                double n = std::stod(&subs[0], &sz);
                edgeIDs.push_back(n);
                //std::cout << n << std::endl;
            }
            if (count % 4 == 1)
            {
                double n = std::stod(&subs[0], &sz);
                startNode.push_back(n);
                //std::cout << n << std::endl;
            }
            if (count % 4 == 2)
            {
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
    for (int i : nodeID)
    {
        std::vector<int> a;
        adjacencyList.push_back(a);
    }
    for (int j : edgeIDs)
    {
        adjacencyList[startNode[j]].push_back(j);
        adjacencyList[endNode[j]].push_back(j);
    }
}

std::vector<int> graph::incidentEdges(int c) const
{
    return adjacencyList[c];
}

bool graph::areAdjecent(int c1, int c2)
{
    std::vector<int> edges = incidentEdges(c1);
    for (int i : edges)
    {
        if (startNode[i] == c2 || endNode[i] == c2)
        {
            return true;
        }
    }
    return false;
}

std::vector<int> graph::getVertices() const
{
    return nodeID;
}

std::vector<int> graph::getAdjacentNodes(int source) const
{
    std::vector<int> node;
    for (int i : adjacencyList[source])
    {
        if (startNode[i] != source)
        {
            node.push_back(startNode[i]);
        }
        else
        {
            node.push_back(endNode[i]);
        }
    }
    return node;
}

double graph::getEdgeWeight(int source, int destination) const
{
    for (int i : startNode)
    {
        if (startNode[i] == source && endNode[i] == destination)
        {
            return edgeLength[i];
        }
    }
    return 0;
}

double graph::getEdge(int source, int destination) const
{
    std::vector<int> edges = incidentEdges(source);
    for (int i : edges)
    {
        if (startNode[i] == destination || endNode[i] == destination)
        {
            return i;
        }
    }
    return 0;
}
void setBlue(cs225::HSLAPixel &pixel)
{
    pixel.a = 1;
    pixel.h = 235;
    pixel.l = .5;
    pixel.s = 1;
    
}
void setRed(cs225::HSLAPixel &pixel)
{
    pixel.a = 1;
    pixel.h = 0;
    pixel.l = .5;
    pixel.s = 1;
}
void setBlack(cs225::HSLAPixel &pixel)
{
    pixel.a = 1;
    pixel.h = 0;
    pixel.l = 0;
    pixel.s = 0;
}
bool isValid(int x, int y, int j, int k, int h, int g){
    if (x == 1 && y ==1) {
        if (j < h && k < g) return true;}
    if (x == -1 && y ==1) {
        if (j > h && k < g) return true;}
    if (x == 1 && y ==-1) {
        if (j < h && k > g) return true;}
    if (x == -1 && y ==-1) {
        if (j > h && k > g) return true;  }
    return false;

}
void graph::printGraph(double tolerance, bool withSol, int src, int dst)
{

    unsigned int sWidth = 10000;
    unsigned int lWidth = 0;
    unsigned int sHeight = 10000;
    unsigned int lHeight = 0;
    for (unsigned i = 0; i < xLocs.size(); i++)
    { //finding max height and width
        if (xLocs[i] > lWidth)
            lWidth = (unsigned int)xLocs[i];
        if (xLocs[i] < sWidth)
            sWidth = (unsigned int)xLocs[i];
        if (yLocs[i] > lHeight)
            lHeight = (unsigned int)yLocs[i];
        if (yLocs[i] < sHeight)
            sHeight = (unsigned int)yLocs[i];
    }
    cs225::PNG map(lWidth, lHeight); //base PNG
    for (unsigned i = 0; i < edgeIDs.size(); i++)
    {
    
        double width = xLocs[endNode[i]] - xLocs[startNode[i]];
        double height = yLocs[endNode[i]] - yLocs[startNode[i]]; //coordinates for sub plot to proccess edge
        int xincrement, yincrement;
        if (width < 0)
            xincrement = -1;
        else
            xincrement = 1;
        if (height < 0)
            yincrement = -1;
        else
            yincrement = 1;
        double slope = tan(height / width);
        int h = xLocs[endNode[i]];
        int g = yLocs[endNode[i]];
        double j = xLocs[startNode[i]];
        double k = yLocs[startNode[i]];
        while (isValid(xincrement, yincrement, (unsigned int)j, (unsigned int)k, h, g)) {                              // (j < (unsigned int)xLocs[endNode[i]]) || (k + yincrement != (unsigned int)yLocs[endNode[i]])
            if (xincrement == 1 && yincrement == 1)
            {   
                

                if (abs(tan((k + 1 - yLocs[startNode[i]]) / (j - xLocs[startNode[i]])) - slope) <
                    (abs(tan((k - yLocs[startNode[i]]) / (j + 1 - xLocs[startNode[i]])) - slope)))
                {

                    for (int m = -tolerance; m <= tolerance; m++)
                    {
                        for (int n = -tolerance; n <= tolerance; n++) {
                            cs225::HSLAPixel &pixel = map.getPixel((unsigned int)j + m, (unsigned int)k + n);
                            setBlack(pixel);
                        }
                    }
                    //cs225::HSLAPixel &pixel = map.getPixel((unsigned int)j, (unsigned int)k);
                    cs225::HSLAPixel &pixel2 = map.getPixel((unsigned int)j + 1, (unsigned int)k+1);
                    cs225::HSLAPixel &pixel3 = map.getPixel((unsigned int)j + 1, (unsigned int)k-1);
                    cs225::HSLAPixel &pixel4 = map.getPixel((unsigned int)j - 1, (unsigned int)k+1);
                    cs225::HSLAPixel &pixel5 = map.getPixel((unsigned int)j - 1, (unsigned int)k-1);
                    cs225::HSLAPixel &pixel6 = map.getPixel((unsigned int)j + 1, (unsigned int)k);
                    cs225::HSLAPixel &pixel7 = map.getPixel((unsigned int)j - 1, (unsigned int)k);
                    cs225::HSLAPixel &pixel8 = map.getPixel((unsigned int)j, (unsigned int)k+1);
                    cs225::HSLAPixel &pixel9 = map.getPixel((unsigned int)j, (unsigned int)k-1);

                  //  setBlack(pixel);
                    setBlack(pixel2);
                    setBlack(pixel3);
                    setBlack(pixel4);
                    setBlack(pixel5);
                    setBlack(pixel6);
                    setBlack(pixel7);
                    setBlack(pixel8);
                    setBlack(pixel9);
                    k += 1;
                }
                else
                {
                    for (int m = -tolerance; m <= tolerance; m++)
                    {
                        for (int n = -tolerance; n <= tolerance; n++) {
                            cs225::HSLAPixel &pixel = map.getPixel((unsigned int)j + m, (unsigned int)k + n);
                            setBlack(pixel);
                        }
                    }
                    //cs225::HSLAPixel &pixel = map.getPixel((unsigned int)j, (unsigned int)k);
                    cs225::HSLAPixel &pixel2 = map.getPixel((unsigned int)j + 1, (unsigned int)k+1);
                    cs225::HSLAPixel &pixel3 = map.getPixel((unsigned int)j + 1, (unsigned int)k-1);
                    cs225::HSLAPixel &pixel4 = map.getPixel((unsigned int)j - 1, (unsigned int)k+1);
                    cs225::HSLAPixel &pixel5 = map.getPixel((unsigned int)j - 1, (unsigned int)k-1);
                    cs225::HSLAPixel &pixel6 = map.getPixel((unsigned int)j + 1, (unsigned int)k);
                    cs225::HSLAPixel &pixel7 = map.getPixel((unsigned int)j - 1, (unsigned int)k);
                    cs225::HSLAPixel &pixel8 = map.getPixel((unsigned int)j, (unsigned int)k+1);
                    cs225::HSLAPixel &pixel9 = map.getPixel((unsigned int)j, (unsigned int)k-1);

                    //setBlack(pixel);
                    setBlack(pixel2);
                    setBlack(pixel3);
                    setBlack(pixel4);
                    setBlack(pixel5);
                    setBlack(pixel6);
                    setBlack(pixel7);
                    setBlack(pixel8);
                    setBlack(pixel9);
                    
                    j += 1;
                }
            }
            if (xincrement == -1 && yincrement == 1)
            {
                if (abs(tan((k + 1 - yLocs[startNode[i]]) / (j - xLocs[startNode[i]])) - slope) <
                    (abs(tan((k - yLocs[startNode[i]]) / (j - 1 - xLocs[startNode[i]])) - slope)))
                {
                    for (int m = -tolerance; m <= tolerance; m++)
                    {
                        for (int n = -tolerance; n <= tolerance; n++) {
                            cs225::HSLAPixel &pixel = map.getPixel((unsigned int)j + m, (unsigned int)k + n);
                            setBlack(pixel);
                        }
                    }
                   // cs225::HSLAPixel &pixel = map.getPixel((unsigned int)j, (unsigned int)k);
                    cs225::HSLAPixel &pixel2 = map.getPixel((unsigned int)j + 1, (unsigned int)k+1);
                    cs225::HSLAPixel &pixel3 = map.getPixel((unsigned int)j + 1, (unsigned int)k-1);
                    cs225::HSLAPixel &pixel4 = map.getPixel((unsigned int)j - 1, (unsigned int)k+1);
                    cs225::HSLAPixel &pixel5 = map.getPixel((unsigned int)j - 1, (unsigned int)k-1);
                    cs225::HSLAPixel &pixel6 = map.getPixel((unsigned int)j + 1, (unsigned int)k);
                    cs225::HSLAPixel &pixel7 = map.getPixel((unsigned int)j - 1, (unsigned int)k);
                    cs225::HSLAPixel &pixel8 = map.getPixel((unsigned int)j, (unsigned int)k+1);
                    cs225::HSLAPixel &pixel9 = map.getPixel((unsigned int)j, (unsigned int)k-1);

                   // setBlack(pixel);
                    setBlack(pixel2);
                    setBlack(pixel3);
                    setBlack(pixel4);
                    setBlack(pixel5);
                    setBlack(pixel6);
                    setBlack(pixel7);
                    setBlack(pixel8);
                    setBlack(pixel9);
                    k += 1;
                }
                else
                {
                    for (int m = -tolerance; m <= tolerance; m++)
                    {
                        for (int n = -tolerance; n <= tolerance; n++) {
                            cs225::HSLAPixel &pixel = map.getPixel((unsigned int)j + m, (unsigned int)k + n);
                            setBlack(pixel);
                        }
                    }
                    //cs225::HSLAPixel &pixel = map.getPixel((unsigned int)j, (unsigned int)k);
                    cs225::HSLAPixel &pixel2 = map.getPixel((unsigned int)j + 1, (unsigned int)k+1);
                    cs225::HSLAPixel &pixel3 = map.getPixel((unsigned int)j + 1, (unsigned int)k-1);
                    cs225::HSLAPixel &pixel4 = map.getPixel((unsigned int)j - 1, (unsigned int)k+1);
                    cs225::HSLAPixel &pixel5 = map.getPixel((unsigned int)j - 1, (unsigned int)k-1);
                    cs225::HSLAPixel &pixel6 = map.getPixel((unsigned int)j + 1, (unsigned int)k);
                    cs225::HSLAPixel &pixel7 = map.getPixel((unsigned int)j - 1, (unsigned int)k);
                    cs225::HSLAPixel &pixel8 = map.getPixel((unsigned int)j, (unsigned int)k+1);
                    cs225::HSLAPixel &pixel9 = map.getPixel((unsigned int)j, (unsigned int)k-1);

                   // setBlack(pixel);
                    setBlack(pixel2);
                    setBlack(pixel3);
                    setBlack(pixel4);
                    setBlack(pixel5);
                    setBlack(pixel6);
                    setBlack(pixel7);
                    setBlack(pixel8);
                    setBlack(pixel9);
                    j -= 1;
                }
            }
            if (xincrement == 1 && yincrement == -1)
            {
                if (abs(tan((k - 1 - yLocs[startNode[i]]) / (j - xLocs[startNode[i]])) - slope) <
                    (abs(tan((k - yLocs[startNode[i]]) / (j + 1 - xLocs[startNode[i]])) - slope)))
                {
                    for (int m = -tolerance; m <= tolerance; m++)
                    {
                        for (int n = -tolerance; n <= tolerance; n++) {
                            cs225::HSLAPixel &pixel = map.getPixel((unsigned int)j + m, (unsigned int)k + n);
                            setBlack(pixel);
                        }
                    }
                   // cs225::HSLAPixel &pixel = map.getPixel((unsigned int)j, (unsigned int)k);
                    cs225::HSLAPixel &pixel2 = map.getPixel((unsigned int)j + 1, (unsigned int)k+1);
                    cs225::HSLAPixel &pixel3 = map.getPixel((unsigned int)j + 1, (unsigned int)k-1);
                    cs225::HSLAPixel &pixel4 = map.getPixel((unsigned int)j - 1, (unsigned int)k+1);
                    cs225::HSLAPixel &pixel5 = map.getPixel((unsigned int)j - 1, (unsigned int)k-1);
                    cs225::HSLAPixel &pixel6 = map.getPixel((unsigned int)j + 1, (unsigned int)k);
                    cs225::HSLAPixel &pixel7 = map.getPixel((unsigned int)j - 1, (unsigned int)k);
                    cs225::HSLAPixel &pixel8 = map.getPixel((unsigned int)j, (unsigned int)k+1);
                    cs225::HSLAPixel &pixel9 = map.getPixel((unsigned int)j, (unsigned int)k-1);

                    //setBlack(pixel);
                    setBlack(pixel2);
                    setBlack(pixel3);
                    setBlack(pixel4);
                    setBlack(pixel5);
                    setBlack(pixel6);
                    setBlack(pixel7);
                    setBlack(pixel8);
                    setBlack(pixel9);
                    k -= 1;
                }
                else
                {
                    for (int m = -tolerance; m <= tolerance; m++)
                    {
                        for (int n = -tolerance; n <= tolerance; n++) {
                            cs225::HSLAPixel &pixel = map.getPixel((unsigned int)j + m, (unsigned int)k + n);
                            setBlack(pixel);
                        }
                    }
                    //cs225::HSLAPixel &pixel = map.getPixel((unsigned int)j, (unsigned int)k);
                    cs225::HSLAPixel &pixel2 = map.getPixel((unsigned int)j + 1, (unsigned int)k+1);
                    cs225::HSLAPixel &pixel3 = map.getPixel((unsigned int)j + 1, (unsigned int)k-1);
                    cs225::HSLAPixel &pixel4 = map.getPixel((unsigned int)j - 1, (unsigned int)k+1);
                    cs225::HSLAPixel &pixel5 = map.getPixel((unsigned int)j - 1, (unsigned int)k-1);
                    cs225::HSLAPixel &pixel6 = map.getPixel((unsigned int)j + 1, (unsigned int)k);
                    cs225::HSLAPixel &pixel7 = map.getPixel((unsigned int)j - 1, (unsigned int)k);
                    cs225::HSLAPixel &pixel8 = map.getPixel((unsigned int)j, (unsigned int)k+1);
                    cs225::HSLAPixel &pixel9 = map.getPixel((unsigned int)j, (unsigned int)k-1);

                   // setBlack(pixel);
                    setBlack(pixel2);
                    setBlack(pixel3);
                    setBlack(pixel4);
                    setBlack(pixel5);
                    setBlack(pixel6);
                    setBlack(pixel7);
                    setBlack(pixel8);
                    setBlack(pixel9);
                    j += 1;
                }
            }
            if (xincrement == -1 && yincrement == -1)
            {
                if (abs(tan((k - 1 - yLocs[startNode[i]]) / (j - xLocs[startNode[i]])) - slope) <
                    (abs(tan((k - yLocs[startNode[i]]) / (j - 1 - xLocs[startNode[i]])) - slope)))
                {
                    for (int m = -tolerance; m <= tolerance; m++)
                    {
                        for (int n = -tolerance; n <= tolerance; n++) {
                            cs225::HSLAPixel &pixel = map.getPixel((unsigned int)j + m, (unsigned int)k + n);
                            setBlack(pixel);
                        }
                    }
                    //cs225::HSLAPixel &pixel = map.getPixel((unsigned int)j, (unsigned int)k);
                    cs225::HSLAPixel &pixel2 = map.getPixel((unsigned int)j + 1, (unsigned int)k+1);
                    cs225::HSLAPixel &pixel3 = map.getPixel((unsigned int)j + 1, (unsigned int)k-1);
                    cs225::HSLAPixel &pixel4 = map.getPixel((unsigned int)j - 1, (unsigned int)k+1);
                    cs225::HSLAPixel &pixel5 = map.getPixel((unsigned int)j - 1, (unsigned int)k-1);
                    cs225::HSLAPixel &pixel6 = map.getPixel((unsigned int)j + 1, (unsigned int)k);
                    cs225::HSLAPixel &pixel7 = map.getPixel((unsigned int)j - 1, (unsigned int)k);
                    cs225::HSLAPixel &pixel8 = map.getPixel((unsigned int)j, (unsigned int)k+1);
                    cs225::HSLAPixel &pixel9 = map.getPixel((unsigned int)j, (unsigned int)k-1);

                    //setBlack(pixel);
                    setBlack(pixel2);
                    setBlack(pixel3);
                    setBlack(pixel4);
                    setBlack(pixel5);
                    setBlack(pixel6);
                    setBlack(pixel7);
                    setBlack(pixel8);
                    setBlack(pixel9);
                    k -= 1;
                }
                else
                {
                    for (int m = -tolerance; m <= tolerance; m++)
                    {
                        for (int n = -tolerance; n <= tolerance; n++) {
                            cs225::HSLAPixel &pixel = map.getPixel((unsigned int)j + m, (unsigned int)k + n);
                            setBlack(pixel);
                        }
                    }
                    //cs225::HSLAPixel &pixel = map.getPixel((unsigned int)j, (unsigned int)k);
                    cs225::HSLAPixel &pixel2 = map.getPixel((unsigned int)j + 1, (unsigned int)k+1);
                    cs225::HSLAPixel &pixel3 = map.getPixel((unsigned int)j + 1, (unsigned int)k-1);
                    cs225::HSLAPixel &pixel4 = map.getPixel((unsigned int)j - 1, (unsigned int)k+1);
                    cs225::HSLAPixel &pixel5 = map.getPixel((unsigned int)j - 1, (unsigned int)k-1);
                    cs225::HSLAPixel &pixel6 = map.getPixel((unsigned int)j + 1, (unsigned int)k);
                    cs225::HSLAPixel &pixel7 = map.getPixel((unsigned int)j - 1, (unsigned int)k);
                    cs225::HSLAPixel &pixel8 = map.getPixel((unsigned int)j, (unsigned int)k+1);
                    cs225::HSLAPixel &pixel9 = map.getPixel((unsigned int)j, (unsigned int)k-1);

                    //setBlack(pixel);
                    setBlack(pixel2);
                    setBlack(pixel3);
                    setBlack(pixel4);
                    setBlack(pixel5);
                    setBlack(pixel6);
                    setBlack(pixel7);
                    setBlack(pixel8);
                    setBlack(pixel9);
                    j -= 1;
                }
        }
    }
    }



for (unsigned l = 0; l < nodeID.size(); l++)
{
    for (int m = -tolerance/4; m <= tolerance/4; m++)
    {
        for (int n = -tolerance; n <= tolerance; n++) {
            cs225::HSLAPixel &pixel = map.getPixel((unsigned int)xLocs[(size_t)l]+m, (unsigned int)yLocs[(size_t)l]+n);
            setRed(pixel);
        }
    }
    
}

map.writeToFile("myMap.png");
return;
}
