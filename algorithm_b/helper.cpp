#include "header.h"

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

// Cumulative product of elements in a complex vector
vector<complex<double>> complexVecCumProd(vector<complex<double>> v) {
    for (int i = 1; i < v.size(); i++) {
        v[i] = v[i] * v[i-1];
    }
    return v;
}

// Add two complex vectors (element-wise)
vector<complex<double>> addVecs(vector<complex<double>> v1, vector<complex<double>> v2) {
    vector<complex<double>> result;
    if (v1.size() != v2.size()) {cout << "Incorrect inputs";
    cout << v1.size() << " " << v2.size(); }
    for (int i = 0; i < v1.size(); i++) {
        result.push_back(v1[i] + v2[i]);
    }
    return result;
}

// Subtract two complex vectors (element-wise)
vector<complex<double>> subtractVecs(vector<complex<double>> v1, vector<complex<double>> v2) {
    vector<complex<double>> result;
    if (v1.size() != v2.size()) {cout << "Incorrect inputs";
    cout << v1.size() << " " << v2.size(); }
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

// Conjugate transpose of a vector matrix
void vectorMatrixConjugateTranspose(vector<vector<complex<double>>> a, vector<vector<complex<double>>> &conjTrans) {
    vectorMatrixInit(conjTrans, a[0].size(), a.size());
    for(int i = 0; i < conjTrans.size(); ++i) {
        for(int j = 0; j < conjTrans[0].size(); ++j){
            conjTrans[i][j] = conj(a[j][i]);
        }
    }
}

// Transpose of a vector matrix
void vectorMatrixTranspose(vector<vector<complex<double>>> a, vector<vector<complex<double>>> &trans) {
    vectorMatrixInit(trans, a[0].size(), a.size());
    for(int i = 0; i < trans.size(); ++i) {
        for(int j = 0; j < trans[0].size(); ++j){
            trans[i][j] = a[j][i];
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

// Vector matrix multiplication
void vectorMatrixMult(vector<vector<complex<double>>> a, vector<vector<complex<double>>> b, vector<vector<complex<double>>> &out) {
    vectorMatrixInit(out, a.size(), b[0].size());
    for(int i = 0; i < a.size(); i++) {
        for(int j = 0; j < b[0].size(); j++){
            out[i][j] = 0;
            for(int k = 0; k < b.size(); k++) {
                out[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

// initialize vector with zeros
void vectorMatrixInit(vector<vector<complex<double>>> &a, int rows, int cols) {
    for(int i = 0; i < rows; i++) {
        vector<complex<double>> temp;
        for(int j = 0; j < cols; j++){
            temp.push_back(0);
        }
        a.push_back(temp);
    }
}

// Get the list of combinations(without repetitions) of K elements from 1 ... N
void comb(int N, int K, vector<vector<int>> &combs) {
    std::string bitmask(K, 1); // K leading 1's
    bitmask.resize(N, 0); // N-K trailing 0's

    // print integers and permute bitmask
    do {
        vector<int> temp;
        for (int i = 1; i <= N; ++i) {
            if (bitmask[i-1]) temp.push_back(i);
        }
        combs.push_back(temp);
    } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
}
