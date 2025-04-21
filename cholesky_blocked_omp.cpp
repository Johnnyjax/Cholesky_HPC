#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <chrono>
#include <x86intrin.h>
#include <omp.h>
#include <fstream>     // <-- Add this
#include <iomanip>     // <-- And this

using namespace std;
using namespace std::chrono;

// const int B = 64;  // Block size
const int B = 32;  // Block size

void generateSPDMatrix(vector<vector<double>>& A, int N) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(1.0, 10.0);

    vector<vector<double>> M(N, vector<double>(N));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            M[i][j] = dis(gen);

    for (int i = 0; i < N; ++i)
        for (int j = 0; j <= i; ++j) {
            A[i][j] = 0;
            for (int k = 0; k < N; ++k)
                A[i][j] += M[i][k] * M[j][k];
            A[j][i] = A[i][j];
        }
}

// Direct pointer access to blocks
double* get_block(vector<double>& mat, int N, int bi, int bj) {
    return &mat[(bi * B * N) + (bj * B)];
}

// Basic blocked kernel: Cholesky on a BxB block
void cholesky_block(double* A, int N) {
    for (int i = 0; i < B; ++i) {
        for (int j = 0; j <= i; ++j) {
            double sum = 0.0;
            for (int k = 0; k < j; ++k)
                sum += A[i * N + k] * A[j * N + k];

            if (i == j) A[i * N + j] = sqrt(A[i * N + j] - sum);
            else A[i * N + j] = (A[i * N + j] - sum) / A[j * N + j];
        }
    }
}

// Triangular solve
void trsm_block(double* Aik, double* Akk, int N) {
    for (int i = 0; i < B; ++i) {
        for (int j = 0; j < B; ++j) {
            double sum = 0.0;
            for (int k = 0; k < j; ++k)
                sum += Aik[i * N + k] * Akk[j * N + k];
            Aik[i * N + j] = (Aik[i * N + j] - sum) / Akk[j * N + j];
        }
    }
}

// Symmetric rank-k update
void syrk_block(double* Aij, double* Aik, double* Ajk, int N) {
    for (int i = 0; i < B; ++i)
        for (int j = 0; j < B; ++j)
            for (int k = 0; k < B; ++k)
                Aij[i * N + j] -= Aik[i * N + k] * Ajk[j * N + k];
}

void blocked_cholesky(vector<double>& A, int N) {
    int nb = N / B;

    #pragma omp parallel
    #pragma omp single
    for (int k = 0; k < nb; ++k) {
        double* Akk = get_block(A, N, k, k);
        #pragma omp task depend(inout: Akk[0:B*B])
        cholesky_block(Akk, N);

        for (int i = k + 1; i < nb; ++i) {
            double* Aik = get_block(A, N, i, k);
            #pragma omp task depend(in: Akk[0:B*B]) depend(inout: Aik[0:B*B])
            trsm_block(Aik, Akk, N);
        }

        for (int i = k + 1; i < nb; ++i) {
            double* Aik = get_block(A, N, i, k);
            for (int j = k + 1; j <= i; ++j) {
                double* Ajk = get_block(A, N, j, k);
                double* Aij = get_block(A, N, i, j);
                #pragma omp task depend(in: Aik[0:B*B], Ajk[0:B*B]) depend(inout: Aij[0:B*B])
                syrk_block(Aij, Aik, Ajk, N);
            }
        }
    }
}

int main() {
    // vector<int> sizes = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
    vector<int> sizes = {64, 128, 256, 512, 1024};
    int thread_counts[] = {1, 2, 4};

    for (int t : thread_counts) {
        omp_set_num_threads(t);
        string filename = "blocked_cholesky_" + to_string(t) + "threads_" + to_string(B) + ".csv";
        ofstream out(filename);
        out << "N,Avg Time (us),Avg Cycles\n";

        for (int N : sizes) {
            if (N % B != 0) continue;

            // Generate SPD matrix
            vector<vector<double>> A2D(N, vector<double>(N));
            generateSPDMatrix(A2D, N);
            vector<double> A(N * N);
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    A[i * N + j] = A2D[i][j];

            // Time measurement
            int repeats = 3;
            vector<double> times;
            vector<unsigned long long> cycles;

            for (int r = 0; r < repeats; ++r) {
                vector<double> A_copy = A;

                unsigned long long start_cycles = __rdtsc();
                auto start = high_resolution_clock::now();

                blocked_cholesky(A_copy, N);

                auto end = high_resolution_clock::now();
                unsigned long long end_cycles = __rdtsc();

                double time_us = duration_cast<duration<double, micro>>(end - start).count();
                times.push_back(time_us);
                cycles.push_back(end_cycles - start_cycles);
            }

            double avg_time = accumulate(times.begin(), times.end(), 0.0) / times.size();
            double avg_cycles = accumulate(cycles.begin(), cycles.end(), 0ull) / static_cast<double>(cycles.size());

            out << N << "," << fixed << setprecision(4) << avg_time << "," << fixed << setprecision(0) << avg_cycles << endl;
            cout << "[Threads=" << t << "] N=" << N << ", Avg Time: " << avg_time << " us, Avg Cycles: " << avg_cycles << endl;
        }

        out.close();
        cout << "Timing results written to " << filename << "\n";
    }

    return 0;
}
