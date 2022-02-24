#include <stack>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
   public:
    int evalRPN(vector<string>& tokens) {
        unordered_set<string> ops = {"+", "-", "*", "/"};
        stack<int> stk;
        for (auto& x : tokens) {
            if(ops.count(x)) {
                int a = stk.top();
                stk.pop();
                int b = stk.top();
                stk.pop();
                if (x == "+") stk.push(a + b);
                if (x == "-") stk.push(b - a);
                if (x == "*") stk.push(a * b);
                if (x == "/") stk.push(b / a);
            } else {
                /*  
                stk.push(stoi(x));
                std::stoi  string to int, 忽略非数字,会进行范围校验，溢出则error
                stoi()会做范围检查，默认范围在int范围内（因为返回的是int类型），如果超出范围的话则会runtime error！
                 */

                /* atoi()参数是 const char* 类型的，因此可以将一个字符数组转换成一个数字。
                但是如果将一个string类型的字符串转换成数字的话，
                这时我们需要先调用string类成员方法.c_str()将其转换为const char* 类型后，再进行转换。
                还需要说的一点就是，atoi()函数的返回值为int类型，代表返回将字符串转换后的数字。
                atoi()则不会做范围检查，如果超出范围的话，超出上界，则输出上界，超出下界，则输出下界。
                 */
                stk.push(atoi(token.c_str()));
            }
        }
        return stk.top();
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    vector<string> test = {"4", "13", "5", "/", "+"};
    int res = so.evalRPN(test);
    cout << res << endl;
    return 0;
}
