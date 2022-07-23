#include <iostream>
#include "bstree.h"
#include "tester/tester.cpp"

using namespace std;

int main(int argc, char *argv[]) {
    cout << "===========================================================" << endl;
    cout << "Binary Search Tree Practice" << endl;
    cout << "===========================================================" << endl << endl;

    Tester::execute();
    BSTree<int> r;
    r.insert(2,10);
    r.insert(3,20);
    r.insert(4,30);
    r.insert(5,40);
    r.insert(6,50);
    r.insert(1,25);
    //r.insert(37,5);
    cout<<r.root->key<<endl;
    if(r.root->left){
        cout<<r.root->left->key<<endl;
    }

    if(r.root->right){
        cout<<r.root->right->key<<endl;
    }

    if(r.root->left->left){
        cout<<r.root->left->left->key<<endl;
    }

    if(r.root->right->right){
        cout<<r.root->right->right->key<<endl;
    }

    if(r.root->left->left->left){
        cout<<r.root->left->left->left->key<<endl;
    }else{
        cout<<r.root->left->left->right->key<<endl;
    }

    if(r.root->right->right->right){
        cout<<r.root->right->right->right->key<<endl;
    }else{
        cout<<r.root->right->right->left->key<<endl;
    }

    //auto kk = r.begin();
    //r.insert(7,6);
    //r.insert(4,6);
    //r.insert(12,6);
    //r.insert(11,6);
    //r.insert(60,4);
    //r.insert(80,5);

    //r.insert(2,7);
    //r.insert(10,7);
    //r.insert(9,7);
    //cout<<r.height();
    //r.traverseInOrder();
    //r.remove(8);
    //r.traverseInOrder();
    //20 30 40 60 70 80
    //cout<<r.insert(3,4)<<endl;
    //cout<<r.remove(-3)<<endl;
    //cout<<r.insert(3,433333)<<endl;
    //cout<<r.hasKey(1)<<endl;
    //cout<<r.hasKey(30033)<<endl;
    //r.traversePostOrder();
    //cout<<r[3];
    //auto d = r.begin();
    //cout<<(*d).first;
    r.traverseInOrder();
    r.remove(30);
    r.traverseInOrder();
    r.remove(50);
    r.traverseInOrder();
    //r[10000];
    //r.~BSTree();

    return EXIT_SUCCESS;
}