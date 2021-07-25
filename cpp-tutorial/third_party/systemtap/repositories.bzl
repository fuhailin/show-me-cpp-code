load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo(COMMIT = "4.2"):
    maybe(
        http_archive,
        name = "systemtap",
        urls = [
            "https://sourceware.org/systemtap/ftp/releases/systemtap-{}.tar.gz".format(COMMIT),
        ],
        strip_prefix = "systemtap-" + COMMIT,
        build_file = Label("//third_party/systemtap:systemtap.BUILD"),
    )
