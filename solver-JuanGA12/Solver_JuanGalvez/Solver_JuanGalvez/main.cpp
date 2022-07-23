//
//  main.cpp
//  Solver_JuanGalvez
//
//  Created by Juan Galvez on 5/16/20.
//  Copyright © 2020 Juan Galvez. All rights reserved.
//

#include <iostream>
#include <vector>
#include <sstream>
#include "Solver.cpp"
#include "tests/Tester.cpp"

using namespace std;

int main(int argc, char *argv[]) {
    // insert code here...
    cout << "===========================================================" << endl;
    cout << "Solver Juan Galvez" << endl;
    cout << "===========================================================" << endl << endl;
    Tester::execute();

    cout<<endl<<endl<<endl;
    string ecuacion = "(+500^4)";
    cout<<"Ecuacion: "<<ecuacion<<endl;
    Solver solver(ecuacion);
    solver.Imprimir_Postfijo();
    solver.Imprimir_Resultado();
    cout<<endl;
    ecuacion = "-500^4";
    cout<<"Ecuacion: "<<ecuacion<<endl;
    Solver solver2(ecuacion);
    solver2.Imprimir_Postfijo();
    solver2.Imprimir_Resultado();

    return EXIT_SUCCESS;
}

