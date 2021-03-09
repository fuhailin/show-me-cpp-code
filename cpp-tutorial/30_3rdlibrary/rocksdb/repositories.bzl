"""A module defining the third party dependency rocksdb"""

# load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def rocksdb_repo():
    # # COMMIT = "5.13.1"
    # COMMIT = "6.8.1"
    # maybe(
    #     new_http_archive,
    #     name = "rocksdb",
    #     urls = [
    #         "https://github.91chifun.workers.dev/https://github.com//facebook/rocksdb/archive/v{commit}.tar.gz".format(commit = COMMIT),
    #         "https://github.com/facebook/rocksdb/archive/v{commit}.tar.gz".format(commit = COMMIT),
    #     ],
    #     strip_prefix = "rocksdb-" + COMMIT,
    #     build_file = Label("//rocksdb:rocksdb.BUILD"),
    # )
    maybe(
        new_git_repository,
        name = "com_github_facebook_rocksdb",
        build_file = Label("//rocksdb:rocksdb.BUILD"),
        tag = "v6.15.5",
        remote = "https://github.com.cnpmjs.org/facebook/rocksdb.git",
    )
