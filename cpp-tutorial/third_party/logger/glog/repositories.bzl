"""A module defining the third party dependency glog"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo():
    COMMIT = "d4e8ebab7e295f20f86cae9557da0d5087a02f73"
    maybe(
        http_archive,
        name = "com_github_google_glog",
        urls = [
            "https://github.com/google/glog/archive/{commit}.tar.gz".format(commit = COMMIT),
        ],
        strip_prefix = "glog-" + COMMIT,
    )
