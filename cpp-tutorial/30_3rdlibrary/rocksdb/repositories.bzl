"""A module defining the third party dependency rocksdb"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def rocksdb_repo():
    COMMIT = "6.8.1"
    maybe(
        http_archive,
        name = "rocksdb",
        urls = [
            "https://github.91chifun.workers.dev/https://github.com//facebook/rocksdb/archive/v{commit}.tar.gz".format(commit = COMMIT),
            "https://github.com/facebook/rocksdb/archive/v{commit}.tar.gz".format(commit = COMMIT),
        ],
        strip_prefix = "rocksdb-" + COMMIT,
        build_file = Label("//rocksdb:rocksdb.BUILD"),
    )
