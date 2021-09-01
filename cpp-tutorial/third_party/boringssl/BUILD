load("@bazel_skylib//rules:build_test.bzl", "build_test")

exports_files(
    [
        "boringssl.BUILD",
    ],
    visibility = ["//visibility:public"],
)

build_test(
    name = "build_test",
    targets = [
        "@boringssl//:ssl",
    ],
    visibility = ["//:__pkg__"],
)
