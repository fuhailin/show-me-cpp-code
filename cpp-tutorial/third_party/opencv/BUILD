load("@bazel_skylib//rules:build_test.bzl", "build_test")

exports_files(
    [
        "opencv.BUILD",
    ],
    visibility = ["//visibility:public"],
)

build_test(
    name = "build_test",
    targets = [
        "@com_github_opencv//:opencv",
    ],
    visibility = ["//:__pkg__"],
)
