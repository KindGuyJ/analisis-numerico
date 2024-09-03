#include "clase.h"

using namespace std;

#define tolerancia 1e-3
#define max_it 30

vector<long double> triang(matrix mat, int n);
vector<long double> seidel(matrix mat, int n);
vector<long double> lalu(matrix mat, int n);
void comparar(const vector<long double> &v1, const vector<long double> &v2);
void printv(const vector<long double> &vec);
bool verificar(const vector<long double> &vec, const matrix &mat);

int main()
{
    int n;
    long double o1;

    cout << "Cantidad de variables: ";
    cin >> n;

    matrix mat(n);

    // Ingresando la matriz
    cout << "Ingresar matriz por filas (coeficientes y términos independientes):" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n + 1; j++)
        {
            cin >> o1;
            mat.set_value(i, j, o1);
        }
    }
    cout << endl;
    mat.print();
    cout << endl;

    vector<long double> x1, x2, x3;
    x1 = triang(mat, n);
    x2 = seidel(mat, n);
    x3 = lalu(mat, n);

    cout << "Solucion via triangulacion:\n";
    printv(x1);

    cout << "Solucion via Gauss-Seidel:\n";
    printv(x2);

    cout << "Solucion via La Lu:\n";
    printv(x3);

    cout << "\nComparacion de sol. triangulacion con Gauss-Seidel" << endl;
    comparar(x1, x2);

    cout << "\nComparacion de sol. triangulacion con La Lu" << endl;
    comparar(x1, x3);

    cout << "\nComparacion de sol. Gauss-Seidel con La Lu" << endl;
    comparar(x2, x3);

    if (verificar(x1, mat))
    {
        cout << "\nEl metodo de triangulacion verifica el resultado con diferencia <= tolerancia\n";
    }
    if (verificar(x2, mat))
    {
        cout << "El metodo de Gauss-Seidel verifica el resultado con diferencia <= tolerancia\n";
    }
    if (verificar(x3, mat))
    {
        cout << "El metodo de La Lu verifica el resultado con diferencia <= tolerancia\n";
    }
}

bool verificar(const vector<long double> &vec, const matrix &mat)
{
    int n = vec.size();
    vector<long double> result(n, 0.0);

    for (int i = 0; i < n; ++i)
    {
        long double sum = 0.0;
        for (int j = 0; j < n; ++j)
        {
            sum += mat.get_value(i, j) * vec[j];
        }
        if ((abs(sum) - mat.get_value(i, n)) > tolerancia)
        {
            return false;
        };
    }
    return true;
}

vector<long double> triang(matrix mat, int n)
{
    long double o1, o2;
    for (int i = 0; i < n; i++)
    {
        o1 = mat.get_value(i, i);
        for (int j = i + 1; j < n; j++)
        {
            if (mat.get_value(j, i) != 0 && abs(mat.get_value(j, i)) > tolerancia)
            {
                o2 = mat.get_value(j, i) / o1;
                for (int k = 0; k < n + 1; k++)
                {
                    mat.set_value(j, k, mat.get_value(j, k) - (mat.get_value(i, k) * o2));
                }
            }
        }
    }
    cout << fixed << setprecision(2); // Ajustar la precisión aquí
    mat.print();

    // Sustitución hacia atrás
    vector<long double> x(n);
    x[n - 1] = mat.get_value(n - 1, n) / mat.get_value(n - 1, n - 1);

    for (int i = n - 2; i >= 0; i--)
    {
        long double sum = 0;
        for (int j = i + 1; j < n; j++)
        {
            sum += mat.get_value(i, j) * x[j];
        }
        x[i] = (mat.get_value(i, n) - sum) / mat.get_value(i, i);
    }

    return x;
}

vector<long double> seidel(matrix mat, int n)
{
    long double error;
    vector<long double> x(n, 0.0);      // Inicializar el vector de soluciones
    vector<long double> x_prev(n, 0.0); // Para almacenar la solución previa y calcular errores

    for (int it = 0; it < max_it; it++)
    {
        for (int i = 0; i < n; i++)
        {
            long double sum = 0.0;
            for (int j = 0; j < n; j++)
            {
                if (j != i)
                {
                    sum += mat.get_value(i, j) * x[j];
                }
            }
            x[i] = (mat.get_value(i, n) - sum) / mat.get_value(i, i);
        }

        // Verificación de la convergencia
        error = 0.0;
        for (int i = 0; i < n; i++)
        {
            error += std::abs(x[i] - x_prev[i]);
            x_prev[i] = x[i]; // Actualiza x_prev para la siguiente iteración
        }

        if (error < tolerancia)
        {
            cout << "Convergencia alcanzada en " << it + 1 << " iteraciones (Gauss-Seidel).\n\n"
                 << endl;
            break;
        }
    }

    if (error >= tolerancia)
    {
        cout << "El método no convergió en " << max_it << " iteraciones (Gauss-Seidel).\n\n"
             << endl;
    }

    return x;
}

vector<long double> lalu(matrix mat, int n)
{

    matrix L(n); // Matriz L (triangular inferior)
    matrix U(n); // Matriz U (triangular superior)

    // Realizar la descomposición LU
    for (int i = 0; i < n; i++)
    {
        // Llenar la matriz U
        for (int k = i; k < n; k++)
        {
            long double sum = 0.0;
            for (int j = 0; j < i; j++)
            {
                sum += (L.get_value(i, j) * U.get_value(j, k));
            }
            U.set_value(i, k, mat.get_value(i, k) - sum);
        }

        // Llenar la matriz L
        for (int k = i; k < n; k++)
        {
            if (i == k)
            {
                L.set_value(i, i, 1.0); // Diagonal principal de L es 1
            }
            else
            {
                long double sum = 0.0;
                for (int j = 0; j < i; j++)
                {
                    sum += (L.get_value(k, j) * U.get_value(j, i));
                }
                L.set_value(k, i, (mat.get_value(k, i) - sum) / U.get_value(i, i));
            }
        }
    }
    // Extraer vector b (términos independientes)
    vector<long double> b(n);
    for (int i = 0; i < n; i++)
    {
        b[i] = mat.get_value(i, n);
    }
    // Resolver Ly = b
    vector<long double> y(n);

    for (int i = 0; i < n; i++)
    {
        long double sum = 0.0;
        for (int j = 0; j < i; j++)
        {
            sum += L.get_value(i, j) * y[j];
        }
        y[i] = (b[i] - sum);
    }
    // Resolver Ux = y
    vector<long double> x(n);

    for (int i = n - 1; i >= 0; i--)
    {
        long double sum = 0.0;
        for (int j = i + 1; j < n; j++)
        {
            sum += U.get_value(i, j) * x[j];
        }
        x[i] = (y[i] - sum) / U.get_value(i, i);
    }

    return x;
}

void printv(const vector<long double> &vec)
{
    cout << "[ ";
    for (long double val : vec)
    {
        cout << setprecision(10) << val << " ";
    }
    cout << "]" << endl;
}

void comparar(const vector<long double> &v1, const vector<long double> &v2)
{
    cout << "Indice\tVector 1\tVector 2\tDiferencia" << endl;

    for (int i = 0; i < v1.size(); ++i)
    {
        long double diff = fabs(v1[i] - v2[i]);
        cout << i << "\t" << setprecision(10) << v1[i] << "\t" << v2[i] << "\t" << diff << endl;
    }
}