#pragma once
#include <stdio.h>

#include <Eigen/Dense>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/variant.hpp>
#include <cmath>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <random>
#include <sstream>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

#include "eigen_func.h"
#include "gflags/gflags.h"
#include "glog/logging.h"
#include "hash_method.h"
#include "nlohmann/json.hpp"
#include "ps/ps.h"
#include "tools.h"

namespace YCDL {
typedef uint64_t ull;
using SLOT_ID_FEAS = std::pair<int, std::vector<std::string>>;

inline nlohmann::json &global_conf() {
  static nlohmann::json conf;
  return conf;
}

class Layer {};
}  // namespace YCDL
