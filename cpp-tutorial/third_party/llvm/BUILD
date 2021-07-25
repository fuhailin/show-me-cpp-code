load("@bazel_skylib//rules:build_test.bzl", "build_test")

exports_files(
    [
        "llvm.BUILD",
    ],
    visibility = ["//visibility:public"],
)

build_test(
    name = "build_test",
    targets = [
        "@org_llvm_llvm//:llvm",
    ],
    visibility = ["//:__pkg__"],
)
