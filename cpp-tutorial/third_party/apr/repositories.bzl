"""A module defining the third party dependency apr"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo():
    maybe(
        http_archive,
        name = "apache_apr",
        urls = [
            "https://ftp.wayne.edu/apache//apr/apr-1.7.0.tar.gz",
        ],
        strip_prefix = "apr-1.7.0",
        build_file = Label("//third_party/apr:apr.BUILD"),
    )
