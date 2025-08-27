//si hay mas filas que columnas (hay mas euaciones que incognitas), se trata de un problema de optimizacion
//si hay mas columnas que filas (hay mas incognitas que ecuaciones), se trata de un problema de soluciones infinitas (sin sloucion)
//si hay el mismo numero de filas que columnas, se trata de un problema de interpolacion
#include <iostream>
#include <random>
#include <ctime>
#include <algorithm>
using namespace std;

int generarIntRandom(int min, int max){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}

void llenarMatriz(int matriz[100][100], int filas, int columnas){
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            matriz[i][j] = generarIntRandom(1, 200);
        }
    }
}

void imprimirMatrizPorFila(int matriz[100][100], int filas, int columnas){
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            cout << matriz[i][j] << " "; // Accede al elemento en la fila i y columna j
        }
        cout << endl; // Mejor presentación
    }
}

void imprimirMatrizPorColumna(int matriz[100][100], int filas, int columnas){
    for(int j = 0; j < columnas; j++){
        for(int i = 0; i < filas; i++){
            cout << matriz[i][j] << " "; // Accede al elemento en la fila i y columna j
        }
        cout << endl;
    }
}

void imprimirDiagonalPrincipal(int matriz[100][100], int filas, int columnas){
    int minDimension = min(filas, columnas);
    for(int i = 0; i < minDimension; i++){
        cout << matriz[i][i] << " "; // Accede al elemento en la fila i y columna i
    }
    cout << endl;
}

void busquedaLinear(int matriz[100][100], int filas, int columnas, int valor) {
   int ri = NULL;
   int rj = NULL;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (matriz[i][j] == valor) {
                ri = i;
                rj = j;
                cout << "Valor " << valor << " encontrado en la matriz en la posicion: (" << ri << ", " << rj << ")" << endl;
                return;
            }
        }
    }

    cout << "Valor " << valor << " no encontrado en la matriz." << endl;
}

int main() {
    int filas, columnas;
    cout << "Ingrese el numero de filas (max 100): ";
    cin >> filas;
    cout << "Ingrese el numero de columnas (max 100): ";
    cin >> columnas;

int a[100][100]; // Tamaño fijo en ambas dimensiones
llenarMatriz(a, filas, columnas);

cout << "Matriz por fila: " << endl;
clock_t start = clock();
imprimirMatrizPorFila(a, filas, columnas);
clock_t end = clock();
cout << "\nTiempo de ejecucion: " << double(end - start) / CLOCKS_PER_SEC << " segundos" << endl;

cout << "Matriz por columna: " << endl;
clock_t startClumn = clock();
imprimirMatrizPorColumna(a, filas, columnas);
clock_t endColumn = clock();
cout << "\nTiempo de ejecucion: " << double(endColumn - startClumn) / CLOCKS_PER_SEC << " segundos" << endl;

cout << "Diagonal principal: " << endl;
clock_t startDiagonal = clock();
imprimirDiagonalPrincipal(a, filas, columnas);
clock_t endDiagonal = clock();
cout << "\nTiempo de ejecucion: " << double(endDiagonal - startDiagonal) / CLOCKS_PER_SEC << " segundos" << endl;
return 0;
}