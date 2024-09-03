#include "clase.h"

#define tolerancia 1e-6
#define max_it 30

using namespace std;

int main() {
    int n;
    long double o1, error;
    
    cout << "Cantidad de variables: ";
    cin >> n;
    
    matrix mat(n);
    
    // Ingresando la matriz
    cout << "Ingresar matriz por filas (coeficientes y términos independientes):" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n + 1; j++) {
            cin >> o1;
            mat.set_value(i, j, o1);
        }
    }
    
    vector<long double> x(n, 0.0);  // Inicializar el vector de soluciones
    vector<long double> x_prev(n, 0.0);  // Para almacenar la solución previa y calcular errores

    for (int it = 0; it < max_it; it++) {
        for (int i = 0; i < n; i++) {
            long double sum = 0.0;
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    sum += mat.get_value(i, j) * x[j];
                }
            }
            x[i] = (mat.get_value(i, n) - sum) / mat.get_value(i, i);
        }
        
        // Verificación de la convergencia
        error = 0.0;
        for (int i = 0; i < n; i++) {
            error += std::abs(x[i] - x_prev[i]);
            x_prev[i] = x[i];  // Actualiza x_prev para la siguiente iteración
        }
        
        if (error < tolerancia) {
            cout << "Convergencia alcanzada en " << it + 1 << " iteraciones." << endl;
            break;
        }
    }
    
    if (error >= tolerancia) {
        cout << "El método no convergió en " << max_it << " iteraciones." << endl;
    }

    // Imprimir soluciones con máxima precisión
    cout << fixed << setprecision(10);
    cout << "Soluciones:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "x[" << i << "] = " << x[i] << endl;
    }

    return 0;
}