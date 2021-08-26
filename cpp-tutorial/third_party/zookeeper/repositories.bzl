"""A module defining the third party dependency zookeeper"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo(COMMIT = "0.2.3"):
    maybe(
        http_archive,
        name = "Apache_ZooKeeper",
        urls = [
            "https://github.com/tgockel/zookeeper-cpp/archive/refs/tags/v{}.tar.gz".format(COMMIT),
        ],
        strip_prefix = "zookeeper-cpp-" + COMMIT,
        build_file = Label("//third_party/zookeeper:zookeeper.BUILD"),
    )
