#include "cholesky_hls.h"
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int main() {
    matrix_t A[N][N];
    matrix_t L[N][N] = {0};
    matrix_t Ar[N][N] = {0};  // Reconstructed matrix

    // Read binary input
    FILE *fp = fopen("C:\\Users\\jonny\\Documents\\Books\\School_Books\\EECS_700_Algorithms_for_HPC\\Cholesky\\matrix_input.bin", "rb");
    if (!fp) {
        cerr << "Failed to open matrix_input.bin\n";
        return 1;
    }

    for (int i = 0; i < N; i++) {
        fread(A[i], sizeof(matrix_t), N, fp);
    }
    fclose(fp);

    // Run HLS version
    cholesky(A, L);

    // Reconstruct A = L * Lᵗ
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            for (int k = 0; k < N; ++k)
                Ar[i][j] += (j >= k && i >= k) ? L[i][k] * L[j][k] : 0;

    // Print original A
    cout << "Input A matrix:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << A[i][j] << "\t";
        cout << endl;
    }

    // Print L
    cout << "L matrix:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << L[i][j] << "\t";
        cout << endl;
    }

    // Print A reconstructed
    cout << "Reconstructed A (L * L-Transpose):\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << Ar[i][j] << "\t";
        cout << endl;
    }

    // Compare original A with Ar
    double error = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            error += fabs(A[i][j] - Ar[i][j]);

    if (error > 1e-4) {
        cout << "Test failed. Error = " << error << endl;
        return 1;
    }

    cout << "Test passed. Error = " << error << endl;
    return 0;
}
