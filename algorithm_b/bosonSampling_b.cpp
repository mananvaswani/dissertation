#include "header.h"

vector<int> bosonSampler(vector<vector<complex<double>>> A, int n, int m) {

    // Generate random seed
    random_device rd;
    mt19937 gen(rd());

    // Line 1
    vector<int> r;

    // Line 2
    // Permute columns of A
    // Using Knuth shuffle algorithm https://en.wikipedia.org/wiki/Random_permutation#Knuth_shuffles
    // Random uniform integer taken from https://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range/19728404
    for (int i = 0; i <= n-2; i++) {
        uniform_int_distribution<int> uni(i, n-1);
        int j = uni(gen);
        for (int k = 0; k < m; k++) {
            complex<double> temp = A[k][i];
            A[k][i] = A[k][j];
            A[k][j] = temp;
        }
    }

    // Line 3
    vector<double> w;
    for (int i = 1; i <= m; i++) {
        w.push_back(norm(A[i-1][1]));
    }

    // Line 4
    discrete_distribution<> d(w.begin(), w.end());
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
        vector<vector<complex<double>>> B_k_trans;
        vectorMatrixTranspose(B_k, B_k_trans);
        perms = getPermMinors(B_k_trans);

        // Line 9
        for (int i = 1; i <= m; i++) {
            complex<double> w_i = 0;
            for (int l = 1; l <= k; l++) {
                w_i = w_i + A[i-1][l-1] * perms[l-1];
            }
            w.push_back(norm(w_i));
        }

        // Line 10
        discrete_distribution<> d(w.begin(), w.end());
        int x = d(gen) + 1;

        // Line 11
        r.push_back(x);
        w.clear();

        // Line 12
    }
    // Line 13
    vector<int> z;
    sort(r.begin(), r.end());
    z = r;
    return z;
    // Line 14
}

void runOneSample(int n, int m) {
    // Start clock
    auto start = chrono::steady_clock::now();

    // Make random unitary matrix A
    vector<vector<complex<double>>> A;
    A = randomUnitary(m);
    // print2dComplexVec(A);

    // Run boson sampling algorithm A
    vector<int> output;
    output = bosonSampler(A, n, m);
    cout << "[ ";
    for (int i = 0; i < output.size(); i++) {
        cout << output[i] << " ";
    }
    cout << "]";
    cout << endl;

    // Stop clock
    auto end = chrono::steady_clock::now();

    cout << "Elapsed time in milliseconds : "
        << chrono::duration_cast<chrono::milliseconds>(end - start).count()
        << " ms" << endl;


    std::ofstream outfile;
    outfile.open("timings.csv", std::ios_base::app);
    outfile << n << ", " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;
}

int main(int argc, char *argv[]) {

    int n, m, num;
    if (argc == 3) {
        n = stoi(argv[1]);
        m = stoi(argv[2]);
        runOneSample(n, m);
    }
    else if (argc == 2) {
        remove ("timings.csv");
        num = stoi(argv[1]);
        for (int i = 2; i <= num; i++) {
            runOneSample(i, i*i);
        }
    }
    else {
        cout << "You didn't enter an n and an m!!!" << endl;
        exit(0);
    }

    return 0;
}
