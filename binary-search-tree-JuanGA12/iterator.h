#ifndef ITERATOR_H
#define ITERATOR_H

#include <utility>
#include <vector>
#include "node.h"

using namespace std;
template <typename T> 
class Iterator {

private:
    vector<Node<T> *> nodes;
    Node<T> * current;
public:
    explicit Iterator():current(nullptr) {
        // TODO
    }

    explicit Iterator(Node<T>* node) {
        // TODO
        if(!node){
            this->current = nullptr;
        }else{
            while(node){
                this->nodes.push_back(node);
                node = node->left;
            }
            this->current = this->nodes.back();
        }
    }

    Iterator<T>& operator=(const Iterator<T> &other) {          
        // TODO
        this->current = other.current;
        return *this;
    }

    bool operator!=(Iterator<T> other) {
        // TODO
        return this->current != other.current;
    }

    Iterator<T>& operator++() {
        // TODO
        if(!this->current){
            throw out_of_range ("Vacio");
        }else {
            if (this->current->right) {
                auto temp = this->current->right;
                this->nodes.pop_back();
                while (temp) {
                    this->nodes.push_back(temp);
                    temp = temp->left;
                }
            } else {
                this->nodes.pop_back();
            }
            this->current = this->nodes.empty() ? nullptr : this->nodes.back();
            /*if (this->nodes.empty()) {
                this->current = nullptr;
            } else {
                this->current = this->nodes.back();
            }*/
            return *this;
        }
    }

    pair<int, T> operator*() {
        // TODO
        return (!this->current) ? throw out_of_range ("Vacio") : make_pair(this->current->key,this->current->data);
        /*if(!this->current){
            throw out_of_range ("Vacio");
        }else{
            pair<int,T> it;
            it = make_pair(this->current->key,this->current->data);
            return it;
        }
         */
    }
};

#endif
