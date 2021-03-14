load("@bazel_skylib//rules:build_test.bzl", "build_test")

exports_files(
    [
        "expat.BUILD",
    ],
    visibility = ["//visibility:public"],
)

build_test(
    name = "build_test",
    targets = [
        "@libexpat//:expat",
    ],
    visibility = ["//:__pkg__"],
)
