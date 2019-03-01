#include "header.h"
#include <algorithm>
#include <string>

complex<double> getPerm(vector<vector<complex<double>>> A) {
// Declarations
    int n = A.size(),  m = A[0].size(); // needs to be square matrix
	if(m != n) cout << "Input matrix has incorrect dimensions";

    int j = 0, k;

    // v = sum of elements in each row /2
    vector<complex<double>> v;
    for (int i = 0; i < n; i++) {
        complex<double> rowsum = 0;
        for (int j = 0; j < n; j++) {
            rowsum += A[i][j];
        }
        v.push_back(rowsum/2.0);
    }

    // p = product of elements in v
    complex<double> p = complex<double>(1., 0.);
    p = complexVecProd(v);

    bool s = true;
//
    vector<bool> d(n, true);
//
    if(n==1) return A[0][0];
//
// g: initialize a gray code iterator
    vector<int> g;
    for (int i = 0; i < n; i++) {
        g.push_back(i);
    }
//
    while (j < n-1) {
        vector<complex<double>> A_j = getCol(A, j);
        if (d[j]) v = subtractVecs(v, A_j);
        else      v = addVecs(v, A_j);
        s? p-= complexVecProd(v) : p+= complexVecProd(v);
        d[j] = !d[j]; s=!s;
// iterate Gray code: j is active index
        if (j > 0) {
            k = j+1;
            g[j] = g[k];
            g[k] = k;
            j = 0;
        }
        else {
            j = g[1];
            g[1] = 1;
        }
    }
    return 2.*p;
}
