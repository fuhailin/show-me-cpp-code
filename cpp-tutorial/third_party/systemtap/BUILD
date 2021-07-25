load("@bazel_skylib//rules:build_test.bzl", "build_test")

exports_files(
    [
        "systemtap.BUILD",
    ],
    visibility = ["//visibility:public"],
)

build_test(
    name = "build_test",
    targets = [
        "@systemtap//:systemtap-sdt",
    ],
)
