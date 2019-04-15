#include "header.h"

vector<int> bosonSampler(arma::cx_mat A, int n, int m, int &timeInPerms) {
    // Take first n columns of A
    A.set_size(m, n);

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
        A.swap_cols(i, j);
    }

    // Line 3
    // Note: Not using armadillo here as i'm not sure how to gnerate a discrete_distribution in arma, and i think its fine
    vector<double> w;
    for (int i = 1; i <= m; i++) {
        w.push_back(norm(A(i-1, 1)));
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
        arma::cx_mat B_k;
        B_k.set_size(k-1, k);
        for (int a = 0; a < r.size(); a++) {
            for (int b = 0; b < k; b++) {
                B_k(a,b) = A(r[a]-1, b);
            }
        }

        // Line 8
        arma::cx_vec perms;
        arma::cx_mat temp;

        auto startPerms = chrono::steady_clock::now();
        //perms = cxPermMinors(B_k.st());
        perms = cxPermMinorsThreads(B_k.st());
        auto endPerms = chrono::steady_clock::now();
        timeInPerms += chrono::duration_cast<chrono::milliseconds>(endPerms - startPerms).count();

        // Line 9
        for (int i = 1; i <= m; i++) {
            arma::cx_double w_i = 0;
            for (int l = 1; l <= k; l++) {
                w_i = w_i + A(i-1, l-1) * perms[l-1];
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

    // Line 14
    return z;
}

void runOneSample(int n, int m) {

    // Start clock
    auto start = chrono::steady_clock::now();

    // Keep track of the time spent in calculating the permanents
    int timeInPerms = 0;

    // Make random unitary matrix A
    arma::cx_mat A;
    A = randomUnitary(m);
    // print2dComplexVec(A);

    // Run boson sampling algorithm A
    vector<int> output;
    output = bosonSampler(A, n, m, timeInPerms);

    // Stop clock
    auto end = chrono::steady_clock::now();

    // Print
    cout << "[ ";
    for (int i = 0; i < output.size(); i++) {
        cout << output[i] << " ";
    }
    cout << "]";
    cout << endl;

    cout << "Elapsed time in milliseconds for n = " << n << " : "
        << chrono::duration_cast<chrono::milliseconds>(end - start).count()
        << " ms" << endl;

    cout << "Time spent in calculating permanents : "
        << timeInPerms
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
