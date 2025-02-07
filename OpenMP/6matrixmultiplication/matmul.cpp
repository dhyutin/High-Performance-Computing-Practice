// code to do matrix multiplication and parallelize

#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>

using namespace std;

int main() {
    long long N = 1000;  

    
    vector<vector<long long>> A(N, vector<long long>(N, 1));  // A matrix initialized to 1s
    vector<vector<long long>> B(N, vector<long long>(N, 2));  // B matrix initialized to 2s
    vector<vector<long long>> C(N, vector<long long>(N, 0));  // Result matrix initialized to 0s

    // Serial
    auto start_time = chrono::high_resolution_clock::now();

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    auto end_time = chrono::high_resolution_clock::now();
    double time_s = chrono::duration<double>(end_time - start_time).count();


    // parallel

    start_time = chrono::high_resolution_clock::now();

    #pragma omp parallel for collapse(2) schedule(dynamic)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    end_time = chrono::high_resolution_clock::now();
    double time_p = chrono::duration<double>(end_time - start_time).count();


    // Output results
    cout << "SERIAL" << endl;
    cout << "Time Taken: " << time_s << " seconds" << endl;

    cout << "PARALLEL" << endl;
    cout << "Time Taken: " << time_p<< " seconds" << endl;

    return 0;
}
