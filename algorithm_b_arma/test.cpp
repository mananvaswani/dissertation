#include "header.h"

int nextGrayCode(long long ctr) {
	return __builtin_ctzll(ctr);
}

int getNthGrayCode(int n) {
    n--;
    return n ^ (n >> 1);
}

arma::uvec getDelta(int ctr, int n) {
    gray = getNthGrayCode(int ctr);
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

arma::uvec getV(arma::uvec d, int j, int n) {
    arma::uvec v(n);
    v = v.fill(n);
    for (int i = 0; i < n; i++) {
        if(d[i] == 1) v[i] = i; else v[i] = n;
    }

    if(d[j] == 1) v[j] = n; else v[j] = j;
    return v;
}

void printArmaVector(arma::uvec d) {
    for (int i = 0; i < d.size(); i++) {
        cout << d[i] << " ";
    }
    cout << endl;
}

int main(int argc, char *argv[]) {

    int n = stoi(argv[1]);

    arma::uvec d(n);
    arma::uvec d_test(n);

    arma::uvec v(n);

    v = arma::regspace<arma::uvec>(0,  n-1);

    d_test.fill(1);

    long long ctr = 1LL;
    int j = 0;
    int gray;
    while(ctr <= pow(2, n-1) - 1) {
        j = nextGrayCode(ctr);
        d = getDelta((int) ctr, n);
        v = getV(d, j, n);
        cout << ctr << " " << j << " " << gray << " " << endl;
        printArmaVector(v);
        printArmaVector(d);
        cout << "=========" << endl;
        //d_test[j] = !d_test[j];
        ctr++;
    }

    return 0;
}
