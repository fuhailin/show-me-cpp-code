load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo():
    COMMIT = "8.0.1"
    maybe(
        http_archive,
        name = "com_github_fmtlib_fmt",
        urls = [
            "https://github.com/fmtlib/fmt/archive/refs/tags/{commit}.tar.gz".format(commit = COMMIT),
        ],
        strip_prefix = "fmt-" + COMMIT,
        build_file = Label("//third_party/fmt:fmt.BUILD"),
    )
