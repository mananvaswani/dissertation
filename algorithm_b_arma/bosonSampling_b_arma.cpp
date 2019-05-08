#include "header.h"

vector<int> bosonSampler(arma::cx_mat A, int n, int m, int &timeInPerms, bool parallelFlag, int numThreads) {
    // Take first n columns of A
    A.st();
    A.set_size(n, m);

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
        A.swap_rows(i, j);
    }

    // Line 3
    vector<double> w;
    for (int i = 1; i <= m; i++) {
        w.push_back(norm(A(0, i-1)));
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
        B_k.set_size(k, k-1);
        for (int a = 0; a < r.size(); a++) {
            for (int b = 0; b < k; b++) {
                B_k(b,a) = A(b, r[a]-1);
            }
        }

        // Line 8
        arma::cx_vec perms;
        arma::cx_mat temp;

        auto startPerms = chrono::steady_clock::now();
        if (!parallelFlag) perms = cxPermMinors(B_k);
        else perms = cxPermMinorsThreads(B_k, numThreads);
        auto endPerms = chrono::steady_clock::now();
        timeInPerms += chrono::duration_cast<chrono::milliseconds>(endPerms - startPerms).count();

        // Line 9
        for (int i = 1; i <= m; i++) {
            arma::cx_double w_i = 0;
            for (int l = 1; l <= k; l++) {
                w_i = w_i + A(l-1, i-1) * perms[l-1];
            }
            w.push_back(norm(w_i));
        }

        // Line 10
        discrete_distribution<> d(w.begin(), w.end());
        int x = d(gen) + 1;

        // Line 11
        r.push_back(x);
        w.clear();

    }
    // Line 12
    vector<int> z;
    sort(r.begin(), r.end());
    z = r;

    // Line 13
    return z;
}

void runOneSample(int n, int m, bool parallelFlag, bool saveData, int numThreads, string filename) {

    // Start clock
    auto start = chrono::steady_clock::now();

    // Keep track of the time spent in calculating the permanents
    int timeInPerms = 0;

    // Make random unitary matrix A
    arma::cx_mat A;
    A = randomUnitary(m);

    // Run boson sampling algorithm A
    vector<int> output;
    output = bosonSampler(A, n, m, timeInPerms, parallelFlag, numThreads);

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

    if (saveData) {
        std::ofstream outfile;
        string parallelStr;
        if (parallelFlag) parallelStr = "_parallel"; else parallelStr = "_serial";
        outfile.open(filename + parallelStr + ".csv", std::ios_base::app);
        outfile << n << ", " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << ", " << timeInPerms << endl;
    }
}

int main(int argc, char *argv[]) {

    // Flags set at runtime
    bool parallelFlag = false;
    bool saveData = false;

    int n, numSamples, numThreads=0;
    string filename="";

    if (argc == 3) {
        n = stoi(argv[1]);
        numSamples = stoi(argv[2]);
    }

    else if (argc == 5) {
        n = stoi(argv[1]);
        numSamples = stoi(argv[2]);
        if (strcmp(argv[3], "-parallel") == 0) {
            parallelFlag = true;
            numThreads = stoi(argv[4]);
        }
        else if (strcmp(argv[3], "-saveData") == 0) {
            saveData = true;
            filename = argv[4];
        }
    }

    else if (argc == 7) {
        n = stoi(argv[1]);
        numSamples = stoi(argv[2]);
        if ((strcmp(argv[3], "-parallel") == 0) && (strcmp(argv[5], "-saveData") == 0)){
            parallelFlag = true;
            numThreads = stoi(argv[4]);

            saveData = true;
            filename = argv[6];
        }
    }

    else {
        cout << "Your arguments are incorrect. Enter an n, followed by number of samples, then flags \'-parallel\' along with number of threads and/or \'-saveData\' along with a file name to save data to, in that order." << endl;
        exit(0);
    }

    if (!saveData) {
        int m = n * n;
        for (int j = 1; j <= numSamples; j++) {
            runOneSample(n, m, parallelFlag, saveData, numThreads, filename);
        }
    }
    else {
        for (int i = 2; i <= n; i++) {
            for (int j = 1; j <= numSamples; j++) {
                runOneSample(i, i*i, parallelFlag, saveData, numThreads, filename);
            }
        }
    }

    return 0;
}
