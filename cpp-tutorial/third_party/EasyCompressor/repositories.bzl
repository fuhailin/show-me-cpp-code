load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo():
    # maybe(
    #     git_repository,
    #     name = "compresser",
    #     branch = "master",
    #     remote = "https://github.com.cnpmjs.org/fuhailin/EasyCompressor.git",
    # )
    maybe(
        native.local_repository,
        name = "compressor",
        path = "/home/fuhailin/projects/EasyCompressor",
        # path = "/Users/vincent/Documents/projects/EasyCompressor",
    )
