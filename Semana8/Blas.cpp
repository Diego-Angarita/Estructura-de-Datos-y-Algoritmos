#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip>

// Incluir OpenBLAS headers
extern "C" {
    #include "openblas/cblas.h"  // OpenBLAS real instalado con vcpkg
}

class OpenBLASDemo {
private:
    std::mt19937 gen;
    std::uniform_real_distribution<double> dis;

public:
    OpenBLASDemo() : gen(std::random_device{}()), dis(-10.0, 10.0) {}

    // Función para generar una matriz aleatoria
    void generateRandomMatrix(std::vector<double>& matrix, int rows, int cols) {
        matrix.resize(rows * cols);
        for (int i = 0; i < rows * cols; i++) {
            matrix[i] = dis(gen);
        }
    }

    // Función para imprimir una matriz
    void printMatrix(const std::vector<double>& matrix, int rows, int cols, const std::string& name) {
        std::cout << "\n" << name << " (" << rows << "x" << cols << "):" << std::endl;
        for (int i = 0; i < rows && i < 5; i++) { // Mostrar solo las primeras 5 filas
            for (int j = 0; j < cols && j < 5; j++) { // Mostrar solo las primeras 5 columnas
                std::cout << std::setw(10) << std::fixed << std::setprecision(3) 
                         << matrix[i * cols + j] << " ";
            }
            if (cols > 5) std::cout << "...";
            std::cout << std::endl;
        }
        if (rows > 5) std::cout << "..." << std::endl;
    }

    // Demostración de DGEMV (Matrix-Vector multiplication: y = alpha*A*x + beta*y)
    void demonstrateDGEMV() {
        std::cout << "\n=== DGEMV: Matrix-Vector Multiplication ===";
        
        const int M = 1000; // filas de A
        const int N = 800;  // columnas de A
        
        std::vector<double> A, x, y;
        
        // Generar datos aleatorios
        generateRandomMatrix(A, M, N);
        generateRandomMatrix(x, N, 1);
        generateRandomMatrix(y, M, 1);
        
        // Parámetros para DGEMV
        double alpha = 1.0;
        double beta = 0.0;
        
        // Medir tiempo
        auto start = std::chrono::high_resolution_clock::now();
        
        // Llamar a DGEMV: y = alpha*A*x + beta*y
        cblas_dgemv(CblasRowMajor,    // Layout de la matriz
                   CblasNoTrans,      // No transponer A
                   M, N,              // Dimensiones de A
                   alpha,             // Escalar alpha
                   A.data(), N,       // Matriz A y su leading dimension
                   x.data(), 1,       // Vector x y su incremento
                   beta,              // Escalar beta
                   y.data(), 1);      // Vector y y su incremento
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "\nDGEMV completado en " << duration.count() << " microsegundos";
        std::cout << "\nOperación: y = A * x (donde A es " << M << "x" << N << ")";
        
        // Mostrar resultados parciales
        printMatrix(A, M, N, "Matriz A (primeras 5x5)");
        printMatrix(x, std::min(N, 5), 1, "Vector x (primeros 5 elementos)");
        printMatrix(y, std::min(M, 5), 1, "Resultado y (primeros 5 elementos)");
    }

    // Demostración de DGEMM (Matrix-Matrix multiplication: C = alpha*A*B + beta*C)
    void demonstrateDGEMM() {
        std::cout << "\n\n=== DGEMM: Matrix-Matrix Multiplication ===";
        
        const int M = 500; // filas de A y C
        const int N = 400; // columnas de B y C
        const int K = 600; // columnas de A, filas de B
        
        std::vector<double> A, B, C;
        
        // Generar datos aleatorios
        generateRandomMatrix(A, M, K);
        generateRandomMatrix(B, K, N);
        generateRandomMatrix(C, M, N);
        
        // Parámetros para DGEMM
        double alpha = 1.0;
        double beta = 0.0;
        
        // Medir tiempo
        auto start = std::chrono::high_resolution_clock::now();
        
        // Llamar a DGEMM: C = alpha*A*B + beta*C
        cblas_dgemm(CblasRowMajor,    // Layout de las matrices
                   CblasNoTrans,      // No transponer A
                   CblasNoTrans,      // No transponer B
                   M, N, K,           // Dimensiones
                   alpha,             // Escalar alpha
                   A.data(), K,       // Matriz A y su leading dimension
                   B.data(), N,       // Matriz B y su leading dimension
                   beta,              // Escalar beta
                   C.data(), N);      // Matriz C y su leading dimension
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "\nDGEMM completado en " << duration.count() << " microsegundos";
        std::cout << "\nOperación: C = A * B (" << M << "x" << K << ") * (" << K << "x" << N << ") = (" << M << "x" << N << ")";
        
        // Mostrar resultados parciales
        printMatrix(A, M, K, "Matriz A (primeras 5x5)");
        printMatrix(B, K, N, "Matriz B (primeras 5x5)");
        printMatrix(C, M, N, "Resultado C (primeras 5x5)");
    }

