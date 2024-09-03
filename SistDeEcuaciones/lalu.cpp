#include "clase.h"
using namespace std;


// Método para realizar la descomposición LU
void lu_decomposition(matrix& L, matrix& U, matrix& mat, int n) {
    for (int i = 0; i < n; i++) {
        // Llenar la matriz U
        for (int k = i; k < n; k++) {
            long double sum = 0.0;
            for (int j = 0; j < i; j++) {
                sum += (L.get_value(i, j) * U.get_value(j, k));
            }
            U.set_value(i, k, mat.get_value(i,k) - sum);
        }

        // Llenar la matriz L
        for (int k = i; k < n; k++) {
            if (i == k) {
                L.set_value(i, i, 1.0);  // Diagonal principal de L es 1
            } else {
                long double sum = 0.0;
                for (int j = 0; j < i; j++) {
                    sum += (L.get_value(k, j) * U.get_value(j, i));
                }
                L.set_value(k, i, (mat.get_value(k,i) - sum) / U.get_value(i, i));
            }
        }
    }
}

// Método para extraer el vector b (términos independientes)
vector<long double> extract_b(const matrix& mat, int n) {
    vector<long double> b(n);
    for (int i = 0; i < n; i++) {
        b[i] = mat.get_value(i,n);
    }
    return b;
}


// Función para resolver Ly = b usando sustitución hacia adelante
vector<long double> forward_substitution(const matrix& L, const vector<long double>& b, int n) {
    vector<long double> y(n);

    for (int i = 0; i < n; i++) {
        long double sum = 0.0;
        for (int j = 0; j < i; j++) {
            sum += L.get_value(i, j) * y[j];
        }
        y[i] = (b[i] - sum);
    }

    return y;
}

// Función para resolver Ux = y usando sustitución hacia atrás
vector<long double> backward_substitution(const matrix& U, const vector<long double>& y, int n) {
    vector<long double> x(n);

    for (int i = n - 1; i >= 0; i--) {
        long double sum = 0.0;
        for (int j = i + 1; j < n; j++) {
            sum += U.get_value(i, j) * x[j];
        }
        x[i] = (y[i] - sum) / U.get_value(i, i);
    }

    return x;
}

int main() {
    int n;
    long double o1;

    cout << "Cantidad de variables: ";
    cin >> n;

    matrix mat(n);
    matrix L(n);  // Matriz L (triangular inferior)
    matrix U(n);  // Matriz U (triangular superior)

    // Ingresando la matriz
    cout << "Ingresar matriz por filas (coeficientes y términos independientes):" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n + 1; j++) {
            cin >> o1;
            mat.set_value(i, j, o1);
        }
    }

    // Realizar la descomposición LU
    lu_decomposition(L, U, mat, n);

    // Extraer vector b (términos independientes)
    vector<long double> b = extract_b(mat, n);

    // Resolver Ly = b
    vector<long double> y = forward_substitution(L, b, n);

    // Resolver Ux = y
    vector<long double> x = backward_substitution(U, y, n);

    // Imprimir soluciones con máxima precisión
    cout << fixed << setprecision(10);
    cout << "Soluciones:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "x[" << i << "] = " << x[i] << endl;
    }

    return 0;
}