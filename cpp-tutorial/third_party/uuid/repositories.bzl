load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo(COMMIT = "2.35.1"):
    maybe(
        http_archive,
        name = "uuid",
        urls = [
            "https://mirrors.edge.kernel.org/pub/linux/utils/util-linux/v2.35/util-linux-{}.tar.gz".format(COMMIT),
        ],
        strip_prefix = "util-linux-" + COMMIT,
        build_file = Label("//third_party/uuid:uuid.BUILD"),
    )
