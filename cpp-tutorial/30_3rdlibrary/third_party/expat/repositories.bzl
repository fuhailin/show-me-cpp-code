"""A module defining the third party dependency expat"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo(commit = "2.4.1"):
    maybe(
        http_archive,
        name = "libexpat",
        urls = [
            "https://github.91chifun.workers.dev/https://github.com//libexpat/libexpat/releases/download/R_2_4_1/expat-2.4.1.tar.gz",
        ],
        strip_prefix = "expat-{commit}".format(commit = commit),
        build_file = Label("//third_party/expat:expat.BUILD"),
    )
