"""A module defining the third party dependency oneTBB"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo():
    maybe(
        http_archive,
        name = "oneTBB",
        urls = [
            "https://github.91chifun.workers.dev/https://github.com//oneapi-src/oneTBB/archive/refs/tags/v2021.2.0.tar.gz",
            "https://github.com/oneapi-src/oneTBB/archive/refs/tags/v2021.2.0.tar.gz",
            ],
        strip_prefix = "oneTBB-2021.2.0",
        build_file = Label("//third_party/oneTBB:oneTBB.BUILD"),
    )