"""A module defining the third party dependency kafka"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo(COMMIT = "1.8.2"):
    maybe(
        http_archive,
        name = "librdkafka",
        urls = [
            "https://github.com/edenhill/librdkafka/archive/refs/tags/v{}.tar.gz".format(COMMIT),
        ],
        strip_prefix = "librdkafka-" + COMMIT,
        build_file = Label("//third_party/kafka:kafka.BUILD"),
    )
