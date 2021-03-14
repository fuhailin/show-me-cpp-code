"""A module defining the third party dependency pslite"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def pslite_repo():
    COMMIT = "08fb534cd1f58dd3b6a83eba44b508b0eb9a52ce"
    maybe(
        http_archive,
        name = "pslite",
        urls = [
            "https://github.91chifun.workers.dev/https://github.com//dmlc/ps-lite/archive/{commit}.tar.gz".format(commit = COMMIT),
            "https://github.com/dmlc/ps-lite/archive/{commit}.tar.gz".format(commit = COMMIT),
        ],
        strip_prefix = "ps-lite-" + COMMIT,
        build_file = Label("//pslite:pslite.BUILD"),
    )