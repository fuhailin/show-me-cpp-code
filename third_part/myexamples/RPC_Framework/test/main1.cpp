#include <iostream>

#include "myexamples/RPC_Framework/test/test.pb.h"

using namespace std;
using namespace ik;

#if 0
int main()
{
    LoginRequest req;
    req.set_name("zhangsan");
    req.set_password("123456");

    //序列化
    string str_req;
    if(req.SerializeToString(&str_req))
    {
        cout << "after serialize" << str_req << endl;
    }

    //反序列化
    LoginRequest new_req;
    if(!new_req.ParseFromString(str_req))
    {
        cout<<"unserialize error!"<<endl;
    }
    else
    {
        cout<<"unserialize success"<<endl;
        cout<<"name: "<<new_req.name()<<" password: "<<new_req.password()<<endl;
    }

    return 0;
}
#endif
