#include <complex>
#include <random>
#include <iostream>

#define SIZE 3

using namespace std;

// Print a complex number
void printComplex(complex<double> n) {
    cout << real(n);
    if (imag(n) >= 0) cout << "+";
    cout << imag(n) << "i";
}

// Print a complex matrix
void printComplexMatrix(complex<double> a[SIZE][SIZE], int size) {
    for(int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printComplex(a[i][j]);
            cout << "\t";
        }
        cout << endl;
    }
}

// Conjugate transpose of a matrix
void matrixConjugateTranspose(complex<double> a[SIZE][SIZE], complex<double> conjTrans[SIZE][SIZE]) {
    for(int i = 0; i < SIZE; ++i) {
        for(int j = 0; j < SIZE; ++j){
            conjTrans[i][j] = conj(a[j][i]);
        }
    }
}

// Matrix multiplication
void matrixMult(complex<double> a[SIZE][SIZE], complex<double> b[SIZE][SIZE], complex<double> out[SIZE][SIZE]) {
    for(int i = 0; i < SIZE; ++i) {
        for(int j = 0; j < SIZE; ++j){
            out[i][j] = 0;
            for(int k = 0; k < SIZE; ++k) {
                out[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}
