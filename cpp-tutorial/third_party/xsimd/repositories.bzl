"""A module defining the third party dependency xsimd"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo(COMMIT = "7.5.0"):
    maybe(
        http_archive,
        name = "xsimd",
        urls = [
            "https://github.com.cnpmjs.org/xtensor-stack/xsimd/archive/refs/tags/{}.tar.gz".format(COMMIT),
            "https://github.com/xtensor-stack/xsimd/archive/refs/tags/{}.tar.gz".format(COMMIT),
        ],
        strip_prefix = "xsimd-" + COMMIT,
        build_file = Label("//third_party/xsimd:xsimd.BUILD"),
    )
