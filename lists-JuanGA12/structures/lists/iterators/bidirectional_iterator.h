#ifndef BIDIRECTIONAL_ITERATOR_H
#define BIDIRECTIONAL_ITERATOR_H

#include "../node.h"

// TODO: Implement all methods
template <typename T> 
class BidirectionalIterator {
    private:
        Node<T> *current;

    public:
        explicit BidirectionalIterator():current(nullptr){};
        explicit BidirectionalIterator(Node<T>* node):current(node){};

        BidirectionalIterator<T> operator=(BidirectionalIterator<T> iter){
            this->current = iter.current;
            return *this;
        };

        bool operator!=(BidirectionalIterator<T> iter){
            return this->current != iter.current;
        };

        BidirectionalIterator<T> operator++(){
            this->current = this->current->next;
            return *this;
        };

        BidirectionalIterator<T> operator--(){
            this->current = this->current->prev;
            return *this;
        };

        T operator*(){
            return this->current->data;
        };
};

#endif