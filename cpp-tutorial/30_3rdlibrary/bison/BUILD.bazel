load("@bazel_skylib//rules:build_test.bzl", "build_test")


exports_files(
    [
        "bison.BUILD",
    ],
    visibility = ["//visibility:public"],
)

build_test(
    name = "build_test",
    targets = [
        "@org_gnu_bison//:bison",
    ],
    visibility = ["//:__pkg__"],
)
