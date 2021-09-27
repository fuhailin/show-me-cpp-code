load("@bazel_skylib//rules:build_test.bzl", "build_test")

exports_files(
    [
        "cityhash.BUILD",
    ],
    visibility = ["//visibility:public"],
)

build_test(
    name = "build_test",
    targets = [
        "@cityhash//:cityhash",
    ],
    visibility = ["//:__pkg__"],
)
