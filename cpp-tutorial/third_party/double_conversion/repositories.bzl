load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo(COMMIT = "3.1.5"):
    maybe(
        http_archive,
        name = "com_github_google_double_conversion",
        urls = [
            "https://github.com/google/double-conversion/archive/v{}.tar.gz".format(COMMIT),
        ],
        strip_prefix = "double-conversion-" + COMMIT,
    )
