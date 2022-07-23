//
//  Solver.cpp
//  Solver_JuanGalvez
//
//  Created by Juan Galvez on 5/20/20.
//  Copyright © 2020 Juan Galvez. All rights reserved.
//

#include "Solver.h"
#include <iostream>


using namespace std;

/*Variable global, no se necesitará como atributo de la clase Solver*/
vector<char> tmp;

bool Solver::isOperator(char token){
    return  token == '+' || token == '-' || token == '*' || token == '/' || token == '^';
}

string Solver::isParenthesis(char token){
    if(token == '('){
        return "left";
    }else if(token == ')'){
        return "right";
    }else{
        return "no_parenthesis";
    }
}

int Solver::Weight_operators(char token){
    if(token == '+' || token == '-'){
        return 1;
    }else if(token == '*' || token == '/'){
        return 2;
    }else if(token == '^'){
        return 3;
    }else{
        return -1;
    }
}

double Solver::Operar(char token , double pri, double seg){
    double rpta = 0;
    switch (token){
        case '+':
            rpta = pri + seg;
            return rpta;
        case '-':
            rpta = pri - seg;
            return rpta;
        case '*':
            rpta = pri * seg;
            return rpta;
        case '/':
            rpta = pri / seg;
            return rpta;
        case '^':
            rpta = pow(pri, seg);
            return rpta;
        default:
            return rpta;
    }
}
bool Solver::Num_decimal(string::iterator & punto, string & numero_decimal){
    auto aux = punto;
    punto = find(this->ecuacion.begin(),this->ecuacion.end(), '.');
    if(*punto == '.') {
        punto--;
        int cnt = 0;
        while (isdigit(*punto)) {
            punto--;
        }
        punto++;
        if(*punto == '.'){/* .numero = 0.numero  */
            numero_decimal += string(1, *punto);
            punto++;
        }
        while (isdigit(*(punto))) {
            cnt++;
            numero_decimal += string(1, *punto);
            punto++;
            if(*punto == '.'){
                cnt=0;
                numero_decimal += string(1, *punto);
                punto++;
            }
        }
        this->ecuacion_postfija.push_back(numero_decimal);
        punto -= (cnt + 1);
        this->ecuacion.erase(punto);
        punto += (cnt - 1);
        return true;
    }else {
        punto = aux;
        return false;
    }

}
void Solver::Postfijo(){
    int balanceado_parenthesis = 0;
    auto it = this->ecuacion.begin();
    for (; it != this->ecuacion.end(); advance(it,1)) {


        if(*it == ' '){
            continue;
        }

        /*Digitos*/
        if(*it == '+' or *it == '-'){
            /* Numeros negativos */
            if(isdigit(*(it+1))  && !isdigit(*(it-1)) && *it!='+') {
                /* Para numeros de 1 a más cifras */
                string numero_negativo;
                while (isdigit(*(it + 1))) {
                    if (*(it + 2) == '.') {
                        /* Numeros decimales negativos */
                        numero_negativo = "-";
                        Num_decimal(it, numero_negativo);
                        numero_negativo = "";
                        it++;
                        break;
                    }
                    numero_negativo += string(1, *it);
                    advance(it, 1);
                }
                auto f = find(this->ecuacion.begin(),this->ecuacion.end(), '(');
                if(*(f+1) == '-'){
                    goto normal_ecuacion;
                }
                if(*(it+1) == '*' or *(it+1) == '/' or *(it+1) == '^'){
                   numero_negativo = "";
                   it = this->ecuacion.begin();
                   goto operadores;
                }
                normal_ecuacion:
                if (isdigit(*it) && !numero_negativo.empty()) {
                    numero_negativo += string(1, *it);
                    this->ecuacion_postfija.push_back(numero_negativo);
                    continue;
                } else {
                    advance(it, -1);
                    continue;
                }
            }
            /* -.numero = -0.numero */
            if(*(it+1) == '.' && *it=='-'){
                string c = "-";
                Num_decimal(it,c);
                c = "";
                continue;
            }
            /* Fin numeros negativos */

            /* Simplifiacion de operadores +,- ejem, +-+ = -, -- = +, etc  */
            int cnt_operadores = 1;
            while( *(it+1) == '+' or *(it+1) == '-'){

                if(*(it+1) == '+'){
                    if(*it =='-'){
                        *it = '-';
                    }
                    cnt_operadores++;
                    *(it+1) = *(it+cnt_operadores);
                    *(it+cnt_operadores) = ' ';
                }
                if(*(it+1) == '-'){
                    if(*it =='+'){
                        *it = '-';
                    }
                    else{
                        *it = '+';
                    }
                    cnt_operadores++;
                    *(it+1) = *(it+cnt_operadores);
                    *(it+cnt_operadores) = ' ';
                }

            }
        }

        if(*it == '.'){/* .numero = 0.numero, positivos  */
            string c;
            Num_decimal(it,c);
            c="";
            continue;
        }
            /* Numeros Positivos */
        if(isdigit(*it)) {
            /* Juntando numeros que se separaron en la simplificación de operadores */
            if(isdigit(*(it+2)) && *(it+1) == ' '){
                *(it+1)=*(it+2);
                *(it+2) = ' ';
            }
            /* Para numeros de 1 a más cifras */
            string numero_positivo;
            while (isdigit(*it)) {
                if(*(it+1) == '.'){
                    /* Numeros decimales */
                    numero_positivo="";
                    Num_decimal(it,numero_positivo);
                    numero_positivo="";
                    break;
                }
                numero_positivo += string(1, *it);
                advance(it,1);
            }
            if(!numero_positivo.empty()) {
                this->ecuacion_postfija.push_back(numero_positivo);
                advance(it, -1);
                continue;
            }else{
                continue;
            }
        }
        /*Parentesis*/
        if(isParenthesis(*it) == "right" || isParenthesis(*it) == "left"){
            if(isParenthesis(*it) == "left"){
                balanceado_parenthesis++;
                tmp.push_back(*it);
                continue;
            }else{
                balanceado_parenthesis--;
                while (!tmp.empty() && isParenthesis(tmp.back()) != "left"){
                    this->ecuacion_postfija.push_back(string(1,tmp.back()));
                    tmp.pop_back();
                }
                tmp.pop_back();
            }
        }

        operadores:
        /*Operadores*/
        if (isOperator(*it)) {
            while (!tmp.empty() && Weight_operators(*it) <= Weight_operators(tmp.back())){
                this->ecuacion_postfija.push_back(string(1,tmp.back()));
                tmp.pop_back();
            }
            tmp.push_back(*it);
            continue;
        }

        /*Variables*/
        if (isalpha(*it)) {
            while (true){
                double i = 0;
                string numero;
                cout<<"Ingresar valor de la variable "<<*it<<": ";
                cin>>numero;
                stringstream mystream(numero);
                if(mystream >> i) {
                    this->ecuacion_postfija.push_back(to_string((double)(i)));
                    break;
                }else{
                    cout<<"Valor no valido"<<endl;
                }
            }
            continue;
        }
    }
    /* En caso que se ingrese una ecuacion que no esté balanceada */
    if(balanceado_parenthesis != 0){
        throw logic_error("La ecuación no esta balanceada por parentesis");
    }
    /*Push y vaciar vector*/
    while (!tmp.empty()) {
        this->ecuacion_postfija.push_back(string(1,tmp.back()));
        tmp.pop_back();
    }

}

