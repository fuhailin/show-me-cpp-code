#include "merge_sort.h"

#include "gtest/gtest.h"

TEST(Sort, MergeSort) {
  Sort::MergeSort<int> s;
  {
    std::vector<int> input = {3, 8, 7, 2, 5, 1, 9};
    std::vector<int> result = {1, 2, 3, 5, 7, 8, 9};

    std::vector<int> ret = s.sortArray(input);

    EXPECT_EQ(ret, result);
  }
}

TEST(Sort1, MergeSort) {
  Sort::MergeSort<double> s;
  {
    std::vector<double> input = {3.1, 8.2, 7.1, 2.0, 5.3, 1.2, 9.1};
    std::vector<double> result = {1.2, 2.0, 3.1, 5.3, 7.1, 8.2, 9.1};

    std::vector<double> ret = s.sortArray(input);

    EXPECT_EQ(ret, result);
  }
}

int main(){
    Mine::C1 c1;
    Mine::C2 c2;
    c1.callme();
    c2.callme();
    return 0;
}