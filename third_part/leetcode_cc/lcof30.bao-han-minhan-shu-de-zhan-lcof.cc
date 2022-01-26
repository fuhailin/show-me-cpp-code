#include <stack>
using namespace std;

class MinStack {
    stack<int> mystack;
    stack<int> minstack;

   public:
    /** initialize your data structure here. */
    MinStack() {
    }

    void push(int x) {
        mystack.push(x);
        if (minstack.empty()) {
            minstack.push(x);
        } else {
            if (x <= minstack.top()) {
                minstack.push(x);
            }
        }
    }

    void pop() {
        if (mystack.top() == minstack.top()) {
            minstack.pop();
        }
        mystack.pop();
    }

    int top() {
        return mystack.top();
    }

    int min() {
        return minstack.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->min();
 */