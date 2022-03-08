#include <string>
#include <unordered_map>
#include <vector>

#include "glog/logging.h"
#include "glog/stl_logging.h"
using namespace std;

class Solution {
 public:
  vector<double> calcEquation(vector<vector<string>>& equations,
                              vector<double>& values,
                              vector<vector<string>>& queries) {
    unordered_map<string, int> variables;
    int n = 0;
    for (vector<string>& equat : equations) {
      for (string& var : equat) {
        if (variables.find(var) == variables.end()) {
          variables[var] = n++;
        }
      }
    }
    // 建图
    vector<vector<double>> graph(n, vector<double>(n, -1.0));
    for (int i = 0; i < values.size(); i++) {
      string a = equations[i][0];
      string b = equations[i][1];
      graph[variables[a]][variables[b]] = values[i];
      graph[variables[b]][variables[a]] = 1.0 / values[i];
    }

    // Floyd
    for (int k = 0; k < n; k++) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          if (graph[i][k] > 0 && graph[k][j] > 0) {
            graph[i][j] = graph[i][k] * graph[k][j];
          }
        }
      }
    }

    vector<double> res;
    for (vector<string> query : queries) {
      string x = query[0];
      string y = query[1];
      if (variables.find(x) == variables.end() &&
          variables.find(y) == variables.end()) {
        res.emplace_back(-1.0);
      } else {
        double x_y = graph[variables[x]][variables[y]];
        res.emplace_back(x_y);
      }
    }
    return res;
  }
};

int main(int argc, const char** argv) {
  Solution so;
  vector<vector<string>> test_equa = {{"a", "b"}, {"c", "d"}};
  vector<double> test_val = {1.0, 1.0};
  vector<vector<string>> test_que = {
      {"a", "c"}, {"b", "d"}, {"b", "a"}, {"d", "c"}};
  vector<double> res = so.calcEquation(test_equa, test_val, test_que);
  LOG(INFO) << res;

  return 0;
}