// Code to parallelize the dot product of two large arrays

#include <iostream>
#include <omp.h>
#include <chrono>
#include <random>

using namespace std;

long long N = 10000000;

int main(){

    omp_set_num_threads(9);

    long long *a, *b;
    random_device rd;
    mt19937 gen(rd());

    a = new long long[N];
    b = new long long[N];

    uniform_int_distribution<int> dist(1, 1000000);

    // populate a and b
    for(long long i = 0; i< N; i++){
        a[i] = dist(gen);
        b[i] = dist(gen);
    }

    long long dot_product = 0;


    // dot product serial
    auto start_serial = chrono::high_resolution_clock::now();
    for (long long i = 0; i < N; i++){
        dot_product += a[i]*b[i];
    }
    auto end_serial = chrono::high_resolution_clock::now();
    double serial_time = chrono::duration<double>(end_serial - start_serial).count();

    dot_product = 0;

    // dot product parallel

    auto start_parallel = chrono::high_resolution_clock::now();
    int threads = 0;
    #pragma omp parallel
    {
        #pragma omp single
        threads = omp_get_num_threads();
        #pragma omp parallel for reduction(+:dot_product)
            for(long long i = 0; i < N; i++){
                dot_product += a[i]*b[i];
            }
    }
    auto end_parallel = chrono::high_resolution_clock::now();

    double parallel_time = chrono::duration<double>(end_parallel - start_parallel).count();

    // Output times
    cout << "SERIAL" << endl;
    cout << "Time Taken: " <<serial_time<< " seconds" << endl;

    cout << "PARALLEL" << endl;
    cout<<"Num Threads: "<<threads<<endl;
    cout << "Time Taken: " <<parallel_time << " seconds" << endl;

    
    // Memory deallocation
    delete[] a;
    delete[] b;


    return 0;
}