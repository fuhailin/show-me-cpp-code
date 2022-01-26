#include <iostream>

#include "ps_util.h"
#include "time_function.h"
int main() {
  // std::cout<<"begin"<<std::endl;
  MatrixXf rand_mat(MatrixRandNorm(0, 1, 1, 50));
  std::cout << "The init matrix " << std::endl << rand_mat << std::endl;

  std::string media = vec2str(rand_mat);
  std::vector<float> vec_tmp(str2vec(media));
  Map<MatrixXf> sec_mat(&vec_tmp.at(0), 1, vec_tmp.size());
  std::cout << "The second Matrix " << std::endl << sec_mat << std::endl;
}