load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo():
    COMMIT = "1d6510aa50075cade5ed539ee09a11a1b8d7f990"
    maybe(
        http_archive,
        name = "com_github_brpc",
        urls = [
            "https://github.com.cnpmjs.org/apache/incubator-brpc/archive/{commit}.tar.gz".format(commit = COMMIT),
            "https://github.com/apache/incubator-brpc/archive/{commit}.tar.gz".format(commit = COMMIT),
        ],
        strip_prefix = "incubator-brpc-" + COMMIT,
    )
