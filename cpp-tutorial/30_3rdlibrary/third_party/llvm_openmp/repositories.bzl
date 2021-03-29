"""A module defining the third party dependency llvm_openmp"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo():
    maybe(
        http_archive,
        name = "llvm_openmp",
        urls = [
            "https://3rdcpp-1256340525.cos.ap-beijing.myqcloud.com/openmp-10.0.1.src.tar.xz",
            "https://storage.googleapis.com/mirror.tensorflow.org/github.com/llvm/llvm-project/releases/download/llvmorg-10.0.1/openmp-10.0.1.src.tar.xz",
            "https://github.com/llvm/llvm-project/releases/download/llvmorg-10.0.1/openmp-10.0.1.src.tar.xz",
        ],
        strip_prefix = "openmp-10.0.1.src",
        build_file = Label("//llvm_openmp:llvm_openmp.BUILD"),
    )
