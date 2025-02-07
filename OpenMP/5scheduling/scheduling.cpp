#include <iostream>
#include <omp.h>
#include <chrono>

using namespace std;

// workload
const long long N = 1000000000; 

void sum_static() {
    long long sum = 0;
    auto start = chrono::high_resolution_clock::now();
    
    #pragma omp parallel for schedule(static) reduction(+:sum)
    for (long long i = 0; i < N; i++) {
        sum += i;
    }
    auto end = chrono::high_resolution_clock::now();
    cout << "Static Scheduling Time: " 
         << chrono::duration<double>(end - start).count() << " seconds\n";
}

void sum_dynamic() {
    long long sum = 0;
    auto start = chrono::high_resolution_clock::now();
    #pragma omp parallel for schedule(dynamic) reduction(+:sum)
    for (long long i = 0; i < N; i++) {
        sum += i;
    }
    auto end = chrono::high_resolution_clock::now();
    cout << "Dynamic Scheduling Time: " 
         << chrono::duration<double>(end - start).count() << " seconds\n";
}

void sum_guided() {
    long long sum = 0;
    auto start = chrono::high_resolution_clock::now();
    #pragma omp parallel for schedule(guided) reduction(+:sum)
    for (long long i = 0; i < N; i++) {
        sum += i;
    }
    auto end = chrono::high_resolution_clock::now();
    cout << "Guided Scheduling Time: " 
         << chrono::duration<double>(end - start).count() << " seconds\n";
}

int main() {
    omp_set_num_threads(10); // Set number of threads

    cout << "Starting Scheduling Benchmark...\n";
    sum_static();
    sum_dynamic();
    sum_guided();

    return 0;
}
