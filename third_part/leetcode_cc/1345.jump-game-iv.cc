#include <iostream>
#include <queue>
#include <type_traits>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
 public:
  int minJumps(vector<int>& arr) {
    // 可以看成一张无向图，每个元素与它相邻的元素相连，同时还与它值相同的元素相连
    // 使用BFS从0搜索到n-1即可
    unordered_map<int, vector<int>> _map;
    for (int i = arr.size() - 1; i >= 0; i--) {
      _map[arr[i]].push_back(i);
    }
    //   BFS使用的队列
    queue<int> que;
    int ans = 0;
    // 无向图需要记录访问过的节点
    vector<bool> visited(arr.size());
    que.push(0);  // 从0节点开始访问
    visited[0] = true;
    while (!que.empty()) {
      // 与二叉树的层序遍历类似
      int size = que.size();
      for (int i = 0; i < size; i++) {
        int index = que.front();
        que.pop();

        // 满足条件，直接返回
        if (index == arr.size() - 1) {
          return ans;
        }

        // 把它相边的直接入队
        if (_map.find(arr[index]) != _map.end()) {
          for (int next : _map[arr[index]]) {
            if (index != next && !visited[next]) {
              que.push(next);
              visited[next] = true;
            }
          }
          // 剪枝：这个元素相连的都处理过了，后面再遍历到再处理肯定都已经访问过了，不如直接移除，可以减少遍历的次数
          _map.erase(arr[index]);
        }

        if (index + 1 <= arr.size() - 1 && !visited[index + 1]) {
          que.push(index + 1);
          visited[index + 1] = true;
        }
        if (index - 1 >= 0 && !visited[index - 1]) {
          que.push(index - 1);
          visited[index - 1] = true;
        }
      }
      ans++;
    }
    return -1;
  }
};

int main(int argc, const char** argv) {
  Solution so;
  vector<int> test = {100, -23, -23, 404, 100, 23, 23, 23, 3, 404};
  int res = so.minJumps(test);
  cout << "res: " << res << endl;
  return 0;
}