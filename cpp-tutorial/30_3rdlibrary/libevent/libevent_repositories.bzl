"""A module defining the third party dependency libevent"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def libevent_repositories():
    maybe(
        http_archive,
        name = "libevent",
        urls = [
            "https://github.91chifun.workers.dev/https://github.com//libevent/libevent/releases/download/release-2.1.12-stable/libevent-2.1.12-stable.tar.gz",
            "https://github.com/libevent/libevent/releases/download/release-2.1.12-stable/libevent-2.1.12-stable.tar.gz",
            # "https://github.com/libevent/libevent/releases/download/release-2.1.8-stable/libevent-2.1.8-stable.tar.gz",
            # "https://mirror.bazel.build/github.com/libevent/libevent/releases/download/release-2.1.8-stable/libevent-2.1.8-stable.tar.gz",
        ],
        type = "tar.gz",
        strip_prefix = "libevent-2.1.12-stable",
        build_file = Label("//libevent:libevent.BUILD"),
    )
