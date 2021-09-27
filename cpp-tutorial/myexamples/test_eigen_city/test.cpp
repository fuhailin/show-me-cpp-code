#include <iostream>
#include <vector>

#include "Eigen/Core"
using namespace std;
using namespace Eigen;

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

MatrixXf HStack(const std::vector<Eigen::MatrixXf>& mat_vec) {
    assert(!mat_vec.empty());
    if (mat_vec.size() == 1) {
        return mat_vec[0];
    }
    long num_rows = mat_vec[0].rows();
    size_t num_cols = 0;
    for (size_t mat_idx = 0; mat_idx < mat_vec.size(); ++mat_idx) {
        assert(mat_vec[mat_idx].rows() == num_rows);
        num_cols += mat_vec[mat_idx].cols();
    }
    MatrixXf hstacked_mat(num_rows, num_cols);
    size_t col_offset = 0;
    for (size_t mat_idx = 0; mat_idx < mat_vec.size(); ++mat_idx) {
        long cur_cols = mat_vec[mat_idx].cols();
        hstacked_mat.middleCols(col_offset, cur_cols) = mat_vec[mat_idx];
        col_offset += cur_cols;
    }
    return hstacked_mat;
}

int main(int argc, char** argv) {
    std::vector<Eigen::MatrixXf> input1;
    //Create a 4x4 diagonal matrix from the vector [ 5 6 7 8 ]
    MatrixXf A(3, 3);
    A << 2, 3, 4, 5, 6, 7, 8, 9, 10;
    cout << "A" << endl
         << A << endl;

    MatrixXf B(1, 2);
    B << 1, 1;
    int test1 = 2;
    A.block<1,test1>(1,1) += B;
    cout << "after A:" << A.cols() << endl;
    int a = 1;
    auto b = 10 / 2;
    std::cout << "a * b = " << a * b << std::endl;

    // input1.push_back(A);

    // MatrixXf B(2, 2);
    // B << 1, 0, 6, 7;
    // cout << "B" << endl
    //      << B << endl;
    // input1.push_back(B);

    // auto test = HStack(input1);
    // cout << "test:" << test << endl;
    return 0;
}