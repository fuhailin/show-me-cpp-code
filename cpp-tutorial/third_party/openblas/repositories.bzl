"""A module defining the third party dependency openblas"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo(commit = "0.3.16"):
    maybe(
        http_archive,
        name = "openblas",
        urls = [
            "https://github.com/xianyi/OpenBLAS/releases/download/v{commit}/OpenBLAS-{commit}.tar.gz".format(commit = commit),
        ],
        type = "tar.gz",
        strip_prefix = "OpenBLAS-{commit}".format(commit = commit),
        build_file = Label("//third_party/openblas:openblas.BUILD"),
    )
