"""A module defining the third party dependency thrift"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def thrift_repo():
    thrift_version = "0.13.0"
    maybe(
        http_archive,
        name = "apache_thrift",
        urls = [
            "https://ftp.cc.uoc.gr/mirrors/apache/thrift/%s/thrift-%s.tar.gz" % (thrift_version, thrift_version),
            "https://apache.cs.utah.edu/thrift/%s/thrift-%s.tar.gz" % (thrift_version, thrift_version),
        ],
        strip_prefix = "thrift-%s" % thrift_version,
        build_file = Label("//thrift:thrift.BUILD"),
    )
