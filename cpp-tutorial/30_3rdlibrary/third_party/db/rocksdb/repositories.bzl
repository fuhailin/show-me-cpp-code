"""A module defining the third party dependency rocksdb"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo(COMMIT = "6.22.1"):
    maybe(
        http_archive,
        name = "com_github_facebook_rocksdb",
        urls = [
            "https://github.91chifun.workers.dev/https://github.com//facebook/rocksdb/archive/refs/tags/v{}.tar.gz".format(COMMIT),
            "https://github.com/facebook/rocksdb/archive/refs/tags/v{}.tar.gz".format(COMMIT),
        ],
        strip_prefix = "rocksdb-" + COMMIT,
        build_file = Label("//third_party/db/rocksdb:rocksdb.BUILD"),
    )