void Solver::Resolver(){

    double primer_valor = 0;
    double segundo_valor = 0;

    auto it = this->ecuacion_postfija.begin();
    for(;it != this->ecuacion_postfija.end(); advance(it,1)){
        
    string operador = *it;

        /*Digitos*/

            /* Numeros positivos */       /* Numeros negativos */                             /* .numero */                                     /* -.numero */
        if(isdigit(operador[0]) || (operador[0] == '-' && isdigit(operador[1])) || (operador[0] == '.' && isdigit(operador[1])) || (operador[0] == '-' && operador[1] == '.')){
            /* Para cualquier tipo de numero */
            this->operacion.push_back(stod(*it));
            continue;
        }
        /*Asignando valores para operar*/
        if(!this->operacion.empty() && isOperator(operador[0])){
            segundo_valor = (!this->operacion.empty()) ?  this->operacion.back() : 0;
            this->operacion.pop_back();
            primer_valor = (!this->operacion.empty()) ?  this->operacion.back() : 0;
            this->operacion.pop_back();
        }
        /*Respuesta*/
        this->operacion.push_back(Operar(operador[0],primer_valor,segundo_valor));
    }
}

void Solver::Imprimir_Postfijo(){
    cout<<"Ecuacion en Postfijo: ";
    for(auto &x : this->ecuacion_postfija){
        cout<<x<<" ";
    }
    cout<<endl;
}

void Solver::Imprimir_Resultado() {
    cout<<"Respuesta: "<<fixed<<this->operacion.back()<<endl;
}


