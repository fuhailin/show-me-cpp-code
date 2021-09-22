"""A module defining the third party dependency redispp"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo(COMMIT = "1.3.1"):
    maybe(
        http_archive,
        name = "redis-plus-plus",
        urls = [
            "https://github.com/sewenew/redis-plus-plus/archive/refs/tags/{commit}.tar.gz".format(commit = COMMIT),
        ],
        strip_prefix = "redis-plus-plus-" + COMMIT,
        build_file = Label("//third_party/db/redispp:redispp.BUILD"),
    )
