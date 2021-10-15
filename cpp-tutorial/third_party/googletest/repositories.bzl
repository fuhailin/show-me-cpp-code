"""A module defining the third party dependency googletest"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo(COMMIT = "1.11.0"):
    maybe(
        http_archive,
        name = "com_google_googletest",
        urls = [
            "https://github.com/google/googletest/archive/refs/tags/release-{}.tar.gz".format(COMMIT),
        ],
        strip_prefix = "googletest-release-" + COMMIT,
    )
