load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo(commit = "3.3.9"):
    maybe(
        http_archive,
        name = "eigen",
        urls = [
            "https://gitlab.com/libeigen/eigen/-/archive/{commit}/eigen-{commit}.tar.gz".format(commit = commit),
        ],
        strip_prefix = "eigen-{commit}".format(commit = commit),
        build_file = Label("//third_party/eigen:eigen.BUILD"),
    )
