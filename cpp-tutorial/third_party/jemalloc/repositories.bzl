"""A module defining the third party dependency jemalloc"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo():
    COMMIT = "5.2.1"
    maybe(
        http_archive,
        name = "jemalloc",
        urls = [
            "https://github.com.cnpmjs.org/jemalloc/jemalloc/archive/{commit}.tar.gz".format(commit = COMMIT),
            "https://github.com/jemalloc/jemalloc/archive/{commit}.tar.gz".format(commit = COMMIT),
        ],
        strip_prefix = "jemalloc-" + COMMIT,
        build_file = Label("//third_party/jemalloc:jemalloc.BUILD"),
    )
