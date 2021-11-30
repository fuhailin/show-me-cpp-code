#include "bits/stdc++.h"

class Solution {
    unordered_set<int> memo;
    int getArea(vector<int>& rectangle) {
        return (rectangle[2] - rectangle[0]) * (rectangle[3] - rectangle[1]);
    }

    void record(int x, int y) {
        int _key = key(x, y);
        if (memo.count(_key)) {
            memo.erase(_key);
        } else {
            memo.insert(_key);
        }
    }

    int key(int x, int y) {
        // 二维坐标转一维，方便比较
        // 100000007是随便取的一个大质数
        // 这里即使溢出了也没什么问题
        return x * 100007 + y;
    }

   public:
    bool isRectangleCover(vector<vector<int>>& rectangles) {
        int bigX = INT_MAX, bigY = INT_MAX, bigA = INT_MIN, bigB = INT_MIN;
        int area = 0;

        for (auto x : rectangles) {
            bigX = min(bigX, x[0]);
            bigY = min(bigY, x[1]);
            bigA = max(bigA, x[2]);
            bigB = max(bigB, x[3]);
            area += getArea(x);

            int x1 = x[0];
            int y1 = x[1];
            int x2 = x[2];
            int y2 = x[3];

            record(x1, y1);
            record(x1, y2);
            record(x2, y1);
            record(x2, y2);
        }
        return area == ((bigA - bigX) * (bigB - bigY)) && (memo.size() == 4) && memo.count(key(bigX, bigY)) && memo.count(key(bigA, bigB)) && memo.count(key(bigX, bigB)) && memo.count(key(bigA, bigY));
    }
};