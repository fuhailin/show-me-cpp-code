#include "Eigen/Core"
#include <iostream>
#include <vector>
using namespace std;
using namespace Eigen;

int main(int argc, char** argv) {
    //     vector<double> a{2, 3};
    //     VectorXd A = Eigen::Map<VectorXd, Unaligned>(a.data(), a.size());
    MatrixXd A(2, 2);
    A << 2, 3, 4, 5;

    //     vector<double> b{1, 1};
    //     VectorXd B = Eigen::Map<VectorXd, Unaligned>(b.data(), b.size());
    //     MatrixXd B(2, 2);
    //     B << 1, 0, 0, 1;

    VectorXd B = VectorXd::Ones(A.cols());
    cout << "A: \n"
         << A << endl;
    cout << "B: \n"
         << B << endl;

    Eigen::MatrixXd v1;
    v1 = A.transpose();  // Copy #1
    v1.resize(A.size(), 1);     // No copy
    cout << "v1: \n"
         << v1 << endl;

    auto res = v1 * B.transpose();
    cout << "res: \n"
         << res << endl;

    return 0;
}