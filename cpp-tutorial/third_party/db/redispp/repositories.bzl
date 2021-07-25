"""A module defining the third party dependency rocksdb"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo():
    COMMIT = "1.2.3"
    maybe(
        http_archive,
        name = "redis-plus-plus",
        urls = [
            "https://github.91chifun.workers.dev/https://github.com//sewenew/redis-plus-plus/archive/refs/tags/{commit}.tar.gz".format(commit = COMMIT),
            "https://github.com/sewenew/redis-plus-plus/archive/refs/tags/{commit}.tar.gz".format(commit = COMMIT),
        ],
        strip_prefix = "redis-plus-plus-" + COMMIT,
        build_file = Label("//third_party/rocksdb:rocksdb.BUILD"),
    )
