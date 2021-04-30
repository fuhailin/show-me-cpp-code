"""A module defining the third party dependency zstd"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo():
    COMMIT = "1.4.9"
    maybe(
        http_archive,
        name = "zstd",
        urls = [
            "https://github.91chifun.workers.dev/https://github.com//facebook/zstd/archive/v{commit}.tar.gz".format(commit = COMMIT),
            "https://github.com/facebook/zstd/archive/v{commit}.tar.gz".format(commit = COMMIT),
        ],
        strip_prefix = "zstd-" + COMMIT,
        build_file = Label("//third_party/zstd:zstd.BUILD"),
    )
