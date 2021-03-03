"""A module defining the third party dependency abseil"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def abseil_repositories():
    maybe(
        http_archive,
        name = "com_google_absl",
        urls = [
            "https://github.com/abseil/abseil-cpp/archive/20200923.3.tar.gz",
            "https://github.91chifun.workers.dev/https://github.com//abseil/abseil-cpp/archive/20200923.3.tar.gz",
        ],
        strip_prefix = "abseil-cpp-20200923.3",
    )