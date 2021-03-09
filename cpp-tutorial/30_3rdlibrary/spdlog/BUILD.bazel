load("@bazel_skylib//rules:build_test.bzl", "build_test")

exports_files(
    [
        "spdlog.BUILD",
    ],
    visibility = ["//visibility:public"],
)

build_test(
    name = "build_test",
    targets = [
        "@spdlog//:spdlog",
    ],
    visibility = ["//:__pkg__"],
)
