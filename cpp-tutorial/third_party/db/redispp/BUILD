load("@bazel_skylib//rules:build_test.bzl", "build_test")

exports_files(
    [
        "redispp.BUILD",
    ],
    visibility = ["//visibility:public"],
)

build_test(
    name = "build_test",
    targets = [
        "@redis-plus-plus//:redispp",
    ],
    visibility = ["//:__pkg__"],
)
