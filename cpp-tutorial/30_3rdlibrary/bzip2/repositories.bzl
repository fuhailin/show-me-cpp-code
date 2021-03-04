"""A module defining the third party dependency bzip2"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def bzip2_repo():
    maybe(
        http_archive,
        name = "bzip2",
        urls = ["https://versaweb.dl.sourceforge.net/project/bzip2/bzip2-1.0.6.tar.gz"],
        strip_prefix = "bzip2-1.0.6",
        build_file = Label("//bzip2:bzip2.BUILD"),
    )
