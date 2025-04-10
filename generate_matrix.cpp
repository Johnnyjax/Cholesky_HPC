#include <iostream>
#include <vector>
#include <fstream>
#include <random>

#define N 4
typedef double matrix_t;

using namespace std;

void generateSPDMatrix(matrix_t A[N][N]) {
    matrix_t M[N][N];
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(1.0, 5.0);

    // Fill M with random values
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            M[i][j] = dis(gen);

    // A = M * Mᵗ to ensure SPD
    for (int i = 0; i < N; ++i)
        for (int j = 0; j <= i; ++j) {
            A[i][j] = 0;
            for (int k = 0; k < N; ++k)
                A[i][j] += M[i][k] * M[j][k];
            A[j][i] = A[i][j];  // symmetric
        }
}

int main() {
    matrix_t A[N][N];
    generateSPDMatrix(A);

    ofstream fout("matrix_input.bin", ios::binary);
    for (int i = 0; i < N; ++i)
        fout.write(reinterpret_cast<char*>(A[i]), sizeof(matrix_t) * N);
    fout.close();

    cout << "matrix_input.bin written with SPD matrix." << endl;
    return 0;
}
