cc_test(
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
