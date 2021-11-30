#include <limits.h>

#include <string>
#include <unordered_map>
using namespace std;

class Solution {
   public:
    unordered_map<char, int> window_map, t_map;
    bool check() {  // 判断窗口中是否全包含 t 中所有字符
        for (const auto& p : t_map) {
            if (window_map[p.first] < p.second) {
                return false;
            }
        }
        return true;
    }
    string minWindow(string s, string t) {
        for (const auto& c : t) {  // 统计 t 中字符
            ++t_map[c];
        }
        int len = INT_MAX, left = 0, ansLeft = -1;  // ansLeft 存储可行窗口的左指针索引，len 为可行窗口的长度
        for (int right = 0; right < s.size(); right++) {
            if (t_map.find(s[right]) != t_map.end()) {  // 若右指针移动 1 个单位后增加的字符存在 t 中则增加到 window_map 中
                window_map[s[right]]++;
            }
            while (check() && left <= right) {  // 当前窗口包含了 t 中全部字符，开始移动左指针
                if (right - left + 1 < len) {   // 当前窗口比上次的窗口小，记录
                    len = right - left + 1;
                    ansLeft = left;
                }
                if (t_map.find(s[left]) != t_map.end()) {  // t 包含左指针指的字符，更新 window_map
                    --window_map[s[left]];
                }
                ++left;  // 左指针移动
            }
        }
        return len == INT_MAX ? string() : s.substr(ansLeft, len);
    }
};