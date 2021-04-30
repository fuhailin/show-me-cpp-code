load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo():
    COMMIT = "af900a78d4f18db468cab28cd5af9d0b37c47058"
    maybe(
        http_archive,
        name = "double-conversion",
        urls = [
            "https://github.91chifun.workers.dev/https://github.com//google/double-conversion/archive/{commit}.tar.gz".format(commit = COMMIT),
            "https://github.com/google/double-conversion/archive/{commit}.tar.gz".format(commit = COMMIT),
        ],
        strip_prefix = "double-conversion-" + COMMIT,
    )
