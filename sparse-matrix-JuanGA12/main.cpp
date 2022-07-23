#include <iostream>

#include "tester/tester.h"
#include "matrix.h"
int main() {

    //Tester::execute();

    Matrix<int> a(3,3);
    Matrix<int> b(3,3);

    a.set(0,0,1);
    a.set(0,1,2);
    a.set(0,2,3);

    a.set(1,0,4);
    a.set(1,1,5);
    a.set(1,2,6);

    a.set(2,0,7);
    a.set(2,1,8);
    a.set(2,2,9);

    a.print();
    cout<<endl;
    a.set(1,1,0);
    a.print();
    cout<<endl;

    //cout<<a(1,1);

    a.print();
    cout<<endl;

    b.set(0,0,2);
    b.set(0,1,4);
    b.set(0,2,6);

    b.set(1,0,8);
    b.set(1,1,10);
    b.set(1,2,12);

    b.set(2,0,14);
    b.set(2,1,16);
    b.set(2,2,18);

    b.print();
    cout<<endl;

  // Matrix<int> c (3,3);
  //  c = a*b;
/*
    a.print();
    cout<<endl;

    b.print();
    cout<<endl;

    c.print();
    cout<<endl;

*/
    return EXIT_SUCCESS;
}

