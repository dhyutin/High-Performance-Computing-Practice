#include <iostream>
#include <omp.h>
#include <chrono>
#include <random>

using namespace std;

long long N = 10000000;

int main() {
    omp_set_num_threads(9);

    long long *a = new long long[N];
    long long *b = new long long[N];

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 1000000);

    // Parallel initialization of arrays
    #pragma omp parallel for
    for (long long i = 0; i < N; i++) {
        a[i] = dist(gen);
        b[i] = dist(gen);
    }

    long long dot_product = 0;

    // Serial dot product
    auto start_serial = chrono::high_resolution_clock::now();
    for (long long i = 0; i < N; i++) {
        dot_product += a[i] * b[i];
    }
    auto end_serial = chrono::high_resolution_clock::now();
    double serial_time = chrono::duration<double>(end_serial - start_serial).count();

    // Reset dot_product for parallel computation
    dot_product = 0;

    // Parallel dot product computation
    auto start_parallel = chrono::high_resolution_clock::now();
    int threads = 0;

    // Keep the threads collection in a separate pragma omp paralle
    

    #pragma omp parallel
    {
        #pragma omp single
        threads = omp_get_num_threads();
    }

    #pragma omp parallel for reduction(+:dot_product)
    for (long long i = 0; i < N; i++) {
        dot_product += a[i] * b[i];
    }

    auto end_parallel = chrono::high_resolution_clock::now();
    double parallel_time = chrono::duration<double>(end_parallel - start_parallel).count();

    // Output results
    cout << "SERIAL" << endl;
    cout << "Time Taken: " << serial_time << " seconds" << endl;

    cout << "PARALLEL" << endl;
    cout << "Num Threads: " << threads << endl;
    cout << "Time Taken: " << parallel_time << " seconds" << endl;

    // Cleanup
    delete[] a;
    delete[] b;

    return 0;
}
