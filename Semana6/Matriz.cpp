//si hay mas filas que columnas (hay mas euaciones que incognitas), se trata de un problema de optimizacion
//si hay mas columnas que filas (hay mas incognitas que ecuaciones), se trata de un problema de soluciones infinitas (sin sloucion)
//si hay el mismo numero de filas que columnas, se trata de un problema de interpolacion (ecueaciones lineales)
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

void imprimirDiagonales_NW_SE(int matriz[100][100], int filas, int columnas){
    // Diagonales desde la esquina noroeste a la sureste
     for(int k = 0; k < filas + columnas - 1; k++){
        int startRow = max(0, k - columnas + 1);
        int endRow = min(filas - 1, k);
        for(int i = startRow; i <= endRow; i++){
            int j = k - i;
            if(j >= 0 && j < columnas){
                cout << matriz[i][j] << " ";
            }
        }
        cout << endl;
    }

/*    for (int d = -(columnas - 1); d <= filas - 1; d++)
    {
        int i = (d>0 ? d : 0);
        int j = (d>0 ? 0 : -d);
        for (; i < filas && j < columnas; i++, j++)
        {
            cout << matriz[i][j] << " ";
        }
        
    } */
}

void imprimirDiagonales_NE_SW(int matriz[100][100], int filas, int columnas){
    // Diagonales desde la esquina noreste a la suroeste
    for(int k = 0; k < filas + columnas - 2; k++){
        int startRow = max(0, k - columnas + 1);
        int endRow = min(filas - 1, k);
        for(int i = startRow; i <= endRow; i++){
            int j = (columnas - 1) - (k - i);
            if(j >= 0 && j < columnas){
                cout << matriz[i][j] << " ";
            }
        }
        cout << endl;
    }
}

void imprimirEspiral(int matriz[100][100], int filas, int columnas) {
    int total = filas * columnas;
    int count = 0;
    int top = 0, bottom = filas - 1;
    int left = 0, right = columnas - 1;

    while (count < total) {
        for (int j = left; j <= right && count < total; j++) {
            cout << matriz[top][j] << " ";
            count++;
        }
        top++;
        for (int i = top; i <= bottom && count < total; i++) {
            cout << matriz[i][right] << " ";
            count++;
        }
        right--;
        for (int j = right; j >= left && count < total; j--) {
            cout << matriz[bottom][j] << " ";
            count++;
        }
        bottom--;
        for (int i = bottom; i >= top && count < total; i--) {
            cout << matriz[i][left] << " ";
            count++;
        }
        left++;
    }
    cout << endl;

/*     int top = 0, bottom = filas - 1;
    int left = 0, right = columnas - 1;
    while (top <= bottom && left <= right)
    {
        for(int j = left; j <= right; j++){
            cout << matriz[top][j] << " ";
            top++;
        }
        for (int i = top; i <= bottom; i++){
            cout << matriz[i][right] << " ";
            right--;
        }
        if (top <= bottom) {
            for (int j = right; j >= left; j--){
                cout << matriz[bottom][j] << " ";
                bottom--;
            }
        }
        if (left <= right) {
            for (int i = bottom; i >= top; i--){
                cout << matriz[i][left] << " ";
                left++;
            }
        }
    } */
    
}

void busquedaLinear(int matriz[100][100], int filas, int columnas, int valor) {
   int* ri = NULL;
   int* rj = NULL;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (matriz[i][j] == valor) {
                *ri = i;
                *rj = j;
                cout << "Valor " << valor << " encontrado en la matriz en la posicion: (" << ri << ", " << rj << ")" << endl;
                return;
            }
        }
    }

    cout << "Valor " << valor << " no encontrado en la matriz." << endl;
}

/* int main() {
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
return 0;
} */