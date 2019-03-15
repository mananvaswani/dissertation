#include "header.h"
#include <algorithm>
#include <string>

vector<complex<double>> getPermMinors(vector<vector<complex<double>>> A) {
// Declarations
    int m = A.size(),  n = A[0].size(); // m = rows, n = cols
	if(m != n+1) cout << "Input matrix has incorrect dimensions" << endl;
    int i, j = 0, k;
    bool s = true;
    vector<complex<double>> p(m);
    vector<complex<double>> q(m);
    vector<complex<double>> v(m);
    complex<double> t;
//
    vector<bool> d(n, true); // almost a boolean vector
//
    if(n == 1) {
        vector<complex<double>> temp;
        temp.push_back(A[1][0]);
        temp.push_back(A[0][0]);
        return temp;
    }
//
// g: initialize Gray code iterator
    vector<int> g;
    for (int i = 0; i < n; i++) {
        g.push_back(i);
    }
//
// Initialise delta sums v and partial products p
//

    // v = sum of elements in each row /2
    v.clear();

    for (int i = 0; i < m; i++) {
        complex<double> rowsum = 0;
        for (int j = 0; j < m; j++) {
            rowsum += A[i][j];
        }
        v.push_back(rowsum/2.0);
    }
    // q = cumulative product of elements in v
    q = complexVecCumProd(v);
    t = v[m-1];
    p[m-1] = q[m-2];
    for(i = m-2; i > 0; i--){
        p[i] = t*q[i-1];
        t *= v[i];
    }
    p[0] = t;
    while (j < n-1) {
        vector<complex<double>> A_j = getCol(A, j);
        if (d[j]) v = subtractVecs(v, A_j);
        else      v = addVecs(v, A_j);
        q = complexVecCumProd(v);
        t = v[m-1];
        if(s){
            p[m-1] -= q[m-2];
            for(i = m-2; i > 0; i--){
                p[i] -= t*q[i-1];
                t *= v[i];
            }
            p[0] -= t;
        } else {
           p[m-1] += q[m-2];
           for(i = m-2; i > 0; i--){
                p[i] += t*q[i-1];
                t *= v[i];
            }
            p[0] += t;
        }
		d[j] = !d[j]; s = !s;

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

    for (int i = 0; i < p.size(); i++) {
        p[i] = 2.*p[i];
    }
    return p;
}
