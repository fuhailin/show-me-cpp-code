load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo(COMMIT = "0.13.0.6"):
    maybe(
        http_archive,
        name = "colm",
        sha256 = "4644956dd82bedf3795bb1a6fdf9ee8bdd33bd1e7769ef81ffdaa3da70c5a349",
        urls = [
            "http://www.colm.net/files/colm/colm-{}.tar.gz".format(COMMIT),
        ],
        strip_prefix = "colm-" + COMMIT,
        build_file = Label("//third_party/colm:colm.BUILD"),
    )
