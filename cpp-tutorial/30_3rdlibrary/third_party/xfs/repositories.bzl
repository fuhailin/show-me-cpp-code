"""A module defining the third party dependency abseil"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo(COMMIT = "5.5.0"):
    maybe(
        http_archive,
        name = "xfs",
        urls = [
            "https://mirrors.edge.kernel.org/pub/linux/utils/fs/xfs/xfsprogs/xfsprogs-{}.tar.xz".format(COMMIT),
        ],
        strip_prefix = "xfsprogs-" + COMMIT,
        build_file = Label("//third_party/xfs:xfs.BUILD"),
    )
