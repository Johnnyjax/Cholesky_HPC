#ifndef CHOLESKY_HLS_H
#define CHOLESKY_HLS_H

#define N 512 // Change as needed (keep small for cosim)

typedef double matrix_t;

void cholesky(matrix_t A[N][N], matrix_t L[N][N]);

#endif
