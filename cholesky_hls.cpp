#include <hls_math.h>
#include <ap_int.h>
#include "cholesky_hls.h"

#define N 512
#define B 32
#define NB (N / B)

typedef float matrix_t;

void cholesky_block(matrix_t A[B][B]) {
#pragma HLS INLINE
    for (int i = 0; i < B; i++) {
        for (int j = 0; j <= i; j++) {
#pragma HLS PIPELINE II=1
            matrix_t sum = 0;
            for (int k = 0; k < j; k++) {
#pragma HLS UNROLL factor=4
                sum += A[i][k] * A[j][k];
            }
            if (i == j)
                A[i][j] = hls::sqrt(A[i][i] - sum);
            else
                A[i][j] = (A[i][j] - sum) / A[j][j];
        }
    }
}

void trsm_block(matrix_t Aik[B][B], matrix_t Akk[B][B]) {
#pragma HLS INLINE
    for (int i = 0; i < B; i++) {
        for (int j = 0; j < B; j++) {
#pragma HLS PIPELINE II=1
            matrix_t sum = 0;
            for (int k = 0; k < j; k++) {
#pragma HLS UNROLL factor=4
                sum += Aik[i][k] * Akk[j][k];
            }
            Aik[i][j] = (Aik[i][j] - sum) / Akk[j][j];
        }
    }
}

void syrk_block(matrix_t Aij[B][B], matrix_t Aik[B][B], matrix_t Ajk[B][B]) {
#pragma HLS INLINE
    for (int i = 0; i < B; i++) {
        for (int j = 0; j < B; j++) {
#pragma HLS PIPELINE II=1
            matrix_t sum = 0;
            for (int k = 0; k < B; k++) {
#pragma HLS UNROLL factor=4
                sum += Aik[i][k] * Ajk[j][k];
            }
            Aij[i][j] -= sum;
        }
    }
}

void blocked_cholesky(matrix_t A[NB][NB][B][B]) {
#pragma HLS INLINE off
#pragma HLS DATAFLOW

    for (int k = 0; k < NB; k++) {
        cholesky_block(A[k][k]);

        for (int i = k + 1; i < NB; i++) {
            trsm_block(A[i][k], A[k][k]);
        }

        for (int i = k + 1; i < NB; i++) {
            for (int j = k + 1; j <= i; j++) {
                syrk_block(A[i][j], A[i][k], A[j][k]);
            }
        }
    }
}

void top(matrix_t A[NB][NB][B][B]) {
#pragma HLS INTERFACE m_axi depth=N*N port=A offset=slave bundle=gmem
#pragma HLS INTERFACE s_axilite port=return bundle=control

    blocked_cholesky(A);
}
