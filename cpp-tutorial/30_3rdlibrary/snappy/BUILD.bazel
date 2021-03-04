load("@bazel_skylib//rules:build_test.bzl", "build_test")

exports_files(
    [
        "snappy.BUILD",
    ],
    visibility = ["//visibility:public"],
)

build_test(
    name = "build_test",
    targets = [
        "@snappy//:snappy",
    ],
    visibility = ["//:__pkg__"],
)
