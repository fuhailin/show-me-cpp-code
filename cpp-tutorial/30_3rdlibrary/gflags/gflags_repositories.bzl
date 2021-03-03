"""A module defining the third party dependency gflags"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def gflags_repositories():
    maybe(
        http_archive,
        name = "com_github_gflags_gflags",
        urls = [
            "https://github.com.cnpmjs.org/gflags/gflags/archive/v2.2.2.tar.gz",
            "https://github.com/gflags/gflags/archive/v2.2.2.tar.gz",
        ],
        strip_prefix = "gflags-2.2.2",
    )
