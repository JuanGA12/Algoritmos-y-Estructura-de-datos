#ifndef SPARSE_MATRIX_NODE_H
#define SPARSE_MATRIX_NODE_H

template <typename T>
class Matrix;

template <typename T>
class Node {
protected:
    Node<T> *next, *down;
    T data;
    int posX;
    int posY;

public:
    explicit Node():data(0),posX(0),posY(0),next(nullptr),down(nullptr){};

    explicit Node(int posX, int posY, T data): posX(posX), posY(posY), data(data),next(nullptr),down(nullptr){};

    void killself_row(){
        if(next!= nullptr)
            next->killself_row();
        delete this;
    }
    friend class Matrix<T>;
};



#endif //SPARSE_MATRIX_NODE_H
