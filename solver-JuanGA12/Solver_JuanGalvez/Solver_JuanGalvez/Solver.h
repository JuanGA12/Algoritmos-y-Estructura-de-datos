//
//  Solver.hpp
//  Solver_JuanGalvez
//
//  Created by Juan Galvez on 5/20/20.
//  Copyright © 2020 Juan Galvez. All rights reserved.
//

#ifndef Solver_hpp
#define Solver_hpp

#include <stdio.h>
#include <string>
#include <stack>
#include <vector>
#include <cmath>
#include <sstream>
#include <ctype.h>

using namespace std;

class Solver{
private:
    string ecuacion;
    vector<string>ecuacion_postfija;
    bool isOperator(char);
    string isParenthesis(char);
    int Weight_operators(char);
    double Operar(char, double, double);
    bool Num_decimal(string::iterator&, string & numero);

public:
    Solver(string& ecuacion): ecuacion(ecuacion){
        Postfijo();
        Resolver();
    }

    ~Solver() = default;
    vector<double>operacion;
    void Postfijo();
    void Resolver();
    void Imprimir_Postfijo();
    void Imprimir_Resultado();


};
#endif /* Solver_hpp */
