/*
 * @Company: TWL
 * @Author: xue jian
 * @Email: xuejian@kanzhun.com
 * @Date: 2019-08-10 15:33:30
 * @LastEditTime: 2020-05-29 10:08:00
 */



#ifndef MY_OP_H
#define MY_OP_H
#include <unordered_map>
#include <Eigen/Dense>
// #include "feature_handler.h"
// #include "MatrixRand.h"
#include "ps_util.h"
#include "time_function.h"
#include "my_server_types.h"
#include <iostream>
#include "rocksdb/db.h"
#include <cassert>
#include <string>
#include "nlohmann/json.hpp"
#include "psconfigure.h"
#include "replication.h"
#include "config.h"
#include <vector>
#include <string>
#include <math.h>
using json = nlohmann::json;


class DB: public RockServerBase {

public:
    DB(ps::Configure *conf): RockServerBase(conf) {}
};



using namespace Eigen;
// using namespace std;

namespace ps{
class MyOp
{
    private:

    //============rocksdb================
    std::unordered_map<std::string, rocksdb::ColumnFamilyHandle *> cfHandles;
    rocksdb::DB* db;
    DB* rep_b;


    std::unordered_map<int, int> fea_use_length;





    public:
    static Configure* conf;

    MyOp()
    {
        rep_b = new DB(conf);
        // db_ada = new DB(conf_ada);
        rep_b->Open0();
        // db_ada->Open0();

        for (size_t i(0); i<conf->columnFamilies.size(); ++i) {
            cfHandles.insert(std::pair<std::string, rocksdb::ColumnFamilyHandle*>(conf->columnFamilies.at(i), rep_b->cfHandles.at(i)));
        }

        db = rep_b->db;
        fea_use_length = conf->slot_dim;
        // get_use_length();




    };
    ~MyOp(){
        delete db;
        // delete ada_db;
    };

    // void push(const std::vector<Key> & keys, const std::vector<vector<double>> & Vals);
    void push(const std::map<Key, std::string>& key_vals, bool is_sync);

    void pushemb(const std::map<Key, std::string> & key_vals);

    void pushada(const std::map<Key, std::string> & key_vals);

    void pull(std::map<Key, std::string> & key_vals, const std::set<Key>& keys);

    void multi_pull(std::map<Key, std::string>&, const std::set<Key>&);

    // void pull_online(const std::vector<Key> & keys, std::vector<std::string> & Vals);
    void pull_online(std::map<Key, std::string> & Vals, const std::set<Key>& keys);


};




}

// int getport(const string& embfile);



#endif
