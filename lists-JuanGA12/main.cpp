#include <iostream>
#include "test/tester.cpp"
#include "structures/stack.h"
#include "structures/queue.h"

using namespace std;

int main(int argc, char *argv[]) {
    cout << "===========================================================" << endl;
    cout << "\tLists Practice" << endl;
    cout << "===========================================================" << endl << endl;

    Tester::execute();

    ForwardList<int>a;

    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.push_back(4);
    a.push_back(5);
    a.push_back(6);
    a.push_back(8);
    a.push_back(7);
    a.remover();
    return EXIT_SUCCESS;
}