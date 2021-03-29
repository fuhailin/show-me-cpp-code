"""A module defining the third party dependency curl"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo():
    maybe(
        http_archive,
        name = "curl",
        urls = [
            "https://curl.se/download/curl-7.74.0.tar.gz",
            "https://github.com/curl/curl/releases/download/curl-7_74_0/curl-7.74.0.tar.gz",
        ],
        strip_prefix = "curl-7.74.0",
        build_file = Label("//third_party/curl:curl.BUILD"),
    )
