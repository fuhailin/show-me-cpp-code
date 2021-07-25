"""A module defining the third party dependency PCRE"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo():
    maybe(
        http_archive,
        name = "pcre",
        build_file = Label("//third_party/pcre:pcre.BUILD"),
        strip_prefix = "pcre-8.43",
        urls = [
            "https://ftp.pcre.org/pub/pcre/pcre-8.43.tar.gz",
            "https://mirror.bazel.build/ftp.pcre.org/pub/pcre/pcre-8.43.tar.gz",
        ],
    )
