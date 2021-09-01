load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo(commit = "1.0.9"):
    maybe(
        http_archive,
        name = "brotli",
        urls = [
            "https://github.com.cnpmjs.org/google/brotli/archive/v{}.tar.gz".format(commit),
            "https://github.com/google/brotli/archive/v{}.tar.gz".format(commit),
        ],
        strip_prefix = "brotli-{}".format(commit),
        build_file = Label("//third_party/brotli:brotli.BUILD"),
    )
