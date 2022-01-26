/*
 * @Company: TWL
 * @Author: xue jian
 * @Email: xuejian@kanzhun.com
 * @Date: 2019-11-19 14:40:13
 */
#include "MatrixRand.h"
#include <iostream>
int main() {
    // std::cout<<"begin"<<std::endl;
    MatrixXf rand_mat(MatrixRandNorm(0, 1, 1, 50));
    std::cout<<"The init matrix "<<std::endl
    <<rand_mat<<std::endl;

    std::string media = vec2str(rand_mat);
    std::vector<float> vec_tmp(str2vec(media));
    Map<MatrixXf> sec_mat(&vec_tmp.at(0), 1, vec_tmp.size());
    std::cout<<"The second Matrix "<<std::endl
    <<sec_mat<<std::endl;
}