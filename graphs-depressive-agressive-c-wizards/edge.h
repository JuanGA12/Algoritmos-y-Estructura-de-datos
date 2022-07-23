#ifndef EDGE_H
#define EDGE_H

#include "vertex.h"

template<typename G>
class Edge {    
    typedef typename G::EE E;
    typedef typename G::vertex vertex;

    vertex* vertices[2];

public:
    E data;

    Edge(vertex* start, vertex* end, E data){
        this->vertices[0] = start;
        this->vertices[1] = end;
        this->data = data;
    }
    ~Edge(){}

    template<typename, typename>
    friend class Graph; 

    template<typename V, typename E>
    friend class UndirectedGraph;

    template<typename V, typename E>
    friend class DirectedGraph;
};

#endif