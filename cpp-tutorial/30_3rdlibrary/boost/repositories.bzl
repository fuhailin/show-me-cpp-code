"""A module defining the third party dependency boost"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def boost_repo():
    maybe(
        http_archive,
        name = "boost_org",
        urls = [
            "https://dl.bintray.com/boostorg/release/1.75.0/source/boost_1_75_0.tar.gz",
        ],
        strip_prefix = "boost_1_75_0",
        build_file = Label("//boost:boost.BUILD"),
    )
