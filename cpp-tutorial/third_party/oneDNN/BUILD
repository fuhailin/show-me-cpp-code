load("@bazel_skylib//rules:build_test.bzl", "build_test")

exports_files(
    [
        "oneDNN.BUILD",
    ],
    visibility = ["//visibility:public"],
)

build_test(
    name = "build_test",
    targets = [
        "@oneDNN//:mkldnn",
    ],
    visibility = ["//:__pkg__"],
)
