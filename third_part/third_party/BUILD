load("@bazel_skylib//rules:build_test.bzl", "build_test")

licenses(["notice"])  # Apache 2.0

package(default_visibility = ["//visibility:public"])

build_test(
    name = "build_test",
    targets = [
        "@zstd//:zstd",
        "@openssl//:openssl",
        "@zeromq//:libzmq",
        "@com_github_jupp0r_prometheus_cpp//pull",
    ],
    visibility = ["//:__pkg__"],
)
