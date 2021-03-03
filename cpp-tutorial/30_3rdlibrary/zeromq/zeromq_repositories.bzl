"""A module defining the third party dependency zeromq"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def zeromq_repositories():
    maybe(
        http_archive,
        name = "zeromq",
        urls = [
            "https://github.91chifun.workers.dev/https://github.com//zeromq/libzmq/releases/download/v4.3.4/zeromq-4.3.4.tar.gz",
            "https://github.com/zeromq/libzmq/releases/download/v4.3.4/zeromq-4.3.4.tar.gz",
        ],
        strip_prefix = "zeromq-4.3.4",
        build_file = Label("//zeromq:zeromq.BUILD"),
    )
