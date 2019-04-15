#include "header.h"
#define NUM_THREADS 2

int nextGrayCode(long long ctr) {
	return __builtin_ctzll(ctr);
}

int getNthGrayCode(long long n) {
    n--;
    return n ^ (n >> 1);
}

arma::uvec getDelta(long long ctr, int n) {
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

arma::cx_vec getV(arma::uvec d, int j, int n, long long ctr, arma::cx_mat C) {
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

// Initialise delta sums v and partial products p
//
    //v = arma::sum(C,1)/2;
	p.zeros(); // new
    // q = arma::cumprod(v); t = v[m-1];
    // p[m-1] = q[m-2];
    // for(i = m-2; i > 0; i--){
    //     p[i] = t*q[i-1];
    //     t *= v[i];
    // }
    // p[0] = t;

	long upperBound = pow(2, n-1);

// #pragma omp declare reduction( + : arma::cx_vec : omp_out += omp_in ) \
// initializer( omp_priv = arma::zeros<arma::cx_vec>(omp_orig.n_rows))

//cout << "Starting off parallel " << endl;
	#pragma omp parallel num_threads(NUM_THREADS) private(d, v, s, q, j) shared(C, p)//reduction (+:p) private(d, v, s, q)
	{
		int this_thread = omp_get_thread_num();
		int num_threads = omp_get_num_threads();
		long long my_start = (this_thread) * upperBound / num_threads;
		long long my_end   = (this_thread+1) * upperBound / num_threads;

		int i;

		std::complex<double> t;

		d = getDelta(my_start, n);

		j = nextGrayCode(my_start);

		v = getV(d, j, n, my_start, C);

		if (my_start%2 == 0) s = false;
		else s = true;

		arma::cx_vec p_local(m);
		p_local.zeros();

		#pragma omp critical
		{
			cout << this_thread << ": v : ";
			printArmaVector(v);
		}

		for(long ctr = my_start; ctr < my_end; ctr++) {
			//j = nextGrayCode(ctr);

			// cout << j << "\t";
			// printArmaVector(d);
			// printArmaVector(v);

			q = arma::cumprod(v);
			t = v[m-1];
	        if(s){
	            p_local[m-1] -= q[m-2];
	            for(i = m-2; i > 0; i--){
	                p_local[i] -= t*q[i-1];
	                t *= v[i];
	            }
	            p_local[0] -= t;
	        } else {
	           p_local[m-1] += q[m-2];
	           for(i = m-2; i > 0; i--){
	                p_local[i] += t*q[i-1];
	                t *= v[i];
	            }
	            p_local[0] += t;
			}

			s = !s;
			if (ctr!=0) d[j] = 1 ^ d[j];
			j = nextGrayCode(ctr+1);
			if(d[j] == 1) v -= C.col(j); else v += C.col(j);
			//if (ctr!=0) d[j] = 1 ^ d[j];
		}
		#pragma omp critical
		{
			cout << this_thread << ": p_local : ";
			printArmaVector(p_local);
			p+= p_local;
			printArmaVector(p);
		}
	}

	// for (long long ctr = 0LL; ctr < upperBound; ctr++) {
	// 	j = nextGrayCode(ctr);
	// 	//cout << j << " ";
	//
	// 	// d = getDelta((int) ctr, n);
	// 	//printArmaVector(d);
	//
	// 	v = getV(d, j, n, (int) ctr, C);
	// 	//printArmaVector(v);
    //     //if(d[j] == 1) v -= C.col(j); else v += C.col(j);
	//
	// 	q = arma::cumprod(v); t = v[m-1];
    //     if(s) {
    //         p[m-1] -= q[m-2];
    //         for(i = m-2; i > 0; i--){
    //             p[i] -= t*q[i-1];
    //             t *= v[i];
    //         }
    //         p[0] -= t;
    //     } else {
    //        p[m-1] += q[m-2];
    //        for(i = m-2; i > 0; i--){
    //             p[i] += t*q[i-1];
    //             t *= v[i];
    //         }
    //         p[0] += t;
    //     }
	// 	//d[j] = 1 ^ d[j];
	// 	s = !s;
	// }
	return 2.*p;
}

// END
