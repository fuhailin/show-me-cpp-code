load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo(commit = "2.3"):
    maybe(
        http_archive,
        name = "oneDNN",
        build_file = Label("//third_party/oneDNN:oneDNN.BUILD"),
        strip_prefix = "oneDNN-" + commit,
        urls = [
            "https://github.91chifun.workers.dev/https://github.com//oneapi-src/oneDNN/archive/refs/tags/v{}.tar.gz".format(commit),
        ],
    )
