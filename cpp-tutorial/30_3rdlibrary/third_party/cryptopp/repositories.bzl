load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo(COMMIT = "8_2_0"):
    maybe(
        http_archive,
        name = "cryptopp",
        urls = [
            "https://github.com.cnpmjs.org/weidai11/cryptopp/archive/CRYPTOPP_{commit}.tar.gz".format(commit = COMMIT),
        ],
        strip_prefix = "cryptopp-CRYPTOPP_" + COMMIT,
        build_file = Label("//third_party/cryptopp:cryptopp.BUILD"),
    )
