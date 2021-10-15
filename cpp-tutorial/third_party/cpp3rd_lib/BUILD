load("@bazel_skylib//rules:build_test.bzl", "build_test")

build_test(
    name = "build_test",
    targets = [
        "@cpp3rd_lib//zk_client",
        "@cpp3rd_lib//tensorflow:tensorflow_cc",
        "@cpp3rd_lib//tensorflow:tensorflow_framework",
    ],
    visibility = ["//:__pkg__"],
)
