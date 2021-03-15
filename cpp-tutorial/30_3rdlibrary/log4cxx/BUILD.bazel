load("@bazel_skylib//rules:build_test.bzl", "build_test")

exports_files(
    [
        "log4cxx.BUILD",
    ],
    visibility = ["//visibility:public"],
)

build_test(
    name = "build_test",
    targets = [
        "@apache_log4cxx//:log4cxx",
    ],
    visibility = ["//:__pkg__"],
)
