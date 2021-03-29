load("@bazel_skylib//rules:build_test.bzl", "build_test")
load("@rules_cc//cc:defs.bzl", "cc_binary")

exports_files(
    [
        "openblas.BUILD",
    ],
    visibility = ["//visibility:public"],
)

build_test(
    name = "openblas_build_test",
    targets = [
        "@openblas//:openblas",
    ],
    visibility = ["//:__pkg__"],
)
