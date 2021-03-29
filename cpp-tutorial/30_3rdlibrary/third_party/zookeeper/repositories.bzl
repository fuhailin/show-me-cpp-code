"""A module defining the third party dependency zookeeper"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo():
    COMMIT = "3.6.2"
    maybe(
        http_archive,
        name = "Apache_ZooKeeper",
        urls = [
            "https://apache.osuosl.org/zookeeper/zookeeper-3.6.2/apache-zookeeper-3.6.2.tar.gz",
        ],
        strip_prefix = "apache-zookeeper-" + COMMIT,
        build_file = Label("//third_party/zookeeper:zookeeper.BUILD"),
    )
