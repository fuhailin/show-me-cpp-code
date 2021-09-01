"""A module defining the third party dependency boringssl"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo(commit = "c6d3fd1d0972d17b2b115f6b7482b62e50406f56"):
    maybe(
        http_archive,
        name = "boringssl",
        urls = [
            "https://github.com.cnpmjs.org/google/boringssl/archive/{}.zip".format(commit),
            "https://github.com/google/boringssl/archive/{}.zip".format(commit),
            "https://boringssl.googlesource.com/boringssl/+archive/{}.tar.gz".format(commit),
        ],
        strip_prefix = "boringssl-{}".format(commit),
        build_file = Label("//third_party/boringssl:boringssl.BUILD"),
        # patch_cmds = [
        #     """sed -i.bak 's/bio.c",/bio.c","src\\/decrepit\\/bio\\/base64_bio.c",/g' BUILD.generated.bzl""",
        # ],
    )
