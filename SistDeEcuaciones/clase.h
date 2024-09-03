#include<iostream>
#include<vector>
#include<iomanip>
#include<cmath>
using namespace std;

class matrix {
private:
    vector<vector<long double>> data;  // Almacena los elementos de la matriz
    int n;  // Tamaño de la matriz

public:
    // Constructor que inicializa una matriz de tamaño n x n
    matrix(int x) : n(x), data(x, vector<long double>(x+1, 0.0)) {}

    // Método para establecer un valor en una posición específica
    void set_value(int row, int col, long double value) {
        if (row >= 0 && row < n && col >= 0 && col < n+1) {
            data[row][col] = value;
        } else {
            cout << "Índice fuera de rango" << endl;
        }
    }

    // Método para obtener un valor en una posición específica
    long double get_value(int row, int col) const {
        if (row >= 0 && row < n && col >= 0 && col < n+1) {
            return data[row][col];
        } else {
            cout << "Índice fuera de rango" << endl;
            return -1;
        }
    }

    // Método para imprimir la matriz
    void print() const {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n+1; ++j) {
                cout << data[i][j] << " \t";
            }
            cout << endl;
        }
    }

    // suma por filas
    void op(int f1, int f2, long double k){
        if (f1 >= 0 && f1 < n && f2 >= 0 && f2 < n && f1 != f2) {
            for (int i = 0; i < n+1; ++i) {
                data[f1][i] = data[f1][i] + data[f2][i]*k;
            }
        } else {
            cout << "Índices fuera de rango en operacion por fila (suma)" << endl;
        }
    }

    // intercambio por filas
    void op(int f1, int f2){
        if (f1 >= 0 && f1 < n && f2 >= 0 && f2 < n && f1 != f2) {
            for (int i = 0; i < n+1; ++i) {
                double long temp = data[f1][i];
                data[f1][i] = data[f2][i];
                data[f2][i] = temp;
            }
        } else {
            cout << "Índices fuera de rango en operacion por fila (intercambio)" << endl;
        }
    }
};