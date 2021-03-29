#include "Eigen/Core"
#include <iostream>
#include <vector>
using namespace std;
using namespace Eigen;

MatrixXf softmax_grad(MatrixXf x) {
    VectorXf vec = Map<const VectorXf>(x.data(), x.size());
    auto mat = vec.asDiagonal().toDenseMatrix();
    auto test = vec * vec.transpose();
    return mat - test;
}

// 先定义softmax函数，使用最大值做rescale，让数值更稳定
MatrixXf softmax_fn(MatrixXf x) {
    auto softmax = x.array().exp();
    VectorXf sorfmax_rowsum = softmax.rowwise().sum();
    return softmax.array().colwise() / sorfmax_rowsum.array();  //行归一化
}

MatrixXf stablesoftmax_fn(MatrixXf x) {
    auto shiftx = x.array() - x.maxCoeff();
    auto exps = shiftx.array().exp();
    VectorXf sorfmax_rowsum = exps.rowwise().sum();
    return exps.array().colwise() / sorfmax_rowsum.array();  //行归一化
}

template <typename T>
MatrixXf softmax_grad1(T x) {
    VectorXf vec = Map<const VectorXf>(x.data(), x.size());
    int size = vec.size();
    auto e = VectorXf::Ones(size);
    auto I = MatrixXf::Identity(size, size);

    auto res = vec * e.transpose();
    auto tmp = I - e * vec.transpose();
    return res.cwiseProduct(tmp);
}

int main(int argc, char const *argv[]) {
    // vector<double> a = {1, 4, 5};
    // VectorXd e = VectorXd::Ones(3);
    // vector<double> a1{2, 3, 4};
    // VectorXd vec = Eigen::Map<VectorXd, Unaligned>(a1.data(), a1.size());

    MatrixXf M = MatrixXf(3, 1);
    M << 1, 2, 3;
    cout << "Matrix: " << M << endl;

    std::cout << "vec: " << softmax_grad(M) << std::endl;

    std::cout << "vec1: " << softmax_grad1(M.col(0)) << std::endl;

    // cout << "out: " << M.cwiseProduct(M)<< endl;

    // Eigen::DiagonalMatrix<double, 3> mat = b.asDiagonal();

    // MatrixXd M = MatrixXd::Map(b.data(), 3, 1);
    // std::cout << "M shape" << M.rows() << " " << M.cols() << std::endl;

    // auto test = b * b.transpose();

    // std::cout << "test: \n" << test << std::endl;

    // // Eigen::MatrixXf c(2, 3);
    // // c << 1, 2, 3, 4, 5, 6;
    // std::cout << "Matrix:\n" << mat.toDenseMatrix() << std::endl;
    /* code */
    return 0;
}
