#ifndef SELF_LIST_H
#define SELF_LIST_H

#include "node.h"


using namespace std;

template <typename T>
class SelfList {
    public: 
        enum Method {
            Move, Count, Transpose
        };

    protected:
        Node<T>* head;
        Node<T>* tail;
        Method method;
        int nodes;
    private:
    bool normal_find(T data){

        auto tmp = this->head;
        while (tmp != nullptr) {
            if(tmp->data == data){
                return true;
            }
            tmp = tmp->next;
        }
        return false;
    }
    public:
        SelfList(Method method) : head(nullptr), tail(nullptr), nodes(0){
        this->method = method;
    };

        void swap( T& a, T& a2, T &b, T& b2){
            T max;
            max = a;
            a = b;
            b = max;

            T max2;
            max2 = a2;
            a2  = b2;
            b2 = max2;
        }

        bool insert(T data) {
            // TODO: If the value is already in the list, just ignore it

            if(normal_find(data)){
                return false;
            }
            //PUSH_BACK
            else {
                auto newNode = new Node<T>(data);

                if (!this->head) {
                    this->head = newNode;
                    this->tail = newNode;
                    newNode->next = nullptr;
                    newNode->prev = nullptr;
                } else {
                    newNode->prev = this->tail;
                    this->tail->next = newNode;
                    newNode->next = nullptr;
                    this->tail = newNode;
                }
                this->nodes++;
                return true;
            }
        }
             
        bool remove(T data) {
            // TODO
            if (!this->head) {
                throw logic_error("Empty");
            } else {
                if (!normal_find(data)) { // Mucha lógica repetida
                    return false;//No se puede remover si no esta
                } else if (this->head == this->tail) {//1 solo nodo
                    auto tmp = this->head;
                    this->head = nullptr;
                    this->tail = nullptr;
                    tmp->contador = 0;
                    delete tmp;
                    this->nodes--;
                    return true;
                } else if (this->head->data == data) {//pop_front
                    auto tmp = this->head;
                    this->head = this->head->next;
                    this->head->prev = nullptr;
                    tmp->contador = 0;
                    delete tmp;
                    this->nodes--;
                    return true;
                } else if (this->tail->data == data) {//pop_back
                    auto tmp = this->tail;
                    this->tail = this->tail->prev;
                    this->tail->next = nullptr;
                    tmp->contador = 0;
                    delete tmp;
                    this->nodes--;
                    return true;
                } else if (this->tail->data != data && this->head->data != data) {//remove by data
                    auto tmp = this->head;
                    while (tmp->next != nullptr && tmp->next->data != data) {
                        tmp = tmp->next;
                    }
                    tmp->next->contador = 0;
                    delete tmp->next;
                    tmp->next = tmp->next->next;
                    this->nodes--;
                    return true;
                } else {
                    return false;//si no se llego a remover
                }
            }
        }

        bool find(T data) {
            // TODO incrementa contador
            switch (this->method){

                case Count:{
                    if(!this->head){
                        throw logic_error("Empty");
                    }else{
                        //TODO CODIGO COUNT
                        if(this->head->data == data){
                            this->head->contador++;
                            return false; //no se puede mover si es head
                        }else {
                            auto tmp = this->head;
                            for (; tmp; tmp = tmp->next) {
                                if (tmp->data == data) {
                                    tmp->contador++;
                                    auto tmp2 = this->head;
                                    ordenar(tmp2);
                                    return true;
                                }
                            }
                            delete tmp;
                            return false;
                        }
                    }
                }

                case Move:{
                    if(!this->head){
                        throw logic_error("Empty");
                    }else{
                        //TODO CODIGO MOVE
                        if(this->head->data == data){
                            return false; //no se puede mover si es head
                        }else {
                            auto tmp = this->head;
                            for(;tmp;tmp = tmp->next){
                                if(tmp->data == data) {
                                    tmp->contador++;
                                    auto tmp2 = this->head;
                                    ordenar(tmp2);
                                    tmp2->contador=0;
                                    return true;
                                }
                            }
                            delete tmp;
                            return false;
                        }
                    }
                }

                case Transpose:{
                    if(!this->head){ // Sería mejor sacar a funciones privadas
                        throw logic_error("Empty");
                    }else{
                        //TODO CODIGO TRANSPOSE
                        if(this->head->data == data){
                            return false; //no se puede mover si es head
                        }else{
                            auto tmp = this->head;
                            for(;tmp;tmp = tmp->next){
                                if(tmp->data == data){
                                    tmp->contador -=1;
                                    tmp->prev->contador -=2;
                                    auto tmp2 = this->head;
                                    for (int i = 0; i < this->nodes; ++i) {
                                        while (tmp2->next != this->tail->next) {
                                            if (tmp2->contador < tmp2->next->contador) {
                                                swap(tmp2->contador, tmp2->data, tmp2->next->contador,
                                                     tmp2->next->data);
                                                tmp->contador=0;
                                                tmp->prev->contador=0;
                                            }
                                            tmp2 = tmp2->next;
                                        }
                                        tmp2 = this->head;
                                    }
                                    return true;
                                }
                            }
                            delete tmp;
                            return false;

                        }

                    }

                }
            }

            //default?

        }

        T operator [] (int index) {
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
            // TODO
            auto tmp = this->head;
            while (tmp != nullptr) {
                cout << tmp->data << " ";
                tmp = tmp->next;
            }
        }


        ~SelfList() {
            // TODO
            while (this->head) { // While?
                this->head->killSelf();
                this->head = this->tail = nullptr;
                this->nodes = 0;
            }
        }
        void ordenar(Node<T> *tmp2){
            for (int i = 0; i < this->nodes; ++i) {
                while (tmp2->next != this->tail->next) {
                    if (tmp2->contador < tmp2->next->contador) {
                        swap(tmp2->contador, tmp2->data, tmp2->next->contador,
                             tmp2->next->data);
                    }
                    tmp2 = tmp2->next;
                }
                tmp2 = this->head;
            }
        }
};

#endif
