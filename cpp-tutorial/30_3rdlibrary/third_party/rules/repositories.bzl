"""A module defining the third party dependency rules"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def rules_cc_repo():
    COMMIT = "608c7b605fb844a20e96a3eddc9b49ad2542adab"
    maybe(
        http_archive,
        name = "rules_cc",
        urls = [
            "https://github.com.cnpmjs.org/bazelbuild/rules_cc/archive/{commit}.zip".format(commit = COMMIT),
            "https://hub.fastgit.org/bazelbuild/rules_cc/archive/{commit}.zip".format(commit = COMMIT),
            "https://github.com/bazelbuild/rules_cc/archive/{commit}.zip".format(commit = COMMIT),
        ],
        strip_prefix = "rules_cc-" + COMMIT,
    )

def rules_foreign_cc_repo():
    COMMIT = "ede2c80a51030c8b5b965680c32768b5acb03f95"
    maybe(
        http_archive,
        name = "rules_foreign_cc",
        strip_prefix = "rules_foreign_cc-" + COMMIT,
        urls = [
            # "https://3rdcpp-1256340525.cos.ap-beijing.myqcloud.com/rules_foreign_cc-{commit}.tar.gz".format(commit = COMMIT),
            "https://github.com.cnpmjs.org/bazelbuild/rules_foreign_cc/archive/{commit}.zip".format(commit = COMMIT),
            "https://github.91chifun.workers.dev//https://github.com/bazelbuild/rules_foreign_cc/archive/{commit}.zip".format(commit = COMMIT),
            "https://hub.fastgit.org/bazelbuild/rules_foreign_cc/archive/{commit}.zip".format(commit = COMMIT),
            "https://github.com/bazelbuild/rules_foreign_cc/archive/{commit}.zip".format(commit = COMMIT),
        ],
    )

def rules_proto_repo():
    COMMIT = "84ba6ec814eebbf5312b2cc029256097ae0042c3"
    maybe(
        http_archive,
        name = "rules_proto",
        strip_prefix = "rules_proto-" + COMMIT,
        urls = [
            "https://github.com.cnpmjs.org/bazelbuild/rules_proto/archive/{commit}.tar.gz".format(commit = COMMIT),
            "https://hub.fastgit.org/bazelbuild/rules_proto/archive/{commit}.tar.gz".format(commit = COMMIT),
            "https://mirror.bazel.build/github.com/bazelbuild/rules_proto/archive/{commit}.tar.gz".format(commit = COMMIT),
            "https://github.com/bazelbuild/rules_proto/archive/{commit}.tar.gz".format(commit = COMMIT),
        ],
    )

def rules_boost_repo():
    COMMIT = "c13a880269cc044c4b5e90046625339836771d77"
    maybe(
        http_archive,
        name = "com_github_nelhage_rules_boost",
        urls = [
            "https://3rdcpp-1256340525.cos.ap-beijing.myqcloud.com/rules_boost-{commit}.tar.gz".format(commit = COMMIT),
            "https://github.com/nelhage/rules_boost/archive/{commit}.tar.gz".format(commit = COMMIT),
        ],
        strip_prefix = "rules_boost-" + COMMIT,
    )

# rules_java defines rules for generating Java code from Protocol Buffers.
def rules_java_repo():
    COMMIT = "d7bf804c8731edd232cb061cb2a9fe003a85d8ee"
    maybe(
        http_archive,
        name = "rules_java",
        urls = [
            "https://github.com/bazelbuild/rules_java/archive/{commit}.tar.gz".format(commit = COMMIT),
        ],
        strip_prefix = "rules_java-" + COMMIT,
    )
