"""Provides a macro to import all dependencies.

Some of the external dependencies need to be initialized. To do this, duplicate
the initialization code from WORKSPACE file.
"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def mydeps_workspace():
    """All external dependencies."""
    # pass
    http_archive(
        name = "apache_thrift_12",
        build_file = "//third_party:thrift.BUILD",
        strip_prefix = "thrift-0.12.0",
        urls = [
            "https://mirrors.tuna.tsinghua.edu.cn/apache/thrift/{commit}/thrift-{commit}.tar.gz".format(commit = "0.12.0"),
            "https://apache.cs.utah.edu/thrift/{commit}/thrift-{commit}.tar.gz".format(commit = "0.12.0"),
        ],
    )
