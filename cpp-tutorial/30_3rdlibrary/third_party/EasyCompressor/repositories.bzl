"""A module defining the third party dependency apr"""

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo():
    # native.local_repository(
    #     name = "compresser",
    #     path = "/Users/vincent/Documents/projects/show-me-cpp-code/cpp-tutorial/compresser",
    # )
    # maybe(
    #     git_repository,
    #     name = "compresser",
    #     branch = "master",
    #     remote = "https://gitee.com/fuhailin/compresser.git",
    # )
    maybe(
        native.local_repository,
        name = "compressor",
        path = "/Users/vincent/Documents/projects/EasyCompressor",
    )
