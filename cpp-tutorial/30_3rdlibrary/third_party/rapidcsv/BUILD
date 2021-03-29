load("@bazel_skylib//rules:build_test.bzl", "build_test")
load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

exports_files(
    [
        "rapidcsv.BUILD",
    ],
    visibility = ["//visibility:public"],
)

build_test(
    name = "build_test",
    targets = [
        "@rapidcsv//:rapidcsv",
    ],
    visibility = ["//:__pkg__"],
)

cc_binary(
    name = "test1",
    srcs = ["ex001.cpp"],
    deps = [
        "@d99kris_rapidcsv//:rapidcsv",
    ],
)
