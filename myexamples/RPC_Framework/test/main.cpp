#include <iostream>

#include "myexamples/RPC_Framework/test/test.pb.h"

using namespace std;
using namespace ik;

int main() {
    LoginResponse login_rsp;
    ErrorMsg *error_msg = login_rsp.mutable_error();
    error_msg->set_error(1);
    error_msg->set_error_msg("login error");

    GetFriendListResponse friend_rsp;
    ErrorMsg *friend_msg = friend_rsp.mutable_error();
    friend_msg->set_error(1);
    friend_msg->set_error_msg("get friend list error");

    User *user1 = friend_rsp.add_friendlists();
    user1->set_name("zhang san");
    user1->set_age(20);
    user1->set_sex(User::man);

    cout << "has friends: " << friend_rsp.friendlists_size() << endl;
}
