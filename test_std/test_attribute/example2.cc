#include <iostream>
using namespace std;
struct p {
  int a;
  char b;
  short c;

} __attribute__((aligned(4))) pp;

struct m {
  char a;
  int b;
  short c;
} __attribute__((aligned(4))) mm;

struct o {
  int a;
  char b;
  short c;
} oo;

struct x {
  int a;
  char b;
  struct p px;
  short c;
} __attribute__((aligned(8))) xx;

int main() {
  printf("sizeof(int)=%d,sizeof(short)=%d.sizeof(char)=%d\n", sizeof(int),
         sizeof(short), sizeof(char));
  printf("pp=%d,mm=%d \n", sizeof(pp), sizeof(mm));
  printf("oo=%d,xx=%d \n", sizeof(oo), sizeof(xx));
  return 0;
}