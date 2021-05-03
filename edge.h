
#pragma once
#include <string>

class edge
{
  public:

    std::string source;
    std::string destination;
    edge(std::string u, std::string v, int w, std::string i)
        : source(u), destination(v), id(i), weight(w)
    {
    }

    edge() : source(""), destination(""), id(""), weight(-1)
    {
    }

    int getWeight() const
    {
        return this->weight;
    }

    std::string getId() const
    {
        return this->id;
    }

private:
    std::string id; 
    int weight;
};