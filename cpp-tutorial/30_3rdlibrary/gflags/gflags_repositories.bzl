"""A module defining the third party dependency gflags"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def gflags_repositories():
    COMMIT = "46f73f88b18aee341538c0dfc22b1710a6abedef"
    maybe(
        http_archive,
        name = "com_github_gflags_gflags",
        urls = [
            "https://github.com.cnpmjs.org/gflags/gflags/archive/{commit}.tar.gz".format(commit = COMMIT),
            "https://github.com/gflags/gflags/archive/{commit}.tar.gz".format(commit = COMMIT),
        ],
        strip_prefix = "gflags-" + COMMIT,
    )
