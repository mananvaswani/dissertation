#include "header.h"

int main(int argc, char *argv[]) {

    int n = stoi(argv[1]);


    arma::mat Cr(n+1, n, arma::fill::randu);
    arma::mat Ci(n+1, n, arma::fill::randu);

    arma::cx_mat C(Cr, Ci);

    arma::cx_vec p1, p2;

    p1 = cxPermMinors(C);
    cout << endl;
    p2 = cxPermMinorsThreads(C);
    cout << endl;
    printArmaVector(p1);
    printArmaVector(p2);

    return 0;
}
