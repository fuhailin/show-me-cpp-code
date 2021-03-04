load("@rules_cc//cc:defs.bzl", "cc_binary")
load("@bazel_skylib//rules:build_test.bzl", "build_test")

exports_files(
    [
        "zlib.BUILD",
    ],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "zlib_usage_example",
    srcs = ["zlib-example.cpp"],
    deps = ["@zlib"],
)

sh_test(
    name = "test_zlib",
    srcs = ["test_zlib.sh"],
    data = [":zlib_usage_example"],
    visibility = ["//:__pkg__"],
)

build_test(
    name = "build_test",
    targets = [
        "@zlib//:zlib",
    ],
    visibility = ["//:__pkg__"],
)
