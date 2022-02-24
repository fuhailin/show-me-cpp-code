#include <algorithm>
#include <boost/bind.hpp>
#include <iostream>
#include <vector>

void print(std::ostream *os, int i) { *os << i << '\n'; }

int main() {
  std::vector<int> v{1, 3, 2};
  std::for_each(v.begin(), v.end(), boost::bind(print, &std::cout, _1));
}