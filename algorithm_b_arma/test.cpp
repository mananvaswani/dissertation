#include "header.h"

int main(int argc, char *argv[]) {

    int count = 0;
    int j = 0;
    int k;

    int n = stoi(argv[1]);

    arma::ivec g = arma::regspace< arma::ivec>(0,(n-1));
    (g.t()).print("G: ");
    cout << j << endl;

    while(j < n-1){
        count++;
        if( j > 0){
            k = j + 1; g[j] = g[k]; g[k] = k; j = 0;
        } else {
            j = g[1]; g[1] = 1;
        }
        (g.t()).print("G: ");
        cout << "j: " << j << endl;
        cout << "count: " << count << endl;
    }
    return 0;
}
