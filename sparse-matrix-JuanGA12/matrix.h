#ifndef SPARSE_MATRIX_MATRIX_H
#define SPARSE_MATRIX_MATRIX_H

#include "node.h"
#include <stdexcept>
#include <vector>

using namespace std;

template <typename T>
class Matrix {
private:

    unsigned rows, columns;
    vector<Node<T>*> vector_rows;
    vector<Node<T>*> vector_columns;

    void addNode(Node<T>* newNode){

        for(auto temp_row = this->vector_rows[newNode->posX];temp_row;temp_row = temp_row->next){
            if(!temp_row->next){
                temp_row->next = newNode;
                break;
            }else if(newNode->posY == temp_row->next->posY){
                temp_row->next->data = newNode->data;
                break;
            }else if (newNode->posY < temp_row->next->posY){
                newNode->next = temp_row->next;
                temp_row->next = newNode;
                break;
            }
        }

        for(auto temp_column = this->vector_columns[newNode->posY];temp_column;temp_column = temp_column->down){
            if(!temp_column->down){
                temp_column->down = newNode;
                break;
            }else if(newNode->posX == temp_column->down->posX){
                temp_column->down->data = newNode->data;
                break;
            }else if (newNode->posX < temp_column->down->posX ){
                newNode->down = temp_column->down;
                temp_column->down = newNode;
                break;
            }
        }
    };
    void deleteNode(Node<T>* nodeToDelete){

        auto temp_row = this->vector_rows[nodeToDelete->posX];
        auto temp_column = this->vector_columns[nodeToDelete->posY];

        for(;temp_row->next != nodeToDelete; temp_row = temp_row->next);
        temp_row->next = temp_row->next->next;

        for(;temp_column->down != nodeToDelete; temp_column = temp_column->down);
        temp_column->down = temp_column->down->down;

        nodeToDelete = nullptr;
        delete nodeToDelete;

    };

    Node<T>* getNode(Node<T>* temp_row, unsigned column)const{
        for(;temp_row;temp_row = temp_row->next){
            if(!temp_row->next){
                return nullptr;
            }else if(temp_row->next->posY == column){
                return temp_row->next;
            }
        }
    };
public:

    Matrix(unsigned rows, unsigned columns){

        this->rows = rows;
        this->columns = columns;

        for (int i = 0; i < this->rows ; ++i) {
            this->vector_rows.push_back(new Node<T>());
        }

        for (int i = 0; i < this->columns ; ++i) {
            this->vector_columns.push_back(new Node<T>());
        }
    };

    void set(unsigned row, unsigned column, T data){

        if( row >= this->vector_rows.size() or row < 0 or column >= this->vector_columns.size() or column < 0){
            throw invalid_argument("Index no válido");
        }
        auto node = new Node<T>(row,column,data);
        if(data!=0) {
            addNode(node);
        }else{
            auto temp_row = this->vector_rows[row];
            auto node_tmp = getNode(temp_row,column);

            if(node_tmp){
                deleteNode(node_tmp);
            }else{
                throw invalid_argument("No se puede agregar Node con data = 0");
            }
        }

    };
    T operator()(unsigned row, unsigned column) const{

        if( row >= this->vector_rows.size() or row < 0 or column >= this->vector_columns.size() or column < 0){
            throw invalid_argument("Index no válido");
        }
        auto temp_row = this->vector_rows[row];
        auto node = getNode(temp_row,column);
        if (node){
            return node->data;
        }else{
            return 0;
        }
    };

