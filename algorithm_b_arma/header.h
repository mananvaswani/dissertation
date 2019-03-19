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

// Random unitary
arma::cx_mat randomUnitary(int m);
