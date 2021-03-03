"""A module defining the third party dependency glog"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def glog_repositories():
    maybe(
        http_archive,
        name = "com_github_google_glog",
        urls = [
            "https://github.91chifun.workers.dev/https://github.com//google/glog/archive/v0.4.0.tar.gz",
            "https://github.com/google/glog/archive/v0.4.0.tar.gz",
        ],
        strip_prefix = "glog-0.4.0",
    )
