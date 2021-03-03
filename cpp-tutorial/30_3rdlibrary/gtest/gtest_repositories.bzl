"""A module defining the third party dependency gtest"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def gtest_repositories():
    maybe(
        http_archive,
        name = "gtest",
        urls = [
            "https://github.com.cnpmjs.org/google/googletest/archive/release-1.7.0.zip",
            "https://github.com/google/googletest/archive/release-1.7.0.zip"
            ],
        type = "zip",
        strip_prefix = "googletest-release-1.7.0",
        build_file = Label("//gtest:BUILD.gtest.bazel"),
    )
