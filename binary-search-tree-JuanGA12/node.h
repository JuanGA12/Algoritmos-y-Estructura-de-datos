#ifndef NODE_H
#define NODE_H

template <typename T>
class BSTree; 

template <typename T>
class Iterator; 

template <typename T>
class Node {
public:
    int key;
    T data;
    Node<T>* left;
    Node<T>* right;

    Node(int key, T data): key(key), data(data){
        left = nullptr;
        right = nullptr;
    }

    void killSelf();

    template<class>
    friend class BSTree; 

    template<class>
    friend class Iterator;


};

template <typename T>
void Node<T>::killSelf() {

    if (left){
        left->killSelf();
    }
    else if (right){
        right->killSelf();
    }
    delete this;

}

#endif