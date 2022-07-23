#ifndef FORWARD_ITERATOR_H
#define FORWARD_ITERATOR_H

#include "../node.h"
#include "../forward.h"

// TODO: Implement all methods
template <typename T> 
class ForwardIterator {
    private:
        Node<T> *current;

    public:
        explicit ForwardIterator():current(nullptr){};
        explicit ForwardIterator(Node<T>* node):current(node){};

        ForwardIterator<T>& operator=(ForwardIterator<T> iter){
            this->current = iter.current;
            return this;
        };

        bool operator!=(ForwardIterator<T> iter){
            return this->current!=iter.current;
        };

        ForwardIterator<T> operator++(){
            this->current = this->current->next;
            return *this;
        };

        T operator*(){
            return this->current->data;
        };
};

#endif