#include "gtest/gtest.h"
 
int abs(int x) {
  return x >= 0? x : -x;
}
 
TEST(BazelTest, AbsTest) {
  EXPECT_EQ(abs(-1), 1);
}