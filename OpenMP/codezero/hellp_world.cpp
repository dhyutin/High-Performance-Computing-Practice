#include <iostream>
#include <omp.h>
#include <chrono>


#define N 100000000  // Large array size for noticeable time difference

using namespace std;

int main() {
    int* arr = new int[N];
    long long sum_parallel = 0, sum_serial = 0;

    // Initialize array with values
    for (int i = 0; i < N; i++) {
        arr[i] = i + 1; // Filling array with values 1 to N
    }

    // Serial computation
    auto start_serial = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        sum_serial += arr[i];
    }
    auto end_serial = chrono::high_resolution_clock::now();
    double time_serial = chrono::duration<double>(end_serial - start_serial).count();

    // Parallel computation
    auto start_parallel = chrono::high_resolution_clock::now();
    #pragma omp parallel for reduction(+:sum_parallel)
    for (int i = 0; i < N; i++) {
        sum_parallel += arr[i];
    }
    auto end_parallel = chrono::high_resolution_clock::now();
    double time_parallel = chrono::duration<double>(end_parallel - start_parallel).count();

    // Print results
    cout << "Serial Sum: " << sum_serial << " | Time: " << time_serial << " sec" << endl;
    cout << "Parallel Sum: " << sum_parallel << " | Time: " << time_parallel << " sec" << endl;

    delete[] arr;
    return 0;
}



//// /opt/homebrew/opt/llvm/bin/clang++ -Xpreprocessor -fopenmp -I/opt/homebrew/opt/llvm/include -L/opt/homebrew/opt/llvm/lib -lomp openmp_test.cpp -o openmp_test