    Matrix<T> operator*(T scalar) const{
        auto Escalar = Matrix(this->rows,this->columns);
        for(auto i : this->vector_rows){
            for(;i;i = i->next){
                Escalar.set(i->posX,i->posY,(i->data * scalar));
            }
        }
        return Escalar;

    };
    Matrix<T> operator*(Matrix<T> other) const{
        if(this->rows != other.columns){
            throw invalid_argument("No tienen el mismo tamaño");
        }else {
            auto Multi = Matrix(this->rows, other.columns);
            for(int i = 0; i < this->rows; ++i){
                for(int j = 0; j < other.columns; ++j ){
                    T data = 0;
                    for(int k = 0; k < this->columns; ++k){
                        data += (*this)(i,k) * other(k,j);
                    }
                    Multi.set(i,j,data);
                }
            }
            return Multi;
        }
    };
    Matrix<T> operator+(Matrix<T> other) const{
        if( (this->rows != other.rows) or (this->columns != other.columns)){
            throw invalid_argument("No tienen el mismo tamaño");
        }else{
            auto Suma = Matrix(this->rows,this->columns);

            for (int i = 0; i < this->vector_rows.size() ; ++i) {

                auto temp_row = this->vector_rows[i];
                auto temp_row_other = other.vector_rows[i];

                for(; temp_row->next or temp_row_other->next; ){

                    if (!temp_row->next and temp_row_other->next){

                        Suma.set(temp_row_other->next->posX,temp_row_other->next->posY,temp_row_other->next->data);
                        temp_row_other = temp_row_other->next;
                        continue;

                    }else if (temp_row->next and !temp_row_other->next) {

                        Suma.set(temp_row->next->posX,temp_row->next->posY,temp_row->next->data);
                        temp_row = temp_row->next;
                        continue;

                    }else{

                        if(temp_row->next->posY == temp_row_other->next->posY){

                            Suma.set(temp_row_other->next->posX,temp_row_other->next->posY, (temp_row->next->data + temp_row_other->next->data) );
                            temp_row = temp_row->next;
                            temp_row_other = temp_row_other->next;
                            continue;

                        }else if (temp_row->next->posY > temp_row_other->next->posY) {

                            Suma.set(temp_row_other->next->posX,temp_row_other->next->posY,temp_row_other->next->data);
                            temp_row_other = temp_row_other->next;
                            continue;

                        }else{

                            Suma.set(temp_row->next->posX,temp_row->next->posY,temp_row->next->data);
                            temp_row = temp_row->next;
                            continue;

                        }
                    }
                }
            }
            return Suma;
        }
    };
    Matrix<T> operator-(Matrix<T> other) const{
        if( (this->rows != other.rows) or (this->columns != other.columns)){
            throw invalid_argument("No tienen el mismo tamaño");
        }else{
            auto Resta = Matrix(this->rows,this->columns);

            for (int i = 0; i < this->vector_rows.size() ; ++i) {

                auto temp_row = this->vector_rows[i];
                auto temp_row_other = other.vector_rows[i];

                for(;temp_row->next or temp_row_other->next;){

                    if (!temp_row->next and temp_row_other->next){

                        Resta.set(temp_row_other->next->posX,temp_row_other->next->posY, -temp_row_other->next->data);
                        temp_row_other = temp_row_other->next;
                        continue;

                    }else if (temp_row->next and !temp_row_other->next) {

                        Resta.set(temp_row->next->posX,temp_row->next->posY,temp_row->next->data);
                        temp_row = temp_row->next;
                        continue;

                    }else {

                        if(temp_row->next->posY == temp_row_other->next->posY){

                            Resta.set(temp_row_other->next->posX,temp_row_other->next->posY, (temp_row->next->data - temp_row_other->next->data ));
                            temp_row = temp_row->next;
                            temp_row_other = temp_row_other->next;
                            continue;

                        }else if (temp_row->next->posY > temp_row_other->next->posY) {

                            Resta.set(temp_row_other->next->posX,temp_row_other->next->posY, -temp_row_other->next->data);
                            temp_row_other = temp_row_other->next;
                            continue;

                        }else {

                            Resta.set(temp_row->next->posX,temp_row->next->posY,temp_row->next->data);
                            temp_row = temp_row->next;
                            continue;

                        }
                    }
                }
            }
            return Resta;
        }
    };
    Matrix<T> transpose() const{
        auto rpta = Matrix(this->columns,this->rows);
        for(auto i : this->vector_rows){
            for(;i;i = i->next){
                rpta.set(i->posY,i->posX,(i->data));
            }
        }
        return rpta;
    };

    Matrix<T>& operator=(Matrix<T> other){

        for(auto to_delete : this->vector_rows){
            to_delete->killself_row();
        }

        this->vector_rows.clear();
        this->vector_columns.clear();

        this->rows = other.rows;
        this->columns = other.columns;

        for (int i = 0; i < this->rows ; ++i) {
            this->vector_rows.push_back(new Node<T>());
        }

        for (int i = 0; i < this->columns ; ++i) {
            this->vector_columns.push_back(new Node<T>());
        }

        for(int i = 0; i < other.vector_columns.size(); ++i){
            for(int j = 0; j < other.vector_rows.size(); ++j){
                this->set(i,j,other(i,j));
            }
        }
        return *this;
    };
    void print() const{
        for(int i = 0; i < this->vector_columns.size(); ++i){
            for(int j = 0; j < this->vector_rows.size(); ++j){
                cout<<(*this)(i,j)<<" ";
            }
            cout<<endl;
        }
    };


    ~Matrix(){

        for(auto to_delete : this->vector_rows){
            to_delete->killself_row();
        }
        this->vector_rows.clear();
        this->vector_columns.clear();
        this->rows = 0;
        this->columns = 0;

    }
};

#endif //SPARSE_MATRIX_MATRIX_H