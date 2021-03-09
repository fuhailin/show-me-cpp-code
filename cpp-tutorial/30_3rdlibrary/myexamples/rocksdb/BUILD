cc_test(
    name = "simple_example",
    srcs = [
        "simple_example.cc",
    ],
    deps = [
        "@rocksdb",
    ],
)

cc_test(
    name = "rocksdb_test",
    srcs = [
        "RocksDbTest.cpp",
    ],
    deps = [
        "@com_google_googletest//:gtest",
        "@com_google_googletest//:gtest_main",
        "@rocksdb",
    ],
)
