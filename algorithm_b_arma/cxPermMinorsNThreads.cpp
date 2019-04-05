#include "header.h"
#define NUM_THREADS 2

int nextGrayCode(long long ctr) {
	return __builtin_ctzll(ctr);
}

int getNthGrayCode(int n) {
    n--;
    return n ^ (n >> 1);
}

arma::uvec getDelta(int ctr, int n) {
    int gray = getNthGrayCode(ctr);
    arma::uvec d(n);
    d.fill(1);
    // first flip the bits
    int temp = gray ^ (int)pow(2, n) - 1;// 2^(n) - 1
    int i = 0;
    while (temp != 0) {
        d[i++] = temp % 2;
        temp = temp / 2;
    }
    return d;
}

arma::cx_vec getV(arma::uvec d, int j, int n, int ctr, arma::cx_mat C) {
	arma::cx_vec v(n);
	v = arma::sum(C,1)/2;
    for (int i = 0; i < n; i++) {
        if(d[i] == 0) v -= C.col(i);
    }
	if (ctr!=0) {if(d[j] == 1) v -= C.col(j); else v += C.col(j);}
    return v;
}

void printArmaVector(arma::uvec d) {
    for (int i = 0; i < d.size(); i++) {
        cout << d[i] << " ";
    }
    cout << endl;
}

void printArmaVector(arma::cx_vec d) {
    for (int i = 0; i < d.size(); i++) {
        cout << d[i] << " ";
    }
    cout << endl;
}

arma::cx_vec cxPermMinorsThreads(arma::cx_mat C) {
// Declarations
	int n = C.n_cols, m = C.n_rows; // m = n + 1

	if(m != n + 1) {
		cout << "Input matrix has incorrect dimensions" << endl;
		exit (EXIT_FAILURE);
	}

	// long long ctr = 1LL; //org
	long long ctr = 0LL;

    int i;
	int j = 0;
	int k;
    //bool s = true; //org
	bool s = false;
    arma::cx_vec p(m), q(m), v(m);
    arma::cx_double t;
//
    arma::uvec d(n); d.fill(true);  // almost a boolean vector
//
    if(n == 1) return arma::flipud(C);
//
// g: initialize Gray code iterator
//
	// arma::ivec g = arma::regspace< arma::ivec>(0,(n-1));

// Initialise delta sums v and partial products p
//
    v = arma::sum(C,1)/2;
	p.zeros(); // new
    // q = arma::cumprod(v); t = v[m-1];
    // p[m-1] = q[m-2];
    // for(i = m-2; i > 0; i--){
    //     p[i] = t*q[i-1];
    //     t *= v[i];
    // }
    // p[0] = t;

	while(ctr <= pow(2, n-1) - 1) {	// while ctr < (2^n-1) - 1
		j = nextGrayCode(ctr);
		//cout << j << " ";

		d = getDelta((int) ctr, n);
		//printArmaVector(d);

		v = getV(d, j, n, (int) ctr, C);
		printArmaVector(v);
        //if(d[j] == 1) v -= C.col(j); else v += C.col(j);

		ctr++;

		q = arma::cumprod(v); t = v[m-1];
        if(s) {
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
		//d[j] = 1 ^ d[j];
		s = !s;

// iterate Gray code: j is active index
// QUESTION: Confused about whats going on here
		// if( j > 0){
        //     k = j + 1; g[j] = g[k]; g[k] = k; j = 0;
        // } else {
        //     j = g[1]; g[1] = 1;
        // }
	}
	return 2.*p;
}

// END
