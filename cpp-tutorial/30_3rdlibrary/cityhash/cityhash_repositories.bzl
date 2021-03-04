"""A module defining the third party dependency cityhash"""

# load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def cityhash_repositories():
    # maybe(
    #     new_git_repository,
    #     name = "cityhash",
    #     build_file = Label("//cityhash:cityhash.BUILD"),
    #     branch = "master",
    #     remote = "https://github.com/google/cityhash.git",
    # )
    maybe(
        http_archive,
        name = "cityhash",
        urls = [
            "https://github.com.cnpmjs.org/google/cityhash/archive/8af9b8c2b889d80c22d6bc26ba0df1afb79a30db.tar.gz",
            "https://github.com/google/cityhash/archive/8af9b8c2b889d80c22d6bc26ba0df1afb79a30db.tar.gz",
        ],
        type = "tar.gz",
        strip_prefix = "cityhash-8af9b8c2b889d80c22d6bc26ba0df1afb79a30db",
        build_file = Label("//cityhash:cityhash.BUILD"),
    )
