
#include "ps_util.h"

#include <city.h>
#include <sys/timeb.h>
#include <time.h>

#include <chrono>
#include <iostream>
using namespace std;

namespace Utils {
std::string vec2str(const MatrixXf& vec) {
  std::string re(sizeof(float) * vec.size(), '0');
  std::memcpy(&re[0], &vec(0, 0), re.size());
  return re;
}

std::string vec2str(const std::vector<float>& vec) {
  std::string re(sizeof(float) * vec.size(), '0');
  std::memcpy(&re[0], &vec.at(0), re.size());
  return re;
}

std::vector<float> str2vec(const std::string& str) {
  std::vector<float> re(str.size() / sizeof(float));
  std::memcpy(&re.at(0), &str[0], str.size());

  return re;
}

MatrixXf MatrixRandNorm(const float& mean, const float& sdev, const int& row,
                        const int& col) {
  static default_random_engine e(time(0));
  static normal_distribution<float> n(mean, sdev);
  return MatrixXf::Zero(row, col).unaryExpr([](float dummy) { return n(e); });
}

MatrixXf Truncated_MatrixRandNorm(const float& mean, const float& sdev,
                                  const int& row, const int& col) {
  static default_random_engine e(time(0));
  static normal_distribution<float> n(mean, sdev);
  static float mean_use = mean;
  static float sdev_use = sdev;
  return MatrixXf::Zero(row, col).unaryExpr([](float dummy) {
    float re = n(e);
    while (abs(re - mean_use) > 2 * sdev_use) {
      re = n(e);
    }
    return re;
  });
}

// define a custom template unary functor
template <typename Scalar>
struct CwiseClampOp {
  CwiseClampOp(const Scalar& inf, const Scalar& sup) : m_inf(inf), m_sup(sup) {}
  const Scalar operator()(const Scalar& x) const {
    return x < m_inf ? m_inf : (x > m_sup ? m_sup : x);
  }
  Scalar m_inf, m_sup;
};

void clip(MatrixXf& m, const float& min, const float& max) {
  m = m.unaryExpr(CwiseClampOp<float>(min, max));
}

void l2_norm_vec(MatrixXf& vec, const float& max_norm) {
  if (max_norm == 0) return;
  float l2_norm = sqrt(vec.squaredNorm());
  if (l2_norm <= max_norm)
    return;
  else {
    vec = vec * max_norm / l2_norm;
  }
}

void l2_norm_vec(Map<MatrixXf>& vec, const float& max_norm) {
  if (max_norm == 0) return;
  float l2_norm = sqrt(vec.squaredNorm());
  if (l2_norm <= max_norm)
    return;
  else {
    vec = vec * max_norm / l2_norm;
  }
}

std::vector<std::string> genRandStr(const int& len, const int& num) {
  std::vector<std::string> re;
  srand((unsigned)time(NULL));
  for (int k(0); k < num; ++k) {
    string ree;

    for (int i(0); i < len; ++i) {
      int flag = rand() % 3;
      switch (flag) {
        case 1:
          ree += 'A' + rand() % 26;
          break;
        case 2:
          ree += 'a' + rand() % 26;
          break;
        case 0:
          ree += '0' + rand() % 10;
          break;
      }
    }
    re.push_back(ree);
  }
  return re;
}

void myshuffle(vector<vector<string>>& data) {
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  shuffle(data.begin(), data.end(), default_random_engine(seed));
}

int64_t get_fid(const std::string& value, const int& slot) {
  return (int64_t)(CityHash64(value.c_str(), value.length()) &
                   ((1lu << 52) - 1)) |
         ((int64_t)slot << 52);
}

int get_slot(const int64_t& fid) { return (int)(fid >> 52); }
}  // namespace Utils
