/*
 * @Company: TWL
 * @Author: xue jian
 * @Email: xuejian@kanzhun.com
 * @Date: 2019-08-13 14:19:01
 */


#include "Serv.h"
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <memory>
#include <vector>
#include "MatrixRand.h"
#include <iostream>
#include <map>
#include "my_op.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace std;

ps::Configure* ps::MyOp::conf = new ps::Configure();
int main(int argc, char **argv)
{
    string tmp_port(argv[1]);

    std::cout<<"start build connection "<<log_Time()<<std::endl;
    int port(stoi(tmp_port));
    shared_ptr<TSocket> socket(new TSocket("127.0.0.1", port));
    // shared_ptr<TSocket> socket(new TSocket("172.18.39.202", port));
    shared_ptr<TTransport> transport(new TFramedTransport(socket));//for the noblockingserver
    //shared_ptr<TTransport> transport(new TBufferedTransport(socket));//for the simpleserver

    shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

    transport->open();

    ServClient client(protocol);
    std::cout<<"end build connection "<<log_Time()<<std::endl;
    // vector<Key> keys;
    std::map<Key, std::string> key_vals;
    std::set<Key> keys;
// for(int ii(0); ii<1; ++ii) {
    for(int i(0); i<1; ++i)
    {
        Key key(get_fid("xuejian", 5));
        keys.insert(key);

    }
    // cout<<"haha"<<endl;
    // vector<string> tmp;

    {
        cout<<log_Time()<<endl;
    }
    client.pull(key_vals, keys);

    for (auto it = key_vals.begin(); it != key_vals.end(); ++it) {
        std::cout<<it->first<<std::endl;
        std::vector<float> media(str2vec(it->second));
        std::cout<<"The media size is"<<media.size()<<std::endl;
        Map<MatrixXf> tmp(&media.at(0), 1, media.size());
        std::cout<<tmp<<std::endl;
    }
    // cout<<key_vals.size()<<endl;
    client.push(key_vals);
    client.pull(key_vals, keys);
    std::cout<<"============="<<std::endl;
    for (auto it = key_vals.begin(); it != key_vals.end(); ++it) {
        std::cout<<it->first<<std::endl;
        std::vector<float> media(str2vec(it->second));
        Map<MatrixXf> tmp(&media.at(0), 1, media.size());
        std::cout<<tmp<<std::endl;
    }
    cout<<log_Time()<<endl;


    return 0;
}
