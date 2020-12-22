#include <iostream>
#include <Eigen/Dense>
 
int main(int argc, char *argv[])
{
    Eigen::Matrix3d m = Eigen::Matrix3d::Identity();
    std::cout << m << std::endl;
    return 0;
}