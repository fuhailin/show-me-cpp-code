
#include <functional>
#include <queue>
#include <vector>
using namespace std;

class MedianFinder {
  priority_queue<int, vector<int>, std::greater<int>> minHeap; // 小顶堆
  priority_queue<int, vector<int>, std::less<int>> maxHeap; // 大顶堆

 public:
  /** initialize your data structure here. */
  MedianFinder() {}

  void addNum(int num) {
    if (maxHeap.size() >= minHeap.size()) {
      maxHeap.emplace(num);
      minHeap.emplace(maxHeap.top());
      maxHeap.pop();
    } else {
      minHeap.emplace(num);
      maxHeap.emplace(minHeap.top());
      minHeap.pop();
    }
  }

  double findMedian() {
    if (maxHeap.size() == minHeap.size()) {
      return (maxHeap.top() + minHeap.top()) / 2.0;
    } else if (maxHeap.size() > minHeap.size()) {
      return maxHeap.top() / 1.0;
    } else {
      return minHeap.top() / 1.0;
    }
  }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */

int main(int argc, const char** argv) {
  MedianFinder* obj = new MedianFinder();
  obj->addNum(num);
  double param_2 = obj->findMedian();
  return 0;
}
