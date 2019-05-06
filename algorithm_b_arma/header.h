#include <complex>
#include <random>
#include <iostream>
#include <chrono>
#include <fstream>
#include <armadillo>
#include <stdlib.h>

#define SIZE 3

using namespace std;

// Function declarations
// Get Permanents
arma::cx_vec cxPermMinors(arma::cx_mat C);

// Threaded Get Permanents
arma::cx_vec cxPermMinorsThreads(arma::cx_mat C, int numThreads);

// Random unitary
arma::cx_mat randomUnitary(int m);




// Helper stuff
void printArmaVector(arma::uvec d);
void printArmaVector(arma::cx_vec d);

arma::cx_vec getV(arma::uvec d, int j, int n, int ctr, arma::cx_mat C);

arma::uvec getDelta(int ctr, int n);

int getKthGrayCode(int k);

int getActiveIndex(long long ctr);
