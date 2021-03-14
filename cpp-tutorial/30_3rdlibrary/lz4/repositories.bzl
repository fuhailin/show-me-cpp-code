"""A module defining the third party dependency lz4"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def lz4_repo():
    COMMIT = "1.9.2"
    maybe(
        http_archive,
        name = "lz4",
        urls = [
            "https://github.91chifun.workers.dev/https://github.com//lz4/lz4/archive/v{commit}.tar.gz".format(commit = COMMIT),
            "https://github.com/lz4/lz4/archive/v{commit}.tar.gz".format(commit = COMMIT),
        ],
        strip_prefix = "lz4-" + COMMIT,
        build_file = Label("//lz4:lz4.BUILD"),
    )