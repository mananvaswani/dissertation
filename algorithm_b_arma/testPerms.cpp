#include "header.h"

int main(int argc, char *argv[]) {

    int n = stoi(argv[1]);

    // arma::mat Cr(n+1, n, arma::fill::randu);
    // arma::mat Ci(n+1, n, arma::fill::randu);

    arma::mat Cr(n+1, n, arma::fill::ones);
    arma::mat Ci(n+1, n, arma::fill::zeros);

    arma::cx_mat C(Cr, Ci);

    arma::cx_vec p1, p2;

    auto start = chrono::steady_clock::now();
    p1 = cxPermMinors(C);
    auto end = chrono::steady_clock::now();
    printArmaVector(p1);
    cout << "Non-parallel elapsed time in milliseconds : "
    << chrono::duration_cast<chrono::milliseconds>(end - start).count()
    << " ms" << endl;

    cout << "==================" << endl;
    start = chrono::steady_clock::now();
    p2 = cxPermMinorsThreads(C);
    end = chrono::steady_clock::now();
    cout << endl;
    printArmaVector(p2);
    cout << "Parallel elapsed time in milliseconds : "
    << chrono::duration_cast<chrono::milliseconds>(end - start).count()
    << " ms" << endl;

    return 0;
}
