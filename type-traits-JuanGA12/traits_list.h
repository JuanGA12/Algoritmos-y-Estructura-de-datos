
#ifndef TRAITS_LIST_H
#define TRAITS_LIST_H

#include "node.h"
#include <iostream>
using namespace std;

template <typename Tr>
class TraitsList {     
    public:
        typedef typename Tr::T T;
        typedef typename Tr::Operation Operation;
      
    private:
        Node<T>* head;
        Operation cmp;
        int nodes;

        bool find(T data, Node<T> **&pointer) {
            // TODO
            pointer = &this->head;
            while (*pointer != nullptr) {
                if(cmp((*pointer)->data,data)){// Esto puede pasar a ser parte del condicional del while
                    if((*pointer)->data == data) {
                        return true;
                    }
                }else{
                    return false;
                }
                pointer = &((*pointer)->next);
            }
            return false;
        }
              
    public:
        TraitsList() : head(nullptr), nodes(0) {};
             
        bool insert(T data) {
            // TODO: Don't allow repeated elements
            auto newNode = new Node<T>(data); // Estás creando nodos aún cuando no insertas (repetidos)

            if (!this->head) { // No es necesario
                this->head = newNode;
                newNode->next = nullptr;
                newNode->prev = nullptr;
                this->nodes++;
                return true;
            } else {
                Node<T> **tmp = nullptr;
                if (!find(data, tmp)) {
                    newNode->next = *tmp;
                    *tmp = newNode;
                    this->nodes++;
                    return true;
                }
                return false;
            }
        }
             
        bool remove(T data) {
            // TODO
            if(!this->head){
                throw logic_error("Empty");
            }else {
                Node<T> **tmp = &this->head;
                if (find(data, tmp)) {
                    auto aux = *tmp;
                    *tmp = (*tmp)->next;
                    delete aux;
                    this->nodes--;
                    return true;
                }
                return false;
            }

        }  

        bool find(T data) {
            // TODO
            Node<T> **tmp = nullptr;
            return find(data,tmp);

        }

        T operator[](int index) {
            // TODO
            if(!this->head){
                throw logic_error("Empty");
            } else if( index < 0 || index >= this->nodes) {
                throw logic_error("Rango invalido");
            } else {
                auto tmp = this->head;
                for (int i = 0; i < index; ++i) {
                    tmp = tmp->next;
                }
                return tmp->data;
            }
        }
             
        int size() {
            // TODO
            return this->nodes;
        }

        void print() {
            // TODO // remueve los TODOs
            if(!this->head){
                throw logic_error("Empty");
            }else {
                auto tmp = this->head;
                while (tmp) {
                    cout << tmp->data << " ";
                    tmp = tmp->next;
                }
                cout << endl;
            }
        }

        ~TraitsList() {
            // TODO
            while(this->head){ // While? Debería ser if, while es innecesario
                this->head->killSelf();
                this->head = nullptr;
                this->nodes = 0;
            }
        }         
};

#endif
