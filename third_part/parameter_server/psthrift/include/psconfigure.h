/*
 * @Company: TWL
 * @Author: xue jian
 * @Email: xuejian@kanzhun.com
 * @Date: 2019-09-11 14:54:14
 * @LastEditTime: 2019-11-20 17:34:20
 */
#ifndef PSCONFIGURE_H
#define PSCONFIGURE_H


#include <fstream>
#include <iostream>
#include <unordered_map>
#include <string>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
// #include "feature_handler.h"
#include "nlohmann/json.hpp"
#include "logger.hpp"
#include "config.h"
using json = nlohmann::json;
using std::string;
using std::to_string;
using std::pair;

namespace ps{
    class Configure:public BaseConfig{
        private:
        std::unordered_map<std::string, std::string> options;
        void get_all_para();
        public:
        float ada_beta;
        float rmsp_beta;
        std::unordered_map<int, float> max_norm;
        std::unordered_map<int, float> learn_rate;
        std::unordered_map<int, std::string> optimazation;
        std::unordered_map<int, int> update_times;
        std::unordered_map<int, int> slot_dim;
        json meta;
        // vector<Net> nets;
        json nets;
        // string config;


        public:
        Configure(){};
        int parse(int argc, char** argv);
        int help();
        bool getnets();
        bool getthriftconf();
        bool getmeta();
        bool getthriftport(int& port);
        bool getmasterport();
        bool getslaveof();
        bool getmodelname(std::string& model_name);
        bool getthreadnum(int& num);
        bool getjsonconfig(json** zook_info);
        bool getgroupid();
        int ParseLine(std::vector<std::string> &argv) {
        return -1; // 交给父类处理
        }

        int PrintUsage() {
            //fprintf(stderr, "Usage: ./test-server [/path/to/conf.conf] [options]\n");
            return -1;
        }

        int Version() {
            return 1;
        }
    };


}






#endif