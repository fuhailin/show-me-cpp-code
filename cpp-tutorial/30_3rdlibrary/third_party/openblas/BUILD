load("@bazel_skylib//rules:build_test.bzl", "build_test")

exports_files(
    [
        "openblas.BUILD",
    ],
    visibility = ["//visibility:public"],
)

build_test(
    name = "build_test",
    targets = [
        "@openblas//:openblas",
    ],
    visibility = ["//:__pkg__"],
)
