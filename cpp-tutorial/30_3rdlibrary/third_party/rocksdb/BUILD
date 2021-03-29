load("@bazel_skylib//rules:build_test.bzl", "build_test")

exports_files(
    [
        "rocksdb.BUILD",
    ],
    visibility = ["//visibility:public"],
)

build_test(
    name = "build_test",
    targets = [
        "@com_github_facebook_rocksdb//:rocksdb",
        # "@com_github_facebook_rocksdb//:rocksdb_tools_lib",
        # "@com_github_facebook_rocksdb//:db_stress",
    ],
    visibility = ["//:__pkg__"],
)
