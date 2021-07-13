load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo(COMMIT = "7.0.0.11"):
    maybe(
        http_archive,
        name = "ragel",
        sha256 = "08bac6ff8ea9ee7bdd703373fe4d39274c87fecf7ae594774dfdc4f4dd4a5340",
        urls = [
            "http://www.colm.net/files/ragel/ragel-{}.tar.gz".format(COMMIT),
        ],
        strip_prefix = "ragel-" + COMMIT,
        build_file = Label("//third_party/ragel:ragel.BUILD"),
    )
