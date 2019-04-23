#include "header.h"

arma::cx_vec cxPermMinors(arma::cx_mat C) {
// Declarations
	int n = C.n_cols, m = C.n_rows; // m = n + 1
	if(m != n + 1) {
		cout << "Input matrix has incorrect dimensions" << endl;
		exit (EXIT_FAILURE);
	}
    int i;
	int j = 0;
	int k;
    bool s = true;
    arma::cx_vec p(m), q(m), v(m);
    arma::cx_double t;
//
    arma::uvec d(n); d.fill(true);  // almost a boolean vector
//
    if(n == 1) return arma::flipud(C);
//
// g: initialize Gray code iterator
//
	arma::ivec g = arma::regspace< arma::ivec>(0,(n-1));
// Initialise delta sums v and partial products p
//
// p is just partial products of v
// e.g. if v = [a b c]
// p = [bc ac ab]
    v = arma::sum(C,1)/2;	// row sums divided by 2
    q = arma::cumprod(v);

	t = v[m-1];	// last element of v
    p[m-1] = q[m-2];
    for(i = m-2; i > 0; i--) {
        p[i] = t*q[i-1];
        t *= v[i];
    }

    p[0] = t;
	while(j < n-1){
        if(d[j]) v -= C.col(j); else v += C.col(j);

        q = arma::cumprod(v);
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
		// Iterate Gray code: j is active index
		if( j > 0){
            k = j + 1; g[j] = g[k]; g[k] = k; j = 0;
        } else {
            j = g[1]; g[1] = 1;
        }
	}
	return 2.*p;
}

// END
