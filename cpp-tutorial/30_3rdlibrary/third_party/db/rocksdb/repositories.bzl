"""A module defining the third party dependency rocksdb"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo():
    COMMIT = "6.17.3"
    maybe(
        http_archive,
        name = "com_github_facebook_rocksdb",
        urls = [
            "https://3rdcpp-1256340525.cos.ap-beijing.myqcloud.com/rocksdb-{commit}.tar.gz".format(commit = COMMIT),
            "https://github.91chifun.workers.dev/https://github.com//facebook/rocksdb/archive/v{commit}.tar.gz".format(commit = COMMIT),
            "https://github.com/facebook/rocksdb/archive/v{commit}.tar.gz".format(commit = COMMIT),
        ],
        strip_prefix = "rocksdb-" + COMMIT,
        build_file = Label("//third_party/rocksdb:rocksdb.BUILD"),
    )
