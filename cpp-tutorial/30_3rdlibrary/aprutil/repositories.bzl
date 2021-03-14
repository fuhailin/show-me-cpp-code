"""A module defining the third party dependency aprutil"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def aprutil_repo():
    maybe(
        http_archive,
        name = "apache_aprutil",
        urls = [
            "https://ftp.wayne.edu/apache//apr/apr-util-1.6.1.tar.gz",
        ],
        strip_prefix = "apr-util-1.6.1",
        build_file = Label("//aprutil:aprutil.BUILD"),
    )
