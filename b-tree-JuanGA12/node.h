#ifndef NODE_H
#define NODE_H

#include <vector>

using namespace std;

template <typename T>
class BTree;

template <typename T>
class Node {
    unsigned int size;
    vector<unsigned int> keys;
    vector<Node<T>*> children;
    bool isLeaf;

    public: 
        Node(unsigned int size, bool isLeaf = true) : size(size), isLeaf(isLeaf) {
            keys.resize(size - 1);
            children.resize(size);
        }

        /**
         * An alternative is to create two different nodes (Internal and Leaf) that inherite from Node 
         * an implement this function
         */
        //virtual bool isLeaf() = 0;

    friend class BTree<T>;
};

#endif