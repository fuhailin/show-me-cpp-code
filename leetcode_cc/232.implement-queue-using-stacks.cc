#include <stack>
using namespace std;

class MyQueue {
    stack<int> stk1, stk2;
public:
    MyQueue() {

    }

    void push(int x) {
        stk1.push(x);
    }

    int pop() {
        int res = -1;
        if(stk2.empty()){
            while (!stk1.empty()) {
                stk2.push(stk1.top());
                stk1.pop();
            }
            res = stk2.top();
            stk2.pop();
        } else {
            res = stk2.top();
            stk2.pop();
        }
        return res;
    }

    int peek() {
        int res = -1;
        if(stk2.empty()){
            while (!stk1.empty()) {
                stk2.push(stk1.top());
                stk1.pop();
            }
            res = stk2.top();
        } else {
            res = stk2.top();
        }
        return res;
    }

    bool empty() {
        return stk1.empty() && stk2.empty();
    }
};

int main(int argc, char const* argv[]) {
    MyQueue* obj = new MyQueue();
    obj->push(x);
    int param_2 = obj->pop();
    int param_3 = obj->peek();
    bool param_4 = obj->empty();
    return 0;
}
