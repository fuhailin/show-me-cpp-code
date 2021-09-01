load("@bazel_skylib//rules:build_test.bzl", "build_test")

exports_files(
    [
        "rapidjson.BUILD",
    ],
    visibility = ["//visibility:public"],
)

build_test(
    name = "build_test",
    targets = [
        "@rapidjson//:rapidjson",
    ],
    visibility = ["//:__pkg__"],
)
