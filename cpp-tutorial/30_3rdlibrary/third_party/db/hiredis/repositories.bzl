load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo():
    COMMIT = "dfa33e60b07c13328133a16065d88d171a2a61d4"
    maybe(
        http_archive,
        name = "hiredis",
        urls = [
            "https://github.com.cnpmjs.org/redis/hiredis/archive/{commit}.tar.gz".format(commit = COMMIT),
        ],
        strip_prefix = "hiredis-" + COMMIT,
        build_file = Label("//third_party/hiredis:hiredis.BUILD"),
    )
