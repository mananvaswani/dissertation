#include "helper.h"

// Modified Gram-schmidt algorithm for QR decomposition
// http://www.ams.sunysb.edu/~jiao/teaching/ams526_fall11/lectures/lecture06.pdf Slide 6
void gramSchmidt(complex<double> a[SIZE][SIZE], complex<double> q[SIZE][SIZE], complex<double> r[SIZE][SIZE], int size) {
    complex<double> v[size][size];
    for (int j = 0; j < size; j++) {
        // v_j = a_j
        for (int k = 0; k < size; k++) {
            v[k][j] = a[k][j];
        }
    }
    for (int i = 0; i < size; i++) {
        // r_ii = ||v_i||_2
        r[i][i] = 0;
        for (int k = 0; k < size; k++) {
            r[i][i] += norm(v[k][i]);
        }
        r[i][i] = sqrt(r[i][i]);

        // q_i = v_j/r_ii
        for (int k = 0; k < size; k++) {
            q[k][i] = v[k][i]/r[i][i];
        }

        for (int j = i + 1; j < size; j++) {
            // r_ij = conj(q_i) * v_j
            r[i][j] = 0;
            for (int k = 0; k < size; k++) {
                r[i][j] += conj(q[k][i]) * v[k][j];
            }
            // v_j = v_j − r_ij * q_i
            for (int k = 0; k < size; k++) {
                v[k][j] -= r[i][j] * q[k][i];
            }
        }
    }
    // cout << endl << "Q is: " << endl;
    // printComplexMatrix(q, SIZE);
    // cout << endl << "R is: " << endl;
    // printComplexMatrix(r, SIZE);

    // // QR MULTIPLICATION to check
    // complex<double> conjTrans[SIZE][SIZE];
    // matrixConjugateTranspose(q, conjTrans);
    //
    // complex<double> output[SIZE][SIZE];
    // matrixMult(q, conjTrans, output);
    //
    // cout << endl;
    // printComplexMatrix(output, SIZE);

}

// Make a random unitary matrix
void randomUnitary(int size) {
    complex<double> A[SIZE][SIZE];

    random_device rd;
    mt19937 gen(rd());
    normal_distribution<> d(0,1);   // mean = 0, std dev = 1

    for(int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            complex<double> temp(d(gen), d(gen));
            A[i][j] = temp;
        }
    }

    // Carry out QR decomposition
    complex<double> q[SIZE][SIZE];
    complex<double> r[SIZE][SIZE];
    gramSchmidt(A, q, r, SIZE);

    // Create R_Diag
    complex<double> r_diag[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        r_diag[i][i] = (real(r[i][i]) > 0) - (real(r[i][i]) < 0);
    }

    // Random unitary matrix
    complex<double> randomUnitary[SIZE][SIZE];
    matrixMult(q, r_diag, randomUnitary);
    printComplexMatrix(randomUnitary, SIZE);

    // Check
    // complex<double> temp[SIZE][SIZE];
    // matrixConjugateTranspose(randomUnitary, temp);
    // complex<double> out[SIZE][SIZE];
    // matrixMult(randomUnitary, temp, out);
    // printComplexMatrix(out, SIZE);
}

int main(int argc, char *argv[]) {
    randomUnitary(SIZE);
    return 0;
}
