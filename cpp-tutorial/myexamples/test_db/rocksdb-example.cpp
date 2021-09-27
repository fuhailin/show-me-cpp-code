#include <rocksdb/db.h>

#include <cassert>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv) {
    rocksdb::DB* db;
    rocksdb::Options options;
    options.create_if_missing = true;
    rocksdb::Status status =
        rocksdb::DB::Open(options, "/tmp/testdb", &db);
    assert(status.ok());

    // Insert value
    status = db->Put(rocksdb::WriteOptions(), "Test key", "Test value = fuhailin");
    assert(status.ok());

    // Read back value
    std::string value;
    status = db->Get(rocksdb::ReadOptions(), "Test key", &value);
    cout << "value: " << value << endl;
    assert(status.ok());
    assert(!status.IsNotFound());

    // Read key which does not exist
    std::string value1;
    status = db->Get(rocksdb::ReadOptions(), "This key does not exist", &value1);
    cout << "value1: " << value1 << endl;
    assert(status.IsNotFound());
}
