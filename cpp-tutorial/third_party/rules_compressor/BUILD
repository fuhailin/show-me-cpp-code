load("@bazel_skylib//rules:build_test.bzl", "build_test")

build_test(
    name = "build_test",
    targets = [
        "@bzip2//:bzip2",
        "@lz4//:lz4",
        "@snappy//:snappy",
        "@zlib//:zlib",
        "@org_lzma_lzma//:lzma",
        "@zstd//:zstd",
    ],
    visibility = ["//:__pkg__"],
)
