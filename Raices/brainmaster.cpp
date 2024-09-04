#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

#define error pow(10,-3)
#define max_it 60
#define A 0.2
#define B 0.8

long double* biseccion();
long double* puntofijosuma(long double x0);
long double* newtonraphson(long double x0);
long double* secante();

long double f(long double x){
    return exp(-x)-x;
}

long double fd(long double x){
    return -exp(-x)-1;
    throw "derivada inexistente";
}

int main(){
    long double* x[6];
    bool s[6];

    for (int i = 0;i<6;i++) s[i]=true;

    //intentar cada metodo
    try{
        x[0] = biseccion();
    }
    catch(const char* e){
        cerr << "Error en biseccion: " << e << endl;
        s[0] = false;
    }

    try{
        x[1] = puntofijosuma(A);
    }
    catch(const char* e){
        cerr << "Error en puntofijosuma por A: " << e << endl;
        s[1] = false;
    }

    try{
        x[2] = puntofijosuma(B);
    }
    catch(const char* e){
        cerr << "Error en puntofijosuma por B: " << e << endl;
        s[2] = false;
    }

    try{
        x[3] = newtonraphson(A);
    }
    catch(const char* e){
        cerr << "Error en Newton-Raphson por A: " << e << endl;
        s[3] = false;
    }

    try{
        x[4] = newtonraphson(B);
    }
    catch(const char* e){
        cerr << "Error en Newton-Raphson por B: " << e << endl;
        s[4] = false;
    }

    try{
        x[5] = secante();
    }
    catch(const char* e){
        cerr << "Error en Secante: " << e << endl;
        s[5] = false;
    }

    //Imprimir resultados
    string methods[] = {"Biseccion", "Punto Fijo A", "Punto Fijo B", 
                        "Newton-Raphson A", "Newton-Raphson B", 
                        "Secante"};

    cout << fixed << setprecision(10);
    cout << left << setw(20) << "Metodo" 
         << setw(20) << "x" 
         << setw(20) << "f(x)" 
         << setw(20) << "Iteraciones" << endl;

    for (int i = 0; i < 6; ++i) {
        if (s[i]) {
            cout << left << setw(20) << methods[i] 
                 << setw(20) << x[i][0] 
                 << setw(20) << x[i][1] 
                 << setw(20) << x[i][2] << endl;
        }
    }

    return 0;
}

long double* biseccion(){
    long double b=B,a=A,x0;
    if ((f(a)*f(b)) >= 0) throw "invalidinterval";
    x0 = 999;
    for (int i=0;i<max_it;i++){
        long double c = (a+b)/2;

        if (abs(x0-c)<error) {
            static long double result[3];
            result[0] = c;            // Raíz estimada
            result[1] = f(c);         // Valor de la función en la raíz
            result[2] = i;            // Número de iteraciones realizadas
            return result;
        }

        if (f(a)*f(c) <= 0) {b=c;}
        else {a=c;}

        x0=c;

    }
    throw "No converge";
}

long double* puntofijosuma(long double x0){
    long double x;

    for (int i=0;i<max_it;i++){
        x = f(x0)+x0;
        if (abs(x-x0)<error){
            static long double result[3];
            result[0] = x;            // Raíz estimada
            result[1] = f(x);         // Valor de la función en la raíz
            result[2] = i;            // Número de iteraciones realizadas
            return result;
        }
        x0=x;
    }
    throw "No converge";
    }


long double* newtonraphson(long double x0){
    long double x;

    for (int i=0;i<max_it;i++){
        x = x0-(f(x0)/fd(x0));
        if (abs(x-x0)<error){
            static long double result[3];
            result[0] = x;            // Raíz estimada
            result[1] = f(x);         // Valor de la función en la raíz
            result[2] = i;            // Número de iteraciones realizadas
            return result;
        }
        x0=x;
    }
    throw "No converge";
    }


long double* secante(){
    long double x0=A, x=B, x1;

    for (int i=0;i<max_it;i++){
        x1 = x0-((f(x0)*(x-x0))/(f(x)-f(x0)));
        if (abs(x-x1)<error){
            static long double result[3];
            result[0] = x1;            // Raíz estimada
            result[1] = f(x1);         // Valor de la función en la raíz
            result[2] = i;             // Número de iteraciones realizadas
            return result;
        }
        x0=x;
        x=x1;
    }
    throw "No converge";
    }