"""A module defining the third party dependency protobuf"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo(COMMIT = "3.17.3"):
    maybe(
        http_archive,
        name = "com_google_protobuf",
        urls = [
            "https://github.com/protocolbuffers/protobuf/releases/download/v{commit}/protobuf-cpp-{commit}.tar.gz".format(commit = COMMIT),
        ],
        strip_prefix = "protobuf-" + COMMIT,
    )
