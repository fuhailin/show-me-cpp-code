"""A module defining the third party dependency folly"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo():
    COMMIT = "2021.03.15.00"
    maybe(
        http_archive,
        name = "com_github_facebook_folly",
        urls = [
            "https://github.com.cnpmjs.org/facebook/folly/releases/download/v{commit}/folly-v{commit}.tar.gz".format(commit = COMMIT),
            "https://hub.fastgit.org/facebook/folly/releases/download/v{commit}/folly-v{commit}.tar.gz".format(commit = COMMIT),
            "https://github.com/facebook/folly/releases/download/v{commit}/folly-v{commit}.tar.gz".format(commit = COMMIT),
        ],
        strip_prefix = "folly-" + COMMIT,
        build_file = Label("//folly:folly.BUILD"),
    )
