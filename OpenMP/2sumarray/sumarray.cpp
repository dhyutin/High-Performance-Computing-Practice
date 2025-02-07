// Code to parallelize the sum of two arrays

#include <iostream>
#include <omp.h>
#include <chrono>

using namespace std;

int main(){

    long long N = 1000000;

    int *arr = new int[N];
    long long sum_parallel = 0, sum_serial = 0;

    // populate the array
    for (long long i = 0; i < N; i++){
        arr[i] = i + 1;
    }

    // serial

    auto start_serial = chrono::high_resolution_clock::now();

    for(long long i =0; i < N; i++){
        sum_serial += arr[i];
    }
    auto end_serial = chrono::high_resolution_clock::now();

    double serial_time = chrono::duration<double>(end_serial-start_serial).count();


    //Parallel
    auto start_parallel = chrono::high_resolution_clock::now();
    #pragma omp parallel for reduction(+:sum_parallel)
    for(long long i =0; i < N; i++){
        sum_parallel += arr[i];
    }

    auto end_parallel = chrono::high_resolution_clock::now();

    double parallel_time = chrono::duration<double>(end_parallel-start_parallel).count();


    // Output times
    cout << "SERIAL" << endl;
    cout << "Time Taken: " <<serial_time<< " seconds" << endl;

    cout << "PARALLEL" << endl;
    cout << "Time Taken: " <<parallel_time << " seconds" << endl;

    return 0;



    
}