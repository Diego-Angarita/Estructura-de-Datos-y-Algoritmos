#include <iostream>
#include <ctime>
#include "c:/Users/diego/Estruc.Datos y Algoritmos/Estructura-de-Datos-y-Algoritmos/Semana7/OperacionesMatrices.cpp"
using namespace std;

void llenarVector(int vec[100], int n) {
    for (int i = 0; i < n; i++) {
        vec[i] = generarIntRandom(1, 200);
    }
}

void imprimirVector(int vec[100], int n) {
    for (int i = 0; i < n; i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
}

void matrizAMatrizAumentada(int A[100][100], int b[100], int Ab[100][101], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Ab[i][j] = A[i][j];
        }
        Ab[i][n] = b[i];
    }
}

void eliminacionGaussiana(int Ab[100][101], int n) {
    for (int k = 0; k < n; k++) {
        // Pivoteo parcial
        int maxIndex = k;
        for (int i = k + 1; i < n; i++) {
            if (abs(Ab[i][k]) > abs(Ab[maxIndex][k])) {
                maxIndex = i;
            }
        }
        if (maxIndex != k) {
            for (int j = k; j <= n; j++) {
                swap(Ab[k][j], Ab[maxIndex][j]);
            }
        }

        // Eliminacion
        for (int i = k + 1; i < n; i++) {
            if (Ab[k][k] == 0) continue; // Evitar division por cero
            double factor = static_cast<double>(Ab[i][k]) / Ab[k][k];
            for (int j = k; j <= n; j++) {
                Ab[i][j] -= factor * Ab[k][j];
            }
        }
    }
}

int sustitucionRegresiva(int Ab[100][101], int n, double x[100]) {
    for (int i = n - 1; i >= 0; i--) {
        if (Ab[i][i] == 0) {
            if (Ab[i][n] != 0) {
                cout << "El sistema no tiene solucion." << endl;
                return -1; // Sistema inconsistente
            } else {
                cout << "El sistema tiene infinitas soluciones." << endl;
                return 0; // Sistema indeterminado
            }
        }
        x[i] = Ab[i][n];
        for (int j = i + 1; j < n; j++) {
            x[i] -= Ab[i][j] * x[j];
        }
        x[i] /= Ab[i][i];
    }
    return 1; // Solucion unica
}

int sustitucionProgresiva(int Ab[100][101], int n, double x[100]) {
    for (int i = 0; i < n; i++) {
        if (Ab[i][i] == 0) {
            if (Ab[i][n] != 0) {
                cout << "El sistema no tiene solucion." << endl;
                return -1; // Sistema inconsistente
            } else {
                cout << "El sistema tiene infinitas soluciones." << endl;
                return 0; // Sistema indeterminado
            }
        }
        x[i] = Ab[i][n];
        for (int j = 0; j < i; j++) {
            x[i] -= Ab[i][j] * x[j];
        }
        x[i] /= Ab[i][i];
    }
    return 1; // Solucion unica
}

int main() {
    int n;
    cout << "Ingrese el tamano de la matriz cuadrada (max 100): ";
    cin >> n;
    if (n <= 0 || n > 100) {
        cout << "Error: El tamano debe estar entre 1 y 100." << endl;
        return 1;
    }

    int A[100][100]; // Matriz de coeficientes
    int b[100];      // Vector de terminos independientes

    llenarMatriz(A, n, n);
    llenarVector(b, n);

    cout << "Matriz A: " << endl;
    imprimirMatrizPorFila(A, n, n);
    cout << "Vector b: " << endl;
    imprimirVector(b, n);

    return 0;
}   