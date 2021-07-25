"""A module defining the third party dependency rapidcsv"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo():
    maybe(
        http_archive,
        name = "d99kris_rapidcsv",
        urls = [
            "https://github.com/d99kris/rapidcsv/archive/v8.48.tar.gz",
        ],
        strip_prefix = "rapidcsv-8.48",
        build_file = Label("//third_party/rapidcsv:rapidcsv.BUILD"),
    )
