#ifndef NODE_H
#define NODE_H

template <typename T>
struct Node {
    T data;
    int contador;
    Node<T>* next;
    Node<T>* prev;
      
    Node(T data) : data(data), contador(0) {
        next = nullptr;
        prev = nullptr;
    }

      
    void killSelf();
};

template <typename T>
void Node<T>::killSelf() {
    if (next) {
        next->killSelf();
    }
    
    delete this;
}

#endif
