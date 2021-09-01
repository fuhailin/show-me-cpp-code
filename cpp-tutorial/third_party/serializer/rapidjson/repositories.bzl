"""A module defining the third party dependency rapidjson"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo(COMMIT = "00dbcf2c6e03c47d6c399338b6de060c71356464"):
    maybe(
        http_archive,
        name = "rapidjson",
        urls = [
            "https://github.com.cnpmjs.org/Tencent/rapidjson/archive/{}.tar.gz".format(COMMIT),
            "https://github.com/Tencent/rapidjson/archive/{}.tar.gz".format(COMMIT),
        ],
        strip_prefix = "rapidjson-" + COMMIT,
        build_file = Label("//third_party/serializer/rapidjson:rapidjson.BUILD"),
    )
