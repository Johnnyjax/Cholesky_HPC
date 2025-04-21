#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <numeric>
#include <x86intrin.h>  // For __rdtsc()
#include <omp.h>        // OpenMP
#include <iomanip>      // <-- Fix for setprecision

using namespace std;
using namespace chrono;

#define IDX(i, j, n) ((i) * (n) + (j))

void generateSPDMatrix(vector<double>& A, int n) {
    vector<double> M(n * n);
    for (int i = 0; i < n * n; ++i) {
        M[i] = 1.0 + (rand() % 1000) / 100.0;
    }

    for (int i = 0; i < n; ++i)
        for (int j = 0; j <= i; ++j) {
            A[IDX(i,j,n)] = 0;
            for (int k = 0; k < n; ++k)
                A[IDX(i,j,n)] += M[IDX(i,k,n)] * M[IDX(j,k,n)];
            A[IDX(j,i,n)] = A[IDX(i,j,n)];
        }
}

bool choleskyDecompositionOpenMP(const vector<double>& A, vector<double>& L, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            double sum = 0;

            #pragma omp parallel for reduction(+:sum)
            for (int k = 0; k < j; ++k) {
                sum += L[IDX(i,k,n)] * L[IDX(j,k,n)];
            }

            if (i == j) {
                double val = A[IDX(i,i,n)] - sum;
                if (val <= 0) return false;
                L[IDX(i,j,n)] = sqrt(val);
            } else {
                L[IDX(i,j,n)] = (A[IDX(i,j,n)] - sum) / L[IDX(j,j,n)];
            }
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

    cout << "Size, Avg Time (us), Avg Cycles\n";

    for (int n : sizes) {
        int repeats = getRepeats(n);

        vector<double> durations_us;
        vector<unsigned long long> cycles;

        vector<double> A(n * n);
        generateSPDMatrix(A, n);

        for (int r = 0; r < repeats; ++r) {
            vector<double> L(n * n, 0.0);

            unsigned long long start_cycles = __rdtsc();
            auto start_time = high_resolution_clock::now();

            choleskyDecompositionOpenMP(A, L, n);

            auto end_time = high_resolution_clock::now();
            unsigned long long end_cycles = __rdtsc();

            auto elapsed_us = duration_cast<microseconds>(end_time - start_time).count();
            durations_us.push_back(static_cast<double>(elapsed_us));
            cycles.push_back(end_cycles - start_cycles);
        }

        double avg_time_us = accumulate(durations_us.begin(), durations_us.end(), 0.0) / durations_us.size();
        double avg_cycles = accumulate(cycles.begin(), cycles.end(), 0.0) / cycles.size();

        cout << n << ", " << fixed << setprecision(4) << avg_time_us << ", "
             << fixed << setprecision(0) << avg_cycles << "\n";
    }

    return 0;
}
