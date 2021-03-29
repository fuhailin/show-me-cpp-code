"""A module defining the third party dependency bison"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo():
    maybe(
        http_archive,
        name = "org_gnu_bison",
        urls = [
            "https://ftp.gnu.org/gnu/bison/bison-3.5.tar.gz",
            "https://mirror.bazel.build/ftp.gnu.org/gnu/bison/bison-3.5.tar.gz",
        ],
        strip_prefix = "bison-3.5",
        build_file = Label("//third_party/bison:bison.BUILD"),
    )
