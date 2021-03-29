"""A module defining the third party dependency rapidjson"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo():
    COMMIT = "1.1.9"
    maybe(
        http_archive,
        name = "rapidjson",
        urls = [
            "https://github.91chifun.workers.dev/https://github.com//Tencent/rapidjson/archive/v{commit}.tar.gz".format(commit = COMMIT),
            "https://github.com/Tencent/rapidjson/archive/v{commit}.tar.gz".format(commit = COMMIT),
        ],
        strip_prefix = "rapidjson-" + COMMIT,
        build_file = Label("//rapidjson:rapidjson.BUILD"),
    )
