load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo():
    COMMIT = "c13a880269cc044c4b5e90046625339836771d77"
    maybe(
        http_archive,
        name = "com_github_nelhage_rules_boost",
        urls = [
            "https://github.com.cnpmjs.org/nelhage/rules_boost/archive/{commit}.tar.gz".format(commit = COMMIT),
            "https://hub.fastgit.org/nelhage/rules_boost/archive/{commit}.tar.gz".format(commit = COMMIT),
            "https://github.com/nelhage/rules_boost/archive/{commit}.tar.gz".format(commit = COMMIT),
        ],
        strip_prefix = "rules_boost-" + COMMIT,
    )
