

#include "Singleton.h"

int main(int argc, const char** argv) {
  Singleton::GetInstance().DoSomething();
  return 0;
}