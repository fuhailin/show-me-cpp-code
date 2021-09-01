load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo():
    COMMIT = "1.37.0"
    maybe(
        http_archive,
        name = "com_github_grpc_grpc",
        urls = [
            "https://github.com/grpc/grpc/archive/v{commit}.tar.gz".format(commit = COMMIT),
        ],
        strip_prefix = "grpc-" + COMMIT,
    )
