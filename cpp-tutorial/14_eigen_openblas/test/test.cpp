#include <Eigen/Core>
#include <iostream>
using namespace std;
using namespace Eigen;

int main(int argc, char** argv) {
    //Create a 4x4 diagonal matrix from the vector [ 5 6 7 8 ]
    Eigen::Vector4d vec;
    vec << 5, 6, 7, 8;
    Eigen::DiagonalMatrix<double, 4> mat = vec.asDiagonal();
    cout << "mat" << endl << mat.toDenseMatrix() << endl;

    MatrixXf matrix_23(2, 3);
    matrix_23 << 1, 2, 3, 4, 5, 6;

    cout<< "max: " <<matrix_23.maxCoeff() << endl; 

    int r = matrix_23.rows();
    int c = matrix_23.cols();
    MatrixXf jacobian_m = matrix_23.asDiagonal();
    cout << "jacobian_m" << endl << jacobian_m << endl;

    auto test = matrix_23.array() - 1.0;

    cout << test << endl;
    cout << "*******" <<endl;
    cout << matrix_23 << endl;

    return 0;
}