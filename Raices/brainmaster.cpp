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

long double f(long double x){
    return exp(-x)-x;
}

int main(){
    long double* x[5];
    try{
        x[0] = biseccion();
    }
    catch(const char* e){
        cerr << "Error en biseccion: " << e << endl;
    }

    try{
        x[1] = puntofijosuma(A);
    }
    catch(const char* e){
        cerr << "Error en puntofijosuma por A: " << e << endl;
        x[1] = new long double[3];
        x[1][0] = 0;x[1][1] = 0;x[1][2] = 0;
    }

    try{
        x[2] = puntofijosuma(B);
    }
    catch(const char* e){
        cerr << "Error en puntofijosuma por B: " << e << endl;
        x[2] = new long double[3];
        x[2][0] = 0;x[2][1] = 0;x[2][2] = 0;
    }
    cout<<fixed<<setprecision(10);
    cout << "Metodo" << setw(11) << "x" << setw(19) << "f(x)" << setw(23) << "Iteraciones" << endl;
    cout<<"Biseccion\t"<<x[0][0]<<"\t"<<x[0][1]<<"\t"<<x[0][2]<<endl;
    cout<<"Punto Fijo A\t"<<x[1][0]<<"\t"<<x[1][1]<<"\t"<<x[1][2]<<endl;
    cout<<"Punto Fijo B\t"<<x[2][0]<<"\t"<<x[2][1]<<"\t"<<x[2][2]<<endl;


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
    throw "noconverge";
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
    throw "noconverge";
    }

