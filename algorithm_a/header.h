#include <complex>
#include <random>
#include <iostream>
#include <stdlib.h> 

#define SIZE 3

using namespace std;

// Function declarations
// Get Permanent
complex<double> getPerm(vector<vector<complex<double>>> A);

// Random unitary
void randomUnitary(int size, vector<vector<complex<double>>> &A);

// Helper
void printComplex(complex<double> n);

void printComplexMatrix(complex<double> a[SIZE][SIZE], int size);

void print2dVec(vector<vector<int>> v);

void print2dComplexVec(vector<vector<complex<double>>> v);

complex<double> complexVecProd(vector<complex<double>> v);

vector<complex<double>> addVecs(vector<complex<double>> v1, vector<complex<double>> v2);

vector<complex<double>> subtractVecs(vector<complex<double>> v1, vector<complex<double>> v2);

vector<complex<double>> getCol(vector<vector<complex<double>>> m, int col);

void matrixConjugateTranspose(complex<double> a[SIZE][SIZE], complex<double> conjTrans[SIZE][SIZE]);

void vectorMatrixConjugateTranspose(vector<vector<complex<double>>> a, vector<vector<complex<double>>> &conjTrans);

void matrixMult(complex<double> a[SIZE][SIZE], complex<double> b[SIZE][SIZE], complex<double> out[SIZE][SIZE]);

void vectorMatrixMult(vector<vector<complex<double>>> a, vector<vector<complex<double>>> b, vector<vector<complex<double>>> &out);

void vectorMatrixInit(vector<vector<complex<double>>> &a, int rows, int cols);

void comb(int N, int K, vector<vector<int>> &combs);
