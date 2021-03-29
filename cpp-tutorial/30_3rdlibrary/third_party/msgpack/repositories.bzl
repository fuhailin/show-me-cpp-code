"""A module defining the third party dependency msgpack"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo():
    MSGPACK_COMMIT = "1e4fd94b90d38167b8b5a0ecf57f59b538669574"
    MSGPACK_SHA256 = "..."
    maybe(
        http_archive,
        name = "msgpack",
        urls = [
            "https://github.com.cnpmjs.org/msgpack/msgpack/archive/{commit}.tar.gz".format(commit = MSGPACK_COMMIT),
            "https://github.com/msgpack/msgpack/archive/{commit}.tar.gz".format(commit = MSGPACK_COMMIT),
        ],
        strip_prefix = "msgpack-" + MSGPACK_COMMIT,
        build_file = Label("//msgpack:msgpack.BUILD"),
    )
