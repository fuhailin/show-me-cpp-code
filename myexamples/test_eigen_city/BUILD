load("@rules_cc//cc:defs.bzl", "cc_binary")

package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "test1",
    srcs = ["test1.cpp"],
    deps = [
        # "@eigen",
        "@eigen_archive//:eigen3",
    ],
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        # "@eigen",
        "@eigen_archive//:eigen3",
    ],
)

cc_binary(
    name = "test",
    srcs = ["test.cpp"],
    deps = [
        # "@eigen",
        "@eigen_archive//:eigen3",
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
