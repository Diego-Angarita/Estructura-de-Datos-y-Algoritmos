#ifndef MOCK_CBLAS_H
#define MOCK_CBLAS_H

// Mock implementation of CBLAS for demonstration purposes
// This is NOT optimized and is only for educational use

typedef enum {CblasRowMajor=101, CblasColMajor=102} CBLAS_LAYOUT;
typedef enum {CblasNoTrans=111, CblasTrans=112, CblasConjTrans=113} CBLAS_TRANSPOSE;

extern "C" {
    // Mock DGEMV: y = alpha*A*x + beta*y
    void cblas_dgemv(const CBLAS_LAYOUT Layout,
                     const CBLAS_TRANSPOSE TransA, const int M, const int N,
                     const double alpha, const double *A, const int lda,
                     const double *X, const int incX, const double beta,
                     double *Y, const int incY);

    // Mock DGEMM: C = alpha*A*B + beta*C
    void cblas_dgemm(const CBLAS_LAYOUT Layout, const CBLAS_TRANSPOSE TransA,
                     const CBLAS_TRANSPOSE TransB, const int M, const int N,
                     const int K, const double alpha, const double *A,
                     const int lda, const double *B, const int ldb,
                     const double beta, double *C, const int ldc);

    // Mock DDOT: dot product
    double cblas_ddot(const int N, const double *X, const int incX,
                      const double *Y, const int incY);

    // Mock DNRM2: Euclidean norm
    double cblas_dnrm2(const int N, const double *X, const int incX);

    // Mock OpenBLAS info functions
    char* openblas_get_config();
    int openblas_get_num_threads();
    int openblas_get_num_procs();
}

#endif // MOCK_CBLAS_H
