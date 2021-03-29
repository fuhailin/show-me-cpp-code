"""A module defining the third party dependency expat"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo():
    maybe(
        http_archive,
        name = "libexpat",
        urls = [
            "https://github.com/libexpat/libexpat/releases/download/R_2_2_10/expat-2.2.10.tar.gz",
        ],
        strip_prefix = "expat-2.2.10",
        build_file = Label("//third_party/expat:expat.BUILD"),
    )
