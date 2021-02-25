// https://blog.csdn.net/hjimce/article/details/71603118

#include <Eigen/Dense>
#include <iostream>
#include <vector>

using namespace std;
using namespace Eigen;

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

// MatrixXf softmax_grad(MatrixXf x) {
//     int rows = x.rows();
//     int cols = x.cols();

//     MatrixXf jacobian_m = x.asDiagonal();
//     int n = jacobian_m.rows();
//     for (int i = 0; i < n; ++i) {
//         for (int j = 0; j < n; ++j) {
//             if (i == j) {
//                 jacobian_m[i][j] = x[i] * (1 - x[i]);
//             } else {
//                 jacobian_m[i][j] = -x[i] * x[j];
//             }
//         }
//     }
// }
MatrixXf softmax_grad(MatrixXf x) {
    VectorXf vec = Map<const VectorXf>(x.data(), x.size());
    auto mat = vec.asDiagonal().toDenseMatrix();
    auto test = vec * vec.transpose();
    return mat - test;
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
// matrix_eig = Eigen::MatrixXf in RowMajor format
MatrixXf VStack(const std::vector<MatrixXf>& mat_vec) {
    assert(!mat_vec.empty());
    long num_cols = mat_vec[0].cols();
    size_t num_rows = 0;
    for (size_t mat_idx = 0; mat_idx < mat_vec.size(); ++mat_idx) {
        assert(mat_vec[mat_idx].cols() == num_cols);
        num_rows += mat_vec[mat_idx].rows();
    }
    MatrixXf vstacked_mat(num_rows, num_cols);
    size_t row_offset = 0;
    for (size_t mat_idx = 0; mat_idx < mat_vec.size(); ++mat_idx) {
        long cur_rows = mat_vec[mat_idx].rows();
        vstacked_mat.middleRows(row_offset, cur_rows) = mat_vec[mat_idx];
        row_offset += cur_rows;
    }
    return vstacked_mat;
}

MatrixXf softmax_grad_martix(MatrixXf x) {
    vector<MatrixXf> holder;
    int dim = x.cols();
    for (int i = 0; i < x.rows(); i++) {
        auto tmp = softmax_grad1(x.row(i));
        holder.push_back(tmp);
    }

    // MatrixXf res(dim * holder.size(), dim);
    // for (auto grad : holder) {
    //     res << grad;
    // }
    // cout << "hehe" << endl;
    auto res = VStack(holder);

    return res;
}

// 定义L2损失函数计算
float l2_loss(MatrixXf pred, MatrixXf label) {
    // pred: 概率，0~1
    // label: one-hot编码后的label
    auto diff = (pred - label).cwiseAbs2().mean();
    return diff;
}

vector<MatrixXf> forward(const MatrixXf& x, const MatrixXf& y) {
    auto z = softmax_fn(x);
    cout << "tmp softmax \n"
         << z << endl;
    cout << "stablesoftmax_fn: \n"
         << stablesoftmax_fn(x) << endl;
    auto loss = l2_loss(z, y);
    cout << "tmp loss \n"
         << loss << endl;
    vector<MatrixXf> res = {x, z, y};
    return res;
}

MatrixXf backward(vector<MatrixXf> cache) {
    MatrixXf x = cache[0];
    MatrixXf z = cache[1];
    MatrixXf y = cache[2];

    auto dLdz = (z - y) * 2 / z.rows();
    auto test1 = dLdz.cwiseProduct(z);
    auto test = dLdz.array() - (test1).sum();
    auto dLdx = z.array() * test;
    return dLdx;
}

// MatrixXf backward_naive(MatrixXf x, MatrixXf y) {
//     float delta = 1e-10;
//     int r = x.rows();
//     int c = x.cols();
//     auto _grad = MatrixXf::Zero(r, c);

//     for (int i = 0; i < x.size(); ++i) {
//         auto xi = x[i];

//         // 把z的每一个值都加减一个很小的偏移量delta
//         auto origin = xi;

//         // 减偏移量
//         x[i] = origin - delta;
//         auto p1 = softmax_fn(x);
//         auto loss1 = l2_loss(p1, y);

//         // 加偏移量
//         x[i] = origin + delta;
//         auto p2 = softmax_fn(x);
//         auto loss2 = l2_loss(p2, y);

//         // 求斜率作为导数
//         _grad[i] = (loss2 - loss1) / (2 * delta);
//         z[i] = origin;
//     }
// }

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