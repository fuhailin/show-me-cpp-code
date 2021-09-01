load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo(COMMIT = "5.2.5"):
    maybe(
        http_archive,
        name = "xz",
        urls = [
            "https://github.com.cnpmjs.org/xz-mirror/xz/archive/v{}.tar.gz".format(COMMIT),
            "https://github.com/xz-mirror/xz/archive/v{}.tar.gz".format(COMMIT),
        ],
        strip_prefix = "xz-" + COMMIT,
        build_file = Label("//third_party/xz:xz.BUILD"),
    )
