#include "header.h"

void bosonSampler(vector<vector<complex<double>>> A, int n, int m, vector<int> &z) {
    // Line 1
    vector<int> r;
    // Line 2
    // TODO: Permute columns of A
    // Line 3
    vector<int> w;
    for (int i = 1; i <= m; i++) {
        w.push_back(norm(A[i-1][1]));
    }
    // Line 4
    discrete_distribution<> d(w.begin(), w.end());
    random_device rd;
    mt19937 gen(rd());
    int x = d(gen) + 1;
    // Line 5
    r.push_back(x);
    w.clear();
    // Line 6
    for (int k = 2; k <= n; k++) {
        // Line 7 Make B_k = A_kr (B_k is B_k diamond)
        vector<vector<complex<double>>> B_k;
        for (int a = 0; a < r.size(); a++) {
            vector<complex<double>> tempRow;
            for (int b = 0; b < k; b++) {
                tempRow.push_back(A[r[a]-1][b]);
            }
            B_k.push_back(tempRow);
        }
        // Line 8
        vector<complex<double>> perms;
        vector<vector<complex<double>>> temp;
        vectorMatrixTranspose(B_k, temp);
        perms = getPermMinors(temp);
        // Line 9
        for (int i = 1; i <= m; i++) {
            complex<double> w_i = 0;
            for (int l = 1; l <= k; l++) {
                w_i = w_i + A[i-1][l-1] * perms[l-1];
            }
            cout << w_i << " ";
            w.push_back(norm(w_i));
        }
        cout << endl << endl;
        // Line 10
        discrete_distribution<> d(w.begin(), w.end());
        random_device rd;
        mt19937 gen(rd());
        int x = d(gen) + 1;
        // Line 11
        r.push_back(x);
        w.clear();
        // Line 12
    }
    // Line 13
    sort(r.begin(), r.end());
    z = r;
    // Line 14
}



int main(int argc, char *argv[]) {

    // Start clock
    auto start = chrono::steady_clock::now();

    int n, m;
    if (argc != 3) {
        cout << "You didn't enter an n and an m!!!" << endl;
        exit(0);
    }
    n = stoi(argv[1]);
    m = stoi(argv[2]);

    // Make random unitary matrix A
    vector<vector<complex<double>>> A;
    randomUnitary(m, A);
    print2dComplexVec(A);

    // Run bosson sampling algorithm A
    vector<int> output;
    bosonSampler(A, n, m, output);
    cout << "[ ";
    for (int i = 0; i < output.size(); i++) {
        cout << output[i] << " ";
    }
    cout << "]";
    cout << endl;

    // Stop clock
    auto end = chrono::steady_clock::now();

    cout << "Elapsed time in microseconds : "
        << chrono::duration_cast<chrono::microseconds>(end - start).count()
        << " µs" << endl;


    std::ofstream outfile;
    outfile.open("timings.csv", std::ios_base::app);
    outfile << n << ", " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl; 

    return 0;
}
