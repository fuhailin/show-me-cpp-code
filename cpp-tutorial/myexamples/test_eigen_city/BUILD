load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "test1",
    srcs = ["test1.cpp"],
    deps = [
        "@eigen",
    ],
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        "@eigen",
    ],
)

cc_binary(
    name = "test",
    srcs = ["test.cpp"],
    deps = [
        "@eigen",
    ],
)

cc_library(
    name = "ps_util",
    srcs = ["ps_util.cpp"],
    hdrs = ["ps_util.h"],
    deps = [
        "@cityhash",
        "@eigen",
    ],
)

cc_binary(
    name = "test_city",
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
