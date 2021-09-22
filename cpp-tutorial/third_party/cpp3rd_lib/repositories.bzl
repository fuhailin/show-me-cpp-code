load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo():
    # maybe(
    #     git_repository,
    #     name = "rules_compressor",
    #     branch = "main",
    #     remote = "https://github.com/fuhailin/rules_compressor.git",
    # )
    maybe(
        native.local_repository,
        name = "cpp3rd_lib",
        # path = "/root/fuhailin/projects/rules_compressor",
        path = "/Users/vincent/Documents/projects/cpp3rd_lib",
    )
