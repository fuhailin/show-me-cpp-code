#include <iostream>
#include <vector>
using namespace std;

void mycapacity(const vector<int>& vec) {
  cout << "分配总空间大小为：" << vec.capacity() << endl;
}

void mysize(const vector<int>& vec) {
  cout << "已用空间大小为：" << vec.size() << endl;
}

void myprint(const vector<int>& vec) {
  for (int i = 0; i < vec.size(); ++i) cout << vec[i] << ",";
  cout << endl;
}

int main() {
  vector<int> vec;
  vec.reserve(3);
  // vec.resize(3);
  cout << "起始状态：" << endl;
  mycapacity(vec);
  mysize(vec);
  cout << "========================" << endl;

  for (int i = 0; i < 10; ++i) {
    vec.push_back(i);
    cout << "压入第" << i + 1 << "个元素之后：" << endl;
    myprint(vec);
    mycapacity(vec);
    mysize(vec);
    cout << "========================" << endl;
  }

  return 0;
}