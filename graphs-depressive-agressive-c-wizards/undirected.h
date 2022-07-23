#ifndef UNDIRECTED_H
#define UNDIRECTED_H

#include <queue>
#include <stack>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <limits.h>
#include <iostream>
#include <iomanip>
#include <limits>

#include "graph.h"
#include "vertex.h"
#include "edge.h"

#define pi 3.14159265358979323846

using namespace std;

template <typename V, typename E>
class UndirectedGraph : public Graph<V, E>
{
public:
     typedef typename Graph<V, E>::vertex vertex;
     typedef typename Graph<V, E>::edge edge;

private:
     vector<edge *> edgeVec;

     bool edgeExists(vertex *start, vertex *end)
     {
          if (!start || !end)
               return false;
          if (start->edges.empty() || end->edges.empty())
          {
               return false;
          }
          bool exists = false;
          for (auto iter = start->edges.begin(); iter != start->edges.end(); ++iter)
          {
               edge *e = *iter;
               if ((e->vertices[0] == end || e->vertices[1] == end))
               {
                    exists = true;
                    break;
               };
          }
          return exists;
     }

     edge *findEdge(vertex *start, vertex *end)
     {
          if (edgeExists(start, end))
          {
               auto edges = &start->edges;
               auto it = edges->begin();
               for (; it != edges->end(); advance(it, 1))
               {
                    edge *e = *it;
                    if (e->vertices[0] == end || e->vertices[1] == end)
                    {
                         return e;
                    }
               }
          }
          return nullptr;
     }

     void link(vertex *&node1, vertex *&node2)
     {
          node1 = find(node1);
          node2 = find(node2);
          if (node1->rank > node2->rank)
          {
               node2->parent = node1;
          }
          else
          {
               node1->parent = node2;
          }
          if (node1->parent == node2->parent)
          {
               node2->rank++;
          }
     }

     vertex *find(vertex *&node)
     {
          vertex *temp = node;
          while (temp->parent != temp)
          {
               temp = temp->parent;
          }
          node->parent = temp;
          return temp;
     }

     edge *findMinEdge(vector<vertex *> vertices)
     {

          int min = INT_MAX;
          edge *minEdge = nullptr;
          for (auto vertex : vertices)
          {
               for (auto edge : vertex->edges)
               {

                    auto vertexFound = std::find(vertices.begin(), vertices.end(), edge->vertices[1]) == vertices.end(); //si no esta retorna true
                    if (!vertexFound)
                    {
                         vertexFound = std::find(vertices.begin(), vertices.end(), edge->vertices[0]) == vertices.end();
                    }

                    if (edge->data < min && vertexFound)
                    {
                         minEdge = edge;
                         min = minEdge->data;
                    }
               }
          }
          return minEdge;
     }

     static bool compareEdge(edge *a, edge *b) { return (a->data < b->data); }

     static bool compareWeight(pair<int, float> a, pair<int, float> b) { return (a.second < b.second); }

     void copy(const UndirectedGraph<V, E> &other)
     {
          this->number_edges = other.number_edges;
          this->number_vertices = other.number_vertices;
          this->visited = other.visited;
          // Copy only vertices first
          for (auto iterV = other.nodes.begin(); iterV != other.nodes.end(); ++iterV)
          {
               int id = iterV->first;
               vertex *v = iterV->second;
               this->nodes[id] = new vertex(id, v->data);
          }
          // Copy edges
          for (auto iterV = other.nodes.begin(); iterV != other.nodes.end(); ++iterV)
          {
               int id = iterV->first;
               vertex *v = iterV->second;
               for (auto iterE = v->edges.begin(); iterE != v->edges.end(); ++iterE)
               {
                    edge *e = *iterE;
                    int startId = e->vertices[0]->id;
                    int endId = e->vertices[1]->id;
                    edge *newEdge = new edge(this->nodes[startId], this->nodes[endId], e->data);
                    this->nodes[id]->edges.push_back(newEdge);
                    this->edgeVec.push_back(newEdge);
               }
          }
     }

public:
     UndirectedGraph() : Graph<V, E>()
     {
     }

     UndirectedGraph(const UndirectedGraph &other) : Graph<V, E>()
     {
          std::cout << "Copy Constructor" << std::endl;
          copy(other);
     }

     ~UndirectedGraph()
     {
          std::cout << "Destructor" << std::endl;
          this->clear();
     }

