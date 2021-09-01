load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def pybind11_repo(COMMIT = "2.7.1"):
    maybe(
        http_archive,
        name = "pybind11",
        urls = [
            "https://github.com/pybind/pybind11/archive/v{}.tar.gz".format(COMMIT),
        ],
        strip_prefix = "pybind11-" + COMMIT,
        build_file = "@pybind11_bazel//:pybind11.BUILD",
    )

def pybind11_bazel_repo(COMMIT = "26973c0ff320cb4b39e45bc3e4297b82bc3a6c09"):
    maybe(
        http_archive,
        name = "pybind11_bazel",
        urls = [
            "https://github.com/pybind/pybind11_bazel/archive/{}.zip".format(COMMIT),
        ],
        strip_prefix = "pybind11_bazel-" + COMMIT,
    )
