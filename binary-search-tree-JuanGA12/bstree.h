#ifndef BSTREE_H
#define BSTREE_H

#include <algorithm>
#include "node.h"
#include "iterator.h"
#define BASURA this->root->data - this->root->data

using namespace std;

template <typename T> 
class BSTree {
public:
    Node<T> *root;
    int nodes;
private:

    bool find_by_key(Node<T>** &node, int key){
        node = &this->root;
        while(*node){
            if((*node)->key == key){
                return true;
            }else{
                node = (key > (*node)->key) ? &(*node)->right : &(*node)->left;
            }
        }
        return false;
    }
    int height(Node<T>* &root_){
        if(!root_){
            return 0;
        }else{
            int height_left = height(root_->left);
            int height_right = height(root_->right);
            return 1 + max(height_left,height_right);
        }
    }
    bool insertar (Node<T>** &node, int key, T data){
        auto newNode = new Node<T>(key,data);
        (*node) = newNode;
        this->nodes++;
        return true;
    }
    Node<T> **Deriv_izquierda(Node<T>** &node){
        node = &(*node)->right;
        while ((*node)->left) {
            node = &(*node)->left;
        }
        return node;
    }
    Node<T> **Deriv_derecha(Node<T>** &node){
        node = &(*node)->left;
        while ((*node)->right) {
            node = &(*node)->right;
        }
        return node;
    }
    bool remover( Node<T>** &node, int key){
        /* Vamos a ver cual de los 3 casos es*/
        if (!(*node)->right && !(*node)->left) {/* No tiene hijos, es hoja */
            delete *node;
            (*node) = nullptr;
            return true;
        }
        Node<T> *aux = *node;/* Guardando node actual*/
        if((*node)->right && (*node)->left) {/* Tiene dos hijos */
            node = Deriv_izquierda(node); /* Tambien se puede usar Deriv_derecha(), solo se
            *tendria que decidir si usar el sucesor o predecesor */
            swap(aux->key, (*node)->key);
            swap(aux->data, (*node)->data);
            remover(node, (*node)->key);
        }else {/* Un solo hijo, a la izquierda o derecha */
            (*node) = (!(*node)->right) ? (*node)->left : (*node)->right;
            delete aux;/* Eliminando node guardado*/
            return true;
        }
    }
    void Pre_order(Node<T>* &root_){
        if(root_){
            cout<<root_->key<<" ";
            Pre_order(root_->left);
            Pre_order(root_->right);
        }
    }
    void In_order(Node<T>* &root_){
        if(root_){
            In_order(root_->left);
            cout<<root_->key<<" ";
            In_order(root_->right);
        }
    }
    void Post_order(Node<T>* &root_){
        if(root_){
            Post_order(root_->left);
            Post_order(root_->right);
            cout<<root_->key<<" ";
        }
    }
public:
    BSTree() : root(nullptr), nodes(0) {};

    bool insert(int key , T data) {
        // TODO: Inserts an element with a key (a repeat key replaces the value)
        if( key<0 ){/* Para esta tarea, solo se aceptaran keys positivas*/
            throw out_of_range ("Key invalido");
        }else {
            //TODO CODIGO, FIND IF KEY EXIST, LOGICA Y CODIGO PARA INSERT
            Node<T> **tmp = nullptr;
            return ( find_by_key(tmp, key) ) ? (*tmp)->data = data, false : insertar(tmp, key, data);
            /* Retorna false en caso si se reemplaza el valor, no INSERTO, solo REEMPLAZÓ data*/
        }
    }
    bool remove(int key) {
        // TODO: Removes an element with a certain key
        Node<T>** tmp = nullptr;
        if(empty()||!find_by_key(tmp,key)){
            return false;/* Vacio o no se encontró key para remover*/
        }else{
            //TODO LOGICA Y CODIGO PARA REMOVE
            return (remover(tmp,key)) ? this->nodes--, true : false;
            /* Se resta el numero de nodos, solo si se removió */
        }
    }
    bool hasKey(int key) {
        // TODO: Looks for a key in the tree
        Node<T>** tmp = nullptr;
        return ( empty() ) ? false : find_by_key(tmp,key);
    }
    T &operator[](int key) {
        // TODO: Gets the element with a certain key 
        // NOTE: For 1+ point, research if it is possible to update the node with this same function (like insert, e.g. tree[2] = "hola")
        if(empty()){
            throw out_of_range ("Vacio");
        }else if(key < 0){
            throw out_of_range ("Key invalida");
        }else{
            Node<T>**tmp = nullptr;
            return find_by_key(tmp,key) ? (*tmp)->data : insert(key,BASURA), (*tmp)->data ;
        }
    }
    int size() {
        // TODO: Amount of nodes
        return this->nodes;
    }
    int height() {
        // TODO
        return height(this->root);
    }
    bool empty() const {
        // TODO: If the tree is empty
        return !this->root;
    }
    void traversePreOrder() {
        // TODO
        empty() ? throw logic_error ("Vacio") : Pre_order(this->root),cout<<endl;
    }
    void traverseInOrder() {
        // TODO
        empty() ? throw logic_error ("Vacio") : In_order(this->root),cout<<endl;
    }
    void traversePostOrder() {
        // TODO
        empty() ? throw logic_error ("Vacio") : Post_order(this->root),cout<<endl;
    }
    Iterator<T> begin() {
        // TODO
        return Iterator<T>(this->root);
    }
    Iterator<T> end() { 
        // TODO
        return Iterator<T>();
    }
    ~BSTree() {
        // TODO
        (this->root) ? this->root->killSelf(), this->root = nullptr, this->nodes = 0 : false;
    }
};

#endif
