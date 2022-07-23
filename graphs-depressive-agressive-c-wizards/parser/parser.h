#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include "../graph.h"

using namespace std;

class Parser{
public:
protected:
public:
    Parser() {}
    ~Parser() {}

    virtual void clear() = 0;
    virtual void uGraphMake(UndirectedGraph<string, double> &tempGraph) = 0;
    virtual void dGraphMake(DirectedGraph<string, double> &tempGraph) = 0;
};

#endif