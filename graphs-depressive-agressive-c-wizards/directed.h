#ifndef DIRECTED_H
#define DIRECTED_H

#include <unordered_map>
#include <stack>
#include <queue>
#include <iomanip>
#include <map>
#include "graph.h"
#include "vertex.h"
#include "edge.h"

template <typename V, typename E>
class DirectedGraph : public Graph<V, E>
{
public:
    typedef typename Graph<V, E>::vertex vertex;
    typedef typename Graph<V, E>::edge edge;

private:

    bool edgeExists(vertex *start, vertex *end)
    { // Slightly different from undirected
        if (!start || !end)
            return false;
        if (start->edges.empty())
        {
            return false;
        }
        bool exists = false;
        for (auto iter = start->edges.begin(); iter != start->edges.end(); ++iter)
        {
            edge *e = *iter;
            if (e->vertices[1] == end)
            {
                exists = true;
                break;
            };
        }
        return exists;
    }

    edge *findEdge(vertex *start, vertex *end){

        if(start || end) {
            if (edgeExists(start, end)) {
                // Slightly different from undirected
                auto edges = &start->edges;
                auto it = edges->begin();
                for (; it != edges->end(); advance(it, 1)) {
                    edge *e = *it;
                    if (e->vertices[1] == end) {
                        return e;
                    }
                }
            }
            return nullptr;
        }else{
            return nullptr;
        }
    }
    static bool compareWeight(pair<int, float> a, pair<int, float> b) { return (a.second < b.second); }

public:
    DirectedGraph() : Graph<V, E>() {}

