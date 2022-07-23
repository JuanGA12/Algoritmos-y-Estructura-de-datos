#ifndef VERTEX_H
#define VERTEX_H

template<typename V, typename E>
class Graph;

template<typename V, typename E>
class UndirectedGraph;

template<typename V, typename E>
class DirectedGraph;

template <typename G>
class Vertex {
    typedef typename G::VV V;
    typedef typename G::EdgeSeq EdgeSeq;
    typedef typename G::edge edge;

    EdgeSeq edges;

public:
    int id;
    V data;
    int rank;
    Vertex* parent;

    Vertex(int id, V data){
        this->id = id;
        this->data = data;
        this->rank = 0;
        this->parent = this;
    }
    ~Vertex() {}

    template<typename, typename>
    friend class Graph;
    
    template<typename V, typename E>
    friend class UndirectedGraph;

    template<typename V, typename E>
    friend class DirectedGraph;
};

#endif