load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo():
    COMMIT = "a53934a3ae1244679f812d998a4f16f2c7f309a6"
    maybe(
        http_archive,
        name = "com_github_google_leveldb",
        urls = [
            "https://github.com.cnpmjs.org/google/leveldb/archive/{commit}.tar.gz".format(commit = COMMIT),
            "https://github.com/google/leveldb/archive/{commit}.tar.gz".format(commit = COMMIT),
        ],
        strip_prefix = "leveldb-" + COMMIT,
        build_file = Label("//third_party/leveldb:leveldb.BUILD"),
    )
