// code to parallelize a counter 

#include <iostream>
#include <omp.h>
#include <chrono>
#include <random>

using namespace std;

int main(){

    omp_set_num_threads(10);

    long long N = 10000000000;
    long long c = 0;


    // serial
    auto start_s = chrono::high_resolution_clock::now();
    for(long long i = 0; i <N; i++){
        c++;
    }
    auto end_s = chrono::high_resolution_clock::now();

    double serial = chrono::duration<double>(end_s - start_s).count();


    c = 0;

    //parallel
    // critical makes sure only one thread runs at a time, there by, reduces any race conditions

    // try with both critical and atomic


    // auto start_p = chrono::high_resolution_clock::now();
    // #pragma omp critical
    // {
    //     #pragma omp parallel for reduction(+:c)
    //     for(long long i = 0; i <N; i++){
    //         c++;
    //     }
    // }
    // int threads = 0;

    // #pragma omp parallel
    // {
    //     #pragma omp single
    //     threads = omp_get_num_threads();
    // }
    // auto end_p = chrono::high_resolution_clock::now();

    // double parallel = chrono::duration<double>(end_p - start_p).count();



   // Using #pragma omp atomic ensures that updates to sum_parallel happen atomically, 
    //avoiding race conditions without needing a reduction clause. 


auto start_p = chrono::high_resolution_clock::now();

#pragma omp parallel
{
    #pragma omp for
    for(long long i = 0; i < N; i++){
        #pragma omp atomic
        c++;
    }
}

    int threads = 0;

    #pragma omp parallel
    {
        #pragma omp single
        threads = omp_get_num_threads();
    }
    auto end_p = chrono::high_resolution_clock::now();

    double parallel = chrono::duration<double>(end_p - start_p).count();


    // Output results
    cout << "SERIAL" << endl;
    cout << "Time Taken: " << serial << " seconds" << endl;

    cout << "PARALLEL" << endl;
    cout << "Num Threads: " << threads << endl;
    cout << "Time Taken: " << parallel << " seconds" << endl;

    // delete c;

    return 0;
}
