#include <Eigen/Dense>
// #include <ctime>
#include <iostream>

using namespace std;

int main() {
    srand(1);
    Eigen::MatrixXd randvalue = (Eigen::MatrixXd::Random(4, 4)).array().abs() * 2 * M_PI;
    std::cout << randvalue << std::endl;
    cout << endl;

    auto test = randvalue.block(0, 1, 1, -1);
    std::cout << randvalue << std::endl;

    srand(1);
    Eigen::MatrixXd randvalue1 = (Eigen::MatrixXd::Random(4, 4)).array().abs() * 2 * M_PI;
    std::cout << randvalue1 << std::endl;
    cout << endl;

    Eigen::MatrixXcd randvalue2 = Eigen::MatrixXcd::Random(4, 4);
    std::cout << randvalue2 << std::endl;
    cout << endl;

    Eigen::MatrixXcd randvalue3 = Eigen::MatrixXcd::Random(4, 4);
    std::cout << randvalue3 << std::endl;
}
