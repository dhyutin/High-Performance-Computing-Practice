#include <iostream>
#include <omp.h>
#include <chrono>

using namespace std;

int main() {
    omp_set_num_threads(10); // Set number of threads

    long long N = 100000000; // Large number of increments
    long long c = 0;

    // Serial Execution
    auto start_s = chrono::high_resolution_clock::now();
    for (long long i = 0; i < N; i++) {
        c++;
    }
    auto end_s = chrono::high_resolution_clock::now();
    double serial_time = chrono::duration<double>(end_s - start_s).count();

    cout << "SERIAL Execution Time: " << serial_time << " seconds" << endl;

    // Parallel using atomic
    c = 0;
    auto start_atomic = chrono::high_resolution_clock::now();
    #pragma omp parallel
    {
        #pragma omp for
        for (long long i = 0; i < N; i++) {
            #pragma omp atomic
            c++;
        }
    }
    auto end_atomic = chrono::high_resolution_clock::now();
    double atomic_time = chrono::duration<double>(end_atomic - start_atomic).count();

    cout << "ATOMIC Execution Time: " << atomic_time << " seconds" << endl;

    // Parallel using critical
    c = 0;
    auto start_critical = chrono::high_resolution_clock::now();
    #pragma omp parallel
    {
        #pragma omp for
        for (long long i = 0; i < N; i++) {
            #pragma omp critical
            c++;
        }
    }
    auto end_critical = chrono::high_resolution_clock::now();
    double critical_time = chrono::duration<double>(end_critical - start_critical).count();

    cout << "CRITICAL Execution Time: " << critical_time << " seconds" << endl;

    // Parallel using reduction
    c = 0;
    auto start_reduction = chrono::high_resolution_clock::now();
    #pragma omp parallel for reduction(+:c)
    for (long long i = 0; i < N; i++) {
        c++;
    }
    auto end_reduction = chrono::high_resolution_clock::now();
    double reduction_time = chrono::duration<double>(end_reduction - start_reduction).count();

    cout << "REDUCTION Execution Time: " << reduction_time << " seconds" << endl;

    return 0;
}
