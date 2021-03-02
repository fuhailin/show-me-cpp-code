"""A module defining the third party dependency openblas"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def openblas_repositories():
    maybe(
        http_archive,
        name = "openblas",
        urls = [
            "https://github.91chifun.workers.dev/https://github.com//xianyi/OpenBLAS/releases/download/v0.3.13/OpenBLAS-0.3.13.tar.gz",
            "https://github.com/xianyi/OpenBLAS/releases/download/v0.3.13/OpenBLAS-0.3.13.tar.gz",
            # "https://github.com.cnpmjs.org/xianyi/OpenBLAS/archive/v0.3.2.tar.gz",
            # "https://github.com/xianyi/OpenBLAS/archive/v0.3.2.tar.gz"
            ],
        type = "tar.gz",
        strip_prefix = "OpenBLAS-0.3.13",
        build_file = Label("//openblas:BUILD.openblas.bazel"),
    )