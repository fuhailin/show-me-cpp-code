load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo(COMMIT = "2021.08.30.00"):
    maybe(
        http_archive,
        name = "com_github_facebook_folly",
        urls = [
            "https://github.com/facebook/folly/archive/refs/tags/v{}.tar.gz".format(COMMIT),
        ],
        strip_prefix = "folly-" + COMMIT,
        build_file = Label("//third_party/folly:folly.BUILD"),
    )
