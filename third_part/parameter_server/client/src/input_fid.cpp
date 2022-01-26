/*
 * 用法：./input_util localhost:2182 test_0316
 *       ./input_util [zk]           [model_name]
 */
#include "ps_util.h"
#include "tcmcp_psProxyServ.h"
#include <stdlib.h>
#include <string.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>
#include "nlohmann/json.hpp"
#include <vector>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;
using json = nlohmann::json;
typedef int64_t Key;

int main(int argc,char** argv){
    if (argc<4) {
        cout << "use: cmd {zk} {model_name} {file_name}\n";
        cout << " eg. ./client localhost:2181 test_tf_12345 input.json\n";
        return 0;
    }
    std::string filename(argv[3]);
    std::string mn(argv[2]);
    std::string zk(argv[1]);
    std::string path = "/psProxy/tcmcp/" + mn + "_offline";
    //auto beginTimeRead = std::chrono::high_resolution_clock::now();
    std::ifstream ifs(filename);
    if(!ifs.good())
    {
        std::cout << "ifstream open file error!\n";
        return -1;
    }

    int ret;
    std::shared_ptr<tcmcp_psProxyServClient> client(new tcmcp_psProxyServClient(zk, path, 1, 120 * 1000 * 1000));
    client->init();

    string line;
    std::map<Key, std::string> key_vals;
    while(getline(ifs, line))
    {
        json j_tmp;
        try {
            j_tmp = json::parse(line);
        } catch (const std::exception&) {
            continue;
        }
        std::vector<float> vec;
        Key fid = j_tmp["fid"].get<int64_t>();
        //std::cout << j_tmp["fid"] << "\n";
        int value_size = j_tmp["value"].size();
        for(int i=0;i<value_size;i++) {
            float value = j_tmp["value"][i].get<float>();
            vec.push_back(value);
        }

        //string fid_value = vec2str(vec);
        Map<MatrixXf> para_dict(&vec.at(0), 1, vec.size());
        string fid_value = vec2str(para_dict);
        //auto values = str2vec(fid_value);
        //for(auto value:values) cout << value;

        key_vals.insert({fid,fid_value});
        if (key_vals.size()>=2000) {
            std::cout << "pushemb size " << key_vals.size() << "\n";
            ret = client->tcmcp_pushemb(key_vals);
            if (ret!=0) {
                std::cout << "push failed, try again\n";
                return -1;
            }
            key_vals.clear();
        }
    }
    if (key_vals.size()>0) {
        ret = client->tcmcp_pushemb(key_vals);
        if (ret!=0) {
            std::cout << "push failed, try again\n";
            return -1;
        } else {
            std::cout << "pushemb size " << key_vals.size() << "\n";
        }
    }
}
