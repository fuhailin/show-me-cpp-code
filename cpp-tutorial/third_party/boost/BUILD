load("@bazel_skylib//rules:build_test.bzl", "build_test")

exports_files(
    [
        "boost.BUILD",
    ],
    visibility = ["//visibility:public"],
)

build_test(
    name = "build_test",
    targets = [
        "@boost//:boost",
    ],
    visibility = ["//:__pkg__"],
)
