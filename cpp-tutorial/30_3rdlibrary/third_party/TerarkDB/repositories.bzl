"""A module defining the third party dependency terarkdb"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo():
    COMMIT = "6.17.3"
    maybe(
        http_archive,
        name = "com_github_bytedance_terarkdb",
        urls = [
            "https://github.91chifun.workers.dev/https://github.com//bytedance/terarkdb/archive/v{commit}.tar.gz".format(commit = COMMIT),
            "https://github.com/bytedance/terarkdb/archive/v{commit}.tar.gz".format(commit = COMMIT),
        ],
        strip_prefix = "terarkdb-" + COMMIT,
        build_file = Label("//third_party/terarkdb:terarkdb.BUILD"),
    )
