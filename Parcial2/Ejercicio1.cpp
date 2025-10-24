#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
#include <cmath>
#include <limits>
using namespace std;

const int maxSize = 1024;
const int umbral = 64;

int A[maxSize][maxSize], B[maxSize][maxSize], CBase[maxSize][maxSize], C_ikj[maxSize][maxSize];
int** C_strassen = nullptr;

int generarRandom() {
    static random_device rd;
    static mt19937 mt(rd());
    uniform_int_distribution<int> dist(1, 50);
    return dist(mt);
}

int** sum_mat(int** A, int** B, int size) {
    int** C = new int*[size];
    for (int i = 0; i < size; i++) {
        C[i] = new int[size];
        for (int j = 0; j < size; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

int** sub_mat(int** A, int** B, int size) {
    int** C = new int*[size];
    for (int i = 0; i < size; i++) {
        C[i] = new int[size];
        for (int j = 0; j < size; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

int** mat_din(int size) {
    int** mat = new int*[size];
    for (int i = 0; i < size; i++) {
        mat[i] = new int[size];
    }
    return mat;
}

void eliminar_mat(int** mat, int size) {
    for (int i = 0; i < size; i++) {
        delete[] mat[i];
    }
    delete[] mat;
}

int** copiar_mat(int** inicial, int** destino, int row_start, int col_start, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            destino[i][j] = inicial[row_start + i][col_start + j];
        }
    }
    return destino;
}

int** reintegrar_mat(int** submat, int** mat, int row_start, int col_start, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            mat[row_start + i][col_start + j] = submat[i][j];
        }
    }
    return mat; 
}

int** strassen(int** A, int** B, int size) {
    // Caso base: si el tamaño es menor o igual al umbral, usar multiplicacion clasica
    if (size <= umbral) {
        int** C = mat_din(size);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                C[i][j] = A[i][0] * B[0][j];
                for (int k = 1; k < size; k++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        return C;
    }

    // Dividir las matrices en 4 cuadrantes
    int newSize = size / 2;
    int** A11 = mat_din(newSize); 
    int** A12 = mat_din(newSize);
    int** A21 = mat_din(newSize); 
    int** A22 = mat_din(newSize);
    int** B11 = mat_din(newSize); 
    int** B12 = mat_din(newSize);
    int** B21 = mat_din(newSize); 
    int** B22 = mat_din(newSize);

    // Usar copiar_mat para dividir las matrices A y B
    copiar_mat(A, A11, 0, 0, newSize);
    copiar_mat(A, A12, 0, newSize, newSize);
    copiar_mat(A, A21, newSize, 0, newSize);
    copiar_mat(A, A22, newSize, newSize, newSize);
    
    copiar_mat(B, B11, 0, 0, newSize);
    copiar_mat(B, B12, 0, newSize, newSize);
    copiar_mat(B, B21, newSize, 0, newSize);
    copiar_mat(B, B22, newSize, newSize, newSize);

    // Calcular las 7 multiplicaciones de Strassen
    // M1 = (A11 + A22) * (B11 + B22)
    int** temp1 = sum_mat(A11, A22, newSize);
    int** temp2 = sum_mat(B11, B22, newSize);
    int** M1 = strassen(temp1, temp2, newSize);
    eliminar_mat(temp1, newSize);
    eliminar_mat(temp2, newSize);
    
    // M2 = (A21 + A22) * B11
    temp1 = sum_mat(A21, A22, newSize);
    int** M2 = strassen(temp1, B11, newSize);
    eliminar_mat(temp1, newSize);
    
    // M3 = A11 * (B12 - B22)
    temp1 = sub_mat(B12, B22, newSize);
    int** M3 = strassen(A11, temp1, newSize);
    eliminar_mat(temp1, newSize);
    
    // M4 = A22 * (B21 - B11)
    temp1 = sub_mat(B21, B11, newSize);
    int** M4 = strassen(A22, temp1, newSize);
    eliminar_mat(temp1, newSize);
    
    // M5 = (A11 + A12) * B22
    temp1 = sum_mat(A11, A12, newSize);
    int** M5 = strassen(temp1, B22, newSize);
    eliminar_mat(temp1, newSize);
    
    // M6 = (A21 - A11) * (B11 + B12)
    temp1 = sub_mat(A21, A11, newSize);
    temp2 = sum_mat(B11, B12, newSize);
    int** M6 = strassen(temp1, temp2, newSize);
    eliminar_mat(temp1, newSize);
    eliminar_mat(temp2, newSize);
    
    // M7 = (A12 - A22) * (B21 + B22)
    temp1 = sub_mat(A12, A22, newSize);
    temp2 = sum_mat(B21, B22, newSize);
    int** M7 = strassen(temp1, temp2, newSize);
    eliminar_mat(temp1, newSize);
    eliminar_mat(temp2, newSize);

    // Calcular los cuadrantes del resultado usando las formulas de Strassen
    // C11 = M1 + M4 - M5 + M7
    temp1 = sum_mat(M1, M4, newSize);
    temp2 = sub_mat(temp1, M5, newSize);
    int** C11 = sum_mat(temp2, M7, newSize);
    eliminar_mat(temp1, newSize);
    eliminar_mat(temp2, newSize);
    
    // C12 = M3 + M5
    int** C12 = sum_mat(M3, M5, newSize);
    // C21 = M2 + M4
    int** C21 = sum_mat(M2, M4, newSize);
    
    // C22 = M1 + M3 - M2 + M6
    temp1 = sum_mat(M1, M3, newSize);
    temp2 = sub_mat(temp1, M2, newSize);
    int** C22 = sum_mat(temp2, M6, newSize);
    eliminar_mat(temp1, newSize);
    eliminar_mat(temp2, newSize);

    // Crear matriz resultado y usar reintegrar_mat para combinar los cuadrantes
    int** C = mat_din(size);
    reintegrar_mat(C11, C, 0, 0, newSize);
    reintegrar_mat(C12, C, 0, newSize, newSize);
    reintegrar_mat(C21, C, newSize, 0, newSize);
    reintegrar_mat(C22, C, newSize, newSize, newSize);

    // Liberar memoria usando eliminar_mat
    eliminar_mat(A11, newSize); eliminar_mat(A12, newSize); eliminar_mat(A21, newSize); eliminar_mat(A22, newSize);
    eliminar_mat(B11, newSize); eliminar_mat(B12, newSize); eliminar_mat(B21, newSize); eliminar_mat(B22, newSize);
    eliminar_mat(M1, newSize); eliminar_mat(M2, newSize); eliminar_mat(M3, newSize); eliminar_mat(M4, newSize);
    eliminar_mat(M5, newSize); eliminar_mat(M6, newSize); eliminar_mat(M7, newSize);
    eliminar_mat(C11, newSize); eliminar_mat(C12, newSize); eliminar_mat(C21, newSize); eliminar_mat(C22, newSize);

    return C;
}

void matmul_base(int A[maxSize][maxSize], int B[maxSize][maxSize], int C[maxSize][maxSize], int m, int p, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][0] * B[0][j];
            for (int k = 1; k < p; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void matmul_ikj(int A[maxSize][maxSize], int B[maxSize][maxSize], int C[maxSize][maxSize], int m, int p, int n) {
    // Inicializar la primera iteración sin suma
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][0] * B[0][j];
        }
    }
    // Continuar con las iteraciones restantes
    for (int i = 0; i < m; i++) {
        for (int k = 1; k < p; k++) {
            for (int j = 0; j < n; j++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main(){
    int m, p, n;
    while (true) {          
        try {
            cout << "ingrese el numero de filas de A (m): ";
            cin >> m;
            if (cin.fail()) throw runtime_error("debe ingresar un numero entero.");
            cout << "ingrese el numero de columnas de A / filas de B (p): ";
            cin >> p;
            if (cin.fail()) throw runtime_error("debe ingresar un numero entero.");
            cout << "ingrese el numero de columnas de B (n): ";
            cin >> n;
            if (cin.fail()) throw runtime_error("debe ingresar un numero entero.");

            if (m <=0 || m > maxSize || p <= 0 || p > maxSize || n <= 0 || n > maxSize) {
                cout << "error: El numero de filas y columnas debe estar entre 1 y " << maxSize << "." << endl;
                continue;
            }
            break; 
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    //Llenar matrices A y B con  numeros random
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            A[i][j] = generarRandom();
        }
    }

    for (int i = 0; i < p; i++) {
        for (int j = 0; j < n; j++) {
            B[i][j] = generarRandom();
        }
    }
    
    cout << "\n multiplicacion de matrices" << endl;
    cout << "Matrices: A(" << m << "x" << p << ") * B(" << p << "x" << n << ")" << endl;
    
    // Algoritmo base (ijk)
    auto startBase = chrono::high_resolution_clock::now();
    matmul_base(A, B, CBase, m, p, n);
    auto endBase = chrono::high_resolution_clock::now();
    chrono::duration<double> durationBase = endBase - startBase;
    cout << "\nTiempo algoritmo base (ijk): " << durationBase.count() << " segundos" << endl;

    // Algoritmo optimizado (ikj)
    // El orden ikj es mas eficiente que ijk debido a mejor localidad de cache
    // en el almacenamiento row-major de C++
    auto startIkj = chrono::high_resolution_clock::now();
    matmul_ikj(A, B, C_ikj, m, p, n);
    auto endIkj = chrono::high_resolution_clock::now();
    chrono::duration<double> durationIkj = endIkj - startIkj;
    cout << "Tiempo algoritmo ikj:       " << durationIkj.count() << " segundos" << endl;

    // Algoritmo de Strassen (solo para matrices cuadradas)
    if (m == n && n == p && m <= maxSize) {
        int** A_dyn = mat_din(m);
        int** B_dyn = mat_din(m);

        // Copiar datos de A y B (arreglos estáticos) a A_dyn y B_dyn (dinámicos)
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                A_dyn[i][j] = A[i][j];
                B_dyn[i][j] = B[i][j];
            }
        }

        auto startStrassen = chrono::high_resolution_clock::now();
        C_strassen = strassen(A_dyn, B_dyn, m);
        auto endStrassen = chrono::high_resolution_clock::now();
        chrono::duration<double> durationStrassen = endStrassen - startStrassen;
        cout << "Tiempo algoritmo Strassen:  " << durationStrassen.count() << " segundos" << endl;

        eliminar_mat(A_dyn, m);
        eliminar_mat(B_dyn, m);

        bool iguales = true;

        for (int f = 0; f < m; f++){
            for (int c = 0; c < n; c++){
                if (CBase[f][c] != C_strassen[f][c]) {
                    break;
                    iguales = false;
                }
            }
        }
        
        if (iguales) {
            cout << "El resultado de Strassen es correcto." << endl;
        } else {
            cout << "El resultado de Strassen es incorrecto." << endl;
        }

        cout << "\n comparacion de algoritmos" <<endl;
        cout << "El algoritmo ikj es " << durationBase.count() / durationIkj.count() << " veces mas rapido que el algoritmo base." << endl;
        cout << "El algoritmo Strassen es " << durationBase.count() / durationStrassen.count() << " veces mas rapido que el algoritmo base." << endl;
    } else {
        cout << "Algoritmo Strassen no se puede ejecutar, la matriz debe ser cuadrada" << endl;
    }

    eliminar_mat(C_strassen, m);
    
  return 0;
}