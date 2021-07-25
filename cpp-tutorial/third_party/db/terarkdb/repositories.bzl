"""A module defining the third party dependency terarkdb"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo(COMMIT = "1.3.6"):
    maybe(
        http_archive,
        name = "com_github_bytedance_terarkdb",
        urls = [
            "https://github.91chifun.workers.dev/https://github.com//bytedance/terarkdb/archive/refs/tags/v{}.tar.gz".format(COMMIT),
            "https://github.com/bytedance/terarkdb/archive/refs/tags/v{}.tar.gz".format(COMMIT),
        ],
        strip_prefix = "terarkdb-" + COMMIT,
        build_file = Label("//third_party/db/terarkdb:terarkdb.BUILD"),
    )
