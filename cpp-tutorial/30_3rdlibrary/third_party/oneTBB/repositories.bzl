"""A module defining the third party dependency oneTBB"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo(commit = "2021.3.0"):
    maybe(
        http_archive,
        name = "oneTBB",
        urls = [
            "https://github.91chifun.workers.dev/https://github.com//oneapi-src/oneTBB/archive/refs/tags/v{commit}.tar.gz".format(commit = commit),
            "https://github.com/oneapi-src/oneTBB/archive/refs/tags/v{commit}.tar.gz".format(commit = commit),
        ],
        strip_prefix = "oneTBB-{commit}".format(commit = commit),
        # build_file = Label("BUILD.bazel"),
    )