    DirectedGraph(const DirectedGraph &other) : Graph<V, E>()
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
            }
        }
    }

    ~DirectedGraph()
    {
        this->clear();
    }


    /**
        * Creates a new edge in the graph with some data
        * @param start id of start vertex
        * @param end id of the end vertex
        * @param data value of the edge
        * @return true if inserted, false if the edge is already in the graph, or one or both of the vertices do not exist
    **/
    bool createEdge(int start, int end, E data) override
    { // Different from undirected graph
        bool verticesExist = (this->nodes.find(start) != this->nodes.end()) && (this->nodes.find(end) != this->nodes.end());
        if (verticesExist)
        {
            if (edgeExists(this->nodes[start], this->nodes[end]))
            {
                return false;
            }
            edge *newEdge = new edge(this->nodes[start], this->nodes[end], data);
            this->nodes[start]->edges.push_back(newEdge);
            this->number_edges++;
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
            vertex *toDelete = this->nodes[id];
            for (auto iter1 = this->nodes.begin(); iter1 != this->nodes.end(); iter1++)
            {
                vertex *current = iter1->second;
                for (auto iter2 = current->edges.begin(); iter2 != current->edges.end(); ++iter2)
                {
                    if ((*iter2)->vertices[0] == toDelete || (*iter2)->vertices[1] == toDelete)
                    {
                        current->edges.erase(iter2);
                        iter2--;
                    }
                }
            }
            this->nodes.erase(id);
            delete toDelete;
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
        // Slightly different from undirected
        edge *edgeTemp = findEdge(this->nodes[start], this->nodes[end]);
        if (edgeTemp)
        {
            vertex *v = edgeTemp->vertices[0];
            for (auto it = v->edges.begin(); it != v->edges.end(); ++it)
            {
                edge *e = *it;
                if (e == edgeTemp)
                {
                    v->edges.erase(it);
                    break;
                }
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
    { // Different from undirected graph
        vertex *vStart = this->nodes[start];
        vertex *vEnd = this->nodes[end];
        if (!vStart->edges.empty())
        {
            for (auto iter = vStart->edges.begin(); iter != vStart->edges.end(); ++iter)
            {
                edge *e = *iter;
                if (e->vertices[1] == vEnd)
                {
                    return e->data;
                }
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
        return (float(Edges) / float(Vertices * (Vertices - 1)));
    }


    /**
        * Detect if the graph is connected
        * @return true if it is connected and false if there is at least one missing connection
    **/
    bool isConnected() override
    {
        for (auto itr = this->nodes.begin(); itr != this->nodes.end(); itr++)
        {
            this->dfs(itr->second);
            if (this->nodes.size() == this->visited.size())
            {
                return true;
            }
            this->visited.clear();
        }
        return false;
    }

    /**
        * Detect if the graph is strongly connected (only for directed graphs)
        * @return true if it is strongly connected 
        * @throw exception if this method is called from a non-directed graph
        **/
    bool isStronglyConnected() throw() override
    {
        for (auto itr = this->nodes.begin(); itr != this->nodes.end(); itr++)
        {
            this->dfs(itr->second);
            if (this->nodes.size() != this->visited.size())
            {
                return false;
            }
            this->visited.clear();
        }
        return true;
    }

    /**
        * Detect if the graph is bipartite
        * @return true if it is bipartite 
        **/
    bool isBipartite() override
    { // Different from undirected graph
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
            this->visited[it->first] = false;
        }
        colorsMap[this->visited.begin()->first] = 0;
        auto it = this->visited.begin();
        while (!this->visited.empty())
        { // Iterate through all vertices of graph
            if (it->second == true)
            {
                this->visited.erase(it);
                it = this->visited.begin();
                continue; // No need to revisit the vertex
            }
            int key = it->first;
            this->visited[key] = true;
            vertex *v = this->nodes[key];
            for (auto iter = v->edges.begin(); iter != v->edges.end(); ++iter)
            { // Iterate through all edges of vertex
                edge *e = *iter;
                vertex *vTemp = e->vertices[1]; // Find the "other" vertex
                int keyTemp = vTemp->id;

                // Determine if vertex needs to be explored again: itself niether its adyacent vertices have been colored
                if (colorsMap[key] == -1 && colorsMap[keyTemp] == -1)
                {
                    this->visited[key] = false;
                    continue;
                }
                // Determine if vertex has not been colored but adjacent vertex has
                else if (colorsMap[key] == -1 && colorsMap[keyTemp] != -1)
                { // Color the vertex with an opposite color
                    colorsMap[key] = !colorsMap[keyTemp];
                    continue;
                }

                // else: color other vertex
                if (colorsMap[keyTemp] == -1)
                { // Vertex has not been visited, "paint" it to a different color
                    colorsMap[keyTemp] = !colorsMap[key];
                }
                else if (colorsMap[keyTemp] == colorsMap[key])
                { // Neighbor vertex has the same color: Not bipartite
                    this->visited.clear();
                    return false;
                } // else: neighbor vertex has a different color, all good, do nothing
            }
            ++it;
            if (it == this->visited.end())
            {
                it = this->visited.begin();
            }
        }
        return true;
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
                delete e;
                v->edges.erase(iterL);
                iterL = v->edges.begin();
            }
            delete v;
            this->nodes.erase(iterM);
            iterM = this->nodes.begin();
        }
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
                cout << u->id << " -- " << (*e)->data << " --> " << v->id << endl
                     << setw(16);
            }
            cout << endl;
        }
        cout << setw(0);
    }

    DirectedGraph<V, E> BFS(int startId)
    {
        if (this->nodes.find(startId) == this->nodes.end())
        { // Vertex not found on graph
            throw "Start vertex does not exist in this graph";
        }
        DirectedGraph<V, E> result;
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
                vertex *adjacent = e->vertices[1]; // select "other" vertex
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
        return result;
    }

    DirectedGraph<V, E> DFS(int startId)
    {
        if (this->nodes.find(startId) == this->nodes.end())
        { // Vertex not found on graph
            throw "Start vertex does not exist in this graph";
        }
        DirectedGraph<V, E> result;
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
                vertex *adjacent = (*itr)->vertices[1];
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
        return result;
    }

    DirectedGraph<V, E> Astar(int startId, int endId, unordered_map<int, float> heuristicMap)
    {
        DirectedGraph<V, E> result;
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
                vertex *adjacent = (*itr)->vertices[1];
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
                vertex *adjacent = (*itr)->vertices[1];
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
    DirectedGraph<V, E> dijkstra(int startId)
    {
        if (this->nodes.find(startId) == this->nodes.end())
        { // Vertex not found on graph
            throw "Start vertex does not exist in this graph";
        }
        DirectedGraph<V, E> result;
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
                vertex *adjacent = e->vertices[1]; // find "other" vertex
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

    pair<vector<vector<int>>,vector<vector<int>>>FloydWarshall() {

        vector<vector<int>> MatrizD(this->number_vertices, vector<int>(this->number_vertices));
        vector<vector<int>> MatrizR(this->number_vertices, vector<int>(this->number_vertices));

        /* Set Matriz Distancia y Matriz Recorrido */
        for(int i = 0; i < this->number_vertices; ++i) {
            for(int j = 0; j < this->number_vertices; ++j) {
                if(i == j) {
                    MatrizD[i][j] = 0;
                    MatrizR[i][j] = 0;
                }
                else{
                    auto tmp = findEdge(this->nodes[i+1], this->nodes[j+1]);
                    MatrizD[i][j] = tmp ? tmp->data : 21474836;
                    MatrizR[i][j] = j + 1;
                }
            }
        }
        /* Logica */
        for(int i = 0; i < this->number_vertices; ++i) {
            for (int  j = 0; j < this->number_vertices; ++j) {
                for (int k = 0; k < this->number_vertices; ++k) {
                        if ( ( MatrizD[j][i] + MatrizD[i][k] ) < MatrizD[j][k] ) {
                            MatrizD[j][k] = MatrizD[j][i] + MatrizD[i][k];
                            MatrizR[j][k] = i + 1;
                        }
                }
            }
        }
        /* Imprimir matrices */
        cout<<"Matriz de Distancia"<<endl;

        for(int i = 0; i < this->number_vertices; ++i) {
            for(int j=0; j < this->number_vertices; ++j) {
                if(MatrizD[i][j] == 21474836 ){
                    cout<<"∞"<<" ";
                }
                else{
                    cout<<MatrizD[i][j]<<" ";
                }
            }
            cout<<endl;
        }
        cout<<endl;
        cout<<"Matriz de Recorrido"<<endl;

        for(int i = 0; i < this->number_vertices; ++i) {
            for(int j = 0; j < this->number_vertices; ++j) {
                if(MatrizR[i][j] == 0){
                    cout<<"-"<<" ";
                }else {
                    cout<<MatrizR[i][j]<< " ";
                }
            }
            cout<<endl;
        }

        return make_pair(MatrizD,MatrizR);
    }

    unordered_map <int,int> BellmanFord(int startId){

        unordered_map <int,int> distances;
        for(auto node : this->nodes){
            distances[node.second->id] = INT_MAX;
        }
        distances[startId] = 0;

        for (int j = 0; j < this->number_vertices - 1 ; ++j) {
            for (auto node : this->nodes){
                for (auto edge : this->nodes[node.second->id]->edges){
                    int data = edge->data;
                    int start = edge->vertices[0]->id;
                    int end = edge->vertices[1]->id;
                    if(distances[start] != INT_MAX && distances[start] + data < distances[end]){
                        distances[end] = distances[start] + data;
                    }

                }
            }

        }

        for(auto node : this->nodes){
            for(auto edge : this->nodes[node.second->id]->edges){
                int data = edge->data;
                int start = edge->vertices[0]->id;
                int end = edge->vertices[1]->id;
                if(distances[start] != INT_MAX && distances[start] + data < distances[end]){
                    throw invalid_argument("Grafo tiene un ciclo con peso negativo");
                }
            }
        }
        cout<<"Vertex\t Distance from Source: "<<this->nodes[startId]->data<<endl;
        for (auto node : this->nodes) {
            cout<<node.second->data<<"\t\t "<<distances[node.second->id]<<endl;
        }

        return distances;
    }

};

typedef DirectedGraph<string, double> dGraph;

#endif