     UndirectedGraph<V, E> operator=(const UndirectedGraph<V, E> &other)
     {
          std::cout << "Operator =" << std::endl;
          if (!this->nodes.empty())
          {
               this->clear();
          }
          copy(other);
          return *this;
     }

     /**
         * Creates a new edge in the graph with some data
         * @param start id of start vertex
         * @param end id of the end vertex
         * @param data value of the edge
         * @return true if inserted, false if the edge is already in the graph, or one or both of the vertices do not exist
     **/
     bool createEdge(int start, int end, E data) override
     {
          bool verticesExist = (this->nodes.find(start) != this->nodes.end()) && (this->nodes.find(end) != this->nodes.end());
          if (verticesExist)
          {
               if (edgeExists(this->nodes[start], this->nodes[end]))
               {
                    return false;
               }
               edge *newEdge = new edge(this->nodes[start], this->nodes[end], data);
               this->nodes[start]->edges.push_back(newEdge);
               this->nodes[end]->edges.push_back(newEdge);
               this->number_edges++;
               this->edgeVec.push_back(newEdge);
               return true;
          }
          else
          {
               return false;
          }
     }

     /**
        * Deletes a vertex in the graph
        * @param data data to be searched and deleted
        * @return true if deleted, false if the vertex is not in the graph 
     **/
     bool deleteVertex(int id) override
     {
          if (this->nodes.find(id) == this->nodes.end())
          {
               return false;
          }
          else
          {
               vertex *current = this->nodes[id];
               for (auto iter = current->edges.begin(); iter != current->edges.end(); ++iter)
               {
                    vertex *next;
                    if ((*iter)->vertices[0] != current)
                    {
                         next = (*iter)->vertices[0];
                    }
                    else
                    {
                         next = (*iter)->vertices[1];
                    }
                    next->edges.remove(*iter);
                    delete *iter;
                    current->edges.erase(iter);
                    iter--;
               }
               this->nodes.erase(id);
               delete current;
               return true;
          }
     }

     /**
         * Deletes an edge in the graph, it is not possible to search by the edge value, 
         * since it can be repeated
         * @param start id of start vertex
         * @param end id of the end vertex
         * @return true if deleted, false if the edge is not in the graph 
     **/
     bool deleteEdge(int start, int end) override
     {
          edge *edgeTemp = findEdge(this->nodes[start], this->nodes[end]);
          if (edgeTemp)
          {
               for (size_t i = 0; i < 2; i++)
               {
                    vertex *v = edgeTemp->vertices[i];
                    for (auto it = v->edges.begin(); it != v->edges.end(); ++it)
                    {
                         edge *e = *it;
                         if (e == edgeTemp)
                         {
                              v->edges.erase(it);
                              break;
                         }
                    }
               }
               auto edge = std::find(this->edgeVec.begin(), this->edgeVec.end(), edgeTemp);
               if (*edge == edgeTemp)
               {
                    this->edgeVec.erase(edge);
               }
               delete edgeTemp;
               return true;
          }
          else
          {
               return false;
          }
     }

     /**
         * Gets the value of the edge from the start and end vertexes
         * @param start id of start vertex
         * @param end id of the end vertex
         * @return value stored in the edge between the vertexes
     **/
     E &operator()(int start, int end) override
     {
          vertex *vStart = this->nodes[start];
          vertex *vEnd = this->nodes[end];
          if (!vStart->edges.empty())
          {
               auto iter = vStart->edges.begin();
               while (iter != vStart->edges.end() && ((*iter)->vertices[0] != vEnd && (*iter)->vertices[1] != vEnd))
               {
                    auto debug = *iter;
                    ++iter;
               }
               if (iter != vStart->edges.end())
               {
                    return (*iter)->data;
               }
          }
          throw "Edge does not exist";
     }

     /**
         * Calculates the density of the graph
         * @return the density as float
     **/
     float density() const override
     {
          int Edges = this->number_edges;
          int Vertices = this->number_vertices;
          return (float(2 * Edges) / float(Vertices * (Vertices - 1)));
     }

     /**
         * Detect if the graph is connected
         * @return true if it is connected and false if there is at least one missing connection
     **/
     bool isConnected() override
     {
          auto itr = this->nodes.begin();
          this->dfs(itr->second);
          if (this->nodes.size() != this->visited.size())
          {
               return false;
          }
          this->visited.clear();
          return true;
     }

     /**
         * Detect if the graph is strongly connected (only for directed graphs)
         * @return true if it is strongly connected 
         * @throw exception if this method is called from a non-directed grac.createEdge(1,2,7)ph
     **/
     bool isStronglyConnected() throw() override
     {
          throw "An undirected graph does not have a strongly connected property";
     }

