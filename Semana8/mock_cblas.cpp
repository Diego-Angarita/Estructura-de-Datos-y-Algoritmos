#include "mock_cblas.h"
#include <cmath>
#include <cstring>

extern "C" {
    // Mock DGEMV: y = alpha*A*x + beta*y
    void cblas_dgemv(const CBLAS_LAYOUT Layout,
                     const CBLAS_TRANSPOSE TransA, const int M, const int N,
                     const double alpha, const double *A, const int lda,
                     const double *X, const int incX, const double beta,
                     double *Y, const int incY) {
        
        // Simple implementation - not optimized
        if (Layout == CblasRowMajor && TransA == CblasNoTrans) {
            for (int i = 0; i < M; i++) {
                double sum = 0.0;
                for (int j = 0; j < N; j++) {
                    sum += A[i * lda + j] * X[j * incX];
                }
                Y[i * incY] = alpha * sum + beta * Y[i * incY];
            }
        }
    }

    // Mock DGEMM: C = alpha*A*B + beta*C
    void cblas_dgemm(const CBLAS_LAYOUT Layout, const CBLAS_TRANSPOSE TransA,
                     const CBLAS_TRANSPOSE TransB, const int M, const int N,
                     const int K, const double alpha, const double *A,
                     const int lda, const double *B, const int ldb,
                     const double beta, double *C, const int ldc) {
        
        // Simple implementation - not optimized
        if (Layout == CblasRowMajor && TransA == CblasNoTrans && TransB == CblasNoTrans) {
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    double sum = 0.0;
                    for (int k = 0; k < K; k++) {
                        sum += A[i * lda + k] * B[k * ldb + j];
                    }
                    C[i * ldc + j] = alpha * sum + beta * C[i * ldc + j];
                }
            }
        }
    }

    // Mock DDOT: dot product
    double cblas_ddot(const int N, const double *X, const int incX,
                      const double *Y, const int incY) {
        double result = 0.0;
        for (int i = 0; i < N; i++) {
            result += X[i * incX] * Y[i * incY];
        }
        return result;
    }

    // Mock DNRM2: Euclidean norm
    double cblas_dnrm2(const int N, const double *X, const int incX) {
        double sum = 0.0;
        for (int i = 0; i < N; i++) {
            double val = X[i * incX];
            sum += val * val;
        }
        return sqrt(sum);
    }

    // Mock OpenBLAS info functions
    char* openblas_get_config() {
        static char config[] = "Mock BLAS v1.0 (Educational purposes only)";
        return config;
    }

    int openblas_get_num_threads() {
        return 1; // Mock: single thread
    }

    int openblas_get_num_procs() {
        return 1; // Mock: single processor
    }
}