    // Demostración de DDOT (Dot product: result = x^T * y)
    void demonstrateDDOT() {
        std::cout << "\n\n=== DDOT: Dot Product ===";
        
        const int N = 1000000; // Tamaño de los vectores
        
        std::vector<double> x, y;
        
        // Generar datos aleatorios
        generateRandomMatrix(x, N, 1);
        generateRandomMatrix(y, N, 1);
        
        // Medir tiempo
        auto start = std::chrono::high_resolution_clock::now();
        
        // Llamar a DDOT
        double result = cblas_ddot(N,           // Longitud de los vectores
                                  x.data(), 1,  // Vector x y su incremento
                                  y.data(), 1); // Vector y y su incremento
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "\nDDOT completado en " << duration.count() << " microsegundos";
        std::cout << "\nProducto punto de vectores de longitud " << N << ": " << result;
        
        // Mostrar algunos elementos de los vectores
        std::cout << "\nPrimeros 5 elementos de x: ";
        for (int i = 0; i < 5; i++) {
            std::cout << std::fixed << std::setprecision(3) << x[i] << " ";
        }
        std::cout << "\nPrimeros 5 elementos de y: ";
        for (int i = 0; i < 5; i++) {
            std::cout << std::fixed << std::setprecision(3) << y[i] << " ";
        }
    }

    // Demostración de DNRM2 (Euclidean norm: result = ||x||_2)
    void demonstrateDNRM2() {
        std::cout << "\n\n=== DNRM2: Euclidean Norm ===";
        
        const int N = 1000000;
        
        std::vector<double> x;
        generateRandomMatrix(x, N, 1);
        
        auto start = std::chrono::high_resolution_clock::now();
        
        double norm = cblas_dnrm2(N, x.data(), 1);
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "\nDNRM2 completado en " << duration.count() << " microsegundos";
        std::cout << "\nNorma euclidiana del vector de longitud " << N << ": " << norm;
    }

    // Función para mostrar información de OpenBLAS
    void showOpenBLASInfo() {
        std::cout << "\n=== Información de OpenBLAS ===";
        std::cout << "\nOpenBLAS versión: " << openblas_get_config();
        std::cout << "\nNúmero de threads: " << openblas_get_num_threads();
        std::cout << "\nNúmero de procesadores: " << openblas_get_num_procs();
    }

    // Ejecutar todas las demostraciones
    void runAllDemonstrations() {
        showOpenBLASInfo();
        demonstrateDDOT();
        demonstrateDNRM2();
        demonstrateDGEMV();
        demonstrateDGEMM();
    }
};

int main() {
    std::cout << "=================================" << std::endl;
    std::cout << "  DEMOSTRACIÓN DE OpenBLAS" << std::endl;
    std::cout << "=================================" << std::endl;
    
    try {
        OpenBLASDemo demo;
        demo.runAllDemonstrations();
        
        std::cout << "\n\n=== Resumen ===";
        std::cout << "\nEste programa demuestra el uso de OpenBLAS con operaciones:";
        std::cout << "\n1. DDOT  - Producto punto de vectores";
        std::cout << "\n2. DNRM2 - Norma euclidiana";
        std::cout << "\n3. DGEMV - Multiplicación matriz-vector";
        std::cout << "\n4. DGEMM - Multiplicación matriz-matriz";
        std::cout << "\n\nOpenBLAS proporciona implementaciones optimizadas";
        std::cout << "\nque aprovechan las capacidades del hardware.";
        std::cout << "\n\n¡Demostración completada exitosamente!\n";
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