     /**
         * Detect if the graph is bipartite
         * @return true if it is bipartite 
     **/
     bool isBipartite() override
     {
          if (this->nodes.empty())
          {
               return false;
          }
          // -1: no color assigned
          //  0: one color (purple)
          //  1: another color (green)
          unordered_map<int, int> colorsMap;
          for (auto it = this->nodes.begin(); it != this->nodes.end(); ++it)
          {
               colorsMap[it->first] = -1;
          }
          colorsMap[colorsMap.begin()->first] = 0;
          queue<int> keys;
          keys.push(colorsMap.begin()->first);
          while (!keys.empty())
          { // Iterate through all vertices of graph
               int key = keys.front();
               keys.pop();
               vertex *v = this->nodes[key];
               for (auto iter = v->edges.begin(); iter != v->edges.end(); ++iter)
               { // Iterate through all edges of vertex
                    edge *e = *iter;
                    vertex *vTemp = e->vertices[0] == v ? e->vertices[1] : e->vertices[0]; // Find the "other" vertex
                    int keyTemp = vTemp->id;
                    if (colorsMap[keyTemp] == -1)
                    { // Vertex not visited yet
                         keys.push(keyTemp);
                    }
                    if (colorsMap[keyTemp] == -1)
                    { // Vertex has not been visited, "paint" it to a different color
                         colorsMap[keyTemp] = !colorsMap[key];
                    }
                    else if (colorsMap[keyTemp] == colorsMap[key])
                    { // Neighbor vertex has the same color: Not bipartite
                         return false;
                    } // else: neighbor vertex has a different color, all good, do nothing
               }
          }
          return true;
     }

     UndirectedGraph<V, E> kruskal()
     {
          UndirectedGraph<V, E> temp;
          for (auto itr = this->nodes.begin(); itr != this->nodes.end(); itr++)
          {
               temp.insertVertex(itr->first, itr->second->data);
          }
          std::sort(edgeVec.begin(), edgeVec.end(), compareEdge);

          for (auto itr = this->edgeVec.begin(); itr != this->edgeVec.end(); itr++)
          {
               vertex *u = (*itr)->vertices[0];
               vertex *v = (*itr)->vertices[1];

               vertex *setU = find(u);
               vertex *setV = find(v);

               if (setU != setV)
               {
                    temp.createEdge(u->id, v->id, (*itr)->data);
                    link(setU, setV);
               }
          }
          return temp;
     }

     UndirectedGraph<V, E> Prim(int id)
     {

          auto tmpVertex = this->nodes[id];
          if (tmpVertex && isConnected())
          {

               UndirectedGraph<V, E> primGraph;
               vector<vertex *> vertices;

               for (auto &it : this->nodes)
               {
                    primGraph.insertVertex(it.first, it.second->data);
               }

               for (auto &it : this->nodes)
               {

                    vertices.push_back(tmpVertex);
                    auto minEdge = findMinEdge(vertices);

                    if (minEdge)
                    {

                         primGraph.createEdge(minEdge->vertices[0]->id, minEdge->vertices[1]->id, minEdge->data);

                         auto vertexFound = std::find(vertices.begin(), vertices.end(), minEdge->vertices[1]);

                         tmpVertex = (*vertexFound == minEdge->vertices[1]) ? minEdge->vertices[0] : minEdge->vertices[1];
                    }
                    else
                    {
                         break;
                    }
               }
               return primGraph;
          }
          else
          {
               throw out_of_range("No existe vertice o el grafo no es conexo");
          }
     }

     /**
         * Clears the graph
     **/
     void clear() override
     {
          auto iterM = this->nodes.begin();
          while (!this->nodes.empty())
          {
               vertex *v = iterM->second;
               auto iterL = v->edges.begin();
               while (!v->edges.empty())
               {
                    edge *e = *iterL;
                    if (e->vertices[1] != v)
                    { // find "other" vertex
                         delete e;
                    }
                    v->edges.erase(iterL);
                    iterL = v->edges.begin();
               }
               delete v;
               this->nodes.erase(iterM);
               iterM = this->nodes.begin();
          }
          this->edgeVec.clear();
          this->visited.clear();
          this->number_vertices = 0;
          this->number_edges = 0;
     }

