#include "header.h"

int getActiveIndex(long long ctr) {
	return __builtin_ctzll(ctr);
}

int getKthGrayCode(long long k) {
    //k--;
    return k ^ (k >> 1);
}

arma::uvec getDelta(long long ctr, int n) {
    int gray = getKthGrayCode(ctr);
    arma::uvec d(n);
    d.fill(1);
    // first flip the bits
    int temp = gray ^ (int)pow(2, n) - 1; // 2^(n) - 1
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
	if (ctr!=0) {
		if(d[j] == 1) v -= C.col(j); else v += C.col(j);
	}
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

arma::cx_vec cxPermMinorsThreads(arma::cx_mat C, int numThreads) {
// Declarations
	int n = C.n_cols, m = C.n_rows; // m = n + 1

	if(m != n + 1) {
		cout << "Input matrix has incorrect dimensions" << endl;
		exit (EXIT_FAILURE);
	}

	int j;
	bool s;
    arma::cx_vec p(m), q(m), v(m);
    arma::cx_double t;

    arma::uvec d(n);
	d.fill(true);

    if(n == 1) return arma::flipud(C);

	p.zeros();

	// Number of loop iterations
	long upperBound = pow(2, n-1);

// #pragma omp declare reduction( + : arma::cx_vec : omp_out += omp_in ) \
// initializer( omp_priv = arma::zeros<arma::cx_vec>(omp_orig.n_rows))

	#pragma omp parallel num_threads(numThreads) private(d, v, s, q, j) shared(C, p)
	{
		// Initialise starting variables for each thread
		int this_thread = omp_get_thread_num();
		int num_threads = omp_get_num_threads();

		int minItsPerThread = upperBound / num_threads;
		int threadsWithExtra = upperBound % num_threads;

		long long my_start;
		long long my_end;

		if (this_thread < threadsWithExtra) {
			my_start = (this_thread) * (minItsPerThread + 1);
			my_end   = (this_thread+1) * (minItsPerThread + 1);
		}
		else {
			my_start = threadsWithExtra * (minItsPerThread + 1) + (this_thread - threadsWithExtra) * (minItsPerThread);
			my_end   = threadsWithExtra * (minItsPerThread + 1) + (this_thread - threadsWithExtra + 1) * (minItsPerThread);
		}

		int i;

		std::complex<double> t;

		d = getDelta(my_start-1, n);

		if (my_start != 0) j = getActiveIndex(my_start); else j = 0;

		v = getV(d, j, n, my_start, C);

		if (my_start%2 == 0) s = false;
		else s = true;

		arma::cx_vec p_local(m);

		p_local.zeros();

		for(long ctr = my_start; ctr < my_end; ctr++) {
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
			j = getActiveIndex(ctr+1);
			if(d[j] == 1) v -= C.col(j); else v += C.col(j);
		}

		#pragma omp critical
		{
			p+= p_local;
		}
	}
	return 2.*p;
}
// END
