#ifndef NODE_H
#define NODE_H

template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;

    void killSelf(){
        if(next){
            next->killSelf();
        }
        delete this;
    };
};

#endif