"""A module defining the third party dependency log4cxx"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo():
    maybe(
        http_archive,
        name = "apache_log4cxx",
        urls = [
            "https://mirrors.tuna.tsinghua.edu.cn/apache/logging/log4cxx/0.11.0/apache-log4cxx-0.11.0.tar.gz",
        ],
        strip_prefix = "apache-log4cxx-0.11.0",
        build_file = Label("//log4cxx:log4cxx.BUILD"),
    )
