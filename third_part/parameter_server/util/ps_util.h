#ifndef PS_UTIL_H
#define PS_UTIL_H

#include <cmath>
#include <ctime>
#include <random>
#include <string>

#include "Eigen/Eigen"

// using namespace std;
using namespace Eigen;

namespace Utils {
/**
 * @note: memory copy the vector to serialized string.
 */
std::string vec2str(const MatrixXf& vec);
std::string vec2str(const std::vector<float>& vec);
/**
 * @note: memory copy the serialized string to vector. Together with the eigen
 * Map, which reuse the same memory of a vector, could calculate the Matrix fast
 * and use less memory.
 */
std::vector<float> str2vec(const std::string& str);

/**
 * @note: The function to gen Rand Matrix. The first one to generate a norm
 * distribution
 */
MatrixXf MatrixRandNorm(const float& mean, const float& sdev, const int& row,
                        const int& col);
MatrixXf Truncated_MatrixRandNorm(const float& mean, const float& sdev,
                                  const int& row, const int& col);
void clip(MatrixXf& m, const float& min, const float& max);

/**
 * @note: normalization of the vector.
 */
void l2_norm_vec(MatrixXf& vec, const float& max_norm);
void l2_norm_vec(Map<MatrixXf>& vec, const float& max_norm);

std::vector<std::string> genRandStr(const int& len, const int& num);

// shuffle the string data
void myshuffle(std::vector<std::vector<std::string>>& data);

int64_t get_fid(const std::string& value, const int& slot);
int get_slot(const int64_t& fid);

}  // namespace Utils

#endif
