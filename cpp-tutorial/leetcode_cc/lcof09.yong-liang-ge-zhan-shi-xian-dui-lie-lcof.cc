#include <stack>
using namespace std;

class CQueue {
    stack<int> sa;
    stack<int> sb;

   public:
    CQueue() {
    }

    void appendTail(int value) {
        sa.push(value);
    }

    int deleteHead() {
        if (sb.empty()) {
            if (sa.empty()) {
                return -1;
            } else {
                while (!sa.empty()) {
                    sb.push(sa.top());
                    sa.pop();
                }
            }
        }
        int res = sb.top();
        sb.pop();
        return res;
    }
};

/**
 * Your CQueue object will be instantiated and called as such:
 * CQueue* obj = new CQueue();
 * obj->appendTail(value);
 * int param_2 = obj->deleteHead();
 */