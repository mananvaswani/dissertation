#include "header.h"

// // Modified Gram-schmidt algorithm for QR decomposition
// // http://www.ams.sunysb.edu/~jiao/teaching/ams526_fall11/lectures/lecture06.pdf Slide 6
// void gramSchmidt(vector<vector<complex<double>>> &a, vector<vector<complex<double>>> &q, vector<vector<complex<double>>> &r, int size) {
//     vector<vector<complex<double>>> v;
//     vectorMatrixInit(v, size, size);
//     for (int j = 0; j < size; j++) {
//         // v_j = a_j
//         for (int k = 0; k < size; k++) {
//             v[k][j] = a[k][j];
//         }
//     }
//     for (int i = 0; i < size; i++) {
//         // r_ii = ||v_i||_2
//         r[i][i] = 0;
//         for (int k = 0; k < size; k++) {
//             r[i][i] += norm(v[k][i]);
//         }
//         r[i][i] = sqrt(r[i][i]);
//
//         // q_i = v_j/r_ii
//         for (int k = 0; k < size; k++) {
//             q[k][i] = v[k][i]/r[i][i];
//         }
//
//         for (int j = i + 1; j < size; j++) {
//             // r_ij = conj(q_i) * v_j
//             r[i][j] = 0;
//             for (int k = 0; k < size; k++) {
//                 r[i][j] += conj(q[k][i]) * v[k][j];
//             }
//             // v_j = v_j − r_ij * q_i
//             for (int k = 0; k < size; k++) {
//                 v[k][j] -= r[i][j] * q[k][i];
//             }
//         }
//     }
//     // cout << endl << "Q is: " << endl;
//     // printComplexMatrix(q, SIZE);
//     // cout << endl << "R is: " << endl;
//     // printComplexMatrix(r, SIZE);
//
//     // // QR MULTIPLICATION to check
//     // vector<vector<complex<double>>> conjTrans;
//     // vectorMatrixConjugateTranspose(q, conjTrans);
//     //
//     // vector<vector<complex<double>>> output;
//     // vectorMatrixMult(q, conjTrans, output);
//     //
//     // cout << endl;
//     // print2dComplexVec(output);
//
// }

// Make a random unitary matrix
// void randomUnitary(int size, vector<vector<complex<double>>> &A) {
//
//     random_device rd;
//     mt19937 gen(rd());
//     normal_distribution<> d(0,1);   // mean = 0, std dev = 1
//
//     vectorMatrixInit(A, size, size);
//
//     for (int i = 0; i < size; i++) {
//         for (int j = 0; j < size; j++) {
//             complex<double> temp(d(gen), d(gen));
//             A[i][j] = temp;
//         }
//     }
//
//     // Carry out QR decomposition
//     vector<vector<complex<double>>> q;
//     vector<vector<complex<double>>> r;
//
//     vectorMatrixInit(q, size, size);
//     vectorMatrixInit(r, size, size);
//
//     gramSchmidt(A, q, r, size);
//
//     // Create R_Diag
//     vector<vector<complex<double>>> r_diag;
//     vectorMatrixInit(r_diag, size, size);
//     for (int i = 0; i < size; i++) {
//         r_diag[i][i] = (real(r[i][i]) > 0) - (real(r[i][i]) < 0);
//     }
//
//     // Random unitary matrix
//     vector<vector<complex<double>>> randomUnitary;
//     vectorMatrixMult(q, r_diag, randomUnitary);
//     // matrixMult(q, r_diag, randomUnitary);
//
//     A = randomUnitary;
//     // Check
//     // complex<double> temp[SIZE][SIZE];
//     // matrixConjugateTranspose(randomUnitary, temp);
//     // complex<double> out[SIZE][SIZE];
//     // matrixMult(randomUnitary, temp, out);
//     // printComplexMatrix(out, SIZE);
// }

arma::cx_mat randomUnitary(int m) {
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<> d(0,1);   // mean = 0, std dev = 1

    arma::mat A_real(m, m, arma::fill::randn);
    arma::mat A_imag(m, m, arma::fill::randn);

    arma::cx_mat A(A_real, A_imag);

    arma::cx_mat Q, R;
    arma::qr(Q, R, A);

    arma::mat R_diag = arma::sign(arma::real(arma::diagmat(R)));

    A = Q * R_diag;

    return A;
}

// int main(int argc, char *argv[]) {
//     arma::cx_mat A;
//     A = randomUnitary(3);
//     A.print("A:");
//
//     // // Check if hermitian
//     // arma:: cx_mat check = A * A.t();
//     return 0;
// }
