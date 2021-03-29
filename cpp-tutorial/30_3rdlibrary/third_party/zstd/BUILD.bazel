load("@bazel_skylib//rules:build_test.bzl", "build_test")

exports_files(
    [
        "zstd.BUILD",
    ],
    visibility = ["//visibility:public"],
)

build_test(
    name = "build_test",
    targets = [
        "@zstd//:zstd",
    ],
    visibility = ["//:__pkg__"],
)
