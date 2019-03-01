#include "header.h"

void bosonSampler(vector<vector<complex<double>>> A, int n, int m, vector<int> &z) {
    // Line 1
    vector<int> r;
    // Line 2
    for (int k = 1; k <= n; k++) {
        // Line 3
        vector<int> w;
        vector<vector<int>> C_k;
        comb(n, k, C_k);
        for (int i = 1; i <= m; i++) {
            r.push_back(i);
            int w_i = 0;
            for (int j = 1; j <= C_k.size(); j++) {
                // Make A_cri
                vector<vector<complex<double>>> A_cri;
                for (int a = 0; a < r.size(); a++) {
                    vector<complex<double>> tempRow;
                    for (int b = 0; b < C_k[j-1].size(); b++) {
                        tempRow.push_back(A[r[a]-1][C_k[j-1][b]-1]);
                    }
                    A_cri.push_back(tempRow);
                }
                // print2dComplexVec(A_cri);
                // cout << endl;
                w_i += norm(getPerm(A_cri));
            }
            w.push_back(w_i);
            r.pop_back(); // Turn (r, i) back into r
        }
        // Line 4
        discrete_distribution<> d(w.begin(), w.end());
        random_device rd;
        mt19937 gen(rd());
        int x = d(gen) + 1;
        // Line 5
        r.push_back(x);
    }
    // Line 7
    sort(r.begin(), r.end());
    z = r;
}

int main(int argc, char *argv[]) {
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
    return 0;
}
