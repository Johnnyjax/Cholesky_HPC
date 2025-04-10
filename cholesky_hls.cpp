#include "cholesky_hls.h"
#include <math.h>

void cholesky(matrix_t A[N][N], matrix_t L[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            matrix_t sum = 0;
            for (int k = 0; k < j; k++) {
                sum += L[i][k] * L[j][k];
            }

            if (i == j) {
                L[i][j] = sqrt(A[i][i] - sum);
            } else {
                L[i][j] = (A[i][j] - sum) / L[j][j];
            }
        }
    }
}
