load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo(COMMIT = "1.0.1"):
    maybe(
        http_archive,
        name = "readerwriterqueue",
        urls = [
            "https://github.com.cnpmjs.org/cameron314/readerwriterqueue/archive/v{commit}.tar.gz".format(commit = COMMIT),
        ],
        strip_prefix = "readerwriterqueue-" + COMMIT,
        build_file = Label("//third_party/readerwriterqueue:readerwriterqueue.BUILD"),
    )
