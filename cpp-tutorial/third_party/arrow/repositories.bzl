"""A module defining the third party dependency arrow"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo(commit = "5.0.0"):
    maybe(
        http_archive,
        name = "apache_arrow",
        urls = [
            "https://github.com.cnpmjs.org/apache/arrow/archive/refs/tags/apache-arrow-{}.tar.gz".format(commit),
            "https://github.com/apache/arrow/archive/refs/tags/apache-arrow-{}.tar.gz".format(commit),
        ],
        strip_prefix = "arrow-apache-arrow-{}".format(commit),
        build_file = Label("//third_party/arrow:arrow.BUILD"),
    )
