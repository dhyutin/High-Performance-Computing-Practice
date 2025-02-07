#include <omp.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>

using namespace std;

// Serial Prefix Sum
void serial_prefix_sum(vector<int>& arr) {
    int N = arr.size();
    for (int i = 1; i < N; i++) {
        arr[i] += arr[i - 1];
    }

    // return arr;
}

void parallel_prefix_sum(vector<int>& arr) {
    int N = arr.size();
    vector<int> arr_p(N, 1);
    
    // Find the next power of 2
    int pow2_N = pow(2, ceil(log2(N)));
    
    // Pad array with zeros to make it power of 2
    arr.resize(pow2_N, 0);
    // Up-Sweep Phase
    for (int step = 1; step < pow2_N; step *= 2) {
        #pragma omp parallel for
        for (int i = 0; i < pow2_N; i += 2 * step) {
            if (i + step - 1 < pow2_N && i + 2 * step - 1 < pow2_N) {
                arr_p[i + 2 * step - 1] += arr_p[i + step - 1];
            }
        }
    }

    // Down-Sweep Phase
    for (int step = pow2_N / 2; step >= 1; step /= 2) {
        #pragma omp parallel for
        for (int i = 0; i < pow2_N; i += 2 * step) {
            if (i + step - 1 < pow2_N && i + 2 * step - 1 < pow2_N) {
                int temp = arr[i + step - 1];
                arr_p[i + step - 1] = arr_p[i + 2 * step - 1];
                arr_p[i + 2 * step - 1] += temp;
            }
        }
    }

    arr = arr_p;
    // Remove the padding
    arr.resize(N);
    // return arr;
}

int main() {
    omp_set_num_threads(5);  // Set number of threads

    int N = 1000000;  // Array size
    vector<int> arr_serial(N, 1);  // Array for serial computation
    vector<int> arr_parallel(N, 1);  // Array for parallel computation

    // Serial Prefix Sum Timing
    auto start_time = chrono::high_resolution_clock::now();
    serial_prefix_sum(arr_serial);
    auto end_time = chrono::high_resolution_clock::now();
    double time_serial = chrono::duration<double>(end_time - start_time).count();
    cout << "Serial Prefix Sum Time Taken: " << time_serial << " seconds" << endl;

    // Parallel Prefix Sum Timing
    start_time = chrono::high_resolution_clock::now();
    parallel_prefix_sum(arr_parallel);
    end_time = chrono::high_resolution_clock::now();
    double time_parallel = chrono::duration<double>(end_time - start_time).count();
    cout << "Parallel Prefix Sum Time Taken: " << time_parallel << " seconds" << endl;

    // Validate correctness
    bool correct = true;
    for (int i = 0; i < N; i++) {
        cout<<arr_serial[i]<<" "<<arr_parallel[i]<<endl;
        if (arr_serial[i] != arr_parallel[i]) {
            correct = false;
            break;
        }
    }
    cout << "Prefix Sum Correctness: " << (correct ? "PASSED" : "FAILED") << endl;

    return 0;
}