     void print()
     {
          for (auto iterV = this->nodes.begin(); iterV != this->nodes.end(); ++iterV)
          {
               vertex *tempV = iterV->second;
               cout << setw(0) << "Vertex " << tempV->id << ":" << endl
                    << "edges:" << setw(10);
               if (tempV->edges.empty())
               {
                    cout << endl;
               }
               for (auto e = tempV->edges.begin(); e != tempV->edges.end(); ++e)
               {
                    vertex *u = (*e)->vertices[0];
                    vertex *v = (*e)->vertices[1];
                    cout << u->id << " <-- " << (*e)->data << " --> " << v->id << endl
                         << setw(16);
               }
               cout << endl;
          }
          cout << setw(0);
     }

     const UndirectedGraph<V, E> BFS(int startId)
     {
          if (this->nodes.find(startId) == this->nodes.end())
          { // Vertex not found on graph
               throw "Start vertex does not exist in this graph";
          }
          UndirectedGraph<V, E> result;
          queue<vertex *> vQueue;
          // unordered_map<int, bool> visited;
          // Make sure visited nodes are cleared at the beginning
          if (!this->visited.empty())
          {
               this->visited.clear();
          }
          vertex *startV = this->nodes[startId];
          result.insertVertex(startId, startV->data);
          this->visited[startId] = true;
          vQueue.push(startV);
          while (!vQueue.empty())
          {
               // Visit all adjacent vertices
               vertex *v = vQueue.front();
               vQueue.pop();
               for (auto iterE = v->edges.begin(); iterE != v->edges.end(); ++iterE)
               {
                    edge *e = *iterE;
                    vertex *adjacent = e->vertices[0] == v ? e->vertices[1] : e->vertices[0]; // find "other" vertex
                    // add to queue if not visited and mark as visited
                    if (this->visited.find(adjacent->id) == this->visited.end())
                    {
                         vQueue.push(adjacent);
                         this->visited[adjacent->id] = true;
                         // add to result graph aswell
                         result.insertVertex(adjacent->id, adjacent->data);
                         result.createEdge(v->id, adjacent->id, e->data);
                    }
               }
          }
          this->visited.clear();
          return result;
     }

     UndirectedGraph<V, E> DFS(int startId)
     {
          if (this->nodes.find(startId) == this->nodes.end())
          { // Vertex not found on graph
               throw "Start vertex does not exist in this graph";
          }
          UndirectedGraph<V, E> result;
          stack<vertex *> stack;
          vertex *startV = this->nodes[startId];

          stack.push(startV);
          this->visited[startV->id] = true;
          result.insertVertex(startId, startV->data);

          while (!stack.empty())
          {
               vertex *current = stack.top();
               bool isNotVisited = false;
               for (auto itr = current->edges.begin(); itr != current->edges.end(); itr++)
               {
                    vertex *adjacent = (*itr)->vertices[0] == current ? (*itr)->vertices[1] : (*itr)->vertices[0];
                    if (!this->visited[adjacent->id])
                    {
                         isNotVisited = true;
                         stack.push(adjacent);
                         this->visited[adjacent->id] = true;
                         result.insertVertex(adjacent->id, adjacent->data);
                         result.createEdge(current->id, adjacent->id, (*itr)->data);
                         break;
                    }
               }
               if (!isNotVisited)
               {
                    stack.pop();
               }
          }
          this->visited.clear();
          return result;
     }

     UndirectedGraph<V, E> Astar(int startId, int endId, unordered_map<int, float> heuristicMap)
     {
          UndirectedGraph<V, E> result;
          unordered_map<int, float> relationMap;

          relationMap[startId] = 0.0;
          heuristicMap[startId] = 0.0;

          pair<int, float> min = *relationMap.begin();

          while (min.first != endId)
          {
               vertex *current = this->nodes[min.first];
               this->visited[current->id] = true;
               for (auto itr = current->edges.begin(); itr != current->edges.end(); itr++)
               {
                    vertex *adjacent = (*itr)->vertices[0] == current ? (*itr)->vertices[1] : (*itr)->vertices[0];
                    float weight = (relationMap[current->id] - heuristicMap[current->id]) + (*itr)->data + heuristicMap[adjacent->id];
                    if (!this->visited[adjacent->id])
                    {
                         if (relationMap.find(adjacent->id) == relationMap.end() || weight < relationMap[adjacent->id])
                         {
                              relationMap[adjacent->id] = weight;
                              adjacent->parent = current;
                         }
                    }
               }
               relationMap.erase(current->id);
               min = *min_element(relationMap.begin(), relationMap.end(), compareWeight);
          }
          vertex *node = this->nodes[min.first];
          vertex *parentNode = node->parent;
          result.insertVertex(node->id, node->data);
          while (node->id != startId)
          {
               result.insertVertex(parentNode->id, parentNode->data);
               for (auto itr = parentNode->edges.begin(); itr != parentNode->edges.end(); itr++)
               {
                    vertex *adjacent = (*itr)->vertices[0] == parentNode ? (*itr)->vertices[1] : (*itr)->vertices[0];
                    if (adjacent->id == node->id)
                    {
                         result.createEdge(parentNode->id, node->id, (*itr)->data);
                         break;
                    }
               }
               parentNode = parentNode->parent;
               node = node->parent;
          }
          return result;
     }

