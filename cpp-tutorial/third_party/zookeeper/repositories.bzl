"""A module defining the third party dependency zookeeper"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo(COMMIT = "3.5.9"):
    maybe(
        http_archive,
        name = "apache_zookeeper",
        urls = [
            "https://dlcdn.apache.org/zookeeper/zookeeper-3.5.9/apache-zookeeper-3.5.9.tar.gz",
            # "https://dlcdn.apache.org/zookeeper/zookeeper-{0}/apache-zookeeper-{0}.tar.gz".format(COMMIT),
        ],
        strip_prefix = "apache-zookeeper-" + COMMIT,
        build_file = Label("//third_party/zookeeper:zookeeper.BUILD"),
    )
