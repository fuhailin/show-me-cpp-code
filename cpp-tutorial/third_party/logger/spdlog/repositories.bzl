"""A module defining the third party dependency spdlog"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo():
    COMMIT = "1.9.2"
    maybe(
        http_archive,
        name = "spdlog",
        urls = [
            "https://github.com/gabime/spdlog/archive/v{commit}.tar.gz".format(commit = COMMIT),
        ],
        strip_prefix = "spdlog-" + COMMIT,
        build_file = Label("//third_party/logger/spdlog:spdlog.BUILD"),
    )
