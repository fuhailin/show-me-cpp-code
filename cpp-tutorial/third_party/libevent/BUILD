load("@bazel_skylib//rules:build_test.bzl", "build_test")

exports_files(
    [
        "libevent.BUILD",
    ],
    visibility = ["//visibility:public"],
)

build_test(
    name = "build_test",
    targets = [
        "@libevent//:libevent",
    ],
    visibility = ["//:__pkg__"],
)


# bazel build build_test --verbose_failures --sandbox_debug --cpu=darwin