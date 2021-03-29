"""A module defining the third party dependency boost"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo():
    maybe(
        http_archive,
        name = "boost",
        urls = [
            "https://3rdcpp-1256340525.cos.ap-beijing.myqcloud.com/boost_1_75_0.tar.gz",
        ],
        strip_prefix = "boost_1_75_0",
        build_file = Label("//third_party/boost:boost.BUILD"),
    )
