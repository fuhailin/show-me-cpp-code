"""A module defining the third party dependency thrift"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo(COMMIT = "0.13.0"):
    maybe(
        http_archive,
        name = "apache_thrift",
        urls = [
            "https://mirrors.tuna.tsinghua.edu.cn/apache/thrift/{commit}/thrift-{commit}.tar.gz".format(commit = COMMIT),
            "https://apache.cs.utah.edu/thrift/{commit}/thrift-{commit}.tar.gz".format(commit = COMMIT),
        ],
        strip_prefix = "thrift-" + COMMIT,
        build_file = Label("//third_party/serializer/thrift:thrift.BUILD"),
    )
