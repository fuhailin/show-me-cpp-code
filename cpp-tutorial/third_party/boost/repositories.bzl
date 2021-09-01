load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo(MAJOR = "1", MINOR = "76", PATCH = "0"):
    maybe(
        http_archive,
        name = "boost",
        urls = [
            "https://dl.bintray.com/boostorg/release/{0}.{1}.{2}/source/boost_{0}_{1}_{2}.tar.gz".format(MAJOR, MINOR, PATCH),
            "https://downloads.sourceforge.net/project/boost/boost/{0}.{1}.{2}/boost_{0}_{1}_{2}.tar.gz".format(MAJOR, MINOR, PATCH),
        ],
        strip_prefix = "boost_{}_{}_{}".format(MAJOR, MINOR, PATCH),
        build_file = Label("//third_party/boost:boost.BUILD"),
    )
