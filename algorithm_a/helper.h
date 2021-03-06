#include <complex>
#include <random>
#include <iostream>

#define SIZE 3

using namespace std;

// Function declarations
complex<double> getPerm(vector<vector<complex<double>>> A);

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

// Print a 2D vector
void print2dVec(vector<vector<int>> v) {
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v.at(0).size(); j++) {
            cout << v[i][j] << "\t";
        }
        cout << endl;
    }
}

// Print a 2D complex vector
void print2dComplexVec(vector<vector<complex<double>>> v) {
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v.at(0).size(); j++) {
            printComplex(v[i][j]);
            cout << "\t";
        }
        cout << endl;
    }
}

// Product of elements in a complex vector
complex<double> complexVecProd(vector<complex<double>> v) {
    complex<double> prod = complex<double>(1., 0.);;
    for (int i = 0; i < v.size(); i++) {
        prod = prod*v[i];
    }
    return prod;
}

// Add two complex vectors (element-wise)
vector<complex<double>> addVecs(vector<complex<double>> v1, vector<complex<double>> v2) {
    vector<complex<double>> result;
    if (v1.size() != v2.size()) cout << "Incorrect inputs";
    for (int i = 0; i < v1.size(); i++) {
        result.push_back(v1[i] + v2[i]);
    }
    return result;
}

// Subtract two complex vectors (element-wise)
vector<complex<double>> subtractVecs(vector<complex<double>> v1, vector<complex<double>> v2) {
    vector<complex<double>> result;
    if (v1.size() != v2.size()) cout << "Incorrect inputs";
    for (int i = 0; i < v1.size(); i++) {
        result.push_back(v1[i] + v2[i]);
    }
    return result;
}

// Get the ith column of a complex vector matrix (as a vector)
vector<complex<double>> getCol(vector<vector<complex<double>>> m, int col) {
    vector<complex<double>> output;
    for (int i = 0; i < m.size(); i++) {
        output.push_back(m[i][col]);
    }
    return output;
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
