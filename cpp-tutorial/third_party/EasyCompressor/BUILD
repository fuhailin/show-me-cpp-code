load("@bazel_skylib//rules:build_test.bzl", "build_test")

build_test(
    name = "build_test",
    targets = [
        "@bzip2//:bzip2",
        "@lz4//:lz4",
        "@lz4//:lz4_hc",
        "@snappy//:snappy",
        "@zlib//:zlib",
    ],
    visibility = ["//:__pkg__"],
)
