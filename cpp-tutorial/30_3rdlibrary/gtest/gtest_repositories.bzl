"""A module defining the third party dependency googletest"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def gtest_repositories():
    maybe(
        http_archive,
        name = "com_google_googletest",
        urls = [
            "https://github.91chifun.workers.dev/https://github.com//google/googletest/archive/v1.10.x.zip",
            "https://github.com/google/googletest/archive/v1.10.x.tar.gz",
            ],
        strip_prefix = "googletest-1.10.x",
        build_file = Label("//gtest:gtest.BUILD"),
    )