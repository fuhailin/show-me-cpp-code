load("@bazel_skylib//rules:build_test.bzl", "build_test")
load("@rules_cc//cc:defs.bzl", "cc_binary")

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

cc_binary(
    name = "test",
    srcs = [
        "cityhash-example.cc",
    ],
    copts = [
        "-std=gnu++17",
    ],
    linkopts = [
        "-lstdc++",
        # "-static",
    ],
    deps = [
        "@cityhash",
    ],
)
