load("@bazel_skylib//rules:build_test.bzl", "build_test")

build_test(
    name = "build_test",
    targets = [
        "@oneTBB//:tbb",
    ],
    visibility = ["//:__pkg__"],
)

cc_binary(
    name = "Demo",
    srcs = ["main.cpp"],
    deps = ["@oneTBB//:tbb"],
)
