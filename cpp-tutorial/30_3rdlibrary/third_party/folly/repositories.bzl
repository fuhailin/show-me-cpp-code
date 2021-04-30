load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo():
    COMMIT = "deb71d745847f5b923ef798fc813d71f5bf9e675"
    maybe(
        http_archive,
        name = "com_github_facebook_folly",
        urls = [
            "https://github.com.cnpmjs.org/facebook/folly/archive/{commit}.tar.gz".format(commit = COMMIT),
            "https://hub.fastgit.org/facebook/folly/archive/{commit}.tar.gz".format(commit = COMMIT),
            "https://github.com/facebook/folly/archive/{commit}.tar.gz".format(commit = COMMIT),
        ],
        strip_prefix = "folly-" + COMMIT,
        build_file = Label("//third_party/folly:folly.BUILD"),
    )
