#include <string>

#include "gtest/gtest.h"
#include "rocksdb/db.h"

using namespace std;

namespace {
const string kDbPath = "/tmp/just_for_test_db";
const string kDbKey = "test_key";
const string kDbValue = "test_value";
}  // namespace

TEST(RocksDbTest, testDb) {
    rocksdb::DB *db = nullptr;
    rocksdb::Options options;
    options.create_if_missing = true;
    rocksdb::Status status = rocksdb::DB::Open(options, kDbPath, &db);
    EXPECT_TRUE(status.ok());

    db->Put(rocksdb::WriteOptions(), kDbKey, kDbValue);

    string actualValue;
    db->Get(rocksdb::ReadOptions(), kDbKey, &actualValue);

    EXPECT_EQ(actualValue, kDbValue);

    // clean up the db
    if (status.ok()) {
        delete db;
    }
}
