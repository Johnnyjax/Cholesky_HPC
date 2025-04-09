#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <random>
#include <chrono>

#define N 512  // Set matrix dimension here

using namespace std;
using namespace std::chrono;

// Generate a symmetric positive definite matrix
void generateSPDMatrix(vector<vector<double>>& A, int n) {
    vector<vector<double>> M(n, vector<double>(n));
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(1.0, 10.0);  // Avoid values too close to zero

    // Generate a random matrix M
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            M[i][j] = dis(gen);

    // Compute A = M * Mᵗ to ensure it's symmetric positive definite
    for (int i = 0; i < n; ++i)
        for (int j = 0; j <= i; ++j) {
            A[i][j] = 0;
            for (int k = 0; k < n; ++k)
                A[i][j] += M[i][k] * M[j][k];
            A[j][i] = A[i][j];  // Make symmetric
        }
}

bool choleskyDecomposition(const vector<vector<double>>& A, vector<vector<double>>& L, int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j <= i; ++j) {
            double sum = 0;
            for (int k = 0; k < j; ++k)
                sum += L[i][k] * L[j][k];

            if (i == j) {
                double val = A[i][i] - sum;
                if (val <= 0)
                    return false;
                L[i][j] = sqrt(val);
            } else {
                L[i][j] = (A[i][j] - sum) / L[j][j];
            }
        }
    return true;
}

int main() {
    int n = N;

    vector<vector<double>> A(n, vector<double>(n));
    vector<vector<double>> L(n, vector<double>(n, 0));

    cout << "Generating " << N << " x " << N << " SPD matrix...\n";
    generateSPDMatrix(A, n);

    cout << "Starting Cholesky decomposition...\n";
    auto start = high_resolution_clock::now();

    if (!choleskyDecomposition(A, L, n)) {
        cout << "Matrix is not positive definite.\n";
        return 1;
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);

    cout << "Cholesky decomposition completed in " << duration.count() << " ms.\n";

    return 0;
}
