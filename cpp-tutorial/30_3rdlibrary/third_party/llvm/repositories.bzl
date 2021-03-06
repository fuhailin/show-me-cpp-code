"""Provides the repository macro to import LLVM."""

# load("//:repo.bzl", "tf_http_archive")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo(commit = "12.0.0"):
    maybe(
        http_archive,
        name = "org_llvm_llvm",
        build_file = Label("//third_party/llvm:llvm.BUILD"),
        urls = [
            "https://3rdcpp-1256340525.cos.ap-beijing.myqcloud.com/llvm/llvm-12.0.0.src.tar.xz",
            "https://github.com.cnpmjs.org/llvm/llvm-project/releases/download/llvmorg-{commit}/llvm-{commit}.src.tar.xz".format(commit = commit),
            "https://github.com/llvm/llvm-project/releases/download/llvmorg-{commit}/llvm-{commit}.src.tar.xz".format(commit = commit),
        ],
        strip_prefix = "llvm-{commit}.src".format(commit = commit),
    )
