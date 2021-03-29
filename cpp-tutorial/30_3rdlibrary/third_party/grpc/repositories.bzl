"""A module defining the third party dependency grpc"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo():
    COMMIT = "ee5b762f33a42170144834f5ab7efda9d76c480b"
    maybe(
        http_archive,
        name = "com_github_grpc_grpc",
        urls = [
            "https://hub.fastgit.org/grpc/grpc/archive/v{commit}.tar.gz".format(commit = COMMIT),
            "https://github.com/grpc/grpc/archive/v{commit}.tar.gz".format(commit = COMMIT),
        ],
        strip_prefix = "grpc-" + COMMIT,
    )
