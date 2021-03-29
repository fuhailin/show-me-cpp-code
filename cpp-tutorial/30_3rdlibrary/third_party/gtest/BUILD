load("@bazel_skylib//rules:build_test.bzl", "build_test")

build_test(
    name = "build_test",
    targets = [
        "@com_google_googletest//:gtest",
        "@com_google_googletest//:gtest_main",
    ],
    visibility = ["//:__pkg__"],
)

cc_test(
    name = "bazel_test",
    srcs = ["main.cc"],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        "@com_google_googletest//:gtest_main",
    ],
)
