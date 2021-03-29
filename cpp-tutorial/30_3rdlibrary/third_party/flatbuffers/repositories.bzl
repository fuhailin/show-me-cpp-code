"""A module defining the third party dependency flatbuffers"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo():
    COMMIT = "1.12.0"
    maybe(
        http_archive,
        name = "com_github_google_flatbuffers",
        urls = [
            "https://3rdcpp-1256340525.cos.ap-beijing.myqcloud.com/flatbuffers-{commit}.tar.gz".format(commit = COMMIT),
            "https://hub.fastgit.org/google/flatbuffers/archive/v{commit}.tar.gz".format(commit = COMMIT),
            "https://github.com/google/flatbuffers/archive/v{commit}.tar.gz".format(commit = COMMIT),
        ],
        strip_prefix = "flatbuffers-" + COMMIT,
    )
