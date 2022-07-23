#include <iostream>
//#include "self_list.h"
#include "test/tester.cpp"

using namespace std;

int main(int argc, char const *argv[]) {
    Tester::execute();

    SelfList<int> myList(SelfList<int>::Method::Transpose);
    myList.insert(1);
    myList.insert(2);
    myList.insert(4);
    myList.insert(7);
    myList.insert(9);
    myList.insert(11);
    myList.insert(7);

    myList.print();

    myList.remove(4); // Remover no funciona bien
    myList.remove(10);

    cout << "Find 10: " << endl;
    myList.find(10);
    myList.print(); cout << endl;

    cout << "Find 9: " << endl;
    myList.find(9);
    myList.print(); cout << endl;

    cout << "Find 11: " << endl;
    myList.find(11);
    myList.print(); cout << endl;

    cout << "Find 2: " << endl;
    myList.find(2);
    myList.print(); cout << endl;

    cout << "Find 11: " << endl;
    myList.find(11);
    myList.print(); cout << endl;
    return EXIT_SUCCESS;
}

