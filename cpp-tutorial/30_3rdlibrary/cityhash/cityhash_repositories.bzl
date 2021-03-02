"""A module defining the third party dependency cityhash"""

load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def cityhash_repositories():
    maybe(
        new_git_repository,
        name = "cityhash",
        build_file = Label("//cityhash:BUILD.cityhash.bazel"),
        branch = "master",
        remote = "https://github.com/google/cityhash.git",
    )
