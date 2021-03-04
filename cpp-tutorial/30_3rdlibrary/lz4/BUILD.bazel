load("@bazel_skylib//rules:build_test.bzl", "build_test")

exports_files(
    [
        "lz4.BUILD",
    ],
    visibility = ["//visibility:public"],
)

build_test(
    name = "build_test",
    targets = [
        "@lz4//:lz4",
        "@lz4//:lz4_hc",
    ],
    visibility = ["//:__pkg__"],
)
