"""A module defining the third party dependency oneTBB"""

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo(commit = "2021.3.0"):
    maybe(
        git_repository,
        name = "oneTBB",
        branch = "master",
        remote = "https://github.com.cnpmjs.org/oneapi-src/oneTBB/",
    )
