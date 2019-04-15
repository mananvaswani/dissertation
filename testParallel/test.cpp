#include <cmath>
#include <iostream>
#include <chrono>
#include <omp.h>

using namespace std;

int main() {

    int result = 0;
#pragma omp parallel reduction (+:result)
{
    int this_thread = omp_get_thread_num();
    int num_threads = omp_get_num_threads();
    int my_start = (this_thread) * 100 / num_threads;
    int my_end   = (this_thread+1) * 100 / num_threads;
    int i = my_start;
    for(int n=my_start; n<my_end; n++) {
        result += i;
        i++;
    }
}

    cout << result << endl;

// auto start = chrono::steady_clock::now();
// #pragma omp parallel
// {
// int this_thread = omp_get_thread_num();
// int num_threads = omp_get_num_threads();
// int my_start = (this_thread) * 100000000 / num_threads;
// int my_end   = (this_thread+1) * 100000000 / num_threads;
// for(int n=my_start; n<my_end; ++n) int i = n*n;
// }
// cout << endl;
// auto end = chrono::steady_clock::now();
//
// cout << "Parallel elapsed time in nanoseconds : "
// << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
// << " ns" << endl;
//
// start = chrono::steady_clock::now();
// for(int n=0; n<100000000; ++n) int i = n*n;
// cout << endl;
// end = chrono::steady_clock::now();
//
// cout << "Not parallel elapsed time in nanoseconds : "
// << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
// << " ns" << endl;

    return 0;
}
