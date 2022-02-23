#include <iostream>
using namespace std;

class A
{
    public:
    A(){};
    ~A(){};
    virtual void showMe()
    {
        cout << "A" << endl;
    }
};

class B:public A
{
    public:
    B(){};
    ~B(){}
    void showMe()
    {
        cout << "B" << endl;
    }
};

int main()
{
    A *p = new B;
    p->showMe();

    return 0;
    }
