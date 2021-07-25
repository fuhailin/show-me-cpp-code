load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo(COMMIT = "1.0.18"):
    maybe(
        http_archive,
        name = "sctp",
        urls = [
            "https://github.com.cnpmjs.org/sctp/lksctp-tools/archive/v{commit}.tar.gz".format(commit = COMMIT),
        ],
        strip_prefix = "lksctp-tools-" + COMMIT,
        build_file = Label("//third_party/sctp:sctp.BUILD"),
    )
