"""A module defining the third party dependency googletest"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo():
    COMMIT = "df7fee587d442b372ef43bd66c6a2f5c9af8c5eb"
    maybe(
        http_archive,
        name = "com_google_googletest",
        urls = [
            "https://github.91chifun.workers.dev/https://github.com//google/googletest/archive/{commit}.tar.gz".format(commit = COMMIT),
            "https://github.com/google/googletest/archive/{commit}.tar.gz".format(commit = COMMIT),
        ],
        strip_prefix = "googletest-" + COMMIT,
    )
