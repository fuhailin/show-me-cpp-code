"""A module defining the third party dependency openblas"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo():
    maybe(
        http_archive,
        name = "eigen",
        urls = [
            "https://gitlab.com/libeigen/eigen/-/archive/3.3.9/eigen-3.3.9.tar.gz",
            "https://3rdcpp-1256340525.cos.ap-beijing.myqcloud.com/eigen-3.3.9.tar.gz",
        ],
        type = "tar.gz",
        strip_prefix = "eigen-3.3.9",
        build_file = Label("//third_party/eigen:eigen.BUILD"),
    )
