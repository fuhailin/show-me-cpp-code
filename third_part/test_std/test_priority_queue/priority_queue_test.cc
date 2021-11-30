#include <algorithm>
#include <iostream>
#include <queue>

class Solution {
   private:
    //方法1
    struct tmp1  //运算符重载<
    {
        int x;
        tmp1(int a) { x = a; }
        bool operator<(tmp1 const& a) const {
            return x < a.x;  //大顶堆
        }
    };

    //方法2
    struct tmp2  //重写仿函数
    {
        bool operator()(tmp1 const& a, tmp1 const& b) const {
            return a.x < b.x;  //大顶堆
        }
    };

   public:
    void priority_queue_test() {
        //对于基础类型 默认是大顶堆
        std::priority_queue<int> a;
        //等同于 priority_queue<int, vector<int>, less<int> > a;

        std::priority_queue<int, std::vector<int>, std::greater<int> > c;  //这样就是小顶堆
        std::priority_queue<std::string> b;

        for (int i = 0; i < 5; i++) {
            a.emplace(i);
            c.push(i);
        }
        while (!a.empty()) {
            std::cout << a.top() << ' ';
            a.pop();
        }
        std::cout << std::endl;

        while (!c.empty()) {
            std::cout << c.top() << ' ';
            c.pop();
        }
        std::cout << std::endl;

        b.emplace("abc");
        b.emplace("abcd");
        b.emplace("cbd");
        while (!b.empty()) {
            std::cout << b.top() << ' ';
            b.pop();
        }
        std::cout << std::endl;
    }

    void priority_queue_test1() {
        tmp1 a(1);
        tmp1 b(2);
        tmp1 c(3);
        std::priority_queue<tmp1> d;
        d.push(b);
        d.push(c);
        d.push(a);
        while (!d.empty()) {
            std::cout << d.top().x << '\n';
            d.pop();
        }
        std::cout << std::endl;
    }

    void priority_queue_test2() {
        tmp1 a(1);
        tmp1 b(2);
        tmp1 c(3);

        std::priority_queue<tmp1, std::vector<tmp1>, tmp2> f;
        f.push(c);
        f.push(b);
        f.push(a);
        while (!f.empty()) {
            std::cout << f.top().x << '\n';
            f.pop();
        }
    }
};

int main(int argc, const char** argv) {
    Solution s;
    {
        s.priority_queue_test();
        s.priority_queue_test1();
    }
    return 0;
}