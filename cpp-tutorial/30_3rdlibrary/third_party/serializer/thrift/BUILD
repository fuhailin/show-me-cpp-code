load("@bazel_skylib//rules:build_test.bzl", "build_test")

exports_files(
    [
        "thrift.BUILD",
    ],
    visibility = ["//visibility:public"],
)

build_test(
    name = "build_test",
    targets = [
        "@apache_thrift//:thrift",
    ],
)
