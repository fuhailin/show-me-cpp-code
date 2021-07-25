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
    ],
    visibility = ["//:__pkg__"],
)