     UndirectedGraph<V, E> dijkstra(int startId)
     {
          if (this->nodes.find(startId) == this->nodes.end())
          { // Vertex not found on graph
               throw "Start vertex does not exist in this graph";
          }
          UndirectedGraph<V, E> result;
          E table[this->number_vertices];
          unordered_map<int, int> idMap;
          unordered_map<int, vertex *> invIdMap;
          int id = 0;
          // Map vertices ids to table ids and initialize first row of table
          for (auto iter = this->nodes.begin(); iter != this->nodes.end(); ++iter)
          {
               idMap[iter->first] = id;
               invIdMap[id] = iter->second;
               table[id] = numeric_limits<E>::max();
               id++;
          }

          // Variable to keep track of vertices parents/way
          unordered_map<int, int> parents; // Child, Parent
          // Initial vertex
          vertex *actualV = this->nodes[startId];
          vector<pair<vertex *, E>> adjacents;
          bool inserted = false;
          this->visited[actualV->id] = true;
          parents[actualV->id] = actualV->id;
          result.insertVertex(actualV->id, actualV->data);
          // Temporal variables to determine the "next" vertex
          vertex *minV = nullptr;
          E totalCost = 0;
          E tempCost;
          E minCostTemp = numeric_limits<E>::max();
          for (size_t i = 0; i < this->number_vertices; i++)
          {
               E minCost = numeric_limits<E>::max();
               // Save adjacent vertices on a vector
               for (auto iterE = actualV->edges.begin(); iterE != actualV->edges.end(); ++iterE)
               {
                    edge *e = *iterE;
                    vertex *adjacent = e->vertices[0] == actualV ? e->vertices[1] : e->vertices[0]; // find "other" vertex
                    bool isVisited = (this->visited.find(adjacent->id) != this->visited.end()) && (this->visited[adjacent->id] == true);
                    if (!isVisited)
                    {
                         adjacents.push_back(make_pair(adjacent, e->data));
                    }
               }
               for (size_t j = 0; j < this->number_vertices; j++)
               {
                    for (auto iterVec = adjacents.begin(); iterVec != adjacents.end(); ++iterVec)
                    {
                         vertex *adjacent = (*iterVec).first;
                         E cost = (*iterVec).second;
                         id = idMap[adjacent->id];
                         // Update table costs
                         tempCost = totalCost + cost;
                         if ((i == 0 && ((id == j) && (table[id] > tempCost))) || (i > 0 && ((id == j) && (table[id] > tempCost))))
                         {
                              table[j] = tempCost;
                              parents[adjacent->id] = actualV->id; // Update parent
                              if (i == 0)
                              {
                                   if (minCostTemp > cost)
                                   {
                                        minCostTemp = cost;
                                   }
                              }
                              else
                              {
                                   minCostTemp = cost;
                              }
                              adjacents.erase(iterVec);
                              --iterVec;
                              inserted = true;
                         }
                    }
                    if (!inserted)
                    {
                         if (i == 0)
                         { // On first row everything is infinite except adjacent vertices
                              if (j == idMap[actualV->id])
                              {
                                   table[j] = 0;
                              }
                              else
                              {
                                   table[j] = numeric_limits<E>::max();
                              }
                         }
                    }
                    inserted = false;
                    // Update "next vertex" and overall cost
                    bool notVisited = this->visited.find(invIdMap[j]->id) == this->visited.end();
                    if ((table[j] < minCost) && notVisited)
                    {
                         minV = invIdMap[j];
                         minCost = table[j];
                    }
               }

               result.insertVertex(minV->id, minV->data);
               int parentId = parents[minV->id];
               result.createEdge(parentId, minV->id, minCostTemp);
               actualV = minV;
               this->visited[actualV->id] = true;
               totalCost = minCost;
               adjacents.clear();
          }
          return result;
     }
};

typedef UndirectedGraph<string, double> uGraph;

#endif