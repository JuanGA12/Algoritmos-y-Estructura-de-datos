#include <iostream>

#include "graph.h"
#include "directed.h"
#include "./parser/airports_parser.h"
using namespace std;

int main(int argc, char *argv[])
{
/*
    // graph test;
    DirectedGraph<string, int> c;
    c.insertVertex(1, "C");
    c.insertVertex(2, "F");
    c.insertVertex(3, "D");
    c.insertVertex(4, "H");
    c.insertVertex(5, "A");

    c.createEdge(1, 3, 6);
    c.createEdge(1, 4, 3);
    c.createEdge(2, 1, 3);
    c.createEdge(3, 4, 2);
    c.createEdge(4, 3, 1);
    c.createEdge(4, 2, 1);
    c.createEdge(5, 2, 4);
    c.createEdge(5, 4, 2);

    c.print();
    c.FloydWarshall();
 */   
    DirectedGraph<string,int>c;
    c.insertVertex(1,"C");
    c.insertVertex(2,"F");
    c.insertVertex(3,"D");
    c.insertVertex(4,"H");
    c.insertVertex(5,"J");
    c.insertVertex(6,"A");
    c.insertVertex(7,"B");
    c.insertVertex(8,"G");
    c.insertVertex(9,"E");
    c.insertVertex(10,"I");

    c.createEdge(1,2,7);
    c.createEdge(1,4,24);
    c.createEdge(1,3,11);
    c.createEdge(2,3,58);
    c.createEdge(3,4,26);
    c.createEdge(2,5,4);
    c.createEdge(2,6,17);
    c.createEdge(3,6,42);
    c.createEdge(3,7,19);
    c.createEdge(4,7,64);
    c.createEdge(4,8,3);
    c.createEdge(8,7,52);
    c.createEdge(7,6,5);
    c.createEdge(6,5,14);
    c.createEdge(5,9,5);
    c.createEdge(6,9,11);
    c.createEdge(9,10,29);
    c.createEdge(10,7,51);
    c.createEdge(10,8,33);
    c.FloydWarshall();
    c.BellmanFord(1);


    return EXIT_SUCCESS;
}
