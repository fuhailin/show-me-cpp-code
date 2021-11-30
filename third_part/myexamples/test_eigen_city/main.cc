// https://blog.csdn.net/hjimce/article/details/71603118

#include <iostream>
#include <vector>

#include "Eigen/Dense"

using namespace std;
using namespace Eigen;

int main(int argc, char* argv[]) {
    Eigen::MatrixXf label(9, 1);
    label << 1, 2, 3, 4, 5, 6, 7, 8, 9;

    cout << "label: " << endl
         << label << endl;

    Eigen::MatrixXf input_message(9, 1);
    input_message << 1.2, 2.1, 3.3, 4.4, 5.1, 5.9, 6.7, 6.8, 7.9;

    cout << "input_message: " << endl
         << input_message << endl;

    float loss_ = 0.5 * ((input_message - label).squaredNorm()) / label.rows();
//     float loss_ = (input_message - label).squaredNorm();
    cout << "loss_: " << loss_ << endl;

    // auto cache = forward(x, y);
    // cout << "cache: " << endl
    //      << cache[1] << endl;

    // auto grad = backward(cache);
    // cout << grad << endl;

    // auto grad_naive = backward_naive(x, y);
    // cout << grad_naive << endl;
    return 0;
}