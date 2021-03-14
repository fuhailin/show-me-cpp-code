"""A module defining the third party dependency m4"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def m4_repo():
    maybe(
        http_archive,
        name = "org_gnu_m4",
        urls = [
            "https://ftp.gnu.org/gnu/m4/m4-1.4.18.tar.gz",
        ],
        strip_prefix = "m4-1.4.18",
        build_file = Label("//m4:m4.BUILD"),
        patch_args = ["-p1"],
        patches = ["//m4:m4.patch"],
    )