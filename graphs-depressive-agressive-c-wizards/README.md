# Algorithms and Data Stuctures Project First Part

This first part of the project from the CS2100 course consists of creating a graph data structure and a file parser. This will allow us to build a graph and use all of the functionalities described below.

## Graph data structure

* This graph data structure is dynamic
* Multi-edged and looped graphs are not considered
* Directed and undirected graphs are allowed

### Methods:
```cpp
bool insertVertex(int id, V data); // Creates a new vertex in the graph with some data and an ID

bool createEdge(int start, int end, E data); // Creates a new edge in the graph with some data

bool deleteVertex(int id); // Deletes a vertex in the graph

bool deleteEdge(int start, int end); // Deletes an edge in the graph, it is not possible to search by the edge value, since it can be repeated

E &operator()(int start, int end); // Gets the value of the edge from the start and end vertexes

float density() const; // Calculates the density of the graph

isDense(float threshold = 0.5) const; // Calculates the density of the graph, and determine if it is dense dependening on a threshold value

bool isConnected(); // Detect if the graph is connected

bool isStronglyConnected() throw(); // Detect if the graph is strongly connected (only for directed graphs)

bool isBipartite(); // Detect if the graph is bipartite

bool empty(); // If the graph is empty

void clear(); // Clears the graph

// Undirected Graph only methods
UndirectedGraph<V, E> kruskal(); // Generates a MST graph using the kruskal approach

UndirectedGraph<V, E> Prim(int id); // Generates a MST graph using the prim approach
```

## JSON file parser

* Parses information about airports from a specific JSON file

### Methods:
```cpp
void clear(); // Clears parser saved atributes

void readJSON(); // Parses JSON file and saves data into class
// NOTE: each derived class has its own readJSON method

void uGraphMake(UndirectedGraph<string, double> &tempGraph); // Adds the parsed data into the specified undirected graph

void dGraphMake(DirectedGraph<string, double> &tempGraph); // Adds the parsed data into the specified directed graph
```

## Group Members
- Alessio Ghio 
- Nelson Soberón
- Juan Gálvez

## Git Karma Guidelines

```
<type>(<scope>): <subject>

<body>
```

### Allowed ```<type>``` values

* feat (new feature for the user, not a new feature for build script)
* fix (bug fix for the user, not a fix to a build script)
* docs (changes to the documentation)
* style (formatting, missing semi colons, etc)
* refactor (refactoring production code, eg. renaming a variable)
* test (adding missing tests, refactoring tests)
* chore (updating grunt tasks etc)

### Allowed ```<scope>``` values

* graph
* directedGraph
* undirectedGraph
* main
* tester
