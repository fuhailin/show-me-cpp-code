"""A module defining the third party dependency json"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def json_repo():
    maybe(
        http_archive,
        name = "nlohmann_json",
        urls = [
            "https://github.com/nlohmann/json/releases/download/v3.9.1/include.zip",
        ],
        build_file = Label("//json:json.BUILD"),
    )
