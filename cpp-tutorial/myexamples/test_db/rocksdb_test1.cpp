#include <iostream>

#include "rocksdb/db.h"

int main(int argc, char* argv[]) {
    rocksdb::DB* db;
    rocksdb::Options options;
    options.create_if_missing = true;
    rocksdb::Status status = rocksdb::DB::Open(options, "./testdb", &db);
    std::cout << "rocksb open status: " << status.ok() << std::endl;

    std::string sKey("key-one");
    std::string sValue("Value Some");

    status = db->Put(rocksdb::WriteOptions(), sKey, sValue);
    if (status.ok()) {
        std::cout << "put key ok" << std::endl;
        std::string rValue;
        rocksdb::Status s = db->Get(rocksdb::ReadOptions(), sKey, &rValue);
        if (s.ok()) {
            std::cout << "read from rocksdb success: " << rValue << std::endl;
        }
    } else {
        std::cout << "put key error, with status: " << status.code() << std::endl;
    }

    db->Close();

    return 0;
}