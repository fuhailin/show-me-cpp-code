"""A module defining the third party dependency bzip2"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo():
    maybe(
        http_archive,
        name = "bzip2",
        urls = [
            "https://www.sourceware.org/pub/bzip2/bzip2-latest.tar.gz",
            "https://sourceware.org/pub/bzip2/bzip2-1.0.8.tar.gz",
            ],
        strip_prefix = "bzip2-1.0.8",
        build_file = Label("//third_party/bzip2:bzip2.BUILD"),
    )
