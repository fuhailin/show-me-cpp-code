"""A module defining the third party dependency folly"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def folly_repo():
    COMMIT = "2017.09.11.00"
    maybe(
        http_archive,
        name = "com_github_facebook_folly",
        urls = [
            "https://github.91chifun.workers.dev/https://github.com//facebook/folly/archive/v{commit}.tar.gz".format(commit = COMMIT),
            "https://github.com/facebook/folly/archive/v{commit}.tar.gz".format(commit = COMMIT),
        ],
        strip_prefix = "folly-" + COMMIT,
        build_file = Label("//folly:folly.BUILD"),
    )
