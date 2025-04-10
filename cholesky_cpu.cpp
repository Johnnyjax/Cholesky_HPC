#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <random>
#include <chrono>
#include <fstream>
#include <x86intrin.h>  // For __rdtsc()

using namespace std;
using namespace std::chrono;

// Function to generate a symmetric positive definite matrix
void generateSPDMatrix(vector<vector<double>>& A, int n) {
    vector<vector<double>> M(n, vector<double>(n));
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(1.0, 10.0);  // Avoid zeros

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            M[i][j] = dis(gen);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j <= i; ++j) {
            A[i][j] = 0;
            for (int k = 0; k < n; ++k)
                A[i][j] += M[i][k] * M[j][k];
            A[j][i] = A[i][j];  // Symmetric
        }
}

// Cholesky decomposition
bool choleskyDecomposition(const vector<vector<double>>& A, vector<vector<double>>& L, int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j <= i; ++j) {
            double sum = 0;
            for (int k = 0; k < j; ++k)
                sum += L[i][k] * L[j][k];

            if (i == j) {
                double val = A[i][i] - sum;
                if (val <= 0) return false;
                L[i][j] = sqrt(val);
            } else {
                L[i][j] = (A[i][j] - sum) / L[j][j];
            }
        }
    return true;
}

int getRepeats(int n) {
    if (n <= 16) return 10000;
    else if (n <= 128) return 1000;
    else return 100;
}

int main() {
    vector<int> sizes = {2, 4, 8, 16, 32, 64, 128, 256, 512};

    ofstream out("cholesky_cpu_timing.csv");
    out << "N,Avg Time (us),Avg Cycles" << endl;

    for (int n : sizes) {
        vector<vector<double>> A(n, vector<double>(n));
        generateSPDMatrix(A, n);

        int repeats = getRepeats(n);
        vector<double> durations;
        vector<unsigned long long> cycles;

        for (int i = 0; i < repeats; ++i) {
            vector<vector<double>> L(n, vector<double>(n, 0));

            unsigned long long start_cycles = __rdtsc();
            auto start_time = high_resolution_clock::now();

            choleskyDecomposition(A, L, n);

            auto end_time = high_resolution_clock::now();
            unsigned long long end_cycles = __rdtsc();

            durations.push_back(duration_cast<duration<double, micro>>(end_time - start_time).count());
            cycles.push_back(end_cycles - start_cycles);
        }

        double avg_time = accumulate(durations.begin(), durations.end(), 0.0) / durations.size();
        double avg_cycles = accumulate(cycles.begin(), cycles.end(), 0ull) / static_cast<double>(cycles.size());

        out << n << "," << fixed << setprecision(4) << avg_time << "," << fixed << setprecision(0) << avg_cycles << endl;
        cout << "N=" << n << ", Avg Time: " << avg_time << " us, Avg Cycles: " << avg_cycles << endl;
    }

    out.close();
    cout << "Timing results written to cholesky_cpu_timing.csv\n";
    return 0;
}
