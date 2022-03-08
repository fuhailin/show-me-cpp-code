#include <iostream>
using namespace std;

class Apple {
 public:
  static int i;

  Apple() {
    // i = 0;
    cout << "Inside Constructor\n";
  }
  ~Apple() { cout << "Inside Destructor\n"; }
};

int main() {
  int x = 0;
  if (x == 0) {
    Apple obj;
    Apple::i = 1;
  }
  cout << "End of main\n";
}
