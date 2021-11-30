#include <queue>

class MyStack {
    queue<int> que;
public:
    MyStack() {

    }
    
    void push(int x) {
        que.push(x);
    }
    
    int pop() {
        int res = -1;
        if(que.empty()) return res; 
        int size = que.size() - 1;
        while (size--)
        {
            que.push(que.front());
            que.pop();
        }
        res = que.front();
        que.pop();
        return res;
    }
    
    int top() {
        int res = -1;
        if(que.empty()) return res; 
        int size = que.size() - 1;
        while (size--)
        {
            que.push(que.front());
            que.pop();
        }
        res = que.front();
        que.pop();
        que.push(res);
        return res;
    }
    
    bool empty() {
        return que.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */