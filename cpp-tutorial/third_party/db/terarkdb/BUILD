load("@bazel_skylib//rules:build_test.bzl", "build_test")

exports_files(
    [
        "terarkdb.BUILD",
    ],
    visibility = ["//visibility:public"],
)

build_test(
    name = "build_test",
    targets = [
        "@com_github_bytedance_terarkdb//:terarkdb",
    ],
    visibility = ["//:__pkg__"],
)
