load("@bazel_skylib//rules:build_test.bzl", "build_test")

exports_files(
    [
        "brotli.BUILD",
    ],
    visibility = ["//visibility:public"],
)

build_test(
    name = "build_test",
    targets = [
        "@brotli//:brotli",
    ],
    visibility = ["//:__pkg__"],
)
