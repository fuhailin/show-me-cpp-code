// https://blog.csdn.net/hjimce/article/details/71603118

#include <iostream>
#include <vector>

#include "Eigen/Dense"

using namespace std;
using namespace Eigen;

int main(int argc, char* argv[]) {
    Eigen::MatrixXf x(3, 3);
    x << 2, 4, 4, 4, 16, 12, 4, 12, 10;

    cout << "x: " << endl
         << x << endl;

    cout << "softmax_fn: " << endl
         << stablesoftmax_fn(x) << endl;

    std::cout << "softmax_backward: " << softmax_grad1(x.row(1)) << std::endl;

    std::cout << "softmax_backward for matrix: " << softmax_grad_martix(x) << std::endl;

    // auto cache = forward(x, y);
    // cout << "cache: " << endl
    //      << cache[1] << endl;

    // auto grad = backward(cache);
    // cout << grad << endl;

    // auto grad_naive = backward_naive(x, y);
    // cout << grad_naive << endl;
    return 0;
}