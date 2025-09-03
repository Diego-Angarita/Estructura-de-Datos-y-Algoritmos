#include<iostream>
#include<random>
#include<ctime>
#include<algorithm>
#include"c:/Users/diego/Estruc.Datos y Algoritmos/Estructura-de-Datos-y-Algoritmos/Semana6/Matriz.cpp"
using namespace std;

void productoMatrices(int A[100][100], int B[100][100], int C[100][100], int filasA, int columnasA, int filasB, int columnasB) {
    if (columnasA != filasB) {
        cout << "Error: El numero de columnas de A debe ser igual al numero de filas de B." << endl;
        return;
    }

    for (int i = 0; i < filasA; i++) {
        for (int j = 0; j < columnasB; j++) {
            C[i][j] = 0; // Inicializa el elemento C[i][j]
            for (int k = 0; k < columnasA; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

/* int main(){
    int filas, columnas;
    cout << "Ingrese el numero de filas (max 100): ";
    cin >> filas;
    cout << "Ingrese el numero de columnas (max 100): ";
    cin >> columnas;
    if (filas <= 0 || filas > 100 || columnas <= 0 || columnas > 100) {
        cout << "Error: El numero de filas y columnas debe estar entre 1 y 100." << endl;
        return 1;
    }

    int a[100][100]; // Tamaño fijo en ambas dimensiones
    llenarMatriz(a, filas, columnas);
    int b[100][100];
    llenarMatriz(b, filas, columnas);
    int c[100][100]; // Matriz resultado

    cout << "Matriz por fila: " << endl;
    clock_t startFila = clock();
    imprimirMatrizPorFila(a, filas, columnas);
    clock_t endFila = clock();
    cout << "\nTiempo de ejecucion: " << double(endFila - startFila) / CLOCKS_PER_SEC << " segundos" << endl;

    cout << "Matriz por columna: " << endl;
    clock_t startColumna = clock();
    imprimirMatrizPorColumna(a, filas, columnas);
    clock_t endColumna = clock();
    cout << "\nTiempo de ejecucion: " << double(endColumna - startColumna) / CLOCKS_PER_SEC << " segundos" << endl;

    cout << "Diagonal principal: " << endl;
    clock_t startDiagonal = clock();
    imprimirDiagonalPrincipal(a, filas, columnas);
    clock_t endDiagonal = clock();
    cout << "\nTiempo de ejecucion: " << double(endDiagonal - startDiagonal) / CLOCKS_PER_SEC << " segundos" << endl;

    cout << "Diagonales NW-SE: " << endl;
    clock_t startDiagonalNW_SE = clock();
    imprimirDiagonales_NW_SE(a, filas, columnas);
    clock_t endDiagonalNW_SE = clock();
    cout << "\nTiempo de ejecucion: " << double(endDiagonalNW_SE - startDiagonalNW_SE) / CLOCKS_PER_SEC << " segundos" << endl;

    cout << "Diagonales NE-SW: " << endl;
    clock_t startDiagonalNE_SW = clock();
    imprimirDiagonales_NE_SW(a, filas, columnas);
    clock_t endDiagonalNE_SW = clock();
    cout << "\nTiempo de ejecucion: " << double(endDiagonalNE_SW - startDiagonalNE_SW) / CLOCKS_PER_SEC << " segundos" << endl;

    cout << "Espiral: " << endl;
    clock_t startEspiral = clock();
    imprimirEspiral(a, filas, columnas);
    clock_t endEspiral = clock();
    cout << "\nTiempo de ejecucion: " << double(endEspiral - startEspiral) / CLOCKS_PER_SEC << " segundos" << endl;

    cout << "Producto de matrices: " << endl;
    clock_t startProducto = clock();
    productoMatrices(a, b, c, filas, columnas, filas, columnas);
    clock_t endProducto = clock();
    cout << "\nTiempo de ejecucion: " << double(endProducto - startProducto) / CLOCKS_PER_SEC << " segundos" << endl;
    imprimirMatrizPorFila(c, filas, columnas);
} */