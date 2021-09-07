load("@bazel_skylib//rules:build_test.bzl", "build_test")

exports_files([
    "folly-config.h",
])

build_test(
    name = "build_test",
    targets = [
        "@com_github_facebook_folly//:folly",
    ],
    visibility = ["//:__pkg__"],
)
