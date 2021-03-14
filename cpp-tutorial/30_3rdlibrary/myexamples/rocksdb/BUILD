cc_test(
    name = "simple_example",
    srcs = [
        "simple_example.cc",
    ],
    deps = [
        "@com_github_facebook_rocksdb//:rocksdb",
    ],
)

cc_test(
    name = "rocksdb_test",
    srcs = [
        "RocksDbTest.cpp",
    ],
    deps = [
        "@com_github_facebook_rocksdb//:rocksdb",
        "@com_google_googletest//:gtest",
        "@com_google_googletest//:gtest_main",
    ],
)
