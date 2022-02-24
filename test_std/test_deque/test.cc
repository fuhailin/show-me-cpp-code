#include <glog/logging.h>
#include <glog/stl_logging.h>

#include <deque>
#include <iostream>

using namespace std;

int main() {
    deque<int> ideq(20);  //Create a deque ideq with 20 elements of default value 0
    deque<int>::iterator pos;
    int i;

    //使用assign()赋值  assign在计算机中就是赋值的意思
    for (i = 0; i < 20; ++i)
        ideq[i] = i;

    //输出deque
    LOG(INFO) << "输出deque中数据:";
    for (i = 0; i < 20; ++i)
        LOG(INFO) << ideq[i];

    //在头尾加入新数据
    LOG(INFO) << "在头尾加入新数据...";
    ideq.push_back(100);
    ideq.push_front(i);

    //输出deque
    LOG(INFO) << "输出deque中数据:";
    for (pos = ideq.begin(); pos != ideq.end(); pos++)
        LOG(INFO) << *pos;

    //查找
    const int FINDNUMBER = 19;
    LOG(INFO) << "查找 " << FINDNUMBER;
    pos = find(ideq.begin(), ideq.end(), FINDNUMBER);
    if (pos != ideq.end())
        LOG(INFO) << "find " << *pos << " success";
    else
        LOG(INFO) << "find failed";

    //在头尾删除数据
    LOG(INFO) << "在头尾删除数据...";
    ideq.pop_back();
    ideq.pop_front();

    //输出deque
    LOG(INFO) << "输出deque中数据:";
    for (pos = ideq.begin(); pos != ideq.end(); pos++)
        LOG(INFO) << *pos;

    return 0;
}
