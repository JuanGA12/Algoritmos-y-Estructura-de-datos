#ifndef LINKED_H
#define LINKED_H

#include "list.h"
#include "iterators/bidirectional_iterator.h"

// TODO: Implement all methods
template <typename T>
class LinkedList : public List<T> {
    public:
        LinkedList() : List<T>() {}

        void swap( T& a, T &b){
            T max;
            max = a;
            a = b;
            b = max;
        }

        T front(){
            if (empty()) {
                throw logic_error("Empty");
            } else {
                return this->head->data;
            }
        };

        T back(){
            if (empty()) {
                throw logic_error("Empty");
            } else {
                return this->tail->data;
            }

        };

        void push_front(T data){
            auto newNode = new Node<T>;
            newNode->data = data;

            if(empty()){
                this->head = newNode;
                this->tail = newNode;
                newNode->next = nullptr;
                newNode->prev = nullptr;
            } else{
                newNode->next = this->head;
                this->head->prev = newNode;
                newNode->prev = nullptr;
                this->head = newNode;
            }
            this->nodes++;
        };

        void push_back(T data){
            auto newNode = new Node<T>;
            newNode->data = data;

            if(empty()){
                this->head = newNode;
                this->tail = newNode;
                newNode->next = nullptr;
                newNode->prev = nullptr;
            } else{
                newNode->prev = this->tail;
                this->tail->next = newNode;
                newNode->next = nullptr;
                this->tail = newNode;
            }
            this->nodes++;
        };

        void pop_front(){
            if (empty()) {
                throw logic_error("Empty");
            } else if (this->head == this->tail){

                auto tmp = this->head;
                this->head = nullptr;
                this->tail = nullptr;
                delete tmp;

            } else{
                auto tmp = this->head;
                this->head = this->head->next;
                this->head->prev = nullptr;
                delete tmp;

            }
            this->nodes--;
        };

        void pop_back(){
            if (empty()) {
                throw logic_error("Empty");
            } else if (this->head == this->tail){

                auto tmp = this->head;
                this->head = nullptr;
                this->tail = nullptr;
                delete tmp;

            } else{
                auto tmp = this->tail;
                this->tail = this->tail->prev;
                this->tail->next = nullptr;
                delete tmp;

            }
            this->nodes--;
        };

        T operator[](int posicion){
            if(empty()){
                throw logic_error("Empty");
            } else if (posicion < 0 || posicion >= this->nodes){
                throw logic_error("Rango invalido");
            } else {
                auto tmp = new Node<T>;
                tmp = this->head;
                for(int i = 0; i < posicion; ++i){
                    tmp = tmp->next;
                }
                return tmp->data;
            }
        };

        bool empty(){
            return this->nodes == 0;
        };

        int size(){
            return this->nodes;
        };

        void clear(){
            if(empty()){
                throw logic_error("Empty");
            }else{
                this->head->killSelf();
                this->head = this->tail = nullptr;
                this->nodes = 0;
            }

        };

        void sort(){
            if(empty()){
                throw logic_error("Empty");
            }else if (this->nodes == 1){
                return;
            }else{
                auto tmp = this->head;
                for(int i = 0; i < this->nodes; ++i){
                    while(tmp->next != this->tail->next){
                        if(tmp->data > tmp->next->data){
                            swap(tmp->data,tmp->next->data);
                        }
                        tmp = tmp->next;
                    }
                    tmp = this->head;
                }
                delete tmp;
            }
        };

        void reverse(){
            if (this->empty()) {
                throw logic_error("Empty");
            } else if (this->head->next == nullptr) {
                throw logic_error("1 nodo");
            } else{
                auto current = this->head;
                Node<T>* tmp = nullptr;
                while (current != nullptr) {
                    tmp = current->prev;
                    current->prev = current->next;
                    current->next = tmp;
                    current = current->prev;
                }
                auto new_tail = this->head;
                this->head = this->tail;
                this->tail = new_tail;
                delete tmp;
            }
        };

        BidirectionalIterator<T> begin(){
            return BidirectionalIterator<T> (this->head);
        };
	    BidirectionalIterator<T> end(){
            return BidirectionalIterator<T> (this->tail->next);
	    };

        string name() {
            return "Linked List";
        }

        /**
         * Merges x into the list by transferring all of its elements at their respective 
         * ordered positions into the container (both containers shall already be ordered).
         * 
         * This effectively removes all the elements in x (which becomes empty), and inserts 
         * them into their ordered position within container (which expands in size by the number 
         * of elements transferred). The operation is performed without constructing nor destroying
         * any element: they are transferred, no matter whether x is an lvalue or an rvalue, 
         * or whether the value_type supports move-construction or not.
        */
        void merge(LinkedList<T>& LinkedList){
            if(LinkedList.empty() && this->empty()){
                throw logic_error("Empty");
            }else {
                auto tmp = LinkedList.head;
                while (tmp != nullptr) {
                    push_back(tmp->data);
                    tmp = tmp->next;
                }
                LinkedList.clear();//removes all the elements in x (which becomes empty)
                //this->sort(); al ordenar toda la nueva lista, no pasa el test.
            }
        };
};

#endif