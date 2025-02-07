#include <iostream>
#include <omp.h>
#include <chrono>

using namespace std;

int main() {
    long long N = 10000;
    long long i = 0;

    // Serial version
    auto start_time_serial = chrono::high_resolution_clock::now();
    for (long long j = 0; j < N; j++) {
        cout << "Serial hello from i = " << i << endl;
        i++;
    }
    auto end_time_serial = chrono::high_resolution_clock::now();
    double time_taken_serial = chrono::duration<double>(end_time_serial - start_time_serial).count();

    // Reset i for parallel version
    i = 0;

    // Parallel version
    auto start_time = chrono::high_resolution_clock::now();
    // #pragma omp parallel for reduction(+:i)
    // for (long long j = 0; j < N; j++) {
    //     int thread_id = omp_get_thread_num();
    //     cout << "Parallel hello from thread " << thread_id << "." << endl;
    //     i++;
    // }

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        #pragma omp critical
        {
            cout << "Parallel hello from thread " << thread_id << "." << endl;
        }
    }

    auto end_time = chrono::high_resolution_clock::now();
    double time_taken = chrono::duration<double>(end_time - start_time).count();

    // Output times
    cout << "SERIAL" << endl;
    cout << "Time Taken: " << time_taken_serial << " seconds" << endl;

    cout << "PARALLEL" << endl;
    cout << "Time Taken: " << time_taken << " seconds" << endl;

    return 0;
}
