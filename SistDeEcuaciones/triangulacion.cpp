#include "clase.h"
using namespace std;

#define tolerancia 1e-6
#define max_it 1000


int main(){
    int n;
    long double o1,o2;
    cout<<"Cantidad de variables: ";
    cin>>n;

    matrix mat(n);

    //ingresando
    cout<<"Ingresar matriz por filas\n";
    for (int i=0;i<n;i++){
        for (int j = 0; j < n+1; j++)
        {
            cin>>o1;
            mat.set_value(i,j,o1);
        }
        
    }


    for (int i=0;i<n;i++){
        o1 = mat.get_value(i,i);
        for (int j = i+1; j < n; j++)
        {
            if (mat.get_value(j,i)!=0 && abs(mat.get_value(j, i)) > tolerancia){
                o2 = mat.get_value(j,i)/o1;
                for (int k=0; k<n+1;k++)
                {
                    mat.set_value(j,k,mat.get_value(j,k)-(mat.get_value(i,k)*o2));
                }
            }
        }
    }
    cout << fixed << setprecision(2);  // Ajustar la precisión aquí
    mat.print();

    // Sustitución hacia atrás
    vector<long double> x(n);
    x[n-1] = mat.get_value(n-1, n) / mat.get_value(n-1, n-1);

    for (int i = n - 2; i >= 0; i--) {
        long double sum = 0;
        for (int j = i + 1; j < n; j++) {
            sum += mat.get_value(i, j) * x[j];
        }
        x[i] = (mat.get_value(i, n) - sum) / mat.get_value(i, i);
    }

    // Imprimir soluciones
    cout << fixed << setprecision(10);  // Ajustar la precisión aquí
    cout << "Soluciones:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "x[" << i << "] = " << x[i] << endl;
    }

    return 0;
    
}