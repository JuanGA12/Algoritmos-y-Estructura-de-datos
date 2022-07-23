#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <vector>
#include <list>
#include <string>
#include <stack>

#include "vertex.h"
#include "edge.h"

using namespace std;

class AirportsParser;
class CitiesParser;

template <typename V, typename E>
class Graph
{
public:
    typedef V VV;
    typedef E EE;
    typedef Graph<V, E> self;
    typedef Vertex<self> vertex;
    typedef Edge<self> edge;
    typedef unordered_map<int, vertex *> VertexSeq;
    typedef list<edge *> EdgeSeq;

protected:
    VertexSeq nodes;
    int number_vertices;
    int number_edges;
    unordered_map<int, bool> visited;

    void dfs(vertex *&start)
    {
        stack<vertex *> stack;
        stack.push(start);
        visited[start->id] = true;

        while (!stack.empty())
        {
            vertex *current = stack.top();
            bool isNotVisited = false;
            for (auto itr = current->edges.begin(); itr != current->edges.end(); itr++)
            {
                vertex *adjacent = (*itr)->vertices[0] == current ? (*itr)->vertices[1] : (*itr)->vertices[0];
                if (!visited[adjacent->id])
                {
                    stack.push(adjacent);
                    visited[adjacent->id] = true;
                    break;
                }
            }
            if (!isNotVisited)
            {
                stack.pop();
            }
        }
    }

public:
    Graph()
    {
        this->number_vertices = 0;
        this->number_edges = 0;
    }

    ~Graph() {}

    /**
        * Creates a new vertex in the graph with some data and an ID
        * @param id a unique identifier within the vertexes
        * @param data vertex data
        * @return true if inserted, false if the vertex is already in the graph
    **/
    bool insertVertex(int id, V data)
    {
        if (this->nodes.find(id) == this->nodes.end())
        { // Vertex not found on graph
            vertex *newVertex =



                    vertex(id, data);
            this->nodes[id] = newVertex;
            this->number_vertices++;
            return true;
        }
        else
        { // Vertex found
            return false;
        }
    }

    /**
        * Creates a new edge in the graph with some data
        * @param start id of start vertex
        * @param end id of the end vertex
        * @param data value of the edge
        * @return true if inserted, false if the edge is already in the graph, or one or both of the vertices do not exist
    **/
    virtual bool createEdge(int start, int end, E data) = 0;

    /**
        * Deletes a vertex in the graph
        * @param data data to be searched and deleted
        * @return true if deleted, false if the vertex is not in the graph 
    **/
    virtual bool deleteVertex(int id) = 0;

    /**
        * Deletes an edge in the graph, it is not possible to search by the edge value, 
        * since it can be repeated
        * @param start id of start vertex
        * @param end id of the end vertex
        * @return true if deleted, false if the edge is not in the graph 
    **/
    virtual bool deleteEdge(int start, int end) = 0;

    /**
        * Gets the value of the edge from the start and end vertexes
        * @param start id of start vertex
        * @param end id of the end vertex
        * @return value stored in the edge between the vertexes
    **/
    virtual E &operator()(int start, int end) = 0;

    /**
        * Gets the value of the vertex from the identifier
        * @param id the identifier of a vertex
        * @return value stored in the vertex
    **/
    V &operator[](int id)
    {
        return this->nodes[id]->data;
    }

    /**
        * Calculates the density of the graph
        * @return the density as float
    **/
    virtual float density() const = 0;

    /**
        * Calculates the density of the graph, and determine if it is dense dependening
        * on a threshold value
        * @param threshold the threshold that defines if it is dense or not
        * @return true if it is dense and false if it is disperse
    **/
    bool isDense(float threshold = 0.5) const
    {
        return (density() >= threshold);
    }

    /**
        * Detect if the graph is connected
        * @return true if it is connected and false if there is at least one missing connection
    **/
    virtual bool isConnected() = 0;

    /**
        * Detect if the graph is strongly connected (only for directed graphs)
        * @return true if it is strongly connected 
        * @throw exception if this method is called from a non-directed graph
    **/
    virtual bool isStronglyConnected() throw() = 0;

    /**
        * Detect if the graph is bipartite
        * @return true if it is bipartite 
    **/
    virtual bool isBipartite() = 0;

    /**
        * If the graph is empty
        * @return true if there are no vertexes, false if the graph has at least one vertex
    **/
    bool empty()
    {
        return this->nodes.empty();
    }

    /**
        * Clears the graph
    **/
    virtual void clear() = 0;

    virtual void print() = 0;

    friend class AirportsParser;
    friend class CitiesParser;
};

typedef Graph<string, double> graph;

#endif