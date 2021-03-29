"""A module defining the third party dependency snappy"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo():
    COMMIT = "1.1.8"
    maybe(
        http_archive,
        name = "snappy",
        urls = [
            "https://github.91chifun.workers.dev/https://github.com//google/snappy/archive/{commit}.tar.gz".format(commit = COMMIT),
            "https://github.com/google/snappy/archive/{commit}.tar.gz".format(commit = COMMIT),
        ],
        strip_prefix = "snappy-" + COMMIT,
        build_file = Label("//snappy:snappy.BUILD"),
    )
