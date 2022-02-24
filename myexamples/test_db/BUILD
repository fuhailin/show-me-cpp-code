cc_binary(
    name = "rocketdb",
    srcs = [
        "test_rocketdb.cc",
    ],
    deps = [
        "@com_github_facebook_rocksdb//:rocksdb",
    ],
)

cc_test(
    name = "rocksdb",
    srcs = [
        "multi_processes_example.cc",
    ],
    deps = [
        "@com_github_facebook_rocksdb//:rocksdb",
    ],
)

cc_test(
    name = "leveldb",
    srcs = [
        "test_leveldb.cc",
    ],
    deps = [
        "@com_github_google_leveldb//:leveldb",
    ],
)

cc_binary(
    name = "rocksdb1",
    srcs = [
        "rocksdb-example.cpp",
    ],
    deps = [
        "@com_github_facebook_rocksdb//:rocksdb",
    ],
)

cc_binary(
    name = "rocksdb2",
    srcs = [
        "rocksdb_test1.cpp",
    ],
    deps = [
        "@com_github_facebook_rocksdb//:rocksdb",
    ],
)

cc_binary(
    name = "rocksdb_option_test",
    srcs = [
        "options_test.cc",
    ],
    deps = [
        "@com_github_facebook_rocksdb//:rocksdb",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_binary(
    name = "db_basic_test",
    srcs = [
        "db_basic_test.cc",
    ],
    deps = [
        "@com_github_facebook_rocksdb//:rocksdb",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_binary(
    name = "c_simple_example",
    srcs = [
        "c_simple_example.c",
    ],
    deps = [
        "@com_github_facebook_rocksdb//:rocksdb",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_binary(
    name = "column_families_example",
    srcs = [
        "column_families_example.cc",
    ],
    deps = [
        "@com_github_facebook_rocksdb//:rocksdb",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_binary(
    name = "compact_files_example",
    srcs = [
        "compact_files_example.cc",
    ],
    deps = [
        "@com_github_facebook_rocksdb//:rocksdb",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_binary(
    name = "compaction_filter_example",
    srcs = [
        "compaction_filter_example.cc",
    ],
    deps = [
        "@com_github_facebook_rocksdb//:rocksdb",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_binary(
    name = "optimistic_transaction_example",
    srcs = [
        "optimistic_transaction_example.cc",
    ],
    deps = [
        "@com_github_facebook_rocksdb//:rocksdb",
        "@com_google_googletest//:gtest_main",
    ],
)
