load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo(COMMIT = "1.23"):
    maybe(
        http_archive,
        name = "com_github_google_leveldb",
        urls = [
            "https://github.com.cnpmjs.org/google/leveldb/archive/refs/tags/{}.tar.gz".format(COMMIT),
            "https://github.com/google/leveldb/archive/refs/tags/{}.tar.gz".format(COMMIT),
        ],
        strip_prefix = "leveldb-" + COMMIT,
        build_file = Label("//third_party/db/leveldb:leveldb.BUILD"),
    )
